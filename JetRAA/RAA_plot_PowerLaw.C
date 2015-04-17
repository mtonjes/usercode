// Raghav Kunnawalkam Elayavalli
// April 14 2014
// Rutgers
// raghav.k.e at CERN dot CH

//
// Macro to plot the final paper plots.  
//


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


#include "/data/users/belt/JetRAA/MatchNtuples/AnalysisPlots/Headers/plot.h"
#include "/data/users/belt/JetRAA/MatchNtuples/AnalysisPlots/Headers/utilities.h"


using namespace std;

void RAA_plot_PowerLaw(Int_t unfoldingCut = 60 , char *algo = "Pu", char *jet_type = "PF", Int_t FitStart=70, Int_t FitEnd=280){
    
  TStopwatch timer;
  timer.Start();

  TDatime date;

  gStyle->SetOptStat(0);

  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();

  TFile *fin_R2, *fin_R3, *fin_R4; 
  fin_R2= TFile::Open(Form("/data/users/belt/JetRAA/MatchNtuples/AnalysisRootFiles/april16/PbPb_pp_calopfpt_jetidcut_R0p%d_unfold_mcclosure_oppside_trgMC_n20_eta_p20_%dGeVCut_ak%s_20150417.root",2,unfoldingCut,jet_type));
  fin_R3= TFile::Open(Form("/data/users/belt/JetRAA/MatchNtuples/AnalysisRootFiles/april16/PbPb_pp_calopfpt_jetidcut_R0p%d_unfold_mcclosure_oppside_trgMC_n20_eta_p20_%dGeVCut_ak%s_20150417.root",3,unfoldingCut,jet_type));
  fin_R4= TFile::Open(Form("/data/users/belt/JetRAA/MatchNtuples/AnalysisRootFiles/april16/PbPb_pp_calopfpt_jetidcut_R0p%d_unfold_mcclosure_oppside_trgMC_n20_eta_p20_%dGeVCut_ak%s_20150417.root",4,unfoldingCut,jet_type));

  // get the histograms.
  TH1F * uPbPb_R2_Bayes[nbins_cent], * uPP_R2_Bayes, * uPbPb_R3_Bayes[nbins_cent], * uPP_R3_Bayes, * uPbPb_R4_Bayes[nbins_cent], * uPP_R4_Bayes;
  TH1F * mPbPb_R2[nbins_cent], * mPP_R2, * mPbPb_R3[nbins_cent], * mPP_R3, * mPbPb_R4[nbins_cent], * mPP_R4;
  
  TH1F * RAA_R2_Bayes[nbins_cent], * RAA_R3_Bayes[nbins_cent], * RAA_R4_Bayes[nbins_cent];
  TH1F * RAA_R2_BinByBin[nbins_cent], * RAA_R3_BinByBin[nbins_cent], * RAA_R4_BinByBin[nbins_cent];
  TH1F * RAA_R2_Meas[nbins_cent], * RAA_R3_Meas[nbins_cent], * RAA_R4_Meas[nbins_cent];
  
  TH1F * hRatio_R2_Bayes[nbins_cent], * hRatio_R3_Bayes[nbins_cent], * hRatio_R4_Bayes[nbins_cent];
  TF1 * Fit_R2_Bayes[nbins_cent], * Fit_R3_Bayes[nbins_cent], * Fit_R4_Bayes[nbins_cent];
  TH1F * hFit_R2_Bayes[nbins_cent], * hFit_R3_Bayes[nbins_cent], * hFit_R4_Bayes[nbins_cent];

  uPP_R2_Bayes = (TH1F*)fin_R2->Get("PP_bayesian_unfolded_spectra");
  uPP_R2_Bayes->Print("base");
  uPP_R3_Bayes = (TH1F*)fin_R3->Get("PP_bayesian_unfolded_spectra");
  uPP_R3_Bayes->Print("base");
  uPP_R4_Bayes = (TH1F*)fin_R4->Get("PP_bayesian_unfolded_spectra");
  uPP_R4_Bayes->Print("base");

  mPP_R2 = (TH1F*)fin_R2->Get("PP_Gen_spectra_refpt");
  mPP_R2->Print("base");
  mPP_R3 = (TH1F*)fin_R3->Get("PP_Gen_spectra_refpt");
  mPP_R3->Print("base");
  mPP_R4 = (TH1F*)fin_R4->Get("PP_Gen_spectra_refpt");
  mPP_R4->Print("base");
  
  for(int i = 0; i<nbins_cent; ++i){

    uPbPb_R2_Bayes[i] = (TH1F*)fin_R2->Get(Form("PbPb_bayesian_unfolded_spectra_combined_cent%d",i));
    uPbPb_R2_Bayes[i]->Print("base");
    uPbPb_R3_Bayes[i] = (TH1F*)fin_R3->Get(Form("PbPb_bayesian_unfolded_spectra_combined_cent%d",i));
    uPbPb_R3_Bayes[i]->Print("base");
    uPbPb_R4_Bayes[i] = (TH1F*)fin_R4->Get(Form("PbPb_bayesian_unfolded_spectra_combined_cent%d",i));
    uPbPb_R3_Bayes[i]->Print("base");
 
    mPbPb_R2[i] = (TH1F*)fin_R2->Get(Form("PbPb_Gen_spectra_refpt_cent%d",i));
    mPbPb_R2[i]->Print("base");
    mPbPb_R3[i] = (TH1F*)fin_R3->Get(Form("PbPb_Gen_spectra_refpt_cent%d",i));
    mPbPb_R3[i]->Print("base");
    mPbPb_R4[i] = (TH1F*)fin_R4->Get(Form("PbPb_Gen_spectra_refpt_cent%d",i));
    mPbPb_R4[i]->Print("base");
    
    RAA_R2_Bayes[i]   = (TH1F*)fin_R2->Get(Form("RAA_bayesian_cent%d",i));  
    RAA_R2_Bayes[i]->Print("base");
    RAA_R3_Bayes[i]   = (TH1F*)fin_R3->Get(Form("RAA_bayesian_cent%d",i));  
    RAA_R3_Bayes[i]->Print("base");
    RAA_R4_Bayes[i]   = (TH1F*)fin_R4->Get(Form("RAA_bayesian_cent%d",i));  
    RAA_R4_Bayes[i]->Print("base");
    
    RAA_R2_BinByBin[i]   = (TH1F*)fin_R2->Get(Form("RAA_binbybin_cent%d",i));  
    RAA_R3_BinByBin[i]   = (TH1F*)fin_R3->Get(Form("RAA_binbybin_cent%d",i));  
    RAA_R4_BinByBin[i]   = (TH1F*)fin_R4->Get(Form("RAA_binbybin_cent%d",i));  
    
    RAA_R2_Meas[i]   = (TH1F*)fin_R2->Get(Form("RAA_measured_cent%d",i));  
    RAA_R3_Meas[i]   = (TH1F*)fin_R3->Get(Form("RAA_measured_cent%d",i));  
    RAA_R4_Meas[i]   = (TH1F*)fin_R4->Get(Form("RAA_measured_cent%d",i));  
    
  }
  
  // plot 1 - spectra plot showing pp and 6 different centrality classes PbPb spectra
  //        - have a 3 panel plot for the different radii, with each of them scaled by two orders of magnitude 

  // first we need to scale the MC to the level of Data:
  // PbPb Data scaling:
  //   uPbPb_Bayes[i]->Scale(1./deltaEta);// delta eta
  //   //uPbPb_Bayes[i]->Scale(1./145.156/1e6);// Jet 80 luminosity
  //   //uPbPb_Bayes[i]->Scale(1./1.1153/1e6);// equivalent no of minbias events 
  //   uPbPb_Bayes[i]->Scale(1./(0.025*(boundaries_cent[i+1] - boundaries_cent[i])));
  //   //uPbPb_Bayes[i]->Scale(1./145.156);
  //   //uPbPb_Bayes[i]->Scale(1./161.939);
  //   uPbPb_Bayes[i]->Scale(1./(7.65*1e6));
  //   uPbPb_Bayes[i]->Scale(64.*1e9/(ncoll[i]*1e3));
  //   uPbPb_Bayes[i] = (TH1F*)uPbPb_Bayes[i]->Rebin(nbins_pt,Form("PbPb_bayesian_unfolded_spectra_combined_cent%d",i),boundaries_pt);
  //   divideBinWidth(uPbPb_Bayes[i]);
  //   uPbPb_Bayes[i]->Write();
  //   So finally PbPb is in 

  // PbPb MC scaling: is already in sigma (mb) / (dEta dpT)
  //   mPbPb_Reco[i]->Scale(1./deltaEta);// delta eta
  //   mPbPb_Reco[i] = (TH1F*)mPbPb_Reco[i]->Rebin(nbins_pt,Form("PbPb_Reco_spectra_refpt_cent%d",i),boundaries_pt);
  //   divideBinWidth(mPbPb_Reco[i]);
  //   mPbPb_Reco[i]->Write();

// //   // take MC to nano barns from milli barns 
// //   mPP_R2->Scale(1e6);
// //   mPP_R3->Scale(1e6);
// //   mPP_R4->Scale(1e6);
// // 
// //   // divide by delta eta = 4. 
// //   mPP_R2->Scale(1./4);
// //   mPP_R3->Scale(1./4);
// //   mPP_R4->Scale(1./4);
// // 
// //   for(int i = 0; i<nbins_cent; ++i){
// // 
// //     mPbPb_R2[i]->Scale(1./(0.025*(boundaries_cent[i+1] - boundaries_cent[i])));
// //     mPbPb_R2[i]->Scale(64.*1e9/(ncoll[i]*1e3));
// //     mPbPb_R2[i]->Scale(1./(7.65));
// // 
// //     mPbPb_R3[i]->Scale(1./(0.025*(boundaries_cent[i+1] - boundaries_cent[i])));
// //     mPbPb_R3[i]->Scale(64.*1e9/(ncoll[i]*1e3));
// //     mPbPb_R3[i]->Scale(1./(7.65));
// // 
// //     mPbPb_R4[i]->Scale(1./(0.025*(boundaries_cent[i+1] - boundaries_cent[i])));
// //     mPbPb_R4[i]->Scale(64.*1e9/(ncoll[i]*1e3));
// //     mPbPb_R4[i]->Scale(1./(7.65));
// //     
// //   }
      TLine *lineRatio = new TLine(60,1,300,1);
    lineRatio->SetLineStyle(2);
    lineRatio->SetLineWidth(2);
  TH2F * hBlankSpectra = new TH2F("hBlankSpectra","",400,60,300,400,1e-4,30);
  TH2F * hBlankRatio = new TH2F("hBlankRatio","",400,60,300,400,0,2);
      
  Double_t ScaleFactor[nbins_cent+2] = {1, 1e2, 1e4, 1e6, 1e8, 1e10, 1e12, 1e14};  
  TCanvas * cSpectra3Pow = new TCanvas("cSpectra3Pow","",1200,1000);
  //cSpectra->cd(2);
  cSpectra3Pow->SetLogy();
  cSpectra3Pow->SetGridy();
  cSpectra3Pow->SetLogx();

 // uPP_R3_Bayes->Scale(ScaleFactor[0]);
  uPP_R3_Bayes->SetMarkerStyle(20);
  uPP_R3_Bayes->SetMarkerColor(kBlack);
  makeHistTitle(uPP_R3_Bayes," "," Jet p_{T} (GeV/c)","#frac{d #sigma}{T_{AA} dp_{T} d#eta} nb");
  uPP_R3_Bayes->SetAxisRange(unfoldingCut, 300, "X");
 // uPP_R3_Bayes->SetAxisRange(1e-4, 1e15, "Y");
  hBlankSpectra->Draw();
  uPP_R3_Bayes->Draw("same");

   TF1 *f = new TF1("f","[0]*pow(x+[2],[1])"); //create function
   f->SetParameters(1e10,-5,0);
   f->SetLineColor(kBlue);
   TH1F *hRatioPP3 = (TH1F*)uPP_R3_Bayes->Clone("hRatioPP3"); //clone histogram hRatio from h
   uPP_R3_Bayes->Fit("f","LL","",FitStart,FitEnd); //fit function
   uPP_R3_Bayes->Fit("f","LL","",FitStart,FitEnd);
   uPP_R3_Bayes->Fit("f","LL","",FitStart,FitEnd);
   uPP_R3_Bayes->Fit("f","LL","",FitStart,FitEnd);
   uPP_R3_Bayes->Fit("f","LL","",FitStart,FitEnd);
   uPP_R3_Bayes->Fit("f","LL","",FitStart,FitEnd);
   uPP_R3_Bayes->Fit("f","LL","",FitStart,FitEnd);
   uPP_R3_Bayes->Fit("f","LL","",FitStart,FitEnd);
   f->Draw("same");

   TH1F *hF = (TH1F*)uPP_R3_Bayes->Clone(); //clone histogram uPP_R3_Bayes from h
   for (int i=1;i<=uPP_R3_Bayes->GetNbinsX();i++) //Turn the fit line into a histogram so I can take a ratio
   {
      double var = f->Integral(uPP_R3_Bayes->GetBinLowEdge(i),uPP_R3_Bayes->GetBinLowEdge(i+1))/uPP_R3_Bayes->GetBinWidth(i);
      hF->SetBinContent(i,var);
   }
//   // draw the MC
//   mPP_R3->Scale(ScaleFactor[0]);
//   //mPP_R3->SetLineStyle(2);
//   mPP_R3->SetLineColor(kBlack);
//   mPP_R3->SetAxisRange(unfoldingCut, 299, "X");
//   mPP_R3->Draw("same Lhist");
  

  TLegend * leg1 = myLegend(0.15,0.1,0.25,0.2);
  leg1->AddEntry(uPP_R3_Bayes,"pp Data","pl");
  leg1->AddEntry(f,"Power law fit","l");
  leg1->SetTextSize(0.02);
  leg1->Draw();
  
  
  drawText("R=0.3, anti k_{T} PF Jets, Bayesian unfolded", 0.15,0.2,16);
  putCMSPrel();
  putPPLumi();
  
  //drawText("pp", 0.7,0.15,16);
  cSpectra3Pow->SaveAs(Form("Plots/Final_paper_plots_spectraPowerLaw_R3_%d.pdf",date.GetDate()),"RECREATE");  
  
    TCanvas * cSpectra3Rat = new TCanvas("cSpectra3Rat","",1200,1000);
  //cSpectra->cd(2);
  cSpectra3Rat->SetGridy();
  cSpectra3Rat->SetLogx();
  hRatioPP3->Divide(hF);
  hRatioPP3->SetMarkerStyle(20);
  hRatioPP3->SetMarkerColor(kBlack);
  makeHistTitle(hRatioPP3," "," Jet p_{T} (GeV/c)","Bayesian unfolded data/Power law fit");
  hRatioPP3->SetAxisRange(unfoldingCut, 299, "X");
 // uPP_R3_Bayes->SetAxisRange(1e-4, 1e15, "Y");
  hBlankRatio->Draw();
  hRatioPP3->Draw("same");
  lineRatio->Draw("same");
  drawText("R=0.3, anti k_{T} PF Jets, Bayesian unfolded", 0.15,0.2,16);
  putCMSPrel();
  putPPLumi();
  cSpectra3Rat->SaveAs(Form("Plots/Final_paper_plots_spectraPowerLawFitRatio_R3_%d.pdf",date.GetDate()),"RECREATE");  

  TCanvas * cSpectra2Pow = new TCanvas("cSpectra2Pow","",1200,1000);
  //cSpectra->cd(2);
  cSpectra2Pow->SetLogy();
  cSpectra2Pow->SetGridy();
  cSpectra2Pow->SetLogx();

 // uPP_R2_Bayes->Scale(ScaleFactor[0]);
  uPP_R2_Bayes->SetMarkerStyle(20);
  uPP_R2_Bayes->SetMarkerColor(kBlack);
  makeHistTitle(uPP_R2_Bayes," "," Jet p_{T} (GeV/c)","#frac{d #sigma}{T_{AA} dp_{T} d#eta} nb");
  uPP_R2_Bayes->SetAxisRange(unfoldingCut, 300, "X");
 // uPP_R2_Bayes->SetAxisRange(1e-4, 1e15, "Y");
 hBlankSpectra->Draw();
  uPP_R2_Bayes->Draw("same");

   TF1 *f2 = new TF1("f2","[0]*pow(x+[2],[1])"); //create function
   f2->SetParameters(1e10,-5,0);
   f2->SetLineColor(kBlue);
   TH1F *hRatioPP2 = (TH1F*)uPP_R2_Bayes->Clone("hRatioPP2"); //clone histogram hRatio from h
   uPP_R2_Bayes->Fit("f2","LL","",FitStart,FitEnd); //fit function
   uPP_R2_Bayes->Fit("f2","LL","",FitStart,FitEnd);
   uPP_R2_Bayes->Fit("f2","LL","",FitStart,FitEnd);
   uPP_R2_Bayes->Fit("f2","LL","",FitStart,FitEnd);
   uPP_R2_Bayes->Fit("f2","LL","",FitStart,FitEnd);
   uPP_R2_Bayes->Fit("f2","LL","",FitStart,FitEnd);
   uPP_R2_Bayes->Fit("f2","LL","",FitStart,FitEnd);
   uPP_R2_Bayes->Fit("f2","LL","",FitStart,FitEnd);
   f2->Draw("same");

   TH1F *hF2 = (TH1F*)uPP_R2_Bayes->Clone(); //clone histogram uPP_R2_Bayes from h
   for (int i=1;i<=uPP_R2_Bayes->GetNbinsX();i++) //Turn the fit line into a histogram so I can take a ratio
   {
      double var = f2->Integral(uPP_R2_Bayes->GetBinLowEdge(i),uPP_R2_Bayes->GetBinLowEdge(i+1))/uPP_R2_Bayes->GetBinWidth(i);
      hF2->SetBinContent(i,var);
   }
//   // draw the MC
//   mPP_R2->Scale(ScaleFactor[0]);
//   //mPP_R2->SetLineStyle(2);
//   mPP_R2->SetLineColor(kBlack);
//   mPP_R2->SetAxisRange(unfoldingCut, 299, "X");
//   mPP_R2->Draw("same Lhist");
  

  TLegend * leg2 = myLegend(0.15,0.1,0.25,0.2);
  leg2->AddEntry(uPP_R2_Bayes,"pp Data","pl");
  leg2->AddEntry(f2,"Power law fit","l");
  leg2->SetTextSize(0.02);
  leg2->Draw();
  
  
  drawText("R=0.2, anti k_{T} PF Jets, Bayesian unfolded", 0.15,0.2,16);
  putCMSPrel();
  putPPLumi();
  
  //drawText("pp", 0.7,0.15,16);
  cSpectra2Pow->SaveAs(Form("Plots/Final_paper_plots_spectraPowerLaw_R2_%d.pdf",date.GetDate()),"RECREATE");  
  
    TCanvas * cSpectra2Rat = new TCanvas("cSpectra2Rat","",1200,1000);
  //cSpectra->cd(2);
  cSpectra2Rat->SetGridy();
  cSpectra2Rat->SetLogx();
  hRatioPP2->Divide(hF2);
  hRatioPP2->SetMarkerStyle(20);
  hRatioPP2->SetMarkerColor(kBlack);
  makeHistTitle(hRatioPP2," "," Jet p_{T} (GeV/c)","Bayesian unfolded data/Power law fit");
  hRatioPP2->SetAxisRange(unfoldingCut, 299, "X");
 // uPP_R2_Bayes->SetAxisRange(1e-4, 1e15, "Y");
 hBlankRatio->Draw();
  hRatioPP2->Draw("same");
  lineRatio->Draw("same");
  drawText("R=0.2, anti k_{T} PF Jets, Bayesian unfolded", 0.15,0.2,16);
  putCMSPrel();
  putPPLumi();
  cSpectra2Rat->SaveAs(Form("Plots/Final_paper_plots_spectraPowerLawFitRatio_R2_%d.pdf",date.GetDate()),"RECREATE"); 
  
    TCanvas * cSpectra4Pow = new TCanvas("cSpectra4Pow","",1200,1000);
  //cSpectra->cd(2);
  cSpectra4Pow->SetLogy();
  cSpectra4Pow->SetGridy();
  cSpectra4Pow->SetLogx();

 // uPP_R4_Bayes->Scale(ScaleFactor[0]);
  uPP_R4_Bayes->SetMarkerStyle(20);
  uPP_R4_Bayes->SetMarkerColor(kBlack);
  makeHistTitle(uPP_R4_Bayes," "," Jet p_{T} (GeV/c)","#frac{d #sigma}{T_{AA} dp_{T} d#eta} nb");
  uPP_R4_Bayes->SetAxisRange(unfoldingCut, 300, "X");
 // uPP_R4_Bayes->SetAxisRange(1e-4, 1e15, "Y");
  hBlankSpectra->Draw();
  uPP_R4_Bayes->Draw("same");

   TF1 *f4 = new TF1("f4","[0]*pow(x+[2],[1])"); //create function
   f4->SetParameters(1e10,-5,0);
   f4->SetLineColor(kBlue);
   TH1F *hRatioPP4 = (TH1F*)uPP_R4_Bayes->Clone("hRatioPP4"); //clone histogram hRatio from h
   uPP_R4_Bayes->Fit("f4","LL","",FitStart,FitEnd); //fit function
   uPP_R4_Bayes->Fit("f4","LL","",FitStart,FitEnd);
   uPP_R4_Bayes->Fit("f4","LL","",FitStart,FitEnd);
   uPP_R4_Bayes->Fit("f4","LL","",FitStart,FitEnd);
   uPP_R4_Bayes->Fit("f4","LL","",FitStart,FitEnd);
   uPP_R4_Bayes->Fit("f4","LL","",FitStart,FitEnd);
   uPP_R4_Bayes->Fit("f4","LL","",FitStart,FitEnd);
   uPP_R4_Bayes->Fit("f4","LL","",FitStart,FitEnd);
   f4->Draw("same");

   TH1F *hF4 = (TH1F*)uPP_R4_Bayes->Clone(); //clone histogram uPP_R4_Bayes from h
   for (int i=1;i<=uPP_R4_Bayes->GetNbinsX();i++) //Turn the fit line into a histogram so I can take a ratio
   {
      double var = f4->Integral(uPP_R4_Bayes->GetBinLowEdge(i),uPP_R4_Bayes->GetBinLowEdge(i+1))/uPP_R4_Bayes->GetBinWidth(i);
      hF4->SetBinContent(i,var);
   }
//   // draw the MC
//   mPP_R4->Scale(ScaleFactor[0]);
//   //mPP_R4->SetLineStyle(2);
//   mPP_R4->SetLineColor(kBlack);
//   mPP_R4->SetAxisRange(unfoldingCut, 299, "X");
//   mPP_R4->Draw("same Lhist");
  

  TLegend * leg4 = myLegend(0.15,0.1,0.25,0.2);
  leg4->AddEntry(uPP_R4_Bayes,"pp Data","pl");
  leg4->AddEntry(f4,"Power law fit","l");
  leg4->SetTextSize(0.02);
  leg4->Draw();
  
  
  drawText("R=0.3, anti k_{T} PF Jets, Bayesian unfolded", 0.15,0.2,16);
  putCMSPrel();
  putPPLumi();
  
  //drawText("pp", 0.7,0.15,16);
  cSpectra4Pow->SaveAs(Form("Plots/Final_paper_plots_spectraPowerLaw_R4_%d.pdf",date.GetDate()),"RECREATE");  
  
    TCanvas * cSpectra4Rat = new TCanvas("cSpectra4Rat","",1200,1000);
  //cSpectra->cd(2);
  cSpectra4Rat->SetGridy();
  cSpectra4Rat->SetLogx();
  hRatioPP4->Divide(hF4);
  hRatioPP4->SetMarkerStyle(20);
  hRatioPP4->SetMarkerColor(kBlack);
  makeHistTitle(hRatioPP4," "," Jet p_{T} (GeV/c)","Bayesian unfolded data/Power law fit");
  hRatioPP4->SetAxisRange(unfoldingCut, 299, "X");
 // uPP_R4_Bayes->SetAxisRange(1e-4, 1e15, "Y");
  hBlankRatio->Draw();
  hRatioPP4->Draw("same");
  lineRatio->Draw("same");
  drawText("R=0.3, anti k_{T} PF Jets, Bayesian unfolded", 0.15,0.2,16);
  putCMSPrel();
  putPPLumi();
  cSpectra4Rat->SaveAs(Form("Plots/Final_paper_plots_spectraPowerLawFitRatio_R4_%d.pdf",date.GetDate()),"RECREATE"); 
  
  TCanvas *cPbPb_PowerLaw_R2 = new TCanvas("cPbPb_PowerLaw_R2","Power Law fit comparisons for PbPb unfolded spectra",1200,800);
  makeMultiPanelCanvas(cPbPb_PowerLaw_R2,3,2,0.0,0.0,0.2,0.15,0.07);

  
    for(int i = 0; i<nbins_cent; ++i){
      cPbPb_PowerLaw_R2->cd(nbins_cent-i);
      cPbPb_PowerLaw_R2->cd(nbins_cent-i)->SetLogy();
      cPbPb_PowerLaw_R2->cd(nbins_cent-i)->SetLogx();
      uPbPb_R2_Bayes[i]->SetMarkerStyle(20);
      uPbPb_R2_Bayes[i]->SetMarkerColor(kRed);
      uPbPb_R2_Bayes[i]->SetAxisRange(unfoldingCut, 300, "X");
      makeHistTitle(uPbPb_R2_Bayes[i]," "," Jet p_{T} (GeV/c)","#frac{d #sigma}{T_{AA} dp_{T} d#eta} nb");
      hBlankSpectra->Draw();
      uPbPb_R2_Bayes[i]->Draw("same");
   Fit_R2_Bayes[i] = new TF1(Form("Fit_R2_Bayes%d",i),"[0]*pow(x+[2],[1])"); //create function
   Fit_R2_Bayes[i]->SetParameters(1e10,-5,0);
   Fit_R2_Bayes[i]->SetLineColor(kBlue);
   hRatio_R2_Bayes[i] = (TH1F*)uPbPb_R2_Bayes[i]->Clone(Form("PbPb_bayesian_unfolded_spectra_combined_cent%d",i)); //clone histogram hRatio from h
   uPbPb_R2_Bayes[i]->Fit(Form("Fit_R2_Bayes%d",i),"LL","",FitStart,FitEnd); //fit function
   uPbPb_R2_Bayes[i]->Fit(Form("Fit_R2_Bayes%d",i),"LL","",FitStart,FitEnd);
   uPbPb_R2_Bayes[i]->Fit(Form("Fit_R2_Bayes%d",i),"LL","",FitStart,FitEnd);
   uPbPb_R2_Bayes[i]->Fit(Form("Fit_R2_Bayes%d",i),"LL","",FitStart,FitEnd);
    uPbPb_R2_Bayes[i]->Fit(Form("Fit_R2_Bayes%d",i),"LL","",FitStart,FitEnd);
    uPbPb_R2_Bayes[i]->Fit(Form("Fit_R2_Bayes%d",i),"LL","",FitStart,FitEnd);
    uPbPb_R2_Bayes[i]->Fit(Form("Fit_R2_Bayes%d",i),"LL","",FitStart,FitEnd);
    uPbPb_R2_Bayes[i]->Fit(Form("Fit_R2_Bayes%d",i),"LL","",FitStart,FitEnd);
   Fit_R2_Bayes[i]->Draw("same");

  hFit_R2_Bayes[i] = (TH1F*)uPbPb_R2_Bayes[i]->Clone(); //clone histogram uPP_R4_Bayes from h
   for (int iv=1;iv<=uPbPb_R2_Bayes[i]->GetNbinsX();iv++) //Turn the fit line into a histogram so I can take a ratio
   {
      double var = Fit_R2_Bayes[i]->Integral(uPbPb_R2_Bayes[i]->GetBinLowEdge(iv),uPbPb_R2_Bayes[i]->GetBinLowEdge(iv+1))/uPbPb_R2_Bayes[i]->GetBinWidth(iv);
      hFit_R2_Bayes[i]->SetBinContent(iv,var);
   }
      drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.6,0.8,20);

  }
  putCMSPrel();
  putPbPbLumi();
  drawText(Form("Anti-k_{T} R=0.2 %s %s Jets",algo,jet_type),0.2,0.23,16);
  cPbPb_PowerLaw_R2->SaveAs(Form("Plots/Final_paper_plots_spectraPowerLawFit_PbPb_R2_%d.pdf",date.GetDate()),"RECREATE"); 

  TCanvas *cPbPb_PowerLawRat_R2 = new TCanvas("cPbPb_PowerLawRat_R2","PbPb unfolded spectra/Power Law Fit",1200,800);
  makeMultiPanelCanvas(cPbPb_PowerLawRat_R2,3,2,0.0,0.0,0.2,0.15,0.07);

    for(int i = 0; i<nbins_cent; ++i){
      cPbPb_PowerLawRat_R2->cd(nbins_cent-i);
      cPbPb_PowerLawRat_R2->cd(nbins_cent-i)->SetLogx();
      hRatio_R2_Bayes[i]->SetMarkerStyle(21);
      hRatio_R2_Bayes[i]->SetMarkerColor(kBlue);
      hRatio_R2_Bayes[i]->SetAxisRange(unfoldingCut, 300, "X");
      hRatio_R2_Bayes[i]->Divide(hFit_R2_Bayes[i]);
      makeHistTitle(hBlankRatio," "," Jet p_{T} (GeV/c)","Bayesian unfolded data/Power law fit");
      hBlankRatio->Draw();
      hRatio_R2_Bayes[i]->Draw("same");
      lineRatio->Draw("same");
      drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.6,0.8,20);
  }
  putCMSPrel();
  putPbPbLumi();
  drawText(Form("Anti-k_{T} R=0.2 %s %s Jets",algo,jet_type),0.2,0.23,16);
 cPbPb_PowerLawRat_R2->SaveAs(Form("Plots/Final_paper_plots_spectraPowerLawFitRatio_PbPb_R2_%d.pdf",date.GetDate()),"RECREATE"); 

  TCanvas *cPbPb_PowerLaw_R3 = new TCanvas("cPbPb_PowerLaw_R3","Power Law fit comparisons for PbPb unfolded spectra",1200,800);
  makeMultiPanelCanvas(cPbPb_PowerLaw_R3,3,2,0.0,0.0,0.2,0.15,0.07);

  
    for(int i = 0; i<nbins_cent; ++i){
      cPbPb_PowerLaw_R3->cd(nbins_cent-i);
      cPbPb_PowerLaw_R3->cd(nbins_cent-i)->SetLogy();
      cPbPb_PowerLaw_R3->cd(nbins_cent-i)->SetLogx();
      uPbPb_R3_Bayes[i]->SetMarkerStyle(20);
      uPbPb_R3_Bayes[i]->SetMarkerColor(kRed);
      uPbPb_R3_Bayes[i]->SetAxisRange(unfoldingCut, 300, "X");
      makeHistTitle(uPbPb_R3_Bayes[i]," "," Jet p_{T} (GeV/c)","#frac{d #sigma}{T_{AA} dp_{T} d#eta} nb");
      hBlankSpectra->Draw();
      uPbPb_R3_Bayes[i]->Draw("same");
   Fit_R3_Bayes[i] = new TF1(Form("Fit_R3_Bayes%d",i),"[0]*pow(x+[2],[1])"); //create function
   Fit_R3_Bayes[i]->SetParameters(1e10,-5,0);
   Fit_R3_Bayes[i]->SetLineColor(kBlue);
   hRatio_R3_Bayes[i] = (TH1F*)uPbPb_R3_Bayes[i]->Clone(Form("PbPb_bayesian_unfolded_spectra_combined_cent%d",i)); //clone histogram hRatio from h
   uPbPb_R3_Bayes[i]->Fit(Form("Fit_R3_Bayes%d",i),"LL","",FitStart,FitEnd); //fit function
   uPbPb_R3_Bayes[i]->Fit(Form("Fit_R3_Bayes%d",i),"LL","",FitStart,FitEnd);
   uPbPb_R3_Bayes[i]->Fit(Form("Fit_R3_Bayes%d",i),"LL","",FitStart,FitEnd);
   uPbPb_R3_Bayes[i]->Fit(Form("Fit_R3_Bayes%d",i),"LL","",FitStart,FitEnd);
    uPbPb_R3_Bayes[i]->Fit(Form("Fit_R3_Bayes%d",i),"LL","",FitStart,FitEnd);
    uPbPb_R3_Bayes[i]->Fit(Form("Fit_R3_Bayes%d",i),"LL","",FitStart,FitEnd);
    uPbPb_R3_Bayes[i]->Fit(Form("Fit_R3_Bayes%d",i),"LL","",FitStart,FitEnd);
    uPbPb_R3_Bayes[i]->Fit(Form("Fit_R3_Bayes%d",i),"LL","",FitStart,FitEnd);
   Fit_R3_Bayes[i]->Draw("same");

  hFit_R3_Bayes[i] = (TH1F*)uPbPb_R3_Bayes[i]->Clone(); //clone histogram uPP_R4_Bayes from h
   for (int iv=1;iv<=uPbPb_R3_Bayes[i]->GetNbinsX();iv++) //Turn the fit line into a histogram so I can take a ratio
   {
      double var = Fit_R3_Bayes[i]->Integral(uPbPb_R3_Bayes[i]->GetBinLowEdge(iv),uPbPb_R3_Bayes[i]->GetBinLowEdge(iv+1))/uPbPb_R3_Bayes[i]->GetBinWidth(iv);
      hFit_R3_Bayes[i]->SetBinContent(iv,var);
   }
      drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.6,0.8,20);

  }
  putCMSPrel();
  putPbPbLumi();
  drawText(Form("Anti-k_{T} R=0.2 %s %s Jets",algo,jet_type),0.2,0.23,16);
  cPbPb_PowerLaw_R3->SaveAs(Form("Plots/Final_paper_plots_spectraPowerLawFit_PbPb_R3_%d.pdf",date.GetDate()),"RECREATE"); 

  TCanvas *cPbPb_PowerLawRat_R3 = new TCanvas("cPbPb_PowerLawRat_R3","PbPb unfolded spectra/Power Law Fit",1200,800);
  makeMultiPanelCanvas(cPbPb_PowerLawRat_R3,3,2,0.0,0.0,0.2,0.15,0.07);

    for(int i = 0; i<nbins_cent; ++i){
      cPbPb_PowerLawRat_R3->cd(nbins_cent-i);
      cPbPb_PowerLawRat_R3->cd(nbins_cent-i)->SetLogx();
      hRatio_R3_Bayes[i]->SetMarkerStyle(21);
      hRatio_R3_Bayes[i]->SetMarkerColor(kBlue);
      hRatio_R3_Bayes[i]->SetAxisRange(unfoldingCut, 300, "X");
      hRatio_R3_Bayes[i]->Divide(hFit_R3_Bayes[i]);
      makeHistTitle(hBlankRatio," "," Jet p_{T} (GeV/c)","Bayesian unfolded data/Power law fit");
      hBlankRatio->Draw();
      hRatio_R3_Bayes[i]->Draw("same");
      lineRatio->Draw("same");
      drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.6,0.8,20);
  }
  putCMSPrel();
  putPbPbLumi();
  drawText(Form("Anti-k_{T} R=0.3 %s %s Jets",algo,jet_type),0.2,0.23,16);
 cPbPb_PowerLawRat_R3->SaveAs(Form("Plots/Final_paper_plots_spectraPowerLawFitRatio_PbPb_R3_%d.pdf",date.GetDate()),"RECREATE"); 
 
   TCanvas *cPbPb_PowerLaw_R4 = new TCanvas("cPbPb_PowerLaw_R4","Power Law fit comparisons for PbPb unfolded spectra",1200,800);
  makeMultiPanelCanvas(cPbPb_PowerLaw_R4,3,2,0.0,0.0,0.2,0.15,0.07);

  
    for(int i = 0; i<nbins_cent; ++i){
      cPbPb_PowerLaw_R4->cd(nbins_cent-i);
      cPbPb_PowerLaw_R4->cd(nbins_cent-i)->SetLogy();
      cPbPb_PowerLaw_R4->cd(nbins_cent-i)->SetLogx();
      uPbPb_R4_Bayes[i]->SetMarkerStyle(20);
      uPbPb_R4_Bayes[i]->SetMarkerColor(kRed);
      uPbPb_R4_Bayes[i]->SetAxisRange(unfoldingCut, 300, "X");
      makeHistTitle(uPbPb_R4_Bayes[i]," "," Jet p_{T} (GeV/c)","#frac{d #sigma}{T_{AA} dp_{T} d#eta} nb");
      hBlankSpectra->Draw();
      uPbPb_R4_Bayes[i]->Draw("same");
   Fit_R4_Bayes[i] = new TF1(Form("Fit_R4_Bayes%d",i),"[0]*pow(x+[2],[1])"); //create function
   Fit_R4_Bayes[i]->SetParameters(1e10,-5,0);
   Fit_R4_Bayes[i]->SetLineColor(kBlue);
   hRatio_R4_Bayes[i] = (TH1F*)uPbPb_R4_Bayes[i]->Clone(Form("PbPb_bayesian_unfolded_spectra_combined_cent%d",i)); //clone histogram hRatio from h
   uPbPb_R4_Bayes[i]->Fit(Form("Fit_R4_Bayes%d",i),"LL","",FitStart,FitEnd); //fit function
   uPbPb_R4_Bayes[i]->Fit(Form("Fit_R4_Bayes%d",i),"LL","",FitStart,FitEnd);
   uPbPb_R4_Bayes[i]->Fit(Form("Fit_R4_Bayes%d",i),"LL","",FitStart,FitEnd);
   uPbPb_R4_Bayes[i]->Fit(Form("Fit_R4_Bayes%d",i),"LL","",FitStart,FitEnd);
    uPbPb_R4_Bayes[i]->Fit(Form("Fit_R4_Bayes%d",i),"LL","",FitStart,FitEnd);
    uPbPb_R4_Bayes[i]->Fit(Form("Fit_R4_Bayes%d",i),"LL","",FitStart,FitEnd);
    uPbPb_R4_Bayes[i]->Fit(Form("Fit_R4_Bayes%d",i),"LL","",FitStart,FitEnd);
    uPbPb_R4_Bayes[i]->Fit(Form("Fit_R4_Bayes%d",i),"LL","",FitStart,FitEnd);
   Fit_R4_Bayes[i]->Draw("same");

  hFit_R4_Bayes[i] = (TH1F*)uPbPb_R4_Bayes[i]->Clone(); //clone histogram uPP_R4_Bayes from h
   for (int iv=1;iv<=uPbPb_R4_Bayes[i]->GetNbinsX();iv++) //Turn the fit line into a histogram so I can take a ratio
   {
      double var = Fit_R4_Bayes[i]->Integral(uPbPb_R4_Bayes[i]->GetBinLowEdge(iv),uPbPb_R4_Bayes[i]->GetBinLowEdge(iv+1))/uPbPb_R4_Bayes[i]->GetBinWidth(iv);
      hFit_R4_Bayes[i]->SetBinContent(iv,var);
   }
      drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.6,0.8,20);

  }
  putCMSPrel();
  putPbPbLumi();
  drawText(Form("Anti-k_{T} R=0.2 %s %s Jets",algo,jet_type),0.2,0.23,16);
  cPbPb_PowerLaw_R4->SaveAs(Form("Plots/Final_paper_plots_spectraPowerLawFit_PbPb_R4_%d.pdf",date.GetDate()),"RECREATE"); 

  TCanvas *cPbPb_PowerLawRat_R4 = new TCanvas("cPbPb_PowerLawRat_R4","PbPb unfolded spectra/Power Law Fit",1200,800);
  makeMultiPanelCanvas(cPbPb_PowerLawRat_R4,3,2,0.0,0.0,0.2,0.15,0.07);

    for(int i = 0; i<nbins_cent; ++i){
      cPbPb_PowerLawRat_R4->cd(nbins_cent-i);
      cPbPb_PowerLawRat_R4->cd(nbins_cent-i)->SetLogx();
      hRatio_R4_Bayes[i]->SetMarkerStyle(21);
      hRatio_R4_Bayes[i]->SetMarkerColor(kBlue);
      hRatio_R4_Bayes[i]->SetAxisRange(unfoldingCut, 300, "X");
      hRatio_R4_Bayes[i]->Divide(hFit_R4_Bayes[i]);
      makeHistTitle(hBlankRatio," "," Jet p_{T} (GeV/c)","Bayesian unfolded data/Power law fit");
      hBlankRatio->Draw();
      hRatio_R4_Bayes[i]->Draw("same");
      lineRatio->Draw("same");
      drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.6,0.8,20);
  }
  putCMSPrel();
  putPbPbLumi();
  drawText(Form("Anti-k_{T} R=0.4 %s %s Jets",algo,jet_type),0.2,0.23,16);
 cPbPb_PowerLawRat_R4->SaveAs(Form("Plots/Final_paper_plots_spectraPowerLawFitRatio_PbPb_R4_%d.pdf",date.GetDate()),"RECREATE"); 
