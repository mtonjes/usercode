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


#include "Headers/plot.h"



static const int nbins_cent = 7;
static const Double_t boundaries_cent[nbins_cent+1] = {0,2,4,12,20,28,36,40};// multiply by 2.5 to get your actual centrality % (old 2011 data) 
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

static const int nbins_pt = 30;
static const double boundaries_pt[nbins_pt+1] = {  3, 4, 5, 7, 9, 12, 15, 18, 21, 24, 28,  32, 37, 43, 49, 56,  64, 74, 84, 97, 114,  133, 153, 174, 196,  220, 245, 300, 330, 362, 395};



using namespace std;

void plot_cent(char* etaWidth = (char*)"10_eta_18", Int_t radius = 3){

  TStopwatch timer;
  gStyle->SetOptStat(0);
  TH1::SetDefaultSumw2();

  //  cout<<"etaWidth = "<<etaWidth<<endl;
  bool isAnalysisBin = false; 

  TDatime date;
  
  TFile * ffileAll=TFile::Open("test.root");
  TFile *ffileMN = TFile::Open("HIMinBiaswithoutHLT80JetDeltaEtaPlotswithcent.root");
  TFile *ffile = TFile::Open("HI80JetDeltaEtaPlotswithcent.root");
   TFile *filecomp=TFile::Open("HIMinBiasJetDeltaEtaPlotswithcentwoleading.root");
   TFile *ffileMock = TFile::Open("mockfake/MinBiasSpectrawiLJcut.root");
   
  //   TFile *filecomp=TFile::Open("HIMinBiasJetDeltaEtaPlotswithcentwoleadingandalso40.root");
//  fMinBias = TFile::Open(Form("Pawan_ntuple_PbPb_MinBiasData_spectra_JetID_CutA_finebins_CentralityWeighted_%s_R0p%d.root",etaWidth,radius));
  // fJetTrig = TFile::Open(Form("/export/d00/scratch/rkunnawa/rootfiles/RAA/Pawan_ntuple_PbPb_data_MC_subid0_spectra_JetID_CutA_finebins_%s_R0p%d.root",etaWidth,radius));

  // get the histograms
  TH1F * hspectra[nbins_cent], * hdeltaphi[nbins_cent];
  TH1F * hspectraMB[nbins_cent];
  TH1F * hspectraAll[nbins_cent];
  
  TH1F * hspectraLMR[nbins_cent];

  TH1F * hspectrawol[nbins_cent];
  TH1F * hspectrawil[nbins_cent];

  Float_t bin_no = 1;

  for(int i = 0; i<nbins_cent-1; ++i){
    hspectraAll[i] = (TH1F*)ffileAll->Get(Form("hptspectra_cent%d",i));
    hspectra[i] = (TH1F*)ffile->Get(Form("hptspectra_cent%d",i));
    hspectraMB[i] = (TH1F*)ffileMN->Get(Form("hptspectra_cent%d",i));
    hdeltaphi[i]   =  (TH1F*)ffileAll->Get(Form("hdphipt_cent%d",i));
  
    hspectrawol[i] = (TH1F*)filecomp->Get(Form("hptspectrawoleading_cent%d",i));
    hspectrawil[i] = (TH1F*)filecomp->Get(Form("hptspectra_cent%d",i));

    hspectraLMR[i] = (TH1F*)ffileMock->Get(Form("hptspectrawoleading_cent%d",i));
  }


  TH2F * hBlankSpectra = new TH2F("hBlankSpectra","",400,0,150,100,1e-6,5e3);
  TCanvas * cFakeSub = new TCanvas("cFakeSub","",1000,800);
  makeMultiPanelCanvasWithGap(cFakeSub,3,2,0.01,0.01,0.16,0.2,0.04,0.04);
  //cFakeSub->Divide(3,2);
  float scale=1;
  //  float scale=1.14218775734552442e-03;
  TLegend * lSub = myLegend(0.5,0.7,0.9,0.9);
  makeHistTitle(hBlankSpectra," ","Jet p_{T} (GeV/c)","Arb. Units");
  // hBlankSpectra->GetYaxis()->SetNdivisions(1000); 
  hBlankSpectra->GetYaxis()->SetMoreLogLabels(kFALSE);
  hBlankSpectra->GetYaxis()->SetTitleOffset(2.5);
  lSub->AddEntry(hspectraAll[0]," MinBias ","pl");
  lSub->AddEntry(hspectra[0]," HLT80 ","pl");
  lSub->AddEntry(hspectraMB[0],"MinBias && !HLT80 ","pl");
    //lSub->AddEntry(hSubtracted[0],"Jet Triggered - MinBias","pl");
    //lSub->SetTextSiz

  for(int i = 0; i<6; ++i){
    //cout<< "    i values "<<i<<endl;
    cFakeSub->cd(6-i);
    cFakeSub->cd(6-i)->SetLogy();
    hBlankSpectra->Draw();
    hspectraMB[i]->SetMarkerStyle(24);    
    hspectraMB[i]->SetMarkerColor(kRed);
    
    hspectraAll[i]->SetMarkerStyle(25);    
    hspectraAll[i]->SetMarkerColor(kBlack);
    
    hspectra[i]->Scale(scale);
    hspectra[i]->SetMarkerStyle(33);    
    hspectra[i]->SetMarkerColor(kBlue);
    //hspectra[i]->SetAxisRange(13,299,"X");
    makeHistTitle(hspectra[i]," ","Jet p_{T} (GeV/c)","Arb. Units");
    Double_t boundaries_cent[nbins_cent+1] = {0,2,4,12,20,28,36,40};

    hspectraMB[i]->Rebin(4);
    hspectraMB[i]->Scale(0.25);
    hspectra[i]->Rebin(4);
    hspectra[i]->Scale(0.25);
    hspectraAll[i]->Rebin(4);
    hspectraAll[i]->Scale(0.25);

    //  hspectraAll[i]->Draw("same");
    hspectraMB[i]->Draw("same");
    hspectra[i]->Draw("same");
    hspectraAll[i]->Draw("same");
   
    lSub->Draw();
    //cout<<"working here   too"<<endl; 
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.85,20);    
    
  }


  cFakeSub->cd(1);
  putCMSPrel();
  
  //  lSub->AddEntry(hJetTrigComb[0],"Jet Triggered Data","pl");
  //lSub->AddEntry(hMinBias[0],"MinBias data","pl");
  //lSub->AddEntry(hSubtracted[0],"Jet Triggered - MinBias","pl");
  lSub->SetTextSize(0.04);
  cFakeSub->SaveAs("MBandHLT80_spectra.pdf","RECREATE");

  //  lSub->Draw();
 
 
  if(false){
  //float pi=TMath::pi();
  TH2F * hBlankSpectra2 = new TH2F("hBlankSpectra2","",400,0,100,100,0,3.2);
  TCanvas * cFakeSub2 = new TCanvas("cFakeSub2","",1000,800);
  makeMultiPanelCanvasWithGap(cFakeSub2,3,2,0.01,0.01,0.16,0.2,0.04,0.04);
  //cFakeSub->Divide(3,2);
  
  
  TLegend * lSub2 = myLegend(0.5,0.7,0.9,0.9);
  makeHistTitle(hBlankSpectra2," ","Jet p_{T} (GeV/c)","#Delta #phi");
  // hBlankSpectra->GetYaxis()->SetNdivisions(1000); 
  hBlankSpectra2->GetYaxis()->SetMoreLogLabels(kFALSE);
  hBlankSpectra2->GetYaxis()->SetTitleOffset(2.5);
  
  for(int i = 0; i<6; ++i){
    //cout<< "    i values "<<i<<endl;
    cFakeSub2->cd(6-i);
    cFakeSub2->cd(6-i)->SetLogz();
    hBlankSpectra2->Draw();
    
    //    hdeltaphi[i]->SetMarkerStyle(24);    
    // hdeltaphi[i]->SetMarkerColor(kBlack);
    
    makeHistTitle(hdeltaphi[i]," ","Jet p_{T} (GeV/c)","#Delta #phi");
    //  hdeltaphi[i]->SetAxisRange(1e-4,1e+2,"Z");
    hdeltaphi[i]->Draw("samecolz");
    //cout<<"working here   too"<<endl; 
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.85,20);    
    
  }


  // cFakeSub2->cd(1);
  //putCMSPrel();
  
  cFakeSub2->SaveAs("MBandHLT80_deltaphi.pdf","RECREATE");
 
  }



  if(true){
  //float pi=TMath::pi();
  //TH2F * hBlankSpectra10 = new TH2F("hBlankSpectra10","",400,0,100,100,1e-5,5e3);
  TH2F * hBlankSpectra10 = new TH2F("hBlankSpectra10","",400,0,150,100,1e-6,5e3);
  TCanvas * cFakeSub10 = new TCanvas("cFakeSub10","",1000,800);
  makeMultiPanelCanvasWithGap(cFakeSub10,3,2,0.01,0.01,0.16,0.2,0.04,0.04);
  //cFakeSub->Divide(3,2);
  
  TLegend * lSub10 = myLegend(0.4,0.6,0.9,0.9);
  makeHistTitle(hBlankSpectra10," ","Jet p_{T} (GeV/c)","Arb. Units.");

  lSub10->AddEntry(hspectrawol[0]," w/o leading jet ","pl");
  lSub10->AddEntry(hspectraLMR[0]," w/o leading jet (Mock scaled) ","pl");
  lSub10->AddEntry(hspectraMB[0],"MinBias && !HLT80 ","pl");
  lSub10->AddEntry(hspectrawil[0],"MinBias ","pl");


// hBlankSpectra->GetYaxis()->SetNdivisions(1000); 
  hBlankSpectra10->GetYaxis()->SetMoreLogLabels(kFALSE);
  hBlankSpectra10->GetYaxis()->SetTitleOffset(2.5);
  
  for(int i = 0; i<6; ++i){
    //cout<< "    i values "<<i<<endl;
    cFakeSub10->cd(6-i);
    cFakeSub10->cd(6-i)->SetLogy();
    hBlankSpectra10->Draw();
    
    hspectrawol[i]->SetMarkerStyle(25);    
    hspectrawol[i]->SetMarkerColor(kRed);
    
    hspectrawol[i]->Rebin(4);
    hspectrawol[i]->Scale(0.25);
    
    hspectrawil[i]->SetMarkerStyle(33);  
    hspectrawil[i]->Rebin(4);
    hspectrawil[i]->Scale(0.25);

    //hspectraAll[i]->Rebin(4);
    //hspectraAll[i]->Scale(0.25);
    hspectraMB[i]->Draw("same");
    //makeHistTitle( hspectrawol[i]," ","Jet p_{T} (GeV/c)","#Delta #phi");
    //  hdeltaphi[i]->SetAxisRange(1e-4,1e+2,"Z");
     hspectrawol[i]->Draw("same");
     hspectrawil[i]->Draw("same");
    

     hspectraLMR[i]->SetMarkerStyle(34); 
     hspectraLMR[i]->SetMarkerColor(kBlue);
     hspectraLMR[i]->Rebin(4);
     hspectraLMR[i]->Scale(0.25);
     hspectraLMR[i]->Draw("same");

     lSub10->Draw();
    //cout<<"working here   too"<<endl; 
    drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.85,20);    
    
  }
   lSub10->SetTextSize(0.04);
   cFakeSub10->SaveAs("MBandOtherMethods_spectra.pdf","RECREATE");
  // cFakeSub2->cd(1);
  //putCMSPrel();
  
 
 
  }



  // 
  //  cFakeSub->SaveAs("MBandHLT80_spectra.pdf","RECREATE");



  //cFakeSub->SaveAs(Form("PbPb_FakeMinBias_SubtractedFrom_Data_R%d_%s_%d.pdf",radius, etaWidth, date.GetDate()),"RECREATE");
  
  //  create output root file to write the output histogram. 
  // TFile fout(Form("PbPb_FakeMinBias_SubtractedFrom_Data_R%d_%s_%d.root",radius, etaWidth, date.GetDate()),"RECREATE");
  //fout.cd();

  //for(int i = 0; i<nbins_cent-1; ++i){

    //  hSubtracted[i]->Write();
    //JetTrigComb[i]->Write();
      //hMinBias[i]->Write();

  //}

  //  fout.Close();

  //macro end. 
  timer.Stop();
  cout<<"Macro finished: "<<endl;
  cout<<"CPU time (min)  = "<<(Float_t)timer.CpuTime()/60<<endl;
  cout<<"Real time (min) = "<<(Float_t)timer.RealTime()/60<<endl;
  
}
