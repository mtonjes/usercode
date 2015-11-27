// -*- C++ -*-
//
// Package:    ForwardAnalyzer
// Class:      ForwardAnalyzer
//
/**\class ForwardAnalyzer ForwardAnalyzer.cc Analyzers/ForwardAnalyzer/src/ForwardAnalyzer.cc

Description: A simple analyzer which can read in Reco or RAW data and makes trees with Reco information and Digi information as well for all of the forward detectors.

90% of this was shamelessly stolen from Pat Kenny's (Kansas) Analyzer

Implementation:
This can be run out of the box with the test cfg or can be installed into a crab.cfg
*/
//
// Original Author: Jaime Arturo Gomez (University of Maryland)
//         Created:  Wed Jan  9 14:43:26 EST 2013
// $Id: ForwardAnalyzer.cc,v 1.14 2013/04/09 19:48:01 jgomez2 Exp $
//
//
#include "Analyzers/ForwardAnalyzer/interface/ForwardAnalyzer.h"
#include "DataFormats/HeavyIonEvent/interface/CentralityBins.h"
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include <iostream>

//static const float HFQIEConst = 4.0;
//static const float HFQIEConst = 2.6;
//static const float EMGain  = 0.025514;
//static const float HADGain = 0.782828;

using namespace edm;
using namespace std;

ForwardAnalyzer::ForwardAnalyzer(const ParameterSet& iConfig)
{
  runBegin = -1;
  evtNo = 0;
  lumibegin = 0;
  lumiend = 0;
  startTime = "Not Avaliable";
//  theTopology(0);
}

ForwardAnalyzer::~ForwardAnalyzer(){}

