#include <TF1.h>
#include <TProfile.h>
#include <TChain.h>
#include <TTree.h>
#include <TEventList.h>
#include <TSystem.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TFile.h>
#include <TStyle.h>
#include <TStopwatch.h>
#include <TRandom3.h>
#include <TCanvas.h>
#include <TMath.h>

#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>
#include <algorithm>

#include "utilities.h"

using namespace std;

#ifdef _MAKECINT_
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#endif

#define pi 3.14159265

const int ncen=8;
const char *cdir [ncen] = {"05","510","1030","3050","5070","7090","90100","pp"};
const char *ccent[ncen] = {"0-5%","5-10%","10-30%","30-50%","50-70%","70-90%","90-100%","pp"};

// const double etabins[] = {-2.000, -1.4000, -0.4500, 0.000, 0.4500, 1.400, 2.000};
// const int neta = sizeof(etabins)/sizeof(double) - 1;
const double ketacut=1.8;
const double etabins[] = {0, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0};
const int neta = sizeof(etabins)/sizeof(double) - 1;
const char *seta[neta] = {"|eta|<1.0","1.0<|eta|<1.1","1.1<|eta|<1.2","1.2<|eta|<1.3","1.3<|eta|<1.4","1.4<|eta|<1.5","1.5<|eta|<1.6","1.6<|eta|<1.7","1.7<|eta|<1.8","1.8<|eta|<1.9","1.9<|eta|<2.0"};

double ptbins[] = {
  3, 4, 5, 7, 9, 12, 
  15, 18, 21, 24, 28,
  32, 37, 43, 49, 56,
  64, 74, 84, 97, 114,
  133, 153, 174, 196,
  220, 245, 272, 300, 
  330, 362, 395, 430,
  468, 507, 548 
};
const int nbins = sizeof(ptbins)/sizeof(double) - 1;

const double phibins[] = {-3.141,-2.100,-1.500,-0.800,-0.300,0.300,0.800,1.500,2.100,3.141};
const int nphi = sizeof(phibins)/sizeof(double) - 1;

const int knj=3;
std::string srad[knj] = {"2", "3", "4"};

TStopwatch timer;

