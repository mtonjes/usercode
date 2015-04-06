#include "Headers/plot.h"

int findBin(int hiBin);

// Run with: 
// .L RAA_plot_jeidvariables_cutPass_jet65.C
// RAA_plot_jeidvariables_cutPass_jet65()

void RAA_plot_jeidvariables_cutPass_jet65(){

  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);
  
   TFile * fData = TFile::Open("/data/users/belt/JetRAA/MatchNtuples/PbPb_Data_calo_pf_jet_correlation_deltaR_0p2_akPu3_20150331.root");
  TTree * Data_matched = (TTree*)fData->Get("matchedJets");
  TTree * Data_unmatched = (TTree*)fData->Get("unmatchedPFJets");

  TFile * fMC = TFile::Open("/data/users/belt/JetRAA/MatchNtuples/PbPb_MC_calo_pf_jet_correlation_deltaR_0p2_akPu3_20150331.root");
  TTree * MC_matched = (TTree*)fMC->Get("matchedJets");
  TTree * MC_unmatched = (TTree*)fMC->Get("unmatchedPFJets");

  const int nbins_cent = 6;
  const int boundaries_cent[nbins_cent+1] = {0,2,4,12,20,28,36};
  int centrality_bins[nbins_cent+1] = {0,5,10,30,50,70,90};
  
  Float_t pfptmin = 50;
  
