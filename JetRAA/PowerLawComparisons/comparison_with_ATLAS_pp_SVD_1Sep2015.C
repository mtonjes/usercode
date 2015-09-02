// run with: root -l 'comparison_with_ATLAS_pp_SVD_1Sep2015.C(10,60,320,"")'
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

void comparison_with_ATLAS_pp_SVD_1Sep2015(Int_t nfit=6, Int_t FitStart=60, Int_t FitEnd=300, Option_t *FitOpt="IWL"){
     TH1::SetDefaultSumw2();
   gStyle->SetOptFit(1);     
   gStyle->SetOptStat(0);
   TF1 *fitppATLAS = new TF1("fitppATLAS","[0]*pow(x+[2],[1])"); //create function
   fitppATLAS->SetParameters(1e10,-5,0);
   fitppATLAS->SetLineColor(kRed);   
   TF1 *fitppCMS = new TF1("fitppCMS","[0]*pow(x+[2],[1])"); //create function
   fitppCMS->SetParameters(1e10,-5,0);
   fitppCMS->SetLineColor(kGreen);   
    //=========Macro generated from canvas: cATLAS_pp_fit/
//=========  (Tue Sep  1 16:39:38 2015) by ROOT version5.32/00
   Double_t xAxis2128[13] = {31, 39, 50, 63, 79, 100, 125, 158, 199, 251, 316, 398, 501}; 
   TH1F *uATLAS_PP_R4 = new TH1F("uATLAS_PP_R4"," ",12, xAxis2128);
   uATLAS_PP_R4->SetBinContent(0,29.95905);
   uATLAS_PP_R4->SetBinContent(2,55.7);
   uATLAS_PP_R4->SetBinContent(3,16.9);
   uATLAS_PP_R4->SetBinContent(4,4.85);
   uATLAS_PP_R4->SetBinContent(5,1.42);
   uATLAS_PP_R4->SetBinContent(6,0.364);
   uATLAS_PP_R4->SetBinContent(7,0.0882);
   uATLAS_PP_R4->SetBinContent(8,0.0197);
   uATLAS_PP_R4->SetBinContent(9,0.00406);
   uATLAS_PP_R4->SetBinContent(10,0.000735);
   uATLAS_PP_R4->SetBinContent(11,0.000114);
   uATLAS_PP_R4->SetBinContent(12,1.41e-05);
   uATLAS_PP_R4->SetBinError(0,29.95905);
   uATLAS_PP_R4->SetBinError(2,7.828377);
   uATLAS_PP_R4->SetBinError(3,2.625436);
   uATLAS_PP_R4->SetBinError(4,0.6276957);
   uATLAS_PP_R4->SetBinError(5,0.1878054);
   uATLAS_PP_R4->SetBinError(6,0.04772427);
   uATLAS_PP_R4->SetBinError(7,0.01103805);
   uATLAS_PP_R4->SetBinError(8,0.002292152);
   uATLAS_PP_R4->SetBinError(9,0.0004822521);
   uATLAS_PP_R4->SetBinError(10,8.981748e-05);
   uATLAS_PP_R4->SetBinError(11,1.442494e-05);
   uATLAS_PP_R4->SetBinError(12,1.98855e-06);
   uATLAS_PP_R4->SetEntries(12);
   uATLAS_PP_R4->SetStats(0);

   for(int i=0; i<nfit; ++i){
     uATLAS_PP_R4->Fit("fitppATLAS",FitOpt,"",FitStart,FitEnd); //fit function
   }    
   
   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   uATLAS_PP_R4->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   uATLAS_PP_R4->SetMarkerColor(ci);
   uATLAS_PP_R4->SetMarkerStyle(24);
   uATLAS_PP_R4->GetXaxis()->SetTitle("ak4PF Jet p_{T} (GeV/c)");
   uATLAS_PP_R4->GetXaxis()->CenterTitle(true);
   uATLAS_PP_R4->GetXaxis()->SetNoExponent();
   uATLAS_PP_R4->GetXaxis()->SetNdivisions(505);
   uATLAS_PP_R4->GetXaxis()->SetLabelFont(43);
   uATLAS_PP_R4->GetXaxis()->SetLabelSize(20);
   uATLAS_PP_R4->GetXaxis()->SetTitleSize(22);
   uATLAS_PP_R4->GetXaxis()->SetTitleOffset(2);
   uATLAS_PP_R4->GetXaxis()->SetTitleFont(43);
   uATLAS_PP_R4->GetYaxis()->SetTitle("#frac{d#sigma}{dp_{T} d#eta}");
   uATLAS_PP_R4->GetYaxis()->CenterTitle(true);
   uATLAS_PP_R4->GetYaxis()->SetNdivisions(610);
   uATLAS_PP_R4->GetYaxis()->SetLabelFont(43);
   uATLAS_PP_R4->GetYaxis()->SetLabelSize(20);
   uATLAS_PP_R4->GetYaxis()->SetTitleSize(22);
   uATLAS_PP_R4->GetYaxis()->SetTitleOffset(2);
   uATLAS_PP_R4->GetYaxis()->SetTitleFont(43);
   uATLAS_PP_R4->GetZaxis()->SetLabelFont(42);
   uATLAS_PP_R4->GetZaxis()->SetLabelSize(0.035);
   uATLAS_PP_R4->GetZaxis()->SetTitleSize(0.035);
   uATLAS_PP_R4->GetZaxis()->SetTitleFont(42);
//   uATLAS_PP_R4->Draw("");
 
 // define CMS results rebinned
   Double_t xAxis2129[11] = {30, 40, 50, 60, 80, 100, 120, 160, 200, 250, 320}; 
   
   TH1F *uPP_R4_ATLASComp = new TH1F("uPP_R4_ATLASComp","Unfold Matrix refpt jtpt from trigger addition R4 20_eta_20 ",10, xAxis2129);
   uPP_R4_ATLASComp->SetBinContent(0,189.1072);
   uPP_R4_ATLASComp->SetBinContent(1,93.24554);
   uPP_R4_ATLASComp->SetBinContent(2,49.35732);
   uPP_R4_ATLASComp->SetBinContent(3,18.96114);
   uPP_R4_ATLASComp->SetBinContent(4,5.508864);
   uPP_R4_ATLASComp->SetBinContent(5,1.265142);
   uPP_R4_ATLASComp->SetBinContent(6,0.3765135);
   uPP_R4_ATLASComp->SetBinContent(7,0.09259047);
   uPP_R4_ATLASComp->SetBinContent(8,0.01665824);
   uPP_R4_ATLASComp->SetBinContent(9,0.003578481);
   uPP_R4_ATLASComp->SetBinContent(10,0.0006783513);
   uPP_R4_ATLASComp->SetBinContent(11,0.01062075);
   uPP_R4_ATLASComp->SetBinError(0,3.111601);
   uPP_R4_ATLASComp->SetBinError(1,1.727673);
   uPP_R4_ATLASComp->SetBinError(2,0.5937772);
   uPP_R4_ATLASComp->SetBinError(3,0.08320043);
   uPP_R4_ATLASComp->SetBinError(4,0.0162068);
   uPP_R4_ATLASComp->SetBinError(5,0.003537616);
   uPP_R4_ATLASComp->SetBinError(6,0.001245648);
   uPP_R4_ATLASComp->SetBinError(7,0.0003453389);
   uPP_R4_ATLASComp->SetBinError(8,0.0001016287);
   uPP_R4_ATLASComp->SetBinError(9,3.382898e-05);
   uPP_R4_ATLASComp->SetBinError(10,9.528861e-06);
   uPP_R4_ATLASComp->SetBinError(11,0.0004386907);
   uPP_R4_ATLASComp->SetEntries(212);
   uPP_R4_ATLASComp->SetStats(0);

   ci = TColor::GetColor("#000099");
   uPP_R4_ATLASComp->SetLineColor(ci);

   ci = TColor::GetColor("#00ff00");
   uPP_R4_ATLASComp->SetMarkerColor(ci);
   uPP_R4_ATLASComp->SetMarkerStyle(27);
   uPP_R4_ATLASComp->GetXaxis()->CenterTitle(true);
   uPP_R4_ATLASComp->GetXaxis()->SetLabelFont(42);
   uPP_R4_ATLASComp->GetXaxis()->SetLabelSize(0.035);
   uPP_R4_ATLASComp->GetXaxis()->SetTitleSize(0.035);
   uPP_R4_ATLASComp->GetXaxis()->SetTitleFont(42);
   uPP_R4_ATLASComp->GetYaxis()->CenterTitle(true);
   uPP_R4_ATLASComp->GetYaxis()->SetLabelFont(42);
   uPP_R4_ATLASComp->GetYaxis()->SetLabelSize(0.035);
   uPP_R4_ATLASComp->GetYaxis()->SetTitleSize(0.035);
   uPP_R4_ATLASComp->GetYaxis()->SetTitleFont(42);
   uPP_R4_ATLASComp->GetZaxis()->SetLabelFont(42);
   uPP_R4_ATLASComp->GetZaxis()->SetLabelSize(0.035);
   uPP_R4_ATLASComp->GetZaxis()->SetTitleSize(0.035);
   uPP_R4_ATLASComp->GetZaxis()->SetTitleFont(42);
//   uPP_R4_ATLASComp->Scale(1/0.966);
   // clone before fit so I don't get that stupid line in the ratio plot
   TH1F *hRatioCMS_axes = (TH1F*)uPP_R4_ATLASComp->Clone("hRatioCMS_axes");
    for(int ic=0; ic<nfit; ic++){
//      uPP_R4_ATLASComp->Fit("fitppCMS",FitOpt,"",60,300); //fit function    
      uPP_R4_ATLASComp->Fit("fitppCMS",FitOpt,"",FitStart,FitEnd); //fit function
    }   

   TCanvas *cATLAS_pp_fit = new TCanvas("cATLAS_pp_fit", "",0,0,1200,1000);
   gStyle->SetOptStat(0);
   cATLAS_pp_fit->Range(-27.75,-6.130128,559.75,2.992811);
   cATLAS_pp_fit->SetFillColor(0);
   cATLAS_pp_fit->SetBorderMode(0);
   cATLAS_pp_fit->SetBorderSize(2);
   cATLAS_pp_fit->SetLogy();
   cATLAS_pp_fit->SetFrameBorderMode(0);
   cATLAS_pp_fit->SetFrameBorderMode(0);
   
      
   uATLAS_PP_R4->Draw("");     
   uPP_R4_ATLASComp->Draw("same");
   
   TLegend *leg = new TLegend(0.2,0.2,0.5,0.4,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("uPP_R4_ATLASComp","CMS PP, R=0.4","pl");

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#00ff00");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(27);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("uATLAS_PP_R4","ATLAS PP, R=0.4","pl");

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1);
   leg->Draw();
   
   TPaveText *pt = new TPaveText(0.4845652,0.94,0.5154348,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText(" ");
   pt->Draw();
   cATLAS_pp_fit->Modified();
   cATLAS_pp_fit->cd();
   cATLAS_pp_fit->SetSelected(cATLAS_pp_fit);
   cATLAS_pp_fit->SaveAs("Plots/ATLAS_CMS_SVD_powerlawFit_ppSpectra.pdf");

   uATLAS_PP_R4->Draw("");     
   uPP_R4_ATLASComp->Draw("same");
   
   TH1F *hFitRatioCMS = (TH1F*)functionHist(fitppCMS,hRatioCMS_axes,"hFitRatioCMS"); //make histo hFitRatioCMS from fitppCMS function with hRatioCMS_axes bins
   TH1F *hFitBottomATLAS = (TH1F*)functionHist(fitppATLAS,hRatioCMS_axes,"hFitBottomATLAS"); // make histo hFitBottomATLAS from fitppATLAS with hRatioCMS_axes bins
   hFitRatioCMS->Divide(hFitBottomATLAS);
   hFitRatioCMS->SetMarkerColor(kBlue);
   hFitRatioCMS->SetMarkerStyle(25);
   hFitRatioCMS->SetLineColor(kBlue);
   
   TCanvas *cRatio_pp = new TCanvas("cRatio_pp", "",0,0,1200,600);
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
   TH1F *hRatioBlank = new TH1F("hRatioBlank"," ",100,50,300);
   hRatioBlank->SetMinimum(0.5);
   hRatioBlank->SetMaximum(1.5);
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
//   hFitRatioATLAS->Scale(5.3/4);
 //  hFitRatioCMS->Scale(1/0.963);
   hFitRatioCMS->Draw("ap,same");
//   hRatioATLAS->Draw("ap,same");
//   hRatioATLASHist->Draw("ap,same");
   
   cRatio_pp->SaveAs("Plots/CMSfit_ATLASfit_ratio_pp.pdf");   
//   hFitRatioATLAS->SetLineColor(0);
//   TH1F *hRatioATLAS = (TH1F*)uPP_R4_SVD->Clone("hRatioATLAS"); //clone histogram hRatio from h

   
}
