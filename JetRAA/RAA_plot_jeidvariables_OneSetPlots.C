#include <Headers/plot.h>
int findBin(int hiBin);

void RAA_plot_jeidvariables_OneSetPlots(){

  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(0);
  
   TFile * fData = TFile::Open("/export/d00/scratch/rkunnawa/rootfiles/PbPb_Data_calo_pf_jet_correlation_deltaR_0p2_akPu3_20150320.root");
  TTree * Data_matched = (TTree*)fData->Get("matchedJets");
  TTree * Data_unmatched = (TTree*)fData->Get("unmatchedPFJets");

  TFile * fMC = TFile::Open("/export/d00/scratch/rkunnawa/rootfiles/PbPb_MC_calo_pf_jet_correlation_deltaR_0p2_akPu3_20150326.root");
  TTree * MC_matched = (TTree*)fMC->Get("matchedJets");
  TTree * MC_unmatched = (TTree*)fMC->Get("unmatchedPFJets");

  const int nbins_cent = 6;
  const int boundaries_cent[nbins_cent+1] = {0,2,4,12,20,28,36};
  int centrality_bins[nbins_cent+1] = {0,5,10,30,50,70,90};
  
  float pfptmin = 50;
  
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

  for(int i = 0 ; i < nbins_cent ; ++i){

    hData_chMaxJtpt[i] = new TH1F(Form("hData_chMaxJtpt_cent%d",i),Form("Data chMax/jtpt in centrality bin %d",i),100,0,1);
    hMC_chMaxJtpt[i] = new TH1F(Form("hMC_chMaxJtpt_cent%d",i),Form("MC chMax/jtpt in centrality bin ",i),100,0,1);
    hData_chSumJtpt[i] = new TH1F(Form("hData_chSumJtpt_cent%d",i),Form("Data chSum/jtpt in centrality bin %d",i),100,0,3);
    hMC_chSumJtpt[i] = new TH1F(Form("hMC_chSumJtpt_cent%d",i),Form("MC chSum/jtpt in centrality bin ",i),100,0,3);

    hData_eMaxJtpt[i] = new TH1F(Form("hData_eMaxJtpt_cent%d",i),Form("Data eMax/jtpt in centrality bin %d",i),100,0,1);
    hMC_eMaxJtpt[i] = new TH1F(Form("hMC_eMaxJtpt_cent%d",i),Form("MC eMax/jtpt in centrality bin ",i),100,0,1);
    hData_eSumJtpt[i] = new TH1F(Form("hData_eSumJtpt_cent%d",i),Form("Data eSum/jtpt in centrality bin %d",i),100,0,1.5);
    hMC_eSumJtpt[i] = new TH1F(Form("hMC_eSumJtpt_cent%d",i),Form("MC eSum/jtpt in centrality bin ",i),100,0,1.5);

    hData_neMaxJtpt[i] = new TH1F(Form("hData_neMaxJtpt_cent%d",i),Form("Data neMax/jtpt in centrality bin %d",i),100,0,1);
    hMC_neMaxJtpt[i] = new TH1F(Form("hMC_neMaxJtpt_cent%d",i),Form("MC neMax/jtpt in centrality bin ",i),100,0,1);
    hData_neSumJtpt[i] = new TH1F(Form("hData_neSumJtpt_cent%d",i),Form("Data neSum/jtpt in centrality bin %d",i),100,0,1.5);
    hMC_neSumJtpt[i] = new TH1F(Form("hMC_neSumJtpt_cent%d",i),Form("MC neSum/jtpt in centrality bin ",i),100,0,1.5);

    hData_phMaxJtpt[i] = new TH1F(Form("hData_phMaxJtpt_cent%d",i),Form("Data phMax/jtpt in centrality bin %d",i),100,0,1);
    hMC_phMaxJtpt[i] = new TH1F(Form("hMC_phMaxJtpt_cent%d",i),Form("MC phMax/jtpt in centrality bin ",i),100,0,1);
    hData_phSumJtpt[i] = new TH1F(Form("hData_phSumJtpt_cent%d",i),Form("Data phSum/jtpt in centrality bin %d",i),100,0,1);
    hMC_phSumJtpt[i] = new TH1F(Form("hMC_phSumJtpt_cent%d",i),Form("MC phSum/jtpt in centrality bin ",i),100,0,1);

    hData_muMaxJtpt[i] = new TH1F(Form("hData_muMaxJtpt_cent%d",i),Form("Data muMax/jtpt in centrality bin %d",i),100,0,1);
    hMC_muMaxJtpt[i] = new TH1F(Form("hMC_muMaxJtpt_cent%d",i),Form("MC muMax/jtpt in centrality bin ",i),100,0,1);
    hData_muSumJtpt[i] = new TH1F(Form("hData_muSumJtpt_cent%d",i),Form("Data muSum/jtpt in centrality bin %d",i),100,0,1);
    hMC_muSumJtpt[i] = new TH1F(Form("hMC_muSumJtpt_cent%d",i),Form("MC muSum/jtpt in centrality bin ",i),100,0,1);

    hData_chMaxJtpt_keep[i] = new TH1F(Form("hData_chMaxJtpt_keep_cent%d",i),Form("Data chMax/Jtpt pass cutA in centrality bin %d",i),100,0,1);
    hMC_chMaxJtpt_keep[i] = new TH1F(Form("hMC_chMaxJtpt_keep_cent%d",i),Form("MC chMax/Jtpt pass cutA in centrality bin ",i),100,0,1);
    hData_chSumJtpt_keep[i] = new TH1F(Form("hData_chSumJtpt_keep_cent%d",i),Form("Data chSum/Jtpt pass cutA in centrality bin %d",i),100,0,3);
    hMC_chSumJtpt_keep[i] = new TH1F(Form("hMC_chSumJtpt_keep_cent%d",i),Form("MC chSum/Jtpt pass cutA in centrality bin ",i),100,0,3);

    hData_eMaxJtpt_keep[i] = new TH1F(Form("hData_eMaxJtpt_keep_cent%d",i),Form("Data eMax/Jtpt pass cutA in centrality bin %d",i),100,0,1);
    hMC_eMaxJtpt_keep[i] = new TH1F(Form("hMC_eMaxJtpt_keep_cent%d",i),Form("MC eMax/Jtpt pass cutA in centrality bin ",i),100,0,1);
    hData_eSumJtpt_keep[i] = new TH1F(Form("hData_eSumJtpt_keep_cent%d",i),Form("Data eSum/Jtpt pass cutA in centrality bin %d",i),100,0,1.5);
    hMC_eSumJtpt_keep[i] = new TH1F(Form("hMC_eSumJtpt_keep_cent%d",i),Form("MC eSum/Jtpt pass cutA in centrality bin ",i),100,0,1.5);

    hData_neMaxJtpt_keep[i] = new TH1F(Form("hData_neMaxJtpt_keep_cent%d",i),Form("Data neMax/Jtpt pass cutA in centrality bin %d",i),100,0,1);
    hMC_neMaxJtpt_keep[i] = new TH1F(Form("hMC_neMaxJtpt_keep_cent%d",i),Form("MC neMax/Jtpt pass cutA in centrality bin ",i),100,0,1);
    hData_neSumJtpt_keep[i] = new TH1F(Form("hData_neSumJtpt_keep_cent%d",i),Form("Data neSum/Jtpt pass cutA in centrality bin %d",i),100,0,1.5);
    hMC_neSumJtpt_keep[i] = new TH1F(Form("hMC_neSumJtpt_keep_cent%d",i),Form("MC neSum/Jtpt pass cutA in centrality bin ",i),100,0,1.5);

    hData_phMaxJtpt_keep[i] = new TH1F(Form("hData_phMaxJtpt_keep_cent%d",i),Form("Data phMax/Jtpt pass cutA in centrality bin %d",i),100,0,1);
    hMC_phMaxJtpt_keep[i] = new TH1F(Form("hMC_phMaxJtpt_keep_cent%d",i),Form("MC phMax/Jtpt pass cutA in centrality bin ",i),100,0,1);
    hData_phSumJtpt_keep[i] = new TH1F(Form("hData_phSumJtpt_keep_cent%d",i),Form("Data phSum/Jtpt pass cutA in centrality bin %d",i),100,0,1);
    hMC_phSumJtpt_keep[i] = new TH1F(Form("hMC_phSumJtpt_keep_cent%d",i),Form("MC phSum/Jtpt pass cutA in centrality bin ",i),100,0,1);

    hData_muMaxJtpt_keep[i] = new TH1F(Form("hData_muMaxJtpt_keep_cent%d",i),Form("Data muMax/Jtpt pass cutA in centrality bin %d",i),100,0,1);
    hMC_muMaxJtpt_keep[i] = new TH1F(Form("hMC_muMaxJtpt_keep_cent%d",i),Form("MC muMax/Jtpt pass cutA in centrality bin ",i),100,0,1);
    hData_muSumJtpt_keep[i] = new TH1F(Form("hData_muSumJtpt_keep_cent%d",i),Form("Data muSum/Jtpt pass cutA in centrality bin %d",i),100,0,1);
    hMC_muSumJtpt_keep[i] = new TH1F(Form("hMC_muSumJtpt_keep_cent%d",i),Form("MC muSum/Jtpt pass cutA in centrality bin ",i),100,0,1);

    hData_chMaxJtpt_rej[i] = new TH1F(Form("hData_chMaxJtpt_rej_cent%d",i),Form("Data chMax/Jtpt fail cutA in centrality bin %d",i),100,0,1);
    hMC_chMaxJtpt_rej[i] = new TH1F(Form("hMC_chMaxJtpt_rej_cent%d",i),Form("MC chMax/Jtpt fail cutA in centrality bin ",i),100,0,1);
    hData_chSumJtpt_rej[i] = new TH1F(Form("hData_chSumJtpt_rej_cent%d",i),Form("Data chSum/Jtpt fail cutA in centrality bin %d",i),100,0,3);
    hMC_chSumJtpt_rej[i] = new TH1F(Form("hMC_chSumJtpt_rej_cent%d",i),Form("MC chSum/Jtpt fail cutA in centrality bin ",i),100,0,3);

    hData_eMaxJtpt_rej[i] = new TH1F(Form("hData_eMaxJtpt_rej_cent%d",i),Form("Data eMax/Jtpt fail cutA in centrality bin %d",i),100,0,1);
    hMC_eMaxJtpt_rej[i] = new TH1F(Form("hMC_eMaxJtpt_rej_cent%d",i),Form("MC eMax/Jtpt fail cutA in centrality bin ",i),100,0,1);
    hData_eSumJtpt_rej[i] = new TH1F(Form("hData_eSumJtpt_rej_cent%d",i),Form("Data eSum/Jtpt fail cutA in centrality bin %d",i),100,0,1.5);
    hMC_eSumJtpt_rej[i] = new TH1F(Form("hMC_eSumJtpt_rej_cent%d",i),Form("MC eSum/Jtpt fail cutA in centrality bin ",i),100,0,1.5);

    hData_neMaxJtpt_rej[i] = new TH1F(Form("hData_neMaxJtpt_rej_cent%d",i),Form("Data neMax/Jtpt fail cutA in centrality bin %d",i),100,0,1);
    hMC_neMaxJtpt_rej[i] = new TH1F(Form("hMC_neMaxJtpt_rej_cent%d",i),Form("MC neMax/Jtpt fail cutA in centrality bin ",i),100,0,1);
    hData_neSumJtpt_rej[i] = new TH1F(Form("hData_neSumJtpt_rej_cent%d",i),Form("Data neSum/Jtpt fail cutA in centrality bin %d",i),100,0,1.5);
    hMC_neSumJtpt_rej[i] = new TH1F(Form("hMC_neSumJtpt_rej_cent%d",i),Form("MC neSum/Jtpt fail cutA in centrality bin ",i),100,0,1.5);

    hData_phMaxJtpt_rej[i] = new TH1F(Form("hData_phMaxJtpt_rej_cent%d",i),Form("Data phMax/Jtpt fail cutA in centrality bin %d",i),100,0,1);
    hMC_phMaxJtpt_rej[i] = new TH1F(Form("hMC_phMaxJtpt_rej_cent%d",i),Form("MC phMax/Jtpt fail cutA in centrality bin ",i),100,0,1);
    hData_phSumJtpt_rej[i] = new TH1F(Form("hData_phSumJtpt_rej_cent%d",i),Form("Data phSum/Jtpt fail cutA in centrality bin %d",i),100,0,1);
    hMC_phSumJtpt_rej[i] = new TH1F(Form("hMC_phSumJtpt_rej_cent%d",i),Form("MC phSum/Jtpt fail cutA in centrality bin ",i),100,0,1);

    hData_muMaxJtpt_rej[i] = new TH1F(Form("hData_muMaxJtpt_rej_cent%d",i),Form("Data muMax/Jtpt fail cutA in centrality bin %d",i),100,0,1);
    hMC_muMaxJtpt_rej[i] = new TH1F(Form("hMC_muMaxJtpt_rej_cent%d",i),Form("MC muMax/Jtpt fail cutA in centrality bin ",i),100,0,1);
    hData_muSumJtpt_rej[i] = new TH1F(Form("hData_muSumJtpt_rej_cent%d",i),Form("Data muSum/Jtpt fail cutA in centrality bin %d",i),100,0,1);
    hMC_muSumJtpt_rej[i] = new TH1F(Form("hMC_muSumJtpt_rej_cent%d",i),Form("MC muSum/Jtpt fail cutA in centrality bin ",i),100,0,1);

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
  entries = 1000;
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
   if(calopt_1/pfpt_1 <= 0.5 && eMax_1/Sumcand < 0.05) {
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
   if(calopt_1/pfpt_1 > 0.5 && calopt_1/pfpt_1 <= 0.85 && eMax_1/Sumcand < (18/7 *(Float_t)calopt_1/pfpt_1 - 9/7)) ){
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
  if(calopt_1/pfpt_1 > 0.5 && calopt_1/pfpt_1 <= 0.85 && eMax_1/Sumcand >= (18/7 *(Float_t)calopt_1/pfpt_1 - 9/7)) ){
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
  duentries = 1000;
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
    if(eMax_1/Sumcand >= 0.05) {
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
  mentries = 1000;
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
         hMC_chMaxJtpt_keep[centb1]->Fill(chMax_2/pfpt_2);
         hMC_eMaxJtpt_keep[centb1]->Fill(eMax_2/pfpt_2);
         hMC_neMaxJtpt_keep[centb1]->Fill(neMax_2/pfpt_2);
         hMC_phMaxJtpt_keep[centb1]->Fill(phMax_2/pfpt_2);
         hMC_muMaxJtpt_keep[centb1]->Fill(muMax_2/pfpt_2);
         hMC_chSumJtpt_keep[centb1]->Fill(chSum_2/pfpt_2);
         hMC_eSumJtpt_keep[centb1]->Fill(eSum_2/pfpt_2);
         hMC_neSumJtpt_keep[centb1]->Fill(neSum_2/pfpt_2);
         hMC_phSumJtpt_keep[centb1]->Fill(phSum_2/pfpt_2);
         hMC_muSumJtpt_keep[centb1]->Fill(muSum_2/pfpt_2);
   }
   if(calopt_2/pfpt_2 > 0.5 && calopt_2/pfpt_2 <= 0.85 && eMax_2/Sumcand < (18/7 *(Float_t)calopt_2/pfpt_2 - 9/7)) ){
         hMC_chMaxJtpt_keep[centb1]->Fill(chMax_2/pfpt_2);
         hMC_eMaxJtpt_keep[centb1]->Fill(eMax_2/pfpt_2);
         hMC_neMaxJtpt_keep[centb1]->Fill(neMax_2/pfpt_2);
         hMC_phMaxJtpt_keep[centb1]->Fill(phMax_2/pfpt_2);
         hMC_muMaxJtpt_keep[centb1]->Fill(muMax_2/pfpt_2);
         hMC_chSumJtpt_keep[centb1]->Fill(chSum_2/pfpt_2);
         hMC_eSumJtpt_keep[centb1]->Fill(eSum_2/pfpt_2);
         hMC_neSumJtpt_keep[centb1]->Fill(neSum_2/pfpt_2);
         hMC_phSumJtpt_keep[centb1]->Fill(phSum_2/pfpt_2);
         hMC_muSumJtpt_keep[centb1]->Fill(muSum_2/pfpt_2);
   }
   if(calopt_2/pfpt_2 > 0.85){
         hMC_chMaxJtpt_keep[centb1]->Fill(chMax_2/pfpt_2);
         hMC_eMaxJtpt_keep[centb1]->Fill(eMax_2/pfpt_2);
         hMC_neMaxJtpt_keep[centb1]->Fill(neMax_2/pfpt_2);
         hMC_phMaxJtpt_keep[centb1]->Fill(phMax_2/pfpt_2);
         hMC_muMaxJtpt_keep[centb1]->Fill(muMax_2/pfpt_2);
         hMC_chSumJtpt_keep[centb1]->Fill(chSum_2/pfpt_2);
         hMC_eSumJtpt_keep[centb1]->Fill(eSum_2/pfpt_2);
         hMC_neSumJtpt_keep[centb1]->Fill(neSum_2/pfpt_2);
         hMC_phSumJtpt_keep[centb1]->Fill(phSum_2/pfpt_2);
         hMC_muSumJtpt_keep[centb1]->Fill(muSum_2/pfpt_2);
   }
// rejected:
  if(calopt_2/pfpt_2 > 0.5 && calopt_2/pfpt_2 <= 0.85 && eMax_2/Sumcand >= (18/7 *(Float_t)calopt_2/pfpt_2 - 9/7)) ){
         hMC_chMaxJtpt_rej[centb1]->Fill(chMax_2/pfpt_2);
         hMC_eMaxJtpt_rej[centb1]->Fill(eMax_2/pfpt_2);
         hMC_neMaxJtpt_rej[centb1]->Fill(neMax_2/pfpt_2);
         hMC_phMaxJtpt_rej[centb1]->Fill(phMax_2/pfpt_2);
         hMC_muMaxJtpt_rej[centb1]->Fill(muMax_2/pfpt_2);
         hMC_chSumJtpt_rej[centb1]->Fill(chSum_2/pfpt_2);
         hMC_eSumJtpt_rej[centb1]->Fill(eSum_2/pfpt_2);
         hMC_neSumJtpt_rej[centb1]->Fill(neSum_2/pfpt_2);
         hMC_phSumJtpt_rej[centb1]->Fill(phSum_2/pfpt_2);
         hMC_muSumJtpt_rej[centb1]->Fill(muSum_2/pfpt_2);
   }
   if(calopt_2/pfpt_2 <= 0.5 && eMax_2/Sumcand >= 0.05) {
         hMC_chMaxJtpt_rej[centb1]->Fill(chMax_2/pfpt_2);
         hMC_eMaxJtpt_rej[centb1]->Fill(eMax_2/pfpt_2);
         hMC_neMaxJtpt_rej[centb1]->Fill(neMax_2/pfpt_2);
         hMC_phMaxJtpt_rej[centb1]->Fill(phMax_2/pfpt_2);
         hMC_muMaxJtpt_rej[centb1]->Fill(muMax_2/pfpt_2);
         hMC_chSumJtpt_rej[centb1]->Fill(chSum_2/pfpt_2);
         hMC_eSumJtpt_rej[centb1]->Fill(eSum_2/pfpt_2);
         hMC_neSumJtpt_rej[centb1]->Fill(neSum_2/pfpt_2);
         hMC_phSumJtpt_rej[centb1]->Fill(phSum_2/pfpt_2);
         hMC_muSumJtpt_rej[centb1]->Fill(muSum_2/pfpt_2);
   }
       } // end pfptmin loop
  } // end MC matched loop


  
  long muentries = MC_unmatched->GetEntries();
  //entries = 1;
  muentries = 1000;
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
         hMC_chMaxJtpt_keep[centb1]->Fill(chMax_2/pfpt_2);
         hMC_eMaxJtpt_keep[centb1]->Fill(eMax_2/pfpt_2);
         hMC_neMaxJtpt_keep[centb1]->Fill(neMax_2/pfpt_2);
         hMC_phMaxJtpt_keep[centb1]->Fill(phMax_2/pfpt_2);
         hMC_muMaxJtpt_keep[centb1]->Fill(muMax_2/pfpt_2);
         hMC_chSumJtpt_keep[centb1]->Fill(chSum_2/pfpt_2);
         hMC_eSumJtpt_keep[centb1]->Fill(eSum_2/pfpt_2);
         hMC_neSumJtpt_keep[centb1]->Fill(neSum_2/pfpt_2);
         hMC_phSumJtpt_keep[centb1]->Fill(phSum_2/pfpt_2);
         hMC_muSumJtpt_keep[centb1]->Fill(muSum_2/pfpt_2);
    }
    if(eMax_2/Sumcand >= 0.05) {
         hMC_chMaxJtpt_rej[centb1]->Fill(chMax_2/pfpt_2);
         hMC_eMaxJtpt_rej[centb1]->Fill(eMax_2/pfpt_2);
         hMC_neMaxJtpt_rej[centb1]->Fill(neMax_2/pfpt_2);
         hMC_phMaxJtpt_rej[centb1]->Fill(phMax_2/pfpt_2);
         hMC_muMaxJtpt_rej[centb1]->Fill(muMax_2/pfpt_2);
         hMC_chSumJtpt_rej[centb1]->Fill(chSum_2/pfpt_2);
         hMC_eSumJtpt_rej[centb1]->Fill(eSum_2/pfpt_2);
         hMC_neSumJtpt_rej[centb1]->Fill(neSum_2/pfpt_2);
         hMC_phSumJtpt_rej[centb1]->Fill(phSum_2/pfpt_2);
         hMC_muSumJtpt_rej[centb1]->Fill(muSum_2/pfpt_2);
    }  
    } // end pfptmin loop
  } // end MC unmatched loop

 /// end of looking at matched and unmatched, now to plot!!! 
