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

static const int nbins_cent = 7;
void ratiospectra_wol(){

  TH1::SetDefaultSumw2();
  TFile *_file1 = TFile::Open("HIMinBiasJetDeltaEtaPlotswithcentwoleading.root");
  TFile *_file0 = TFile::Open("HIMinBiasJetDeltaEtaPlotswithcentwoleadingandalso40.root");
  TFile *_file2=TFile::Open("Pawan_ntuple_PbPb_MinBiasData_spectra_JetID_CutA_finebins_CentralityWeightedAllMB_20_eta_20_R0p3.root");
  // hMinBiasbin=(TH1F*)_file0->Get("hBinEvents");
  //hHLTbin=(TH1F*)_file1->Get("hBinEvents");
  // hHLTbin->Draw();
  
  //hratio=(TH1F*) hHLTbin->Clone();
  
 // get the histograms

  TFile f("MinBiasSpectrawiLJcut.root","RECREATE");

  
  TH1F * hspectraSub[nbins_cent];
 TH1F * hspectraSub40[nbins_cent];

  TH1F * hspectraMB[nbins_cent];
  TH1F * hspectrawol[nbins_cent];
  TH1F * hspectrawil[nbins_cent];
  //  TH1F * hspectrawil40[nbins_cent];
  TH1F * hspectrawol40[nbins_cent];


  Float_t bin_no = 1;

  for(int i = 0; i<nbins_cent-1; ++i){
    hspectraMB[i] = (TH1F*)_file2->Get(Form("hpbpb_HLTComb_R3_20_eta_20_cent%d",i));
   
    hspectrawol40[i] = (TH1F*)_file0->Get(Form("hptspectrawoleading_40_cent%d",i));
    hspectrawol[i] = (TH1F*)_file1->Get(Form("hptspectrawoleading_cent%d",i));
    hspectrawil[i] = (TH1F*)_file1->Get(Form("hptspectra_cent%d",i));

    //hspectraSub[i]=(TH1F*)_file2->Get(Form("hpbpb_HLTComb_R3_20_eta_20_cent%d",i));
    // hspectraSub40[i]=(TH1F*)_file2->Get(Form("hpbpb_HLTComb_R3_20_eta_20_cent%d",i));


    float bin_no = hspectraMB[i]->FindBin(25);
    float bin_end=hspectraMB[i]->FindBin(35);
    
    float bin_no_cut = hspectrawol[i]->FindBin(25);
    float bin_end_cut=hspectrawol[i]->FindBin(35);
    
    float scalerangeweight40=hspectraMB[i]->Integral(bin_no,bin_end)/hspectrawol40[i]->Integral(bin_no_cut,bin_end_cut);
    float scalerangeweight=hspectraMB[i]->Integral(bin_no,bin_end)/hspectrawol[i]->Integral(bin_no_cut,bin_end_cut);
    cout<<"   "<<bin_no<<"   "<<bin_no_cut<<endl;  
    cout<<"   "<<bin_end<<"   "<<bin_end_cut<<endl;
    cout<<" weight  "<<scalerangeweight<<"  with 40 cut "<<scalerangeweight40<<endl;

    float bincontentratio==hspectraMB[i]->GetBinContent(9)/hspectrawol[i]->GetBinContent(9);
   
    // normalize the histogram by the jet entries in bin of pT = 15.
    //    hJetTrigComb[i]->Scale(1./hJetTrigComb[i]->GetBinContent(bin_no));
    //    hMinBias[i]->Scale(1./hMinBias[i]->GetBinContent(bin_no));
    hspectraSub40[i]=(TH1F*)hspectrawol40[i]->Clone(Form("hptspectrawoleading_40_cent%d", i));
    hspectraSub40[i]->Scale(scalerangeweight40);
   
    hspectraSub[i]=(TH1F*)hspectrawol[i]->Clone(Form("hptspectrawoleading_cent%d", i));
    if(i<3) hspectraSub[i]->Scale(scalerangeweight);
    if(i>2) hspectraSub[i]->Scale(bincontentratio);
    /*  for(int j = bin_no_cut; j<bin_end_cut; ++j){
      hspectraSub40[i]->SetBinError(j,hspectraSub40[i]->GetBinError(j)*(1./scalerangeweight40));
      hspectraSub[i]->SetBinError(j,hspectraSub[i]->GetBinError(j)*(1./scalerangeweight));

      }*/

    
    // set all the entries before bin no 15 to be zero.
   for(int j = 1; j<bin_no; ++j){
      hspectraSub40[i]->SetBinContent(j, hspectraMB[i]->GetBinContent(j));
      hspectraSub40[i]->SetBinError(j,hspectraMB[i]->GetBinError(j));

      hspectraSub[i]->SetBinContent(j, hspectraMB[i]->GetBinContent(j));
      hspectraSub[i]->SetBinError(j,hspectraMB[i]->GetBinError(j));
      }
   
    for(int j = 1; j<16; ++j){
      hspectraSub40[i]->SetBinContent(j,0);
      hspectraSub40[i]->SetBinError(j,0);

      hspectraSub[i]->SetBinContent(j, 0);
      hspectraSub[i]->SetBinError(j,0);
    }

  }



  // hratio->Draw();
  // hratio->Divide(hMinBiasbin);
  //hratio->SetLineColor(2);
  //float integral= hratio->Integral(0,180);
  //hratio->Scale(1./integral);
  //hratio->Draw("same");
  


  f.cd();
 

  
  f.Write();
  f.Close();

  //hHLTbin->Divide(hMinBiasbin);



}
