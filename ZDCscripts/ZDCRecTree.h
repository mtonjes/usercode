//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Sep 14 15:25:54 2011 by ROOT version 5.27/06b
// from TTree ZDCRecTree/ZDC Rec Tree
// found on file: /data/users/belt/PbPb_data/zdc/zdctrees_151353_allFiles.root
//////////////////////////////////////////////////////////

#ifndef ZDCRecTree_h
#define ZDCRecTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class ZDCRecTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Float_t         negEM1energy;
   Float_t         negEM1timing;
   Float_t         negEM2energy;
   Float_t         negEM2timing;
   Float_t         negEM3energy;
   Float_t         negEM3timing;
   Float_t         negEM4energy;
   Float_t         negEM4timing;
   Float_t         negEM5energy;
   Float_t         negEM5timing;
   Float_t         negHD1energy;
   Float_t         negHD1timing;
   Float_t         negHD2energy;
   Float_t         negHD2timing;
   Float_t         negHD3energy;
   Float_t         negHD3timing;
   Float_t         negHD4energy;
   Float_t         negHD4timing;
   Float_t         posEM1energy;
   Float_t         posEM1timing;
   Float_t         posEM2energy;
   Float_t         posEM2timing;
   Float_t         posEM3energy;
   Float_t         posEM3timing;
   Float_t         posEM4energy;
   Float_t         posEM4timing;
   Float_t         posEM5energy;
   Float_t         posEM5timing;
   Float_t         posHD1energy;
   Float_t         posHD1timing;
   Float_t         posHD2energy;
   Float_t         posHD2timing;
   Float_t         posHD3energy;
   Float_t         posHD3timing;
   Float_t         posHD4energy;
   Float_t         posHD4timing;

   // List of branches
   TBranch        *b_negEM1energy;   //!
   TBranch        *b_negEM1timing;   //!
   TBranch        *b_negEM2energy;   //!
   TBranch        *b_negEM2timing;   //!
   TBranch        *b_negEM3energy;   //!
   TBranch        *b_negEM3timing;   //!
   TBranch        *b_negEM4energy;   //!
   TBranch        *b_negEM4timing;   //!
   TBranch        *b_negEM5energy;   //!
   TBranch        *b_negEM5timing;   //!
   TBranch        *b_negHD1energy;   //!
   TBranch        *b_negHD1timing;   //!
   TBranch        *b_negHD2energy;   //!
   TBranch        *b_negHD2timing;   //!
   TBranch        *b_negHD3energy;   //!
   TBranch        *b_negHD3timing;   //!
   TBranch        *b_negHD4energy;   //!
   TBranch        *b_negHD4timing;   //!
   TBranch        *b_posEM1energy;   //!
   TBranch        *b_posEM1timing;   //!
   TBranch        *b_posEM2energy;   //!
   TBranch        *b_posEM2timing;   //!
   TBranch        *b_posEM3energy;   //!
   TBranch        *b_posEM3timing;   //!
   TBranch        *b_posEM4energy;   //!
   TBranch        *b_posEM4timing;   //!
   TBranch        *b_posEM5energy;   //!
   TBranch        *b_posEM5timing;   //!
   TBranch        *b_posHD1energy;   //!
   TBranch        *b_posHD1timing;   //!
   TBranch        *b_posHD2energy;   //!
   TBranch        *b_posHD2timing;   //!
   TBranch        *b_posHD3energy;   //!
   TBranch        *b_posHD3timing;   //!
   TBranch        *b_posHD4energy;   //!
   TBranch        *b_posHD4timing;   //!

   ZDCRecTree(TTree *tree=0);
   virtual ~ZDCRecTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ZDCRecTree_cxx
ZDCRecTree::ZDCRecTree(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/data/users/belt/PbPb_data/zdc/zdctrees_151350_151351_allev_OlegRaw.root");
      if (!f) {
         f = new TFile("/data/users/belt/PbPb_data/zdc/zdctrees_151350_151351_allev_OlegRaw.root");
      }
      tree = (TTree*)gDirectory->Get("ZDCRecTree");

   }
   Init(tree);
}

