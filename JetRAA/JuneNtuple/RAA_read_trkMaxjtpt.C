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
#include "/net/hisrv0001/home/belt/wrk/JetRAA/RaghavCode/Headers/plot.h"

static const int nbins_cent = 6;
static const Double_t boundaries_cent[nbins_cent+1] = {0,2,4,12,20,28,36};// multiply by 2.5 to get your actual centrality % (old 2011 data) 
//now we have to multiply by 5, since centrality goes from 0-200. 
const double kdelrcut=0.3;

int findBin(int bin)
{
  int ibin=-1;
  //! centrality is defined as 0.5% bins of cross section
  //! in 0-200 bins               
  if(bin<=10)ibin=0; //! 0-5%
  else if(bin>10  && bin<=20 )ibin=1; //! 5-10%
  else if(bin>20  && bin<=60 )ibin=2;  //! 10-30%
  else if(bin>60  && bin<=100)ibin=3;  //! 30-50%
  else if(bin>100 && bin<=140)ibin=4;  //! 50-70%
  else if(bin>140 && bin<=180)ibin=5;  //! 70-90%
  else if(bin>180 && bin<=200)ibin=6;  //! 90-100%
  return ibin;
}

static const int nbins_pt = 32;
static const double boundaries_pt[nbins_pt+1] = {  3, 4, 5, 7, 9, 12, 15, 18, 21, 24, 28,  32, 37, 43, 49, 56,  64, 74, 84, 97, 114,  133, 153, 174, 196,  220, 245, 272, 300, 330, 362, 395, 501};

//  const int ptSelection = 17;
//  const int ptBoundary[ptSelection+1] = {30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};
  const int ptSelection = 17;
  const int ptBoundary[ptSelection+1] = {40,60,80,100,120,140,160,180,200,220,240,260,280,300,320,340};
  
int findPtBin(float inpt)
{
  int ptbin=-1;
  for(int a = 0;a<ptSelection; ++a) { 
    if(inpt>ptBoundary[a] && inpt<=ptBoundary[a+1]){
      ptbin=a;
    }
  }
  return ptbin;
}
// static const int nbins_pt = 30;
// static const double boundaries_pt[nbins_pt+1] = {  3, 4, 5, 7, 9, 12, 15, 18, 21, 24, 28,  32, 37, 43, 49, 56,  64, 74, 84, 97, 114,  133, 153, 174, 196,  220, 245, 300, 330, 362, 395};

// the following bins is the cms pp nlo pt bins
// static const int nbins_pt = 29;
// static const double boundaries_pt[nbins_pt+1] = {22, 27, 33, 39, 47, 55, 64, 74, 84, 97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 507, 548, 592, 638,790,967};

// the following bins is the atlas spectra pt binning
// static const int nbins_pt = 12;
// static const double boundaries_pt[nbins_pt+1] = {31., 39., 50., 63., 79., 100., 125., 158., 199., 251., 316., 398., 501};

// the following bins is the atlas Rcp pt binning
// static const int nbins_pt = 12;
// static const double boundaries_pt[nbins_pt+1] = {38.36, 44.21, 50.94, 58.7, 67.64 , 77.94 , 89.81, 103.5, 119.3, 137.4 , 158.3, 182.5,  210.3};


using namespace std;


