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
#include "/net/hisrv0001/home/belt/wrk/JetRAA/RaghavCode/Headers/plot.h"

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

// static const int nbins_pt = 30;
// static const double boundaries_pt[nbins_pt+1] = {  3, 4, 5, 7, 9, 12, 15, 18, 21, 24, 28,  32, 37, 43, 49, 56,  64, 74, 84, 97, 114,  133, 153, 174, 196,  220, 245, 300, 330, 362, 395};

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

void Draw_TrkOverCutA(Int_t radius=3)
{
  gStyle->SetOptStat(0);
  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();
    TFile * fTrk, * fCutA;
    TH1F *hRatioPbPb[nbins_cent], *hTrkPbPb[nbins_cent], *hCutAPbPb[nbins_cent];
    TH1F *hRatioPbPb_MCrec[nbins_cent], *hTrkPbPb_MCrec[nbins_cent], *hCutAPbPb_MCrec[nbins_cent];
    TH1F *hRatioPbPb_MCgen[nbins_cent], *hTrkPbPb_MCgen[nbins_cent], *hCutAPbPb_MCgen[nbins_cent];
    TH1F *hRatioPbPb_jet55[nbins_cent], *hTrkPbPb_jet55[nbins_cent], *hCutAPbPb_jet55[nbins_cent];
    TH1F *hRatioPbPb_MCrec_jet55[nbins_cent], *hTrkPbPb_MCrec_jet55[nbins_cent], *hCutAPbPb_MCrec_jet55[nbins_cent];
    TH1F *hRatioPbPb_MCgen_jet55[nbins_cent], *hTrkPbPb_MCgen_jet55[nbins_cent], *hCutAPbPb_MCgen_jet55[nbins_cent];   
    TH1F *hRatioPbPb_jet65[nbins_cent], *hTrkPbPb_jet65[nbins_cent], *hCutAPbPb_jet65[nbins_cent];
    TH1F *hRatioPbPb_MCrec_jet65[nbins_cent], *hTrkPbPb_MCrec_jet65[nbins_cent], *hCutAPbPb_MCrec_jet65[nbins_cent];
    TH1F *hRatioPbPb_MCgen_jet65[nbins_cent], *hTrkPbPb_MCgen_jet65[nbins_cent], *hCutAPbPb_MCgen_jet65[nbins_cent]; 
    TH1F *hRatioPbPb_jet80[nbins_cent], *hTrkPbPb_jet80[nbins_cent], *hCutAPbPb_jet80[nbins_cent];
    TH1F *hRatioPbPb_MCrec_jet80[nbins_cent], *hTrkPbPb_MCrec_jet80[nbins_cent], *hCutAPbPb_MCrec_jet80[nbins_cent];
    TH1F *hRatioPbPb_MCgen_jet80[nbins_cent], *hTrkPbPb_MCgen_jet80[nbins_cent], *hCutAPbPb_MCgen_jet80[nbins_cent];          
    TH1F *hInvRatioPbPb[nbins_cent];
   TH2F * hBlankRatio = new TH2F("hBlankRatio","",400,30,501,400,0,2);
      TLine *lineRatio = new TLine(30,1,501,1);
    lineRatio->SetLineStyle(2);
    lineRatio->SetLineWidth(2);
       
  fTrk=TFile::Open(Form("Pawan_TTree_PbPb_Data_MC_subid0_spectra_JetID_CutA_finebins_20_eta_20_R0p%d_trkMaxJtptGt2percent.root",radius));
  fCutA=TFile::Open(Form("Pawan_TTree_PbPb_Data_MC_subid0_spectra_JetID_CutA_finebins_20_eta_20_R0p%d_test.root",radius));

  for(int i=0;i<nbins_cent;i++){
    hTrkPbPb[i] = (TH1F*)fTrk->Get(Form("hpbpb_HLTComb_R%d_20_eta_20_cent%d",radius,i));
     hTrkPbPb[i]->Print("base");
    hCutAPbPb[i] = (TH1F*)fCutA->Get(Form("hpbpb_HLTComb_R%d_20_eta_20_cent%d",radius,i));
    hCutAPbPb[i]->Print("base");
    hRatioPbPb[i]=(TH1F*)hTrkPbPb[i]->Clone(Form("hRatioPbPb_R%d_cent%d",radius,i));
      hRatioPbPb[i]->Rebin(10.);
      hRatioPbPb[i]->Scale(1./10.);
      hCutAPbPb[i]->Rebin(10.);
      hCutAPbPb[i]->Scale(1./10.);
    hRatioPbPb[i]->Divide(hCutAPbPb[i]);
    hRatioPbPb[i]->SetMarkerStyle(20);
    hRatioPbPb[i]->SetMarkerColor(kBlue);
    hTrkPbPb_MCrec[i] = (TH1F*)fTrk->Get(Form("hpbpb_JetComb_reco_R%d_20_eta_20_cent%d",radius,i));
    hTrkPbPb_MCrec[i]->Print("base");
    hCutAPbPb_MCrec[i] = (TH1F*)fCutA->Get(Form("hpbpb_JetComb_reco_R%d_20_eta_20_cent%d",radius,i));
    hCutAPbPb_MCrec[i]->Print("base");
    hRatioPbPb_MCrec[i]=(TH1F*)hTrkPbPb_MCrec[i]->Clone(Form("hRatioPbPb_MCreco_R%d_cent%d",radius,i));
      hRatioPbPb_MCrec[i]->Rebin(10.);
      hRatioPbPb_MCrec[i]->Scale(1./10.);
      hCutAPbPb_MCrec[i]->Rebin(10.);
      hCutAPbPb_MCrec[i]->Scale(1./10.);    
    hRatioPbPb_MCrec[i]->Divide(hCutAPbPb_MCrec[i]);
    hRatioPbPb_MCrec[i]->SetMarkerStyle(21);
    hRatioPbPb_MCrec[i]->SetMarkerColor(kRed);
    hTrkPbPb_MCgen[i] = (TH1F*)fTrk->Get(Form("hpbpb_JetComb_gen_R%d_20_eta_20_cent%d",radius,i));
    hTrkPbPb_MCgen[i]->Print("base");
    hCutAPbPb_MCgen[i] = (TH1F*)fCutA->Get(Form("hpbpb_JetComb_gen_R%d_20_eta_20_cent%d",radius,i));
     hCutAPbPb_MCgen[i]->Print("base");
    hRatioPbPb_MCgen[i]=(TH1F*)hTrkPbPb_MCgen[i]->Clone(Form("hRatioPbPb_MCgen_R%d_cent%d",radius,i));
      hRatioPbPb_MCgen[i]->Rebin(10.);
      hRatioPbPb_MCgen[i]->Scale(1./10.);
      hCutAPbPb_MCgen[i]->Rebin(10.);
      hCutAPbPb_MCgen[i]->Scale(1./10.);        
    hRatioPbPb_MCgen[i]->Divide(hCutAPbPb_MCgen[i]);
    hRatioPbPb_MCgen[i]->SetMarkerStyle(22);
    hRatioPbPb_MCgen[i]->SetMarkerColor(kGreen+1);    
    hTrkPbPb_jet55[i] = (TH1F*)fTrk->Get(Form("hpbpb_HLT55_R%d_20_eta_20_cent%d",radius,i));
     hTrkPbPb_jet55[i]->Print("base");
    hCutAPbPb_jet55[i] = (TH1F*)fCutA->Get(Form("hpbpb_HLT55_R%d_20_eta_20_cent%d",radius,i));
    hCutAPbPb_jet55[i]->Print("base");
    hRatioPbPb_jet55[i]=(TH1F*)hTrkPbPb_jet55[i]->Clone(Form("hRatioPbPb_R%d_cent%d",radius,i));
      hRatioPbPb_jet55[i]->Rebin(10.);
      hRatioPbPb_jet55[i]->Scale(1./10.);
      hCutAPbPb_jet55[i]->Rebin(10.);
      hCutAPbPb_jet55[i]->Scale(1./10.);      
    hRatioPbPb_jet55[i]->Divide(hCutAPbPb_jet55[i]);
    hRatioPbPb_jet55[i]->SetMarkerStyle(20);
    hRatioPbPb_jet55[i]->SetMarkerColor(kBlue);
    hTrkPbPb_MCrec_jet55[i] = (TH1F*)fTrk->Get(Form("hpbpb_Jet55_reco_R%d_20_eta_20_cent%d",radius,i));
    hTrkPbPb_MCrec_jet55[i]->Print("base");
    hCutAPbPb_MCrec_jet55[i] = (TH1F*)fCutA->Get(Form("hpbpb_Jet55_reco_R%d_20_eta_20_cent%d",radius,i));
    hCutAPbPb_MCrec_jet55[i]->Print("base");
    hRatioPbPb_MCrec_jet55[i]=(TH1F*)hTrkPbPb_MCrec_jet55[i]->Clone(Form("hRatioPbPb_MCreco_R%d_cent%d",radius,i));
      hRatioPbPb_MCrec_jet55[i]->Rebin(10.);
      hRatioPbPb_MCrec_jet55[i]->Scale(1./10.);
      hCutAPbPb_MCrec_jet55[i]->Rebin(10.);
      hCutAPbPb_MCrec_jet55[i]->Scale(1./10.);        
    hRatioPbPb_MCrec_jet55[i]->Divide(hCutAPbPb_MCrec_jet55[i]);
    hRatioPbPb_MCrec_jet55[i]->SetMarkerStyle(21);
    hRatioPbPb_MCrec_jet55[i]->SetMarkerColor(kRed);
    hTrkPbPb_MCgen_jet55[i] = (TH1F*)fTrk->Get(Form("hpbpb_Jet55_gen_R%d_20_eta_20_cent%d",radius,i));
    hTrkPbPb_MCgen_jet55[i]->Print("base");
    hCutAPbPb_MCgen_jet55[i] = (TH1F*)fCutA->Get(Form("hpbpb_Jet55_gen_R%d_20_eta_20_cent%d",radius,i));
     hCutAPbPb_MCgen_jet55[i]->Print("base");
    hRatioPbPb_MCgen_jet55[i]=(TH1F*)hTrkPbPb_MCgen_jet55[i]->Clone(Form("hRatioPbPb_MCgen_R%d_cent%d",radius,i));
      hRatioPbPb_MCgen_jet55[i]->Rebin(10.);
      hRatioPbPb_MCgen_jet55[i]->Scale(1./10.);
      hCutAPbPb_MCgen_jet55[i]->Rebin(10.);
      hCutAPbPb_MCgen_jet55[i]->Scale(1./10.);                
    hRatioPbPb_MCgen_jet55[i]->Divide(hCutAPbPb_MCgen_jet55[i]);
    hRatioPbPb_MCgen_jet55[i]->SetMarkerStyle(22);
    hRatioPbPb_MCgen_jet55[i]->SetMarkerColor(kGreen+1);    
    hTrkPbPb_jet65[i] = (TH1F*)fTrk->Get(Form("hpbpb_HLT65_R%d_20_eta_20_cent%d",radius,i));
     hTrkPbPb_jet65[i]->Print("base");
    hCutAPbPb_jet65[i] = (TH1F*)fCutA->Get(Form("hpbpb_HLT65_R%d_20_eta_20_cent%d",radius,i));
    hCutAPbPb_jet65[i]->Print("base");
    hRatioPbPb_jet65[i]=(TH1F*)hTrkPbPb_jet65[i]->Clone(Form("hRatioPbPb_R%d_cent%d",radius,i));
      hRatioPbPb_jet65[i]->Rebin(10.);
      hRatioPbPb_jet65[i]->Scale(1./10.);
      hCutAPbPb_jet65[i]->Rebin(10.);
      hCutAPbPb_jet65[i]->Scale(1./10.);    
    hRatioPbPb_jet65[i]->Divide(hCutAPbPb_jet65[i]);
    hRatioPbPb_jet65[i]->SetMarkerStyle(20);
    hRatioPbPb_jet65[i]->SetMarkerColor(kBlue);
    hTrkPbPb_MCrec_jet65[i] = (TH1F*)fTrk->Get(Form("hpbpb_Jet65_reco_R%d_20_eta_20_cent%d",radius,i));
    hTrkPbPb_MCrec_jet65[i]->Print("base");
    hCutAPbPb_MCrec_jet65[i] = (TH1F*)fCutA->Get(Form("hpbpb_Jet65_reco_R%d_20_eta_20_cent%d",radius,i));
    hCutAPbPb_MCrec_jet65[i]->Print("base");
    hRatioPbPb_MCrec_jet65[i]=(TH1F*)hTrkPbPb_MCrec_jet65[i]->Clone(Form("hRatioPbPb_MCreco_R%d_cent%d",radius,i));
      hRatioPbPb_MCrec_jet65[i]->Rebin(10.);
      hRatioPbPb_MCrec_jet65[i]->Scale(1./10.);
      hCutAPbPb_MCrec_jet65[i]->Rebin(10.);
      hCutAPbPb_MCrec_jet65[i]->Scale(1./10.);    
    hRatioPbPb_MCrec_jet65[i]->Divide(hCutAPbPb_MCrec_jet65[i]);
    hRatioPbPb_MCrec_jet65[i]->SetMarkerStyle(21);
    hRatioPbPb_MCrec_jet65[i]->SetMarkerColor(kRed);
    hTrkPbPb_MCgen_jet65[i] = (TH1F*)fTrk->Get(Form("hpbpb_Jet65_gen_R%d_20_eta_20_cent%d",radius,i));
    hTrkPbPb_MCgen_jet65[i]->Print("base");
    hCutAPbPb_MCgen_jet65[i] = (TH1F*)fCutA->Get(Form("hpbpb_Jet65_gen_R%d_20_eta_20_cent%d",radius,i));
     hCutAPbPb_MCgen_jet65[i]->Print("base");
    hRatioPbPb_MCgen_jet65[i]=(TH1F*)hTrkPbPb_MCgen_jet65[i]->Clone(Form("hRatioPbPb_MCgen_R%d_cent%d",radius,i));
      hRatioPbPb_MCgen_jet65[i]->Rebin(10.);
      hRatioPbPb_MCgen_jet65[i]->Scale(1./10.);
      hCutAPbPb_MCgen_jet65[i]->Rebin(10.);
      hCutAPbPb_MCgen_jet65[i]->Scale(1./10.);                    
    hRatioPbPb_MCgen_jet65[i]->Divide(hCutAPbPb_MCgen_jet65[i]);
    hRatioPbPb_MCgen_jet65[i]->SetMarkerStyle(22);
    hRatioPbPb_MCgen_jet65[i]->SetMarkerColor(kGreen+1);    
    hTrkPbPb_jet80[i] = (TH1F*)fTrk->Get(Form("hpbpb_HLT80_R%d_20_eta_20_cent%d",radius,i));
     hTrkPbPb_jet80[i]->Print("base");
    hCutAPbPb_jet80[i] = (TH1F*)fCutA->Get(Form("hpbpb_HLT80_R%d_20_eta_20_cent%d",radius,i));
    hCutAPbPb_jet80[i]->Print("base");
    hRatioPbPb_jet80[i]=(TH1F*)hTrkPbPb_jet80[i]->Clone(Form("hRatioPbPb_R%d_cent%d",radius,i));
      hRatioPbPb_jet80[i]->Rebin(10.);
      hRatioPbPb_jet80[i]->Scale(1./10.);
      hCutAPbPb_jet80[i]->Rebin(10.);
      hCutAPbPb_jet80[i]->Scale(1./10.);    
    hRatioPbPb_jet80[i]->Divide(hCutAPbPb_jet80[i]);
    hRatioPbPb_jet80[i]->SetMarkerStyle(20);
    hRatioPbPb_jet80[i]->SetMarkerColor(kBlue);
    hTrkPbPb_MCrec_jet80[i] = (TH1F*)fTrk->Get(Form("hpbpb_Jet80_reco_R%d_20_eta_20_cent%d",radius,i));
    hTrkPbPb_MCrec_jet80[i]->Print("base");
    hCutAPbPb_MCrec_jet80[i] = (TH1F*)fCutA->Get(Form("hpbpb_Jet80_reco_R%d_20_eta_20_cent%d",radius,i));
    hCutAPbPb_MCrec_jet80[i]->Print("base");
    hRatioPbPb_MCrec_jet80[i]=(TH1F*)hTrkPbPb_MCrec_jet80[i]->Clone(Form("hRatioPbPb_MCreco_R%d_cent%d",radius,i));
      hRatioPbPb_MCrec_jet80[i]->Rebin(10.);
      hRatioPbPb_MCrec_jet80[i]->Scale(1./10.);
      hCutAPbPb_MCrec_jet80[i]->Rebin(10.);
      hCutAPbPb_MCrec_jet80[i]->Scale(1./10.);      
    hRatioPbPb_MCrec_jet80[i]->Divide(hCutAPbPb_MCrec_jet80[i]);
    hRatioPbPb_MCrec_jet80[i]->SetMarkerStyle(21);
    hRatioPbPb_MCrec_jet80[i]->SetMarkerColor(kRed);
    hTrkPbPb_MCgen_jet80[i] = (TH1F*)fTrk->Get(Form("hpbpb_Jet80_gen_R%d_20_eta_20_cent%d",radius,i));
    hTrkPbPb_MCgen_jet80[i]->Print("base");
    hCutAPbPb_MCgen_jet80[i] = (TH1F*)fCutA->Get(Form("hpbpb_Jet80_gen_R%d_20_eta_20_cent%d",radius,i));
     hCutAPbPb_MCgen_jet80[i]->Print("base");
    hRatioPbPb_MCgen_jet80[i]=(TH1F*)hTrkPbPb_MCgen_jet80[i]->Clone(Form("hRatioPbPb_MCgen_R%d_cent%d",radius,i));
      hRatioPbPb_MCgen_jet80[i]->Rebin(10.);
      hRatioPbPb_MCgen_jet80[i]->Scale(1./10.);
      hCutAPbPb_MCgen_jet80[i]->Rebin(10.);
      hCutAPbPb_MCgen_jet80[i]->Scale(1./10.);                    
    hRatioPbPb_MCgen_jet80[i]->Divide(hCutAPbPb_MCgen_jet80[i]);
    hRatioPbPb_MCgen_jet80[i]->SetMarkerStyle(22);
    hRatioPbPb_MCgen_jet80[i]->SetMarkerColor(kGreen+1);                
    
  }
   
    TCanvas *cRatio = new TCanvas("cRatio","Ratio",1200,800);
    makeMultiPanelCanvasWithGap(cRatio,3,2,0.01,0.01,0.16,0.2,0.04,0.04);
    makeHistTitle(hBlankRatio,"",Form("akPu%dPF Jet p_{T} (GeV/c) PbPb data",radius),"(TrMax/Jtpt>0.02 & CutA)/CutA");    
    
    for(int i = 0;i<nbins_cent;i++){
      cRatio->cd(nbins_cent-i);
      hBlankRatio->Draw();
      hRatioPbPb[i]->Draw("same");
      lineRatio->Draw("same");
      drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.6,0.8,20);
   }
  cRatio->SaveAs(Form("RatioPlots/PbPb_HLTComb_OverTrkCutAOverCutA_R0p%d.pdf",radius),"RECREATE"); 

    TCanvas *cRatio_MCrec = new TCanvas("cRatio_MCrec","Ratio MC reco",1200,800);
    makeMultiPanelCanvasWithGap(cRatio_MCrec,3,2,0.01,0.01,0.16,0.2,0.04,0.04);
    makeHistTitle(hBlankRatio,"",Form("akPu%dPF Jet p_{T} (GeV/c) MC reco",radius),"(TrMax/Jtpt>0.02 & CutA)/CutA");    
    
    for(int i = 0;i<nbins_cent;i++){
      cRatio_MCrec->cd(nbins_cent-i);
      hBlankRatio->Draw();
      hRatioPbPb_MCrec[i]->Draw("same");
      lineRatio->Draw("same");
      drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.6,0.8,20);
   }
  cRatio_MCrec->SaveAs(Form("RatioPlots/PbPb_HLTComb_MCrec_OverTrkCutAOverCutA_R0p%d.pdf",radius),"RECREATE"); 

    TCanvas *cRatio_MCgen = new TCanvas("cRatio_MCgen","Ratio MC gen",1200,800);
    makeMultiPanelCanvasWithGap(cRatio_MCgen,3,2,0.01,0.01,0.16,0.2,0.04,0.04);
    makeHistTitle(hBlankRatio,"",Form("akPu%dPF Jet p_{T} (GeV/c) MC gen",radius),"(TrMax/Jtpt>0.02 & CutA)/CutA");    
    
    for(int i = 0;i<nbins_cent;i++){
      cRatio_MCgen->cd(nbins_cent-i);
      hBlankRatio->Draw();
      hRatioPbPb_MCgen[i]->Draw("same");
      lineRatio->Draw("same");
      drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.6,0.8,20);
   }
  cRatio_MCgen->SaveAs(Form("RatioPlots/PbPb_HLTComb_MCgen_OverTrkCutAOverCutA_R0p%d.pdf",radius),"RECREATE");  
    TCanvas *cRatio55 = new TCanvas("cRatio55","Ratio",1200,800);
    makeMultiPanelCanvasWithGap(cRatio55,3,2,0.01,0.01,0.16,0.2,0.04,0.04);
    makeHistTitle(hBlankRatio,"",Form("akPu%dPF Jet p_{T} (GeV/c) PbPb data jet55",radius),"(TrMax/Jtpt>0.02 & CutA)/CutA");    
    
    for(int i = 0;i<nbins_cent;i++){
      cRatio55->cd(nbins_cent-i);
      hBlankRatio->Draw();
      hRatioPbPb_jet55[i]->Draw("same");
      lineRatio->Draw("same");
      drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.6,0.8,20);
   }
  cRatio55->SaveAs(Form("RatioPlots/PbPb_Jet55_OverTrkCutAOverCutA_R0p%d.pdf",radius),"RECREATE"); 

    TCanvas *cRatio55_MCrec = new TCanvas("cRatio55_MCrec","Ratio MC reco",1200,800);
    makeMultiPanelCanvasWithGap(cRatio55_MCrec,3,2,0.01,0.01,0.16,0.2,0.04,0.04);
    makeHistTitle(hBlankRatio,"",Form("akPu%dPF Jet p_{T} (GeV/c) MC reco jet55",radius),"(TrMax/Jtpt>0.02 & CutA)/CutA");    
    
    for(int i = 0;i<nbins_cent;i++){
      cRatio55_MCrec->cd(nbins_cent-i);
      hBlankRatio->Draw();
      hRatioPbPb_MCrec_jet55[i]->Draw("same");
      lineRatio->Draw("same");
      drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.6,0.8,20);
   }
  cRatio55_MCrec->SaveAs(Form("RatioPlots/PbPb_Jet55_MCrec_OverTrkCutAOverCutA_R0p%d.pdf",radius),"RECREATE"); 

    TCanvas *cRatio55_MCgen = new TCanvas("cRatio55_MCgen","Ratio MC gen",1200,800);
    makeMultiPanelCanvasWithGap(cRatio55_MCgen,3,2,0.01,0.01,0.16,0.2,0.04,0.04);
    makeHistTitle(hBlankRatio,"",Form("akPu%dPF Jet p_{T} (GeV/c) MC gen jet55",radius),"(TrMax/Jtpt>0.02 & CutA)/CutA");    
    
    for(int i = 0;i<nbins_cent;i++){
      cRatio55_MCgen->cd(nbins_cent-i);
      hBlankRatio->Draw();
      hRatioPbPb_MCgen_jet55[i]->Draw("same");
      lineRatio->Draw("same");
      drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.6,0.8,20);
   }
  cRatio55_MCgen->SaveAs(Form("RatioPlots/PbPb_Jet55_MCgen_OverTrkCutAOverCutA_R0p%d.pdf",radius),"RECREATE");   
    TCanvas *cRatio65 = new TCanvas("cRatio65","Ratio",1200,800);
    makeMultiPanelCanvasWithGap(cRatio65,3,2,0.01,0.01,0.16,0.2,0.04,0.04);
    makeHistTitle(hBlankRatio,"",Form("akPu%dPF Jet p_{T} (GeV/c) PbPb data jet65",radius),"(TrMax/Jtpt>0.02 & CutA)/CutA");    
    
    for(int i = 0;i<nbins_cent;i++){
      cRatio65->cd(nbins_cent-i);
      hBlankRatio->Draw();
      hRatioPbPb_jet65[i]->Draw("same");
      lineRatio->Draw("same");
      drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.6,0.8,20);
   }
  cRatio65->SaveAs(Form("RatioPlots/PbPb_Jet65_OverTrkCutAOverCutA_R0p%d.pdf",radius),"RECREATE"); 

    TCanvas *cRatio65_MCrec = new TCanvas("cRatio65_MCrec","Ratio MC reco",1200,800);
    makeMultiPanelCanvasWithGap(cRatio65_MCrec,3,2,0.01,0.01,0.16,0.2,0.04,0.04);
    makeHistTitle(hBlankRatio,"",Form("akPu%dPF Jet p_{T} (GeV/c) MC reco jet65",radius),"(TrMax/Jtpt>0.02 & CutA)/CutA");    
    
    for(int i = 0;i<nbins_cent;i++){
      cRatio65_MCrec->cd(nbins_cent-i);
      hBlankRatio->Draw();
      hRatioPbPb_MCrec_jet65[i]->Draw("same");
      lineRatio->Draw("same");
      drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.6,0.8,20);
   }
  cRatio65_MCrec->SaveAs(Form("RatioPlots/PbPb_Jet65_MCrec_OverTrkCutAOverCutA_R0p%d.pdf",radius),"RECREATE"); 

    TCanvas *cRatio65_MCgen = new TCanvas("cRatio65_MCgen","Ratio MC gen",1200,800);
    makeMultiPanelCanvasWithGap(cRatio65_MCgen,3,2,0.01,0.01,0.16,0.2,0.04,0.04);
    makeHistTitle(hBlankRatio,"",Form("akPu%dPF Jet p_{T} (GeV/c) MC gen jet65",radius),"(TrMax/Jtpt>0.02 & CutA)/CutA");    
    
    for(int i = 0;i<nbins_cent;i++){
      cRatio65_MCgen->cd(nbins_cent-i);
      hBlankRatio->Draw();
      hRatioPbPb_MCgen_jet65[i]->Draw("same");
      lineRatio->Draw("same");
      drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.6,0.8,20);
   }
  cRatio65_MCgen->SaveAs(Form("RatioPlots/PbPb_Jet65_MCgen_OverTrkCutAOverCutA_R0p%d.pdf",radius),"RECREATE");   
    TCanvas *cRatio80 = new TCanvas("cRatio80","Ratio",1200,800);
    makeMultiPanelCanvasWithGap(cRatio80,3,2,0.01,0.01,0.16,0.2,0.04,0.04);
    makeHistTitle(hBlankRatio,"",Form("akPu%dPF Jet p_{T} (GeV/c) PbPb data jet80",radius),"(TrMax/Jtpt>0.02 & CutA)/CutA");    
    
    for(int i = 0;i<nbins_cent;i++){
      cRatio80->cd(nbins_cent-i);
      hBlankRatio->Draw();
      hRatioPbPb_jet80[i]->Draw("same");
      lineRatio->Draw("same");
      drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.6,0.8,20);
   }
  cRatio80->SaveAs(Form("RatioPlots/PbPb_Jet80_OverTrkCutAOverCutA_R0p%d.pdf",radius),"RECREATE"); 

    TCanvas *cRatio80_MCrec = new TCanvas("cRatio80_MCrec","Ratio MC reco",1200,800);
    makeMultiPanelCanvasWithGap(cRatio80_MCrec,3,2,0.01,0.01,0.16,0.2,0.04,0.04);
    makeHistTitle(hBlankRatio,"",Form("akPu%dPF Jet p_{T} (GeV/c) MC reco jet80",radius),"(TrMax/Jtpt>0.02 & CutA)/CutA");    
    
    for(int i = 0;i<nbins_cent;i++){
      cRatio80_MCrec->cd(nbins_cent-i);
      hBlankRatio->Draw();
      hRatioPbPb_MCrec_jet80[i]->Draw("same");
      lineRatio->Draw("same");
      drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.6,0.8,20);
   }
  cRatio80_MCrec->SaveAs(Form("RatioPlots/PbPb_Jet80_MCrec_OverTrkCutAOverCutA_R0p%d.pdf",radius),"RECREATE"); 

    TCanvas *cRatio80_MCgen = new TCanvas("cRatio80_MCgen","Ratio MC gen",1200,800);
    makeMultiPanelCanvasWithGap(cRatio80_MCgen,3,2,0.01,0.01,0.16,0.2,0.04,0.04);
    makeHistTitle(hBlankRatio,"",Form("akPu%dPF Jet p_{T} (GeV/c) MC gen jet80",radius),"(TrMax/Jtpt>0.02 & CutA)/CutA");    
    
    for(int i = 0;i<nbins_cent;i++){
      cRatio80_MCgen->cd(nbins_cent-i);
      hBlankRatio->Draw();
      hRatioPbPb_MCgen_jet80[i]->Draw("same");
      lineRatio->Draw("same");
      drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.6,0.8,20);
   }
  cRatio80_MCgen->SaveAs(Form("RatioPlots/PbPb_Jet80_MCgen_OverTrkCutAOverCutA_R0p%d.pdf",radius),"RECREATE");          
}