// jet65
  TH1F * hData_chMaxJtpt_jet65[nbins_cent], * hData_phMaxJtpt_jet65[nbins_cent], * hData_neMaxJtpt_jet65[nbins_cent], * hData_muMaxJtpt_jet65[nbins_cent], * hData_eMaxJtpt_jet65[nbins_cent];
  TH1F * hData_chSumJtpt_jet65[nbins_cent], * hData_phSumJtpt_jet65[nbins_cent], * hData_neSumJtpt_jet65[nbins_cent], * hData_muSumJtpt_jet65[nbins_cent], * hData_eSumJtpt_jet65[nbins_cent];  
  
  TH1F * hMC_chMaxJtpt_jet65[nbins_cent], * hMC_phMaxJtpt_jet65[nbins_cent], * hMC_neMaxJtpt_jet65[nbins_cent], * hMC_muMaxJtpt_jet65[nbins_cent], * hMC_eMaxJtpt_jet65[nbins_cent];
  TH1F * hMC_chSumJtpt_jet65[nbins_cent], * hMC_phSumJtpt_jet65[nbins_cent], * hMC_neSumJtpt_jet65[nbins_cent], * hMC_muSumJtpt_jet65[nbins_cent], * hMC_eSumJtpt_jet65[nbins_cent];  

  TH1F * hData_chMaxJtpt_jet65_keep[nbins_cent], * hData_phMaxJtpt_jet65_keep[nbins_cent], * hData_neMaxJtpt_jet65_keep[nbins_cent], * hData_muMaxJtpt_jet65_keep[nbins_cent], * hData_eMaxJtpt_jet65_keep[nbins_cent];
  TH1F * hData_chSumJtpt_jet65_keep[nbins_cent], * hData_phSumJtpt_jet65_keep[nbins_cent], * hData_neSumJtpt_jet65_keep[nbins_cent], * hData_muSumJtpt_jet65_keep[nbins_cent], * hData_eSumJtpt_jet65_keep[nbins_cent];  
  
  TH1F * hMC_chMaxJtpt_jet65_keep[nbins_cent], * hMC_phMaxJtpt_jet65_keep[nbins_cent], * hMC_neMaxJtpt_jet65_keep[nbins_cent], * hMC_muMaxJtpt_jet65_keep[nbins_cent], * hMC_eMaxJtpt_jet65_keep[nbins_cent];
  TH1F * hMC_chSumJtpt_jet65_keep[nbins_cent], * hMC_phSumJtpt_jet65_keep[nbins_cent], * hMC_neSumJtpt_jet65_keep[nbins_cent], * hMC_muSumJtpt_jet65_keep[nbins_cent], * hMC_eSumJtpt_jet65_keep[nbins_cent];  

  TH1F * hData_chMaxJtpt_jet65_rej[nbins_cent], * hData_phMaxJtpt_jet65_rej[nbins_cent], * hData_neMaxJtpt_jet65_rej[nbins_cent], * hData_muMaxJtpt_jet65_rej[nbins_cent], * hData_eMaxJtpt_jet65_rej[nbins_cent];
  TH1F * hData_chSumJtpt_jet65_rej[nbins_cent], * hData_phSumJtpt_jet65_rej[nbins_cent], * hData_neSumJtpt_jet65_rej[nbins_cent], * hData_muSumJtpt_jet65_rej[nbins_cent], * hData_eSumJtpt_jet65_rej[nbins_cent];  
  
  TH1F * hMC_chMaxJtpt_jet65_rej[nbins_cent], * hMC_phMaxJtpt_jet65_rej[nbins_cent], * hMC_neMaxJtpt_jet65_rej[nbins_cent], * hMC_muMaxJtpt_jet65_rej[nbins_cent], * hMC_eMaxJtpt_jet65_rej[nbins_cent];
  TH1F * hMC_chSumJtpt_jet65_rej[nbins_cent], * hMC_phSumJtpt_jet65_rej[nbins_cent], * hMC_neSumJtpt_jet65_rej[nbins_cent], * hMC_muSumJtpt_jet65_rej[nbins_cent], * hMC_eSumJtpt_jet65_rej[nbins_cent];  

  Int_t * nData_chMaxJtpt_jet65_keep[nbins_cent], * nData_phMaxJtpt_jet65_keep[nbins_cent], * nData_neMaxJtpt_jet65_keep[nbins_cent], * nData_muMaxJtpt_jet65_keep[nbins_cent], * nData_eMaxJtpt_jet65_keep[nbins_cent];
  Int_t * nData_chSumJtpt_jet65_keep[nbins_cent], * nData_phSumJtpt_jet65_keep[nbins_cent], * nData_neSumJtpt_jet65_keep[nbins_cent], * nData_muSumJtpt_jet65_keep[nbins_cent], * nData_eSumJtpt_jet65_keep[nbins_cent];  
  
  Int_t * nMC_chMaxJtpt_jet65_keep[nbins_cent], * nMC_phMaxJtpt_jet65_keep[nbins_cent], * nMC_neMaxJtpt_jet65_keep[nbins_cent], * nMC_muMaxJtpt_jet65_keep[nbins_cent], * nMC_eMaxJtpt_jet65_keep[nbins_cent];
  Int_t * nMC_chSumJtpt_jet65_keep[nbins_cent], * nMC_phSumJtpt_jet65_keep[nbins_cent], * nMC_neSumJtpt_jet65_keep[nbins_cent], * nMC_muSumJtpt_jet65_keep[nbins_cent], * nMC_eSumJtpt_jet65_keep[nbins_cent];  

  Int_t * nData_chMaxJtpt_jet65_rej[nbins_cent], * nData_phMaxJtpt_jet65_rej[nbins_cent], * nData_neMaxJtpt_jet65_rej[nbins_cent], * nData_muMaxJtpt_jet65_rej[nbins_cent], * nData_eMaxJtpt_jet65_rej[nbins_cent];
  Int_t * nData_chSumJtpt_jet65_rej[nbins_cent], * nData_phSumJtpt_jet65_rej[nbins_cent], * nData_neSumJtpt_jet65_rej[nbins_cent], * nData_muSumJtpt_jet65_rej[nbins_cent], * nData_eSumJtpt_jet65_rej[nbins_cent];  
  
  Int_t * nMC_chMaxJtpt_jet65_rej[nbins_cent], * nMC_phMaxJtpt_jet65_rej[nbins_cent], * nMC_neMaxJtpt_jet65_rej[nbins_cent], * nMC_muMaxJtpt_jet65_rej[nbins_cent], * nMC_eMaxJtpt_jet65_rej[nbins_cent];
  Int_t * nMC_chSumJtpt_jet65_rej[nbins_cent], * nMC_phSumJtpt_jet65_rej[nbins_cent], * nMC_neSumJtpt_jet65_rej[nbins_cent], * nMC_muSumJtpt_jet65_rej[nbins_cent], * nMC_eSumJtpt_jet65_rej[nbins_cent];  

  for(int i = 0 ; i < nbins_cent ; ++i){


// jet65
    hData_chMaxJtpt_jet65[i] = new TH1F(Form("hData_chMaxJtpt_jet65_cent%d",i),Form("Data chMax/Jtpt, jet65 in centrality bin %d",i),100,0,1);
    hMC_chMaxJtpt_jet65[i] = new TH1F(Form("hMC_chMaxJtpt_jet65_cent%d",i),Form("MC chMax/Jtpt, jet65 in centrality bin ",i),100,0,1);
    hData_chSumJtpt_jet65[i] = new TH1F(Form("hData_chSumJtpt_jet65_cent%d",i),Form("Data chSum/Jtpt, jet65 in centrality bin %d",i),100,0,3);
    hMC_chSumJtpt_jet65[i] = new TH1F(Form("hMC_chSumJtpt_jet65_cent%d",i),Form("MC chSum/Jtpt, jet65 in centrality bin ",i),100,0,3);

    hData_eMaxJtpt_jet65[i] = new TH1F(Form("hData_eMaxJtpt_jet65_cent%d",i),Form("Data eMax/Jtpt, jet65 in centrality bin %d",i),100,0,1.4);
    hMC_eMaxJtpt_jet65[i] = new TH1F(Form("hMC_eMaxJtpt_jet65_cent%d",i),Form("MC eMax/Jtpt, jet65 in centrality bin ",i),100,0,1.4);
    hData_eSumJtpt_jet65[i] = new TH1F(Form("hData_eSumJtpt_jet65_cent%d",i),Form("Data eSum/Jtpt, jet65 in centrality bin %d",i),100,0,1.5);
    hMC_eSumJtpt_jet65[i] = new TH1F(Form("hMC_eSumJtpt_jet65_cent%d",i),Form("MC eSum/Jtpt, jet65 in centrality bin ",i),100,0,1.5);

    hData_neMaxJtpt_jet65[i] = new TH1F(Form("hData_neMaxJtpt_jet65_cent%d",i),Form("Data neMax/Jtpt, jet65 in centrality bin %d",i),100,0,1.2);
    hMC_neMaxJtpt_jet65[i] = new TH1F(Form("hMC_neMaxJtpt_jet65_cent%d",i),Form("MC neMax/Jtpt, jet65 in centrality bin ",i),100,0,1.2);
    hData_neSumJtpt_jet65[i] = new TH1F(Form("hData_neSumJtpt_jet65_cent%d",i),Form("Data neSum/Jtpt, jet65 in centrality bin %d",i),100,0,1.8);
    hMC_neSumJtpt_jet65[i] = new TH1F(Form("hMC_neSumJtpt_jet65_cent%d",i),Form("MC neSum/Jtpt, jet65 in centrality bin ",i),100,0,1.8);

    hData_phMaxJtpt_jet65[i] = new TH1F(Form("hData_phMaxJtpt_jet65_cent%d",i),Form("Data phMax/Jtpt, jet65 in centrality bin %d",i),100,0,1.5);
    hMC_phMaxJtpt_jet65[i] = new TH1F(Form("hMC_phMaxJtpt_jet65_cent%d",i),Form("MC phMax/Jtpt, jet65 in centrality bin ",i),100,0,1.5);
    hData_phSumJtpt_jet65[i] = new TH1F(Form("hData_phSumJtpt_jet65_cent%d",i),Form("Data phSum/Jtpt, jet65 in centrality bin %d",i),100,0,2);
    hMC_phSumJtpt_jet65[i] = new TH1F(Form("hMC_phSumJtpt_jet65_cent%d",i),Form("MC phSum/Jtpt, jet65 in centrality bin ",i),100,0,2);

    hData_muMaxJtpt_jet65[i] = new TH1F(Form("hData_muMaxJtpt_jet65_cent%d",i),Form("Data muMax/Jtpt, jet65 in centrality bin %d",i),100,0,1);
    hMC_muMaxJtpt_jet65[i] = new TH1F(Form("hMC_muMaxJtpt_jet65_cent%d",i),Form("MC muMax/Jtpt, jet65 in centrality bin ",i),100,0,1);
    hData_muSumJtpt_jet65[i] = new TH1F(Form("hData_muSumJtpt_jet65_cent%d",i),Form("Data muSum/Jtpt, jet65 in centrality bin %d",i),100,0,1);
    hMC_muSumJtpt_jet65[i] = new TH1F(Form("hMC_muSumJtpt_jet65_cent%d",i),Form("MC muSum/Jtpt, jet65 in centrality bin ",i),100,0,1);


    hData_chMaxJtpt_jet65_keep[i] = new TH1F(Form("hData_chMaxJtpt_jet65_keep_cent%d",i),Form("Data chMax/Jtpt, jet65 pass cutA in centrality bin %d",i),100,0,1);
    hMC_chMaxJtpt_jet65_keep[i] = new TH1F(Form("hMC_chMaxJtpt_jet65_keep_cent%d",i),Form("MC chMax/Jtpt, jet65 pass cutA in centrality bin ",i),100,0,1);
    hData_chSumJtpt_jet65_keep[i] = new TH1F(Form("hData_chSumJtpt_jet65_keep_cent%d",i),Form("Data chSum/Jtpt, jet65 pass cutA in centrality bin %d",i),100,0,3);
    hMC_chSumJtpt_jet65_keep[i] = new TH1F(Form("hMC_chSumJtpt_jet65_keep_cent%d",i),Form("MC chSum/Jtpt, jet65 pass cutA in centrality bin ",i),100,0,3);

    hData_eMaxJtpt_jet65_keep[i] = new TH1F(Form("hData_eMaxJtpt_jet65_keep_cent%d",i),Form("Data eMax/Jtpt, jet65 pass cutA in centrality bin %d",i),100,0,1.4);
    hMC_eMaxJtpt_jet65_keep[i] = new TH1F(Form("hMC_eMaxJtpt_jet65_keep_cent%d",i),Form("MC eMax/Jtpt, jet65 pass cutA in centrality bin ",i),100,0,1.4);
    hData_eSumJtpt_jet65_keep[i] = new TH1F(Form("hData_eSumJtpt_jet65_keep_cent%d",i),Form("Data eSum/Jtpt, jet65 pass cutA in centrality bin %d",i),100,0,1.5);
    hMC_eSumJtpt_jet65_keep[i] = new TH1F(Form("hMC_eSumJtpt_jet65_keep_cent%d",i),Form("MC eSum/Jtpt, jet65 pass cutA in centrality bin ",i),100,0,1.5);

    hData_neMaxJtpt_jet65_keep[i] = new TH1F(Form("hData_neMaxJtpt_jet65_keep_cent%d",i),Form("Data neMax/Jtpt, jet65 pass cutA in centrality bin %d",i),100,0,1.2);
    hMC_neMaxJtpt_jet65_keep[i] = new TH1F(Form("hMC_neMaxJtpt_jet65_keep_cent%d",i),Form("MC neMax/Jtpt, jet65 pass cutA in centrality bin ",i),100,0,1.2);
    hData_neSumJtpt_jet65_keep[i] = new TH1F(Form("hData_neSumJtpt_jet65_keep_cent%d",i),Form("Data neSum/Jtpt, jet65 pass cutA in centrality bin %d",i),100,0,1.8);
    hMC_neSumJtpt_jet65_keep[i] = new TH1F(Form("hMC_neSumJtpt_jet65_keep_cent%d",i),Form("MC neSum/Jtpt, jet65 pass cutA in centrality bin ",i),100,0,1.8);

    hData_phMaxJtpt_jet65_keep[i] = new TH1F(Form("hData_phMaxJtpt_jet65_keep_cent%d",i),Form("Data phMax/Jtpt, jet65 pass cutA in centrality bin %d",i),100,0,1.5);
    hMC_phMaxJtpt_jet65_keep[i] = new TH1F(Form("hMC_phMaxJtpt_jet65_keep_cent%d",i),Form("MC phMax/Jtpt, jet65 pass cutA in centrality bin ",i),100,0,1.5);
    hData_phSumJtpt_jet65_keep[i] = new TH1F(Form("hData_phSumJtpt_jet65_keep_cent%d",i),Form("Data phSum/Jtpt, jet65 pass cutA in centrality bin %d",i),100,0,2);
    hMC_phSumJtpt_jet65_keep[i] = new TH1F(Form("hMC_phSumJtpt_jet65_keep_cent%d",i),Form("MC phSum/Jtpt, jet65 pass cutA in centrality bin ",i),100,0,2);

    hData_muMaxJtpt_jet65_keep[i] = new TH1F(Form("hData_muMaxJtpt_jet65_keep_cent%d",i),Form("Data muMax/Jtpt, jet65 pass cutA in centrality bin %d",i),100,0,1);
    hMC_muMaxJtpt_jet65_keep[i] = new TH1F(Form("hMC_muMaxJtpt_jet65_keep_cent%d",i),Form("MC muMax/Jtpt, jet65 pass cutA in centrality bin ",i),100,0,1);
    hData_muSumJtpt_jet65_keep[i] = new TH1F(Form("hData_muSumJtpt_jet65_keep_cent%d",i),Form("Data muSum/Jtpt, jet65 pass cutA in centrality bin %d",i),100,0,1);
    hMC_muSumJtpt_jet65_keep[i] = new TH1F(Form("hMC_muSumJtpt_jet65_keep_cent%d",i),Form("MC muSum/Jtpt, jet65 pass cutA in centrality bin ",i),100,0,1);

    hData_chMaxJtpt_jet65_rej[i] = new TH1F(Form("hData_chMaxJtpt_jet65_rej_cent%d",i),Form("Data chMax/Jtpt, jet65 fail cutA in centrality bin %d",i),100,0,1);
    hMC_chMaxJtpt_jet65_rej[i] = new TH1F(Form("hMC_chMaxJtpt_jet65_rej_cent%d",i),Form("MC chMax/Jtpt, jet65 fail cutA in centrality bin ",i),100,0,1);
    hData_chSumJtpt_jet65_rej[i] = new TH1F(Form("hData_chSumJtpt_jet65_rej_cent%d",i),Form("Data chSum/Jtpt, jet65 fail cutA in centrality bin %d",i),100,0,3);
    hMC_chSumJtpt_jet65_rej[i] = new TH1F(Form("hMC_chSumJtpt_jet65_rej_cent%d",i),Form("MC chSum/Jtpt, jet65 fail cutA in centrality bin ",i),100,0,3);

    hData_eMaxJtpt_jet65_rej[i] = new TH1F(Form("hData_eMaxJtpt_jet65_rej_cent%d",i),Form("Data eMax/Jtpt, jet65 fail cutA in centrality bin %d",i),100,0,1.4);
    hMC_eMaxJtpt_jet65_rej[i] = new TH1F(Form("hMC_eMaxJtpt_jet65_rej_cent%d",i),Form("MC eMax/Jtpt, jet65 fail cutA in centrality bin ",i),100,0,1.4);
    hData_eSumJtpt_jet65_rej[i] = new TH1F(Form("hData_eSumJtpt_jet65_rej_cent%d",i),Form("Data eSum/Jtpt, jet65 fail cutA in centrality bin %d",i),100,0,1.5);
    hMC_eSumJtpt_jet65_rej[i] = new TH1F(Form("hMC_eSumJtpt_jet65_rej_cent%d",i),Form("MC eSum/Jtpt, jet65 fail cutA in centrality bin ",i),100,0,1.5);

    hData_neMaxJtpt_jet65_rej[i] = new TH1F(Form("hData_neMaxJtpt_jet65_rej_cent%d",i),Form("Data neMax/Jtpt, jet65 fail cutA in centrality bin %d",i),100,0,1.2);
    hMC_neMaxJtpt_jet65_rej[i] = new TH1F(Form("hMC_neMaxJtpt_jet65_rej_cent%d",i),Form("MC neMax/Jtpt, jet65 fail cutA in centrality bin ",i),100,0,1.2);
    hData_neSumJtpt_jet65_rej[i] = new TH1F(Form("hData_neSumJtpt_jet65_rej_cent%d",i),Form("Data neSum/Jtpt, jet65 fail cutA in centrality bin %d",i),100,0,1.8);
    hMC_neSumJtpt_jet65_rej[i] = new TH1F(Form("hMC_neSumJtpt_jet65_rej_cent%d",i),Form("MC neSum/Jtpt, jet65 fail cutA in centrality bin ",i),100,0,1.8);

    hData_phMaxJtpt_jet65_rej[i] = new TH1F(Form("hData_phMaxJtpt_jet65_rej_cent%d",i),Form("Data phMax/Jtpt, jet65 fail cutA in centrality bin %d",i),100,0,1.5);
    hMC_phMaxJtpt_jet65_rej[i] = new TH1F(Form("hMC_phMaxJtpt_jet65_rej_cent%d",i),Form("MC phMax/Jtpt, jet65 fail cutA in centrality bin ",i),100,0,1.5);
    hData_phSumJtpt_jet65_rej[i] = new TH1F(Form("hData_phSumJtpt_jet65_rej_cent%d",i),Form("Data phSum/Jtpt, jet65 fail cutA in centrality bin %d",i),100,0,2);
    hMC_phSumJtpt_jet65_rej[i] = new TH1F(Form("hMC_phSumJtpt_jet65_rej_cent%d",i),Form("MC phSum/Jtpt, jet65 fail cutA in centrality bin ",i),100,0,2);

    hData_muMaxJtpt_jet65_rej[i] = new TH1F(Form("hData_muMaxJtpt_jet65_rej_cent%d",i),Form("Data muMax/Jtpt, jet65 fail cutA in centrality bin %d",i),100,0,1);
    hMC_muMaxJtpt_jet65_rej[i] = new TH1F(Form("hMC_muMaxJtpt_jet65_rej_cent%d",i),Form("MC muMax/Jtpt, jet65 fail cutA in centrality bin ",i),100,0,1);
    hData_muSumJtpt_jet65_rej[i] = new TH1F(Form("hData_muSumJtpt_jet65_rej_cent%d",i),Form("Data muSum/Jtpt, jet65 fail cutA in centrality bin %d",i),100,0,1);
    hMC_muSumJtpt_jet65_rej[i] = new TH1F(Form("hMC_muSumJtpt_jet65_rej_cent%d",i),Form("MC muSum/Jtpt, jet65 fail cutA in centrality bin ",i),100,0,1);

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
         if(jet65_1==1 && jet80_1 == 0) {
             hData_chMaxJtpt_jet65[centb1]->Fill(chMax_1/pfpt_1);
             hData_eMaxJtpt_jet65[centb1]->Fill(eMax_1/pfpt_1);
             hData_neMaxJtpt_jet65[centb1]->Fill(neMax_1/pfpt_1);
             hData_phMaxJtpt_jet65[centb1]->Fill(phMax_1/pfpt_1);
             hData_muMaxJtpt_jet65[centb1]->Fill(muMax_1/pfpt_1);
             hData_chSumJtpt_jet65[centb1]->Fill(chSum_1/pfpt_1);
             hData_eSumJtpt_jet65[centb1]->Fill(eSum_1/pfpt_1);
             hData_neSumJtpt_jet65[centb1]->Fill(neSum_1/pfpt_1);
             hData_phSumJtpt_jet65[centb1]->Fill(phSum_1/pfpt_1);
             hData_muSumJtpt_jet65[centb1]->Fill(muSum_1/pfpt_1);
         }
   if((calopt_1/pfpt_1) <= 0.5 && eMax_1/Sumcand < 0.05 ) {
         if(jet65_1==1 && jet80_1 == 0) {
             hData_chMaxJtpt_jet65_keep[centb1]->Fill(chMax_1/pfpt_1);
             hData_eMaxJtpt_jet65_keep[centb1]->Fill(eMax_1/pfpt_1);
             hData_neMaxJtpt_jet65_keep[centb1]->Fill(neMax_1/pfpt_1);
             hData_phMaxJtpt_jet65_keep[centb1]->Fill(phMax_1/pfpt_1);
             hData_muMaxJtpt_jet65_keep[centb1]->Fill(muMax_1/pfpt_1);
             hData_chSumJtpt_jet65_keep[centb1]->Fill(chSum_1/pfpt_1);
             hData_eSumJtpt_jet65_keep[centb1]->Fill(eSum_1/pfpt_1);
             hData_neSumJtpt_jet65_keep[centb1]->Fill(neSum_1/pfpt_1);
             hData_phSumJtpt_jet65_keep[centb1]->Fill(phSum_1/pfpt_1);
             hData_muSumJtpt_jet65_keep[centb1]->Fill(muSum_1/pfpt_1);         
         }
   }
   if((calopt_1/pfpt_1) > 0.5 && calopt_1/pfpt_1 <= 0.85 && eMax_1/Sumcand < (18/7 *(Float_t)calopt_1/pfpt_1 - 9/7))){
         if(jet65_1==1 && jet80_1 == 0) {
             hData_chMaxJtpt_jet65_keep[centb1]->Fill(chMax_1/pfpt_1);
             hData_eMaxJtpt_jet65_keep[centb1]->Fill(eMax_1/pfpt_1);
             hData_neMaxJtpt_jet65_keep[centb1]->Fill(neMax_1/pfpt_1);
             hData_phMaxJtpt_jet65_keep[centb1]->Fill(phMax_1/pfpt_1);
             hData_muMaxJtpt_jet65_keep[centb1]->Fill(muMax_1/pfpt_1);
             hData_chSumJtpt_jet65_keep[centb1]->Fill(chSum_1/pfpt_1);
             hData_eSumJtpt_jet65_keep[centb1]->Fill(eSum_1/pfpt_1);
             hData_neSumJtpt_jet65_keep[centb1]->Fill(neSum_1/pfpt_1);
             hData_phSumJtpt_jet65_keep[centb1]->Fill(phSum_1/pfpt_1);
             hData_muSumJtpt_jet65_keep[centb1]->Fill(muSum_1/pfpt_1);         
         }
   }
   if(calopt_1/pfpt_1 > 0.85){
         if(jet65_1==1 && jet80_1 == 0) {
             hData_chMaxJtpt_jet65_keep[centb1]->Fill(chMax_1/pfpt_1);
             hData_eMaxJtpt_jet65_keep[centb1]->Fill(eMax_1/pfpt_1);
             hData_neMaxJtpt_jet65_keep[centb1]->Fill(neMax_1/pfpt_1);
             hData_phMaxJtpt_jet65_keep[centb1]->Fill(phMax_1/pfpt_1);
             hData_muMaxJtpt_jet65_keep[centb1]->Fill(muMax_1/pfpt_1);
             hData_chSumJtpt_jet65_keep[centb1]->Fill(chSum_1/pfpt_1);
             hData_eSumJtpt_jet65_keep[centb1]->Fill(eSum_1/pfpt_1);
             hData_neSumJtpt_jet65_keep[centb1]->Fill(neSum_1/pfpt_1);
             hData_phSumJtpt_jet65_keep[centb1]->Fill(phSum_1/pfpt_1);
             hData_muSumJtpt_jet65_keep[centb1]->Fill(muSum_1/pfpt_1);         
         }
   }
