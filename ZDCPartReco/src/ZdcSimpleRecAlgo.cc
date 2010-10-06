#include "RecoLocalCalo/HcalRecAlgos/interface/ZdcSimpleRecAlgo.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "CalibCalorimetry/HcalAlgos/interface/HcalTimeSlew.h"
#include <algorithm> // for "max"
#include <iostream>
#include <math.h>



static double MaximumFractionalError = 0.0005; // 0.05% error allowed from this source

ZdcSimpleRecAlgo::ZdcSimpleRecAlgo(int firstSample, int samplesToAdd, bool correctForTimeslew, bool correctForPulse, float phaseNS, int recoMethod) : 
  firstSample_(firstSample), 
  samplesToAdd_(samplesToAdd),
  recoMethod_(recoMethod),
  correctForTimeslew_(correctForTimeslew) {
  if (correctForPulse) 
    pulseCorr_=std::auto_ptr<HcalPulseContainmentCorrection>(new HcalPulseContainmentCorrection(samplesToAdd_,phaseNS,MaximumFractionalError));
}

ZdcSimpleRecAlgo::ZdcSimpleRecAlgo(int firstSample, int samplesToAdd, int recoMethod) : 
  firstSample_(firstSample), 
  samplesToAdd_(samplesToAdd),
  recoMethod_(recoMethod),
  correctForTimeslew_(false) {
}

/** Timeshift correction for HPDs based on the position of the peak ADC measurement.
    Allows for an accurate determination of the relative phase of the pulse shape from
    the HPD.  Calculated based on a weighted sum of the -1,0,+1 samples relative to the peak
    as follows:  wpksamp = (0*sample[0] + 1*sample[1] + 2*sample[2]) / (sample[0] + sample[1] + sample[2])
    where sample[1] is the maximum ADC sample value.
    static float timeshift_ns_hbheho(float wpksamp);
    Same as above, but for the HF PMTs
    static float timeshift_ns_hf(float wpksamp);
    To first approximation the same method and constant used for hf will be used for ZDC 
**/

static float timeshift_ns_zdc(float wpksamp);

namespace ZdcSimpleRecAlgoImpl {
  template<class Digi, class RecHit>
  inline RecHit reco1(const Digi& digi, const HcalCoder& coder, const HcalCalibrations& calibs, 
		     int ifirst, int n, bool slewCorrect, const HcalPulseContainmentCorrection* corr, HcalTimeSlew::BiasSetting slewFlavor) {
    CaloSamples tool;
    coder.adc2fC(digi,tool);
    double ampl=0; int maxI = -1; double maxA = -1e10; float ta=0;
    double fc_ampl=0;
    for (int i=ifirst; i<tool.size() && i<n+ifirst; i++) {
      int capid=digi[i].capid();
      ta = (tool[i]-calibs.pedestal(capid)); // pedestal subtraction
      fc_ampl+=ta; 
      ta*= calibs.respcorrgain(capid) ; // fC --> GeV
      ampl+=ta;
      if(ta>maxA){
	maxA=ta;
	maxI=i;
      }
    }
    
    float time=-9999;
    ////Cannot calculate time value with max ADC sample at first or last position in window....
    if(maxI==0 || maxI==(tool.size()-1)) {      
      LogDebug("HCAL Pulse") << "ZdcSimpleRecAlgo::reconstruct :" 
					       << " Invalid max amplitude position, " 
					       << " max Amplitude: "<< maxI
					       << " first: "<<ifirst
					       << " last: "<<(tool.size()-1)
					       << std::endl;
    } else {
      maxA=fabs(maxA);
      int capid=digi[maxI-1].capid();
      float t0 = fabs((tool[maxI-1]-calibs.pedestal(capid))*calibs.respcorrgain(capid) );
      capid=digi[maxI+1].capid();
      float t2 = fabs((tool[maxI+1]-calibs.pedestal(capid))*calibs.respcorrgain(capid) );    
      float wpksamp = (t0 + maxA + t2);
      if (wpksamp!=0) wpksamp=(maxA + 2.0*t2) / wpksamp; 
      time = (maxI - digi.presamples())*25.0 + timeshift_ns_zdc(wpksamp);
      if (corr!=0) {
	// Apply phase-based amplitude correction:
	ampl *= corr->getCorrection(fc_ampl);
	//      std::cout << fc_ampl << " --> " << corr->getCorrection(fc_ampl) << std::endl;
      }
    
      if (slewCorrect) time-=HcalTimeSlew::delay(std::max(1.0,fc_ampl),slewFlavor);
    }

    time=time-calibs.timecorr(); // time calibration
    return RecHit(digi.id(),ampl,time);    
  }
}


