#define TimeSliceEventCount_cxx
#include "TimeSliceEventCount.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void TimeSliceEventCount::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L TimeSliceEventCount.C
//      Root > TimeSliceEventCount t
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
 TFile *OutFile=new TFile("ZDCDigiOut_TS_eventCount_Run262081_lumi50_VdM.root","RECREATE");
  TH1F* histogram_1D_PosHAD1 = new TH1F("PHAD1signal_TS_eventCount", "PHAD1signal_TS_eventCount", 10, 0, 10); 
  TH1F* histogram_1D_PosHAD2 = new TH1F("PHAD2signal_TS_eventCount", "PHAD2signal_TS_eventCount", 10, 0, 10); 
  TH1F* histogram_1D_PosHAD3 = new TH1F("PHAD3signal_TS_eventCount", "PHAD3signal_TS_eventCount", 10, 0, 10); 
  TH1F* histogram_1D_PosHAD4 = new TH1F("PHAD4signal_TS_eventCount", "PHAD4signal_TS_eventCount", 10, 0, 10); 
  TH1F* histogram_1D_NegHAD1 = new TH1F("NHAD1signal_TS_eventCount", "NHAD1signal_TS_eventCount", 10, 0, 10); 
  TH1F* histogram_1D_NegHAD2 = new TH1F("NHAD2signal_TS_eventCount", "NHAD2signal_TS_eventCount", 10, 0, 10); 
  TH1F* histogram_1D_NegHAD3 = new TH1F("NHAD3signal_TS_eventCount", "NHAD3signal_TS_eventCount", 10, 0, 10); 
  TH1F* histogram_1D_NegHAD4 = new TH1F("NHAD4signal_TS_eventCount", "NHAD4signal_TS_eventCount", 10, 0, 10); 

  TH1F* histogram_1D_PosEM1 = new TH1F("PEM1signal_TS_eventCount", "PEM1signal_TS_eventCount", 10, 0, 10); 
  TH1F* histogram_1D_PosEM2 = new TH1F("PEM2signal_TS_eventCount", "PEM2signal_TS_eventCount", 10, 0, 10); 
  TH1F* histogram_1D_PosEM3 = new TH1F("PEM3signal_TS_eventCount", "PEM3signal_TS_eventCount", 10, 0, 10); 
  TH1F* histogram_1D_PosEM4 = new TH1F("PEM4signal_TS_eventCount", "PEM4signal_TS_eventCount", 10, 0, 10); 
  TH1F* histogram_1D_PosEM5 = new TH1F("PEM5signal_TS_eventCount", "PEM5signal_TS_eventCount", 10, 0, 10); 
  TH1F* histogram_1D_NegEM1 = new TH1F("NEM1signal_TS_eventCount", "NEM1signal_TS_eventCount", 10, 0, 10); 
  TH1F* histogram_1D_NegEM2 = new TH1F("NEM2signal_TS_eventCount", "NEM2signal_TS_eventCount", 10, 0, 10); 
  TH1F* histogram_1D_NegEM3 = new TH1F("NEM3signal_TS_eventCount", "NEM3signal_TS_eventCount", 10, 0, 10); 
  TH1F* histogram_1D_NegEM4 = new TH1F("NEM4signal_TS_eventCount", "NEM4signal_TS_eventCount", 10, 0, 10); 
  TH1F* histogram_1D_NegEM5 = new TH1F("NEM5signal_TS_eventCount", "NEM5signal_TS_eventCount", 10, 0, 10); 


 // TH2F* histogram_2D = new TH2F("TimeSliceEventCount", "negHD4fCvsTS", 10, 0, 10, 200, 100, 30000);
  if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;


   for(int iTS=0;iTS<10;iTS++){
      if(posHD1fC[iTS]<0) 
      {
	   posHD1fC[iTS]=0;
      }
      if(posHD1fC[iTS]>0 )
      {
        histogram_1D_PosHAD1->Fill(iTS); 
      }
      if(posHD2fC[iTS]<0) 
      {
	   posHD2fC[iTS]=0;
      }
      if(posHD2fC[iTS]>0 )
      {
        histogram_1D_PosHAD2->Fill(iTS); 
      }
      if(posHD3fC[iTS]<0) 
      {
	   posHD3fC[iTS]=0;
      }
      if(posHD3fC[iTS]>0 )
      {
        histogram_1D_PosHAD3->Fill(iTS); 
      }
      if(posHD4fC[iTS]<0) 
      {
	   posHD4fC[iTS]=0;
      }
      if(posHD4fC[iTS]>0 )
      {
        histogram_1D_PosHAD4->Fill(iTS); 
      }   
      if(negHD1fC[iTS]<0) 
      {
	   negHD1fC[iTS]=0;
      }
      if(negHD1fC[iTS]>0 )
      {
        histogram_1D_NegHAD1->Fill(iTS); 
      }
      if(negHD2fC[iTS]<0) 
      {
	   negHD2fC[iTS]=0;
      }
      if(negHD2fC[iTS]>0 )
      {
        histogram_1D_NegHAD2->Fill(iTS); 
      }
      if(negHD3fC[iTS]<0) 
      {
	   negHD3fC[iTS]=0;
      }
      if(negHD3fC[iTS]>0 )
      {
        histogram_1D_NegHAD3->Fill(iTS); 
      }
      if(negHD4fC[iTS]<0) 
      {
	   negHD4fC[iTS]=0;
      }
      if(negHD4fC[iTS]>0 )
      {
        histogram_1D_NegHAD4->Fill(iTS); 
      } 
// EM
      if(posEM1fC[iTS]<0) 
      {
	   posEM1fC[iTS]=0;
      }
      if(posEM1fC[iTS]>0 )
      {
        histogram_1D_PosEM1->Fill(iTS); 
      }
      if(posEM2fC[iTS]<0) 
      {
	   posEM2fC[iTS]=0;
      }
      if(posEM2fC[iTS]>0 )
      {
        histogram_1D_PosEM2->Fill(iTS); 
      }
      if(posEM3fC[iTS]<0) 
      {
	   posEM3fC[iTS]=0;
      }
      if(posEM3fC[iTS]>0 )
      {
        histogram_1D_PosEM3->Fill(iTS); 
      }
      if(posEM4fC[iTS]<0) 
      {
	   posEM4fC[iTS]=0;
      }
      if(posEM4fC[iTS]>0 )
      {
        histogram_1D_PosEM4->Fill(iTS); 
      }   
      if(posEM5fC[iTS]<0) 
      {
	   posEM5fC[iTS]=0;
      }
      if(posEM5fC[iTS]>0 )
      {
        histogram_1D_PosEM5->Fill(iTS); 
      }         
      if(negEM1fC[iTS]<0) 
      {
	   negEM1fC[iTS]=0;
      }
      if(negEM1fC[iTS]>0 )
      {
        histogram_1D_NegEM1->Fill(iTS); 
      }
      if(negEM2fC[iTS]<0) 
      {
	   negEM2fC[iTS]=0;
      }
      if(negEM2fC[iTS]>0 )
      {
        histogram_1D_NegEM2->Fill(iTS); 
      }
      if(negEM3fC[iTS]<0) 
      {
	   negEM3fC[iTS]=0;
      }
      if(negEM3fC[iTS]>0 )
      {
        histogram_1D_NegEM3->Fill(iTS); 
      }
      if(negEM4fC[iTS]<0) 
      {
	   negEM4fC[iTS]=0;
      }
      if(negEM4fC[iTS]>0 )
      {
        histogram_1D_NegEM4->Fill(iTS); 
      } 
      if(negEM5fC[iTS]<0) 
      {
	   negEM5fC[iTS]=0;
      }
      if(negEM5fC[iTS]>0 )
      {
        histogram_1D_NegEM5->Fill(iTS); 
      }                                  
   }
