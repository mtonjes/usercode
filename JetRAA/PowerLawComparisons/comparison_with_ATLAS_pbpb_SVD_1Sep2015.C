//root -l 'comparison_with_ATLAS_pbpb_SVD_1Sep2015.C(10,60,280,"IL")'
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

void comparison_with_ATLAS_pbpb_SVD_1Sep2015(Int_t nfit=6, Int_t FitStart=60, Int_t FitEnd=300, Option_t *FitOpt="")
{

     TH1::SetDefaultSumw2();
   gStyle->SetOptFit(1);     
   gStyle->SetOptStat(0);
   
//=========Macro generated from canvas: cATLAS_HistComp/
//=========  (Tue Sep  1 16:39:38 2015) by ROOT version5.32/00

   Double_t xAxis2136[11] = {30, 40, 50, 60, 80, 100, 120, 160, 200, 250, 320}; 
   
   TH1F *uPbPb_R4_ATLASComp_cent5 = new TH1F("uPbPb_R4_ATLASComp_cent5"," ",10, xAxis2136);
   uPbPb_R4_ATLASComp_cent5->SetBinContent(0,71.86244);
   uPbPb_R4_ATLASComp_cent5->SetBinContent(1,27.41588);
   uPbPb_R4_ATLASComp_cent5->SetBinContent(2,15.97968);
   uPbPb_R4_ATLASComp_cent5->SetBinContent(3,9.597994);
   uPbPb_R4_ATLASComp_cent5->SetBinContent(4,4.048452);
   uPbPb_R4_ATLASComp_cent5->SetBinContent(5,0.9779469);
   uPbPb_R4_ATLASComp_cent5->SetBinContent(6,0.3094218);
   uPbPb_R4_ATLASComp_cent5->SetBinContent(7,0.07702038);
   uPbPb_R4_ATLASComp_cent5->SetBinContent(8,0.01644542);
   uPbPb_R4_ATLASComp_cent5->SetBinContent(9,0.002238312);
   uPbPb_R4_ATLASComp_cent5->SetBinContent(10,0.0001344882);
   uPbPb_R4_ATLASComp_cent5->SetBinContent(11,-0.003210287);
   uPbPb_R4_ATLASComp_cent5->SetBinError(0,158.4335);
   uPbPb_R4_ATLASComp_cent5->SetBinError(1,37.938);
   uPbPb_R4_ATLASComp_cent5->SetBinError(2,7.619901);
   uPbPb_R4_ATLASComp_cent5->SetBinError(3,1.718012);
   uPbPb_R4_ATLASComp_cent5->SetBinError(4,0.6204245);
   uPbPb_R4_ATLASComp_cent5->SetBinError(5,0.2479669);
   uPbPb_R4_ATLASComp_cent5->SetBinError(6,0.07769491);
   uPbPb_R4_ATLASComp_cent5->SetBinError(7,0.02182564);
   uPbPb_R4_ATLASComp_cent5->SetBinError(8,0.008110724);
   uPbPb_R4_ATLASComp_cent5->SetBinError(9,0.009963158);
   uPbPb_R4_ATLASComp_cent5->SetBinError(10,0.003779066);
   uPbPb_R4_ATLASComp_cent5->SetBinError(11,0.07536064);
   uPbPb_R4_ATLASComp_cent5->SetEntries(212);
   uPbPb_R4_ATLASComp_cent5->SetStats(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   uPbPb_R4_ATLASComp_cent5->SetLineColor(ci);

   ci = TColor::GetColor("#00ff00");
   uPbPb_R4_ATLASComp_cent5->SetMarkerColor(ci);
   uPbPb_R4_ATLASComp_cent5->SetMarkerStyle(27);
   uPbPb_R4_ATLASComp_cent5->GetXaxis()->SetTitle("akPu4PF Jet p_{T} (GeV/c)");
   uPbPb_R4_ATLASComp_cent5->GetXaxis()->SetRange(2,10);
   uPbPb_R4_ATLASComp_cent5->GetXaxis()->CenterTitle(true);
   uPbPb_R4_ATLASComp_cent5->GetXaxis()->SetNoExponent();
   uPbPb_R4_ATLASComp_cent5->GetXaxis()->SetNdivisions(505);
   uPbPb_R4_ATLASComp_cent5->GetXaxis()->SetLabelFont(43);
   uPbPb_R4_ATLASComp_cent5->GetXaxis()->SetLabelSize(20);
   uPbPb_R4_ATLASComp_cent5->GetXaxis()->SetTitleSize(22);
   uPbPb_R4_ATLASComp_cent5->GetXaxis()->SetTitleOffset(2);
   uPbPb_R4_ATLASComp_cent5->GetXaxis()->SetTitleFont(43);
   uPbPb_R4_ATLASComp_cent5->GetYaxis()->SetTitle("#frac{dN}{T_{AA} dp_{T} d#eta}");
   uPbPb_R4_ATLASComp_cent5->GetYaxis()->CenterTitle(true);
   uPbPb_R4_ATLASComp_cent5->GetYaxis()->SetNdivisions(610);
   uPbPb_R4_ATLASComp_cent5->GetYaxis()->SetLabelFont(43);
   uPbPb_R4_ATLASComp_cent5->GetYaxis()->SetLabelSize(20);
   uPbPb_R4_ATLASComp_cent5->GetYaxis()->SetTitleSize(22);
   uPbPb_R4_ATLASComp_cent5->GetYaxis()->SetTitleOffset(2);
   uPbPb_R4_ATLASComp_cent5->GetYaxis()->SetTitleFont(43);
   uPbPb_R4_ATLASComp_cent5->GetZaxis()->SetLabelFont(42);
   uPbPb_R4_ATLASComp_cent5->GetZaxis()->SetLabelSize(0.035);
   uPbPb_R4_ATLASComp_cent5->GetZaxis()->SetTitleSize(0.035);
   uPbPb_R4_ATLASComp_cent5->GetZaxis()->SetTitleFont(42);

   Double_t xAxis2137[13] = {31, 39, 50, 63, 79, 100, 125, 158, 199, 251, 316, 398, 501}; 
   
   TH1F *uATLAS_PbPb_R4_cent7 = new TH1F("uATLAS_PbPb_R4_cent7","",12, xAxis2137);
   uATLAS_PbPb_R4_cent7->SetBinContent(0,2.994659e-06);
   uATLAS_PbPb_R4_cent7->SetBinContent(3,13.16667);
   uATLAS_PbPb_R4_cent7->SetBinContent(4,3.854167);
   uATLAS_PbPb_R4_cent7->SetBinContent(5,1.125);
   uATLAS_PbPb_R4_cent7->SetBinContent(6,0.2904167);
   uATLAS_PbPb_R4_cent7->SetBinContent(7,0.07083333);
   uATLAS_PbPb_R4_cent7->SetBinContent(8,0.0155);
   uATLAS_PbPb_R4_cent7->SetBinContent(9,0.003045833);
   uATLAS_PbPb_R4_cent7->SetBinError(0,2.994659e-06);
   uATLAS_PbPb_R4_cent7->SetBinError(3,9.421147e-07);
   uATLAS_PbPb_R4_cent7->SetBinError(4,2.559744e-07);
   uATLAS_PbPb_R4_cent7->SetBinError(5,7.343752e-08);
   uATLAS_PbPb_R4_cent7->SetBinError(6,1.94353e-08);
   uATLAS_PbPb_R4_cent7->SetBinError(7,4.75353e-09);
   uATLAS_PbPb_R4_cent7->SetBinError(8,1.080383e-09);
   uATLAS_PbPb_R4_cent7->SetBinError(9,2.318215e-10);
   uATLAS_PbPb_R4_cent7->SetEntries(8);
   uATLAS_PbPb_R4_cent7->SetStats(0);

   ci = TColor::GetColor("#000099");
   uATLAS_PbPb_R4_cent7->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   uATLAS_PbPb_R4_cent7->SetMarkerColor(ci);
   uATLAS_PbPb_R4_cent7->SetMarkerStyle(24);
   uATLAS_PbPb_R4_cent7->GetXaxis()->SetLabelFont(42);
   uATLAS_PbPb_R4_cent7->GetXaxis()->SetLabelSize(0.035);
   uATLAS_PbPb_R4_cent7->GetXaxis()->SetTitleSize(0.035);
   uATLAS_PbPb_R4_cent7->GetXaxis()->SetTitleFont(42);
   uATLAS_PbPb_R4_cent7->GetYaxis()->SetLabelFont(42);
   uATLAS_PbPb_R4_cent7->GetYaxis()->SetLabelSize(0.035);
   uATLAS_PbPb_R4_cent7->GetYaxis()->SetTitleSize(0.035);
   uATLAS_PbPb_R4_cent7->GetYaxis()->SetTitleFont(42);
   uATLAS_PbPb_R4_cent7->GetZaxis()->SetLabelFont(42);
   uATLAS_PbPb_R4_cent7->GetZaxis()->SetLabelSize(0.035);
   uATLAS_PbPb_R4_cent7->GetZaxis()->SetTitleSize(0.035);
   uATLAS_PbPb_R4_cent7->GetZaxis()->SetTitleFont(42);
   TF1 *fitATLAS_periph = new TF1("fitATLAS_periph","[0]*pow(x+[2],[1])"); //create function
   fitATLAS_periph->SetParameters(1e10,-5,0);
   fitATLAS_periph->SetLineColor(kRed);   
   TF1 *fitCMS_periph = new TF1("fitCMS_periph","[0]*pow(x+[2],[1])"); //create function
   fitCMS_periph->SetParameters(1e10,-5,0);
   fitCMS_periph->SetLineColor(kGreen);   
 
   for(int i=0; i<nfit; ++i){
     uATLAS_PbPb_R4_cent7->Fit("fitATLAS_periph",FitOpt,"",FitStart,FitEnd); //fit function
   }    
   // clone before fit so I don't get that stupid line in the ratio plot
   TH1F *hRatioCMS_periph_axes = (TH1F*)uPbPb_R4_ATLASComp_cent5->Clone("hRatioCMS_periph_axes");
    for(int ic=0; ic<nfit; ic++){
//      uPP_R4_ATLASComp->Fit("fitppCMS",FitOpt,"",60,300); //fit function    
      uPbPb_R4_ATLASComp_cent5->Fit("fitCMS_periph",FitOpt,"",FitStart,FitEnd); //fit function
    }   
    
   Double_t xAxis2138[11] = {30, 40, 50, 60, 80, 100, 120, 160, 200, 250, 320}; 
   
   TH1F *uPbPb_R4_ATLASComp_cent4 = new TH1F("uPbPb_R4_ATLASComp_cent4"," ",10, xAxis2138);
   uPbPb_R4_ATLASComp_cent4->SetBinContent(0,160.7114);
   uPbPb_R4_ATLASComp_cent4->SetBinContent(1,43.89309);
   uPbPb_R4_ATLASComp_cent4->SetBinContent(2,19.8542);
   uPbPb_R4_ATLASComp_cent4->SetBinContent(3,9.662419);
   uPbPb_R4_ATLASComp_cent4->SetBinContent(4,3.840201);
   uPbPb_R4_ATLASComp_cent4->SetBinContent(5,1.018387);
   uPbPb_R4_ATLASComp_cent4->SetBinContent(6,0.2931249);
   uPbPb_R4_ATLASComp_cent4->SetBinContent(7,0.07895391);
   uPbPb_R4_ATLASComp_cent4->SetBinContent(8,0.01430236);
   uPbPb_R4_ATLASComp_cent4->SetBinContent(9,0.003178017);
   uPbPb_R4_ATLASComp_cent4->SetBinContent(10,0.0005168053);
   uPbPb_R4_ATLASComp_cent4->SetBinContent(11,0.006619798);
   uPbPb_R4_ATLASComp_cent4->SetBinError(0,35.7356);
   uPbPb_R4_ATLASComp_cent4->SetBinError(1,8.038963);
   uPbPb_R4_ATLASComp_cent4->SetBinError(2,1.187369);
   uPbPb_R4_ATLASComp_cent4->SetBinError(3,0.3812186);
   uPbPb_R4_ATLASComp_cent4->SetBinError(4,0.1250717);
   uPbPb_R4_ATLASComp_cent4->SetBinError(5,0.02877286);
   uPbPb_R4_ATLASComp_cent4->SetBinError(6,0.01311737);
   uPbPb_R4_ATLASComp_cent4->SetBinError(7,0.003064629);
   uPbPb_R4_ATLASComp_cent4->SetBinError(8,0.0009360799);
   uPbPb_R4_ATLASComp_cent4->SetBinError(9,0.0003311584);
   uPbPb_R4_ATLASComp_cent4->SetBinError(10,0.0002700729);
   uPbPb_R4_ATLASComp_cent4->SetBinError(11,0.008414639);
   uPbPb_R4_ATLASComp_cent4->SetEntries(212);
   uPbPb_R4_ATLASComp_cent4->SetStats(0);

   ci = TColor::GetColor("#000099");
   uPbPb_R4_ATLASComp_cent4->SetLineColor(ci);

   ci = TColor::GetColor("#00ff00");
   uPbPb_R4_ATLASComp_cent4->SetMarkerColor(ci);
   uPbPb_R4_ATLASComp_cent4->SetMarkerStyle(27);
   uPbPb_R4_ATLASComp_cent4->GetXaxis()->SetTitle("akPu4PF Jet p_{T} (GeV/c)");
   uPbPb_R4_ATLASComp_cent4->GetXaxis()->SetRange(2,10);
   uPbPb_R4_ATLASComp_cent4->GetXaxis()->CenterTitle(true);
   uPbPb_R4_ATLASComp_cent4->GetXaxis()->SetNoExponent();
   uPbPb_R4_ATLASComp_cent4->GetXaxis()->SetNdivisions(505);
   uPbPb_R4_ATLASComp_cent4->GetXaxis()->SetLabelFont(43);
   uPbPb_R4_ATLASComp_cent4->GetXaxis()->SetLabelSize(20);
   uPbPb_R4_ATLASComp_cent4->GetXaxis()->SetTitleSize(22);
   uPbPb_R4_ATLASComp_cent4->GetXaxis()->SetTitleOffset(2);
   uPbPb_R4_ATLASComp_cent4->GetXaxis()->SetTitleFont(43);
   uPbPb_R4_ATLASComp_cent4->GetYaxis()->SetTitle("#frac{dN}{T_{AA} dp_{T} d#eta}");
   uPbPb_R4_ATLASComp_cent4->GetYaxis()->CenterTitle(true);
   uPbPb_R4_ATLASComp_cent4->GetYaxis()->SetNdivisions(610);
   uPbPb_R4_ATLASComp_cent4->GetYaxis()->SetLabelFont(43);
   uPbPb_R4_ATLASComp_cent4->GetYaxis()->SetLabelSize(20);
   uPbPb_R4_ATLASComp_cent4->GetYaxis()->SetTitleSize(22);
   uPbPb_R4_ATLASComp_cent4->GetYaxis()->SetTitleOffset(2);
   uPbPb_R4_ATLASComp_cent4->GetYaxis()->SetTitleFont(43);
   uPbPb_R4_ATLASComp_cent4->GetZaxis()->SetLabelFont(42);
   uPbPb_R4_ATLASComp_cent4->GetZaxis()->SetLabelSize(0.035);
   uPbPb_R4_ATLASComp_cent4->GetZaxis()->SetTitleSize(0.035);
   uPbPb_R4_ATLASComp_cent4->GetZaxis()->SetTitleFont(42);
   Double_t xAxis2139[13] = {31, 39, 50, 63, 79, 100, 125, 158, 199, 251, 316, 398, 501}; 
   
   TH1F *uATLAS_PbPb_R4_cent5 = new TH1F("uATLAS_PbPb_R4_cent5","",12, xAxis2139);
   uATLAS_PbPb_R4_cent5->SetBinContent(3,12.93233);
   uATLAS_PbPb_R4_cent5->SetBinContent(4,3.857143);
   uATLAS_PbPb_R4_cent5->SetBinContent(5,1.075188);
   uATLAS_PbPb_R4_cent5->SetBinContent(6,0.2977444);
   uATLAS_PbPb_R4_cent5->SetBinContent(7,0.07135338);
   uATLAS_PbPb_R4_cent5->SetBinContent(8,0.01496241);
   uATLAS_PbPb_R4_cent5->SetBinContent(9,0.00275188);
   uATLAS_PbPb_R4_cent5->SetBinContent(10,0.0004571428);
   uATLAS_PbPb_R4_cent5->SetBinError(3,3.576525e-06);
   uATLAS_PbPb_R4_cent5->SetBinError(4,1.081214e-06);
   uATLAS_PbPb_R4_cent5->SetBinError(5,2.963656e-07);
   uATLAS_PbPb_R4_cent5->SetBinError(6,8.163557e-08);
   uATLAS_PbPb_R4_cent5->SetBinError(7,1.968254e-08);
   uATLAS_PbPb_R4_cent5->SetBinError(8,4.313942e-09);
   uATLAS_PbPb_R4_cent5->SetBinError(9,8.801672e-10);
   uATLAS_PbPb_R4_cent5->SetBinError(10,1.710696e-10);
   uATLAS_PbPb_R4_cent5->SetEntries(9);
   uATLAS_PbPb_R4_cent5->SetStats(0);

   ci = TColor::GetColor("#000099");
   uATLAS_PbPb_R4_cent5->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   uATLAS_PbPb_R4_cent5->SetMarkerColor(ci);
   uATLAS_PbPb_R4_cent5->SetMarkerStyle(24);
   uATLAS_PbPb_R4_cent5->GetXaxis()->SetLabelFont(42);
   uATLAS_PbPb_R4_cent5->GetXaxis()->SetLabelSize(0.035);
   uATLAS_PbPb_R4_cent5->GetXaxis()->SetTitleSize(0.035);
   uATLAS_PbPb_R4_cent5->GetXaxis()->SetTitleFont(42);
   uATLAS_PbPb_R4_cent5->GetYaxis()->SetLabelFont(42);
   uATLAS_PbPb_R4_cent5->GetYaxis()->SetLabelSize(0.035);
   uATLAS_PbPb_R4_cent5->GetYaxis()->SetTitleSize(0.035);
   uATLAS_PbPb_R4_cent5->GetYaxis()->SetTitleFont(42);
   uATLAS_PbPb_R4_cent5->GetZaxis()->SetLabelFont(42);
   uATLAS_PbPb_R4_cent5->GetZaxis()->SetLabelSize(0.035);
   uATLAS_PbPb_R4_cent5->GetZaxis()->SetTitleSize(0.035);
   uATLAS_PbPb_R4_cent5->GetZaxis()->SetTitleFont(42);

   TF1 *fitATLAS_midperiph = new TF1("fitATLAS_midperiph","[0]*pow(x+[2],[1])"); //create function
   fitATLAS_midperiph->SetParameters(1e10,-5,0);
   fitATLAS_midperiph->SetLineColor(kRed);   
   TF1 *fitCMS_midperiph = new TF1("fitCMS_midperiph","[0]*pow(x+[2],[1])"); //create function
   fitCMS_midperiph->SetParameters(1e10,-5,0);
   fitCMS_midperiph->SetLineColor(kGreen);     

   for(int i=0; i<nfit; ++i){
     uATLAS_PbPb_R4_cent5->Fit("fitATLAS_midperiph",FitOpt,"",FitStart,FitEnd); //fit function
   }    
   // clone before fit so I don't get that stupid line in the ratio plot
   TH1F *hRatioCMS_midperiph_axes = (TH1F*)uPbPb_R4_ATLASComp_cent4->Clone("hRatioCMS_midperiph_axes");
    for(int ic=0; ic<nfit; ic++){
//      uPP_R4_ATLASComp->Fit("fitppCMS",FitOpt,"",60,300); //fit function    
      uPbPb_R4_ATLASComp_cent4->Fit("fitCMS_midperiph",FitOpt,"",FitStart,FitEnd); //fit function
    }   
    
   Double_t xAxis2140[11] = {30, 40, 50, 60, 80, 100, 120, 160, 200, 250, 320}; 
   
   TH1F *uPbPb_R4_ATLASComp_cent3 = new TH1F("uPbPb_R4_ATLASComp_cent3"," ",10, xAxis2140);
   uPbPb_R4_ATLASComp_cent3->SetBinContent(0,124.9441);
   uPbPb_R4_ATLASComp_cent3->SetBinContent(1,34.3583);
   uPbPb_R4_ATLASComp_cent3->SetBinContent(2,15.81941);
   uPbPb_R4_ATLASComp_cent3->SetBinContent(3,7.768165);
   uPbPb_R4_ATLASComp_cent3->SetBinContent(4,3.063328);
   uPbPb_R4_ATLASComp_cent3->SetBinContent(5,0.8924736);
   uPbPb_R4_ATLASComp_cent3->SetBinContent(6,0.2782454);
   uPbPb_R4_ATLASComp_cent3->SetBinContent(7,0.06843327);
   uPbPb_R4_ATLASComp_cent3->SetBinContent(8,0.01294765);
   uPbPb_R4_ATLASComp_cent3->SetBinContent(9,0.002861388);
   uPbPb_R4_ATLASComp_cent3->SetBinContent(10,0.0005377622);
   uPbPb_R4_ATLASComp_cent3->SetBinContent(11,0.009096305);
   uPbPb_R4_ATLASComp_cent3->SetBinError(0,9.964294);
   uPbPb_R4_ATLASComp_cent3->SetBinError(1,1.728586);
   uPbPb_R4_ATLASComp_cent3->SetBinError(2,0.2604999);
   uPbPb_R4_ATLASComp_cent3->SetBinError(3,0.1072433);
   uPbPb_R4_ATLASComp_cent3->SetBinError(4,0.04298532);
   uPbPb_R4_ATLASComp_cent3->SetBinError(5,0.009419063);
   uPbPb_R4_ATLASComp_cent3->SetBinError(6,0.003555957);
   uPbPb_R4_ATLASComp_cent3->SetBinError(7,0.0008296324);
   uPbPb_R4_ATLASComp_cent3->SetBinError(8,0.0002675282);
   uPbPb_R4_ATLASComp_cent3->SetBinError(9,7.396354e-05);
   uPbPb_R4_ATLASComp_cent3->SetBinError(10,2.266889e-05);
   uPbPb_R4_ATLASComp_cent3->SetBinError(11,0.001153854);
   uPbPb_R4_ATLASComp_cent3->SetEntries(212);
   uPbPb_R4_ATLASComp_cent3->SetStats(0);

   ci = TColor::GetColor("#000099");
   uPbPb_R4_ATLASComp_cent3->SetLineColor(ci);

   ci = TColor::GetColor("#00ff00");
   uPbPb_R4_ATLASComp_cent3->SetMarkerColor(ci);
   uPbPb_R4_ATLASComp_cent3->SetMarkerStyle(27);
   uPbPb_R4_ATLASComp_cent3->GetXaxis()->SetTitle("akPu4PF Jet p_{T} (GeV/c)");
   uPbPb_R4_ATLASComp_cent3->GetXaxis()->SetRange(2,10);
   uPbPb_R4_ATLASComp_cent3->GetXaxis()->CenterTitle(true);
   uPbPb_R4_ATLASComp_cent3->GetXaxis()->SetNoExponent();
   uPbPb_R4_ATLASComp_cent3->GetXaxis()->SetNdivisions(505);
   uPbPb_R4_ATLASComp_cent3->GetXaxis()->SetLabelFont(43);
   uPbPb_R4_ATLASComp_cent3->GetXaxis()->SetLabelSize(20);
   uPbPb_R4_ATLASComp_cent3->GetXaxis()->SetTitleSize(22);
   uPbPb_R4_ATLASComp_cent3->GetXaxis()->SetTitleOffset(2);
   uPbPb_R4_ATLASComp_cent3->GetXaxis()->SetTitleFont(43);
   uPbPb_R4_ATLASComp_cent3->GetYaxis()->SetTitle("#frac{dN}{T_{AA} dp_{T} d#eta}");
   uPbPb_R4_ATLASComp_cent3->GetYaxis()->CenterTitle(true);
   uPbPb_R4_ATLASComp_cent3->GetYaxis()->SetNdivisions(610);
   uPbPb_R4_ATLASComp_cent3->GetYaxis()->SetLabelFont(43);
   uPbPb_R4_ATLASComp_cent3->GetYaxis()->SetLabelSize(20);
   uPbPb_R4_ATLASComp_cent3->GetYaxis()->SetTitleSize(22);
   uPbPb_R4_ATLASComp_cent3->GetYaxis()->SetTitleOffset(2);
   uPbPb_R4_ATLASComp_cent3->GetYaxis()->SetTitleFont(43);
   uPbPb_R4_ATLASComp_cent3->GetZaxis()->SetLabelFont(42);
   uPbPb_R4_ATLASComp_cent3->GetZaxis()->SetLabelSize(0.035);
   uPbPb_R4_ATLASComp_cent3->GetZaxis()->SetTitleSize(0.035);
   uPbPb_R4_ATLASComp_cent3->GetZaxis()->SetTitleFont(42);
   
   Double_t xAxis2141[13] = {31, 39, 50, 63, 79, 100, 125, 158, 199, 251, 316, 398, 501}; 
   
   TH1F *uATLAS_PbPb_R4_cent3 = new TH1F("uATLAS_PbPb_R4_cent3","",12, xAxis2141);
   uATLAS_PbPb_R4_cent3->SetBinContent(0,2.361534e-05);
   uATLAS_PbPb_R4_cent3->SetBinContent(3,10.75397);
   uATLAS_PbPb_R4_cent3->SetBinContent(4,3.273809);
   uATLAS_PbPb_R4_cent3->SetBinContent(5,0.9166667);
   uATLAS_PbPb_R4_cent3->SetBinContent(6,0.2460317);
   uATLAS_PbPb_R4_cent3->SetBinContent(7,0.06388889);
   uATLAS_PbPb_R4_cent3->SetBinContent(8,0.01515873);
   uATLAS_PbPb_R4_cent3->SetBinContent(9,0.003174603);
   uATLAS_PbPb_R4_cent3->SetBinContent(10,0.0005773809);
   uATLAS_PbPb_R4_cent3->SetBinContent(11,9.226191e-05);
   uATLAS_PbPb_R4_cent3->SetBinError(0,2.361534e-05);
   uATLAS_PbPb_R4_cent3->SetBinError(3,9.526565e-06);
   uATLAS_PbPb_R4_cent3->SetBinError(4,3.137951e-06);
   uATLAS_PbPb_R4_cent3->SetBinError(5,8.184966e-07);
   uATLAS_PbPb_R4_cent3->SetBinError(6,2.081612e-07);
   uATLAS_PbPb_R4_cent3->SetBinError(7,5.382411e-08);
   uATLAS_PbPb_R4_cent3->SetBinError(8,1.317296e-08);
   uATLAS_PbPb_R4_cent3->SetBinError(9,2.853702e-09);
   uATLAS_PbPb_R4_cent3->SetBinError(10,5.391438e-10);
   uATLAS_PbPb_R4_cent3->SetBinError(11,8.978956e-11);
   uATLAS_PbPb_R4_cent3->SetEntries(10);
   uATLAS_PbPb_R4_cent3->SetStats(0);

   ci = TColor::GetColor("#000099");
   uATLAS_PbPb_R4_cent3->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   uATLAS_PbPb_R4_cent3->SetMarkerColor(ci);
   uATLAS_PbPb_R4_cent3->SetMarkerStyle(24);
   uATLAS_PbPb_R4_cent3->GetXaxis()->SetLabelFont(42);
   uATLAS_PbPb_R4_cent3->GetXaxis()->SetLabelSize(0.035);
   uATLAS_PbPb_R4_cent3->GetXaxis()->SetTitleSize(0.035);
   uATLAS_PbPb_R4_cent3->GetXaxis()->SetTitleFont(42);
   uATLAS_PbPb_R4_cent3->GetYaxis()->SetLabelFont(42);
   uATLAS_PbPb_R4_cent3->GetYaxis()->SetLabelSize(0.035);
   uATLAS_PbPb_R4_cent3->GetYaxis()->SetTitleSize(0.035);
   uATLAS_PbPb_R4_cent3->GetYaxis()->SetTitleFont(42);
   uATLAS_PbPb_R4_cent3->GetZaxis()->SetLabelFont(42);
   uATLAS_PbPb_R4_cent3->GetZaxis()->SetLabelSize(0.035);
   uATLAS_PbPb_R4_cent3->GetZaxis()->SetTitleSize(0.035);
   uATLAS_PbPb_R4_cent3->GetZaxis()->SetTitleFont(42);

   TF1 *fitATLAS_midcent = new TF1("fitATLAS_midcent","[0]*pow(x+[2],[1])"); //create function
   fitATLAS_midcent->SetParameters(1e10,-5,0);
   fitATLAS_midcent->SetLineColor(kRed);   
   TF1 *fitCMS_midcent = new TF1("fitCMS_midcent","[0]*pow(x+[2],[1])"); //create function
   fitCMS_midcent->SetParameters(1e10,-5,0);
   fitCMS_midcent->SetLineColor(kGreen);     

   for(int i=0; i<nfit; ++i){
     uATLAS_PbPb_R4_cent3->Fit("fitATLAS_midcent",FitOpt,"",FitStart,FitEnd); //fit function
   }    
   // clone before fit so I don't get that stupid line in the ratio plot
   TH1F *hRatioCMS_midcent_axes = (TH1F*)uPbPb_R4_ATLASComp_cent3->Clone("hRatioCMS_midcent_axes");
    for(int ic=0; ic<nfit; ic++){
//      uPP_R4_ATLASComp->Fit("fitppCMS",FitOpt,"",60,300); //fit function    
      uPbPb_R4_ATLASComp_cent3->Fit("fitCMS_midcent",FitOpt,"",FitStart,FitEnd); //fit function
    }   

   Double_t xAxis2142[11] = {30, 40, 50, 60, 80, 100, 120, 160, 200, 250, 320}; 
   
   TH1F *uPbPb_R4_ATLASComp_cent2 = new TH1F("uPbPb_R4_ATLASComp_cent2"," ",10, xAxis2142);
   uPbPb_R4_ATLASComp_cent2->SetBinContent(0,238.031);
   uPbPb_R4_ATLASComp_cent2->SetBinContent(1,45.01383);
   uPbPb_R4_ATLASComp_cent2->SetBinContent(2,15.27294);
   uPbPb_R4_ATLASComp_cent2->SetBinContent(3,6.010644);
   uPbPb_R4_ATLASComp_cent2->SetBinContent(4,2.366487);
   uPbPb_R4_ATLASComp_cent2->SetBinContent(5,0.7317495);
   uPbPb_R4_ATLASComp_cent2->SetBinContent(6,0.2176009);
   uPbPb_R4_ATLASComp_cent2->SetBinContent(7,0.0548892);
   uPbPb_R4_ATLASComp_cent2->SetBinContent(8,0.01093431);
   uPbPb_R4_ATLASComp_cent2->SetBinContent(9,0.002409252);
   uPbPb_R4_ATLASComp_cent2->SetBinContent(10,0.000467059);
   uPbPb_R4_ATLASComp_cent2->SetBinContent(11,0.008593984);
   uPbPb_R4_ATLASComp_cent2->SetBinError(0,5.094755);
   uPbPb_R4_ATLASComp_cent2->SetBinError(1,0.3963241);
   uPbPb_R4_ATLASComp_cent2->SetBinError(2,0.1649383);
   uPbPb_R4_ATLASComp_cent2->SetBinError(3,0.08245976);
   uPbPb_R4_ATLASComp_cent2->SetBinError(4,0.01982589);
   uPbPb_R4_ATLASComp_cent2->SetBinError(5,0.004966019);
   uPbPb_R4_ATLASComp_cent2->SetBinError(6,0.001984391);
   uPbPb_R4_ATLASComp_cent2->SetBinError(7,0.0005394355);
   uPbPb_R4_ATLASComp_cent2->SetBinError(8,0.0001517952);
   uPbPb_R4_ATLASComp_cent2->SetBinError(9,4.849018e-05);
   uPbPb_R4_ATLASComp_cent2->SetBinError(10,1.421853e-05);
   uPbPb_R4_ATLASComp_cent2->SetBinError(11,0.0006208667);
   uPbPb_R4_ATLASComp_cent2->SetEntries(212);
   uPbPb_R4_ATLASComp_cent2->SetStats(0);

   ci = TColor::GetColor("#000099");
   uPbPb_R4_ATLASComp_cent2->SetLineColor(ci);

   ci = TColor::GetColor("#00ff00");
   uPbPb_R4_ATLASComp_cent2->SetMarkerColor(ci);
   uPbPb_R4_ATLASComp_cent2->SetMarkerStyle(27);
   uPbPb_R4_ATLASComp_cent2->GetXaxis()->SetTitle("akPu4PF Jet p_{T} (GeV/c)");
   uPbPb_R4_ATLASComp_cent2->GetXaxis()->SetRange(2,10);
   uPbPb_R4_ATLASComp_cent2->GetXaxis()->CenterTitle(true);
   uPbPb_R4_ATLASComp_cent2->GetXaxis()->SetNoExponent();
   uPbPb_R4_ATLASComp_cent2->GetXaxis()->SetNdivisions(505);
   uPbPb_R4_ATLASComp_cent2->GetXaxis()->SetLabelFont(43);
   uPbPb_R4_ATLASComp_cent2->GetXaxis()->SetLabelSize(20);
   uPbPb_R4_ATLASComp_cent2->GetXaxis()->SetTitleSize(22);
   uPbPb_R4_ATLASComp_cent2->GetXaxis()->SetTitleOffset(2);
   uPbPb_R4_ATLASComp_cent2->GetXaxis()->SetTitleFont(43);
   uPbPb_R4_ATLASComp_cent2->GetYaxis()->SetTitle("#frac{dN}{T_{AA} dp_{T} d#eta}");
   uPbPb_R4_ATLASComp_cent2->GetYaxis()->CenterTitle(true);
   uPbPb_R4_ATLASComp_cent2->GetYaxis()->SetNdivisions(610);
   uPbPb_R4_ATLASComp_cent2->GetYaxis()->SetLabelFont(43);
   uPbPb_R4_ATLASComp_cent2->GetYaxis()->SetLabelSize(20);
   uPbPb_R4_ATLASComp_cent2->GetYaxis()->SetTitleSize(22);
   uPbPb_R4_ATLASComp_cent2->GetYaxis()->SetTitleOffset(2);
   uPbPb_R4_ATLASComp_cent2->GetYaxis()->SetTitleFont(43);
   uPbPb_R4_ATLASComp_cent2->GetZaxis()->SetLabelFont(42);
   uPbPb_R4_ATLASComp_cent2->GetZaxis()->SetLabelSize(0.035);
   uPbPb_R4_ATLASComp_cent2->GetZaxis()->SetTitleSize(0.035);
   uPbPb_R4_ATLASComp_cent2->GetZaxis()->SetTitleFont(42);

   
   Double_t xAxis2143[13] = {31, 39, 50, 63, 79, 100, 125, 158, 199, 251, 316, 398, 501}; 
   
   TH1F *uATLAS_PbPb_R4_cent1 = new TH1F("uATLAS_PbPb_R4_cent1","",12, xAxis2143);
   uATLAS_PbPb_R4_cent1->SetBinContent(4,2.564102);
   uATLAS_PbPb_R4_cent1->SetBinContent(5,0.7068607);
   uATLAS_PbPb_R4_cent1->SetBinContent(6,0.1975052);
   uATLAS_PbPb_R4_cent1->SetBinContent(7,0.05114345);
   uATLAS_PbPb_R4_cent1->SetBinContent(8,0.01288981);
   uATLAS_PbPb_R4_cent1->SetBinContent(9,0.002647263);
   uATLAS_PbPb_R4_cent1->SetBinContent(10,0.0004830215);
   uATLAS_PbPb_R4_cent1->SetBinContent(11,7.415107e-05);
   uATLAS_PbPb_R4_cent1->SetBinError(4,7.716252e-06);
   uATLAS_PbPb_R4_cent1->SetBinError(5,1.792909e-06);
   uATLAS_PbPb_R4_cent1->SetBinError(6,5.048524e-07);
   uATLAS_PbPb_R4_cent1->SetBinError(7,1.218617e-07);
   uATLAS_PbPb_R4_cent1->SetBinError(8,3.001466e-08);
   uATLAS_PbPb_R4_cent1->SetBinError(9,6.65437e-09);
   uATLAS_PbPb_R4_cent1->SetBinError(10,1.316242e-09);
   uATLAS_PbPb_R4_cent1->SetBinError(11,2.304577e-10);
   uATLAS_PbPb_R4_cent1->SetEntries(9);
   uATLAS_PbPb_R4_cent1->SetStats(0);

   ci = TColor::GetColor("#000099");
   uATLAS_PbPb_R4_cent1->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   uATLAS_PbPb_R4_cent1->SetMarkerColor(ci);
   uATLAS_PbPb_R4_cent1->SetMarkerStyle(24);
   uATLAS_PbPb_R4_cent1->GetXaxis()->SetLabelFont(42);
   uATLAS_PbPb_R4_cent1->GetXaxis()->SetLabelSize(0.035);
   uATLAS_PbPb_R4_cent1->GetXaxis()->SetTitleSize(0.035);
   uATLAS_PbPb_R4_cent1->GetXaxis()->SetTitleFont(42);
   uATLAS_PbPb_R4_cent1->GetYaxis()->SetLabelFont(42);
   uATLAS_PbPb_R4_cent1->GetYaxis()->SetLabelSize(0.035);
   uATLAS_PbPb_R4_cent1->GetYaxis()->SetTitleSize(0.035);
   uATLAS_PbPb_R4_cent1->GetYaxis()->SetTitleFont(42);
   uATLAS_PbPb_R4_cent1->GetZaxis()->SetLabelFont(42);
   uATLAS_PbPb_R4_cent1->GetZaxis()->SetLabelSize(0.035);
   uATLAS_PbPb_R4_cent1->GetZaxis()->SetTitleSize(0.035);
   uATLAS_PbPb_R4_cent1->GetZaxis()->SetTitleFont(42);

   TF1 *fitATLAS_cent = new TF1("fitATLAS_cent","[0]*pow(x+[2],[1])"); //create function
   fitATLAS_cent->SetParameters(1e10,-5,0);
   fitATLAS_cent->SetLineColor(kRed);   
   TF1 *fitCMS_cent = new TF1("fitCMS_cent","[0]*pow(x+[2],[1])"); //create function
   fitCMS_cent->SetParameters(1e10,-5,0);
   fitCMS_cent->SetLineColor(kGreen);     
   
   for(int i=0; i<nfit; ++i){
     uATLAS_PbPb_R4_cent1->Fit("fitATLAS_cent",FitOpt,"",FitStart,FitEnd); //fit function
   }    
   // clone before fit so I don't get that stupid line in the ratio plot
   TH1F *hRatioCMS_cent_axes = (TH1F*)uPbPb_R4_ATLASComp_cent2->Clone("hRatioCMS_cent_axes");
    for(int ic=0; ic<nfit; ic++){
//      uPP_R4_ATLASComp->Fit("fitppCMS",FitOpt,"",60,300); //fit function    
      uPbPb_R4_ATLASComp_cent2->Fit("fitCMS_cent",FitOpt,"",FitStart,FitEnd); //fit function
    }   
   
   Double_t xAxis2144[11] = {30, 40, 50, 60, 80, 100, 120, 160, 200, 250, 320}; 
   
   TH1F *uPbPb_R4_ATLASComp_cent0 = new TH1F("uPbPb_R4_ATLASComp_cent0"," ",10, xAxis2144);
   uPbPb_R4_ATLASComp_cent0->SetBinContent(0,589.9679);
   uPbPb_R4_ATLASComp_cent0->SetBinContent(1,125.0149);
   uPbPb_R4_ATLASComp_cent0->SetBinContent(2,33.32589);
   uPbPb_R4_ATLASComp_cent0->SetBinContent(3,8.46418);
   uPbPb_R4_ATLASComp_cent0->SetBinContent(4,2.07101);
   uPbPb_R4_ATLASComp_cent0->SetBinContent(5,0.6138139);
   uPbPb_R4_ATLASComp_cent0->SetBinContent(6,0.1712831);
   uPbPb_R4_ATLASComp_cent0->SetBinContent(7,0.04574798);
   uPbPb_R4_ATLASComp_cent0->SetBinContent(8,0.009282498);
   uPbPb_R4_ATLASComp_cent0->SetBinContent(9,0.001985688);
   uPbPb_R4_ATLASComp_cent0->SetBinContent(10,0.0004251682);
   uPbPb_R4_ATLASComp_cent0->SetBinContent(11,0.008604864);
   uPbPb_R4_ATLASComp_cent0->SetBinError(0,5.577454);
   uPbPb_R4_ATLASComp_cent0->SetBinError(1,1.226594);
   uPbPb_R4_ATLASComp_cent0->SetBinError(2,0.6014387);
   uPbPb_R4_ATLASComp_cent0->SetBinError(3,0.221742);
   uPbPb_R4_ATLASComp_cent0->SetBinError(4,0.05554596);
   uPbPb_R4_ATLASComp_cent0->SetBinError(5,0.01230441);
   uPbPb_R4_ATLASComp_cent0->SetBinError(6,0.005103485);
   uPbPb_R4_ATLASComp_cent0->SetBinError(7,0.001207927);
   uPbPb_R4_ATLASComp_cent0->SetBinError(8,0.0003100666);
   uPbPb_R4_ATLASComp_cent0->SetBinError(9,8.357864e-05);
   uPbPb_R4_ATLASComp_cent0->SetBinError(10,2.402643e-05);
   uPbPb_R4_ATLASComp_cent0->SetBinError(11,0.0009303364);
   uPbPb_R4_ATLASComp_cent0->SetEntries(212);
   uPbPb_R4_ATLASComp_cent0->SetStats(0);

   ci = TColor::GetColor("#000099");
   uPbPb_R4_ATLASComp_cent0->SetLineColor(ci);

   ci = TColor::GetColor("#00ff00");
   uPbPb_R4_ATLASComp_cent0->SetMarkerColor(ci);
   uPbPb_R4_ATLASComp_cent0->SetMarkerStyle(27);
   uPbPb_R4_ATLASComp_cent0->GetXaxis()->SetTitle("akPu4PF Jet p_{T} (GeV/c)");
   uPbPb_R4_ATLASComp_cent0->GetXaxis()->SetRange(2,10);
   uPbPb_R4_ATLASComp_cent0->GetXaxis()->CenterTitle(true);
   uPbPb_R4_ATLASComp_cent0->GetXaxis()->SetNoExponent();
   uPbPb_R4_ATLASComp_cent0->GetXaxis()->SetNdivisions(505);
   uPbPb_R4_ATLASComp_cent0->GetXaxis()->SetLabelFont(43);
   uPbPb_R4_ATLASComp_cent0->GetXaxis()->SetLabelSize(20);
   uPbPb_R4_ATLASComp_cent0->GetXaxis()->SetTitleSize(22);
   uPbPb_R4_ATLASComp_cent0->GetXaxis()->SetTitleOffset(2);
   uPbPb_R4_ATLASComp_cent0->GetXaxis()->SetTitleFont(43);
   uPbPb_R4_ATLASComp_cent0->GetYaxis()->SetTitle("#frac{dN}{T_{AA} dp_{T} d#eta}");
   uPbPb_R4_ATLASComp_cent0->GetYaxis()->CenterTitle(true);
   uPbPb_R4_ATLASComp_cent0->GetYaxis()->SetNdivisions(610);
   uPbPb_R4_ATLASComp_cent0->GetYaxis()->SetLabelFont(43);
   uPbPb_R4_ATLASComp_cent0->GetYaxis()->SetLabelSize(20);
   uPbPb_R4_ATLASComp_cent0->GetYaxis()->SetTitleSize(22);
   uPbPb_R4_ATLASComp_cent0->GetYaxis()->SetTitleOffset(2);
   uPbPb_R4_ATLASComp_cent0->GetYaxis()->SetTitleFont(43);
   uPbPb_R4_ATLASComp_cent0->GetZaxis()->SetLabelFont(42);
   uPbPb_R4_ATLASComp_cent0->GetZaxis()->SetLabelSize(0.035);
   uPbPb_R4_ATLASComp_cent0->GetZaxis()->SetTitleSize(0.035);
   uPbPb_R4_ATLASComp_cent0->GetZaxis()->SetTitleFont(42);
   Double_t xAxis2145[13] = {31, 39, 50, 63, 79, 100, 125, 158, 199, 251, 316, 398, 501}; 
   
   TH1F *uATLAS_PbPb_R4_cent0 = new TH1F("uATLAS_PbPb_R4_cent0","",12, xAxis2145);
   uATLAS_PbPb_R4_cent0->SetBinContent(4,2.379531);
   uATLAS_PbPb_R4_cent0->SetBinContent(5,0.6439232);
   uATLAS_PbPb_R4_cent0->SetBinContent(6,0.1739872);
   uATLAS_PbPb_R4_cent0->SetBinContent(7,0.04520256);
   uATLAS_PbPb_R4_cent0->SetBinContent(8,0.01113006);
   uATLAS_PbPb_R4_cent0->SetBinContent(9,0.002430703);
   uATLAS_PbPb_R4_cent0->SetBinContent(10,0.0004392324);
   uATLAS_PbPb_R4_cent0->SetBinContent(11,6.396588e-05);
   uATLAS_PbPb_R4_cent0->SetBinError(4,1.179296e-05);
   uATLAS_PbPb_R4_cent0->SetBinError(5,3.363913e-06);
   uATLAS_PbPb_R4_cent0->SetBinError(6,7.43971e-07);
   uATLAS_PbPb_R4_cent0->SetBinError(7,1.809684e-07);
   uATLAS_PbPb_R4_cent0->SetBinError(8,4.389148e-08);
   uATLAS_PbPb_R4_cent0->SetBinError(9,1.005884e-08);
   uATLAS_PbPb_R4_cent0->SetBinError(10,2.024494e-09);
   uATLAS_PbPb_R4_cent0->SetBinError(11,3.648948e-10);
   uATLAS_PbPb_R4_cent0->SetEntries(9);
   uATLAS_PbPb_R4_cent0->SetStats(0);

   ci = TColor::GetColor("#000099");
   uATLAS_PbPb_R4_cent0->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   uATLAS_PbPb_R4_cent0->SetMarkerColor(ci);
   uATLAS_PbPb_R4_cent0->SetMarkerStyle(24);
   uATLAS_PbPb_R4_cent0->GetXaxis()->SetLabelFont(42);
   uATLAS_PbPb_R4_cent0->GetXaxis()->SetLabelSize(0.035);
   uATLAS_PbPb_R4_cent0->GetXaxis()->SetTitleSize(0.035);
   uATLAS_PbPb_R4_cent0->GetXaxis()->SetTitleFont(42);
   uATLAS_PbPb_R4_cent0->GetYaxis()->SetLabelFont(42);
   uATLAS_PbPb_R4_cent0->GetYaxis()->SetLabelSize(0.035);
   uATLAS_PbPb_R4_cent0->GetYaxis()->SetTitleSize(0.035);
   uATLAS_PbPb_R4_cent0->GetYaxis()->SetTitleFont(42);
   uATLAS_PbPb_R4_cent0->GetZaxis()->SetLabelFont(42);
   uATLAS_PbPb_R4_cent0->GetZaxis()->SetLabelSize(0.035);
   uATLAS_PbPb_R4_cent0->GetZaxis()->SetTitleSize(0.035);
   uATLAS_PbPb_R4_cent0->GetZaxis()->SetTitleFont(42);

   TF1 *fitATLAS_mostcent = new TF1("fitATLAS_mostcent","[0]*pow(x+[2],[1])"); //create function
   fitATLAS_mostcent->SetParameters(1e10,-5,0);
   fitATLAS_mostcent->SetLineColor(kRed);   
   TF1 *fitCMS_mostcent = new TF1("fitCMS_mostcent","[0]*pow(x+[2],[1])"); //create function
   fitCMS_mostcent->SetParameters(1e10,-5,0);
   fitCMS_mostcent->SetLineColor(kGreen);   
   
   for(int i=0; i<nfit; ++i){
     uATLAS_PbPb_R4_cent0->Fit("fitATLAS_mostcent",FitOpt,"",FitStart,FitEnd); //fit function
   }    
   // clone before fit so I don't get that stupid line in the ratio plot
   TH1F *hRatioCMS_mostcent_axes = (TH1F*)uPbPb_R4_ATLASComp_cent0->Clone("hRatioCMS_mostcent_axes");
    for(int ic=0; ic<nfit; ic++){
//      uPP_R4_ATLASComp->Fit("fitppCMS",FitOpt,"",60,300); //fit function    
      uPbPb_R4_ATLASComp_cent0->Fit("fitCMS_mostcent",FitOpt,"",FitStart,FitEnd); //fit function
    }   
          
// DRAW CANVAS STUFF
   TCanvas *cATLAS_HistComp = new TCanvas("cATLAS_HistComp", "",0,0,1400,1000);
   gStyle->SetOptStat(0);
   cATLAS_HistComp->Range(0,0,1,1);
   cATLAS_HistComp->SetFillColor(0);
   cATLAS_HistComp->SetBorderMode(0);
   cATLAS_HistComp->SetBorderSize(2);
   cATLAS_HistComp->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: cATLAS_HistComp_1 EMPTY
   TPad *cATLAS_HistComp_1 = new TPad("cATLAS_HistComp_1", "cATLAS_HistComp_1",0.01,0.51,0.3233333,0.99);
   cATLAS_HistComp_1->Draw();
   cATLAS_HistComp_1->cd();
   cATLAS_HistComp_1->Range(0,0,1,1);
   cATLAS_HistComp_1->SetFillColor(0);
   cATLAS_HistComp_1->SetBorderMode(0);
   cATLAS_HistComp_1->SetBorderSize(2);
   cATLAS_HistComp_1->SetFrameBorderMode(0);
   cATLAS_HistComp_1->Modified();
   cATLAS_HistComp->cd();
  
// ------------>Primitives in pad: cATLAS_HistComp_2 PERIPHERAL
   cATLAS_HistComp_2 = new TPad("cATLAS_HistComp_2", "cATLAS_HistComp_2",0.3433333,0.51,0.6566667,0.99);
   cATLAS_HistComp_2->Draw();
   cATLAS_HistComp_2->cd();
   cATLAS_HistComp_2->Range(4.999997,-4.900196,355,2.378303);
   cATLAS_HistComp_2->SetFillColor(0);
   cATLAS_HistComp_2->SetBorderMode(0);
   cATLAS_HistComp_2->SetBorderSize(2);
   cATLAS_HistComp_2->SetLogy();
   cATLAS_HistComp_2->SetFrameBorderMode(0);
   cATLAS_HistComp_2->SetFrameBorderMode(0);
   
   uPbPb_R4_ATLASComp_cent5->Draw("");
   uATLAS_PbPb_R4_cent7->Draw("same");
   
   TLegend *leg = new TLegend(0.25,0.75,0.5,0.85,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("uPbPb_R4_ATLASComp_cent5","CMS PbPb 70-90%, R=0.4","pl");


   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#00ff00");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(27);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("uATLAS_PbPb_R4_cent7","ATLAS PbPb 70-80%, R=0.4","pl");

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1);
   leg->Draw();
   
   TPaveText *pt = new TPaveText(0.4831415,0.94,0.5168585,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText(" ");
   pt->Draw();
   cATLAS_HistComp_2->Modified();
   cATLAS_HistComp->cd();
      
 // different pad

  
// ------------>Primitives in pad: cATLAS_HistComp_3 50-60 or 50-70%
   cATLAS_HistComp_3 = new TPad("cATLAS_HistComp_3", "cATLAS_HistComp_3",0.6766667,0.51,0.99,0.99);
   cATLAS_HistComp_3->Draw();
   cATLAS_HistComp_3->cd();
   cATLAS_HistComp_3->Range(4.999997,-4.597483,355,2.289306);
   cATLAS_HistComp_3->SetFillColor(0);
   cATLAS_HistComp_3->SetBorderMode(0);
   cATLAS_HistComp_3->SetBorderSize(2);
   cATLAS_HistComp_3->SetLogy();
   cATLAS_HistComp_3->SetFrameBorderMode(0);
   cATLAS_HistComp_3->SetFrameBorderMode(0);
    uPbPb_R4_ATLASComp_cent4->Draw("");
   uATLAS_PbPb_R4_cent5->Draw("same");
   
   leg = new TLegend(0.25,0.75,0.5,0.85,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(0);
   entry=leg->AddEntry("uPbPb_R4_ATLASComp_cent4","CMS PbPb 50-70%, R=0.4","pl");

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#00ff00");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(27);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("uATLAS_PbPb_R4_cent5","ATLAS PbPb 50-60%, R=0.4","pl");

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1);
   leg->Draw();
   
   pt = new TPaveText(0.4831415,0.94,0.5168585,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   text = pt->AddText(" ");
   pt->Draw();
   cATLAS_HistComp_3->Modified();
   cATLAS_HistComp->cd();     
// new pad
// ------------>Primitives in pad: cATLAS_HistComp_4
   cATLAS_HistComp_4 = new TPad("cATLAS_HistComp_4", "cATLAS_HistComp_4",0.01,0.01,0.3233333,0.49);
   cATLAS_HistComp_4->Draw();
   cATLAS_HistComp_4->cd();
   cATLAS_HistComp_4->Range(4.999997,-4.223266,355,2.117955);
   cATLAS_HistComp_4->SetFillColor(0);
   cATLAS_HistComp_4->SetBorderMode(0);
   cATLAS_HistComp_4->SetBorderSize(2);
   cATLAS_HistComp_4->SetLogy();
   cATLAS_HistComp_4->SetFrameBorderMode(0);
   cATLAS_HistComp_4->SetFrameBorderMode(0);
   uPbPb_R4_ATLASComp_cent3->Draw("");
   uATLAS_PbPb_R4_cent3->Draw("same");
   
   leg = new TLegend(0.25,0.75,0.5,0.85,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(0);
   entry=leg->AddEntry("uPbPb_R4_ATLASComp_cent3","CMS PbPb 30-50%, R=0.4","pl");

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#00ff00");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(27);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("uATLAS_PbPb_R4_cent3","ATLAS PbPb 30-40%, R=0.4","pl");

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1);
   leg->Draw();
   
   pt = new TPaveText(0.4831415,0.94,0.5168585,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   text = pt->AddText(" ");
   pt->Draw();
   cATLAS_HistComp_4->Modified();
   cATLAS_HistComp->cd();
// new pad
// ------------>Primitives in pad: cATLAS_HistComp_5 10-20 or 10-30%
   cATLAS_HistComp_5 = new TPad("cATLAS_HistComp_5", "cATLAS_HistComp_5",0.3433333,0.01,0.6566667,0.49);
   cATLAS_HistComp_5->Draw();
   cATLAS_HistComp_5->cd();
   cATLAS_HistComp_5->Range(4.999997,-4.283988,355,2.105039);
   cATLAS_HistComp_5->SetFillColor(0);
   cATLAS_HistComp_5->SetBorderMode(0);
   cATLAS_HistComp_5->SetBorderSize(2);
   cATLAS_HistComp_5->SetLogy();
   cATLAS_HistComp_5->SetFrameBorderMode(0);
   cATLAS_HistComp_5->SetFrameBorderMode(0);
   uPbPb_R4_ATLASComp_cent2->Draw("");
   uATLAS_PbPb_R4_cent1->Draw("same");
   leg = new TLegend(0.25,0.75,0.5,0.85,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(0);
   entry=leg->AddEntry("uPbPb_R4_ATLASComp_cent2","CMS PbPb 10-30%, R=0.4","pl");

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#00ff00");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(27);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("uATLAS_PbPb_R4_cent1","ATLAS PbPb 10-20%, R=0.4","pl");

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1);
   leg->Draw();
   
   pt = new TPaveText(0.4831415,0.94,0.5168585,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   text = pt->AddText(" ");
   pt->Draw();
   cATLAS_HistComp_5->Modified();
   cATLAS_HistComp->cd();
// new pad
// ------------>Primitives in pad: cATLAS_HistComp_6 0-5 or 0-10%
   cATLAS_HistComp_6 = new TPad("cATLAS_HistComp_6", "cATLAS_HistComp_6",0.6766667,0.01,0.99,0.49);
   cATLAS_HistComp_6->Draw();
   cATLAS_HistComp_6->cd();
   cATLAS_HistComp_6->Range(4.999997,-4.385961,355,2.496327);
   cATLAS_HistComp_6->SetFillColor(0);
   cATLAS_HistComp_6->SetBorderMode(0);
   cATLAS_HistComp_6->SetBorderSize(2);
   cATLAS_HistComp_6->SetLogy();
   cATLAS_HistComp_6->SetFrameBorderMode(0);
   cATLAS_HistComp_6->SetFrameBorderMode(0);
 
    uPbPb_R4_ATLASComp_cent0->Draw("");
   uATLAS_PbPb_R4_cent0->Draw("same");
   leg = new TLegend(0.25,0.75,0.5,0.85,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(0);
   entry=leg->AddEntry("uPbPb_R4_ATLASComp_cent0","CMS PbPb 0-5%, R=0.4","pl");

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#00ff00");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(27);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("uATLAS_PbPb_R4_cent0","ATLAS PbPb 0-10%, R=0.4","pl");

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(1);
   leg->Draw();
   
   pt = new TPaveText(0.4831415,0.94,0.5168585,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   text = pt->AddText(" ");
   pt->Draw();
   cATLAS_HistComp_6->Modified();
   cATLAS_HistComp->cd();
   cATLAS_HistComp->Modified();
   cATLAS_HistComp->cd();
   cATLAS_HistComp->SetSelected(cATLAS_HistComp);
   cATLAS_HistComp->SaveAs("Plots/ATLAS_CMS_SVD_powerlawFit_PbPbSpectra.pdf");
// Draw Ratios
   TH1F *hFitRatioCMS_periph = (TH1F*)functionHist(fitCMS_periph,hRatioCMS_periph_axes,"hFitRatioCMS_periph"); //make histo hFitRatioCMS from fitppCMS function with hRatioCMS_axes bins
   TH1F *hFitBottomATLAS_periph = (TH1F*)functionHist(fitATLAS_periph,hRatioCMS_periph_axes,"hFitBottomATLAS_periph"); // make histo hFitBottomATLAS from fitppATLAS with hRatioCMS_axes bins
   hFitRatioCMS_periph->Divide(hFitBottomATLAS_periph);
   hFitRatioCMS_periph->SetMarkerColor(kBlue);
   hFitRatioCMS_periph->SetMarkerStyle(25);
   hFitRatioCMS_periph->SetLineColor(kBlue);

   TH1F *hFitRatioCMS_midperiph = (TH1F*)functionHist(fitCMS_midperiph,hRatioCMS_midperiph_axes,"hFitRatioCMS_midperiph"); //make histo hFitRatioCMS from fitppCMS function with hRatioCMS_axes bins
   TH1F *hFitBottomATLAS_midperiph = (TH1F*)functionHist(fitATLAS_midperiph,hRatioCMS_midperiph_axes,"hFitBottomATLAS_midperiph"); // make histo hFitBottomATLAS from fitppATLAS with hRatioCMS_axes bins
   hFitRatioCMS_midperiph->Divide(hFitBottomATLAS_midperiph);
   hFitRatioCMS_midperiph->SetMarkerColor(kRed);
   hFitRatioCMS_midperiph->SetMarkerStyle(24);
   hFitRatioCMS_midperiph->SetLineColor(kRed);

   TH1F *hFitRatioCMS_midcent = (TH1F*)functionHist(fitCMS_midcent,hRatioCMS_midcent_axes,"hFitRatioCMS_midcent"); //make histo hFitRatioCMS from fitppCMS function with hRatioCMS_axes bins
   TH1F *hFitBottomATLAS_midcent = (TH1F*)functionHist(fitATLAS_midcent,hRatioCMS_midcent_axes,"hFitBottomATLAS_midcent"); // make histo hFitBottomATLAS from fitppATLAS with hRatioCMS_axes bins
   hFitRatioCMS_midcent->Divide(hFitBottomATLAS_midcent);
   hFitRatioCMS_midcent->SetMarkerColor(kGreen+1);
   hFitRatioCMS_midcent->SetMarkerStyle(27);
   hFitRatioCMS_midcent->SetLineColor(kGreen+1);

   TH1F *hFitRatioCMS_cent = (TH1F*)functionHist(fitCMS_cent,hRatioCMS_cent_axes,"hFitRatioCMS_cent"); //make histo hFitRatioCMS from fitppCMS function with hRatioCMS_axes bins
   TH1F *hFitBottomATLAS_cent = (TH1F*)functionHist(fitATLAS_cent,hRatioCMS_cent_axes,"hFitBottomATLAS_cent"); // make histo hFitBottomATLAS from fitppATLAS with hRatioCMS_axes bins
   hFitRatioCMS_cent->Divide(hFitBottomATLAS_cent);
   hFitRatioCMS_cent->SetMarkerColor(kCyan+2);
   hFitRatioCMS_cent->SetMarkerStyle(28);
   hFitRatioCMS_cent->SetLineColor(kCyan+2);

   TH1F *hFitRatioCMS_mostcent = (TH1F*)functionHist(fitCMS_mostcent,hRatioCMS_mostcent_axes,"hFitRatioCMS_mostcent"); //make histo hFitRatioCMS from fitppCMS function with hRatioCMS_axes bins
   TH1F *hFitBottomATLAS_mostcent = (TH1F*)functionHist(fitATLAS_mostcent,hRatioCMS_mostcent_axes,"hFitBottomATLAS_mostcent"); // make histo hFitBottomATLAS from fitppATLAS with hRatioCMS_axes bins
   hFitRatioCMS_mostcent->Divide(hFitBottomATLAS_mostcent);
   hFitRatioCMS_mostcent->SetMarkerColor(kMagenta+2);
   hFitRatioCMS_mostcent->SetMarkerStyle(20);
   hFitRatioCMS_mostcent->SetLineColor(kMagenta+2);
            
   TCanvas *cATLAS_Ratio = new TCanvas("cATLAS_Ratio", "",0,0,1400,600);
   gStyle->SetOptStat(0);
   cATLAS_Ratio->Range(0,0,1,1);
   cATLAS_Ratio->SetFillColor(0);
   cATLAS_Ratio->SetBorderMode(0);
   cATLAS_Ratio->SetBorderSize(2);
   cATLAS_Ratio->SetFrameBorderMode(0);
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
     
// ------------>Primitives in pad: cATLAS_Ratio_1 EMPTY
   TPad *cATLAS_Ratio_1 = new TPad("cATLAS_Ratio_1", "cATLAS_Ratio_1",0.01,0.51,0.3233333,0.99);
   cATLAS_Ratio_1->Draw();
   cATLAS_Ratio_1->cd();
   cATLAS_Ratio_1->Range(0,0,1,1);
   cATLAS_Ratio_1->SetFillColor(0);
   cATLAS_Ratio_1->SetBorderMode(0);
   cATLAS_Ratio_1->SetBorderSize(2);
   cATLAS_Ratio_1->SetFrameBorderMode(0);
   cATLAS_Ratio_1->Modified();
   cATLAS_Ratio->cd();
  
// ------------>Primitives in pad: cATLAS_Ratio_2 PERIPHERAL
   cATLAS_Ratio_2 = new TPad("cATLAS_Ratio_2", "cATLAS_Ratio_2",0.3433333,0.51,0.6566667,0.99);
   cATLAS_Ratio_2->Draw();
   cATLAS_Ratio_2->cd();
   cATLAS_Ratio_2->Range(4.999997,-4.900196,355,2.378303);
   cATLAS_Ratio_2->SetFillColor(0);
   cATLAS_Ratio_2->SetBorderMode(0);
   cATLAS_Ratio_2->SetBorderSize(2);
   cATLAS_Ratio_2->SetLogy();
   cATLAS_Ratio_2->SetFrameBorderMode(0);
   cATLAS_Ratio_2->SetFrameBorderMode(0);
   hRatioBlank->Draw();     
   hFitRatioCMS_periph->Draw("same,ap");
   
   TLegend *leg = new TLegend(0.25,0.75,0.5,0.85,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("hFitRatioCMS_periph","CMS 70-90%/ATLAS 70-80%, R=0.4","pl");
   leg->Draw();
   
   TPaveText *pt = new TPaveText(0.4831415,0.94,0.5168585,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *text = pt->AddText(" ");
   pt->Draw();
   cATLAS_Ratio_2->Modified();
   cATLAS_Ratio->cd();
      
 // different pad

  
// ------------>Primitives in pad: cATLAS_Ratio_3 50-60 or 50-70%
   cATLAS_Ratio_3 = new TPad("cATLAS_Ratio_3", "cATLAS_Ratio_3",0.6766667,0.51,0.99,0.99);
   cATLAS_Ratio_3->Draw();
   cATLAS_Ratio_3->cd();
   cATLAS_Ratio_3->Range(4.999997,-4.597483,355,2.289306);
   cATLAS_Ratio_3->SetFillColor(0);
   cATLAS_Ratio_3->SetBorderMode(0);
   cATLAS_Ratio_3->SetBorderSize(2);
   cATLAS_Ratio_3->SetLogy();
   cATLAS_Ratio_3->SetFrameBorderMode(0);
   cATLAS_Ratio_3->SetFrameBorderMode(0);
   hRatioBlank->Draw();     
   hFitRatioCMS_midperiph->Draw("same,ap");
   
   leg = new TLegend(0.25,0.75,0.5,0.85,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(0);
   entry=leg->AddEntry("hFitRatioCMS_midperiph","CMS 50-70%/ATLAS 50-60%, R=0.4","pl");
   leg->Draw();
   
   pt = new TPaveText(0.4831415,0.94,0.5168585,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   text = pt->AddText(" ");
   pt->Draw();
   cATLAS_Ratio_3->Modified();
   cATLAS_Ratio->cd();     
// new pad
// ------------>Primitives in pad: cATLAS_Ratio_4
   cATLAS_Ratio_4 = new TPad("cATLAS_Ratio_4", "cATLAS_Ratio_4",0.01,0.01,0.3233333,0.49);
   cATLAS_Ratio_4->Draw();
   cATLAS_Ratio_4->cd();
   cATLAS_Ratio_4->Range(4.999997,-4.223266,355,2.117955);
   cATLAS_Ratio_4->SetFillColor(0);
   cATLAS_Ratio_4->SetBorderMode(0);
   cATLAS_Ratio_4->SetBorderSize(2);
   cATLAS_Ratio_4->SetLogy();
   cATLAS_Ratio_4->SetFrameBorderMode(0);
   cATLAS_Ratio_4->SetFrameBorderMode(0);
   hRatioBlank->Draw();     
   hFitRatioCMS_midcent->Draw("same,ap");
   
   leg = new TLegend(0.25,0.75,0.5,0.85,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(0);
   entry=leg->AddEntry("hFitRatioCMS_midcent","CMS 30-50%/ATLAS 30-40%, R=0.4","pl");
   leg->Draw();
   
   pt = new TPaveText(0.4831415,0.94,0.5168585,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   text = pt->AddText(" ");
   pt->Draw();
   cATLAS_Ratio_4->Modified();
   cATLAS_Ratio->cd();
// new pad
// ------------>Primitives in pad: cATLAS_Ratio_5 10-20 or 10-30%
   cATLAS_Ratio_5 = new TPad("cATLAS_Ratio_5", "cATLAS_Ratio_5",0.3433333,0.01,0.6566667,0.49);
   cATLAS_Ratio_5->Draw();
   cATLAS_Ratio_5->cd();
   cATLAS_Ratio_5->Range(4.999997,-4.283988,355,2.105039);
   cATLAS_Ratio_5->SetFillColor(0);
   cATLAS_Ratio_5->SetBorderMode(0);
   cATLAS_Ratio_5->SetBorderSize(2);
   cATLAS_Ratio_5->SetLogy();
   cATLAS_Ratio_5->SetFrameBorderMode(0);
   cATLAS_Ratio_5->SetFrameBorderMode(0);
   hRatioBlank->Draw();     
   hFitRatioCMS_cent->Draw("same,ap");
   leg = new TLegend(0.25,0.75,0.5,0.85,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(0);
   entry=leg->AddEntry("hFitRatioCMS_cent","CMS 10-30%/ATLAS 10-20%, R=0.4","pl");
   leg->Draw();
   
   pt = new TPaveText(0.4831415,0.94,0.5168585,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   text = pt->AddText(" ");
   pt->Draw();
   cATLAS_Ratio_5->Modified();
   cATLAS_Ratio->cd();
// new pad
// ------------>Primitives in pad: cATLAS_Ratio_6 0-5 or 0-10%
   cATLAS_Ratio_6 = new TPad("cATLAS_Ratio_6", "cATLAS_Ratio_6",0.6766667,0.01,0.99,0.49);
   cATLAS_Ratio_6->Draw();
   cATLAS_Ratio_6->cd();
   cATLAS_Ratio_6->Range(4.999997,-4.385961,355,2.496327);
   cATLAS_Ratio_6->SetFillColor(0);
   cATLAS_Ratio_6->SetBorderMode(0);
   cATLAS_Ratio_6->SetBorderSize(2);
   cATLAS_Ratio_6->SetLogy();
   cATLAS_Ratio_6->SetFrameBorderMode(0);
   cATLAS_Ratio_6->SetFrameBorderMode(0);
 
   hRatioBlank->Draw();     
   hFitRatioCMS_mostcent->Draw("same,ap");
   leg = new TLegend(0.25,0.75,0.5,0.85,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(0);
   entry=leg->AddEntry("hFitRatioCMS_mostcent","CMS 0-5%/ATLAS 0-10%, R=0.4","pl");
   leg->Draw();
   
   pt = new TPaveText(0.4831415,0.94,0.5168585,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   text = pt->AddText(" ");
   pt->Draw();
   cATLAS_Ratio_6->Modified();
   cATLAS_Ratio->cd();
   cATLAS_Ratio->Modified();
   cATLAS_Ratio->cd();
   cATLAS_Ratio->SetSelected(cATLAS_Ratio);
   cATLAS_Ratio->SaveAs("Plots/ATLAS_CMS_SVD_powerlawFitRatio_PbPbSpectra.pdf");           
}