void RAA_read_trkMaxjtpt(
				  Int_t radius = 3
)
{
  gStyle->SetOptStat(0);
  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();
char* etaWidth = (char*)"20_eta_20";
				  Int_t etaLow = 20;
				  Int_t etaHigh = 20;
  // char * etaWidth = (char*)Form("%d_eta_%d",etaLow, etaHigh);
  cout<<"etaWidth = "<<etaWidth<<endl;
  cout<<"Radius = "<<radius<<endl;

  Float_t pfptmin=30;
  Float_t trMaxCut=0.01; 
// to run macro in test mode and not process whole tree, make Short=1
// to read all entries, make Short=0  
  Int_t Short=0;
  long TestEntries=10000;
  long entries;
  
  if(radius==2){
     pfptmin = 30;
  } else if(radius==3){
     pfptmin = 40;
  } else if(radius==4){
     pfptmin = 50;
  }

  bool isSymm = false;
  if(etaLow == etaHigh) isSymm = true;
  
  char * ntuple = (char*)"Pawan"; //  or "Pawan"
  
  // the cut is a 3 step cut based on the different value of the trMax/chMax - copy the following lines into your loop (with the corresponding branch address set)
  // if(trMax/chMax <= 0.5 && eMax/Sumcand < 0.05) hGood->Fill();
  // if(trMax/chMax > 0.5 && trMax/chMax <= 0.85 && eMax/Sumcand < (18/7 *(Float_t)calopt_1/pfpt_1 - 9/7)) ) hGood->Fill();
  // if(trMax/chMax > 0.85 & eMax/Sumcand > 0.9) hGood->Fill();
  
  TFile * fData, * fMC;
  TTree * Data_matched, * Data_unmatched, *MC_matched, * MC_unmatched; 
  TCanvas * ceMaxSumcand_jet55[ptSelection], * ceMaxSumcand_jet65[ptSelection], * ceMaxSumcand_jet80[ptSelection];

  if(ntuple == "Pawan"){
    fData = TFile::Open("/mnt/hadoop/cms/store/user/pawan/trees/JetRaaTree_akPu234_PbPb_DATA.root");
    fMC = TFile::Open("/mnt/hadoop/cms/store/user/pawan/trees/JetRaaTree_akPu234_PbPb_MC.root");

    Data_matched = (TTree*)fData->Get(Form("akPu%dJetAnalyzer/jetTree",radius));
    MC_matched = (TTree*)fMC->Get(Form("akPu%dJetAnalyzer/jetTree",radius));
  }
  if(ntuple == "Raghav"){
    // Raghav's ntuples - running to find the difference in spectra between Pawan's and mine.
    fData = TFile::Open(Form("/export/d00/scratch/rkunnawa/rootfiles/PbPb_Data_calo_pf_jet_correlation_deltaR_0p2_akPu%d_20150331.root",radius));
    fMC = TFile::Open(Form("/export/d00/scratch/rkunnawa/rootfiles/PbPb_MC_calo_pf_jet_correlation_deltaR_0p2_akPu%d_20150331.root",radius));

    Data_matched= (TTree*)fData->Get("matchedJets");
    Data_unmatched = (TTree*)fData->Get("unmatchedPFJets");

    MC_matched = (TTree*)fMC->Get("matchedJets");
    MC_unmatched = (TTree*)fMC->Get("unmatchedPFJets");
  }
  
  
//  TH2F* hData_eMaxSumcand_calopfpt_ptselection[ptSelection];
//  TH2F* hMC_eMaxSumcand_calopfpt_ptselection[ptSelection];
//  TH2F* hMC_eMaxSumcand_calopfpt_refptselection[ptSelection];
//  TCanvas * ceMaxSumcand [ptSelection];

  TLine * CutA_1 = new TLine(0.5, 0.05, 0.85, 0.9);
  CutA_1->SetLineStyle(2);
  CutA_1->SetLineWidth(2);
  CutA_1->SetLineColor(kRed);
  TLine * CutA_2 = new TLine(0.85, 0.9, 0.85, 5);
  CutA_2->SetLineStyle(2);
  CutA_2->SetLineWidth(2);
  CutA_2->SetLineColor(kRed);
  TLine * CutA_3 = new TLine(0, 0.05, 0.5, 0.05);
  CutA_3->SetLineStyle(2);
  CutA_3->SetLineWidth(2);
  CutA_3->SetLineColor(kRed);

  TH2F* hData_eMaxSumcand_calopfpt_ptselection_jet55[ptSelection];
  TH2F* hMC_eMaxSumcand_calopfpt_ptselection_jet55[ptSelection];
  TH2F* hMC_eMaxSumcand_calopfpt_refptselection_jet55[ptSelection];
  
  TH2F* hData_eMaxSumcand_calopfpt_ptselection_jet65[ptSelection];
  TH2F* hMC_eMaxSumcand_calopfpt_ptselection_jet65[ptSelection];
  TH2F* hMC_eMaxSumcand_calopfpt_refptselection_jet65[ptSelection];

  TH2F* hData_eMaxSumcand_calopfpt_ptselection_jet80[ptSelection];
  TH2F* hMC_eMaxSumcand_calopfpt_ptselection_jet80[ptSelection];
  TH2F* hMC_eMaxSumcand_calopfpt_refptselection_jet80[ptSelection];  

  TH2F* hData_unmatch_eMaxSumcand_calopfpt_ptselection_jet55[ptSelection];
  TH2F* hMC_unmatch_eMaxSumcand_calopfpt_ptselection_jet55[ptSelection];
  TH2F* hMC_unmatch_eMaxSumcand_calopfpt_refptselection_jet55[ptSelection];
  
  TH2F* hData_unmatch_eMaxSumcand_calopfpt_ptselection_jet65[ptSelection];
  TH2F* hMC_unmatch_eMaxSumcand_calopfpt_ptselection_jet65[ptSelection];
  TH2F* hMC_unmatch_eMaxSumcand_calopfpt_refptselection_jet65[ptSelection];

  TH2F* hData_unmatch_eMaxSumcand_calopfpt_ptselection_jet80[ptSelection];
  TH2F* hMC_unmatch_eMaxSumcand_calopfpt_ptselection_jet80[ptSelection];
  TH2F* hMC_unmatch_eMaxSumcand_calopfpt_refptselection_jet80[ptSelection];  
  for(int a = 0;a<ptSelection; ++a) {

    hData_eMaxSumcand_calopfpt_ptselection_jet55[a] = new TH2F(Form("hData_eMaxSumcand_calopfpt_ptselection_jet55_%d",a),"",100, 0, 1.2, 100, 0, 1.2);
    hMC_eMaxSumcand_calopfpt_ptselection_jet55[a] = new TH2F(Form("hMC_eMaxSumcand_calopfpt_ptselection_jet55_%d",a),"",100, 0, 1.2, 100, 0, 1.2);
    hMC_eMaxSumcand_calopfpt_refptselection_jet55[a] = new TH2F(Form("hMC_eMaxSumcand_calopfpt_refptselection_jet55_%d",a),"",100, 0, 1.2, 100, 0, 1.2);
    
    hData_unmatch_eMaxSumcand_calopfpt_ptselection_jet55[a] = new TH2F(Form("hData_unmatch_eMaxSumcand_calopfpt_ptselection_jet55_%d",a),"",100, 0, 1.2, 100, 0, 1.2);
    hMC_unmatch_eMaxSumcand_calopfpt_ptselection_jet55[a] = new TH2F(Form("hMC_unmatch_eMaxSumcand_calopfpt_ptselection_jet55_%d",a),"",100, 0, 1.2, 100, 0, 1.2);
    hMC_unmatch_eMaxSumcand_calopfpt_refptselection_jet55[a] = new TH2F(Form("hMC_unmatch_eMaxSumcand_calopfpt_refptselection_jet55_%d",a),"",100, 0, 1.2, 100, 0, 1.2);

    hData_eMaxSumcand_calopfpt_ptselection_jet65[a] = new TH2F(Form("hData_eMaxSumcand_calopfpt_ptselection_jet65_%d",a),"",100, 0, 1.2, 100, 0, 1.2);
    hMC_eMaxSumcand_calopfpt_ptselection_jet65[a] = new TH2F(Form("hMC_eMaxSumcand_calopfpt_ptselection_jet65_%d",a),"",100, 0, 1.2, 100, 0, 1.2);
    hMC_eMaxSumcand_calopfpt_refptselection_jet65[a] = new TH2F(Form("hMC_eMaxSumcand_calopfpt_refptselection_jet65_%d",a),"",100, 0, 1.2, 100, 0, 1.2);
    
    hData_unmatch_eMaxSumcand_calopfpt_ptselection_jet65[a] = new TH2F(Form("hData_unmatch_eMaxSumcand_calopfpt_ptselection_jet65_%d",a),"",100, 0, 1.2, 100, 0, 1.2);
    hMC_unmatch_eMaxSumcand_calopfpt_ptselection_jet65[a] = new TH2F(Form("hMC_unmatch_eMaxSumcand_calopfpt_ptselection_jet65_%d",a),"",100, 0, 1.2, 100, 0, 1.2);
    hMC_unmatch_eMaxSumcand_calopfpt_refptselection_jet65[a] = new TH2F(Form("hMC_unmatch_eMaxSumcand_calopfpt_refptselection_jet65_%d",a),"",100, 0, 1.2, 100, 0, 1.2);

    hData_eMaxSumcand_calopfpt_ptselection_jet80[a] = new TH2F(Form("hData_eMaxSumcand_calopfpt_ptselection_jet80_%d",a),"",100, 0, 1.2, 100, 0, 1.2);
    hMC_eMaxSumcand_calopfpt_ptselection_jet80[a] = new TH2F(Form("hMC_eMaxSumcand_calopfpt_ptselection_jet80_%d",a),"",100, 0, 1.2, 100, 0, 1.2);
    hMC_eMaxSumcand_calopfpt_refptselection_jet80[a] = new TH2F(Form("hMC_eMaxSumcand_calopfpt_refptselection_jet80_%d",a),"",100, 0, 1.2, 100, 0, 1.2);
    
    hData_unmatch_eMaxSumcand_calopfpt_ptselection_jet80[a] = new TH2F(Form("hData_unmatch_eMaxSumcand_calopfpt_ptselection_jet80_%d",a),"",100, 0, 1.2, 100, 0, 1.2);
    hMC_unmatch_eMaxSumcand_calopfpt_ptselection_jet80[a] = new TH2F(Form("hMC_unmatch_eMaxSumcand_calopfpt_ptselection_jet80_%d",a),"",100, 0, 1.2, 100, 0, 1.2);
    hMC_unmatch_eMaxSumcand_calopfpt_refptselection_jet80[a] = new TH2F(Form("hMC_unmatch_eMaxSumcand_calopfpt_refptselection_jet80_%d",a),"",100, 0, 1.2, 100, 0, 1.2);

  }  
  // 1 - Data, 2 - MC
  Float_t pfpt_1[1000], pfpt_2[1000];
  Float_t pfrefpt_2[1000];
  Float_t calopt_1[1000], calopt_2[1000];
  Int_t npf_1, npf_2;
  Int_t isCaloMatch_1[1000], isCaloMatch_2[1000]; 
  Float_t eMax_1[1000], eMax_2[1000];
  Float_t chMax_1[1000], chMax_2[1000];
  Float_t neMax_1[1000], neMax_2[1000];
  Float_t phMax_1[1000], phMax_2[1000];
  Float_t muMax_1[1000], muMax_2[1000]; 
  Float_t trMax_1[1000], trMax_2[1000];
  Float_t eSum_1[1000], eSum_2[1000];  
  Float_t chSum_1[1000], chSum_2[1000];
//  Float_t trSum_1[1000], trSum_2[1000];
  Float_t phSum_1[1000], phSum_2[1000];
  Float_t neSum_1[1000], neSum_2[1000];
  Float_t muSum_1[1000], muSum_2[1000];
  Int_t jet55_1, jet65_1, jet80_1;
  Int_t jet55_p_1, jet65_p_1, jet80_p_1;
  Int_t jet55_2, jet65_2, jet80_2;
  Int_t jet55_p_2;
  Float_t pthat_2;
  Double_t weight;
  Int_t subid_2[1000];
  Int_t hiBin_1, hiBin_2;
  Float_t eta_1[1000], eta_2[1000];
  Float_t pfrawpt_1[1000], pfrawpt_2[1000]; 
  Int_t nref_2;
  Int_t pfrefidx_2[1000]; //! REF -> PF match index
  Float_t refdrjt_2[1000];

  if(ntuple == "Pawan"){
    Data_matched->SetBranchAddress("npf", &npf_1);
    Data_matched->SetBranchAddress("isCaloMatch", &isCaloMatch_1);
    Data_matched->SetBranchAddress("calopt",&calopt_1);
    Data_matched->SetBranchAddress("pfpt",&pfpt_1);
    Data_matched->SetBranchAddress("eMax",&eMax_1);
    Data_matched->SetBranchAddress("chMax",&chMax_1);
    Data_matched->SetBranchAddress("trMax",&trMax_1);    
    Data_matched->SetBranchAddress("neMax",&neMax_1);
    Data_matched->SetBranchAddress("phMax",&phMax_1);
    Data_matched->SetBranchAddress("muMax",&muMax_1);
    Data_matched->SetBranchAddress("chSum",&chSum_1);
//    Data_matched->SetBranchAddress("trSum",&trSum_1);
    Data_matched->SetBranchAddress("phSum",&phSum_1);
    Data_matched->SetBranchAddress("neSum",&neSum_1);
    Data_matched->SetBranchAddress("muSum",&muSum_1);
    Data_matched->SetBranchAddress("hiBin",&hiBin_1);
    Data_matched->SetBranchAddress("jet55",&jet55_1);
    Data_matched->SetBranchAddress("jet65",&jet65_1);
    Data_matched->SetBranchAddress("jet80",&jet80_1);
    Data_matched->SetBranchAddress("jet55_prescl",&jet55_p_1);
    Data_matched->SetBranchAddress("jet65_prescl",&jet65_p_1);
    Data_matched->SetBranchAddress("jet80_prescl",&jet80_p_1);
    Data_matched->SetBranchAddress("pfeta",&eta_1);
    Data_matched->SetBranchAddress("pfrawpt",&pfrawpt_1);
  }

#if 0
  if(ntuple == "Raghav")  {
    Data_matched->SetBranchAddress("calopt",&calopt_1);
    Data_matched->SetBranchAddress("pfpt",&pfpt_1);
    Data_matched->SetBranchAddress("eMax",&eMax_1);
    Data_matched->SetBranchAddress("chMax",&chMax_1);
    Data_matched->SetBranchAddress("trMax",&trMax_1);
    Data_matched->SetBranchAddress("neMax",&neMax_1);
    Data_matched->SetBranchAddress("phMax",&phMax_1);
    Data_matched->SetBranchAddress("chSum",&chSum_1);
//    Data_matched->SetBranchAddress("trSum",&trSum_1);
    Data_matched->SetBranchAddress("phSum",&phSum_1);
    Data_matched->SetBranchAddress("neSum",&neSum_1);
    Data_matched->SetBranchAddress("muSum",&muSum_1);
    Data_matched->SetBranchAddress("hiBin",&hiBin_1);
    Data_matched->SetBranchAddress("jet55",&jet55_1);
    Data_matched->SetBranchAddress("jet65",&jet65_1);
    Data_matched->SetBranchAddress("jet80",&jet80_1);
    Data_matched->SetBranchAddress("jet55_prescl",&jet55_p_1);
    Data_matched->SetBranchAddress("jet65_prescl",&jet65_p_1);
    Data_matched->SetBranchAddress("jet80_prescl",&jet80_p_1);
    Data_matched->SetBranchAddress("pfeta",&eta_1);
    Data_matched->SetBranchAddress("pfrawpt",&pfrawpt_1);
 
    Data_unmatched->SetBranchAddress("pfpt",&pfpt_1);
    Data_unmatched->SetBranchAddress("eMax",&eMax_1);
    Data_unmatched->SetBranchAddress("chMax",&chMax_1);
    Data_unmatched->SetBranchAddress("trMax",&trMax_1);
    Data_unmatched->SetBranchAddress("chSum",&chSum_1);
//    Data_unmatched->SetBranchAddress("trSum",&trSum_1);
    Data_unmatched->SetBranchAddress("phSum",&phSum_1);
    Data_unmatched->SetBranchAddress("neSum",&neSum_1);
    Data_unmatched->SetBranchAddress("muSum",&muSum_1);
    Data_unmatched->SetBranchAddress("hiBin",&hiBin_1);
    Data_unmatched->SetBranchAddress("jet55",&jet55_1);
    Data_unmatched->SetBranchAddress("jet65",&jet65_1);
    Data_unmatched->SetBranchAddress("jet80",&jet80_1);
    Data_unmatched->SetBranchAddress("jet55_prescl",&jet55_p_1);
    Data_unmatched->SetBranchAddress("jet65_prescl",&jet65_p_1);
    Data_unmatched->SetBranchAddress("jet80_prescl",&jet80_p_1);
    Data_unmatched->SetBranchAddress("pfeta",&eta_1);
    Data_unmatched->SetBranchAddress("pfrawpt",&pfrawpt_1);
  }
#endif

  MC_matched->SetBranchAddress("npf", &npf_2);
  MC_matched->SetBranchAddress("nref", &nref_2);
  MC_matched->SetBranchAddress("pfrefidx",&pfrefidx_2);
  MC_matched->SetBranchAddress("refdrjt",&refdrjt_2);
  MC_matched->SetBranchAddress("pthat", &pthat_2);
  MC_matched->SetBranchAddress("isCaloMatch", &isCaloMatch_2);
  MC_matched->SetBranchAddress("calopt",&calopt_2);
  MC_matched->SetBranchAddress("pfpt",&pfpt_2);
  MC_matched->SetBranchAddress("eMax",&eMax_2);
  MC_matched->SetBranchAddress("chMax",&chMax_2);
  MC_matched->SetBranchAddress("trMax",&trMax_2);
  MC_matched->SetBranchAddress("neMax",&neMax_2);
  MC_matched->SetBranchAddress("phMax",&phMax_2);
  MC_matched->SetBranchAddress("muMax",&muMax_2);  
  MC_matched->SetBranchAddress("chSum",&chSum_2);
//  MC_matched->SetBranchAddress("trSum",&trSum_2);
  MC_matched->SetBranchAddress("phSum",&phSum_2);
  MC_matched->SetBranchAddress("neSum",&neSum_2);
  MC_matched->SetBranchAddress("muSum",&muSum_2);
  MC_matched->SetBranchAddress("hiBin",&hiBin_2);
  if(ntuple == "Pawan")  MC_matched->SetBranchAddress("refpt",&pfrefpt_2);
  //if(ntuple == "Raghav") MC_matched->SetBranchAddress("pfrefpt",&pfrefpt_2);
  MC_matched->SetBranchAddress("jet55",&jet55_2);
  MC_matched->SetBranchAddress("jet65",&jet65_2);
  MC_matched->SetBranchAddress("jet80",&jet80_2);
  MC_matched->SetBranchAddress("weight", &weight);
  MC_matched->SetBranchAddress("subid", &subid_2);
  MC_matched->SetBranchAddress("jet55_prescl",&jet55_p_2);
  MC_matched->SetBranchAddress("pfeta",&eta_2);
  MC_matched->SetBranchAddress("pfrawpt",&pfrawpt_2);

#if 0
  if(ntuple == "Raghav"){
    MC_unmatched->SetBranchAddress("pfpt",&pfpt_2);
    MC_unmatched->SetBranchAddress("eMax",&eMax_2);
    MC_unmatched->SetBranchAddress("chMax",&chMax_2);
    MC_unmatched->SetBranchAddress("trMax",&trMax_2);
    MC_unmatched->SetBranchAddress("chSum",&chSum_2);
//    MC_unmatched->SetBranchAddress("trSum",&trSum_2);
    MC_unmatched->SetBranchAddress("phSum",&phSum_2);
    MC_unmatched->SetBranchAddress("neSum",&neSum_2);
    MC_unmatched->SetBranchAddress("muSum",&muSum_2);
    MC_unmatched->SetBranchAddress("hiBin",&hiBin_2);
    if(ntuple == "Pawan")  MC_unmatched->SetBranchAddress("refpt",&pfrefpt_2);
    if(ntuple == "Raghav") MC_unmatched->SetBranchAddress("pfrefpt",&pfrefpt_2);
    MC_unmatched->SetBranchAddress("jet55",&jet55_2);
    MC_unmatched->SetBranchAddress("jet65",&jet65_2);
    MC_unmatched->SetBranchAddress("jet80",&jet80_2);
    MC_unmatched->SetBranchAddress("weight", & weight);
    MC_unmatched->SetBranchAddress("subid", &subid_2);
    MC_unmatched->SetBranchAddress("jet55_prescl",&jet55_p_2);
    MC_unmatched->SetBranchAddress("pfeta",&eta_2);
    MC_unmatched->SetBranchAddress("pfrawpt",&pfrawpt_2);
  }
#endif
  
  // data loop
// test mode is Short=1
  if(Short==1){
   entries=TestEntries;
  } else {
    entries = Data_matched->GetEntries();
  }    
  //entries = 1000;
  Float_t Jet55_prescl = 2.0475;

  // get the random value for smear systematics, TRandom rnd, value per jet = rnd.Gaus(0,1);
  TRandom rnd; 
  TH1F * htest = new TH1F("htest","",nbins_pt, boundaries_pt);

  cout<<"matched Data ntuple "<<endl;

  for(long nentry = 0; nentry < entries; ++nentry ){

    if(nentry%100000 == 0) cout<<nentry<<"/"<<entries<<endl;
    Data_matched->GetEntry(nentry);

    Int_t cBin = findBin(hiBin_1);
    if(cBin == -1 || cBin >= nbins_cent) continue;

    Float_t wght = 1; 
    // if(etaBoundary == 1.0){ 
    //   if(radius == 2) wght = R2nCorr[cBin][htest->FindBin(pfpt_1)];
    //   if(radius == 3) wght = R3nCorr[cBin][htest->FindBin(pfpt_1)];
    //   if(radius == 4) wght = R4nCorr[cBin][htest->FindBin(pfpt_1)];  
    // }
    
    for(int g = 0; g<npf_1; ++g){ // jet loop

      if(isSymm && TMath::Abs(eta_1[g]) > (Float_t)etaHigh/10) continue;       
      if(!isSymm && (TMath::Abs(eta_1[g]) < (Float_t)etaLow/10 || TMath::Abs(eta_1[g]) > (Float_t)etaHigh/10)) continue;
   
      Float_t Sumcand = chSum_1[g] + phSum_1[g] + neSum_1[g] + muSum_1[g];
//      cout<<"find my ptbin with pfpt_1[g]: "<<pfpt_1[g]<<endl;
      int ptbin=findPtBin(pfpt_1[g]);
 //     cout<<"ptbin is: "<<ptbin<<endl;
      if(ptbin==-1){ continue; }
      if(isCaloMatch_1[g] == 1){

	if(jet55_1 == 1 && jet65_1 == 0 && jet80_1 == 0 ) {
	 if(calopt_1[g]/pfpt_1[g] > 0.5 && calopt_1[g]/pfpt_1[g] <= 0.85 && eMax_1[g]/Sumcand < ((Float_t)18/7 *(Float_t)calopt_1[g]/pfpt_1[g] - (Float_t)9/7)) {
	  hData_eMaxSumcand_calopfpt_ptselection_jet55[ptbin]->Fill((trMax_1[g]/pfpt_1[g]),(neSum_1[g]+phSum_1[g])/Sumcand);
    }
    if(calopt_1[g]/pfpt_1[g] > 0.85){
	  hData_eMaxSumcand_calopfpt_ptselection_jet55[ptbin]->Fill((trMax_1[g]/pfpt_1[g]),(neSum_1[g]+phSum_1[g])/Sumcand);    
    }
 	if(calopt_1[g]/pfpt_1[g] <= 0.5 && eMax_1[g]/Sumcand < 0.05) {
	  hData_eMaxSumcand_calopfpt_ptselection_jet55[ptbin]->Fill((trMax_1[g]/pfpt_1[g]),(neSum_1[g]+phSum_1[g])/Sumcand);    
    }   
//	  hData_Jet55_noCut->Fill(pfpt_1[g], Jet55_prescl* wght);
//	  hpbpb_Data_Jet55_noCut[cBin]->Fill(pfpt_1[g], Jet55_prescl* wght);
	  }
          
	if(jet65_1 == 1 && jet80_1 == 0 ) {
	 if(calopt_1[g]/pfpt_1[g] > 0.5 && calopt_1[g]/pfpt_1[g] <= 0.85 && eMax_1[g]/Sumcand < ((Float_t)18/7 *(Float_t)calopt_1[g]/pfpt_1[g] - (Float_t)9/7)) {
	  hData_eMaxSumcand_calopfpt_ptselection_jet65[ptbin]->Fill((trMax_1[g]/pfpt_1[g]),(neSum_1[g]+phSum_1[g])/Sumcand);
    }
    if(calopt_1[g]/pfpt_1[g] > 0.85){
	  hData_eMaxSumcand_calopfpt_ptselection_jet65[ptbin]->Fill((trMax_1[g]/pfpt_1[g]),(neSum_1[g]+phSum_1[g])/Sumcand);    
    }
 	if(calopt_1[g]/pfpt_1[g] <= 0.5 && eMax_1[g]/Sumcand < 0.05) {
	  hData_eMaxSumcand_calopfpt_ptselection_jet65[ptbin]->Fill((trMax_1[g]/pfpt_1[g]),(neSum_1[g]+phSum_1[g])/Sumcand);    
    }   
	}

	if(jet80_1 == 1) {
	 if(calopt_1[g]/pfpt_1[g] > 0.5 && calopt_1[g]/pfpt_1[g] <= 0.85 && eMax_1[g]/Sumcand < ((Float_t)18/7 *(Float_t)calopt_1[g]/pfpt_1[g] - (Float_t)9/7)) {
	  hData_eMaxSumcand_calopfpt_ptselection_jet80[ptbin]->Fill((trMax_1[g]/pfpt_1[g]),(neSum_1[g]+phSum_1[g])/Sumcand);
    }
    if(calopt_1[g]/pfpt_1[g] > 0.85){
	  hData_eMaxSumcand_calopfpt_ptselection_jet80[ptbin]->Fill((trMax_1[g]/pfpt_1[g]),(neSum_1[g]+phSum_1[g])/Sumcand);    
    }
 	if(calopt_1[g]/pfpt_1[g] <= 0.5 && eMax_1[g]/Sumcand < 0.05) {
	  hData_eMaxSumcand_calopfpt_ptselection_jet80[ptbin]->Fill((trMax_1[g]/pfpt_1[g]),(neSum_1[g]+phSum_1[g])/Sumcand);    
    }   
	}
      }
      // fill the histograms with unmatched Jets 
      if(isCaloMatch_1[g] ==0) {
      	
	if(jet55_1 == 1 && jet65_1 == 0 && jet80_1 == 0 ) {
	   if(eMax_1[g]/Sumcand < 0.05 ){
		hData_unmatch_eMaxSumcand_calopfpt_ptselection_jet55[ptbin]->Fill((trMax_1[g]/pfpt_1[g]),(neSum_1[g]+phSum_1[g])/Sumcand);
		}
	}
	if(jet65_1 == 1 && jet80_1 == 0 ) {
	   if(eMax_1[g]/Sumcand < 0.05 ){	
		hData_unmatch_eMaxSumcand_calopfpt_ptselection_jet65[ptbin]->Fill((trMax_1[g]/pfpt_1[g]),(neSum_1[g]+phSum_1[g])/Sumcand);
	   }
	}
	if(jet80_1 == 1) {
	   if(eMax_1[g]/Sumcand < 0.05 ){	
		hData_unmatch_eMaxSumcand_calopfpt_ptselection_jet80[ptbin]->Fill((trMax_1[g]/pfpt_1[g]),(neSum_1[g]+phSum_1[g])/Sumcand);
	   }
	}
 
      } // end caloMatch loop
 //   } // end pfptbin check loop
    }// jet loop
    
  }// data ntuple loop
  
#if 0
  if(ntuple == "Raghav"){
    // data unmatched loop:
    entries = Data_unmatched->GetEntries();
    //entries = 1000;
    cout<<"Unmatched Data ntuple "<<endl;
    for(long nentry = 0; nentry < entries; ++nentry ){

      if(nentry%100000 == 0) cout<<nentry<<"/"<<entries<<endl;
      Data_unmatched->GetEntry(nentry);
      Int_t cBin = findBin(hiBin_1);
      if(cBin == -1 || cBin >= nbins_cent) continue;
    
      if(isSymm && TMath::Abs(eta_1) > (Float_t)etaHigh/10) continue;       
      if(!isSymm && (TMath::Abs(eta_1) < (Float_t)etaLow/10 || TMath::Abs(eta_1) > (Float_t)etaHigh/10)) continue;
    
      Float_t wght = 1; 
      // if(etaBoundary == 1.0){
      //   if(radius == 2) wght = R2nCorr[cBin][htest->FindBin(pfpt_1)];
      //   if(radius == 3) wght = R3nCorr[cBin][htest->FindBin(pfpt_1)];
      //   if(radius == 4) wght = R4nCorr[cBin][htest->FindBin(pfpt_1)];    
      // }
      Float_t Sumcand = chSum_1 + phSum_1 + neSum_1 + muSum_1;

      if(jet55_1 == 1 && jet65_1 == 0 && jet80_1 == 0 ) {
    
	hData_unmatched_Jet55_noCut->Fill(pfpt_1, Jet55_prescl*wght);
	hpbpb_Data_Jet55_noCut[cBin]->Fill(pfpt_1, Jet55_prescl*wght);
      
      }

      if(jet65_1 == 1 && jet80_1 == 0 ) {

	hData_unmatched_Jet65_noCut->Fill(pfpt_1, wght);
	hpbpb_Data_Jet65_noCut[cBin]->Fill(pfpt_1, wght);
      
      }

      if(jet80_1 == 1) {
    
	hData_unmatched_Jet80_noCut->Fill(pfpt_1, wght);
	hpbpb_Data_Jet80_noCut[cBin]->Fill(pfpt_1, wght);

      
      }
    
    }// data ntuple loop
  
  }// only for different Raghav's ntuple 
#endif
  if(Short==1){
   entries=TestEntries;
  } else {  
    entries = MC_matched->GetEntries();
  }
  //entries = 1000;
  // MC loop
  cout<<" looking at matched MC ntuple "<<endl;
  for(long nentry = 0; nentry < entries; ++nentry){

    if(nentry%100000 == 0) cout<<nentry<<"/"<<entries<<endl;
    MC_matched->GetEntry(nentry);
    
    Int_t cBin = findBin(hiBin_2);
    if(cBin == -1 || cBin >= nbins_cent) continue;    
    
    for(int g = 0; g<npf_2; ++g){
    
      Float_t Sumcand = chSum_2[g] + phSum_2[g] + neSum_2[g] + muSum_2[g];
      int refid = -1; 
      
      if(pfpt_2[g] > 2 * pthat_2) continue;
      refid = pfrefidx_2[g];
      if(subid_2[refid] != 0 || fabs(refdrjt_2[refid]) > kdelrcut) continue;
      if(refid < 0) continue;
      
      if(isSymm && TMath::Abs(eta_2[g]) > (Float_t)etaHigh/10) continue;       
      if(!isSymm && (TMath::Abs(eta_2[g]) < (Float_t)etaLow/10 || TMath::Abs(eta_2[g]) > (Float_t)etaHigh/10)) continue;

      int ptbin=findPtBin(pfpt_2[g]);
      int refptbin=findPtBin(pfrefpt_2[refid]);
      if(ptbin==-1){ continue; }
      if(isCaloMatch_2[g] == 1){
//	  hpbpb_gen[cBin]->Fill(pfrefpt_2[refid], weight);
//	  hpbpb_reco[cBin]->Fill(pfpt_2[g], weight);
//	  hpbpb_matrix[cBin]->Fill(pfrefpt_2[refid], pfpt_2[g], weight);	
//	hpbpb_MC_noCut[cBin]->Fill(pfrefpt_2[refid], weight);
	if(jet55_2 == 1 && jet65_2==0 && jet80_2 == 0){
	 if(calopt_2[g]/pfpt_2[g] > 0.5 && calopt_2[g]/pfpt_2[g] <= 0.85 && eMax_2[g]/Sumcand < ((Float_t)18/7 *(Float_t)calopt_2[g]/pfpt_2[g] - (Float_t)9/7)) {
      hMC_eMaxSumcand_calopfpt_ptselection_jet55[ptbin]->Fill((trMax_2[g]/pfpt_2[g]),(neSum_2[g]+phSum_2[g])/Sumcand);
      if(ptbin==refptbin){
        hMC_eMaxSumcand_calopfpt_refptselection_jet55[ptbin]->Fill((trMax_2[g]/pfpt_2[g]),(neSum_2[g]+phSum_2[g])/Sumcand);
      }
    }
    if(calopt_2[g]/pfpt_2[g] > 0.85){
      hMC_eMaxSumcand_calopfpt_ptselection_jet55[ptbin]->Fill((trMax_2[g]/pfpt_2[g]),(neSum_2[g]+phSum_2[g])/Sumcand);
      if(ptbin==refptbin){
        hMC_eMaxSumcand_calopfpt_refptselection_jet55[ptbin]->Fill((trMax_2[g]/pfpt_2[g]),(neSum_2[g]+phSum_2[g])/Sumcand);
      }      
    }
 	if(calopt_2[g]/pfpt_2[g] <= 0.5 && eMax_2[g]/Sumcand < 0.05) {
      hMC_eMaxSumcand_calopfpt_ptselection_jet55[ptbin]->Fill((trMax_2[g]/pfpt_2[g]),(neSum_2[g]+phSum_2[g])/Sumcand);
      if(ptbin==refptbin){
        hMC_eMaxSumcand_calopfpt_refptselection_jet55[ptbin]->Fill((trMax_2[g]/pfpt_2[g]),(neSum_2[g]+phSum_2[g])/Sumcand);
      }
    }   
//	  hMC_Jet55_noCut->Fill(pfrefpt_2[refid], weight);
//	  hpbpb_MC_Jet55_noCut[cBin]->Fill(pfrefpt_2[refid],weight);
	}
	if(jet65_2 == 1 && jet80_2 == 0){
	 if(calopt_2[g]/pfpt_2[g] > 0.5 && calopt_2[g]/pfpt_2[g] <= 0.85 && eMax_2[g]/Sumcand < ((Float_t)18/7 *(Float_t)calopt_2[g]/pfpt_2[g] - (Float_t)9/7)) {
      hMC_eMaxSumcand_calopfpt_ptselection_jet65[ptbin]->Fill((trMax_2[g]/pfpt_2[g]),(neSum_2[g]+phSum_2[g])/Sumcand);
      if(ptbin==refptbin){
        hMC_eMaxSumcand_calopfpt_refptselection_jet65[ptbin]->Fill((trMax_2[g]/pfpt_2[g]),(neSum_2[g]+phSum_2[g])/Sumcand);
      }
    }
    if(calopt_2[g]/pfpt_2[g] > 0.85){
      hMC_eMaxSumcand_calopfpt_ptselection_jet65[ptbin]->Fill((trMax_2[g]/pfpt_2[g]),(neSum_2[g]+phSum_2[g])/Sumcand);
      if(ptbin==refptbin){
        hMC_eMaxSumcand_calopfpt_refptselection_jet65[ptbin]->Fill((trMax_2[g]/pfpt_2[g]),(neSum_2[g]+phSum_2[g])/Sumcand);
      }      
    }
 	if(calopt_2[g]/pfpt_2[g] <= 0.5 && eMax_2[g]/Sumcand < 0.05) {
      hMC_eMaxSumcand_calopfpt_ptselection_jet65[ptbin]->Fill((trMax_2[g]/pfpt_2[g]),(neSum_2[g]+phSum_2[g])/Sumcand);
      if(ptbin==refptbin){
        hMC_eMaxSumcand_calopfpt_refptselection_jet65[ptbin]->Fill((trMax_2[g]/pfpt_2[g]),(neSum_2[g]+phSum_2[g])/Sumcand);
      }
    }   
	}
    
	if(jet80_2 == 1){
	 if(calopt_2[g]/pfpt_2[g] > 0.5 && calopt_2[g]/pfpt_2[g] <= 0.85 && eMax_2[g]/Sumcand < ((Float_t)18/7 *(Float_t)calopt_2[g]/pfpt_2[g] - (Float_t)9/7)) {
      hMC_eMaxSumcand_calopfpt_ptselection_jet80[ptbin]->Fill((trMax_2[g]/pfpt_2[g]),(neSum_2[g]+phSum_2[g])/Sumcand);
      if(ptbin==refptbin){
        hMC_eMaxSumcand_calopfpt_refptselection_jet80[ptbin]->Fill((trMax_2[g]/pfpt_2[g]),(neSum_2[g]+phSum_2[g])/Sumcand);
      }
    }
    if(calopt_2[g]/pfpt_2[g] > 0.85){
      hMC_eMaxSumcand_calopfpt_ptselection_jet80[ptbin]->Fill((trMax_2[g]/pfpt_2[g]),(neSum_2[g]+phSum_2[g])/Sumcand);
      if(ptbin==refptbin){
        hMC_eMaxSumcand_calopfpt_refptselection_jet80[ptbin]->Fill((trMax_2[g]/pfpt_2[g]),(neSum_2[g]+phSum_2[g])/Sumcand);
      }      
    }
 	if(calopt_2[g]/pfpt_2[g] <= 0.5 && eMax_2[g]/Sumcand < 0.05) {
      hMC_eMaxSumcand_calopfpt_ptselection_jet80[ptbin]->Fill((trMax_2[g]/pfpt_2[g]),(neSum_2[g]+phSum_2[g])/Sumcand);
      if(ptbin==refptbin){
        hMC_eMaxSumcand_calopfpt_refptselection_jet80[ptbin]->Fill((trMax_2[g]/pfpt_2[g]),(neSum_2[g]+phSum_2[g])/Sumcand);
      }
    }   
	}// jet 80 selection
    
      }// matched jets 

      if(isCaloMatch_2[g] == 0){


//	hpbpb_MC_noCut[cBin]->Fill(pfrefpt_2[refid], weight);

	if(jet55_2 == 1 && jet65_2==0 && jet80_2 == 0){
		if(eMax_2[g]/Sumcand < 0.05 ){
		hMC_unmatch_eMaxSumcand_calopfpt_ptselection_jet55[ptbin]->Fill((trMax_2[g]/pfpt_2[g]),(neSum_2[g]+phSum_2[g])/Sumcand);
      if(ptbin==refptbin){
        hMC_unmatch_eMaxSumcand_calopfpt_refptselection_jet55[ptbin]->Fill((trMax_2[g]/pfpt_2[g]),(neSum_2[g]+phSum_2[g])/Sumcand);
      }
        }
	}   
	if(jet65_2 == 1 && jet80_2 == 0){
	  if(eMax_2[g]/Sumcand < 0.05 ){
		hMC_unmatch_eMaxSumcand_calopfpt_ptselection_jet65[ptbin]->Fill((trMax_2[g]/pfpt_2[g]),(neSum_2[g]+phSum_2[g])/Sumcand);
      if(ptbin==refptbin){
        hMC_unmatch_eMaxSumcand_calopfpt_refptselection_jet65[ptbin]->Fill((trMax_2[g]/pfpt_2[g]),(neSum_2[g]+phSum_2[g])/Sumcand);
      }
      }
	}
	if(jet80_2 == 1){
			if(eMax_2[g]/Sumcand < 0.05 ){
		hMC_unmatch_eMaxSumcand_calopfpt_ptselection_jet80[ptbin]->Fill((trMax_2[g]/pfpt_2[g]),(neSum_2[g]+phSum_2[g])/Sumcand);
      if(ptbin==refptbin){
        hMC_unmatch_eMaxSumcand_calopfpt_refptselection_jet80[ptbin]->Fill((trMax_2[g]/pfpt_2[g]),(neSum_2[g]+phSum_2[g])/Sumcand);
      }      
      }
	}
    
      }//unmatched jets

    }// jet loop
    
  }// mc ntuple loop

#if 0
  if(ntuple == "Raghav"){
    entries = MC_unmatched->GetEntries();
    //entries = 1000;
    // MC loop
    cout<<" looking at unmatched MC ntuple"<<endl;
    for(long nentry = 0; nentry < entries; ++nentry){

      if(nentry%100000 == 0) cout<<nentry<<"/"<<entries<<endl;
      MC_unmatched->GetEntry(nentry);

      if(subid_2 != 0) continue;

      Int_t cBin = findBin(hiBin_2);
      if(cBin == -1 || cBin >= nbins_cent) continue;
    
      Float_t Sumcand = chSum_2 + phSum_2 + neSum_2 + muSum_2;

      if(isSymm && TMath::Abs(eta_2) > (Float_t)etaHigh/10) continue;       
      if(!isSymm && (TMath::Abs(eta_2) < (Float_t)etaLow/10 || TMath::Abs(eta_2) > (Float_t)etaHigh/10)) continue;

      weight = (Float_t)weight * 1e-5;

      if(eMax_2/Sumcand < 0.05  ){
	hpbpb_gen[cBin]->Fill(pfrefpt_2, weight);
	hpbpb_reco[cBin]->Fill(pfpt_2, weight);
	hpbpb_matrix[cBin]->Fill(pfrefpt_2, pfpt_2, weight);

      }

      hpbpb_MC_noCut[cBin]->Fill(pfrefpt_2, weight);

      if(jet55_2 == 1 && jet65_2==0 && jet80_2 == 0){
	hpbpb_MC_Jet55_noCut[cBin]->Fill(pfrefpt_2,weight);
	hMC_unmatched_Jet55_noCut->Fill(pfrefpt_2, weight);
	if(eMax_2/Sumcand < 0.05  ){

	  hpbpb_Jet55_gen[cBin]->Fill(pfrefpt_2, weight);
	  hpbpb_Jet55_GenSmear[cBin]->Fill(pfrefpt_2 + rnd.Gaus(0,1), weight);
	  hpbpb_Jet55_reco[cBin]->Fill(pfpt_2, weight);
	  hpbpb_Jet55_RecoSmear[cBin]->Fill(pfpt_2 + rnd.Gaus(0,1), weight);
	  hpbpb_Jet55_raw[cBin]->Fill(pfrawpt_2, weight);
	  hpbpb_matrix_HLT[cBin]->Fill(pfrefpt_2, pfpt_2, weight);
	  hpbpb_matrix_HLT_GenSmear[cBin]->Fill(pfrefpt_2 + rnd.Gaus(0,1), pfpt_2, weight);
	  hpbpb_matrix_HLT_RecoSmear[cBin]->Fill(pfrefpt_2, pfpt_2 + rnd.Gaus(0,1), weight);
	  hpbpb_matrix_HLT_BothSmear[cBin]->Fill(pfrefpt_2 + rnd.Gaus(0,1), pfpt_2 + rnd.Gaus(0,1), weight);
	  hpbpb_Jet55_gen2pSmear[cBin]->Fill(pfrefpt_2 * (1. + 0.02/nbins_cent*(nbins_cent-cBin)), weight);
	  hpbpb_matrix_HLT_gen2pSmear[cBin]->Fill(pfrefpt_2 * (1. + 0.02/nbins_cent*(nbins_cent-cBin)), pfpt_2, weight);

	  hMC_unmatched_Jet55_CutA->Fill(pfrefpt_2, weight);
	  hpbpb_anaBin_Jet55_gen[cBin]->Fill(pfrefpt_2, weight);
	  hpbpb_anaBin_Jet55_reco[cBin]->Fill(pfpt_2, weight);
	  hpbpb_anaBin_matrix_HLT[cBin]->Fill(pfrefpt_2, pfpt_2, weight);

	}
	else hMC_unmatched_Jet55_CutA_rej->Fill(pfrefpt_2, weight);
      
      }

    
      if(jet65_2 == 1 && jet80_2 == 0){
	hpbpb_MC_Jet65_noCut[cBin]->Fill(pfrefpt_2,weight);
	hMC_unmatched_Jet65_noCut->Fill(pfrefpt_2, weight);
	if(eMax_2/Sumcand < 0.05  ){

	  hpbpb_Jet65_gen[cBin]->Fill(pfrefpt_2, weight);
	  hpbpb_Jet65_GenSmear[cBin]->Fill(pfrefpt_2 + rnd.Gaus(0,1), weight);
	  hpbpb_Jet65_reco[cBin]->Fill(pfpt_2, weight);
	  hpbpb_Jet65_RecoSmear[cBin]->Fill(pfpt_2 + rnd.Gaus(0,1), weight);
	  hpbpb_Jet65_raw[cBin]->Fill(pfrawpt_2, weight);
	  hpbpb_matrix_HLT[cBin]->Fill(pfrefpt_2, pfpt_2, weight);
	  hpbpb_matrix_HLT_GenSmear[cBin]->Fill(pfrefpt_2 + rnd.Gaus(0,1), pfpt_2, weight);
	  hpbpb_matrix_HLT_RecoSmear[cBin]->Fill(pfrefpt_2, pfpt_2 + rnd.Gaus(0,1), weight);
	  hpbpb_matrix_HLT_BothSmear[cBin]->Fill(pfrefpt_2 + rnd.Gaus(0,1), pfpt_2 + rnd.Gaus(0,1), weight);
	  hpbpb_Jet65_gen2pSmear[cBin]->Fill(pfrefpt_2 * (1. + 0.02/nbins_cent*(nbins_cent-cBin)), weight);
	  hpbpb_matrix_HLT_gen2pSmear[cBin]->Fill(pfrefpt_2 * (1. + 0.02/nbins_cent*(nbins_cent-cBin)), pfpt_2, weight);

	  hMC_unmatched_Jet65_CutA->Fill(pfrefpt_2, weight);
	  hpbpb_anaBin_Jet65_gen[cBin]->Fill(pfrefpt_2, weight);
	  hpbpb_anaBin_Jet65_reco[cBin]->Fill(pfpt_2, weight);
	  hpbpb_anaBin_matrix_HLT[cBin]->Fill(pfrefpt_2, pfpt_2, weight);

	}
	else hMC_unmatched_Jet65_CutA_rej->Fill(pfrefpt_2);
      
      }

    
      if(jet80_2 == 1){
	hpbpb_MC_Jet80_noCut[cBin]->Fill(pfrefpt_2,weight);
	hMC_unmatched_Jet80_noCut->Fill(pfrefpt_2, weight);
	if(eMax_2/Sumcand < 0.05  ){

	  hpbpb_Jet80_gen[cBin]->Fill(pfrefpt_2, weight);
	  hpbpb_Jet80_GenSmear[cBin]->Fill(pfrefpt_2 + rnd.Gaus(0,1), weight);
	  hpbpb_Jet80_reco[cBin]->Fill(pfpt_2, weight);
	  hpbpb_Jet80_RecoSmear[cBin]->Fill(pfpt_2 + rnd.Gaus(0,1), weight);
	  hpbpb_Jet80_raw[cBin]->Fill(pfrawpt_2, weight);
	  hpbpb_matrix_HLT[cBin]->Fill(pfrefpt_2, pfpt_2, weight);
	  hpbpb_matrix_HLT_GenSmear[cBin]->Fill(pfrefpt_2 + rnd.Gaus(0,1), pfpt_2, weight);
	  hpbpb_matrix_HLT_RecoSmear[cBin]->Fill(pfrefpt_2, pfpt_2 + rnd.Gaus(0,1), weight);
	  hpbpb_matrix_HLT_BothSmear[cBin]->Fill(pfrefpt_2 + rnd.Gaus(0,1), pfpt_2 + rnd.Gaus(0,1), weight);
	  hpbpb_Jet80_gen2pSmear[cBin]->Fill(pfrefpt_2 * (1. + 0.02/nbins_cent*(nbins_cent-cBin)), weight);
	  hpbpb_matrix_HLT_gen2pSmear[cBin]->Fill(pfrefpt_2 * (1. + 0.02/nbins_cent*(nbins_cent-cBin)), pfpt_2, weight);

	  hMC_unmatched_Jet80_CutA->Fill(pfrefpt_2, weight);
	  hpbpb_anaBin_Jet80_gen[cBin]->Fill(pfrefpt_2, weight);
	  hpbpb_anaBin_Jet80_reco[cBin]->Fill(pfpt_2, weight);
	  hpbpb_anaBin_matrix_HLT[cBin]->Fill(pfrefpt_2, pfpt_2, weight);

	}else hMC_unmatched_Jet80_CutA_rej->Fill(pfrefpt_2, weight);
      
      }
    
    
    }// mc unmatched  ntuple loop

  }
#endif

  TFile fout(Form("%s_TTree_PbPb_Data_MC_JetID_CutA_finebins_%s_R0p%d_nePlusphOverSumCand.root",ntuple,etaWidth,radius),"RECREATE");
//  TFile fout(Form("%s_TTree_PbPb_Data_MC_subid0_JetID_CutA_trMaxOverjtptgt1percent_finebins_%s_R0p%d.root",ntuple,etaWidth,radius),"RECREATE");
  fout.cd();
  

//    hpbpb_MC_noCut[i]->Write();

  for(int a = 0;a<ptSelection; ++a) {
    hData_eMaxSumcand_calopfpt_ptselection_jet55[a]->Add(hData_unmatch_eMaxSumcand_calopfpt_ptselection_jet55[a]);
    hMC_eMaxSumcand_calopfpt_ptselection_jet55[a]->Add(hMC_unmatch_eMaxSumcand_calopfpt_ptselection_jet55[a]);
    hMC_eMaxSumcand_calopfpt_refptselection_jet55[a]->Add(hMC_unmatch_eMaxSumcand_calopfpt_refptselection_jet55[a]);
    hData_eMaxSumcand_calopfpt_ptselection_jet65[a]->Add(hData_unmatch_eMaxSumcand_calopfpt_ptselection_jet65[a]);
    hMC_eMaxSumcand_calopfpt_ptselection_jet65[a]->Add(hMC_unmatch_eMaxSumcand_calopfpt_ptselection_jet65[a]);
    hMC_eMaxSumcand_calopfpt_refptselection_jet65[a]->Add(hMC_unmatch_eMaxSumcand_calopfpt_refptselection_jet65[a]);
    hData_eMaxSumcand_calopfpt_ptselection_jet80[a]->Add(hData_unmatch_eMaxSumcand_calopfpt_ptselection_jet80[a]);
    hMC_eMaxSumcand_calopfpt_ptselection_jet80[a]->Add(hMC_unmatch_eMaxSumcand_calopfpt_ptselection_jet80[a]);
    hMC_eMaxSumcand_calopfpt_refptselection_jet80[a]->Add(hMC_unmatch_eMaxSumcand_calopfpt_refptselection_jet80[a]);  
    hData_eMaxSumcand_calopfpt_ptselection_jet55[a]->Write();
    hMC_eMaxSumcand_calopfpt_ptselection_jet55[a]->Write();
    hMC_eMaxSumcand_calopfpt_refptselection_jet55[a]->Write();
    hData_eMaxSumcand_calopfpt_ptselection_jet65[a]->Write();
    hMC_eMaxSumcand_calopfpt_ptselection_jet65[a]->Write();
    hMC_eMaxSumcand_calopfpt_refptselection_jet65[a]->Write();
    hData_eMaxSumcand_calopfpt_ptselection_jet80[a]->Write();
    hMC_eMaxSumcand_calopfpt_ptselection_jet80[a]->Write();
    hMC_eMaxSumcand_calopfpt_refptselection_jet80[a]->Write();
     
   }
   for(int a = 0;a<ptSelection; ++a) {
    ceMaxSumcand_jet55[a] = new TCanvas(Form("ceMaxSumcand_jet55_%d",a),"",1000,800);
    ceMaxSumcand_jet55[a]->Divide(3,1);
    ceMaxSumcand_jet55[a]->cd(1);
    ceMaxSumcand_jet55[a]->cd(1)->SetLogz();
    hData_eMaxSumcand_calopfpt_ptselection_jet55[a]->SetXTitle("trMax/Jet pT");
    hData_eMaxSumcand_calopfpt_ptselection_jet55[a]->SetYTitle("(neSum+phSum)/(chSum+phSum+neSum+muSum)");
    hData_eMaxSumcand_calopfpt_ptselection_jet55[a]->Draw("colz");
    drawText(Form("%d < pfpt < %d", ptBoundary[a], ptBoundary[a+1]),0.2,0.7,14);
    drawText("Data - jet55 !jet65 !jet80",0.25,0.8,14);

    
    ceMaxSumcand_jet55[a]->cd(2);
    ceMaxSumcand_jet55[a]->cd(2)->SetLogz();
    hMC_eMaxSumcand_calopfpt_ptselection_jet55[a]->SetXTitle("trMax/Jet pT");
    hMC_eMaxSumcand_calopfpt_ptselection_jet55[a]->SetYTitle("(neSum+phSum)/(chSum+phSum+neSum+muSum)");
    hMC_eMaxSumcand_calopfpt_ptselection_jet55[a]->Draw("colz");
    drawText(Form("%d < pfpt < %d", ptBoundary[a], ptBoundary[a+1]),0.2,0.7,14);
    drawText("MC - jet55 !jet65 !jet80",0.25,0.8,14);


    ceMaxSumcand_jet55[a]->cd(3);
    ceMaxSumcand_jet55[a]->cd(3)->SetLogz();
    hMC_eMaxSumcand_calopfpt_refptselection_jet55[a]->SetXTitle("trMax/Jet pT");
    hMC_eMaxSumcand_calopfpt_refptselection_jet55[a]->SetYTitle("(neSum+phSum)/(chSum+phSum+neSum+muSum)");
    hMC_eMaxSumcand_calopfpt_refptselection_jet55[a]->Draw("colz");
    drawText(Form("%d < pfpt, refpt < %d", ptBoundary[a], ptBoundary[a+1]),0.2,0.7,14);
    drawText("MC - jet55 !jet65 !jet80",0.25,0.8,14);


    ceMaxSumcand_jet55[a]->SaveAs(Form("Plots_nePlusphOverSumCand/nePlusphSumOverSumCand_trMaxOverchMax_PbPb_jet55_fullstat_R0p%d_%d_ptrange_%d.pdf",radius, ptBoundary[a], ptBoundary[a+1]),"RECREATE");


    ceMaxSumcand_jet65[a] = new TCanvas(Form("ceMaxSumcand_jet65_%d",a),"",1000,800);
    ceMaxSumcand_jet65[a]->Divide(3,1);
    ceMaxSumcand_jet65[a]->cd(1);
    ceMaxSumcand_jet65[a]->cd(1)->SetLogz();
    hData_eMaxSumcand_calopfpt_ptselection_jet65[a]->SetXTitle("trMax/Jet pT");
    hData_eMaxSumcand_calopfpt_ptselection_jet65[a]->SetYTitle("(neSum+phSum)/(chSum+phSum+neSum+muSum)");
    hData_eMaxSumcand_calopfpt_ptselection_jet65[a]->Draw("colz");
    drawText(Form("%d < pfpt < %d", ptBoundary[a], ptBoundary[a+1]),0.2,0.7,14);
    drawText("Data - jet65 !jet80",0.25,0.8,14);

    
    ceMaxSumcand_jet65[a]->cd(2);
    ceMaxSumcand_jet65[a]->cd(2)->SetLogz();
    hMC_eMaxSumcand_calopfpt_ptselection_jet65[a]->SetXTitle("trMax/Jet pT");
    hMC_eMaxSumcand_calopfpt_ptselection_jet65[a]->SetYTitle("(neSum+phSum)/(chSum+phSum+neSum+muSum)");
    hMC_eMaxSumcand_calopfpt_ptselection_jet65[a]->Draw("colz");
    drawText(Form("%d < pfpt < %d", ptBoundary[a], ptBoundary[a+1]),0.2,0.7,14);
    drawText("MC - jet65 !jet80",0.25,0.8,14);


    ceMaxSumcand_jet65[a]->cd(3);
    ceMaxSumcand_jet65[a]->cd(3)->SetLogz();
    hMC_eMaxSumcand_calopfpt_refptselection_jet65[a]->SetXTitle("trMax/Jet pT");
    hMC_eMaxSumcand_calopfpt_refptselection_jet65[a]->SetYTitle("(neSum+phSum)/(chSum+phSum+neSum+muSum)");
    hMC_eMaxSumcand_calopfpt_refptselection_jet65[a]->Draw("colz");
    drawText(Form("%d < pfpt, refpt < %d", ptBoundary[a], ptBoundary[a+1]),0.2,0.7,14);
    drawText("MC - jet65 !jet80",0.25,0.8,14);


    ceMaxSumcand_jet65[a]->SaveAs(Form("Plots_nePlusphOverSumCand/nePlusphSumOverSumCand_trMaxOverchMax_PbPb_jet65_fullstat_R0p%d_%d_ptrange_%d.pdf",radius, ptBoundary[a], ptBoundary[a+1]),"RECREATE");

    ceMaxSumcand_jet80[a] = new TCanvas(Form("ceMaxSumcand_jet80_%d",a),"",1000,800);
    ceMaxSumcand_jet80[a]->Divide(3,1);
    ceMaxSumcand_jet80[a]->cd(1);
    ceMaxSumcand_jet80[a]->cd(1)->SetLogz();
    hData_eMaxSumcand_calopfpt_ptselection_jet80[a]->SetXTitle("trMax/Jet pT");
    hData_eMaxSumcand_calopfpt_ptselection_jet80[a]->SetYTitle("(neSum+phSum)/(chSum+phSum+neSum+muSum)");
    hData_eMaxSumcand_calopfpt_ptselection_jet80[a]->Draw("colz");
    drawText(Form("%d < pfpt < %d", ptBoundary[a], ptBoundary[a+1]),0.2,0.7,14);
    drawText("Data - jet80",0.25,0.8,14);

    
    ceMaxSumcand_jet80[a]->cd(2);
    ceMaxSumcand_jet80[a]->cd(2)->SetLogz();
    hMC_eMaxSumcand_calopfpt_ptselection_jet80[a]->SetXTitle("trMax/Jet pT");
    hMC_eMaxSumcand_calopfpt_ptselection_jet80[a]->SetYTitle("(neSum+phSum)/(chSum+phSum+neSum+muSum)");
    hMC_eMaxSumcand_calopfpt_ptselection_jet80[a]->Draw("colz");
    drawText(Form("%d < pfpt < %d", ptBoundary[a], ptBoundary[a+1]),0.2,0.7,14);
    drawText("MC - jet80",0.25,0.8,14);


    ceMaxSumcand_jet80[a]->cd(3);
    ceMaxSumcand_jet80[a]->cd(3)->SetLogz();
    hMC_eMaxSumcand_calopfpt_refptselection_jet80[a]->SetXTitle("trMax/Jet pT");
    hMC_eMaxSumcand_calopfpt_refptselection_jet80[a]->SetYTitle("(neSum+phSum)/(chSum+phSum+neSum+muSum)");
    hMC_eMaxSumcand_calopfpt_refptselection_jet80[a]->Draw("colz");
    drawText(Form("%d < pfpt, refpt < %d", ptBoundary[a], ptBoundary[a+1]),0.2,0.7,14);
    drawText("MC - jet80",0.25,0.8,14);


    ceMaxSumcand_jet80[a]->SaveAs(Form("Plots_nePlusphOverSumCand_trkMaxJtPt/nePlusphSumOverSumCand_trMaxOverJtpt_PbPb_jet80_fullstat_R0p%d_%d_ptrange_%d.pdf",radius, ptBoundary[a], ptBoundary[a+1]),"RECREATE");
    
  }

  
}
