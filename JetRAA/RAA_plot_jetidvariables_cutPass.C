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

#define pi 3.14159265
using namespace std;

#include "Headers/plot.h"

int findBin(int hiBin);

void RAA_plot_jetidvariables_cutPass(){

  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);
  
   TFile * fData = TFile::Open("/data/users/belt/JetRAA/MatchNtuples/PbPb_Data_calo_pf_jet_correlation_deltaR_0p2_akPu4_20150331.root");
  TTree * Data_matched = (TTree*)fData->Get("matchedJets");
  TTree * Data_unmatched = (TTree*)fData->Get("unmatchedPFJets");

  TFile * fMC = TFile::Open("/data/users/belt/JetRAA/MatchNtuples/PbPb_MC_calo_pf_jet_correlation_deltaR_0p2_akPu4_20150331.root");
  TTree * MC_matched = (TTree*)fMC->Get("matchedJets");
  TTree * MC_unmatched = (TTree*)fMC->Get("unmatchedPFJets");

  const int nbins_cent = 6;
  const int boundaries_cent[nbins_cent+1] = {0,2,4,12,20,28,36};
  int centrality_bins[nbins_cent+1] = {0,5,10,30,50,70,90};
  
  Float_t pfptmin = 50;
  
  TH1F * hData_chMaxJtpt[nbins_cent], * hData_phMaxJtpt[nbins_cent], * hData_neMaxJtpt[nbins_cent], * hData_muMaxJtpt[nbins_cent], * hData_eMaxJtpt[nbins_cent];
  TH1F * hData_chSumJtpt[nbins_cent], * hData_phSumJtpt[nbins_cent], * hData_neSumJtpt[nbins_cent], * hData_muSumJtpt[nbins_cent], * hData_eSumJtpt[nbins_cent];  
  
  TH1F * hMC_chMaxJtpt[nbins_cent], * hMC_phMaxJtpt[nbins_cent], * hMC_neMaxJtpt[nbins_cent], * hMC_muMaxJtpt[nbins_cent], * hMC_eMaxJtpt[nbins_cent];
  TH1F * hMC_chSumJtpt[nbins_cent], * hMC_phSumJtpt[nbins_cent], * hMC_neSumJtpt[nbins_cent], * hMC_muSumJtpt[nbins_cent], * hMC_eSumJtpt[nbins_cent];  

  TH1F * hData_chMaxJtpt_keep[nbins_cent], * hData_phMaxJtpt_keep[nbins_cent], * hData_neMaxJtpt_keep[nbins_cent], * hData_muMaxJtpt_keep[nbins_cent], * hData_eMaxJtpt_keep[nbins_cent];
  TH1F * hData_chSumJtpt_keep[nbins_cent], * hData_phSumJtpt_keep[nbins_cent], * hData_neSumJtpt_keep[nbins_cent], * hData_muSumJtpt_keep[nbins_cent], * hData_eSumJtpt_keep[nbins_cent];  
  
  TH1F * hMC_chMaxJtpt_keep[nbins_cent], * hMC_phMaxJtpt_keep[nbins_cent], * hMC_neMaxJtpt_keep[nbins_cent], * hMC_muMaxJtpt_keep[nbins_cent], * hMC_eMaxJtpt_keep[nbins_cent];
  TH1F * hMC_chSumJtpt_keep[nbins_cent], * hMC_phSumJtpt_keep[nbins_cent], * hMC_neSumJtpt_keep[nbins_cent], * hMC_muSumJtpt_keep[nbins_cent], * hMC_eSumJtpt_keep[nbins_cent];  

  TH1F * hData_chMaxJtpt_rej[nbins_cent], * hData_phMaxJtpt_rej[nbins_cent], * hData_neMaxJtpt_rej[nbins_cent], * hData_muMaxJtpt_rej[nbins_cent], * hData_eMaxJtpt_rej[nbins_cent];
  TH1F * hData_chSumJtpt_rej[nbins_cent], * hData_phSumJtpt_rej[nbins_cent], * hData_neSumJtpt_rej[nbins_cent], * hData_muSumJtpt_rej[nbins_cent], * hData_eSumJtpt_rej[nbins_cent];  
  
  TH1F * hMC_chMaxJtpt_rej[nbins_cent], * hMC_phMaxJtpt_rej[nbins_cent], * hMC_neMaxJtpt_rej[nbins_cent], * hMC_muMaxJtpt_rej[nbins_cent], * hMC_eMaxJtpt_rej[nbins_cent];
  TH1F * hMC_chSumJtpt_rej[nbins_cent], * hMC_phSumJtpt_rej[nbins_cent], * hMC_neSumJtpt_rej[nbins_cent], * hMC_muSumJtpt_rej[nbins_cent], * hMC_eSumJtpt_rej[nbins_cent];  

  Int_t * nData_chMaxJtpt_keep[nbins_cent], * nData_phMaxJtpt_keep[nbins_cent], * nData_neMaxJtpt_keep[nbins_cent], * nData_muMaxJtpt_keep[nbins_cent], * nData_eMaxJtpt_keep[nbins_cent];
  Int_t * nData_chSumJtpt_keep[nbins_cent], * nData_phSumJtpt_keep[nbins_cent], * nData_neSumJtpt_keep[nbins_cent], * nData_muSumJtpt_keep[nbins_cent], * nData_eSumJtpt_keep[nbins_cent];  
  
  Int_t * nMC_chMaxJtpt_keep[nbins_cent], * nMC_phMaxJtpt_keep[nbins_cent], * nMC_neMaxJtpt_keep[nbins_cent], * nMC_muMaxJtpt_keep[nbins_cent], * nMC_eMaxJtpt_keep[nbins_cent];
  Int_t * nMC_chSumJtpt_keep[nbins_cent], * nMC_phSumJtpt_keep[nbins_cent], * nMC_neSumJtpt_keep[nbins_cent], * nMC_muSumJtpt_keep[nbins_cent], * nMC_eSumJtpt_keep[nbins_cent];  

  Int_t * nData_chMaxJtpt_rej[nbins_cent], * nData_phMaxJtpt_rej[nbins_cent], * nData_neMaxJtpt_rej[nbins_cent], * nData_muMaxJtpt_rej[nbins_cent], * nData_eMaxJtpt_rej[nbins_cent];
  Int_t * nData_chSumJtpt_rej[nbins_cent], * nData_phSumJtpt_rej[nbins_cent], * nData_neSumJtpt_rej[nbins_cent], * nData_muSumJtpt_rej[nbins_cent], * nData_eSumJtpt_rej[nbins_cent];  
  
  Int_t * nMC_chMaxJtpt_rej[nbins_cent], * nMC_phMaxJtpt_rej[nbins_cent], * nMC_neMaxJtpt_rej[nbins_cent], * nMC_muMaxJtpt_rej[nbins_cent], * nMC_eMaxJtpt_rej[nbins_cent];
  Int_t * nMC_chSumJtpt_rej[nbins_cent], * nMC_phSumJtpt_rej[nbins_cent], * nMC_neSumJtpt_rej[nbins_cent], * nMC_muSumJtpt_rej[nbins_cent], * nMC_eSumJtpt_rej[nbins_cent];  


  for(int i = 0 ; i < nbins_cent ; ++i){

    hData_chMaxJtpt[i] = new TH1F(Form("hData_chMaxJtpt_cent%d",i),Form("Data chMax/jtpt in centrality bin %d",i),100,0,1);
    hMC_chMaxJtpt[i] = new TH1F(Form("hMC_chMaxJtpt_cent%d",i),Form("MC chMax/jtpt in centrality bin %d",i),100,0,1);
    hData_chSumJtpt[i] = new TH1F(Form("hData_chSumJtpt_cent%d",i),Form("Data chSum/jtpt in centrality bin %d",i),100,0,3);
    hMC_chSumJtpt[i] = new TH1F(Form("hMC_chSumJtpt_cent%d",i),Form("MC chSum/jtpt in centrality bin %d",i),100,0,3);

    hData_eMaxJtpt[i] = new TH1F(Form("hData_eMaxJtpt_cent%d",i),Form("Data eMax/jtpt in centrality bin %d",i),100,0,1.4);
    hMC_eMaxJtpt[i] = new TH1F(Form("hMC_eMaxJtpt_cent%d",i),Form("MC eMax/jtpt in centrality bin %d",i),100,0,1.4);
    hData_eSumJtpt[i] = new TH1F(Form("hData_eSumJtpt_cent%d",i),Form("Data eSum/jtpt in centrality bin %d",i),100,0,1.5);
    hMC_eSumJtpt[i] = new TH1F(Form("hMC_eSumJtpt_cent%d",i),Form("MC eSum/jtpt in centrality bin %d",i),100,0,1.5);

    hData_neMaxJtpt[i] = new TH1F(Form("hData_neMaxJtpt_cent%d",i),Form("Data neMax/jtpt in centrality bin %d",i),100,0,1.2);
    hMC_neMaxJtpt[i] = new TH1F(Form("hMC_neMaxJtpt_cent%d",i),Form("MC neMax/jtpt in centrality bin %d",i),100,0,1.2);
    hData_neSumJtpt[i] = new TH1F(Form("hData_neSumJtpt_cent%d",i),Form("Data neSum/jtpt in centrality bin %d",i),100,0,1.8);
    hMC_neSumJtpt[i] = new TH1F(Form("hMC_neSumJtpt_cent%d",i),Form("MC neSum/jtpt in centrality bin %d",i),100,0,1.8);

    hData_phMaxJtpt[i] = new TH1F(Form("hData_phMaxJtpt_cent%d",i),Form("Data phMax/jtpt in centrality bin %d",i),100,0,1.5);
    hMC_phMaxJtpt[i] = new TH1F(Form("hMC_phMaxJtpt_cent%d",i),Form("MC phMax/jtpt in centrality bin %d",i),100,0,1.5);
    hData_phSumJtpt[i] = new TH1F(Form("hData_phSumJtpt_cent%d",i),Form("Data phSum/jtpt in centrality bin %d",i),100,0,2);
    hMC_phSumJtpt[i] = new TH1F(Form("hMC_phSumJtpt_cent%d",i),Form("MC phSum/jtpt in centrality bin %d",i),100,0,2);

    hData_muMaxJtpt[i] = new TH1F(Form("hData_muMaxJtpt_cent%d",i),Form("Data muMax/jtpt in centrality bin %d",i),100,0,1);
    hMC_muMaxJtpt[i] = new TH1F(Form("hMC_muMaxJtpt_cent%d",i),Form("MC muMax/jtpt in centrality bin %d",i),100,0,1);
    hData_muSumJtpt[i] = new TH1F(Form("hData_muSumJtpt_cent%d",i),Form("Data muSum/jtpt in centrality bin %d",i),100,0,1);
    hMC_muSumJtpt[i] = new TH1F(Form("hMC_muSumJtpt_cent%d",i),Form("MC muSum/jtpt in centrality bin %d",i),100,0,1);

    hData_chMaxJtpt_keep[i] = new TH1F(Form("hData_chMaxJtpt_keep_cent%d",i),Form("Data chMax/Jtpt pass cutA in centrality bin %d",i),100,0,1);
    hMC_chMaxJtpt_keep[i] = new TH1F(Form("hMC_chMaxJtpt_keep_cent%d",i),Form("MC chMax/Jtpt pass cutA in centrality bin %d",i),100,0,1);
    hData_chSumJtpt_keep[i] = new TH1F(Form("hData_chSumJtpt_keep_cent%d",i),Form("Data chSum/Jtpt pass cutA in centrality bin %d",i),100,0,3);
    hMC_chSumJtpt_keep[i] = new TH1F(Form("hMC_chSumJtpt_keep_cent%d",i),Form("MC chSum/Jtpt pass cutA in centrality bin %d",i),100,0,3);

    hData_eMaxJtpt_keep[i] = new TH1F(Form("hData_eMaxJtpt_keep_cent%d",i),Form("Data eMax/Jtpt pass cutA in centrality bin %d",i),100,0,1.4);
    hMC_eMaxJtpt_keep[i] = new TH1F(Form("hMC_eMaxJtpt_keep_cent%d",i),Form("MC eMax/Jtpt pass cutA in centrality bin %d",i),100,0,1.4);
    hData_eSumJtpt_keep[i] = new TH1F(Form("hData_eSumJtpt_keep_cent%d",i),Form("Data eSum/Jtpt pass cutA in centrality bin %d",i),100,0,1.5);
    hMC_eSumJtpt_keep[i] = new TH1F(Form("hMC_eSumJtpt_keep_cent%d",i),Form("MC eSum/Jtpt pass cutA in centrality bin %d",i),100,0,1.5);

    hData_neMaxJtpt_keep[i] = new TH1F(Form("hData_neMaxJtpt_keep_cent%d",i),Form("Data neMax/Jtpt pass cutA in centrality bin %d",i),100,0,1.2);
    hMC_neMaxJtpt_keep[i] = new TH1F(Form("hMC_neMaxJtpt_keep_cent%d",i),Form("MC neMax/Jtpt pass cutA in centrality bin %d",i),100,0,1.2);
    hData_neSumJtpt_keep[i] = new TH1F(Form("hData_neSumJtpt_keep_cent%d",i),Form("Data neSum/Jtpt pass cutA in centrality bin %d",i),100,0,1.8);
    hMC_neSumJtpt_keep[i] = new TH1F(Form("hMC_neSumJtpt_keep_cent%d",i),Form("MC neSum/Jtpt pass cutA in centrality bin %d",i),100,0,1.8);

    hData_phMaxJtpt_keep[i] = new TH1F(Form("hData_phMaxJtpt_keep_cent%d",i),Form("Data phMax/Jtpt pass cutA in centrality bin %d",i),100,0,1.5);
    hMC_phMaxJtpt_keep[i] = new TH1F(Form("hMC_phMaxJtpt_keep_cent%d",i),Form("MC phMax/Jtpt pass cutA in centrality bin %d",i),100,0,1.5);
    hData_phSumJtpt_keep[i] = new TH1F(Form("hData_phSumJtpt_keep_cent%d",i),Form("Data phSum/Jtpt pass cutA in centrality bin %d",i),100,0,2);
    hMC_phSumJtpt_keep[i] = new TH1F(Form("hMC_phSumJtpt_keep_cent%d",i),Form("MC phSum/Jtpt pass cutA in centrality bin %d",i),100,0,2);

    hData_muMaxJtpt_keep[i] = new TH1F(Form("hData_muMaxJtpt_keep_cent%d",i),Form("Data muMax/Jtpt pass cutA in centrality bin %d",i),100,0,1);
    hMC_muMaxJtpt_keep[i] = new TH1F(Form("hMC_muMaxJtpt_keep_cent%d",i),Form("MC muMax/Jtpt pass cutA in centrality bin %d",i),100,0,1);
    hData_muSumJtpt_keep[i] = new TH1F(Form("hData_muSumJtpt_keep_cent%d",i),Form("Data muSum/Jtpt pass cutA in centrality bin %d",i),100,0,1);
    hMC_muSumJtpt_keep[i] = new TH1F(Form("hMC_muSumJtpt_keep_cent%d",i),Form("MC muSum/Jtpt pass cutA in centrality bin %d",i),100,0,1);

    hData_chMaxJtpt_rej[i] = new TH1F(Form("hData_chMaxJtpt_rej_cent%d",i),Form("Data chMax/Jtpt fail cutA in centrality bin %d",i),100,0,1);
    hMC_chMaxJtpt_rej[i] = new TH1F(Form("hMC_chMaxJtpt_rej_cent%d",i),Form("MC chMax/Jtpt fail cutA in centrality bin %d",i),100,0,1);
    hData_chSumJtpt_rej[i] = new TH1F(Form("hData_chSumJtpt_rej_cent%d",i),Form("Data chSum/Jtpt fail cutA in centrality bin %d",i),100,0,3);
    hMC_chSumJtpt_rej[i] = new TH1F(Form("hMC_chSumJtpt_rej_cent%d",i),Form("MC chSum/Jtpt fail cutA in centrality bin %d",i),100,0,3);

    hData_eMaxJtpt_rej[i] = new TH1F(Form("hData_eMaxJtpt_rej_cent%d",i),Form("Data eMax/Jtpt fail cutA in centrality bin %d",i),100,0,1.4);
    hMC_eMaxJtpt_rej[i] = new TH1F(Form("hMC_eMaxJtpt_rej_cent%d",i),Form("MC eMax/Jtpt fail cutA in centrality bin %d",i),100,0,1.4);
    hData_eSumJtpt_rej[i] = new TH1F(Form("hData_eSumJtpt_rej_cent%d",i),Form("Data eSum/Jtpt fail cutA in centrality bin %d",i),100,0,1.5);
    hMC_eSumJtpt_rej[i] = new TH1F(Form("hMC_eSumJtpt_rej_cent%d",i),Form("MC eSum/Jtpt fail cutA in centrality bin %d",i),100,0,1.5);

    hData_neMaxJtpt_rej[i] = new TH1F(Form("hData_neMaxJtpt_rej_cent%d",i),Form("Data neMax/Jtpt fail cutA in centrality bin %d",i),100,0,1.2);
    hMC_neMaxJtpt_rej[i] = new TH1F(Form("hMC_neMaxJtpt_rej_cent%d",i),Form("MC neMax/Jtpt fail cutA in centrality bin %d",i),100,0,1.2);
    hData_neSumJtpt_rej[i] = new TH1F(Form("hData_neSumJtpt_rej_cent%d",i),Form("Data neSum/Jtpt fail cutA in centrality bin %d",i),100,0,1.8);
    hMC_neSumJtpt_rej[i] = new TH1F(Form("hMC_neSumJtpt_rej_cent%d",i),Form("MC neSum/Jtpt fail cutA in centrality bin %d",i),100,0,1.8);

    hData_phMaxJtpt_rej[i] = new TH1F(Form("hData_phMaxJtpt_rej_cent%d",i),Form("Data phMax/Jtpt fail cutA in centrality bin %d",i),100,0,1.5);
    hMC_phMaxJtpt_rej[i] = new TH1F(Form("hMC_phMaxJtpt_rej_cent%d",i),Form("MC phMax/Jtpt fail cutA in centrality bin %d",i),100,0,1.5);
    hData_phSumJtpt_rej[i] = new TH1F(Form("hData_phSumJtpt_rej_cent%d",i),Form("Data phSum/Jtpt fail cutA in centrality bin %d",i),100,0,2);
    hMC_phSumJtpt_rej[i] = new TH1F(Form("hMC_phSumJtpt_rej_cent%d",i),Form("MC phSum/Jtpt fail cutA in centrality bin %d",i),100,0,2);

    hData_muMaxJtpt_rej[i] = new TH1F(Form("hData_muMaxJtpt_rej_cent%d",i),Form("Data muMax/Jtpt fail cutA in centrality bin %d",i),100,0,1);
    hMC_muMaxJtpt_rej[i] = new TH1F(Form("hMC_muMaxJtpt_rej_cent%d",i),Form("MC muMax/Jtpt fail cutA in centrality bin %d",i),100,0,1);
    hData_muSumJtpt_rej[i] = new TH1F(Form("hData_muSumJtpt_rej_cent%d",i),Form("Data muSum/Jtpt fail cutA in centrality bin %d",i),100,0,1);
    hMC_muSumJtpt_rej[i] = new TH1F(Form("hMC_muSumJtpt_rej_cent%d",i),Form("MC muSum/Jtpt fail cutA in centrality bin %d",i),100,0,1);

  }
  
  // 1 - Data, 2 - MC
  Float_t pfpt_1, pfpt_2;
  Float_t pfrefpt_2;
  Float_t calopt_1, calopt_2;
  Float_t chMax_1, chMax_2;
  Float_t phMax_1, phMax_2;
  Float_t neMax_1, neMax_2;
  Float_t muMax_1, muMax_2;
  Float_t eMax_1, eMax_2;
  Float_t chSum_1, chSum_2;
  Float_t phSum_1, phSum_2;
  Float_t neSum_1, neSum_2;
  Float_t muSum_1, muSum_2;
  Float_t eSum_1, eSum_2; 
  Int_t jet55_1, jet65_1, jet80_1;
  Int_t jet55_p_1, jet65_p_1, jet80_p_1;
  Int_t jet55_2, jet65_2, jet80_2;
  Int_t jet55_p_2, jet65_p_2, jet80_p_2;
  Int_t hiBin_1, hiBin_2;
  Float_t weight_2;

  Data_matched->SetBranchAddress("calopt",&calopt_1);
  Data_matched->SetBranchAddress("pfpt",&pfpt_1);
  Data_matched->SetBranchAddress("eMax",&eMax_1);
  Data_matched->SetBranchAddress("phMax",&phMax_1);
  Data_matched->SetBranchAddress("muMax",&muMax_1);
  Data_matched->SetBranchAddress("neMax",&neMax_1);
  Data_matched->SetBranchAddress("chMax",&chMax_1);
  Data_matched->SetBranchAddress("chSum",&chSum_1);
  Data_matched->SetBranchAddress("phSum",&phSum_1);
  Data_matched->SetBranchAddress("neSum",&neSum_1);
  Data_matched->SetBranchAddress("muSum",&muSum_1);
  Data_matched->SetBranchAddress("eSum",&eSum_1);
  Data_matched->SetBranchAddress("hiBin",&hiBin_1);
  Data_matched->SetBranchAddress("jet55",&jet55_1);
  Data_matched->SetBranchAddress("jet65",&jet65_1);
  Data_matched->SetBranchAddress("jet80",&jet80_1);
  Data_matched->SetBranchAddress("jet55_prescl",&jet55_p_1);
  Data_matched->SetBranchAddress("jet65_prescl",&jet65_p_1);
  Data_matched->SetBranchAddress("jet80_prescl",&jet80_p_1);
  
  Data_unmatched->SetBranchAddress("pfpt",&pfpt_1);
  Data_unmatched->SetBranchAddress("eMax",&eMax_1);
  Data_unmatched->SetBranchAddress("phMax",&phMax_1);
  Data_unmatched->SetBranchAddress("muMax",&muMax_1);
  Data_unmatched->SetBranchAddress("neMax",&neMax_1);
  Data_unmatched->SetBranchAddress("chMax",&chMax_1);
  Data_unmatched->SetBranchAddress("chSum",&chSum_1);
  Data_unmatched->SetBranchAddress("phSum",&phSum_1);
  Data_unmatched->SetBranchAddress("neSum",&neSum_1);
  Data_unmatched->SetBranchAddress("muSum",&muSum_1);
  Data_unmatched->SetBranchAddress("eSum",&eSum_1);
  Data_unmatched->SetBranchAddress("hiBin",&hiBin_1);
  Data_unmatched->SetBranchAddress("jet55",&jet55_1);
  Data_unmatched->SetBranchAddress("jet65",&jet65_1);
  Data_unmatched->SetBranchAddress("jet80",&jet80_1);
  Data_unmatched->SetBranchAddress("jet55_prescl",&jet55_p_1);
  Data_unmatched->SetBranchAddress("jet65_prescl",&jet65_p_1);
  Data_unmatched->SetBranchAddress("jet80_prescl",&jet80_p_1);
  
  MC_matched->SetBranchAddress("calopt",&calopt_2);
  MC_matched->SetBranchAddress("pfpt",&pfpt_2);
  MC_matched->SetBranchAddress("eMax",&eMax_2);
  MC_matched->SetBranchAddress("phMax",&phMax_2);
  MC_matched->SetBranchAddress("muMax",&muMax_2);
  MC_matched->SetBranchAddress("neMax",&neMax_2);
  MC_matched->SetBranchAddress("chMax",&chMax_2);
  MC_matched->SetBranchAddress("chSum",&chSum_2);
  MC_matched->SetBranchAddress("phSum",&phSum_2);
  MC_matched->SetBranchAddress("neSum",&neSum_2);
  MC_matched->SetBranchAddress("muSum",&muSum_2);
  MC_matched->SetBranchAddress("eSum",&eSum_2);
  MC_matched->SetBranchAddress("hiBin",&hiBin_2);
  MC_matched->SetBranchAddress("weight",&weight_2);
  MC_matched->SetBranchAddress("pfrefpt",&pfrefpt_2);
  MC_matched->SetBranchAddress("jet55",&jet55_2);
  MC_matched->SetBranchAddress("jet65",&jet65_2);
  MC_matched->SetBranchAddress("jet80",&jet80_2);
  
  MC_unmatched->SetBranchAddress("pfpt",&pfpt_2);
  MC_unmatched->SetBranchAddress("eMax",&eMax_2);
  MC_unmatched->SetBranchAddress("phMax",&phMax_2);
  MC_unmatched->SetBranchAddress("muMax",&muMax_2);
  MC_unmatched->SetBranchAddress("neMax",&neMax_2);
  MC_unmatched->SetBranchAddress("chMax",&chMax_2);
  MC_unmatched->SetBranchAddress("chSum",&chSum_2);
  MC_unmatched->SetBranchAddress("phSum",&phSum_2);
  MC_unmatched->SetBranchAddress("neSum",&neSum_2);
  MC_unmatched->SetBranchAddress("muSum",&muSum_2);
  MC_unmatched->SetBranchAddress("eSum",&eSum_2);
  MC_unmatched->SetBranchAddress("hiBin",&hiBin_2);
  MC_unmatched->SetBranchAddress("weight",&weight_2);
  MC_unmatched->SetBranchAddress("pfrefpt",&pfrefpt_2);
  MC_unmatched->SetBranchAddress("jet55",&jet55_2);
  MC_unmatched->SetBranchAddress("jet65",&jet65_2);
  MC_unmatched->SetBranchAddress("jet80",&jet80_2);
  
  
  // data loop
  long entries = Data_matched->GetEntries();
  //entries = 1;
  cout<<"matched Data ntuple: "<<entries<<" entries"<<endl;
  for(long nentry = 0; nentry < entries; ++nentry){
    
    if(nentry%10000 == 0) cout<<" nentry = "<<nentry<<endl;
    Data_matched->GetEntry(nentry);
    if(hiBin_1>=180) continue;
    int centb1=-1;	
    centb1 = findBin(hiBin_1);
    Float_t Sumcand = chSum_1 + phSum_1 + neSum_1 + muSum_1;
    if(pfpt_1>pfptmin){
         hData_chMaxJtpt[centb1]->Fill(chMax_1/pfpt_1);
         hData_eMaxJtpt[centb1]->Fill(eMax_1/pfpt_1);
         hData_neMaxJtpt[centb1]->Fill(neMax_1/pfpt_1);
         hData_phMaxJtpt[centb1]->Fill(phMax_1/pfpt_1);
         hData_muMaxJtpt[centb1]->Fill(muMax_1/pfpt_1);
         hData_chSumJtpt[centb1]->Fill(chSum_1/pfpt_1);
         hData_eSumJtpt[centb1]->Fill(eSum_1/pfpt_1);
         hData_neSumJtpt[centb1]->Fill(neSum_1/pfpt_1);
         hData_phSumJtpt[centb1]->Fill(phSum_1/pfpt_1);
         hData_muSumJtpt[centb1]->Fill(muSum_1/pfpt_1);
   if((calopt_1/pfpt_1) <= 0.5 && eMax_1/Sumcand < 0.05 ) {
         hData_chMaxJtpt_keep[centb1]->Fill(chMax_1/pfpt_1);
         hData_eMaxJtpt_keep[centb1]->Fill(eMax_1/pfpt_1);
         hData_neMaxJtpt_keep[centb1]->Fill(neMax_1/pfpt_1);
         hData_phMaxJtpt_keep[centb1]->Fill(phMax_1/pfpt_1);
         hData_muMaxJtpt_keep[centb1]->Fill(muMax_1/pfpt_1);
         hData_chSumJtpt_keep[centb1]->Fill(chSum_1/pfpt_1);
         hData_eSumJtpt_keep[centb1]->Fill(eSum_1/pfpt_1);
         hData_neSumJtpt_keep[centb1]->Fill(neSum_1/pfpt_1);
         hData_phSumJtpt_keep[centb1]->Fill(phSum_1/pfpt_1);
         hData_muSumJtpt_keep[centb1]->Fill(muSum_1/pfpt_1);
   }
   if((calopt_1/pfpt_1) > 0.5 && calopt_1/pfpt_1 <= 0.85 && eMax_1/Sumcand < (18/7 *(Float_t)calopt_1/pfpt_1 - 9/7)){
         hData_chMaxJtpt_keep[centb1]->Fill(chMax_1/pfpt_1);
         hData_eMaxJtpt_keep[centb1]->Fill(eMax_1/pfpt_1);
         hData_neMaxJtpt_keep[centb1]->Fill(neMax_1/pfpt_1);
         hData_phMaxJtpt_keep[centb1]->Fill(phMax_1/pfpt_1);
         hData_muMaxJtpt_keep[centb1]->Fill(muMax_1/pfpt_1);
         hData_chSumJtpt_keep[centb1]->Fill(chSum_1/pfpt_1);
         hData_eSumJtpt_keep[centb1]->Fill(eSum_1/pfpt_1);
         hData_neSumJtpt_keep[centb1]->Fill(neSum_1/pfpt_1);
         hData_phSumJtpt_keep[centb1]->Fill(phSum_1/pfpt_1);
         hData_muSumJtpt_keep[centb1]->Fill(muSum_1/pfpt_1);
   }
   if(calopt_1/pfpt_1 > 0.85){
         hData_chMaxJtpt_keep[centb1]->Fill(chMax_1/pfpt_1);
         hData_eMaxJtpt_keep[centb1]->Fill(eMax_1/pfpt_1);
         hData_neMaxJtpt_keep[centb1]->Fill(neMax_1/pfpt_1);
         hData_phMaxJtpt_keep[centb1]->Fill(phMax_1/pfpt_1);
         hData_muMaxJtpt_keep[centb1]->Fill(muMax_1/pfpt_1);
         hData_chSumJtpt_keep[centb1]->Fill(chSum_1/pfpt_1);
         hData_eSumJtpt_keep[centb1]->Fill(eSum_1/pfpt_1);
         hData_neSumJtpt_keep[centb1]->Fill(neSum_1/pfpt_1);
         hData_phSumJtpt_keep[centb1]->Fill(phSum_1/pfpt_1);
         hData_muSumJtpt_keep[centb1]->Fill(muSum_1/pfpt_1);
   }
// rejected:
  if(calopt_1/pfpt_1 > 0.5 && calopt_1/pfpt_1 <= 0.85 && (eMax_1/Sumcand >= (18/7 *(Float_t)calopt_1/pfpt_1 - 9/7))){
         hData_chMaxJtpt_rej[centb1]->Fill(chMax_1/pfpt_1);
         hData_eMaxJtpt_rej[centb1]->Fill(eMax_1/pfpt_1);
         hData_neMaxJtpt_rej[centb1]->Fill(neMax_1/pfpt_1);
         hData_phMaxJtpt_rej[centb1]->Fill(phMax_1/pfpt_1);
         hData_muMaxJtpt_rej[centb1]->Fill(muMax_1/pfpt_1);
         hData_chSumJtpt_rej[centb1]->Fill(chSum_1/pfpt_1);
         hData_eSumJtpt_rej[centb1]->Fill(eSum_1/pfpt_1);
         hData_neSumJtpt_rej[centb1]->Fill(neSum_1/pfpt_1);
         hData_phSumJtpt_rej[centb1]->Fill(phSum_1/pfpt_1);
         hData_muSumJtpt_rej[centb1]->Fill(muSum_1/pfpt_1);
   }
   if(calopt_1/pfpt_1 <= 0.5 && eMax_1/Sumcand >= 0.05) {
         hData_chMaxJtpt_rej[centb1]->Fill(chMax_1/pfpt_1);
         hData_eMaxJtpt_rej[centb1]->Fill(eMax_1/pfpt_1);
         hData_neMaxJtpt_rej[centb1]->Fill(neMax_1/pfpt_1);
         hData_phMaxJtpt_rej[centb1]->Fill(phMax_1/pfpt_1);
         hData_muMaxJtpt_rej[centb1]->Fill(muMax_1/pfpt_1);
         hData_chSumJtpt_rej[centb1]->Fill(chSum_1/pfpt_1);
         hData_eSumJtpt_rej[centb1]->Fill(eSum_1/pfpt_1);
         hData_neSumJtpt_rej[centb1]->Fill(neSum_1/pfpt_1);
         hData_phSumJtpt_rej[centb1]->Fill(phSum_1/pfpt_1);
         hData_muSumJtpt_rej[centb1]->Fill(muSum_1/pfpt_1);
   }

    } // end pfptmin loop
  } // end data matched loop

  
  // data unmatched loop:
  long duentries = Data_unmatched->GetEntries();
  //entries = 1;
  cout<<"Unmatched Data ntuple: "<<duentries<<" entries"<<endl;
  for(long unentry = 0; unentry < duentries; ++unentry ){

    if(unentry%10000 == 0) cout<<" unentry = "<<unentry<<endl;
    Data_unmatched->GetEntry(unentry);
    if(hiBin_1>=180) continue;
    centb1=-1;	
    centb1 = findBin(hiBin_1);
    Float_t Sumcand = chSum_1 + phSum_1 + neSum_1 + muSum_1;
    if(pfpt_1>pfptmin){
         hData_chMaxJtpt[centb1]->Fill(chMax_1/pfpt_1);
         hData_eMaxJtpt[centb1]->Fill(eMax_1/pfpt_1);
         hData_neMaxJtpt[centb1]->Fill(neMax_1/pfpt_1);
         hData_phMaxJtpt[centb1]->Fill(phMax_1/pfpt_1);
         hData_muMaxJtpt[centb1]->Fill(muMax_1/pfpt_1);
         hData_chSumJtpt[centb1]->Fill(chSum_1/pfpt_1);
         hData_eSumJtpt[centb1]->Fill(eSum_1/pfpt_1);
         hData_neSumJtpt[centb1]->Fill(neSum_1/pfpt_1);
         hData_phSumJtpt[centb1]->Fill(phSum_1/pfpt_1);
         hData_muSumJtpt[centb1]->Fill(muSum_1/pfpt_1);
    if(eMax_1/Sumcand < 0.05) {
         hData_chMaxJtpt_keep[centb1]->Fill(chMax_1/pfpt_1);
         hData_eMaxJtpt_keep[centb1]->Fill(eMax_1/pfpt_1);
         hData_neMaxJtpt_keep[centb1]->Fill(neMax_1/pfpt_1);
         hData_phMaxJtpt_keep[centb1]->Fill(phMax_1/pfpt_1);
         hData_muMaxJtpt_keep[centb1]->Fill(muMax_1/pfpt_1);
         hData_chSumJtpt_keep[centb1]->Fill(chSum_1/pfpt_1);
         hData_eSumJtpt_keep[centb1]->Fill(eSum_1/pfpt_1);
         hData_neSumJtpt_keep[centb1]->Fill(neSum_1/pfpt_1);
         hData_phSumJtpt_keep[centb1]->Fill(phSum_1/pfpt_1);
         hData_muSumJtpt_keep[centb1]->Fill(muSum_1/pfpt_1);         
    }
    if(eMax_1/Sumcand >= 0.05 ) {
         hData_chMaxJtpt_rej[centb1]->Fill(chMax_1/pfpt_1);
         hData_eMaxJtpt_rej[centb1]->Fill(eMax_1/pfpt_1);
         hData_neMaxJtpt_rej[centb1]->Fill(neMax_1/pfpt_1);
         hData_phMaxJtpt_rej[centb1]->Fill(phMax_1/pfpt_1);
         hData_muMaxJtpt_rej[centb1]->Fill(muMax_1/pfpt_1);
         hData_chSumJtpt_rej[centb1]->Fill(chSum_1/pfpt_1);
         hData_eSumJtpt_rej[centb1]->Fill(eSum_1/pfpt_1);
         hData_neSumJtpt_rej[centb1]->Fill(neSum_1/pfpt_1);
         hData_phSumJtpt_rej[centb1]->Fill(phSum_1/pfpt_1);
         hData_muSumJtpt_rej[centb1]->Fill(muSum_1/pfpt_1);        
    }  
    } // end pfptmin loop
  } // end Data unmatched loop


  
  long mentries = MC_matched->GetEntries();
  //entries = 1;
  // MC loop
  cout<<" looking at matched MC ntuple: "<<mentries<<" entries"<<endl;
  for(long mnentry = 0; mnentry < mentries; ++mnentry){

    if(mnentry%10000 == 0) cout<<" mnentry = "<<mnentry<<endl;
    MC_matched->GetEntry(mnentry);
    if(hiBin_2>=180) continue;
    int centb2=-1;	
    centb2 = findBin(hiBin_2); 
//    cout<<"my hiBin_2 is: "<<hiBin_2<<" and I got out the bin: "<<centb2<<endl;
    Float_t Sumcand = chSum_2 + phSum_2 + neSum_2 + muSum_2;
    if(pfpt_2>pfptmin){
         hMC_chMaxJtpt[centb2]->Fill(chMax_2/pfpt_2,weight_2);
         hMC_eMaxJtpt[centb2]->Fill(eMax_2/pfpt_2,weight_2);
         hMC_neMaxJtpt[centb2]->Fill(neMax_2/pfpt_2,weight_2);
         hMC_phMaxJtpt[centb2]->Fill(phMax_2/pfpt_2,weight_2);
         hMC_muMaxJtpt[centb2]->Fill(muMax_2/pfpt_2,weight_2);
         hMC_chSumJtpt[centb2]->Fill(chSum_2/pfpt_2,weight_2);
         hMC_eSumJtpt[centb2]->Fill(eSum_2/pfpt_2,weight_2);
         hMC_neSumJtpt[centb2]->Fill(neSum_2/pfpt_2,weight_2);
         hMC_phSumJtpt[centb2]->Fill(phSum_2/pfpt_2,weight_2);
         hMC_muSumJtpt[centb2]->Fill(muSum_2/pfpt_2,weight_2);       
   if(calopt_2/pfpt_2 <= 0.5 && eMax_2/Sumcand < 0.05) {
         hMC_chMaxJtpt_keep[centb2]->Fill(chMax_2/pfpt_2,weight_2);
         hMC_eMaxJtpt_keep[centb2]->Fill(eMax_2/pfpt_2,weight_2);
         hMC_neMaxJtpt_keep[centb2]->Fill(neMax_2/pfpt_2,weight_2);
         hMC_phMaxJtpt_keep[centb2]->Fill(phMax_2/pfpt_2,weight_2);
         hMC_muMaxJtpt_keep[centb2]->Fill(muMax_2/pfpt_2,weight_2);
         hMC_chSumJtpt_keep[centb2]->Fill(chSum_2/pfpt_2,weight_2);
         hMC_eSumJtpt_keep[centb2]->Fill(eSum_2/pfpt_2,weight_2);
         hMC_neSumJtpt_keep[centb2]->Fill(neSum_2/pfpt_2,weight_2);
         hMC_phSumJtpt_keep[centb2]->Fill(phSum_2/pfpt_2,weight_2);
         hMC_muSumJtpt_keep[centb2]->Fill(muSum_2/pfpt_2,weight_2);        
   }
   if(calopt_2/pfpt_2 > 0.5 && calopt_2/pfpt_2 <= 0.85 && eMax_2/Sumcand < (18/7 *(Float_t)calopt_2/pfpt_2 - 9/7)){
         hMC_chMaxJtpt_keep[centb2]->Fill(chMax_2/pfpt_2,weight_2);
         hMC_eMaxJtpt_keep[centb2]->Fill(eMax_2/pfpt_2,weight_2);
         hMC_neMaxJtpt_keep[centb2]->Fill(neMax_2/pfpt_2,weight_2);
         hMC_phMaxJtpt_keep[centb2]->Fill(phMax_2/pfpt_2,weight_2);
         hMC_muMaxJtpt_keep[centb2]->Fill(muMax_2/pfpt_2,weight_2);
         hMC_chSumJtpt_keep[centb2]->Fill(chSum_2/pfpt_2,weight_2);
         hMC_eSumJtpt_keep[centb2]->Fill(eSum_2/pfpt_2,weight_2);
         hMC_neSumJtpt_keep[centb2]->Fill(neSum_2/pfpt_2,weight_2);
         hMC_phSumJtpt_keep[centb2]->Fill(phSum_2/pfpt_2,weight_2);
         hMC_muSumJtpt_keep[centb2]->Fill(muSum_2/pfpt_2,weight_2);         
   }
   if(calopt_2/pfpt_2 > 0.85){
         hMC_chMaxJtpt_keep[centb2]->Fill(chMax_2/pfpt_2,weight_2);
         hMC_eMaxJtpt_keep[centb2]->Fill(eMax_2/pfpt_2,weight_2);
         hMC_neMaxJtpt_keep[centb2]->Fill(neMax_2/pfpt_2,weight_2);
         hMC_phMaxJtpt_keep[centb2]->Fill(phMax_2/pfpt_2,weight_2);
         hMC_muMaxJtpt_keep[centb2]->Fill(muMax_2/pfpt_2,weight_2);
         hMC_chSumJtpt_keep[centb2]->Fill(chSum_2/pfpt_2,weight_2);
         hMC_eSumJtpt_keep[centb2]->Fill(eSum_2/pfpt_2,weight_2);
         hMC_neSumJtpt_keep[centb2]->Fill(neSum_2/pfpt_2,weight_2);
         hMC_phSumJtpt_keep[centb2]->Fill(phSum_2/pfpt_2,weight_2);
         hMC_muSumJtpt_keep[centb2]->Fill(muSum_2/pfpt_2,weight_2);        
   }
// rejected:
  if(calopt_2/pfpt_2 > 0.5 && calopt_2/pfpt_2 <= 0.85 && eMax_2/Sumcand >= (18/7 *(Float_t)calopt_2/pfpt_2 - 9/7)){
         hMC_chMaxJtpt_rej[centb2]->Fill(chMax_2/pfpt_2,weight_2);
         hMC_eMaxJtpt_rej[centb2]->Fill(eMax_2/pfpt_2,weight_2);
         hMC_neMaxJtpt_rej[centb2]->Fill(neMax_2/pfpt_2,weight_2);
         hMC_phMaxJtpt_rej[centb2]->Fill(phMax_2/pfpt_2,weight_2);
         hMC_muMaxJtpt_rej[centb2]->Fill(muMax_2/pfpt_2,weight_2);
         hMC_chSumJtpt_rej[centb2]->Fill(chSum_2/pfpt_2,weight_2);
         hMC_eSumJtpt_rej[centb2]->Fill(eSum_2/pfpt_2,weight_2);
         hMC_neSumJtpt_rej[centb2]->Fill(neSum_2/pfpt_2,weight_2);
         hMC_phSumJtpt_rej[centb2]->Fill(phSum_2/pfpt_2,weight_2);
         hMC_muSumJtpt_rej[centb2]->Fill(muSum_2/pfpt_2,weight_2);        
   }
   if(calopt_2/pfpt_2 <= 0.5 && eMax_2/Sumcand >= 0.05) {
         hMC_chMaxJtpt_rej[centb2]->Fill(chMax_2/pfpt_2,weight_2);
         hMC_eMaxJtpt_rej[centb2]->Fill(eMax_2/pfpt_2,weight_2);
         hMC_neMaxJtpt_rej[centb2]->Fill(neMax_2/pfpt_2,weight_2);
         hMC_phMaxJtpt_rej[centb2]->Fill(phMax_2/pfpt_2,weight_2);
         hMC_muMaxJtpt_rej[centb2]->Fill(muMax_2/pfpt_2,weight_2);
         hMC_chSumJtpt_rej[centb2]->Fill(chSum_2/pfpt_2,weight_2);
         hMC_eSumJtpt_rej[centb2]->Fill(eSum_2/pfpt_2,weight_2);
         hMC_neSumJtpt_rej[centb2]->Fill(neSum_2/pfpt_2,weight_2);
         hMC_phSumJtpt_rej[centb2]->Fill(phSum_2/pfpt_2,weight_2);
         hMC_muSumJtpt_rej[centb2]->Fill(muSum_2/pfpt_2,weight_2);      
   }
       } // end pfptmin loop
  } // end MC matched loop


  
  long muentries = MC_unmatched->GetEntries();
  //entries = 1;
  // MC loop
  cout<<" looking at unmatched MC ntuple: "<<muentries<<" entries"<<endl;
  for(long munentry = 0; munentry < muentries; ++munentry){

    if(munentry%10000 == 0) cout<<" munentry = "<<munentry<<endl;
    MC_unmatched->GetEntry(munentry);
    if(hiBin_2>=180) continue;
    centb2=-1;	
    centb2 = findBin(hiBin_2);   
    Float_t Sumcand = chSum_2 + phSum_2 + neSum_2 + muSum_2;
    if(pfpt_2>pfptmin){
         hMC_chMaxJtpt[centb2]->Fill(chMax_2/pfpt_2,weight_2);
         hMC_eMaxJtpt[centb2]->Fill(eMax_2/pfpt_2,weight_2);
         hMC_neMaxJtpt[centb2]->Fill(neMax_2/pfpt_2,weight_2);
         hMC_phMaxJtpt[centb2]->Fill(phMax_2/pfpt_2,weight_2);
         hMC_muMaxJtpt[centb2]->Fill(muMax_2/pfpt_2,weight_2);
         hMC_chSumJtpt[centb2]->Fill(chSum_2/pfpt_2,weight_2);
         hMC_eSumJtpt[centb2]->Fill(eSum_2/pfpt_2,weight_2);
         hMC_neSumJtpt[centb2]->Fill(neSum_2/pfpt_2,weight_2);
         hMC_phSumJtpt[centb2]->Fill(phSum_2/pfpt_2,weight_2);
         hMC_muSumJtpt[centb2]->Fill(muSum_2/pfpt_2,weight_2);      
    if(eMax_2/Sumcand < 0.05) {
         hMC_chMaxJtpt_keep[centb2]->Fill(chMax_2/pfpt_2,weight_2);
         hMC_eMaxJtpt_keep[centb2]->Fill(eMax_2/pfpt_2,weight_2);
         hMC_neMaxJtpt_keep[centb2]->Fill(neMax_2/pfpt_2,weight_2);
         hMC_phMaxJtpt_keep[centb2]->Fill(phMax_2/pfpt_2,weight_2);
         hMC_muMaxJtpt_keep[centb2]->Fill(muMax_2/pfpt_2,weight_2);
         hMC_chSumJtpt_keep[centb2]->Fill(chSum_2/pfpt_2,weight_2);
         hMC_eSumJtpt_keep[centb2]->Fill(eSum_2/pfpt_2,weight_2);
         hMC_neSumJtpt_keep[centb2]->Fill(neSum_2/pfpt_2,weight_2);
         hMC_phSumJtpt_keep[centb2]->Fill(phSum_2/pfpt_2,weight_2);
         hMC_muSumJtpt_keep[centb2]->Fill(muSum_2/pfpt_2,weight_2);       
    }
    if(eMax_2/Sumcand >= 0.05) {
         hMC_chMaxJtpt_rej[centb2]->Fill(chMax_2/pfpt_2,weight_2);
         hMC_eMaxJtpt_rej[centb2]->Fill(eMax_2/pfpt_2,weight_2);
         hMC_neMaxJtpt_rej[centb2]->Fill(neMax_2/pfpt_2,weight_2);
         hMC_phMaxJtpt_rej[centb2]->Fill(phMax_2/pfpt_2,weight_2);
         hMC_muMaxJtpt_rej[centb2]->Fill(muMax_2/pfpt_2,weight_2);
         hMC_chSumJtpt_rej[centb2]->Fill(chSum_2/pfpt_2,weight_2);
         hMC_eSumJtpt_rej[centb2]->Fill(eSum_2/pfpt_2,weight_2);
         hMC_neSumJtpt_rej[centb2]->Fill(neSum_2/pfpt_2,weight_2);
         hMC_phSumJtpt_rej[centb2]->Fill(phSum_2/pfpt_2,weight_2);
         hMC_muSumJtpt_rej[centb2]->Fill(muSum_2/pfpt_2,weight_2);      
    }  
    } // end pfptmin loop
  } // end MC unmatched loop

 /// end of looking at matched and unmatched, now to plot!!! 
