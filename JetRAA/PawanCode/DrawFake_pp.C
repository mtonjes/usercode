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
const char *ccent[ncen] = {"0-5%","5-10%","10-30%","30-50%","50-70%","70-90%","90-100%","pp"};

const double etabins[] = {-2.000, -1.4000, -0.4500, 0.000, 0.4500, 1.400, 2.000};
const int neta = sizeof(etabins)/sizeof(double) - 1;

const double phibins[] = {-3.141,-2.100,-1.500,-0.800,-0.300,0.300,0.800,1.500,2.100,3.141};
const int nphi = sizeof(phibins)/sizeof(double) - 1;

const int knj=3;
std::string srad[knj] = {"2", "3", "4"};

TStopwatch timer;

void DrawFake_pp(std::string kSpecies="pp"){
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
  TH2F * hBlankRatio = new TH2F("hBlankRatio","",20,-2.1,2.1,50,0,0.1);
  TH2F * hBlankPhiRatio = new TH2F("hBlankPhiRatio","",20,-pi,pi,50,0,0.1);
  TH2F * hBlankPt= new TH2F("hBlankPt","",50,20,350,50,0,0.1);
  int ic=7;

    TH1F *hPtAll , *hPtEff [2];
    TH1F *hPtFakeAll, *hPtFake[2];
    TH1F *hPtFakeRatio[2];
//     TH1F *hPtAll_etalt1pt6, *hPtEff_etalt1pt6[2];
//     TH1F *hPtFakeAll_etalt1pt6, *hPtFake_etalt1pt6[2];
//     TH1F *hPtFakeRatio_etalt1pt6[2];    
    TH1F *hEtaFakeAll_20,*hEtaFakeAll_30, *hEtaFakeAll_40,*hEtaFakeAll_45, *hEtaFakeAll_50, *hEtaFakeAll_60;
    TH1F *hPhiFakeAll_20,*hPhiFakeAll_30, *hPhiFakeAll_40,*hPhiFakeAll_45, *hPhiFakeAll_50, *hPhiFakeAll_60;
    TH1F *hEtaFake_20[2],*hEtaFake_30[2], *hEtaFake_40[2],*hEtaFake_45[2], *hEtaFake_50[2], *hEtaFake_60[2];
    TH1F *hPhiFake_20[2],*hPhiFake_30[2], *hPhiFake_40[2],*hPhiFake_45[2], *hPhiFake_50[2], *hPhiFake_60[2];  
    TH1F *hEtaFakeRatio_20[2],*hEtaFakeRatio_30[2], *hEtaFakeRatio_40[2],*hEtaFakeRatio_45[2], *hEtaFakeRatio_50[2], *hEtaFakeRatio_60[2];
    TH1F *hPhiFakeRatio_20[2],*hPhiFakeRatio_30[2], *hPhiFakeRatio_40[2],*hPhiFakeRatio_45[2], *hPhiFakeRatio_50[2], *hPhiFakeRatio_60[2];

  TFile *fin = new TFile(Form("Histos/OutputHist_ntuples_%s.root",kSpecies.c_str()),"r");
// radius loop
    for(int nj=0; nj<knj; nj++){
    // i is the with or without jetID loop, NOT the nj loop! 0 == no JetID, 1== JetID
     for(int i=0; i<2; i++){
 // centrality loop    
//      for(int ic=0; ic<ncen; ic++){
 //      int ic=7;
    	if(i==0){
     	  hPtAll = (TH1F*)fin->Get(Form("hPtAll_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic));
     	  hPtAll->Print("base");
//      	  hEtaAll = (TH1F*)fin->Get(Form("hEtaAll_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
//      	  hEtaAll->Print("base");
//      	  hPhiAll = (TH1F*)fin->Get(Form("hPhiAll_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic));
//      	  hPhiAll->Print("base"); 
     	  hPtFakeAll = (TH1F*)fin->Get(Form("hPtFakeAll_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
     	  hPtFakeAll->Print("base");
    	  hEtaFakeAll_20 = (TH1F*)fin->Get(Form("hEtaFakeAll_20_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
    	  hEtaFakeAll_20->Print("base");
    	  hPhiFakeAll_20 = (TH1F*)fin->Get(Form("hPhiFakeAll_20_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
          hPhiFakeAll_20->Print("base");
    	  hEtaFakeAll_30 = (TH1F*)fin->Get(Form("hEtaFakeAll_30_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
    	  hEtaFakeAll_30->Print("base");
    	  hPhiFakeAll_30 = (TH1F*)fin->Get(Form("hPhiFakeAll_30_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
          hPhiFakeAll_30->Print("base");
    	  hEtaFakeAll_40 = (TH1F*)fin->Get(Form("hEtaFakeAll_40_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
    	  hEtaFakeAll_40->Print("base");
    	  hPhiFakeAll_40 = (TH1F*)fin->Get(Form("hPhiFakeAll_40_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
          hPhiFakeAll_40->Print("base");
    	  hEtaFakeAll_45 = (TH1F*)fin->Get(Form("hEtaFakeAll_45_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
    	  hEtaFakeAll_45 ->Print("base");
    	  hPhiFakeAll_45 = (TH1F*)fin->Get(Form("hPhiFakeAll_45_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
          hPhiFakeAll_45->Print("base");
    	  hEtaFakeAll_50 = (TH1F*)fin->Get(Form("hEtaFakeAll_50_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic));
    	  hEtaFakeAll_50->Print("base"); 
    	  hPhiFakeAll_50 = (TH1F*)fin->Get(Form("hPhiFakeAll_50_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
    	  hPhiFakeAll_50->Print("base"); 
    	  hEtaFakeAll_60 = (TH1F*)fin->Get(Form("hEtaFakeAll_60_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
    	  hEtaFakeAll_60->Print("base");
    	  hPhiFakeAll_60 = (TH1F*)fin->Get(Form("hPhiFakeAll_60_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic)); 
          hPhiFakeAll_60->Print("base");
    	}
    	// end if i=0 (no jetID)
     	hPtEff[i] = (TH1F*)fin->Get(Form("hPtEff_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
     	hPtEff[i]->Print("base");
//     	hEtaEff[i] = (TH1F*)fin->Get(Form("hEtaEff_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
//     	hEtaEff[i]->Print("base");
//     	hPhiEff[i] = (TH1F*)fin->Get(Form("hPhiEff_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
//         hPhiEff[i]->Print("base");
    	hPtFake[i] = (TH1F*)fin->Get(Form("hPtFake_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
        hPtFake[i]->Print("base");
    	hEtaFake_20[i] = (TH1F*)fin->Get(Form("hEtaFake_20_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
    	hEtaFake_20[i]->Print("base");
    	hPhiFake_20[i] = (TH1F*)fin->Get(Form("hPhiFake_20_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
        hPhiFake_20[i]->Print("base");
    	hEtaFake_30[i] = (TH1F*)fin->Get(Form("hEtaFake_30_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
    	hEtaFake_30[i]->Print("base");
    	hPhiFake_30[i] = (TH1F*)fin->Get(Form("hPhiFake_30_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
        hPhiFake_30[i]->Print("base");
    	hEtaFake_40[i] = (TH1F*)fin->Get(Form("hEtaFake_40_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
    	hEtaFake_40[i]->Print("base");
    	hPhiFake_40[i] = (TH1F*)fin->Get(Form("hPhiFake_40_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
        hPhiFake_40[i]->Print("base");
    	hEtaFake_45[i] = (TH1F*)fin->Get(Form("hEtaFake_45_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
    	hEtaFake_45[i]->Print("base");
    	hPhiFake_45[i] = (TH1F*)fin->Get(Form("hPhiFake_45_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
        hPhiFake_45[i]->Print("base");
    	hEtaFake_50[i] = (TH1F*)fin->Get(Form("hEtaFake_50_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
    	hEtaFake_50[i]->Print("base");
    	hPhiFake_50[i] = (TH1F*)fin->Get(Form("hPhiFake_50_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
   	    hPhiFake_50[i]->Print("base");
    	hEtaFake_60[i] = (TH1F*)fin->Get(Form("hEtaFake_60_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
    	hEtaFake_60[i]->Print("base");
//     	hEtaFake_60[i]->Draw();   	
    	hPhiFake_60[i] = (TH1F*)fin->Get(Form("hPhiFake_60_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic)); 
    	hPhiFake_60[i]->Print("base");
    	hEtaFakeRatio_20[i]=(TH1F*)hEtaFake_20[i]->Clone(Form("hEtaFakeRatio_20_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hEtaFakeRatio_20[i]->Divide(hEtaFakeAll_20);
    	hEtaFakeRatio_30[i]=(TH1F*)hEtaFake_30[i]->Clone(Form("hEtaFakeRatio_30_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hEtaFakeRatio_30[i]->Divide(hEtaFakeAll_30);
    	hEtaFakeRatio_30[i]->SetMarkerSize(2.5);
    	hEtaFakeRatio_40[i]=(TH1F*)hEtaFake_40[i]->Clone(Form("hEtaFakeRatio_40_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hEtaFakeRatio_40[i]->Divide(hEtaFakeAll_40);
    	hEtaFakeRatio_40[i]->SetMarkerSize(2.5);
    	hEtaFakeRatio_45[i]=(TH1F*)hEtaFake_45[i]->Clone(Form("hEtaFakeRatio_45_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hEtaFakeRatio_45[i]->Divide(hEtaFakeAll_45);
    	hEtaFakeRatio_50[i]=(TH1F*)hEtaFake_50[i]->Clone(Form("hEtaFakeRatio_50_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hEtaFakeRatio_50[i]->Divide(hEtaFakeAll_50);
    	hEtaFakeRatio_50[i]->SetMarkerSize(2.5);
    	hEtaFakeRatio_60[i]=(TH1F*)hEtaFake_60[i]->Clone(Form("hEtaFakeRatio_60_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hEtaFakeRatio_60[i]->Divide(hEtaFakeAll_60);
    	hEtaFakeRatio_60[i]->SetMarkerSize(2.5);
     	hPhiFakeRatio_20[i]=(TH1F*)hPhiFake_20[i]->Clone(Form("hPhiFakeRatio_20_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hPhiFakeRatio_20[i]->Divide(hPhiFakeAll_20);
    	hPhiFakeRatio_30[i]=(TH1F*)hPhiFake_30[i]->Clone(Form("hPhiFakeRatio_30_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hPhiFakeRatio_30[i]->Divide(hPhiFakeAll_30);
    	hPhiFakeRatio_30[i]->SetMarkerSize(2.5);
    	hPhiFakeRatio_40[i]=(TH1F*)hPhiFake_40[i]->Clone(Form("hPhiFakeRatio_40_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hPhiFakeRatio_40[i]->Divide(hPhiFakeAll_40);
    	hPhiFakeRatio_40[i]->SetMarkerSize(2.5);
    	hPhiFakeRatio_45[i]=(TH1F*)hPhiFake_45[i]->Clone(Form("hPhiFakeRatio_45_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hPhiFakeRatio_45[i]->Divide(hPhiFakeAll_45);
    	hPhiFakeRatio_50[i]=(TH1F*)hPhiFake_50[i]->Clone(Form("hPhiFakeRatio_50_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hPhiFakeRatio_50[i]->Divide(hPhiFakeAll_50);
    	hPhiFakeRatio_50[i]->SetMarkerSize(2.5);
    	hPhiFakeRatio_60[i]=(TH1F*)hPhiFake_60[i]->Clone(Form("hPhiFakeRatio_60_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hPhiFakeRatio_60[i]->Divide(hPhiFakeAll_60);
    	hPhiFakeRatio_60[i]->SetMarkerSize(2.5);
    	hPtFakeRatio[i]=(TH1F*)hPtFake[i]->Clone(Form("hPtFakeRatio_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic));
    	hPtFakeRatio[i]->Divide(hPtFakeAll);    
    	hPtFakeRatio[i]->SetMarkerSize(2.5);	
//       }
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
    TCanvas * c30 = new TCanvas("c30","",800,800);
    TLegend *leg30 = getLegend(0.5,0.5,0.7,0.9);
    leg30->SetHeader("");   
//    int ic=7;
       hEtaFakeRatio_30[1]->SetMarkerColor(kGray); 
       hEtaFakeRatio_30[1]->SetLineColor(kGray);
       hEtaFakeRatio_30[1]->SetMarkerStyle(20);
 //      if(ic==0){
         hBlankRatio->SetTitle(Form(" %s, %s, jetID, pT>30 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankRatio->GetXaxis()->SetTitle("Reco jet eta");
         hBlankRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankRatio->Draw();
  //     }
       leg30->AddEntry(hEtaFakeRatio_30[1],Form("%s",ccent[ic]),"p");
       hEtaFakeRatio_30[1]->Draw("same");
//    }
    leg30->Draw();    
     c30->SaveAs(Form("ANPlots/FakeEtaRate_30_%sMC_JetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
//          hBlankRatio->SetTitle(Form(" %s, pp (PYTHIA), jetID, pT>30 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str()));
//          hBlankRatio->GetXaxis()->SetTitle("Reco jet eta");
//          hBlankRatio->GetYaxis()->SetTitle("Fake rate");
//          hBlankRatio->Draw(); 
//          leg30->AddEntry(hEtaFakeRatio_30[1][7],Form("%s",ccent[7]),"p"); 
//          hEtaFakeRatio_30[1][7]->Draw("same"); 
//     c30->SaveAs(Form("ANPlots/FakeEtaRate_30_ppMC_JetID_%s_%d.pdf",(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
    
    TCanvas * c40 = new TCanvas("c40","",800,800);
    TLegend *leg40 = getLegend(0.5,0.5,0.7,0.9);
    leg40->SetHeader("");    
  //  int ic=7;
       hEtaFakeRatio_40[1]->SetMarkerStyle(20);
       hEtaFakeRatio_40[1]->SetMarkerColor(kGray); 
       hEtaFakeRatio_40[1]->SetLineColor(kGray);  
//       if(ic==0){
         hBlankRatio->SetTitle(Form(" %s, %s, jetID, pT>40 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankRatio->GetXaxis()->SetTitle("Reco jet eta");
         hBlankRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankRatio->Draw();
//       }
       leg40->AddEntry(hEtaFakeRatio_40[1],Form("%s",ccent[ic]),"p");
      hEtaFakeRatio_40[1]->Draw("same");
 //   }
    leg40->Draw();
    c40->SaveAs(Form("ANPlots/FakeEtaRate_40_%sMC_JetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
//          hBlankRatio->SetTitle(Form(" %s, pp (PYTHIA), jetID, pT>40 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str()));
//          hBlankRatio->GetXaxis()->SetTitle("Reco jet eta");
//          hBlankRatio->GetYaxis()->SetTitle("Fake rate");
//          hBlankRatio->Draw(); 
//          leg40->AddEntry(hEtaFakeRatio_40[1][7],Form("%s",ccent[7]),"p"); 
//          hEtaFakeRatio_40[1][7]->Draw("same"); 
//     c40->SaveAs(Form("ANPlots/FakeEtaRate_40_ppMC_JetID_%s_%d.pdf",(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
    
    TCanvas * c50 = new TCanvas("c50","",800,800);
    TLegend *leg50 = getLegend(0.5,0.5,0.7,0.9);
    leg50->SetHeader("");   
  //  int ic=7;
       hEtaFakeRatio_50[1]->SetMarkerStyle(20);
       hEtaFakeRatio_50[1]->SetMarkerColor(kGray); 
       hEtaFakeRatio_50[1]->SetLineColor(kGray);
 //      if(ic==0){
         hBlankRatio->SetTitle(Form(" %s, %s, jetID, pT>50 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankRatio->GetXaxis()->SetTitle("Reco jet eta");
         hBlankRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankRatio->Draw();
//       }
       leg50->AddEntry(hEtaFakeRatio_50[1],Form("%s",ccent[ic]),"p");
       hEtaFakeRatio_50[1]->Draw("same");
//    }
    leg50->Draw();
    c50->SaveAs(Form("ANPlots/FakeEtaRate_50_%sMC_JetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
//          hBlankRatio->SetTitle(Form(" %s, pp (PYTHIA), jetID, pT>50 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str()));
//          hBlankRatio->GetXaxis()->SetTitle("Reco jet eta");
//          hBlankRatio->GetYaxis()->SetTitle("Fake rate");
//          hBlankRatio->Draw(); 
//          leg50->AddEntry(hEtaFakeRatio_50[1][7],Form("%s",ccent[7]),"p"); 
//          hEtaFakeRatio_50[1][7]->Draw("same"); 
//     c50->SaveAs(Form("ANPlots/FakeEtaRate_50_ppMC_JetID_%s_%d.pdf",(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");

    TCanvas * c60 = new TCanvas("c60","",800,800);
    TLegend *leg60 = getLegend(0.5,0.5,0.7,0.9);
    leg60->SetHeader("");      
   // int ic=7;
       hEtaFakeRatio_60[1]->SetMarkerStyle(20);
       hEtaFakeRatio_60[1]->SetMarkerColor(kGray); 
       hEtaFakeRatio_60[1]->SetLineColor(kGray);
//       if(ic==0){
         hBlankRatio->SetTitle(Form(" %s, %s, jetID, pT>60 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankRatio->GetXaxis()->SetTitle("Reco jet eta");
         hBlankRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankRatio->Draw();
//       }
       leg60->AddEntry(hEtaFakeRatio_60[1],Form("%s",ccent[ic]),"p");
       hEtaFakeRatio_60[1]->Draw("same");  
//    }
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
    TCanvas * cPhi30 = new TCanvas("cPhi30","",800,800);
    TLegend *legPhi30 = getLegend(0.5,0.5,0.7,0.9);
    legPhi30->SetHeader("");   
  //  int ic=7;
       hPhiFakeRatio_30[1]->SetMarkerStyle(20);
       hPhiFakeRatio_30[1]->SetLineColor(kGray);
       hPhiFakeRatio_30[1]->SetMarkerColor(kGray);
//       if(ic==0){
         hBlankPhiRatio->SetTitle(Form(" %s, %s, jetID, pT>30 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankPhiRatio->GetXaxis()->SetTitle("Reco jet Phi");
         hBlankPhiRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankPhiRatio->Draw();
//       }
       legPhi30->AddEntry(hPhiFakeRatio_30[1],Form("%s",ccent[ic]),"p");
       hPhiFakeRatio_30[1]->Draw("same");
//    }
    legPhi30->Draw();    
    cPhi30->SaveAs(Form("ANPlots/FakePhiRate_30_%sMC_JetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
    TCanvas * cPhi40 = new TCanvas("cPhi40","",800,800);
    TLegend *legPhi40 = getLegend(0.5,0.5,0.7,0.9);
    legPhi40->SetHeader("");    
 //   int ic=7;
       hPhiFakeRatio_40[1]->SetMarkerStyle(20);
       hPhiFakeRatio_40[1]->SetLineColor(kGray);
       hPhiFakeRatio_40[1]->SetMarkerColor(kGray);
 //      if(ic==0){
         hBlankPhiRatio->SetTitle(Form(" %s, %s, jetID, pT>40 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankPhiRatio->GetXaxis()->SetTitle("Reco jet Phi");
         hBlankPhiRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankPhiRatio->Draw();
//       }
       legPhi40->AddEntry(hPhiFakeRatio_40[1],Form("%s",ccent[ic]),"p");
      hPhiFakeRatio_40[1]->Draw("same");
//    }
    legPhi40->Draw();
    cPhi40->SaveAs(Form("ANPlots/FakePhiRate_40_%sMC_JetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
    TCanvas * cPhi50 = new TCanvas("cPhi50","",800,800);
    TLegend *legPhi50 = getLegend(0.5,0.5,0.7,0.9);
    legPhi50->SetHeader("");   
  //  int ic=7;
       hPhiFakeRatio_50[1]->SetMarkerStyle(20);
       hPhiFakeRatio_50[1]->SetLineColor(kGray);
       hPhiFakeRatio_50[1]->SetMarkerColor(kGray);
 //      if(ic==0){
         hBlankPhiRatio->SetTitle(Form(" %s, %s, jetID, pT>50 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankPhiRatio->GetXaxis()->SetTitle("Reco jet Phi");
         hBlankPhiRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankPhiRatio->Draw();
//       }
       legPhi50->AddEntry(hPhiFakeRatio_50[1],Form("%s",ccent[ic]),"p");
       hPhiFakeRatio_50[1]->Draw("same");
//    }
    legPhi50->Draw();
    cPhi50->SaveAs(Form("ANPlots/FakePhiRate_50_%sMC_JetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
    TCanvas * cPhi60 = new TCanvas("cPhi60","",800,800);
    TLegend *legPhi60 = getLegend(0.5,0.5,0.7,0.9);
    legPhi60->SetHeader("");      
 //   int ic=7;
       hPhiFakeRatio_60[1]->SetMarkerStyle(20);
       hPhiFakeRatio_60[1]->SetLineColor(kGray);
       hPhiFakeRatio_60[1]->SetMarkerColor(kGray);
//       if(ic==0){
         hBlankPhiRatio->SetTitle(Form(" %s, %s, jetID, pT>60 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankPhiRatio->GetXaxis()->SetTitle("Reco jet Phi");
         hBlankPhiRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankPhiRatio->Draw();
//       }
       legPhi60->AddEntry(hPhiFakeRatio_60[1],Form("%s",ccent[ic]),"p");
       hPhiFakeRatio_60[1]->Draw("same");  
//    }
    legPhi60->Draw();    
    cPhi60->SaveAs(Form("ANPlots/FakePhiRate_60_%sMC_JetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");      
    TCanvas * cpT = new TCanvas("cpT","",800,800);
    TLegend *legpT = getLegend(0.5,0.5,0.7,0.9);
    legpT->SetHeader("");  
       hPtFakeRatio[1]->SetMarkerStyle(20);
       hPtFakeRatio[1]->SetLineColor(kGray);
       hPtFakeRatio[1]->SetMarkerColor(kGray);
         hBlankPt->SetTitle(Form(" %s, %s, jetID",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankPt->GetXaxis()->SetTitle("Reco jet pT (GeV/c)");
         hBlankPt->GetYaxis()->SetTitle("Fake rate");
         hBlankPt->Draw();
       legpT->AddEntry(hPtFakeRatio[1],Form("%s",ccent[ic]),"p");
       hPtFakeRatio[1]->Draw("same");
    legpT->Draw();    
     cpT->SaveAs(Form("ANPlots/FakeRatepT_%sMC_JetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
// no jetID:
    TCanvas * c30no = new TCanvas("c30no","",800,800);
    TLegend *leg30no = getLegend(0.5,0.5,0.7,0.9);
    leg30no->SetHeader("");   
//    int ic=7;
       hEtaFakeRatio_30[0]->SetMarkerColor(kGray); 
       hEtaFakeRatio_30[0]->SetLineColor(kGray);
       hEtaFakeRatio_30[0]->SetMarkerStyle(20);
 //      if(ic==0){
         hBlankRatio->SetTitle(Form(" %s, %s, no jetID, pT>30 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankRatio->GetXaxis()->SetTitle("Reco jet eta");
         hBlankRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankRatio->Draw();
  //     }
       leg30no->AddEntry(hEtaFakeRatio_30[0],Form("%s",ccent[ic]),"p");
       hEtaFakeRatio_30[0]->Draw("same");
//    }
    leg30no->Draw();    
     c30no->SaveAs(Form("ANPlots/FakeEtaRate_30_%sMC_noJetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
//          hBlankRatio->SetTitle(Form(" %s, pp (PYTHIA), no jetID, pT>30 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str()));
//          hBlankRatio->GetXaxis()->SetTitle("Reco jet eta");
//          hBlankRatio->GetYaxis()->SetTitle("Fake rate");
//          hBlankRatio->Draw(); 
//          leg30no->AddEntry(hEtaFakeRatio_30[0][7],Form("%s",ccent[7]),"p"); 
//          hEtaFakeRatio_30[0][7]->Draw("same"); 
//     c30no->SaveAs(Form("ANPlots/FakeEtaRate_30_ppMC_noJetID_%s_%d.pdf",(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
    
    TCanvas * c40no = new TCanvas("c40no","",800,800);
    TLegend *leg40no = getLegend(0.5,0.5,0.7,0.9);
    leg40no->SetHeader("");    
  //  int ic=7;
       hEtaFakeRatio_40[0]->SetMarkerStyle(20);
       hEtaFakeRatio_40[0]->SetMarkerColor(kGray); 
       hEtaFakeRatio_40[0]->SetLineColor(kGray);  
//       if(ic==0){
         hBlankRatio->SetTitle(Form(" %s, %s, no jetID, pT>40 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankRatio->GetXaxis()->SetTitle("Reco jet eta");
         hBlankRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankRatio->Draw();
//       }
       leg40no->AddEntry(hEtaFakeRatio_40[0],Form("%s",ccent[ic]),"p");
      hEtaFakeRatio_40[0]->Draw("same");
 //   }
    leg40no->Draw();
    c40no->SaveAs(Form("ANPlots/FakeEtaRate_40_%sMC_noJetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
//          hBlankRatio->SetTitle(Form(" %s, pp (PYTHIA), no jetID, pT>40 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str()));
//          hBlankRatio->GetXaxis()->SetTitle("Reco jet eta");
//          hBlankRatio->GetYaxis()->SetTitle("Fake rate");
//          hBlankRatio->Draw(); 
//          leg40no->AddEntry(hEtaFakeRatio_40[0][7],Form("%s",ccent[7]),"p"); 
//          hEtaFakeRatio_40[0][7]->Draw("same"); 
//     c40no->SaveAs(Form("ANPlots/FakeEtaRate_40_ppMC_noJetID_%s_%d.pdf",(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
    
    TCanvas * c50no = new TCanvas("c50no","",800,800);
    TLegend *leg50no = getLegend(0.5,0.5,0.7,0.9);
    leg50no->SetHeader("");   
  //  int ic=7;
       hEtaFakeRatio_50[0]->SetMarkerStyle(20);
       hEtaFakeRatio_50[0]->SetMarkerColor(kGray); 
       hEtaFakeRatio_50[0]->SetLineColor(kGray);
 //      if(ic==0){
         hBlankRatio->SetTitle(Form(" %s, %s, no jetID, pT>50 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankRatio->GetXaxis()->SetTitle("Reco jet eta");
         hBlankRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankRatio->Draw();
//       }
       leg50no->AddEntry(hEtaFakeRatio_50[0],Form("%s",ccent[ic]),"p");
       hEtaFakeRatio_50[0]->Draw("same");
//    }
    leg50no->Draw();
    c50no->SaveAs(Form("ANPlots/FakeEtaRate_50_%sMC_noJetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
//          hBlankRatio->SetTitle(Form(" %s, pp (PYTHIA), no jetID, pT>50 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str()));
//          hBlankRatio->GetXaxis()->SetTitle("Reco jet eta");
//          hBlankRatio->GetYaxis()->SetTitle("Fake rate");
//          hBlankRatio->Draw(); 
//          leg50no->AddEntry(hEtaFakeRatio_50[0][7],Form("%s",ccent[7]),"p"); 
//          hEtaFakeRatio_50[0][7]->Draw("same"); 
//     c50no->SaveAs(Form("ANPlots/FakeEtaRate_50_ppMC_noJetID_%s_%d.pdf",(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");

    TCanvas * c60no = new TCanvas("c60no","",800,800);
    TLegend *leg60no = getLegend(0.5,0.5,0.7,0.9);
    leg60no->SetHeader("");      
   // int ic=7;
       hEtaFakeRatio_60[0]->SetMarkerStyle(20);
       hEtaFakeRatio_60[0]->SetMarkerColor(kGray); 
       hEtaFakeRatio_60[0]->SetLineColor(kGray);
//       if(ic==0){
         hBlankRatio->SetTitle(Form(" %s, %s, no jetID, pT>60 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankRatio->GetXaxis()->SetTitle("Reco jet eta");
         hBlankRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankRatio->Draw();
//       }
       leg60no->AddEntry(hEtaFakeRatio_60[0],Form("%s",ccent[ic]),"p");
       hEtaFakeRatio_60[0]->Draw("same");  
//    }
    leg60no->Draw();    
    c60no->SaveAs(Form("ANPlots/FakeEtaRate_60_%sMC_noJetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");    
//          hBlankRatio->SetTitle(Form(" %s, pp (PYTHIA), no jetID, pT>60 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str()));
//          hBlankRatio->GetXaxis()->SetTitle("Reco jet eta");
//          hBlankRatio->GetYaxis()->SetTitle("Fake rate");
//          hBlankRatio->Draw(); 
//          leg60no->AddEntry(hEtaFakeRatio_60[0][7],Form("%s",ccent[7]),"p"); 
//          hEtaFakeRatio_60[0][7]->Draw("same"); 
//     c60no->SaveAs(Form("ANPlots/FakeEtaRate_60_ppMC_noJetID_%s_%d.pdf",(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");

// phi plots
    TCanvas * cPhi30no = new TCanvas("cPhi30no","",800,800);
    TLegend *legPhi30no = getLegend(0.5,0.5,0.7,0.9);
    legPhi30no->SetHeader("");   
  //  int ic=7;
       hPhiFakeRatio_30[0]->SetMarkerStyle(20);
       hPhiFakeRatio_30[0]->SetLineColor(kGray);
       hPhiFakeRatio_30[0]->SetMarkerColor(kGray);
//       if(ic==0){
         hBlankPhiRatio->SetTitle(Form(" %s, %s, no jetID, pT>30 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankPhiRatio->GetXaxis()->SetTitle("Reco jet Phi");
         hBlankPhiRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankPhiRatio->Draw();
//       }
       legPhi30no->AddEntry(hPhiFakeRatio_30[0],Form("%s",ccent[ic]),"p");
       hPhiFakeRatio_30[0]->Draw("same");
//    }
    legPhi30no->Draw();    
    cPhi30no->SaveAs(Form("ANPlots/FakePhiRate_30_%sMC_noJetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
    TCanvas * cPhi40no = new TCanvas("cPhi40no","",800,800);
    TLegend *legPhi40no = getLegend(0.5,0.5,0.7,0.9);
    legPhi40no->SetHeader("");    
 //   int ic=7;
       hPhiFakeRatio_40[0]->SetMarkerStyle(20);
       hPhiFakeRatio_40[0]->SetLineColor(kGray);
       hPhiFakeRatio_40[0]->SetMarkerColor(kGray);
 //      if(ic==0){
         hBlankPhiRatio->SetTitle(Form(" %s, %s, no jetID, pT>40 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankPhiRatio->GetXaxis()->SetTitle("Reco jet Phi");
         hBlankPhiRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankPhiRatio->Draw();
//       }
       legPhi40no->AddEntry(hPhiFakeRatio_40[0],Form("%s",ccent[ic]),"p");
      hPhiFakeRatio_40[0]->Draw("same");
//    }
    legPhi40no->Draw();
    cPhi40no->SaveAs(Form("ANPlots/FakePhiRate_40_%sMC_noJetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
    TCanvas * cPhi50no = new TCanvas("cPhi50no","",800,800);
    TLegend *legPhi50no = getLegend(0.5,0.5,0.7,0.9);
    legPhi50no->SetHeader("");   
  //  int ic=7;
       hPhiFakeRatio_50[0]->SetMarkerStyle(20);
       hPhiFakeRatio_50[0]->SetLineColor(kGray);
       hPhiFakeRatio_50[0]->SetMarkerColor(kGray);
 //      if(ic==0){
         hBlankPhiRatio->SetTitle(Form(" %s, %s, no jetID, pT>50 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankPhiRatio->GetXaxis()->SetTitle("Reco jet Phi");
         hBlankPhiRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankPhiRatio->Draw();
//       }
       legPhi50no->AddEntry(hPhiFakeRatio_50[0],Form("%s",ccent[ic]),"p");
       hPhiFakeRatio_50[0]->Draw("same");
//    }
    legPhi50no->Draw();
    cPhi50no->SaveAs(Form("ANPlots/FakePhiRate_50_%sMC_noJetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");
    TCanvas * cPhi60no = new TCanvas("cPhi60no","",800,800);
    TLegend *legPhi60no = getLegend(0.5,0.5,0.7,0.9);
    legPhi60no->SetHeader("");      
 //   int ic=7;
       hPhiFakeRatio_60[0]->SetMarkerStyle(20);
       hPhiFakeRatio_60[0]->SetLineColor(kGray);
       hPhiFakeRatio_60[0]->SetMarkerColor(kGray);
//       if(ic==0){
         hBlankPhiRatio->SetTitle(Form(" %s, %s, no jetID, pT>60 GeV/c ",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankPhiRatio->GetXaxis()->SetTitle("Reco jet Phi");
         hBlankPhiRatio->GetYaxis()->SetTitle("Fake rate");
         hBlankPhiRatio->Draw();
//       }
       legPhi60no->AddEntry(hPhiFakeRatio_60[0],Form("%s",ccent[ic]),"p");
       hPhiFakeRatio_60[0]->Draw("same");  
//    }
    legPhi60no->Draw();    
    cPhi60no->SaveAs(Form("ANPlots/FakePhiRate_60_%sMC_noJetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");      
    TCanvas * cpTno = new TCanvas("cpTno","",800,800);
    TLegend *legpTno = getLegend(0.5,0.5,0.7,0.9);
    legpTno->SetHeader("");  
       hPtFakeRatio[0]->SetMarkerStyle(20);
       hPtFakeRatio[0]->SetLineColor(kGray);
       hPtFakeRatio[0]->SetMarkerColor(kGray);
         hBlankPt->SetTitle(Form(" %s, %s, no jetID",(kAlgName+srad[nj]+kjetType).c_str(),kSpeciesLong.c_str()));
         hBlankPt->GetXaxis()->SetTitle("Reco jet pT (GeV/c)");
         hBlankPt->GetYaxis()->SetTitle("Fake rate");
         hBlankPt->Draw();
       legpTno->AddEntry(hPtFakeRatio[0],Form("%s",ccent[ic]),"p");
       hPtFakeRatio[0]->Draw("same");
    legpTno->Draw();    
     cpTno->SaveAs(Form("ANPlots/FakeRatepT_%sMC_noJetID_%s_%d.pdf",kSpecies.c_str(),(kAlgName+srad[nj]+kjetType).c_str(),date.GetDate()),"RECREATE");


    } // end nj loop (radius)
    
} // end program