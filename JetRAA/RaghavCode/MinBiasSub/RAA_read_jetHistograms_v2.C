#include <iostream>
#include <stdio.h>
#include <fstream>
#include <fstream>
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
#include <TStyle.h>
#include <TStopwatch.h>
#include <TRandom3.h>
#include <TChain.h>
#include <TProfile.h>
#include <TStopwatch.h>
#include <TCut.h>
#include <cstdlib>
#include <cmath>
#include "TLegend.h"
#include "TLatex.h"
#include "TMath.h"
#include "TLine.h"
#include "../Headers/plot.h"



static const int nbins_cent = 6;
static const Double_t boundaries_cent[nbins_cent+1] = {0,2,4,12,20,28,36};// multiply by 2.5 to get your actual centrality % (old 2011 data) 
//now we have to multiply by 5, since centrality goes from 0-200. 
const double kdelrcut=0.3;

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

static const int nbins_pt = 32;
static const double boundaries_pt[nbins_pt+1] = {  3, 4, 5, 7, 9, 12, 15, 18, 21, 24, 28,  32, 37, 43, 49, 56,  64, 74, 84, 97, 114,  133, 153, 174, 196,  220, 245, 272, 300, 330, 362, 395, 501};

// static const int nbins_pt = 17;
// static const double boundaries_pt[nbins_pt+1] = { 32, 37, 43, 49, 56,  64, 74, 84, 97, 114,  133, 153, 174, 196,  220, 245, 300, 330};

// the following bins is the cms pp nlo pt bins
// static const int nbins_pt = 29;
// static const double boundaries_pt[nbins_pt+1] = {22, 27, 33, 39, 47, 55, 64, 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638,790,967};

// the following bins is the atlas spectra pt binning
// static const int nbins_pt = 12;
// static const double boundaries_pt[nbins_pt+1] = {31., 39., 50., 63., 79., 100., 125., 158., 199., 251., 316., 398., 501};

// the following bins is the atlas Rcp pt binning
// static const int nbins_pt = 12;
// static const double boundaries_pt[nbins_pt+1] = {38.36, 44.21, 50.94, 58.7, 67.64 , 77.94 , 89.81, 103.5, 119.3, 137.4 , 158.3, 182.5,  210.3};


using namespace std;