// rejected:
  if(calopt_1/pfpt_1 > 0.5 && calopt_1/pfpt_1 <= 0.85 && (eMax_1/Sumcand >= (18/7 *(Float_t)calopt_1/pfpt_1 - 9/7)) ){
         if(jet65_1==1 && jet80_1 == 0) {
             hData_chMaxJtpt_jet65_rej[centb1]->Fill(chMax_1/pfpt_1);
             hData_eMaxJtpt_jet65_rej[centb1]->Fill(eMax_1/pfpt_1);
             hData_neMaxJtpt_jet65_rej[centb1]->Fill(neMax_1/pfpt_1);
             hData_phMaxJtpt_jet65_rej[centb1]->Fill(phMax_1/pfpt_1);
             hData_muMaxJtpt_jet65_rej[centb1]->Fill(muMax_1/pfpt_1);
             hData_chSumJtpt_jet65_rej[centb1]->Fill(chSum_1/pfpt_1);
             hData_eSumJtpt_jet65_rej[centb1]->Fill(eSum_1/pfpt_1);
             hData_neSumJtpt_jet65_rej[centb1]->Fill(neSum_1/pfpt_1);
             hData_phSumJtpt_jet65_rej[centb1]->Fill(phSum_1/pfpt_1);
             hData_muSumJtpt_jet65_rej[centb1]->Fill(muSum_1/pfpt_1);         
         }
   }
   if(calopt_1/pfpt_1 <= 0.5 && eMax_1/Sumcand >= 0.05) {
         if(jet65_1==1 && jet80_1 == 0) {
             hData_chMaxJtpt_jet65_rej[centb1]->Fill(chMax_1/pfpt_1);
             hData_eMaxJtpt_jet65_rej[centb1]->Fill(eMax_1/pfpt_1);
             hData_neMaxJtpt_jet65_rej[centb1]->Fill(neMax_1/pfpt_1);
             hData_phMaxJtpt_jet65_rej[centb1]->Fill(phMax_1/pfpt_1);
             hData_muMaxJtpt_jet65_rej[centb1]->Fill(muMax_1/pfpt_1);
             hData_chSumJtpt_jet65_rej[centb1]->Fill(chSum_1/pfpt_1);
             hData_eSumJtpt_jet65_rej[centb1]->Fill(eSum_1/pfpt_1);
             hData_neSumJtpt_jet65_rej[centb1]->Fill(neSum_1/pfpt_1);
             hData_phSumJtpt_jet65_rej[centb1]->Fill(phSum_1/pfpt_1);
             hData_muSumJtpt_jet65_rej[centb1]->Fill(muSum_1/pfpt_1);         
         }
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
         if(jet65_1==1 && jet80_1 == 0) {
             hData_chMaxJtpt_jet65[centb1]->Fill(chMax_1/pfpt_1);
             hData_eMaxJtpt_jet65[centb1]->Fill(eMax_1/pfpt_1);
             hData_neMaxJtpt_jet65[centb1]->Fill(neMax_1/pfpt_1);
             hData_phMaxJtpt_jet65[centb1]->Fill(phMax_1/pfpt_1);
             hData_muMaxJtpt_jet65[centb1]->Fill(muMax_1/pfpt_1);
             hData_chSumJtpt_jet65[centb1]->Fill(chSum_1/pfpt_1);
             hData_eSumJtpt_jet65[centb1]->Fill(eSum_1/pfpt_1);
             hData_neSumJtpt_jet65[centb1]->Fill(neSum_1/pfpt_1);
             hData_phSumJtpt_jet65[centb1]->Fill(phSum_1/pfpt_1);
             hData_muSumJtpt_jet65[centb1]->Fill(muSum_1/pfpt_1);         
         }
    if(eMax_1/Sumcand < 0.05) {
         if(jet65_1==1 && jet80_1 == 0) {
             hData_chMaxJtpt_jet65_keep[centb1]->Fill(chMax_1/pfpt_1);
             hData_eMaxJtpt_jet65_keep[centb1]->Fill(eMax_1/pfpt_1);
             hData_neMaxJtpt_jet65_keep[centb1]->Fill(neMax_1/pfpt_1);
             hData_phMaxJtpt_jet65_keep[centb1]->Fill(phMax_1/pfpt_1);
             hData_muMaxJtpt_jet65_keep[centb1]->Fill(muMax_1/pfpt_1);
             hData_chSumJtpt_jet65_keep[centb1]->Fill(chSum_1/pfpt_1);
             hData_eSumJtpt_jet65_keep[centb1]->Fill(eSum_1/pfpt_1);
             hData_neSumJtpt_jet65_keep[centb1]->Fill(neSum_1/pfpt_1);
             hData_phSumJtpt_jet65_keep[centb1]->Fill(phSum_1/pfpt_1);
             hData_muSumJtpt_jet65_keep[centb1]->Fill(muSum_1/pfpt_1);         
         }         
    }
    if(eMax_1/Sumcand >= 0.05 ) {
         if(jet65_1==1 && jet80_1 == 0) {
             hData_chMaxJtpt_jet65_rej[centb1]->Fill(chMax_1/pfpt_1);
             hData_eMaxJtpt_jet65_rej[centb1]->Fill(eMax_1/pfpt_1);
             hData_neMaxJtpt_jet65_rej[centb1]->Fill(neMax_1/pfpt_1);
             hData_phMaxJtpt_jet65_rej[centb1]->Fill(phMax_1/pfpt_1);
             hData_muMaxJtpt_jet65_rej[centb1]->Fill(muMax_1/pfpt_1);
             hData_chSumJtpt_jet65_rej[centb1]->Fill(chSum_1/pfpt_1);
             hData_eSumJtpt_jet65_rej[centb1]->Fill(eSum_1/pfpt_1);
             hData_neSumJtpt_jet65_rej[centb1]->Fill(neSum_1/pfpt_1);
             hData_phSumJtpt_jet65_rej[centb1]->Fill(phSum_1/pfpt_1);
             hData_muSumJtpt_jet65_rej[centb1]->Fill(muSum_1/pfpt_1);         
         }         
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
         if(jet65_2==1 && jet80_2 == 0){
             hMC_chMaxJtpt_jet65[centb2]->Fill(chMax_2/pfpt_2,weight_2);
             hMC_eMaxJtpt_jet65[centb2]->Fill(eMax_2/pfpt_2,weight_2);
             hMC_neMaxJtpt_jet65[centb2]->Fill(neMax_2/pfpt_2,weight_2);
             hMC_phMaxJtpt_jet65[centb2]->Fill(phMax_2/pfpt_2,weight_2);
             hMC_muMaxJtpt_jet65[centb2]->Fill(muMax_2/pfpt_2,weight_2);
             hMC_chSumJtpt_jet65[centb2]->Fill(chSum_2/pfpt_2,weight_2);
             hMC_eSumJtpt_jet65[centb2]->Fill(eSum_2/pfpt_2,weight_2);
             hMC_neSumJtpt_jet65[centb2]->Fill(neSum_2/pfpt_2,weight_2);
             hMC_phSumJtpt_jet65[centb2]->Fill(phSum_2/pfpt_2,weight_2);
             hMC_muSumJtpt_jet65[centb2]->Fill(muSum_2/pfpt_2,weight_2);         
         }         
   if(calopt_2/pfpt_2 <= 0.5 && eMax_2/Sumcand < 0.05) {
         if(jet65_2==1 && jet80_2 == 0){
             hMC_chMaxJtpt_jet65_keep[centb2]->Fill(chMax_2/pfpt_2,weight_2);
             hMC_eMaxJtpt_jet65_keep[centb2]->Fill(eMax_2/pfpt_2,weight_2);
             hMC_neMaxJtpt_jet65_keep[centb2]->Fill(neMax_2/pfpt_2,weight_2);
             hMC_phMaxJtpt_jet65_keep[centb2]->Fill(phMax_2/pfpt_2,weight_2);
             hMC_muMaxJtpt_jet65_keep[centb2]->Fill(muMax_2/pfpt_2,weight_2);
             hMC_chSumJtpt_jet65_keep[centb2]->Fill(chSum_2/pfpt_2,weight_2);
             hMC_eSumJtpt_jet65_keep[centb2]->Fill(eSum_2/pfpt_2,weight_2);
             hMC_neSumJtpt_jet65_keep[centb2]->Fill(neSum_2/pfpt_2,weight_2);
             hMC_phSumJtpt_jet65_keep[centb2]->Fill(phSum_2/pfpt_2,weight_2);
             hMC_muSumJtpt_jet65_keep[centb2]->Fill(muSum_2/pfpt_2,weight_2);         
         }         
   }
   if(calopt_2/pfpt_2 > 0.5 && calopt_2/pfpt_2 <= 0.85 && eMax_2/Sumcand < (18/7 *(Float_t)calopt_2/pfpt_2 - 9/7))){
         if(jet65_2==1 && jet80_2 == 0){
             hMC_chMaxJtpt_jet65_keep[centb2]->Fill(chMax_2/pfpt_2,weight_2);
             hMC_eMaxJtpt_jet65_keep[centb2]->Fill(eMax_2/pfpt_2,weight_2);
             hMC_neMaxJtpt_jet65_keep[centb2]->Fill(neMax_2/pfpt_2,weight_2);
             hMC_phMaxJtpt_jet65_keep[centb2]->Fill(phMax_2/pfpt_2,weight_2);
             hMC_muMaxJtpt_jet65_keep[centb2]->Fill(muMax_2/pfpt_2,weight_2);
             hMC_chSumJtpt_jet65_keep[centb2]->Fill(chSum_2/pfpt_2,weight_2);
             hMC_eSumJtpt_jet65_keep[centb2]->Fill(eSum_2/pfpt_2,weight_2);
             hMC_neSumJtpt_jet65_keep[centb2]->Fill(neSum_2/pfpt_2,weight_2);
             hMC_phSumJtpt_jet65_keep[centb2]->Fill(phSum_2/pfpt_2,weight_2);
             hMC_muSumJtpt_jet65_keep[centb2]->Fill(muSum_2/pfpt_2,weight_2);         
         }         
   }
   if(calopt_2/pfpt_2 > 0.85){
         if(jet65_2==1 && jet80_2 == 0){
             hMC_chMaxJtpt_jet65_keep[centb2]->Fill(chMax_2/pfpt_2,weight_2);
             hMC_eMaxJtpt_jet65_keep[centb2]->Fill(eMax_2/pfpt_2,weight_2);
             hMC_neMaxJtpt_jet65_keep[centb2]->Fill(neMax_2/pfpt_2,weight_2);
             hMC_phMaxJtpt_jet65_keep[centb2]->Fill(phMax_2/pfpt_2,weight_2);
             hMC_muMaxJtpt_jet65_keep[centb2]->Fill(muMax_2/pfpt_2,weight_2);
             hMC_chSumJtpt_jet65_keep[centb2]->Fill(chSum_2/pfpt_2,weight_2);
             hMC_eSumJtpt_jet65_keep[centb2]->Fill(eSum_2/pfpt_2,weight_2);
             hMC_neSumJtpt_jet65_keep[centb2]->Fill(neSum_2/pfpt_2,weight_2);
             hMC_phSumJtpt_jet65_keep[centb2]->Fill(phSum_2/pfpt_2,weight_2);
             hMC_muSumJtpt_jet65_keep[centb2]->Fill(muSum_2/pfpt_2,weight_2);         
         }         
   }
// rejected:
  if(calopt_2/pfpt_2 > 0.5 && calopt_2/pfpt_2 <= 0.85 && eMax_2/Sumcand >= (18/7 *(Float_t)calopt_2/pfpt_2 - 9/7))){
         if(jet65_2==1 && jet80_2 == 0){
             hMC_chMaxJtpt_jet65_rej[centb2]->Fill(chMax_2/pfpt_2,weight_2);
             hMC_eMaxJtpt_jet65_rej[centb2]->Fill(eMax_2/pfpt_2,weight_2);
             hMC_neMaxJtpt_jet65_rej[centb2]->Fill(neMax_2/pfpt_2,weight_2);
             hMC_phMaxJtpt_jet65_rej[centb2]->Fill(phMax_2/pfpt_2,weight_2);
             hMC_muMaxJtpt_jet65_rej[centb2]->Fill(muMax_2/pfpt_2,weight_2);
             hMC_chSumJtpt_jet65_rej[centb2]->Fill(chSum_2/pfpt_2,weight_2);
             hMC_eSumJtpt_jet65_rej[centb2]->Fill(eSum_2/pfpt_2,weight_2);
             hMC_neSumJtpt_jet65_rej[centb2]->Fill(neSum_2/pfpt_2,weight_2);
             hMC_phSumJtpt_jet65_rej[centb2]->Fill(phSum_2/pfpt_2,weight_2);
             hMC_muSumJtpt_jet65_rej[centb2]->Fill(muSum_2/pfpt_2,weight_2);         
         }         
   }
   if(calopt_2/pfpt_2 <= 0.5 && eMax_2/Sumcand >= 0.05) {
         if(jet65_2==1 && jet80_2 == 0){
             hMC_chMaxJtpt_jet65_rej[centb2]->Fill(chMax_2/pfpt_2,weight_2);
             hMC_eMaxJtpt_jet65_rej[centb2]->Fill(eMax_2/pfpt_2,weight_2);
             hMC_neMaxJtpt_jet65_rej[centb2]->Fill(neMax_2/pfpt_2,weight_2);
             hMC_phMaxJtpt_jet65_rej[centb2]->Fill(phMax_2/pfpt_2,weight_2);
             hMC_muMaxJtpt_jet65_rej[centb2]->Fill(muMax_2/pfpt_2,weight_2);
             hMC_chSumJtpt_jet65_rej[centb2]->Fill(chSum_2/pfpt_2,weight_2);
             hMC_eSumJtpt_jet65_rej[centb2]->Fill(eSum_2/pfpt_2,weight_2);
             hMC_neSumJtpt_jet65_rej[centb2]->Fill(neSum_2/pfpt_2,weight_2);
             hMC_phSumJtpt_jet65_rej[centb2]->Fill(phSum_2/pfpt_2,weight_2);
             hMC_muSumJtpt_jet65_rej[centb2]->Fill(muSum_2/pfpt_2,weight_2);         
         }        
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
          if(jet65_2==1 && jet80_2 == 0){
             hMC_chMaxJtpt_jet65[centb2]->Fill(chMax_2/pfpt_2,weight_2);
             hMC_eMaxJtpt_jet65[centb2]->Fill(eMax_2/pfpt_2,weight_2);
             hMC_neMaxJtpt_jet65[centb2]->Fill(neMax_2/pfpt_2,weight_2);
             hMC_phMaxJtpt_jet65[centb2]->Fill(phMax_2/pfpt_2,weight_2);
             hMC_muMaxJtpt_jet65[centb2]->Fill(muMax_2/pfpt_2,weight_2);
             hMC_chSumJtpt_jet65[centb2]->Fill(chSum_2/pfpt_2,weight_2);
             hMC_eSumJtpt_jet65[centb2]->Fill(eSum_2/pfpt_2,weight_2);
             hMC_neSumJtpt_jet65[centb2]->Fill(neSum_2/pfpt_2,weight_2);
             hMC_phSumJtpt_jet65[centb2]->Fill(phSum_2/pfpt_2,weight_2);
             hMC_muSumJtpt_jet65[centb2]->Fill(muSum_2/pfpt_2,weight_2);         
         }        
    if(eMax_2/Sumcand < 0.05) {
         if(jet65_2==1 && jet80_2 == 0){
             hMC_chMaxJtpt_jet65_keep[centb2]->Fill(chMax_2/pfpt_2,weight_2);
             hMC_eMaxJtpt_jet65_keep[centb2]->Fill(eMax_2/pfpt_2,weight_2);
             hMC_neMaxJtpt_jet65_keep[centb2]->Fill(neMax_2/pfpt_2,weight_2);
             hMC_phMaxJtpt_jet65_keep[centb2]->Fill(phMax_2/pfpt_2,weight_2);
             hMC_muMaxJtpt_jet65_keep[centb2]->Fill(muMax_2/pfpt_2,weight_2);
             hMC_chSumJtpt_jet65_keep[centb2]->Fill(chSum_2/pfpt_2,weight_2);
             hMC_eSumJtpt_jet65_keep[centb2]->Fill(eSum_2/pfpt_2,weight_2);
             hMC_neSumJtpt_jet65_keep[centb2]->Fill(neSum_2/pfpt_2,weight_2);
             hMC_phSumJtpt_jet65_keep[centb2]->Fill(phSum_2/pfpt_2,weight_2);
             hMC_muSumJtpt_jet65_keep[centb2]->Fill(muSum_2/pfpt_2,weight_2);         
         }         
    }
    if(eMax_2/Sumcand >= 0.05) {
          if(jet65_2==1 && jet80_2 == 0){
             hMC_chMaxJtpt_jet65_rej[centb2]->Fill(chMax_2/pfpt_2,weight_2);
             hMC_eMaxJtpt_jet65_rej[centb2]->Fill(eMax_2/pfpt_2,weight_2);
             hMC_neMaxJtpt_jet65_rej[centb2]->Fill(neMax_2/pfpt_2,weight_2);
             hMC_phMaxJtpt_jet65_rej[centb2]->Fill(phMax_2/pfpt_2,weight_2);
             hMC_muMaxJtpt_jet65_rej[centb2]->Fill(muMax_2/pfpt_2,weight_2);
             hMC_chSumJtpt_jet65_rej[centb2]->Fill(chSum_2/pfpt_2,weight_2);
             hMC_eSumJtpt_jet65_rej[centb2]->Fill(eSum_2/pfpt_2,weight_2);
             hMC_neSumJtpt_jet65_rej[centb2]->Fill(neSum_2/pfpt_2,weight_2);
             hMC_phSumJtpt_jet65_rej[centb2]->Fill(phSum_2/pfpt_2,weight_2);
             hMC_muSumJtpt_jet65_rej[centb2]->Fill(muSum_2/pfpt_2,weight_2);         
         }        
    }  
    } // end pfptmin loop
  } // end MC unmatched loop

 /// end of looking at matched and unmatched, now to plot!!! 