// && negHD4ADC[iTS]>126
   
   }
  // histogram_2D->Draw("COLZ");
  c1 = new TCanvas();
 histogram_1D_PosHAD1->Draw();
 c1->Print("Plots/PosHAD1signal_TS_eventCount_Run262081_lumi50_VdM.pdf");
 histogram_1D_PosHAD2->Draw();
 c1->Print("Plots/PosHAD2signal_TS_eventCount_Run262081_lumi50_VdM.pdf");
 histogram_1D_PosHAD3->Draw();
 c1->Print("Plots/PosHAD3signal_TS_eventCount_Run262081_lumi50_VdM.pdf");
 histogram_1D_PosHAD4->Draw();
 c1->Print("Plots/PosHAD4signal_TS_eventCount_Run262081_lumi50_VdM.pdf");   
 histogram_1D_NegHAD1->Draw();
 c1->Print("Plots/NegHAD1signal_TS_eventCount_Run262081_lumi50_VdM.pdf");
 histogram_1D_NegHAD2->Draw();
 c1->Print("Plots/NegHAD2signal_TS_eventCount_Run262081_lumi50_VdM.pdf");
 histogram_1D_NegHAD3->Draw();
 c1->Print("Plots/NegHAD3signal_TS_eventCount_Run262081_lumi50_VdM.pdf");
 histogram_1D_NegHAD4->Draw();
 c1->Print("Plots/NegHAD4signal_TS_eventCount_Run262081_lumi50_VdM.pdf");   
 histogram_1D_PosEM1->Draw();
 c1->Print("Plots/PosEM1signal_TS_eventCount_Run262081_lumi50_VdM.pdf");
 histogram_1D_PosEM2->Draw();
 c1->Print("Plots/PosEM2signal_TS_eventCount_Run262081_lumi50_VdM.pdf");
 histogram_1D_PosEM3->Draw();
 c1->Print("Plots/PosEM3signal_TS_eventCount_Run262081_lumi50_VdM.pdf");
 histogram_1D_PosEM4->Draw();
 c1->Print("Plots/PosEM4signal_TS_eventCount_Run262081_lumi50_VdM.pdf");   
 histogram_1D_PosEM5->Draw();
 c1->Print("Plots/PosEM5signal_TS_eventCount_Run262081_lumi50_VdM.pdf");  
 histogram_1D_NegEM1->Draw();
 c1->Print("Plots/NegEM1signal_TS_eventCount_Run262081_lumi50_VdM.pdf");
 histogram_1D_NegEM2->Draw();
 c1->Print("Plots/NegEM2signal_TS_eventCount_Run262081_lumi50_VdM.pdf");
 histogram_1D_NegEM3->Draw();
 c1->Print("Plots/NegEM3signal_TS_eventCount_Run262081_lumi50_VdM.pdf");
 histogram_1D_NegEM4->Draw();
 c1->Print("Plots/NegEM4signal_TS_eventCount_Run262081_lumi50_VdM.pdf"); 
 histogram_1D_NegEM5->Draw();
 c1->Print("Plots/NegEM5signal_TS_eventCount_Run262081_lumi50_VdM.pdf");   
}
