#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <TH1F.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TTree.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TFile.h>
#include <TNtuple.h>
#include <TStyle.h>
#include <TStopwatch.h>
#include <TRandom3.h>
#include <TChain.h>
#include <TProfile.h>
#include <TStopwatch.h>
#include <TEventList.h>
#include <TSystem.h>
#include <TCut.h>
#include <cstdlib>
#include <cmath>
#include "TLegend.h"
#include "TLatex.h"
#include "TMath.h"
#include "TLine.h"

#include "/net/hisrv0001/home/belt/wrk/JetRAA/30July/Headers/plot.h"

static const int nbins_pt = 39;
static const double boundaries_pt[nbins_pt+1] = {
  3, 4, 5, 7, 9, 12, 
  15, 18, 21, 24, 28,
  32, 37, 43, 49, 56,
  64, 74, 84, 97, 114,
  133, 153, 174, 196,
  220, 245, 272, 300, 
  330, 362, 395, 430,
  468, 507, 548, 592,
  638, 686, 1000 
};

//these are the only radii we are interested for the RAA analysis: 2,3,4,5
//static const int no_radius = 3; 
//static const int list_radius[no_radius] = {2,3,4};

static const int nbins_cent = 6;
static const Double_t boundaries_cent[nbins_cent+1] = {0,2,4,12,20,28,36};// multiply by 2.5 to get your actual centrality % (old 2011 data) 
//now we have to multiply by 5, since centrality goes from 0-200. 
static const Double_t ncoll[nbins_cent] = { 1660, 1310, 745, 251, 62.8, 10.8 };
static const int trigValue = 4;
static const char trigName [trigValue][256] = {"HLT55","HLT65","HLT80","Combined"};
static const Float_t effecPrescl = 2.047507;
static const char * etaWidth = (char*)"20_eta_20";

int findBin(int bin)
{
  int ibin=-1;
  //! centrality is defined as 0.5% bins of cross section
  //! in 0-200 bins               
  if(bin<=10)ibin=0; //! 0-5%
  else if(bin>10  && bin<=20 )ibin=1; //! 5-10%
  else if(bin>20  && bin<=60 )ibin=2;  //! 10-30%
  else if(bin>60  && bin<=100)ibin=3;  //! 30-50%
  else if(bin>100 && bin<=140)ibin=4;  //! 50-70%
  else if(bin>140 && bin<=180)ibin=5;  //! 70-90%
  else if(bin>180 && bin<=200)ibin=6;  //! 90-100%
  return ibin;
}

static const double cent_HF_bound[] = {0, 0, 4.18352, 6.93443, 7.81838, 8.54289, 9.23664, 9.88781, 10.5473, 11.1902, 11.8706, 12.5891, 13.319, 14.0674, 14.8253, 15.6046, 16.4299, 17.2737, 18.1496, 19.0479, 20.0015, 20.912, 21.9531, 23.0394, 24.1431, 25.328, 26.5151, 27.8044, 29.0709, 30.4214, 31.8381, 33.283, 34.6493, 36.0984, 37.6395, 39.2199, 40.9588, 42.6406, 44.569, 46.3474, 48.2599, 50.2071, 52.3226, 54.5107, 56.9493, 59.3141, 61.7028, 64.244, 66.8831, 69.5266, 72.3771, 75.4711, 78.4157, 81.5896, 84.769, 88.2238, 91.8252, 95.4077, 98.98, 102.798, 106.782, 110.906, 115.16, 119.625, 124.341, 129.065, 133.87, 138.692, 143.708, 149.042, 154.287, 159.825, 165.462, 171.257, 176.947, 183.167, 189.585, 195.883, 202.593, 209.261, 216.241, 223.538, 231.183, 238.531, 246.204, 254.287, 262.356, 270.439, 278.961, 287.651, 297.26, 306.368, 315.948, 325.339, 335.032, 345.099, 355.337, 365.822, 376.405, 387.344, 399.021, 411.008, 422.029, 433.915, 446.391, 458.551, 470.541, 483.077, 495.431, 508.121, 521.027, 534.43, 548.443, 562.924, 576.951, 592.656, 608.19, 623.398, 639.439, 654.628, 670.442, 686.71, 702.497, 719.216, 736.875, 753.611, 771.997, 790, 809.284, 827.785, 846.916, 866.011, 885.882, 904.369, 924.095, 944.936, 966.012, 987.122, 1009.07, 1031.27, 1054.05, 1076.25, 1099.91, 1122.04, 1144.78, 1167.66, 1191.41, 1216.09, 1241.13, 1267.38, 1293.67, 1321.55, 1350.66, 1378.46, 1407.54, 1434.55, 1462.55, 1490.14, 1520.59, 1550.78, 1581.24, 1613.24, 1645.85, 1678.99, 1711.05, 1745.42, 1778.74, 1812.54, 1846.99, 1884.43, 1922.16, 1958.71, 1997.48, 2037.29, 2076.29, 2114.1, 2155.37, 2196.62, 2237.9, 2279.55, 2324.23, 2371.58, 2415.58, 2465.63, 2515.93, 2562.36, 2612.32, 2663.82, 2719.3, 2770.5, 2829.21, 2890.39, 2948.11, 3011.59, 3073.29, 3135.95, 3202.43, 3270.81, 3340.31, 3429.82, 5805.99};
static const int nbins_HF_bound = sizeof(cent_HF_bound)/sizeof(double) -1;

int findHFbin(float HF_energy){
  int ibin = -1;
  for(int k = 0; k<nbins_HF_bound; ++k){
    if(HF_energy > cent_HF_bound[k])
      ibin = 200 - k;
  }
  return ibin;
}


// divide by bin width
// void divideBinWidth(TH1 *h){
//   h->Sumw2();
//   for (int i=0;i<=h->GetNbinsX();i++){
//     Float_t val = h->GetBinContent(i);
//     Float_t valErr = h->GetBinError(i);
//     val/=h->GetBinWidth(i);
//     valErr/=h->GetBinWidth(i);
//     h->SetBinContent(i,val);
//     h->SetBinError(i,valErr);
//   }//binsX loop 
//   h->GetXaxis()->CenterTitle();
//   h->GetYaxis()->CenterTitle();
// }

struct Jet{
  int id;
  float pt;
};
bool compare_pt(Jet jet1, Jet jet2);
bool compare_pt(Jet jet1, Jet jet2){
  return jet1.pt > jet2.pt;
}

using namespace std;