// save those histos to a root file, remembering that I did DrawNormalized, so they are not normalized in the root file!  
  TFile fout("PbPb_JetIDPlots_NoCuts_and_YetkinCuts_matchedAndUn_slantedlinecalopfpt_eMaxSumcand_A_jet65Not80.root","RECREATE");
  for(int i = 0 ; i < nbins_cent ; ++i){

    hData_chMaxJtpt_jet65[i]->Write();
    hMC_chMaxJtpt_jet65[i]->Write();
    hData_chSumJtpt_jet65[i]->Write();
    hMC_chSumJtpt_jet65[i]->Write();
    hData_eMaxJtpt_jet65[i]->Write();
    hMC_eMaxJtpt_jet65[i]->Write();
    hData_eSumJtpt_jet65[i]->Write();
    hMC_eSumJtpt_jet65[i]->Write();
    hData_neMaxJtpt_jet65[i]->Write();
    hMC_neMaxJtpt_jet65[i]->Write();
    hData_neSumJtpt_jet65[i]->Write();
    hMC_neSumJtpt_jet65[i]->Write();
    hData_phMaxJtpt_jet65[i]->Write();
    hMC_phMaxJtpt_jet65[i]->Write();
    hData_phSumJtpt_jet65[i]->Write();
    hMC_phSumJtpt_jet65[i]->Write();
    hData_muMaxJtpt_jet65[i]->Write();
    hMC_muMaxJtpt_jet65[i]->Write();
    hData_muSumJtpt_jet65[i]->Write();
    hMC_muSumJtpt_jet65[i]->Write();
    
    hData_chMaxJtpt_jet65_keep[i]->Write();
    hMC_chMaxJtpt_jet65_keep[i]->Write();
    hData_chSumJtpt_jet65_keep[i]->Write();
    hMC_chSumJtpt_jet65_keep[i]->Write();
    hData_eMaxJtpt_jet65_keep[i]->Write();
    hMC_eMaxJtpt_jet65_keep[i]->Write();
    hData_eSumJtpt_jet65_keep[i]->Write();
    hMC_eSumJtpt_jet65_keep[i]->Write();
    hData_neMaxJtpt_jet65_keep[i]->Write();
    hMC_neMaxJtpt_jet65_keep[i]->Write();
    hData_neSumJtpt_jet65_keep[i]->Write();
    hMC_neSumJtpt_jet65_keep[i]->Write();
    hData_phMaxJtpt_jet65_keep[i]->Write();
    hMC_phMaxJtpt_jet65_keep[i]->Write();
    hData_phSumJtpt_jet65_keep[i]->Write();
    hMC_phSumJtpt_jet65_keep[i]->Write();
    hData_muMaxJtpt_jet65_keep[i]->Write();
    hMC_muMaxJtpt_jet65_keep[i]->Write();
    hData_muSumJtpt_jet65_keep[i]->Write();
    hMC_muSumJtpt_jet65_keep[i]->Write();
    
    hData_chMaxJtpt_jet65_rej[i]->Write();
    hMC_chMaxJtpt_jet65_rej[i]->Write();
    hData_chSumJtpt_jet65_rej[i]->Write();
    hMC_chSumJtpt_jet65_rej[i]->Write();
    hData_eMaxJtpt_jet65_rej[i]->Write();
    hMC_eMaxJtpt_jet65_rej[i]->Write();
    hData_eSumJtpt_jet65_rej[i]->Write();
    hMC_eSumJtpt_jet65_rej[i]->Write();
    hData_neMaxJtpt_jet65_rej[i]->Write();
    hMC_neMaxJtpt_jet65_rej[i]->Write();
    hData_neSumJtpt_jet65_rej[i]->Write();
    hMC_neSumJtpt_jet65_rej[i]->Write();
    hData_phMaxJtpt_jet65_rej[i]->Write();
    hMC_phMaxJtpt_jet65_rej[i]->Write();
    hData_phSumJtpt_jet65_rej[i]->Write();
    hMC_phSumJtpt_jet65_rej[i]->Write();
    hData_muMaxJtpt_jet65_rej[i]->Write();
    hMC_muMaxJtpt_jet65_rej[i]->Write();
    hData_muSumJtpt_jet65_rej[i]->Write();
    hMC_muSumJtpt_jet65_rej[i]->Write();
  }  
 
