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
    TH1F *hInvRatioPbPb[nbins_cent];
   TH2F * hBlankRatio = new TH2F("hBlankRatio","",400,30,501,400,0,2);
      TLine *lineRatio = new TLine(30,1,501,1);
    lineRatio->SetLineStyle(2);
    lineRatio->SetLineWidth(2);
       
  fTrk=TFile::Open(Form("Pawan_TTree_PbPb_Data_MC_subid0_spectra_JetID_CutA_finebins_20_eta_20_R0p%d_trkMaxJtptGt1percent.root",radius));
  fCutA=TFile::Open(Form("Pawan_TTree_PbPb_Data_MC_subid0_spectra_JetID_CutA_finebins_20_eta_20_R0p%d_test.root",radius));

  for(int i=0;i<nbins_cent;i++){
    hTrkPbPb[i] = (TH1F*)fTrk->Get(Form("hpbpb_HLTComb_R%d_20_eta_20_cent%d",radius,i));
    hCutAPbPb[i] = (TH1F*)fCutA->Get(Form("hpbpb_HLTComb_R%d_20_eta_20_cent%d",radius,i));
    hRatioPbPb[i]=(TH1F*)hCutAPbPb[i]->Clone(Form("hRatioPbPb_R%d_cent%d",radius,i));
    hRatioPbPb[i]->Divide(hTrkPbPb[i]);
    hRatioPbPb[i]->SetMarkerStyle(20);
    hRatioPbPb[i]->SetMarkerColor(kBlue);
  }
   
    TCanvas *cRatio = new TCanvas("cRatio","Ratio",1200,800);
    makeMultiPanelCanvasWithGap(cRatio,3,2,0.01,0.01,0.16,0.2,0.04,0.04);
    makeHistTitle(hBlankRatio,"",Form("akPu%dPF Jet p_{T} (GeV/c) ",radius),"CutA/(TrkMax/JetpT>0.01 & CutA)");    
    
    for(int i = 0;i<nbins_cent;i++){
      cRatio->cd(nbins_cent-i);
      hRatioPbPb[i]->Rebin(5.);
      hRatioPbPb[i]->Scale(1./5.);
      hBlankRatio->Draw();
      hRatioPbPb[i]->Draw("same");
      lineRatio->Draw("same");
      drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.6,0.8,20);
   }
  cRatio->SaveAs(Form("RatioPlots/PbPb_HLTComb_CutAOverTrkCutA_R0p%d.pdf",radius),"RECREATE"); 
}