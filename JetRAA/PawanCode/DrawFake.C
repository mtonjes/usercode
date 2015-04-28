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

const double etabins[] = {-2.000, -1.4000, -0.4500, 0.000, 0.4500, 1.400, 2.000};
const int neta = sizeof(etabins)/sizeof(double) - 1;

const double phibins[] = {-3.141,-2.100,-1.500,-0.800,-0.300,0.300,0.800,1.500,2.100,3.141};
const int nphi = sizeof(phibins)/sizeof(double) - 1;

const int knj=3;
std::string srad[knj] = {"2", "3", "4"};

TStopwatch timer;

void DrawFake(std::string kSpecies="PbPb"){
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

    TH1F *hPtAll [ncen], *hPtEff [2][ncen];
    TH1F *hPtFakeAll[ncen], *hPtFake[2][ncen];
    TH1F *hPtFakeRatio[2][ncen];
    TH1F *hPtAll_etalt1pt6[ncen], *hPtEff_etalt1pt6[2][ncen];
    TH1F *hPtFakeAll_etalt1pt6[ncen], *hPtFake_etalt1pt6[2][ncen];
    TH1F *hPtFakeRatio_etalt1pt6[2][ncen];    
    TH1F *hEtaFakeAll_20[ncen],*hEtaFakeAll_30[ncen], *hEtaFakeAll_40[ncen],*hEtaFakeAll_45[ncen], *hEtaFakeAll_50[ncen], *hEtaFakeAll_60[ncen];
    TH1F *hPhiFakeAll_20[ncen],*hPhiFakeAll_30[ncen], *hPhiFakeAll_40[ncen],*hPhiFakeAll_45[ncen], *hPhiFakeAll_50[ncen], *hPhiFakeAll_60[ncen];
    TH1F *hEtaFake_20[2][ncen],*hEtaFake_30[2][ncen], *hEtaFake_40[2][ncen],*hEtaFake_45[2][ncen], *hEtaFake_50[2][ncen], *hEtaFake_60[2][ncen];
    TH1F *hPhiFake_20[2][ncen],*hPhiFake_30[2][ncen], *hPhiFake_40[2][ncen],*hPhiFake_45[2][ncen], *hPhiFake_50[2][ncen], *hPhiFake_60[2][ncen];  
    TH1F *hEtaFakeRatio_20[2][ncen],*hEtaFakeRatio_30[2][ncen], *hEtaFakeRatio_40[2][ncen],*hEtaFakeRatio_45[2][ncen], *hEtaFakeRatio_50[2][ncen], *hEtaFakeRatio_60[2][ncen];
    TH1F *hPhiFakeRatio_20[2][ncen],*hPhiFakeRatio_30[2][ncen], *hPhiFakeRatio_40[2][ncen],*hPhiFakeRatio_45[2][ncen], *hPhiFakeRatio_50[2][ncen], *hPhiFakeRatio_60[2][ncen];

  TFile *fin = new TFile(Form("Histos/OutputHist_ntuples_%s.root",kSpecies.c_str()),"r");
// radius loop
    for(int nj=0; nj<knj; nj++){
    // i is the with or without jetID loop, NOT the nj loop! 0 == no JetID, 1== JetID
     for(int i=0; i<2; i++){
 // centrality loop    
      for(int ic=0; ic<ncen; ic++){
    	if(i==0){
     	  hPtAll[ic] = (TH1F*)fin->Get(Form("hPtAll_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic));
     	  hPtAll[ic]->Print("base");
     	  hPtFakeAll[ic] = (TH1F*)fin->Get(Form("hPtFakeAll_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
     	  hPtFakeAll[ic]->Print("base");
     	  hPtFakeAll_etalt1pt6[ic] = (TH1F*)fin->Get(Form("hPtFakeAll_etalt1pt6_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
     	  hPtFakeAll_etalt1pt6[ic]->Print("base");    	  
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
    	}
    	// end if i=0 (no jetID)
     	hPtEff[i][ic] = (TH1F*)fin->Get(Form("hPtEff_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
     	hPtEff[i][ic]->Print("base");
    	hPtFake[i][ic] = (TH1F*)fin->Get(Form("hPtFake_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
        hPtFake[i][ic]->Print("base");
     	hPtEff_etalt1pt6[i][ic] = (TH1F*)fin->Get(Form("hPtEff_etalt1pt6_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
     	hPtEff_etalt1pt6[i][ic]->Print("base");
    	hPtFake_etalt1pt6[i][ic] = (TH1F*)fin->Get(Form("hPtFake_etalt1pt6_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
        hPtFake_etalt1pt6[i][ic]->Print("base");
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
    	hPtFakeRatio[i][ic]=(TH1F*)hPtFake[i][ic]->Clone(Form("hPtFakeRatio_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hPtFakeRatio[i][ic]->Divide(hPtFakeAll[ic]);    
    	hPtFakeRatio[i][ic]->SetMarkerSize(2.5);	
    	hPtFakeRatio_etalt1pt6[i][ic]=(TH1F*)hPtFake_etalt1pt6[i][ic]->Clone(Form("hPtFakeRatio_etalt1pt6_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hPtFakeRatio_etalt1pt6[i][ic]->Divide(hPtFakeAll_etalt1pt6[ic]);    
    	hPtFakeRatio_etalt1pt6[i][ic]->SetMarkerSize(2.5);	
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
         hBlankRatio->SetTitle(Form(" %s, %s, jetID, pT>30 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
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
         hBlankRatio->SetTitle(Form(" %s, %s, jetID, pT>40 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
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
         hBlankRatio->SetTitle(Form(" %s, %s, jetID, pT>50 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
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
         hBlankRatio->SetTitle(Form(" %s, %s, jetID, pT>60 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankRatio->GetXaxis()->SetTitle("Reco jet eta");
         hBlankRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankRatio->Draw();
       }
       leg60->AddEntry(hEtaFakeRatio_60[1][ic],Form("%s",ccent[ic]),"p");
       hEtaFakeRatio_60[1][ic]->Draw("same");  
    }
    leg60->Draw();    
    c60->SaveAs(Form("ANPlots/FakeEtaRate_60_%sMC_JetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");    
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
         hBlankPhiRatio->SetTitle(Form(" %s, %s, jetID, pT>30 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
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
         hBlankPhiRatio->SetTitle(Form(" %s, %s, jetID, pT>40 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
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
         hBlankPhiRatio->SetTitle(Form(" %s, %s, jetID, pT>50 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
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
         hBlankPhiRatio->SetTitle(Form(" %s, %s, jetID, pT>60 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankPhiRatio->GetXaxis()->SetTitle("Reco jet Phi");
         hBlankPhiRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankPhiRatio->Draw();
       }
       legPhi60->AddEntry(hPhiFakeRatio_60[1][ic],Form("%s",ccent[ic]),"p");
       hPhiFakeRatio_60[1][ic]->Draw("same");  
    }
    legPhi60->Draw();    
    cPhi60->SaveAs(Form("ANPlots/FakePhiRate_60_%sMC_JetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE"); 
         
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
         hBlankPt->GetXaxis()->SetTitle("Reco jet pT (GeV/c)");
         hBlankPt->GetYaxis()->SetTitle("Fake rate");
         hBlankPt->Draw();
       }
       legpT->AddEntry(hPtFakeRatio[1][ic],Form("%s",ccent[ic]),"p");
       hPtFakeRatio[1][ic]->Draw("same");
    }
    legpT->Draw();    
     cpT->SaveAs(Form("ANPlots/FakeRatepT_%sMC_JetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
    TCanvas * cpT_etalt1pt6 = new TCanvas("cpT_etalt1pt6","",1200,1000);
    TLegend *legpT_etalt1pt6 = getLegend(0.5,0.5,0.7,0.9);
    legpT_etalt1pt6->SetHeader("");   
    for(int ic=0; ic<ncen-2; ic++){
       hPtFakeRatio_etalt1pt6[1][ic]->SetMarkerStyle(24+ic);
       if(ic==0){ hPtFakeRatio_etalt1pt6[1][ic]->SetMarkerColor(kViolet); hPtFakeRatio[1][ic]->SetLineColor(kViolet);}
       if(ic==1){ hPtFakeRatio_etalt1pt6[1][ic]->SetMarkerColor(kGreen+1); hPtFakeRatio[1][ic]->SetLineColor(kGreen+1);}
       if(ic==2){ hPtFakeRatio_etalt1pt6[1][ic]->SetMarkerColor(kRed); hPtFakeRatio[1][ic]->SetLineColor(kRed);}
       if(ic==3){ hPtFakeRatio_etalt1pt6[1][ic]->SetMarkerColor(kBlue); hPtFakeRatio[1][ic]->SetLineColor(kBlue);}
       if(ic==4){ hPtFakeRatio_etalt1pt6[1][ic]->SetMarkerColor(kPink);  hPtFakeRatio[1][ic]->SetLineColor(kPink);}
       if(ic==5){ hPtFakeRatio_etalt1pt6[1][ic]->SetMarkerColor(kYellow); hPtFakeRatio[1][ic]->SetLineColor(kYellow);}
       if(ic==0){
         hBlankPt->SetTitle(Form(" %s, %s, jetID",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankPt->GetXaxis()->SetTitle("Reco jet pT (GeV/c) (|eta|<1.6)");
         hBlankPt->GetYaxis()->SetTitle("Fake rate");
         hBlankPt->Draw();
       }
       legpT_etalt1pt6->AddEntry(hPtFakeRatio_etalt1pt6[1][ic],Form("%s",ccent[ic]),"p");
       hPtFakeRatio_etalt1pt6[1][ic]->Draw("same");
    }
    legpT_etalt1pt6->Draw();    
     cpT_etalt1pt6->SaveAs(Form("ANPlots/FakeRatepT_etalt1pt6_%sMC_JetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
    } // end nj loop (radius)
    
} // end program