void DrawJetIDVars(int radius=3, std::string kFDataname="/export/d00/scratch/belt/JetRAA/30July/PbPb_Data_jetID_r3.root",
			std::string kFMCname="/export/d00/scratch/belt/JetRAA/30July/PbPb_MC_jetID_r3.root",
		    std::string kFoname="/export/d00/scratch/belt/JetRAA/30July/PbPb_Data_MC_JetIDPlots_r3.root")
{
// open files		      
  TFile *fout = new TFile(kFoname.c_str(),"RECREATE");
  fout->cd();
  TFile *fData = new TFile(kFDataname.c_str());
  TFile *fMC = new TFile(kFMCname.c_str());
// define histograms and counting 
// (note that there's more histograms in the file, they were ones from Raghav's code and I just didn't take them out)
// Data histograms and numbers
  TH1F * hData_chMaxJtpt_jet55_keep[nbins_cent], * hData_phMaxJtpt_jet55_keep[nbins_cent], * hData_neMaxJtpt_jet55_keep[nbins_cent], * hData_muMaxJtpt_jet55_keep[nbins_cent], * hData_eMaxJtpt_jet55_keep[nbins_cent];
  TH1F * hData_chSumJtpt_jet55_keep[nbins_cent], * hData_phSumJtpt_jet55_keep[nbins_cent], * hData_neSumJtpt_jet55_keep[nbins_cent], * hData_muSumJtpt_jet55_keep[nbins_cent], * hData_eSumJtpt_jet55_keep[nbins_cent];  
  TH1F * hData_chMaxJtpt_jet55_rej[nbins_cent], * hData_phMaxJtpt_jet55_rej[nbins_cent], * hData_neMaxJtpt_jet55_rej[nbins_cent], * hData_muMaxJtpt_jet55_rej[nbins_cent], * hData_eMaxJtpt_jet55_rej[nbins_cent];
  TH1F * hData_chSumJtpt_jet55_rej[nbins_cent], * hData_phSumJtpt_jet55_rej[nbins_cent], * hData_neSumJtpt_jet55_rej[nbins_cent], * hData_muSumJtpt_jet55_rej[nbins_cent], * hData_eSumJtpt_jet55_rej[nbins_cent];  
  TH1F * hData_chMaxJtpt_jet65_keep[nbins_cent], * hData_phMaxJtpt_jet65_keep[nbins_cent], * hData_neMaxJtpt_jet65_keep[nbins_cent], * hData_muMaxJtpt_jet65_keep[nbins_cent], * hData_eMaxJtpt_jet65_keep[nbins_cent];
  TH1F * hData_chSumJtpt_jet65_keep[nbins_cent], * hData_phSumJtpt_jet65_keep[nbins_cent], * hData_neSumJtpt_jet65_keep[nbins_cent], * hData_muSumJtpt_jet65_keep[nbins_cent], * hData_eSumJtpt_jet65_keep[nbins_cent];  
  TH1F * hData_chMaxJtpt_jet65_rej[nbins_cent], * hData_phMaxJtpt_jet65_rej[nbins_cent], * hData_neMaxJtpt_jet65_rej[nbins_cent], * hData_muMaxJtpt_jet65_rej[nbins_cent], * hData_eMaxJtpt_jet65_rej[nbins_cent];
  TH1F * hData_chSumJtpt_jet65_rej[nbins_cent], * hData_phSumJtpt_jet65_rej[nbins_cent], * hData_neSumJtpt_jet65_rej[nbins_cent], * hData_muSumJtpt_jet65_rej[nbins_cent], * hData_eSumJtpt_jet65_rej[nbins_cent];  
  TH1F * hData_chMaxJtpt_jet80_keep[nbins_cent], * hData_phMaxJtpt_jet80_keep[nbins_cent], * hData_neMaxJtpt_jet80_keep[nbins_cent], * hData_muMaxJtpt_jet80_keep[nbins_cent], * hData_eMaxJtpt_jet80_keep[nbins_cent];
  TH1F * hData_chSumJtpt_jet80_keep[nbins_cent], * hData_phSumJtpt_jet80_keep[nbins_cent], * hData_neSumJtpt_jet80_keep[nbins_cent], * hData_muSumJtpt_jet80_keep[nbins_cent], * hData_eSumJtpt_jet80_keep[nbins_cent];  
  TH1F * hData_chMaxJtpt_jet80_rej[nbins_cent], * hData_phMaxJtpt_jet80_rej[nbins_cent], * hData_neMaxJtpt_jet80_rej[nbins_cent], * hData_muMaxJtpt_jet80_rej[nbins_cent], * hData_eMaxJtpt_jet80_rej[nbins_cent];
  TH1F * hData_chSumJtpt_jet80_rej[nbins_cent], * hData_phSumJtpt_jet80_rej[nbins_cent], * hData_neSumJtpt_jet80_rej[nbins_cent], * hData_muSumJtpt_jet80_rej[nbins_cent], * hData_eSumJtpt_jet80_rej[nbins_cent];  
  TH1F * hData_trkMaxJtpt_jet55_keep[nbins_cent]; 
  TH1F * hData_trkMaxJtpt_jet55_rej[nbins_cent]; 
  TH1F * hData_trkMaxJtpt_jet65_keep[nbins_cent]; 
  TH1F * hData_trkMaxJtpt_jet65_rej[nbins_cent]; 
  TH1F * hData_trkMaxJtpt_jet80_keep[nbins_cent]; 
  TH1F * hData_trkMaxJtpt_jet80_rej[nbins_cent]; 
//  TH1F * hData_trSumJtpt_jet55_keep[nbins_cent] ;
//  TH1F * hData_trSumJtpt_jet55_rej[nbins_cent] ;
//  TH1F * hData_trSumJtpt_jet65_keep[nbins_cent] ;
//  TH1F * hData_trSumJtpt_jet65_rej[nbins_cent] ;
//  TH1F * hData_trSumJtpt_jet80_keep[nbins_cent] ;
//  TH1F * hData_trSumJtpt_jet80_rej[nbins_cent] ;  

  Double_t  nData_chMaxJtpt_jet55_keep[nbins_cent],  nData_phMaxJtpt_jet55_keep[nbins_cent],  nData_neMaxJtpt_jet55_keep[nbins_cent],  nData_muMaxJtpt_jet55_keep[nbins_cent],  nData_eMaxJtpt_jet55_keep[nbins_cent];
  Double_t  nData_chSumJtpt_jet55_keep[nbins_cent],  nData_phSumJtpt_jet55_keep[nbins_cent],  nData_neSumJtpt_jet55_keep[nbins_cent],  nData_muSumJtpt_jet55_keep[nbins_cent],  nData_eSumJtpt_jet55_keep[nbins_cent];  
  Double_t  nData_chMaxJtpt_jet55_rej[nbins_cent],  nData_phMaxJtpt_jet55_rej[nbins_cent],  nData_neMaxJtpt_jet55_rej[nbins_cent],  nData_muMaxJtpt_jet55_rej[nbins_cent],  nData_eMaxJtpt_jet55_rej[nbins_cent];
  Double_t  nData_chSumJtpt_jet55_rej[nbins_cent],  nData_phSumJtpt_jet55_rej[nbins_cent],  nData_neSumJtpt_jet55_rej[nbins_cent],  nData_muSumJtpt_jet55_rej[nbins_cent],  nData_eSumJtpt_jet55_rej[nbins_cent];  
  Double_t  nData_chMaxJtpt_jet65_keep[nbins_cent],  nData_phMaxJtpt_jet65_keep[nbins_cent],  nData_neMaxJtpt_jet65_keep[nbins_cent],  nData_muMaxJtpt_jet65_keep[nbins_cent],  nData_eMaxJtpt_jet65_keep[nbins_cent];
  Double_t  nData_chSumJtpt_jet65_keep[nbins_cent],  nData_phSumJtpt_jet65_keep[nbins_cent],  nData_neSumJtpt_jet65_keep[nbins_cent],  nData_muSumJtpt_jet65_keep[nbins_cent],  nData_eSumJtpt_jet65_keep[nbins_cent];  
  Double_t  nData_chMaxJtpt_jet65_rej[nbins_cent],  nData_phMaxJtpt_jet65_rej[nbins_cent],  nData_neMaxJtpt_jet65_rej[nbins_cent],  nData_muMaxJtpt_jet65_rej[nbins_cent],  nData_eMaxJtpt_jet65_rej[nbins_cent];
  Double_t  nData_chSumJtpt_jet65_rej[nbins_cent],  nData_phSumJtpt_jet65_rej[nbins_cent],  nData_neSumJtpt_jet65_rej[nbins_cent],  nData_muSumJtpt_jet65_rej[nbins_cent],  nData_eSumJtpt_jet65_rej[nbins_cent];  
  Double_t  nData_chMaxJtpt_jet80_keep[nbins_cent],  nData_phMaxJtpt_jet80_keep[nbins_cent],  nData_neMaxJtpt_jet80_keep[nbins_cent],  nData_muMaxJtpt_jet80_keep[nbins_cent],  nData_eMaxJtpt_jet80_keep[nbins_cent];
  Double_t  nData_chSumJtpt_jet80_keep[nbins_cent],  nData_phSumJtpt_jet80_keep[nbins_cent],  nData_neSumJtpt_jet80_keep[nbins_cent],  nData_muSumJtpt_jet80_keep[nbins_cent],  nData_eSumJtpt_jet80_keep[nbins_cent];  
  Double_t  nData_chMaxJtpt_jet80_rej[nbins_cent],  nData_phMaxJtpt_jet80_rej[nbins_cent],  nData_neMaxJtpt_jet80_rej[nbins_cent],  nData_muMaxJtpt_jet80_rej[nbins_cent],  nData_eMaxJtpt_jet80_rej[nbins_cent];
  Double_t  nData_chSumJtpt_jet80_rej[nbins_cent],  nData_phSumJtpt_jet80_rej[nbins_cent],  nData_neSumJtpt_jet80_rej[nbins_cent],  nData_muSumJtpt_jet80_rej[nbins_cent],  nData_eSumJtpt_jet80_rej[nbins_cent];  
 Double_t  nData_trkMaxJtpt_jet55_keep[nbins_cent];
// Double_t nData_trSumJtpt_jet55_keep[nbins_cent];
 Double_t  nData_trkMaxJtpt_jet65_keep[nbins_cent];
// Double_t nData_trSumJtpt_jet65_keep[nbins_cent];
 Double_t  nData_trkMaxJtpt_jet80_keep[nbins_cent];
// Double_t nData_trSumJtpt_jet80_keep[nbins_cent];
 Double_t  nData_trkMaxJtpt_jet55_rej[nbins_cent];
// Double_t nData_trSumJtpt_jet55_rej[nbins_cent];
 Double_t  nData_trkMaxJtpt_jet65_rej[nbins_cent];
// Double_t nData_trSumJtpt_jet65_rej[nbins_cent];
 Double_t  nData_trkMaxJtpt_jet80_rej[nbins_cent];
// Double_t nData_trSumJtpt_jet80_rej[nbins_cent];
  TH1F *hData_trkMaxJtpt_Matched_keep[nbins_cent];
  TH1F *hData_trkMaxJtpt_Unmatched_keep[nbins_cent];
  TH1F *hData_trkMaxJtpt_jet55_Matched_keep[nbins_cent];
  TH1F *hData_trkMaxJtpt_jet55_Unmatched_keep[nbins_cent];
  TH1F *hData_trkMaxJtpt_jet65_Matched_keep[nbins_cent];
  TH1F *hData_trkMaxJtpt_jet65_Unmatched_keep[nbins_cent];
  TH1F *hData_trkMaxJtpt_jet80_Matched_keep[nbins_cent];
  TH1F *hData_trkMaxJtpt_jet80_Unmatched_keep[nbins_cent];
  Double_t nData_trkMaxJtpt_Matched_keep[nbins_cent];
  Double_t nData_trkMaxJtpt_Unmatched_keep[nbins_cent];
  Double_t nData_trkMaxJtpt_jet55_Matched_keep[nbins_cent];
  Double_t nData_trkMaxJtpt_jet55_Unmatched_keep[nbins_cent];
  Double_t nData_trkMaxJtpt_jet65_Matched_keep[nbins_cent];
  Double_t nData_trkMaxJtpt_jet65_Unmatched_keep[nbins_cent];
  Double_t nData_trkMaxJtpt_jet80_Matched_keep[nbins_cent];
  Double_t nData_trkMaxJtpt_jet80_Unmatched_keep[nbins_cent];   
// MC histograms and numbers
  TH1F * hMC_chMaxJtpt_jet55_keep[nbins_cent], * hMC_phMaxJtpt_jet55_keep[nbins_cent], * hMC_neMaxJtpt_jet55_keep[nbins_cent], * hMC_muMaxJtpt_jet55_keep[nbins_cent], * hMC_eMaxJtpt_jet55_keep[nbins_cent];
  TH1F * hMC_chSumJtpt_jet55_keep[nbins_cent], * hMC_phSumJtpt_jet55_keep[nbins_cent], * hMC_neSumJtpt_jet55_keep[nbins_cent], * hMC_muSumJtpt_jet55_keep[nbins_cent], * hMC_eSumJtpt_jet55_keep[nbins_cent];  
  TH1F * hMC_chMaxJtpt_jet55_rej[nbins_cent], * hMC_phMaxJtpt_jet55_rej[nbins_cent], * hMC_neMaxJtpt_jet55_rej[nbins_cent], * hMC_muMaxJtpt_jet55_rej[nbins_cent], * hMC_eMaxJtpt_jet55_rej[nbins_cent];
  TH1F * hMC_chSumJtpt_jet55_rej[nbins_cent], * hMC_phSumJtpt_jet55_rej[nbins_cent], * hMC_neSumJtpt_jet55_rej[nbins_cent], * hMC_muSumJtpt_jet55_rej[nbins_cent], * hMC_eSumJtpt_jet55_rej[nbins_cent];  
  TH1F * hMC_chMaxJtpt_jet65_keep[nbins_cent], * hMC_phMaxJtpt_jet65_keep[nbins_cent], * hMC_neMaxJtpt_jet65_keep[nbins_cent], * hMC_muMaxJtpt_jet65_keep[nbins_cent], * hMC_eMaxJtpt_jet65_keep[nbins_cent];
  TH1F * hMC_chSumJtpt_jet65_keep[nbins_cent], * hMC_phSumJtpt_jet65_keep[nbins_cent], * hMC_neSumJtpt_jet65_keep[nbins_cent], * hMC_muSumJtpt_jet65_keep[nbins_cent], * hMC_eSumJtpt_jet65_keep[nbins_cent];  
  TH1F * hMC_chMaxJtpt_jet65_rej[nbins_cent], * hMC_phMaxJtpt_jet65_rej[nbins_cent], * hMC_neMaxJtpt_jet65_rej[nbins_cent], * hMC_muMaxJtpt_jet65_rej[nbins_cent], * hMC_eMaxJtpt_jet65_rej[nbins_cent];
  TH1F * hMC_chSumJtpt_jet65_rej[nbins_cent], * hMC_phSumJtpt_jet65_rej[nbins_cent], * hMC_neSumJtpt_jet65_rej[nbins_cent], * hMC_muSumJtpt_jet65_rej[nbins_cent], * hMC_eSumJtpt_jet65_rej[nbins_cent];  
  TH1F * hMC_chMaxJtpt_jet80_keep[nbins_cent], * hMC_phMaxJtpt_jet80_keep[nbins_cent], * hMC_neMaxJtpt_jet80_keep[nbins_cent], * hMC_muMaxJtpt_jet80_keep[nbins_cent], * hMC_eMaxJtpt_jet80_keep[nbins_cent];
  TH1F * hMC_chSumJtpt_jet80_keep[nbins_cent], * hMC_phSumJtpt_jet80_keep[nbins_cent], * hMC_neSumJtpt_jet80_keep[nbins_cent], * hMC_muSumJtpt_jet80_keep[nbins_cent], * hMC_eSumJtpt_jet80_keep[nbins_cent];  
  TH1F * hMC_chMaxJtpt_jet80_rej[nbins_cent], * hMC_phMaxJtpt_jet80_rej[nbins_cent], * hMC_neMaxJtpt_jet80_rej[nbins_cent], * hMC_muMaxJtpt_jet80_rej[nbins_cent], * hMC_eMaxJtpt_jet80_rej[nbins_cent];
  TH1F * hMC_chSumJtpt_jet80_rej[nbins_cent], * hMC_phSumJtpt_jet80_rej[nbins_cent], * hMC_neSumJtpt_jet80_rej[nbins_cent], * hMC_muSumJtpt_jet80_rej[nbins_cent], * hMC_eSumJtpt_jet80_rej[nbins_cent];  
  TH1F * hMC_trkMaxJtpt_jet55_keep[nbins_cent]; 
  TH1F * hMC_trkMaxJtpt_jet65_keep[nbins_cent]; 
  TH1F * hMC_trkMaxJtpt_jet80_keep[nbins_cent]; 
//  TH1F * hMC_trSumJtpt_jet55_keep[nbins_cent] ;
//  TH1F * hMC_trSumJtpt_jet65_keep[nbins_cent] ;
//  TH1F * hMC_trSumJtpt_jet80_keep[nbins_cent] ;
  TH1F * hMC_trkMaxJtpt_jet55_rej[nbins_cent]; 
  TH1F * hMC_trkMaxJtpt_jet65_rej[nbins_cent]; 
  TH1F * hMC_trkMaxJtpt_jet80_rej[nbins_cent]; 
//  TH1F * hMC_trSumJtpt_jet55_rej[nbins_cent] ;
//  TH1F * hMC_trSumJtpt_jet65_rej[nbins_cent] ;
//  TH1F * hMC_trSumJtpt_jet80_rej[nbins_cent] ;
  Double_t  nMC_chMaxJtpt_jet55_keep[nbins_cent],  nMC_phMaxJtpt_jet55_keep[nbins_cent],  nMC_neMaxJtpt_jet55_keep[nbins_cent],  nMC_muMaxJtpt_jet55_keep[nbins_cent],  nMC_eMaxJtpt_jet55_keep[nbins_cent];
  Double_t  nMC_chSumJtpt_jet55_keep[nbins_cent],  nMC_phSumJtpt_jet55_keep[nbins_cent],  nMC_neSumJtpt_jet55_keep[nbins_cent],  nMC_muSumJtpt_jet55_keep[nbins_cent],  nMC_eSumJtpt_jet55_keep[nbins_cent];  
  Double_t  nMC_chMaxJtpt_jet55_rej[nbins_cent],  nMC_phMaxJtpt_jet55_rej[nbins_cent],  nMC_neMaxJtpt_jet55_rej[nbins_cent],  nMC_muMaxJtpt_jet55_rej[nbins_cent],  nMC_eMaxJtpt_jet55_rej[nbins_cent];
  Double_t  nMC_chSumJtpt_jet55_rej[nbins_cent],  nMC_phSumJtpt_jet55_rej[nbins_cent],  nMC_neSumJtpt_jet55_rej[nbins_cent],  nMC_muSumJtpt_jet55_rej[nbins_cent],  nMC_eSumJtpt_jet55_rej[nbins_cent];  
  Double_t  nMC_chMaxJtpt_jet65_keep[nbins_cent],  nMC_phMaxJtpt_jet65_keep[nbins_cent],  nMC_neMaxJtpt_jet65_keep[nbins_cent],  nMC_muMaxJtpt_jet65_keep[nbins_cent],  nMC_eMaxJtpt_jet65_keep[nbins_cent];
  Double_t  nMC_chSumJtpt_jet65_keep[nbins_cent],  nMC_phSumJtpt_jet65_keep[nbins_cent],  nMC_neSumJtpt_jet65_keep[nbins_cent],  nMC_muSumJtpt_jet65_keep[nbins_cent],  nMC_eSumJtpt_jet65_keep[nbins_cent];  
  Double_t  nMC_chMaxJtpt_jet65_rej[nbins_cent],  nMC_phMaxJtpt_jet65_rej[nbins_cent],  nMC_neMaxJtpt_jet65_rej[nbins_cent],  nMC_muMaxJtpt_jet65_rej[nbins_cent],  nMC_eMaxJtpt_jet65_rej[nbins_cent];
  Double_t  nMC_chSumJtpt_jet65_rej[nbins_cent],  nMC_phSumJtpt_jet65_rej[nbins_cent],  nMC_neSumJtpt_jet65_rej[nbins_cent],  nMC_muSumJtpt_jet65_rej[nbins_cent],  nMC_eSumJtpt_jet65_rej[nbins_cent];  
  Double_t  nMC_chMaxJtpt_jet80_keep[nbins_cent],  nMC_phMaxJtpt_jet80_keep[nbins_cent],  nMC_neMaxJtpt_jet80_keep[nbins_cent],  nMC_muMaxJtpt_jet80_keep[nbins_cent],  nMC_eMaxJtpt_jet80_keep[nbins_cent];
  Double_t  nMC_chSumJtpt_jet80_keep[nbins_cent],  nMC_phSumJtpt_jet80_keep[nbins_cent],  nMC_neSumJtpt_jet80_keep[nbins_cent],  nMC_muSumJtpt_jet80_keep[nbins_cent],  nMC_eSumJtpt_jet80_keep[nbins_cent];  
  Double_t  nMC_chMaxJtpt_jet80_rej[nbins_cent],  nMC_phMaxJtpt_jet80_rej[nbins_cent],  nMC_neMaxJtpt_jet80_rej[nbins_cent],  nMC_muMaxJtpt_jet80_rej[nbins_cent],  nMC_eMaxJtpt_jet80_rej[nbins_cent];
  Double_t  nMC_chSumJtpt_jet80_rej[nbins_cent],  nMC_phSumJtpt_jet80_rej[nbins_cent],  nMC_neSumJtpt_jet80_rej[nbins_cent],  nMC_muSumJtpt_jet80_rej[nbins_cent],  nMC_eSumJtpt_jet80_rej[nbins_cent];  
 Double_t  nMC_trkMaxJtpt_jet55_keep[nbins_cent];
// Double_t nMC_trSumJtpt_jet55_keep[nbins_cent];
 Double_t  nMC_trkMaxJtpt_jet65_keep[nbins_cent];
// Double_t nMC_trSumJtpt_jet65_keep[nbins_cent];
 Double_t  nMC_trkMaxJtpt_jet80_keep[nbins_cent];
// Double_t nMC_trSumJtpt_jet80_keep[nbins_cent];
 Double_t  nMC_trkMaxJtpt_jet55_rej[nbins_cent];
// Double_t nMC_trSumJtpt_jet55_rej[nbins_cent];
 Double_t  nMC_trkMaxJtpt_jet65_rej[nbins_cent];
// Double_t nMC_trSumJtpt_jet65_rej[nbins_cent];
 Double_t  nMC_trkMaxJtpt_jet80_rej[nbins_cent];
// Double_t nMC_trSumJtpt_jet80_rej[nbins_cent];
  TH1F *hMC_trkMaxJtpt_Matched_keep[nbins_cent];
  TH1F *hMC_trkMaxJtpt_jet55_Matched_keep[nbins_cent];
  TH1F *hMC_trkMaxJtpt_jet65_Matched_keep[nbins_cent];
  TH1F *hMC_trkMaxJtpt_jet80_Matched_keep[nbins_cent];
  Double_t nMC_trkMaxJtpt_Matched_keep[nbins_cent];
  Double_t nMC_trkMaxJtpt_jet55_Matched_keep[nbins_cent];
  Double_t nMC_trkMaxJtpt_jet65_Matched_keep[nbins_cent];
  Double_t nMC_trkMaxJtpt_jet80_Matched_keep[nbins_cent];  
// get histograms (put them in one file incidentally, although it'll keep rebinned versions maybe)
  for(int i = 0;i<nbins_cent;++i){
// Data  
    hData_chMaxJtpt_jet55_keep[i] = (TH1F*)fData->Get(Form("hData_chMaxJtpt_jet55_keep_cent%d",i));
    hData_chSumJtpt_jet55_keep[i] = (TH1F*)fData->Get(Form("hData_chSumJtpt_jet55_keep_cent%d",i));
    hData_eMaxJtpt_jet55_keep[i] = (TH1F*)fData->Get(Form("hData_eMaxJtpt_jet55_keep_cent%d",i));
    hData_eSumJtpt_jet55_keep[i] = (TH1F*)fData->Get(Form("hData_eSumJtpt_jet55_keep_cent%d",i));
    hData_neMaxJtpt_jet55_keep[i] = (TH1F*)fData->Get(Form("hData_neMaxJtpt_jet55_keep_cent%d",i));
    hData_neSumJtpt_jet55_keep[i] = (TH1F*)fData->Get(Form("hData_neSumJtpt_jet55_keep_cent%d",i));
    hData_phMaxJtpt_jet55_keep[i] = (TH1F*)fData->Get(Form("hData_phMaxJtpt_jet55_keep_cent%d",i));
    hData_phSumJtpt_jet55_keep[i] = (TH1F*)fData->Get(Form("hData_phSumJtpt_jet55_keep_cent%d",i));
    hData_muMaxJtpt_jet55_keep[i] = (TH1F*)fData->Get(Form("hData_muMaxJtpt_jet55_keep_cent%d",i));
    hData_muSumJtpt_jet55_keep[i] = (TH1F*)fData->Get(Form("hData_muSumJtpt_jet55_keep_cent%d",i));
    hData_chMaxJtpt_jet55_rej[i] = (TH1F*)fData->Get(Form("hData_chMaxJtpt_jet55_rej_cent%d",i));
    hData_chSumJtpt_jet55_rej[i] = (TH1F*)fData->Get(Form("hData_chSumJtpt_jet55_rej_cent%d",i));
    hData_eMaxJtpt_jet55_rej[i] = (TH1F*)fData->Get(Form("hData_eMaxJtpt_jet55_rej_cent%d",i));
    hData_eSumJtpt_jet55_rej[i] = (TH1F*)fData->Get(Form("hData_eSumJtpt_jet55_rej_cent%d",i));
    hData_neMaxJtpt_jet55_rej[i] = (TH1F*)fData->Get(Form("hData_neMaxJtpt_jet55_rej_cent%d",i));
    hData_neSumJtpt_jet55_rej[i] = (TH1F*)fData->Get(Form("hData_neSumJtpt_jet55_rej_cent%d",i));
    hData_phMaxJtpt_jet55_rej[i] = (TH1F*)fData->Get(Form("hData_phMaxJtpt_jet55_rej_cent%d",i));
    hData_phSumJtpt_jet55_rej[i] = (TH1F*)fData->Get(Form("hData_phSumJtpt_jet55_rej_cent%d",i));
    hData_muMaxJtpt_jet55_rej[i] = (TH1F*)fData->Get(Form("hData_muMaxJtpt_jet55_rej_cent%d",i));
    hData_muSumJtpt_jet55_rej[i] = (TH1F*)fData->Get(Form("hData_muSumJtpt_jet55_rej_cent%d",i));
    hData_chMaxJtpt_jet65_keep[i] = (TH1F*)fData->Get(Form("hData_chMaxJtpt_jet65_keep_cent%d",i));
    hData_chSumJtpt_jet65_keep[i] = (TH1F*)fData->Get(Form("hData_chSumJtpt_jet65_keep_cent%d",i));
    hData_eMaxJtpt_jet65_keep[i] = (TH1F*)fData->Get(Form("hData_eMaxJtpt_jet65_keep_cent%d",i));
    hData_eSumJtpt_jet65_keep[i] = (TH1F*)fData->Get(Form("hData_eSumJtpt_jet65_keep_cent%d",i));
    hData_neMaxJtpt_jet65_keep[i] = (TH1F*)fData->Get(Form("hData_neMaxJtpt_jet65_keep_cent%d",i));
    hData_neSumJtpt_jet65_keep[i] = (TH1F*)fData->Get(Form("hData_neSumJtpt_jet65_keep_cent%d",i));
    hData_phMaxJtpt_jet65_keep[i] = (TH1F*)fData->Get(Form("hData_phMaxJtpt_jet65_keep_cent%d",i));
    hData_phSumJtpt_jet65_keep[i] = (TH1F*)fData->Get(Form("hData_phSumJtpt_jet65_keep_cent%d",i));
    hData_muMaxJtpt_jet65_keep[i] = (TH1F*)fData->Get(Form("hData_muMaxJtpt_jet65_keep_cent%d",i));
    hData_muSumJtpt_jet65_keep[i] = (TH1F*)fData->Get(Form("hData_muSumJtpt_jet65_keep_cent%d",i));
    hData_chMaxJtpt_jet65_rej[i] = (TH1F*)fData->Get(Form("hData_chMaxJtpt_jet65_rej_cent%d",i));
    hData_chSumJtpt_jet65_rej[i] = (TH1F*)fData->Get(Form("hData_chSumJtpt_jet65_rej_cent%d",i));
    hData_eMaxJtpt_jet65_rej[i] = (TH1F*)fData->Get(Form("hData_eMaxJtpt_jet65_rej_cent%d",i));
    hData_eSumJtpt_jet65_rej[i] = (TH1F*)fData->Get(Form("hData_eSumJtpt_jet65_rej_cent%d",i));
    hData_neMaxJtpt_jet65_rej[i] = (TH1F*)fData->Get(Form("hData_neMaxJtpt_jet65_rej_cent%d",i));
    hData_neSumJtpt_jet65_rej[i] = (TH1F*)fData->Get(Form("hData_neSumJtpt_jet65_rej_cent%d",i));
    hData_phMaxJtpt_jet65_rej[i] = (TH1F*)fData->Get(Form("hData_phMaxJtpt_jet65_rej_cent%d",i));
    hData_phSumJtpt_jet65_rej[i] = (TH1F*)fData->Get(Form("hData_phSumJtpt_jet65_rej_cent%d",i));
    hData_muMaxJtpt_jet65_rej[i] = (TH1F*)fData->Get(Form("hData_muMaxJtpt_jet65_rej_cent%d",i));
    hData_muSumJtpt_jet65_rej[i] = (TH1F*)fData->Get(Form("hData_muSumJtpt_jet65_rej_cent%d",i));
    hData_chMaxJtpt_jet80_keep[i] = (TH1F*)fData->Get(Form("hData_chMaxJtpt_jet80_keep_cent%d",i));
    hData_chSumJtpt_jet80_keep[i] = (TH1F*)fData->Get(Form("hData_chSumJtpt_jet80_keep_cent%d",i));
    hData_eMaxJtpt_jet80_keep[i] = (TH1F*)fData->Get(Form("hData_eMaxJtpt_jet80_keep_cent%d",i));
    hData_eSumJtpt_jet80_keep[i] = (TH1F*)fData->Get(Form("hData_eSumJtpt_jet80_keep_cent%d",i));
    hData_neMaxJtpt_jet80_keep[i] = (TH1F*)fData->Get(Form("hData_neMaxJtpt_jet80_keep_cent%d",i));
    hData_neSumJtpt_jet80_keep[i] = (TH1F*)fData->Get(Form("hData_neSumJtpt_jet80_keep_cent%d",i));
    hData_phMaxJtpt_jet80_keep[i] = (TH1F*)fData->Get(Form("hData_phMaxJtpt_jet80_keep_cent%d",i));
    hData_phSumJtpt_jet80_keep[i] = (TH1F*)fData->Get(Form("hData_phSumJtpt_jet80_keep_cent%d",i));
    hData_muMaxJtpt_jet80_keep[i] = (TH1F*)fData->Get(Form("hData_muMaxJtpt_jet80_keep_cent%d",i));
    hData_muSumJtpt_jet80_keep[i] = (TH1F*)fData->Get(Form("hData_muSumJtpt_jet80_keep_cent%d",i));
    hData_chMaxJtpt_jet80_rej[i] = (TH1F*)fData->Get(Form("hData_chMaxJtpt_jet80_rej_cent%d",i));
    hData_chSumJtpt_jet80_rej[i] = (TH1F*)fData->Get(Form("hData_chSumJtpt_jet80_rej_cent%d",i));
    hData_eMaxJtpt_jet80_rej[i] = (TH1F*)fData->Get(Form("hData_eMaxJtpt_jet80_rej_cent%d",i));
    hData_eSumJtpt_jet80_rej[i] = (TH1F*)fData->Get(Form("hData_eSumJtpt_jet80_rej_cent%d",i));
    hData_neMaxJtpt_jet80_rej[i] = (TH1F*)fData->Get(Form("hData_neMaxJtpt_jet80_rej_cent%d",i));
    hData_neSumJtpt_jet80_rej[i] = (TH1F*)fData->Get(Form("hData_neSumJtpt_jet80_rej_cent%d",i));
    hData_phMaxJtpt_jet80_rej[i] = (TH1F*)fData->Get(Form("hData_phMaxJtpt_jet80_rej_cent%d",i));
    hData_phSumJtpt_jet80_rej[i] = (TH1F*)fData->Get(Form("hData_phSumJtpt_jet80_rej_cent%d",i));
    hData_muMaxJtpt_jet80_rej[i] = (TH1F*)fData->Get(Form("hData_muMaxJtpt_jet80_rej_cent%d",i));
    hData_muSumJtpt_jet80_rej[i] = (TH1F*)fData->Get(Form("hData_muSumJtpt_jet80_rej_cent%d",i));
//     hData_trkMaxJtpt_jet55_keep[i] = (TH1F*)fData->Get(Form("hData_trkMaxJtpt_jet55_keep_cent%d",i));
 //    hData_trSumJtpt_jet55_keep[i] = (TH1F*)fData->Get(Form("hData_trSumJtpt_jet55_keep_cent%d",i));
    hData_trkMaxJtpt_jet55_keep[i] = (TH1F*)fData->Get(Form("hData_trkMaxJtpt_jet55_keep_cent%d",i));
//    hData_trSumJtpt_jet55_keep[i] = (TH1F*)fData->Get(Form("hData_trSumJtpt_jet55_keep_cent%d",i));
    hData_trkMaxJtpt_jet65_keep[i] = (TH1F*)fData->Get(Form("hData_trkMaxJtpt_jet65_keep_cent%d",i));
//    hData_trSumJtpt_jet65_keep[i] = (TH1F*)fData->Get(Form("hData_trSumJtpt_jet65_keep_cent%d",i));
    hData_trkMaxJtpt_jet80_keep[i] = (TH1F*)fData->Get(Form("hData_trkMaxJtpt_jet80_keep_cent%d",i));
//    hData_trSumJtpt_jet80_keep[i] = (TH1F*)fData->Get(Form("hData_trSumJtpt_jet80_keep_cent%d",i));
    hData_trkMaxJtpt_jet55_rej[i] = (TH1F*)fData->Get(Form("hData_trkMaxJtpt_jet55_rej_cent%d",i));
//    hData_trSumJtpt_jet55_rej[i] = (TH1F*)fData->Get(Form("hData_trSumJtpt_jet55_rej_cent%d",i));
    hData_trkMaxJtpt_jet65_rej[i] = (TH1F*)fData->Get(Form("hData_trkMaxJtpt_jet65_rej_cent%d",i));
//    hData_trSumJtpt_jet65_rej[i] = (TH1F*)fData->Get(Form("hData_trSumJtpt_jet65_rej_cent%d",i));
    hData_trkMaxJtpt_jet80_rej[i] = (TH1F*)fData->Get(Form("hData_trkMaxJtpt_jet80_rej_cent%d",i));
//    hData_trSumJtpt_jet80_rej[i] = (TH1F*)fData->Get(Form("hData_trSumJtpt_jet80_rej_cent%d",i));
    hData_trkMaxJtpt_Matched_keep[i] = (TH1F*)fData->Get(Form("hData_trkMaxJtpt_Matched_keep_cent%d",i));
    hData_trkMaxJtpt_jet55_Matched_keep[i] = (TH1F*)fData->Get(Form("hData_trkMaxJtpt_jet55_Matched_keep_cent%d",i));
    hData_trkMaxJtpt_jet65_Matched_keep[i] = (TH1F*)fData->Get(Form("hData_trkMaxJtpt_jet65_Matched_keep_cent%d",i));
    hData_trkMaxJtpt_jet80_Matched_keep[i] = (TH1F*)fData->Get(Form("hData_trkMaxJtpt_jet80_Matched_keep_cent%d",i));
    hData_trkMaxJtpt_Unmatched_keep[i] = (TH1F*)fData->Get(Form("hData_trkMaxJtpt_Unmatched_keep_cent%d",i));
    hData_trkMaxJtpt_jet55_Unmatched_keep[i] = (TH1F*)fData->Get(Form("hData_trkMaxJtpt_jet55_Unmatched_keep_cent%d",i));
    hData_trkMaxJtpt_jet65_Unmatched_keep[i] = (TH1F*)fData->Get(Form("hData_trkMaxJtpt_jet65_Unmatched_keep_cent%d",i));
    hData_trkMaxJtpt_jet80_Unmatched_keep[i] = (TH1F*)fData->Get(Form("hData_trkMaxJtpt_jet80_Unmatched_keep_cent%d",i));
// MC
    hMC_chMaxJtpt_jet55_keep[i] = (TH1F*)fMC->Get(Form("hMC_chMaxJtpt_jet55_keep_cent%d",i));
    hMC_chSumJtpt_jet55_keep[i] = (TH1F*)fMC->Get(Form("hMC_chSumJtpt_jet55_keep_cent%d",i));
    hMC_eMaxJtpt_jet55_keep[i] = (TH1F*)fMC->Get(Form("hMC_eMaxJtpt_jet55_keep_cent%d",i));
    hMC_eSumJtpt_jet55_keep[i] = (TH1F*)fMC->Get(Form("hMC_eSumJtpt_jet55_keep_cent%d",i));
    hMC_neMaxJtpt_jet55_keep[i] = (TH1F*)fMC->Get(Form("hMC_neMaxJtpt_jet55_keep_cent%d",i));
    hMC_neSumJtpt_jet55_keep[i] = (TH1F*)fMC->Get(Form("hMC_neSumJtpt_jet55_keep_cent%d",i));
    hMC_phMaxJtpt_jet55_keep[i] = (TH1F*)fMC->Get(Form("hMC_phMaxJtpt_jet55_keep_cent%d",i));
    hMC_phSumJtpt_jet55_keep[i] = (TH1F*)fMC->Get(Form("hMC_phSumJtpt_jet55_keep_cent%d",i));
    hMC_muMaxJtpt_jet55_keep[i] = (TH1F*)fMC->Get(Form("hMC_muMaxJtpt_jet55_keep_cent%d",i));
    hMC_muSumJtpt_jet55_keep[i] = (TH1F*)fMC->Get(Form("hMC_muSumJtpt_jet55_keep_cent%d",i));
    hMC_chMaxJtpt_jet55_rej[i] = (TH1F*)fMC->Get(Form("hMC_chMaxJtpt_jet55_rej_cent%d",i));
    hMC_chSumJtpt_jet55_rej[i] = (TH1F*)fMC->Get(Form("hMC_chSumJtpt_jet55_rej_cent%d",i));
    hMC_eMaxJtpt_jet55_rej[i] = (TH1F*)fMC->Get(Form("hMC_eMaxJtpt_jet55_rej_cent%d",i));
    hMC_eSumJtpt_jet55_rej[i] = (TH1F*)fMC->Get(Form("hMC_eSumJtpt_jet55_rej_cent%d",i));
    hMC_neMaxJtpt_jet55_rej[i] = (TH1F*)fMC->Get(Form("hMC_neMaxJtpt_jet55_rej_cent%d",i));
    hMC_neSumJtpt_jet55_rej[i] = (TH1F*)fMC->Get(Form("hMC_neSumJtpt_jet55_rej_cent%d",i));
    hMC_phMaxJtpt_jet55_rej[i] = (TH1F*)fMC->Get(Form("hMC_phMaxJtpt_jet55_rej_cent%d",i));
    hMC_phSumJtpt_jet55_rej[i] = (TH1F*)fMC->Get(Form("hMC_phSumJtpt_jet55_rej_cent%d",i));
    hMC_muMaxJtpt_jet55_rej[i] = (TH1F*)fMC->Get(Form("hMC_muMaxJtpt_jet55_rej_cent%d",i));
    hMC_muSumJtpt_jet55_rej[i] = (TH1F*)fMC->Get(Form("hMC_muSumJtpt_jet55_rej_cent%d",i));
    hMC_chMaxJtpt_jet65_keep[i] = (TH1F*)fMC->Get(Form("hMC_chMaxJtpt_jet65_keep_cent%d",i));
    hMC_chSumJtpt_jet65_keep[i] = (TH1F*)fMC->Get(Form("hMC_chSumJtpt_jet65_keep_cent%d",i));
    hMC_eMaxJtpt_jet65_keep[i] = (TH1F*)fMC->Get(Form("hMC_eMaxJtpt_jet65_keep_cent%d",i));
    hMC_eSumJtpt_jet65_keep[i] = (TH1F*)fMC->Get(Form("hMC_eSumJtpt_jet65_keep_cent%d",i));
    hMC_neMaxJtpt_jet65_keep[i] = (TH1F*)fMC->Get(Form("hMC_neMaxJtpt_jet65_keep_cent%d",i));
    hMC_neSumJtpt_jet65_keep[i] = (TH1F*)fMC->Get(Form("hMC_neSumJtpt_jet65_keep_cent%d",i));
    hMC_phMaxJtpt_jet65_keep[i] = (TH1F*)fMC->Get(Form("hMC_phMaxJtpt_jet65_keep_cent%d",i));
    hMC_phSumJtpt_jet65_keep[i] = (TH1F*)fMC->Get(Form("hMC_phSumJtpt_jet65_keep_cent%d",i));
    hMC_muMaxJtpt_jet65_keep[i] = (TH1F*)fMC->Get(Form("hMC_muMaxJtpt_jet65_keep_cent%d",i));
    hMC_muSumJtpt_jet65_keep[i] = (TH1F*)fMC->Get(Form("hMC_muSumJtpt_jet65_keep_cent%d",i));
    hMC_chMaxJtpt_jet65_rej[i] = (TH1F*)fMC->Get(Form("hMC_chMaxJtpt_jet65_rej_cent%d",i));
    hMC_chSumJtpt_jet65_rej[i] = (TH1F*)fMC->Get(Form("hMC_chSumJtpt_jet65_rej_cent%d",i));
    hMC_eMaxJtpt_jet65_rej[i] = (TH1F*)fMC->Get(Form("hMC_eMaxJtpt_jet65_rej_cent%d",i));
    hMC_eSumJtpt_jet65_rej[i] = (TH1F*)fMC->Get(Form("hMC_eSumJtpt_jet65_rej_cent%d",i));
    hMC_neMaxJtpt_jet65_rej[i] = (TH1F*)fMC->Get(Form("hMC_neMaxJtpt_jet65_rej_cent%d",i));
    hMC_neSumJtpt_jet65_rej[i] = (TH1F*)fMC->Get(Form("hMC_neSumJtpt_jet65_rej_cent%d",i));
    hMC_phMaxJtpt_jet65_rej[i] = (TH1F*)fMC->Get(Form("hMC_phMaxJtpt_jet65_rej_cent%d",i));
    hMC_phSumJtpt_jet65_rej[i] = (TH1F*)fMC->Get(Form("hMC_phSumJtpt_jet65_rej_cent%d",i));
    hMC_muMaxJtpt_jet65_rej[i] = (TH1F*)fMC->Get(Form("hMC_muMaxJtpt_jet65_rej_cent%d",i));
    hMC_muSumJtpt_jet65_rej[i] = (TH1F*)fMC->Get(Form("hMC_muSumJtpt_jet65_rej_cent%d",i));
    hMC_chMaxJtpt_jet80_keep[i] = (TH1F*)fMC->Get(Form("hMC_chMaxJtpt_jet80_keep_cent%d",i));
    hMC_chSumJtpt_jet80_keep[i] = (TH1F*)fMC->Get(Form("hMC_chSumJtpt_jet80_keep_cent%d",i));
    hMC_eMaxJtpt_jet80_keep[i] = (TH1F*)fMC->Get(Form("hMC_eMaxJtpt_jet80_keep_cent%d",i));
    hMC_eSumJtpt_jet80_keep[i] = (TH1F*)fMC->Get(Form("hMC_eSumJtpt_jet80_keep_cent%d",i));
    hMC_neMaxJtpt_jet80_keep[i] = (TH1F*)fMC->Get(Form("hMC_neMaxJtpt_jet80_keep_cent%d",i));
    hMC_neSumJtpt_jet80_keep[i] = (TH1F*)fMC->Get(Form("hMC_neSumJtpt_jet80_keep_cent%d",i));
    hMC_phMaxJtpt_jet80_keep[i] = (TH1F*)fMC->Get(Form("hMC_phMaxJtpt_jet80_keep_cent%d",i));
    hMC_phSumJtpt_jet80_keep[i] = (TH1F*)fMC->Get(Form("hMC_phSumJtpt_jet80_keep_cent%d",i));
    hMC_muMaxJtpt_jet80_keep[i] = (TH1F*)fMC->Get(Form("hMC_muMaxJtpt_jet80_keep_cent%d",i));
    hMC_muSumJtpt_jet80_keep[i] = (TH1F*)fMC->Get(Form("hMC_muSumJtpt_jet80_keep_cent%d",i));
    hMC_chMaxJtpt_jet80_rej[i] = (TH1F*)fMC->Get(Form("hMC_chMaxJtpt_jet80_rej_cent%d",i));
    hMC_chSumJtpt_jet80_rej[i] = (TH1F*)fMC->Get(Form("hMC_chSumJtpt_jet80_rej_cent%d",i));
    hMC_eMaxJtpt_jet80_rej[i] = (TH1F*)fMC->Get(Form("hMC_eMaxJtpt_jet80_rej_cent%d",i));
    hMC_eSumJtpt_jet80_rej[i] = (TH1F*)fMC->Get(Form("hMC_eSumJtpt_jet80_rej_cent%d",i));
    hMC_neMaxJtpt_jet80_rej[i] = (TH1F*)fMC->Get(Form("hMC_neMaxJtpt_jet80_rej_cent%d",i));
    hMC_neSumJtpt_jet80_rej[i] = (TH1F*)fMC->Get(Form("hMC_neSumJtpt_jet80_rej_cent%d",i));
    hMC_phMaxJtpt_jet80_rej[i] = (TH1F*)fMC->Get(Form("hMC_phMaxJtpt_jet80_rej_cent%d",i));
    hMC_phSumJtpt_jet80_rej[i] = (TH1F*)fMC->Get(Form("hMC_phSumJtpt_jet80_rej_cent%d",i));
    hMC_muMaxJtpt_jet80_rej[i] = (TH1F*)fMC->Get(Form("hMC_muMaxJtpt_jet80_rej_cent%d",i));
    hMC_muSumJtpt_jet80_rej[i] = (TH1F*)fMC->Get(Form("hMC_muSumJtpt_jet80_rej_cent%d",i));
//     hMC_trkMaxJtpt_jet55_keep[i] = (TH1F*)fMC->Get(Form("hMC_trkMaxJtpt_jet55_keep_cent%d",i));
//     hMC_trSumJtpt_jet55_keep[i] = (TH1F*)fMC->Get(Form("hMC_trSumJtpt_jet55_keep_cent%d",i));
    hMC_trkMaxJtpt_jet55_keep[i] = (TH1F*)fMC->Get(Form("hMC_trkMaxJtpt_jet55_keep_cent%d",i));
//    hMC_trSumJtpt_jet55_keep[i] = (TH1F*)fMC->Get(Form("hMC_trSumJtpt_jet55_keep_cent%d",i));
    hMC_trkMaxJtpt_jet65_keep[i] = (TH1F*)fMC->Get(Form("hMC_trkMaxJtpt_jet65_keep_cent%d",i));
 //   hMC_trSumJtpt_jet65_keep[i] = (TH1F*)fMC->Get(Form("hMC_trSumJtpt_jet65_keep_cent%d",i));
    hMC_trkMaxJtpt_jet80_keep[i] = (TH1F*)fMC->Get(Form("hMC_trkMaxJtpt_jet80_keep_cent%d",i));
 //   hMC_trSumJtpt_jet80_keep[i] = (TH1F*)fMC->Get(Form("hMC_trSumJtpt_jet80_keep_cent%d",i));
    hMC_trkMaxJtpt_jet55_rej[i] = (TH1F*)fMC->Get(Form("hMC_trkMaxJtpt_jet55_rej_cent%d",i));
 //   hMC_trSumJtpt_jet55_rej[i] = (TH1F*)fMC->Get(Form("hMC_trSumJtpt_jet55_rej_cent%d",i));
    hMC_trkMaxJtpt_jet65_rej[i] = (TH1F*)fMC->Get(Form("hMC_trkMaxJtpt_jet65_rej_cent%d",i));
 //   hMC_trSumJtpt_jet65_rej[i] = (TH1F*)fMC->Get(Form("hMC_trSumJtpt_jet65_rej_cent%d",i));
    hMC_trkMaxJtpt_jet80_rej[i] = (TH1F*)fMC->Get(Form("hMC_trkMaxJtpt_jet80_rej_cent%d",i));
 //   hMC_trSumJtpt_jet80_rej[i] = (TH1F*)fMC->Get(Form("hMC_trSumJtpt_jet80_rej_cent%d",i));
    hMC_trkMaxJtpt_Matched_keep[i] = (TH1F*)fMC->Get(Form("hMC_trkMaxJtpt_Matched_keep_cent%d",i));
    hMC_trkMaxJtpt_jet55_Matched_keep[i] = (TH1F*)fMC->Get(Form("hMC_trkMaxJtpt_jet55_Matched_keep_cent%d",i));
    hMC_trkMaxJtpt_jet65_Matched_keep[i] = (TH1F*)fMC->Get(Form("hMC_trkMaxJtpt_jet65_Matched_keep_cent%d",i));
    hMC_trkMaxJtpt_jet80_Matched_keep[i] = (TH1F*)fMC->Get(Form("hMC_trkMaxJtpt_jet80_Matched_keep_cent%d",i));
//    hMC_trkMaxJtpt_Matched_NoTrig_keep[i] = (TH1F*)fMC->Get(Form("hMC_trkMaxJtpt_Matched_NoTrig_keep_cent%d",i));
  }


// start drawing things		      
//#if 0
  TCanvas * cchMaxJtpt_jet55_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchMaxJtpt_jet55_keep[i] = new TCanvas(Form("cchMaxJtpt_jet55_keep_cent%d",i),"",800,600);
    cchMaxJtpt_jet55_keep[i]->SetLogy();
    hMC_chMaxJtpt_jet55_keep[i]->SetMarkerColor(kRed);
    hMC_chMaxJtpt_jet55_keep[i]->SetMarkerStyle(25);
    hMC_chMaxJtpt_jet55_keep[i]->Print("base");
    hMC_chMaxJtpt_jet55_keep[i]->SetTitle(" ");
    hMC_chMaxJtpt_jet55_keep[i]->SetXTitle(Form("chMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));
    nMC_chMaxJtpt_jet55_keep[i]=hMC_chMaxJtpt_jet55_keep[i]->GetEntries();
    if (nMC_chMaxJtpt_jet55_keep[i]>0){
       hMC_chMaxJtpt_jet55_keep[i]->DrawNormalized();
    } else { cout<<"hMC_chMaxJtpt_jet55_keep[i] for i= "<<i<<" has "<<nMC_chMaxJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }

    hData_chMaxJtpt_jet55_keep[i]->SetMarkerStyle(24);
    hData_chMaxJtpt_jet55_keep[i]->SetMarkerColor(kBlack);
    nData_chMaxJtpt_jet55_keep[i]=hData_chMaxJtpt_jet55_keep[i]->GetEntries();
    if (nData_chMaxJtpt_jet55_keep[i]>0){
      if(nMC_chMaxJtpt_jet55_keep[i]<=0){
        hData_chMaxJtpt_jet55_keep[i]->Print("base");
        hData_chMaxJtpt_jet55_keep[i]->SetTitle(" ");
        hData_chMaxJtpt_jet55_keep[i]->SetXTitle(Form("chMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_chMaxJtpt_jet55_keep[i]->DrawNormalized();
      } else {
      hData_chMaxJtpt_jet55_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_chMaxJtpt_jet55_keep[i] for i= "<<i<<" has "<<nData_chMaxJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }      
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chMaxJtpt_jet55_keep[0],"MC","pl");
    leg->AddEntry(hData_chMaxJtpt_jet55_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchMaxJtpt_jet55_keep[i]->SaveAs(Form("Plots/chMaxJtpt_jet55_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  
  TCanvas * ceMaxJtpt_jet55_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceMaxJtpt_jet55_keep[i] = new TCanvas(Form("ceMaxJtpt_jet55_keep_cent%d",i),"",800,600);
    ceMaxJtpt_jet55_keep[i]->SetLogy();
    hMC_eMaxJtpt_jet55_keep[i]->SetMarkerColor(kBlue);
    hMC_eMaxJtpt_jet55_keep[i]->SetMarkerStyle(25);
    hMC_eMaxJtpt_jet55_keep[i]->Print("base");
    hMC_eMaxJtpt_jet55_keep[i]->SetTitle(" ");
    hMC_eMaxJtpt_jet55_keep[i]->SetXTitle(Form("eMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));
    nMC_eMaxJtpt_jet55_keep[i]=hMC_eMaxJtpt_jet55_keep[i]->GetEntries();
    if (nMC_eMaxJtpt_jet55_keep[i]>0){
       hMC_eMaxJtpt_jet55_keep[i]->DrawNormalized();
    } else { cout<<"hMC_eMaxJtpt_jet55_keep[i] for i= "<<i<<" has "<<nMC_eMaxJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }

    hData_eMaxJtpt_jet55_keep[i]->SetMarkerStyle(24);
    hData_eMaxJtpt_jet55_keep[i]->SetMarkerColor(kBlack);
    nData_eMaxJtpt_jet55_keep[i]=hData_eMaxJtpt_jet55_keep[i]->GetEntries();
    if (nData_eMaxJtpt_jet55_keep[i]>0){
      if(nMC_eMaxJtpt_jet55_keep[i]<=0){
        hData_eMaxJtpt_jet55_keep[i]->Print("base");
        hData_eMaxJtpt_jet55_keep[i]->SetTitle(" ");
        hData_eMaxJtpt_jet55_keep[i]->SetXTitle(Form("eMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_eMaxJtpt_jet55_keep[i]->DrawNormalized();
      } else {
      hData_eMaxJtpt_jet55_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_eMaxJtpt_jet55_keep[i] for i= "<<i<<" has "<<nData_eMaxJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }   
        drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eMaxJtpt_jet55_keep[0],"MC","pl");
    leg->AddEntry(hData_eMaxJtpt_jet55_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceMaxJtpt_jet55_keep[i]->SaveAs(Form("Plots/eMaxJtpt_jet55_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }

   TCanvas * cphMaxJtpt_jet55_keep[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphMaxJtpt_jet55_keep[i] = new TCanvas(Form("cphMaxJtpt_jet55_keep_cent%d",i),"",800,600);
    cphMaxJtpt_jet55_keep[i]->SetLogy();
    hMC_phMaxJtpt_jet55_keep[i]->SetMarkerColor(kGreen+2);
    hMC_phMaxJtpt_jet55_keep[i]->SetMarkerStyle(25);
    hMC_phMaxJtpt_jet55_keep[i]->Print("base");
    hMC_phMaxJtpt_jet55_keep[i]->SetTitle(" ");
    hMC_phMaxJtpt_jet55_keep[i]->SetXTitle(Form("phMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));
    nMC_phMaxJtpt_jet55_keep[i]=hMC_phMaxJtpt_jet55_keep[i]->GetEntries();
    if (nMC_phMaxJtpt_jet55_keep[i]>0){
       hMC_phMaxJtpt_jet55_keep[i]->DrawNormalized();
    } else { cout<<"hMC_phMaxJtpt_jet55_keep[i] for i= "<<i<<" has "<<nMC_phMaxJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }

    hData_phMaxJtpt_jet55_keep[i]->SetMarkerStyle(24);
    hData_phMaxJtpt_jet55_keep[i]->SetMarkerColor(kBlack);
    nData_phMaxJtpt_jet55_keep[i]=hData_phMaxJtpt_jet55_keep[i]->GetEntries();
    if (nData_phMaxJtpt_jet55_keep[i]>0){
      if(nMC_phMaxJtpt_jet55_keep[i]<=0){
        hData_phMaxJtpt_jet55_keep[i]->Print("base");
        hData_phMaxJtpt_jet55_keep[i]->SetTitle(" ");
        hData_phMaxJtpt_jet55_keep[i]->SetXTitle(Form("phMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_phMaxJtpt_jet55_keep[i]->DrawNormalized();
      } else {
      hData_phMaxJtpt_jet55_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_phMaxJtpt_jet55_keep[i] for i= "<<i<<" has "<<nData_phMaxJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }   
        drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phMaxJtpt_jet55_keep[0],"MC","pl");
    leg->AddEntry(hData_phMaxJtpt_jet55_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphMaxJtpt_jet55_keep[i]->SaveAs(Form("Plots/phMaxJtpt_jet55_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cneMaxJtpt_jet55_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneMaxJtpt_jet55_keep[i] = new TCanvas(Form("cneMaxJtpt_jet55_keep_cent%d",i),"",800,600);
    cneMaxJtpt_jet55_keep[i]->SetLogy();
    hMC_neMaxJtpt_jet55_keep[i]->SetMarkerColor(kMagenta);
    hMC_neMaxJtpt_jet55_keep[i]->SetMarkerStyle(25);
    hMC_neMaxJtpt_jet55_keep[i]->Print("base");
    hMC_neMaxJtpt_jet55_keep[i]->SetTitle(" ");
    hMC_neMaxJtpt_jet55_keep[i]->SetXTitle(Form("neMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));
    nMC_neMaxJtpt_jet55_keep[i]=hMC_neMaxJtpt_jet55_keep[i]->GetEntries();
    if (nMC_neMaxJtpt_jet55_keep[i]>0){
       hMC_neMaxJtpt_jet55_keep[i]->DrawNormalized();
    } else { cout<<"hMC_neMaxJtpt_jet55_keep[i] for i= "<<i<<" has "<<nMC_neMaxJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }

    hData_neMaxJtpt_jet55_keep[i]->SetMarkerStyle(24);
    hData_neMaxJtpt_jet55_keep[i]->SetMarkerColor(kBlack);
    nData_neMaxJtpt_jet55_keep[i]=hData_neMaxJtpt_jet55_keep[i]->GetEntries();
    if (nData_neMaxJtpt_jet55_keep[i]>0){
      if(nMC_neMaxJtpt_jet55_keep[i]<=0){
        hData_neMaxJtpt_jet55_keep[i]->Print("base");
        hData_neMaxJtpt_jet55_keep[i]->SetTitle(" ");
        hData_neMaxJtpt_jet55_keep[i]->SetXTitle(Form("neMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_neMaxJtpt_jet55_keep[i]->DrawNormalized();
      } else {
      hData_neMaxJtpt_jet55_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_neMaxJtpt_jet55_keep[i] for i= "<<i<<" has "<<nData_neMaxJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neMaxJtpt_jet55_keep[0],"MC","pl");
    leg->AddEntry(hData_neMaxJtpt_jet55_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneMaxJtpt_jet55_keep[i]->SaveAs(Form("Plots/neMaxJtpt_jet55_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cmuMaxJtpt_jet55_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuMaxJtpt_jet55_keep[i] = new TCanvas(Form("cmuMaxJtpt_jet55_keep_cent%d",i),"",800,600);
    cmuMaxJtpt_jet55_keep[i]->SetLogy();
    hMC_muMaxJtpt_jet55_keep[i]->SetMarkerColor(kCyan);
    hMC_muMaxJtpt_jet55_keep[i]->SetMarkerStyle(25);
    hMC_muMaxJtpt_jet55_keep[i]->Print("base");
    hMC_muMaxJtpt_jet55_keep[i]->SetTitle(" ");
    hMC_muMaxJtpt_jet55_keep[i]->SetXTitle(Form("muMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));
    nMC_muMaxJtpt_jet55_keep[i]=hMC_muMaxJtpt_jet55_keep[i]->GetEntries();
    if (nMC_muMaxJtpt_jet55_keep[i]>0){
       hMC_muMaxJtpt_jet55_keep[i]->DrawNormalized();
    } else { cout<<"hMC_muMaxJtpt_jet55_keep[i] for i= "<<i<<" has "<<nMC_muMaxJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }

    hData_muMaxJtpt_jet55_keep[i]->SetMarkerStyle(24);
    hData_muMaxJtpt_jet55_keep[i]->SetMarkerColor(kBlack);
    nData_muMaxJtpt_jet55_keep[i]=hData_muMaxJtpt_jet55_keep[i]->GetEntries();
    if (nData_muMaxJtpt_jet55_keep[i]>0){
      if(nMC_muMaxJtpt_jet55_keep[i]<=0){
        hData_muMaxJtpt_jet55_keep[i]->Print("base");
        hData_muMaxJtpt_jet55_keep[i]->SetTitle(" ");
        hData_muMaxJtpt_jet55_keep[i]->SetXTitle(Form("muMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_muMaxJtpt_jet55_keep[i]->DrawNormalized();
      } else {
      hData_muMaxJtpt_jet55_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_muMaxJtpt_jet55_keep[i] for i= "<<i<<" has "<<nData_muMaxJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muMaxJtpt_jet55_keep[0],"MC","pl");
    leg->AddEntry(hData_muMaxJtpt_jet55_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuMaxJtpt_jet55_keep[i]->SaveAs(Form("Plots/muMaxJtpt_jet55_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }    
// draw some Sum variables
  TCanvas * cchSumJtpt_jet55_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchSumJtpt_jet55_keep[i] = new TCanvas(Form("cchSumJtpt_jet55_keep_cent%d",i),"",800,600);
    cchSumJtpt_jet55_keep[i]->SetLogy();
    hMC_chSumJtpt_jet55_keep[i]->SetMarkerColor(kRed+1);
    hMC_chSumJtpt_jet55_keep[i]->SetMarkerStyle(25);
    hMC_chSumJtpt_jet55_keep[i]->Print("base");
    hMC_chSumJtpt_jet55_keep[i]->SetTitle(" ");
    hMC_chSumJtpt_jet55_keep[i]->SetXTitle(Form("chSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));
    nMC_chSumJtpt_jet55_keep[i]=hMC_chSumJtpt_jet55_keep[i]->GetEntries();
    if (nMC_chSumJtpt_jet55_keep[i]>0){
       hMC_chSumJtpt_jet55_keep[i]->DrawNormalized();
    } else { cout<<"hMC_chSumJtpt_jet55_keep[i] for i= "<<i<<" has "<<nMC_chSumJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }

    hData_chSumJtpt_jet55_keep[i]->SetMarkerStyle(24);
    hData_chSumJtpt_jet55_keep[i]->SetMarkerColor(kBlack);
    nData_chSumJtpt_jet55_keep[i]=hData_chSumJtpt_jet55_keep[i]->GetEntries();
    if (nData_chSumJtpt_jet55_keep[i]>0){
      if(nMC_chSumJtpt_jet55_keep[i]<=0){
        hData_chSumJtpt_jet55_keep[i]->Print("base");
        hData_chSumJtpt_jet55_keep[i]->SetTitle(" ");
        hData_chSumJtpt_jet55_keep[i]->SetXTitle(Form("chSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_chSumJtpt_jet55_keep[i]->DrawNormalized();
      } else {
      hData_chSumJtpt_jet55_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_chSumJtpt_jet55_keep[i] for i= "<<i<<" has "<<nData_chSumJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }   
        drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chSumJtpt_jet55_keep[0],"MC","pl");
    leg->AddEntry(hData_chSumJtpt_jet55_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchSumJtpt_jet55_keep[i]->SaveAs(Form("Plots/chSumJtpt_jet55_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * ceSumJtpt_jet55_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceSumJtpt_jet55_keep[i] = new TCanvas(Form("ceSumJtpt_jet55_keep_cent%d",i),"",800,600);
    ceSumJtpt_jet55_keep[i]->SetLogy();
    hMC_eSumJtpt_jet55_keep[i]->SetMarkerColor(kBlue+1);
    hMC_eSumJtpt_jet55_keep[i]->SetMarkerStyle(25);
    hMC_eSumJtpt_jet55_keep[i]->Print("base");
    hMC_eSumJtpt_jet55_keep[i]->SetTitle(" ");
    hMC_eSumJtpt_jet55_keep[i]->SetXTitle(Form("eSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));
    nMC_eSumJtpt_jet55_keep[i]=hMC_eSumJtpt_jet55_keep[i]->GetEntries();
    if (nMC_eSumJtpt_jet55_keep[i]>0){
       hMC_eSumJtpt_jet55_keep[i]->DrawNormalized();
    } else { cout<<"hMC_eSumJtpt_jet55_keep[i] for i= "<<i<<" has "<<nMC_eSumJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }

    hData_eSumJtpt_jet55_keep[i]->SetMarkerStyle(24);
    hData_eSumJtpt_jet55_keep[i]->SetMarkerColor(kBlack);
    nData_eSumJtpt_jet55_keep[i]=hData_eSumJtpt_jet55_keep[i]->GetEntries();
    if (nData_eSumJtpt_jet55_keep[i]>0){
      if(nMC_eSumJtpt_jet55_keep[i]<=0){
        hData_eSumJtpt_jet55_keep[i]->Print("base");
        hData_eSumJtpt_jet55_keep[i]->SetTitle(" ");
        hData_eSumJtpt_jet55_keep[i]->SetXTitle(Form("eSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_eSumJtpt_jet55_keep[i]->DrawNormalized();
      } else {
      hData_eSumJtpt_jet55_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_eSumJtpt_jet55_keep[i] for i= "<<i<<" has "<<nData_eSumJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }   
        drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eSumJtpt_jet55_keep[0],"MC","pl");
    leg->AddEntry(hData_eSumJtpt_jet55_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceSumJtpt_jet55_keep[i]->SaveAs(Form("Plots/eSumJtpt_jet55_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cphSumJtpt_jet55_keep[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphSumJtpt_jet55_keep[i] = new TCanvas(Form("cphSumJtpt_jet55_keep_cent%d",i),"",800,600);
    cphSumJtpt_jet55_keep[i]->SetLogy();
    hMC_phSumJtpt_jet55_keep[i]->SetMarkerColor(kGreen-3);
    hMC_phSumJtpt_jet55_keep[i]->SetMarkerStyle(25);
    hMC_phSumJtpt_jet55_keep[i]->Print("base");
    hMC_phSumJtpt_jet55_keep[i]->SetTitle(" ");
    hMC_phSumJtpt_jet55_keep[i]->SetXTitle(Form("phSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));
    nMC_phSumJtpt_jet55_keep[i]=hMC_phSumJtpt_jet55_keep[i]->GetEntries();
    if (nMC_phSumJtpt_jet55_keep[i]>0){
       hMC_phSumJtpt_jet55_keep[i]->DrawNormalized();
    } else { cout<<"hMC_phSumJtpt_jet55_keep[i] for i= "<<i<<" has "<<nMC_phSumJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }

    hData_phSumJtpt_jet55_keep[i]->SetMarkerStyle(24);
    hData_phSumJtpt_jet55_keep[i]->SetMarkerColor(kBlack);
    nData_phSumJtpt_jet55_keep[i]=hData_phSumJtpt_jet55_keep[i]->GetEntries();
    if (nData_phSumJtpt_jet55_keep[i]>0){
      if(nMC_phSumJtpt_jet55_keep[i]<=0){
        hData_phSumJtpt_jet55_keep[i]->Print("base");
        hData_phSumJtpt_jet55_keep[i]->SetTitle(" ");
        hData_phSumJtpt_jet55_keep[i]->SetXTitle(Form("phSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_phSumJtpt_jet55_keep[i]->DrawNormalized();
      } else {
      hData_phSumJtpt_jet55_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_phSumJtpt_jet55_keep[i] for i= "<<i<<" has "<<nData_phSumJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phSumJtpt_jet55_keep[0],"MC","pl");
    leg->AddEntry(hData_phSumJtpt_jet55_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphSumJtpt_jet55_keep[i]->SaveAs(Form("Plots/phSumJtpt_jet55_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cneSumJtpt_jet55_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneSumJtpt_jet55_keep[i] = new TCanvas(Form("cneSumJtpt_jet55_keep_cent%d",i),"",800,600);
    cneSumJtpt_jet55_keep[i]->SetLogy();
    hMC_neSumJtpt_jet55_keep[i]->SetMarkerColor(kMagenta+1);
    hMC_neSumJtpt_jet55_keep[i]->SetMarkerStyle(25);
    hMC_neSumJtpt_jet55_keep[i]->Print("base");
    hMC_neSumJtpt_jet55_keep[i]->SetTitle(" ");
    hMC_neSumJtpt_jet55_keep[i]->SetXTitle(Form("neSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));
    nMC_neSumJtpt_jet55_keep[i]=hMC_neSumJtpt_jet55_keep[i]->GetEntries();
    if (nMC_neSumJtpt_jet55_keep[i]>0){
       hMC_neSumJtpt_jet55_keep[i]->DrawNormalized();
    } else { cout<<"hMC_neSumJtpt_jet55_keep[i] for i= "<<i<<" has "<<nMC_neSumJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }

    hData_neSumJtpt_jet55_keep[i]->SetMarkerStyle(24);
    hData_neSumJtpt_jet55_keep[i]->SetMarkerColor(kBlack);
    nData_neSumJtpt_jet55_keep[i]=hData_neSumJtpt_jet55_keep[i]->GetEntries();
    if (nData_neSumJtpt_jet55_keep[i]>0){
      if(nMC_neSumJtpt_jet55_keep[i]<=0){
        hData_neSumJtpt_jet55_keep[i]->Print("base");
        hData_neSumJtpt_jet55_keep[i]->SetTitle(" ");
        hData_neSumJtpt_jet55_keep[i]->SetXTitle(Form("neSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_neSumJtpt_jet55_keep[i]->DrawNormalized();
      } else {
      hData_neSumJtpt_jet55_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_neSumJtpt_jet55_keep[i] for i= "<<i<<" has "<<nData_neSumJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neSumJtpt_jet55_keep[0],"MC","pl");
    leg->AddEntry(hData_neSumJtpt_jet55_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneSumJtpt_jet55_keep[i]->SaveAs(Form("Plots/neSumJtpt_jet55_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cmuSumJtpt_jet55_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuSumJtpt_jet55_keep[i] = new TCanvas(Form("cmuSumJtpt_jet55_keep_cent%d",i),"",800,600);
    cmuSumJtpt_jet55_keep[i]->SetLogy();
    hMC_muSumJtpt_jet55_keep[i]->SetMarkerColor(kCyan+1);
    hMC_muSumJtpt_jet55_keep[i]->SetMarkerStyle(25);
    hMC_muSumJtpt_jet55_keep[i]->Print("base");
    hMC_muSumJtpt_jet55_keep[i]->SetTitle(" ");
    hMC_muSumJtpt_jet55_keep[i]->SetXTitle(Form("muSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));
    nMC_muSumJtpt_jet55_keep[i]=hMC_muSumJtpt_jet55_keep[i]->GetEntries();
    if (nMC_muSumJtpt_jet55_keep[i]>0){
       hMC_muSumJtpt_jet55_keep[i]->DrawNormalized();
    } else { cout<<"hMC_muSumJtpt_jet55_keep[i] for i= "<<i<<" has "<<nMC_muSumJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }

    hData_muSumJtpt_jet55_keep[i]->SetMarkerStyle(24);
    hData_muSumJtpt_jet55_keep[i]->SetMarkerColor(kBlack);
    nData_muSumJtpt_jet55_keep[i]=hData_muSumJtpt_jet55_keep[i]->GetEntries();
    if (nData_muSumJtpt_jet55_keep[i]>0){
      if(nMC_muSumJtpt_jet55_keep[i]<=0){
        hData_muSumJtpt_jet55_keep[i]->Print("base");
        hData_muSumJtpt_jet55_keep[i]->SetTitle(" ");
        hData_muSumJtpt_jet55_keep[i]->SetXTitle(Form("muSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_muSumJtpt_jet55_keep[i]->DrawNormalized();
      } else {
      hData_muSumJtpt_jet55_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_muSumJtpt_jet55_keep[i] for i= "<<i<<" has "<<nData_muSumJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muSumJtpt_jet55_keep[0],"MC","pl");
    leg->AddEntry(hData_muSumJtpt_jet55_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuSumJtpt_jet55_keep[i]->SaveAs(Form("Plots/muSumJtpt_jet55_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cchMaxJtpt_jet55_rej[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchMaxJtpt_jet55_rej[i] = new TCanvas(Form("cchMaxJtpt_jet55_rej_cent%d",i),"",800,600);
    cchMaxJtpt_jet55_rej[i]->SetLogy();
    hMC_chMaxJtpt_jet55_rej[i]->SetMarkerColor(kRed);
    hMC_chMaxJtpt_jet55_rej[i]->SetMarkerStyle(25);
    hMC_chMaxJtpt_jet55_rej[i]->Print("base");
    hMC_chMaxJtpt_jet55_rej[i]->SetTitle(" ");
    hMC_chMaxJtpt_jet55_rej[i]->SetXTitle(Form("chMax/(ak%dPuPF jet p_{T}) jet55, fail CutA",radius));
    nMC_chMaxJtpt_jet55_rej[i]=hMC_chMaxJtpt_jet55_rej[i]->GetEntries();
    if (nMC_chMaxJtpt_jet55_rej[i]>0){
       hMC_chMaxJtpt_jet55_rej[i]->DrawNormalized();
    } else { cout<<"hMC_chMaxJtpt_jet55_rej[i] for i= "<<i<<" has "<<nMC_chMaxJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }

    hData_chMaxJtpt_jet55_rej[i]->SetMarkerStyle(24);
    hData_chMaxJtpt_jet55_rej[i]->SetMarkerColor(kBlack);
    nData_chMaxJtpt_jet55_rej[i]=hData_chMaxJtpt_jet55_rej[i]->GetEntries();
    if (nData_chMaxJtpt_jet55_rej[i]>0){
      if(nMC_chMaxJtpt_jet55_rej[i]<=0){
        hData_chMaxJtpt_jet55_rej[i]->Print("base");
        hData_chMaxJtpt_jet55_rej[i]->SetTitle(" ");
        hData_chMaxJtpt_jet55_rej[i]->SetXTitle(Form("chMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_chMaxJtpt_jet55_rej[i]->DrawNormalized();
      } else {
      hData_chMaxJtpt_jet55_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_chMaxJtpt_jet55_rej[i] for i= "<<i<<" has "<<nData_chMaxJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chMaxJtpt_jet55_rej[0],"MC","pl");
    leg->AddEntry(hData_chMaxJtpt_jet55_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchMaxJtpt_jet55_rej[i]->SaveAs(Form("Plots/chMaxJtpt_jet55_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  
  TCanvas * ceMaxJtpt_jet55_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceMaxJtpt_jet55_rej[i] = new TCanvas(Form("ceMaxJtpt_jet55_rej_cent%d",i),"",800,600);
    ceMaxJtpt_jet55_rej[i]->SetLogy();
    hMC_eMaxJtpt_jet55_rej[i]->SetMarkerColor(kBlue);
    hMC_eMaxJtpt_jet55_rej[i]->SetMarkerStyle(25);
    hMC_eMaxJtpt_jet55_rej[i]->Print("base");
    hMC_eMaxJtpt_jet55_rej[i]->SetTitle(" ");
    hMC_eMaxJtpt_jet55_rej[i]->SetXTitle(Form("eMax/(ak%dPuPF jet p_{T}) jet55, fail CutA",radius));
    nMC_eMaxJtpt_jet55_rej[i]=hMC_eMaxJtpt_jet55_rej[i]->GetEntries();
    if (nMC_eMaxJtpt_jet55_rej[i]>0){
       hMC_eMaxJtpt_jet55_rej[i]->DrawNormalized();
    } else { cout<<"hMC_eMaxJtpt_jet55_rej[i] for i= "<<i<<" has "<<nMC_eMaxJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }

    hData_eMaxJtpt_jet55_rej[i]->SetMarkerStyle(24);
    hData_eMaxJtpt_jet55_rej[i]->SetMarkerColor(kBlack);
    nData_eMaxJtpt_jet55_rej[i]=hData_eMaxJtpt_jet55_rej[i]->GetEntries();
    if (nData_eMaxJtpt_jet55_rej[i]>0){
      if(nMC_eMaxJtpt_jet55_rej[i]<=0){
        hData_eMaxJtpt_jet55_rej[i]->Print("base");
        hData_eMaxJtpt_jet55_rej[i]->SetTitle(" ");
        hData_eMaxJtpt_jet55_rej[i]->SetXTitle(Form("eMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_eMaxJtpt_jet55_rej[i]->DrawNormalized();
      } else {
      hData_eMaxJtpt_jet55_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_eMaxJtpt_jet55_rej[i] for i= "<<i<<" has "<<nData_eMaxJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eMaxJtpt_jet55_rej[0],"MC","pl");
    leg->AddEntry(hData_eMaxJtpt_jet55_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceMaxJtpt_jet55_rej[i]->SaveAs(Form("Plots/eMaxJtpt_jet55_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }

   TCanvas * cphMaxJtpt_jet55_rej[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphMaxJtpt_jet55_rej[i] = new TCanvas(Form("cphMaxJtpt_jet55_rej_cent%d",i),"",800,600);
    cphMaxJtpt_jet55_rej[i]->SetLogy();
    hMC_phMaxJtpt_jet55_rej[i]->SetMarkerColor(kGreen+2);
    hMC_phMaxJtpt_jet55_rej[i]->SetMarkerStyle(25);
    hMC_phMaxJtpt_jet55_rej[i]->Print("base");
    hMC_phMaxJtpt_jet55_rej[i]->SetTitle(" ");
    hMC_phMaxJtpt_jet55_rej[i]->SetXTitle(Form("phMax/(ak%dPuPF jet p_{T}) jet55, fail CutA",radius));
    nMC_phMaxJtpt_jet55_rej[i]=hMC_phMaxJtpt_jet55_rej[i]->GetEntries();
    if (nMC_phMaxJtpt_jet55_rej[i]>0){
       hMC_phMaxJtpt_jet55_rej[i]->DrawNormalized();
    } else { cout<<"hMC_phMaxJtpt_jet55_rej[i] for i= "<<i<<" has "<<nMC_phMaxJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }

    hData_phMaxJtpt_jet55_rej[i]->SetMarkerStyle(24);
    hData_phMaxJtpt_jet55_rej[i]->SetMarkerColor(kBlack);
    nData_phMaxJtpt_jet55_rej[i]=hData_phMaxJtpt_jet55_rej[i]->GetEntries();
    if (nData_phMaxJtpt_jet55_rej[i]>0){
      if(nMC_phMaxJtpt_jet55_rej[i]<=0){
        hData_phMaxJtpt_jet55_rej[i]->Print("base");
        hData_phMaxJtpt_jet55_rej[i]->SetTitle(" ");
        hData_phMaxJtpt_jet55_rej[i]->SetXTitle(Form("phMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_phMaxJtpt_jet55_rej[i]->DrawNormalized();
      } else {
      hData_phMaxJtpt_jet55_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_phMaxJtpt_jet55_rej[i] for i= "<<i<<" has "<<nData_phMaxJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phMaxJtpt_jet55_rej[0],"MC","pl");
    leg->AddEntry(hData_phMaxJtpt_jet55_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphMaxJtpt_jet55_rej[i]->SaveAs(Form("Plots/phMaxJtpt_jet55_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cneMaxJtpt_jet55_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneMaxJtpt_jet55_rej[i] = new TCanvas(Form("cneMaxJtpt_jet55_rej_cent%d",i),"",800,600);
    cneMaxJtpt_jet55_rej[i]->SetLogy();
    hMC_neMaxJtpt_jet55_rej[i]->SetMarkerColor(kMagenta);
    hMC_neMaxJtpt_jet55_rej[i]->SetMarkerStyle(25);
    hMC_neMaxJtpt_jet55_rej[i]->Print("base");
    hMC_neMaxJtpt_jet55_rej[i]->SetTitle(" ");
    hMC_neMaxJtpt_jet55_rej[i]->SetXTitle(Form("neMax/(ak%dPuPF jet p_{T}) jet55, fail CutA",radius));
    nMC_neMaxJtpt_jet55_rej[i]=hMC_neMaxJtpt_jet55_rej[i]->GetEntries();
    if (nMC_neMaxJtpt_jet55_rej[i]>0){
       hMC_neMaxJtpt_jet55_rej[i]->DrawNormalized();
    } else { cout<<"hMC_neMaxJtpt_jet55_rej[i] for i= "<<i<<" has "<<nMC_neMaxJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }

    hData_neMaxJtpt_jet55_rej[i]->SetMarkerStyle(24);
    hData_neMaxJtpt_jet55_rej[i]->SetMarkerColor(kBlack);
    nData_neMaxJtpt_jet55_rej[i]=hData_neMaxJtpt_jet55_rej[i]->GetEntries();
    if (nData_neMaxJtpt_jet55_rej[i]>0){
      if(nMC_neMaxJtpt_jet55_rej[i]<=0){
        hData_neMaxJtpt_jet55_rej[i]->Print("base");
        hData_neMaxJtpt_jet55_rej[i]->SetTitle(" ");
        hData_neMaxJtpt_jet55_rej[i]->SetXTitle(Form("neMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_neMaxJtpt_jet55_rej[i]->DrawNormalized();
      } else {
      hData_neMaxJtpt_jet55_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_neMaxJtpt_jet55_rej[i] for i= "<<i<<" has "<<nData_neMaxJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neMaxJtpt_jet55_rej[0],"MC","pl");
    leg->AddEntry(hData_neMaxJtpt_jet55_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneMaxJtpt_jet55_rej[i]->SaveAs(Form("Plots/neMaxJtpt_jet55_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cmuMaxJtpt_jet55_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuMaxJtpt_jet55_rej[i] = new TCanvas(Form("cmuMaxJtpt_jet55_rej_cent%d",i),"",800,600);
    cmuMaxJtpt_jet55_rej[i]->SetLogy();
    hMC_muMaxJtpt_jet55_rej[i]->SetMarkerColor(kCyan);
    hMC_muMaxJtpt_jet55_rej[i]->SetMarkerStyle(25);
    hMC_muMaxJtpt_jet55_rej[i]->Print("base");
    hMC_muMaxJtpt_jet55_rej[i]->SetTitle(" ");
    hMC_muMaxJtpt_jet55_rej[i]->SetXTitle(Form("muMax/(ak%dPuPF jet p_{T}) jet55, fail CutA",radius));
    nMC_muMaxJtpt_jet55_rej[i]=hMC_muMaxJtpt_jet55_rej[i]->GetEntries();
    if (nMC_muMaxJtpt_jet55_rej[i]>0){
       hMC_muMaxJtpt_jet55_rej[i]->DrawNormalized();
    } else { cout<<"hMC_muMaxJtpt_jet55_rej[i] for i= "<<i<<" has "<<nMC_muMaxJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }

    hData_muMaxJtpt_jet55_rej[i]->SetMarkerStyle(24);
    hData_muMaxJtpt_jet55_rej[i]->SetMarkerColor(kBlack);
    nData_muMaxJtpt_jet55_rej[i]=hData_muMaxJtpt_jet55_rej[i]->GetEntries();
    if (nData_muMaxJtpt_jet55_rej[i]>0){
      if(nMC_muMaxJtpt_jet55_rej[i]<=0){
        hData_muMaxJtpt_jet55_rej[i]->Print("base");
        hData_muMaxJtpt_jet55_rej[i]->SetTitle(" ");
        hData_muMaxJtpt_jet55_rej[i]->SetXTitle(Form("muMax/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_muMaxJtpt_jet55_rej[i]->DrawNormalized();
      } else {
      hData_muMaxJtpt_jet55_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_muMaxJtpt_jet55_rej[i] for i= "<<i<<" has "<<nData_muMaxJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; } 
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muMaxJtpt_jet55_rej[0],"MC","pl");
    leg->AddEntry(hData_muMaxJtpt_jet55_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuMaxJtpt_jet55_rej[i]->SaveAs(Form("Plots/muMaxJtpt_jet55_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }    
// draw some Sum variables
  TCanvas * cchSumJtpt_jet55_rej[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchSumJtpt_jet55_rej[i] = new TCanvas(Form("cchSumJtpt_jet55_rej_cent%d",i),"",800,600);
    cchSumJtpt_jet55_rej[i]->SetLogy();
    hMC_chSumJtpt_jet55_rej[i]->SetMarkerColor(kRed+1);
    hMC_chSumJtpt_jet55_rej[i]->SetMarkerStyle(25);
    hMC_chSumJtpt_jet55_rej[i]->Print("base");
    hMC_chSumJtpt_jet55_rej[i]->SetTitle(" ");
    hMC_chSumJtpt_jet55_rej[i]->SetXTitle(Form("chSum/(ak%dPuPF jet p_{T}) jet55, fail CutA",radius));
    nMC_chSumJtpt_jet55_rej[i]=hMC_chSumJtpt_jet55_rej[i]->GetEntries();
    if (nMC_chSumJtpt_jet55_rej[i]>0){
       hMC_chSumJtpt_jet55_rej[i]->DrawNormalized();
    } else { cout<<"hMC_chSumJtpt_jet55_rej[i] for i= "<<i<<" has "<<nMC_chSumJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }

    hData_chSumJtpt_jet55_rej[i]->SetMarkerStyle(24);
    hData_chSumJtpt_jet55_rej[i]->SetMarkerColor(kBlack);
    nData_chSumJtpt_jet55_rej[i]=hData_chSumJtpt_jet55_rej[i]->GetEntries();
    if (nData_chSumJtpt_jet55_rej[i]>0){
      if(nMC_chSumJtpt_jet55_rej[i]<=0){
        hData_chSumJtpt_jet55_rej[i]->Print("base");
        hData_chSumJtpt_jet55_rej[i]->SetTitle(" ");
        hData_chSumJtpt_jet55_rej[i]->SetXTitle(Form("chSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_chSumJtpt_jet55_rej[i]->DrawNormalized();
      } else {
      hData_chSumJtpt_jet55_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_chSumJtpt_jet55_rej[i] for i= "<<i<<" has "<<nData_chSumJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chSumJtpt_jet55_rej[0],"MC","pl");
    leg->AddEntry(hData_chSumJtpt_jet55_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchSumJtpt_jet55_rej[i]->SaveAs(Form("Plots/chSumJtpt_jet55_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * ceSumJtpt_jet55_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceSumJtpt_jet55_rej[i] = new TCanvas(Form("ceSumJtpt_jet55_rej_cent%d",i),"",800,600);
    ceSumJtpt_jet55_rej[i]->SetLogy();
    hMC_eSumJtpt_jet55_rej[i]->SetMarkerColor(kBlue+1);
    hMC_eSumJtpt_jet55_rej[i]->SetMarkerStyle(25);
    hMC_eSumJtpt_jet55_rej[i]->Print("base");
    hMC_eSumJtpt_jet55_rej[i]->SetTitle(" ");
    hMC_eSumJtpt_jet55_rej[i]->SetXTitle(Form("eSum/(ak%dPuPF jet p_{T}) jet55, fail CutA",radius));
    nMC_eSumJtpt_jet55_rej[i]=hMC_eSumJtpt_jet55_rej[i]->GetEntries();
    if (nMC_eSumJtpt_jet55_rej[i]>0){
       hMC_eSumJtpt_jet55_rej[i]->DrawNormalized();
    } else { cout<<"hMC_eSumJtpt_jet55_rej[i] for i= "<<i<<" has "<<nMC_eSumJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }

    hData_eSumJtpt_jet55_rej[i]->SetMarkerStyle(24);
    hData_eSumJtpt_jet55_rej[i]->SetMarkerColor(kBlack);
    nData_eSumJtpt_jet55_rej[i]=hData_eSumJtpt_jet55_rej[i]->GetEntries();
    if (nData_eSumJtpt_jet55_rej[i]>0){
      if(nMC_eSumJtpt_jet55_rej[i]<=0){
        hData_eSumJtpt_jet55_rej[i]->Print("base");
        hData_eSumJtpt_jet55_rej[i]->SetTitle(" ");
        hData_eSumJtpt_jet55_rej[i]->SetXTitle(Form("eSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_eSumJtpt_jet55_rej[i]->DrawNormalized();
      } else {
      hData_eSumJtpt_jet55_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_eSumJtpt_jet55_rej[i] for i= "<<i<<" has "<<nData_eSumJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eSumJtpt_jet55_rej[0],"MC","pl");
    leg->AddEntry(hData_eSumJtpt_jet55_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceSumJtpt_jet55_rej[i]->SaveAs(Form("Plots/eSumJtpt_jet55_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cphSumJtpt_jet55_rej[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphSumJtpt_jet55_rej[i] = new TCanvas(Form("cphSumJtpt_jet55_rej_cent%d",i),"",800,600);
    cphSumJtpt_jet55_rej[i]->SetLogy();
    hMC_phSumJtpt_jet55_rej[i]->SetMarkerColor(kGreen-3);
    hMC_phSumJtpt_jet55_rej[i]->SetMarkerStyle(25);
    hMC_phSumJtpt_jet55_rej[i]->Print("base");
    hMC_phSumJtpt_jet55_rej[i]->SetTitle(" ");
    hMC_phSumJtpt_jet55_rej[i]->SetXTitle(Form("phSum/(ak%dPuPF jet p_{T}) jet55, fail CutA",radius));
    nMC_phSumJtpt_jet55_rej[i]=hMC_phSumJtpt_jet55_rej[i]->GetEntries();
    if (nMC_phSumJtpt_jet55_rej[i]>0){
       hMC_phSumJtpt_jet55_rej[i]->DrawNormalized();
    } else { cout<<"hMC_phSumJtpt_jet55_rej[i] for i= "<<i<<" has "<<nMC_phSumJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }

    hData_phSumJtpt_jet55_rej[i]->SetMarkerStyle(24);
    hData_phSumJtpt_jet55_rej[i]->SetMarkerColor(kBlack);
    nData_phSumJtpt_jet55_rej[i]=hData_phSumJtpt_jet55_rej[i]->GetEntries();
    if (nData_phSumJtpt_jet55_rej[i]>0){
      if(nMC_phSumJtpt_jet55_rej[i]<=0){
        hData_phSumJtpt_jet55_rej[i]->Print("base");
        hData_phSumJtpt_jet55_rej[i]->SetTitle(" ");
        hData_phSumJtpt_jet55_rej[i]->SetXTitle(Form("phSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_phSumJtpt_jet55_rej[i]->DrawNormalized();
      } else {
      hData_phSumJtpt_jet55_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_phSumJtpt_jet55_rej[i] for i= "<<i<<" has "<<nData_phSumJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phSumJtpt_jet55_rej[0],"MC","pl");
    leg->AddEntry(hData_phSumJtpt_jet55_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphSumJtpt_jet55_rej[i]->SaveAs(Form("Plots/phSumJtpt_jet55_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cneSumJtpt_jet55_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneSumJtpt_jet55_rej[i] = new TCanvas(Form("cneSumJtpt_jet55_rej_cent%d",i),"",800,600);
    cneSumJtpt_jet55_rej[i]->SetLogy();
    hMC_neSumJtpt_jet55_rej[i]->SetMarkerColor(kMagenta+1);
    hMC_neSumJtpt_jet55_rej[i]->SetMarkerStyle(25);
    hMC_neSumJtpt_jet55_rej[i]->Print("base");
    hMC_neSumJtpt_jet55_rej[i]->SetTitle(" ");
    hMC_neSumJtpt_jet55_rej[i]->SetXTitle(Form("neSum/(ak%dPuPF jet p_{T}) jet55, fail CutA",radius));
    nMC_neSumJtpt_jet55_rej[i]=hMC_neSumJtpt_jet55_rej[i]->GetEntries();
    if (nMC_neSumJtpt_jet55_rej[i]>0){
       hMC_neSumJtpt_jet55_rej[i]->DrawNormalized();
    } else { cout<<"hMC_neSumJtpt_jet55_rej[i] for i= "<<i<<" has "<<nMC_neSumJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }

    hData_neSumJtpt_jet55_rej[i]->SetMarkerStyle(24);
    hData_neSumJtpt_jet55_rej[i]->SetMarkerColor(kBlack);
    nData_neSumJtpt_jet55_rej[i]=hData_neSumJtpt_jet55_rej[i]->GetEntries();
    if (nData_neSumJtpt_jet55_rej[i]>0){
      if(nMC_neSumJtpt_jet55_rej[i]<=0){
        hData_neSumJtpt_jet55_rej[i]->Print("base");
        hData_neSumJtpt_jet55_rej[i]->SetTitle(" ");
        hData_neSumJtpt_jet55_rej[i]->SetXTitle(Form("neSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_neSumJtpt_jet55_rej[i]->DrawNormalized();
      } else {
      hData_neSumJtpt_jet55_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_neSumJtpt_jet55_rej[i] for i= "<<i<<" has "<<nData_neSumJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neSumJtpt_jet55_rej[0],"MC","pl");
    leg->AddEntry(hData_neSumJtpt_jet55_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneSumJtpt_jet55_rej[i]->SaveAs(Form("Plots/neSumJtpt_jet55_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cmuSumJtpt_jet55_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuSumJtpt_jet55_rej[i] = new TCanvas(Form("cmuSumJtpt_jet55_rej_cent%d",i),"",800,600);
    cmuSumJtpt_jet55_rej[i]->SetLogy();
    hMC_muSumJtpt_jet55_rej[i]->SetMarkerColor(kCyan+1);
    hMC_muSumJtpt_jet55_rej[i]->SetMarkerStyle(25);
    hMC_muSumJtpt_jet55_rej[i]->Print("base");
    hMC_muSumJtpt_jet55_rej[i]->SetTitle(" ");
    hMC_muSumJtpt_jet55_rej[i]->SetXTitle(Form("muSum/(ak%dPuPF jet p_{T}) jet55, fail CutA",radius));
    nMC_muSumJtpt_jet55_rej[i]=hMC_muSumJtpt_jet55_rej[i]->GetEntries();
    if (nMC_muSumJtpt_jet55_rej[i]>0){
       hMC_muSumJtpt_jet55_rej[i]->DrawNormalized();
    } else { cout<<"hMC_muSumJtpt_jet55_rej[i] for i= "<<i<<" has "<<nMC_muSumJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }

    hData_muSumJtpt_jet55_rej[i]->SetMarkerStyle(24);
    hData_muSumJtpt_jet55_rej[i]->SetMarkerColor(kBlack);
    nData_muSumJtpt_jet55_rej[i]=hData_muSumJtpt_jet55_rej[i]->GetEntries();
    if (nData_muSumJtpt_jet55_rej[i]>0){
      if(nMC_muSumJtpt_jet55_rej[i]<=0){
        hData_muSumJtpt_jet55_rej[i]->Print("base");
        hData_muSumJtpt_jet55_rej[i]->SetTitle(" ");
        hData_muSumJtpt_jet55_rej[i]->SetXTitle(Form("muSum/(ak%dPuPF jet p_{T}) jet55, pass CutA",radius));      
        hData_muSumJtpt_jet55_rej[i]->DrawNormalized();
      } else {
      hData_muSumJtpt_jet55_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_muSumJtpt_jet55_rej[i] for i= "<<i<<" has "<<nData_muSumJtpt_jet55_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muSumJtpt_jet55_rej[0],"MC","pl");
    leg->AddEntry(hData_muSumJtpt_jet55_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuSumJtpt_jet55_rej[i]->SaveAs(Form("Plots/muSumJtpt_jet55_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  } 
//#endif
  TCanvas * cchMaxJtpt_jet65_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchMaxJtpt_jet65_keep[i] = new TCanvas(Form("cchMaxJtpt_jet65_keep_cent%d",i),"",800,600);
    cchMaxJtpt_jet65_keep[i]->SetLogy();
    hMC_chMaxJtpt_jet65_keep[i]->SetMarkerColor(kRed);
    hMC_chMaxJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_chMaxJtpt_jet65_keep[i]->Print("base");
    hMC_chMaxJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_chMaxJtpt_jet65_keep[i]->SetXTitle(Form("chMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));
    nMC_chMaxJtpt_jet65_keep[i]=hMC_chMaxJtpt_jet65_keep[i]->GetEntries();
    if (nMC_chMaxJtpt_jet65_keep[i]>0){
       hMC_chMaxJtpt_jet65_keep[i]->DrawNormalized();
    } else { cout<<"hMC_chMaxJtpt_jet65_keep[i] for i= "<<i<<" has "<<nMC_chMaxJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }

    hData_chMaxJtpt_jet65_keep[i]->SetMarkerStyle(24);
    hData_chMaxJtpt_jet65_keep[i]->SetMarkerColor(kBlack);
    nData_chMaxJtpt_jet65_keep[i]=hData_chMaxJtpt_jet65_keep[i]->GetEntries();
    if (nData_chMaxJtpt_jet65_keep[i]>0){
      if(nMC_chMaxJtpt_jet65_keep[i]<=0){
        hData_chMaxJtpt_jet65_keep[i]->Print("base");
        hData_chMaxJtpt_jet65_keep[i]->SetTitle(" ");
        hData_chMaxJtpt_jet65_keep[i]->SetXTitle(Form("chMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_chMaxJtpt_jet65_keep[i]->DrawNormalized();
      } else {
      hData_chMaxJtpt_jet65_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_chMaxJtpt_jet65_keep[i] for i= "<<i<<" has "<<nData_chMaxJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }      
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chMaxJtpt_jet65_keep[0],"MC","pl");
    leg->AddEntry(hData_chMaxJtpt_jet65_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchMaxJtpt_jet65_keep[i]->SaveAs(Form("Plots/chMaxJtpt_jet65_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  
  TCanvas * ceMaxJtpt_jet65_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceMaxJtpt_jet65_keep[i] = new TCanvas(Form("ceMaxJtpt_jet65_keep_cent%d",i),"",800,600);
    ceMaxJtpt_jet65_keep[i]->SetLogy();
    hMC_eMaxJtpt_jet65_keep[i]->SetMarkerColor(kBlue);
    hMC_eMaxJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_eMaxJtpt_jet65_keep[i]->Print("base");
    hMC_eMaxJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_eMaxJtpt_jet65_keep[i]->SetXTitle(Form("eMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));
    nMC_eMaxJtpt_jet65_keep[i]=hMC_eMaxJtpt_jet65_keep[i]->GetEntries();
    if (nMC_eMaxJtpt_jet65_keep[i]>0){
       hMC_eMaxJtpt_jet65_keep[i]->DrawNormalized();
    } else { cout<<"hMC_eMaxJtpt_jet65_keep[i] for i= "<<i<<" has "<<nMC_eMaxJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }

    hData_eMaxJtpt_jet65_keep[i]->SetMarkerStyle(24);
    hData_eMaxJtpt_jet65_keep[i]->SetMarkerColor(kBlack);
    nData_eMaxJtpt_jet65_keep[i]=hData_eMaxJtpt_jet65_keep[i]->GetEntries();
    if (nData_eMaxJtpt_jet65_keep[i]>0){
      if(nMC_eMaxJtpt_jet65_keep[i]<=0){
        hData_eMaxJtpt_jet65_keep[i]->Print("base");
        hData_eMaxJtpt_jet65_keep[i]->SetTitle(" ");
        hData_eMaxJtpt_jet65_keep[i]->SetXTitle(Form("eMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_eMaxJtpt_jet65_keep[i]->DrawNormalized();
      } else {
      hData_eMaxJtpt_jet65_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_eMaxJtpt_jet65_keep[i] for i= "<<i<<" has "<<nData_eMaxJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }   
        drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eMaxJtpt_jet65_keep[0],"MC","pl");
    leg->AddEntry(hData_eMaxJtpt_jet65_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceMaxJtpt_jet65_keep[i]->SaveAs(Form("Plots/eMaxJtpt_jet65_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }

   TCanvas * cphMaxJtpt_jet65_keep[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphMaxJtpt_jet65_keep[i] = new TCanvas(Form("cphMaxJtpt_jet65_keep_cent%d",i),"",800,600);
    cphMaxJtpt_jet65_keep[i]->SetLogy();
    hMC_phMaxJtpt_jet65_keep[i]->SetMarkerColor(kGreen+2);
    hMC_phMaxJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_phMaxJtpt_jet65_keep[i]->Print("base");
    hMC_phMaxJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_phMaxJtpt_jet65_keep[i]->SetXTitle(Form("phMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));
    nMC_phMaxJtpt_jet65_keep[i]=hMC_phMaxJtpt_jet65_keep[i]->GetEntries();
    if (nMC_phMaxJtpt_jet65_keep[i]>0){
       hMC_phMaxJtpt_jet65_keep[i]->DrawNormalized();
    } else { cout<<"hMC_phMaxJtpt_jet65_keep[i] for i= "<<i<<" has "<<nMC_phMaxJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }

    hData_phMaxJtpt_jet65_keep[i]->SetMarkerStyle(24);
    hData_phMaxJtpt_jet65_keep[i]->SetMarkerColor(kBlack);
    nData_phMaxJtpt_jet65_keep[i]=hData_phMaxJtpt_jet65_keep[i]->GetEntries();
    if (nData_phMaxJtpt_jet65_keep[i]>0){
      if(nMC_phMaxJtpt_jet65_keep[i]<=0){
        hData_phMaxJtpt_jet65_keep[i]->Print("base");
        hData_phMaxJtpt_jet65_keep[i]->SetTitle(" ");
        hData_phMaxJtpt_jet65_keep[i]->SetXTitle(Form("phMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_phMaxJtpt_jet65_keep[i]->DrawNormalized();
      } else {
      hData_phMaxJtpt_jet65_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_phMaxJtpt_jet65_keep[i] for i= "<<i<<" has "<<nData_phMaxJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }   
        drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phMaxJtpt_jet65_keep[0],"MC","pl");
    leg->AddEntry(hData_phMaxJtpt_jet65_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphMaxJtpt_jet65_keep[i]->SaveAs(Form("Plots/phMaxJtpt_jet65_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cneMaxJtpt_jet65_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneMaxJtpt_jet65_keep[i] = new TCanvas(Form("cneMaxJtpt_jet65_keep_cent%d",i),"",800,600);
    cneMaxJtpt_jet65_keep[i]->SetLogy();
    hMC_neMaxJtpt_jet65_keep[i]->SetMarkerColor(kMagenta);
    hMC_neMaxJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_neMaxJtpt_jet65_keep[i]->Print("base");
    hMC_neMaxJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_neMaxJtpt_jet65_keep[i]->SetXTitle(Form("neMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));
    nMC_neMaxJtpt_jet65_keep[i]=hMC_neMaxJtpt_jet65_keep[i]->GetEntries();
    if (nMC_neMaxJtpt_jet65_keep[i]>0){
       hMC_neMaxJtpt_jet65_keep[i]->DrawNormalized();
    } else { cout<<"hMC_neMaxJtpt_jet65_keep[i] for i= "<<i<<" has "<<nMC_neMaxJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }

    hData_neMaxJtpt_jet65_keep[i]->SetMarkerStyle(24);
    hData_neMaxJtpt_jet65_keep[i]->SetMarkerColor(kBlack);
    nData_neMaxJtpt_jet65_keep[i]=hData_neMaxJtpt_jet65_keep[i]->GetEntries();
    if (nData_neMaxJtpt_jet65_keep[i]>0){
      if(nMC_neMaxJtpt_jet65_keep[i]<=0){
        hData_neMaxJtpt_jet65_keep[i]->Print("base");
        hData_neMaxJtpt_jet65_keep[i]->SetTitle(" ");
        hData_neMaxJtpt_jet65_keep[i]->SetXTitle(Form("neMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_neMaxJtpt_jet65_keep[i]->DrawNormalized();
      } else {
      hData_neMaxJtpt_jet65_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_neMaxJtpt_jet65_keep[i] for i= "<<i<<" has "<<nData_neMaxJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neMaxJtpt_jet65_keep[0],"MC","pl");
    leg->AddEntry(hData_neMaxJtpt_jet65_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneMaxJtpt_jet65_keep[i]->SaveAs(Form("Plots/neMaxJtpt_jet65_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cmuMaxJtpt_jet65_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuMaxJtpt_jet65_keep[i] = new TCanvas(Form("cmuMaxJtpt_jet65_keep_cent%d",i),"",800,600);
    cmuMaxJtpt_jet65_keep[i]->SetLogy();
    hMC_muMaxJtpt_jet65_keep[i]->SetMarkerColor(kCyan);
    hMC_muMaxJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_muMaxJtpt_jet65_keep[i]->Print("base");
    hMC_muMaxJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_muMaxJtpt_jet65_keep[i]->SetXTitle(Form("muMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));
    nMC_muMaxJtpt_jet65_keep[i]=hMC_muMaxJtpt_jet65_keep[i]->GetEntries();
    if (nMC_muMaxJtpt_jet65_keep[i]>0){
       hMC_muMaxJtpt_jet65_keep[i]->DrawNormalized();
    } else { cout<<"hMC_muMaxJtpt_jet65_keep[i] for i= "<<i<<" has "<<nMC_muMaxJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }

    hData_muMaxJtpt_jet65_keep[i]->SetMarkerStyle(24);
    hData_muMaxJtpt_jet65_keep[i]->SetMarkerColor(kBlack);
    nData_muMaxJtpt_jet65_keep[i]=hData_muMaxJtpt_jet65_keep[i]->GetEntries();
    if (nData_muMaxJtpt_jet65_keep[i]>0){
      if(nMC_muMaxJtpt_jet65_keep[i]<=0){
        hData_muMaxJtpt_jet65_keep[i]->Print("base");
        hData_muMaxJtpt_jet65_keep[i]->SetTitle(" ");
        hData_muMaxJtpt_jet65_keep[i]->SetXTitle(Form("muMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_muMaxJtpt_jet65_keep[i]->DrawNormalized();
      } else {
      hData_muMaxJtpt_jet65_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_muMaxJtpt_jet65_keep[i] for i= "<<i<<" has "<<nData_muMaxJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muMaxJtpt_jet65_keep[0],"MC","pl");
    leg->AddEntry(hData_muMaxJtpt_jet65_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuMaxJtpt_jet65_keep[i]->SaveAs(Form("Plots/muMaxJtpt_jet65_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }    
// draw some Sum variables
  TCanvas * cchSumJtpt_jet65_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchSumJtpt_jet65_keep[i] = new TCanvas(Form("cchSumJtpt_jet65_keep_cent%d",i),"",800,600);
    cchSumJtpt_jet65_keep[i]->SetLogy();
    hMC_chSumJtpt_jet65_keep[i]->SetMarkerColor(kRed+1);
    hMC_chSumJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_chSumJtpt_jet65_keep[i]->Print("base");
    hMC_chSumJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_chSumJtpt_jet65_keep[i]->SetXTitle(Form("chSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));
    nMC_chSumJtpt_jet65_keep[i]=hMC_chSumJtpt_jet65_keep[i]->GetEntries();
    if (nMC_chSumJtpt_jet65_keep[i]>0){
       hMC_chSumJtpt_jet65_keep[i]->DrawNormalized();
    } else { cout<<"hMC_chSumJtpt_jet65_keep[i] for i= "<<i<<" has "<<nMC_chSumJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }

    hData_chSumJtpt_jet65_keep[i]->SetMarkerStyle(24);
    hData_chSumJtpt_jet65_keep[i]->SetMarkerColor(kBlack);
    nData_chSumJtpt_jet65_keep[i]=hData_chSumJtpt_jet65_keep[i]->GetEntries();
    if (nData_chSumJtpt_jet65_keep[i]>0){
      if(nMC_chSumJtpt_jet65_keep[i]<=0){
        hData_chSumJtpt_jet65_keep[i]->Print("base");
        hData_chSumJtpt_jet65_keep[i]->SetTitle(" ");
        hData_chSumJtpt_jet65_keep[i]->SetXTitle(Form("chSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_chSumJtpt_jet65_keep[i]->DrawNormalized();
      } else {
      hData_chSumJtpt_jet65_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_chSumJtpt_jet65_keep[i] for i= "<<i<<" has "<<nData_chSumJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }   
        drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chSumJtpt_jet65_keep[0],"MC","pl");
    leg->AddEntry(hData_chSumJtpt_jet65_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchSumJtpt_jet65_keep[i]->SaveAs(Form("Plots/chSumJtpt_jet65_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * ceSumJtpt_jet65_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceSumJtpt_jet65_keep[i] = new TCanvas(Form("ceSumJtpt_jet65_keep_cent%d",i),"",800,600);
    ceSumJtpt_jet65_keep[i]->SetLogy();
    hMC_eSumJtpt_jet65_keep[i]->SetMarkerColor(kBlue+1);
    hMC_eSumJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_eSumJtpt_jet65_keep[i]->Print("base");
    hMC_eSumJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_eSumJtpt_jet65_keep[i]->SetXTitle(Form("eSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));
    nMC_eSumJtpt_jet65_keep[i]=hMC_eSumJtpt_jet65_keep[i]->GetEntries();
    if (nMC_eSumJtpt_jet65_keep[i]>0){
       hMC_eSumJtpt_jet65_keep[i]->DrawNormalized();
    } else { cout<<"hMC_eSumJtpt_jet65_keep[i] for i= "<<i<<" has "<<nMC_eSumJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }

    hData_eSumJtpt_jet65_keep[i]->SetMarkerStyle(24);
    hData_eSumJtpt_jet65_keep[i]->SetMarkerColor(kBlack);
    nData_eSumJtpt_jet65_keep[i]=hData_eSumJtpt_jet65_keep[i]->GetEntries();
    if (nData_eSumJtpt_jet65_keep[i]>0){
      if(nMC_eSumJtpt_jet65_keep[i]<=0){
        hData_eSumJtpt_jet65_keep[i]->Print("base");
        hData_eSumJtpt_jet65_keep[i]->SetTitle(" ");
        hData_eSumJtpt_jet65_keep[i]->SetXTitle(Form("eSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_eSumJtpt_jet65_keep[i]->DrawNormalized();
      } else {
      hData_eSumJtpt_jet65_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_eSumJtpt_jet65_keep[i] for i= "<<i<<" has "<<nData_eSumJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }   
        drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eSumJtpt_jet65_keep[0],"MC","pl");
    leg->AddEntry(hData_eSumJtpt_jet65_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceSumJtpt_jet65_keep[i]->SaveAs(Form("Plots/eSumJtpt_jet65_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cphSumJtpt_jet65_keep[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphSumJtpt_jet65_keep[i] = new TCanvas(Form("cphSumJtpt_jet65_keep_cent%d",i),"",800,600);
    cphSumJtpt_jet65_keep[i]->SetLogy();
    hMC_phSumJtpt_jet65_keep[i]->SetMarkerColor(kGreen-3);
    hMC_phSumJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_phSumJtpt_jet65_keep[i]->Print("base");
    hMC_phSumJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_phSumJtpt_jet65_keep[i]->SetXTitle(Form("phSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));
    nMC_phSumJtpt_jet65_keep[i]=hMC_phSumJtpt_jet65_keep[i]->GetEntries();
    if (nMC_phSumJtpt_jet65_keep[i]>0){
       hMC_phSumJtpt_jet65_keep[i]->DrawNormalized();
    } else { cout<<"hMC_phSumJtpt_jet65_keep[i] for i= "<<i<<" has "<<nMC_phSumJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }

    hData_phSumJtpt_jet65_keep[i]->SetMarkerStyle(24);
    hData_phSumJtpt_jet65_keep[i]->SetMarkerColor(kBlack);
    nData_phSumJtpt_jet65_keep[i]=hData_phSumJtpt_jet65_keep[i]->GetEntries();
    if (nData_phSumJtpt_jet65_keep[i]>0){
      if(nMC_phSumJtpt_jet65_keep[i]<=0){
        hData_phSumJtpt_jet65_keep[i]->Print("base");
        hData_phSumJtpt_jet65_keep[i]->SetTitle(" ");
        hData_phSumJtpt_jet65_keep[i]->SetXTitle(Form("phSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_phSumJtpt_jet65_keep[i]->DrawNormalized();
      } else {
      hData_phSumJtpt_jet65_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_phSumJtpt_jet65_keep[i] for i= "<<i<<" has "<<nData_phSumJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phSumJtpt_jet65_keep[0],"MC","pl");
    leg->AddEntry(hData_phSumJtpt_jet65_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphSumJtpt_jet65_keep[i]->SaveAs(Form("Plots/phSumJtpt_jet65_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cneSumJtpt_jet65_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneSumJtpt_jet65_keep[i] = new TCanvas(Form("cneSumJtpt_jet65_keep_cent%d",i),"",800,600);
    cneSumJtpt_jet65_keep[i]->SetLogy();
    hMC_neSumJtpt_jet65_keep[i]->SetMarkerColor(kMagenta+1);
    hMC_neSumJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_neSumJtpt_jet65_keep[i]->Print("base");
    hMC_neSumJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_neSumJtpt_jet65_keep[i]->SetXTitle(Form("neSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));
    nMC_neSumJtpt_jet65_keep[i]=hMC_neSumJtpt_jet65_keep[i]->GetEntries();
    if (nMC_neSumJtpt_jet65_keep[i]>0){
       hMC_neSumJtpt_jet65_keep[i]->DrawNormalized();
    } else { cout<<"hMC_neSumJtpt_jet65_keep[i] for i= "<<i<<" has "<<nMC_neSumJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }

    hData_neSumJtpt_jet65_keep[i]->SetMarkerStyle(24);
    hData_neSumJtpt_jet65_keep[i]->SetMarkerColor(kBlack);
    nData_neSumJtpt_jet65_keep[i]=hData_neSumJtpt_jet65_keep[i]->GetEntries();
    if (nData_neSumJtpt_jet65_keep[i]>0){
      if(nMC_neSumJtpt_jet65_keep[i]<=0){
        hData_neSumJtpt_jet65_keep[i]->Print("base");
        hData_neSumJtpt_jet65_keep[i]->SetTitle(" ");
        hData_neSumJtpt_jet65_keep[i]->SetXTitle(Form("neSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_neSumJtpt_jet65_keep[i]->DrawNormalized();
      } else {
      hData_neSumJtpt_jet65_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_neSumJtpt_jet65_keep[i] for i= "<<i<<" has "<<nData_neSumJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neSumJtpt_jet65_keep[0],"MC","pl");
    leg->AddEntry(hData_neSumJtpt_jet65_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneSumJtpt_jet65_keep[i]->SaveAs(Form("Plots/neSumJtpt_jet65_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cmuSumJtpt_jet65_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuSumJtpt_jet65_keep[i] = new TCanvas(Form("cmuSumJtpt_jet65_keep_cent%d",i),"",800,600);
    cmuSumJtpt_jet65_keep[i]->SetLogy();
    hMC_muSumJtpt_jet65_keep[i]->SetMarkerColor(kCyan+1);
    hMC_muSumJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_muSumJtpt_jet65_keep[i]->Print("base");
    hMC_muSumJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_muSumJtpt_jet65_keep[i]->SetXTitle(Form("muSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));
    nMC_muSumJtpt_jet65_keep[i]=hMC_muSumJtpt_jet65_keep[i]->GetEntries();
    if (nMC_muSumJtpt_jet65_keep[i]>0){
       hMC_muSumJtpt_jet65_keep[i]->DrawNormalized();
    } else { cout<<"hMC_muSumJtpt_jet65_keep[i] for i= "<<i<<" has "<<nMC_muSumJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }

    hData_muSumJtpt_jet65_keep[i]->SetMarkerStyle(24);
    hData_muSumJtpt_jet65_keep[i]->SetMarkerColor(kBlack);
    nData_muSumJtpt_jet65_keep[i]=hData_muSumJtpt_jet65_keep[i]->GetEntries();
    if (nData_muSumJtpt_jet65_keep[i]>0){
      if(nMC_muSumJtpt_jet65_keep[i]<=0){
        hData_muSumJtpt_jet65_keep[i]->Print("base");
        hData_muSumJtpt_jet65_keep[i]->SetTitle(" ");
        hData_muSumJtpt_jet65_keep[i]->SetXTitle(Form("muSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_muSumJtpt_jet65_keep[i]->DrawNormalized();
      } else {
      hData_muSumJtpt_jet65_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_muSumJtpt_jet65_keep[i] for i= "<<i<<" has "<<nData_muSumJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muSumJtpt_jet65_keep[0],"MC","pl");
    leg->AddEntry(hData_muSumJtpt_jet65_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuSumJtpt_jet65_keep[i]->SaveAs(Form("Plots/muSumJtpt_jet65_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cchMaxJtpt_jet65_rej[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchMaxJtpt_jet65_rej[i] = new TCanvas(Form("cchMaxJtpt_jet65_rej_cent%d",i),"",800,600);
    cchMaxJtpt_jet65_rej[i]->SetLogy();
    hMC_chMaxJtpt_jet65_rej[i]->SetMarkerColor(kRed);
    hMC_chMaxJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_chMaxJtpt_jet65_rej[i]->Print("base");
    hMC_chMaxJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_chMaxJtpt_jet65_rej[i]->SetXTitle(Form("chMax/(ak%dPuPF jet p_{T}) jet65, fail CutA",radius));
    nMC_chMaxJtpt_jet65_rej[i]=hMC_chMaxJtpt_jet65_rej[i]->GetEntries();
    if (nMC_chMaxJtpt_jet65_rej[i]>0){
       hMC_chMaxJtpt_jet65_rej[i]->DrawNormalized();
    } else { cout<<"hMC_chMaxJtpt_jet65_rej[i] for i= "<<i<<" has "<<nMC_chMaxJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }

    hData_chMaxJtpt_jet65_rej[i]->SetMarkerStyle(24);
    hData_chMaxJtpt_jet65_rej[i]->SetMarkerColor(kBlack);
    nData_chMaxJtpt_jet65_rej[i]=hData_chMaxJtpt_jet65_rej[i]->GetEntries();
    if (nData_chMaxJtpt_jet65_rej[i]>0){
      if(nMC_chMaxJtpt_jet65_rej[i]<=0){
        hData_chMaxJtpt_jet65_rej[i]->Print("base");
        hData_chMaxJtpt_jet65_rej[i]->SetTitle(" ");
        hData_chMaxJtpt_jet65_rej[i]->SetXTitle(Form("chMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_chMaxJtpt_jet65_rej[i]->DrawNormalized();
      } else {
      hData_chMaxJtpt_jet65_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_chMaxJtpt_jet65_rej[i] for i= "<<i<<" has "<<nData_chMaxJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chMaxJtpt_jet65_rej[0],"MC","pl");
    leg->AddEntry(hData_chMaxJtpt_jet65_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchMaxJtpt_jet65_rej[i]->SaveAs(Form("Plots/chMaxJtpt_jet65_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  
  TCanvas * ceMaxJtpt_jet65_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceMaxJtpt_jet65_rej[i] = new TCanvas(Form("ceMaxJtpt_jet65_rej_cent%d",i),"",800,600);
    ceMaxJtpt_jet65_rej[i]->SetLogy();
    hMC_eMaxJtpt_jet65_rej[i]->SetMarkerColor(kBlue);
    hMC_eMaxJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_eMaxJtpt_jet65_rej[i]->Print("base");
    hMC_eMaxJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_eMaxJtpt_jet65_rej[i]->SetXTitle(Form("eMax/(ak%dPuPF jet p_{T}) jet65, fail CutA",radius));
    nMC_eMaxJtpt_jet65_rej[i]=hMC_eMaxJtpt_jet65_rej[i]->GetEntries();
    if (nMC_eMaxJtpt_jet65_rej[i]>0){
       hMC_eMaxJtpt_jet65_rej[i]->DrawNormalized();
    } else { cout<<"hMC_eMaxJtpt_jet65_rej[i] for i= "<<i<<" has "<<nMC_eMaxJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }

    hData_eMaxJtpt_jet65_rej[i]->SetMarkerStyle(24);
    hData_eMaxJtpt_jet65_rej[i]->SetMarkerColor(kBlack);
    nData_eMaxJtpt_jet65_rej[i]=hData_eMaxJtpt_jet65_rej[i]->GetEntries();
    if (nData_eMaxJtpt_jet65_rej[i]>0){
      if(nMC_eMaxJtpt_jet65_rej[i]<=0){
        hData_eMaxJtpt_jet65_rej[i]->Print("base");
        hData_eMaxJtpt_jet65_rej[i]->SetTitle(" ");
        hData_eMaxJtpt_jet65_rej[i]->SetXTitle(Form("eMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_eMaxJtpt_jet65_rej[i]->DrawNormalized();
      } else {
      hData_eMaxJtpt_jet65_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_eMaxJtpt_jet65_rej[i] for i= "<<i<<" has "<<nData_eMaxJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eMaxJtpt_jet65_rej[0],"MC","pl");
    leg->AddEntry(hData_eMaxJtpt_jet65_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceMaxJtpt_jet65_rej[i]->SaveAs(Form("Plots/eMaxJtpt_jet65_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }

   TCanvas * cphMaxJtpt_jet65_rej[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphMaxJtpt_jet65_rej[i] = new TCanvas(Form("cphMaxJtpt_jet65_rej_cent%d",i),"",800,600);
    cphMaxJtpt_jet65_rej[i]->SetLogy();
    hMC_phMaxJtpt_jet65_rej[i]->SetMarkerColor(kGreen+2);
    hMC_phMaxJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_phMaxJtpt_jet65_rej[i]->Print("base");
    hMC_phMaxJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_phMaxJtpt_jet65_rej[i]->SetXTitle(Form("phMax/(ak%dPuPF jet p_{T}) jet65, fail CutA",radius));
    nMC_phMaxJtpt_jet65_rej[i]=hMC_phMaxJtpt_jet65_rej[i]->GetEntries();
    if (nMC_phMaxJtpt_jet65_rej[i]>0){
       hMC_phMaxJtpt_jet65_rej[i]->DrawNormalized();
    } else { cout<<"hMC_phMaxJtpt_jet65_rej[i] for i= "<<i<<" has "<<nMC_phMaxJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }

    hData_phMaxJtpt_jet65_rej[i]->SetMarkerStyle(24);
    hData_phMaxJtpt_jet65_rej[i]->SetMarkerColor(kBlack);
    nData_phMaxJtpt_jet65_rej[i]=hData_phMaxJtpt_jet65_rej[i]->GetEntries();
    if (nData_phMaxJtpt_jet65_rej[i]>0){
      if(nMC_phMaxJtpt_jet65_rej[i]<=0){
        hData_phMaxJtpt_jet65_rej[i]->Print("base");
        hData_phMaxJtpt_jet65_rej[i]->SetTitle(" ");
        hData_phMaxJtpt_jet65_rej[i]->SetXTitle(Form("phMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_phMaxJtpt_jet65_rej[i]->DrawNormalized();
      } else {
      hData_phMaxJtpt_jet65_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_phMaxJtpt_jet65_rej[i] for i= "<<i<<" has "<<nData_phMaxJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phMaxJtpt_jet65_rej[0],"MC","pl");
    leg->AddEntry(hData_phMaxJtpt_jet65_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphMaxJtpt_jet65_rej[i]->SaveAs(Form("Plots/phMaxJtpt_jet65_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cneMaxJtpt_jet65_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneMaxJtpt_jet65_rej[i] = new TCanvas(Form("cneMaxJtpt_jet65_rej_cent%d",i),"",800,600);
    cneMaxJtpt_jet65_rej[i]->SetLogy();
    hMC_neMaxJtpt_jet65_rej[i]->SetMarkerColor(kMagenta);
    hMC_neMaxJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_neMaxJtpt_jet65_rej[i]->Print("base");
    hMC_neMaxJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_neMaxJtpt_jet65_rej[i]->SetXTitle(Form("neMax/(ak%dPuPF jet p_{T}) jet65, fail CutA",radius));
    nMC_neMaxJtpt_jet65_rej[i]=hMC_neMaxJtpt_jet65_rej[i]->GetEntries();
    if (nMC_neMaxJtpt_jet65_rej[i]>0){
       hMC_neMaxJtpt_jet65_rej[i]->DrawNormalized();
    } else { cout<<"hMC_neMaxJtpt_jet65_rej[i] for i= "<<i<<" has "<<nMC_neMaxJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }

    hData_neMaxJtpt_jet65_rej[i]->SetMarkerStyle(24);
    hData_neMaxJtpt_jet65_rej[i]->SetMarkerColor(kBlack);
    nData_neMaxJtpt_jet65_rej[i]=hData_neMaxJtpt_jet65_rej[i]->GetEntries();
    if (nData_neMaxJtpt_jet65_rej[i]>0){
      if(nMC_neMaxJtpt_jet65_rej[i]<=0){
        hData_neMaxJtpt_jet65_rej[i]->Print("base");
        hData_neMaxJtpt_jet65_rej[i]->SetTitle(" ");
        hData_neMaxJtpt_jet65_rej[i]->SetXTitle(Form("neMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_neMaxJtpt_jet65_rej[i]->DrawNormalized();
      } else {
      hData_neMaxJtpt_jet65_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_neMaxJtpt_jet65_rej[i] for i= "<<i<<" has "<<nData_neMaxJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neMaxJtpt_jet65_rej[0],"MC","pl");
    leg->AddEntry(hData_neMaxJtpt_jet65_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneMaxJtpt_jet65_rej[i]->SaveAs(Form("Plots/neMaxJtpt_jet65_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cmuMaxJtpt_jet65_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuMaxJtpt_jet65_rej[i] = new TCanvas(Form("cmuMaxJtpt_jet65_rej_cent%d",i),"",800,600);
    cmuMaxJtpt_jet65_rej[i]->SetLogy();
    hMC_muMaxJtpt_jet65_rej[i]->SetMarkerColor(kCyan);
    hMC_muMaxJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_muMaxJtpt_jet65_rej[i]->Print("base");
    hMC_muMaxJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_muMaxJtpt_jet65_rej[i]->SetXTitle(Form("muMax/(ak%dPuPF jet p_{T}) jet65, fail CutA",radius));
    nMC_muMaxJtpt_jet65_rej[i]=hMC_muMaxJtpt_jet65_rej[i]->GetEntries();
    if (nMC_muMaxJtpt_jet65_rej[i]>0){
       hMC_muMaxJtpt_jet65_rej[i]->DrawNormalized();
    } else { cout<<"hMC_muMaxJtpt_jet65_rej[i] for i= "<<i<<" has "<<nMC_muMaxJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }

    hData_muMaxJtpt_jet65_rej[i]->SetMarkerStyle(24);
    hData_muMaxJtpt_jet65_rej[i]->SetMarkerColor(kBlack);
    nData_muMaxJtpt_jet65_rej[i]=hData_muMaxJtpt_jet65_rej[i]->GetEntries();
    if (nData_muMaxJtpt_jet65_rej[i]>0){
      if(nMC_muMaxJtpt_jet65_rej[i]<=0){
        hData_muMaxJtpt_jet65_rej[i]->Print("base");
        hData_muMaxJtpt_jet65_rej[i]->SetTitle(" ");
        hData_muMaxJtpt_jet65_rej[i]->SetXTitle(Form("muMax/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_muMaxJtpt_jet65_rej[i]->DrawNormalized();
      } else {
      hData_muMaxJtpt_jet65_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_muMaxJtpt_jet65_rej[i] for i= "<<i<<" has "<<nData_muMaxJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; } 
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muMaxJtpt_jet65_rej[0],"MC","pl");
    leg->AddEntry(hData_muMaxJtpt_jet65_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuMaxJtpt_jet65_rej[i]->SaveAs(Form("Plots/muMaxJtpt_jet65_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }    
// draw some Sum variables
  TCanvas * cchSumJtpt_jet65_rej[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchSumJtpt_jet65_rej[i] = new TCanvas(Form("cchSumJtpt_jet65_rej_cent%d",i),"",800,600);
    cchSumJtpt_jet65_rej[i]->SetLogy();
    hMC_chSumJtpt_jet65_rej[i]->SetMarkerColor(kRed+1);
    hMC_chSumJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_chSumJtpt_jet65_rej[i]->Print("base");
    hMC_chSumJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_chSumJtpt_jet65_rej[i]->SetXTitle(Form("chSum/(ak%dPuPF jet p_{T}) jet65, fail CutA",radius));
    nMC_chSumJtpt_jet65_rej[i]=hMC_chSumJtpt_jet65_rej[i]->GetEntries();
    if (nMC_chSumJtpt_jet65_rej[i]>0){
       hMC_chSumJtpt_jet65_rej[i]->DrawNormalized();
    } else { cout<<"hMC_chSumJtpt_jet65_rej[i] for i= "<<i<<" has "<<nMC_chSumJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }

    hData_chSumJtpt_jet65_rej[i]->SetMarkerStyle(24);
    hData_chSumJtpt_jet65_rej[i]->SetMarkerColor(kBlack);
    nData_chSumJtpt_jet65_rej[i]=hData_chSumJtpt_jet65_rej[i]->GetEntries();
    if (nData_chSumJtpt_jet65_rej[i]>0){
      if(nMC_chSumJtpt_jet65_rej[i]<=0){
        hData_chSumJtpt_jet65_rej[i]->Print("base");
        hData_chSumJtpt_jet65_rej[i]->SetTitle(" ");
        hData_chSumJtpt_jet65_rej[i]->SetXTitle(Form("chSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_chSumJtpt_jet65_rej[i]->DrawNormalized();
      } else {
      hData_chSumJtpt_jet65_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_chSumJtpt_jet65_rej[i] for i= "<<i<<" has "<<nData_chSumJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chSumJtpt_jet65_rej[0],"MC","pl");
    leg->AddEntry(hData_chSumJtpt_jet65_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchSumJtpt_jet65_rej[i]->SaveAs(Form("Plots/chSumJtpt_jet65_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * ceSumJtpt_jet65_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceSumJtpt_jet65_rej[i] = new TCanvas(Form("ceSumJtpt_jet65_rej_cent%d",i),"",800,600);
    ceSumJtpt_jet65_rej[i]->SetLogy();
    hMC_eSumJtpt_jet65_rej[i]->SetMarkerColor(kBlue+1);
    hMC_eSumJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_eSumJtpt_jet65_rej[i]->Print("base");
    hMC_eSumJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_eSumJtpt_jet65_rej[i]->SetXTitle(Form("eSum/(ak%dPuPF jet p_{T}) jet65, fail CutA",radius));
    nMC_eSumJtpt_jet65_rej[i]=hMC_eSumJtpt_jet65_rej[i]->GetEntries();
    if (nMC_eSumJtpt_jet65_rej[i]>0){
       hMC_eSumJtpt_jet65_rej[i]->DrawNormalized();
    } else { cout<<"hMC_eSumJtpt_jet65_rej[i] for i= "<<i<<" has "<<nMC_eSumJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }

    hData_eSumJtpt_jet65_rej[i]->SetMarkerStyle(24);
    hData_eSumJtpt_jet65_rej[i]->SetMarkerColor(kBlack);
    nData_eSumJtpt_jet65_rej[i]=hData_eSumJtpt_jet65_rej[i]->GetEntries();
    if (nData_eSumJtpt_jet65_rej[i]>0){
      if(nMC_eSumJtpt_jet65_rej[i]<=0){
        hData_eSumJtpt_jet65_rej[i]->Print("base");
        hData_eSumJtpt_jet65_rej[i]->SetTitle(" ");
        hData_eSumJtpt_jet65_rej[i]->SetXTitle(Form("eSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_eSumJtpt_jet65_rej[i]->DrawNormalized();
      } else {
      hData_eSumJtpt_jet65_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_eSumJtpt_jet65_rej[i] for i= "<<i<<" has "<<nData_eSumJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eSumJtpt_jet65_rej[0],"MC","pl");
    leg->AddEntry(hData_eSumJtpt_jet65_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceSumJtpt_jet65_rej[i]->SaveAs(Form("Plots/eSumJtpt_jet65_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cphSumJtpt_jet65_rej[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphSumJtpt_jet65_rej[i] = new TCanvas(Form("cphSumJtpt_jet65_rej_cent%d",i),"",800,600);
    cphSumJtpt_jet65_rej[i]->SetLogy();
    hMC_phSumJtpt_jet65_rej[i]->SetMarkerColor(kGreen-3);
    hMC_phSumJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_phSumJtpt_jet65_rej[i]->Print("base");
    hMC_phSumJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_phSumJtpt_jet65_rej[i]->SetXTitle(Form("phSum/(ak%dPuPF jet p_{T}) jet65, fail CutA",radius));
    nMC_phSumJtpt_jet65_rej[i]=hMC_phSumJtpt_jet65_rej[i]->GetEntries();
    if (nMC_phSumJtpt_jet65_rej[i]>0){
       hMC_phSumJtpt_jet65_rej[i]->DrawNormalized();
    } else { cout<<"hMC_phSumJtpt_jet65_rej[i] for i= "<<i<<" has "<<nMC_phSumJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }

    hData_phSumJtpt_jet65_rej[i]->SetMarkerStyle(24);
    hData_phSumJtpt_jet65_rej[i]->SetMarkerColor(kBlack);
    nData_phSumJtpt_jet65_rej[i]=hData_phSumJtpt_jet65_rej[i]->GetEntries();
    if (nData_phSumJtpt_jet65_rej[i]>0){
      if(nMC_phSumJtpt_jet65_rej[i]<=0){
        hData_phSumJtpt_jet65_rej[i]->Print("base");
        hData_phSumJtpt_jet65_rej[i]->SetTitle(" ");
        hData_phSumJtpt_jet65_rej[i]->SetXTitle(Form("phSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_phSumJtpt_jet65_rej[i]->DrawNormalized();
      } else {
      hData_phSumJtpt_jet65_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_phSumJtpt_jet65_rej[i] for i= "<<i<<" has "<<nData_phSumJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phSumJtpt_jet65_rej[0],"MC","pl");
    leg->AddEntry(hData_phSumJtpt_jet65_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphSumJtpt_jet65_rej[i]->SaveAs(Form("Plots/phSumJtpt_jet65_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cneSumJtpt_jet65_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneSumJtpt_jet65_rej[i] = new TCanvas(Form("cneSumJtpt_jet65_rej_cent%d",i),"",800,600);
    cneSumJtpt_jet65_rej[i]->SetLogy();
    hMC_neSumJtpt_jet65_rej[i]->SetMarkerColor(kMagenta+1);
    hMC_neSumJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_neSumJtpt_jet65_rej[i]->Print("base");
    hMC_neSumJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_neSumJtpt_jet65_rej[i]->SetXTitle(Form("neSum/(ak%dPuPF jet p_{T}) jet65, fail CutA",radius));
    nMC_neSumJtpt_jet65_rej[i]=hMC_neSumJtpt_jet65_rej[i]->GetEntries();
    if (nMC_neSumJtpt_jet65_rej[i]>0){
       hMC_neSumJtpt_jet65_rej[i]->DrawNormalized();
    } else { cout<<"hMC_neSumJtpt_jet65_rej[i] for i= "<<i<<" has "<<nMC_neSumJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }

    hData_neSumJtpt_jet65_rej[i]->SetMarkerStyle(24);
    hData_neSumJtpt_jet65_rej[i]->SetMarkerColor(kBlack);
    nData_neSumJtpt_jet65_rej[i]=hData_neSumJtpt_jet65_rej[i]->GetEntries();
    if (nData_neSumJtpt_jet65_rej[i]>0){
      if(nMC_neSumJtpt_jet65_rej[i]<=0){
        hData_neSumJtpt_jet65_rej[i]->Print("base");
        hData_neSumJtpt_jet65_rej[i]->SetTitle(" ");
        hData_neSumJtpt_jet65_rej[i]->SetXTitle(Form("neSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_neSumJtpt_jet65_rej[i]->DrawNormalized();
      } else {
      hData_neSumJtpt_jet65_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_neSumJtpt_jet65_rej[i] for i= "<<i<<" has "<<nData_neSumJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neSumJtpt_jet65_rej[0],"MC","pl");
    leg->AddEntry(hData_neSumJtpt_jet65_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneSumJtpt_jet65_rej[i]->SaveAs(Form("Plots/neSumJtpt_jet65_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cmuSumJtpt_jet65_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuSumJtpt_jet65_rej[i] = new TCanvas(Form("cmuSumJtpt_jet65_rej_cent%d",i),"",800,600);
    cmuSumJtpt_jet65_rej[i]->SetLogy();
    hMC_muSumJtpt_jet65_rej[i]->SetMarkerColor(kCyan+1);
    hMC_muSumJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_muSumJtpt_jet65_rej[i]->Print("base");
    hMC_muSumJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_muSumJtpt_jet65_rej[i]->SetXTitle(Form("muSum/(ak%dPuPF jet p_{T}) jet65, fail CutA",radius));
    nMC_muSumJtpt_jet65_rej[i]=hMC_muSumJtpt_jet65_rej[i]->GetEntries();
    if (nMC_muSumJtpt_jet65_rej[i]>0){
       hMC_muSumJtpt_jet65_rej[i]->DrawNormalized();
    } else { cout<<"hMC_muSumJtpt_jet65_rej[i] for i= "<<i<<" has "<<nMC_muSumJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }

    hData_muSumJtpt_jet65_rej[i]->SetMarkerStyle(24);
    hData_muSumJtpt_jet65_rej[i]->SetMarkerColor(kBlack);
    nData_muSumJtpt_jet65_rej[i]=hData_muSumJtpt_jet65_rej[i]->GetEntries();
    if (nData_muSumJtpt_jet65_rej[i]>0){
      if(nMC_muSumJtpt_jet65_rej[i]<=0){
        hData_muSumJtpt_jet65_rej[i]->Print("base");
        hData_muSumJtpt_jet65_rej[i]->SetTitle(" ");
        hData_muSumJtpt_jet65_rej[i]->SetXTitle(Form("muSum/(ak%dPuPF jet p_{T}) jet65, pass CutA",radius));      
        hData_muSumJtpt_jet65_rej[i]->DrawNormalized();
      } else {
      hData_muSumJtpt_jet65_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_muSumJtpt_jet65_rej[i] for i= "<<i<<" has "<<nData_muSumJtpt_jet65_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muSumJtpt_jet65_rej[0],"MC","pl");
    leg->AddEntry(hData_muSumJtpt_jet65_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuSumJtpt_jet65_rej[i]->SaveAs(Form("Plots/muSumJtpt_jet65_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }  

// plot jet80
  TCanvas * cchMaxJtpt_jet80_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchMaxJtpt_jet80_keep[i] = new TCanvas(Form("cchMaxJtpt_jet80_keep_cent%d",i),"",800,600);
    cchMaxJtpt_jet80_keep[i]->SetLogy();
    hMC_chMaxJtpt_jet80_keep[i]->SetMarkerColor(kRed);
    hMC_chMaxJtpt_jet80_keep[i]->SetMarkerStyle(25);
    hMC_chMaxJtpt_jet80_keep[i]->Print("base");
    hMC_chMaxJtpt_jet80_keep[i]->SetTitle(" ");
    hMC_chMaxJtpt_jet80_keep[i]->SetXTitle(Form("chMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));
    nMC_chMaxJtpt_jet80_keep[i]=hMC_chMaxJtpt_jet80_keep[i]->GetEntries();
    if (nMC_chMaxJtpt_jet80_keep[i]>0){
       hMC_chMaxJtpt_jet80_keep[i]->DrawNormalized();
    } else { cout<<"hMC_chMaxJtpt_jet80_keep[i] for i= "<<i<<" has "<<nMC_chMaxJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }

    hData_chMaxJtpt_jet80_keep[i]->SetMarkerStyle(24);
    hData_chMaxJtpt_jet80_keep[i]->SetMarkerColor(kBlack);
    nData_chMaxJtpt_jet80_keep[i]=hData_chMaxJtpt_jet80_keep[i]->GetEntries();
    if (nData_chMaxJtpt_jet80_keep[i]>0){
      if(nMC_chMaxJtpt_jet80_keep[i]<=0){
        hData_chMaxJtpt_jet80_keep[i]->Print("base");
        hData_chMaxJtpt_jet80_keep[i]->SetTitle(" ");
        hData_chMaxJtpt_jet80_keep[i]->SetXTitle(Form("chMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_chMaxJtpt_jet80_keep[i]->DrawNormalized();
      } else {
      hData_chMaxJtpt_jet80_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_chMaxJtpt_jet80_keep[i] for i= "<<i<<" has "<<nData_chMaxJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }      
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chMaxJtpt_jet80_keep[0],"MC","pl");
    leg->AddEntry(hData_chMaxJtpt_jet80_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchMaxJtpt_jet80_keep[i]->SaveAs(Form("Plots/chMaxJtpt_jet80_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  
  TCanvas * ceMaxJtpt_jet80_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceMaxJtpt_jet80_keep[i] = new TCanvas(Form("ceMaxJtpt_jet80_keep_cent%d",i),"",800,600);
    ceMaxJtpt_jet80_keep[i]->SetLogy();
    hMC_eMaxJtpt_jet80_keep[i]->SetMarkerColor(kBlue);
    hMC_eMaxJtpt_jet80_keep[i]->SetMarkerStyle(25);
    hMC_eMaxJtpt_jet80_keep[i]->Print("base");
    hMC_eMaxJtpt_jet80_keep[i]->SetTitle(" ");
    hMC_eMaxJtpt_jet80_keep[i]->SetXTitle(Form("eMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));
    nMC_eMaxJtpt_jet80_keep[i]=hMC_eMaxJtpt_jet80_keep[i]->GetEntries();
    if (nMC_eMaxJtpt_jet80_keep[i]>0){
       hMC_eMaxJtpt_jet80_keep[i]->DrawNormalized();
    } else { cout<<"hMC_eMaxJtpt_jet80_keep[i] for i= "<<i<<" has "<<nMC_eMaxJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }

    hData_eMaxJtpt_jet80_keep[i]->SetMarkerStyle(24);
    hData_eMaxJtpt_jet80_keep[i]->SetMarkerColor(kBlack);
    nData_eMaxJtpt_jet80_keep[i]=hData_eMaxJtpt_jet80_keep[i]->GetEntries();
    if (nData_eMaxJtpt_jet80_keep[i]>0){
      if(nMC_eMaxJtpt_jet80_keep[i]<=0){
        hData_eMaxJtpt_jet80_keep[i]->Print("base");
        hData_eMaxJtpt_jet80_keep[i]->SetTitle(" ");
        hData_eMaxJtpt_jet80_keep[i]->SetXTitle(Form("eMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_eMaxJtpt_jet80_keep[i]->DrawNormalized();
      } else {
      hData_eMaxJtpt_jet80_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_eMaxJtpt_jet80_keep[i] for i= "<<i<<" has "<<nData_eMaxJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }   
        drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eMaxJtpt_jet80_keep[0],"MC","pl");
    leg->AddEntry(hData_eMaxJtpt_jet80_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceMaxJtpt_jet80_keep[i]->SaveAs(Form("Plots/eMaxJtpt_jet80_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }

   TCanvas * cphMaxJtpt_jet80_keep[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphMaxJtpt_jet80_keep[i] = new TCanvas(Form("cphMaxJtpt_jet80_keep_cent%d",i),"",800,600);
    cphMaxJtpt_jet80_keep[i]->SetLogy();
    hMC_phMaxJtpt_jet80_keep[i]->SetMarkerColor(kGreen+2);
    hMC_phMaxJtpt_jet80_keep[i]->SetMarkerStyle(25);
    hMC_phMaxJtpt_jet80_keep[i]->Print("base");
    hMC_phMaxJtpt_jet80_keep[i]->SetTitle(" ");
    hMC_phMaxJtpt_jet80_keep[i]->SetXTitle(Form("phMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));
    nMC_phMaxJtpt_jet80_keep[i]=hMC_phMaxJtpt_jet80_keep[i]->GetEntries();
    if (nMC_phMaxJtpt_jet80_keep[i]>0){
       hMC_phMaxJtpt_jet80_keep[i]->DrawNormalized();
    } else { cout<<"hMC_phMaxJtpt_jet80_keep[i] for i= "<<i<<" has "<<nMC_phMaxJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }

    hData_phMaxJtpt_jet80_keep[i]->SetMarkerStyle(24);
    hData_phMaxJtpt_jet80_keep[i]->SetMarkerColor(kBlack);
    nData_phMaxJtpt_jet80_keep[i]=hData_phMaxJtpt_jet80_keep[i]->GetEntries();
    if (nData_phMaxJtpt_jet80_keep[i]>0){
      if(nMC_phMaxJtpt_jet80_keep[i]<=0){
        hData_phMaxJtpt_jet80_keep[i]->Print("base");
        hData_phMaxJtpt_jet80_keep[i]->SetTitle(" ");
        hData_phMaxJtpt_jet80_keep[i]->SetXTitle(Form("phMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_phMaxJtpt_jet80_keep[i]->DrawNormalized();
      } else {
      hData_phMaxJtpt_jet80_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_phMaxJtpt_jet80_keep[i] for i= "<<i<<" has "<<nData_phMaxJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }   
        drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phMaxJtpt_jet80_keep[0],"MC","pl");
    leg->AddEntry(hData_phMaxJtpt_jet80_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphMaxJtpt_jet80_keep[i]->SaveAs(Form("Plots/phMaxJtpt_jet80_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cneMaxJtpt_jet80_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneMaxJtpt_jet80_keep[i] = new TCanvas(Form("cneMaxJtpt_jet80_keep_cent%d",i),"",800,600);
    cneMaxJtpt_jet80_keep[i]->SetLogy();
    hMC_neMaxJtpt_jet80_keep[i]->SetMarkerColor(kMagenta);
    hMC_neMaxJtpt_jet80_keep[i]->SetMarkerStyle(25);
    hMC_neMaxJtpt_jet80_keep[i]->Print("base");
    hMC_neMaxJtpt_jet80_keep[i]->SetTitle(" ");
    hMC_neMaxJtpt_jet80_keep[i]->SetXTitle(Form("neMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));
    nMC_neMaxJtpt_jet80_keep[i]=hMC_neMaxJtpt_jet80_keep[i]->GetEntries();
    if (nMC_neMaxJtpt_jet80_keep[i]>0){
       hMC_neMaxJtpt_jet80_keep[i]->DrawNormalized();
    } else { cout<<"hMC_neMaxJtpt_jet80_keep[i] for i= "<<i<<" has "<<nMC_neMaxJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }

    hData_neMaxJtpt_jet80_keep[i]->SetMarkerStyle(24);
    hData_neMaxJtpt_jet80_keep[i]->SetMarkerColor(kBlack);
    nData_neMaxJtpt_jet80_keep[i]=hData_neMaxJtpt_jet80_keep[i]->GetEntries();
    if (nData_neMaxJtpt_jet80_keep[i]>0){
      if(nMC_neMaxJtpt_jet80_keep[i]<=0){
        hData_neMaxJtpt_jet80_keep[i]->Print("base");
        hData_neMaxJtpt_jet80_keep[i]->SetTitle(" ");
        hData_neMaxJtpt_jet80_keep[i]->SetXTitle(Form("neMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_neMaxJtpt_jet80_keep[i]->DrawNormalized();
      } else {
      hData_neMaxJtpt_jet80_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_neMaxJtpt_jet80_keep[i] for i= "<<i<<" has "<<nData_neMaxJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neMaxJtpt_jet80_keep[0],"MC","pl");
    leg->AddEntry(hData_neMaxJtpt_jet80_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneMaxJtpt_jet80_keep[i]->SaveAs(Form("Plots/neMaxJtpt_jet80_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cmuMaxJtpt_jet80_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuMaxJtpt_jet80_keep[i] = new TCanvas(Form("cmuMaxJtpt_jet80_keep_cent%d",i),"",800,600);
    cmuMaxJtpt_jet80_keep[i]->SetLogy();
    hMC_muMaxJtpt_jet80_keep[i]->SetMarkerColor(kCyan);
    hMC_muMaxJtpt_jet80_keep[i]->SetMarkerStyle(25);
    hMC_muMaxJtpt_jet80_keep[i]->Print("base");
    hMC_muMaxJtpt_jet80_keep[i]->SetTitle(" ");
    hMC_muMaxJtpt_jet80_keep[i]->SetXTitle(Form("muMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));
    nMC_muMaxJtpt_jet80_keep[i]=hMC_muMaxJtpt_jet80_keep[i]->GetEntries();
    if (nMC_muMaxJtpt_jet80_keep[i]>0){
       hMC_muMaxJtpt_jet80_keep[i]->DrawNormalized();
    } else { cout<<"hMC_muMaxJtpt_jet80_keep[i] for i= "<<i<<" has "<<nMC_muMaxJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }

    hData_muMaxJtpt_jet80_keep[i]->SetMarkerStyle(24);
    hData_muMaxJtpt_jet80_keep[i]->SetMarkerColor(kBlack);
    nData_muMaxJtpt_jet80_keep[i]=hData_muMaxJtpt_jet80_keep[i]->GetEntries();
    if (nData_muMaxJtpt_jet80_keep[i]>0){
      if(nMC_muMaxJtpt_jet80_keep[i]<=0){
        hData_muMaxJtpt_jet80_keep[i]->Print("base");
        hData_muMaxJtpt_jet80_keep[i]->SetTitle(" ");
        hData_muMaxJtpt_jet80_keep[i]->SetXTitle(Form("muMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_muMaxJtpt_jet80_keep[i]->DrawNormalized();
      } else {
      hData_muMaxJtpt_jet80_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_muMaxJtpt_jet80_keep[i] for i= "<<i<<" has "<<nData_muMaxJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muMaxJtpt_jet80_keep[0],"MC","pl");
    leg->AddEntry(hData_muMaxJtpt_jet80_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuMaxJtpt_jet80_keep[i]->SaveAs(Form("Plots/muMaxJtpt_jet80_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }    
// draw some Sum variables
  TCanvas * cchSumJtpt_jet80_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchSumJtpt_jet80_keep[i] = new TCanvas(Form("cchSumJtpt_jet80_keep_cent%d",i),"",800,600);
    cchSumJtpt_jet80_keep[i]->SetLogy();
    hMC_chSumJtpt_jet80_keep[i]->SetMarkerColor(kRed+1);
    hMC_chSumJtpt_jet80_keep[i]->SetMarkerStyle(25);
    hMC_chSumJtpt_jet80_keep[i]->Print("base");
    hMC_chSumJtpt_jet80_keep[i]->SetTitle(" ");
    hMC_chSumJtpt_jet80_keep[i]->SetXTitle(Form("chSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));
    nMC_chSumJtpt_jet80_keep[i]=hMC_chSumJtpt_jet80_keep[i]->GetEntries();
    if (nMC_chSumJtpt_jet80_keep[i]>0){
       hMC_chSumJtpt_jet80_keep[i]->DrawNormalized();
    } else { cout<<"hMC_chSumJtpt_jet80_keep[i] for i= "<<i<<" has "<<nMC_chSumJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }

    hData_chSumJtpt_jet80_keep[i]->SetMarkerStyle(24);
    hData_chSumJtpt_jet80_keep[i]->SetMarkerColor(kBlack);
    nData_chSumJtpt_jet80_keep[i]=hData_chSumJtpt_jet80_keep[i]->GetEntries();
    if (nData_chSumJtpt_jet80_keep[i]>0){
      if(nMC_chSumJtpt_jet80_keep[i]<=0){
        hData_chSumJtpt_jet80_keep[i]->Print("base");
        hData_chSumJtpt_jet80_keep[i]->SetTitle(" ");
        hData_chSumJtpt_jet80_keep[i]->SetXTitle(Form("chSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_chSumJtpt_jet80_keep[i]->DrawNormalized();
      } else {
      hData_chSumJtpt_jet80_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_chSumJtpt_jet80_keep[i] for i= "<<i<<" has "<<nData_chSumJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }   
        drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chSumJtpt_jet80_keep[0],"MC","pl");
    leg->AddEntry(hData_chSumJtpt_jet80_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchSumJtpt_jet80_keep[i]->SaveAs(Form("Plots/chSumJtpt_jet80_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * ceSumJtpt_jet80_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceSumJtpt_jet80_keep[i] = new TCanvas(Form("ceSumJtpt_jet80_keep_cent%d",i),"",800,600);
    ceSumJtpt_jet80_keep[i]->SetLogy();
    hMC_eSumJtpt_jet80_keep[i]->SetMarkerColor(kBlue+1);
    hMC_eSumJtpt_jet80_keep[i]->SetMarkerStyle(25);
    hMC_eSumJtpt_jet80_keep[i]->Print("base");
    hMC_eSumJtpt_jet80_keep[i]->SetTitle(" ");
    hMC_eSumJtpt_jet80_keep[i]->SetXTitle(Form("eSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));
    nMC_eSumJtpt_jet80_keep[i]=hMC_eSumJtpt_jet80_keep[i]->GetEntries();
    if (nMC_eSumJtpt_jet80_keep[i]>0){
       hMC_eSumJtpt_jet80_keep[i]->DrawNormalized();
    } else { cout<<"hMC_eSumJtpt_jet80_keep[i] for i= "<<i<<" has "<<nMC_eSumJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }

    hData_eSumJtpt_jet80_keep[i]->SetMarkerStyle(24);
    hData_eSumJtpt_jet80_keep[i]->SetMarkerColor(kBlack);
    nData_eSumJtpt_jet80_keep[i]=hData_eSumJtpt_jet80_keep[i]->GetEntries();
    if (nData_eSumJtpt_jet80_keep[i]>0){
      if(nMC_eSumJtpt_jet80_keep[i]<=0){
        hData_eSumJtpt_jet80_keep[i]->Print("base");
        hData_eSumJtpt_jet80_keep[i]->SetTitle(" ");
        hData_eSumJtpt_jet80_keep[i]->SetXTitle(Form("eSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_eSumJtpt_jet80_keep[i]->DrawNormalized();
      } else {
      hData_eSumJtpt_jet80_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_eSumJtpt_jet80_keep[i] for i= "<<i<<" has "<<nData_eSumJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }   
        drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eSumJtpt_jet80_keep[0],"MC","pl");
    leg->AddEntry(hData_eSumJtpt_jet80_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceSumJtpt_jet80_keep[i]->SaveAs(Form("Plots/eSumJtpt_jet80_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cphSumJtpt_jet80_keep[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphSumJtpt_jet80_keep[i] = new TCanvas(Form("cphSumJtpt_jet80_keep_cent%d",i),"",800,600);
    cphSumJtpt_jet80_keep[i]->SetLogy();
    hMC_phSumJtpt_jet80_keep[i]->SetMarkerColor(kGreen-3);
    hMC_phSumJtpt_jet80_keep[i]->SetMarkerStyle(25);
    hMC_phSumJtpt_jet80_keep[i]->Print("base");
    hMC_phSumJtpt_jet80_keep[i]->SetTitle(" ");
    hMC_phSumJtpt_jet80_keep[i]->SetXTitle(Form("phSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));
    nMC_phSumJtpt_jet80_keep[i]=hMC_phSumJtpt_jet80_keep[i]->GetEntries();
    if (nMC_phSumJtpt_jet80_keep[i]>0){
       hMC_phSumJtpt_jet80_keep[i]->DrawNormalized();
    } else { cout<<"hMC_phSumJtpt_jet80_keep[i] for i= "<<i<<" has "<<nMC_phSumJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }

    hData_phSumJtpt_jet80_keep[i]->SetMarkerStyle(24);
    hData_phSumJtpt_jet80_keep[i]->SetMarkerColor(kBlack);
    nData_phSumJtpt_jet80_keep[i]=hData_phSumJtpt_jet80_keep[i]->GetEntries();
    if (nData_phSumJtpt_jet80_keep[i]>0){
      if(nMC_phSumJtpt_jet80_keep[i]<=0){
        hData_phSumJtpt_jet80_keep[i]->Print("base");
        hData_phSumJtpt_jet80_keep[i]->SetTitle(" ");
        hData_phSumJtpt_jet80_keep[i]->SetXTitle(Form("phSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_phSumJtpt_jet80_keep[i]->DrawNormalized();
      } else {
      hData_phSumJtpt_jet80_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_phSumJtpt_jet80_keep[i] for i= "<<i<<" has "<<nData_phSumJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phSumJtpt_jet80_keep[0],"MC","pl");
    leg->AddEntry(hData_phSumJtpt_jet80_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphSumJtpt_jet80_keep[i]->SaveAs(Form("Plots/phSumJtpt_jet80_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cneSumJtpt_jet80_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneSumJtpt_jet80_keep[i] = new TCanvas(Form("cneSumJtpt_jet80_keep_cent%d",i),"",800,600);
    cneSumJtpt_jet80_keep[i]->SetLogy();
    hMC_neSumJtpt_jet80_keep[i]->SetMarkerColor(kMagenta+1);
    hMC_neSumJtpt_jet80_keep[i]->SetMarkerStyle(25);
    hMC_neSumJtpt_jet80_keep[i]->Print("base");
    hMC_neSumJtpt_jet80_keep[i]->SetTitle(" ");
    hMC_neSumJtpt_jet80_keep[i]->SetXTitle(Form("neSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));
    nMC_neSumJtpt_jet80_keep[i]=hMC_neSumJtpt_jet80_keep[i]->GetEntries();
    if (nMC_neSumJtpt_jet80_keep[i]>0){
       hMC_neSumJtpt_jet80_keep[i]->DrawNormalized();
    } else { cout<<"hMC_neSumJtpt_jet80_keep[i] for i= "<<i<<" has "<<nMC_neSumJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }

    hData_neSumJtpt_jet80_keep[i]->SetMarkerStyle(24);
    hData_neSumJtpt_jet80_keep[i]->SetMarkerColor(kBlack);
    nData_neSumJtpt_jet80_keep[i]=hData_neSumJtpt_jet80_keep[i]->GetEntries();
    if (nData_neSumJtpt_jet80_keep[i]>0){
      if(nMC_neSumJtpt_jet80_keep[i]<=0){
        hData_neSumJtpt_jet80_keep[i]->Print("base");
        hData_neSumJtpt_jet80_keep[i]->SetTitle(" ");
        hData_neSumJtpt_jet80_keep[i]->SetXTitle(Form("neSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_neSumJtpt_jet80_keep[i]->DrawNormalized();
      } else {
      hData_neSumJtpt_jet80_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_neSumJtpt_jet80_keep[i] for i= "<<i<<" has "<<nData_neSumJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neSumJtpt_jet80_keep[0],"MC","pl");
    leg->AddEntry(hData_neSumJtpt_jet80_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneSumJtpt_jet80_keep[i]->SaveAs(Form("Plots/neSumJtpt_jet80_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cmuSumJtpt_jet80_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuSumJtpt_jet80_keep[i] = new TCanvas(Form("cmuSumJtpt_jet80_keep_cent%d",i),"",800,600);
    cmuSumJtpt_jet80_keep[i]->SetLogy();
    hMC_muSumJtpt_jet80_keep[i]->SetMarkerColor(kCyan+1);
    hMC_muSumJtpt_jet80_keep[i]->SetMarkerStyle(25);
    hMC_muSumJtpt_jet80_keep[i]->Print("base");
    hMC_muSumJtpt_jet80_keep[i]->SetTitle(" ");
    hMC_muSumJtpt_jet80_keep[i]->SetXTitle(Form("muSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));
    nMC_muSumJtpt_jet80_keep[i]=hMC_muSumJtpt_jet80_keep[i]->GetEntries();
    if (nMC_muSumJtpt_jet80_keep[i]>0){
       hMC_muSumJtpt_jet80_keep[i]->DrawNormalized();
    } else { cout<<"hMC_muSumJtpt_jet80_keep[i] for i= "<<i<<" has "<<nMC_muSumJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }

    hData_muSumJtpt_jet80_keep[i]->SetMarkerStyle(24);
    hData_muSumJtpt_jet80_keep[i]->SetMarkerColor(kBlack);
    nData_muSumJtpt_jet80_keep[i]=hData_muSumJtpt_jet80_keep[i]->GetEntries();
    if (nData_muSumJtpt_jet80_keep[i]>0){
      if(nMC_muSumJtpt_jet80_keep[i]<=0){
        hData_muSumJtpt_jet80_keep[i]->Print("base");
        hData_muSumJtpt_jet80_keep[i]->SetTitle(" ");
        hData_muSumJtpt_jet80_keep[i]->SetXTitle(Form("muSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_muSumJtpt_jet80_keep[i]->DrawNormalized();
      } else {
      hData_muSumJtpt_jet80_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_muSumJtpt_jet80_keep[i] for i= "<<i<<" has "<<nData_muSumJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muSumJtpt_jet80_keep[0],"MC","pl");
    leg->AddEntry(hData_muSumJtpt_jet80_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuSumJtpt_jet80_keep[i]->SaveAs(Form("Plots/muSumJtpt_jet80_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cchMaxJtpt_jet80_rej[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchMaxJtpt_jet80_rej[i] = new TCanvas(Form("cchMaxJtpt_jet80_rej_cent%d",i),"",800,600);
    cchMaxJtpt_jet80_rej[i]->SetLogy();
    hMC_chMaxJtpt_jet80_rej[i]->SetMarkerColor(kRed);
    hMC_chMaxJtpt_jet80_rej[i]->SetMarkerStyle(25);
    hMC_chMaxJtpt_jet80_rej[i]->Print("base");
    hMC_chMaxJtpt_jet80_rej[i]->SetTitle(" ");
    hMC_chMaxJtpt_jet80_rej[i]->SetXTitle(Form("chMax/(ak%dPuPF jet p_{T}) jet80, fail CutA",radius));
    nMC_chMaxJtpt_jet80_rej[i]=hMC_chMaxJtpt_jet80_rej[i]->GetEntries();
    if (nMC_chMaxJtpt_jet80_rej[i]>0){
       hMC_chMaxJtpt_jet80_rej[i]->DrawNormalized();
    } else { cout<<"hMC_chMaxJtpt_jet80_rej[i] for i= "<<i<<" has "<<nMC_chMaxJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }

    hData_chMaxJtpt_jet80_rej[i]->SetMarkerStyle(24);
    hData_chMaxJtpt_jet80_rej[i]->SetMarkerColor(kBlack);
    nData_chMaxJtpt_jet80_rej[i]=hData_chMaxJtpt_jet80_rej[i]->GetEntries();
    if (nData_chMaxJtpt_jet80_rej[i]>0){
      if(nMC_chMaxJtpt_jet80_rej[i]<=0){
        hData_chMaxJtpt_jet80_rej[i]->Print("base");
        hData_chMaxJtpt_jet80_rej[i]->SetTitle(" ");
        hData_chMaxJtpt_jet80_rej[i]->SetXTitle(Form("chMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_chMaxJtpt_jet80_rej[i]->DrawNormalized();
      } else {
      hData_chMaxJtpt_jet80_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_chMaxJtpt_jet80_rej[i] for i= "<<i<<" has "<<nData_chMaxJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chMaxJtpt_jet80_rej[0],"MC","pl");
    leg->AddEntry(hData_chMaxJtpt_jet80_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchMaxJtpt_jet80_rej[i]->SaveAs(Form("Plots/chMaxJtpt_jet80_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  
  TCanvas * ceMaxJtpt_jet80_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceMaxJtpt_jet80_rej[i] = new TCanvas(Form("ceMaxJtpt_jet80_rej_cent%d",i),"",800,600);
    ceMaxJtpt_jet80_rej[i]->SetLogy();
    hMC_eMaxJtpt_jet80_rej[i]->SetMarkerColor(kBlue);
    hMC_eMaxJtpt_jet80_rej[i]->SetMarkerStyle(25);
    hMC_eMaxJtpt_jet80_rej[i]->Print("base");
    hMC_eMaxJtpt_jet80_rej[i]->SetTitle(" ");
    hMC_eMaxJtpt_jet80_rej[i]->SetXTitle(Form("eMax/(ak%dPuPF jet p_{T}) jet80, fail CutA",radius));
    nMC_eMaxJtpt_jet80_rej[i]=hMC_eMaxJtpt_jet80_rej[i]->GetEntries();
    if (nMC_eMaxJtpt_jet80_rej[i]>0){
       hMC_eMaxJtpt_jet80_rej[i]->DrawNormalized();
    } else { cout<<"hMC_eMaxJtpt_jet80_rej[i] for i= "<<i<<" has "<<nMC_eMaxJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }

    hData_eMaxJtpt_jet80_rej[i]->SetMarkerStyle(24);
    hData_eMaxJtpt_jet80_rej[i]->SetMarkerColor(kBlack);
    nData_eMaxJtpt_jet80_rej[i]=hData_eMaxJtpt_jet80_rej[i]->GetEntries();
    if (nData_eMaxJtpt_jet80_rej[i]>0){
      if(nMC_eMaxJtpt_jet80_rej[i]<=0){
        hData_eMaxJtpt_jet80_rej[i]->Print("base");
        hData_eMaxJtpt_jet80_rej[i]->SetTitle(" ");
        hData_eMaxJtpt_jet80_rej[i]->SetXTitle(Form("eMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_eMaxJtpt_jet80_rej[i]->DrawNormalized();
      } else {
      hData_eMaxJtpt_jet80_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_eMaxJtpt_jet80_rej[i] for i= "<<i<<" has "<<nData_eMaxJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eMaxJtpt_jet80_rej[0],"MC","pl");
    leg->AddEntry(hData_eMaxJtpt_jet80_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceMaxJtpt_jet80_rej[i]->SaveAs(Form("Plots/eMaxJtpt_jet80_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }

   TCanvas * cphMaxJtpt_jet80_rej[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphMaxJtpt_jet80_rej[i] = new TCanvas(Form("cphMaxJtpt_jet80_rej_cent%d",i),"",800,600);
    cphMaxJtpt_jet80_rej[i]->SetLogy();
    hMC_phMaxJtpt_jet80_rej[i]->SetMarkerColor(kGreen+2);
    hMC_phMaxJtpt_jet80_rej[i]->SetMarkerStyle(25);
    hMC_phMaxJtpt_jet80_rej[i]->Print("base");
    hMC_phMaxJtpt_jet80_rej[i]->SetTitle(" ");
    hMC_phMaxJtpt_jet80_rej[i]->SetXTitle(Form("phMax/(ak%dPuPF jet p_{T}) jet80, fail CutA",radius));
    nMC_phMaxJtpt_jet80_rej[i]=hMC_phMaxJtpt_jet80_rej[i]->GetEntries();
    if (nMC_phMaxJtpt_jet80_rej[i]>0){
       hMC_phMaxJtpt_jet80_rej[i]->DrawNormalized();
    } else { cout<<"hMC_phMaxJtpt_jet80_rej[i] for i= "<<i<<" has "<<nMC_phMaxJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }

    hData_phMaxJtpt_jet80_rej[i]->SetMarkerStyle(24);
    hData_phMaxJtpt_jet80_rej[i]->SetMarkerColor(kBlack);
    nData_phMaxJtpt_jet80_rej[i]=hData_phMaxJtpt_jet80_rej[i]->GetEntries();
    if (nData_phMaxJtpt_jet80_rej[i]>0){
      if(nMC_phMaxJtpt_jet80_rej[i]<=0){
        hData_phMaxJtpt_jet80_rej[i]->Print("base");
        hData_phMaxJtpt_jet80_rej[i]->SetTitle(" ");
        hData_phMaxJtpt_jet80_rej[i]->SetXTitle(Form("phMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_phMaxJtpt_jet80_rej[i]->DrawNormalized();
      } else {
      hData_phMaxJtpt_jet80_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_phMaxJtpt_jet80_rej[i] for i= "<<i<<" has "<<nData_phMaxJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phMaxJtpt_jet80_rej[0],"MC","pl");
    leg->AddEntry(hData_phMaxJtpt_jet80_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphMaxJtpt_jet80_rej[i]->SaveAs(Form("Plots/phMaxJtpt_jet80_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cneMaxJtpt_jet80_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneMaxJtpt_jet80_rej[i] = new TCanvas(Form("cneMaxJtpt_jet80_rej_cent%d",i),"",800,600);
    cneMaxJtpt_jet80_rej[i]->SetLogy();
    hMC_neMaxJtpt_jet80_rej[i]->SetMarkerColor(kMagenta);
    hMC_neMaxJtpt_jet80_rej[i]->SetMarkerStyle(25);
    hMC_neMaxJtpt_jet80_rej[i]->Print("base");
    hMC_neMaxJtpt_jet80_rej[i]->SetTitle(" ");
    hMC_neMaxJtpt_jet80_rej[i]->SetXTitle(Form("neMax/(ak%dPuPF jet p_{T}) jet80, fail CutA",radius));
    nMC_neMaxJtpt_jet80_rej[i]=hMC_neMaxJtpt_jet80_rej[i]->GetEntries();
    if (nMC_neMaxJtpt_jet80_rej[i]>0){
       hMC_neMaxJtpt_jet80_rej[i]->DrawNormalized();
    } else { cout<<"hMC_neMaxJtpt_jet80_rej[i] for i= "<<i<<" has "<<nMC_neMaxJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }

    hData_neMaxJtpt_jet80_rej[i]->SetMarkerStyle(24);
    hData_neMaxJtpt_jet80_rej[i]->SetMarkerColor(kBlack);
    nData_neMaxJtpt_jet80_rej[i]=hData_neMaxJtpt_jet80_rej[i]->GetEntries();
    if (nData_neMaxJtpt_jet80_rej[i]>0){
      if(nMC_neMaxJtpt_jet80_rej[i]<=0){
        hData_neMaxJtpt_jet80_rej[i]->Print("base");
        hData_neMaxJtpt_jet80_rej[i]->SetTitle(" ");
        hData_neMaxJtpt_jet80_rej[i]->SetXTitle(Form("neMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_neMaxJtpt_jet80_rej[i]->DrawNormalized();
      } else {
      hData_neMaxJtpt_jet80_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_neMaxJtpt_jet80_rej[i] for i= "<<i<<" has "<<nData_neMaxJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neMaxJtpt_jet80_rej[0],"MC","pl");
    leg->AddEntry(hData_neMaxJtpt_jet80_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneMaxJtpt_jet80_rej[i]->SaveAs(Form("Plots/neMaxJtpt_jet80_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cmuMaxJtpt_jet80_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuMaxJtpt_jet80_rej[i] = new TCanvas(Form("cmuMaxJtpt_jet80_rej_cent%d",i),"",800,600);
    cmuMaxJtpt_jet80_rej[i]->SetLogy();
    hMC_muMaxJtpt_jet80_rej[i]->SetMarkerColor(kCyan);
    hMC_muMaxJtpt_jet80_rej[i]->SetMarkerStyle(25);
    hMC_muMaxJtpt_jet80_rej[i]->Print("base");
    hMC_muMaxJtpt_jet80_rej[i]->SetTitle(" ");
    hMC_muMaxJtpt_jet80_rej[i]->SetXTitle(Form("muMax/(ak%dPuPF jet p_{T}) jet80, fail CutA",radius));
    nMC_muMaxJtpt_jet80_rej[i]=hMC_muMaxJtpt_jet80_rej[i]->GetEntries();
    if (nMC_muMaxJtpt_jet80_rej[i]>0){
       hMC_muMaxJtpt_jet80_rej[i]->DrawNormalized();
    } else { cout<<"hMC_muMaxJtpt_jet80_rej[i] for i= "<<i<<" has "<<nMC_muMaxJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }

    hData_muMaxJtpt_jet80_rej[i]->SetMarkerStyle(24);
    hData_muMaxJtpt_jet80_rej[i]->SetMarkerColor(kBlack);
    nData_muMaxJtpt_jet80_rej[i]=hData_muMaxJtpt_jet80_rej[i]->GetEntries();
    if (nData_muMaxJtpt_jet80_rej[i]>0){
      if(nMC_muMaxJtpt_jet80_rej[i]<=0){
        hData_muMaxJtpt_jet80_rej[i]->Print("base");
        hData_muMaxJtpt_jet80_rej[i]->SetTitle(" ");
        hData_muMaxJtpt_jet80_rej[i]->SetXTitle(Form("muMax/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_muMaxJtpt_jet80_rej[i]->DrawNormalized();
      } else {
      hData_muMaxJtpt_jet80_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_muMaxJtpt_jet80_rej[i] for i= "<<i<<" has "<<nData_muMaxJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; } 
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muMaxJtpt_jet80_rej[0],"MC","pl");
    leg->AddEntry(hData_muMaxJtpt_jet80_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuMaxJtpt_jet80_rej[i]->SaveAs(Form("Plots/muMaxJtpt_jet80_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }    
// draw some Sum variables
  TCanvas * cchSumJtpt_jet80_rej[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchSumJtpt_jet80_rej[i] = new TCanvas(Form("cchSumJtpt_jet80_rej_cent%d",i),"",800,600);
    cchSumJtpt_jet80_rej[i]->SetLogy();
    hMC_chSumJtpt_jet80_rej[i]->SetMarkerColor(kRed+1);
    hMC_chSumJtpt_jet80_rej[i]->SetMarkerStyle(25);
    hMC_chSumJtpt_jet80_rej[i]->Print("base");
    hMC_chSumJtpt_jet80_rej[i]->SetTitle(" ");
    hMC_chSumJtpt_jet80_rej[i]->SetXTitle(Form("chSum/(ak%dPuPF jet p_{T}) jet80, fail CutA",radius));
    nMC_chSumJtpt_jet80_rej[i]=hMC_chSumJtpt_jet80_rej[i]->GetEntries();
    if (nMC_chSumJtpt_jet80_rej[i]>0){
       hMC_chSumJtpt_jet80_rej[i]->DrawNormalized();
    } else { cout<<"hMC_chSumJtpt_jet80_rej[i] for i= "<<i<<" has "<<nMC_chSumJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }

    hData_chSumJtpt_jet80_rej[i]->SetMarkerStyle(24);
    hData_chSumJtpt_jet80_rej[i]->SetMarkerColor(kBlack);
    nData_chSumJtpt_jet80_rej[i]=hData_chSumJtpt_jet80_rej[i]->GetEntries();
    if (nData_chSumJtpt_jet80_rej[i]>0){
      if(nMC_chSumJtpt_jet80_rej[i]<=0){
        hData_chSumJtpt_jet80_rej[i]->Print("base");
        hData_chSumJtpt_jet80_rej[i]->SetTitle(" ");
        hData_chSumJtpt_jet80_rej[i]->SetXTitle(Form("chSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_chSumJtpt_jet80_rej[i]->DrawNormalized();
      } else {
      hData_chSumJtpt_jet80_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_chSumJtpt_jet80_rej[i] for i= "<<i<<" has "<<nData_chSumJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chSumJtpt_jet80_rej[0],"MC","pl");
    leg->AddEntry(hData_chSumJtpt_jet80_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchSumJtpt_jet80_rej[i]->SaveAs(Form("Plots/chSumJtpt_jet80_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * ceSumJtpt_jet80_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceSumJtpt_jet80_rej[i] = new TCanvas(Form("ceSumJtpt_jet80_rej_cent%d",i),"",800,600);
    ceSumJtpt_jet80_rej[i]->SetLogy();
    hMC_eSumJtpt_jet80_rej[i]->SetMarkerColor(kBlue+1);
    hMC_eSumJtpt_jet80_rej[i]->SetMarkerStyle(25);
    hMC_eSumJtpt_jet80_rej[i]->Print("base");
    hMC_eSumJtpt_jet80_rej[i]->SetTitle(" ");
    hMC_eSumJtpt_jet80_rej[i]->SetXTitle(Form("eSum/(ak%dPuPF jet p_{T}) jet80, fail CutA",radius));
    nMC_eSumJtpt_jet80_rej[i]=hMC_eSumJtpt_jet80_rej[i]->GetEntries();
    if (nMC_eSumJtpt_jet80_rej[i]>0){
       hMC_eSumJtpt_jet80_rej[i]->DrawNormalized();
    } else { cout<<"hMC_eSumJtpt_jet80_rej[i] for i= "<<i<<" has "<<nMC_eSumJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }

    hData_eSumJtpt_jet80_rej[i]->SetMarkerStyle(24);
    hData_eSumJtpt_jet80_rej[i]->SetMarkerColor(kBlack);
    nData_eSumJtpt_jet80_rej[i]=hData_eSumJtpt_jet80_rej[i]->GetEntries();
    if (nData_eSumJtpt_jet80_rej[i]>0){
      if(nMC_eSumJtpt_jet80_rej[i]<=0){
        hData_eSumJtpt_jet80_rej[i]->Print("base");
        hData_eSumJtpt_jet80_rej[i]->SetTitle(" ");
        hData_eSumJtpt_jet80_rej[i]->SetXTitle(Form("eSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_eSumJtpt_jet80_rej[i]->DrawNormalized();
      } else {
      hData_eSumJtpt_jet80_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_eSumJtpt_jet80_rej[i] for i= "<<i<<" has "<<nData_eSumJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eSumJtpt_jet80_rej[0],"MC","pl");
    leg->AddEntry(hData_eSumJtpt_jet80_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceSumJtpt_jet80_rej[i]->SaveAs(Form("Plots/eSumJtpt_jet80_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cphSumJtpt_jet80_rej[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphSumJtpt_jet80_rej[i] = new TCanvas(Form("cphSumJtpt_jet80_rej_cent%d",i),"",800,600);
    cphSumJtpt_jet80_rej[i]->SetLogy();
    hMC_phSumJtpt_jet80_rej[i]->SetMarkerColor(kGreen-3);
    hMC_phSumJtpt_jet80_rej[i]->SetMarkerStyle(25);
    hMC_phSumJtpt_jet80_rej[i]->Print("base");
    hMC_phSumJtpt_jet80_rej[i]->SetTitle(" ");
    hMC_phSumJtpt_jet80_rej[i]->SetXTitle(Form("phSum/(ak%dPuPF jet p_{T}) jet80, fail CutA",radius));
    nMC_phSumJtpt_jet80_rej[i]=hMC_phSumJtpt_jet80_rej[i]->GetEntries();
    if (nMC_phSumJtpt_jet80_rej[i]>0){
       hMC_phSumJtpt_jet80_rej[i]->DrawNormalized();
    } else { cout<<"hMC_phSumJtpt_jet80_rej[i] for i= "<<i<<" has "<<nMC_phSumJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }

    hData_phSumJtpt_jet80_rej[i]->SetMarkerStyle(24);
    hData_phSumJtpt_jet80_rej[i]->SetMarkerColor(kBlack);
    nData_phSumJtpt_jet80_rej[i]=hData_phSumJtpt_jet80_rej[i]->GetEntries();
    if (nData_phSumJtpt_jet80_rej[i]>0){
      if(nMC_phSumJtpt_jet80_rej[i]<=0){
        hData_phSumJtpt_jet80_rej[i]->Print("base");
        hData_phSumJtpt_jet80_rej[i]->SetTitle(" ");
        hData_phSumJtpt_jet80_rej[i]->SetXTitle(Form("phSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_phSumJtpt_jet80_rej[i]->DrawNormalized();
      } else {
      hData_phSumJtpt_jet80_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_phSumJtpt_jet80_rej[i] for i= "<<i<<" has "<<nData_phSumJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phSumJtpt_jet80_rej[0],"MC","pl");
    leg->AddEntry(hData_phSumJtpt_jet80_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphSumJtpt_jet80_rej[i]->SaveAs(Form("Plots/phSumJtpt_jet80_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
  TCanvas * cneSumJtpt_jet80_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneSumJtpt_jet80_rej[i] = new TCanvas(Form("cneSumJtpt_jet80_rej_cent%d",i),"",800,600);
    cneSumJtpt_jet80_rej[i]->SetLogy();
    hMC_neSumJtpt_jet80_rej[i]->SetMarkerColor(kMagenta+1);
    hMC_neSumJtpt_jet80_rej[i]->SetMarkerStyle(25);
    hMC_neSumJtpt_jet80_rej[i]->Print("base");
    hMC_neSumJtpt_jet80_rej[i]->SetTitle(" ");
    hMC_neSumJtpt_jet80_rej[i]->SetXTitle(Form("neSum/(ak%dPuPF jet p_{T}) jet80, fail CutA",radius));
    nMC_neSumJtpt_jet80_rej[i]=hMC_neSumJtpt_jet80_rej[i]->GetEntries();
    if (nMC_neSumJtpt_jet80_rej[i]>0){
       hMC_neSumJtpt_jet80_rej[i]->DrawNormalized();
    } else { cout<<"hMC_neSumJtpt_jet80_rej[i] for i= "<<i<<" has "<<nMC_neSumJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }

    hData_neSumJtpt_jet80_rej[i]->SetMarkerStyle(24);
    hData_neSumJtpt_jet80_rej[i]->SetMarkerColor(kBlack);
    nData_neSumJtpt_jet80_rej[i]=hData_neSumJtpt_jet80_rej[i]->GetEntries();
    if (nData_neSumJtpt_jet80_rej[i]>0){
      if(nMC_neSumJtpt_jet80_rej[i]<=0){
        hData_neSumJtpt_jet80_rej[i]->Print("base");
        hData_neSumJtpt_jet80_rej[i]->SetTitle(" ");
        hData_neSumJtpt_jet80_rej[i]->SetXTitle(Form("neSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_neSumJtpt_jet80_rej[i]->DrawNormalized();
      } else {
      hData_neSumJtpt_jet80_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_neSumJtpt_jet80_rej[i] for i= "<<i<<" has "<<nData_neSumJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neSumJtpt_jet80_rej[0],"MC","pl");
    leg->AddEntry(hData_neSumJtpt_jet80_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneSumJtpt_jet80_rej[i]->SaveAs(Form("Plots/neSumJtpt_jet80_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
    TCanvas * cmuSumJtpt_jet80_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuSumJtpt_jet80_rej[i] = new TCanvas(Form("cmuSumJtpt_jet80_rej_cent%d",i),"",800,600);
    cmuSumJtpt_jet80_rej[i]->SetLogy();
    hMC_muSumJtpt_jet80_rej[i]->SetMarkerColor(kCyan+1);
    hMC_muSumJtpt_jet80_rej[i]->SetMarkerStyle(25);
    hMC_muSumJtpt_jet80_rej[i]->Print("base");
    hMC_muSumJtpt_jet80_rej[i]->SetTitle(" ");
    hMC_muSumJtpt_jet80_rej[i]->SetXTitle(Form("muSum/(ak%dPuPF jet p_{T}) jet80, fail CutA",radius));
    nMC_muSumJtpt_jet80_rej[i]=hMC_muSumJtpt_jet80_rej[i]->GetEntries();
    if (nMC_muSumJtpt_jet80_rej[i]>0){
       hMC_muSumJtpt_jet80_rej[i]->DrawNormalized();
    } else { cout<<"hMC_muSumJtpt_jet80_rej[i] for i= "<<i<<" has "<<nMC_muSumJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }

    hData_muSumJtpt_jet80_rej[i]->SetMarkerStyle(24);
    hData_muSumJtpt_jet80_rej[i]->SetMarkerColor(kBlack);
    nData_muSumJtpt_jet80_rej[i]=hData_muSumJtpt_jet80_rej[i]->GetEntries();
    if (nData_muSumJtpt_jet80_rej[i]>0){
      if(nMC_muSumJtpt_jet80_rej[i]<=0){
        hData_muSumJtpt_jet80_rej[i]->Print("base");
        hData_muSumJtpt_jet80_rej[i]->SetTitle(" ");
        hData_muSumJtpt_jet80_rej[i]->SetXTitle(Form("muSum/(ak%dPuPF jet p_{T}) jet80, pass CutA",radius));      
        hData_muSumJtpt_jet80_rej[i]->DrawNormalized();
      } else {
      hData_muSumJtpt_jet80_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_muSumJtpt_jet80_rej[i] for i= "<<i<<" has "<<nData_muSumJtpt_jet80_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muSumJtpt_jet80_rej[0],"MC","pl");
    leg->AddEntry(hData_muSumJtpt_jet80_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuSumJtpt_jet80_rej[i]->SaveAs(Form("Plots/muSumJtpt_jet80_rej_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }    
  TCanvas * ctrkMaxJtpt_jet55_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    ctrkMaxJtpt_jet55_keep[i] = new TCanvas(Form("ctrkMaxJtpt_jet55_keep_cent%d",i),"",800,600);
    ctrkMaxJtpt_jet55_keep[i]->SetLogy();
    hMC_trkMaxJtpt_jet55_keep[i]->SetMarkerColor(kRed);
    hMC_trkMaxJtpt_jet55_keep[i]->SetMarkerStyle(25);
    hMC_trkMaxJtpt_jet55_keep[i]->Print("base");
    hMC_trkMaxJtpt_jet55_keep[i]->SetTitle(" ");
    hMC_trkMaxJtpt_jet55_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet55, pass CutA ",radius));
    nMC_trkMaxJtpt_jet55_keep[i]=hMC_trkMaxJtpt_jet55_keep[i]->GetEntries();
    if (nMC_trkMaxJtpt_jet55_keep[i]>0){
       hMC_trkMaxJtpt_jet55_keep[i]->DrawNormalized();
    } else { cout<<"hMC_trkMaxJtpt_jet55_keep[i] for i= "<<i<<" has "<<nMC_trkMaxJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }

    hData_trkMaxJtpt_jet55_keep[i]->SetMarkerStyle(24);
    hData_trkMaxJtpt_jet55_keep[i]->SetMarkerColor(kBlack);
    nData_trkMaxJtpt_jet55_keep[i]=hData_trkMaxJtpt_jet55_keep[i]->GetEntries();
    if (nData_trkMaxJtpt_jet55_keep[i]>0){
      if(nMC_trkMaxJtpt_jet55_keep[i]<=0){
        hData_trkMaxJtpt_jet55_keep[i]->Print("base");
        hData_trkMaxJtpt_jet55_keep[i]->SetTitle(" ");
        hData_trkMaxJtpt_jet55_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet55, pass CutA ",radius));      
        hData_trkMaxJtpt_jet55_keep[i]->DrawNormalized();
      } else {
      hData_trkMaxJtpt_jet55_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_trkMaxJtpt_jet55_keep[i] for i= "<<i<<" has "<<nData_trkMaxJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }      
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_trkMaxJtpt_jet55_keep[0],"MC","pl");
    leg->AddEntry(hData_trkMaxJtpt_jet55_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ctrkMaxJtpt_jet55_keep[i]->SaveAs(Form("Plots/trkMaxJtpt_jet55_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
//     TCanvas * ctrkSumJtpt_jet55_keep[nbins_cent];
//   
//   for(int i = 0 ; i < nbins_cent ; ++i){
// 
//     ctrkSumJtpt_jet55_keep[i] = new TCanvas(Form("ctrkSumJtpt_jet55_keep_cent%d",i),"",800,600);
//     ctrkSumJtpt_jet55_keep[i]->SetLogy();
//     hMC_trkSumJtpt_jet55_keep[i]->SetMarkerColor(kRed+1);
//     hMC_trkSumJtpt_jet55_keep[i]->SetMarkerStyle(25);
//     hMC_trkSumJtpt_jet55_keep[i]->Print("base");
//     hMC_trkSumJtpt_jet55_keep[i]->SetTitle(" ");
//     hMC_trkSumJtpt_jet55_keep[i]->SetXTitle(Form("trkSum/(ak%dPuPF jet p_{T}) jet55, pass CutA ",radius));
//     nMC_trkSumJtpt_jet55_keep[i]=hMC_trkSumJtpt_jet55_keep[i]->GetEntries();
//     if (nMC_trkSumJtpt_jet55_keep[i]>0){
//        hMC_trkSumJtpt_jet55_keep[i]->DrawNormalized();
//     } else { cout<<"hMC_trkSumJtpt_jet55_keep[i] for i= "<<i<<" has "<<nMC_trkSumJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }
// 
//     hData_trkSumJtpt_jet55_keep[i]->SetMarkerStyle(24);
//     hData_trkSumJtpt_jet55_keep[i]->SetMarkerColor(kBlack);
//     nData_trkSumJtpt_jet55_keep[i]=hData_trkSumJtpt_jet55_keep[i]->GetEntries();
//     if (nData_trkSumJtpt_jet55_keep[i]>0){
//       if(nMC_trkSumJtpt_jet55_keep[i]<=0){
//         hData_trkSumJtpt_jet55_keep[i]->Print("base");
//         hData_trkSumJtpt_jet55_keep[i]->SetTitle(" ");
//         hData_trkSumJtpt_jet55_keep[i]->SetXTitle(Form("trkSum/(ak%dPuPF jet p_{T}) jet55, pass CutA ",radius));      
//         hData_trkSumJtpt_jet55_keep[i]->DrawNormalized();
//       } else {
//       hData_trkSumJtpt_jet55_keep[i]->DrawNormalized("same");
//       }
//     } else { cout<<"hData_trkSumJtpt_jet55_keep[i] for i= "<<i<<" has "<<nData_trkSumJtpt_jet55_keep[i]<<" entries and is not drawn"<<endl; }   
//         drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);
// 
//     TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
//     leg->AddEntry(hMC_trkSumJtpt_jet55_keep[0],"MC","pl");
//     leg->AddEntry(hData_trkSumJtpt_jet55_keep[0],"Data","pl");
//     leg->SetTextSize(0.04);
//     leg->Draw();
//     
//     ctrkSumJtpt_jet55_keep[i]->SaveAs(Form("Plots/trkSumJtpt_jet55_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");
// 
//   }
  TCanvas * ctrkMaxJtpt_jet65_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    ctrkMaxJtpt_jet65_keep[i] = new TCanvas(Form("ctrkMaxJtpt_jet65_keep_cent%d",i),"",800,600);
    ctrkMaxJtpt_jet65_keep[i]->SetLogy();
    hMC_trkMaxJtpt_jet65_keep[i]->SetMarkerColor(kRed);
    hMC_trkMaxJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_trkMaxJtpt_jet65_keep[i]->Print("base");
    hMC_trkMaxJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_trkMaxJtpt_jet65_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet65, pass CutA ",radius));
    nMC_trkMaxJtpt_jet65_keep[i]=hMC_trkMaxJtpt_jet65_keep[i]->GetEntries();
    if (nMC_trkMaxJtpt_jet65_keep[i]>0){
       hMC_trkMaxJtpt_jet65_keep[i]->DrawNormalized();
    } else { cout<<"hMC_trkMaxJtpt_jet65_keep[i] for i= "<<i<<" has "<<nMC_trkMaxJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }

    hData_trkMaxJtpt_jet65_keep[i]->SetMarkerStyle(24);
    hData_trkMaxJtpt_jet65_keep[i]->SetMarkerColor(kBlack);
    nData_trkMaxJtpt_jet65_keep[i]=hData_trkMaxJtpt_jet65_keep[i]->GetEntries();
    if (nData_trkMaxJtpt_jet65_keep[i]>0){
      if(nMC_trkMaxJtpt_jet65_keep[i]<=0){
        hData_trkMaxJtpt_jet65_keep[i]->Print("base");
        hData_trkMaxJtpt_jet65_keep[i]->SetTitle(" ");
        hData_trkMaxJtpt_jet65_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet65, pass CutA ",radius));      
        hData_trkMaxJtpt_jet65_keep[i]->DrawNormalized();
      } else {
      hData_trkMaxJtpt_jet65_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_trkMaxJtpt_jet65_keep[i] for i= "<<i<<" has "<<nData_trkMaxJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }      
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_trkMaxJtpt_jet65_keep[0],"MC","pl");
    leg->AddEntry(hData_trkMaxJtpt_jet65_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ctrkMaxJtpt_jet65_keep[i]->SaveAs(Form("Plots/trkMaxJtpt_jet65_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
//     TCanvas * ctrkSumJtpt_jet65_keep[nbins_cent];
//   
//   for(int i = 0 ; i < nbins_cent ; ++i){
// 
//     ctrkSumJtpt_jet65_keep[i] = new TCanvas(Form("ctrkSumJtpt_jet65_keep_cent%d",i),"",800,600);
//     ctrkSumJtpt_jet65_keep[i]->SetLogy();
//     hMC_trkSumJtpt_jet65_keep[i]->SetMarkerColor(kRed+1);
//     hMC_trkSumJtpt_jet65_keep[i]->SetMarkerStyle(25);
//     hMC_trkSumJtpt_jet65_keep[i]->Print("base");
//     hMC_trkSumJtpt_jet65_keep[i]->SetTitle(" ");
//     hMC_trkSumJtpt_jet65_keep[i]->SetXTitle(Form("trkSum/(ak%dPuPF jet p_{T}) jet65, pass CutA ",radius));
//     nMC_trkSumJtpt_jet65_keep[i]=hMC_trkSumJtpt_jet65_keep[i]->GetEntries();
//     if (nMC_trkSumJtpt_jet65_keep[i]>0){
//        hMC_trkSumJtpt_jet65_keep[i]->DrawNormalized();
//     } else { cout<<"hMC_trkSumJtpt_jet65_keep[i] for i= "<<i<<" has "<<nMC_trkSumJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }
// 
//     hData_trkSumJtpt_jet65_keep[i]->SetMarkerStyle(24);
//     hData_trkSumJtpt_jet65_keep[i]->SetMarkerColor(kBlack);
//     nData_trkSumJtpt_jet65_keep[i]=hData_trkSumJtpt_jet65_keep[i]->GetEntries();
//     if (nData_trkSumJtpt_jet65_keep[i]>0){
//       if(nMC_trkSumJtpt_jet65_keep[i]<=0){
//         hData_trkSumJtpt_jet65_keep[i]->Print("base");
//         hData_trkSumJtpt_jet65_keep[i]->SetTitle(" ");
//         hData_trkSumJtpt_jet65_keep[i]->SetXTitle(Form("trkSum/(ak%dPuPF jet p_{T}) jet65, pass CutA ",radius));      
//         hData_trkSumJtpt_jet65_keep[i]->DrawNormalized();
//       } else {
//       hData_trkSumJtpt_jet65_keep[i]->DrawNormalized("same");
//       }
//     } else { cout<<"hData_trkSumJtpt_jet65_keep[i] for i= "<<i<<" has "<<nData_trkSumJtpt_jet65_keep[i]<<" entries and is not drawn"<<endl; }   
//         drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);
// 
//     TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
//     leg->AddEntry(hMC_trkSumJtpt_jet65_keep[0],"MC","pl");
//     leg->AddEntry(hData_trkSumJtpt_jet65_keep[0],"Data","pl");
//     leg->SetTextSize(0.04);
//     leg->Draw();
//     
//     ctrkSumJtpt_jet65_keep[i]->SaveAs(Form("Plots/trkSumJtpt_jet65_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");
// 
//   }
  TCanvas * ctrkMaxJtpt_80_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    ctrkMaxJtpt_80_keep[i] = new TCanvas(Form("ctrkMaxJtpt_80_keep_cent%d",i),"",800,600);
    ctrkMaxJtpt_80_keep[i]->SetLogy();
    hMC_trkMaxJtpt_jet80_keep[i]->SetMarkerColor(kRed);
    hMC_trkMaxJtpt_jet80_keep[i]->SetMarkerStyle(25);
    hMC_trkMaxJtpt_jet80_keep[i]->Print("base");
    hMC_trkMaxJtpt_jet80_keep[i]->SetTitle(" ");
    hMC_trkMaxJtpt_jet80_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) 80, pass CutA ",radius));
    nMC_trkMaxJtpt_jet80_keep[i]=hMC_trkMaxJtpt_jet80_keep[i]->GetEntries();
    if (nMC_trkMaxJtpt_jet80_keep[i]>0){
       hMC_trkMaxJtpt_jet80_keep[i]->DrawNormalized();
    } else { cout<<"hMC_trkMaxJtpt_jet80_keep[i] for i= "<<i<<" has "<<nMC_trkMaxJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }

    hData_trkMaxJtpt_jet80_keep[i]->SetMarkerStyle(24);
    hData_trkMaxJtpt_jet80_keep[i]->SetMarkerColor(kBlack);
    nData_trkMaxJtpt_jet80_keep[i]=hData_trkMaxJtpt_jet80_keep[i]->GetEntries();
    if (nData_trkMaxJtpt_jet80_keep[i]>0){
      if(nMC_trkMaxJtpt_jet80_keep[i]<=0){
        hData_trkMaxJtpt_jet80_keep[i]->Print("base");
        hData_trkMaxJtpt_jet80_keep[i]->SetTitle(" ");
        hData_trkMaxJtpt_jet80_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) 80, pass CutA ",radius));      
        hData_trkMaxJtpt_jet80_keep[i]->DrawNormalized();
      } else {
      hData_trkMaxJtpt_jet80_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_trkMaxJtpt_jet80_keep[i] for i= "<<i<<" has "<<nData_trkMaxJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }      
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_trkMaxJtpt_jet80_keep[0],"MC","pl");
    leg->AddEntry(hData_trkMaxJtpt_jet80_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ctrkMaxJtpt_80_keep[i]->SaveAs(Form("Plots/trkMaxJtpt_80_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");

  }
//     TCanvas * ctrkSumJtpt_80_keep[nbins_cent];
//   
//   for(int i = 0 ; i < nbins_cent ; ++i){
// 
//     ctrkSumJtpt_80_keep[i] = new TCanvas(Form("ctrkSumJtpt_80_keep_cent%d",i),"",800,600);
//     ctrkSumJtpt_80_keep[i]->SetLogy();
//     hMC_trkSumJtpt_jet80_keep[i]->SetMarkerColor(kRed+1);
//     hMC_trkSumJtpt_jet80_keep[i]->SetMarkerStyle(25);
//     hMC_trkSumJtpt_jet80_keep[i]->Print("base");
//     hMC_trkSumJtpt_jet80_keep[i]->SetTitle(" ");
//     hMC_trkSumJtpt_jet80_keep[i]->SetXTitle(Form("trkSum/(ak%dPuPF jet p_{T}) 80, pass CutA ",radius));
//     nMC_trkSumJtpt_jet80_keep[i]=hMC_trkSumJtpt_jet80_keep[i]->GetEntries();
//     if (nMC_trkSumJtpt_jet80_keep[i]>0){
//        hMC_trkSumJtpt_jet80_keep[i]->DrawNormalized();
//     } else { cout<<"hMC_trkSumJtpt_jet80_keep[i] for i= "<<i<<" has "<<nMC_trkSumJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }
// 
//     hData_trkSumJtpt_jet80_keep[i]->SetMarkerStyle(24);
//     hData_trkSumJtpt_jet80_keep[i]->SetMarkerColor(kBlack);
//     nData_trkSumJtpt_jet80_keep[i]=hData_trkSumJtpt_jet80_keep[i]->GetEntries();
//     if (nData_trkSumJtpt_jet80_keep[i]>0){
//       if(nMC_trkSumJtpt_jet80_keep[i]<=0){
//         hData_trkSumJtpt_jet80_keep[i]->Print("base");
//         hData_trkSumJtpt_jet80_keep[i]->SetTitle(" ");
//         hData_trkSumJtpt_jet80_keep[i]->SetXTitle(Form("trkSum/(ak%dPuPF jet p_{T}) 80, pass CutA ",radius));      
//         hData_trkSumJtpt_jet80_keep[i]->DrawNormalized();
//       } else {
//       hData_trkSumJtpt_jet80_keep[i]->DrawNormalized("same");
//       }
//     } else { cout<<"hData_trkSumJtpt_jet80_keep[i] for i= "<<i<<" has "<<nData_trkSumJtpt_jet80_keep[i]<<" entries and is not drawn"<<endl; }   
//         drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);
// 
//     TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
//     leg->AddEntry(hMC_trkSumJtpt_jet80_keep[0],"MC","pl");
//     leg->AddEntry(hData_trkSumJtpt_jet80_keep[0],"Data","pl");
//     leg->SetTextSize(0.04);
//     leg->Draw();
//     
//     ctrkSumJtpt_80_keep[i]->SaveAs(Form("Plots/trkSumJtpt_80_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");
// 
//   } 
//   TCanvas * ctrkMaxJtpt_Matched_keep[nbins_cent];
//   
//   for(int i = 0 ; i < nbins_cent ; ++i){
// 
//     ctrkMaxJtpt_Matched_keep[i] = new TCanvas(Form("ctrkMaxJtpt_Matched_keep_cent%d",i),"",800,600);
//     ctrkMaxJtpt_Matched_keep[i]->SetLogy();
//     hMC_trkMaxJtpt_Matched_keep[i]->SetMarkerColor(kRed);
//     hMC_trkMaxJtpt_Matched_keep[i]->SetMarkerStyle(25);
//     hMC_trkMaxJtpt_Matched_keep[i]->Print("base");
//     hMC_trkMaxJtpt_Matched_keep[i]->SetTitle(" ");
//     hMC_trkMaxJtpt_Matched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet55||jet65||jet80, pass CutA ",radius));
//     nMC_trkMaxJtpt_Matched_keep[i]=hMC_trkMaxJtpt_Matched_keep[i]->GetEntries();
//     if (nMC_trkMaxJtpt_Matched_keep[i]>0){
//        hMC_trkMaxJtpt_Matched_keep[i]->DrawNormalized();
//     } else { cout<<"hMC_trkMaxJtpt_Matched_keep[i] for i= "<<i<<" has "<<nMC_trkMaxJtpt_Matched_keep[i]<<" entries and is not drawn"<<endl; }
// 
//     hData_trkMaxJtpt_Matched_keep[i]->SetMarkerStyle(24);
//     hData_trkMaxJtpt_Matched_keep[i]->SetMarkerColor(kBlack);
//     nData_trkMaxJtpt_Matched_keep[i]=hData_trkMaxJtpt_Matched_keep[i]->GetEntries();
//     if (nData_trkMaxJtpt_Matched_keep[i]>0){
//       if(nMC_trkMaxJtpt_Matched_keep[i]<=0){
//         hData_trkMaxJtpt_Matched_keep[i]->Print("base");
//         hData_trkMaxJtpt_Matched_keep[i]->SetTitle(" ");
//         hData_trkMaxJtpt_Matched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet55||jet65||jet80, matched pass CutA ",radius));      
//         hData_trkMaxJtpt_Matched_keep[i]->DrawNormalized();
//       } else {
//       hData_trkMaxJtpt_Matched_keep[i]->DrawNormalized("same");
//       }
//     } else { cout<<"hData_trkMaxJtpt_Matched_keep[i] for i= "<<i<<" has "<<nData_trkMaxJtpt_Matched_keep[i]<<" entries and is not drawn"<<endl; }      
//     drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);
// 
//     TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
//     leg->AddEntry(hMC_trkMaxJtpt_Matched_keep[0],"MC","pl");
//     leg->AddEntry(hData_trkMaxJtpt_Matched_keep[0],"Data","pl");
//     leg->SetTextSize(0.04);
//     leg->Draw();
//     
//     ctrkMaxJtpt_Matched_keep[i]->SaveAs(Form("Plots/trkMaxJtpt_Matched_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");
// 
//   }
// 
//   TCanvas * ctrkMaxJtpt_jet55_Matched_keep[nbins_cent];
//   
//   for(int i = 0 ; i < nbins_cent ; ++i){
// 
//     ctrkMaxJtpt_jet55_Matched_keep[i] = new TCanvas(Form("ctrkMaxJtpt_jet55_Matched_keep_cent%d",i),"",800,600);
//     ctrkMaxJtpt_jet55_Matched_keep[i]->SetLogy();
//     hMC_trkMaxJtpt_jet55_Matched_keep[i]->SetMarkerColor(kRed);
//     hMC_trkMaxJtpt_jet55_Matched_keep[i]->SetMarkerStyle(25);
//     hMC_trkMaxJtpt_jet55_Matched_keep[i]->Print("base");
//     hMC_trkMaxJtpt_jet55_Matched_keep[i]->SetTitle(" ");
//     hMC_trkMaxJtpt_jet55_Matched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet55, matched pass CutA ",radius));
//     nMC_trkMaxJtpt_jet55_Matched_keep[i]=hMC_trkMaxJtpt_jet55_Matched_keep[i]->GetEntries();
//     if (nMC_trkMaxJtpt_jet55_Matched_keep[i]>0){
//        hMC_trkMaxJtpt_jet55_Matched_keep[i]->DrawNormalized();
//     } else { cout<<"hMC_trkMaxJtpt_jet55_Matched_keep[i] for i= "<<i<<" has "<<nMC_trkMaxJtpt_jet55_Matched_keep[i]<<" entries and is not drawn"<<endl; }
// 
//     hData_trkMaxJtpt_jet55_Matched_keep[i]->SetMarkerStyle(24);
//     hData_trkMaxJtpt_jet55_Matched_keep[i]->SetMarkerColor(kBlack);
//     nData_trkMaxJtpt_jet55_Matched_keep[i]=hData_trkMaxJtpt_jet55_Matched_keep[i]->GetEntries();
//     if (nData_trkMaxJtpt_jet55_Matched_keep[i]>0){
//       if(nMC_trkMaxJtpt_jet55_Matched_keep[i]<=0){
//         hData_trkMaxJtpt_jet55_Matched_keep[i]->Print("base");
//         hData_trkMaxJtpt_jet55_Matched_keep[i]->SetTitle(" ");
//         hData_trkMaxJtpt_jet55_Matched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet55, matched pass CutA ",radius));      
//         hData_trkMaxJtpt_jet55_Matched_keep[i]->DrawNormalized();
//       } else {
//       hData_trkMaxJtpt_jet55_Matched_keep[i]->DrawNormalized("same");
//       }
//     } else { cout<<"hData_trkMaxJtpt_jet55_Matched_keep[i] for i= "<<i<<" has "<<nData_trkMaxJtpt_jet55_Matched_keep[i]<<" entries and is not drawn"<<endl; }      
//     drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);
// 
//     TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
//     leg->AddEntry(hMC_trkMaxJtpt_jet55_Matched_keep[0],"MC","pl");
//     leg->AddEntry(hData_trkMaxJtpt_jet55_Matched_keep[0],"Data","pl");
//     leg->SetTextSize(0.04);
//     leg->Draw();
//     
//     ctrkMaxJtpt_jet55_Matched_keep[i]->SaveAs(Form("Plots/trkMaxJtpt_jet55_Matched_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");
// 
//   }
//   TCanvas * ctrkMaxJtpt_jet65_Matched_keep[nbins_cent];
//   
//   for(int i = 0 ; i < nbins_cent ; ++i){
// 
//     ctrkMaxJtpt_jet65_Matched_keep[i] = new TCanvas(Form("ctrkMaxJtpt_jet65_Matched_keep_cent%d",i),"",800,600);
//     ctrkMaxJtpt_jet65_Matched_keep[i]->SetLogy();
//     hMC_trkMaxJtpt_jet65_Matched_keep[i]->SetMarkerColor(kRed);
//     hMC_trkMaxJtpt_jet65_Matched_keep[i]->SetMarkerStyle(25);
//     hMC_trkMaxJtpt_jet65_Matched_keep[i]->Print("base");
//     hMC_trkMaxJtpt_jet65_Matched_keep[i]->SetTitle(" ");
//     hMC_trkMaxJtpt_jet65_Matched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet65, matched pass CutA ",radius));
//     nMC_trkMaxJtpt_jet65_Matched_keep[i]=hMC_trkMaxJtpt_jet65_Matched_keep[i]->GetEntries();
//     if (nMC_trkMaxJtpt_jet65_Matched_keep[i]>0){
//        hMC_trkMaxJtpt_jet65_Matched_keep[i]->DrawNormalized();
//     } else { cout<<"hMC_trkMaxJtpt_jet65_Matched_keep[i] for i= "<<i<<" has "<<nMC_trkMaxJtpt_jet65_Matched_keep[i]<<" entries and is not drawn"<<endl; }
// 
//     hData_trkMaxJtpt_jet65_Matched_keep[i]->SetMarkerStyle(24);
//     hData_trkMaxJtpt_jet65_Matched_keep[i]->SetMarkerColor(kBlack);
//     nData_trkMaxJtpt_jet65_Matched_keep[i]=hData_trkMaxJtpt_jet65_Matched_keep[i]->GetEntries();
//     if (nData_trkMaxJtpt_jet65_Matched_keep[i]>0){
//       if(nMC_trkMaxJtpt_jet65_Matched_keep[i]<=0){
//         hData_trkMaxJtpt_jet65_Matched_keep[i]->Print("base");
//         hData_trkMaxJtpt_jet65_Matched_keep[i]->SetTitle(" ");
//         hData_trkMaxJtpt_jet65_Matched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet65, matched pass CutA ",radius));      
//         hData_trkMaxJtpt_jet65_Matched_keep[i]->DrawNormalized();
//       } else {
//       hData_trkMaxJtpt_jet65_Matched_keep[i]->DrawNormalized("same");
//       }
//     } else { cout<<"hData_trkMaxJtpt_jet65_Matched_keep[i] for i= "<<i<<" has "<<nData_trkMaxJtpt_jet65_Matched_keep[i]<<" entries and is not drawn"<<endl; }      
//     drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);
// 
//     TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
//     leg->AddEntry(hMC_trkMaxJtpt_jet65_Matched_keep[0],"MC","pl");
//     leg->AddEntry(hData_trkMaxJtpt_jet65_Matched_keep[0],"Data","pl");
//     leg->SetTextSize(0.04);
//     leg->Draw();
//     
//     ctrkMaxJtpt_jet65_Matched_keep[i]->SaveAs(Form("Plots/trkMaxJtpt_jet65_Matched_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");
// 
//   }
//   TCanvas * ctrkMaxJtpt_jet80_Matched_keep[nbins_cent];
//   
//   for(int i = 0 ; i < nbins_cent ; ++i){
// 
//     ctrkMaxJtpt_jet80_Matched_keep[i] = new TCanvas(Form("ctrkMaxJtpt_jet80_Matched_keep_cent%d",i),"",800,600);
//     ctrkMaxJtpt_jet80_Matched_keep[i]->SetLogy();
//     hMC_trkMaxJtpt_jet80_Matched_keep[i]->SetMarkerColor(kRed);
//     hMC_trkMaxJtpt_jet80_Matched_keep[i]->SetMarkerStyle(25);
//     hMC_trkMaxJtpt_jet80_Matched_keep[i]->Print("base");
//     hMC_trkMaxJtpt_jet80_Matched_keep[i]->SetTitle(" ");
//     hMC_trkMaxJtpt_jet80_Matched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) 80, matched pass CutA ",radius));
//     nMC_trkMaxJtpt_jet80_Matched_keep[i]=hMC_trkMaxJtpt_jet80_Matched_keep[i]->GetEntries();
//     if (nMC_trkMaxJtpt_jet80_Matched_keep[i]>0){
//        hMC_trkMaxJtpt_jet80_Matched_keep[i]->DrawNormalized();
//     } else { cout<<"hMC_trkMaxJtpt_jet80_Matched_keep[i] for i= "<<i<<" has "<<nMC_trkMaxJtpt_jet80_Matched_keep[i]<<" entries and is not drawn"<<endl; }
// 
//     hData_trkMaxJtpt_jet80_Matched_keep[i]->SetMarkerStyle(24);
//     hData_trkMaxJtpt_jet80_Matched_keep[i]->SetMarkerColor(kBlack);
//     nData_trkMaxJtpt_jet80_Matched_keep[i]=hData_trkMaxJtpt_jet80_Matched_keep[i]->GetEntries();
//     if (nData_trkMaxJtpt_jet80_Matched_keep[i]>0){
//       if(nMC_trkMaxJtpt_jet80_Matched_keep[i]<=0){
//         hData_trkMaxJtpt_jet80_Matched_keep[i]->Print("base");
//         hData_trkMaxJtpt_jet80_Matched_keep[i]->SetTitle(" ");
//         hData_trkMaxJtpt_jet80_Matched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) 80, matched pass CutA ",radius));      
//         hData_trkMaxJtpt_jet80_Matched_keep[i]->DrawNormalized();
//       } else {
//       hData_trkMaxJtpt_jet80_Matched_keep[i]->DrawNormalized("same");
//       }
//     } else { cout<<"hData_trkMaxJtpt_jet80_Matched_keep[i] for i= "<<i<<" has "<<nData_trkMaxJtpt_jet80_Matched_keep[i]<<" entries and is not drawn"<<endl; }      
//     drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);
// 
//     TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
//     leg->AddEntry(hMC_trkMaxJtpt_jet80_Matched_keep[0],"MC","pl");
//     leg->AddEntry(hData_trkMaxJtpt_jet80_Matched_keep[0],"Data","pl");
//     leg->SetTextSize(0.04);
//     leg->Draw();
//     
//     ctrkMaxJtpt_jet80_Matched_keep[i]->SaveAs(Form("Plots/trkMaxJtpt_jet80_Matched_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");
// 
//   }
//   
// #if 0
//   TCanvas * ctrkMaxJtpt_Unmatched_keep[nbins_cent];
//   
//   for(int i = 0 ; i < nbins_cent ; ++i){
// 
//     ctrkMaxJtpt_Unmatched_keep[i] = new TCanvas(Form("ctrkMaxJtpt_Unmatched_keep_cent%d",i),"",800,600);
//     ctrkMaxJtpt_Unmatched_keep[i]->SetLogy();
//     hMC_trkMaxJtpt_Unmatched_keep[i]->SetMarkerColor(kRed);
//     hMC_trkMaxJtpt_Unmatched_keep[i]->SetMarkerStyle(25);
//     hMC_trkMaxJtpt_Unmatched_keep[i]->Print("base");
//     hMC_trkMaxJtpt_Unmatched_keep[i]->SetTitle(" ");
//     hMC_trkMaxJtpt_Unmatched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet55||jet65||jet80, pass CutA ",radius));
//     nMC_trkMaxJtpt_Unmatched_keep[i]=hMC_trkMaxJtpt_Unmatched_keep[i]->GetEntries();
//     if (nMC_trkMaxJtpt_Unmatched_keep[i]>0){
//        hMC_trkMaxJtpt_Unmatched_keep[i]->DrawNormalized();
//     } else { cout<<"hMC_trkMaxJtpt_Unmatched_keep[i] for i= "<<i<<" has "<<nMC_trkMaxJtpt_Unmatched_keep[i]<<" entries and is not drawn"<<endl; }
// 
//     hData_trkMaxJtpt_Unmatched_keep[i]->SetMarkerStyle(24);
//     hData_trkMaxJtpt_Unmatched_keep[i]->SetMarkerColor(kBlack);
//     nData_trkMaxJtpt_Unmatched_keep[i]=hData_trkMaxJtpt_Unmatched_keep[i]->GetEntries();
//     if (nData_trkMaxJtpt_Unmatched_keep[i]>0){
//       if(nMC_trkMaxJtpt_Unmatched_keep[i]<=0){
//         hData_trkMaxJtpt_Unmatched_keep[i]->Print("base");
//         hData_trkMaxJtpt_Unmatched_keep[i]->SetTitle(" ");
//         hData_trkMaxJtpt_Unmatched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet55||jet65||jet80, Unmatched pass CutA ",radius));      
//         hData_trkMaxJtpt_Unmatched_keep[i]->DrawNormalized();
//       } else {
//       hData_trkMaxJtpt_Unmatched_keep[i]->DrawNormalized("same");
//       }
//     } else { cout<<"hData_trkMaxJtpt_Unmatched_keep[i] for i= "<<i<<" has "<<nData_trkMaxJtpt_Unmatched_keep[i]<<" entries and is not drawn"<<endl; }      
//     drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);
// 
//     TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
//     leg->AddEntry(hMC_trkMaxJtpt_Unmatched_keep[0],"MC","pl");
//     leg->AddEntry(hData_trkMaxJtpt_Unmatched_keep[0],"Data","pl");
//     leg->SetTextSize(0.04);
//     leg->Draw();
//     
//     ctrkMaxJtpt_Unmatched_keep[i]->SaveAs(Form("Plots/trkMaxJtpt_Unmatched_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");
// 
//   }
// 
//   TCanvas * ctrkMaxJtpt_jet55_Unmatched_keep[nbins_cent];
//   
//   for(int i = 0 ; i < nbins_cent ; ++i){
// 
//     ctrkMaxJtpt_jet55_Unmatched_keep[i] = new TCanvas(Form("ctrkMaxJtpt_jet55_Unmatched_keep_cent%d",i),"",800,600);
//     ctrkMaxJtpt_jet55_Unmatched_keep[i]->SetLogy();
//     hMC_trkMaxJtpt_jet55_Unmatched_keep[i]->SetMarkerColor(kRed);
//     hMC_trkMaxJtpt_jet55_Unmatched_keep[i]->SetMarkerStyle(25);
//     hMC_trkMaxJtpt_jet55_Unmatched_keep[i]->Print("base");
//     hMC_trkMaxJtpt_jet55_Unmatched_keep[i]->SetTitle(" ");
//     hMC_trkMaxJtpt_jet55_Unmatched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet55, pass CutA ",radius));
//     nMC_trkMaxJtpt_jet55_Unmatched_keep[i]=hMC_trkMaxJtpt_jet55_Unmatched_keep[i]->GetEntries();
//     if (nMC_trkMaxJtpt_jet55_Unmatched_keep[i]>0){
//        hMC_trkMaxJtpt_jet55_Unmatched_keep[i]->DrawNormalized();
//     } else { cout<<"hMC_trkMaxJtpt_jet55_Unmatched_keep[i] for i= "<<i<<" has "<<nMC_trkMaxJtpt_jet55_Unmatched_keep[i]<<" entries and is not drawn"<<endl; }
// 
//     hData_trkMaxJtpt_jet55_Unmatched_keep[i]->SetMarkerStyle(24);
//     hData_trkMaxJtpt_jet55_Unmatched_keep[i]->SetMarkerColor(kBlack);
//     nData_trkMaxJtpt_jet55_Unmatched_keep[i]=hData_trkMaxJtpt_jet55_Unmatched_keep[i]->GetEntries();
//     if (nData_trkMaxJtpt_jet55_Unmatched_keep[i]>0){
//       if(nMC_trkMaxJtpt_jet55_Unmatched_keep[i]<=0){
//         hData_trkMaxJtpt_jet55_Unmatched_keep[i]->Print("base");
//         hData_trkMaxJtpt_jet55_Unmatched_keep[i]->SetTitle(" ");
//         hData_trkMaxJtpt_jet55_Unmatched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet55, Unmatched pass CutA ",radius));      
//         hData_trkMaxJtpt_jet55_Unmatched_keep[i]->DrawNormalized();
//       } else {
//       hData_trkMaxJtpt_jet55_Unmatched_keep[i]->DrawNormalized("same");
//       }
//     } else { cout<<"hData_trkMaxJtpt_jet55_Unmatched_keep[i] for i= "<<i<<" has "<<nData_trkMaxJtpt_jet55_Unmatched_keep[i]<<" entries and is not drawn"<<endl; }      
//     drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);
// 
//     TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
//     leg->AddEntry(hMC_trkMaxJtpt_jet55_Unmatched_keep[0],"MC","pl");
//     leg->AddEntry(hData_trkMaxJtpt_jet55_Unmatched_keep[0],"Data","pl");
//     leg->SetTextSize(0.04);
//     leg->Draw();
//     
//     ctrkMaxJtpt_jet55_Unmatched_keep[i]->SaveAs(Form("Plots/trkMaxJtpt_jet55_Unmatched_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");
// 
//   }
//   TCanvas * ctrkMaxJtpt_jet65_Unmatched_keep[nbins_cent];
//   
//   for(int i = 0 ; i < nbins_cent ; ++i){
// 
//     ctrkMaxJtpt_jet65_Unmatched_keep[i] = new TCanvas(Form("ctrkMaxJtpt_jet65_Unmatched_keep_cent%d",i),"",800,600);
//     ctrkMaxJtpt_jet65_Unmatched_keep[i]->SetLogy();
//     hMC_trkMaxJtpt_jet65_Unmatched_keep[i]->SetMarkerColor(kRed);
//     hMC_trkMaxJtpt_jet65_Unmatched_keep[i]->SetMarkerStyle(25);
//     hMC_trkMaxJtpt_jet65_Unmatched_keep[i]->Print("base");
//     hMC_trkMaxJtpt_jet65_Unmatched_keep[i]->SetTitle(" ");
//     hMC_trkMaxJtpt_jet65_Unmatched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet65, Unmatched pass CutA ",radius));
//     nMC_trkMaxJtpt_jet65_Unmatched_keep[i]=hMC_trkMaxJtpt_jet65_Unmatched_keep[i]->GetEntries();
//     if (nMC_trkMaxJtpt_jet65_Unmatched_keep[i]>0){
//        hMC_trkMaxJtpt_jet65_Unmatched_keep[i]->DrawNormalized();
//     } else { cout<<"hMC_trkMaxJtpt_jet65_Unmatched_keep[i] for i= "<<i<<" has "<<nMC_trkMaxJtpt_jet65_Unmatched_keep[i]<<" entries and is not drawn"<<endl; }
// 
//     hData_trkMaxJtpt_jet65_Unmatched_keep[i]->SetMarkerStyle(24);
//     hData_trkMaxJtpt_jet65_Unmatched_keep[i]->SetMarkerColor(kBlack);
//     nData_trkMaxJtpt_jet65_Unmatched_keep[i]=hData_trkMaxJtpt_jet65_Unmatched_keep[i]->GetEntries();
//     if (nData_trkMaxJtpt_jet65_Unmatched_keep[i]>0){
//       if(nMC_trkMaxJtpt_jet65_Unmatched_keep[i]<=0){
//         hData_trkMaxJtpt_jet65_Unmatched_keep[i]->Print("base");
//         hData_trkMaxJtpt_jet65_Unmatched_keep[i]->SetTitle(" ");
//         hData_trkMaxJtpt_jet65_Unmatched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) jet65, Unmatched pass CutA ",radius));      
//         hData_trkMaxJtpt_jet65_Unmatched_keep[i]->DrawNormalized();
//       } else {
//       hData_trkMaxJtpt_jet65_Unmatched_keep[i]->DrawNormalized("same");
//       }
//     } else { cout<<"hData_trkMaxJtpt_jet65_Unmatched_keep[i] for i= "<<i<<" has "<<nData_trkMaxJtpt_jet65_Unmatched_keep[i]<<" entries and is not drawn"<<endl; }      
//     drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);
// 
//     TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
//     leg->AddEntry(hMC_trkMaxJtpt_jet65_Unmatched_keep[0],"MC","pl");
//     leg->AddEntry(hData_trkMaxJtpt_jet65_Unmatched_keep[0],"Data","pl");
//     leg->SetTextSize(0.04);
//     leg->Draw();
//     
//     ctrkMaxJtpt_jet65_Unmatched_keep[i]->SaveAs(Form("Plots/trkMaxJtpt_jet65_Unmatched_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");
// 
//   }
//   TCanvas * ctrkMaxJtpt_jet80_Unmatched_keep[nbins_cent];
//   
//   for(int i = 0 ; i < nbins_cent ; ++i){
// 
//     ctrkMaxJtpt_jet80_Unmatched_keep[i] = new TCanvas(Form("ctrkMaxJtpt_jet80_Unmatched_keep_cent%d",i),"",800,600);
//     ctrkMaxJtpt_jet80_Unmatched_keep[i]->SetLogy();
//     hMC_trkMaxJtpt_jet80_Unmatched_keep[i]->SetMarkerColor(kRed);
//     hMC_trkMaxJtpt_jet80_Unmatched_keep[i]->SetMarkerStyle(25);
//     hMC_trkMaxJtpt_jet80_Unmatched_keep[i]->Print("base");
//     hMC_trkMaxJtpt_jet80_Unmatched_keep[i]->SetTitle(" ");
//     hMC_trkMaxJtpt_jet80_Unmatched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) 80, unmatched pass CutA ",radius));
//     nMC_trkMaxJtpt_jet80_Unmatched_keep[i]=hMC_trkMaxJtpt_jet80_Unmatched_keep[i]->GetEntries();
//     if (nMC_trkMaxJtpt_jet80_Unmatched_keep[i]>0){
//        hMC_trkMaxJtpt_jet80_Unmatched_keep[i]->DrawNormalized();
//     } else { cout<<"hMC_trkMaxJtpt_jet80_Unmatched_keep[i] for i= "<<i<<" has "<<nMC_trkMaxJtpt_jet80_Unmatched_keep[i]<<" entries and is not drawn"<<endl; }
// 
//     hData_trkMaxJtpt_jet80_Unmatched_keep[i]->SetMarkerStyle(24);
//     hData_trkMaxJtpt_jet80_Unmatched_keep[i]->SetMarkerColor(kBlack);
//     nData_trkMaxJtpt_jet80_Unmatched_keep[i]=hData_trkMaxJtpt_jet80_Unmatched_keep[i]->GetEntries();
//     if (nData_trkMaxJtpt_jet80_Unmatched_keep[i]>0){
//       if(nMC_trkMaxJtpt_jet80_Unmatched_keep[i]<=0){
//         hData_trkMaxJtpt_jet80_Unmatched_keep[i]->Print("base");
//         hData_trkMaxJtpt_jet80_Unmatched_keep[i]->SetTitle(" ");
//         hData_trkMaxJtpt_jet80_Unmatched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}) 80, unmatched pass CutA ",radius));      
//         hData_trkMaxJtpt_jet80_Unmatched_keep[i]->DrawNormalized();
//       } else {
//       hData_trkMaxJtpt_jet80_Unmatched_keep[i]->DrawNormalized("same");
//       }
//     } else { cout<<"hData_trkMaxJtpt_jet80_Unmatched_keep[i] for i= "<<i<<" has "<<nData_trkMaxJtpt_jet80_Unmatched_keep[i]<<" entries and is not drawn"<<endl; }      
//     drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);
// 
//     TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
//     leg->AddEntry(hMC_trkMaxJtpt_jet80_Unmatched_keep[0],"MC","pl");
//     leg->AddEntry(hData_trkMaxJtpt_jet80_Unmatched_keep[0],"Data","pl");
//     leg->SetTextSize(0.04);
//     leg->Draw();
//     
//     ctrkMaxJtpt_jet80_Unmatched_keep[i]->SaveAs(Form("Plots/trkMaxJtpt_jet80_Unmatched_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");
// 
//   }
// 
//   TCanvas * ctrkMaxJtpt_Matched_NoTrig_keep[nbins_cent];
//   
//   for(int i = 0 ; i < nbins_cent ; ++i){
// 
//     ctrkMaxJtpt_Matched_NoTrig_keep[i] = new TCanvas(Form("ctrkMaxJtpt_Matched_NoTrig_keep_cent%d",i),"",800,600);
//     ctrkMaxJtpt_Matched_NoTrig_keep[i]->SetLogy();
//     hMC_trkMaxJtpt_Matched_NoTrig_keep[i]->SetMarkerColor(kRed);
//     hMC_trkMaxJtpt_Matched_NoTrig_keep[i]->SetMarkerStyle(25);
//     hMC_trkMaxJtpt_Matched_NoTrig_keep[i]->Print("base");
//     hMC_trkMaxJtpt_Matched_NoTrig_keep[i]->SetTitle(" ");
//     hMC_trkMaxJtpt_Matched_NoTrig_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}), pass CutA ",radius));
//     nMC_trkMaxJtpt_Matched_NoTrig_keep[i]=hMC_trkMaxJtpt_Matched_NoTrig_keep[i]->GetEntries();
//     if (nMC_trkMaxJtpt_Matched_NoTrig_keep[i]>0){
//        hMC_trkMaxJtpt_Matched_NoTrig_keep[i]->DrawNormalized();
//     } else { cout<<"hMC_trkMaxJtpt_Matched_NoTrig_keep[i] for i= "<<i<<" has "<<nMC_trkMaxJtpt_Matched_NoTrig_keep[i]<<" entries and is not drawn"<<endl; }
// 
//     hData_trkMaxJtpt_Matched_keep[i]->SetMarkerStyle(24);
//     hData_trkMaxJtpt_Matched_keep[i]->SetMarkerColor(kBlack);
//     nData_trkMaxJtpt_Matched_keep[i]=hData_trkMaxJtpt_Matched_keep[i]->GetEntries();
//     if (nData_trkMaxJtpt_Matched_keep[i]>0){
//       if(nMC_trkMaxJtpt_Matched_keep[i]<=0){
//         hData_trkMaxJtpt_Matched_keep[i]->Print("base");
//         hData_trkMaxJtpt_Matched_keep[i]->SetTitle(" ");
//         hData_trkMaxJtpt_Matched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}), matched pass CutA ",radius));      
//         hData_trkMaxJtpt_Matched_keep[i]->DrawNormalized();
//       } else {
//       hData_trkMaxJtpt_Matched_keep[i]->DrawNormalized("same");
//       }
//     } else { cout<<"hData_trkMaxJtpt_Matched_keep[i] for i= "<<i<<" has "<<nData_trkMaxJtpt_Matched_keep[i]<<" entries and is not drawn"<<endl; }      
//     drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);
// 
//     TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
//     leg->AddEntry(hMC_trkMaxJtpt_Matched_NoTrig_keep[0],"MC","pl");
//     leg->AddEntry(hData_trkMaxJtpt_Matched_keep[0],"Data","pl");
//     leg->SetTextSize(0.04);
//     leg->Draw();
//     
//     ctrkMaxJtpt_Matched_NoTrig_keep[i]->SaveAs(Form("Plots/trkMaxJtpt_Matched_NoTrig_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");
// 
//   }
//    TCanvas * ctrkMaxJtpt_Unmatched_NoTrig_keep[nbins_cent];
//   
//   for(int i = 0 ; i < nbins_cent ; ++i){
// 
//     ctrkMaxJtpt_Unmatched_NoTrig_keep[i] = new TCanvas(Form("ctrkMaxJtpt_Unmatched_NoTrig_keep_cent%d",i),"",800,600);
//     ctrkMaxJtpt_Unmatched_NoTrig_keep[i]->SetLogy();
//     hMC_trkMaxJtpt_Unmatched_NoTrig_keep[i]->SetMarkerColor(kRed);
//     hMC_trkMaxJtpt_Unmatched_NoTrig_keep[i]->SetMarkerStyle(25);
//     hMC_trkMaxJtpt_Unmatched_NoTrig_keep[i]->Print("base");
//     hMC_trkMaxJtpt_Unmatched_NoTrig_keep[i]->SetTitle(" ");
//     hMC_trkMaxJtpt_Unmatched_NoTrig_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}), pass CutA ",radius));
//     nMC_trkMaxJtpt_Unmatched_NoTrig_keep[i]=hMC_trkMaxJtpt_Unmatched_NoTrig_keep[i]->GetEntries();
//     if (nMC_trkMaxJtpt_Unmatched_NoTrig_keep[i]>0){
//        hMC_trkMaxJtpt_Unmatched_NoTrig_keep[i]->DrawNormalized();
//     } else { cout<<"hMC_trkMaxJtpt_Unmatched_NoTrig_keep[i] for i= "<<i<<" has "<<nMC_trkMaxJtpt_Unmatched_NoTrig_keep[i]<<" entries and is not drawn"<<endl; }
// 
//     hData_trkMaxJtpt_Unmatched_keep[i]->SetMarkerStyle(24);
//     hData_trkMaxJtpt_Unmatched_keep[i]->SetMarkerColor(kBlack);
//     nData_trkMaxJtpt_Unmatched_keep[i]=hData_trkMaxJtpt_Unmatched_keep[i]->GetEntries();
//     if (nData_trkMaxJtpt_Unmatched_keep[i]>0){
//       if(nMC_trkMaxJtpt_Unmatched_NoTrig_keep[i]<=0){
//         hData_trkMaxJtpt_Unmatched_keep[i]->Print("base");
//         hData_trkMaxJtpt_Unmatched_keep[i]->SetTitle(" ");
//         hData_trkMaxJtpt_Unmatched_keep[i]->SetXTitle(Form("trkMax/(ak%dPuPF jet p_{T}), Unmatched pass CutA ",radius));      
//         hData_trkMaxJtpt_Unmatched_keep[i]->DrawNormalized();
//       } else {
//       hData_trkMaxJtpt_Unmatched_keep[i]->DrawNormalized("same");
//       }
//     } else { cout<<"hData_trkMaxJtpt_Unmatched_keep[i] for i= "<<i<<" has "<<nData_trkMaxJtpt_Unmatched_keep[i]<<" entries and is not drawn"<<endl; }      
//     drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);
// 
//     TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
//     leg->AddEntry(hMC_trkMaxJtpt_Unmatched_NoTrig_keep[0],"MC","pl");
//     leg->AddEntry(hData_trkMaxJtpt_Unmatched_keep[0],"Data","pl");
//     leg->SetTextSize(0.04);
//     leg->Draw();
//     
//     ctrkMaxJtpt_Unmatched_NoTrig_keep[i]->SaveAs(Form("Plots/trkMaxJtpt_Unmatched_NoTrig_keep_cent%deMax_MCweight_R%d.pdf",i,radius),"RECREATE");
// 
//   }  
// #endif

// end of code
} 