// //     uPbPb_R2_Bayes[i]->Scale(ScaleFactor[i+1]);
// //     uPbPb_R2_Bayes[i]->SetMarkerStyle(20);
// //     uPbPb_R2_Bayes[i]->SetMarkerColor(kRed);
// //     uPbPb_R2_Bayes[i]->Draw("same");
// //   }

// //   TCanvas * cSpectra = new TCanvas("cSpectra","",1200,1000);
// //   //makeMultiPanelCanvas(cSpectra,3,1,0.0,0.0,0.2,0.15,0.07);
// //   
// //   cSpectra->cd(1);
// //   cSpectra->cd(1)->SetLogy();
// //   cSpectra->cd(1)->SetLogx();
// // 
// //   uPP_R2_Bayes->Scale(ScaleFactor[0]);
// //   uPP_R2_Bayes->SetMarkerStyle(20);
// //   uPP_R2_Bayes->SetMarkerColor(kBlack);
// //   makeHistTitle(uPP_R2_Bayes," "," Jet p_{T} (GeV/c)","cross section");
// //   uPP_R2_Bayes->SetAxisRange(unfoldingCut, 299, "X");
// //   uPP_R2_Bayes->SetAxisRange(1e-4, 1e15, "Y");
// //   uPP_R2_Bayes->Draw();
// //   
// //   // draw the MC
// //   mPP_R2->Scale(ScaleFactor[0]);
// // //  mPP_R2->SetLineStyle(2);
// //   mPP_R2->SetLineColor(kBlack);
// //   mPP_R2->Draw("same Lhist");
// //   
// //   for(int i = 0; i<nbins_cent; ++i){
// //     uPbPb_R2_Bayes[i]->Scale(ScaleFactor[i+1]);
// //     uPbPb_R2_Bayes[i]->SetMarkerStyle(20);
// //     uPbPb_R2_Bayes[i]->SetMarkerColor(kRed);
// //     uPbPb_R2_Bayes[i]->Draw("same");
// // 
// // //     mPbPb_R2[i]->Scale(ScaleFactor[i+1]);
// // //     mPbPb_R2[i]->SetLineStyle(2);
// // //     mPbPb_R2[i]->SetLineColor(kRed);
// // //     mPbPb_R2[i]->Draw("same C");
// //     
// //   }
// //   TLegend * leg12 = myLegend(0.15,0.1,0.25,0.2);
// //   leg12->AddEntry(uPP_R2_Bayes,"pp Data","pl");
// //   leg12->AddEntry(mPP_R2,"PYTHIA","pl");
// //   leg12->SetTextSize(0.02);
// //   leg12->Draw();
// // 
// // 
// //   TLegend * leg22 = myLegend(0.75,0.8,0.85,0.9);
// //   leg22->AddEntry(uPbPb_R2_Bayes[0],"PbPb Data","pl");
// // //  leg22->AddEntry(mPbPb_R2[0],"PYTHIA+HYDJET","pl");
// //   leg22->SetTextSize(0.02);
// //   leg22->Draw();
// //   
// //   
// //   drawText("R=0.2, anti k_{T} PF Jets, Bayesian unfolded", 0.15,0.2,16);
// //   drawText("R=0.2, anti k_{T} Pu PF Jets, Bayesian unfolded", 0.75,0.78,16);
// //   putCMSPrel();
// //   putPbPbLumi();
// //   putPPLumi();
// //   
// //   //drawText("pp", 0.7,0.15,16);
// //   drawText("0-5% x 10^{2}", 0.8,0.20,16);
// //   drawText("5-10% x 10^{4}", 0.8,0.28,16);
// //   drawText("10-30% x 10^{6}", 0.8,0.38,16);
// //   drawText("30-50% x 10^{8}", 0.8,0.47,16);
// //   drawText("50-70% x 10^{10}", 0.8,0.54,16);
// //   drawText("70-90% x 10^{12}", 0.8,0.63,16);
// //   cSpectra->SaveAs(Form("Plots/Final_paper_plots_spectra_R2_%d.pdf",date.GetDate()),"RECREATE");

