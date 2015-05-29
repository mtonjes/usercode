// root -l -q -b PowerLawFitRatio_ATLASpp.C+
//MIT VERSION UPDATED May 19 2015 for MinBias subtraction MBT
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

#include "/net/hisrv0001/home/belt/wrk/JetRAA/RaghavCode/Headers/plot.h"

void PowerLawFitRatio_ATLASPbPb(Int_t nfit=6, Int_t FitStart=50, Int_t FitEnd=300){
bool doScale=true;
float ScaleFactor=145./140.;
  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(00000000);
  
  TH1F * PbPbATLAS_c0, PbPbCMS_c0, PbPbATLAS_c1, PbPbCMS_c1, PbPbATLAS_c2, PbPbCMS_c2, PbPbATLAS_c3, PbPbCMS_c3, PbPbATLAS_c4, PbPbCMS_c4, PbPbATLAS_c5, PbPbCMS_c5;
   TF1 *fitPbPbATLAS_c0 = new TF1("fitPbPbATLAS_c0","[0]*pow(x+[2],[1])"); //create function
   fitPbPbATLAS_c0->SetParameters(1e10,-5,0);
   fitPbPbATLAS_c0->SetLineColor(kRed);   
   TF1 *fitPbPbATLAS_c1 = new TF1("fitPbPbATLAS_c1","[0]*pow(x+[2],[1])"); //create function
   fitPbPbATLAS_c1->SetParameters(1e10,-5,0);
   fitPbPbATLAS_c1->SetLineColor(kRed);   
   TF1 *fitPbPbATLAS_c2 = new TF1("fitPbPbATLAS_c2","[0]*pow(x+[2],[1])"); //create function
   fitPbPbATLAS_c2->SetParameters(1e10,-5,0);
   fitPbPbATLAS_c2->SetLineColor(kRed);   
   TF1 *fitPbPbATLAS_c3 = new TF1("fitPbPbATLAS_c3","[0]*pow(x+[2],[1])"); //create function
   fitPbPbATLAS_c3->SetParameters(1e10,-5,0);
   fitPbPbATLAS_c3->SetLineColor(kRed);   
   TF1 *fitPbPbATLAS_c4 = new TF1("fitPbPbATLAS_c4","[0]*pow(x+[2],[1])"); //create function
   fitPbPbATLAS_c4->SetParameters(1e10,-5,0);
   fitPbPbATLAS_c4->SetLineColor(kRed);   
   TF1 *fitPbPbATLAS_c5 = new TF1("fitPbPbATLAS_c5","[0]*pow(x+[2],[1])"); //create function
   fitPbPbATLAS_c5->SetParameters(1e10,-5,0);
   fitPbPbATLAS_c5->SetLineColor(kRed);         
// get some CMS histos from a root file in a nice fashion
 TFile * fData;
fData = TFile::Open("Pawan_ntuple_PbPb_pp_calopfpt_ppNoJetidcut_R0p4_SevilFakeMBnoJet80Cut_unfold_mcclosure_oppside_trgMC_noSmear_20_eta_20_50GeVCut_akPF_20150528.root");
  TH1F *PbPb_bayesian_unfolded_spectra_combined_cent0=(TH1F*)fData->Get("PbPb_bayesian_unfolded_spectra_combined_cent0");
  TH1F *PbPb_bayesian_unfolded_spectra_combined_cent1=(TH1F*)fData->Get("PbPb_bayesian_unfolded_spectra_combined_cent1");
  TH1F *PbPb_bayesian_unfolded_spectra_combined_cent2=(TH1F*)fData->Get("PbPb_bayesian_unfolded_spectra_combined_cent2");
  TH1F *PbPb_bayesian_unfolded_spectra_combined_cent3=(TH1F*)fData->Get("PbPb_bayesian_unfolded_spectra_combined_cent3");
  TH1F *PbPb_bayesian_unfolded_spectra_combined_cent4=(TH1F*)fData->Get("PbPb_bayesian_unfolded_spectra_combined_cent4");
  TH1F *PbPb_bayesian_unfolded_spectra_combined_cent5=(TH1F*)fData->Get("PbPb_bayesian_unfolded_spectra_combined_cent5");
   TH1F *hRatioATLAS_cent0 = (TH1F*)PbPb_bayesian_unfolded_spectra_combined_cent0->Clone("hRatioATLAS_cent0"); //clone histogram hRatio from h
   TH1F *hRatioATLAS_cent1 = (TH1F*)PbPb_bayesian_unfolded_spectra_combined_cent1->Clone("hRatioATLAS_cent1"); //clone histogram hRatio from h
   TH1F *hRatioATLAS_cent2 = (TH1F*)PbPb_bayesian_unfolded_spectra_combined_cent2->Clone("hRatioATLAS_cent2"); //clone histogram hRatio from h
   TH1F *hRatioATLAS_cent3 = (TH1F*)PbPb_bayesian_unfolded_spectra_combined_cent3->Clone("hRatioATLAS_cent3"); //clone histogram hRatio from h
   TH1F *hRatioATLAS_cent4 = (TH1F*)PbPb_bayesian_unfolded_spectra_combined_cent4->Clone("hRatioATLAS_cent4"); //clone histogram hRatio from h
   TH1F *hRatioATLAS_cent5 = (TH1F*)PbPb_bayesian_unfolded_spectra_combined_cent5->Clone("hRatioATLAS_cent5"); //clone histogram hRatio from h
// set up a blank ratio histogram for later
   TH1F *hRatioBlank = new TH1F("hRatioBlank"," ",100,65,300);
   hRatioBlank->SetMinimum(0);
   hRatioBlank->SetMaximum(1.2);
   hRatioBlank->SetDirectory(0);
   hRatioBlank->SetStats(0);
   hRatioBlank->SetFillColor(1);
   hRatioBlank->SetFillStyle(0);
   hRatioBlank->SetLineStyle(0);
   hRatioBlank->SetMarkerStyle(20);
   hRatioBlank->SetMarkerSize(1.2);
   hRatioBlank->GetXaxis()->SetTitle("ak R=0.4 Jet p_{T} (GeV/c)");
   hRatioBlank->GetXaxis()->SetLabelFont(42);
   hRatioBlank->GetXaxis()->SetLabelOffset(0.01);
   hRatioBlank->GetXaxis()->SetLabelSize(0.045);
   hRatioBlank->GetXaxis()->SetTitleSize(0.055);
   hRatioBlank->GetXaxis()->SetTitleFont(42);
   hRatioBlank->GetYaxis()->SetTitle("CMS/ATLAS");
   hRatioBlank->GetYaxis()->SetLabelFont(42);
   hRatioBlank->GetYaxis()->SetLabelOffset(0.01);
   hRatioBlank->GetYaxis()->SetLabelSize(0.045);
   hRatioBlank->GetYaxis()->SetTitleSize(0.055);
   hRatioBlank->GetYaxis()->SetTitleOffset(1.5);
   hRatioBlank->GetYaxis()->SetTitleFont(42);
   hRatioBlank->GetZaxis()->SetLabelFont(42);
   hRatioBlank->GetZaxis()->SetLabelSize(0.045);
   hRatioBlank->GetZaxis()->SetTitleSize(0.035);
   hRatioBlank->GetZaxis()->SetTitleFont(42);
// now plot and fit spectra (only fit ATLAS)
// get some ATLAS histos the hard way      
   TCanvas *cATLAS_pbpb = new TCanvas("cATLAS_pbpb", "",0,0,1200,1000);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   cATLAS_pbpb->Range(0,0,1,1);
   cATLAS_pbpb->SetFillColor(0);
   cATLAS_pbpb->SetBorderMode(0);
   cATLAS_pbpb->SetBorderSize(0);
   cATLAS_pbpb->SetTickx(1);
   cATLAS_pbpb->SetTicky(1);
   cATLAS_pbpb->SetLeftMargin(0.17);
   cATLAS_pbpb->SetRightMargin(0.15);
   cATLAS_pbpb->SetTopMargin(0.03);
   cATLAS_pbpb->SetBottomMargin(0.15);
   cATLAS_pbpb->SetFrameLineColor(0);
   cATLAS_pbpb->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: p_0_0
   TPad *p_0_0 = new TPad("p_0_0", "p_0_0",0,0.5224719,0.3759095,1);
   p_0_0->Draw();
   p_0_0->cd();
   p_0_0->Range(0,0,1,1);
   p_0_0->SetFillColor(0);
   p_0_0->SetBorderMode(0);
   p_0_0->SetBorderSize(0);
   p_0_0->SetTickx(1);
   p_0_0->SetTicky(1);
   p_0_0->SetLeftMargin(0.2);
   p_0_0->SetRightMargin(0);
   p_0_0->SetTopMargin(0.07);
   p_0_0->SetBottomMargin(0);
   p_0_0->SetFrameLineColor(0);
   p_0_0->SetFrameBorderMode(0);
   p_0_0->Modified();
   cATLAS_pbpb->cd();
  
// ------------>Primitives in pad: p_0_1
   p_0_1 = new TPad("p_0_1", "p_0_1",0,0,0.3759095,0.5224719);
   p_0_1->Draw();
   p_0_1->cd();
   p_0_1->Range(6.5,-5.058824,299,2);
   p_0_1->SetFillColor(0);
   p_0_1->SetBorderMode(0);
   p_0_1->SetBorderSize(0);
   p_0_1->SetLogy();
   p_0_1->SetTickx(1);
   p_0_1->SetTicky(1);
   p_0_1->SetLeftMargin(0.2);
   p_0_1->SetRightMargin(0);
   p_0_1->SetTopMargin(0);
   p_0_1->SetBottomMargin(0.15);
   p_0_1->SetFrameLineColor(0);
   p_0_1->SetFrameBorderMode(0);
   p_0_1->SetFrameLineColor(0);
   p_0_1->SetFrameBorderMode(0);
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(10);
   grae->SetName("/HepData/8719/d10x1y1");
   grae->SetTitle("  ");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(33);
   grae->SetMarkerSize(1.2);
   grae->SetPoint(0,44.5,30.15873);
   grae->SetPointError(0,5.5,5.5,2.361534e-05,2.361534e-05);
   grae->SetPoint(1,56.5,10.75397);
   grae->SetPointError(1,6.5,6.5,9.526565e-06,9.526565e-06);
   grae->SetPoint(2,71,3.27381);
   grae->SetPointError(2,8,8,3.137951e-06,3.137951e-06);
   grae->SetPoint(3,89.5,0.9166667);
   grae->SetPointError(3,10.5,10.5,8.184966e-07,8.184966e-07);
   grae->SetPoint(4,112.5,0.2460317);
   grae->SetPointError(4,12.5,12.5,2.081612e-07,2.081612e-07);
   grae->SetPoint(5,141.5,0.06388889);
   grae->SetPointError(5,16.5,16.5,5.382411e-08,5.382411e-08);
   grae->SetPoint(6,178.5,0.01515873);
   grae->SetPointError(6,20.5,20.5,1.317296e-08,1.317296e-08);
   grae->SetPoint(7,225,0.003174603);
   grae->SetPointError(7,26,26,2.853702e-09,2.853702e-09);
   grae->SetPoint(8,283.5,0.000577381);
   grae->SetPointError(8,32.5,32.5,5.391438e-10,5.391438e-10);
   grae->SetPoint(9,357,9.226191e-05);
   grae->SetPointError(9,41,41,8.978956e-11,8.978956e-11);
   
   TH1F *Graph_d10x1y115 = new TH1F("Graph_d10x1y115","  ",100,65,299);
   Graph_d10x1y115->SetMinimum(0.0001);
   Graph_d10x1y115->SetMaximum(100);
   Graph_d10x1y115->SetDirectory(0);
   Graph_d10x1y115->SetStats(0);
   Graph_d10x1y115->SetFillColor(1);
   Graph_d10x1y115->SetFillStyle(0);
   Graph_d10x1y115->SetLineStyle(0);
   Graph_d10x1y115->SetMarkerStyle(20);
   Graph_d10x1y115->SetMarkerSize(1.2);
   Graph_d10x1y115->GetXaxis()->SetLabelFont(42);
   Graph_d10x1y115->GetXaxis()->SetLabelOffset(0.01);
   Graph_d10x1y115->GetXaxis()->SetLabelSize(0.045);
   Graph_d10x1y115->GetXaxis()->SetTitleSize(0.055);
   Graph_d10x1y115->GetXaxis()->SetTitleFont(42);
   Graph_d10x1y115->GetYaxis()->SetLabelFont(42);
   Graph_d10x1y115->GetYaxis()->SetLabelOffset(0.01);
   Graph_d10x1y115->GetYaxis()->SetLabelSize(0.045);
   Graph_d10x1y115->GetYaxis()->SetTitleSize(0.055);
   Graph_d10x1y115->GetYaxis()->SetTitleOffset(1.5);
   Graph_d10x1y115->GetYaxis()->SetTitleFont(42);
   Graph_d10x1y115->GetZaxis()->SetLabelFont(42);
   Graph_d10x1y115->GetZaxis()->SetLabelSize(0.045);
   Graph_d10x1y115->GetZaxis()->SetTitleSize(0.035);
   Graph_d10x1y115->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_d10x1y115);
   Graph_d10x1y115->Draw();
   grae->Draw("ap,same");
   
   grae = new TGraphAsymmErrors(9);
   grae->SetName("/HepData/8719/d11x1y1");
   grae->SetTitle("  ");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(34);
   grae->SetMarkerSize(1.2);
   grae->SetPoint(0,44.5,35.2963);
   grae->SetPointError(0,5.5,5.5,1.607748e-05,1.607748e-05);
   grae->SetPoint(1,56.5,12);
   grae->SetPointError(1,6.5,6.5,6.086804e-06,6.086804e-06);
   grae->SetPoint(2,71,3.62963);
   grae->SetPointError(2,8,8,1.942527e-06,1.942527e-06);
   grae->SetPoint(3,89.5,1.018519);
   grae->SetPointError(3,10.5,10.5,5.289802e-07,5.289802e-07);
   grae->SetPoint(4,112.5,0.2714815);
   grae->SetPointError(4,12.5,12.5,1.358524e-07,1.358524e-07);
   grae->SetPoint(5,141.5,0.06851852);
   grae->SetPointError(5,16.5,16.5,3.374818e-08,3.374818e-08);
   grae->SetPoint(6,178.5,0.01514815);
   grae->SetPointError(6,20.5,20.5,7.763785e-09,7.763785e-09);
   grae->SetPoint(7,225,0.002948148);
   grae->SetPointError(7,26,26,1.594128e-09,1.594128e-09);
   grae->SetPoint(8,283.5,0.0005);
   grae->SetPointError(8,32.5,32.5,3.004713e-10,3.004713e-10);
   
   TH1F *Graph_d11x1y116 = new TH1F("Graph_d11x1y116","  ",100,11.3,343.7);
   Graph_d11x1y116->SetMinimum(0.0004499997);
   Graph_d11x1y116->SetMaximum(38.82589);
   Graph_d11x1y116->SetDirectory(0);
   Graph_d11x1y116->SetStats(0);
   Graph_d11x1y116->SetFillColor(1);
   Graph_d11x1y116->SetFillStyle(0);
   Graph_d11x1y116->SetLineStyle(0);
   Graph_d11x1y116->SetMarkerStyle(20);
   Graph_d11x1y116->SetMarkerSize(1.2);
   Graph_d11x1y116->GetXaxis()->SetLabelFont(42);
   Graph_d11x1y116->GetXaxis()->SetLabelOffset(0.01);
   Graph_d11x1y116->GetXaxis()->SetLabelSize(0.045);
   Graph_d11x1y116->GetXaxis()->SetTitleSize(0.055);
   Graph_d11x1y116->GetXaxis()->SetTitleFont(42);
   Graph_d11x1y116->GetYaxis()->SetLabelFont(42);
   Graph_d11x1y116->GetYaxis()->SetLabelOffset(0.01);
   Graph_d11x1y116->GetYaxis()->SetLabelSize(0.045);
   Graph_d11x1y116->GetYaxis()->SetTitleSize(0.055);
   Graph_d11x1y116->GetYaxis()->SetTitleOffset(1.5);
   Graph_d11x1y116->GetYaxis()->SetTitleFont(42);
   Graph_d11x1y116->GetZaxis()->SetLabelFont(42);
   Graph_d11x1y116->GetZaxis()->SetLabelSize(0.045);
   Graph_d11x1y116->GetZaxis()->SetTitleSize(0.035);
   Graph_d11x1y116->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_d11x1y116);
   
   grae->Draw("p,same");
   