ZDCRecTree::~ZDCRecTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ZDCRecTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ZDCRecTree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void ZDCRecTree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("negEM1energy", &negEM1energy, &b_negEM1energy);
   fChain->SetBranchAddress("negEM1timing", &negEM1timing, &b_negEM1timing);
   fChain->SetBranchAddress("negEM2energy", &negEM2energy, &b_negEM2energy);
   fChain->SetBranchAddress("negEM2timing", &negEM2timing, &b_negEM2timing);
   fChain->SetBranchAddress("negEM3energy", &negEM3energy, &b_negEM3energy);
   fChain->SetBranchAddress("negEM3timing", &negEM3timing, &b_negEM3timing);
   fChain->SetBranchAddress("negEM4energy", &negEM4energy, &b_negEM4energy);
   fChain->SetBranchAddress("negEM4timing", &negEM4timing, &b_negEM4timing);
   fChain->SetBranchAddress("negEM5energy", &negEM5energy, &b_negEM5energy);
   fChain->SetBranchAddress("negEM5timing", &negEM5timing, &b_negEM5timing);
   fChain->SetBranchAddress("negHD1energy", &negHD1energy, &b_negHD1energy);
   fChain->SetBranchAddress("negHD1timing", &negHD1timing, &b_negHD1timing);
   fChain->SetBranchAddress("negHD2energy", &negHD2energy, &b_negHD2energy);
   fChain->SetBranchAddress("negHD2timing", &negHD2timing, &b_negHD2timing);
   fChain->SetBranchAddress("negHD3energy", &negHD3energy, &b_negHD3energy);
   fChain->SetBranchAddress("negHD3timing", &negHD3timing, &b_negHD3timing);
   fChain->SetBranchAddress("negHD4energy", &negHD4energy, &b_negHD4energy);
   fChain->SetBranchAddress("negHD4timing", &negHD4timing, &b_negHD4timing);
   fChain->SetBranchAddress("posEM1energy", &posEM1energy, &b_posEM1energy);
   fChain->SetBranchAddress("posEM1timing", &posEM1timing, &b_posEM1timing);
   fChain->SetBranchAddress("posEM2energy", &posEM2energy, &b_posEM2energy);
   fChain->SetBranchAddress("posEM2timing", &posEM2timing, &b_posEM2timing);
   fChain->SetBranchAddress("posEM3energy", &posEM3energy, &b_posEM3energy);
   fChain->SetBranchAddress("posEM3timing", &posEM3timing, &b_posEM3timing);
   fChain->SetBranchAddress("posEM4energy", &posEM4energy, &b_posEM4energy);
   fChain->SetBranchAddress("posEM4timing", &posEM4timing, &b_posEM4timing);
   fChain->SetBranchAddress("posEM5energy", &posEM5energy, &b_posEM5energy);
   fChain->SetBranchAddress("posEM5timing", &posEM5timing, &b_posEM5timing);
   fChain->SetBranchAddress("posHD1energy", &posHD1energy, &b_posHD1energy);
   fChain->SetBranchAddress("posHD1timing", &posHD1timing, &b_posHD1timing);
   fChain->SetBranchAddress("posHD2energy", &posHD2energy, &b_posHD2energy);
   fChain->SetBranchAddress("posHD2timing", &posHD2timing, &b_posHD2timing);
   fChain->SetBranchAddress("posHD3energy", &posHD3energy, &b_posHD3energy);
   fChain->SetBranchAddress("posHD3timing", &posHD3timing, &b_posHD3timing);
   fChain->SetBranchAddress("posHD4energy", &posHD4energy, &b_posHD4energy);
   fChain->SetBranchAddress("posHD4timing", &posHD4timing, &b_posHD4timing);
   Notify();
}

Bool_t ZDCRecTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ZDCRecTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ZDCRecTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ZDCRecTree_cxx
