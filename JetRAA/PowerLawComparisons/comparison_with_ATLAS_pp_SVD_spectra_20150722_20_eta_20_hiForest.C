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

void comparison_with_ATLAS_pp_SVD_spectra_20150722_20_eta_20_hiForest(Int_t nfit=6, Int_t FitStart=50, Int_t FitEnd=450){

//=========Macro generated from canvas: cATLAS_pp/
//=========  (Wed Jul 22 23:01:26 2015) by ROOT version5.32/00
   TCanvas *cATLAS_pp = new TCanvas("cATLAS_pp", "",0,0,1200,1000);
     TH1::SetDefaultSumw2();
   gStyle->SetOptFit(1);     
   gStyle->SetOptStat(0);
   cATLAS_pp->Range(-3.725291e-06,-5.878322,500,3.279288);
   cATLAS_pp->SetFillColor(0);
   cATLAS_pp->SetBorderMode(0);
   cATLAS_pp->SetBorderSize(2);
   cATLAS_pp->SetLogy();
   cATLAS_pp->SetFrameBorderMode(0);
   cATLAS_pp->SetFrameBorderMode(0);
   TF1 *fitppATLAS = new TF1("fitppATLAS","[0]*pow(x+[2],[1])"); //create function
   fitppATLAS->SetParameters(1e10,-5,0);
   fitppATLAS->SetLineColor(kRed);   
   TF1 *fitppCMS = new TF1("fitppCMS","[0]*pow(x+[2],[1])"); //create function
   fitppCMS->SetParameters(1e10,-5,0);
   fitppCMS->SetLineColor(kBlue);   
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(12);
   grae->SetName("/HepData/8719/d2x1y1");
   grae->SetTitle(" ");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(33);
   grae->SetPoint(0,35,180);
   grae->SetPointError(0,4,4,29.95905,29.95905);
   grae->SetPoint(1,44.5,55.7);
   grae->SetPointError(1,5.5,5.5,7.828377,7.828377);
   grae->SetPoint(2,56.5,16.9);
   grae->SetPointError(2,6.5,6.5,2.625436,2.625436);
   grae->SetPoint(3,71,4.85);
   grae->SetPointError(3,8,8,0.6276957,0.6276957);
   grae->SetPoint(4,89.5,1.42);
   grae->SetPointError(4,10.5,10.5,0.1878054,0.1878054);
   grae->SetPoint(5,112.5,0.364);
   grae->SetPointError(5,12.5,12.5,0.04772427,0.04772427);
   grae->SetPoint(6,141.5,0.0882);
   grae->SetPointError(6,16.5,16.5,0.01103805,0.01103805);
   grae->SetPoint(7,178.5,0.0197);
   grae->SetPointError(7,20.5,20.5,0.002292152,0.002292152);
   grae->SetPoint(8,225,0.00406);
   grae->SetPointError(8,26,26,0.0004822521,0.0004822521);
   grae->SetPoint(9,283.5,0.000735);
   grae->SetPointError(9,32.5,32.5,8.981748e-05,8.981748e-05);
   grae->SetPoint(10,357,0.000114);
   grae->SetPointError(10,41,41,1.442494e-05,1.442494e-05);
   grae->SetPoint(11,449.5,1.41e-05);
   grae->SetPointError(11,51.5,51.5,1.98855e-06,1.98855e-06);
   
   TH1F *hATLASpp = new TH1F("hATLASpp"," ",100,50,450);
   hATLASpp->SetMinimum(1.090031e-05);
   hATLASpp->SetMaximum(230.955);
   hATLASpp->SetDirectory(0);
   hATLASpp->SetStats(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   hATLASpp->SetLineColor(ci);
   hATLASpp->GetXaxis()->SetTitle("ak R=0.4 Jet p_{T} (GeV/c)");
   hATLASpp->GetXaxis()->SetLabelFont(42);
   hATLASpp->GetXaxis()->SetLabelSize(0.035);
   hATLASpp->GetXaxis()->SetTitleSize(0.035);
   hATLASpp->GetXaxis()->SetTitleFont(42);
   hATLASpp->GetYaxis()->SetTitle("#frac{d^{2}#sigma}{dp_{T} d#eta} nb");
   hATLASpp->GetYaxis()->SetLabelFont(42);
   hATLASpp->GetYaxis()->SetLabelSize(0.035);
   hATLASpp->GetYaxis()->SetTitleSize(0.035);
   hATLASpp->GetYaxis()->SetTitleFont(42);
   hATLASpp->GetZaxis()->SetLabelFont(42);
   hATLASpp->GetZaxis()->SetLabelSize(0.035);
   hATLASpp->GetZaxis()->SetTitleSize(0.035);
   hATLASpp->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(hATLASpp);
   hATLASpp->Draw();
   grae->Draw("ap,same");
   
   for(int i=0; i<nfit; ++i){
     grae->Fit("fitppATLAS","LL","",FitStart,FitEnd); //fit function
   } 
      
   Double_t xAxis2086[15] = {50, 60, 70, 80, 90, 100, 110, 130, 150, 170, 190, 210, 240, 270, 300}; 
   
   TH1F *uPP_R4_SVD = new TH1F("uPP_R4_SVD","Unfold Matrix refpt jtpt from trigger addition R4 20_eta_20 ",14, xAxis2086);
   uPP_R4_SVD->SetBinContent(0,320.4344);
   uPP_R4_SVD->SetBinContent(1,18.31659);
   uPP_R4_SVD->SetBinContent(2,7.348096);
   uPP_R4_SVD->SetBinContent(3,3.295203);
   uPP_R4_SVD->SetBinContent(4,1.60486);
   uPP_R4_SVD->SetBinContent(5,0.8393627);
   uPP_R4_SVD->SetBinContent(6,0.4622419);
   uPP_R4_SVD->SetBinContent(7,0.2119189);
   uPP_R4_SVD->SetBinContent(8,0.07964096);
   uPP_R4_SVD->SetBinContent(9,0.0330097);
   uPP_R4_SVD->SetBinContent(10,0.01486732);
   uPP_R4_SVD->SetBinContent(11,0.007179563);
   uPP_R4_SVD->SetBinContent(12,0.003214285);
   uPP_R4_SVD->SetBinContent(13,0.001317327);
   uPP_R4_SVD->SetBinContent(14,0.0005884789);
   uPP_R4_SVD->SetBinContent(15,0.0169141);
   uPP_R4_SVD->SetBinError(0,1.028773);
   uPP_R4_SVD->SetBinError(1,0.04990473);
   uPP_R4_SVD->SetBinError(2,0.01308245);
   uPP_R4_SVD->SetBinError(3,0.006804986);
   uPP_R4_SVD->SetBinError(4,0.003260532);
   uPP_R4_SVD->SetBinError(5,0.001534405);
   uPP_R4_SVD->SetBinError(6,0.001026545);
   uPP_R4_SVD->SetBinError(7,0.0004263077);
   uPP_R4_SVD->SetBinError(8,0.0002173216);
   uPP_R4_SVD->SetBinError(9,0.0001177803);
   uPP_R4_SVD->SetBinError(10,6.555553e-05);
   uPP_R4_SVD->SetBinError(11,3.980599e-05);
   uPP_R4_SVD->SetBinError(12,1.938485e-05);
   uPP_R4_SVD->SetBinError(13,1.257981e-05);
   uPP_R4_SVD->SetBinError(14,8.729444e-06);
   uPP_R4_SVD->SetBinError(15,0.0002215048);
   uPP_R4_SVD->SetEntries(216);
   uPP_R4_SVD->SetStats(0);

   ci = TColor::GetColor("#000099");
   uPP_R4_SVD->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   uPP_R4_SVD->SetMarkerColor(ci);
   uPP_R4_SVD->SetMarkerStyle(24);
   uPP_R4_SVD->GetXaxis()->CenterTitle(true);
   uPP_R4_SVD->GetXaxis()->SetLabelFont(42);
   uPP_R4_SVD->GetXaxis()->SetLabelSize(0.035);
   uPP_R4_SVD->GetXaxis()->SetTitleSize(0.035);
   uPP_R4_SVD->GetXaxis()->SetTitleFont(42);
   uPP_R4_SVD->GetYaxis()->CenterTitle(true);
   uPP_R4_SVD->GetYaxis()->SetLabelFont(42);
   uPP_R4_SVD->GetYaxis()->SetLabelSize(0.035);
   uPP_R4_SVD->GetYaxis()->SetTitleSize(0.035);
   uPP_R4_SVD->GetYaxis()->SetTitleFont(42);
   uPP_R4_SVD->GetZaxis()->SetLabelFont(42);
   uPP_R4_SVD->GetZaxis()->SetLabelSize(0.035);
   uPP_R4_SVD->GetZaxis()->SetTitleSize(0.035);
   uPP_R4_SVD->GetZaxis()->SetTitleFont(42);
   uPP_R4_SVD->Draw("same E1");
   TBox *box = new TBox(60,7.108492,70,7.587699);
   box->SetFillColor(2);
   box->SetFillStyle(0);
   box->SetLineColor(2);
   box->Draw();
   box = new TBox(70,3.186674,80,3.403731);
   box->SetFillColor(2);
   box->SetFillStyle(0);
   box->SetLineColor(2);
   box->Draw();
   box = new TBox(80,1.551541,90,1.658179);
   box->SetFillColor(2);
   box->SetFillStyle(0);
   box->SetLineColor(2);
   box->Draw();
   box = new TBox(90,0.8111346,100,0.8675909);
   box->SetFillColor(2);
   box->SetFillStyle(0);
   box->SetLineColor(2);
   box->Draw();
   box = new TBox(100,0.4464541,110,0.4780297);
   box->SetFillColor(2);
   box->SetFillStyle(0);
   box->SetLineColor(2);
   box->Draw();
   box = new TBox(110,0.2045159,130,0.2193219);
   box->SetFillColor(2);
   box->SetFillStyle(0);
   box->SetLineColor(2);
   box->Draw();
   box = new TBox(130,0.07677678,150,0.08250514);
   box->SetFillColor(2);
   box->SetFillStyle(0);
   box->SetLineColor(2);
   box->Draw();
   box = new TBox(150,0.03180206,170,0.03421734);
   box->SetFillColor(2);
   box->SetFillStyle(0);
   box->SetLineColor(2);
   box->Draw();
   box = new TBox(170,0.01431415,190,0.01542048);
   box->SetFillColor(2);
   box->SetFillStyle(0);
   box->SetLineColor(2);
   box->Draw();
   box = new TBox(190,0.006909775,210,0.007449351);
   box->SetFillColor(2);
   box->SetFillStyle(0);
   box->SetLineColor(2);
   box->Draw();
   box = new TBox(210,0.003092187,240,0.003336382);
   box->SetFillColor(2);
   box->SetFillStyle(0);
   box->SetLineColor(2);
   box->Draw();
   box = new TBox(240,0.001266417,270,0.001368238);
   box->SetFillColor(2);
   box->SetFillStyle(0);
   box->SetLineColor(2);
   box->Draw();
   box = new TBox(270,0.00056544,300,0.0006115177);
   box->SetFillColor(2);
   box->SetFillStyle(0);
   box->SetLineColor(2);
   box->Draw();
   
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
   entry->SetTextFont(62);
   entry=leg->AddEntry("/HepData/8719/d2x1y1","ATLAS pp","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(33);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("uPP_R4_SVD","CMS pp","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000ff");
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
   cATLAS_pp->Modified();
   cATLAS_pp->cd();
   cATLAS_pp->SetSelected(cATLAS_pp);
   
    hATLASpp->Draw();
   grae->Draw("ap,same");
   uPP_R4_SVD->Draw("same E1");
   leg->Draw();
   cATLAS_pp->SaveAs("Plots/CMShist_ATLASfit_spectra_pp.pdf");
   TH1F *hRatioATLAS = (TH1F*)uPP_R4_SVD->Clone("hRatioATLAS"); //clone histogram hRatio from h
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
   TH1F *hfunctionATLAS = (TH1F*)functionHist(fitppATLAS,uPP_R4_SVD,"hfunctionATLAS");
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
   hRatioBlank->GetYaxis()->SetTitle("CMS*(5.3/4)/ATLAS #frac{d^{2}#sigma}{dp_{T} d#eta} nb");
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
   hRatioATLAS->Scale(5.3/4);
   hRatioATLAS->Draw("ap,same");
   
   cRatio_pp->SaveAs("Plots/CMShist_ATLASfit_ratio_pp.pdf");
   
}