namespace ZdcSimpleRecAlgoImpl {
  template<class Digi, class RecHit>
  inline RecHit reco2(const Digi& digi, const HcalCoder& coder, const HcalCalibrations& calibs, 
		     int ifirst, int n, bool slewCorrect, const HcalPulseContainmentCorrection* corr, HcalTimeSlew::BiasSetting slewFlavor) {
    CaloSamples tool;
    coder.adc2fC(digi,tool);
    double ampl=0; int maxI = -1; double maxA = -1e10; float ta=0;
    double prenoise = 0; double postnoise = 0; 
    int noiseslices = 0;
    double noise = 0;
    double fc_ampl=0;

    for(int k = 0 ; k < tool.size() && k < ifirst; k++){
      prenoise += tool[k];
      noiseslices++;
    }
    for(int j = (n + ifirst + 1); j <tool.size(); j++){
      postnoise += tool[j];
      noiseslices++;
    }
    
    if(noiseslices != 0)
      noise = (prenoise+postnoise)/float(noiseslices);
    else
      noise = 0;
 
    for (int i=ifirst; i<tool.size() && i<n+ifirst; i++) {
      int capid=digi[i].capid();
      ta = tool[i]-noise;
      LogDebug("HCAL Pulse") <<"ZdcSimpleRecAlgo::reco2, noise: "<<noise<<", tool[i]: "<<tool[i]<<std::endl;
      fc_ampl+=ta; 
      ta*= calibs.respcorrgain(capid) ; // fC --> GeV
      LogDebug("HCAL Pulse") <<"ZdcSimpleRecAlgo::reco2, calibs.respcorrgain(capid)= "<<calibs.respcorrgain(capid)<<std::endl;
      ampl+=ta;
      LogDebug("HCAL Pulse") <<"ZdcSimpleRecAlgo::reco2, TS: "<<i<<", ta: "<<ta<<", ampl: "<<ampl<<std::endl;
      if(ta>maxA){
	maxA=ta;
	maxI=i;
      }
    }

    float time=-9999;
    ////Cannot calculate time value with max ADC sample at first or last position in window....
    if(maxI==0 || maxI==(tool.size()-1)) {      
      LogDebug("HCAL Pulse") << "ZdcSimpleRecAlgo::reco2 :" 
					       << " Invalid max amplitude position, " 
					       << " max Amplitude: "<< maxI
					       << " first: "<<ifirst
					       << " last: "<<(tool.size()-1)
					       << std::endl;
    } else {
//      maxA=fabs(maxA);
      int capid=digi[maxI-1].capid();
//      float t0 = fabs((tool[maxI-1]-calibs.pedestal(capid))*calibs.respcorrgain(capid) );
      LogDebug("HCAL Pulse") <<"ZdcSimpleRecAlgo::reco2, QIE TS-1: "<<tool[maxI-1]<<", QIE TS max: "<<tool[maxI]
            <<", QIE TS+1: "<<tool[maxI+1]<<std::endl;
      float Energy0 = ((tool[maxI-1])*calibs.respcorrgain(capid) );
      capid=digi[maxI].capid();
      float Energy1 = ((tool[maxI])*calibs.respcorrgain(capid) ) ;
      capid=digi[maxI+1].capid();
//      float t2 = fabs((tool[maxI+1]-calibs.pedestal(capid))*calibs.respcorrgain(capid) ); 
      float Energy2 = ((tool[maxI+1])*calibs.respcorrgain(capid) );
      LogDebug("HCAL Pulse") << "ZdcSimpleRecAlgo::reco2 :maxA ="
          <<maxA<<", maxI= "<<maxI<<", Energy0= "<<Energy0<<", Energy1= "<<Energy1
          <<", Energy2 = "<<Energy2<<std::endl;
//
      float TSWeightEnergy = ((maxI-1)*Energy0 + maxI*Energy1 + (maxI+1)*Energy2);
      LogDebug("HCAL Pulse") <<"ZdcSimpleRecAlgo::reco2, TSWeightEnergy = "<<TSWeightEnergy<<std::endl;
      float EnergySum=Energy0+Energy1+Energy2;
      float AvgTSPos=0;
      if (EnergySum!=0) AvgTSPos=TSWeightEnergy/ EnergySum; 
      LogDebug("HCAL Pulse") <<"ZdcSimpleRecAlgo::reco2, AvgTSPos is = "<<AvgTSPos<<std::endl;
      time = (AvgTSPos*25.0);
//      + timeshift_ns_zdc(wpksamp);
      LogDebug("HCAL Pulse") <<"ZdcSimpleRecAlgo::reco2, time = "<<time<<std::endl;
//        <<", timeshift_ns_zdc(EnergySum) = "<<timeshift_ns_zdc(wpksamp)<< std::endl;
      if (corr!=0) {
	// Apply phase-based amplitude correction:
	ampl *= corr->getCorrection(fc_ampl);
	 LogDebug("HCAL Pulse") <<"ZdcSimpleRecAlgo::reco2, phase based amplitude correction: ampl = "<<ampl<<std::endl;
	//std::cout << fc_ampl << " --> " << corr->getCorrection(fc_ampl) << std::endl;
      }  
//      if (slewCorrect) time-=HcalTimeSlew::delay(std::max(1.0,fc_ampl),slewFlavor);
    }

//    time=time-calibs.timecorr(); // time calibration
    return RecHit(digi.id(),ampl,time);    
  }
}

