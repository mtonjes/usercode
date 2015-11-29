#define TimeSlice_fCWeight_cxx
#include "TimeSlice_fCWeight.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <cstring>
void drawText(const char *text, float xp, float yp, int size){
  TLatex *tex = new TLatex(xp,yp,text);
  tex->SetTextFont(63);
  tex->SetTextSize(size);
  tex->SetTextColor(kBlack);
  tex->SetLineWidth(1);
  //tex->SetTextFont(42);
  tex->SetNDC();
  tex->Draw();
}

void TimeSlice_fCWeight::Loop()
{
// CHANGE THAT VARIABLE IdentifyString
// String to identify file: this will be used in pdf file naming and output plot file naming
string IdentifyString="ForwardAnalyzerRun262811_MinBiasHF1AndExpress";
string InRun="262811";
//   In a ROOT session, you can do:
//      Root > .L TimeSlice_fCWeight.C
//      Root > TimeSlice_fCWeight t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

 TChain *chain=new TChain("ZDCDigiTree","");
 TFile *OutFile=new TFile(Form("ForwardAnalyzerPlots_%s.root",IdentifyString.c_str()),"RECREATE");
  TH1F* histogram_1D_PosHAD1 = new TH1F("PHAD1signal_TS_fC", "PHAD1signal_fC_TS", 10, 0, 10); 
  TH1F* histogram_1D_PosHAD2 = new TH1F("PHAD2signal_TS_fC", "PHAD2signal_fC_TS", 10, 0, 10); 
  TH1F* histogram_1D_PosHAD3 = new TH1F("PHAD3signal_TS_fC", "PHAD3signal_fC_TS", 10, 0, 10); 
  TH1F* histogram_1D_PosHAD4 = new TH1F("PHAD4signal_TS_fC", "PHAD4signal_fC_TS", 10, 0, 10); 
  TH1F* histogram_1D_NegHAD1 = new TH1F("NHAD1signal_TS_fC", "NHAD1signal_fC_TS", 10, 0, 10); 
  TH1F* histogram_1D_NegHAD2 = new TH1F("NHAD2signal_TS_fC", "NHAD2signal_fC_TS", 10, 0, 10); 
  TH1F* histogram_1D_NegHAD3 = new TH1F("NHAD3signal_TS_fC", "NHAD3signal_fC_TS", 10, 0, 10); 
  TH1F* histogram_1D_NegHAD4 = new TH1F("NHAD4signal_TS_fC", "NHAD4signal_fC_TS", 10, 0, 10); 

  TH1F* histogram_1D_PosEM1 = new TH1F("PEM1signal_TS_fC", "PEM1signal_fC_TS", 10, 0, 10); 
  TH1F* histogram_1D_PosEM2 = new TH1F("PEM2signal_TS_fC", "PEM2signal_fC_TS", 10, 0, 10); 
  TH1F* histogram_1D_PosEM3 = new TH1F("PEM3signal_TS_fC", "PEM3signal_fC_TS", 10, 0, 10); 
  TH1F* histogram_1D_PosEM4 = new TH1F("PEM4signal_TS_fC", "PEM4signal_fC_TS", 10, 0, 10); 
  TH1F* histogram_1D_PosEM5 = new TH1F("PEM5signal_TS_fC", "PEM5signal_fC_TS", 10, 0, 10); 
  TH1F* histogram_1D_NegEM1 = new TH1F("NEM1signal_TS_fC", "NEM1signal_fC_TS", 10, 0, 10); 
  TH1F* histogram_1D_NegEM2 = new TH1F("NEM2signal_TS_fC", "NEM2signal_fC_TS", 10, 0, 10); 
  TH1F* histogram_1D_NegEM3 = new TH1F("NEM3signal_TS_fC", "NEM3signal_fC_TS", 10, 0, 10); 
  TH1F* histogram_1D_NegEM4 = new TH1F("NEM4signal_TS_fC", "NEM4signal_fC_TS", 10, 0, 10); 
  TH1F* histogram_1D_NegEM5 = new TH1F("NEM5signal_TS_fC", "NEM5signal_fC_TS", 10, 0, 10); 


 // TH2F* histogram_2D = new TH2F("TimeSlice_fCWeight", "negHD4fCvsTS", 10, 0, 10, 200, 100, 30000);
  if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;


   for(int iTS=0;iTS<10;iTS++){
//      if(posHD1fC[iTS]<0) 
//      {
//	   posHD1fC[iTS]=0;
//      }
 //     if(posHD1fC[iTS]>0 )
 //     {
        histogram_1D_PosHAD1->Fill(iTS,posHD1fC[iTS]); 
//      }
//      if(posHD2fC[iTS]<0) 
//      {
//	   posHD2fC[iTS]=0;
//      }
//      if(posHD2fC[iTS]>0 )
 //     {
        histogram_1D_PosHAD2->Fill(iTS,posHD2fC[iTS]); 
 //     }
//      if(posHD3fC[iTS]<0) 
//      {
//	   posHD3fC[iTS]=0;
//      }
//      if(posHD3fC[iTS]>0 )
//      {
        histogram_1D_PosHAD3->Fill(iTS,posHD3fC[iTS]); 
//      }
//      if(posHD4fC[iTS]<0) 
 //     {
//	   posHD4fC[iTS]=0;
//      }
//      if(posHD4fC[iTS]>0 )
//      {
        histogram_1D_PosHAD4->Fill(iTS,posHD4fC[iTS]); 
//      }   
//      if(negHD1fC[iTS]<0) 
//      {
//	   negHD1fC[iTS]=0;
//      }
//      if(negHD1fC[iTS]>0 )
//      {
        histogram_1D_NegHAD1->Fill(iTS,negHD1fC[iTS]); 
//      }
//      if(negHD2fC[iTS]<0) 
//      {
//	   negHD2fC[iTS]=0;
//      }
//      if(negHD2fC[iTS]>0 )
//      {
        histogram_1D_NegHAD2->Fill(iTS,negHD2fC[iTS]); 
//      }
//      if(negHD3fC[iTS]<0) 
//      {
//	   negHD3fC[iTS]=0;
//      }
//      if(negHD3fC[iTS]>0 )
//      {
        histogram_1D_NegHAD3->Fill(iTS,negHD3fC[iTS]); 
//      }
//      if(negHD4fC[iTS]<0) 
//      {
//	   negHD4fC[iTS]=0;
//      }
//      if(negHD4fC[iTS]>0 )
//      {
        histogram_1D_NegHAD4->Fill(iTS,negHD4fC[iTS]); 
//      } 
// EM
//      if(posEM1fC[iTS]<0) 
//      {
//	   posEM1fC[iTS]=0;
//      }
//      if(posEM1fC[iTS]>0 )
//      {
        histogram_1D_PosEM1->Fill(iTS,posEM1fC[iTS]); 
//      }
//      if(posEM2fC[iTS]<0) 
//      {
//	   posEM2fC[iTS]=0;
//      }
//      if(posEM2fC[iTS]>0 )
//      {
        histogram_1D_PosEM2->Fill(iTS,posEM2fC[iTS]); 
//      }
//      if(posEM3fC[iTS]<0) 
//      {
//	   posEM3fC[iTS]=0;
//      }
//      if(posEM3fC[iTS]>0 )
//      {
        histogram_1D_PosEM3->Fill(iTS,posEM3fC[iTS]); 
//      }
//      if(posEM4fC[iTS]<0) 
//      {
//	   posEM4fC[iTS]=0;
//      }
//      if(posEM4fC[iTS]>0 )
//      {
        histogram_1D_PosEM4->Fill(iTS,posEM4fC[iTS]); 
//      }   
//      if(posEM5fC[iTS]<0) 
//      {
//	   posEM5fC[iTS]=0;
//      }
//      if(posEM5fC[iTS]>0 )
//      {
        histogram_1D_PosEM5->Fill(iTS,posEM5fC[iTS]); 
//      }         
//      if(negEM1fC[iTS]<0) 
//      {
//	   negEM1fC[iTS]=0;
//      }
//      if(negEM1fC[iTS]>0 )
//      {
        histogram_1D_NegEM1->Fill(iTS,negEM1fC[iTS]); 
//      }
//      if(negEM2fC[iTS]<0) 
//      {
//	   negEM2fC[iTS]=0;
//      }
//      if(negEM2fC[iTS]>0 )
//      {
        histogram_1D_NegEM2->Fill(iTS,negEM2fC[iTS]); 
//      }
//      if(negEM3fC[iTS]<0) 
//      {
//	   negEM3fC[iTS]=0;
//      }
//      if(negEM3fC[iTS]>0 )
//      {
        histogram_1D_NegEM3->Fill(iTS,negEM3fC[iTS]); 
//      }
//      if(negEM4fC[iTS]<0) 
//      {
//	   negEM4fC[iTS]=0;
//      }
//      if(negEM4fC[iTS]>0 )
//      {
        histogram_1D_NegEM4->Fill(iTS,negEM4fC[iTS]); 
//      } 
//      if(negEM5fC[iTS]<0) 
//      {
//	   negEM5fC[iTS]=0;
//      }
//      if(negEM5fC[iTS]>0 )
//      {
        histogram_1D_NegEM5->Fill(iTS,negEM5fC[iTS]); 
//      }                                  
   }
// && negHD4ADC[iTS]>126
   
   }
  // histogram_2D->Draw("COLZ");