void ForwardAnalyzer::analyze(const Event& iEvent, const EventSetup& iSetup)
{
  using namespace edm;
  using namespace reco;
  using namespace std;
//  std::cout<<"ForwardAnalyzer::analyze, go!"<<std::endl;
  ++evtNo;
  time_t a = (iEvent.time().value()) >> 32; // store event info
  event = iEvent.id().event();
  run = iEvent.id().run();
  lumi = iEvent.luminosityBlock();
   edm::ESHandle<HcalTopology> htopo;
   iSetup.get<IdealGeometryRecord>().get(htopo);
   theTopology=new HcalTopology(*htopo);
//   myobject->setTopo(theTopology);


  if (runBegin < 0) {         // parameters for the first event
    startTime = ctime(&a);
    lumibegin = lumiend = lumi;
    runBegin = iEvent.id().run();
    Runno=iEvent.id().run();
  }
  if (lumi < lumibegin)lumibegin = lumi;
  if (lumi > lumiend)lumiend = lumi;

  BeamData[0]=iEvent.bunchCrossing();
  BeamData[1]=lumi;
  BeamData[2]=run;
  BeamData[3]=event;


  BeamTree->Fill();



//   std::cout<<"ForwardAnalyzer::analyze, handle ZDCDigi Collection"<<std::endl;

  Handle<ZDCDigiCollection> castorDigis;
//     std::cout<<"ForwardAnalyzer::analyze, now get those HF RecHits"<<std::endl;

  edm::Handle<HFRecHitCollection> hf_recHits_h;
  Handle<CastorRecHitCollection> castor_recHits_h; //added Nov 19 2015 to see if it will make line 83 work
  edm::ESHandle<HcalDbService> conditions;
  iSetup.get<HcalDbRecord>().get(conditions);
 //see below
  iEvent.getByLabel("castor_recHits_h",castor_recHits_h);// changed Nov 19 2015 to use getByLabel instead of getByType. Seems to work ok after adding line 80

//  Handle<reco::EvtPlaneCollection> evtPlanes;
//  iEvent.getByLabel("hiEvtPlane","recoLevel",evtPlanes);


//  if(!evtPlanes.isValid()){
//    return ;
//  }
  

  if (!(iEvent.getByLabel("hfreco",hf_recHits_h)))
    {
      std::cout<<"NO HF, I don't care!!!"<<std::endl;
   //   return;
    }
//         std::cout<<"ForwardAnalyzer::analyze, now get those ZDC digis by label"<<std::endl;

  if (!(iEvent.getByLabel("castorDigis",castorDigis)))
  {
      std::cout<<"No ZDC Digis gotten with label:"<<castorDigis<<std::endl;
      return;
  }
  const ZDCDigiCollection *zdc_digi = castorDigis.failedToGet()? 0 : &*castorDigis;
//  const HFRecHitCollection *hf_recHits = hf_recHits_h.failedToGet()? 0 : &*hf_recHits_h;

  iSetup.get<HcalDbRecord>().get(conditions);

  if(zdc_digi){
    for(int i=0; i<180; i++){DigiDatafC[i]=0;DigiDataADC[i]=0;}
//std::cout<<"ForwardAnalyzer::analyze if(zdc_digi) is fine, now to loop over the digis"<<std::endl;
    for (ZDCDigiCollection::const_iterator j=zdc_digi->begin();j!=zdc_digi->end();j++){
      const ZDCDataFrame digi = (const ZDCDataFrame)(*j);
      int iSide      = digi.id().zside();
      int iSection   = digi.id().section();
      int iChannel   = digi.id().channel();
      int chid = (iSection-1)*5+(iSide+1)/2*9+(iChannel-1);
      
//      std::cout << "ForwardAnalyzer::analyze, looping over digis, at j: "<<j<<std::endl;
//      std::cout<<"ForwardAnalyzer::analyze looping over digis, iSide: "<<iSide<<", iSection: "<<iSection<<", iChannel: "<<iChannel<<", chid: "<<chid<<std::endl;
      //<<

    HcalZDCDetId cell = j->id();
//	const HcalCalibrations& calibrations=conditions->getHcalCalibrations(cell);
	const HcalQIECoder* qiecoder = conditions->getHcalCoder (cell);
	const HcalQIEShape* qieshape = conditions->getHcalShape (qiecoder);
//	HcalCoderDb coder (*qiecoder, *qieshape);

//      const HcalQIEShape* qieshape=conditions->getHcalShape();
//      const HcalQIECoder* qiecoder=conditions->getHcalCoder(digi.id());
      CaloSamples caldigi;
      HcalCoderDb coder(*qiecoder,*qieshape);

      coder.adc2fC(digi,caldigi);

      int fTS = digi.size();
      for (int i = 0; i < fTS; ++i) {
        DigiDatafC[i+chid*10] = caldigi[i];
        DigiDataADC[i+chid*10] = digi[i].adc();
      }
    }

    ZDCDigiTree->Fill();
  }


//   if(hf_recHits){
//     int hf_counter=0;
//     HF_NumberofHits=hf_recHits->size();
//     for (HFRecHitCollection::const_iterator HFiter=hf_recHits->begin();HFiter!=hf_recHits->end();++HFiter){
//       HF_Energy[hf_counter]=HFiter->energy();
//       HcalDetId id(HFiter->detid().rawId());
//       HF_iEta[hf_counter]=id.ieta();
//       HF_iPhi[hf_counter]=id.iphi();
//       HF_Depth[hf_counter]=id.depth();
//       ++hf_counter;
//     }//end of HF RecHits Iterator
//     HFRecoTree->Fill();
//   }//end of if(hf_recHits)

  ///Event Plane Section
//   for (EvtPlaneCollection::const_iterator rp=evtPlanes->begin();rp!=evtPlanes->end();rp++)
//     {
//       if(!rp->label().compare("EvtPlaneFromTracksMidEta"))
//         {
//           EPAngle[0] = rp->angle();
//         }
//       else if(!rp->label().compare("EvtPTracksPosEtaGap"))
//         {
//           // EvtPTracksPosEtaGap = rp->angle();
//           EPAngle[1] = rp->angle();
//         }
//       else if(!rp->label().compare("EvtPTracksNegEtaGap"))
//         {
//           EPAngle[2] = rp->angle();
//           //EvtPTracksNegEtaGap = rp->angle();
//         }
//       else if(!rp->label().compare("EPTracksMid3"))
//         {
//           EPAngle[3] = rp->angle();
//           //EPTracksMid3 = rp->angle();
//         }
//       else if(!rp->label().compare("EPTracksPos3"))
//         {
//           EPAngle[4] = rp->angle();
//           //EPTracksPos3 = rp->angle();
//         }
//       else if(!rp->label().compare("EPTracksNeg3"))
//         {
//           EPAngle[5] = rp->angle();
//           //EPTracksNeg3 = rp->angle();
//         }
//       else if(!rp->label().compare("EPTracksMid4"))
//         {
//           EPAngle[6] = rp->angle();
//           //EPTracksMid4 = rp->angle();
//         }
//       else if(!rp->label().compare("EPTracksPos4"))
//         {
//           EPAngle[7] = rp->angle();
//           //EPTracksPos4 = rp->angle();
//         }
//       else if(!rp->label().compare("EPTracksNeg4"))
//         {
//           EPAngle[8] = rp->angle();
//           //EPTracksNeg4 = rp->angle();
//         }
//       else if(!rp->label().compare("EPTracksMid5"))
//         {
//           EPAngle[9] = rp->angle();
//           //EPTracksMid5 = rp->angle();
//         }
//       else if(!rp->label().compare("EPTracksPos5"))
//         {
//           EPAngle[10] = rp->angle();
//           //EPTracksPos5 = rp->angle();
//         }
//       else if(!rp->label().compare("EPTracksNeg5"))
//         {
//           EPAngle[11] = rp->angle();
//           //EPTracksNeg5 = rp->angle();
//         }
//       else if(!rp->label().compare("EPTracksMid6"))
//         {
//           EPAngle[12] = rp->angle();
//           //EPTracksMid6 = rp->angle();
//         }
//       else if(!rp->label().compare("EPTracksPos6"))
//         {
//           EPAngle[13] = rp->angle();
//           //EPTracksPos6 = rp->angle();
//         }
//       else if(!rp->label().compare("EPTracksNeg6"))
//         {
//           EPAngle[14] = rp->angle();
//           //EPTracksNeg6 = rp->angle();
//         }
//       else if(!rp->label().compare("etEcal"))
//         {
//           EPAngle[15] = rp->angle();
//           //etEcal = rp->angle();
//         }
//       else if(!rp->label().compare("etEcalP"))
//         {
//           EPAngle[16] = rp->angle();
//           //etEcalP = rp->angle();
//         }
//       else if(!rp->label().compare("etEcalM"))
//         {
//           EPAngle[17] = rp->angle();
//           //etEcalM = rp->angle();
//         }
//       else if(!rp->label().compare("etHcal"))
//         {
//           EPAngle[18] = rp->angle();
//           //etHcal = rp->angle();
//         }
//       else if(!rp->label().compare("etHcalP"))
//         {
//           EPAngle[19] = rp->angle();
//           // etHcalP = rp->angle();
//         }
//       else if(!rp->label().compare("etHcalM"))
//         {
//           EPAngle[20] = rp->angle();
//           // etHcalM = rp->angle();
//         }
//       else if(!rp->label().compare("etHF"))
//         {
//           EPAngle[21] = rp->angle();
//           //etHF = rp->angle();
//         }
//       else if(!rp->label().compare("etHFp"))
//         {
//           EPAngle[22] = rp->angle();
//           //etHFp = rp->angle();
//         }
//       else if(!rp->label().compare("etHFm"))
//         {
//           EPAngle[23] = rp->angle();
//           //etHFm = rp->angle();
//         }
//       else if(!rp->label().compare("etHF3"))
//         {
//           EPAngle[24] = rp->angle();
//           //etHF3 = rp->angle();
//         }
//       else if(!rp->label().compare("etHFp3"))
//         {
//           EPAngle[25] = rp->angle();
//           //etHFp3 = rp->angle();
//         }
//       else if(!rp->label().compare("etHFm3"))
//         {
//           EPAngle[26] = rp->angle();
//           // etHFm3 = rp->angle();
//         }
//       else if(!rp->label().compare("etHF4"))
//         {
//           EPAngle[27] = rp->angle();
//           //etHF4 = rp->angle();
//         }
//       else if(!rp->label().compare("etHFp4"))
//         {
//           EPAngle[28] = rp->angle();
//           //etHFp4 = rp->angle();
//         }
//       else if(!rp->label().compare("etHFm4"))
//         {
//           EPAngle[29] = rp->angle();
//           //etHFm4 = rp->angle();
//         }
//       else if(!rp->label().compare("etHF5"))
//         {
//           EPAngle[30] = rp->angle();
//           //etHF5 = rp->angle();
//         }
//       else if(!rp->label().compare("etHFp5"))
//         {
//           EPAngle[31] = rp->angle();
//           //etHFp5 = rp->angle();
//         }
//       else if(!rp->label().compare("etHFm5"))
//         {
//           EPAngle[32] = rp->angle();
//           //etHFm5 = rp->angle();
//         }
//       else if(!rp->label().compare("etHF6"))
//         {
//           EPAngle[33] = rp->angle();
//           //etHF6 = rp->angle();
//         }
//       else if(!rp->label().compare("etHFp6"))
//         {
//           EPAngle[34] = rp->angle();
//           //etHFp6 = rp->angle();
//         }
//       else if(!rp->label().compare("etHFm6"))
//         {
//           EPAngle[35] = rp->angle();
//           //etHFm6 = rp->angle();
//         }
//       else if(!rp->label().compare("etCaloHFP"))
//         {
//           EPAngle[36] = rp->angle();
//           //etCaloHFP = rp->angle();
//         }
//       else if(!rp->label().compare("etCaloHFM"))
//         {
//           EPAngle[37] = rp->angle();
//           //etCaloHFM = rp->angle();
//         }
// 
//     }//end of loop over event planes
//   EventPlaneTree->Fill();

}//end of Analyze