// save those histos to a root file, remembering that I did DrawNormalized, so they are not normalized in the root file!  
  TFile fout("PbPb_JetIDPlots_NoCuts_and_YetkinCuts_matchedAndUn_slantedlinecalopfpt_eMaxSumcand_A.root","RECREATE");
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
  
  for(int i = 0 ; i < 1 ; ++i){

    cchMaxJtpt[i] = new TCanvas(Form("cchMaxJtpt_cent%d",i),"",800,600);
    cchMaxJtpt[i]->SetLogy();
    hMC_chMaxJtpt[i]->SetMarkerColor(kRed);
    hMC_chMaxJtpt[i]->SetMarkerStyle(25);
    hMC_chMaxJtpt[i]->Print("base");
    hMC_chMaxJtpt[i]->SetTitle(Form("%i - %i %",centrality_bins[i],centrality_bins[i+1]));
    hMC_chMaxJtpt[i]->SetXTitle("chMax/PF p_{T} no cuts");
    hMC_chMaxJtpt[i]->DrawNormalized();

    hData_chMaxJtpt[i]->SetMarkerStyle(24);
    hData_chMaxJtpt[i]->SetMarkerColor(kBlack);
    hData_chMaxJtpt[i]->DrawNormalized("same");
    //       drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.9,20);
    char *MyCentBin = Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]);
//    char *MyCentBin = Form("%2.0f - %2.0f %",centrality_bins[i],centrality_bins[i+1]);
//    cout<<"MyCentBin: "<<MyCentBin<<endl;
//    drawText(MyCentBin,0.8,0.8,16);
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.8,16);
    
    TLegend * leg = myLegend(0.7,0.7,0.8,0.8);
    leg->AddEntry(hMC_chMaxJtpt[0],"MC","PL");
    leg->AddEntry(hData_chMaxJtpt[0],"Data","PL");
    leg->SetTextSize(0.04);
    leg->Draw();

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