// //   TCanvas * cSpectra3 = new TCanvas("cSpectra3","",1200,1000);
// //   //cSpectra->cd(2);
// //   cSpectra3->SetLogy();
// //   cSpectra3->SetGridy();
// //   cSpectra3->SetLogx();
// // 
// //   uPP_R3_Bayes->Scale(ScaleFactor[0]);
// //   uPP_R3_Bayes->SetMarkerStyle(20);
// //   uPP_R3_Bayes->SetMarkerColor(kBlack);
// //   makeHistTitle(uPP_R3_Bayes," "," Jet p_{T} (GeV/c)","#frac{d #sigma}{T_{AA} dp_{T} d#eta} nb");
// //   uPP_R3_Bayes->SetAxisRange(unfoldingCut, 299, "X");
// //   uPP_R3_Bayes->SetAxisRange(1e-4, 1e15, "Y");
// //   uPP_R3_Bayes->Draw();
// // 
// //   // draw the MC
// //   mPP_R3->Scale(ScaleFactor[0]);
// //   //mPP_R3->SetLineStyle(2);
// //   mPP_R3->SetLineColor(kBlack);
// //   mPP_R3->SetAxisRange(unfoldingCut, 299, "X");
// //   mPP_R3->Draw("same Lhist");
// //   
// //   for(int i = 0; i<nbins_cent; ++i){
// //     uPbPb_R3_Bayes[i]->Scale(ScaleFactor[i+1]);
// //     uPbPb_R3_Bayes[i]->SetMarkerStyle(25);
// //     uPbPb_R3_Bayes[i]->SetMarkerColor(kBlack);
// //     uPbPb_R3_Bayes[i]->SetAxisRange(unfoldingCut, 299, "X");
// //     uPbPb_R3_Bayes[i]->Draw("same");
// // 
// // //     mPbPb_R3[i]->Scale(ScaleFactor[i+2]);
// // //     //mPbPb_R3[i]->SetLineStyle(2);
// // //     mPbPb_R3[i]->SetLineColor(kBlack);
// // //     mPbPb_R3[i]->SetAxisRange(unfoldingCut, 299, "X");
// // //     mPbPb_R3[i]->Draw("same Lhist");
// //   }
// // 
// //   TLegend * leg1 = myLegend(0.15,0.1,0.25,0.2);
// //   leg1->AddEntry(uPP_R3_Bayes,"pp Data","pl");
// //   leg1->AddEntry(mPP_R3,"PYTHIA","pl");
// //   leg1->SetTextSize(0.02);
// //   leg1->Draw();
// // 
// // 
// //   TLegend * leg2 = myLegend(0.75,0.8,0.85,0.9);
// //   leg2->AddEntry(uPbPb_R3_Bayes[0],"PbPb Data","pl");
// // //  leg2->AddEntry(mPbPb_R3[0],"PYTHIA+HYDJET","pl");
// //   leg2->SetTextSize(0.02);
// //   leg2->Draw();
// //   
// //   
// //   drawText("R=0.3, anti k_{T} PF Jets, Bayesian unfolded", 0.15,0.2,16);
// //   drawText("R=0.3, anti k_{T} Pu PF Jets, Bayesian unfolded", 0.75,0.78,16);
// //   putCMSPrel();
// //   putPbPbLumi();
// //   putPPLumi();
// //   
// //   //drawText("pp", 0.7,0.15,16);
// //   drawText("0-5% x 10^{2}", 0.8,0.20,16);
// //   drawText("5-10% x 10^{4}", 0.8,0.28,16);
// //   drawText("10-30% x 10^{6}", 0.8,0.38,16);
// //   drawText("30-50% x 10^{8}", 0.8,0.47,16);
// //   drawText("50-70% x 10^{10}", 0.8,0.54,16);
// //   drawText("70-90% x 10^{12}", 0.8,0.63,16);
// //   cSpectra3->SaveAs(Form("Plots/Final_paper_plots_spectra_R3_%d.pdf",date.GetDate()),"RECREATE");
// //   
// //   TCanvas * cSpectra4 = new TCanvas("cSpectra4","",1200,1000);
// //   cSpectra4->SetLogy();
// //   cSpectra4->SetLogx();
// // 
// //   uPP_R4_Bayes->Scale(ScaleFactor[0]);
// //   uPP_R4_Bayes->SetMarkerStyle(20);
// //   uPP_R4_Bayes->SetMarkerColor(kBlack);
// //   makeHistTitle(uPP_R4_Bayes," "," Jet p_{T} (GeV/c)","cross section");
// //   uPP_R4_Bayes->SetAxisRange(unfoldingCut, 299, "X");
// //   uPP_R4_Bayes->SetAxisRange(1e-4, 1e15, "Y");
// //   uPP_R4_Bayes->Draw();
// // 
// //   // draw the MC
// //   mPP_R4->Scale(ScaleFactor[0]);
// // //  mPP_R4->SetLineStyle(2);
// //   mPP_R4->SetLineColor(kBlack);
// //   mPP_R4->Draw("same Lhist");
// //   
// //   uPP_R4_Bayes->Draw();
// //   for(int i = 0; i<nbins_cent; ++i){
// //     uPbPb_R4_Bayes[i]->Scale(ScaleFactor[i+1]);
// //     uPbPb_R4_Bayes[i]->SetMarkerStyle(20);
// //     uPbPb_R4_Bayes[i]->SetMarkerColor(kBlue);
// //     uPbPb_R4_Bayes[i]->Draw("same");
// //     
// // //     mPbPb_R4[i]->Scale(ScaleFactor[i]);
// // //     mPbPb_R4[i]->SetLineStyle(2);
// // //     mPbPb_R4[i]->SetLineColor(kBlue);
// // //     mPbPb_R4[i]->Draw("same C");
// //   }
// //   TLegend * leg14 = myLegend(0.15,0.1,0.25,0.2);
// //   leg14->AddEntry(uPP_R4_Bayes,"pp Data","pl");
// //   leg14->AddEntry(mPP_R4,"PYTHIA","pl");
// //   leg14->SetTextSize(0.02);
// //   leg14->Draw();
// // 
// // 
// //   TLegend * leg24 = myLegend(0.75,0.8,0.85,0.9);
// //   leg24->AddEntry(uPbPb_R4_Bayes[0],"PbPb Data","pl");
// // //  leg24->AddEntry(mPbPb_R4[0],"PYTHIA+HYDJET","pl");
// //   leg24->SetTextSize(0.02);
// //   leg24->Draw();
// //   
// //   
// //   drawText("R=0.4, anti k_{T} PF Jets, Bayesian unfolded", 0.15,0.2,16);
// //   drawText("R=0.4, anti k_{T} Pu PF Jets, Bayesian unfolded", 0.75,0.78,16);
// //     
// // 
// //   putCMSPrel();
// //   putPbPbLumi();
// //   putPPLumi();
// //   
// //   //drawText("pp", 0.7,0.15,16);
// //   drawText("0-5% x 10^{2}", 0.8,0.20,16);
// //   drawText("5-10% x 10^{4}", 0.8,0.28,16);
// //   drawText("10-30% x 10^{6}", 0.8,0.38,16);
// //   drawText("30-50% x 10^{8}", 0.8,0.47,16);
// //   drawText("50-70% x 10^{10}", 0.8,0.54,16);
// //   drawText("70-90% x 10^{12}", 0.8,0.63,16);
// // 
// // 
// //   cSpectra4->SaveAs(Form("Plots/Final_paper_plots_spectra_R4_%d.pdf",date.GetDate()),"RECREATE");
// // 
// // 
// //   
// //   
// //   // plot 2 - Bayesian unfolded RAA as a function of pT for the different radii
// //   //        - regular 6 panel plot 
// //   
// //   // again this will be a 6 panel plot. showing measured, unfolded Bayesian, and unfolded Bin By Bin methods. 
// //   TCanvas *cRAA = new TCanvas("cRAA","RAA",1200,800);
// //   makeMultiPanelCanvasWithGap(cRAA,3,2,0.01,0.01,0.16,0.2,0.04,0.04);
// // 
// //   TLegend *tRAA = myLegend(0.45,0.75,0.85,0.9);
// //   TLine *lineRAA = new TLine(unfoldingCut,1,299,1);
// //   lineRAA->SetLineStyle(2);
// //   lineRAA->SetLineWidth(2);
// // 
// //   TLine *lUnfoldingCut = new TLine(unfoldingCut+30,0,unfoldingCut+30,2);
// //   lUnfoldingCut->SetLineStyle(4);
// //   lUnfoldingCut->SetLineWidth(2);
// //     
// //   for(int i = 0;i<nbins_cent;++i){
// // 
// //     cRAA->cd(nbins_cent-i);
// // 
// //     RAA_R2_Bayes[i]->SetMarkerColor(kRed);
// //     RAA_R2_Bayes[i]->SetMarkerStyle(20);
// //     makeHistTitle(RAA_R2_Bayes[i],"","Jet p_{T} (GeV/c)","R_{AA}");
// //     RAA_R2_Bayes[i]->SetAxisRange(unfoldingCut,299,"X");
// //     RAA_R2_Bayes[i]->SetAxisRange(0,2,"Y");
// //     RAA_R2_Bayes[i]->Draw("E1");
// // 
// //     RAA_R3_Bayes[i]->SetMarkerColor(kBlack);
// //     RAA_R3_Bayes[i]->SetMarkerStyle(20);
// //     RAA_R3_Bayes[i]->Draw("same E1");
// // 
// //     RAA_R4_Bayes[i]->SetMarkerStyle(20);
// //     RAA_R4_Bayes[i]->SetMarkerColor(kBlue);
// //     RAA_R4_Bayes[i]->Draw("same E1");
// // 
// //     lineRAA->Draw();
// //     //lUnfoldingCut->Draw();
// //     drawText(Form("%2.0f-%2.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]),0.8,0.9,20);
// // 
// //   }
// //     
// //   tRAA->AddEntry(RAA_R2_Bayes[0],"R=0.2","pl");
// //   tRAA->AddEntry(RAA_R3_Bayes[0],"R=0.3","pl");
// //   tRAA->AddEntry(RAA_R4_Bayes[0],"R=0.4","pl");
// //   tRAA->SetTextSize(0.04);
// // 
// //   cRAA->cd(1);
// //   tRAA->Draw();
// //   cRAA->cd(1);
// //   putCMSPrel();
// //   putPbPbLumi();
// //   putPPLumi();
// //   drawText(Form("Anti-k_{T} %s %s Jets",algo,jet_type),0.2,0.23,16);
// //   //drawText("|#eta|<2, |vz|<15",0.65,0.31,16);
// //   cRAA->cd(2);
// //   drawText("Jet ID cut, |#eta|<2",0.1,0.3,16);
// //   drawText("|vz|<15, HBHEfilter, pCES",0.1,0.2,16);
// //   cRAA->cd(3);
// //   drawText("Jet RAA dataset, trigger combined",0.1,0.3,16);
// //   drawText("Pile up rejection cut applied",0.1,0.2,16);
// // 
// //   cRAA->SaveAs(Form("Plots/Final_paper_plots_RAA_%d.pdf",date.GetDate()),"RECREATE");
// //     
// //   
// // 
// //   
// //   
// //   // plot 3 - RAA as a function of npart - taken from http://dde.web.cern.ch/dde/glauber_lhc.htm for 84 < pT < 97 in PbPb,PP
// //   //        - need to decide if we have to unfold this? or if we can just take that respective pt ranges from the already existing RAA histograms.  this is bin number 16 from the centrality classes weve measured.
// // 
// //   // get the responsible histograms for this.
// //   TH1F * hRAA_R2_npart = new TH1F("hRAA_R2_npart","",45, 0, 450);
// //   //hRAA_R2_npart->LabelsOption(">","X");
// //   TH1F * hRAA_R3_npart = new TH1F("hRAA_R3_npart","",45, 0, 450);
// //   //hRAA_R3_npart->LabelsOption(">","X");
// //   TH1F * hRAA_R4_npart = new TH1F("hRAA_R4_npart","",45, 0, 450);
// //   //hRAA_R4_npart->LabelsOption(">","X");
// // 
// //   for(int i = 0; i<nbins_cent; ++i){
// //     hRAA_R2_npart->SetBinContent(hRAA_R2_npart->FindBin(npart[i]), RAA_R2_Bayes[i]->GetBinContent(RAA_R2_Bayes[i]->FindBin(100)));
// //     hRAA_R2_npart->SetBinError(hRAA_R2_npart->FindBin(npart[i]), RAA_R2_Bayes[i]->GetBinError(RAA_R2_Bayes[i]->FindBin(100)));
// //     hRAA_R3_npart->SetBinContent(hRAA_R3_npart->FindBin(npart[i]), RAA_R3_Bayes[i]->GetBinContent(RAA_R3_Bayes[i]->FindBin(100)));
// //     hRAA_R3_npart->SetBinError(hRAA_R3_npart->FindBin(npart[i]), RAA_R3_Bayes[i]->GetBinError(RAA_R3_Bayes[i]->FindBin(100)));
// //     hRAA_R4_npart->SetBinContent(hRAA_R4_npart->FindBin(npart[i]), RAA_R4_Bayes[i]->GetBinContent(RAA_R4_Bayes[i]->FindBin(100)));    
// //     hRAA_R4_npart->SetBinError(hRAA_R4_npart->FindBin(npart[i]), RAA_R4_Bayes[i]->GetBinError(RAA_R4_Bayes[i]->FindBin(100)));    
// //   }
// // 
// //   TCanvas * cRAA_npart = new TCanvas("cRAA_npart","",600,400);
// //   cRAA_npart->SetGridy();
// //   cRAA_npart->SetGridx();
// // 
// //   hRAA_R2_npart->SetTitle(" ");
// //   hRAA_R2_npart->SetXTitle(" N_{part} ");
// //   hRAA_R2_npart->SetYTitle(" R_{AA} ");
// //   hRAA_R2_npart->SetMarkerColor(kRed);
// //   hRAA_R2_npart->SetLineColor(kRed);
// //   hRAA_R2_npart->SetMarkerStyle(20);
// //   hRAA_R2_npart->SetAxisRange(0.3,0.9, "Y");
// //   hRAA_R2_npart->Draw("E1");
// //   hRAA_R3_npart->SetMarkerColor(kBlack);
// //   hRAA_R3_npart->SetLineColor(kBlack);
// //   hRAA_R3_npart->SetMarkerStyle(20);
// //   hRAA_R3_npart->Draw("same E1");
// //   hRAA_R4_npart->SetMarkerColor(kBlue);
// //   hRAA_R4_npart->SetLineColor(kBlue);
// //   hRAA_R4_npart->SetMarkerStyle(20);
// //   hRAA_R4_npart->Draw("same E1");
// // 
// //   drawText(Form("Anti-k_{T} %s %s Jets",algo,jet_type),0.6,0.2,16);
// //   drawText("Jet ID cut, |#eta|<2",0.15,0.3,16);
// //   drawText("|vz|<15, HBHEfilter, pCES",0.15,0.2,16);
// //   drawText("97 < Jet p_{T} < 114", 0.15,0.8,16);
// //   
// //   TLegend * npart = myLegend(0.7,0.7,0.9,0.9);
// //   npart->AddEntry(hRAA_R2_npart,"R=0.2", "pl");
// //   npart->AddEntry(hRAA_R3_npart,"R=0.3", "pl");
// //   npart->AddEntry(hRAA_R4_npart,"R=0.4", "pl");
// //   npart->SetTextSize(0.04);
// //   npart->Draw();
// // 
// //   putCMSPrel();
// //   putPbPbLumi();
// //   putPPLumi();
// //   
// //   cRAA_npart->SaveAs(Form("Plots/Final_paper_plots_RAA_npart_%d.pdf",date.GetDate()),"RECREATE");
// //   
  

}