void ForwardAnalyzer::beginJob(){
  mFileServer->file().SetCompressionLevel(9);
  mFileServer->file().cd();

  string bnames[] = {"negEM1","negEM2","negEM3","negEM4","negEM5",
                     "negHD1","negHD2","negHD3","negHD4",
                     "posEM1","posEM2","posEM3","posEM4","posEM5",
                     "posHD1","posHD2","posHD3","posHD4"};
//   string EPNames[]={
//     "EvtPlaneFromTracksMidEta",    "EvtPTracksPosEtaGap",    "EvtPTracksNegEtaGap",
//     "EPTracksMid3",                "EPTracksPos3",           "EPTracksNeg3",
//     "EPTracksMid4",                "EPTracksPos4",           "EPTracksNeg4",
//     "EPTracksMid5",                "EPTracksPos5",           "EPTracksNeg5",
//     "EPTracksMid6",                "EPTracksPos6",           "EPTracksNeg6",
//     "etEcal",                      "etEcalP",                "etEcalM",
//     "etHcal",                      "etHcalP",                "etHcalM",
//     "etHF",                        "etHFp",                  "etHFm",
//     "etHF3",                        "etHFp3",                 "etHFm3",
//     "etHF4",                        "etHFp4",                 "etHFm4",
//     "etHF5",                        "etHFp5",                 "etHFm5",
//     "etHF6",                        "etHFp6",                 "etHFm6",
//     "etCaloHFP",                   "etCaloHFM"
//   };
  BranchNames=bnames;
  ZDCDigiTree = new TTree("ZDCDigiTree","ZDC Digi Tree");

  BeamTree = new TTree("BeamTree","Beam Tree");
//  HFRecoTree = new TTree("HFRecTree","HF RecHit Tree");
//  EventPlaneTree = new TTree("EventPlaneTree","Event Plane Tree");


  for(int i=0; i<18; i++){
    ZDCDigiTree->Branch((bnames[i]+"fC").c_str(),&DigiDatafC[i*10],(bnames[i]+"cFtsz[10]/F").c_str());
    ZDCDigiTree->Branch((bnames[i]+"ADC").c_str(),&DigiDataADC[i*10],(bnames[i]+"ADCtsz[10]/I").c_str());
  }


//   HFRecoTree->Branch("HF_NumberOfHits",&HF_NumberofHits,"HF_NumberOfHits/I");
//   HFRecoTree->Branch("HF_iEta",&HF_iEta,"HF_iEta[HF_NumberOfHits]/F");
//   HFRecoTree->Branch("HF_iPhi",&HF_iPhi,"HF_iPhi[HF_NumberOfHits]/F");
//   HFRecoTree->Branch("HF_Depth",&HF_Depth,"HF_Depth[HF_NumberOfHits]/F");
//   HFRecoTree->Branch("HF_Energy",&HF_Energy,"HF_Energy[HF_NumberOfHits]/F");


  BeamTree->Branch("BunchXing",&BeamData[0],"BunchXing/I");
  BeamTree->Branch("LumiBlock",&BeamData[1],"LumiBlock/I");
  BeamTree->Branch("Run",&BeamData[2],"Run/I");
  BeamTree->Branch("Event",&BeamData[3],"Event/I");

//   BranchNames=EPNames;
//   for (int i=0;i<38;i++)
//     {
//       //EventPlaneTree->Branch("EPAngle",&rpAng,"EPAngle/F");
//       EventPlaneTree->Branch((EPNames[i]).c_str(),&EPAngle[i],(EPNames[i]+"/F").c_str());
//     }
}
