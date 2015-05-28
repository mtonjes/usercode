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

#include "/net/hisrv0001/home/belt/wrk/JetRAA/RaghavCode/Headers/plot.h"
void eMaxCutGen_study(Int_t radius = 3){

  TH1::SetDefaultSumw2();
  TFile * fData, * fMC;
  fData = TFile::Open("/mnt/hadoop/cms/store/user/pawan/ntuples/JetRaa_akPu234_PbPb_Data.root");
  fMC = TFile::Open("/mnt/hadoop/cms/store/user/pawan/ntuples/JetRaa_akPu234_PbPb_MC.root");
  
  TTree * Data_matched= (TTree*)fData->Get(Form("akPu%dJetAnalyzer/matchedJets",radius));
  TTree * Data_unmatched = (TTree*)fData->Get(Form("akPu%dJetAnalyzer/unmatchedPFJets",radius));

  TTree * MC_matched = (TTree*)fMC->Get(Form("akPu%dJetAnalyzer/matchedJets",radius));
  TTree * MC_unmatched = (TTree*)fMC->Get(Form("akPu%dJetAnalyzer/unmatchedPFJets",radius));


  TH1F * hMC_AllTrig_noCut_pfrefOverpfpt = new TH1F(" hMC_AllTrig_noCut_pfrefOverpfpt","",1000,-40,10);
  TH1F * hMC_AllTrig_CutA_pfrefOverpfpt_rej = new TH1F("hMC_AllTrig_CutA_pfrefOverpfpt_rej","",1000,-40,10);
  TH1F * hMC_AllTrig_CutA_pfrefOverpfpt_keep = new TH1F("hMC_AllTrig_CutA_pfrefOverpfpt_keep","",1000,-40,10);
  TH1F * hMC_AllTrig_noCut_pfrefOverpfpt_pfrefptgt0 = new TH1F(" hMC_AllTrig_noCut_pfrefOverpfpt_pfrefOverpfpt","",1000,0,10);
  TH1F * hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_rej = new TH1F("hMC_AllTrig_CutA_pfrefOverpfpt_pfrefOverpfpt_rej","",1000,0,10);
  TH1F * hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_keep = new TH1F("hMC_AllTrig_CutA_pfrefOverpfpt_pfrefOverpfpt_keep","",1000,0,10);
  
  TH1F * hMC_AllTrig_noCut_pfrefOverpfpt_matchAndUn = new TH1F(" hMC_AllTrig_noCut_pfrefOverpfpt_matchAndUn","",1000,-40,10);
  TH1F * hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_rej = new TH1F("hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_rej","",1000,-40,10);
  TH1F * hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_keep = new TH1F("hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_keep","",1000,-40,10);
  TH1F * hMC_AllTrig_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0 = new TH1F(" hMC_AllTrig_noCut_pfrefOverpfpt_matchAndUn_pfrefOverpfpt_matchAndUn","",1000,0,10);
  TH1F * hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej = new TH1F("hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefOverpfpt_matchAndUn_rej","",1000,0,10);
  TH1F * hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep = new TH1F("hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefOverpfpt_matchAndUn_keep","",1000,0,10);


  TH1F * hMC_Jet55_noCut_pfrefOverpfpt_matchAndUn = new TH1F(" hMC_Jet55_noCut_pfrefOverpfpt_matchAndUn","",1000,-40,10);
  TH1F * hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_rej = new TH1F("hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_rej","",1000,-40,10);
  TH1F * hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_keep = new TH1F("hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_keep","",1000,-40,10);
  TH1F * hMC_Jet55_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0 = new TH1F(" hMC_Jet55_noCut_pfrefOverpfpt_matchAndUn_pfrefOverpfpt_matchAndUn","",1000,0,10);
  TH1F * hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej = new TH1F("hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefOverpfpt_matchAndUn_rej","",1000,0,10);
  TH1F * hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep = new TH1F("hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefOverpfpt_matchAndUn_keep","",1000,0,10);
  TH1F * hMC_Jet65_noCut_pfrefOverpfpt_matchAndUn = new TH1F(" hMC_Jet65_noCut_pfrefOverpfpt_matchAndUn","",1000,-40,10);
  TH1F * hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_rej = new TH1F("hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_rej","",1000,-40,10);
  TH1F * hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_keep = new TH1F("hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_keep","",1000,-40,10);
  TH1F * hMC_Jet65_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0 = new TH1F(" hMC_Jet65_noCut_pfrefOverpfpt_matchAndUn_pfrefOverpfpt_matchAndUn","",1000,0,10);
  TH1F * hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej = new TH1F("hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefOverpfpt_matchAndUn_rej","",1000,0,10);
  TH1F * hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep = new TH1F("hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefOverpfpt_matchAndUn_keep","",1000,0,10);
  TH1F * hMC_Jet80_noCut_pfrefOverpfpt_matchAndUn = new TH1F(" hMC_Jet80_noCut_pfrefOverpfpt_matchAndUn","",1000,-40,10);
  TH1F * hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_rej = new TH1F("hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_rej","",1000,-40,10);
  TH1F * hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_keep = new TH1F("hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_keep","",1000,-40,10);
  TH1F * hMC_Jet80_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0 = new TH1F(" hMC_Jet80_noCut_pfrefOverpfpt_matchAndUn_pfrefOverpfpt_matchAndUn","",1000,0,10);
  TH1F * hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej = new TH1F("hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefOverpfpt_matchAndUn_rej","",1000,0,10);
  TH1F * hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep = new TH1F("hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefOverpfpt_matchAndUn_keep","",1000,0,10);
 
   TH1F * hMC_NoTrig_noCut_pfrefOverpfpt_matchAndUn = new TH1F(" hMC_NoTrig_noCut_pfrefOverpfpt_matchAndUn","",1000,-40,10);
  TH1F * hMC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_rej = new TH1F("hMC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_rej","",1000,-40,10);
  TH1F * hMC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_keep = new TH1F("hMC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_keep","",1000,-40,10);
   
  // this cut is: 
  
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
  Int_t jet55_p_2, jet65_p_2, jet80_p_2;
  Int_t subid;

  Data_matched->SetBranchAddress("calopt",&calopt_1);
  Data_matched->SetBranchAddress("pfpt",&pfpt_1);
  Data_matched->SetBranchAddress("eMax",&eMax_1);
  Data_matched->SetBranchAddress("chMax",&chMax_1);
  Data_matched->SetBranchAddress("chSum",&chSum_1);
  Data_matched->SetBranchAddress("phSum",&phSum_1);
  Data_matched->SetBranchAddress("neSum",&neSum_1);
  Data_matched->SetBranchAddress("muSum",&muSum_1);
  Data_matched->SetBranchAddress("jet55",&jet55_1);
  Data_matched->SetBranchAddress("jet65",&jet65_1);
  Data_matched->SetBranchAddress("jet80",&jet80_1);
  Data_matched->SetBranchAddress("jet55_prescl",&jet55_p_1);
  Data_matched->SetBranchAddress("jet65_prescl",&jet65_p_1);
  Data_matched->SetBranchAddress("jet80_prescl",&jet80_p_1);
  
  Data_unmatched->SetBranchAddress("pfpt",&pfpt_1);
  Data_unmatched->SetBranchAddress("eMax",&eMax_1);
  Data_unmatched->SetBranchAddress("chMax",&chMax_1);
  Data_unmatched->SetBranchAddress("chSum",&chSum_1);
  Data_unmatched->SetBranchAddress("phSum",&phSum_1);
  Data_unmatched->SetBranchAddress("neSum",&neSum_1);
  Data_unmatched->SetBranchAddress("muSum",&muSum_1);
  Data_unmatched->SetBranchAddress("jet55",&jet55_1);
  Data_unmatched->SetBranchAddress("jet65",&jet65_1);
  Data_unmatched->SetBranchAddress("jet80",&jet80_1);
  Data_unmatched->SetBranchAddress("jet55_prescl",&jet55_p_1);
  Data_unmatched->SetBranchAddress("jet65_prescl",&jet65_p_1);
  Data_unmatched->SetBranchAddress("jet80_prescl",&jet80_p_1);
  
  MC_matched->SetBranchAddress("calopt",&calopt_2);
  MC_matched->SetBranchAddress("pfpt",&pfpt_2);
  MC_matched->SetBranchAddress("eMax",&eMax_2);
  MC_matched->SetBranchAddress("chMax",&chMax_2);
  MC_matched->SetBranchAddress("chSum",&chSum_2);
  MC_matched->SetBranchAddress("phSum",&phSum_2);
  MC_matched->SetBranchAddress("neSum",&neSum_2);
  MC_matched->SetBranchAddress("muSum",&muSum_2);
  MC_matched->SetBranchAddress("refpt",&pfrefpt_2);
  MC_matched->SetBranchAddress("jet55",&jet55_2);
  MC_matched->SetBranchAddress("jet65",&jet65_2);
  MC_matched->SetBranchAddress("jet80",&jet80_2);
    MC_matched->SetBranchAddress("subid",&subid);

  MC_unmatched->SetBranchAddress("pfpt",&pfpt_2);
  MC_unmatched->SetBranchAddress("eMax",&eMax_2);
  MC_unmatched->SetBranchAddress("chMax",&chMax_2);
  MC_unmatched->SetBranchAddress("chSum",&chSum_2);
  MC_unmatched->SetBranchAddress("phSum",&phSum_2);
  MC_unmatched->SetBranchAddress("neSum",&neSum_2);
  MC_unmatched->SetBranchAddress("muSum",&muSum_2);
  MC_unmatched->SetBranchAddress("refpt",&pfrefpt_2);
  MC_unmatched->SetBranchAddress("jet55",&jet55_2);
  MC_unmatched->SetBranchAddress("jet65",&jet65_2);
  MC_unmatched->SetBranchAddress("jet80",&jet80_2);
  MC_unmatched->SetBranchAddress("subid",&subid);

 long nentries = MC_matched->GetEntries();
  //entries = 1;
  // MC loop
  cout<<" looking at matched MC ntuple "<<endl;
  for(long nentry = 0; nentry < nentries; ++nentry){

    if(nentry%100000 == 0) cout<<nentry<<"/"<<nentries<<endl;
    MC_matched->GetEntry(nentry);
    
    Float_t Sumcand = chSum_2 + phSum_2 + neSum_2 + muSum_2;
    Float_t ratioGenPF = pfrefpt_2/pfpt_2;
    if(subid==0){
    hMC_AllTrig_noCut_pfrefOverpfpt->Fill(ratioGenPF);
    hMC_AllTrig_noCut_pfrefOverpfpt_matchAndUn->Fill(ratioGenPF);
    if(pfrefpt_2>0){
       hMC_AllTrig_noCut_pfrefOverpfpt_pfrefptgt0->Fill(ratioGenPF);
       hMC_AllTrig_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->Fill(ratioGenPF);
    }
// all triggers
   if(calopt_2/pfpt_2 <= 0.5 && eMax_2/Sumcand < 0.05) {
   		hMC_AllTrig_CutA_pfrefOverpfpt_keep->Fill(ratioGenPF);
   		hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_keep->Fill(ratioGenPF); 
   		if(pfrefpt_2>0){
   		   hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_keep->Fill(ratioGenPF); 
   		   hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->Fill(ratioGenPF);
   		}
   }
   if(calopt_2/pfpt_2 > 0.5 && calopt_2/pfpt_2 <= 0.85 && eMax_2/Sumcand < (18/7 *(Float_t)calopt_2/pfpt_2 - 9/7)) {
   		hMC_AllTrig_CutA_pfrefOverpfpt_keep->Fill(ratioGenPF);
   		hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_keep->Fill(ratioGenPF); 
   		if(pfrefpt_2>0){
   		   hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_keep->Fill(ratioGenPF);
   		   hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->Fill(ratioGenPF);
   		}
   }
   if(calopt_2/pfpt_2 > 0.85){
    	hMC_AllTrig_CutA_pfrefOverpfpt_keep->Fill(ratioGenPF);
    	hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_keep->Fill(ratioGenPF); 
    	if(pfrefpt_2>0){
   		   hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_keep->Fill(ratioGenPF); 
   		   hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->Fill(ratioGenPF); 
   		}
   }
// rejected area:
   if(calopt_2/pfpt_2 > 0.5 && calopt_2/pfpt_2 <= 0.85 && eMax_2/Sumcand >= (18/7 *(Float_t)calopt_2/pfpt_2 - 9/7)) {
   		hMC_AllTrig_CutA_pfrefOverpfpt_rej->Fill(ratioGenPF);
   		hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_rej->Fill(ratioGenPF);
   		if(pfrefpt_2>0){
   		   hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_rej->Fill(ratioGenPF);
   		   hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->Fill(ratioGenPF);
   		}
   }
   if(calopt_2/pfpt_2 <= 0.5 && eMax_2/Sumcand >= 0.05) {
   		hMC_AllTrig_CutA_pfrefOverpfpt_rej->Fill(ratioGenPF);
   		hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_rej->Fill(ratioGenPF);
   		if(pfrefpt_2>0){
   		   hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_rej->Fill(ratioGenPF);
   		   hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->Fill(ratioGenPF);
   		}
   }
   
// !jet55 !jet65 !jet80
  if(jet55_2 == 0 && jet65_2==0 && jet80_2 == 0){
      hMC_NoTrig_noCut_pfrefOverpfpt_matchAndUn->Fill(ratioGenPF);
   if(calopt_2/pfpt_2 <= 0.5 && eMax_2/Sumcand < 0.05) {
   		hMC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_keep->Fill(ratioGenPF); 
   }
   if(calopt_2/pfpt_2 > 0.5 && calopt_2/pfpt_2 <= 0.85 && eMax_2/Sumcand < (18/7 *(Float_t)calopt_2/pfpt_2 - 9/7)) {
   		hMC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_keep->Fill(ratioGenPF); 
   }
   if(calopt_2/pfpt_2 > 0.85){
    	hMC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_keep->Fill(ratioGenPF); 
   }
// rejected area:
   if(calopt_2/pfpt_2 > 0.5 && calopt_2/pfpt_2 <= 0.85 && eMax_2/Sumcand >= (18/7 *(Float_t)calopt_2/pfpt_2 - 9/7)) {
   		hMC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_rej->Fill(ratioGenPF);
   }
   if(calopt_2/pfpt_2 <= 0.5 && eMax_2/Sumcand >= 0.05) {
   		hMC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_rej->Fill(ratioGenPF);
   } // end NoTrig
  } // end noTrig
   
// jet55 !jet65 !jet80   
  if(jet55_2 == 1 && jet65_2==0 && jet80_2 == 0){
      hMC_Jet55_noCut_pfrefOverpfpt_matchAndUn->Fill(ratioGenPF);
    if(pfrefpt_2>0){
       hMC_Jet55_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->Fill(ratioGenPF);
    }
   if(calopt_2/pfpt_2 <= 0.5 && eMax_2/Sumcand < 0.05) {
   		hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_keep->Fill(ratioGenPF); 
   		if(pfrefpt_2>0){
   		   hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->Fill(ratioGenPF);
   		}
   }
   if(calopt_2/pfpt_2 > 0.5 && calopt_2/pfpt_2 <= 0.85 && eMax_2/Sumcand < (18/7 *(Float_t)calopt_2/pfpt_2 - 9/7)) {
   		hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_keep->Fill(ratioGenPF); 
   		if(pfrefpt_2>0){
   		   hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->Fill(ratioGenPF);
   		}
   }
   if(calopt_2/pfpt_2 > 0.85){
    	hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_keep->Fill(ratioGenPF); 
    	if(pfrefpt_2>0){
   		   hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->Fill(ratioGenPF); 
   		}
   }
// rejected area:
   if(calopt_2/pfpt_2 > 0.5 && calopt_2/pfpt_2 <= 0.85 && eMax_2/Sumcand >= (18/7 *(Float_t)calopt_2/pfpt_2 - 9/7)) {
   		hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_rej->Fill(ratioGenPF);
   		if(pfrefpt_2>0){
   		   hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->Fill(ratioGenPF);
   		}
   }
   if(calopt_2/pfpt_2 <= 0.5 && eMax_2/Sumcand >= 0.05) {
   		hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_rej->Fill(ratioGenPF);
   		if(pfrefpt_2>0){
   		   hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->Fill(ratioGenPF);
   		}
   } 
  } // end jet55
//  
// jet65 !jet80 
     if(jet65_2 == 1 && jet80_2 == 0){
         hMC_Jet65_noCut_pfrefOverpfpt_matchAndUn->Fill(ratioGenPF);
    if(pfrefpt_2>0){
       hMC_Jet65_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->Fill(ratioGenPF);
    }
   if(calopt_2/pfpt_2 <= 0.5 && eMax_2/Sumcand < 0.05) {
   		hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_keep->Fill(ratioGenPF); 
   		if(pfrefpt_2>0){
   		   hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->Fill(ratioGenPF);
   		}
   }
   if(calopt_2/pfpt_2 > 0.5 && calopt_2/pfpt_2 <= 0.85 && eMax_2/Sumcand < (18/7 *(Float_t)calopt_2/pfpt_2 - 9/7)) {
   		hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_keep->Fill(ratioGenPF); 
   		if(pfrefpt_2>0){
   		   hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->Fill(ratioGenPF);
   		}
   }
   if(calopt_2/pfpt_2 > 0.85){
    	hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_keep->Fill(ratioGenPF); 
    	if(pfrefpt_2>0){
   		   hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->Fill(ratioGenPF); 
   		}
   }
// rejected area:
   if(calopt_2/pfpt_2 > 0.5 && calopt_2/pfpt_2 <= 0.85 && eMax_2/Sumcand >= (18/7 *(Float_t)calopt_2/pfpt_2 - 9/7)) {
   		hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_rej->Fill(ratioGenPF);
   		if(pfrefpt_2>0){
   		   hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->Fill(ratioGenPF);
   		}
   }
   if(calopt_2/pfpt_2 <= 0.5 && eMax_2/Sumcand >= 0.05) {
   		hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_rej->Fill(ratioGenPF);
   		if(pfrefpt_2>0){
   		   hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->Fill(ratioGenPF);
   		}
   }

     } // end jet65
// 
//     
     if(jet80_2 == 1){
         hMC_Jet80_noCut_pfrefOverpfpt_matchAndUn->Fill(ratioGenPF);
    if(pfrefpt_2>0){
       hMC_Jet80_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->Fill(ratioGenPF);
    }
   if(calopt_2/pfpt_2 <= 0.5 && eMax_2/Sumcand < 0.05) {
   		hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_keep->Fill(ratioGenPF); 
   		if(pfrefpt_2>0){
   		   hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->Fill(ratioGenPF);
   		}
   }
   if(calopt_2/pfpt_2 > 0.5 && calopt_2/pfpt_2 <= 0.85 && eMax_2/Sumcand < (18/7 *(Float_t)calopt_2/pfpt_2 - 9/7)) {
   		hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_keep->Fill(ratioGenPF); 
   		if(pfrefpt_2>0){
   		   hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->Fill(ratioGenPF);
   		}
   }
   if(calopt_2/pfpt_2 > 0.85){
    	hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_keep->Fill(ratioGenPF); 
    	if(pfrefpt_2>0){
   		   hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->Fill(ratioGenPF); 
   		}
   }
// rejected area:
   if(calopt_2/pfpt_2 > 0.5 && calopt_2/pfpt_2 <= 0.85 && eMax_2/Sumcand >= (18/7 *(Float_t)calopt_2/pfpt_2 - 9/7)) {
   		hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_rej->Fill(ratioGenPF);
   		if(pfrefpt_2>0){
   		   hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->Fill(ratioGenPF);
   		}
   }
   if(calopt_2/pfpt_2 <= 0.5 && eMax_2/Sumcand >= 0.05) {
   		hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_rej->Fill(ratioGenPF);
   		if(pfrefpt_2>0){
   		   hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->Fill(ratioGenPF);
   		}
   }

     }
    
} // end subid loop    
  }// mc matched ntuple loop


  long entries = MC_unmatched->GetEntries();
  //entries = 1;
  // MC loop
  cout<<" looking at unmatched MC ntuple"<<endl;
  for(long nentry = 0; nentry < entries; ++nentry){

    if(nentry%100000 == 0) cout<<nentry<<"/"<<entries<<endl;
    MC_unmatched->GetEntry(nentry);
    
    Float_t Sumcand = chSum_2 + phSum_2 + neSum_2 + muSum_2;
    Float_t ratioGenPF = pfrefpt_2/pfpt_2;
    if(subid==0){
    hMC_AllTrig_noCut_pfrefOverpfpt_matchAndUn->Fill(ratioGenPF);
    if(pfrefpt_2>0){
        hMC_AllTrig_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->Fill(ratioGenPF);
    }
    if(eMax_2/Sumcand < 0.05) {
        hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_keep->Fill(ratioGenPF);  
    	if(pfrefpt_2>0){
   		     hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->Fill(ratioGenPF);
   		}    
    } 
    if(eMax_2/Sumcand >= 0.05) {
        hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_rej->Fill(ratioGenPF); 
        if(pfrefpt_2>0){
            hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->Fill(ratioGenPF);
        }
    }
    
   if(jet55_2 == 0 && jet65_2==0 && jet80_2 == 0){
    hMC_NoTrig_noCut_pfrefOverpfpt_matchAndUn->Fill(ratioGenPF);
    if(eMax_2/Sumcand < 0.05) {
        hMC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_keep->Fill(ratioGenPF);  
    } 
    if(eMax_2/Sumcand >= 0.05) {
        hMC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_rej->Fill(ratioGenPF); 
    }
   } // end NoTrig      
// jet55 !jet65 !jet80   
  if(jet55_2 == 1 && jet65_2==0 && jet80_2 == 0){
    hMC_Jet55_noCut_pfrefOverpfpt_matchAndUn->Fill(ratioGenPF);
    if(pfrefpt_2>0){
        hMC_Jet55_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->Fill(ratioGenPF);
    }
    if(eMax_2/Sumcand < 0.05) {
        hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_keep->Fill(ratioGenPF);  
    	if(pfrefpt_2>0){
   		     hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->Fill(ratioGenPF);
   		}    
    } 
    if(eMax_2/Sumcand >= 0.05) {
        hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_rej->Fill(ratioGenPF); 
        if(pfrefpt_2>0){
            hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->Fill(ratioGenPF);
        }
    }
   } // end jet55
// jet65 !jet80 
   if(jet65_2 == 1 && jet80_2 == 0){
    hMC_Jet65_noCut_pfrefOverpfpt_matchAndUn->Fill(ratioGenPF);
    if(pfrefpt_2>0){
        hMC_Jet65_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->Fill(ratioGenPF);
    }
    if(eMax_2/Sumcand < 0.05) {
        hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_keep->Fill(ratioGenPF);  
    	if(pfrefpt_2>0){
   		     hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->Fill(ratioGenPF);
   		}    
    } 
    if(eMax_2/Sumcand >= 0.05) {
        hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_rej->Fill(ratioGenPF); 
        if(pfrefpt_2>0){
            hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->Fill(ratioGenPF);
        }
    }
  } // end jet65  
   if(jet80_2 == 1){
    hMC_Jet80_noCut_pfrefOverpfpt_matchAndUn->Fill(ratioGenPF);
    if(pfrefpt_2>0){
        hMC_Jet80_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->Fill(ratioGenPF);
    }
    if(eMax_2/Sumcand < 0.05) {
        hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_keep->Fill(ratioGenPF);  
    	if(pfrefpt_2>0){
   		     hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->Fill(ratioGenPF);
   		}    
    } 
    if(eMax_2/Sumcand >= 0.05) {
        hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_rej->Fill(ratioGenPF); 
        if(pfrefpt_2>0){
            hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->Fill(ratioGenPF);
        }
    }
  } // end jet80 
} // end subid loop  
  }// mc unmatched  ntuple loop
  


  TFile fout(Form("Plots/PbPb_MCGenStudy_YetkinCuts_matched_slantedlinecalopfpt_addingunmatched_exclusionhighertriggers_eMaxSumcand_A_R0p%d.root",radius),"RECREATE");
   hMC_AllTrig_noCut_pfrefOverpfpt->Write();
   hMC_AllTrig_CutA_pfrefOverpfpt_rej->Write();
   hMC_AllTrig_CutA_pfrefOverpfpt_keep->Write();
   hMC_AllTrig_noCut_pfrefOverpfpt_pfrefptgt0->Write();
   hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_rej->Write();
   hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_keep->Write();
     hMC_AllTrig_noCut_pfrefOverpfpt_matchAndUn->Write();
     hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_rej->Write();
     hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_keep->Write();
     hMC_AllTrig_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->Write();
     hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->Write();
     hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->Write();
hMC_Jet55_noCut_pfrefOverpfpt_matchAndUn->Write();
hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_rej->Write();
hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_keep->Write();
hMC_Jet55_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->Write();
hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->Write();
hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->Write();
hMC_Jet65_noCut_pfrefOverpfpt_matchAndUn->Write();
hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_rej->Write();
hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_keep->Write();
hMC_Jet65_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->Write();
hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->Write();
hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->Write();
hMC_Jet80_noCut_pfrefOverpfpt_matchAndUn->Write();
hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_rej->Write();
hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_keep->Write();
hMC_Jet80_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->Write();
hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->Write();
hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->Write();

  gStyle->SetOptStat(000000);
  // add the unmatched histograms to the matched ones to get the final cut efficiency
  TCanvas * cGenJetMC = new TCanvas("cGenJetMC","",800,600);
  cGenJetMC->SetLogy();

  hMC_AllTrig_noCut_pfrefOverpfpt->SetMarkerColor(kBlack);
  hMC_AllTrig_noCut_pfrefOverpfpt->SetMarkerStyle(25);
  hMC_AllTrig_noCut_pfrefOverpfpt->SetXTitle("GenJet p_{T} (subid selected)/ matched PF p_{T}");
  hMC_AllTrig_noCut_pfrefOverpfpt->Draw();
  Int_t MC_AllTrig_noCut_pfrefOverpfpt=hMC_AllTrig_noCut_pfrefOverpfpt->GetEntries();
  cout<<"hMC_AllTrig_noCut_pfrefOverpfpt: "<<hMC_AllTrig_noCut_pfrefOverpfpt->GetEntries()<<endl;;
  
  hMC_AllTrig_CutA_pfrefOverpfpt_rej->SetMarkerColor(kRed);
  hMC_AllTrig_CutA_pfrefOverpfpt_rej->SetMarkerStyle(20);
  hMC_AllTrig_CutA_pfrefOverpfpt_rej->Draw("same");
  Int_t MC_AllTrig_CutA_pfrefOverpfpt_rej=hMC_AllTrig_CutA_pfrefOverpfpt_rej->GetEntries();
  cout<<"hMC_AllTrig_CutA_pfrefOverpfpt_rej: "<<hMC_AllTrig_CutA_pfrefOverpfpt_rej->GetEntries()<<endl;;
    
  hMC_AllTrig_CutA_pfrefOverpfpt_keep->SetMarkerColor(kGreen);
  hMC_AllTrig_CutA_pfrefOverpfpt_keep->SetMarkerStyle(20);
  hMC_AllTrig_CutA_pfrefOverpfpt_keep->Draw("same");
  Int_t MC_AllTrig_CutA_pfrefOverpfpt_keep=hMC_AllTrig_CutA_pfrefOverpfpt_keep->GetEntries();
  cout<<"hMC_AllTrig_CutA_pfrefOverpfpt_keep: "<<hMC_AllTrig_CutA_pfrefOverpfpt_keep->GetEntries()<<endl;;
        
      TLegend * LpfrefOverpfpt_full = myLegend(0.2,0.6,0.4,0.8);
      LpfrefOverpfpt_full->SetTextSize(0.03);
      LpfrefOverpfpt_full->AddEntry(hMC_AllTrig_noCut_pfrefOverpfpt,Form("Matched MC all jets: %d entries",MC_AllTrig_noCut_pfrefOverpfpt),"pl");
      LpfrefOverpfpt_full->AddEntry(hMC_AllTrig_CutA_pfrefOverpfpt_keep,Form("Matched MC keep CutA: %d entries",MC_AllTrig_CutA_pfrefOverpfpt_keep),"pl");
      LpfrefOverpfpt_full->AddEntry(hMC_AllTrig_CutA_pfrefOverpfpt_rej,Form("Matched MC reject CutA: %d entries",MC_AllTrig_CutA_pfrefOverpfpt_rej),"pl");
      LpfrefOverpfpt_full->Draw();
      
  cGenJetMC->SaveAs(Form("Plots/R%d/hMC_AllTrig_YetkinCuts_CutA_pfrefOverpfpt_fullrange_subid_R0p%d.pdf",radius,radius),"RECREATE");

  TCanvas * cGenJetMC_pfrefptgt0 = new TCanvas("cGenJetMC_pfrefptgt0","",800,600);
  cGenJetMC_pfrefptgt0->SetLogy();

  hMC_AllTrig_noCut_pfrefOverpfpt_pfrefptgt0->SetMarkerColor(kBlack);
  hMC_AllTrig_noCut_pfrefOverpfpt_pfrefptgt0->SetMarkerStyle(25);
  hMC_AllTrig_noCut_pfrefOverpfpt_pfrefptgt0->SetXTitle("GenJet p_{T} (subid selected)/ matched PF p_{T}");
  hMC_AllTrig_noCut_pfrefOverpfpt_pfrefptgt0->Draw();
  Int_t MC_AllTrig_noCut_pfrefOverpfpt_pfrefptgt0=hMC_AllTrig_noCut_pfrefOverpfpt_pfrefptgt0->GetEntries();
  cout<<"hMC_AllTrig_noCut_pfrefOverpfpt_pfrefptgt0: "<<hMC_AllTrig_noCut_pfrefOverpfpt_pfrefptgt0->GetEntries()<<endl;;

  hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_rej->SetMarkerColor(kRed);
  hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_rej->SetMarkerStyle(20);
  hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_rej->Draw("same");
  Int_t MC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_rej=hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_rej->GetEntries();
  cout<<"hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_rej: "<<hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_rej->GetEntries()<<endl;;

  hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_keep->SetMarkerColor(kGreen);
  hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_keep->SetMarkerStyle(20);
  hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_keep->Draw("same");
  Int_t MC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_keep=hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_keep->GetEntries();
  cout<<"hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_keep: "<<hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_keep->GetEntries()<<endl;;
  
      TLegend * LpfrefOverpfpt = myLegend(0.2,0.7,0.4,0.9);
      LpfrefOverpfpt->SetTextSize(0.03);
      LpfrefOverpfpt->AddEntry(hMC_AllTrig_noCut_pfrefOverpfpt_pfrefptgt0,Form("Matched MC all jets: %d entries",MC_AllTrig_noCut_pfrefOverpfpt_pfrefptgt0),"p");
      LpfrefOverpfpt->AddEntry(hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_keep,Form("Matched MC keep CutA: %d entries",MC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_keep),"p");
      LpfrefOverpfpt->AddEntry(hMC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_rej,Form("Matched MC reject CutA: %d entries",MC_AllTrig_CutA_pfrefOverpfpt_pfrefptgt0_rej),"p");
      LpfrefOverpfpt->Draw();
      
  cGenJetMC_pfrefptgt0->SaveAs(Form("Plots/R%d/hMC_AllTrig_YetkinCuts_CutA_pfrefOverpfpt_pfrefptgt0_subid_R0p%d.pdf",radius,radius),"RECREATE");

  TCanvas * cGenJetMC_matchAndUn = new TCanvas("cGenJetMC_matchAndUn","",800,600);
  cGenJetMC_matchAndUn->SetLogy();

  hMC_AllTrig_noCut_pfrefOverpfpt_matchAndUn->SetMarkerColor(kBlack);
  hMC_AllTrig_noCut_pfrefOverpfpt_matchAndUn->SetMarkerStyle(25);
  hMC_AllTrig_noCut_pfrefOverpfpt_matchAndUn->SetXTitle("GenJet p_{T} (subid selected)/ matched PF p_{T}");
  hMC_AllTrig_noCut_pfrefOverpfpt_matchAndUn->Draw();
  Int_t MC_AllTrig_noCut_pfrefOverpfpt_matchAndUn=hMC_AllTrig_noCut_pfrefOverpfpt_matchAndUn->GetEntries();
  cout<<"hMC_AllTrig_noCut_pfrefOverpfpt_matchAndUn: "<<hMC_AllTrig_noCut_pfrefOverpfpt_matchAndUn->GetEntries()<<endl;;
  
  hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_rej->SetMarkerColor(kOrange);
  hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_rej->SetMarkerStyle(20);
  hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_rej->Draw("same");
  Int_t MC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_rej=hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_rej->GetEntries();
  cout<<"hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_rej: "<<hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_rej->GetEntries()<<endl;;
    
  hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_keep->SetMarkerColor(kBlue);
  hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_keep->SetMarkerStyle(20);
  hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_keep->Draw("same");
  Int_t MC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_keep=hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_keep->GetEntries();
  cout<<"hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_keep: "<<hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_keep->GetEntries()<<endl;;
        
      TLegend * LpfrefOverpfpt_matchAndUn_full = myLegend(0.2,0.6,0.4,0.8);
      LpfrefOverpfpt_matchAndUn_full->SetTextSize(0.03);
      LpfrefOverpfpt_matchAndUn_full->AddEntry(hMC_AllTrig_noCut_pfrefOverpfpt_matchAndUn,Form("Matched and Unmatched MC all jets: %d entries",MC_AllTrig_noCut_pfrefOverpfpt_matchAndUn),"pl");
      LpfrefOverpfpt_matchAndUn_full->AddEntry(hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_keep,Form("Matched and Unmatched MC keep CutA: %d entries",MC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_keep),"pl");
      LpfrefOverpfpt_matchAndUn_full->AddEntry(hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_rej,Form("Matched and Unmatched MC reject CutA: %d entries",MC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_rej),"pl");
      LpfrefOverpfpt_matchAndUn_full->Draw();
      
  cGenJetMC_matchAndUn->SaveAs(Form("Plots/R%d/hMC_AllTrig_YetkinCuts_CutA_pfrefOverpfpt_matchAndUn_fullrange_subid_R0p%d.pdf",radius,radius),"RECREATE");

  TCanvas * cGenJetMC_matchAndUn_pfrefptgt0 = new TCanvas("cGenJetMC_matchAndUn_pfrefptgt0","",800,600);
  cGenJetMC_matchAndUn_pfrefptgt0->SetLogy();

  hMC_AllTrig_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->SetMarkerColor(kBlack);
  hMC_AllTrig_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->SetMarkerStyle(25);
  hMC_AllTrig_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->SetXTitle("GenJet p_{T} (subid selected)/ matched PF p_{T}");
  hMC_AllTrig_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->Draw();
  Int_t MC_AllTrig_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0=hMC_AllTrig_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->GetEntries();
  cout<<"hMC_AllTrig_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0: "<<hMC_AllTrig_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->GetEntries()<<endl;;

  hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->SetMarkerColor(kOrange);
  hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->SetMarkerStyle(20);
  hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->Draw("same");
  Int_t MC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej=hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->GetEntries();
  cout<<"hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej: "<<hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->GetEntries()<<endl;;

  hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->SetMarkerColor(kBlue);
  hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->SetMarkerStyle(20);
  hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->Draw("same");
  Int_t MC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep=hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->GetEntries();
  cout<<"hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep: "<<hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->GetEntries()<<endl;;
  
      TLegend * LpfrefOverpfpt_matchAndUn = myLegend(0.2,0.7,0.4,0.9);
      LpfrefOverpfpt_matchAndUn->SetTextSize(0.03);
      LpfrefOverpfpt_matchAndUn->AddEntry(hMC_AllTrig_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0,Form("Matched and Unmatched MC all jets: %d entries",MC_AllTrig_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0),"p");
      LpfrefOverpfpt_matchAndUn->AddEntry(hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep,Form("Matched and Unmatched MC keep CutA: %d entries",MC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep),"p");
      LpfrefOverpfpt_matchAndUn->AddEntry(hMC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej,Form("Matched and Unmatched MC reject CutA: %d entries",MC_AllTrig_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej),"p");
      LpfrefOverpfpt_matchAndUn->Draw();
      
  cGenJetMC_matchAndUn_pfrefptgt0->SaveAs(Form("Plots/R%d/hMC_AllTrig_YetkinCuts_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_subid_R0p%d.pdf",radius,radius),"RECREATE");

  TCanvas * cGenJetMC_matchAndUn_NoTrig = new TCanvas("cGenJetMC_matchAndUn_NoTrig","",800,600);
  cGenJetMC_matchAndUn_NoTrig->SetLogy();

  hMC_NoTrig_noCut_pfrefOverpfpt_matchAndUn->SetMarkerColor(kBlack);
  hMC_NoTrig_noCut_pfrefOverpfpt_matchAndUn->SetMarkerStyle(25);
  hMC_NoTrig_noCut_pfrefOverpfpt_matchAndUn->SetXTitle("GenJet p_{T} (subid selected)/ matched PF p_{T}");
  hMC_NoTrig_noCut_pfrefOverpfpt_matchAndUn->Draw();
  Int_t MC_NoTrig_noCut_pfrefOverpfpt_matchAndUn=hMC_NoTrig_noCut_pfrefOverpfpt_matchAndUn->GetEntries();
  cout<<"hMC_NoTrig_noCut_pfrefOverpfpt_matchAndUn: "<<hMC_NoTrig_noCut_pfrefOverpfpt_matchAndUn->GetEntries()<<endl;;
  
  hMC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_rej->SetMarkerColor(kYellow+2);
  hMC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_rej->SetMarkerStyle(20);
  hMC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_rej->Draw("same");
  Int_t MC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_rej=hMC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_rej->GetEntries();
  cout<<"hMC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_rej: "<<hMC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_rej->GetEntries()<<endl;;
    
  hMC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_keep->SetMarkerColor(kCyan+2);
  hMC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_keep->SetMarkerStyle(20);
  hMC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_keep->Draw("same");
  Int_t MC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_keep=hMC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_keep->GetEntries();
  cout<<"hMC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_keep: "<<hMC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_keep->GetEntries()<<endl;;
        
      TLegend * LpfrefOverpfpt_matchAndUn_NoTrig_full = myLegend(0.2,0.6,0.4,0.8);
      LpfrefOverpfpt_matchAndUn_NoTrig_full->SetTextSize(0.03);
      LpfrefOverpfpt_matchAndUn_NoTrig_full->AddEntry(hMC_NoTrig_noCut_pfrefOverpfpt_matchAndUn,Form("Matched and Unmatched MC all NoTrig jets: %d entries",MC_NoTrig_noCut_pfrefOverpfpt_matchAndUn),"pl");
      LpfrefOverpfpt_matchAndUn_NoTrig_full->AddEntry(hMC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_keep,Form("Matched and Unmatched MC keep NoTrig CutA: %d entries",MC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_keep),"pl");
      LpfrefOverpfpt_matchAndUn_NoTrig_full->AddEntry(hMC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_rej,Form("Matched and Unmatched MC reject NoTrig CutA: %d entries",MC_NoTrig_CutA_pfrefOverpfpt_matchAndUn_rej),"pl");
      LpfrefOverpfpt_matchAndUn_NoTrig_full->Draw();
      
  cGenJetMC_matchAndUn_NoTrig->SaveAs(Form("Plots/R%d/hMC_NoTrig_YetkinCuts_CutA_pfrefOverpfpt_matchAndUn_fullrange_subid_R0p%d.pdf",radius,radius),"RECREATE");


  TCanvas * cGenJetMC_matchAndUn_Jet55 = new TCanvas("cGenJetMC_matchAndUn_Jet55","",800,600);
  cGenJetMC_matchAndUn_Jet55->SetLogy();

  hMC_Jet55_noCut_pfrefOverpfpt_matchAndUn->SetMarkerColor(kBlack);
  hMC_Jet55_noCut_pfrefOverpfpt_matchAndUn->SetMarkerStyle(25);
  hMC_Jet55_noCut_pfrefOverpfpt_matchAndUn->SetXTitle("GenJet p_{T} (subid selected)/ matched PF p_{T}");
  hMC_Jet55_noCut_pfrefOverpfpt_matchAndUn->Draw();
  Int_t MC_Jet55_noCut_pfrefOverpfpt_matchAndUn=hMC_Jet55_noCut_pfrefOverpfpt_matchAndUn->GetEntries();
  cout<<"hMC_Jet55_noCut_pfrefOverpfpt_matchAndUn: "<<hMC_Jet55_noCut_pfrefOverpfpt_matchAndUn->GetEntries()<<endl;;
  
  hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_rej->SetMarkerColor(kRed+2);
  hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_rej->SetMarkerStyle(20);
  hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_rej->Draw("same");
  Int_t MC_Jet55_CutA_pfrefOverpfpt_matchAndUn_rej=hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_rej->GetEntries();
  cout<<"hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_rej: "<<hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_rej->GetEntries()<<endl;;
    
  hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_keep->SetMarkerColor(kGreen+2);
  hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_keep->SetMarkerStyle(20);
  hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_keep->Draw("same");
  Int_t MC_Jet55_CutA_pfrefOverpfpt_matchAndUn_keep=hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_keep->GetEntries();
  cout<<"hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_keep: "<<hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_keep->GetEntries()<<endl;;
        
      TLegend * LpfrefOverpfpt_matchAndUn_Jet55_full = myLegend(0.2,0.6,0.4,0.8);
      LpfrefOverpfpt_matchAndUn_Jet55_full->SetTextSize(0.03);
      LpfrefOverpfpt_matchAndUn_Jet55_full->AddEntry(hMC_Jet55_noCut_pfrefOverpfpt_matchAndUn,Form("Matched and Unmatched MC all Jet55 jets: %d entries",MC_Jet55_noCut_pfrefOverpfpt_matchAndUn),"pl");
      LpfrefOverpfpt_matchAndUn_Jet55_full->AddEntry(hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_keep,Form("Matched and Unmatched MC keep Jet55 CutA: %d entries",MC_Jet55_CutA_pfrefOverpfpt_matchAndUn_keep),"pl");
      LpfrefOverpfpt_matchAndUn_Jet55_full->AddEntry(hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_rej,Form("Matched and Unmatched MC reject Jet55 CutA: %d entries",MC_Jet55_CutA_pfrefOverpfpt_matchAndUn_rej),"pl");
      LpfrefOverpfpt_matchAndUn_Jet55_full->Draw();
      
  cGenJetMC_matchAndUn_Jet55->SaveAs(Form("Plots/R%d/hMC_Jet55_YetkinCuts_CutA_pfrefOverpfpt_matchAndUn_fullrange_subid_R0p%d.pdf",radius,radius),"RECREATE");

  TCanvas * cGenJetMC_matchAndUn_Jet55_pfrefptgt0_Jet55 = new TCanvas("cGenJetMC_matchAndUn_Jet55_pfrefptgt0_Jet55","",800,600);
  cGenJetMC_matchAndUn_Jet55_pfrefptgt0_Jet55->SetLogy();
  
  hMC_Jet55_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->SetMarkerColor(kBlack);
  hMC_Jet55_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->SetMarkerStyle(25);
  hMC_Jet55_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->SetXTitle("GenJet p_{T} (subid selected)/ matched PF p_{T}");
  hMC_Jet55_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->Draw();
  Int_t MC_Jet55_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0=hMC_Jet55_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->GetEntries();
  cout<<"hMC_Jet55_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0: "<<hMC_Jet55_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->GetEntries()<<endl;;

  hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->SetMarkerColor(kRed+2);
  hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->SetMarkerStyle(20);
  hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->Draw("same");
  Int_t MC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej=hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->GetEntries();
  cout<<"hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej: "<<hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->GetEntries()<<endl;;

  hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->SetMarkerColor(kGreen+2);
  hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->SetMarkerStyle(20);
  hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->Draw("same");
  Int_t MC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep=hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->GetEntries();
  cout<<"hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep: "<<hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->GetEntries()<<endl;;
  
      TLegend * LpfrefOverpfpt_matchAndUn_Jet55 = myLegend(0.2,0.7,0.4,0.9);
      LpfrefOverpfpt_matchAndUn_Jet55->SetTextSize(0.03);
      LpfrefOverpfpt_matchAndUn_Jet55->AddEntry(hMC_Jet55_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0,Form("Matched and Unmatched MC all Jet55 jets: %d entries",MC_Jet55_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0),"p");
      LpfrefOverpfpt_matchAndUn_Jet55->AddEntry(hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep,Form("Matched and Unmatched MC keep Jet55 CutA: %d entries",MC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep),"p");
      LpfrefOverpfpt_matchAndUn_Jet55->AddEntry(hMC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej,Form("Matched and Unmatched MC reject Jet55 CutA: %d entries",MC_Jet55_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej),"p");
      LpfrefOverpfpt_matchAndUn_Jet55->Draw();
      
  cGenJetMC_matchAndUn_Jet55_pfrefptgt0_Jet55->SaveAs(Form("Plots/R%d/hMC_Jet55_YetkinCuts_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_subid_R0p%d.pdf",radius,radius),"RECREATE");

  TCanvas * cGenJetMC_matchAndUn_Jet65 = new TCanvas("cGenJetMC_matchAndUn_Jet65","",800,600);
  cGenJetMC_matchAndUn_Jet65->SetLogy();

  hMC_Jet65_noCut_pfrefOverpfpt_matchAndUn->SetMarkerColor(kBlack);
  hMC_Jet65_noCut_pfrefOverpfpt_matchAndUn->SetMarkerStyle(25);
  hMC_Jet65_noCut_pfrefOverpfpt_matchAndUn->SetXTitle("GenJet p_{T} (subid selected)/ matched PF p_{T}");
  hMC_Jet65_noCut_pfrefOverpfpt_matchAndUn->Draw();
  Int_t MC_Jet65_noCut_pfrefOverpfpt_matchAndUn=hMC_Jet65_noCut_pfrefOverpfpt_matchAndUn->GetEntries();
  cout<<"hMC_Jet65_noCut_pfrefOverpfpt_matchAndUn: "<<hMC_Jet65_noCut_pfrefOverpfpt_matchAndUn->GetEntries()<<endl;;
  
  hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_rej->SetMarkerColor(kOrange);
  hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_rej->SetMarkerStyle(20);
  hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_rej->Draw("same");
  Int_t MC_Jet65_CutA_pfrefOverpfpt_matchAndUn_rej=hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_rej->GetEntries();
  cout<<"hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_rej: "<<hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_rej->GetEntries()<<endl;;
    
  hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_keep->SetMarkerColor(kBlue);
  hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_keep->SetMarkerStyle(20);
  hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_keep->Draw("same");
  Int_t MC_Jet65_CutA_pfrefOverpfpt_matchAndUn_keep=hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_keep->GetEntries();
  cout<<"hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_keep: "<<hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_keep->GetEntries()<<endl;;
        
      TLegend * LpfrefOverpfpt_matchAndUn_Jet65_full = myLegend(0.2,0.6,0.4,0.8);
      LpfrefOverpfpt_matchAndUn_Jet65_full->SetTextSize(0.03);
      LpfrefOverpfpt_matchAndUn_Jet65_full->AddEntry(hMC_Jet65_noCut_pfrefOverpfpt_matchAndUn,Form("Matched and Unmatched MC all Jet65 jets: %d entries",MC_Jet65_noCut_pfrefOverpfpt_matchAndUn),"pl");
      LpfrefOverpfpt_matchAndUn_Jet65_full->AddEntry(hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_keep,Form("Matched and Unmatched MC keep Jet65 CutA: %d entries",MC_Jet65_CutA_pfrefOverpfpt_matchAndUn_keep),"pl");
      LpfrefOverpfpt_matchAndUn_Jet65_full->AddEntry(hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_rej,Form("Matched and Unmatched MC reject Jet65 CutA: %d entries",MC_Jet65_CutA_pfrefOverpfpt_matchAndUn_rej),"pl");
      LpfrefOverpfpt_matchAndUn_Jet65_full->Draw();
      
  cGenJetMC_matchAndUn_Jet65->SaveAs(Form("Plots/R%d/hMC_Jet65_YetkinCuts_CutA_pfrefOverpfpt_matchAndUn_fullrange_subid_R0p%d.pdf",radius,radius),"RECREATE");

  TCanvas * cGenJetMC_matchAndUn_Jet65_pfrefptgt0_Jet65 = new TCanvas("cGenJetMC_matchAndUn_Jet65_pfrefptgt0_Jet65","",800,600);
  cGenJetMC_matchAndUn_Jet65_pfrefptgt0_Jet65->SetLogy();

  hMC_Jet65_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->SetMarkerColor(kBlack);
  hMC_Jet65_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->SetMarkerStyle(25);
  hMC_Jet65_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->SetXTitle("GenJet p_{T} (subid selected)/ matched PF p_{T}");
  hMC_Jet65_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->Draw();
  Int_t MC_Jet65_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0=hMC_Jet65_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->GetEntries();
  cout<<"hMC_Jet65_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0: "<<hMC_Jet65_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->GetEntries()<<endl;;

  hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->SetMarkerColor(kOrange);
  hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->SetMarkerStyle(20);
  hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->Draw("same");
  Int_t MC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej=hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->GetEntries();
  cout<<"hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej: "<<hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->GetEntries()<<endl;;

  hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->SetMarkerColor(kBlue);
  hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->SetMarkerStyle(20);
  hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->Draw("same");
  Int_t MC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep=hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->GetEntries();
  cout<<"hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep: "<<hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->GetEntries()<<endl;;
  
      TLegend * LpfrefOverpfpt_matchAndUn_Jet65 = myLegend(0.2,0.7,0.4,0.9);
      LpfrefOverpfpt_matchAndUn_Jet65->SetTextSize(0.03);
      LpfrefOverpfpt_matchAndUn_Jet65->AddEntry(hMC_Jet65_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0,Form("Matched and Unmatched MC all Jet65 jets: %d entries",MC_Jet65_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0),"p");
      LpfrefOverpfpt_matchAndUn_Jet65->AddEntry(hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep,Form("Matched and Unmatched MC keep Jet65 CutA: %d entries",MC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep),"p");
      LpfrefOverpfpt_matchAndUn_Jet65->AddEntry(hMC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej,Form("Matched and Unmatched MC reject Jet65 CutA: %d entries",MC_Jet65_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej),"p");
      LpfrefOverpfpt_matchAndUn_Jet65->Draw();
      
  cGenJetMC_matchAndUn_Jet65_pfrefptgt0_Jet65->SaveAs(Form("Plots/R%d/hMC_Jet65_YetkinCuts_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_subid_R0p%d.pdf",radius,radius),"RECREATE");

  TCanvas * cGenJetMC_matchAndUn_Jet80 = new TCanvas("cGenJetMC_matchAndUn_Jet80","",800,600);
  cGenJetMC_matchAndUn_Jet80->SetLogy();

  hMC_Jet80_noCut_pfrefOverpfpt_matchAndUn->SetMarkerColor(kBlack);
  hMC_Jet80_noCut_pfrefOverpfpt_matchAndUn->SetMarkerStyle(25);
  hMC_Jet80_noCut_pfrefOverpfpt_matchAndUn->SetXTitle("GenJet p_{T} (subid selected)/ matched PF p_{T}");
  hMC_Jet80_noCut_pfrefOverpfpt_matchAndUn->Draw();
  Int_t MC_Jet80_noCut_pfrefOverpfpt_matchAndUn=hMC_Jet80_noCut_pfrefOverpfpt_matchAndUn->GetEntries();
  cout<<"hMC_Jet80_noCut_pfrefOverpfpt_matchAndUn: "<<hMC_Jet80_noCut_pfrefOverpfpt_matchAndUn->GetEntries()<<endl;;
  
  hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_rej->SetMarkerColor(kMagenta+3);
  hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_rej->SetMarkerStyle(20);
  hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_rej->Draw("same");
  Int_t MC_Jet80_CutA_pfrefOverpfpt_matchAndUn_rej=hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_rej->GetEntries();
  cout<<"hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_rej: "<<hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_rej->GetEntries()<<endl;;
    
  hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_keep->SetMarkerColor(kRed);
  hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_keep->SetMarkerStyle(20);
  hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_keep->Draw("same");
  Int_t MC_Jet80_CutA_pfrefOverpfpt_matchAndUn_keep=hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_keep->GetEntries();
  cout<<"hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_keep: "<<hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_keep->GetEntries()<<endl;;
        
      TLegend * LpfrefOverpfpt_matchAndUn_Jet80_full = myLegend(0.2,0.6,0.4,0.8);
      LpfrefOverpfpt_matchAndUn_Jet80_full->SetTextSize(0.03);
      LpfrefOverpfpt_matchAndUn_Jet80_full->AddEntry(hMC_Jet80_noCut_pfrefOverpfpt_matchAndUn,Form("Matched and Unmatched MC all Jet80 jets: %d entries",MC_Jet80_noCut_pfrefOverpfpt_matchAndUn),"pl");
      LpfrefOverpfpt_matchAndUn_Jet80_full->AddEntry(hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_keep,Form("Matched and Unmatched MC keep Jet80 CutA: %d entries",MC_Jet80_CutA_pfrefOverpfpt_matchAndUn_keep),"pl");
      LpfrefOverpfpt_matchAndUn_Jet80_full->AddEntry(hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_rej,Form("Matched and Unmatched MC reject Jet80 CutA: %d entries",MC_Jet80_CutA_pfrefOverpfpt_matchAndUn_rej),"pl");
      LpfrefOverpfpt_matchAndUn_Jet80_full->Draw();
      
  cGenJetMC_matchAndUn_Jet80->SaveAs(Form("Plots/R%d/hMC_Jet80_YetkinCuts_CutA_pfrefOverpfpt_matchAndUn_fullrange_subid_R0p%d.pdf",radius,radius),"RECREATE");

  TCanvas * cGenJetMC_matchAndUn_Jet80_pfrefptgt0_Jet80 = new TCanvas("cGenJetMC_matchAndUn_Jet80_pfrefptgt0_Jet80","",800,600);
  cGenJetMC_matchAndUn_Jet80_pfrefptgt0_Jet80->SetLogy();

  hMC_Jet80_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->SetMarkerColor(kBlack);
  hMC_Jet80_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->SetMarkerStyle(25);
  hMC_Jet80_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->SetXTitle("GenJet p_{T} (subid selected)/ matched PF p_{T}");
  hMC_Jet80_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->Draw();
  Int_t MC_Jet80_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0=hMC_Jet80_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->GetEntries();
  cout<<"hMC_Jet80_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0: "<<hMC_Jet80_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0->GetEntries()<<endl;;

  hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->SetMarkerColor(kMagenta+3);
  hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->SetMarkerStyle(20);
  hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->Draw("same");
  Int_t MC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej=hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->GetEntries();
  cout<<"hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej: "<<hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej->GetEntries()<<endl;;

  hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->SetMarkerColor(kRed);
  hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->SetMarkerStyle(20);
  hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->Draw("same");
  Int_t MC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep=hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->GetEntries();
  cout<<"hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep: "<<hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep->GetEntries()<<endl;;
  
      TLegend * LpfrefOverpfpt_matchAndUn_Jet80 = myLegend(0.2,0.7,0.4,0.9);
      LpfrefOverpfpt_matchAndUn_Jet80->SetTextSize(0.03);
      LpfrefOverpfpt_matchAndUn_Jet80->AddEntry(hMC_Jet80_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0,Form("Matched and Unmatched MC all Jet80 jets: %d entries",MC_Jet80_noCut_pfrefOverpfpt_matchAndUn_pfrefptgt0),"p");
      LpfrefOverpfpt_matchAndUn_Jet80->AddEntry(hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep,Form("Matched and Unmatched MC keep Jet80 CutA: %d entries",MC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_keep),"p");
      LpfrefOverpfpt_matchAndUn_Jet80->AddEntry(hMC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej,Form("Matched and Unmatched MC reject Jet80 CutA: %d entries",MC_Jet80_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_rej),"p");
      LpfrefOverpfpt_matchAndUn_Jet80->Draw();
      
  cGenJetMC_matchAndUn_Jet80_pfrefptgt0_Jet80->SaveAs(Form("Plots/R%d/hMC_Jet80_YetkinCuts_CutA_pfrefOverpfpt_matchAndUn_pfrefptgt0_subid_R0p%d.pdf",radius,radius),"RECREATE");


}
