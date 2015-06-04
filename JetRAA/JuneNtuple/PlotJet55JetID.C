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

static const int nbins_pt = 29;
static const double boundaries_pt[nbins_pt+1] = {  3, 4, 5, 7, 9, 12, 15, 18, 21, 24, 28,  32, 37, 43, 49, 56,  64, 74, 84, 97, 114,  133, 153, 174, 196,  220, 245, 300, 355, 400};


using namespace std;
void PlotJet55JetID(char* etaWidth = (char*)"20_eta_20",
				  Int_t radius = 3,
				  Int_t etaLow = 20,
				  Int_t etaHigh = 20)
{
  
  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();

  // char * etaWidth = (char*)Form("%d_eta_%d",etaLow, etaHigh);
  cout<<"etaWidth = "<<etaWidth<<endl;
  cout<<"Radius = "<<radius<<endl;

  Float_t pfptmin=30;
  
  if(radius==2){
     pfptmin = 30;
  } else if(radius==3){
     pfptmin = 40;
  } else if(radius=4){
     pfptmin = 50;
  }
  TFile fin(Form("%s_TTree_PbPb_Data_MC_subid0_spectra_JetID_CutA_finebins_%s_R0p%d.root",ntuple,etaWidth,radius));
  TH1F * hData_chMaxJtpt_jet55_keep[nbins_cent], * hData_phMaxJtpt_jet55_keep[nbins_cent], * hData_neMaxJtpt_jet55_keep[nbins_cent], * hData_muMaxJtpt_jet55_keep[nbins_cent], * hData_eMaxJtpt_jet55_keep[nbins_cent];
  TH1F * hData_chSumJtpt_jet55_keep[nbins_cent], * hData_phSumJtpt_jet55_keep[nbins_cent], * hData_neSumJtpt_jet55_keep[nbins_cent], * hData_muSumJtpt_jet55_keep[nbins_cent], * hData_eSumJtpt_jet55_keep[nbins_cent];  
  
  TH1F * hMC_chMaxJtpt_jet55_keep[nbins_cent], * hMC_phMaxJtpt_jet55_keep[nbins_cent], * hMC_neMaxJtpt_jet55_keep[nbins_cent], * hMC_muMaxJtpt_jet55_keep[nbins_cent], * hMC_eMaxJtpt_jet55_keep[nbins_cent];
  TH1F * hMC_chSumJtpt_jet55_keep[nbins_cent], * hMC_phSumJtpt_jet55_keep[nbins_cent], * hMC_neSumJtpt_jet55_keep[nbins_cent], * hMC_muSumJtpt_jet55_keep[nbins_cent], * hMC_eSumJtpt_jet55_keep[nbins_cent];  

  TH1F * hData_chMaxJtpt_jet55_rej[nbins_cent], * hData_phMaxJtpt_jet55_rej[nbins_cent], * hData_neMaxJtpt_jet55_rej[nbins_cent], * hData_muMaxJtpt_jet55_rej[nbins_cent], * hData_eMaxJtpt_jet55_rej[nbins_cent];
  TH1F * hData_chSumJtpt_jet55_rej[nbins_cent], * hData_phSumJtpt_jet55_rej[nbins_cent], * hData_neSumJtpt_jet55_rej[nbins_cent], * hData_muSumJtpt_jet55_rej[nbins_cent], * hData_eSumJtpt_jet55_rej[nbins_cent];  
  
  TH1F * hMC_chMaxJtpt_jet55_rej[nbins_cent], * hMC_phMaxJtpt_jet55_rej[nbins_cent], * hMC_neMaxJtpt_jet55_rej[nbins_cent], * hMC_muMaxJtpt_jet55_rej[nbins_cent], * hMC_eMaxJtpt_jet55_rej[nbins_cent];
  TH1F * hMC_chSumJtpt_jet55_rej[nbins_cent], * hMC_phSumJtpt_jet55_rej[nbins_cent], * hMC_neSumJtpt_jet55_rej[nbins_cent], * hMC_muSumJtpt_jet55_rej[nbins_cent], * hMC_eSumJtpt_jet55_rej[nbins_cent];  

  Int_t * nData_chMaxJtpt_jet55_keep[nbins_cent], * nData_phMaxJtpt_jet55_keep[nbins_cent], * nData_neMaxJtpt_jet55_keep[nbins_cent], * nData_muMaxJtpt_jet55_keep[nbins_cent], * nData_eMaxJtpt_jet55_keep[nbins_cent];
  Int_t * nData_chSumJtpt_jet55_keep[nbins_cent], * nData_phSumJtpt_jet55_keep[nbins_cent], * nData_neSumJtpt_jet55_keep[nbins_cent], * nData_muSumJtpt_jet55_keep[nbins_cent], * nData_eSumJtpt_jet55_keep[nbins_cent];  
  
  Int_t * nMC_chMaxJtpt_jet55_keep[nbins_cent], * nMC_phMaxJtpt_jet55_keep[nbins_cent], * nMC_neMaxJtpt_jet55_keep[nbins_cent], * nMC_muMaxJtpt_jet55_keep[nbins_cent], * nMC_eMaxJtpt_jet55_keep[nbins_cent];
  Int_t * nMC_chSumJtpt_jet55_keep[nbins_cent], * nMC_phSumJtpt_jet55_keep[nbins_cent], * nMC_neSumJtpt_jet55_keep[nbins_cent], * nMC_muSumJtpt_jet55_keep[nbins_cent], * nMC_eSumJtpt_jet55_keep[nbins_cent];  

  Int_t * nData_chMaxJtpt_jet55_rej[nbins_cent], * nData_phMaxJtpt_jet55_rej[nbins_cent], * nData_neMaxJtpt_jet55_rej[nbins_cent], * nData_muMaxJtpt_jet55_rej[nbins_cent], * nData_eMaxJtpt_jet55_rej[nbins_cent];
  Int_t * nData_chSumJtpt_jet55_rej[nbins_cent], * nData_phSumJtpt_jet55_rej[nbins_cent], * nData_neSumJtpt_jet55_rej[nbins_cent], * nData_muSumJtpt_jet55_rej[nbins_cent], * nData_eSumJtpt_jet55_rej[nbins_cent];  
  
  Int_t * nMC_chMaxJtpt_jet55_rej[nbins_cent], * nMC_phMaxJtpt_jet55_rej[nbins_cent], * nMC_neMaxJtpt_jet55_rej[nbins_cent], * nMC_muMaxJtpt_jet55_rej[nbins_cent], * nMC_eMaxJtpt_jet55_rej[nbins_cent];
  Int_t * nMC_chSumJtpt_jet55_rej[nbins_cent], * nMC_phSumJtpt_jet55_rej[nbins_cent], * nMC_neSumJtpt_jet55_rej[nbins_cent], * nMC_muSumJtpt_jet55_rej[nbins_cent], * nMC_eSumJtpt_jet55_rej[nbins_cent];  
  
  for(int i = 0;i<nbins_cent;++i){
    hData_chMaxJtpt_jet55_keep[i] = (TH1F*)fin->Get(Form("hData_chMaxJtpt_jet55_keep_cent%d",i));
    hMC_chMaxJtpt_jet55_keep[i] = (TH1F*)fin->Get(Form("hMC_chMaxJtpt_jet55_keep_cent%d",i));
    hData_chSumJtpt_jet55_keep[i] = (TH1F*)fin->Get(Form("hData_chSumJtpt_jet55_keep_cent%d",i));
    hMC_chSumJtpt_jet55_keep[i] = (TH1F*)fin->Get(Form("hMC_chSumJtpt_jet55_keep_cent%d",i));

    hData_eMaxJtpt_jet55_keep[i] = (TH1F*)fin->Get(Form("hData_eMaxJtpt_jet55_keep_cent%d",i));
    hMC_eMaxJtpt_jet55_keep[i] = (TH1F*)fin->Get(Form("hMC_eMaxJtpt_jet55_keep_cent%d",i));
    hData_eSumJtpt_jet55_keep[i] = (TH1F*)fin->Get(Form("hData_eSumJtpt_jet55_keep_cent%d",i));
    hMC_eSumJtpt_jet55_keep[i] = (TH1F*)fin->Get(Form("hMC_eSumJtpt_jet55_keep_cent%d",i));

    hData_neMaxJtpt_jet55_keep[i] = (TH1F*)fin->Get(Form("hData_neMaxJtpt_jet55_keep_cent%d",i));
    hMC_neMaxJtpt_jet55_keep[i] = (TH1F*)fin->Get(Form("hMC_neMaxJtpt_jet55_keep_cent%d",i));
    hData_neSumJtpt_jet55_keep[i] = (TH1F*)fin->Get(Form("hData_neSumJtpt_jet55_keep_cent%d",i));
    hMC_neSumJtpt_jet55_keep[i] = (TH1F*)fin->Get(Form("hMC_neSumJtpt_jet55_keep_cent%d",i));

    hData_phMaxJtpt_jet55_keep[i] = (TH1F*)fin->Get(Form("hData_phMaxJtpt_jet55_keep_cent%d",i));
    hMC_phMaxJtpt_jet55_keep[i] = (TH1F*)fin->Get(Form("hMC_phMaxJtpt_jet55_keep_cent%d",i));
    hData_phSumJtpt_jet55_keep[i] = (TH1F*)fin->Get(Form("hData_phSumJtpt_jet55_keep_cent%d",i));
    hMC_phSumJtpt_jet55_keep[i] = (TH1F*)fin->Get(Form("hMC_phSumJtpt_jet55_keep_cent%d",i));

    hData_muMaxJtpt_jet55_keep[i] = (TH1F*)fin->Get(Form("hData_muMaxJtpt_jet55_keep_cent%d",i));
    hMC_muMaxJtpt_jet55_keep[i] = (TH1F*)fin->Get(Form("hMC_muMaxJtpt_jet55_keep_cent%d",i));
    hData_muSumJtpt_jet55_keep[i] = (TH1F*)fin->Get(Form("hData_muSumJtpt_jet55_keep_cent%d",i));
    hMC_muSumJtpt_jet55_keep[i] = (TH1F*)fin->Get(Form("hMC_muSumJtpt_jet55_keep_cent%d",i));

    hData_chMaxJtpt_jet55_rej[i] = (TH1F*)fin->Get(Form("hData_chMaxJtpt_jet55_rej_cent%d",i));
    hMC_chMaxJtpt_jet55_rej[i] = (TH1F*)fin->Get(Form("hMC_chMaxJtpt_jet55_rej_cent%d",i));
    hData_chSumJtpt_jet55_rej[i] = (TH1F*)fin->Get(Form("hData_chSumJtpt_jet55_rej_cent%d",i));
    hMC_chSumJtpt_jet55_rej[i] = (TH1F*)fin->Get(Form("hMC_chSumJtpt_jet55_rej_cent%d",i));

    hData_eMaxJtpt_jet55_rej[i] = (TH1F*)fin->Get(Form("hData_eMaxJtpt_jet55_rej_cent%d",i));
    hMC_eMaxJtpt_jet55_rej[i] = (TH1F*)fin->Get(Form("hMC_eMaxJtpt_jet55_rej_cent%d",i));
    hData_eSumJtpt_jet55_rej[i] = (TH1F*)fin->Get(Form("hData_eSumJtpt_jet55_rej_cent%d",i));
    hMC_eSumJtpt_jet55_rej[i] = (TH1F*)fin->Get(Form("hMC_eSumJtpt_jet55_rej_cent%d",i));

    hData_neMaxJtpt_jet55_rej[i] = (TH1F*)fin->Get(Form("hData_neMaxJtpt_jet55_rej_cent%d",i));
    hMC_neMaxJtpt_jet55_rej[i] = (TH1F*)fin->Get(Form("hMC_neMaxJtpt_jet55_rej_cent%d",i));
    hData_neSumJtpt_jet55_rej[i] = (TH1F*)fin->Get(Form("hData_neSumJtpt_jet55_rej_cent%d",i));
    hMC_neSumJtpt_jet55_rej[i] = (TH1F*)fin->Get(Form("hMC_neSumJtpt_jet55_rej_cent%d",i));

    hData_phMaxJtpt_jet55_rej[i] = (TH1F*)fin->Get(Form("hData_phMaxJtpt_jet55_rej_cent%d",i));
    hMC_phMaxJtpt_jet55_rej[i] = (TH1F*)fin->Get(Form("hMC_phMaxJtpt_jet55_rej_cent%d",i));
    hData_phSumJtpt_jet55_rej[i] = (TH1F*)fin->Get(Form("hData_phSumJtpt_jet55_rej_cent%d",i));
    hMC_phSumJtpt_jet55_rej[i] = (TH1F*)fin->Get(Form("hMC_phSumJtpt_jet55_rej_cent%d",i));

    hData_muMaxJtpt_jet55_rej[i] = (TH1F*)fin->Get(Form("hData_muMaxJtpt_jet55_rej_cent%d",i));
    hMC_muMaxJtpt_jet55_rej[i] = (TH1F*)fin->Get(Form("hMC_muMaxJtpt_jet55_rej_cent%d",i));
    hData_muSumJtpt_jet55_rej[i] = (TH1F*)fin->Get(Form("hData_muSumJtpt_jet55_rej_cent%d",i));
    hMC_muSumJtpt_jet55_rej[i] = (TH1F*)fin->Get(Form("hMC_muSumJtpt_jet55_rej_cent%d",i));

  }
    
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
}