void DrawFakeEtaBins_reduced(std::string kSpecies="PbPb"){
  timer.Start();

  bool printDebug=false;
   TDatime date;

  std::string kAlgName="ak";
  std::string kSpeciesLong = "pp (PYTHIA)";
  if( kSpecies == "PbPb" ) { kAlgName="akPu";  kSpeciesLong = "PbPb (PYTHIA+HYDJET)"; }
  std::string kjetType="PF";
  
  LoadStyle();
  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();
  TH2F * hBlankRatio = new TH2F("hBlankRatio","",20,-2.1,2.1,50,0,1.0);
  TH2F * hBlankPhiRatio = new TH2F("hBlankPhiRatio","",20,-pi,pi,50,0,1.0);
  TH2F * hBlankPt= new TH2F("hBlankPt","",50,20,350,50,0,1.0);
  TH2F * hBlankPtEff= new TH2F("hBlankPtEff","",50,20,350,50,0.6,1.1);


    TH1F *hPtAll [2][ncen], *hPtEff [2][ncen];
    TH1F *hPtFakeAll[ncen], *hPtFake[2][ncen];
    TH1F *hPtFakeRatio[2][ncen];
    TH1F *hPtAll_etabin[2][ncen][neta], *hPtEff_etabin[2][ncen][neta];    
    TH1F *hPtFakeAll_etabin[ncen][neta], *hPtFake_etabin[2][ncen][neta];
    TH1F *hPtFakeRatio_etabin[2][ncen][neta];   
    TH1F *hPtEffRatio_etabin[2][ncen][neta];     
    TH1F *hPtEffRatio[2][ncen];     
    TH1F *hEtaFakeAll_20[ncen],*hEtaFakeAll_30[ncen], *hEtaFakeAll_40[ncen],*hEtaFakeAll_45[ncen], *hEtaFakeAll_50[ncen], *hEtaFakeAll_60[ncen];
    TH1F *hPhiFakeAll_20[ncen],*hPhiFakeAll_30[ncen], *hPhiFakeAll_40[ncen],*hPhiFakeAll_45[ncen], *hPhiFakeAll_50[ncen], *hPhiFakeAll_60[ncen];
    TH1F *hEtaFake_20[2][ncen],*hEtaFake_30[2][ncen], *hEtaFake_40[2][ncen],*hEtaFake_45[2][ncen], *hEtaFake_50[2][ncen], *hEtaFake_60[2][ncen];
    TH1F *hPhiFake_20[2][ncen],*hPhiFake_30[2][ncen], *hPhiFake_40[2][ncen],*hPhiFake_45[2][ncen], *hPhiFake_50[2][ncen], *hPhiFake_60[2][ncen];  
    TH1F *hEtaFakeRatio_20[2][ncen],*hEtaFakeRatio_30[2][ncen], *hEtaFakeRatio_40[2][ncen],*hEtaFakeRatio_45[2][ncen], *hEtaFakeRatio_50[2][ncen], *hEtaFakeRatio_60[2][ncen];
    TH1F *hPhiFakeRatio_20[2][ncen],*hPhiFakeRatio_30[2][ncen], *hPhiFakeRatio_40[2][ncen],*hPhiFakeRatio_45[2][ncen], *hPhiFakeRatio_50[2][ncen], *hPhiFakeRatio_60[2][ncen];

    TH1F *hEtaFakeRatio_70[2][ncen], *hEtaFakeRatio_80[2][ncen];
    TH1F *hPhiFakeRatio_70[2][ncen], *hPhiFakeRatio_80[2][ncen];
    TH1F *hEtaFakeAll_70[ncen], *hEtaFakeAll_80[ncen];
    TH1F *hPhiFakeAll_70[ncen], *hPhiFakeAll_80[ncen];
    TH1F *hEtaFake_70[2][ncen], *hEtaFake_80[2][ncen];
    TH1F *hPhiFake_70[2][ncen], *hPhiFake_80[2][ncen];
    
  TFile *fin = new TFile(Form("Histos/OutputHist_ntuples_reduced_eta_lt1pt8_%s.root",kSpecies.c_str()),"r");
// radius loop
    for(int nj=0; nj<knj; nj++){
    // i is the with or without jetID loop, NOT the nj loop! 0 == no JetID, 1== JetID
     for(int i=0; i<2; i++){
 // centrality loop    
      for(int ic=0; ic<ncen; ic++){
    	if(i==0){
     	  hPtFakeAll[ic] = (TH1F*)fin->Get(Form("hPtFakeAll_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
     	  hPtFakeAll[ic]->Print("base");  	  
    	  hEtaFakeAll_20[ic] = (TH1F*)fin->Get(Form("hEtaFakeAll_20_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
    	  hEtaFakeAll_20[ic]->Print("base");
    	  hPhiFakeAll_20[ic] = (TH1F*)fin->Get(Form("hPhiFakeAll_20_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
          hPhiFakeAll_20[ic]->Print("base");
    	  hEtaFakeAll_30[ic] = (TH1F*)fin->Get(Form("hEtaFakeAll_30_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
    	  hEtaFakeAll_30[ic]->Print("base");
    	  hPhiFakeAll_30[ic] = (TH1F*)fin->Get(Form("hPhiFakeAll_30_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
          hPhiFakeAll_30[ic]->Print("base");
    	  hEtaFakeAll_40[ic] = (TH1F*)fin->Get(Form("hEtaFakeAll_40_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
    	  hEtaFakeAll_40[ic]->Print("base");
    	  hPhiFakeAll_40[ic] = (TH1F*)fin->Get(Form("hPhiFakeAll_40_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
          hPhiFakeAll_40[ic]->Print("base");
    	  hEtaFakeAll_45[ic] = (TH1F*)fin->Get(Form("hEtaFakeAll_45_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
    	  hEtaFakeAll_45[ic] ->Print("base");
    	  hPhiFakeAll_45[ic] = (TH1F*)fin->Get(Form("hPhiFakeAll_45_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
          hPhiFakeAll_45[ic]->Print("base");
    	  hEtaFakeAll_50[ic] = (TH1F*)fin->Get(Form("hEtaFakeAll_50_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic));
    	  hEtaFakeAll_50[ic]->Print("base"); 
    	  hPhiFakeAll_50[ic] = (TH1F*)fin->Get(Form("hPhiFakeAll_50_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
    	  hPhiFakeAll_50[ic]->Print("base"); 
    	  hEtaFakeAll_60[ic] = (TH1F*)fin->Get(Form("hEtaFakeAll_60_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
    	  hEtaFakeAll_60[ic]->Print("base");
    	  hPhiFakeAll_60[ic] = (TH1F*)fin->Get(Form("hPhiFakeAll_60_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
          hPhiFakeAll_60[ic]->Print("base");
    	  hEtaFakeAll_70[ic] = (TH1F*)fin->Get(Form("hEtaFakeAll_70_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
    	  hEtaFakeAll_70[ic]->Print("base");
    	  hPhiFakeAll_70[ic] = (TH1F*)fin->Get(Form("hPhiFakeAll_70_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
          hPhiFakeAll_70[ic]->Print("base");
    	  hEtaFakeAll_80[ic] = (TH1F*)fin->Get(Form("hEtaFakeAll_80_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
    	  hEtaFakeAll_80[ic]->Print("base");
    	  hPhiFakeAll_80[ic] = (TH1F*)fin->Get(Form("hPhiFakeAll_80_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
          hPhiFakeAll_80[ic]->Print("base");
           for(int in=0; in<neta; in++){    
              hPtFakeAll_etabin[ic][in] = (TH1F*)fin->Get(Form("hPtFakeAll_etabin_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic,in)); 
     	      hPtFakeAll_etabin[ic][in]->Print("base");  
      	  }
   	  
    	}
     	  hPtAll[i][ic] = (TH1F*)fin->Get(Form("hPtAll_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
     	  hPtAll[i][ic]->Print("base");    	
    	// end if i=0 (no jetID)
     	hPtEff[i][ic] = (TH1F*)fin->Get(Form("hPtEff_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
     	hPtEff[i][ic]->Print("base");
    	hPtFake[i][ic] = (TH1F*)fin->Get(Form("hPtFake_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
        hPtFake[i][ic]->Print("base");
    	hEtaFake_20[i][ic] = (TH1F*)fin->Get(Form("hEtaFake_20_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
    	hEtaFake_20[i][ic]->Print("base");
    	hPhiFake_20[i][ic] = (TH1F*)fin->Get(Form("hPhiFake_20_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
        hPhiFake_20[i][ic]->Print("base");
    	hEtaFake_30[i][ic] = (TH1F*)fin->Get(Form("hEtaFake_30_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
    	hEtaFake_30[i][ic]->Print("base");
    	hPhiFake_30[i][ic] = (TH1F*)fin->Get(Form("hPhiFake_30_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
        hPhiFake_30[i][ic]->Print("base");
    	hEtaFake_40[i][ic] = (TH1F*)fin->Get(Form("hEtaFake_40_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
    	hEtaFake_40[i][ic]->Print("base");
    	hPhiFake_40[i][ic] = (TH1F*)fin->Get(Form("hPhiFake_40_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
        hPhiFake_40[i][ic]->Print("base");
    	hEtaFake_45[i][ic] = (TH1F*)fin->Get(Form("hEtaFake_45_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
    	hEtaFake_45[i][ic]->Print("base");
    	hPhiFake_45[i][ic] = (TH1F*)fin->Get(Form("hPhiFake_45_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
        hPhiFake_45[i][ic]->Print("base");
    	hEtaFake_50[i][ic] = (TH1F*)fin->Get(Form("hEtaFake_50_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
    	hEtaFake_50[i][ic]->Print("base");
    	hPhiFake_50[i][ic] = (TH1F*)fin->Get(Form("hPhiFake_50_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
   	    hPhiFake_50[i][ic]->Print("base");
    	hEtaFake_60[i][ic] = (TH1F*)fin->Get(Form("hEtaFake_60_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
    	hEtaFake_60[i][ic]->Print("base");
     	hEtaFake_60[i][ic]->Draw();   	
    	hPhiFake_60[i][ic] = (TH1F*)fin->Get(Form("hPhiFake_60_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
    	hPhiFake_60[i][ic]->Print("base");
    	hEtaFake_70[i][ic] = (TH1F*)fin->Get(Form("hEtaFake_70_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
    	hEtaFake_70[i][ic]->Print("base");
     	hEtaFake_70[i][ic]->Draw();   	
    	hPhiFake_70[i][ic] = (TH1F*)fin->Get(Form("hPhiFake_70_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
    	hPhiFake_70[i][ic]->Print("base");
    	hEtaFake_80[i][ic] = (TH1F*)fin->Get(Form("hEtaFake_80_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
    	hEtaFake_80[i][ic]->Print("base");
     	hEtaFake_80[i][ic]->Draw();   	
    	hPhiFake_80[i][ic] = (TH1F*)fin->Get(Form("hPhiFake_80_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
    	hPhiFake_80[i][ic]->Print("base");
    	hEtaFakeRatio_20[i][ic]=(TH1F*)hEtaFake_20[i][ic]->Clone(Form("hEtaFakeRatio_20_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hEtaFakeRatio_20[i][ic]->Divide(hEtaFakeAll_20[ic]);
    	hEtaFakeRatio_30[i][ic]=(TH1F*)hEtaFake_30[i][ic]->Clone(Form("hEtaFakeRatio_30_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hEtaFakeRatio_30[i][ic]->Divide(hEtaFakeAll_30[ic]);
    	hEtaFakeRatio_30[i][ic]->SetMarkerSize(2.5);
    	hEtaFakeRatio_40[i][ic]=(TH1F*)hEtaFake_40[i][ic]->Clone(Form("hEtaFakeRatio_40_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hEtaFakeRatio_40[i][ic]->Divide(hEtaFakeAll_40[ic]);
    	hEtaFakeRatio_40[i][ic]->SetMarkerSize(2.5);
    	hEtaFakeRatio_45[i][ic]=(TH1F*)hEtaFake_45[i][ic]->Clone(Form("hEtaFakeRatio_45_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hEtaFakeRatio_45[i][ic]->Divide(hEtaFakeAll_45[ic]);
    	hEtaFakeRatio_50[i][ic]=(TH1F*)hEtaFake_50[i][ic]->Clone(Form("hEtaFakeRatio_50_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hEtaFakeRatio_50[i][ic]->Divide(hEtaFakeAll_50[ic]);
    	hEtaFakeRatio_50[i][ic]->SetMarkerSize(2.5);
    	hEtaFakeRatio_60[i][ic]=(TH1F*)hEtaFake_60[i][ic]->Clone(Form("hEtaFakeRatio_60_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hEtaFakeRatio_60[i][ic]->Divide(hEtaFakeAll_60[ic]);
    	hEtaFakeRatio_60[i][ic]->SetMarkerSize(2.5);
     	hPhiFakeRatio_20[i][ic]=(TH1F*)hPhiFake_20[i][ic]->Clone(Form("hPhiFakeRatio_20_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hPhiFakeRatio_20[i][ic]->Divide(hPhiFakeAll_20[ic]);
    	hPhiFakeRatio_30[i][ic]=(TH1F*)hPhiFake_30[i][ic]->Clone(Form("hPhiFakeRatio_30_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hPhiFakeRatio_30[i][ic]->Divide(hPhiFakeAll_30[ic]);
    	hPhiFakeRatio_30[i][ic]->SetMarkerSize(2.5);
    	hPhiFakeRatio_40[i][ic]=(TH1F*)hPhiFake_40[i][ic]->Clone(Form("hPhiFakeRatio_40_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hPhiFakeRatio_40[i][ic]->Divide(hPhiFakeAll_40[ic]);
    	hPhiFakeRatio_40[i][ic]->SetMarkerSize(2.5);
    	hPhiFakeRatio_45[i][ic]=(TH1F*)hPhiFake_45[i][ic]->Clone(Form("hPhiFakeRatio_45_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hPhiFakeRatio_45[i][ic]->Divide(hPhiFakeAll_45[ic]);
    	hPhiFakeRatio_50[i][ic]=(TH1F*)hPhiFake_50[i][ic]->Clone(Form("hPhiFakeRatio_50_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hPhiFakeRatio_50[i][ic]->Divide(hPhiFakeAll_50[ic]);
    	hPhiFakeRatio_50[i][ic]->SetMarkerSize(2.5);
    	hPhiFakeRatio_60[i][ic]=(TH1F*)hPhiFake_60[i][ic]->Clone(Form("hPhiFakeRatio_60_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hPhiFakeRatio_60[i][ic]->Divide(hPhiFakeAll_60[ic]);
    	hPhiFakeRatio_60[i][ic]->SetMarkerSize(2.5);
    	hEtaFakeRatio_70[i][ic]=(TH1F*)hEtaFake_70[i][ic]->Clone(Form("hEtaFakeRatio_70_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hEtaFakeRatio_70[i][ic]->Divide(hEtaFakeAll_70[ic]);
    	hEtaFakeRatio_70[i][ic]->SetMarkerSize(2.5);
    	hPhiFakeRatio_70[i][ic]=(TH1F*)hPhiFake_70[i][ic]->Clone(Form("hPhiFakeRatio_70_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hPhiFakeRatio_70[i][ic]->Divide(hPhiFakeAll_70[ic]);
    	hPhiFakeRatio_70[i][ic]->SetMarkerSize(2.5);
    	hEtaFakeRatio_80[i][ic]=(TH1F*)hEtaFake_80[i][ic]->Clone(Form("hEtaFakeRatio_80_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hEtaFakeRatio_80[i][ic]->Divide(hEtaFakeAll_80[ic]);
    	hEtaFakeRatio_80[i][ic]->SetMarkerSize(2.5);
    	hPhiFakeRatio_80[i][ic]=(TH1F*)hPhiFake_80[i][ic]->Clone(Form("hPhiFakeRatio_80_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hPhiFakeRatio_80[i][ic]->Divide(hPhiFakeAll_80[ic]);
    	hPhiFakeRatio_80[i][ic]->SetMarkerSize(2.5);
    	    	
    	hPtFakeRatio[i][ic]=(TH1F*)hPtFake[i][ic]->Clone(Form("hPtFakeRatio_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hPtFakeRatio[i][ic]->Divide(hPtFakeAll[ic]);    
    	hPtFakeRatio[i][ic]->SetMarkerSize(2.5);	
        for(int in=0; in<neta; in++){
            hPtAll_etabin[i][ic][in] = (TH1F*)fin->Get(Form("hPtAll_etabin_%s_%d_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic,in)); 
     	   hPtAll_etabin[i][ic][in]->Print("base");       
     	   hPtEff_etabin[i][ic][in] = (TH1F*)fin->Get(Form("hPtEff_etabin_%s_%d_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic,in)); 
     	   hPtEff_etabin[i][ic][in]->Print("base");
    	   hPtFake_etabin[i][ic][in] = (TH1F*)fin->Get(Form("hPtFake_etabin_%s_%d_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic,in)); 
           hPtFake_etabin[i][ic][in]->Print("base");    	
    	   hPtFakeRatio_etabin[i][ic][in]=(TH1F*)hPtFake_etabin[i][ic][in]->Clone(Form("hPtFakeRatio_etabin%d_%s_%d_%d",in,(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	   hPtFakeRatio_etabin[i][ic][in]->Divide(hPtFakeAll_etabin[ic][in]);    
    	   hPtFakeRatio_etabin[i][ic][in]->SetMarkerSize(2.5);	
    	   hPtEffRatio_etabin[i][ic][in]=(TH1F*)hPtEff_etabin[i][ic][in]->Clone(Form("hPtEffRatio_etabin%d_%s_%d",in,(kAlgName+srad[nj]+kjetType).c_str(),ic));
    	   hPtEffRatio_etabin[i][ic][in]->Divide(hPtAll_etabin[i][ic][in]);    
    	   hPtEffRatio_etabin[i][ic][in]->SetMarkerSize(2.5);	
    	}
    	   hPtEffRatio[i][ic]=(TH1F*)hPtEff[i][ic]->Clone(Form("hPtEffRatio_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic));
    	   hPtEffRatio[i][ic]->Divide(hPtAll[i][ic]);    
    	   hPtEffRatio[i][ic]->SetMarkerSize(2.5);	
    	
       }
//  end centrality loop
    	
     } // end i loop (JetID)   
//     if(nj==0){   
//         TCanvas *c0 = new TCanvas();
//         c0.cd();
//     } else {
//     if(nj==1){
//         TCanvas *c1 = new TCanvas();
//         c1.cd();
//     } else {
//     if(nj==2){
//         TCanvas *c2 = new TCanvas();
//         c2.cd();
//     }
    TCanvas * c30 = new TCanvas("c30","",1200,1000);
    TLegend *leg30 = getLegend(0.5,0.5,0.7,0.9);
    leg30->SetHeader("");   
    for(int ic=0; ic<ncen-2; ic++){
       hEtaFakeRatio_30[1][ic]->SetMarkerStyle(24+ic);
       if(ic==0){ hEtaFakeRatio_30[1][ic]->SetMarkerColor(kViolet); hEtaFakeRatio_30[1][ic]->SetLineColor(kViolet);}
       if(ic==1){ hEtaFakeRatio_30[1][ic]->SetMarkerColor(kGreen+1); hEtaFakeRatio_30[1][ic]->SetLineColor(kGreen+1);}
       if(ic==2){ hEtaFakeRatio_30[1][ic]->SetMarkerColor(kRed); hEtaFakeRatio_30[1][ic]->SetLineColor(kRed);}
       if(ic==3){ hEtaFakeRatio_30[1][ic]->SetMarkerColor(kBlue); hEtaFakeRatio_30[1][ic]->SetLineColor(kBlue);}
       if(ic==4){ hEtaFakeRatio_30[1][ic]->SetMarkerColor(kPink);  hEtaFakeRatio_30[1][ic]->SetLineColor(kPink);}
       if(ic==5){ hEtaFakeRatio_30[1][ic]->SetMarkerColor(kYellow); hEtaFakeRatio_30[1][ic]->SetLineColor(kYellow);}
       if(ic==0){
         hBlankRatio->SetTitle(Form(" %s, %s, jetID, pT>30 GeV/c",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankRatio->GetXaxis()->SetTitle("Reco jet eta");
         hBlankRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankRatio->Draw();
       }
       leg30->AddEntry(hEtaFakeRatio_30[1][ic],Form("%s",ccent[ic]),"p");
       hEtaFakeRatio_30[1][ic]->Draw("same");
    }
    leg30->Draw();    
     c30->SaveAs(Form("ANPlots/FakeEtaRate_30_%sMC_JetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
//          hBlankRatio->SetTitle(Form(" %s, pp (PYTHIA), jetID, pT>30 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str()));
//          hBlankRatio->GetXaxis()->SetTitle("Reco jet eta");
//          hBlankRatio->GetYaxis()->SetTitle("Fake rate");
//          hBlankRatio->Draw(); 
//          leg30->AddEntry(hEtaFakeRatio_30[1][7],Form("%s",ccent[7]),"p"); 
//          hEtaFakeRatio_30[1][7]->Draw("same"); 
//     c30->SaveAs(Form("ANPlots/FakeEtaRate_30_ppMC_JetID_%s_%d.pdf",(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
    
    TCanvas * c40 = new TCanvas("c40","",1200,1000);
    TLegend *leg40 = getLegend(0.5,0.5,0.7,0.9);
    leg40->SetHeader("");    
    for(int ic=0; ic<ncen-2; ic++){
       hEtaFakeRatio_40[1][ic]->SetMarkerStyle(24+ic);
       if(ic==0){ hEtaFakeRatio_40[1][ic]->SetMarkerColor(kViolet); hEtaFakeRatio_40[1][ic]->SetLineColor(kViolet);}
       if(ic==1){ hEtaFakeRatio_40[1][ic]->SetMarkerColor(kGreen+1); hEtaFakeRatio_40[1][ic]->SetLineColor(kGreen+1);}
       if(ic==2){ hEtaFakeRatio_40[1][ic]->SetMarkerColor(kRed); hEtaFakeRatio_40[1][ic]->SetLineColor(kRed);}
       if(ic==3){ hEtaFakeRatio_40[1][ic]->SetMarkerColor(kBlue); hEtaFakeRatio_40[1][ic]->SetLineColor(kBlue);}
       if(ic==4){ hEtaFakeRatio_40[1][ic]->SetMarkerColor(kPink);  hEtaFakeRatio_40[1][ic]->SetLineColor(kPink);}
       if(ic==5){ hEtaFakeRatio_40[1][ic]->SetMarkerColor(kYellow); hEtaFakeRatio_40[1][ic]->SetLineColor(kYellow);}
       if(ic==0){
         hBlankRatio->SetTitle(Form(" %s, %s, jetID, pT>40 GeV/c",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankRatio->GetXaxis()->SetTitle("Reco jet eta");
         hBlankRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankRatio->Draw();
       }
       leg40->AddEntry(hEtaFakeRatio_40[1][ic],Form("%s",ccent[ic]),"p");
      hEtaFakeRatio_40[1][ic]->Draw("same");
    }
    leg40->Draw();
    c40->SaveAs(Form("ANPlots/FakeEtaRate_40_%sMC_JetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
//          hBlankRatio->SetTitle(Form(" %s, pp (PYTHIA), jetID, pT>40 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str()));
//          hBlankRatio->GetXaxis()->SetTitle("Reco jet eta");
//          hBlankRatio->GetYaxis()->SetTitle("Fake rate");
//          hBlankRatio->Draw(); 
//          leg40->AddEntry(hEtaFakeRatio_40[1][7],Form("%s",ccent[7]),"p"); 
//          hEtaFakeRatio_40[1][7]->Draw("same"); 
//     c40->SaveAs(Form("ANPlots/FakeEtaRate_40_ppMC_JetID_%s_%d.pdf",(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
    
    TCanvas * c50 = new TCanvas("c50","",1200,1000);
    TLegend *leg50 = getLegend(0.5,0.5,0.7,0.9);
    leg50->SetHeader("");   
    for(int ic=0; ic<ncen-2; ic++){
       hEtaFakeRatio_50[1][ic]->SetMarkerStyle(24+ic);
       if(ic==0){ hEtaFakeRatio_50[1][ic]->SetMarkerColor(kViolet); hEtaFakeRatio_50[1][ic]->SetLineColor(kViolet);}
       if(ic==1){ hEtaFakeRatio_50[1][ic]->SetMarkerColor(kGreen+1); hEtaFakeRatio_50[1][ic]->SetLineColor(kGreen+1);}
       if(ic==2){ hEtaFakeRatio_50[1][ic]->SetMarkerColor(kRed); hEtaFakeRatio_50[1][ic]->SetLineColor(kRed);}
       if(ic==3){ hEtaFakeRatio_50[1][ic]->SetMarkerColor(kBlue); hEtaFakeRatio_50[1][ic]->SetLineColor(kBlue);}
       if(ic==4){ hEtaFakeRatio_50[1][ic]->SetMarkerColor(kPink);  hEtaFakeRatio_50[1][ic]->SetLineColor(kPink);}
       if(ic==5){ hEtaFakeRatio_50[1][ic]->SetMarkerColor(kYellow); hEtaFakeRatio_50[1][ic]->SetLineColor(kYellow);}
       if(ic==0){
         hBlankRatio->SetTitle(Form(" %s, %s, jetID, pT>50 GeV/c",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankRatio->GetXaxis()->SetTitle("Reco jet eta");
         hBlankRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankRatio->Draw();
       }
       leg50->AddEntry(hEtaFakeRatio_50[1][ic],Form("%s",ccent[ic]),"p");
       hEtaFakeRatio_50[1][ic]->Draw("same");
    }
    leg50->Draw();
    c50->SaveAs(Form("ANPlots/FakeEtaRate_50_%sMC_JetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
//          hBlankRatio->SetTitle(Form(" %s, pp (PYTHIA), jetID, pT>50 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str()));
//          hBlankRatio->GetXaxis()->SetTitle("Reco jet eta");
//          hBlankRatio->GetYaxis()->SetTitle("Fake rate");
//          hBlankRatio->Draw(); 
//          leg50->AddEntry(hEtaFakeRatio_50[1][7],Form("%s",ccent[7]),"p"); 
//          hEtaFakeRatio_50[1][7]->Draw("same"); 
//     c50->SaveAs(Form("ANPlots/FakeEtaRate_50_ppMC_JetID_%s_%d.pdf",(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");

    TCanvas * c60 = new TCanvas("c60","",1200,1000);
    TLegend *leg60 = getLegend(0.5,0.5,0.7,0.9);
    leg60->SetHeader("");      
    for(int ic=0; ic<ncen-2; ic++){
       hEtaFakeRatio_60[1][ic]->SetMarkerStyle(24+ic);
       if(ic==0){ hEtaFakeRatio_60[1][ic]->SetMarkerColor(kViolet); hEtaFakeRatio_60[1][ic]->SetLineColor(kViolet);}
       if(ic==1){ hEtaFakeRatio_60[1][ic]->SetMarkerColor(kGreen+1); hEtaFakeRatio_60[1][ic]->SetLineColor(kGreen+1);}
       if(ic==2){ hEtaFakeRatio_60[1][ic]->SetMarkerColor(kRed); hEtaFakeRatio_60[1][ic]->SetLineColor(kRed);}
       if(ic==3){ hEtaFakeRatio_60[1][ic]->SetMarkerColor(kBlue); hEtaFakeRatio_60[1][ic]->SetLineColor(kBlue);}
       if(ic==4){ hEtaFakeRatio_60[1][ic]->SetMarkerColor(kPink);  hEtaFakeRatio_60[1][ic]->SetLineColor(kPink);}
       if(ic==5){ hEtaFakeRatio_60[1][ic]->SetMarkerColor(kYellow); hEtaFakeRatio_60[1][ic]->SetLineColor(kYellow);}
       if(ic==0){
         hBlankRatio->SetTitle(Form(" %s, %s, jetID, pT>60 GeV/c",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankRatio->GetXaxis()->SetTitle("Reco jet eta");
         hBlankRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankRatio->Draw();
       }
       leg60->AddEntry(hEtaFakeRatio_60[1][ic],Form("%s",ccent[ic]),"p");
       hEtaFakeRatio_60[1][ic]->Draw("same");  
    }
    leg60->Draw();    
    c60->SaveAs(Form("ANPlots/FakeEtaRate_60_%sMC_JetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");    

    TCanvas * c70 = new TCanvas("c70","",1200,1000);
    TLegend *leg70 = getLegend(0.5,0.5,0.7,0.9);
    leg70->SetHeader("");      
    for(int ic=0; ic<ncen-2; ic++){
       hEtaFakeRatio_70[1][ic]->SetMarkerStyle(24+ic);
       if(ic==0){ hEtaFakeRatio_70[1][ic]->SetMarkerColor(kViolet); hEtaFakeRatio_70[1][ic]->SetLineColor(kViolet);}
       if(ic==1){ hEtaFakeRatio_70[1][ic]->SetMarkerColor(kGreen+1); hEtaFakeRatio_70[1][ic]->SetLineColor(kGreen+1);}
       if(ic==2){ hEtaFakeRatio_70[1][ic]->SetMarkerColor(kRed); hEtaFakeRatio_70[1][ic]->SetLineColor(kRed);}
       if(ic==3){ hEtaFakeRatio_70[1][ic]->SetMarkerColor(kBlue); hEtaFakeRatio_70[1][ic]->SetLineColor(kBlue);}
       if(ic==4){ hEtaFakeRatio_70[1][ic]->SetMarkerColor(kPink);  hEtaFakeRatio_70[1][ic]->SetLineColor(kPink);}
       if(ic==5){ hEtaFakeRatio_70[1][ic]->SetMarkerColor(kYellow); hEtaFakeRatio_70[1][ic]->SetLineColor(kYellow);}
       if(ic==0){
         hBlankRatio->SetTitle(Form(" %s, %s, jetID, pT>70 GeV/c",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankRatio->GetXaxis()->SetTitle("Reco jet eta");
         hBlankRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankRatio->Draw();
       }
       leg70->AddEntry(hEtaFakeRatio_70[1][ic],Form("%s",ccent[ic]),"p");
       hEtaFakeRatio_70[1][ic]->Draw("same");  
    }
    leg70->Draw();    
    c70->SaveAs(Form("ANPlots/FakeEtaRate_70_%sMC_JetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");    

    TCanvas * c80 = new TCanvas("c80","",1200,1000);
    TLegend *leg80 = getLegend(0.5,0.5,0.7,0.9);
    leg80->SetHeader("");      
    for(int ic=0; ic<ncen-2; ic++){
       hEtaFakeRatio_80[1][ic]->SetMarkerStyle(24+ic);
       if(ic==0){ hEtaFakeRatio_80[1][ic]->SetMarkerColor(kViolet); hEtaFakeRatio_80[1][ic]->SetLineColor(kViolet);}
       if(ic==1){ hEtaFakeRatio_80[1][ic]->SetMarkerColor(kGreen+1); hEtaFakeRatio_80[1][ic]->SetLineColor(kGreen+1);}
       if(ic==2){ hEtaFakeRatio_80[1][ic]->SetMarkerColor(kRed); hEtaFakeRatio_80[1][ic]->SetLineColor(kRed);}
       if(ic==3){ hEtaFakeRatio_80[1][ic]->SetMarkerColor(kBlue); hEtaFakeRatio_80[1][ic]->SetLineColor(kBlue);}
       if(ic==4){ hEtaFakeRatio_80[1][ic]->SetMarkerColor(kPink);  hEtaFakeRatio_80[1][ic]->SetLineColor(kPink);}
       if(ic==5){ hEtaFakeRatio_80[1][ic]->SetMarkerColor(kYellow); hEtaFakeRatio_80[1][ic]->SetLineColor(kYellow);}
       if(ic==0){
         hBlankRatio->SetTitle(Form(" %s, %s, jetID, pT>80 GeV/c",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankRatio->GetXaxis()->SetTitle("Reco jet eta");
         hBlankRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankRatio->Draw();
       }
       leg80->AddEntry(hEtaFakeRatio_80[1][ic],Form("%s",ccent[ic]),"p");
       hEtaFakeRatio_80[1][ic]->Draw("same");  
    }
    leg80->Draw();    
    c80->SaveAs(Form("ANPlots/FakeEtaRate_80_%sMC_JetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");    

//          hBlankRatio->SetTitle(Form(" %s, pp (PYTHIA), jetID, pT>60 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str()));
//          hBlankRatio->GetXaxis()->SetTitle("Reco jet eta");
//          hBlankRatio->GetYaxis()->SetTitle("Fake rate");
//          hBlankRatio->Draw(); 
//          leg60->AddEntry(hEtaFakeRatio_60[1][7],Form("%s",ccent[7]),"p"); 
//          hEtaFakeRatio_60[1][7]->Draw("same"); 
//     c60->SaveAs(Form("ANPlots/FakeEtaRate_60_ppMC_JetID_%s_%d.pdf",(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");

// phi plots
    TCanvas * cPhi30 = new TCanvas("cPhi30","",1200,1000);
    TLegend *legPhi30 = getLegend(0.5,0.5,0.7,0.9);
    legPhi30->SetHeader("");   
    for(int ic=0; ic<ncen-2; ic++){
       hPhiFakeRatio_30[1][ic]->SetMarkerStyle(24+ic);
       if(ic==0){ hPhiFakeRatio_30[1][ic]->SetMarkerColor(kViolet); hPhiFakeRatio_30[1][ic]->SetLineColor(kViolet);}
       if(ic==1){ hPhiFakeRatio_30[1][ic]->SetMarkerColor(kGreen+1); hPhiFakeRatio_30[1][ic]->SetLineColor(kGreen+1);}
       if(ic==2){ hPhiFakeRatio_30[1][ic]->SetMarkerColor(kRed); hPhiFakeRatio_30[1][ic]->SetLineColor(kRed);}
       if(ic==3){ hPhiFakeRatio_30[1][ic]->SetMarkerColor(kBlue); hPhiFakeRatio_30[1][ic]->SetLineColor(kBlue);}
       if(ic==4){ hPhiFakeRatio_30[1][ic]->SetMarkerColor(kPink);  hPhiFakeRatio_30[1][ic]->SetLineColor(kPink);}
       if(ic==5){ hPhiFakeRatio_30[1][ic]->SetMarkerColor(kYellow); hPhiFakeRatio_30[1][ic]->SetLineColor(kYellow);}
       if(ic==0){
         hBlankPhiRatio->SetTitle(Form(" %s, %s, jetID, pT>30 GeV/c |eta|<%.2f",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str(),ketacut));
         hBlankPhiRatio->GetXaxis()->SetTitle("Reco jet Phi");
         hBlankPhiRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankPhiRatio->Draw();
       }
       legPhi30->AddEntry(hPhiFakeRatio_30[1][ic],Form("%s",ccent[ic]),"p");
       hPhiFakeRatio_30[1][ic]->Draw("same");
    }
    legPhi30->Draw();    
    cPhi30->SaveAs(Form("ANPlots/FakePhiRate_30_%sMC_JetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
    TCanvas * cPhi40 = new TCanvas("cPhi40","",1200,1000);
    TLegend *legPhi40 = getLegend(0.5,0.5,0.7,0.9);
    legPhi40->SetHeader("");    
    for(int ic=0; ic<ncen-2; ic++){
       hPhiFakeRatio_40[1][ic]->SetMarkerStyle(24+ic);
       if(ic==0){ hPhiFakeRatio_40[1][ic]->SetMarkerColor(kViolet); hPhiFakeRatio_40[1][ic]->SetLineColor(kViolet);}
       if(ic==1){ hPhiFakeRatio_40[1][ic]->SetMarkerColor(kGreen+1); hPhiFakeRatio_40[1][ic]->SetLineColor(kGreen+1);}
       if(ic==2){ hPhiFakeRatio_40[1][ic]->SetMarkerColor(kRed); hPhiFakeRatio_40[1][ic]->SetLineColor(kRed);}
       if(ic==3){ hPhiFakeRatio_40[1][ic]->SetMarkerColor(kBlue); hPhiFakeRatio_40[1][ic]->SetLineColor(kBlue);}
       if(ic==4){ hPhiFakeRatio_40[1][ic]->SetMarkerColor(kPink);  hPhiFakeRatio_40[1][ic]->SetLineColor(kPink);}
       if(ic==5){ hPhiFakeRatio_40[1][ic]->SetMarkerColor(kYellow); hPhiFakeRatio_40[1][ic]->SetLineColor(kYellow);}
       if(ic==0){
         hBlankPhiRatio->SetTitle(Form(" %s, %s, jetID, pT>40 GeV/c |eta|<%.2f",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str(),ketacut));
         hBlankPhiRatio->GetXaxis()->SetTitle("Reco jet Phi");
         hBlankPhiRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankPhiRatio->Draw();
       }
       legPhi40->AddEntry(hPhiFakeRatio_40[1][ic],Form("%s",ccent[ic]),"p");
      hPhiFakeRatio_40[1][ic]->Draw("same");
    }
    legPhi40->Draw();
    cPhi40->SaveAs(Form("ANPlots/FakePhiRate_40_%sMC_JetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
    TCanvas * cPhi50 = new TCanvas("cPhi50","",1200,1000);
    TLegend *legPhi50 = getLegend(0.5,0.5,0.7,0.9);
    legPhi50->SetHeader("");   
    for(int ic=0; ic<ncen-2; ic++){
       hPhiFakeRatio_50[1][ic]->SetMarkerStyle(24+ic);
       if(ic==0){ hPhiFakeRatio_50[1][ic]->SetMarkerColor(kViolet); hPhiFakeRatio_50[1][ic]->SetLineColor(kViolet);}
       if(ic==1){ hPhiFakeRatio_50[1][ic]->SetMarkerColor(kGreen+1); hPhiFakeRatio_50[1][ic]->SetLineColor(kGreen+1);}
       if(ic==2){ hPhiFakeRatio_50[1][ic]->SetMarkerColor(kRed); hPhiFakeRatio_50[1][ic]->SetLineColor(kRed);}
       if(ic==3){ hPhiFakeRatio_50[1][ic]->SetMarkerColor(kBlue); hPhiFakeRatio_50[1][ic]->SetLineColor(kBlue);}
       if(ic==4){ hPhiFakeRatio_50[1][ic]->SetMarkerColor(kPink);  hPhiFakeRatio_50[1][ic]->SetLineColor(kPink);}
       if(ic==5){ hPhiFakeRatio_50[1][ic]->SetMarkerColor(kYellow); hPhiFakeRatio_50[1][ic]->SetLineColor(kYellow);}
       if(ic==0){
         hBlankPhiRatio->SetTitle(Form(" %s, %s, jetID, pT>50 GeV/c |eta|<%.2f",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str(),ketacut));
         hBlankPhiRatio->GetXaxis()->SetTitle("Reco jet Phi");
         hBlankPhiRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankPhiRatio->Draw();
       }
       legPhi50->AddEntry(hPhiFakeRatio_50[1][ic],Form("%s",ccent[ic]),"p");
       hPhiFakeRatio_50[1][ic]->Draw("same");
    }
    legPhi50->Draw();
    cPhi50->SaveAs(Form("ANPlots/FakePhiRate_50_%sMC_JetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
    TCanvas * cPhi60 = new TCanvas("cPhi60","",1200,1000);
    TLegend *legPhi60 = getLegend(0.5,0.5,0.7,0.9);
    legPhi60->SetHeader("");      
    for(int ic=0; ic<ncen-2; ic++){
       hPhiFakeRatio_60[1][ic]->SetMarkerStyle(24+ic);
       if(ic==0){ hPhiFakeRatio_60[1][ic]->SetMarkerColor(kViolet); hPhiFakeRatio_60[1][ic]->SetLineColor(kViolet);}
       if(ic==1){ hPhiFakeRatio_60[1][ic]->SetMarkerColor(kGreen+1); hPhiFakeRatio_60[1][ic]->SetLineColor(kGreen+1);}
       if(ic==2){ hPhiFakeRatio_60[1][ic]->SetMarkerColor(kRed); hPhiFakeRatio_60[1][ic]->SetLineColor(kRed);}
       if(ic==3){ hPhiFakeRatio_60[1][ic]->SetMarkerColor(kBlue); hPhiFakeRatio_60[1][ic]->SetLineColor(kBlue);}
       if(ic==4){ hPhiFakeRatio_60[1][ic]->SetMarkerColor(kPink);  hPhiFakeRatio_60[1][ic]->SetLineColor(kPink);}
       if(ic==5){ hPhiFakeRatio_60[1][ic]->SetMarkerColor(kYellow); hPhiFakeRatio_60[1][ic]->SetLineColor(kYellow);}
       if(ic==0){
         hBlankPhiRatio->SetTitle(Form(" %s, %s, jetID, pT>60 GeV/c |eta|<%.2f",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str(),ketacut));
         hBlankPhiRatio->GetXaxis()->SetTitle("Reco jet Phi");
         hBlankPhiRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankPhiRatio->Draw();
       }
       legPhi60->AddEntry(hPhiFakeRatio_60[1][ic],Form("%s",ccent[ic]),"p");
       hPhiFakeRatio_60[1][ic]->Draw("same");  
    }
    legPhi60->Draw();    
    cPhi60->SaveAs(Form("ANPlots/FakePhiRate_60_%sMC_JetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE"); 
    TCanvas * cPhi70 = new TCanvas("cPhi70","",1200,1000);
    TLegend *legPhi70 = getLegend(0.5,0.5,0.7,0.9);
    legPhi70->SetHeader("");      
    for(int ic=0; ic<ncen-2; ic++){
       hPhiFakeRatio_70[1][ic]->SetMarkerStyle(24+ic);
       if(ic==0){ hPhiFakeRatio_70[1][ic]->SetMarkerColor(kViolet); hPhiFakeRatio_70[1][ic]->SetLineColor(kViolet);}
       if(ic==1){ hPhiFakeRatio_70[1][ic]->SetMarkerColor(kGreen+1); hPhiFakeRatio_70[1][ic]->SetLineColor(kGreen+1);}
       if(ic==2){ hPhiFakeRatio_70[1][ic]->SetMarkerColor(kRed); hPhiFakeRatio_70[1][ic]->SetLineColor(kRed);}
       if(ic==3){ hPhiFakeRatio_70[1][ic]->SetMarkerColor(kBlue); hPhiFakeRatio_70[1][ic]->SetLineColor(kBlue);}
       if(ic==4){ hPhiFakeRatio_70[1][ic]->SetMarkerColor(kPink);  hPhiFakeRatio_70[1][ic]->SetLineColor(kPink);}
       if(ic==5){ hPhiFakeRatio_70[1][ic]->SetMarkerColor(kYellow); hPhiFakeRatio_70[1][ic]->SetLineColor(kYellow);}
       if(ic==0){
         hBlankPhiRatio->SetTitle(Form(" %s, %s, jetID, pT>70 GeV/c |eta|<%.2f",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str(),ketacut));
         hBlankPhiRatio->GetXaxis()->SetTitle("Reco jet Phi");
         hBlankPhiRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankPhiRatio->Draw();
       }
       legPhi70->AddEntry(hPhiFakeRatio_70[1][ic],Form("%s",ccent[ic]),"p");
       hPhiFakeRatio_70[1][ic]->Draw("same");  
    }
    legPhi70->Draw();    
    cPhi70->SaveAs(Form("ANPlots/FakePhiRate_70_%sMC_JetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE"); 
     TCanvas * cPhi80 = new TCanvas("cPhi80","",1200,1000);
    TLegend *legPhi80 = getLegend(0.5,0.5,0.7,0.9);
    legPhi80->SetHeader("");      
    for(int ic=0; ic<ncen-2; ic++){
       hPhiFakeRatio_80[1][ic]->SetMarkerStyle(24+ic);
       if(ic==0){ hPhiFakeRatio_80[1][ic]->SetMarkerColor(kViolet); hPhiFakeRatio_80[1][ic]->SetLineColor(kViolet);}
       if(ic==1){ hPhiFakeRatio_80[1][ic]->SetMarkerColor(kGreen+1); hPhiFakeRatio_80[1][ic]->SetLineColor(kGreen+1);}
       if(ic==2){ hPhiFakeRatio_80[1][ic]->SetMarkerColor(kRed); hPhiFakeRatio_80[1][ic]->SetLineColor(kRed);}
       if(ic==3){ hPhiFakeRatio_80[1][ic]->SetMarkerColor(kBlue); hPhiFakeRatio_80[1][ic]->SetLineColor(kBlue);}
       if(ic==4){ hPhiFakeRatio_80[1][ic]->SetMarkerColor(kPink);  hPhiFakeRatio_80[1][ic]->SetLineColor(kPink);}
       if(ic==5){ hPhiFakeRatio_80[1][ic]->SetMarkerColor(kYellow); hPhiFakeRatio_80[1][ic]->SetLineColor(kYellow);}
       if(ic==0){
         hBlankPhiRatio->SetTitle(Form(" %s, %s, jetID, pT>80 GeV/c |eta|<%.2f",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str(),ketacut));
         hBlankPhiRatio->GetXaxis()->SetTitle("Reco jet Phi");
         hBlankPhiRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankPhiRatio->Draw();
       }
       legPhi80->AddEntry(hPhiFakeRatio_80[1][ic],Form("%s",ccent[ic]),"p");
       hPhiFakeRatio_80[1][ic]->Draw("same");  
    }
    legPhi80->Draw();    
    cPhi80->SaveAs(Form("ANPlots/FakePhiRate_80_%sMC_JetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE"); 
            
    TCanvas * cpT = new TCanvas("cpT","",1200,1000);
    TLegend *legpT = getLegend(0.5,0.5,0.7,0.9);
    legpT->SetHeader("");   
    for(int ic=0; ic<ncen-2; ic++){
       hPtFakeRatio[1][ic]->SetMarkerStyle(24+ic);
       if(ic==0){ hPtFakeRatio[1][ic]->SetMarkerColor(kViolet); hPtFakeRatio[1][ic]->SetLineColor(kViolet);}
       if(ic==1){ hPtFakeRatio[1][ic]->SetMarkerColor(kGreen+1); hPtFakeRatio[1][ic]->SetLineColor(kGreen+1);}
       if(ic==2){ hPtFakeRatio[1][ic]->SetMarkerColor(kRed); hPtFakeRatio[1][ic]->SetLineColor(kRed);}
       if(ic==3){ hPtFakeRatio[1][ic]->SetMarkerColor(kBlue); hPtFakeRatio[1][ic]->SetLineColor(kBlue);}
       if(ic==4){ hPtFakeRatio[1][ic]->SetMarkerColor(kPink);  hPtFakeRatio[1][ic]->SetLineColor(kPink);}
       if(ic==5){ hPtFakeRatio[1][ic]->SetMarkerColor(kYellow); hPtFakeRatio[1][ic]->SetLineColor(kYellow);}
       if(ic==0){
         hBlankPt->SetTitle(Form(" %s, %s, jetID",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankPt->GetXaxis()->SetTitle(Form("Reco jet pT (GeV/c) |eta|<%.2f",ketacut));
         hBlankPt->GetYaxis()->SetTitle("Fake rate");
         hBlankPt->Draw();
       }
       legpT->AddEntry(hPtFakeRatio[1][ic],Form("%s",ccent[ic]),"p");
       hPtFakeRatio[1][ic]->Draw("same");
    }
    legpT->Draw();    
     cpT->SaveAs(Form("ANPlots/FakeRatepT_%sMC_JetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
     
    TCanvas * cpT_etabin = new TCanvas("cpT_etabin","",1200,1000);
    TLegend *legpT_etabin = getLegend(0.5,0.5,0.7,0.9);
    legpT_etabin->SetHeader("");   
    for(int ic=0; ic<ncen-2; ic++){
       hPtFakeRatio_etabin[1][ic][0]->SetMarkerStyle(24+ic);
       if(ic==0){ hPtFakeRatio_etabin[1][ic][0]->SetMarkerColor(kViolet); hPtFakeRatio_etabin[1][ic][0]->SetLineColor(kViolet);}
       if(ic==1){ hPtFakeRatio_etabin[1][ic][0]->SetMarkerColor(kGreen+1); hPtFakeRatio_etabin[1][ic][0]->SetLineColor(kGreen+1);}
       if(ic==2){ hPtFakeRatio_etabin[1][ic][0]->SetMarkerColor(kRed); hPtFakeRatio_etabin[1][ic][0]->SetLineColor(kRed);}
       if(ic==3){ hPtFakeRatio_etabin[1][ic][0]->SetMarkerColor(kBlue); hPtFakeRatio_etabin[1][ic][0]->SetLineColor(kBlue);}
       if(ic==4){ hPtFakeRatio_etabin[1][ic][0]->SetMarkerColor(kPink);  hPtFakeRatio_etabin[1][ic][0]->SetLineColor(kPink);}
       if(ic==5){ hPtFakeRatio_etabin[1][ic][0]->SetMarkerColor(kYellow); hPtFakeRatio_etabin[1][ic][0]->SetLineColor(kYellow);}
       if(ic==0){
         hBlankPt->SetTitle(Form(" %s, %s, jetID",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankPt->GetXaxis()->SetTitle(Form("Reco jet pT (GeV/c) %s",seta[0]));
         hBlankPt->GetYaxis()->SetTitle("Fake rate");
         hBlankPt->Draw();
       }
       legpT_etabin->AddEntry(hPtFakeRatio_etabin[1][ic][0],Form("%s",ccent[ic]),"p");
       hPtFakeRatio_etabin[1][ic][0]->Draw("same");
    }
    legpT_etabin->Draw();    
     cpT_etabin->SaveAs(Form("ANPlots/FakeRatepT_etabin%d_%sMC_JetID_%s_%d.pdf",0,kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
     
    TCanvas * cpT_eff_etabin = new TCanvas("cpT_eff_etabin","",1200,1000);
    TLegend *legpT_eff_etabin = getLegend(0.5,0.5,0.3,0.7);
    legpT_eff_etabin->SetHeader("");   
    for(int ic=0; ic<ncen-2; ic++){
       hPtEffRatio_etabin[0][ic][0]->SetMarkerStyle(24+ic);
       if(ic==0){ hPtEffRatio_etabin[0][ic][0]->SetMarkerColor(kViolet); hPtEffRatio_etabin[0][ic][0]->SetLineColor(kViolet);}
       if(ic==1){ hPtEffRatio_etabin[0][ic][0]->SetMarkerColor(kGreen+1); hPtEffRatio_etabin[0][ic][0]->SetLineColor(kGreen+1);}
       if(ic==2){ hPtEffRatio_etabin[0][ic][0]->SetMarkerColor(kRed); hPtEffRatio_etabin[0][ic][0]->SetLineColor(kRed);}
       if(ic==3){ hPtEffRatio_etabin[0][ic][0]->SetMarkerColor(kBlue); hPtEffRatio_etabin[0][ic][0]->SetLineColor(kBlue);}
       if(ic==4){ hPtEffRatio_etabin[0][ic][0]->SetMarkerColor(kPink);  hPtEffRatio_etabin[0][ic][0]->SetLineColor(kPink);}
       if(ic==5){ hPtEffRatio_etabin[0][ic][0]->SetMarkerColor(kYellow); hPtEffRatio_etabin[0][ic][0]->SetLineColor(kYellow);}
       if(ic==0){
         hBlankPtEff->SetTitle(Form(" %s, %s",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankPtEff->GetXaxis()->SetTitle(Form("Reco jet pT (GeV/c) %s",seta[0]));
         hBlankPtEff->GetYaxis()->SetTitle("Efficiency");
         hBlankPtEff->Draw();
       }
       legpT_eff_etabin->AddEntry(hPtEffRatio_etabin[0][ic][0],Form("%s",ccent[ic]),"p");
       hPtEffRatio_etabin[0][ic][0]->Draw("same");
    }
    legpT_eff_etabin->Draw();    
     cpT_eff_etabin->SaveAs(Form("ANPlots/EfficiencypT_eff_etabin%d_%sMC_noJetID_%s_%d.pdf",0,kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");

    TCanvas * cpT_eff = new TCanvas("cpT_eff","",1200,1000);
    TLegend *legpT_eff = getLegend(0.5,0.5,0.3,0.7);
    legpT_eff->SetHeader("");   
    for(int ic=0; ic<ncen-2; ic++){
       hPtEffRatio[0][ic]->SetMarkerStyle(24+ic);
       if(ic==0){ hPtEffRatio[0][ic]->SetMarkerColor(kViolet); hPtEffRatio[0][ic]->SetLineColor(kViolet);}
       if(ic==1){ hPtEffRatio[0][ic]->SetMarkerColor(kGreen+1); hPtEffRatio[0][ic]->SetLineColor(kGreen+1);}
       if(ic==2){ hPtEffRatio[0][ic]->SetMarkerColor(kRed); hPtEffRatio[0][ic]->SetLineColor(kRed);}
       if(ic==3){ hPtEffRatio[0][ic]->SetMarkerColor(kBlue); hPtEffRatio[0][ic]->SetLineColor(kBlue);}
       if(ic==4){ hPtEffRatio[0][ic]->SetMarkerColor(kPink);  hPtEffRatio[0][ic]->SetLineColor(kPink);}
       if(ic==5){ hPtEffRatio[0][ic]->SetMarkerColor(kYellow); hPtEffRatio[0][ic]->SetLineColor(kYellow);}
       if(ic==0){
         hBlankPtEff->SetTitle(Form(" %s, %s",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankPtEff->GetXaxis()->SetTitle(Form("Reco jet pT (GeV/c) |eta|<%.2f",ketacut));
         hBlankPtEff->GetYaxis()->SetTitle("Efficiency");
         hBlankPtEff->Draw();
       }
       legpT_eff->AddEntry(hPtEffRatio[0][ic],Form("%s",ccent[ic]),"p");
       hPtEffRatio[0][ic]->Draw("same");
    }
    legpT_eff->Draw();    
     cpT_eff->SaveAs(Form("ANPlots/EfficiencypT_etaLt2_%sMC_noJetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");

    } // end nj loop (radius)
    
} // end program