void RAA_read_jetHistograms_v2(char* etaWidth = (char*)"20_eta_20",
			    Int_t radius = 3,
			    Int_t etaLow = 20,
			    Int_t etaHigh = 20,
			    char * ptbins = (char*)"finebins")
{
  
  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();

  // char * etaWidth = (char*)Form("%d_eta_%d",etaLow, etaHigh);
  cout<<"etaWidth = "<<etaWidth<<endl;
  cout<<"Radius = "<<radius<<endl;

  bool isSymm = false;
  if(etaLow == etaHigh) isSymm = true;
  bool cutEvents = true; 

  // declare #of events to run through for specific triggers, in Millions
  Long_t nEvents_Jet55 = 3;
  Long_t nEvents_Jet65 = 3;

  Long_t jet55_counter = 0, jet65_counter = 0, jet80_counter = 0; 
  
  // the prescl for the specific trigger is then scaled by the factor of no of events you are choosing.
  // so if you choose 1M events for jet55, then you a prescl of prescl * 20/1,
  double Jet55_prescl_fac = (double)20.0/nEvents_Jet55;
  double Jet65_prescl_fac = (double)6.5/nEvents_Jet65;
  
  
  char * ntuple = (char*)"Pawan"; //  or "Pawan"
  
  // the cut is a 3 step cut based on the different value of the calopt/pfpt - copy the following lines into your loop (with the corresponding branch address set)
  // if(calopt/pfpt <= 0.5 && eMax/Sumcand < 0.05) hGood->Fill();
  // if(calopt/pfpt > 0.5 && calopt/pfpt <= 0.85 && eMax/Sumcand < (18/7 *(Float_t)calopt_1/pfpt_1 - 9/7)) ) hGood->Fill();
  // if(calopt/pfpt > 0.85 & eMax/Sumcand > 0.9) hGood->Fill();
  
  TFile * fData, * fMC, * fJetID;
  TTree * Data_matched, *MC_matched, * Data_JetID, * MC_JetID; 

  if(ntuple == "Pawan"){
    fData = TFile::Open("/mnt/hadoop/cms/store/user/pawan/trees/JetRaaTree_akPu234_PbPb_DATA.root");
    fMC = TFile::Open("/mnt/hadoop/cms/store/user/pawan/trees/JetRaaTree_akPu234_PbPb_MC.root");
    fJetID = TFile::Open(Form("/export/d00/scratch/rkunnawa/rootfiles/RAA/Pawan_TTree_PbPb_Data_MC_JetID_CutA_flag_R0p%d.root", radius));
    
    Data_JetID = (TTree*)fJetID->Get("jetID_Data");
    MC_JetID = (TTree*)fJetID->Get("jetID_MC");
    Data_matched = (TTree*)fData->Get(Form("akPu%dJetAnalyzer/jetTree",radius));
    MC_matched = (TTree*)fMC->Get(Form("akPu%dJetAnalyzer/jetTree",radius));

    Data_matched->AddFriend(Data_JetID);
    MC_matched->AddFriend(MC_JetID);
    
  }

  //get the spectra with the specific trigger object from the different files. 
  TH1F *hpbpb_Jet80_gen[nbins_cent],
    *hpbpb_Jet80_reco[nbins_cent],
    *hpbpb_Jet80_raw[nbins_cent],
    *hpbpb_Jet80_GenSmear[nbins_cent],
    *hpbpb_Jet80_RecoSmear[nbins_cent];
  TH1F *hpbpb_Jet65_gen[nbins_cent],
    *hpbpb_Jet65_reco[nbins_cent],
    *hpbpb_Jet65_raw[nbins_cent],
    *hpbpb_Jet65_GenSmear[nbins_cent],
    *hpbpb_Jet65_RecoSmear[nbins_cent];
  TH1F *hpbpb_Jet55_gen[nbins_cent],
    *hpbpb_Jet55_reco[nbins_cent],
    *hpbpb_Jet55_raw[nbins_cent],
    *hpbpb_Jet55_GenSmear[nbins_cent],
    *hpbpb_Jet55_RecoSmear[nbins_cent],
    * hpbpb_Jet55_reco_5TrigIneff_Smear[nbins_cent],
    * hpbpb_Jet55_reco_10TrigIneff_Smear[nbins_cent],
    * hpbpb_Jet55_gen_5TrigIneff_Smear[nbins_cent],
    * hpbpb_Jet55_gen_10TrigIneff_Smear[nbins_cent];
  TH1F *hpbpb_JetComb_gen[nbins_cent],
    *hpbpb_JetComb_reco[nbins_cent],
    *hpbpb_JetComb_raw[nbins_cent],
    *hpbpb_JetComb_GenSmear[nbins_cent],
    *hpbpb_JetComb_RecoSmear[nbins_cent],
    * hpbpb_JetComb_reco_5TrigIneff_Smear[nbins_cent],
    * hpbpb_JetComb_reco_10TrigIneff_Smear[nbins_cent],
    * hpbpb_JetComb_gen_5TrigIneff_Smear[nbins_cent],
    * hpbpb_JetComb_gen_10TrigIneff_Smear[nbins_cent];

  TH1F * hpbpb_JetComb_gen2pSmear[nbins_cent],
    * hpbpb_Jet80_gen2pSmear[nbins_cent],
    * hpbpb_Jet65_gen2pSmear[nbins_cent],
    * hpbpb_Jet55_gen2pSmear[nbins_cent];

  TH1F * hpbpb_MC_noCut[nbins_cent];
  TH1F * hpbpb_MC_Comb_noCut[nbins_cent];
  TH1F * hpbpb_MC_Jet80_noCut[nbins_cent];
  TH1F * hpbpb_MC_Jet65_noCut[nbins_cent];
  TH1F * hpbpb_MC_Jet55_noCut[nbins_cent];
  TH1F * hpbpb_Data_Comb_noCut[nbins_cent];
  TH1F * hpbpb_Data_Jet55_noCut[nbins_cent];
  TH1F * hpbpb_Data_Jet65_noCut[nbins_cent];
  TH1F * hpbpb_Data_Jet80_noCut[nbins_cent];

  TH1F *hpbpb_gen[nbins_cent],*hpbpb_reco[nbins_cent];
  TH2F *hpbpb_matrix[nbins_cent];
  TH2F *hpbpb_matrix_HLT[nbins_cent];
  TH2F *hpbpb_Trans_matrix_HLT[nbins_cent];
  TH2F *hpbpb_matrix_HLT_GenSmear[nbins_cent];
  TH2F *hpbpb_matrix_HLT_gen2pSmear[nbins_cent];
  TH2F *hpbpb_matrix_HLT_RecoSmear[nbins_cent];
  TH2F *hpbpb_matrix_HLT_BothSmear[nbins_cent];
  TH2F *hpbpb_matrix_HLT_5TrigIneff_Smear[nbins_cent];
  TH2F *hpbpb_matrix_HLT_10TrigIneff_Smear[nbins_cent];
  
  TH2F *hpbpb_mcclosure_matrix[nbins_cent];
  TH2F *hpbpb_mcclosure_matrix_HLT[nbins_cent];  
  TH2F *hpbpb_mcclosure_matrix_HLT_5TrigIneff_Smear[nbins_cent];  
  TH2F *hpbpb_mcclosure_matrix_HLT_10TrigIneff_Smear[nbins_cent];  
  TH1F *hpbpb_mcclosure_data[nbins_cent];
  TH1F *hpbpb_mcclosure_data_train[nbins_cent];
  TH1F *hpbpb_mcclosure_JetComb_data[nbins_cent];
  TH1F *hpbpb_mcclosure_JetComb_data_5TrigIneff_Smear[nbins_cent];
  TH1F *hpbpb_mcclosure_JetComb_data_10TrigIneff_Smear[nbins_cent];
  TH1F *hpbpb_mcclosure_Jet80_data[nbins_cent];
  TH1F *hpbpb_mcclosure_Jet65_data[nbins_cent];
  TH1F *hpbpb_mcclosure_Jet55_data[nbins_cent];
  TH1F *hpbpb_mcclosure_Jet55_data_5TrigIneff_Smear[nbins_cent];
  TH1F *hpbpb_mcclosure_Jet55_data_10TrigIneff_Smear[nbins_cent];
  TH1F *hpbpb_mcclosure_JetComb_data_train[nbins_cent];
  TH1F *hpbpb_mcclosure_JetComb_data_train_5TrigIneff_Smear[nbins_cent];
  TH1F *hpbpb_mcclosure_JetComb_data_train_10TrigIneff_Smear[nbins_cent];
  TH1F *hpbpb_mcclosure_Jet80_data_train[nbins_cent];
  TH1F *hpbpb_mcclosure_Jet65_data_train[nbins_cent];
  TH1F *hpbpb_mcclosure_Jet55_data_train[nbins_cent];
  TH1F *hpbpb_mcclosure_Jet55_data_train_5TrigIneff_Smear[nbins_cent];
  TH1F *hpbpb_mcclosure_Jet55_data_train_10TrigIneff_Smear[nbins_cent];
  TH1F *hpbpb_mcclosure_gen[nbins_cent];
  TH1F *hpbpb_mcclosure_JetComb_gen[nbins_cent];
  TH1F *hpbpb_mcclosure_JetComb_gen_5TrigIneff_Smear[nbins_cent];
  TH1F *hpbpb_mcclosure_JetComb_gen_10TrigIneff_Smear[nbins_cent];
  TH1F *hpbpb_mcclosure_Jet80_gen[nbins_cent];
  TH1F *hpbpb_mcclosure_Jet65_gen[nbins_cent];
  TH1F *hpbpb_mcclosure_Jet55_gen[nbins_cent];
  TH1F *hpbpb_mcclosure_Jet55_gen_5TrigIneff_Smear[nbins_cent];
  TH1F *hpbpb_mcclosure_Jet55_gen_10TrigIneff_Smear[nbins_cent];

  TH1F *hpbpb_TrgObj80[nbins_cent];
  TH1F *hpbpb_TrgObj65[nbins_cent];
  TH1F *hpbpb_TrgObj55[nbins_cent];
  TH1F *hpbpb_TrgObjComb[nbins_cent];

  TH1F *hpbpb_raw_TrgObj80[nbins_cent];
  TH1F *hpbpb_raw_TrgObj65[nbins_cent];
  TH1F *hpbpb_raw_TrgObj55[nbins_cent];
  TH1F *hpbpb_raw_TrgObjComb[nbins_cent];

  TH1F *hpbpb_anaBin_TrgObj80[nbins_cent];
  TH1F *hpbpb_anaBin_TrgObj65[nbins_cent];
  TH1F *hpbpb_anaBin_TrgObj55[nbins_cent];
  TH1F *hpbpb_anaBin_TrgObjComb[nbins_cent];
  TH2F *hpbpb_anaBin_matrix_HLT[nbins_cent];
  TH2F *hpbpb_anaBin_Trans_matrix_HLT[nbins_cent];
  TH1F *hpbpb_anaBin_Jet80_gen[nbins_cent],*hpbpb_anaBin_Jet80_reco[nbins_cent];
  TH1F *hpbpb_anaBin_Jet65_gen[nbins_cent],*hpbpb_anaBin_Jet65_reco[nbins_cent];
  TH1F *hpbpb_anaBin_Jet55_gen[nbins_cent],*hpbpb_anaBin_Jet55_reco[nbins_cent];
  TH1F *hpbpb_anaBin_JetComb_gen[nbins_cent],*hpbpb_anaBin_JetComb_reco[nbins_cent];

  TH1F *hpbpb_JEC_TrgObj80[nbins_cent];
  TH1F *hpbpb_JEC_TrgObj65[nbins_cent];
  TH1F *hpbpb_JEC_TrgObj55[nbins_cent];
  TH1F *hpbpb_JEC_TrgObjComb[nbins_cent];

  TH1F *hpbpb_Smear_TrgObj80[nbins_cent];
  TH1F *hpbpb_Smear_TrgObj65[nbins_cent];
  TH1F *hpbpb_Smear_TrgObj55[nbins_cent];
  TH1F *hpbpb_Smear_TrgObjComb[nbins_cent];
  
  for(int i = 0;i<nbins_cent;++i){
    //cout<<"cent bin = "<<i<<endl;

    hpbpb_MC_noCut[i] = new TH1F(Form("hpbpb_MC_noCut_cent%d",i),"",501,0,501);
    
    hpbpb_MC_Jet55_noCut[i] = new TH1F(Form("hpbpb_MC_Jet55_noCut_cent%d",i),"",501,0,501);
    hpbpb_MC_Jet65_noCut[i] = new TH1F(Form("hpbpb_MC_Jet65_noCut_cent%d",i),"",501,0,501);
    hpbpb_MC_Jet80_noCut[i] = new TH1F(Form("hpbpb_MC_Jet80_noCut_cent%d",i),"",501,0,501);
    hpbpb_MC_Comb_noCut[i] = new TH1F(Form("hpbpb_MC_Comb_noCut_cent%d",i),"",501,0,501);

    hpbpb_Data_Jet55_noCut[i] = new TH1F(Form("hpbpb_Data_Jet55_noCut_cent%d",i),"",501,0,501);
    hpbpb_Data_Jet65_noCut[i] = new TH1F(Form("hpbpb_Data_Jet65_noCut_cent%d",i),"",501,0,501);
    hpbpb_Data_Jet80_noCut[i] = new TH1F(Form("hpbpb_Data_Jet80_noCut_cent%d",i),"",501,0,501);
    hpbpb_Data_Comb_noCut[i] = new TH1F(Form("hpbpb_Data_Comb_noCut_cent%d",i),"",501,0,501);

    hpbpb_TrgObj80[i] = new TH1F(Form("hpbpb_HLT80_R%d_%s_cent%d",radius,etaWidth,i),Form("Spectra from  Jet 80 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_TrgObj65[i] = new TH1F(Form("hpbpb_HLT65_R%d_%s_cent%d",radius,etaWidth,i),Form("Spectra from  Jet 65 && !jet80 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_TrgObj55[i] = new TH1F(Form("hpbpb_HLT55_R%d_%s_cent%d",radius,etaWidth,i),Form("Spectra from Jet 55 && !jet65 && !jet80 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_TrgObjComb[i] = new TH1F(Form("hpbpb_HLTComb_R%d_%s_cent%d",radius,etaWidth,i),Form("Trig Combined Spectra R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);

    hpbpb_raw_TrgObj80[i] = new TH1F(Form("hpbpb_raw_HLT80_R%d_%s_cent%d",radius,etaWidth,i),Form("Spectra from  Jet 80 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_raw_TrgObj65[i] = new TH1F(Form("hpbpb_raw_HLT65_R%d_%s_cent%d",radius,etaWidth,i),Form("Spectra from  Jet 65 && !jet80 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_raw_TrgObj55[i] = new TH1F(Form("hpbpb_raw_HLT55_R%d_%s_cent%d",radius,etaWidth,i),Form("Spectra from Jet 55 && !jet65 && !jet80 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_raw_TrgObjComb[i] = new TH1F(Form("hpbpb_raw_HLTComb_R%d_%s_cent%d",radius,etaWidth,i),Form("Trig Combined Spectra R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);

    hpbpb_anaBin_TrgObj80[i] = new TH1F(Form("hpbpb_anaBin_HLT80_R%d_%s_cent%d",radius,etaWidth,i),Form("Spectra from  Jet 80 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),nbins_pt, boundaries_pt);
    hpbpb_anaBin_TrgObj65[i] = new TH1F(Form("hpbpb_anaBin_HLT65_R%d_%s_cent%d",radius,etaWidth,i),Form("Spectra from  Jet 65 && !jet80 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),nbins_pt, boundaries_pt);
    hpbpb_anaBin_TrgObj55[i] = new TH1F(Form("hpbpb_anaBin_HLT55_R%d_%s_cent%d",radius,etaWidth,i),Form("Spectra from Jet 55 && !jet65 && !jet80 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),nbins_pt, boundaries_pt);
    hpbpb_anaBin_TrgObjComb[i] = new TH1F(Form("hpbpb_anaBin_HLTComb_R%d_%s_cent%d",radius,etaWidth,i),Form("Trig Combined Spectra R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),nbins_pt, boundaries_pt);
    
    hpbpb_JEC_TrgObj80[i] = new TH1F(Form("hpbpb_JEC_HLT80_R%d_%s_cent%d",radius,etaWidth,i),Form("Spectra from  Jet 80 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_JEC_TrgObj65[i] = new TH1F(Form("hpbpb_JEC_HLT65_R%d_%s_cent%d",radius,etaWidth,i),Form("Spectra from  Jet 65 && !jet80 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_JEC_TrgObj55[i] = new TH1F(Form("hpbpb_JEC_HLT55_R%d_%s_cent%d",radius,etaWidth,i),Form("Spectra from Jet 55 && !jet65 && !jet80 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_JEC_TrgObjComb[i] = new TH1F(Form("hpbpb_JEC_HLTComb_R%d_%s_cent%d",radius,etaWidth,i),Form("Trig Combined Spectra R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);

    hpbpb_Smear_TrgObj80[i] = new TH1F(Form("hpbpb_Smear_HLT80_R%d_%s_cent%d",radius,etaWidth,i),Form("Spectra from  Jet 80 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_Smear_TrgObj65[i] = new TH1F(Form("hpbpb_Smear_HLT65_R%d_%s_cent%d",radius,etaWidth,i),Form("Spectra from  Jet 65 && !jet80 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_Smear_TrgObj55[i] = new TH1F(Form("hpbpb_Smear_HLT55_R%d_%s_cent%d",radius,etaWidth,i),Form("Spectra from Jet 55 && !jet65 && !jet80 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_Smear_TrgObjComb[i] = new TH1F(Form("hpbpb_Smear_HLTComb_R%d_%s_cent%d",radius,etaWidth,i),Form("Trig Combined Spectra R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);

    hpbpb_gen[i] = new TH1F(Form("hpbpb_gen_R%d_%s_cent%d",radius,etaWidth,i),Form("Gen refpt R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    //cout<<"A"<<endl;
    hpbpb_reco[i] = new TH1F(Form("hpbpb_reco_R%d_%s_cent%d",radius,etaWidth,i),Form("Reco jtpt R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    //cout<<"B"<<endl;
    hpbpb_matrix[i] = new TH2F(Form("hpbpb_matrix_R%d_%s_cent%d",radius,etaWidth,i),Form("Matrix refpt jtpt R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501,501,0,501);
    
    hpbpb_matrix_HLT[i] = new TH2F(Form("hpbpb_matrix_HLT_R%d_%s_cent%d",radius,etaWidth,i),Form("Matrix refpt jtpt from trigger addition R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501,501,0,501);
    hpbpb_Trans_matrix_HLT[i] = new TH2F(Form("hpbpb_Trans_matrix_HLT_R%d_%s_cent%d",radius,etaWidth,i),Form("Matrix refpt jtpt from trigger addition R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501,501,0,501);
    hpbpb_matrix_HLT_GenSmear[i] = new TH2F(Form("hpbpb_matrix_HLT_GenSmear_R%d_%s_cent%d",radius,etaWidth,i),Form("Matrix refpt jtpt from trigger addition R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501,501,0,501);
    hpbpb_matrix_HLT_gen2pSmear[i] = new TH2F(Form("hpbpb_matrix_HLT_gen2pSmear_R%d_%s_cent%d",radius,etaWidth,i),Form("Matrix refpt jtpt from trigger addition R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501,501,0,501);
    hpbpb_matrix_HLT_RecoSmear[i] = new TH2F(Form("hpbpb_matrix_HLT_RecoSmear_R%d_%s_cent%d",radius,etaWidth,i),Form("Matrix refpt jtpt from trigger addition R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501,501,0,501);
    hpbpb_matrix_HLT_BothSmear[i] = new TH2F(Form("hpbpb_matrix_HLT_BothSmear_R%d_%s_cent%d",radius,etaWidth,i),Form("Matrix refpt jtpt from trigger addition R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501,501,0,501);
    hpbpb_matrix_HLT_5TrigIneff_Smear[i] = new TH2F(Form("hpbpb_matrix_HLT_5TrigIneffSmear_R%d_%s_cent%d",radius,etaWidth,i),Form("Matrix refpt jtpt from trigger addition R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501,501,0,501);
    hpbpb_matrix_HLT_10TrigIneff_Smear[i] = new TH2F(Form("hpbpb_matrix_HLT_10TrigIneffSmear_R%d_%s_cent%d",radius,etaWidth,i),Form("Matrix refpt jtpt from trigger addition R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501,501,0,501);

    hpbpb_anaBin_matrix_HLT[i] = new TH2F(Form("hpbpb_anaBin_matrix_HLT_R%d_%s_cent%d",radius,etaWidth,i),Form("Matrix refpt jtpt from trigger addition R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),nbins_pt, boundaries_pt,nbins_pt, boundaries_pt);
    hpbpb_anaBin_Trans_matrix_HLT[i] = new TH2F(Form("hpbpb_anaBin_Trans_matrix_HLT_R%d_%s_cent%d",radius,etaWidth,i),Form("Matrix refpt jtpt from trigger addition R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),nbins_pt, boundaries_pt,nbins_pt, boundaries_pt);

    hpbpb_mcclosure_matrix[i] = new TH2F(Form("hpbpb_mcclosure_matrix_R%d_%s_cent%d",radius,etaWidth,i),Form("Matrix for mcclosure refpt jtpt R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501,501,0,501);
    hpbpb_mcclosure_matrix_HLT[i] = new TH2F(Form("hpbpb_mcclosure_matrix_HLT_R%d_%s_cent%d",radius,etaWidth,i),Form("Matrix for mcclosure refpt jtpt from Jet triggers R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501,501,0,501);
    hpbpb_mcclosure_matrix_HLT_5TrigIneff_Smear[i] = new TH2F(Form("hpbpb_mcclosure_matrix_HLT_5TrigIneff_Smear_R%d_%s_cent%d",radius,etaWidth,i),Form("Matrix for mcclosure refpt jtpt from Jet triggers R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501,501,0,501);
    hpbpb_mcclosure_matrix_HLT_10TrigIneff_Smear[i] = new TH2F(Form("hpbpb_mcclosure_matrix_HLT_10TrigIneff_Smear_R%d_%s_cent%d",radius,etaWidth,i),Form("Matrix for mcclosure refpt jtpt from Jet triggers R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501,501,0,501);
    //cout<<"C"<<endl;
    hpbpb_mcclosure_data[i] =new TH1F(Form("hpbpb_mcclosure_data_R%d_%s_cent%d",radius,etaWidth,i),Form("data for unfolding mc closure test R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_mcclosure_data_train[i] =new TH1F(Form("hpbpb_mcclosure_data_train_R%d_%s_cent%d",radius,etaWidth,i),Form("data_train for unfolding mc closure test R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_mcclosure_JetComb_data[i] = new TH1F(Form("hpbpb_mcclosure_JetComb_data_R%d_%s_cent%d",radius,etaWidth,i),Form("data for unfolding mc closure test trigger combined  R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_mcclosure_JetComb_data_5TrigIneff_Smear[i] = new TH1F(Form("hpbpb_mcclosure_JetComb_data_5TrigIneff_Smear_R%d_%s_cent%d",radius,etaWidth,i),Form("data for unfolding mc closure test trigger combined  R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_mcclosure_JetComb_data_10TrigIneff_Smear[i] = new TH1F(Form("hpbpb_mcclosure_JetComb_data_10TrigIneff_Smear_R%d_%s_cent%d",radius,etaWidth,i),Form("data for unfolding mc closure test trigger combined  R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_mcclosure_Jet80_data[i] = new TH1F(Form("hpbpb_mcclosure_Jet80_data_R%d_%s_cent%d",radius,etaWidth,i),Form("data for unfolding mc closure test trigger 80  R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_mcclosure_Jet65_data[i] = new TH1F(Form("hpbpb_mcclosure_Jet65_data_R%d_%s_cent%d",radius,etaWidth,i),Form("data for unfolding mc closure test trigger 65  R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_mcclosure_Jet55_data[i] = new TH1F(Form("hpbpb_mcclosure_Jet55_data_R%d_%s_cent%d",radius,etaWidth,i),Form("data for unfolding mc closure test trigger 55  R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_mcclosure_Jet55_data_5TrigIneff_Smear[i] = new TH1F(Form("hpbpb_mcclosure_Jet55_data_5TrigIneff_Smear_R%d_%s_cent%d",radius,etaWidth,i),Form("data for unfolding mc closure test trigger 55  R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_mcclosure_Jet55_data_10TrigIneff_Smear[i] = new TH1F(Form("hpbpb_mcclosure_Jet55_data_10TrigIneff_Smear_R%d_%s_cent%d",radius,etaWidth,i),Form("data for unfolding mc closure test trigger 55  R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);

    hpbpb_mcclosure_JetComb_data_train[i] = new TH1F(Form("hpbpb_mcclosure_JetComb_data_train_R%d_%s_cent%d",radius,etaWidth,i),Form("data_train for unfolding mc closure test trigger combined  R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_mcclosure_Jet80_data_train[i] = new TH1F(Form("hpbpb_mcclosure_Jet80_data_train_R%d_%s_cent%d",radius,etaWidth,i),Form("data_train for unfolding mc closure test trigger 80  R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_mcclosure_Jet65_data_train[i] = new TH1F(Form("hpbpb_mcclosure_Jet65_data_train_R%d_%s_cent%d",radius,etaWidth,i),Form("data_train for unfolding mc closure test trigger 65  R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_mcclosure_Jet55_data_train[i] = new TH1F(Form("hpbpb_mcclosure_Jet55_data_train_R%d_%s_cent%d",radius,etaWidth,i),Form("data_train for unfolding mc closure test trigger 55  R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);

    hpbpb_mcclosure_gen[i] = new TH1F(Form("hpbpb_mcclosure_gen_R%d_%s_cent%d",radius,etaWidth,i),Form("gen spectra for unfolding mc closure test R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_mcclosure_JetComb_gen[i] = new TH1F(Form("hpbpb_mcclosure_gen_JetComb_R%d_%s_cent%d",radius,etaWidth,i),Form("gen spectra for unfolding mc closure test trigger combined R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_mcclosure_JetComb_gen_5TrigIneff_Smear[i] = new TH1F(Form("hpbpb_mcclosure_gen_JetComb_5TrigIneff_Smear_R%d_%s_cent%d",radius,etaWidth,i),Form("gen spectra for unfolding mc closure test trigger combined R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_mcclosure_JetComb_gen_10TrigIneff_Smear[i] = new TH1F(Form("hpbpb_mcclosure_gen_JetComb_10TrigIneff_Smear_R%d_%s_cent%d",radius,etaWidth,i),Form("gen spectra for unfolding mc closure test trigger combined R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_mcclosure_Jet80_gen[i] = new TH1F(Form("hpbpb_mcclosure_gen_Jet80_R%d_%s_cent%d",radius,etaWidth,i),Form("gen spectra for unfolding mc closure test trigger 80 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_mcclosure_Jet65_gen[i] = new TH1F(Form("hpbpb_mcclosure_gen_Jet65_R%d_%s_cent%d",radius,etaWidth,i),Form("gen spectra for unfolding mc closure test trigger 65 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_mcclosure_Jet55_gen[i] = new TH1F(Form("hpbpb_mcclosure_gen_Jet55_R%d_%s_cent%d",radius,etaWidth,i),Form("gen spectra for unfolding mc closure test trigger 55 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_mcclosure_Jet55_gen_5TrigIneff_Smear[i] = new TH1F(Form("hpbpb_mcclosure_gen_Jet55_5TrigIneff_Smear_R%d_%s_cent%d",radius,etaWidth,i),Form("gen spectra for unfolding mc closure test trigger 55 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_mcclosure_Jet55_gen_10TrigIneff_Smear[i] = new TH1F(Form("hpbpb_mcclosure_gen_Jet55_10TrigIneff_Smear[_R%d_%s_cent%d",radius,etaWidth,i),Form("gen spectra for unfolding mc closure test trigger 55 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    
    hpbpb_JetComb_gen[i] = new TH1F(Form("hpbpb_JetComb_gen_R%d_%s_cent%d",radius,etaWidth,i),Form("Gen refpt from HLT trigger combined R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_JetComb_reco[i] = new TH1F(Form("hpbpb_JetComb_reco_R%d_%s_cent%d",radius,etaWidth,i),Form("reco jtpt from HLT trigger combined R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_Jet80_gen[i] = new TH1F(Form("hpbpb_Jet80_gen_R%d_%s_cent%d",radius,etaWidth,i),Form("Gen refpt from Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_Jet80_reco[i] = new TH1F(Form("hpbpb_Jet80_reco_R%d_%s_cent%d",radius,etaWidth,i),Form("reco jtpt from Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_Jet65_gen[i] = new TH1F(Form("hpbpb_Jet65_gen_R%d_%s_cent%d",radius,etaWidth,i),Form("Gen refpt from Jet65 && !Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_Jet65_reco[i] = new TH1F(Form("hpbpb_Jet65_reco_R%d_%s_cent%d",radius,etaWidth,i),Form("reco jtpt from Jet65 && !Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_Jet55_gen[i] = new TH1F(Form("hpbpb_Jet55_gen_R%d_%s_cent%d",radius,etaWidth,i),Form("Gen refpt from Jet55 && !Jet65 && !Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_Jet55_reco[i] = new TH1F(Form("hpbpb_Jet55_reco_R%d_%s_cent%d",radius,etaWidth,i),Form("reco jtpt from Jet55 && !Jet65 && !Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
						
    hpbpb_JetComb_GenSmear[i] = new TH1F(Form("hpbpb_JetComb_GenSmear_R%d_%s_cent%d",radius,etaWidth,i),Form("GenSmear refpt from HLT trigger combined R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_JetComb_gen2pSmear[i] = new TH1F(Form("hpbpb_JetComb_gen2pSmear_R%d_%s_cent%d",radius,etaWidth,i),Form("gen2pSmear refpt from HLT trigger combined R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_JetComb_RecoSmear[i] = new TH1F(Form("hpbpb_JetComb_RecoSmear_R%d_%s_cent%d",radius,etaWidth,i),Form("RecoSmear jtpt from HLT trigger combined R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_Jet80_GenSmear[i] = new TH1F(Form("hpbpb_Jet80_GenSmear_R%d_%s_cent%d",radius,etaWidth,i),Form("GenSmear refpt from Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_Jet80_gen2pSmear[i] = new TH1F(Form("hpbpb_Jet80_gen2pSmear_R%d_%s_cent%d",radius,etaWidth,i),Form("gen2pSmear refpt from Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_Jet80_RecoSmear[i] = new TH1F(Form("hpbpb_Jet80_RecoSmear_R%d_%s_cent%d",radius,etaWidth,i),Form("RecoSmear jtpt from Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_Jet65_GenSmear[i] = new TH1F(Form("hpbpb_Jet65_GenSmear_R%d_%s_cent%d",radius,etaWidth,i),Form("GenSmear refpt from Jet65 && !Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_Jet65_gen2pSmear[i] = new TH1F(Form("hpbpb_Jet65_gen2pSmear_R%d_%s_cent%d",radius,etaWidth,i),Form("gen2pSmear refpt from Jet65 && !Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_Jet65_RecoSmear[i] = new TH1F(Form("hpbpb_Jet65_RecoSmear_R%d_%s_cent%d",radius,etaWidth,i),Form("RecoSmear jtpt from Jet65 && !Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_Jet55_GenSmear[i] = new TH1F(Form("hpbpb_Jet55_GenSmear_R%d_%s_cent%d",radius,etaWidth,i),Form("GenSmear refpt from Jet55 && !Jet65 && !Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_Jet55_gen2pSmear[i] = new TH1F(Form("hpbpb_Jet55_gen2pSmear_R%d_%s_cent%d",radius,etaWidth,i),Form("gen2pSmear refpt from Jet55 && !Jet65 && !Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_Jet55_RecoSmear[i] = new TH1F(Form("hpbpb_Jet55_RecoSmear_R%d_%s_cent%d",radius,etaWidth,i),Form("RecoSmear jtpt from Jet55 && !Jet65 && !Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);

    hpbpb_JetComb_gen_5TrigIneff_Smear[i] = new TH1F(Form("hpbpb_JetComb_gen_5TrigIneff_Smear_R%d_%s_cent%d",radius,etaWidth,i),Form("GenSmear refpt from HLT trigger combined R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_JetComb_reco_5TrigIneff_Smear[i] = new TH1F(Form("hpbpb_JetComb_reco_5TrigIneff_Smear_R%d_%s_cent%d",radius,etaWidth,i),Form("GenSmear refpt from HLT trigger combined R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_Jet55_gen_5TrigIneff_Smear[i] = new TH1F(Form("hpbpb_Jet55_gen_5TrigIneff_Smear_R%d_%s_cent%d",radius,etaWidth,i),Form("GenSmear refpt from HLT trigger combined R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_Jet55_reco_5TrigIneff_Smear[i] = new TH1F(Form("hpbpb_Jet55_reco_5TrigIneff_Smear_R%d_%s_cent%d",radius,etaWidth,i),Form("GenSmear refpt from HLT trigger combined R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);

    hpbpb_JetComb_gen_10TrigIneff_Smear[i] = new TH1F(Form("hpbpb_JetComb_gen_10TrigIneff_Smear_R%d_%s_cent%d",radius,etaWidth,i),Form("GenSmear refpt from HLT trigger combined R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_JetComb_reco_10TrigIneff_Smear[i] = new TH1F(Form("hpbpb_JetComb_reco_10TrigIneff_Smear_R%d_%s_cent%d",radius,etaWidth,i),Form("GenSmear refpt from HLT trigger combined R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_Jet55_gen_10TrigIneff_Smear[i] = new TH1F(Form("hpbpb_Jet55_gen_10TrigIneff_Smear_R%d_%s_cent%d",radius,etaWidth,i),Form("GenSmear refpt from HLT trigger combined R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_Jet55_reco_10TrigIneff_Smear[i] = new TH1F(Form("hpbpb_Jet55_reco_10TrigIneff_Smear_R%d_%s_cent%d",radius,etaWidth,i),Form("GenSmear refpt from HLT trigger combined R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);



    hpbpb_JetComb_raw[i] = new TH1F(Form("hpbpb_JetComb_raw_R%d_%s_cent%d",radius,etaWidth,i),Form("raw jtpt from HLT trigger combined R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_Jet80_raw[i] = new TH1F(Form("hpbpb_Jet80_raw_R%d_%s_cent%d",radius,etaWidth,i),Form("raw jtpt from Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_Jet65_raw[i] = new TH1F(Form("hpbpb_Jet65_raw_R%d_%s_cent%d",radius,etaWidth,i),Form("raw jtpt from Jet65 && !Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);
    hpbpb_Jet55_raw[i] = new TH1F(Form("hpbpb_Jet55_raw_R%d_%s_cent%d",radius,etaWidth,i),Form("raw jtpt from Jet55 && !Jet65 && !Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),501,0,501);

    hpbpb_anaBin_JetComb_gen[i] = new TH1F(Form("hpbpb_anaBin_JetComb_gen_R%d_%s_cent%d",radius,etaWidth,i),Form("Gen refpt from HLT trigger combined R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),nbins_pt, boundaries_pt);
    hpbpb_anaBin_JetComb_reco[i] = new TH1F(Form("hpbpb_anaBin_JetComb_reco_R%d_%s_cent%d",radius,etaWidth,i),Form("reco jtpt from HLT trigger combined R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),nbins_pt, boundaries_pt);
    hpbpb_anaBin_Jet80_gen[i] = new TH1F(Form("hpbpb_anaBin_Jet80_gen_R%d_%s_cent%d",radius,etaWidth,i),Form("Gen refpt from Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),nbins_pt, boundaries_pt);
    hpbpb_anaBin_Jet80_reco[i] = new TH1F(Form("hpbpb_anaBin_Jet80_reco_R%d_%s_cent%d",radius,etaWidth,i),Form("reco jtpt from Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),nbins_pt, boundaries_pt);
    hpbpb_anaBin_Jet65_gen[i] = new TH1F(Form("hpbpb_anaBin_Jet65_gen_R%d_%s_cent%d",radius,etaWidth,i),Form("Gen refpt from Jet65 && !Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),nbins_pt, boundaries_pt);
    hpbpb_anaBin_Jet65_reco[i] = new TH1F(Form("hpbpb_anaBin_Jet65_reco_R%d_%s_cent%d",radius,etaWidth,i),Form("reco jtpt from Jet65 && !Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),nbins_pt, boundaries_pt);
    hpbpb_anaBin_Jet55_gen[i] = new TH1F(Form("hpbpb_anaBin_Jet55_gen_R%d_%s_cent%d",radius,etaWidth,i),Form("Gen refpt from Jet55 && !Jet65 && !Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),nbins_pt, boundaries_pt);
    hpbpb_anaBin_Jet55_reco[i] = new TH1F(Form("hpbpb_anaBin_Jet55_reco_R%d_%s_cent%d",radius,etaWidth,i),Form("reco jtpt from Jet55 && !Jet65 && !Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),nbins_pt, boundaries_pt);

    
	
  }// centrality bin loop
  


  // Define all the histograms necessary for the analysis: 
  
  // 1 - Data, 2 - MC
  Float_t pfpt_1[1000], pfpt_2[1000];
  Float_t pfrefpt_2[1000];
  Float_t calopt_1[1000], calopt_2[1000];
  Int_t npf_1, npf_2;
  Int_t isCaloMatch_1[1000], isCaloMatch_2[1000]; 
  Float_t eMax_1[1000], eMax_2[1000];
  Float_t chMax_1[1000], chMax_2[1000];
  Float_t chSum_1[1000], chSum_2[1000];
  Float_t phSum_1[1000], phSum_2[1000];
  Float_t neSum_1[1000], neSum_2[1000];
  Float_t muSum_1[1000], muSum_2[1000];
  Float_t phMax_1[1000], phMax_2[1000];
  Float_t neMax_1[1000], neMax_2[1000];
  Float_t muMax_1[1000], muMax_2[1000];
  Float_t trkMax_1[1000], trkMax_2[1000];
  Int_t jet55_1, jet65_1, jet80_1;
  Int_t jet55_p_1, jet65_p_1, jet80_p_1;
  Int_t jet55_2, jet65_2, jet80_2;
  Int_t jet55_p_2;
  Float_t pthat_2;
  Double_t weight;
  Int_t subid_2[1000];
  Int_t hiBin_1, hiBin_2;
  Float_t eta_1[1000], eta_2[1000];
  Float_t pfrawpt_1[1000], pfrawpt_2[1000]; 
  Int_t nref_2;
  Int_t pfrefidx_2[1000]; //! REF -> PF match index
  Float_t refdrjt_2[1000];

  Int_t jetid_1[1000], jetid_2[1000];

  Data_JetID->SetBranchAddress("jetid", &jetid_1);
  Data_matched->SetBranchAddress("npf", &npf_1);
  Data_matched->SetBranchAddress("isCaloMatch", &isCaloMatch_1);
  Data_matched->SetBranchAddress("calopt",&calopt_1);
  Data_matched->SetBranchAddress("pfpt",&pfpt_1);
  Data_matched->SetBranchAddress("eMax",&eMax_1);
  Data_matched->SetBranchAddress("chMax",&chMax_1);
  Data_matched->SetBranchAddress("chSum",&chSum_1);
  Data_matched->SetBranchAddress("phMax",&phMax_1);
  Data_matched->SetBranchAddress("neMax",&neMax_1);
  Data_matched->SetBranchAddress("muMax",&muMax_1);
  Data_matched->SetBranchAddress("trMax",&trkMax_1);
  Data_matched->SetBranchAddress("phSum",&phSum_1);
  Data_matched->SetBranchAddress("neSum",&neSum_1);
  Data_matched->SetBranchAddress("muSum",&muSum_1);
  Data_matched->SetBranchAddress("hiBin",&hiBin_1);
  Data_matched->SetBranchAddress("jet55",&jet55_1);
  Data_matched->SetBranchAddress("jet65",&jet65_1);
  Data_matched->SetBranchAddress("jet80",&jet80_1);
  Data_matched->SetBranchAddress("jet55_prescl",&jet55_p_1);
  Data_matched->SetBranchAddress("jet65_prescl",&jet65_p_1);
  Data_matched->SetBranchAddress("jet80_prescl",&jet80_p_1);
  Data_matched->SetBranchAddress("pfeta",&eta_1);
  Data_matched->SetBranchAddress("pfrawpt",&pfrawpt_1);
 
  MC_JetID->SetBranchAddress("jetid", &jetid_2);
  MC_matched->SetBranchAddress("npf", &npf_2);
  MC_matched->SetBranchAddress("nref", &nref_2);
  MC_matched->SetBranchAddress("pfrefidx",&pfrefidx_2);
  MC_matched->SetBranchAddress("refdrjt",&refdrjt_2);
  MC_matched->SetBranchAddress("pthat", &pthat_2);
  MC_matched->SetBranchAddress("isCaloMatch", &isCaloMatch_2);
  MC_matched->SetBranchAddress("calopt",&calopt_2);
  MC_matched->SetBranchAddress("pfpt",&pfpt_2);
  MC_matched->SetBranchAddress("eMax",&eMax_2);
  MC_matched->SetBranchAddress("chMax",&chMax_2);
  MC_matched->SetBranchAddress("trMax",&trkMax_2);
  MC_matched->SetBranchAddress("chSum",&chSum_2);
  MC_matched->SetBranchAddress("phMax",&phMax_2);
  MC_matched->SetBranchAddress("neMax",&neMax_2);
  MC_matched->SetBranchAddress("muMax",&muMax_2);
  MC_matched->SetBranchAddress("phSum",&phSum_2);
  MC_matched->SetBranchAddress("neSum",&neSum_2);
  MC_matched->SetBranchAddress("muSum",&muSum_2);
  MC_matched->SetBranchAddress("hiBin",&hiBin_2);
  MC_matched->SetBranchAddress("refpt",&pfrefpt_2);
  MC_matched->SetBranchAddress("jet55",&jet55_2);
  MC_matched->SetBranchAddress("jet65",&jet65_2);
  MC_matched->SetBranchAddress("jet80",&jet80_2);
  MC_matched->SetBranchAddress("weight", &weight);
  MC_matched->SetBranchAddress("subid", &subid_2);
  MC_matched->SetBranchAddress("jet55_prescl",&jet55_p_2);
  MC_matched->SetBranchAddress("pfeta",&eta_2);
  MC_matched->SetBranchAddress("pfrawpt",&pfrawpt_2);

  
  // data loop
  long entries = Data_matched->GetEntries();
  //entries = 1000;
  Float_t Jet55_prescl = 2.0475;

  // get the random value for smear systematics, TRandom rnd, value per jet = rnd.Gaus(0,1);
  TRandom rnd; 
  TH1F * htest = new TH1F("htest","",nbins_pt, boundaries_pt);

  cout<<"matched Data ntuple "<<endl;

  for(long nentry = 0; nentry < entries; ++nentry ){

    if(nentry%100000 == 0) cout<<nentry<<"/"<<entries<<endl;
    Data_matched->GetEntry(nentry);

    Int_t cBin = findBin(hiBin_1);
    if(cBin == -1 || cBin >= nbins_cent) continue;

    if(jet55_1 == 1) jet55_counter++;
    if(jet65_1 == 1) jet65_counter++;
    if(jet80_1 == 1) jet80_counter++;

    // if(jet55_counter%100000 == 0) cout<<"read "<<jet55_counter<<" jet55 events"<<endl;
    // if(jet65_counter%100000 == 0) cout<<"read "<<jet65_counter<<" jet65 events"<<endl;
    // if(jet80_counter%100000 == 0) cout<<"read "<<jet80_counter<<" jet80 events"<<endl;

    // you can also have a selection on the number of events passed by the Jet 55 sample in the if condition below. 
    
    double wght = 1;
    
    for(int g = 0; g<npf_1; ++g){ // jet loop

      if(isSymm && TMath::Abs(eta_1[g]) > (Float_t)etaHigh/10) continue;       
      if(!isSymm && (TMath::Abs(eta_1[g]) < (Float_t)etaLow/10 || TMath::Abs(eta_1[g]) > (Float_t)etaHigh/10)) continue;
   
      if(jet55_1 == 1 && jet65_1 == 0 && jet80_1 == 0 && jetid_1[g] == 1){
	hpbpb_TrgObj55[cBin]->Fill(pfpt_1[g], Jet55_prescl* wght);
	hpbpb_raw_TrgObj55[cBin]->Fill(pfrawpt_1[g], Jet55_prescl* wght);
	hpbpb_anaBin_TrgObj55[cBin]->Fill(pfpt_1[g], Jet55_prescl* wght);
	hpbpb_JEC_TrgObj55[cBin]->Fill(pfpt_1[g] * (1. + 0.02/nbins_cent*(nbins_cent-cBin)), Jet55_prescl* wght);
	hpbpb_Smear_TrgObj55[cBin]->Fill(pfpt_1[g] + rnd.Gaus(0,1), Jet55_prescl* wght);
      }

      if(jet65_1 == 1 && jet80_1 == 0 && jetid_1[g] == 1){
	hpbpb_TrgObj65[cBin]->Fill(pfpt_1[g], wght);
	hpbpb_raw_TrgObj65[cBin]->Fill(pfrawpt_1[g], wght);
	hpbpb_anaBin_TrgObj65[cBin]->Fill(pfpt_1[g], wght);
	hpbpb_JEC_TrgObj65[cBin]->Fill(pfpt_1[g] * (1. + 0.02/nbins_cent*(nbins_cent-cBin)), wght);
	hpbpb_Smear_TrgObj65[cBin]->Fill(pfpt_1[g] + rnd.Gaus(0,1), wght);
      }
      
      if(jet80_1 == 1 && jetid_1[g] == 1){
	hpbpb_TrgObj80[cBin]->Fill(pfpt_1[g], wght);
	hpbpb_raw_TrgObj80[cBin]->Fill(pfrawpt_1[g], wght);
	hpbpb_anaBin_TrgObj80[cBin]->Fill(pfpt_1[g], wght);
	hpbpb_JEC_TrgObj80[cBin]->Fill(pfpt_1[g] * (1. + 0.02/nbins_cent*(nbins_cent-cBin)), wght);
	hpbpb_Smear_TrgObj80[cBin]->Fill(pfpt_1[g] + rnd.Gaus(0,1), wght);
      }
    
    }// jet loop  
    
  }// data ntuple loop

  
  entries = MC_matched->GetEntries();
  //entries = 1000;
  // MC loop      

  cout<<" looking at matched MC ntuple "<<endl;
  for(long nentry = 0; nentry < entries; ++nentry){

    if(nentry%100000 == 0) cout<<nentry<<"/"<<entries<<endl;
    MC_matched->GetEntry(nentry);
    
    Int_t cBin = findBin(hiBin_2);
    if(cBin == -1 || cBin >= nbins_cent) continue;    
    
    for(int g = 0; g<npf_2; ++g){
    
      int refid = -1; 
      
      if(pfpt_2[g] > 2 * pthat_2) continue;
      refid = pfrefidx_2[g];
      if(subid_2[refid] != 0 || fabs(refdrjt_2[refid]) > kdelrcut) continue;
      if(refid < 0) continue;
      
      if(isSymm && TMath::Abs(eta_2[g]) > (Float_t)etaHigh/10) continue;       
      if(!isSymm && (TMath::Abs(eta_2[g]) < (Float_t)etaLow/10 || TMath::Abs(eta_2[g]) > (Float_t)etaHigh/10)) continue;

      // apply the jet iD cut
      if(jetid_2[g] == 1){
	
	hpbpb_gen[cBin]->Fill(pfrefpt_2[refid], weight);
	hpbpb_reco[cBin]->Fill(pfpt_2[g], weight);
	hpbpb_matrix[cBin]->Fill(pfrefpt_2[refid], pfpt_2[g], weight);

	if(nentry%2==0){
	  hpbpb_mcclosure_data[cBin]->Fill(pfpt_2[g], weight);
	}else {
	  hpbpb_mcclosure_matrix[cBin]->Fill(pfrefpt_2[refid], pfpt_2[g], weight);
	  hpbpb_mcclosure_gen[cBin]->Fill(pfrefpt_2[refid], weight);
	  hpbpb_mcclosure_data_train[cBin]->Fill(pfpt_2[g], weight);
	}

	if(jet55_2 == 1 && jet65_2==0 && jet80_2 == 0){
	  hpbpb_Jet55_gen[cBin]->Fill(pfrefpt_2[refid], weight);
	  hpbpb_Jet55_GenSmear[cBin]->Fill(pfrefpt_2[refid] + rnd.Gaus(0,1), weight);
	  hpbpb_Jet55_gen2pSmear[cBin]->Fill(pfrefpt_2[refid] * (1. + 0.02/nbins_cent*(nbins_cent-cBin)), weight);
	  hpbpb_Jet55_gen_5TrigIneff_Smear[cBin]->Fill(pfrefpt_2[refid] * (1. + 0.05/nbins_cent*(nbins_cent-cBin)), weight);
	  hpbpb_Jet55_gen_10TrigIneff_Smear[cBin]->Fill(pfrefpt_2[refid] * (1. + 0.10/nbins_cent*(nbins_cent-cBin)), weight);
	  hpbpb_Jet55_reco_5TrigIneff_Smear[cBin]->Fill(pfpt_2[g] * (1. + 0.05/nbins_cent*(nbins_cent-cBin)), weight);
	  hpbpb_Jet55_reco_10TrigIneff_Smear[cBin]->Fill(pfpt_2[g] * (1. + 0.10/nbins_cent*(nbins_cent-cBin)), weight);
	  hpbpb_matrix_HLT_5TrigIneff_Smear[cBin]->Fill(pfrefpt_2[refid] * (1. + 0.05/nbins_cent*(nbins_cent-cBin)), pfpt_2[g] * (1. + 0.05/nbins_cent*(nbins_cent-cBin)), weight);
	  hpbpb_matrix_HLT_10TrigIneff_Smear[cBin]->Fill(pfrefpt_2[refid] * (1. + 0.1/nbins_cent*(nbins_cent-cBin)), pfpt_2[g] * (1. + 0.1/nbins_cent*(nbins_cent-cBin)), weight);


	  hpbpb_matrix_HLT_gen2pSmear[cBin]->Fill(pfrefpt_2[refid] * (1. + 0.02/nbins_cent*(nbins_cent-cBin)), pfpt_2[g], weight);

	  hpbpb_Jet55_reco[cBin]->Fill(pfpt_2[g], weight);
	  hpbpb_Jet55_RecoSmear[cBin]->Fill(pfpt_2[g] + rnd.Gaus(0,1), weight);
	  hpbpb_Jet55_raw[cBin]->Fill(pfrawpt_2[g], weight);
	  hpbpb_matrix_HLT[cBin]->Fill(pfrefpt_2[refid], pfpt_2[g], weight);
	  hpbpb_Trans_matrix_HLT[cBin]->Fill( pfpt_2[g],pfrefpt_2[refid], weight);
	  hpbpb_matrix_HLT_GenSmear[cBin]->Fill(pfrefpt_2[refid] + rnd.Gaus(0,1), pfpt_2[g], weight);
	  hpbpb_matrix_HLT_RecoSmear[cBin]->Fill(pfrefpt_2[refid], pfpt_2[g] + rnd.Gaus(0,1), weight);
	  hpbpb_matrix_HLT_BothSmear[cBin]->Fill(pfrefpt_2[refid] + rnd.Gaus(0,1), pfpt_2[g] + rnd.Gaus(0,1), weight);
	
	  hpbpb_anaBin_Jet55_gen[cBin]->Fill(pfrefpt_2[refid], weight);
	  hpbpb_anaBin_Jet55_reco[cBin]->Fill(pfpt_2[g], weight);
	  hpbpb_anaBin_matrix_HLT[cBin]->Fill(pfrefpt_2[refid], pfpt_2[g], weight);
	  hpbpb_anaBin_Trans_matrix_HLT[cBin]->Fill( pfpt_2[g],pfrefpt_2[refid], weight);

	  if(nentry%2==0){
	    hpbpb_mcclosure_Jet55_data_5TrigIneff_Smear[cBin]->Fill(pfpt_2[g]* (1. + 0.5/nbins_cent*(nbins_cent-cBin)), weight);
	    hpbpb_mcclosure_Jet55_data_10TrigIneff_Smear[cBin]->Fill(pfpt_2[g]* (1. + 0.1/nbins_cent*(nbins_cent-cBin)), weight);
	    hpbpb_mcclosure_Jet55_data[cBin]->Fill(pfpt_2[g], weight);
	  }else {
	    hpbpb_mcclosure_matrix_HLT_5TrigIneff_Smear[cBin]->Fill(pfrefpt_2[refid] * (1. + 0.05/nbins_cent*(nbins_cent-cBin)), pfpt_2[g] * (1. + 0.05/nbins_cent*(nbins_cent-cBin)), weight);
	    hpbpb_mcclosure_matrix_HLT_10TrigIneff_Smear[cBin]->Fill(pfrefpt_2[refid] * (1. + 0.1/nbins_cent*(nbins_cent-cBin)), pfpt_2[g] * (1. + 0.1/nbins_cent*(nbins_cent-cBin)), weight);
	    hpbpb_mcclosure_matrix_HLT[cBin]->Fill(pfrefpt_2[refid], pfpt_2[g], weight);
	    hpbpb_mcclosure_Jet55_gen_5TrigIneff_Smear[cBin]->Fill(pfrefpt_2[refid]* (1. + 0.05/nbins_cent*(nbins_cent-cBin)), weight);
	    hpbpb_mcclosure_Jet55_gen_10TrigIneff_Smear[cBin]->Fill(pfrefpt_2[refid]* (1. + 0.1/nbins_cent*(nbins_cent-cBin)), weight);
	    hpbpb_mcclosure_Jet55_data_train[cBin]->Fill(pfpt_2[g], weight);
	  }
	
	
	}// jet55 selection

	if(jet65_2 == 1 && jet80_2 == 0){
	  hpbpb_Jet65_gen[cBin]->Fill(pfrefpt_2[refid], weight);
	  hpbpb_Jet65_GenSmear[cBin]->Fill(pfrefpt_2[refid] + rnd.Gaus(0,1), weight);
	  hpbpb_Jet65_gen2pSmear[cBin]->Fill(pfrefpt_2[refid] * (1. + 0.02/nbins_cent*(nbins_cent-cBin)), weight);
	  hpbpb_matrix_HLT_5TrigIneff_Smear[cBin]->Fill(pfrefpt_2[refid] * (1. + 0.05/nbins_cent*(nbins_cent-cBin)), pfpt_2[g] * (1. + 0.05/nbins_cent*(nbins_cent-cBin)), weight);
	  hpbpb_matrix_HLT_10TrigIneff_Smear[cBin]->Fill(pfrefpt_2[refid] * (1. + 0.1/nbins_cent*(nbins_cent-cBin)), pfpt_2[g] * (1. + 0.1/nbins_cent*(nbins_cent-cBin)), weight);


	  hpbpb_matrix_HLT_gen2pSmear[cBin]->Fill(pfrefpt_2[refid] * (1. + 0.02/nbins_cent*(nbins_cent-cBin)), pfpt_2[g], weight);

	  hpbpb_Jet65_reco[cBin]->Fill(pfpt_2[g], weight);
	  hpbpb_Jet65_RecoSmear[cBin]->Fill(pfpt_2[g] + rnd.Gaus(0,1), weight);
	  hpbpb_Jet65_raw[cBin]->Fill(pfrawpt_2[g], weight);
	  hpbpb_matrix_HLT[cBin]->Fill(pfrefpt_2[refid], pfpt_2[g], weight);
	  hpbpb_Trans_matrix_HLT[cBin]->Fill( pfpt_2[g],pfrefpt_2[refid], weight);
	  hpbpb_matrix_HLT_GenSmear[cBin]->Fill(pfrefpt_2[refid] + rnd.Gaus(0,1), pfpt_2[g], weight);
	  hpbpb_matrix_HLT_RecoSmear[cBin]->Fill(pfrefpt_2[refid], pfpt_2[g] + rnd.Gaus(0,1), weight);
	  hpbpb_matrix_HLT_BothSmear[cBin]->Fill(pfrefpt_2[refid] + rnd.Gaus(0,1), pfpt_2[g] + rnd.Gaus(0,1), weight);
	
	  hpbpb_anaBin_Jet65_gen[cBin]->Fill(pfrefpt_2[refid], weight);
	  hpbpb_anaBin_Jet65_reco[cBin]->Fill(pfpt_2[g], weight);
	  hpbpb_anaBin_matrix_HLT[cBin]->Fill(pfrefpt_2[refid], pfpt_2[g], weight);
	  hpbpb_anaBin_Trans_matrix_HLT[cBin]->Fill( pfpt_2[g],pfrefpt_2[refid], weight);

	  if(nentry%2==0){
	    hpbpb_mcclosure_Jet65_data[cBin]->Fill(pfpt_2[g], weight);
	  }else {
	    hpbpb_mcclosure_matrix_HLT_5TrigIneff_Smear[cBin]->Fill(pfrefpt_2[refid] * (1. + 0.05/nbins_cent*(nbins_cent-cBin)), pfpt_2[g] * (1. + 0.05/nbins_cent*(nbins_cent-cBin)), weight);
	    hpbpb_mcclosure_matrix_HLT_10TrigIneff_Smear[cBin]->Fill(pfrefpt_2[refid] * (1. + 0.1/nbins_cent*(nbins_cent-cBin)), pfpt_2[g] * (1. + 0.1/nbins_cent*(nbins_cent-cBin)), weight);
	    hpbpb_mcclosure_matrix_HLT[cBin]->Fill(pfrefpt_2[refid], pfpt_2[g], weight);
	    hpbpb_mcclosure_Jet65_data_train[cBin]->Fill(pfpt_2[g], weight);
	  }
	
	}// jet65 selection

	if(jet80_2 == 1){
	  hpbpb_Jet80_gen[cBin]->Fill(pfrefpt_2[refid], weight);
	  hpbpb_Jet80_GenSmear[cBin]->Fill(pfrefpt_2[refid] + rnd.Gaus(0,1), weight);
	  hpbpb_Jet80_gen2pSmear[cBin]->Fill(pfrefpt_2[refid] * (1. + 0.02/nbins_cent*(nbins_cent-cBin)), weight);
	  hpbpb_matrix_HLT_5TrigIneff_Smear[cBin]->Fill(pfrefpt_2[refid] * (1. + 0.05/nbins_cent*(nbins_cent-cBin)), pfpt_2[g] * (1. + 0.05/nbins_cent*(nbins_cent-cBin)), weight);
	  hpbpb_matrix_HLT_10TrigIneff_Smear[cBin]->Fill(pfrefpt_2[refid] * (1. + 0.1/nbins_cent*(nbins_cent-cBin)), pfpt_2[g] * (1. + 0.1/nbins_cent*(nbins_cent-cBin)), weight);


	  hpbpb_matrix_HLT_gen2pSmear[cBin]->Fill(pfrefpt_2[refid] * (1. + 0.02/nbins_cent*(nbins_cent-cBin)), pfpt_2[g], weight);

	  hpbpb_Jet80_reco[cBin]->Fill(pfpt_2[g], weight);
	  hpbpb_Jet80_RecoSmear[cBin]->Fill(pfpt_2[g] + rnd.Gaus(0,1), weight);
	  hpbpb_Jet80_raw[cBin]->Fill(pfrawpt_2[g], weight);
	  hpbpb_matrix_HLT[cBin]->Fill(pfrefpt_2[refid], pfpt_2[g], weight);
	  hpbpb_Trans_matrix_HLT[cBin]->Fill( pfpt_2[g],pfrefpt_2[refid], weight);
	  hpbpb_matrix_HLT_GenSmear[cBin]->Fill(pfrefpt_2[refid] + rnd.Gaus(0,1), pfpt_2[g], weight);
	  hpbpb_matrix_HLT_RecoSmear[cBin]->Fill(pfrefpt_2[refid], pfpt_2[g] + rnd.Gaus(0,1), weight);
	  hpbpb_matrix_HLT_BothSmear[cBin]->Fill(pfrefpt_2[refid] + rnd.Gaus(0,1), pfpt_2[g] + rnd.Gaus(0,1), weight);
	
	  hpbpb_anaBin_Jet80_gen[cBin]->Fill(pfrefpt_2[refid], weight);
	  hpbpb_anaBin_Jet80_reco[cBin]->Fill(pfpt_2[g], weight);
	  hpbpb_anaBin_matrix_HLT[cBin]->Fill(pfrefpt_2[refid], pfpt_2[g], weight);
	  hpbpb_anaBin_Trans_matrix_HLT[cBin]->Fill( pfpt_2[g],pfrefpt_2[refid], weight);

	  if(nentry%2==0){
	    hpbpb_mcclosure_Jet80_data[cBin]->Fill(pfpt_2[g], weight);
	  }else {
	    hpbpb_mcclosure_matrix_HLT_5TrigIneff_Smear[cBin]->Fill(pfrefpt_2[refid] * (1. + 0.05/nbins_cent*(nbins_cent-cBin)), pfpt_2[g] * (1. + 0.05/nbins_cent*(nbins_cent-cBin)), weight);
	    hpbpb_mcclosure_matrix_HLT_10TrigIneff_Smear[cBin]->Fill(pfrefpt_2[refid] * (1. + 0.1/nbins_cent*(nbins_cent-cBin)), pfpt_2[g] * (1. + 0.1/nbins_cent*(nbins_cent-cBin)), weight);
	    hpbpb_mcclosure_matrix_HLT[cBin]->Fill(pfrefpt_2[refid], pfpt_2[g], weight);
	    hpbpb_mcclosure_Jet80_data_train[cBin]->Fill(pfpt_2[g], weight);
	  }
	
	}// jet80 selection

      }// jet ID selection
    }// jet loop
    
  }// mc ntuple loop


  // cout<<"Number of events that passed Jet 55 = "<<jet55_counter<<endl;
  // cout<<"Number of events that passed Jet 65 = "<<jet65_counter<<endl;

  TFile fout(Form("/export/d00/scratch/rkunnawa/rootfiles/RAA/%s_TTree_PbPb_Data_MC_newflagtest_subid0_spectra_JetID_CutA_%s_%s_R0p%d.root",ntuple, ptbins, etaWidth, radius),"RECREATE");
  fout.cd();
  
  for(int i = 0;i<nbins_cent;++i){

    hpbpb_Data_Comb_noCut[i]->Add(hpbpb_Data_Jet80_noCut[i]);
    hpbpb_Data_Comb_noCut[i]->Add(hpbpb_Data_Jet65_noCut[i]);
    hpbpb_Data_Comb_noCut[i]->Add(hpbpb_Data_Jet55_noCut[i]);

    // hpbpb_TrgObj80[i]->Scale(1./4/1e8/(1+0.898+0.494));
    // hpbpb_TrgObj65[i]->Scale(1./2.93/1e8/(1+0.898+0.494));
    // hpbpb_TrgObj55[i]->Scale(1./2.52/1e8/(1+0.898+0.494));
    
    hpbpb_TrgObjComb[i]->Add(hpbpb_TrgObj80[i]);
    hpbpb_TrgObjComb[i]->Add(hpbpb_TrgObj65[i]);
    hpbpb_TrgObjComb[i]->Add(hpbpb_TrgObj55[i]);
    
    divideBinWidth(hpbpb_TrgObjComb[i]);
    divideBinWidth(hpbpb_TrgObj80[i]);
    divideBinWidth(hpbpb_TrgObj65[i]);
    divideBinWidth(hpbpb_TrgObj55[i]);

    hpbpb_raw_TrgObjComb[i]->Add(hpbpb_raw_TrgObj80[i]);
    hpbpb_raw_TrgObjComb[i]->Add(hpbpb_raw_TrgObj65[i]);
    hpbpb_raw_TrgObjComb[i]->Add(hpbpb_raw_TrgObj55[i]);

    divideBinWidth(hpbpb_raw_TrgObjComb[i]);
    divideBinWidth(hpbpb_raw_TrgObj80[i]);
    divideBinWidth(hpbpb_raw_TrgObj65[i]);
    divideBinWidth(hpbpb_raw_TrgObj55[i]);

    hpbpb_anaBin_TrgObjComb[i]->Add(hpbpb_anaBin_TrgObj80[i]);
    hpbpb_anaBin_TrgObjComb[i]->Add(hpbpb_anaBin_TrgObj65[i]);
    hpbpb_anaBin_TrgObjComb[i]->Add(hpbpb_anaBin_TrgObj55[i]);

    divideBinWidth(hpbpb_anaBin_TrgObjComb[i]);
    divideBinWidth(hpbpb_anaBin_TrgObj80[i]);
    divideBinWidth(hpbpb_anaBin_TrgObj65[i]);
    divideBinWidth(hpbpb_anaBin_TrgObj55[i]);

    hpbpb_Smear_TrgObjComb[i]->Add(hpbpb_Smear_TrgObj80[i]);
    hpbpb_Smear_TrgObjComb[i]->Add(hpbpb_Smear_TrgObj65[i]);
    hpbpb_Smear_TrgObjComb[i]->Add(hpbpb_Smear_TrgObj55[i]);

    divideBinWidth(hpbpb_Smear_TrgObjComb[i]);

    hpbpb_JEC_TrgObjComb[i]->Add(hpbpb_JEC_TrgObj80[i]);
    hpbpb_JEC_TrgObjComb[i]->Add(hpbpb_JEC_TrgObj65[i]);
    hpbpb_JEC_TrgObjComb[i]->Add(hpbpb_JEC_TrgObj55[i]);

    divideBinWidth(hpbpb_JEC_TrgObjComb[i]);
    
    hpbpb_mcclosure_JetComb_data[i]->Add(hpbpb_mcclosure_Jet80_data[i]);
    hpbpb_mcclosure_JetComb_data[i]->Add(hpbpb_mcclosure_Jet65_data[i]);
    hpbpb_mcclosure_JetComb_data[i]->Add(hpbpb_mcclosure_Jet55_data[i]);

    divideBinWidth(hpbpb_mcclosure_JetComb_data[i]);
    
    hpbpb_mcclosure_JetComb_data_5TrigIneff_Smear[i]->Add(hpbpb_mcclosure_Jet80_data[i]);
    hpbpb_mcclosure_JetComb_data_5TrigIneff_Smear[i]->Add(hpbpb_mcclosure_Jet65_data[i]);
    hpbpb_mcclosure_JetComb_data_5TrigIneff_Smear[i]->Add(hpbpb_mcclosure_Jet55_data_5TrigIneff_Smear[i]);

    divideBinWidth(hpbpb_mcclosure_JetComb_data_5TrigIneff_Smear[i]);

    hpbpb_mcclosure_JetComb_data_10TrigIneff_Smear[i]->Add(hpbpb_mcclosure_Jet80_data[i]);
    hpbpb_mcclosure_JetComb_data_10TrigIneff_Smear[i]->Add(hpbpb_mcclosure_Jet65_data[i]);
    hpbpb_mcclosure_JetComb_data_10TrigIneff_Smear[i]->Add(hpbpb_mcclosure_Jet55_data_10TrigIneff_Smear[i]);

    divideBinWidth(hpbpb_mcclosure_JetComb_data_10TrigIneff_Smear[i]);
    
    hpbpb_mcclosure_JetComb_data_train[i]->Add(hpbpb_mcclosure_Jet80_data_train[i]);
    hpbpb_mcclosure_JetComb_data_train[i]->Add(hpbpb_mcclosure_Jet65_data_train[i]);
    hpbpb_mcclosure_JetComb_data_train[i]->Add(hpbpb_mcclosure_Jet55_data_train[i]);

    divideBinWidth(hpbpb_mcclosure_JetComb_data_train[i]);
    
    hpbpb_mcclosure_JetComb_gen[i]->Add(hpbpb_mcclosure_Jet80_gen[i]);
    hpbpb_mcclosure_JetComb_gen[i]->Add(hpbpb_mcclosure_Jet65_gen[i]);
    hpbpb_mcclosure_JetComb_gen[i]->Add(hpbpb_mcclosure_Jet55_gen[i]);

    divideBinWidth(hpbpb_mcclosure_JetComb_gen[i]);

    hpbpb_mcclosure_JetComb_gen_10TrigIneff_Smear[i]->Add(hpbpb_mcclosure_Jet80_gen[i]);
    hpbpb_mcclosure_JetComb_gen_10TrigIneff_Smear[i]->Add(hpbpb_mcclosure_Jet65_gen[i]);
    hpbpb_mcclosure_JetComb_gen_10TrigIneff_Smear[i]->Add(hpbpb_mcclosure_Jet55_gen_10TrigIneff_Smear[i]);

    divideBinWidth(hpbpb_mcclosure_JetComb_gen_10TrigIneff_Smear[i]);

    hpbpb_mcclosure_JetComb_gen_5TrigIneff_Smear[i]->Add(hpbpb_mcclosure_Jet80_gen[i]);
    hpbpb_mcclosure_JetComb_gen_5TrigIneff_Smear[i]->Add(hpbpb_mcclosure_Jet65_gen[i]);
    hpbpb_mcclosure_JetComb_gen_5TrigIneff_Smear[i]->Add(hpbpb_mcclosure_Jet55_gen_5TrigIneff_Smear[i]);

    divideBinWidth(hpbpb_mcclosure_JetComb_gen_5TrigIneff_Smear[i]);

    
    hpbpb_JetComb_reco[i]->Add(hpbpb_Jet80_reco[i]);
    hpbpb_JetComb_reco[i]->Add(hpbpb_Jet65_reco[i]);
    hpbpb_JetComb_reco[i]->Add(hpbpb_Jet55_reco[i]);

    hpbpb_JetComb_reco_5TrigIneff_Smear[i]->Add(hpbpb_Jet80_reco[i]);
    hpbpb_JetComb_reco_5TrigIneff_Smear[i]->Add(hpbpb_Jet65_reco[i]);
    hpbpb_JetComb_reco_5TrigIneff_Smear[i]->Add(hpbpb_Jet55_reco_5TrigIneff_Smear[i]);

    hpbpb_JetComb_gen_5TrigIneff_Smear[i]->Add(hpbpb_Jet80_gen[i]);
    hpbpb_JetComb_gen_5TrigIneff_Smear[i]->Add(hpbpb_Jet65_gen[i]);
    hpbpb_JetComb_gen_5TrigIneff_Smear[i]->Add(hpbpb_Jet55_gen_5TrigIneff_Smear[i]);

    hpbpb_JetComb_reco_10TrigIneff_Smear[i]->Add(hpbpb_Jet80_reco[i]);
    hpbpb_JetComb_reco_10TrigIneff_Smear[i]->Add(hpbpb_Jet65_reco[i]);
    hpbpb_JetComb_reco_10TrigIneff_Smear[i]->Add(hpbpb_Jet55_reco_10TrigIneff_Smear[i]);

    hpbpb_JetComb_gen_10TrigIneff_Smear[i]->Add(hpbpb_Jet80_gen[i]);
    hpbpb_JetComb_gen_10TrigIneff_Smear[i]->Add(hpbpb_Jet65_gen[i]);
    hpbpb_JetComb_gen_10TrigIneff_Smear[i]->Add(hpbpb_Jet55_gen_10TrigIneff_Smear[i]);

    hpbpb_JetComb_RecoSmear[i]->Add(hpbpb_Jet80_RecoSmear[i]);
    hpbpb_JetComb_RecoSmear[i]->Add(hpbpb_Jet65_RecoSmear[i]);
    hpbpb_JetComb_RecoSmear[i]->Add(hpbpb_Jet55_RecoSmear[i]);
    
    hpbpb_JetComb_raw[i]->Add(hpbpb_Jet80_raw[i]);
    hpbpb_JetComb_raw[i]->Add(hpbpb_Jet65_raw[i]);
    hpbpb_JetComb_raw[i]->Add(hpbpb_Jet55_raw[i]);

    hpbpb_JetComb_GenSmear[i]->Add(hpbpb_Jet80_GenSmear[i]);
    hpbpb_JetComb_GenSmear[i]->Add(hpbpb_Jet65_GenSmear[i]);
    hpbpb_JetComb_GenSmear[i]->Add(hpbpb_Jet55_GenSmear[i]);

    hpbpb_JetComb_gen2pSmear[i]->Add(hpbpb_Jet80_gen2pSmear[i]);
    hpbpb_JetComb_gen2pSmear[i]->Add(hpbpb_Jet65_gen2pSmear[i]);
    hpbpb_JetComb_gen2pSmear[i]->Add(hpbpb_Jet55_gen2pSmear[i]);
    
    hpbpb_JetComb_gen[i]->Add(hpbpb_Jet80_gen[i]);
    hpbpb_JetComb_gen[i]->Add(hpbpb_Jet65_gen[i]);
    hpbpb_JetComb_gen[i]->Add(hpbpb_Jet55_gen[i]);

    divideBinWidth(hpbpb_JetComb_gen[i]);
    divideBinWidth(hpbpb_JetComb_reco[i]);

    divideBinWidth(hpbpb_JetComb_GenSmear[i]);
    divideBinWidth(hpbpb_JetComb_gen2pSmear[i]);
    divideBinWidth(hpbpb_JetComb_RecoSmear[i]);
    
    divideBinWidth(hpbpb_JetComb_raw[i]);
    divideBinWidth(hpbpb_reco[i]);
    divideBinWidth(hpbpb_gen[i]);

    hpbpb_anaBin_JetComb_reco[i]->Add(hpbpb_anaBin_Jet80_reco[i]);
    hpbpb_anaBin_JetComb_reco[i]->Add(hpbpb_anaBin_Jet65_reco[i]);
    hpbpb_anaBin_JetComb_reco[i]->Add(hpbpb_anaBin_Jet55_reco[i]);
    
    hpbpb_anaBin_JetComb_gen[i]->Add(hpbpb_anaBin_Jet80_gen[i]);
    hpbpb_anaBin_JetComb_gen[i]->Add(hpbpb_anaBin_Jet65_gen[i]);
    hpbpb_anaBin_JetComb_gen[i]->Add(hpbpb_anaBin_Jet55_gen[i]);

    divideBinWidth(hpbpb_anaBin_JetComb_gen[i]);
    divideBinWidth(hpbpb_anaBin_JetComb_reco[i]);
  
  }



  for(int i = 0; i<nbins_cent;++i){

    hpbpb_TrgObjComb[i]->Write();
    hpbpb_TrgObj80[i]->Write();
    hpbpb_TrgObj65[i]->Write();
    hpbpb_TrgObj55[i]->Write();

    hpbpb_raw_TrgObjComb[i]->Write();
    hpbpb_raw_TrgObj80[i]->Write();
    hpbpb_raw_TrgObj65[i]->Write();
    hpbpb_raw_TrgObj55[i]->Write();
    
    hpbpb_anaBin_TrgObjComb[i]->Write();
    hpbpb_anaBin_TrgObj80[i]->Write();
    hpbpb_anaBin_TrgObj65[i]->Write();
    hpbpb_anaBin_TrgObj55[i]->Write();

    hpbpb_JEC_TrgObjComb[i]->Write();
    hpbpb_JEC_TrgObj80[i]->Write();
    hpbpb_JEC_TrgObj65[i]->Write();
    hpbpb_JEC_TrgObj55[i]->Write();

    hpbpb_Smear_TrgObjComb[i]->Write();
    hpbpb_Smear_TrgObj80[i]->Write();
    hpbpb_Smear_TrgObj65[i]->Write();
    hpbpb_Smear_TrgObj55[i]->Write();
    
    hpbpb_matrix_HLT[i]->Write();
    hpbpb_Trans_matrix_HLT[i]->Write();
    hpbpb_matrix_HLT_GenSmear[i]->Write();
    hpbpb_matrix_HLT_gen2pSmear[i]->Write();
    hpbpb_matrix_HLT_RecoSmear[i]->Write();
    hpbpb_matrix_HLT_BothSmear[i]->Write();
    hpbpb_anaBin_matrix_HLT[i]->Write();
    hpbpb_anaBin_Trans_matrix_HLT[i]->Write();
    hpbpb_matrix_HLT_5TrigIneff_Smear[i]->Write();
    hpbpb_matrix_HLT_10TrigIneff_Smear[i]->Write();
    
    hpbpb_mcclosure_matrix_HLT[i]->Write();
    hpbpb_mcclosure_matrix_HLT_5TrigIneff_Smear[i]->Write();
    hpbpb_mcclosure_matrix_HLT_10TrigIneff_Smear[i]->Write();
    hpbpb_mcclosure_JetComb_data[i]->Write();
    hpbpb_mcclosure_JetComb_data_5TrigIneff_Smear[i]->Write();
    hpbpb_mcclosure_JetComb_data_10TrigIneff_Smear[i]->Write();
    hpbpb_mcclosure_Jet80_data[i]->Write();
    hpbpb_mcclosure_Jet65_data[i]->Write();
    hpbpb_mcclosure_Jet55_data[i]->Write();
    hpbpb_mcclosure_Jet55_data_5TrigIneff_Smear[i]->Write();
    hpbpb_mcclosure_Jet55_data_10TrigIneff_Smear[i]->Write();
    hpbpb_mcclosure_JetComb_data_train[i]->Write();
    hpbpb_mcclosure_Jet80_data_train[i]->Write();
    hpbpb_mcclosure_Jet65_data_train[i]->Write();
    hpbpb_mcclosure_Jet55_data_train[i]->Write();
    hpbpb_mcclosure_JetComb_gen[i]->Write();    
    hpbpb_mcclosure_JetComb_gen_5TrigIneff_Smear[i]->Write();    
    hpbpb_mcclosure_JetComb_gen_10TrigIneff_Smear[i]->Write();    
    hpbpb_mcclosure_Jet80_gen[i]->Write();
    hpbpb_mcclosure_Jet65_gen[i]->Write();
    hpbpb_mcclosure_Jet55_gen[i]->Write();
    hpbpb_mcclosure_Jet55_gen_5TrigIneff_Smear[i]->Write();
    hpbpb_mcclosure_Jet55_gen_10TrigIneff_Smear[i]->Write();

    hpbpb_mcclosure_data[i]->Write();
    hpbpb_mcclosure_gen[i]->Write();
    hpbpb_mcclosure_data_train[i]->Write();
    hpbpb_mcclosure_matrix[i]->Write();

    hpbpb_JetComb_reco[i]->Write();
    hpbpb_JetComb_reco_5TrigIneff_Smear[i]->Write();
    hpbpb_JetComb_reco_10TrigIneff_Smear[i]->Write();
    hpbpb_Jet80_reco[i]->Write();
    hpbpb_Jet65_reco[i]->Write();
    hpbpb_Jet55_reco[i]->Write();
    hpbpb_JetComb_gen[i]->Write();
    hpbpb_JetComb_gen_5TrigIneff_Smear[i]->Write();
    hpbpb_JetComb_gen_10TrigIneff_Smear[i]->Write();
    hpbpb_Jet80_gen[i]->Write();
    hpbpb_Jet65_gen[i]->Write();
    hpbpb_Jet55_gen[i]->Write();

    hpbpb_JetComb_RecoSmear[i]->Write();
    hpbpb_Jet80_RecoSmear[i]->Write();
    hpbpb_Jet65_RecoSmear[i]->Write();
    hpbpb_Jet55_RecoSmear[i]->Write();
    hpbpb_JetComb_GenSmear[i]->Write();
    hpbpb_Jet80_GenSmear[i]->Write();
    hpbpb_Jet65_GenSmear[i]->Write();
    hpbpb_Jet55_GenSmear[i]->Write();

    hpbpb_JetComb_gen2pSmear[i]->Write();
    hpbpb_Jet80_gen2pSmear[i]->Write();
    hpbpb_Jet65_gen2pSmear[i]->Write();
    hpbpb_Jet55_gen2pSmear[i]->Write();

    hpbpb_JetComb_raw[i]->Write();
    hpbpb_Jet80_raw[i]->Write();
    hpbpb_Jet65_raw[i]->Write();
    hpbpb_Jet55_raw[i]->Write();

    hpbpb_anaBin_JetComb_reco[i]->Write();
    hpbpb_anaBin_Jet80_reco[i]->Write();
    hpbpb_anaBin_Jet65_reco[i]->Write();
    hpbpb_anaBin_Jet55_reco[i]->Write();
    hpbpb_anaBin_JetComb_gen[i]->Write();
    hpbpb_anaBin_Jet80_gen[i]->Write();
    hpbpb_anaBin_Jet65_gen[i]->Write();
    hpbpb_anaBin_Jet55_gen[i]->Write();
    
    hpbpb_reco[i]->Write();
    hpbpb_gen[i]->Write();
    hpbpb_matrix[i]->Write();

  }

}