// save those histos to a root file, remembering that I did DrawNormalized, so they are not normalized in the root file!  
  TFile fout("PbPb_JetIDPlots_NoCuts_and_YetkinCuts_matchedAndUn_slantedlinecalopfpt_eMaxSumcand_A_R4.root","RECREATE");
  for(int i = 0 ; i < nbins_cent ; ++i){

    hData_chMaxJtpt[i]->Write();
    hMC_chMaxJtpt[i]->Write();
    hData_chSumJtpt[i]->Write();
    hMC_chSumJtpt[i]->Write();
    hData_eMaxJtpt[i]->Write();
    hMC_eMaxJtpt[i]->Write();
    hData_eSumJtpt[i]->Write();
    hMC_eSumJtpt[i]->Write();
    hData_neMaxJtpt[i]->Write();
    hMC_neMaxJtpt[i]->Write();
    hData_neSumJtpt[i]->Write();
    hMC_neSumJtpt[i]->Write();
    hData_phMaxJtpt[i]->Write();
    hMC_phMaxJtpt[i]->Write();
    hData_phSumJtpt[i]->Write();
    hMC_phSumJtpt[i]->Write();
    hData_muMaxJtpt[i]->Write();
    hMC_muMaxJtpt[i]->Write();
    hData_muSumJtpt[i]->Write();
    hMC_muSumJtpt[i]->Write();
    
    hData_chMaxJtpt_keep[i]->Write();
    hMC_chMaxJtpt_keep[i]->Write();
    hData_chSumJtpt_keep[i]->Write();
    hMC_chSumJtpt_keep[i]->Write();
    hData_eMaxJtpt_keep[i]->Write();
    hMC_eMaxJtpt_keep[i]->Write();
    hData_eSumJtpt_keep[i]->Write();
    hMC_eSumJtpt_keep[i]->Write();
    hData_neMaxJtpt_keep[i]->Write();
    hMC_neMaxJtpt_keep[i]->Write();
    hData_neSumJtpt_keep[i]->Write();
    hMC_neSumJtpt_keep[i]->Write();
    hData_phMaxJtpt_keep[i]->Write();
    hMC_phMaxJtpt_keep[i]->Write();
    hData_phSumJtpt_keep[i]->Write();
    hMC_phSumJtpt_keep[i]->Write();
    hData_muMaxJtpt_keep[i]->Write();
    hMC_muMaxJtpt_keep[i]->Write();
    hData_muSumJtpt_keep[i]->Write();
    hMC_muSumJtpt_keep[i]->Write();
    
    hData_chMaxJtpt_rej[i]->Write();
    hMC_chMaxJtpt_rej[i]->Write();
    hData_chSumJtpt_rej[i]->Write();
    hMC_chSumJtpt_rej[i]->Write();
    hData_eMaxJtpt_rej[i]->Write();
    hMC_eMaxJtpt_rej[i]->Write();
    hData_eSumJtpt_rej[i]->Write();
    hMC_eSumJtpt_rej[i]->Write();
    hData_neMaxJtpt_rej[i]->Write();
    hMC_neMaxJtpt_rej[i]->Write();
    hData_neSumJtpt_rej[i]->Write();
    hMC_neSumJtpt_rej[i]->Write();
    hData_phMaxJtpt_rej[i]->Write();
    hMC_phMaxJtpt_rej[i]->Write();
    hData_phSumJtpt_rej[i]->Write();
    hMC_phSumJtpt_rej[i]->Write();
    hData_muMaxJtpt_rej[i]->Write();
    hMC_muMaxJtpt_rej[i]->Write();
    hData_muSumJtpt_rej[i]->Write();
    hMC_muSumJtpt_rej[i]->Write();
  }  
 
