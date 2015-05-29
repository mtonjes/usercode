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

void PowerLawFitRatio_ATLASpp(Int_t nfit=6, Int_t FitStart=50, Int_t FitEnd=450){
  TH1::SetDefaultSumw2();
  gStyle->SetOptStat(00000000);
  
  TH1F * ppATLAS, ppCMS;
   TF1 *fitppATLAS = new TF1("fitppATLAS","[0]*pow(x+[2],[1])"); //create function
   fitppATLAS->SetParameters(1e10,-5,0);
   fitppATLAS->SetLineColor(kRed);   
   TF1 *fitppCMS = new TF1("fitppCMS","[0]*pow(x+[2],[1])"); //create function
   fitppCMS->SetParameters(1e10,-5,0);
   fitppCMS->SetLineColor(kBlue);   
   
   TCanvas *cATLAS_pp = new TCanvas("cATLAS_pp", "",0,0,1200,1000);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   cATLAS_pp->Range(-50.00001,-6.302699,538.2353,2.631555);
   cATLAS_pp->SetFillColor(0);
   cATLAS_pp->SetBorderMode(0);
   cATLAS_pp->SetBorderSize(0);
   cATLAS_pp->SetLogy();
   cATLAS_pp->SetTickx(1);
   cATLAS_pp->SetTicky(1);
   cATLAS_pp->SetLeftMargin(0.17);
   cATLAS_pp->SetRightMargin(0.15);
   cATLAS_pp->SetTopMargin(0.03);
   cATLAS_pp->SetBottomMargin(0.15);
   cATLAS_pp->SetFrameLineColor(0);
   cATLAS_pp->SetFrameBorderMode(0);
   cATLAS_pp->SetFrameLineColor(0);
   cATLAS_pp->SetFrameBorderMode(0);
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(12);
   grae->SetName("/HepData/8719/d2x1y1");
   grae->SetTitle(" ");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(33);
   grae->SetMarkerSize(1.2);
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
   hATLASpp->SetFillColor(1);
   hATLASpp->SetFillStyle(0);
   hATLASpp->SetLineStyle(0);
   hATLASpp->SetMarkerStyle(20);
   hATLASpp->SetMarkerSize(1.2);
   hATLASpp->GetXaxis()->SetTitle("ak R=0.4 Jet p_{T} (GeV/c)");
   hATLASpp->GetXaxis()->SetLabelFont(42);
   hATLASpp->GetXaxis()->SetLabelOffset(0.01);
   hATLASpp->GetXaxis()->SetLabelSize(0.045);
   hATLASpp->GetXaxis()->SetTitleSize(0.055);
   hATLASpp->GetXaxis()->SetTitleFont(42);
   hATLASpp->GetYaxis()->SetTitle("#frac{d^{2}#sigma}{dp_{T} d#eta} nb");
   hATLASpp->GetYaxis()->SetLabelFont(42);
   hATLASpp->GetYaxis()->SetLabelOffset(0.01);
   hATLASpp->GetYaxis()->SetLabelSize(0.045);
   hATLASpp->GetYaxis()->SetTitleSize(0.055);
   hATLASpp->GetYaxis()->SetTitleOffset(1.5);
   hATLASpp->GetYaxis()->SetTitleFont(42);
   hATLASpp->GetZaxis()->SetLabelFont(42);
   hATLASpp->GetZaxis()->SetLabelSize(0.045);
   hATLASpp->GetZaxis()->SetTitleSize(0.035);
   hATLASpp->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(hATLASpp);
   hATLASpp->Draw();
   grae->Draw("ap,same");

   for(int i=0; i<nfit; ++i){
     grae->Fit("fitppATLAS","LL","",FitStart,FitEnd); //fit function
   } 
//   fitppATLAS->Draw("same");
   Double_t xAxis1[31] = {3, 4, 5, 7, 9, 12, 15, 18, 21, 24, 28, 32, 37, 43, 49, 56, 64, 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 300, 330, 362, 395}; 
// should get from here, but use hard coded for now: Pawan_ntuple_PbPb_pp_calopfpt_ppNoJetidcut_R0p4_without80FakeRemoval_unfold_mcclosure_oppside_trgMC_noSmear_20_eta_20_50GeVCut_akPF_20150521.root   
   TH1F *PP_bayesian_unfolded_spectra = new TH1F("PP_bayesian_unfolded_spectra","Unfolded pp Bayes",30, xAxis1);
   PP_bayesian_unfolded_spectra->SetBinContent(1,9.536424);
   PP_bayesian_unfolded_spectra->SetBinContent(2,11.68343);
   PP_bayesian_unfolded_spectra->SetBinContent(3,17.5697);
   PP_bayesian_unfolded_spectra->SetBinContent(4,36.44376);
   PP_bayesian_unfolded_spectra->SetBinContent(5,85.42736);
   PP_bayesian_unfolded_spectra->SetBinContent(6,96.81938);
   PP_bayesian_unfolded_spectra->SetBinContent(7,85.24363);
   PP_bayesian_unfolded_spectra->SetBinContent(8,81.90266);
   PP_bayesian_unfolded_spectra->SetBinContent(9,90.42524);
   PP_bayesian_unfolded_spectra->SetBinContent(10,105.3756);
   PP_bayesian_unfolded_spectra->SetBinContent(11,107.9912);
   PP_bayesian_unfolded_spectra->SetBinContent(12,89.15275);
   PP_bayesian_unfolded_spectra->SetBinContent(13,62.50061);
   PP_bayesian_unfolded_spectra->SetBinContent(14,42.19855);
   PP_bayesian_unfolded_spectra->SetBinContent(15,22.47647);
   PP_bayesian_unfolded_spectra->SetBinContent(16,10.39846);
   PP_bayesian_unfolded_spectra->SetBinContent(17,4.803998);
   PP_bayesian_unfolded_spectra->SetBinContent(18,2.381109);
   PP_bayesian_unfolded_spectra->SetBinContent(19,1.158909);
   PP_bayesian_unfolded_spectra->SetBinContent(20,0.4750738);
   PP_bayesian_unfolded_spectra->SetBinContent(21,0.1806116);
   PP_bayesian_unfolded_spectra->SetBinContent(22,0.06970008);
   PP_bayesian_unfolded_spectra->SetBinContent(23,0.02977117);
   PP_bayesian_unfolded_spectra->SetBinContent(24,0.0124227);
   PP_bayesian_unfolded_spectra->SetBinContent(25,0.005254247);
   PP_bayesian_unfolded_spectra->SetBinContent(26,0.002484067);
   PP_bayesian_unfolded_spectra->SetBinContent(27,0.000780875);
   PP_bayesian_unfolded_spectra->SetBinContent(28,0.0002405737);
   PP_bayesian_unfolded_spectra->SetBinContent(29,8.799078e-05);
   PP_bayesian_unfolded_spectra->SetBinContent(30,4.509825e-05);
   PP_bayesian_unfolded_spectra->SetBinContent(31,0.0001361757);
   PP_bayesian_unfolded_spectra->SetBinError(1,0.003557945);
   PP_bayesian_unfolded_spectra->SetBinError(2,0.004697597);
   PP_bayesian_unfolded_spectra->SetBinError(3,0.01488396);
   PP_bayesian_unfolded_spectra->SetBinError(4,0.03267496);
   PP_bayesian_unfolded_spectra->SetBinError(5,0.09476053);
   PP_bayesian_unfolded_spectra->SetBinError(6,0.0969545);
   PP_bayesian_unfolded_spectra->SetBinError(7,0.09703425);
   PP_bayesian_unfolded_spectra->SetBinError(8,0.09680707);
   PP_bayesian_unfolded_spectra->SetBinError(9,0.08594806);
   PP_bayesian_unfolded_spectra->SetBinError(10,0.09559136);
   PP_bayesian_unfolded_spectra->SetBinError(11,0.0830177);
   PP_bayesian_unfolded_spectra->SetBinError(12,0.06991306);
   PP_bayesian_unfolded_spectra->SetBinError(13,0.05846729);
   PP_bayesian_unfolded_spectra->SetBinError(14,0.04506683);
   PP_bayesian_unfolded_spectra->SetBinError(15,0.02865936);
   PP_bayesian_unfolded_spectra->SetBinError(16,0.01453776);
   PP_bayesian_unfolded_spectra->SetBinError(17,0.007743395);
   PP_bayesian_unfolded_spectra->SetBinError(18,0.004109383);
   PP_bayesian_unfolded_spectra->SetBinError(19,0.002172191);
   PP_bayesian_unfolded_spectra->SetBinError(20,0.001200029);
   PP_bayesian_unfolded_spectra->SetBinError(21,0.0007354374);
   PP_bayesian_unfolded_spectra->SetBinError(22,0.0004518535);
   PP_bayesian_unfolded_spectra->SetBinError(23,0.0002843619);
   PP_bayesian_unfolded_spectra->SetBinError(24,0.0001774032);
   PP_bayesian_unfolded_spectra->SetBinError(25,0.0001087047);
   PP_bayesian_unfolded_spectra->SetBinError(26,6.784654e-05);
   PP_bayesian_unfolded_spectra->SetBinError(27,2.708384e-05);
   PP_bayesian_unfolded_spectra->SetBinError(28,2.345789e-05);
   PP_bayesian_unfolded_spectra->SetBinError(29,1.176688e-05);
   PP_bayesian_unfolded_spectra->SetBinError(30,9.876941e-06);
   PP_bayesian_unfolded_spectra->SetBinError(31,9.490217e-06);
   PP_bayesian_unfolded_spectra->SetEntries(1016523);
   PP_bayesian_unfolded_spectra->SetFillColor(1);
   PP_bayesian_unfolded_spectra->SetFillStyle(0);
   PP_bayesian_unfolded_spectra->SetLineStyle(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#0000ff");
   PP_bayesian_unfolded_spectra->SetMarkerColor(ci);
   PP_bayesian_unfolded_spectra->SetMarkerStyle(24);
   PP_bayesian_unfolded_spectra->SetMarkerSize(1.2);
   PP_bayesian_unfolded_spectra->GetXaxis()->CenterTitle(true);
   PP_bayesian_unfolded_spectra->GetXaxis()->SetLabelFont(42);
   PP_bayesian_unfolded_spectra->GetXaxis()->SetLabelOffset(0.01);
   PP_bayesian_unfolded_spectra->GetXaxis()->SetLabelSize(0.045);
   PP_bayesian_unfolded_spectra->GetXaxis()->SetTitleSize(0.055);
   PP_bayesian_unfolded_spectra->GetXaxis()->SetTitleFont(42);
   PP_bayesian_unfolded_spectra->GetYaxis()->CenterTitle(true);
   PP_bayesian_unfolded_spectra->GetYaxis()->SetLabelFont(42);
   PP_bayesian_unfolded_spectra->GetYaxis()->SetLabelOffset(0.01);
   PP_bayesian_unfolded_spectra->GetYaxis()->SetLabelSize(0.045);
   PP_bayesian_unfolded_spectra->GetYaxis()->SetTitleSize(0.055);
   PP_bayesian_unfolded_spectra->GetYaxis()->SetTitleOffset(1.5);
   PP_bayesian_unfolded_spectra->GetYaxis()->SetTitleFont(42);
   PP_bayesian_unfolded_spectra->GetZaxis()->SetLabelFont(42);
   PP_bayesian_unfolded_spectra->GetZaxis()->SetLabelSize(0.045);
   PP_bayesian_unfolded_spectra->GetZaxis()->SetTitleSize(0.035);
   PP_bayesian_unfolded_spectra->GetZaxis()->SetTitleFont(42);
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
   cATLAS_pp->SaveAs("Plots/CMShist_ATLASfit_spectra_pp.pdf");
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
  // TH1F* hBinByBinCor = (TH1F*)functionHist(f,hBinByBinCorRaw,Form("hBinByBinCor_cent%d",i));
//    TH1F *hRatioATLAS = (TH1F*)g->Clone("hRatioATLAS"); //clone histogram hRatio from h
  
   
}