histogram_1D_PosHAD1->Write();
histogram_1D_PosHAD2->Write();
histogram_1D_PosHAD3->Write();
histogram_1D_PosHAD4->Write();
histogram_1D_NegHAD1->Write();
histogram_1D_NegHAD2->Write();
histogram_1D_NegHAD3->Write();
histogram_1D_NegHAD4->Write();
histogram_1D_PosEM1->Write();
histogram_1D_PosEM2->Write();
histogram_1D_PosEM3->Write();
histogram_1D_PosEM4->Write();
histogram_1D_PosEM5->Write();
histogram_1D_NegEM1->Write();
histogram_1D_NegEM2->Write();
histogram_1D_NegEM3->Write();
histogram_1D_NegEM4->Write();
histogram_1D_NegEM5->Write();
     
  c1 = new TCanvas();
 histogram_1D_PosHAD1->Draw();
 drawText(Form("Run: %s",InRun.c_str()), 0.6, 0.8, 18); 
 c1->Print(Form("Plots/PosHAD1signal_TS_fCWeight_%s.pdf",IdentifyString.c_str()));
 histogram_1D_PosHAD2->Draw();
  drawText(Form("Run: %s",InRun.c_str()), 0.6, 0.8, 18); 
 c1->Print(Form("Plots/PosHAD2signal_TS_fCWeight_%s.pdf",IdentifyString.c_str()));
 histogram_1D_PosHAD3->Draw();
  drawText(Form("Run: %s",InRun.c_str()), 0.6, 0.8, 18); 
 c1->Print(Form("Plots/PosHAD3signal_TS_fCWeight_%s.pdf",IdentifyString.c_str()));
 histogram_1D_PosHAD4->Draw();
 drawText(Form("Run: %s",InRun.c_str()), 0.6, 0.8, 18);
 c1->Print(Form("Plots/PosHAD4signal_TS_fCWeight_%s.pdf",IdentifyString.c_str()));   
 histogram_1D_NegHAD1->Draw();
 drawText(Form("Run: %s",InRun.c_str()), 0.6, 0.8, 18);
 c1->Print(Form("Plots/NegHAD1signal_TS_fCWeight_%s.pdf",IdentifyString.c_str()));
 histogram_1D_NegHAD2->Draw();
 drawText(Form("Run: %s",InRun.c_str()), 0.6, 0.8, 18);
 c1->Print(Form("Plots/NegHAD2signal_TS_fCWeight_%s.pdf",IdentifyString.c_str()));
 histogram_1D_NegHAD3->Draw();
 drawText(Form("Run: %s",InRun.c_str()), 0.6, 0.8, 18);
 c1->Print(Form("Plots/NegHAD3signal_TS_fCWeight_%s.pdf",IdentifyString.c_str()));
 histogram_1D_NegHAD4->Draw();
 drawText(Form("Run: %s",InRun.c_str()), 0.6, 0.8, 18);
 c1->Print(Form("Plots/NegHAD4signal_TS_fCWeight_%s.pdf",IdentifyString.c_str()));   
 histogram_1D_PosEM1->Draw();
 drawText(Form("Run: %s",InRun.c_str()), 0.6, 0.8, 18);
 c1->Print(Form("Plots/PosEM1signal_TS_fCWeight_%s.pdf",IdentifyString.c_str()));
 histogram_1D_PosEM2->Draw();
 drawText(Form("Run: %s",InRun.c_str()), 0.6, 0.8, 18);
 c1->Print(Form("Plots/PosEM2signal_TS_fCWeight_%s.pdf",IdentifyString.c_str()));
 histogram_1D_PosEM3->Draw();
 drawText(Form("Run: %s",InRun.c_str()), 0.6, 0.8, 18);
 c1->Print(Form("Plots/PosEM3signal_TS_fCWeight_%s.pdf",IdentifyString.c_str()));
 histogram_1D_PosEM4->Draw();
 drawText(Form("Run: %s",InRun.c_str()), 0.6, 0.8, 18);
 c1->Print(Form("Plots/PosEM4signal_TS_fCWeight_%s.pdf",IdentifyString.c_str()));   
 histogram_1D_PosEM5->Draw();
 drawText(Form("Run: %s",InRun.c_str()), 0.6, 0.8, 18);
 c1->Print(Form("Plots/PosEM5signal_TS_fCWeight_%s.pdf",IdentifyString.c_str()));  
 histogram_1D_NegEM1->Draw();
 drawText(Form("Run: %s",InRun.c_str()), 0.6, 0.8, 18);
 c1->Print(Form("Plots/NegEM1signal_TS_fCWeight_%s.pdf",IdentifyString.c_str()));
 histogram_1D_NegEM2->Draw();
 drawText(Form("Run: %s",InRun.c_str()), 0.6, 0.8, 18);
 c1->Print(Form("Plots/NegEM2signal_TS_fCWeight_%s.pdf",IdentifyString.c_str()));
 histogram_1D_NegEM3->Draw();
 drawText(Form("Run: %s",InRun.c_str()), 0.6, 0.8, 18);
 c1->Print(Form("Plots/NegEM3signal_TS_fCWeight_%s.pdf",IdentifyString.c_str()));
 histogram_1D_NegEM4->Draw();
 drawText(Form("Run: %s",InRun.c_str()), 0.6, 0.8, 18);
 c1->Print(Form("Plots/NegEM4signal_TS_fCWeight_%s.pdf",IdentifyString.c_str())); 
 histogram_1D_NegEM5->Draw();
 drawText(Form("Run: %s",InRun.c_str()), 0.6, 0.8, 18); 
 c1->Print(Form("Plots/NegEM5signal_TS_fCWeight_%s.pdf",IdentifyString.c_str()));   
}
