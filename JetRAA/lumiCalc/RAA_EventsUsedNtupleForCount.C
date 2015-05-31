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


#include "/net/hisrv0001/home/belt/wrk/JetRAA/RaghavCode/Headers/plot.h"

static const int nbins_cent = 7;
static const Double_t boundaries_cent[nbins_cent+1] = {0,2,4,12,20,28,36,40};// multiply by 2.5 to get your actual centrality % (old 2011 data) 
//now we have to multiply by 5, since centrality goes from 0-200. 

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


float deltaR(float eta1, float phi1, float eta2, float phi2)
{
  float pi=TMath::Pi();
  
  float deta = eta1 - eta2;
  float dphi = fabs(phi1 - phi2);
  if(dphi > pi)dphi -= 2*pi;
  float dr = sqrt(pow(deta,2) + pow(dphi,2));
  return dr;
}

float deltaphi(float phi1, float phi2)
{
  float pi=TMath::Pi();
 
  float dphi = fabs(phi1 - phi2);
  if(dphi > pi)dphi -= 2*pi;
  return dphi;
}

static const int nbins_pt = 30;
static const double boundaries_pt[nbins_pt+1] = {  3, 4, 5, 7, 9, 12, 15, 18, 21, 24, 28,  32, 37, 43, 49, 56,  64, 74, 84, 97, 114,  133, 153, 174, 196,  220, 245, 300, 330, 362, 395};



using namespace std;