// now plot
  TCanvas * cchMaxJtpt[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchMaxJtpt[i] = new TCanvas(Form("cchMaxJtpt_cent%d",i),"",800,600);
    cchMaxJtpt[i]->SetLogy();
    hMC_chMaxJtpt[i]->SetMarkerColor(kRed);
    hMC_chMaxJtpt[i]->SetMarkerStyle(25);
    hMC_chMaxJtpt[i]->Print("base");
    hMC_chMaxJtpt[i]->SetTitle(" ");
    hMC_chMaxJtpt[i]->SetXTitle("chMax/(ak4PuPF jet p_{T}) no cuts");
    hMC_chMaxJtpt[i]->DrawNormalized();

    hData_chMaxJtpt[i]->SetMarkerStyle(24);
    hData_chMaxJtpt[i]->SetMarkerColor(kBlack);
    hData_chMaxJtpt[i]->DrawNormalized("same");
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chMaxJtpt[0],"MC","pl");
    leg->AddEntry(hData_chMaxJtpt[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchMaxJtpt[i]->SaveAs(Form("chMaxJtpt_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }
  
  TCanvas * ceMaxJtpt[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceMaxJtpt[i] = new TCanvas(Form("ceMaxJtpt_cent%d",i),"",800,600);
    ceMaxJtpt[i]->SetLogy();
    hMC_eMaxJtpt[i]->SetMarkerColor(kBlue);
    hMC_eMaxJtpt[i]->SetMarkerStyle(25);
    hMC_eMaxJtpt[i]->Print("base");
    hMC_eMaxJtpt[i]->SetTitle(" ");
    hMC_eMaxJtpt[i]->SetXTitle("eMax/(ak4PuPF jet p_{T}) no cuts");
    hMC_eMaxJtpt[i]->DrawNormalized();

    hData_eMaxJtpt[i]->SetMarkerStyle(24);
    hData_eMaxJtpt[i]->SetMarkerColor(kBlack);
    hData_eMaxJtpt[i]->DrawNormalized("same");
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eMaxJtpt[0],"MC","pl");
    leg->AddEntry(hData_eMaxJtpt[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceMaxJtpt[i]->SaveAs(Form("eMaxJtpt_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }

   TCanvas * cphMaxJtpt[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphMaxJtpt[i] = new TCanvas(Form("cphMaxJtpt_cent%d",i),"",800,600);
    cphMaxJtpt[i]->SetLogy();
    hMC_phMaxJtpt[i]->SetMarkerColor(kGreen+2);
    hMC_phMaxJtpt[i]->SetMarkerStyle(25);
    hMC_phMaxJtpt[i]->Print("base");
    hMC_phMaxJtpt[i]->SetTitle(" ");
    hMC_phMaxJtpt[i]->SetXTitle("phMax/(ak4PuPF jet p_{T}) no cuts");
    hMC_phMaxJtpt[i]->DrawNormalized();

    hData_phMaxJtpt[i]->SetMarkerStyle(24);
    hData_phMaxJtpt[i]->SetMarkerColor(kBlack);
    hData_phMaxJtpt[i]->DrawNormalized("same");
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phMaxJtpt[0],"MC","pl");
    leg->AddEntry(hData_phMaxJtpt[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphMaxJtpt[i]->SaveAs(Form("phMaxJtpt_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }
  TCanvas * cneMaxJtpt[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneMaxJtpt[i] = new TCanvas(Form("cneMaxJtpt_cent%d",i),"",800,600);
    cneMaxJtpt[i]->SetLogy();
    hMC_neMaxJtpt[i]->SetMarkerColor(kMagenta);
    hMC_neMaxJtpt[i]->SetMarkerStyle(25);
    hMC_neMaxJtpt[i]->Print("base");
    hMC_neMaxJtpt[i]->SetTitle(" ");
    hMC_neMaxJtpt[i]->SetXTitle("neMax/(ak4PuPF jet p_{T}) no cuts");
    hMC_neMaxJtpt[i]->DrawNormalized();

    hData_neMaxJtpt[i]->SetMarkerStyle(24);
    hData_neMaxJtpt[i]->SetMarkerColor(kBlack);
    hData_neMaxJtpt[i]->DrawNormalized("same");
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neMaxJtpt[0],"MC","pl");
    leg->AddEntry(hData_neMaxJtpt[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneMaxJtpt[i]->SaveAs(Form("neMaxJtpt_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }
    TCanvas * cmuMaxJtpt[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuMaxJtpt[i] = new TCanvas(Form("cmuMaxJtpt_cent%d",i),"",800,600);
    cmuMaxJtpt[i]->SetLogy();
    hMC_muMaxJtpt[i]->SetMarkerColor(kCyan);
    hMC_muMaxJtpt[i]->SetMarkerStyle(25);
    hMC_muMaxJtpt[i]->Print("base");
    hMC_muMaxJtpt[i]->SetTitle(" ");
    hMC_muMaxJtpt[i]->SetXTitle("muMax/(ak4PuPF jet p_{T}) no cuts");
    hMC_muMaxJtpt[i]->DrawNormalized();

    hData_muMaxJtpt[i]->SetMarkerStyle(24);
    hData_muMaxJtpt[i]->SetMarkerColor(kBlack);
    hData_muMaxJtpt[i]->DrawNormalized("same");
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muMaxJtpt[0],"MC","pl");
    leg->AddEntry(hData_muMaxJtpt[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuMaxJtpt[i]->SaveAs(Form("muMaxJtpt_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }    
// draw some Sum variables
  TCanvas * cchSumJtpt[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchSumJtpt[i] = new TCanvas(Form("cchSumJtpt_cent%d",i),"",800,600);
    cchSumJtpt[i]->SetLogy();
    hMC_chSumJtpt[i]->SetMarkerColor(kRed+1);
    hMC_chSumJtpt[i]->SetMarkerStyle(25);
    hMC_chSumJtpt[i]->Print("base");
    hMC_chSumJtpt[i]->SetTitle(" ");
    hMC_chSumJtpt[i]->SetXTitle("chSum/(ak4PuPF jet p_{T}) no cuts");
    hMC_chSumJtpt[i]->DrawNormalized();

    hData_chSumJtpt[i]->SetMarkerStyle(24);
    hData_chSumJtpt[i]->SetMarkerColor(kBlack);
    hData_chSumJtpt[i]->DrawNormalized("same");
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chSumJtpt[0],"MC","pl");
    leg->AddEntry(hData_chSumJtpt[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchSumJtpt[i]->SaveAs(Form("chSumJtpt_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }
  TCanvas * ceSumJtpt[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceSumJtpt[i] = new TCanvas(Form("ceSumJtpt_cent%d",i),"",800,600);
    ceSumJtpt[i]->SetLogy();
    hMC_eSumJtpt[i]->SetMarkerColor(kBlue+1);
    hMC_eSumJtpt[i]->SetMarkerStyle(25);
    hMC_eSumJtpt[i]->Print("base");
    hMC_eSumJtpt[i]->SetTitle(" ");
    hMC_eSumJtpt[i]->SetXTitle("eSum/(ak4PuPF jet p_{T}) no cuts");
    hMC_eSumJtpt[i]->DrawNormalized();

    hData_eSumJtpt[i]->SetMarkerStyle(24);
    hData_eSumJtpt[i]->SetMarkerColor(kBlack);
    hData_eSumJtpt[i]->DrawNormalized("same");
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eSumJtpt[0],"MC","pl");
    leg->AddEntry(hData_eSumJtpt[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceSumJtpt[i]->SaveAs(Form("eSumJtpt_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }
  TCanvas * cphSumJtpt[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphSumJtpt[i] = new TCanvas(Form("cphSumJtpt_cent%d",i),"",800,600);
    cphSumJtpt[i]->SetLogy();
    hMC_phSumJtpt[i]->SetMarkerColor(kGreen-3);
    hMC_phSumJtpt[i]->SetMarkerStyle(25);
    hMC_phSumJtpt[i]->Print("base");
    hMC_phSumJtpt[i]->SetTitle(" ");
    hMC_phSumJtpt[i]->SetXTitle("phSum/(ak4PuPF jet p_{T}) no cuts");
    hMC_phSumJtpt[i]->DrawNormalized();

    hData_phSumJtpt[i]->SetMarkerStyle(24);
    hData_phSumJtpt[i]->SetMarkerColor(kBlack);
    hData_phSumJtpt[i]->DrawNormalized("same");
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phSumJtpt[0],"MC","pl");
    leg->AddEntry(hData_phSumJtpt[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphSumJtpt[i]->SaveAs(Form("phSumJtpt_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }
  TCanvas * cneSumJtpt[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneSumJtpt[i] = new TCanvas(Form("cneSumJtpt_cent%d",i),"",800,600);
    cneSumJtpt[i]->SetLogy();
    hMC_neSumJtpt[i]->SetMarkerColor(kMagenta+1);
    hMC_neSumJtpt[i]->SetMarkerStyle(25);
    hMC_neSumJtpt[i]->Print("base");
    hMC_neSumJtpt[i]->SetTitle(" ");
    hMC_neSumJtpt[i]->SetXTitle("neSum/(ak4PuPF jet p_{T}) no cuts");
    hMC_neSumJtpt[i]->DrawNormalized();

    hData_neSumJtpt[i]->SetMarkerStyle(24);
    hData_neSumJtpt[i]->SetMarkerColor(kBlack);
    hData_neSumJtpt[i]->DrawNormalized("same");
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neSumJtpt[0],"MC","pl");
    leg->AddEntry(hData_neSumJtpt[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneSumJtpt[i]->SaveAs(Form("neSumJtpt_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }
    TCanvas * cmuSumJtpt[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuSumJtpt[i] = new TCanvas(Form("cmuSumJtpt_cent%d",i),"",800,600);
    cmuSumJtpt[i]->SetLogy();
    hMC_muSumJtpt[i]->SetMarkerColor(kCyan+1);
    hMC_muSumJtpt[i]->SetMarkerStyle(25);
    hMC_muSumJtpt[i]->Print("base");
    hMC_muSumJtpt[i]->SetTitle(" ");
    hMC_muSumJtpt[i]->SetXTitle("muSum/(ak4PuPF jet p_{T}) no cuts");
    hMC_muSumJtpt[i]->DrawNormalized();

    hData_muSumJtpt[i]->SetMarkerStyle(24);
    hData_muSumJtpt[i]->SetMarkerColor(kBlack);
    hData_muSumJtpt[i]->DrawNormalized("same");
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muSumJtpt[0],"MC","pl");
    leg->AddEntry(hData_muSumJtpt[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuSumJtpt[i]->SaveAs(Form("muSumJtpt_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }    

  TCanvas * cchMaxJtpt_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchMaxJtpt_keep[i] = new TCanvas(Form("cchMaxJtpt_keep_cent%d",i),"",800,600);
    cchMaxJtpt_keep[i]->SetLogy();
    hMC_chMaxJtpt_keep[i]->SetMarkerColor(kRed);
    hMC_chMaxJtpt_keep[i]->SetMarkerStyle(25);
    hMC_chMaxJtpt_keep[i]->Print("base");
    hMC_chMaxJtpt_keep[i]->SetTitle(" ");
    hMC_chMaxJtpt_keep[i]->SetXTitle("chMax/(ak4PuPF jet p_{T}) pass CutA");
    nMC_chMaxJtpt_keep[i]=hMC_chMaxJtpt_keep[i]->GetEntries();
    if (nMC_chMaxJtpt_keep[i]>0){
       hMC_chMaxJtpt_keep[i]->DrawNormalized();
    } else { cout<<"hMC_chMaxJtpt_keep[i] for i= "<<i<<" has "<<nMC_chMaxJtpt_keep[i]<<" entries and is not drawn"<<endl; }

    hData_chMaxJtpt_keep[i]->SetMarkerStyle(24);
    hData_chMaxJtpt_keep[i]->SetMarkerColor(kBlack);
    nData_chMaxJtpt_keep[i]=hData_chMaxJtpt_keep[i]->GetEntries();
    if (nData_chMaxJtpt_keep[i]>0){
      if(nMC_chMaxJtpt_keep[i]<=0){
        hData_chMaxJtpt_keep[i]->Print("base");
        hData_chMaxJtpt_keep[i]->SetTitle(" ");
        hData_chMaxJtpt_keep[i]->SetXTitle("chMax/(ak4PuPF jet p_{T}) pass CutA");      
        hData_chMaxJtpt_keep[i]->DrawNormalized();
      } else {
      hData_chMaxJtpt_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_chMaxJtpt_keep[i] for i= "<<i<<" has "<<nData_chMaxJtpt_keep[i]<<" entries and is not drawn"<<endl; }      
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chMaxJtpt_keep[0],"MC","pl");
    leg->AddEntry(hData_chMaxJtpt_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchMaxJtpt_keep[i]->SaveAs(Form("chMaxJtpt_keep_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }
  
  TCanvas * ceMaxJtpt_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceMaxJtpt_keep[i] = new TCanvas(Form("ceMaxJtpt_keep_cent%d",i),"",800,600);
    ceMaxJtpt_keep[i]->SetLogy();
    hMC_eMaxJtpt_keep[i]->SetMarkerColor(kBlue);
    hMC_eMaxJtpt_keep[i]->SetMarkerStyle(25);
    hMC_eMaxJtpt_keep[i]->Print("base");
    hMC_eMaxJtpt_keep[i]->SetTitle(" ");
    hMC_eMaxJtpt_keep[i]->SetXTitle("eMax/(ak4PuPF jet p_{T}) pass CutA");
    nMC_eMaxJtpt_keep[i]=hMC_eMaxJtpt_keep[i]->GetEntries();
    if (nMC_eMaxJtpt_keep[i]>0){
       hMC_eMaxJtpt_keep[i]->DrawNormalized();
    } else { cout<<"hMC_eMaxJtpt_keep[i] for i= "<<i<<" has "<<nMC_eMaxJtpt_keep[i]<<" entries and is not drawn"<<endl; }

    hData_eMaxJtpt_keep[i]->SetMarkerStyle(24);
    hData_eMaxJtpt_keep[i]->SetMarkerColor(kBlack);
    nData_eMaxJtpt_keep[i]=hData_eMaxJtpt_keep[i]->GetEntries();
    if (nData_eMaxJtpt_keep[i]>0){
      if(nMC_eMaxJtpt_keep[i]<=0){
        hData_eMaxJtpt_keep[i]->Print("base");
        hData_eMaxJtpt_keep[i]->SetTitle(" ");
        hData_eMaxJtpt_keep[i]->SetXTitle("eMax/(ak4PuPF jet p_{T}) pass CutA");      
        hData_eMaxJtpt_keep[i]->DrawNormalized();
      } else {
      hData_eMaxJtpt_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_eMaxJtpt_keep[i] for i= "<<i<<" has "<<nData_eMaxJtpt_keep[i]<<" entries and is not drawn"<<endl; }   
        drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eMaxJtpt_keep[0],"MC","pl");
    leg->AddEntry(hData_eMaxJtpt_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceMaxJtpt_keep[i]->SaveAs(Form("eMaxJtpt_keep_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }

   TCanvas * cphMaxJtpt_keep[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphMaxJtpt_keep[i] = new TCanvas(Form("cphMaxJtpt_keep_cent%d",i),"",800,600);
    cphMaxJtpt_keep[i]->SetLogy();
    hMC_phMaxJtpt_keep[i]->SetMarkerColor(kGreen+2);
    hMC_phMaxJtpt_keep[i]->SetMarkerStyle(25);
    hMC_phMaxJtpt_keep[i]->Print("base");
    hMC_phMaxJtpt_keep[i]->SetTitle(" ");
    hMC_phMaxJtpt_keep[i]->SetXTitle("phMax/(ak4PuPF jet p_{T}) pass CutA");
    nMC_phMaxJtpt_keep[i]=hMC_phMaxJtpt_keep[i]->GetEntries();
    if (nMC_phMaxJtpt_keep[i]>0){
       hMC_phMaxJtpt_keep[i]->DrawNormalized();
    } else { cout<<"hMC_phMaxJtpt_keep[i] for i= "<<i<<" has "<<nMC_phMaxJtpt_keep[i]<<" entries and is not drawn"<<endl; }

    hData_phMaxJtpt_keep[i]->SetMarkerStyle(24);
    hData_phMaxJtpt_keep[i]->SetMarkerColor(kBlack);
    nData_phMaxJtpt_keep[i]=hData_phMaxJtpt_keep[i]->GetEntries();
    if (nData_phMaxJtpt_keep[i]>0){
      if(nMC_phMaxJtpt_keep[i]<=0){
        hData_phMaxJtpt_keep[i]->Print("base");
        hData_phMaxJtpt_keep[i]->SetTitle(" ");
        hData_phMaxJtpt_keep[i]->SetXTitle("phMax/(ak4PuPF jet p_{T}) pass CutA");      
        hData_phMaxJtpt_keep[i]->DrawNormalized();
      } else {
      hData_phMaxJtpt_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_phMaxJtpt_keep[i] for i= "<<i<<" has "<<nData_phMaxJtpt_keep[i]<<" entries and is not drawn"<<endl; }   
        drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phMaxJtpt_keep[0],"MC","pl");
    leg->AddEntry(hData_phMaxJtpt_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphMaxJtpt_keep[i]->SaveAs(Form("phMaxJtpt_keep_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }
  TCanvas * cneMaxJtpt_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneMaxJtpt_keep[i] = new TCanvas(Form("cneMaxJtpt_keep_cent%d",i),"",800,600);
    cneMaxJtpt_keep[i]->SetLogy();
    hMC_neMaxJtpt_keep[i]->SetMarkerColor(kMagenta);
    hMC_neMaxJtpt_keep[i]->SetMarkerStyle(25);
    hMC_neMaxJtpt_keep[i]->Print("base");
    hMC_neMaxJtpt_keep[i]->SetTitle(" ");
    hMC_neMaxJtpt_keep[i]->SetXTitle("neMax/(ak4PuPF jet p_{T}) pass CutA");
    nMC_neMaxJtpt_keep[i]=hMC_neMaxJtpt_keep[i]->GetEntries();
    if (nMC_neMaxJtpt_keep[i]>0){
       hMC_neMaxJtpt_keep[i]->DrawNormalized();
    } else { cout<<"hMC_neMaxJtpt_keep[i] for i= "<<i<<" has "<<nMC_neMaxJtpt_keep[i]<<" entries and is not drawn"<<endl; }

    hData_neMaxJtpt_keep[i]->SetMarkerStyle(24);
    hData_neMaxJtpt_keep[i]->SetMarkerColor(kBlack);
    nData_neMaxJtpt_keep[i]=hData_neMaxJtpt_keep[i]->GetEntries();
    if (nData_neMaxJtpt_keep[i]>0){
      if(nMC_neMaxJtpt_keep[i]<=0){
        hData_neMaxJtpt_keep[i]->Print("base");
        hData_neMaxJtpt_keep[i]->SetTitle(" ");
        hData_neMaxJtpt_keep[i]->SetXTitle("neMax/(ak4PuPF jet p_{T}) pass CutA");      
        hData_neMaxJtpt_keep[i]->DrawNormalized();
      } else {
      hData_neMaxJtpt_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_neMaxJtpt_keep[i] for i= "<<i<<" has "<<nData_neMaxJtpt_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neMaxJtpt_keep[0],"MC","pl");
    leg->AddEntry(hData_neMaxJtpt_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneMaxJtpt_keep[i]->SaveAs(Form("neMaxJtpt_keep_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }
    TCanvas * cmuMaxJtpt_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuMaxJtpt_keep[i] = new TCanvas(Form("cmuMaxJtpt_keep_cent%d",i),"",800,600);
    cmuMaxJtpt_keep[i]->SetLogy();
    hMC_muMaxJtpt_keep[i]->SetMarkerColor(kCyan);
    hMC_muMaxJtpt_keep[i]->SetMarkerStyle(25);
    hMC_muMaxJtpt_keep[i]->Print("base");
    hMC_muMaxJtpt_keep[i]->SetTitle(" ");
    hMC_muMaxJtpt_keep[i]->SetXTitle("muMax/(ak4PuPF jet p_{T}) pass CutA");
    nMC_muMaxJtpt_keep[i]=hMC_muMaxJtpt_keep[i]->GetEntries();
    if (nMC_muMaxJtpt_keep[i]>0){
       hMC_muMaxJtpt_keep[i]->DrawNormalized();
    } else { cout<<"hMC_muMaxJtpt_keep[i] for i= "<<i<<" has "<<nMC_muMaxJtpt_keep[i]<<" entries and is not drawn"<<endl; }

    hData_muMaxJtpt_keep[i]->SetMarkerStyle(24);
    hData_muMaxJtpt_keep[i]->SetMarkerColor(kBlack);
    nData_muMaxJtpt_keep[i]=hData_muMaxJtpt_keep[i]->GetEntries();
    if (nData_muMaxJtpt_keep[i]>0){
      if(nMC_muMaxJtpt_keep[i]<=0){
        hData_muMaxJtpt_keep[i]->Print("base");
        hData_muMaxJtpt_keep[i]->SetTitle(" ");
        hData_muMaxJtpt_keep[i]->SetXTitle("muMax/(ak4PuPF jet p_{T}) pass CutA");      
        hData_muMaxJtpt_keep[i]->DrawNormalized();
      } else {
      hData_muMaxJtpt_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_muMaxJtpt_keep[i] for i= "<<i<<" has "<<nData_muMaxJtpt_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muMaxJtpt_keep[0],"MC","pl");
    leg->AddEntry(hData_muMaxJtpt_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuMaxJtpt_keep[i]->SaveAs(Form("muMaxJtpt_keep_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }    
// draw some Sum variables
  TCanvas * cchSumJtpt_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchSumJtpt_keep[i] = new TCanvas(Form("cchSumJtpt_keep_cent%d",i),"",800,600);
    cchSumJtpt_keep[i]->SetLogy();
    hMC_chSumJtpt_keep[i]->SetMarkerColor(kRed+1);
    hMC_chSumJtpt_keep[i]->SetMarkerStyle(25);
    hMC_chSumJtpt_keep[i]->Print("base");
    hMC_chSumJtpt_keep[i]->SetTitle(" ");
    hMC_chSumJtpt_keep[i]->SetXTitle("chSum/(ak4PuPF jet p_{T}) pass CutA");
    nMC_chSumJtpt_keep[i]=hMC_chSumJtpt_keep[i]->GetEntries();
    if (nMC_chSumJtpt_keep[i]>0){
       hMC_chSumJtpt_keep[i]->DrawNormalized();
    } else { cout<<"hMC_chSumJtpt_keep[i] for i= "<<i<<" has "<<nMC_chSumJtpt_keep[i]<<" entries and is not drawn"<<endl; }

    hData_chSumJtpt_keep[i]->SetMarkerStyle(24);
    hData_chSumJtpt_keep[i]->SetMarkerColor(kBlack);
    nData_chSumJtpt_keep[i]=hData_chSumJtpt_keep[i]->GetEntries();
    if (nData_chSumJtpt_keep[i]>0){
      if(nMC_chSumJtpt_keep[i]<=0){
        hData_chSumJtpt_keep[i]->Print("base");
        hData_chSumJtpt_keep[i]->SetTitle(" ");
        hData_chSumJtpt_keep[i]->SetXTitle("chSum/(ak4PuPF jet p_{T}) pass CutA");      
        hData_chSumJtpt_keep[i]->DrawNormalized();
      } else {
      hData_chSumJtpt_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_chSumJtpt_keep[i] for i= "<<i<<" has "<<nData_chSumJtpt_keep[i]<<" entries and is not drawn"<<endl; }   
        drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chSumJtpt_keep[0],"MC","pl");
    leg->AddEntry(hData_chSumJtpt_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchSumJtpt_keep[i]->SaveAs(Form("chSumJtpt_keep_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }
  TCanvas * ceSumJtpt_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceSumJtpt_keep[i] = new TCanvas(Form("ceSumJtpt_keep_cent%d",i),"",800,600);
    ceSumJtpt_keep[i]->SetLogy();
    hMC_eSumJtpt_keep[i]->SetMarkerColor(kBlue+1);
    hMC_eSumJtpt_keep[i]->SetMarkerStyle(25);
    hMC_eSumJtpt_keep[i]->Print("base");
    hMC_eSumJtpt_keep[i]->SetTitle(" ");
    hMC_eSumJtpt_keep[i]->SetXTitle("eSum/(ak4PuPF jet p_{T}) pass CutA");
    nMC_eSumJtpt_keep[i]=hMC_eSumJtpt_keep[i]->GetEntries();
    if (nMC_eSumJtpt_keep[i]>0){
       hMC_eSumJtpt_keep[i]->DrawNormalized();
    } else { cout<<"hMC_eSumJtpt_keep[i] for i= "<<i<<" has "<<nMC_eSumJtpt_keep[i]<<" entries and is not drawn"<<endl; }

    hData_eSumJtpt_keep[i]->SetMarkerStyle(24);
    hData_eSumJtpt_keep[i]->SetMarkerColor(kBlack);
    nData_eSumJtpt_keep[i]=hData_eSumJtpt_keep[i]->GetEntries();
    if (nData_eSumJtpt_keep[i]>0){
      if(nMC_eSumJtpt_keep[i]<=0){
        hData_eSumJtpt_keep[i]->Print("base");
        hData_eSumJtpt_keep[i]->SetTitle(" ");
        hData_eSumJtpt_keep[i]->SetXTitle("eSum/(ak4PuPF jet p_{T}) pass CutA");      
        hData_eSumJtpt_keep[i]->DrawNormalized();
      } else {
      hData_eSumJtpt_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_eSumJtpt_keep[i] for i= "<<i<<" has "<<nData_eSumJtpt_keep[i]<<" entries and is not drawn"<<endl; }   
        drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eSumJtpt_keep[0],"MC","pl");
    leg->AddEntry(hData_eSumJtpt_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceSumJtpt_keep[i]->SaveAs(Form("eSumJtpt_keep_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }
  TCanvas * cphSumJtpt_keep[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphSumJtpt_keep[i] = new TCanvas(Form("cphSumJtpt_keep_cent%d",i),"",800,600);
    cphSumJtpt_keep[i]->SetLogy();
    hMC_phSumJtpt_keep[i]->SetMarkerColor(kGreen-3);
    hMC_phSumJtpt_keep[i]->SetMarkerStyle(25);
    hMC_phSumJtpt_keep[i]->Print("base");
    hMC_phSumJtpt_keep[i]->SetTitle(" ");
    hMC_phSumJtpt_keep[i]->SetXTitle("phSum/(ak4PuPF jet p_{T}) pass CutA");
    nMC_phSumJtpt_keep[i]=hMC_phSumJtpt_keep[i]->GetEntries();
    if (nMC_phSumJtpt_keep[i]>0){
       hMC_phSumJtpt_keep[i]->DrawNormalized();
    } else { cout<<"hMC_phSumJtpt_keep[i] for i= "<<i<<" has "<<nMC_phSumJtpt_keep[i]<<" entries and is not drawn"<<endl; }

    hData_phSumJtpt_keep[i]->SetMarkerStyle(24);
    hData_phSumJtpt_keep[i]->SetMarkerColor(kBlack);
    nData_phSumJtpt_keep[i]=hData_phSumJtpt_keep[i]->GetEntries();
    if (nData_phSumJtpt_keep[i]>0){
      if(nMC_phSumJtpt_keep[i]<=0){
        hData_phSumJtpt_keep[i]->Print("base");
        hData_phSumJtpt_keep[i]->SetTitle(" ");
        hData_phSumJtpt_keep[i]->SetXTitle("phSum/(ak4PuPF jet p_{T}) pass CutA");      
        hData_phSumJtpt_keep[i]->DrawNormalized();
      } else {
      hData_phSumJtpt_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_phSumJtpt_keep[i] for i= "<<i<<" has "<<nData_phSumJtpt_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phSumJtpt_keep[0],"MC","pl");
    leg->AddEntry(hData_phSumJtpt_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphSumJtpt_keep[i]->SaveAs(Form("phSumJtpt_keep_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }
  TCanvas * cneSumJtpt_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneSumJtpt_keep[i] = new TCanvas(Form("cneSumJtpt_keep_cent%d",i),"",800,600);
    cneSumJtpt_keep[i]->SetLogy();
    hMC_neSumJtpt_keep[i]->SetMarkerColor(kMagenta+1);
    hMC_neSumJtpt_keep[i]->SetMarkerStyle(25);
    hMC_neSumJtpt_keep[i]->Print("base");
    hMC_neSumJtpt_keep[i]->SetTitle(" ");
    hMC_neSumJtpt_keep[i]->SetXTitle("neSum/(ak4PuPF jet p_{T}) pass CutA");
    nMC_neSumJtpt_keep[i]=hMC_neSumJtpt_keep[i]->GetEntries();
    if (nMC_neSumJtpt_keep[i]>0){
       hMC_neSumJtpt_keep[i]->DrawNormalized();
    } else { cout<<"hMC_neSumJtpt_keep[i] for i= "<<i<<" has "<<nMC_neSumJtpt_keep[i]<<" entries and is not drawn"<<endl; }

    hData_neSumJtpt_keep[i]->SetMarkerStyle(24);
    hData_neSumJtpt_keep[i]->SetMarkerColor(kBlack);
    nData_neSumJtpt_keep[i]=hData_neSumJtpt_keep[i]->GetEntries();
    if (nData_neSumJtpt_keep[i]>0){
      if(nMC_neSumJtpt_keep[i]<=0){
        hData_neSumJtpt_keep[i]->Print("base");
        hData_neSumJtpt_keep[i]->SetTitle(" ");
        hData_neSumJtpt_keep[i]->SetXTitle("neSum/(ak4PuPF jet p_{T}) pass CutA");      
        hData_neSumJtpt_keep[i]->DrawNormalized();
      } else {
      hData_neSumJtpt_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_neSumJtpt_keep[i] for i= "<<i<<" has "<<nData_neSumJtpt_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neSumJtpt_keep[0],"MC","pl");
    leg->AddEntry(hData_neSumJtpt_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneSumJtpt_keep[i]->SaveAs(Form("neSumJtpt_keep_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }
    TCanvas * cmuSumJtpt_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuSumJtpt_keep[i] = new TCanvas(Form("cmuSumJtpt_keep_cent%d",i),"",800,600);
    cmuSumJtpt_keep[i]->SetLogy();
    hMC_muSumJtpt_keep[i]->SetMarkerColor(kCyan+1);
    hMC_muSumJtpt_keep[i]->SetMarkerStyle(25);
    hMC_muSumJtpt_keep[i]->Print("base");
    hMC_muSumJtpt_keep[i]->SetTitle(" ");
    hMC_muSumJtpt_keep[i]->SetXTitle("muSum/(ak4PuPF jet p_{T}) pass CutA");
    nMC_muSumJtpt_keep[i]=hMC_muSumJtpt_keep[i]->GetEntries();
    if (nMC_muSumJtpt_keep[i]>0){
       hMC_muSumJtpt_keep[i]->DrawNormalized();
    } else { cout<<"hMC_muSumJtpt_keep[i] for i= "<<i<<" has "<<nMC_muSumJtpt_keep[i]<<" entries and is not drawn"<<endl; }

    hData_muSumJtpt_keep[i]->SetMarkerStyle(24);
    hData_muSumJtpt_keep[i]->SetMarkerColor(kBlack);
    nData_muSumJtpt_keep[i]=hData_muSumJtpt_keep[i]->GetEntries();
    if (nData_muSumJtpt_keep[i]>0){
      if(nMC_muSumJtpt_keep[i]<=0){
        hData_muSumJtpt_keep[i]->Print("base");
        hData_muSumJtpt_keep[i]->SetTitle(" ");
        hData_muSumJtpt_keep[i]->SetXTitle("muSum/(ak4PuPF jet p_{T}) pass CutA");      
        hData_muSumJtpt_keep[i]->DrawNormalized();
      } else {
      hData_muSumJtpt_keep[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_muSumJtpt_keep[i] for i= "<<i<<" has "<<nData_muSumJtpt_keep[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muSumJtpt_keep[0],"MC","pl");
    leg->AddEntry(hData_muSumJtpt_keep[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuSumJtpt_keep[i]->SaveAs(Form("muSumJtpt_keep_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }
    TCanvas * cchMaxJtpt_rej[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchMaxJtpt_rej[i] = new TCanvas(Form("cchMaxJtpt_rej_cent%d",i),"",800,600);
    cchMaxJtpt_rej[i]->SetLogy();
    hMC_chMaxJtpt_rej[i]->SetMarkerColor(kRed);
    hMC_chMaxJtpt_rej[i]->SetMarkerStyle(25);
    hMC_chMaxJtpt_rej[i]->Print("base");
    hMC_chMaxJtpt_rej[i]->SetTitle(" ");
    hMC_chMaxJtpt_rej[i]->SetXTitle("chMax/(ak4PuPF jet p_{T}) fail CutA");
    nMC_chMaxJtpt_rej[i]=hMC_chMaxJtpt_rej[i]->GetEntries();
    if (nMC_chMaxJtpt_rej[i]>0){
       hMC_chMaxJtpt_rej[i]->DrawNormalized();
    } else { cout<<"hMC_chMaxJtpt_rej[i] for i= "<<i<<" has "<<nMC_chMaxJtpt_rej[i]<<" entries and is not drawn"<<endl; }

    hData_chMaxJtpt_rej[i]->SetMarkerStyle(24);
    hData_chMaxJtpt_rej[i]->SetMarkerColor(kBlack);
    nData_chMaxJtpt_rej[i]=hData_chMaxJtpt_rej[i]->GetEntries();
    if (nData_chMaxJtpt_rej[i]>0){
      if(nMC_chMaxJtpt_rej[i]<=0){
        hData_chMaxJtpt_rej[i]->Print("base");
        hData_chMaxJtpt_rej[i]->SetTitle(" ");
        hData_chMaxJtpt_rej[i]->SetXTitle("chMax/(ak4PuPF jet p_{T}) pass CutA");      
        hData_chMaxJtpt_rej[i]->DrawNormalized();
      } else {
      hData_chMaxJtpt_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_chMaxJtpt_rej[i] for i= "<<i<<" has "<<nData_chMaxJtpt_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chMaxJtpt_rej[0],"MC","pl");
    leg->AddEntry(hData_chMaxJtpt_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchMaxJtpt_rej[i]->SaveAs(Form("chMaxJtpt_rej_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }
  
  TCanvas * ceMaxJtpt_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceMaxJtpt_rej[i] = new TCanvas(Form("ceMaxJtpt_rej_cent%d",i),"",800,600);
    ceMaxJtpt_rej[i]->SetLogy();
    hMC_eMaxJtpt_rej[i]->SetMarkerColor(kBlue);
    hMC_eMaxJtpt_rej[i]->SetMarkerStyle(25);
    hMC_eMaxJtpt_rej[i]->Print("base");
    hMC_eMaxJtpt_rej[i]->SetTitle(" ");
    hMC_eMaxJtpt_rej[i]->SetXTitle("eMax/(ak4PuPF jet p_{T}) fail CutA");
    nMC_eMaxJtpt_rej[i]=hMC_eMaxJtpt_rej[i]->GetEntries();
    if (nMC_eMaxJtpt_rej[i]>0){
       hMC_eMaxJtpt_rej[i]->DrawNormalized();
    } else { cout<<"hMC_eMaxJtpt_rej[i] for i= "<<i<<" has "<<nMC_eMaxJtpt_rej[i]<<" entries and is not drawn"<<endl; }

    hData_eMaxJtpt_rej[i]->SetMarkerStyle(24);
    hData_eMaxJtpt_rej[i]->SetMarkerColor(kBlack);
    nData_eMaxJtpt_rej[i]=hData_eMaxJtpt_rej[i]->GetEntries();
    if (nData_eMaxJtpt_rej[i]>0){
      if(nMC_eMaxJtpt_rej[i]<=0){
        hData_eMaxJtpt_rej[i]->Print("base");
        hData_eMaxJtpt_rej[i]->SetTitle(" ");
        hData_eMaxJtpt_rej[i]->SetXTitle("eMax/(ak4PuPF jet p_{T}) pass CutA");      
        hData_eMaxJtpt_rej[i]->DrawNormalized();
      } else {
      hData_eMaxJtpt_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_eMaxJtpt_rej[i] for i= "<<i<<" has "<<nData_eMaxJtpt_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eMaxJtpt_rej[0],"MC","pl");
    leg->AddEntry(hData_eMaxJtpt_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceMaxJtpt_rej[i]->SaveAs(Form("eMaxJtpt_rej_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }

   TCanvas * cphMaxJtpt_rej[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphMaxJtpt_rej[i] = new TCanvas(Form("cphMaxJtpt_rej_cent%d",i),"",800,600);
    cphMaxJtpt_rej[i]->SetLogy();
    hMC_phMaxJtpt_rej[i]->SetMarkerColor(kGreen+2);
    hMC_phMaxJtpt_rej[i]->SetMarkerStyle(25);
    hMC_phMaxJtpt_rej[i]->Print("base");
    hMC_phMaxJtpt_rej[i]->SetTitle(" ");
    hMC_phMaxJtpt_rej[i]->SetXTitle("phMax/(ak4PuPF jet p_{T}) fail CutA");
    nMC_phMaxJtpt_rej[i]=hMC_phMaxJtpt_rej[i]->GetEntries();
    if (nMC_phMaxJtpt_rej[i]>0){
       hMC_phMaxJtpt_rej[i]->DrawNormalized();
    } else { cout<<"hMC_phMaxJtpt_rej[i] for i= "<<i<<" has "<<nMC_phMaxJtpt_rej[i]<<" entries and is not drawn"<<endl; }

    hData_phMaxJtpt_rej[i]->SetMarkerStyle(24);
    hData_phMaxJtpt_rej[i]->SetMarkerColor(kBlack);
    nData_phMaxJtpt_rej[i]=hData_phMaxJtpt_rej[i]->GetEntries();
    if (nData_phMaxJtpt_rej[i]>0){
      if(nMC_phMaxJtpt_rej[i]<=0){
        hData_phMaxJtpt_rej[i]->Print("base");
        hData_phMaxJtpt_rej[i]->SetTitle(" ");
        hData_phMaxJtpt_rej[i]->SetXTitle("phMax/(ak4PuPF jet p_{T}) pass CutA");      
        hData_phMaxJtpt_rej[i]->DrawNormalized();
      } else {
      hData_phMaxJtpt_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_phMaxJtpt_rej[i] for i= "<<i<<" has "<<nData_phMaxJtpt_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phMaxJtpt_rej[0],"MC","pl");
    leg->AddEntry(hData_phMaxJtpt_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphMaxJtpt_rej[i]->SaveAs(Form("phMaxJtpt_rej_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }
  TCanvas * cneMaxJtpt_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneMaxJtpt_rej[i] = new TCanvas(Form("cneMaxJtpt_rej_cent%d",i),"",800,600);
    cneMaxJtpt_rej[i]->SetLogy();
    hMC_neMaxJtpt_rej[i]->SetMarkerColor(kMagenta);
    hMC_neMaxJtpt_rej[i]->SetMarkerStyle(25);
    hMC_neMaxJtpt_rej[i]->Print("base");
    hMC_neMaxJtpt_rej[i]->SetTitle(" ");
    hMC_neMaxJtpt_rej[i]->SetXTitle("neMax/(ak4PuPF jet p_{T}) fail CutA");
    nMC_neMaxJtpt_rej[i]=hMC_neMaxJtpt_rej[i]->GetEntries();
    if (nMC_neMaxJtpt_rej[i]>0){
       hMC_neMaxJtpt_rej[i]->DrawNormalized();
    } else { cout<<"hMC_neMaxJtpt_rej[i] for i= "<<i<<" has "<<nMC_neMaxJtpt_rej[i]<<" entries and is not drawn"<<endl; }

    hData_neMaxJtpt_rej[i]->SetMarkerStyle(24);
    hData_neMaxJtpt_rej[i]->SetMarkerColor(kBlack);
    nData_neMaxJtpt_rej[i]=hData_neMaxJtpt_rej[i]->GetEntries();
    if (nData_neMaxJtpt_rej[i]>0){
      if(nMC_neMaxJtpt_rej[i]<=0){
        hData_neMaxJtpt_rej[i]->Print("base");
        hData_neMaxJtpt_rej[i]->SetTitle(" ");
        hData_neMaxJtpt_rej[i]->SetXTitle("neMax/(ak4PuPF jet p_{T}) pass CutA");      
        hData_neMaxJtpt_rej[i]->DrawNormalized();
      } else {
      hData_neMaxJtpt_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_neMaxJtpt_rej[i] for i= "<<i<<" has "<<nData_neMaxJtpt_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neMaxJtpt_rej[0],"MC","pl");
    leg->AddEntry(hData_neMaxJtpt_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneMaxJtpt_rej[i]->SaveAs(Form("neMaxJtpt_rej_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }
    TCanvas * cmuMaxJtpt_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuMaxJtpt_rej[i] = new TCanvas(Form("cmuMaxJtpt_rej_cent%d",i),"",800,600);
    cmuMaxJtpt_rej[i]->SetLogy();
    hMC_muMaxJtpt_rej[i]->SetMarkerColor(kCyan);
    hMC_muMaxJtpt_rej[i]->SetMarkerStyle(25);
    hMC_muMaxJtpt_rej[i]->Print("base");
    hMC_muMaxJtpt_rej[i]->SetTitle(" ");
    hMC_muMaxJtpt_rej[i]->SetXTitle("muMax/(ak4PuPF jet p_{T}) fail CutA");
    nMC_muMaxJtpt_rej[i]=hMC_muMaxJtpt_rej[i]->GetEntries();
    if (nMC_muMaxJtpt_rej[i]>0){
       hMC_muMaxJtpt_rej[i]->DrawNormalized();
    } else { cout<<"hMC_muMaxJtpt_rej[i] for i= "<<i<<" has "<<nMC_muMaxJtpt_rej[i]<<" entries and is not drawn"<<endl; }

    hData_muMaxJtpt_rej[i]->SetMarkerStyle(24);
    hData_muMaxJtpt_rej[i]->SetMarkerColor(kBlack);
    nData_muMaxJtpt_rej[i]=hData_muMaxJtpt_rej[i]->GetEntries();
    if (nData_muMaxJtpt_rej[i]>0){
      if(nMC_muMaxJtpt_rej[i]<=0){
        hData_muMaxJtpt_rej[i]->Print("base");
        hData_muMaxJtpt_rej[i]->SetTitle(" ");
        hData_muMaxJtpt_rej[i]->SetXTitle("muMax/(ak4PuPF jet p_{T}) pass CutA");      
        hData_muMaxJtpt_rej[i]->DrawNormalized();
      } else {
      hData_muMaxJtpt_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_muMaxJtpt_rej[i] for i= "<<i<<" has "<<nData_muMaxJtpt_rej[i]<<" entries and is not drawn"<<endl; } 
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muMaxJtpt_rej[0],"MC","pl");
    leg->AddEntry(hData_muMaxJtpt_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuMaxJtpt_rej[i]->SaveAs(Form("muMaxJtpt_rej_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }    
// draw some Sum variables
  TCanvas * cchSumJtpt_rej[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchSumJtpt_rej[i] = new TCanvas(Form("cchSumJtpt_rej_cent%d",i),"",800,600);
    cchSumJtpt_rej[i]->SetLogy();
    hMC_chSumJtpt_rej[i]->SetMarkerColor(kRed+1);
    hMC_chSumJtpt_rej[i]->SetMarkerStyle(25);
    hMC_chSumJtpt_rej[i]->Print("base");
    hMC_chSumJtpt_rej[i]->SetTitle(" ");
    hMC_chSumJtpt_rej[i]->SetXTitle("chSum/(ak4PuPF jet p_{T}) fail CutA");
    nMC_chSumJtpt_rej[i]=hMC_chSumJtpt_rej[i]->GetEntries();
    if (nMC_chSumJtpt_rej[i]>0){
       hMC_chSumJtpt_rej[i]->DrawNormalized();
    } else { cout<<"hMC_chSumJtpt_rej[i] for i= "<<i<<" has "<<nMC_chSumJtpt_rej[i]<<" entries and is not drawn"<<endl; }

    hData_chSumJtpt_rej[i]->SetMarkerStyle(24);
    hData_chSumJtpt_rej[i]->SetMarkerColor(kBlack);
    nData_chSumJtpt_rej[i]=hData_chSumJtpt_rej[i]->GetEntries();
    if (nData_chSumJtpt_rej[i]>0){
      if(nMC_chSumJtpt_rej[i]<=0){
        hData_chSumJtpt_rej[i]->Print("base");
        hData_chSumJtpt_rej[i]->SetTitle(" ");
        hData_chSumJtpt_rej[i]->SetXTitle("chSum/(ak4PuPF jet p_{T}) pass CutA");      
        hData_chSumJtpt_rej[i]->DrawNormalized();
      } else {
      hData_chSumJtpt_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_chSumJtpt_rej[i] for i= "<<i<<" has "<<nData_chSumJtpt_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chSumJtpt_rej[0],"MC","pl");
    leg->AddEntry(hData_chSumJtpt_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchSumJtpt_rej[i]->SaveAs(Form("chSumJtpt_rej_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }
  TCanvas * ceSumJtpt_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceSumJtpt_rej[i] = new TCanvas(Form("ceSumJtpt_rej_cent%d",i),"",800,600);
    ceSumJtpt_rej[i]->SetLogy();
    hMC_eSumJtpt_rej[i]->SetMarkerColor(kBlue+1);
    hMC_eSumJtpt_rej[i]->SetMarkerStyle(25);
    hMC_eSumJtpt_rej[i]->Print("base");
    hMC_eSumJtpt_rej[i]->SetTitle(" ");
    hMC_eSumJtpt_rej[i]->SetXTitle("eSum/(ak4PuPF jet p_{T}) fail CutA");
    nMC_eSumJtpt_rej[i]=hMC_eSumJtpt_rej[i]->GetEntries();
    if (nMC_eSumJtpt_rej[i]>0){
       hMC_eSumJtpt_rej[i]->DrawNormalized();
    } else { cout<<"hMC_eSumJtpt_rej[i] for i= "<<i<<" has "<<nMC_eSumJtpt_rej[i]<<" entries and is not drawn"<<endl; }

    hData_eSumJtpt_rej[i]->SetMarkerStyle(24);
    hData_eSumJtpt_rej[i]->SetMarkerColor(kBlack);
    nData_eSumJtpt_rej[i]=hData_eSumJtpt_rej[i]->GetEntries();
    if (nData_eSumJtpt_rej[i]>0){
      if(nMC_eSumJtpt_rej[i]<=0){
        hData_eSumJtpt_rej[i]->Print("base");
        hData_eSumJtpt_rej[i]->SetTitle(" ");
        hData_eSumJtpt_rej[i]->SetXTitle("eSum/(ak4PuPF jet p_{T}) pass CutA");      
        hData_eSumJtpt_rej[i]->DrawNormalized();
      } else {
      hData_eSumJtpt_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_eSumJtpt_rej[i] for i= "<<i<<" has "<<nData_eSumJtpt_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eSumJtpt_rej[0],"MC","pl");
    leg->AddEntry(hData_eSumJtpt_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceSumJtpt_rej[i]->SaveAs(Form("eSumJtpt_rej_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }
  TCanvas * cphSumJtpt_rej[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphSumJtpt_rej[i] = new TCanvas(Form("cphSumJtpt_rej_cent%d",i),"",800,600);
    cphSumJtpt_rej[i]->SetLogy();
    hMC_phSumJtpt_rej[i]->SetMarkerColor(kGreen-3);
    hMC_phSumJtpt_rej[i]->SetMarkerStyle(25);
    hMC_phSumJtpt_rej[i]->Print("base");
    hMC_phSumJtpt_rej[i]->SetTitle(" ");
    hMC_phSumJtpt_rej[i]->SetXTitle("phSum/(ak4PuPF jet p_{T}) fail CutA");
    nMC_phSumJtpt_rej[i]=hMC_phSumJtpt_rej[i]->GetEntries();
    if (nMC_phSumJtpt_rej[i]>0){
       hMC_phSumJtpt_rej[i]->DrawNormalized();
    } else { cout<<"hMC_phSumJtpt_rej[i] for i= "<<i<<" has "<<nMC_phSumJtpt_rej[i]<<" entries and is not drawn"<<endl; }

    hData_phSumJtpt_rej[i]->SetMarkerStyle(24);
    hData_phSumJtpt_rej[i]->SetMarkerColor(kBlack);
    nData_phSumJtpt_rej[i]=hData_phSumJtpt_rej[i]->GetEntries();
    if (nData_phSumJtpt_rej[i]>0){
      if(nMC_phSumJtpt_rej[i]<=0){
        hData_phSumJtpt_rej[i]->Print("base");
        hData_phSumJtpt_rej[i]->SetTitle(" ");
        hData_phSumJtpt_rej[i]->SetXTitle("phSum/(ak4PuPF jet p_{T}) pass CutA");      
        hData_phSumJtpt_rej[i]->DrawNormalized();
      } else {
      hData_phSumJtpt_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_phSumJtpt_rej[i] for i= "<<i<<" has "<<nData_phSumJtpt_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phSumJtpt_rej[0],"MC","pl");
    leg->AddEntry(hData_phSumJtpt_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphSumJtpt_rej[i]->SaveAs(Form("phSumJtpt_rej_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }
  TCanvas * cneSumJtpt_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneSumJtpt_rej[i] = new TCanvas(Form("cneSumJtpt_rej_cent%d",i),"",800,600);
    cneSumJtpt_rej[i]->SetLogy();
    hMC_neSumJtpt_rej[i]->SetMarkerColor(kMagenta+1);
    hMC_neSumJtpt_rej[i]->SetMarkerStyle(25);
    hMC_neSumJtpt_rej[i]->Print("base");
    hMC_neSumJtpt_rej[i]->SetTitle(" ");
    hMC_neSumJtpt_rej[i]->SetXTitle("neSum/(ak4PuPF jet p_{T}) fail CutA");
    nMC_neSumJtpt_rej[i]=hMC_neSumJtpt_rej[i]->GetEntries();
    if (nMC_neSumJtpt_rej[i]>0){
       hMC_neSumJtpt_rej[i]->DrawNormalized();
    } else { cout<<"hMC_neSumJtpt_rej[i] for i= "<<i<<" has "<<nMC_neSumJtpt_rej[i]<<" entries and is not drawn"<<endl; }

    hData_neSumJtpt_rej[i]->SetMarkerStyle(24);
    hData_neSumJtpt_rej[i]->SetMarkerColor(kBlack);
    nData_neSumJtpt_rej[i]=hData_neSumJtpt_rej[i]->GetEntries();
    if (nData_neSumJtpt_rej[i]>0){
      if(nMC_neSumJtpt_rej[i]<=0){
        hData_neSumJtpt_rej[i]->Print("base");
        hData_neSumJtpt_rej[i]->SetTitle(" ");
        hData_neSumJtpt_rej[i]->SetXTitle("neSum/(ak4PuPF jet p_{T}) pass CutA");      
        hData_neSumJtpt_rej[i]->DrawNormalized();
      } else {
      hData_neSumJtpt_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_neSumJtpt_rej[i] for i= "<<i<<" has "<<nData_neSumJtpt_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neSumJtpt_rej[0],"MC","pl");
    leg->AddEntry(hData_neSumJtpt_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneSumJtpt_rej[i]->SaveAs(Form("neSumJtpt_rej_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }
    TCanvas * cmuSumJtpt_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuSumJtpt_rej[i] = new TCanvas(Form("cmuSumJtpt_rej_cent%d",i),"",800,600);
    cmuSumJtpt_rej[i]->SetLogy();
    hMC_muSumJtpt_rej[i]->SetMarkerColor(kCyan+1);
    hMC_muSumJtpt_rej[i]->SetMarkerStyle(25);
    hMC_muSumJtpt_rej[i]->Print("base");
    hMC_muSumJtpt_rej[i]->SetTitle(" ");
    hMC_muSumJtpt_rej[i]->SetXTitle("muSum/(ak4PuPF jet p_{T}) fail CutA");
    nMC_muSumJtpt_rej[i]=hMC_muSumJtpt_rej[i]->GetEntries();
    if (nMC_muSumJtpt_rej[i]>0){
       hMC_muSumJtpt_rej[i]->DrawNormalized();
    } else { cout<<"hMC_muSumJtpt_rej[i] for i= "<<i<<" has "<<nMC_muSumJtpt_rej[i]<<" entries and is not drawn"<<endl; }

    hData_muSumJtpt_rej[i]->SetMarkerStyle(24);
    hData_muSumJtpt_rej[i]->SetMarkerColor(kBlack);
    nData_muSumJtpt_rej[i]=hData_muSumJtpt_rej[i]->GetEntries();
    if (nData_muSumJtpt_rej[i]>0){
      if(nMC_muSumJtpt_rej[i]<=0){
        hData_muSumJtpt_rej[i]->Print("base");
        hData_muSumJtpt_rej[i]->SetTitle(" ");
        hData_muSumJtpt_rej[i]->SetXTitle("muSum/(ak4PuPF jet p_{T}) pass CutA");      
        hData_muSumJtpt_rej[i]->DrawNormalized();
      } else {
      hData_muSumJtpt_rej[i]->DrawNormalized("same");
      }
    } else { cout<<"hData_muSumJtpt_rej[i] for i= "<<i<<" has "<<nData_muSumJtpt_rej[i]<<" entries and is not drawn"<<endl; }   
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muSumJtpt_rej[0],"MC","pl");
    leg->AddEntry(hData_muSumJtpt_rej[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuSumJtpt_rej[i]->SaveAs(Form("muSumJtpt_rej_cent%deMaxAndchMax_R4.pdf",i),"RECREATE");

  }  
}
int findBin(int hiBin){
  int binNo = -1;
  const int nbins_cent = 6;
  const int boundaries_cent[nbins_cent+1] = {0,2,4,12,20,28,36};
  // 0, 10, 20, 60, 100, 140, 180
  
  for(int i = 0;i<nbins_cent;i++){
    if(hiBin>=5*boundaries_cent[i] && hiBin<5*boundaries_cent[i+1]) {
      binNo = i;
      break;
    }
  }

  return binNo;
}