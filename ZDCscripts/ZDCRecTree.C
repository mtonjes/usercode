#define ZDCRecTree_cxx
#include "ZDCRecTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void ZDCRecTree::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L ZDCRecTree.C
//      Root > ZDCRecTree t
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
  gStyle->SetPalette(1);


    TChain *chain=new TChain("ZDCRecTree","");
     TH1F* histogram_1 = new TH1F("RecHitNegEMandHAD", "RecHit 151350,151351 Net(EM+HAD) TS 4 5 6 Sum_EM<200, EM*0.78283/0.025514", 1000, -100, 30000); 
 //    TH1F* histogram_1 = new TH1F("TotalNetNegEMandHAD", "151353Net(1.35*EM+HAD)*0.78283/1.48 TS 4 5 6", 1000, -100, 30000); 
     TH2F* histogram_2D = new TH2F("RecHitNegEMandHAD2D", "RecHit 151350,151351 EMvsEM+HAD TS 4 5 6, EM*0.78283/0.025514",  200, -100, 30000, 200, -100, 2000); 
     
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      float EMsum=0;
      float HADsum=0;
      float EMandHADsum=0;
      float ratioEMtoHAD=0;
      EMsum = (negEM1energy + negEM2energy + negEM3energy + negEM4energy + negEM5energy)*0.78283/0.02551;
      HADsum = negHD1energy + negHD2energy + negHD3energy + negHD4energy;
      EMandHADsum=EMsum+HADsum;
      ratioEMtoHAD=EMsum/HADsum;
      
         histogram_1->Fill((HADsum+EMsum), EMsum<200);
//   histogram_1->Fill((HADsum+(1.35)*EMsum)*0.78283/(1.48), EMsum<200);
   histogram_2D->Fill((HADsum+EMsum),EMsum);
   }
   histogram_1->Draw(); 
   c2 = new TCanvas();
   histogram_2D->Draw("colz");
}