// now plot
  TCanvas * cchMaxJtpt_jet65[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchMaxJtpt_jet65[i] = new TCanvas(Form("cchMaxJtpt_jet65_cent%d",i),"",800,600);
    cchMaxJtpt_jet65[i]->SetLogy();
    hMC_chMaxJtpt_jet65[i]->SetMarkerColor(kRed);
    hMC_chMaxJtpt_jet65[i]->SetMarkerStyle(25);
    hMC_chMaxJtpt_jet65[i]->Print("base");
    hMC_chMaxJtpt_jet65[i]->SetTitle(" ");
    hMC_chMaxJtpt_jet65[i]->SetXTitle("chMax/(ak3PuPF jet p_{T}) jet65 no cuts");
    hMC_chMaxJtpt_jet65[i]->DrawNormalized();

    hData_chMaxJtpt_jet65[i]->SetMarkerStyle(24);
    hData_chMaxJtpt_jet65[i]->SetMarkerColor(kBlack);
    hData_chMaxJtpt_jet65[i]->DrawNormalized("same");
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chMaxJtpt_jet65[0],"MC","pl");
    leg->AddEntry(hData_chMaxJtpt_jet65[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchMaxJtpt_jet65[i]->SaveAs(Form("chMaxJtpt_jet65_cent%deMax_MCweight.pdf",i),"RECREATE");

  }
  
  TCanvas * ceMaxJtpt_jet65[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceMaxJtpt_jet65[i] = new TCanvas(Form("ceMaxJtpt_jet65_cent%d",i),"",800,600);
    ceMaxJtpt_jet65[i]->SetLogy();
    hMC_eMaxJtpt_jet65[i]->SetMarkerColor(kBlue);
    hMC_eMaxJtpt_jet65[i]->SetMarkerStyle(25);
    hMC_eMaxJtpt_jet65[i]->Print("base");
    hMC_eMaxJtpt_jet65[i]->SetTitle(" ");
    hMC_eMaxJtpt_jet65[i]->SetXTitle("eMax/(ak3PuPF jet p_{T}) jet65 no cuts");
    hMC_eMaxJtpt_jet65[i]->DrawNormalized();

    hData_eMaxJtpt_jet65[i]->SetMarkerStyle(24);
    hData_eMaxJtpt_jet65[i]->SetMarkerColor(kBlack);
    hData_eMaxJtpt_jet65[i]->DrawNormalized("same");
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eMaxJtpt_jet65[0],"MC","pl");
    leg->AddEntry(hData_eMaxJtpt_jet65[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceMaxJtpt_jet65[i]->SaveAs(Form("eMaxJtpt_jet65_cent%deMax_MCweight.pdf",i),"RECREATE");

  }

   TCanvas * cphMaxJtpt_jet65[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphMaxJtpt_jet65[i] = new TCanvas(Form("cphMaxJtpt_jet65_cent%d",i),"",800,600);
    cphMaxJtpt_jet65[i]->SetLogy();
    hMC_phMaxJtpt_jet65[i]->SetMarkerColor(kGreen+2);
    hMC_phMaxJtpt_jet65[i]->SetMarkerStyle(25);
    hMC_phMaxJtpt_jet65[i]->Print("base");
    hMC_phMaxJtpt_jet65[i]->SetTitle(" ");
    hMC_phMaxJtpt_jet65[i]->SetXTitle("phMax/(ak3PuPF jet p_{T}) jet65 no cuts");
    hMC_phMaxJtpt_jet65[i]->DrawNormalized();

    hData_phMaxJtpt_jet65[i]->SetMarkerStyle(24);
    hData_phMaxJtpt_jet65[i]->SetMarkerColor(kBlack);
    hData_phMaxJtpt_jet65[i]->DrawNormalized("same");
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phMaxJtpt_jet65[0],"MC","pl");
    leg->AddEntry(hData_phMaxJtpt_jet65[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphMaxJtpt_jet65[i]->SaveAs(Form("phMaxJtpt_jet65_cent%deMax_MCweight.pdf",i),"RECREATE");

  }
  TCanvas * cneMaxJtpt_jet65[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneMaxJtpt_jet65[i] = new TCanvas(Form("cneMaxJtpt_jet65_cent%d",i),"",800,600);
    cneMaxJtpt_jet65[i]->SetLogy();
    hMC_neMaxJtpt_jet65[i]->SetMarkerColor(kMagenta);
    hMC_neMaxJtpt_jet65[i]->SetMarkerStyle(25);
    hMC_neMaxJtpt_jet65[i]->Print("base");
    hMC_neMaxJtpt_jet65[i]->SetTitle(" ");
    hMC_neMaxJtpt_jet65[i]->SetXTitle("neMax/(ak3PuPF jet p_{T}) jet65 no cuts");
    hMC_neMaxJtpt_jet65[i]->DrawNormalized();

    hData_neMaxJtpt_jet65[i]->SetMarkerStyle(24);
    hData_neMaxJtpt_jet65[i]->SetMarkerColor(kBlack);
    hData_neMaxJtpt_jet65[i]->DrawNormalized("same");
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neMaxJtpt_jet65[0],"MC","pl");
    leg->AddEntry(hData_neMaxJtpt_jet65[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneMaxJtpt_jet65[i]->SaveAs(Form("neMaxJtpt_jet65_cent%deMax_MCweight.pdf",i),"RECREATE");

  }
    TCanvas * cmuMaxJtpt_jet65[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuMaxJtpt_jet65[i] = new TCanvas(Form("cmuMaxJtpt_jet65_cent%d",i),"",800,600);
    cmuMaxJtpt_jet65[i]->SetLogy();
    hMC_muMaxJtpt_jet65[i]->SetMarkerColor(kCyan);
    hMC_muMaxJtpt_jet65[i]->SetMarkerStyle(25);
    hMC_muMaxJtpt_jet65[i]->Print("base");
    hMC_muMaxJtpt_jet65[i]->SetTitle(" ");
    hMC_muMaxJtpt_jet65[i]->SetXTitle("muMax/(ak3PuPF jet p_{T}) jet65 no cuts");
    hMC_muMaxJtpt_jet65[i]->DrawNormalized();

    hData_muMaxJtpt_jet65[i]->SetMarkerStyle(24);
    hData_muMaxJtpt_jet65[i]->SetMarkerColor(kBlack);
    hData_muMaxJtpt_jet65[i]->DrawNormalized("same");
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muMaxJtpt_jet65[0],"MC","pl");
    leg->AddEntry(hData_muMaxJtpt_jet65[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuMaxJtpt_jet65[i]->SaveAs(Form("muMaxJtpt_jet65_cent%deMax_MCweight.pdf",i),"RECREATE");

  }    
// draw some Sum variables
  TCanvas * cchSumJtpt_jet65[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchSumJtpt_jet65[i] = new TCanvas(Form("cchSumJtpt_jet65_cent%d",i),"",800,600);
    cchSumJtpt_jet65[i]->SetLogy();
    hMC_chSumJtpt_jet65[i]->SetMarkerColor(kRed+1);
    hMC_chSumJtpt_jet65[i]->SetMarkerStyle(25);
    hMC_chSumJtpt_jet65[i]->Print("base");
    hMC_chSumJtpt_jet65[i]->SetTitle(" ");
    hMC_chSumJtpt_jet65[i]->SetXTitle("chSum/(ak3PuPF jet p_{T}) jet65 no cuts");
    hMC_chSumJtpt_jet65[i]->DrawNormalized();

    hData_chSumJtpt_jet65[i]->SetMarkerStyle(24);
    hData_chSumJtpt_jet65[i]->SetMarkerColor(kBlack);
    hData_chSumJtpt_jet65[i]->DrawNormalized("same");
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_chSumJtpt_jet65[0],"MC","pl");
    leg->AddEntry(hData_chSumJtpt_jet65[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cchSumJtpt_jet65[i]->SaveAs(Form("chSumJtpt_jet65_cent%deMax_MCweight.pdf",i),"RECREATE");

  }
  TCanvas * ceSumJtpt_jet65[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceSumJtpt_jet65[i] = new TCanvas(Form("ceSumJtpt_jet65_cent%d",i),"",800,600);
    ceSumJtpt_jet65[i]->SetLogy();
    hMC_eSumJtpt_jet65[i]->SetMarkerColor(kBlue+1);
    hMC_eSumJtpt_jet65[i]->SetMarkerStyle(25);
    hMC_eSumJtpt_jet65[i]->Print("base");
    hMC_eSumJtpt_jet65[i]->SetTitle(" ");
    hMC_eSumJtpt_jet65[i]->SetXTitle("eSum/(ak3PuPF jet p_{T}) jet65 no cuts");
    hMC_eSumJtpt_jet65[i]->DrawNormalized();

    hData_eSumJtpt_jet65[i]->SetMarkerStyle(24);
    hData_eSumJtpt_jet65[i]->SetMarkerColor(kBlack);
    hData_eSumJtpt_jet65[i]->DrawNormalized("same");
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_eSumJtpt_jet65[0],"MC","pl");
    leg->AddEntry(hData_eSumJtpt_jet65[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    ceSumJtpt_jet65[i]->SaveAs(Form("eSumJtpt_jet65_cent%deMax_MCweight.pdf",i),"RECREATE");

  }
  TCanvas * cphSumJtpt_jet65[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphSumJtpt_jet65[i] = new TCanvas(Form("cphSumJtpt_jet65_cent%d",i),"",800,600);
    cphSumJtpt_jet65[i]->SetLogy();
    hMC_phSumJtpt_jet65[i]->SetMarkerColor(kGreen-3);
    hMC_phSumJtpt_jet65[i]->SetMarkerStyle(25);
    hMC_phSumJtpt_jet65[i]->Print("base");
    hMC_phSumJtpt_jet65[i]->SetTitle(" ");
    hMC_phSumJtpt_jet65[i]->SetXTitle("phSum/(ak3PuPF jet p_{T}) jet65 no cuts");
    hMC_phSumJtpt_jet65[i]->DrawNormalized();

    hData_phSumJtpt_jet65[i]->SetMarkerStyle(24);
    hData_phSumJtpt_jet65[i]->SetMarkerColor(kBlack);
    hData_phSumJtpt_jet65[i]->DrawNormalized("same");
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_phSumJtpt_jet65[0],"MC","pl");
    leg->AddEntry(hData_phSumJtpt_jet65[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cphSumJtpt_jet65[i]->SaveAs(Form("phSumJtpt_jet65_cent%deMax_MCweight.pdf",i),"RECREATE");

  }
  TCanvas * cneSumJtpt_jet65[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneSumJtpt_jet65[i] = new TCanvas(Form("cneSumJtpt_jet65_cent%d",i),"",800,600);
    cneSumJtpt_jet65[i]->SetLogy();
    hMC_neSumJtpt_jet65[i]->SetMarkerColor(kMagenta+1);
    hMC_neSumJtpt_jet65[i]->SetMarkerStyle(25);
    hMC_neSumJtpt_jet65[i]->Print("base");
    hMC_neSumJtpt_jet65[i]->SetTitle(" ");
    hMC_neSumJtpt_jet65[i]->SetXTitle("neSum/(ak3PuPF jet p_{T}) jet65 no cuts");
    hMC_neSumJtpt_jet65[i]->DrawNormalized();

    hData_neSumJtpt_jet65[i]->SetMarkerStyle(24);
    hData_neSumJtpt_jet65[i]->SetMarkerColor(kBlack);
    hData_neSumJtpt_jet65[i]->DrawNormalized("same");
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_neSumJtpt_jet65[0],"MC","pl");
    leg->AddEntry(hData_neSumJtpt_jet65[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cneSumJtpt_jet65[i]->SaveAs(Form("neSumJtpt_jet65_cent%deMax_MCweight.pdf",i),"RECREATE");

  }
    TCanvas * cmuSumJtpt_jet65[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuSumJtpt_jet65[i] = new TCanvas(Form("cmuSumJtpt_jet65_cent%d",i),"",800,600);
    cmuSumJtpt_jet65[i]->SetLogy();
    hMC_muSumJtpt_jet65[i]->SetMarkerColor(kCyan+1);
    hMC_muSumJtpt_jet65[i]->SetMarkerStyle(25);
    hMC_muSumJtpt_jet65[i]->Print("base");
    hMC_muSumJtpt_jet65[i]->SetTitle(" ");
    hMC_muSumJtpt_jet65[i]->SetXTitle("muSum/(ak3PuPF jet p_{T}) jet65 no cuts");
    hMC_muSumJtpt_jet65[i]->DrawNormalized();

    hData_muSumJtpt_jet65[i]->SetMarkerStyle(24);
    hData_muSumJtpt_jet65[i]->SetMarkerColor(kBlack);
    hData_muSumJtpt_jet65[i]->DrawNormalized("same");
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);

    TLegend * leg = myLegend(0.15,0.15,0.3,0.3);
    leg->AddEntry(hMC_muSumJtpt_jet65[0],"MC","pl");
    leg->AddEntry(hData_muSumJtpt_jet65[0],"Data","pl");
    leg->SetTextSize(0.04);
    leg->Draw();
    
    cmuSumJtpt_jet65[i]->SaveAs(Form("muSumJtpt_jet65_cent%deMax_MCweight.pdf",i),"RECREATE");

  }    

  TCanvas * cchMaxJtpt_jet65_keep[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchMaxJtpt_jet65_keep[i] = new TCanvas(Form("cchMaxJtpt_jet65_keep_cent%d",i),"",800,600);
    cchMaxJtpt_jet65_keep[i]->SetLogy();
    hMC_chMaxJtpt_jet65_keep[i]->SetMarkerColor(kRed);
    hMC_chMaxJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_chMaxJtpt_jet65_keep[i]->Print("base");
    hMC_chMaxJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_chMaxJtpt_jet65_keep[i]->SetXTitle("chMax/(ak3PuPF jet p_{T}) jet65, pass CutA");
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
        hData_chMaxJtpt_jet65_keep[i]->SetXTitle("chMax/(ak3PuPF jet p_{T}) jet65, pass CutA");      
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
    
    cchMaxJtpt_jet65_keep[i]->SaveAs(Form("chMaxJtpt_jet65_keep_cent%deMax_MCweight.pdf",i),"RECREATE");

  }
  
  TCanvas * ceMaxJtpt_jet65_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceMaxJtpt_jet65_keep[i] = new TCanvas(Form("ceMaxJtpt_jet65_keep_cent%d",i),"",800,600);
    ceMaxJtpt_jet65_keep[i]->SetLogy();
    hMC_eMaxJtpt_jet65_keep[i]->SetMarkerColor(kBlue);
    hMC_eMaxJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_eMaxJtpt_jet65_keep[i]->Print("base");
    hMC_eMaxJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_eMaxJtpt_jet65_keep[i]->SetXTitle("eMax/(ak3PuPF jet p_{T}) jet65, pass CutA");
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
        hData_eMaxJtpt_jet65_keep[i]->SetXTitle("eMax/(ak3PuPF jet p_{T}) jet65, pass CutA");      
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
    
    ceMaxJtpt_jet65_keep[i]->SaveAs(Form("eMaxJtpt_jet65_keep_cent%deMax_MCweight.pdf",i),"RECREATE");

  }

   TCanvas * cphMaxJtpt_jet65_keep[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphMaxJtpt_jet65_keep[i] = new TCanvas(Form("cphMaxJtpt_jet65_keep_cent%d",i),"",800,600);
    cphMaxJtpt_jet65_keep[i]->SetLogy();
    hMC_phMaxJtpt_jet65_keep[i]->SetMarkerColor(kGreen+2);
    hMC_phMaxJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_phMaxJtpt_jet65_keep[i]->Print("base");
    hMC_phMaxJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_phMaxJtpt_jet65_keep[i]->SetXTitle("phMax/(ak3PuPF jet p_{T}) jet65, pass CutA");
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
        hData_phMaxJtpt_jet65_keep[i]->SetXTitle("phMax/(ak3PuPF jet p_{T}) jet65, pass CutA");      
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
    
    cphMaxJtpt_jet65_keep[i]->SaveAs(Form("phMaxJtpt_jet65_keep_cent%deMax_MCweight.pdf",i),"RECREATE");

  }
  TCanvas * cneMaxJtpt_jet65_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneMaxJtpt_jet65_keep[i] = new TCanvas(Form("cneMaxJtpt_jet65_keep_cent%d",i),"",800,600);
    cneMaxJtpt_jet65_keep[i]->SetLogy();
    hMC_neMaxJtpt_jet65_keep[i]->SetMarkerColor(kMagenta);
    hMC_neMaxJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_neMaxJtpt_jet65_keep[i]->Print("base");
    hMC_neMaxJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_neMaxJtpt_jet65_keep[i]->SetXTitle("neMax/(ak3PuPF jet p_{T}) jet65, pass CutA");
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
        hData_neMaxJtpt_jet65_keep[i]->SetXTitle("neMax/(ak3PuPF jet p_{T}) jet65, pass CutA");      
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
    
    cneMaxJtpt_jet65_keep[i]->SaveAs(Form("neMaxJtpt_jet65_keep_cent%deMax_MCweight.pdf",i),"RECREATE");

  }
    TCanvas * cmuMaxJtpt_jet65_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuMaxJtpt_jet65_keep[i] = new TCanvas(Form("cmuMaxJtpt_jet65_keep_cent%d",i),"",800,600);
    cmuMaxJtpt_jet65_keep[i]->SetLogy();
    hMC_muMaxJtpt_jet65_keep[i]->SetMarkerColor(kCyan);
    hMC_muMaxJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_muMaxJtpt_jet65_keep[i]->Print("base");
    hMC_muMaxJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_muMaxJtpt_jet65_keep[i]->SetXTitle("muMax/(ak3PuPF jet p_{T}) jet65, pass CutA");
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
        hData_muMaxJtpt_jet65_keep[i]->SetXTitle("muMax/(ak3PuPF jet p_{T}) jet65, pass CutA");      
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
    
    cmuMaxJtpt_jet65_keep[i]->SaveAs(Form("muMaxJtpt_jet65_keep_cent%deMax_MCweight.pdf",i),"RECREATE");

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
    hMC_chSumJtpt_jet65_keep[i]->SetXTitle("chSum/(ak3PuPF jet p_{T}) jet65, pass CutA");
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
        hData_chSumJtpt_jet65_keep[i]->SetXTitle("chSum/(ak3PuPF jet p_{T}) jet65, pass CutA");      
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
    
    cchSumJtpt_jet65_keep[i]->SaveAs(Form("chSumJtpt_jet65_keep_cent%deMax_MCweight.pdf",i),"RECREATE");

  }
  TCanvas * ceSumJtpt_jet65_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceSumJtpt_jet65_keep[i] = new TCanvas(Form("ceSumJtpt_jet65_keep_cent%d",i),"",800,600);
    ceSumJtpt_jet65_keep[i]->SetLogy();
    hMC_eSumJtpt_jet65_keep[i]->SetMarkerColor(kBlue+1);
    hMC_eSumJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_eSumJtpt_jet65_keep[i]->Print("base");
    hMC_eSumJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_eSumJtpt_jet65_keep[i]->SetXTitle("eSum/(ak3PuPF jet p_{T}) jet65, pass CutA");
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
        hData_eSumJtpt_jet65_keep[i]->SetXTitle("eSum/(ak3PuPF jet p_{T}) jet65, pass CutA");      
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
    
    ceSumJtpt_jet65_keep[i]->SaveAs(Form("eSumJtpt_jet65_keep_cent%deMax_MCweight.pdf",i),"RECREATE");

  }
  TCanvas * cphSumJtpt_jet65_keep[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphSumJtpt_jet65_keep[i] = new TCanvas(Form("cphSumJtpt_jet65_keep_cent%d",i),"",800,600);
    cphSumJtpt_jet65_keep[i]->SetLogy();
    hMC_phSumJtpt_jet65_keep[i]->SetMarkerColor(kGreen-3);
    hMC_phSumJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_phSumJtpt_jet65_keep[i]->Print("base");
    hMC_phSumJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_phSumJtpt_jet65_keep[i]->SetXTitle("phSum/(ak3PuPF jet p_{T}) jet65, pass CutA");
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
        hData_phSumJtpt_jet65_keep[i]->SetXTitle("phSum/(ak3PuPF jet p_{T}) jet65, pass CutA");      
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
    
    cphSumJtpt_jet65_keep[i]->SaveAs(Form("phSumJtpt_jet65_keep_cent%deMax_MCweight.pdf",i),"RECREATE");

  }
  TCanvas * cneSumJtpt_jet65_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneSumJtpt_jet65_keep[i] = new TCanvas(Form("cneSumJtpt_jet65_keep_cent%d",i),"",800,600);
    cneSumJtpt_jet65_keep[i]->SetLogy();
    hMC_neSumJtpt_jet65_keep[i]->SetMarkerColor(kMagenta+1);
    hMC_neSumJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_neSumJtpt_jet65_keep[i]->Print("base");
    hMC_neSumJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_neSumJtpt_jet65_keep[i]->SetXTitle("neSum/(ak3PuPF jet p_{T}) jet65, pass CutA");
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
        hData_neSumJtpt_jet65_keep[i]->SetXTitle("neSum/(ak3PuPF jet p_{T}) jet65, pass CutA");      
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
    
    cneSumJtpt_jet65_keep[i]->SaveAs(Form("neSumJtpt_jet65_keep_cent%deMax_MCweight.pdf",i),"RECREATE");

  }
    TCanvas * cmuSumJtpt_jet65_keep[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuSumJtpt_jet65_keep[i] = new TCanvas(Form("cmuSumJtpt_jet65_keep_cent%d",i),"",800,600);
    cmuSumJtpt_jet65_keep[i]->SetLogy();
    hMC_muSumJtpt_jet65_keep[i]->SetMarkerColor(kCyan+1);
    hMC_muSumJtpt_jet65_keep[i]->SetMarkerStyle(25);
    hMC_muSumJtpt_jet65_keep[i]->Print("base");
    hMC_muSumJtpt_jet65_keep[i]->SetTitle(" ");
    hMC_muSumJtpt_jet65_keep[i]->SetXTitle("muSum/(ak3PuPF jet p_{T}) jet65, pass CutA");
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
        hData_muSumJtpt_jet65_keep[i]->SetXTitle("muSum/(ak3PuPF jet p_{T}) jet65, pass CutA");      
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
    
    cmuSumJtpt_jet65_keep[i]->SaveAs(Form("muSumJtpt_jet65_keep_cent%deMax_MCweight.pdf",i),"RECREATE");

  }
    TCanvas * cchMaxJtpt_jet65_rej[nbins_cent];
  
  for(int i = 0 ; i < nbins_cent ; ++i){

    cchMaxJtpt_jet65_rej[i] = new TCanvas(Form("cchMaxJtpt_jet65_rej_cent%d",i),"",800,600);
    cchMaxJtpt_jet65_rej[i]->SetLogy();
    hMC_chMaxJtpt_jet65_rej[i]->SetMarkerColor(kRed);
    hMC_chMaxJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_chMaxJtpt_jet65_rej[i]->Print("base");
    hMC_chMaxJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_chMaxJtpt_jet65_rej[i]->SetXTitle("chMax/(ak3PuPF jet p_{T}) jet65, fail CutA");
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
        hData_chMaxJtpt_jet65_rej[i]->SetXTitle("chMax/(ak3PuPF jet p_{T}) jet65, pass CutA");      
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
    
    cchMaxJtpt_jet65_rej[i]->SaveAs(Form("chMaxJtpt_jet65_rej_cent%deMax_MCweight.pdf",i),"RECREATE");

  }
  
  TCanvas * ceMaxJtpt_jet65_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceMaxJtpt_jet65_rej[i] = new TCanvas(Form("ceMaxJtpt_jet65_rej_cent%d",i),"",800,600);
    ceMaxJtpt_jet65_rej[i]->SetLogy();
    hMC_eMaxJtpt_jet65_rej[i]->SetMarkerColor(kBlue);
    hMC_eMaxJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_eMaxJtpt_jet65_rej[i]->Print("base");
    hMC_eMaxJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_eMaxJtpt_jet65_rej[i]->SetXTitle("eMax/(ak3PuPF jet p_{T}) jet65, fail CutA");
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
        hData_eMaxJtpt_jet65_rej[i]->SetXTitle("eMax/(ak3PuPF jet p_{T}) jet65, pass CutA");      
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
    
    ceMaxJtpt_jet65_rej[i]->SaveAs(Form("eMaxJtpt_jet65_rej_cent%deMax_MCweight.pdf",i),"RECREATE");

  }

   TCanvas * cphMaxJtpt_jet65_rej[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphMaxJtpt_jet65_rej[i] = new TCanvas(Form("cphMaxJtpt_jet65_rej_cent%d",i),"",800,600);
    cphMaxJtpt_jet65_rej[i]->SetLogy();
    hMC_phMaxJtpt_jet65_rej[i]->SetMarkerColor(kGreen+2);
    hMC_phMaxJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_phMaxJtpt_jet65_rej[i]->Print("base");
    hMC_phMaxJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_phMaxJtpt_jet65_rej[i]->SetXTitle("phMax/(ak3PuPF jet p_{T}) jet65, fail CutA");
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
        hData_phMaxJtpt_jet65_rej[i]->SetXTitle("phMax/(ak3PuPF jet p_{T}) jet65, pass CutA");      
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
    
    cphMaxJtpt_jet65_rej[i]->SaveAs(Form("phMaxJtpt_jet65_rej_cent%deMax_MCweight.pdf",i),"RECREATE");

  }
  TCanvas * cneMaxJtpt_jet65_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneMaxJtpt_jet65_rej[i] = new TCanvas(Form("cneMaxJtpt_jet65_rej_cent%d",i),"",800,600);
    cneMaxJtpt_jet65_rej[i]->SetLogy();
    hMC_neMaxJtpt_jet65_rej[i]->SetMarkerColor(kMagenta);
    hMC_neMaxJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_neMaxJtpt_jet65_rej[i]->Print("base");
    hMC_neMaxJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_neMaxJtpt_jet65_rej[i]->SetXTitle("neMax/(ak3PuPF jet p_{T}) jet65, fail CutA");
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
        hData_neMaxJtpt_jet65_rej[i]->SetXTitle("neMax/(ak3PuPF jet p_{T}) jet65, pass CutA");      
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
    
    cneMaxJtpt_jet65_rej[i]->SaveAs(Form("neMaxJtpt_jet65_rej_cent%deMax_MCweight.pdf",i),"RECREATE");

  }
    TCanvas * cmuMaxJtpt_jet65_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuMaxJtpt_jet65_rej[i] = new TCanvas(Form("cmuMaxJtpt_jet65_rej_cent%d",i),"",800,600);
    cmuMaxJtpt_jet65_rej[i]->SetLogy();
    hMC_muMaxJtpt_jet65_rej[i]->SetMarkerColor(kCyan);
    hMC_muMaxJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_muMaxJtpt_jet65_rej[i]->Print("base");
    hMC_muMaxJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_muMaxJtpt_jet65_rej[i]->SetXTitle("muMax/(ak3PuPF jet p_{T}) jet65, fail CutA");
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
        hData_muMaxJtpt_jet65_rej[i]->SetXTitle("muMax/(ak3PuPF jet p_{T}) jet65, pass CutA");      
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
    
    cmuMaxJtpt_jet65_rej[i]->SaveAs(Form("muMaxJtpt_jet65_rej_cent%deMax_MCweight.pdf",i),"RECREATE");

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
    hMC_chSumJtpt_jet65_rej[i]->SetXTitle("chSum/(ak3PuPF jet p_{T}) jet65, fail CutA");
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
        hData_chSumJtpt_jet65_rej[i]->SetXTitle("chSum/(ak3PuPF jet p_{T}) jet65, pass CutA");      
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
    
    cchSumJtpt_jet65_rej[i]->SaveAs(Form("chSumJtpt_jet65_rej_cent%deMax_MCweight.pdf",i),"RECREATE");

  }
  TCanvas * ceSumJtpt_jet65_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    ceSumJtpt_jet65_rej[i] = new TCanvas(Form("ceSumJtpt_jet65_rej_cent%d",i),"",800,600);
    ceSumJtpt_jet65_rej[i]->SetLogy();
    hMC_eSumJtpt_jet65_rej[i]->SetMarkerColor(kBlue+1);
    hMC_eSumJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_eSumJtpt_jet65_rej[i]->Print("base");
    hMC_eSumJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_eSumJtpt_jet65_rej[i]->SetXTitle("eSum/(ak3PuPF jet p_{T}) jet65, fail CutA");
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
        hData_eSumJtpt_jet65_rej[i]->SetXTitle("eSum/(ak3PuPF jet p_{T}) jet65, pass CutA");      
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
    
    ceSumJtpt_jet65_rej[i]->SaveAs(Form("eSumJtpt_jet65_rej_cent%deMax_MCweight.pdf",i),"RECREATE");

  }
  TCanvas * cphSumJtpt_jet65_rej[nbins_cent];
  
    for(int i = 0 ; i < nbins_cent ; ++i){

    cphSumJtpt_jet65_rej[i] = new TCanvas(Form("cphSumJtpt_jet65_rej_cent%d",i),"",800,600);
    cphSumJtpt_jet65_rej[i]->SetLogy();
    hMC_phSumJtpt_jet65_rej[i]->SetMarkerColor(kGreen-3);
    hMC_phSumJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_phSumJtpt_jet65_rej[i]->Print("base");
    hMC_phSumJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_phSumJtpt_jet65_rej[i]->SetXTitle("phSum/(ak3PuPF jet p_{T}) jet65, fail CutA");
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
        hData_phSumJtpt_jet65_rej[i]->SetXTitle("phSum/(ak3PuPF jet p_{T}) jet65, pass CutA");      
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
    
    cphSumJtpt_jet65_rej[i]->SaveAs(Form("phSumJtpt_jet65_rej_cent%deMax_MCweight.pdf",i),"RECREATE");

  }
  TCanvas * cneSumJtpt_jet65_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cneSumJtpt_jet65_rej[i] = new TCanvas(Form("cneSumJtpt_jet65_rej_cent%d",i),"",800,600);
    cneSumJtpt_jet65_rej[i]->SetLogy();
    hMC_neSumJtpt_jet65_rej[i]->SetMarkerColor(kMagenta+1);
    hMC_neSumJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_neSumJtpt_jet65_rej[i]->Print("base");
    hMC_neSumJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_neSumJtpt_jet65_rej[i]->SetXTitle("neSum/(ak3PuPF jet p_{T}) jet65, fail CutA");
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
        hData_neSumJtpt_jet65_rej[i]->SetXTitle("neSum/(ak3PuPF jet p_{T}) jet65, pass CutA");      
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
    
    cneSumJtpt_jet65_rej[i]->SaveAs(Form("neSumJtpt_jet65_rej_cent%deMax_MCweight.pdf",i),"RECREATE");

  }
    TCanvas * cmuSumJtpt_jet65_rej[nbins_cent];

  for(int i = 0 ; i < nbins_cent ; ++i){

    cmuSumJtpt_jet65_rej[i] = new TCanvas(Form("cmuSumJtpt_jet65_rej_cent%d",i),"",800,600);
    cmuSumJtpt_jet65_rej[i]->SetLogy();
    hMC_muSumJtpt_jet65_rej[i]->SetMarkerColor(kCyan+1);
    hMC_muSumJtpt_jet65_rej[i]->SetMarkerStyle(25);
    hMC_muSumJtpt_jet65_rej[i]->Print("base");
    hMC_muSumJtpt_jet65_rej[i]->SetTitle(" ");
    hMC_muSumJtpt_jet65_rej[i]->SetXTitle("muSum/(ak3PuPF jet p_{T}) jet65, fail CutA");
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
        hData_muSumJtpt_jet65_rej[i]->SetXTitle("muSum/(ak3PuPF jet p_{T}) jet65, pass CutA");      
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
    
    cmuSumJtpt_jet65_rej[i]->SaveAs(Form("muSumJtpt_jet65_rej_cent%deMax_MCweight.pdf",i),"RECREATE");

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