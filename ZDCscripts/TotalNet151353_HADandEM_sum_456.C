#define TotalNet151353_HADandEM_sum_456_cxx
#include "TotalNet151353_HADandEM_sum_456.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void TotalNet151353_HADandEM_sum_456::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L TotalNet151353_HADandEM_sum_456.C
//      Root > TotalNet151353_HADandEM_sum_456 t
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
  gStyle->SetPalette(1);


    TChain *chain=new TChain("ZDCDigiTree","");

      TH1F* histogram_1 = new TH1F("TotalNetNegEMandHAD", "151353Net(EM+HAD) TS 4 5 6 saturation allowed", 1000, -100, 30000); 
 //    TH1F* histogram_1 = new TH1F("TotalNetNegEMandHAD", "151353Net(1.35*EM+HAD)*0.78283/1.48 TS 4 5 6", 1000, -100, 30000); 
     TH2F* histogram_2D = new TH2F("TotalNetNegEMandHAD2D", "NetEMvsEM+HAD TS 4 5 6",  200, -100, 30000, 200, -100, 2000); 


  if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      float EMsum=0;
      float HADsum=0;
      float EMandHADsum=0;
      float ratioEMtoHAD=0;
 
   float HDTotalSignal=0;
   for(int iTS=4;iTS<7;iTS++){
      if(negHD1fC[iTS]<0){
	negHD1fC[iTS]=0;
      }  
      HDTotalSignal=HDTotalSignal+negHD1fC[iTS];
   }
  float HDTotalNoise=0;
   for(int iTS=0;iTS<3;iTS++){
      HDTotalNoise=HDTotalNoise+negHD1fC[iTS];
   }

   float HDTotalSignal2=0;
   for(int iTS=4;iTS<7;iTS++){
      if(negHD2fC[iTS]<0){
	negHD2fC[iTS]=0;
      }  
      HDTotalSignal2=HDTotalSignal2+negHD2fC[iTS];
   }
  float HDTotalNoise2=0;
   for(int iTS=0;iTS<3;iTS++){
      HDTotalNoise2=HDTotalNoise2+negHD2fC[iTS];
   }

   float HDTotalSignal3=0;
   for(int iTS=4;iTS<7;iTS++){
      if(negHD3fC[iTS]<0){
	negHD3fC[iTS]=0;
      }  
      HDTotalSignal3=HDTotalSignal3+negHD3fC[iTS];
   }
  float HDTotalNoise3=0;
   for(int iTS=0;iTS<3;iTS++){
      HDTotalNoise3=HDTotalNoise3+negHD3fC[iTS];
   }

   float HDTotalSignal4=0;
   for(int iTS=4;iTS<7;iTS++){
      if(negHD4fC[iTS]<0){
	negHD4fC[iTS]=0;
      }  
      HDTotalSignal4=HDTotalSignal4+negHD4fC[iTS];
   }
  float HDTotalNoise4=0;
   for(int iTS=0;iTS<3;iTS++){
      HDTotalNoise4=HDTotalNoise4+negHD4fC[iTS];
      }


   //EM
   float TotalSignal=0;
   for(int iTS=4;iTS<7;iTS++){
      if(negEM1fC[iTS]<0){
	negEM1fC[iTS]=0;
      }  
      
      TotalSignal=TotalSignal+negEM1fC[iTS];
      
   }
 
   float TotalNoise=0;
   for(int iTS=0;iTS<3;iTS++){
      TotalNoise=TotalNoise+negEM1fC[iTS];
   }

   float TotalSignal2=0;
   for(int iTS=4;iTS<7;iTS++){
      if(negEM2fC[iTS]<0){
	negEM2fC[iTS]=0;
      }  
     
      TotalSignal2=TotalSignal2+negEM2fC[iTS];
      
   }
  float TotalNoise2=0;
   for(int iTS=0;iTS<3;iTS++){
      TotalNoise2=TotalNoise2+negEM2fC[iTS];
   }

   float TotalSignal3=0;
   for(int iTS=4;iTS<7;iTS++){
      if(negEM3fC[iTS]<0){
	negEM3fC[iTS]=0;
      }  
      
      TotalSignal3=TotalSignal3+negEM3fC[iTS];
      
   }
  
  float TotalNoise3=0;
   for(int iTS=0;iTS<3;iTS++){
      TotalNoise3=TotalNoise3+negEM3fC[iTS];
   }

   float TotalSignal4=0;
   for(int iTS=4;iTS<7;iTS++){
      if(negEM4fC[iTS]<0){
	negEM4fC[iTS]=0;
      }  
      
      TotalSignal4=TotalSignal4+negEM4fC[iTS];
      
   }
  
  float TotalNoise4=0;
   for(int iTS=0;iTS<3;iTS++){
      TotalNoise4=TotalNoise4+negEM4fC[iTS];
      }
   
   
   float TotalSignal5=0;
   for(int iTS=4;iTS<7;iTS++){
      if(negEM5fC[iTS]<0){
	negEM5fC[iTS]=0;
      }  
      
      TotalSignal5=TotalSignal5+negEM5fC[iTS];
      
   }
  
  float TotalNoise5=0;
   for(int iTS=0;iTS<3;iTS++){
      TotalNoise5=TotalNoise5+negEM5fC[iTS];
  	  }
  
   EMsum=(TotalSignal-TotalNoise)+(TotalSignal2-TotalNoise2)+(TotalSignal3-TotalNoise3)+(TotalSignal4-TotalNoise4)+(TotalSignal5-TotalNoise5);
   HADsum=(HDTotalSignal-HDTotalNoise)+(HDTotalSignal2-HDTotalNoise2)+(HDTotalSignal3-HDTotalNoise3)+(HDTotalSignal4-HDTotalNoise4);
   EMandHADsum=EMsum+HADsum;
   ratioEMtoHAD=EMsum/HADsum;

   histogram_1->Fill((HADsum+EMsum));
//   histogram_1->Fill((HADsum+(1.35)*EMsum)*0.78283/(1.48), EMsum<200);
   histogram_2D->Fill((HADsum+EMsum),EMsum);
   }
   histogram_1->Draw(); 
   c2 = new TCanvas();
   histogram_2D->Draw("colz");
}
