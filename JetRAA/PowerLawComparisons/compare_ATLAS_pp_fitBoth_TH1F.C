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

void compare_ATLAS_pp_fitBoth_TH1F(Int_t nfit=6, Int_t FitStart=50, Int_t FitEnd=450){
     TH1::SetDefaultSumw2();
   gStyle->SetOptFit(1);     
   gStyle->SetOptStat(0);
   
//=========Macro generated from canvas: cATLAS_pp/
//=========  (Wed Jul 22 23:01:26 2015) by ROOT version5.32/00

   TF1 *fitppATLAS = new TF1("fitppATLAS","[0]*pow(x+[2],[1])"); //create function
   fitppATLAS->SetParameters(1e10,-5,0);
   fitppATLAS->SetLineColor(kRed);   
   TF1 *fitppCMS = new TF1("fitppCMS","[0]*pow(x+[2],[1])"); //create function
   fitppCMS->SetParameters(1e10,-5,0);
   fitppCMS->SetLineColor(kBlue);   
   TF1 *fitppATLASHist = new TF1("fitppATLASHist","[0]*pow(x+[2],[1])"); //create function
   fitppATLASHist->SetParameters(1e10,-5,0);
   fitppATLASHist->SetLineColor(kGreen+1);   
      
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


Double_t xAxisATLASpp[13] = {31,39,50,63,79,100,125,158,199,251,316,398,501}; 
   TH1F *hATLASppHist = new TH1F("hATLASppHist"," ",12,xAxisATLASpp);
   hATLASppHist->SetMinimum(1.090031e-05);
   hATLASppHist->SetMaximum(230.955);
   hATLASppHist->SetDirectory(0);
   hATLASppHist->SetStats(0);
   hATLASppHist->SetBinContent(1,180);
   hATLASppHist->SetBinError(1,29.95905);
   hATLASppHist->SetBinContent(2,55.7);
   hATLASppHist->SetBinError(2,7.828377);
   hATLASppHist->SetBinContent(3,16.9);
   hATLASppHist->SetBinError(3,2.625436);
   hATLASppHist->SetBinContent(4,4.85);
   hATLASppHist->SetBinError(4,0.6276957);
   hATLASppHist->SetBinContent(5,1.42);
   hATLASppHist->SetBinError(5,0.1878054);
   hATLASppHist->SetBinContent(6,0.364);
   hATLASppHist->SetBinError(6,0.04772427);
   hATLASppHist->SetBinContent(7,0.0882);
   hATLASppHist->SetBinError(7,0.01103805);
   hATLASppHist->SetBinContent(8,0.0197);
   hATLASppHist->SetBinError(8,0.002292152);
   hATLASppHist->SetBinContent(9,0.00406);
   hATLASppHist->SetBinError(9,0.0004822521);
   hATLASppHist->SetBinContent(10,0.000735);
   hATLASppHist->SetBinError(10,8.981748e-05);
   hATLASppHist->SetBinContent(11,0.000114);
   hATLASppHist->SetBinError(11,1.442494e-05);
   hATLASppHist->SetBinContent(12,1.41e-05);
   hATLASppHist->SetBinError(12,1.98855e-06);
//    c1=new TCanvas();
// //   c1.cd();
//    hATLASppHist->Draw();
  // was grae
   for(int i=0; i<nfit; ++i){
     grae->Fit("fitppATLAS","","",FitStart,FitEnd); //fit function
   } 
   cout<<"now to fit hATLASppHist"<<endl;
   for(int ib=0; ib<nfit; ++ib){
     hATLASppHist->Fit("fitppATLASHist","IL","",FitStart,FitEnd); //fit function
   } 

   TCanvas *cATLAS_ppHist = new TCanvas("cATLAS_ppHist", "",0,0,1200,1000);
   cATLAS_ppHist->Range(-3.725291e-06,-5.878322,500,3.279288);
   cATLAS_ppHist->SetFillColor(0);
   cATLAS_ppHist->SetBorderMode(0);
   cATLAS_ppHist->SetBorderSize(2);
   cATLAS_ppHist->SetLogy();
   cATLAS_ppHist->SetFrameBorderMode(0);
   cATLAS_ppHist->SetFrameBorderMode(0);

//   grae->SetHistogram(hATLASpp);

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
   entry=leg->AddEntry("hATLASppHist","ATLAS pp histogram","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(kGreen);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("grae","ATLAS pp TGraphAsymErrors","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(33);
   entry->SetMarkerSize(1);
   
   leg->Draw();
   hATLASppHist->SetMarkerColor(kGreen);
   hATLASppHist->SetMarkerStyle(22);
   grae->SetMarkerStyle(21);
   grae->SetMarkerColor(1);
   hATLASpp->Draw();
   grae->Draw("ap,same");
//   uPP_R4_SVD->Draw("same E1");
   hATLASppHist->Draw("ap,same");
   
   TPaveText *pt = new TPaveText(0.4845652,0.94,0.5154348,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText(" ");
   pt->Draw();
   cATLAS_ppHist->Modified();
   cATLAS_ppHist->cd();
   cATLAS_ppHist->SetSelected(cATLAS_ppHist);
   
//     for(int ic=0; ic<nfit; ic++){
//       uPP_R4_SVD->Fit("fitppCMS","IL","",60,FitEnd); //fit function    
// //      uPP_R4_SVD->Fit("fitppCMS","IL","",50,300); //fit function
//     } 
   
//     hATLASpp->Draw();
//    grae->Draw("ap,same");
//    uPP_R4_SVD->Draw("same E1");
//    hATLASppHist->Draw("same E1");
   leg->Draw();
   cATLAS_ppHist->SaveAs("Plots/ATLASHistfit_spectra_pp.pdf");
   
   
   Double_t xAxis2086[101] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 500, 510, 520, 530, 540, 550, 560, 570, 580, 590, 600, 610, 620, 630, 640, 650, 660, 670, 680, 690, 700, 710, 720, 730, 740, 750, 760, 770, 780, 790, 800, 810, 820, 830, 840, 850, 860, 870, 880, 890, 900, 910, 920, 930, 940, 950, 960, 970, 980, 990, 1000}; 
   
   TH1F *uPP_R4_SVD = new TH1F("uPP_R4_SVD","Unfold Matrix refpt jtpt from trigger addition R4 20_eta_20 ",100, xAxis2086);
   uPP_R4_SVD->SetBinContent(1,15.44572);
   uPP_R4_SVD->SetBinContent(2,81.73347);
   uPP_R4_SVD->SetBinContent(3,85.49986);
   uPP_R4_SVD->SetBinContent(4,90.07588);
   uPP_R4_SVD->SetBinContent(5,47.67952);
   uPP_R4_SVD->SetBinContent(6,18.31659);
   uPP_R4_SVD->SetBinContent(7,7.348095);
   uPP_R4_SVD->SetBinContent(8,3.295203);
   uPP_R4_SVD->SetBinContent(9,1.60486);
   uPP_R4_SVD->SetBinContent(10,0.8393627);
   uPP_R4_SVD->SetBinContent(11,0.4622419);
   uPP_R4_SVD->SetBinContent(12,0.265131);
   uPP_R4_SVD->SetBinContent(13,0.1587068);
   uPP_R4_SVD->SetBinContent(14,0.09774788);
   uPP_R4_SVD->SetBinContent(15,0.06153403);
   uPP_R4_SVD->SetBinContent(16,0.03981187);
   uPP_R4_SVD->SetBinContent(17,0.02620752);
   uPP_R4_SVD->SetBinContent(18,0.01766706);
   uPP_R4_SVD->SetBinContent(19,0.01206758);
   uPP_R4_SVD->SetBinContent(20,0.008403017);
   uPP_R4_SVD->SetBinContent(21,0.005956108);
   uPP_R4_SVD->SetBinContent(22,0.004267026);
   uPP_R4_SVD->SetBinContent(23,0.003102345);
   uPP_R4_SVD->SetBinContent(24,0.002273482);
   uPP_R4_SVD->SetBinContent(25,0.001699103);
   uPP_R4_SVD->SetBinContent(26,0.001281323);
   uPP_R4_SVD->SetBinContent(27,0.000971557);
   uPP_R4_SVD->SetBinContent(28,0.0007444665);
   uPP_R4_SVD->SetBinContent(29,0.0005746992);
   uPP_R4_SVD->SetBinContent(30,0.0004462709);
   uPP_R4_SVD->SetBinContent(31,0.0003483805);
   uPP_R4_SVD->SetBinContent(32,0.0002725941);
   uPP_R4_SVD->SetBinContent(33,0.0002141152);
   uPP_R4_SVD->SetBinContent(34,0.0001705039);
   uPP_R4_SVD->SetBinContent(35,0.0001352845);
   uPP_R4_SVD->SetBinContent(36,0.0001073623);
   uPP_R4_SVD->SetBinContent(37,8.559958e-05);
   uPP_R4_SVD->SetBinContent(38,6.847693e-05);
   uPP_R4_SVD->SetBinContent(39,5.506579e-05);
   uPP_R4_SVD->SetBinContent(40,4.404838e-05);
   uPP_R4_SVD->SetBinContent(41,3.566817e-05);
   uPP_R4_SVD->SetBinContent(42,2.88001e-05);
   uPP_R4_SVD->SetBinContent(43,2.33088e-05);
   uPP_R4_SVD->SetBinContent(44,1.897322e-05);
   uPP_R4_SVD->SetBinContent(45,1.546483e-05);
   uPP_R4_SVD->SetBinContent(46,1.251424e-05);
   uPP_R4_SVD->SetBinContent(47,1.020799e-05);
   uPP_R4_SVD->SetBinContent(48,8.267746e-06);
   uPP_R4_SVD->SetBinContent(49,6.760333e-06);
   uPP_R4_SVD->SetBinContent(50,5.504337e-06);
   uPP_R4_SVD->SetBinContent(51,4.514429e-06);
   uPP_R4_SVD->SetBinContent(52,3.665816e-06);
   uPP_R4_SVD->SetBinContent(53,3.010496e-06);
   uPP_R4_SVD->SetBinContent(54,2.463812e-06);
   uPP_R4_SVD->SetBinContent(55,2.01082e-06);
   uPP_R4_SVD->SetBinContent(56,1.624154e-06);
   uPP_R4_SVD->SetBinContent(57,1.334625e-06);
   uPP_R4_SVD->SetBinContent(58,1.088798e-06);
   uPP_R4_SVD->SetBinContent(59,8.896167e-07);
   uPP_R4_SVD->SetBinContent(60,7.305952e-07);
   uPP_R4_SVD->SetBinContent(61,5.930196e-07);
   uPP_R4_SVD->SetBinContent(62,4.863888e-07);
   uPP_R4_SVD->SetBinContent(63,3.941485e-07);
   uPP_R4_SVD->SetBinContent(64,3.221651e-07);
   uPP_R4_SVD->SetBinContent(65,2.636797e-07);
   uPP_R4_SVD->SetBinContent(66,2.146457e-07);
   uPP_R4_SVD->SetBinContent(67,1.742243e-07);
   uPP_R4_SVD->SetBinContent(68,1.409108e-07);
   uPP_R4_SVD->SetBinContent(69,1.142703e-07);
   uPP_R4_SVD->SetBinContent(70,9.293402e-08);
   uPP_R4_SVD->SetBinContent(71,7.511816e-08);
   uPP_R4_SVD->SetBinContent(72,6.013509e-08);
   uPP_R4_SVD->SetBinContent(73,4.927971e-08);
   uPP_R4_SVD->SetBinContent(74,3.992714e-08);
   uPP_R4_SVD->SetBinContent(75,3.176246e-08);
   uPP_R4_SVD->SetBinContent(76,2.560933e-08);
   uPP_R4_SVD->SetBinContent(77,2.039975e-08);
   uPP_R4_SVD->SetBinContent(78,1.627726e-08);
   uPP_R4_SVD->SetBinContent(79,1.272043e-08);
   uPP_R4_SVD->SetBinContent(80,1.022684e-08);
   uPP_R4_SVD->SetBinContent(81,8.172451e-09);
   uPP_R4_SVD->SetBinContent(82,6.570082e-09);
   uPP_R4_SVD->SetBinContent(83,5.205766e-09);
   uPP_R4_SVD->SetBinContent(84,4.075393e-09);
   uPP_R4_SVD->SetBinContent(85,3.265506e-09);
   uPP_R4_SVD->SetBinContent(86,2.62088e-09);
   uPP_R4_SVD->SetBinContent(87,2.003114e-09);
   uPP_R4_SVD->SetBinContent(88,1.535628e-09);
   uPP_R4_SVD->SetBinContent(89,1.063791e-09);
   uPP_R4_SVD->SetBinContent(90,9.092138e-10);
   uPP_R4_SVD->SetBinContent(91,6.803265e-10);
   uPP_R4_SVD->SetBinContent(92,4.778346e-10);
   uPP_R4_SVD->SetBinContent(93,3.988072e-10);
   uPP_R4_SVD->SetBinContent(94,2.474126e-10);
   uPP_R4_SVD->SetBinContent(95,2.140924e-10);
   uPP_R4_SVD->SetBinContent(96,1.623732e-10);
   uPP_R4_SVD->SetBinContent(97,1.45067e-10);
   uPP_R4_SVD->SetBinContent(98,9.186947e-11);
   uPP_R4_SVD->SetBinContent(99,6.040857e-11);
   uPP_R4_SVD->SetBinContent(100,6.157141e-11);
   uPP_R4_SVD->SetBinError(1,0.1237595);
   uPP_R4_SVD->SetBinError(2,0.6234048);
   uPP_R4_SVD->SetBinError(3,0.586929);
   uPP_R4_SVD->SetBinError(4,0.5173901);
   uPP_R4_SVD->SetBinError(5,0.2055361);
   uPP_R4_SVD->SetBinError(6,0.04990473);
   uPP_R4_SVD->SetBinError(7,0.01308245);
   uPP_R4_SVD->SetBinError(8,0.006804987);
   uPP_R4_SVD->SetBinError(9,0.003260532);
   uPP_R4_SVD->SetBinError(10,0.001534405);
   uPP_R4_SVD->SetBinError(11,0.001026545);
   uPP_R4_SVD->SetBinError(12,0.000705749);
   uPP_R4_SVD->SetBinError(13,0.0004784051);
   uPP_R4_SVD->SetBinError(14,0.0003483983);
   uPP_R4_SVD->SetBinError(15,0.0002598719);
   uPP_R4_SVD->SetBinError(16,0.0001903908);
   uPP_R4_SVD->SetBinError(17,0.0001387089);
   uPP_R4_SVD->SetBinError(18,0.0001040173);
   uPP_R4_SVD->SetBinError(19,7.981541e-05);
   uPP_R4_SVD->SetBinError(20,6.24475e-05);
   uPP_R4_SVD->SetBinError(21,4.937991e-05);
   uPP_R4_SVD->SetBinError(22,3.947987e-05);
   uPP_R4_SVD->SetBinError(23,3.254473e-05);
   uPP_R4_SVD->SetBinError(24,2.764293e-05);
   uPP_R4_SVD->SetBinError(25,2.429597e-05);
   uPP_R4_SVD->SetBinError(26,2.159774e-05);
   uPP_R4_SVD->SetBinError(27,1.917051e-05);
   uPP_R4_SVD->SetBinError(28,1.6997e-05);
   uPP_R4_SVD->SetBinError(29,1.498669e-05);
   uPP_R4_SVD->SetBinError(30,1.312744e-05);
   uPP_R4_SVD->SetBinError(31,1.142902e-05);
   uPP_R4_SVD->SetBinError(32,9.871913e-06);
   uPP_R4_SVD->SetBinError(33,8.480939e-06);
   uPP_R4_SVD->SetBinError(34,7.324674e-06);
   uPP_R4_SVD->SetBinError(35,6.255272e-06);
   uPP_R4_SVD->SetBinError(36,5.306614e-06);
   uPP_R4_SVD->SetBinError(37,4.495288e-06);
   uPP_R4_SVD->SetBinError(38,3.800242e-06);
   uPP_R4_SVD->SetBinError(39,3.214166e-06);
   uPP_R4_SVD->SetBinError(40,2.692884e-06);
   uPP_R4_SVD->SetBinError(41,2.275421e-06);
   uPP_R4_SVD->SetBinError(42,1.910914e-06);
   uPP_R4_SVD->SetBinError(43,1.60384e-06);
   uPP_R4_SVD->SetBinError(44,1.350324e-06);
   uPP_R4_SVD->SetBinError(45,1.135728e-06);
   uPP_R4_SVD->SetBinError(46,9.463317e-07);
   uPP_R4_SVD->SetBinError(47,7.933288e-07);
   uPP_R4_SVD->SetBinError(48,6.591956e-07);
   uPP_R4_SVD->SetBinError(49,5.520988e-07);
   uPP_R4_SVD->SetBinError(50,4.597711e-07);
   uPP_R4_SVD->SetBinError(51,3.851643e-07);
   uPP_R4_SVD->SetBinError(52,3.190695e-07);
   uPP_R4_SVD->SetBinError(53,2.670117e-07);
   uPP_R4_SVD->SetBinError(54,2.22444e-07);
   uPP_R4_SVD->SetBinError(55,1.84622e-07);
   uPP_R4_SVD->SetBinError(56,1.515098e-07);
   uPP_R4_SVD->SetBinError(57,1.263889e-07);
   uPP_R4_SVD->SetBinError(58,1.045901e-07);
   uPP_R4_SVD->SetBinError(59,8.662012e-08);
   uPP_R4_SVD->SetBinError(60,7.20551e-08);
   uPP_R4_SVD->SetBinError(61,5.920339e-08);
   uPP_R4_SVD->SetBinError(62,4.912298e-08);
   uPP_R4_SVD->SetBinError(63,4.024705e-08);
   uPP_R4_SVD->SetBinError(64,3.324212e-08);
   uPP_R4_SVD->SetBinError(65,2.747888e-08);
   uPP_R4_SVD->SetBinError(66,2.258106e-08);
   uPP_R4_SVD->SetBinError(67,1.849393e-08);
   uPP_R4_SVD->SetBinError(68,1.50859e-08);
   uPP_R4_SVD->SetBinError(69,1.233344e-08);
   uPP_R4_SVD->SetBinError(70,1.010825e-08);
   uPP_R4_SVD->SetBinError(71,8.230567e-09);
   uPP_R4_SVD->SetBinError(72,6.634947e-09);
   uPP_R4_SVD->SetBinError(73,5.473309e-09);
   uPP_R4_SVD->SetBinError(74,4.462479e-09);
   uPP_R4_SVD->SetBinError(75,3.571148e-09);
   uPP_R4_SVD->SetBinError(76,2.895626e-09);
   uPP_R4_SVD->SetBinError(77,2.318939e-09);
   uPP_R4_SVD->SetBinError(78,1.859689e-09);
   uPP_R4_SVD->SetBinError(79,1.460273e-09);
   uPP_R4_SVD->SetBinError(80,1.179314e-09);
   uPP_R4_SVD->SetBinError(81,9.46416e-10);
   uPP_R4_SVD->SetBinError(82,7.638915e-10);
   uPP_R4_SVD->SetBinError(83,6.075323e-10);
   uPP_R4_SVD->SetBinError(84,4.772801e-10);
   uPP_R4_SVD->SetBinError(85,3.836821e-10);
   uPP_R4_SVD->SetBinError(86,3.088773e-10);
   uPP_R4_SVD->SetBinError(87,2.367363e-10);
   uPP_R4_SVD->SetBinError(88,1.819577e-10);
   uPP_R4_SVD->SetBinError(89,1.263493e-10);
   uPP_R4_SVD->SetBinError(90,1.082238e-10);
   uPP_R4_SVD->SetBinError(91,8.113796e-11);
   uPP_R4_SVD->SetBinError(92,5.70881e-11);
   uPP_R4_SVD->SetBinError(93,4.772047e-11);
   uPP_R4_SVD->SetBinError(94,2.964495e-11);
   uPP_R4_SVD->SetBinError(95,2.568217e-11);
   uPP_R4_SVD->SetBinError(96,1.949672e-11);
   uPP_R4_SVD->SetBinError(97,1.743206e-11);
   uPP_R4_SVD->SetBinError(98,1.104588e-11);
   uPP_R4_SVD->SetBinError(99,7.265969e-12);
   uPP_R4_SVD->SetBinError(100,7.407249e-12);
   uPP_R4_SVD->SetEntries(100);
   uPP_R4_SVD->SetStats(0);

   ci = TColor::GetColor("#000099");
   uPP_R4_SVD->SetLineColor(ci);

//    ci = TColor::GetColor("#0000ff");
//    uPP_R4_SVD->SetMarkerColor(ci);
//    uPP_R4_SVD->SetMarkerStyle(24);
//    uPP_R4_SVD->GetXaxis()->CenterTitle(true);
//    uPP_R4_SVD->GetXaxis()->SetLabelFont(42);
//    uPP_R4_SVD->GetXaxis()->SetLabelSize(0.035);
//    uPP_R4_SVD->GetXaxis()->SetTitleSize(0.035);
//    uPP_R4_SVD->GetXaxis()->SetTitleFont(42);
//    uPP_R4_SVD->GetYaxis()->CenterTitle(true);
//    uPP_R4_SVD->GetYaxis()->SetLabelFont(42);
//    uPP_R4_SVD->GetYaxis()->SetLabelSize(0.035);
//    uPP_R4_SVD->GetYaxis()->SetTitleSize(0.035);
//    uPP_R4_SVD->GetYaxis()->SetTitleFont(42);
//    uPP_R4_SVD->GetZaxis()->SetLabelFont(42);
//    uPP_R4_SVD->GetZaxis()->SetLabelSize(0.035);
//    uPP_R4_SVD->GetZaxis()->SetTitleSize(0.035);
//    uPP_R4_SVD->GetZaxis()->SetTitleFont(42);
//    uPP_R4_SVD->Draw("same E1");
//    TBox *box = new TBox(60,7.108492,70,7.587699);
//    box->SetFillColor(2);
//    box->SetFillStyle(0);
//    box->SetLineColor(2);
//    box->Draw();
//    box = new TBox(70,3.186674,80,3.403731);
//    box->SetFillColor(2);
//    box->SetFillStyle(0);
//    box->SetLineColor(2);
//    box->Draw();
//    box = new TBox(80,1.551541,90,1.658179);
//    box->SetFillColor(2);
//    box->SetFillStyle(0);
//    box->SetLineColor(2);
//    box->Draw();
//    box = new TBox(90,0.8111346,100,0.8675909);
//    box->SetFillColor(2);
//    box->SetFillStyle(0);
//    box->SetLineColor(2);
//    box->Draw();
//    box = new TBox(100,0.4464541,110,0.4780297);
//    box->SetFillColor(2);
//    box->SetFillStyle(0);
//    box->SetLineColor(2);
//    box->Draw();
//    box = new TBox(110,0.2045159,130,0.2193219);
//    box->SetFillColor(2);
//    box->SetFillStyle(0);
//    box->SetLineColor(2);
//    box->Draw();
//    box = new TBox(130,0.07677678,150,0.08250514);
//    box->SetFillColor(2);
//    box->SetFillStyle(0);
//    box->SetLineColor(2);
//    box->Draw();
//    box = new TBox(150,0.03180206,170,0.03421734);
//    box->SetFillColor(2);
//    box->SetFillStyle(0);
//    box->SetLineColor(2);
//    box->Draw();
//    box = new TBox(170,0.01431415,190,0.01542048);
//    box->SetFillColor(2);
//    box->SetFillStyle(0);
//    box->SetLineColor(2);
//    box->Draw();
//    box = new TBox(190,0.006909775,210,0.007449351);
//    box->SetFillColor(2);
//    box->SetFillStyle(0);
//    box->SetLineColor(2);
//    box->Draw();
//    box = new TBox(210,0.003092187,240,0.003336382);
//    box->SetFillColor(2);
//    box->SetFillStyle(0);
//    box->SetLineColor(2);
//    box->Draw();
//    box = new TBox(240,0.001266417,270,0.001368238);
//    box->SetFillColor(2);
//    box->SetFillStyle(0);
//    box->SetLineColor(2);
//    box->Draw();
//    box = new TBox(270,0.00056544,300,0.0006115177);
//    box->SetFillColor(2);
//    box->SetFillStyle(0);
//    box->SetLineColor(2);
//    box->Draw();
   TCanvas *cATLAS_pp = new TCanvas("cATLAS_pp", "",0,0,1200,1000);
   cATLAS_pp->Range(-3.725291e-06,-5.878322,500,3.279288);
   cATLAS_pp->SetFillColor(0);
   cATLAS_pp->SetBorderMode(0);
   cATLAS_pp->SetBorderSize(2);
   cATLAS_pp->SetLogy();
   cATLAS_pp->SetFrameBorderMode(0);
   cATLAS_pp->SetFrameBorderMode(0);
   grae->SetHistogram(hATLASpp);
   hATLASpp->Draw();
   grae->Draw("ap,same");   
         
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
   
    for(int ic=0; ic<nfit; ic++){
      uPP_R4_SVD->Fit("fitppCMS","IL","",60,FitEnd); //fit function    
//      uPP_R4_SVD->Fit("fitppCMS","IL","",50,300); //fit function
    } 
   
    hATLASpp->Draw();
   grae->Draw("ap,same");
   uPP_R4_SVD->Draw("same E1");
   leg->Draw();
   cATLAS_pp->SaveAs("Plots/CMSfit_ATLASfit_spectra_pp.pdf");
   
   
   TCanvas *cCMS_pp = new TCanvas("cCMS_pp", "",0,0,1200,1000);
   cCMS_pp->Range(-3.725291e-06,-5.878322,500,3.279288);
   cCMS_pp->SetFillColor(0);
   cCMS_pp->SetBorderMode(0);
   cCMS_pp->SetBorderSize(2);
   cCMS_pp->SetLogy();
   cCMS_pp->SetLogx();
   cCMS_pp->SetFrameBorderMode(0);
   cCMS_pp->SetFrameBorderMode(0);
   uPP_R4_SVD->GetXaxis()->SetTitle("ak R=0.4 Jet p_{T} (GeV/c)");
   uPP_R4_SVD->GetXaxis()->SetLabelFont(42);
   uPP_R4_SVD->GetXaxis()->SetLabelSize(0.035);
   uPP_R4_SVD->GetXaxis()->SetTitleSize(0.035);
   uPP_R4_SVD->GetXaxis()->SetTitleFont(42);
   uPP_R4_SVD->GetXaxis()->SetRangeUser(50,450);
   uPP_R4_SVD->GetYaxis()->SetTitle("#frac{d^{2}#sigma}{dp_{T} d#eta} nb");
   uPP_R4_SVD->GetYaxis()->SetLabelFont(42);
   uPP_R4_SVD->GetYaxis()->SetLabelSize(0.035);
   uPP_R4_SVD->GetYaxis()->SetTitleSize(0.035);
   uPP_R4_SVD->GetYaxis()->SetTitleFont(42);
   uPP_R4_SVD->GetZaxis()->SetLabelFont(42);
   uPP_R4_SVD->GetZaxis()->SetLabelSize(0.035);
   uPP_R4_SVD->GetZaxis()->SetTitleSize(0.035);
   uPP_R4_SVD->GetZaxis()->SetTitleFont(42);
      
   uPP_R4_SVD->Draw();
      
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
   cCMS_pp->Modified();
   cCMS_pp->cd();
   cCMS_pp->SetSelected(cCMS_pp);
   cCMS_pp->SaveAs("Plots/CMSfit_spectra_pp.pdf"); 

   TCanvas *cATLAS_lin_pp = new TCanvas("cATLAS_lin_pp", "",0,0,1200,1000);
   cATLAS_lin_pp->Range(-3.725291e-06,-5.878322,500,3.279288);
   cATLAS_lin_pp->SetFillColor(0);
   cATLAS_lin_pp->SetBorderMode(0);
   cATLAS_lin_pp->SetBorderSize(2);
   cATLAS_lin_pp->SetFrameBorderMode(0);
   cATLAS_lin_pp->SetFrameBorderMode(0);
   cATLAS_lin_pp->SetLogy();
   cATLAS_lin_pp->SetLogx();
   hATLASpp->Draw();
   grae->Draw("ap,same");
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
   cATLAS_lin_pp->Modified();
   cATLAS_lin_pp->cd();
   cATLAS_lin_pp->SetSelected(cATLAS_lin_pp);
   
//     for(int ic=0; ic<nfit; ic++){
//       uPP_R4_SVD->Fit("fitppCMS","IL","",60,FitEnd); //fit function    
// //      uPP_R4_SVD->Fit("fitppCMS","IL","",50,300); //fit function
//     } 
   
    hATLASpp->Draw();
   grae->Draw("ap,same");
   uPP_R4_SVD->Draw("same E1");
   leg->Draw();
   cATLAS_lin_pp->SaveAs("Plots/CMSfit_ATLASfit_spectra_loglog_pp.pdf");  

   fitppCMS->SetBit(TF1::kNotDraw);
   fitppCMS->SetLineColor(0);
   uPP_R4_SVD->SetBit(TF1::kNotDraw);




   TH1F *hFitRatioATLAS = (TH1F*)functionHist(fitppCMS,uPP_R4_SVD,"hFitRatioATLAS"); //clone fitRatioATLAS from fitppCMS
//   hFitRatioATLAS->SetLineColor(0);
   TH1F *hRatioATLAS = (TH1F*)uPP_R4_SVD->Clone("hRatioATLAS"); //clone histogram hRatio from h

   TH1F *hfunctionATLAS = (TH1F*)functionHist(fitppATLAS,uPP_R4_SVD,"hfunctionATLAS");
   hFitRatioATLAS->Divide(hfunctionATLAS);
   hFitRatioATLAS->SetMarkerColor(kRed); 
   hFitRatioATLAS->SetMarkerStyle(21);
   hFitRatioATLAS->SetMarkerSize(1.2);
   hFitRatioATLAS->SetLineColor(0);  

   TH1F *hfunctionATLASHist = (TH1F*)functionHist(fitppATLASHist,uPP_R4_SVD,"hfunctionATLASHist");
   TH1F *hRatioATLASHist = (TH1F*)uPP_R4_SVD->Clone("hRatioATLASHist"); //clone histogram hRatio from h
   hRatioATLASHist->Divide(hfunctionATLASHist);
   hRatioATLASHist->SetMarkerColor(kGreen+1); 
   hRatioATLASHist->SetMarkerStyle(22);
   hRatioATLASHist->SetMarkerSize(1.2);
   hRatioATLASHist->SetLineColor(0); 
      
//   hfunctionATLAS->Draw();
//   hATLASpp->Draw();
   hRatioATLAS->Divide(hfunctionATLAS);
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
//   hFitRatioATLAS->Scale(5.3/4);
   hFitRatioATLAS->Draw("ap,same");
   hRatioATLAS->Draw("ap,same");
   hRatioATLASHist->Draw("ap,same");
   
   cRatio_pp->SaveAs("Plots/CMSfit_ATLASfit_ratio_pp.pdf");
   

   
}