void RAA_EventsUsedNtupleForCount(char* etaWidth = (char*)"20_eta_20",
					  Int_t radius = 3,
					  Int_t etaLow = 20,
					  Int_t etaHigh = 20)
{

  Int_t unm=1;
  Int_t mat=1;
  Int_t Short=0;
  long TestEntries=100000;
  long entries;
  
  TH1::SetDefaultSumw2();
  
  // the cut is a 3 step cut based on the different value of the calopt/pfpt - copy the following lines into your loop (with the corresponding branch address set)
  // if(calopt/pfpt <= 0.5 && eMax/Sumcand < 0.05) hGood->Fill();
  // if(calopt/pfpt > 0.5 && calopt/pfpt <= 0.85 && eMax/Sumcand < (18/7 *(Float_t)calopt_1/pfpt_1 - 9/7)) ) hGood->Fill();
  // if(calopt/pfpt > 0.85 & eMax/Sumcand > 0.9) hGood->Fill();
  
  
  cout<<"etaWidth = "<<etaWidth<<endl;

  bool isSymm = false;
  if(etaLow == etaHigh) isSymm = true;
  
  TFile * fData;

  //  fData = TFile::Open("/mnt/hadoop/cms/store/user/pawan/ntuples/JetRaa_akPu234_PbPb_MinBias.root");
// fData = TFile::Open("/export/d00/scratch/belt/condorfiles/pbpb/ntuples/JetRAA_DATA_PbPb_MinBias_ntuples.root");
  fData = TFile::Open("/mnt/hadoop/cms/store/user/pawan/ntuples/JetRaa_akPu234_PbPb_Data.root");


  TTree * Data_matched= (TTree*)fData->Get(Form("akPu%dJetAnalyzer/matchedJets",radius));
  TTree * Data_unmatched = (TTree*)fData->Get(Form("akPu%dJetAnalyzer/unmatchedPFJets",radius));
//  TFile *fcentin = TFile::Open("MinBiasHLTRatioWeightsVZ.root");
//  TH1F *hCentWeight = (TH1F*)fcentin->Get("hBinEvents");
  
  // TTree * MC_matched = (TTree*)fMC->Get("matchedJets");
  // TTree * MC_unmatched = (TTree*)fMC->Get("unmatchedPFJets");
  
  
  // //get the spectra with the specific trigger object from the different files. 
  // TH1F *hpbpb_Jet80_gen[nbins_cent],*hpbpb_Jet80_reco[nbins_cent];
  // TH1F *hpbpb_Jet65_gen[nbins_cent],*hpbpb_Jet65_reco[nbins_cent];
  // TH1F *hpbpb_Jet55_gen[nbins_cent],*hpbpb_Jet55_reco[nbins_cent];
  // TH1F *hpbpb_JetComb_gen[nbins_cent],*hpbpb_JetComb_reco[nbins_cent];

  // //TH1F *hpbpb_gen[nbins_cent],*hpbpb_reco[nbins_cent];
  // //TH2F *hpbpb_matrix[nbins_cent];
  // TH2F *hpbpb_matrix_HLT[nbins_cent];
  // //TH2F *hpbpb_mcclosure_matrix[nbins_cent];
  // TH2F *hpbpb_mcclosure_matrix_HLT[nbins_cent];
  // //TH2F *hpbpb_response[nbins_cent];
  // TH1F *hpbpb_mcclosure_JetComb_data[nbins_cent];
  // //TH1F *hpbpb_mcclosure_data[nbins_cent];
  // TH1F *hpbpb_mcclosure_Jet80_data[nbins_cent];
  // TH1F *hpbpb_mcclosure_Jet65_data[nbins_cent];
  // TH1F *hpbpb_mcclosure_Jet55_data[nbins_cent];
  // //TH1F *hpbpb_mcclosure_gen[nbins_cent];
  // TH1F *hpbpb_mcclosure_JetComb_gen[nbins_cent];
  // TH1F *hpbpb_mcclosure_Jet80_gen[nbins_cent];
  // TH1F *hpbpb_mcclosure_Jet65_gen[nbins_cent];
  // TH1F *hpbpb_mcclosure_Jet55_gen[nbins_cent];
#if 0    

  TH1F *hpbpb_TrgObj80[nbins_cent];
  TH1F *hpbpb_TrgObj65[nbins_cent];
  TH1F *hpbpb_TrgObj55[nbins_cent];
  TH1F *hpbpb_TrgObjComb[nbins_cent];
  TH1F * hpbpb_noTrg[nbins_cent];

  TH1F *hdphi_TrgObj80[nbins_cent];
  TH2F *hdphipt_TrgObj80[nbins_cent];
  TH1F *hpt_TrgObj80[nbins_cent];

  TH2F *hcalopf_TrgObjComb[nbins_cent];
  TH2F *hcalopf_TrgObj80[nbins_cent];

  // JEC systematics
  TH1F *hpbpb_JEC_TrgObjComb[nbins_cent];

  // Smear systematics
  TH1F *hpbpb_Smear_TrgObjComb[nbins_cent];

  for(int i = 0;i<nbins_cent;++i){
    //cout<<"cent bin = "<<i<<endl;

    hcalopf_TrgObjComb[i]=new TH2F(Form("hcalopfpt_TrgObjComb_%d_%s_cent%d",radius,etaWidth,i),Form("hCalopfpt_TrgObj%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400,400,0,400);
    
    hcalopf_TrgObj80[i]=new TH2F(Form("hcalopfpt_TrgObj80_%d_%s_cent%d",radius,etaWidth,i),Form("hCalopfpt_TrgObj%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400,400,0,400);

    hpbpb_noTrg[i] = new TH1F(Form("hpbpb_noTrg_R%d_%s_cent%d",radius,etaWidth,i),"",400,0,400);
    
    hpbpb_TrgObj80[i] = new TH1F(Form("hpbpb_HLT80_R%d_%s_cent%d",radius,etaWidth,i),Form("Spectra from  Jet 80 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400);
    hpbpb_TrgObj65[i] = new TH1F(Form("hpbpb_HLT65_R%d_%s_cent%d",radius,etaWidth,i),Form("Spectra from  Jet 65 && !jet80 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400);
    hpbpb_TrgObj55[i] = new TH1F(Form("hpbpb_HLT55_R%d_%s_cent%d",radius,etaWidth,i),Form("Spectra from Jet 55 && !jet65 && !jet80 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400);
    hpbpb_TrgObjComb[i] = new TH1F(Form("hpbpb_HLTComb_R%d_%s_cent%d",radius,etaWidth,i),Form("Trig Combined Spectra R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400);
    hpbpb_JEC_TrgObjComb[i] = new TH1F(Form("hpbpb_JEC_HLTComb_R%d_%s_cent%d",radius,etaWidth,i),Form("Trig Combined Spectra R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400);
    hpbpb_Smear_TrgObjComb[i] = new TH1F(Form("hpbpb_Smear_HLTComb_R%d_%s_cent%d",radius,etaWidth,i),Form("Trig Combined Spectra R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400);

    hdphi_TrgObj80[i]=new TH1F(Form("hdeltaphi_HLT80_%d_%s_cent%d",radius,etaWidth,i),Form("Delta phi  Jet 80 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,-10,10);
   
    hpt_TrgObj80[i]=new TH1F(Form("hdeltaphipt_HLT80_%d_%s_cent%d",radius,etaWidth,i),Form("pt  Jet 80 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400);
   
    //    hdphipt_TrgObj80[i]=new TH2F(Form("hdeltaphi_HLT80_%d_%s_cent%d",radius,etaWidth,i),Form("Delta phi  Jet 80 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400,400,-10,10);



#if 0
    //hpbpb_gen[i] = new TH1F(Form("hpbpb_gen_R%d_%s_cent%d",radius,etaWidth,i),Form("Gen refpt R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400);
    //cout<<"A"<<endl;
    //hpbpb_reco[i] = new TH1F(Form("hpbpb_reco_R%d_%s_cent%d",radius,etaWidth,i),Form("Reco jtpt R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400);
    //cout<<"B"<<endl;
    //hpbpb_matrix[i] = new TH2F(Form("hpbpb_matrix_R%d_%s_cent%d",radius,etaWidth,i),Form("Matrix refpt jtpt R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400,400,0,400);
    hpbpb_matrix_HLT[i] = new TH2F(Form("hpbpb_matrix_HLT_R%d_%s_cent%d",radius,etaWidth,i),Form("Matrix refpt jtpt from trigger addition R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400,400,0,400);
    //hpbpb_mcclosure_matrix[i] = new TH2F(Form("hpbpb_mcclosure_matrix_R%d_%s_cent%d",radius,etaWidth,i),Form("Matrix for mcclosure refpt jtpt R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400,400,0,400);
    hpbpb_mcclosure_matrix_HLT[i] = new TH2F(Form("hpbpb_mcclosure_matrix_HLT_R%d_%s_cent%d",radius,etaWidth,i),Form("Matrix for mcclosure refpt jtpt from Jet triggers R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400,400,0,400);
    //cout<<"C"<<endl;
    //hpbpb_mcclosure_data[i] = new TH1F(Form("hpbpb_mcclosure_data_R%d_%s_cent%d",radius,etaWidth,i),Form("data for unfolding mc closure test R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400);
    hpbpb_mcclosure_JetComb_data[i] = new TH1F(Form("hpbpb_mcclosure_JetComb_data_R%d_%s_cent%d",radius,etaWidth,i),Form("data for unfolding mc closure test trigger combined  R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400);
    hpbpb_mcclosure_Jet80_data[i] = new TH1F(Form("hpbpb_mcclosure_Jet80_data_R%d_%s_cent%d",radius,etaWidth,i),Form("data for unfolding mc closure test trigger 80  R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400);
    hpbpb_mcclosure_Jet65_data[i] = new TH1F(Form("hpbpb_mcclosure_Jet65_data_R%d_%s_cent%d",radius,etaWidth,i),Form("data for unfolding mc closure test trigger 65  R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400);
    hpbpb_mcclosure_Jet55_data[i] = new TH1F(Form("hpbpb_mcclosure_Jet55_data_R%d_%s_cent%d",radius,etaWidth,i),Form("data for unfolding mc closure test trigger 55  R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400);
    //hpbpb_mcclosure_gen[i] = new TH1F(Form("hpbpb_mcclosure_gen_R%d_%s_cent%d",radius,etaWidth,i),Form("gen spectra for unfolding mc closure test R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400);
    hpbpb_mcclosure_JetComb_gen[i] = new TH1F(Form("hpbpb_mcclosure_gen_JetComb_R%d_%s_cent%d",radius,etaWidth,i),Form("gen spectra for unfolding mc closure test trigger combined R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400);
    hpbpb_mcclosure_Jet80_gen[i] = new TH1F(Form("hpbpb_mcclosure_gen_Jet80_R%d_%s_cent%d",radius,etaWidth,i),Form("gen spectra for unfolding mc closure test trigger 80 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400);
    hpbpb_mcclosure_Jet65_gen[i] = new TH1F(Form("hpbpb_mcclosure_gen_Jet65_R%d_%s_cent%d",radius,etaWidth,i),Form("gen spectra for unfolding mc closure test trigger 65 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400);
    hpbpb_mcclosure_Jet55_gen[i] = new TH1F(Form("hpbpb_mcclosure_gen_Jet55_R%d_%s_cent%d",radius,etaWidth,i),Form("gen spectra for unfolding mc closure test trigger 55 R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400);
    hpbpb_JetComb_gen[i] = new TH1F(Form("hpbpb_JetComb_gen_R%d_%s_cent%d",radius,etaWidth,i),Form("Gen refpt from HLT trigger combined R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400);
    hpbpb_JetComb_reco[i] = new TH1F(Form("hpbpb_JetComb_reco_R%d_%s_cent%d",radius,etaWidth,i),Form("reco jtpt from HLT trigger combined R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400);
    hpbpb_Jet80_gen[i] = new TH1F(Form("hpbpb_Jet80_gen_R%d_%s_cent%d",radius,etaWidth,i),Form("Gen refpt from Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400);
    hpbpb_Jet80_reco[i] = new TH1F(Form("hpbpb_Jet80_reco_R%d_%s_cent%d",radius,etaWidth,i),Form("reco jtpt from Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400);
    hpbpb_Jet65_gen[i] = new TH1F(Form("hpbpb_Jet65_gen_R%d_%s_cent%d",radius,etaWidth,i),Form("Gen refpt from Jet65 && !Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400);
    hpbpb_Jet65_reco[i] = new TH1F(Form("hpbpb_Jet65_reco_R%d_%s_cent%d",radius,etaWidth,i),Form("reco jtpt from Jet65 && !Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400);
    hpbpb_Jet55_gen[i] = new TH1F(Form("hpbpb_Jet55_gen_R%d_%s_cent%d",radius,etaWidth,i),Form("Gen refpt from Jet55 && !Jet65 && !Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400);
    hpbpb_Jet55_reco[i] = new TH1F(Form("hpbpb_Jet55_reco_R%d_%s_cent%d",radius,etaWidth,i),Form("reco jtpt from Jet55 && !Jet65 && !Jet80 trigger R%d %s %2.0f - %2.0f cent",radius,etaWidth,5*boundaries_cent[i],5*boundaries_cent[i+1]),400,0,400);
#endif	
  }// centrality bin loop
#endif 


  // Define all the histograms necessary for the analysis: 
  
  // 1 - Data, 2 - MC
  Float_t pfpt_1, pfpt_2;
  Float_t pfrefpt_2;
  Float_t calopt_1, calopt_2;
  Float_t eMax_1, eMax_2;
  Float_t chMax_1, chMax_2;
  Float_t chSum_1, chSum_2;
  Float_t phSum_1, phSum_2;
  Float_t neSum_1, neSum_2;
  Float_t muSum_1, muSum_2;
  Int_t jet55_1, jet65_1, jet80_1;
  Int_t jet55_p_1, jet65_p_1, jet80_p_1;
  Int_t jet55_2, jet65_2, jet80_2;
  Int_t jet55_p_2;
  Float_t weight;
  Int_t subid_2;
  Int_t hiBin_1, hiBin_2;
  Int_t jetMB_1, jetMB_p_1;
  Float_t eta_1, eta_2;
  Float_t pfrawpt_1, pfrawpt_2;
Int_t run_1, evt_1, lumi_1;
 Float_t phi_1, phi_2;
  Data_matched->SetBranchAddress("calopt",&calopt_1);
  Data_matched->SetBranchAddress("pfpt",&pfpt_1);
  Data_matched->SetBranchAddress("eMax",&eMax_1);
  Data_matched->SetBranchAddress("chMax",&chMax_1);
  Data_matched->SetBranchAddress("chSum",&chSum_1);
  Data_matched->SetBranchAddress("phSum",&phSum_1);
  Data_matched->SetBranchAddress("neSum",&neSum_1);
  Data_matched->SetBranchAddress("muSum",&muSum_1);
  Data_matched->SetBranchAddress("hiBin",&hiBin_1);  
  Data_matched->SetBranchAddress("jetMB",&jetMB_1);
  Data_matched->SetBranchAddress("jet55",&jet55_1);
  Data_matched->SetBranchAddress("jet65",&jet65_1);
  Data_matched->SetBranchAddress("jet80",&jet80_1);
  Data_matched->SetBranchAddress("jetMB_prescl",&jetMB_p_1);
  Data_matched->SetBranchAddress("jet55_prescl",&jet55_p_1);
  Data_matched->SetBranchAddress("jet65_prescl",&jet65_p_1);
  Data_matched->SetBranchAddress("jet80_prescl",&jet80_p_1);
  Data_matched->SetBranchAddress("pfeta",&eta_1);
  Data_matched->SetBranchAddress("pfphi",&phi_1);
  Data_matched->SetBranchAddress("pfrawpt",&pfrawpt_1);
  Data_matched->SetBranchAddress("run_value",&run_1);
  Data_matched->SetBranchAddress("evt_value",&evt_1);
  Data_matched->SetBranchAddress("lumi_value",&lumi_1);

  Data_unmatched->SetBranchAddress("pfpt",&pfpt_1);
  Data_unmatched->SetBranchAddress("eMax",&eMax_1);
  Data_unmatched->SetBranchAddress("chMax",&chMax_1);
  Data_unmatched->SetBranchAddress("chSum",&chSum_1);
  Data_unmatched->SetBranchAddress("phSum",&phSum_1);
  Data_unmatched->SetBranchAddress("neSum",&neSum_1);
  Data_unmatched->SetBranchAddress("muSum",&muSum_1);
  Data_unmatched->SetBranchAddress("hiBin",&hiBin_1);
  Data_unmatched->SetBranchAddress("jet55",&jet55_1);
  Data_unmatched->SetBranchAddress("jet65",&jet65_1);
  Data_unmatched->SetBranchAddress("jet80",&jet80_1);
  Data_unmatched->SetBranchAddress("jetMB",&jetMB_1);
  Data_unmatched->SetBranchAddress("jetMB_prescl",&jetMB_p_1);
  Data_unmatched->SetBranchAddress("jet55_prescl",&jet55_p_1);
  Data_unmatched->SetBranchAddress("jet65_prescl",&jet65_p_1);
  Data_unmatched->SetBranchAddress("jet80_prescl",&jet80_p_1);
  Data_unmatched->SetBranchAddress("pfeta",&eta_1);
  Data_unmatched->SetBranchAddress("pfphi",&phi_1);
  Data_unmatched->SetBranchAddress("pfrawpt",&pfrawpt_1);
  Data_unmatched->SetBranchAddress("run_value",&run_1);
  Data_unmatched->SetBranchAddress("evt_value",&evt_1);
  Data_unmatched->SetBranchAddress("lumi_value",&lumi_1);
  
#if 0
  MC_matched->SetBranchAddress("calopt",&calopt_2);
  MC_matched->SetBranchAddress("pfpt",&pfpt_2);
  MC_matched->SetBranchAddress("eMax",&eMax_2);
  MC_matched->SetBranchAddress("chMax",&chMax_2);
  MC_matched->SetBranchAddress("chSum",&chSum_2);
  MC_matched->SetBranchAddress("phSum",&phSum_2);
  MC_matched->SetBranchAddress("neSum",&neSum_2);
  MC_matched->SetBranchAddress("muSum",&muSum_2);
  MC_matched->SetBranchAddress("hiBin",&hiBin_2);
  MC_matched->SetBranchAddress("pfrefpt",&pfrefpt_2);
  MC_matched->SetBranchAddress("jet55",&jet55_2);
  MC_matched->SetBranchAddress("jet65",&jet65_2);
  MC_matched->SetBranchAddress("jet80",&jet80_2);
  MC_matched->SetBranchAddress("weight", &weight);
  MC_matched->SetBranchAddress("subid", &subid_2);
  MC_matched->SetBranchAddress("jet55_prescl",&jet55_p_2);
  
  MC_unmatched->SetBranchAddress("pfpt",&pfpt_2);
  MC_unmatched->SetBranchAddress("eMax",&eMax_2);
  MC_unmatched->SetBranchAddress("chMax",&chMax_2);
  MC_unmatched->SetBranchAddress("chSum",&chSum_2);
  MC_unmatched->SetBranchAddress("phSum",&phSum_2);
  MC_unmatched->SetBranchAddress("neSum",&neSum_2);
  MC_unmatched->SetBranchAddress("muSum",&muSum_2);
  MC_unmatched->SetBranchAddress("hiBin",&hiBin_2);
  MC_unmatched->SetBranchAddress("pfrefpt",&pfrefpt_2);
  MC_unmatched->SetBranchAddress("jet55",&jet55_2);
  MC_unmatched->SetBranchAddress("jet65",&jet65_2);
  MC_unmatched->SetBranchAddress("jet80",&jet80_2);
  MC_unmatched->SetBranchAddress("weight", & weight);
  MC_unmatched->SetBranchAddress("subid", &subid_2);
  MC_unmatched->SetBranchAddress("jet55_prescl",&jet55_p_2);
#endif

// tree stuff
  Int_t maxrun=70,maxlumi=75000;
  Int_t eid=0;
  Int_t run[maxlumi];
  Int_t lumi[maxlumi];
  Int_t eidnow=0;
  Int_t matched=-999;
  
  for(int i=0;i<maxrun;i++){
    run[i]=-999;
  }
  for(int j=0;j<maxlumi;j++){
    lumi[j]=-999;
  } 
  
  // data loop
  if(Short==1){
   entries=TestEntries;
  } else {
   entries = Data_matched->GetEntries();
  }
  //entries = 1000;
  cout<<"matched Data ntuple "<<endl;

  TRandom rnd; 
  //Adding the centrality weighting 
  //    Float_t prescl = 38.695;
  //  Float_t prescl = weight_cent;
  //  Float_t prescl=1;
  if(mat==1)  for(long nentry = 0; nentry < entries; ++nentry ){

      //    if(nentry%100000 == 0) cout<<" nentry = "<<nentry<<endl;
      
//      Float_t weight_cent = hCentWeight->GetBinContent(hCentWeight->FindBin(hiBin_1));
//      Float_t prescl = weight_cent;
      
      Data_matched->GetEntry(nentry);
      Int_t cBin = findBin(hiBin_1);
      
       matched=-999;
  	 for(int ieid=0;ieid<(eidnow+1);ieid++){
  	   if(matched==1){ 
//  	      cout<<"breaking out of loop at ieid: "<<ieid<<", eidnow: "<<eidnow<<" due to matched: "<<matched<<", at entry: "<<nentry<<endl; 
  	      continue; 
  	   }
//  	   cout<<"looping at ieid: "<<ieid<<", eidnow: "<<eidnow<<endl;
	   if(run_1==run[ieid] && lumi_1==lumi[ieid]){
	    matched=1;
//	    cout<<"I found a matched="<<matched<<" with run[ieid]: "<<run[ieid]<<" && lumi[ieid]:"<<lumi[ieid]<<" for run: "<<run_1<<", lumi: "<<lumi_1<<endl;
	   } else {
//	    cout<<"unmatched: run, lumi: "<<run_1<<", "<<lumi_1<<", eidnow: "<<eidnow<<", ieid: "<<ieid<<", at entry: "<<nentry<<endl;
        matched=0;
	   }
	 }   
	 if(matched==0){
	     run[eidnow]=run_1;
	     lumi[eidnow]=lumi_1;
	     cout<<"\""<<run[eidnow]<<"\":"<<" [["<<lumi[eidnow]<<","<<lumi[eidnow]<<"]], "<<endl;	     
//	     cout<<"unique run&&lumi: run of "<<run_1<<" should = "<<run[eidnow]<<", lumi:"<<lumi_1<<" should equal: "<<lumi[eidnow]<<", eidnow: "<<eidnow<<", at entry: "<<nentry<<endl;
	     eidnow++; 
    } 
	 
	 
      // do we want event count before centrality selection? I think so...      
      if(cBin == -1 || cBin >= nbins_cent) continue;
      
      
    
  }// data ntuple loop

  // data unmatched loop:
  if(Short==1){
   entries=TestEntries;
  } else {
    entries = Data_unmatched->GetEntries();
  }
  //entries = 1000;
  cout<<"Unmatched Data ntuple "<<endl;
     if(unm==1)  for(long nentry = 0; nentry < entries; ++nentry ){

//	 Float_t weight_cent = hCentWeight->GetBinContent(hCentWeight->FindBin(hiBin_1));
//	 Float_t prescl = weight_cent;
	 
	 //    if(nentry%100000 == 0) cout<<" nentry = "<<nentry<<endl;
	 Data_unmatched->GetEntry(nentry);
	 Int_t cBin = findBin(hiBin_1);
	 
       matched=-999;
  	 for(int ieid=0;ieid<(eidnow+1);ieid++){
  	   if(matched==1){ 
//  	      cout<<"breaking out of loop at ieid: "<<ieid<<", eidnow: "<<eidnow<<" due to matched: "<<matched<<", at entry: "<<nentry<<endl; 
  	      continue; 
  	   }
//  	   cout<<"looping at ieid: "<<ieid<<", eidnow: "<<eidnow<<endl;
	   if(run_1==run[ieid] && lumi_1==lumi[ieid]){
	    matched=1;
//	    cout<<"I found a matched="<<matched<<" with run[ieid]: "<<run[ieid]<<" && lumi[ieid]:"<<lumi[ieid]<<" for run: "<<run_1<<", lumi: "<<lumi_1<<endl;
	   } else {
//	    cout<<"unmatched: run, lumi: "<<run_1<<", "<<lumi_1<<", eidnow: "<<eidnow<<", ieid: "<<ieid<<", at entry: "<<nentry<<endl;
        matched=0;
	   }
	 }   
	 if(matched==0){
	     run[eidnow]=run_1;
	     lumi[eidnow]=lumi_1;
	     cout<<"\""<<run[eidnow]<<"\":"<<" [["<<lumi[eidnow]<<","<<lumi[eidnow]<<"]], "<<endl;	     
//	     cout<<"unique run&&lumi: run of "<<run_1<<" should = "<<run[eidnow]<<", lumi:"<<lumi_1<<" should equal: "<<lumi[eidnow]<<", eidnow: "<<eidnow<<", at entry: "<<nentry<<endl;
	     eidnow++; 
    } 

	 if(cBin == -1 || cBin >= nbins_cent) continue;
    }// data ntuple loop

#if 0
 
  entries = MC_matched->GetEntries();
  //entries = 1000;
  // MC loop
  cout<<" looking at matched MC ntuple "<<endl;
  for(long nentry = 0; nentry < entries; ++nentry){
    if(nentry%10000 == 0) cout<<" nentry = "<<nentry<<endl;
    MC_matched->GetEntry(nentry);
    
    Float_t Sumcand = chSum_2 + phSum_2 + neSum_2 + muSum_2;
    if(subid_2 != 0) continue;
    Int_t cBin = findBin(hiBin_2);
    if(cBin == -1 || cBin >= nbins_cent) continue;

    
    
  }// mc ntuple loop
  entries = MC_unmatched->GetEntries();
  //entries = 1000;
  // MC loop
  cout<<" looking at unmatched MC ntuple"<<endl;
  for(long nentry = 0; nentry < entries; ++nentry){
    if(nentry%10000 == 0) cout<<" nentry = "<<nentry<<endl;
    MC_unmatched->GetEntry(nentry);
    if(subid_2 != 0) continue;
    Int_t cBin = findBin(hiBin_2);
    if(cBin == -1 || cBin >= nbins_cent) continue;
    
    
    
    
  }// mc unmatched  ntuple loop
#endif
  //TFile fout(Form("Pawan_ntuple_PbPb_MinBiasData_spectra_JetID_CutA_finebins_CentralityWeightedHLT80andMBOnly_%s_R0p%d.root",etaWidth,radius),"RECREATE");
  //  TFile fout(Form("Pawan_ntuple_PbPb_MinBiasData_spectra_JetID_CutA_finebins_CentralityWeightedMBwithoutHLT80and65_%s_R0p%d.root",etaWidth,radius),"RECREATE");
  //  TFile fout(Form("Pawan_ntuple_PbPb_MinBiasData_spectra_JetID_CutA_finebins_CentralityWeightedMBwithchmaxcut10_withpt40_%s_R0p%d.root",etaWidth,radius),"RECREATE");
   TFile fout("EventCounting.root","RECREATE");

  //  TFile fout(Form("Pawan_ntuple_PbPb_MinBiasDatawithoutHLT_spectra_JetID_CutA_finebins_%s_R0p%d.root",etaWidth,radius),"RECREATE");
  fout.cd();
  // write some tree!

  fout.Close();

    }