//   Graph_d10x1y115->Draw();
//   grae->Draw("ap,same");

   for(int i=0; i<nfit; ++i){
     grae->Fit("fitPbPbATLAS_c3","LL","",FitStart,FitEnd); //fit function
   } 
   TH1F *hfunctionATLAS_cent3 = (TH1F*)functionHist(fitPbPbATLAS_c3,PbPb_bayesian_unfolded_spectra_combined_cent3,"hfunctionATLAS_cent3");   
    hRatioATLAS_cent3->Divide(hfunctionATLAS_cent3);   
//   fitppATLAS->Draw("same");
   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#0000ff");
   PbPb_bayesian_unfolded_spectra_combined_cent3->SetMarkerColor(ci);
   PbPb_bayesian_unfolded_spectra_combined_cent3->SetMarkerStyle(24);
   PbPb_bayesian_unfolded_spectra_combined_cent3->SetMarkerSize(1.2);
   PbPb_bayesian_unfolded_spectra_combined_cent3->GetXaxis()->CenterTitle(true);
   PbPb_bayesian_unfolded_spectra_combined_cent3->GetXaxis()->SetLabelFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent3->GetXaxis()->SetLabelOffset(0.01);
   PbPb_bayesian_unfolded_spectra_combined_cent3->GetXaxis()->SetLabelSize(0.045);
   PbPb_bayesian_unfolded_spectra_combined_cent3->GetXaxis()->SetTitleSize(0.055);
   PbPb_bayesian_unfolded_spectra_combined_cent3->GetXaxis()->SetTitleFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent3->GetYaxis()->CenterTitle(true);
   PbPb_bayesian_unfolded_spectra_combined_cent3->GetYaxis()->SetLabelFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent3->GetYaxis()->SetLabelOffset(0.01);
   PbPb_bayesian_unfolded_spectra_combined_cent3->GetYaxis()->SetLabelSize(0.045);
   PbPb_bayesian_unfolded_spectra_combined_cent3->GetYaxis()->SetTitleSize(0.055);
   PbPb_bayesian_unfolded_spectra_combined_cent3->GetYaxis()->SetTitleOffset(1.5);
   PbPb_bayesian_unfolded_spectra_combined_cent3->GetYaxis()->SetTitleFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent3->GetZaxis()->SetLabelFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent3->GetZaxis()->SetLabelSize(0.045);
   PbPb_bayesian_unfolded_spectra_combined_cent3->GetZaxis()->SetTitleSize(0.035);
   PbPb_bayesian_unfolded_spectra_combined_cent3->GetZaxis()->SetTitleFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent3->Draw("same");
   TLegend *leg = new TLegend(0.6,0.65,0.8,0.85,NULL,"BRNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(10);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("NULL","","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("/HepData/8719/d10x1y1","ATLAS 30-40%","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(33);
   entry->SetMarkerSize(1.2);
   entry=leg->AddEntry("/HepData/8719/d11x1y1","ATLAS 40-50%","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(34);
   entry->SetMarkerSize(1.2);
   entry=leg->AddEntry("PbPb_bayesian_unfolded_spectra_combined_cent3","CMS 30-50%","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1.2);
   leg->Draw();
   p_0_1->Modified();
   cATLAS_pbpb->cd();

// ------------>Primitives in pad: p_1_0
   p_1_0 = new TPad("p_1_0", "p_1_0",0.3759095,0.5224719,0.6766371,1);
   p_1_0->Draw();
   p_1_0->cd();
   p_1_0->Range(65,-4,299,2.451613);
   p_1_0->SetFillColor(0);
   p_1_0->SetBorderMode(0);
   p_1_0->SetBorderSize(0);
   p_1_0->SetLogy();
   p_1_0->SetTickx(1);
   p_1_0->SetTicky(1);
   p_1_0->SetLeftMargin(0);
   p_1_0->SetRightMargin(0);
   p_1_0->SetTopMargin(0.07);
   p_1_0->SetBottomMargin(0);
   p_1_0->SetFrameLineColor(0);
   p_1_0->SetFrameBorderMode(0);
   p_1_0->SetFrameLineColor(0);
   p_1_0->SetFrameBorderMode(0);
   
   grae = new TGraphAsymmErrors(8);
   grae->SetName("/HepData/8719/d14x1y1");
   grae->SetTitle(" ");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(33);
   grae->SetMarkerSize(1.2);
   grae->SetPoint(0,44.5,45);
   grae->SetPointError(0,5.5,5.5,2.994659e-06,2.994659e-06);
   grae->SetPoint(1,56.5,13.16667);
   grae->SetPointError(1,6.5,6.5,9.421147e-07,9.421147e-07);
   grae->SetPoint(2,71,3.854167);
   grae->SetPointError(2,8,8,2.559744e-07,2.559744e-07);
   grae->SetPoint(3,89.5,1.125);
   grae->SetPointError(3,10.5,10.5,7.343752e-08,7.343752e-08);
   grae->SetPoint(4,112.5,0.2904167);
   grae->SetPointError(4,12.5,12.5,1.94353e-08,1.94353e-08);
   grae->SetPoint(5,141.5,0.07083333);
   grae->SetPointError(5,16.5,16.5,4.75353e-09,4.75353e-09);
   grae->SetPoint(6,178.5,0.0155);
   grae->SetPointError(6,20.5,20.5,1.080383e-09,1.080383e-09);
   grae->SetPoint(7,225,0.003045833);
   grae->SetPointError(7,26,26,2.318215e-10,2.318215e-10);
   
   TH1F *Graph_d14x1y117 = new TH1F("Graph_d14x1y117"," ",100,65,299);
   Graph_d14x1y117->SetMinimum(0.0001);
   Graph_d14x1y117->SetMaximum(100);
   Graph_d14x1y117->SetDirectory(0);
   Graph_d14x1y117->SetStats(0);
   Graph_d14x1y117->SetFillColor(1);
   Graph_d14x1y117->SetFillStyle(0);
   Graph_d14x1y117->SetLineStyle(0);
   Graph_d14x1y117->SetMarkerStyle(20);
   Graph_d14x1y117->SetMarkerSize(1.2);
   Graph_d14x1y117->GetXaxis()->SetLabelFont(42);
   Graph_d14x1y117->GetXaxis()->SetLabelOffset(0.01);
   Graph_d14x1y117->GetXaxis()->SetLabelSize(0.045);
   Graph_d14x1y117->GetXaxis()->SetTitleSize(0.055);
   Graph_d14x1y117->GetXaxis()->SetTitleFont(42);
   Graph_d14x1y117->GetYaxis()->SetLabelFont(42);
   Graph_d14x1y117->GetYaxis()->SetLabelOffset(0.01);
   Graph_d14x1y117->GetYaxis()->SetLabelSize(0.045);
   Graph_d14x1y117->GetYaxis()->SetTitleSize(0.055);
   Graph_d14x1y117->GetYaxis()->SetTitleOffset(1.5);
   Graph_d14x1y117->GetYaxis()->SetTitleFont(42);
   Graph_d14x1y117->GetZaxis()->SetLabelFont(42);
   Graph_d14x1y117->GetZaxis()->SetLabelSize(0.045);
   Graph_d14x1y117->GetZaxis()->SetTitleSize(0.035);
   Graph_d14x1y117->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_d14x1y117);
   
   grae->Draw("ap");
   for(int ia=0; ia<nfit; ++ia){
     grae->Fit("fitPbPbATLAS_c5","LL","",FitStart,FitEnd); //fit function
   } 
   TH1F *hfunctionATLAS_cent5 = (TH1F*)functionHist(fitPbPbATLAS_c5,PbPb_bayesian_unfolded_spectra_combined_cent5,"hfunctionATLAS_cent5");   
    hRatioATLAS_cent5->Divide(hfunctionATLAS_cent5); 
       
   ci = TColor::GetColor("#0000ff");
   PbPb_bayesian_unfolded_spectra_combined_cent5->SetMarkerColor(ci);
   PbPb_bayesian_unfolded_spectra_combined_cent5->SetMarkerStyle(24);
   PbPb_bayesian_unfolded_spectra_combined_cent5->SetMarkerSize(1.2);
   PbPb_bayesian_unfolded_spectra_combined_cent5->GetXaxis()->CenterTitle(true);
   PbPb_bayesian_unfolded_spectra_combined_cent5->GetXaxis()->SetLabelFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent5->GetXaxis()->SetLabelOffset(0.01);
   PbPb_bayesian_unfolded_spectra_combined_cent5->GetXaxis()->SetLabelSize(0.045);
   PbPb_bayesian_unfolded_spectra_combined_cent5->GetXaxis()->SetTitleSize(0.055);
   PbPb_bayesian_unfolded_spectra_combined_cent5->GetXaxis()->SetTitleFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent5->GetYaxis()->CenterTitle(true);
   PbPb_bayesian_unfolded_spectra_combined_cent5->GetYaxis()->SetLabelFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent5->GetYaxis()->SetLabelOffset(0.01);
   PbPb_bayesian_unfolded_spectra_combined_cent5->GetYaxis()->SetLabelSize(0.045);
   PbPb_bayesian_unfolded_spectra_combined_cent5->GetYaxis()->SetTitleSize(0.055);
   PbPb_bayesian_unfolded_spectra_combined_cent5->GetYaxis()->SetTitleOffset(1.5);
   PbPb_bayesian_unfolded_spectra_combined_cent5->GetYaxis()->SetTitleFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent5->GetZaxis()->SetLabelFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent5->GetZaxis()->SetLabelSize(0.045);
   PbPb_bayesian_unfolded_spectra_combined_cent5->GetZaxis()->SetTitleSize(0.035);
   PbPb_bayesian_unfolded_spectra_combined_cent5->GetZaxis()->SetTitleFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent5->Draw("same");
   
   leg = new TLegend(0.6,0.65,0.8,0.85,NULL,"BRNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(10);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("NULL","","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("/HepData/8719/d14x1y1","ATLAS 70-80%","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(33);
   entry->SetMarkerSize(1.2);
   entry=leg->AddEntry("PbPb_bayesian_unfolded_spectra_combined_cent5","CMS 70-90%","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1.2);
   leg->Draw();
   p_1_0->Modified();
   cATLAS_pbpb->cd();
// ------------>Primitives in pad: p_1_1
   p_1_1 = new TPad("p_1_1", "p_1_1",0.3759095,0,0.6766371,0.5224719);
   p_1_1->Draw();
   p_1_1->cd();
   p_1_1->Range(65,-5.058824,299,2);
   p_1_1->SetFillColor(0);
   p_1_1->SetBorderMode(0);
   p_1_1->SetBorderSize(0);
   p_1_1->SetLogy();
   p_1_1->SetTickx(1);
   p_1_1->SetTicky(1);
   p_1_1->SetLeftMargin(0);
   p_1_1->SetRightMargin(0);
   p_1_1->SetTopMargin(0);
   p_1_1->SetBottomMargin(0.15);
   p_1_1->SetFrameLineColor(0);
   p_1_1->SetFrameBorderMode(0);
   p_1_1->SetFrameLineColor(0);
   p_1_1->SetFrameBorderMode(0);
   
   grae = new TGraphAsymmErrors(9);
   grae->SetName("/HepData/8719/d8x1y1");
   grae->SetTitle("  ");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(33);
   grae->SetMarkerSize(1.2);
   grae->SetPoint(0,56.5,8.870409);
   grae->SetPointError(0,6.5,6.5,2.365369e-05,2.365369e-05);
   grae->SetPoint(1,71,2.564103);
   grae->SetPointError(1,8,8,7.716252e-06,7.716252e-06);
   grae->SetPoint(2,89.5,0.7068607);
   grae->SetPointError(2,10.5,10.5,1.792909e-06,1.792909e-06);
   grae->SetPoint(3,112.5,0.1975052);
   grae->SetPointError(3,12.5,12.5,5.048524e-07,5.048524e-07);
   grae->SetPoint(4,141.5,0.05114345);
   grae->SetPointError(4,16.5,16.5,1.218617e-07,1.218617e-07);
   grae->SetPoint(5,178.5,0.01288981);
   grae->SetPointError(5,20.5,20.5,3.001466e-08,3.001466e-08);
   grae->SetPoint(6,225,0.002647263);
   grae->SetPointError(6,26,26,6.65437e-09,6.65437e-09);
   grae->SetPoint(7,283.5,0.0004830215);
   grae->SetPointError(7,32.5,32.5,1.316242e-09,1.316242e-09);
   grae->SetPoint(8,357,7.415107e-05);
   grae->SetPointError(8,41,41,2.304577e-10,2.304577e-10);
   
   TH1F *Graph_d8x1y118 = new TH1F("Graph_d8x1y118","  ",100,65,299);
   Graph_d8x1y118->SetMinimum(0.0001);
   Graph_d8x1y118->SetMaximum(100);
   Graph_d8x1y118->SetDirectory(0);
   Graph_d8x1y118->SetStats(0);
   Graph_d8x1y118->SetFillColor(1);
   Graph_d8x1y118->SetFillStyle(0);
   Graph_d8x1y118->SetLineStyle(0);
   Graph_d8x1y118->SetMarkerStyle(20);
   Graph_d8x1y118->SetMarkerSize(1.2);
   Graph_d8x1y118->GetXaxis()->SetLabelFont(42);
   Graph_d8x1y118->GetXaxis()->SetLabelOffset(0.01);
   Graph_d8x1y118->GetXaxis()->SetLabelSize(0.045);
   Graph_d8x1y118->GetXaxis()->SetTitleSize(0.055);
   Graph_d8x1y118->GetXaxis()->SetTitleFont(42);
   Graph_d8x1y118->GetYaxis()->SetLabelFont(42);
   Graph_d8x1y118->GetYaxis()->SetLabelOffset(0.01);
   Graph_d8x1y118->GetYaxis()->SetLabelSize(0.045);
   Graph_d8x1y118->GetYaxis()->SetTitleSize(0.055);
   Graph_d8x1y118->GetYaxis()->SetTitleOffset(1.5);
   Graph_d8x1y118->GetYaxis()->SetTitleFont(42);
   Graph_d8x1y118->GetZaxis()->SetLabelFont(42);
   Graph_d8x1y118->GetZaxis()->SetLabelSize(0.045);
   Graph_d8x1y118->GetZaxis()->SetTitleSize(0.035);
   Graph_d8x1y118->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_d8x1y118);
   
   grae->Draw("ap");
   
   grae = new TGraphAsymmErrors(9);
   grae->SetName("/HepData/8719/d9x1y1");
   grae->SetTitle("  ");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(34);
   grae->SetMarkerSize(1.2);
   grae->SetPoint(0,56.5,8.900344);
   grae->SetPointError(0,6.5,6.5,1.355058e-05,1.355058e-05);
   grae->SetPoint(1,71,2.966781);
   grae->SetPointError(1,8,8,4.497138e-06,4.497138e-06);
   grae->SetPoint(2,89.5,0.8075602);
   grae->SetPointError(2,10.5,10.5,1.258835e-06,1.258835e-06);
   grae->SetPoint(3,112.5,0.2199313);
   grae->SetPointError(3,12.5,12.5,3.438945e-07,3.438945e-07);
   grae->SetPoint(4,141.5,0.05704468);
   grae->SetPointError(4,16.5,16.5,8.247878e-08,8.247878e-08);
   grae->SetPoint(5,178.5,0.01317297);
   grae->SetPointError(5,20.5,20.5,1.912115e-08,1.912115e-08);
   grae->SetPoint(6,225,0.002760596);
   grae->SetPointError(6,26,26,4.183832e-09,4.183832e-09);
   grae->SetPoint(7,283.5,0.0005097366);
   grae->SetPointError(7,32.5,32.5,8.232019e-10,8.232019e-10);
   grae->SetPoint(8,357,8.281787e-05);
   grae->SetPointError(8,41,41,1.46696e-10,1.46696e-10);
   
   TH1F *Graph_d9x1y119 = new TH1F("Graph_d9x1y119","  ",100,15.2,432.8);
   Graph_d9x1y119->SetMinimum(7.453595e-05);
   Graph_d9x1y119->SetMaximum(9.790385);
   Graph_d9x1y119->SetDirectory(0);
   Graph_d9x1y119->SetStats(0);
   Graph_d9x1y119->SetFillColor(1);
   Graph_d9x1y119->SetFillStyle(0);
   Graph_d9x1y119->SetLineStyle(0);
   Graph_d9x1y119->SetMarkerStyle(20);
   Graph_d9x1y119->SetMarkerSize(1.2);
   Graph_d9x1y119->GetXaxis()->SetLabelFont(42);
   Graph_d9x1y119->GetXaxis()->SetLabelOffset(0.01);
   Graph_d9x1y119->GetXaxis()->SetLabelSize(0.045);
   Graph_d9x1y119->GetXaxis()->SetTitleSize(0.055);
   Graph_d9x1y119->GetXaxis()->SetTitleFont(42);
   Graph_d9x1y119->GetYaxis()->SetLabelFont(42);
   Graph_d9x1y119->GetYaxis()->SetLabelOffset(0.01);
   Graph_d9x1y119->GetYaxis()->SetLabelSize(0.045);
   Graph_d9x1y119->GetYaxis()->SetTitleSize(0.055);
   Graph_d9x1y119->GetYaxis()->SetTitleOffset(1.5);
   Graph_d9x1y119->GetYaxis()->SetTitleFont(42);
   Graph_d9x1y119->GetZaxis()->SetLabelFont(42);
   Graph_d9x1y119->GetZaxis()->SetLabelSize(0.045);
   Graph_d9x1y119->GetZaxis()->SetTitleSize(0.035);
   Graph_d9x1y119->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_d9x1y119);
   
   grae->Draw("p");
   for(int ib=0; ib<nfit; ++ib){
     grae->Fit("fitPbPbATLAS_c2","LL","",FitStart,FitEnd); //fit function
   }    
   TH1F *hfunctionATLAS_cent2 = (TH1F*)functionHist(fitPbPbATLAS_c2,PbPb_bayesian_unfolded_spectra_combined_cent2,"hfunctionATLAS_cent2");   
    hRatioATLAS_cent2->Divide(hfunctionATLAS_cent2); 
       
   ci = TColor::GetColor("#0000ff");
   PbPb_bayesian_unfolded_spectra_combined_cent2->SetMarkerColor(ci);
   PbPb_bayesian_unfolded_spectra_combined_cent2->SetMarkerStyle(24);
   PbPb_bayesian_unfolded_spectra_combined_cent2->SetMarkerSize(1.2);
   PbPb_bayesian_unfolded_spectra_combined_cent2->GetXaxis()->CenterTitle(true);
   PbPb_bayesian_unfolded_spectra_combined_cent2->GetXaxis()->SetLabelFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent2->GetXaxis()->SetLabelOffset(0.01);
   PbPb_bayesian_unfolded_spectra_combined_cent2->GetXaxis()->SetLabelSize(0.045);
   PbPb_bayesian_unfolded_spectra_combined_cent2->GetXaxis()->SetTitleSize(0.055);
   PbPb_bayesian_unfolded_spectra_combined_cent2->GetXaxis()->SetTitleFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent2->GetYaxis()->CenterTitle(true);
   PbPb_bayesian_unfolded_spectra_combined_cent2->GetYaxis()->SetLabelFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent2->GetYaxis()->SetLabelOffset(0.01);
   PbPb_bayesian_unfolded_spectra_combined_cent2->GetYaxis()->SetLabelSize(0.045);
   PbPb_bayesian_unfolded_spectra_combined_cent2->GetYaxis()->SetTitleSize(0.055);
   PbPb_bayesian_unfolded_spectra_combined_cent2->GetYaxis()->SetTitleOffset(1.5);
   PbPb_bayesian_unfolded_spectra_combined_cent2->GetYaxis()->SetTitleFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent2->GetZaxis()->SetLabelFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent2->GetZaxis()->SetLabelSize(0.045);
   PbPb_bayesian_unfolded_spectra_combined_cent2->GetZaxis()->SetTitleSize(0.035);
   PbPb_bayesian_unfolded_spectra_combined_cent2->GetZaxis()->SetTitleFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent2->Draw("same");
   
   leg = new TLegend(0.6,0.65,0.8,0.85,NULL,"BRNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(10);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("NULL","","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("/HepData/8719/d8x1y1","ATLAS 10-20%","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(33);
   entry->SetMarkerSize(1.2);
   entry=leg->AddEntry("/HepData/8719/d9x1y1","ATLAS 20-30%","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(34);
   entry->SetMarkerSize(1.2);
   entry=leg->AddEntry("PbPb_bayesian_unfolded_spectra_combined_cent2","CMS 10-30%","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1.2);
   leg->Draw();
   p_1_1->Modified();
   cATLAS_pbpb->cd();


// ------------>Primitives in pad: p_2_0
   p_2_0 = new TPad("p_2_0", "p_2_0",0.676637,0.5224719,1,1);
   p_2_0->Draw();
   p_2_0->cd();
   p_2_0->Range(65,-4,316.6129,2.451613);
   p_2_0->SetFillColor(0);
   p_2_0->SetBorderMode(0);
   p_2_0->SetBorderSize(0);
   p_2_0->SetLogy();
   p_2_0->SetTickx(1);
   p_2_0->SetTicky(1);
   p_2_0->SetLeftMargin(0);
   p_2_0->SetRightMargin(0.07);
   p_2_0->SetTopMargin(0.07);
   p_2_0->SetBottomMargin(0);
   p_2_0->SetFrameLineColor(0);
   p_2_0->SetFrameBorderMode(0);
   p_2_0->SetFrameLineColor(0);
   p_2_0->SetFrameBorderMode(0);
   
   grae = new TGraphAsymmErrors(9);
   grae->SetName("/HepData/8719/d12x1y1");
   grae->SetTitle("  ");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(33);
   grae->SetMarkerSize(1.2);
   grae->SetPoint(0,44.5,38.79699);
   grae->SetPointError(0,5.5,5.5,1.081952e-05,1.081952e-05);
   grae->SetPoint(1,56.5,12.93233);
   grae->SetPointError(1,6.5,6.5,3.576525e-06,3.576525e-06);
   grae->SetPoint(2,71,3.857143);
   grae->SetPointError(2,8,8,1.081214e-06,1.081214e-06);
   grae->SetPoint(3,89.5,1.075188);
   grae->SetPointError(3,10.5,10.5,2.963656e-07,2.963656e-07);
   grae->SetPoint(4,112.5,0.2977444);
   grae->SetPointError(4,12.5,12.5,8.163557e-08,8.163557e-08);
   grae->SetPoint(5,141.5,0.07135338);
   grae->SetPointError(5,16.5,16.5,1.968254e-08,1.968254e-08);
   grae->SetPoint(6,178.5,0.01496241);
   grae->SetPointError(6,20.5,20.5,4.313942e-09,4.313942e-09);
   grae->SetPoint(7,225,0.00275188);
   grae->SetPointError(7,26,26,8.801672e-10,8.801672e-10);
   grae->SetPoint(8,283.5,0.0004571428);
   grae->SetPointError(8,32.5,32.5,1.710696e-10,1.710696e-10);
   
   TH1F *Graph_d12x1y120 = new TH1F("Graph_d12x1y120","  ",100,65,299);
   Graph_d12x1y120->SetMinimum(0.0001);
   Graph_d12x1y120->SetMaximum(100);
   Graph_d12x1y120->SetDirectory(0);
   Graph_d12x1y120->SetStats(0);
   Graph_d12x1y120->SetFillColor(1);
   Graph_d12x1y120->SetFillStyle(0);
   Graph_d12x1y120->SetLineStyle(0);
   Graph_d12x1y120->SetMarkerStyle(20);
   Graph_d12x1y120->SetMarkerSize(1.2);
   Graph_d12x1y120->GetXaxis()->SetLabelFont(42);
   Graph_d12x1y120->GetXaxis()->SetLabelOffset(0.01);
   Graph_d12x1y120->GetXaxis()->SetLabelSize(0.045);
   Graph_d12x1y120->GetXaxis()->SetTitleSize(0.055);
   Graph_d12x1y120->GetXaxis()->SetTitleFont(42);
   Graph_d12x1y120->GetYaxis()->SetLabelFont(42);
   Graph_d12x1y120->GetYaxis()->SetLabelOffset(0.01);
   Graph_d12x1y120->GetYaxis()->SetLabelSize(0.045);
   Graph_d12x1y120->GetYaxis()->SetTitleSize(0.055);
   Graph_d12x1y120->GetYaxis()->SetTitleOffset(1.5);
   Graph_d12x1y120->GetYaxis()->SetTitleFont(42);
   Graph_d12x1y120->GetZaxis()->SetLabelFont(42);
   Graph_d12x1y120->GetZaxis()->SetLabelSize(0.045);
   Graph_d12x1y120->GetZaxis()->SetTitleSize(0.035);
   Graph_d12x1y120->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_d12x1y120);
   
   grae->Draw("ap");
   
   grae = new TGraphAsymmErrors(9);
   grae->SetName("/HepData/8719/d13x1y1");
   grae->SetTitle("  ");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(34);
   grae->SetMarkerSize(1.2);
   grae->SetPoint(0,44.5,42.71187);
   grae->SetPointError(0,5.5,5.5,5.79189e-06,5.79189e-06);
   grae->SetPoint(1,56.5,13.13559);
   grae->SetPointError(1,6.5,6.5,1.907665e-06,1.907665e-06);
   grae->SetPoint(2,71,3.915254);
   grae->SetPointError(2,8,8,5.322733e-07,5.322733e-07);
   grae->SetPoint(3,89.5,1.128814);
   grae->SetPointError(3,10.5,10.5,1.55228e-07,1.55228e-07);
   grae->SetPoint(4,112.5,0.2949153);
   grae->SetPointError(4,12.5,12.5,4.130036e-08,4.130036e-08);
   grae->SetPoint(5,141.5,0.07305085);
   grae->SetPointError(5,16.5,16.5,1.007646e-08,1.007646e-08);
   grae->SetPoint(6,178.5,0.01608475);
   grae->SetPointError(6,20.5,20.5,2.284016e-09,2.284016e-09);
   grae->SetPoint(7,225,0.003135593);
   grae->SetPointError(7,26,26,4.806085e-10,4.806085e-10);
   grae->SetPoint(8,283.5,0.0005508475);
   grae->SetPointError(8,32.5,32.5,9.458393e-11,9.458393e-11);
   
   TH1F *Graph_d13x1y121 = new TH1F("Graph_d13x1y121","  ",100,11.3,343.7);
   Graph_d13x1y121->SetMinimum(0.0004957626);
   Graph_d13x1y121->SetMaximum(46.983);
   Graph_d13x1y121->SetDirectory(0);
   Graph_d13x1y121->SetStats(0);
   Graph_d13x1y121->SetFillColor(1);
   Graph_d13x1y121->SetFillStyle(0);
   Graph_d13x1y121->SetLineStyle(0);
   Graph_d13x1y121->SetMarkerStyle(20);
   Graph_d13x1y121->SetMarkerSize(1.2);
   Graph_d13x1y121->GetXaxis()->SetLabelFont(42);
   Graph_d13x1y121->GetXaxis()->SetLabelOffset(0.01);
   Graph_d13x1y121->GetXaxis()->SetLabelSize(0.045);
   Graph_d13x1y121->GetXaxis()->SetTitleSize(0.055);
   Graph_d13x1y121->GetXaxis()->SetTitleFont(42);
   Graph_d13x1y121->GetYaxis()->SetLabelFont(42);
   Graph_d13x1y121->GetYaxis()->SetLabelOffset(0.01);
   Graph_d13x1y121->GetYaxis()->SetLabelSize(0.045);
   Graph_d13x1y121->GetYaxis()->SetTitleSize(0.055);
   Graph_d13x1y121->GetYaxis()->SetTitleOffset(1.5);
   Graph_d13x1y121->GetYaxis()->SetTitleFont(42);
   Graph_d13x1y121->GetZaxis()->SetLabelFont(42);
   Graph_d13x1y121->GetZaxis()->SetLabelSize(0.045);
   Graph_d13x1y121->GetZaxis()->SetTitleSize(0.035);
   Graph_d13x1y121->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_d13x1y121);
   
   grae->Draw("p");
   for(int ic=0; ic<nfit; ++ic){
     grae->Fit("fitPbPbATLAS_c4","LL","",FitStart,FitEnd); //fit function
   } 
   TH1F *hfunctionATLAS_cent4 = (TH1F*)functionHist(fitPbPbATLAS_c4,PbPb_bayesian_unfolded_spectra_combined_cent4,"hfunctionATLAS_cent4");   
    hRatioATLAS_cent4->Divide(hfunctionATLAS_cent4); 
    
   ci = TColor::GetColor("#0000ff");
   PbPb_bayesian_unfolded_spectra_combined_cent4->SetMarkerColor(ci);
   PbPb_bayesian_unfolded_spectra_combined_cent4->SetMarkerStyle(24);
   PbPb_bayesian_unfolded_spectra_combined_cent4->SetMarkerSize(1.2);
   PbPb_bayesian_unfolded_spectra_combined_cent4->GetXaxis()->CenterTitle(true);
   PbPb_bayesian_unfolded_spectra_combined_cent4->GetXaxis()->SetLabelFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent4->GetXaxis()->SetLabelOffset(0.01);
   PbPb_bayesian_unfolded_spectra_combined_cent4->GetXaxis()->SetLabelSize(0.045);
   PbPb_bayesian_unfolded_spectra_combined_cent4->GetXaxis()->SetTitleSize(0.055);
   PbPb_bayesian_unfolded_spectra_combined_cent4->GetXaxis()->SetTitleFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent4->GetYaxis()->CenterTitle(true);
   PbPb_bayesian_unfolded_spectra_combined_cent4->GetYaxis()->SetLabelFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent4->GetYaxis()->SetLabelOffset(0.01);
   PbPb_bayesian_unfolded_spectra_combined_cent4->GetYaxis()->SetLabelSize(0.045);
   PbPb_bayesian_unfolded_spectra_combined_cent4->GetYaxis()->SetTitleSize(0.055);
   PbPb_bayesian_unfolded_spectra_combined_cent4->GetYaxis()->SetTitleOffset(1.5);
   PbPb_bayesian_unfolded_spectra_combined_cent4->GetYaxis()->SetTitleFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent4->GetZaxis()->SetLabelFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent4->GetZaxis()->SetLabelSize(0.045);
   PbPb_bayesian_unfolded_spectra_combined_cent4->GetZaxis()->SetTitleSize(0.035);
   PbPb_bayesian_unfolded_spectra_combined_cent4->GetZaxis()->SetTitleFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent4->Draw("same");
   
   leg = new TLegend(0.6,0.65,0.8,0.85,NULL,"BRNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(10);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("NULL","","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("/HepData/8719/d10x1y1","ATLAS 50-60%","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(33);
   entry->SetMarkerSize(1.2);
   entry=leg->AddEntry("/HepData/8719/d11x1y1","ATLAS 60-70%","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(34);
   entry->SetMarkerSize(1.2);
   entry=leg->AddEntry("PbPb_bayesian_unfolded_spectra_combined_cent4","CMS 50-70%","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1.2);
   leg->Draw();
   p_2_0->Modified();
   cATLAS_pbpb->cd();
   
// ------------>Primitives in pad: p_2_1
   p_2_1 = new TPad("p_2_1", "p_2_1",0.676637,0,1,0.5224719);
   p_2_1->Draw();
   p_2_1->cd();
   p_2_1->Range(65,-5.058824,316.6129,2);
   p_2_1->SetFillColor(0);
   p_2_1->SetBorderMode(0);
   p_2_1->SetBorderSize(0);
   p_2_1->SetLogy();
   p_2_1->SetTickx(1);
   p_2_1->SetTicky(1);
   p_2_1->SetLeftMargin(0);
   p_2_1->SetRightMargin(0.07);
   p_2_1->SetTopMargin(0);
   p_2_1->SetBottomMargin(0.15);
   p_2_1->SetFrameLineColor(0);
   p_2_1->SetFrameBorderMode(0);
   p_2_1->SetFrameLineColor(0);
   p_2_1->SetFrameBorderMode(0);
   
   grae = new TGraphAsymmErrors(9);
   grae->SetName("/HepData/8719/d7x1y1");
   grae->SetTitle("  ");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(33);
   grae->SetMarkerSize(1.2);
   grae->SetPoint(0,56.5,7.974413);
   grae->SetPointError(0,6.5,6.5,3.04322e-05,3.04322e-05);
   grae->SetPoint(1,71,2.379531);
   grae->SetPointError(1,8,8,1.179296e-05,1.179296e-05);
   grae->SetPoint(2,89.5,0.6439232);
   grae->SetPointError(2,10.5,10.5,3.363913e-06,3.363913e-06);
   grae->SetPoint(3,112.5,0.1739872);
   grae->SetPointError(3,12.5,12.5,7.43971e-07,7.43971e-07);
   grae->SetPoint(4,141.5,0.04520256);
   grae->SetPointError(4,16.5,16.5,1.809684e-07,1.809684e-07);
   grae->SetPoint(5,178.5,0.01113006);
   grae->SetPointError(5,20.5,20.5,4.389148e-08,4.389148e-08);
   grae->SetPoint(6,225,0.002430704);
   grae->SetPointError(6,26,26,1.005884e-08,1.005884e-08);
   grae->SetPoint(7,283.5,0.0004392324);
   grae->SetPointError(7,32.5,32.5,2.024494e-09,2.024494e-09);
   grae->SetPoint(8,357,6.396588e-05);
   grae->SetPointError(8,41,41,3.648948e-10,3.648948e-10);
   
   TH1F *Graph_d7x1y122 = new TH1F("Graph_d7x1y122","  ",100,65,299);
   Graph_d7x1y122->SetMinimum(0.0001);
   Graph_d7x1y122->SetMaximum(100);
   Graph_d7x1y122->SetDirectory(0);
   Graph_d7x1y122->SetStats(0);
   Graph_d7x1y122->SetFillColor(1);
   Graph_d7x1y122->SetFillStyle(0);
   Graph_d7x1y122->SetLineStyle(0);
   Graph_d7x1y122->SetMarkerStyle(20);
   Graph_d7x1y122->SetMarkerSize(1.2);
   Graph_d7x1y122->GetXaxis()->SetLabelFont(42);
   Graph_d7x1y122->GetXaxis()->SetLabelOffset(0.01);
   Graph_d7x1y122->GetXaxis()->SetLabelSize(0.045);
   Graph_d7x1y122->GetXaxis()->SetTitleSize(0.055);
   Graph_d7x1y122->GetXaxis()->SetTitleFont(42);
   Graph_d7x1y122->GetYaxis()->SetLabelFont(42);
   Graph_d7x1y122->GetYaxis()->SetLabelOffset(0.01);
   Graph_d7x1y122->GetYaxis()->SetLabelSize(0.045);
   Graph_d7x1y122->GetYaxis()->SetTitleSize(0.055);
   Graph_d7x1y122->GetYaxis()->SetTitleOffset(1.5);
   Graph_d7x1y122->GetYaxis()->SetTitleFont(42);
   Graph_d7x1y122->GetZaxis()->SetLabelFont(42);
   Graph_d7x1y122->GetZaxis()->SetLabelSize(0.045);
   Graph_d7x1y122->GetZaxis()->SetTitleSize(0.035);
   Graph_d7x1y122->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_d7x1y122);
   
   grae->Draw("ap");
   for(int id=0; id<nfit; ++id){
     grae->Fit("fitPbPbATLAS_c0","LL","",FitStart,FitEnd); //fit function
   }   
   TH1F *hfunctionATLAS_cent0 = (TH1F*)functionHist(fitPbPbATLAS_c0,PbPb_bayesian_unfolded_spectra_combined_cent0,"hfunctionATLAS_cent0");   
    hRatioATLAS_cent0->Divide(hfunctionATLAS_cent0);    
   ci = TColor::GetColor("#0000ff");
   PbPb_bayesian_unfolded_spectra_combined_cent0->SetMarkerColor(ci);
   PbPb_bayesian_unfolded_spectra_combined_cent0->SetMarkerStyle(24);
   PbPb_bayesian_unfolded_spectra_combined_cent0->SetMarkerSize(1.2);
   PbPb_bayesian_unfolded_spectra_combined_cent0->GetXaxis()->CenterTitle(true);
   PbPb_bayesian_unfolded_spectra_combined_cent0->GetXaxis()->SetLabelFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent0->GetXaxis()->SetLabelOffset(0.01);
   PbPb_bayesian_unfolded_spectra_combined_cent0->GetXaxis()->SetLabelSize(0.045);
   PbPb_bayesian_unfolded_spectra_combined_cent0->GetXaxis()->SetTitleSize(0.055);
   PbPb_bayesian_unfolded_spectra_combined_cent0->GetXaxis()->SetTitleFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent0->GetYaxis()->CenterTitle(true);
   PbPb_bayesian_unfolded_spectra_combined_cent0->GetYaxis()->SetLabelFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent0->GetYaxis()->SetLabelOffset(0.01);
   PbPb_bayesian_unfolded_spectra_combined_cent0->GetYaxis()->SetLabelSize(0.045);
   PbPb_bayesian_unfolded_spectra_combined_cent0->GetYaxis()->SetTitleSize(0.055);
   PbPb_bayesian_unfolded_spectra_combined_cent0->GetYaxis()->SetTitleOffset(1.5);
   PbPb_bayesian_unfolded_spectra_combined_cent0->GetYaxis()->SetTitleFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent0->GetZaxis()->SetLabelFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent0->GetZaxis()->SetLabelSize(0.045);
   PbPb_bayesian_unfolded_spectra_combined_cent0->GetZaxis()->SetTitleSize(0.035);
   PbPb_bayesian_unfolded_spectra_combined_cent0->GetZaxis()->SetTitleFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent0->Draw("same");
   ci = TColor::GetColor("#ff0000");
   PbPb_bayesian_unfolded_spectra_combined_cent1->SetMarkerColor(ci);
   PbPb_bayesian_unfolded_spectra_combined_cent1->SetMarkerStyle(24);
   PbPb_bayesian_unfolded_spectra_combined_cent1->SetMarkerSize(1.2);
   PbPb_bayesian_unfolded_spectra_combined_cent1->GetXaxis()->CenterTitle(true);
   PbPb_bayesian_unfolded_spectra_combined_cent1->GetXaxis()->SetLabelFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent1->GetXaxis()->SetLabelOffset(0.01);
   PbPb_bayesian_unfolded_spectra_combined_cent1->GetXaxis()->SetLabelSize(0.045);
   PbPb_bayesian_unfolded_spectra_combined_cent1->GetXaxis()->SetTitleSize(0.055);
   PbPb_bayesian_unfolded_spectra_combined_cent1->GetXaxis()->SetTitleFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent1->GetYaxis()->CenterTitle(true);
   PbPb_bayesian_unfolded_spectra_combined_cent1->GetYaxis()->SetLabelFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent1->GetYaxis()->SetLabelOffset(0.01);
   PbPb_bayesian_unfolded_spectra_combined_cent1->GetYaxis()->SetLabelSize(0.045);
   PbPb_bayesian_unfolded_spectra_combined_cent1->GetYaxis()->SetTitleSize(0.055);
   PbPb_bayesian_unfolded_spectra_combined_cent1->GetYaxis()->SetTitleOffset(1.5);
   PbPb_bayesian_unfolded_spectra_combined_cent1->GetYaxis()->SetTitleFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent1->GetZaxis()->SetLabelFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent1->GetZaxis()->SetLabelSize(0.045);
   PbPb_bayesian_unfolded_spectra_combined_cent1->GetZaxis()->SetTitleSize(0.035);
   PbPb_bayesian_unfolded_spectra_combined_cent1->GetZaxis()->SetTitleFont(42);
   PbPb_bayesian_unfolded_spectra_combined_cent1->Draw("same");
   
   leg = new TLegend(0.6,0.65,0.8,0.85,NULL,"BRNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(10);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("NULL","","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("/HepData/8719/d7x1y1","ATLAS 0-10%","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(33);
   entry->SetMarkerSize(1.2);
   entry=leg->AddEntry("PbPb_bayesian_unfolded_spectra_combined_cent0","CMS 0-5%","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1.2);
   entry=leg->AddEntry("PbPb_bayesian_unfolded_spectra_combined_cent1","CMS 5-10%","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1.2);
   leg->Draw();
   p_2_1->Modified();
   cATLAS_pbpb->cd();
   cATLAS_pbpb->Modified();
   cATLAS_pbpb->cd();
   cATLAS_pbpb->SetSelected(cATLAS_pbpb);
   cATLAS_pbpb->SaveAs("Plots/CMShist_ATLASfit_spectra_PbPb.pdf");
   
   TCanvas *cATLAS_pbpbRatio = new TCanvas("cATLAS_pbpbRatio", "",0,0,1200,1000);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   cATLAS_pbpbRatio->Range(0,0,1,1);
   cATLAS_pbpbRatio->SetFillColor(0);
   cATLAS_pbpbRatio->SetBorderMode(0);
   cATLAS_pbpbRatio->SetBorderSize(0);
   cATLAS_pbpbRatio->SetTickx(1);
   cATLAS_pbpbRatio->SetTicky(1);
   cATLAS_pbpbRatio->SetLeftMargin(0.17);
   cATLAS_pbpbRatio->SetRightMargin(0.15);
   cATLAS_pbpbRatio->SetTopMargin(0.03);
   cATLAS_pbpbRatio->SetBottomMargin(0.15);
   cATLAS_pbpbRatio->SetFrameLineColor(0);
   cATLAS_pbpbRatio->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: p_0_0
   TPad *p_0_0 = new TPad("p_0_0", "p_0_0",0,0.5224719,0.3759095,1);
   p_0_0->Draw();
   p_0_0->cd();
   p_0_0->Range(0,0,1,1);
   p_0_0->SetFillColor(0);
   p_0_0->SetBorderMode(0);
   p_0_0->SetBorderSize(0);
   p_0_0->SetTickx(1);
   p_0_0->SetTicky(1);
   p_0_0->SetLeftMargin(0.2);
   p_0_0->SetRightMargin(0);
   p_0_0->SetTopMargin(0.07);
   p_0_0->SetBottomMargin(0);
   p_0_0->SetFrameLineColor(0);
   p_0_0->SetFrameBorderMode(0);
   p_0_0->Modified();
   cATLAS_pbpbRatio->cd();
  
// ------------>Primitives in pad: p_0_1
   p_0_1 = new TPad("p_0_1", "p_0_1",0,0,0.3759095,0.5224719);
   p_0_1->Draw();
   p_0_1->cd();
   p_0_1->Range(6.5,-5.058824,299,2);
   p_0_1->SetFillColor(0);
   p_0_1->SetBorderMode(0);
   p_0_1->SetBorderSize(0);
   p_0_1->SetTickx(1);
   p_0_1->SetTicky(1);
   p_0_1->SetLeftMargin(0.2);
   p_0_1->SetRightMargin(0);
   p_0_1->SetTopMargin(0);
   p_0_1->SetBottomMargin(0.15);
   p_0_1->SetFrameLineColor(0);
   p_0_1->SetFrameBorderMode(0);
   p_0_1->SetFrameLineColor(0);
   p_0_1->SetFrameBorderMode(0);
   hRatioBlank->GetYaxis()->SetTitle("CMS/ATLAS");
   hRatioBlank->GetXaxis()->SetTitle("ak R=0.4 Jet p_{T} (GeV/c)");

hRatioBlank->Draw();
if(doScale) { hRatioATLAS_cent3->Scale(ScaleFactor); }
hRatioATLAS_cent3->Draw("ap,same");
   p_0_1->Modified();
// put a legend here   
   cATLAS_pbpbRatio->cd();
// ------------>Primitives in pad: p_1_0
   p_1_0 = new TPad("p_1_0", "p_1_0",0.3759095,0.5224719,0.6766371,1);
   p_1_0->Draw();
   p_1_0->cd();
   p_1_0->Range(65,-4,299,2.451613);
   p_1_0->SetFillColor(0);
   p_1_0->SetBorderMode(0);
   p_1_0->SetBorderSize(0);
   p_1_0->SetTickx(1);
   p_1_0->SetTicky(1);
   p_1_0->SetLeftMargin(0);
   p_1_0->SetRightMargin(0);
   p_1_0->SetTopMargin(0.07);
   p_1_0->SetBottomMargin(0);
   p_1_0->SetFrameLineColor(0);
   p_1_0->SetFrameBorderMode(0);
   p_1_0->SetFrameLineColor(0);
   p_1_0->SetFrameBorderMode(0);
     hRatioBlank->GetXaxis()->SetTitle("");   
hRatioBlank->Draw();
if(doScale){ hRatioATLAS_cent5->Scale(ScaleFactor); }
hRatioATLAS_cent5->Draw("ap,same");    
// put a legend here
   p_1_0->Modified();
   cATLAS_pbpbRatio->cd();
 // ------------>Primitives in pad: p_1_1
   p_1_1 = new TPad("p_1_1", "p_1_1",0.3759095,0,0.6766371,0.5224719);
   p_1_1->Draw();
   p_1_1->cd();
   p_1_1->Range(65,-5.058824,299,2);
   p_1_1->SetFillColor(0);
   p_1_1->SetBorderMode(0);
   p_1_1->SetBorderSize(0);
   p_1_1->SetTickx(1);
   p_1_1->SetTicky(1);
   p_1_1->SetLeftMargin(0);
   p_1_1->SetRightMargin(0);
   p_1_1->SetTopMargin(0);
   p_1_1->SetBottomMargin(0.15);
   p_1_1->SetFrameLineColor(0);
   p_1_1->SetFrameBorderMode(0);
   p_1_1->SetFrameLineColor(0);
   p_1_1->SetFrameBorderMode(0);
   hRatioBlank->GetXaxis()->SetTitle("ak R=0.4 Jet p_{T} (GeV/c)");
   hRatioBlank->GetYaxis()->SetTitle("");
hRatioBlank->Draw();
if(doScale) { hRatioATLAS_cent2->Scale(ScaleFactor);}
hRatioATLAS_cent2->Draw("ap,same");    
// put a legend here
   p_1_1->Modified();
   cATLAS_pbpbRatio->cd();
   
// ------------>Primitives in pad: p_2_0
   p_2_0 = new TPad("p_2_0", "p_2_0",0.676637,0.5224719,1,1);
   p_2_0->Draw();
   p_2_0->cd();
   p_2_0->Range(65,-4,316.6129,2.451613);
   p_2_0->SetFillColor(0);
   p_2_0->SetBorderMode(0);
   p_2_0->SetBorderSize(0);
   p_2_0->SetTickx(1);
   p_2_0->SetTicky(1);
   p_2_0->SetLeftMargin(0);
   p_2_0->SetRightMargin(0.07);
   p_2_0->SetTopMargin(0.07);
   p_2_0->SetBottomMargin(0);
   p_2_0->SetFrameLineColor(0);
   p_2_0->SetFrameBorderMode(0);
   p_2_0->SetFrameLineColor(0);
   p_2_0->SetFrameBorderMode(0);
     hRatioBlank->GetXaxis()->SetTitle("");
   hRatioBlank->GetYaxis()->SetTitle("");   
hRatioBlank->Draw();
if(doScale) {hRatioATLAS_cent4->Scale(ScaleFactor);}
hRatioATLAS_cent4->Draw("ap,same");    
// put a legend here     
   p_2_0->Modified();
   cATLAS_pbpbRatio->cd();
// ------------>Primitives in pad: p_2_1
   p_2_1 = new TPad("p_2_1", "p_2_1",0.676637,0,1,0.5224719);
   p_2_1->Draw();
   p_2_1->cd();
   p_2_1->Range(65,-5.058824,316.6129,2);
   p_2_1->SetFillColor(0);
   p_2_1->SetBorderMode(0);
   p_2_1->SetBorderSize(0);
   p_2_1->SetTickx(1);
   p_2_1->SetTicky(1);
   p_2_1->SetLeftMargin(0);
   p_2_1->SetRightMargin(0.07);
   p_2_1->SetTopMargin(0);
   p_2_1->SetBottomMargin(0.15);
   p_2_1->SetFrameLineColor(0);
   p_2_1->SetFrameBorderMode(0);
   p_2_1->SetFrameLineColor(0);
   p_2_1->SetFrameBorderMode(0);
   hRatioBlank->GetYaxis()->SetTitle("CMS/ATLAS");
if(doScale)   { hRatioBlank->GetYaxis()->SetTitle("CMS(scaled)/ATLAS"); }  
   hRatioBlank->GetXaxis()->SetTitle("ak R=0.4 Jet p_{T} (GeV/c)");
   
hRatioBlank->Draw();
if(doScale) {hRatioATLAS_cent0->Scale(ScaleFactor);}
hRatioATLAS_cent0->Draw("ap,same");    
// put a legend here        
   p_2_1->Modified();
   cATLAS_pbpbRatio->cd();
   cATLAS_pbpbRatio->Modified();
   cATLAS_pbpbRatio->cd();
   cATLAS_pbpbRatio->SetSelected(cATLAS_pbpbRatio);
   if(doScale){
     cATLAS_pbpbRatio->SaveAs("Plots/CMShist_ATLASfit_ratioScaled_PbPb.pdf");
   } else {
     cATLAS_pbpbRatio->SaveAs("Plots/CMShist_ATLASfit_ratio_PbPb.pdf");
   }
            
#if 0
   Double_t xAxis1[31] = {3, 4, 5, 7, 9, 12, 15, 18, 21, 24, 28, 32, 37, 43, 49, 56, 64, 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 300, 330, 362, 395}; 
   
   TH1F *PP_bayesian_unfolded_spectra = new TH1F("PP_bayesian_unfolded_spectra","Unfolded pp Bayes",30, xAxis1);

   PP_bayesian_unfolded_spectra->Draw("same E1");
   
   TLegend *leg = new TLegend(0.4,0.65,0.6,0.85,NULL,"BRNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(10);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("NULL","","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("/HepData/8719/d2x1y1","ATLAS pp","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(33);
   entry->SetMarkerSize(1.2);
   entry=leg->AddEntry("PP_bayesian_unfolded_spectra","CMS pp","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1.2);
   leg->Draw();
   cATLAS_pp->Modified();
   cATLAS_pp->cd();
   cATLAS_pp->SetSelected(cATLAS_pp);
   
//    for(int ic=0; ic<nfit; ic++){
//      PP_bayesian_unfolded_spectra->Fit("fitppCMS","LL","",50,300); //fit function
//    } 
    hATLASpp->Draw();
   grae->Draw("ap,same");
   PP_bayesian_unfolded_spectra->Draw("same E1");
   leg->Draw();
   cATLAS_pp->SaveAs("Plots/CMShist_ATLASfit_spectra_PbPb.pdf");
   
   TH1F *hRatioATLAS = (TH1F*)PP_bayesian_unfolded_spectra->Clone("hRatioATLAS"); //clone histogram hRatio from h
   TCanvas *cRatio_pp = new TCanvas("cRatio_pp", "",0,0,1200,1000);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   cRatio_pp->Range(-50.00001,-6.302699,538.2353,2.631555);
   cRatio_pp->SetFillColor(0);
   cRatio_pp->SetBorderMode(0);
   cRatio_pp->SetBorderSize(0);
   cRatio_pp->SetTickx(1);
   cRatio_pp->SetTicky(1);
   cRatio_pp->SetLeftMargin(0.17);
   cRatio_pp->SetRightMargin(0.15);
   cRatio_pp->SetTopMargin(0.03);
   cRatio_pp->SetBottomMargin(0.15);
   cRatio_pp->SetFrameLineColor(0);
   cRatio_pp->SetFrameBorderMode(0);
   cRatio_pp->SetFrameLineColor(0);
   cRatio_pp->SetFrameBorderMode(0);
   TH1F *hfunctionATLAS = (TH1F*)functionHist(fitppATLAS,PP_bayesian_unfolded_spectra,"hfunctionATLAS");
//   hfunctionATLAS->Draw();
//   hATLASpp->Draw();
   hRatioATLAS->Divide(hfunctionATLAS);
   TH1F *hRatioBlank = new TH1F("hRatioBlank"," ",100,50,300);
   hRatioBlank->SetMinimum(0);
   hRatioBlank->SetMaximum(1.2);
   hRatioBlank->SetDirectory(0);
   hRatioBlank->SetStats(0);
   hRatioBlank->SetFillColor(1);
   hRatioBlank->SetFillStyle(0);
   hRatioBlank->SetLineStyle(0);
   hRatioBlank->SetMarkerStyle(20);
   hRatioBlank->SetMarkerSize(1.2);
   hRatioBlank->GetXaxis()->SetTitle("ak R=0.4 Jet p_{T} (GeV/c)");
   hRatioBlank->GetXaxis()->SetLabelFont(42);
   hRatioBlank->GetXaxis()->SetLabelOffset(0.01);
   hRatioBlank->GetXaxis()->SetLabelSize(0.045);
   hRatioBlank->GetXaxis()->SetTitleSize(0.055);
   hRatioBlank->GetXaxis()->SetTitleFont(42);
   hRatioBlank->GetYaxis()->SetTitle("CMS/ATLAS #frac{d^{2}#sigma}{dp_{T} d#eta} nb");
   hRatioBlank->GetYaxis()->SetLabelFont(42);
   hRatioBlank->GetYaxis()->SetLabelOffset(0.01);
   hRatioBlank->GetYaxis()->SetLabelSize(0.045);
   hRatioBlank->GetYaxis()->SetTitleSize(0.055);
   hRatioBlank->GetYaxis()->SetTitleOffset(1.5);
   hRatioBlank->GetYaxis()->SetTitleFont(42);
   hRatioBlank->GetZaxis()->SetLabelFont(42);
   hRatioBlank->GetZaxis()->SetLabelSize(0.045);
   hRatioBlank->GetZaxis()->SetTitleSize(0.035);
   hRatioBlank->GetZaxis()->SetTitleFont(42);
   hRatioBlank->Draw();   
//   hRatioATLAS->Scale(5.3/4);
   hRatioATLAS->Draw("ap,same");
   
   cRatio_pp->SaveAs("Plots/CMShist_ATLASfit_ratio_PbPb.pdf");
#endif 
  // TH1F* hBinByBinCor = (TH1F*)functionHist(f,hBinByBinCorRaw,Form("hBinByBinCor_cent%d",i));
//    TH1F *hRatioATLAS = (TH1F*)g->Clone("hRatioATLAS"); //clone histogram hRatio from h
  
   
}