ZDCRecHit ZdcSimpleRecAlgo::reconstruct(const ZDCDataFrame& digi, const HcalCoder& coder, const HcalCalibrations& calibs) const {
 
  if(recoMethod_ == 1)
   return ZdcSimpleRecAlgoImpl::reco1<ZDCDataFrame,ZDCRecHit>(digi,coder,calibs,
							      firstSample_,samplesToAdd_,false,
							      0,
							      HcalTimeSlew::Fast);
  if(recoMethod_ == 2)
   return ZdcSimpleRecAlgoImpl::reco2<ZDCDataFrame,ZDCRecHit>(digi,coder,calibs,
							      firstSample_,samplesToAdd_,false,
							      0,HcalTimeSlew::Fast);

     edm::LogError("ZDCSimpleRecAlgoImpl::reconstruct, recoMethod was not declared");
     throw cms::Exception("ZDCSimpleRecoAlgos::exiting process");
   
}

static const float wpksamp0_zdc = 0.500053;
static const float scale_zdc    = 0.999683;
static const int   num_bins_zdc = 100;

static const float actual_ns_zdc[num_bins_zdc] = {
 0.00250, // 0.000-0.010
 0.08000, // 0.010-0.020
 0.16000, // 0.020-0.030
 0.23750, // 0.030-0.040
 0.31750, // 0.040-0.050
 0.39500, // 0.050-0.060
 0.47500, // 0.060-0.070
 0.55500, // 0.070-0.080
 0.63000, // 0.080-0.090
 0.70000, // 0.090-0.100
 0.77000, // 0.100-0.110
 0.84000, // 0.110-0.120
 0.91000, // 0.120-0.130
 0.98000, // 0.130-0.140
 1.05000, // 0.140-0.150
 1.12000, // 0.150-0.160
 1.19000, // 0.160-0.170
 1.26000, // 0.170-0.180
 1.33000, // 0.180-0.190
 1.40000, // 0.190-0.200
 1.47000, // 0.200-0.210
 1.54000, // 0.210-0.220
 1.61000, // 0.220-0.230
 1.68000, // 0.230-0.240
 1.75000, // 0.240-0.250
 1.82000, // 0.250-0.260
 1.89000, // 0.260-0.270
 1.96000, // 0.270-0.280
 2.03000, // 0.280-0.290
 2.10000, // 0.290-0.300
 2.17000, // 0.300-0.310
 2.24000, // 0.310-0.320
 2.31000, // 0.320-0.330
 2.38000, // 0.330-0.340
 2.45000, // 0.340-0.350
 2.52000, // 0.350-0.360
 2.59000, // 0.360-0.370
 2.68500, // 0.370-0.380
 2.79250, // 0.380-0.390
 2.90250, // 0.390-0.400
 3.01000, // 0.400-0.410
 3.11750, // 0.410-0.420
 3.22500, // 0.420-0.430
 3.33500, // 0.430-0.440
 3.44250, // 0.440-0.450
 3.55000, // 0.450-0.460
 3.73250, // 0.460-0.470
 4.02000, // 0.470-0.480
 4.30750, // 0.480-0.490
 4.59500, // 0.490-0.500
 6.97500, // 0.500-0.510
10.98750, // 0.510-0.520
13.03750, // 0.520-0.530
14.39250, // 0.530-0.540
15.39500, // 0.540-0.550
16.18250, // 0.550-0.560
16.85250, // 0.560-0.570
17.42750, // 0.570-0.580
17.91500, // 0.580-0.590
18.36250, // 0.590-0.600
18.76500, // 0.600-0.610
19.11250, // 0.610-0.620
19.46000, // 0.620-0.630
19.76500, // 0.630-0.640
20.03500, // 0.640-0.650
20.30250, // 0.650-0.660
20.57250, // 0.660-0.670
20.79250, // 0.670-0.680
21.00250, // 0.680-0.690
21.21000, // 0.690-0.700
21.42000, // 0.700-0.710
21.62750, // 0.710-0.720
21.79000, // 0.720-0.730
21.95250, // 0.730-0.740
22.11500, // 0.740-0.750
22.27750, // 0.750-0.760
22.44000, // 0.760-0.770
22.60500, // 0.770-0.780
22.73250, // 0.780-0.790
22.86000, // 0.790-0.800
22.98500, // 0.800-0.810
23.11250, // 0.810-0.820
23.23750, // 0.820-0.830
23.36500, // 0.830-0.840
23.49000, // 0.840-0.850
23.61750, // 0.850-0.860
23.71500, // 0.860-0.870
23.81250, // 0.870-0.880
23.91250, // 0.880-0.890
24.01000, // 0.890-0.900
24.10750, // 0.900-0.910
24.20750, // 0.910-0.920
24.30500, // 0.920-0.930
24.40500, // 0.930-0.940
24.50250, // 0.940-0.950
24.60000, // 0.950-0.960
24.68250, // 0.960-0.970
24.76250, // 0.970-0.980
24.84000, // 0.980-0.990
24.92000  // 0.990-1.000
};

float timeshift_ns_zdc(float wpksamp) {
  float flx = (num_bins_zdc*(wpksamp - wpksamp0_zdc)/scale_zdc);
  int index = (int)flx;
  float yval;
  
  if      (index <    0)        return actual_ns_zdc[0];
  else if (index >= num_bins_zdc-1) return actual_ns_zdc[num_bins_zdc-1];

  // else interpolate:
  float y1       = actual_ns_zdc[index];
  float y2       = actual_ns_zdc[index+1];

  // float delta_x  = 1/(float)num_bins_zdc;
  // yval = y1 + (y2-y1)*(flx-(float)index)/delta_x;

  yval = y1 + (y2-y1)*(flx-(float)index);
  return yval;
}
