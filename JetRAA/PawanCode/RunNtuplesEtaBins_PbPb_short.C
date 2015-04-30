#include <TF1.h>
#include <TProfile.h>
#include <TChain.h>
#include <TTree.h>
#include <TEventList.h>
#include <TSystem.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TFile.h>
#include <TStyle.h>
#include <TStopwatch.h>
#include <TRandom3.h>
#include <TCanvas.h>
#include <TMath.h>

#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>
#include <algorithm>

#include "utilities.h"

using namespace std;

#ifdef _MAKECINT_
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#endif

#define pi 3.14159265

void MakeIndHist(TProfile *&/*hist*/);
void MakeIndHist(TH1F *&/*hist*/);

int GetPhiBin(float /*phi*/);
int GetEtaBin(float /*eta*/);
int GetPtBin(float /*pt*/);
int GetCentBin(int /*hiBin*/);
double delphi(double /*phi1*/, double /*phi2*/);
double deltaR(float /*eta1*/, float /*phi1*/,
              float /*eta2*/, float /*phi2*/);

const double ketacut=2.0;
const double kptrawcut =0.0;
const double kptrecocut=1.0;
const double kdelrcut=0.3;

const int ncen=8;
const char *cdir [ncen] = {"05","510","1030","3050","5070","7090","90100","pp"};
const char *ccent[ncen] = {"0-5%","5-10%","10-30%","30-50%","50-70%","70-90%","90-100%","pp"};

//double ptbins[] ={40, 50 ,60 ,70 ,80 ,90 ,100, 110, 120, 130, 140, 160, 200, 250, 300, 400, 548};
double ptbins[] = {
  3, 4, 5, 7, 9, 12, 
  15, 18, 21, 24, 28,
  32, 37, 43, 49, 56,
  64, 74, 84, 97, 114,
  133, 153, 174, 196,
  220, 245, 272, 300, 
  330, 362, 395, 430,
  468, 507, 548 
};
const int nbins = sizeof(ptbins)/sizeof(double) - 1;
// double ptbinsfine[] ={30,35,40, 45,50,55,60,65 ,70,75 ,80,85 ,90,95 ,100,105, 110, 115,120, 125,130,135, 140,150, 160, 170,180, 200,225, 250, 300, 350, 400, 548};
// const int nbinsfine = sizeof(ptbinsfine)/sizeof(double) - 1;

// const double etabins[] = {-2.000, -1.4000, -0.4500, 0.000, 0.4500, 1.400, 2.000};
// const int neta = sizeof(etabins)/sizeof(double) - 1;
const double etabins[] = {0, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0};
const int neta = sizeof(etabins)/sizeof(double) - 1;
const char *seta[neta] = {"|eta|<1.0","1.0<|eta|<1.1","1.1<|eta|<1.2","1.2<|eta|<1.3","1.3<|eta|<1.4","1.4<|eta|<1.5","1.5<|eta|<1.6","1.6<|eta|<1.7","1.7<|eta|<1.8","1.8<|eta|<1.9","1.9<|eta|<2.0"};

const double phibins[] = {-3.141,-2.100,-1.500,-0.800,-0.300,0.300,0.800,1.500,2.100,3.141};
const int nphi = sizeof(phibins)/sizeof(double) - 1;

const int knj=3;
std::string srad[knj] = {"2", "3", "4"};

int rbins=50;
double rbinl=0.0;
double rbinh=2.0;


TStopwatch timer;
int RunNtuplesEtaBins_PbPb_short(std::string kSpecies="PbPb")
{

  timer.Start();

  bool printDebug=false;

  std::string kAlgName="ak";
  if( kSpecies == "PbPb" ) kAlgName="akPu";
  std::string kjetType="PF";

  LoadStyle();
  cout << endl;
  cout <<" Running for " << kSpecies.c_str() << endl;
  cout << " # of ptbins : " << nbins << endl;
//   cout << " # of fine ptbins : " << nbinsfine << endl;
  //return 0;

  int iSave=1;

  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();

  TFile *fData=0, *fMC=0;
  TTree *Data_matched=0,*Data_unmatched=0;
  TTree *MC_matched=0,*MC_unmatched=0;

  Float_t Jet55_prescl = 2.0475;
  Float_t Jet40_prescl = 9.275;
  int myeta_1=12;
  int myeta_2=12;

  if( kSpecies == "pp" ) {
    fData = new TFile("/mnt/hadoop/cms/store/user/pawan/ntuples/JetRaa_ak234_pp_Data.root","r");
    fMC   = new TFile("/mnt/hadoop/cms/store/user/pawan/ntuples/JetRaa_ak234_pp_MC.root","r");
  }else{
    fData = new TFile("/mnt/hadoop/cms/store/user/pawan/ntuples/JetRaa_akPu234_PbPb_Data.root","r");
    fMC   = new TFile("/mnt/hadoop/cms/store/user/pawan/ntuples/JetRaa_akPu234_PbPb_MC.root","r");
  }

  TFile *fout = new TFile(Form("Histos/OutputHist_ntuples_short_%s.root",kSpecies.c_str()),"RECREATE");

  for (int nj=0; nj<knj; nj++){
    cout <<"\t  \t " << (kAlgName+srad[nj]+kjetType).c_str() << endl;
    if( kSpecies == "pp" ) {
      Data_matched   = (TTree*)fData->Get(Form("%sJetAnalyzer/matchedJets",(kAlgName+srad[nj]).c_str()));
      Data_unmatched = (TTree*)fData->Get(Form("%sJetAnalyzer/unmatched%sJets",(kAlgName+srad[nj]).c_str(),kjetType.c_str()));
      
      MC_matched   = (TTree*)fMC->Get(Form("%sJetAnalyzer/matchedJets",(kAlgName+srad[nj]).c_str()));
      MC_unmatched = (TTree*)fMC->Get(Form("%sJetAnalyzer/unmatched%sJets",(kAlgName+srad[nj]).c_str(),kjetType.c_str()));
    }else{
      Data_matched   = (TTree*)fData->Get(Form("%sJetAnalyzer/matchedJets",(kAlgName+srad[nj]).c_str()));
      Data_unmatched = (TTree*)fData->Get(Form("%sJetAnalyzer/unmatched%sJets",(kAlgName+srad[nj]).c_str(),kjetType.c_str()));
      
      MC_matched   = (TTree*)fMC->Get(Form("%sJetAnalyzer/matchedJets",(kAlgName+srad[nj]).c_str()));
      MC_unmatched = (TTree*)fMC->Get(Form("%sJetAnalyzer/unmatched%sJets",(kAlgName+srad[nj]).c_str(),kjetType.c_str()));
    }

    cout <<" Data m  : " << Data_matched->GetEntries() << " "
	 <<" Data um : " << Data_unmatched->GetEntries() <<" "
	 <<" MC   m  : " << MC_matched->GetEntries() << " "
	 <<" MC   um : " << MC_unmatched->GetEntries() <<endl;


    // 1 - Data, 2 - MC
    Float_t pfpt_1, pfpt_2;
    Float_t pfeta_1, pfeta_2;
    Float_t pfphi_1, pfphi_2;
    Float_t pfrawpt_1, pfrawpt_2;
    Float_t refpt_2, refdrjt_2;
    Float_t refeta_2, refphi_2;
    Float_t calopt_1, calopt_2;
    Float_t chMax_1, chMax_2;
    Float_t phMax_1, phMax_2;
    Float_t neMax_1, neMax_2;
    Float_t muMax_1, muMax_2;
    Float_t eMax_1, eMax_2;
    Float_t chSum_1, chSum_2;
    Float_t phSum_1, phSum_2;
    Float_t neSum_1, neSum_2;
    Float_t muSum_1, muSum_2;
    Float_t eSum_1, eSum_2;
    Int_t jet40_1, jet60_1, jet80_1;
    Int_t jet40_p_1, jet60_p_1, jet80_p_1;
    Int_t jet40_2, jet60_2, jet80_2;
    Int_t jet40_p_2, jet60_p_2, jet80_p_2;
    Int_t jet55_1, jet65_1;
    Int_t jet55_p_1, jet65_p_1;
    Int_t jet55_2, jet65_2;
    Int_t jet55_p_2, jet65_p_2;

    Int_t hiBin_1, hiBin_2;
    Float_t weight_2, pthat_2;
    int subid_2;

    Data_matched->SetBranchAddress("calopt",&calopt_1);
    Data_matched->SetBranchAddress("pfpt",&pfpt_1);
    Data_matched->SetBranchAddress("pfeta",&pfeta_1);
    Data_matched->SetBranchAddress("pfphi",&pfphi_1);
    Data_matched->SetBranchAddress("pfrawpt",&pfrawpt_1);
    Data_matched->SetBranchAddress("eMax",&eMax_1);
    Data_matched->SetBranchAddress("phMax",&phMax_1);
    Data_matched->SetBranchAddress("muMax",&muMax_1);
    Data_matched->SetBranchAddress("neMax",&neMax_1);
    Data_matched->SetBranchAddress("chMax",&chMax_1);
    Data_matched->SetBranchAddress("chSum",&chSum_1);
    Data_matched->SetBranchAddress("phSum",&phSum_1);
    Data_matched->SetBranchAddress("neSum",&neSum_1);
    Data_matched->SetBranchAddress("muSum",&muSum_1);
    Data_matched->SetBranchAddress("eSum",&eSum_1);
    if( kSpecies == "pp" ){
      Data_matched->SetBranchAddress("jet40",&jet40_1);
      Data_matched->SetBranchAddress("jet60",&jet60_1);
      Data_matched->SetBranchAddress("jet80",&jet80_1);
      Data_matched->SetBranchAddress("jet40_prescl",&jet40_p_1);
      Data_matched->SetBranchAddress("jet60_prescl",&jet60_p_1);
      Data_matched->SetBranchAddress("jet80_prescl",&jet80_p_1);
    }else{
      Data_matched->SetBranchAddress("hiBin",&hiBin_1);
      Data_matched->SetBranchAddress("jet55",&jet55_1);
      Data_matched->SetBranchAddress("jet65",&jet65_1);
      Data_matched->SetBranchAddress("jet80",&jet80_1);
      Data_matched->SetBranchAddress("jet55_prescl",&jet55_p_1);
      Data_matched->SetBranchAddress("jet65_prescl",&jet65_p_1);
      Data_matched->SetBranchAddress("jet80_prescl",&jet80_p_1);
    }

    Data_unmatched->SetBranchAddress("pfpt",&pfpt_1);
    Data_unmatched->SetBranchAddress("pfeta",&pfeta_1);
    Data_unmatched->SetBranchAddress("pfphi",&pfphi_1);
    Data_unmatched->SetBranchAddress("pfrawpt",&pfrawpt_1);
    Data_unmatched->SetBranchAddress("eMax",&eMax_1);
    Data_unmatched->SetBranchAddress("phMax",&phMax_1);
    Data_unmatched->SetBranchAddress("muMax",&muMax_1);
    Data_unmatched->SetBranchAddress("neMax",&neMax_1);
    Data_unmatched->SetBranchAddress("chMax",&chMax_1);
    Data_unmatched->SetBranchAddress("chSum",&chSum_1);
    Data_unmatched->SetBranchAddress("phSum",&phSum_1);
    Data_unmatched->SetBranchAddress("neSum",&neSum_1);
    Data_unmatched->SetBranchAddress("muSum",&muSum_1);
    Data_unmatched->SetBranchAddress("eSum",&eSum_1);
    if( kSpecies == "pp" ){
      Data_unmatched->SetBranchAddress("jet40",&jet40_1);
      Data_unmatched->SetBranchAddress("jet60",&jet60_1);
      Data_unmatched->SetBranchAddress("jet80",&jet80_1);
      Data_unmatched->SetBranchAddress("jet40_prescl",&jet40_p_1);
      Data_unmatched->SetBranchAddress("jet60_prescl",&jet60_p_1);
      Data_unmatched->SetBranchAddress("jet80_prescl",&jet80_p_1);
    }else{
      Data_unmatched->SetBranchAddress("hiBin",&hiBin_1);
      Data_unmatched->SetBranchAddress("jet55",&jet55_1);
      Data_unmatched->SetBranchAddress("jet65",&jet65_1);
      Data_unmatched->SetBranchAddress("jet80",&jet80_1);
      Data_unmatched->SetBranchAddress("jet55_prescl",&jet55_p_1);
      Data_unmatched->SetBranchAddress("jet65_prescl",&jet65_p_1);
      Data_unmatched->SetBranchAddress("jet80_prescl",&jet80_p_1);
    }

    MC_matched->SetBranchAddress("calopt",&calopt_2);
    MC_matched->SetBranchAddress("pfpt",&pfpt_2);
    MC_matched->SetBranchAddress("pfeta",&pfeta_2);
    MC_matched->SetBranchAddress("pfphi",&pfphi_2);
    MC_matched->SetBranchAddress("pfrawpt",&pfrawpt_2);
    MC_matched->SetBranchAddress("eMax",&eMax_2);
    MC_matched->SetBranchAddress("phMax",&phMax_2);
    MC_matched->SetBranchAddress("muMax",&muMax_2);
    MC_matched->SetBranchAddress("neMax",&neMax_2);
    MC_matched->SetBranchAddress("chMax",&chMax_2);
    MC_matched->SetBranchAddress("chSum",&chSum_2);
    MC_matched->SetBranchAddress("phSum",&phSum_2);
    MC_matched->SetBranchAddress("neSum",&neSum_2);
    MC_matched->SetBranchAddress("muSum",&muSum_2);
    MC_matched->SetBranchAddress("eSum",&eSum_2);

    MC_matched->SetBranchAddress("weight",&weight_2);
    MC_matched->SetBranchAddress("pthat",&pthat_2);
    MC_matched->SetBranchAddress("subid",&subid_2);
    MC_matched->SetBranchAddress("refpt",&refpt_2);
    MC_matched->SetBranchAddress("refdrjt",&refdrjt_2);
    MC_matched->SetBranchAddress("refeta",&refeta_2);
    MC_matched->SetBranchAddress("refphi",&refphi_2);
    if( kSpecies == "pp" ){
      MC_matched->SetBranchAddress("jet40",&jet40_2);
      MC_matched->SetBranchAddress("jet60",&jet60_2);
      MC_matched->SetBranchAddress("jet80",&jet80_2);
      MC_matched->SetBranchAddress("jet40_prescl",&jet40_p_2);
      MC_matched->SetBranchAddress("jet60_prescl",&jet60_p_2);
      MC_matched->SetBranchAddress("jet80_prescl",&jet80_p_2);
    }else{
      MC_matched->SetBranchAddress("hiBin",&hiBin_2);
      MC_matched->SetBranchAddress("jet55",&jet55_2);
      MC_matched->SetBranchAddress("jet65",&jet65_2);
      MC_matched->SetBranchAddress("jet80",&jet80_2);
      MC_matched->SetBranchAddress("jet55_prescl",&jet55_p_2);
      MC_matched->SetBranchAddress("jet65_prescl",&jet65_p_2);
      MC_matched->SetBranchAddress("jet80_prescl",&jet80_p_2);
    }

    MC_unmatched->SetBranchAddress("pfpt",&pfpt_2);
    MC_unmatched->SetBranchAddress("pfeta",&pfeta_2);
    MC_unmatched->SetBranchAddress("pfphi",&pfphi_2);
    MC_unmatched->SetBranchAddress("pfrawpt",&pfrawpt_2);
    MC_unmatched->SetBranchAddress("eMax",&eMax_2);
    MC_unmatched->SetBranchAddress("phMax",&phMax_2);
    MC_unmatched->SetBranchAddress("muMax",&muMax_2);
    MC_unmatched->SetBranchAddress("neMax",&neMax_2);
    MC_unmatched->SetBranchAddress("chMax",&chMax_2);
    MC_unmatched->SetBranchAddress("chSum",&chSum_2);
    MC_unmatched->SetBranchAddress("phSum",&phSum_2);
    MC_unmatched->SetBranchAddress("neSum",&neSum_2);
    MC_unmatched->SetBranchAddress("muSum",&muSum_2);
    MC_unmatched->SetBranchAddress("eSum",&eSum_2);

    MC_unmatched->SetBranchAddress("weight",&weight_2);
    MC_unmatched->SetBranchAddress("pthat",&pthat_2);
    MC_unmatched->SetBranchAddress("subid",&subid_2);
    MC_unmatched->SetBranchAddress("refpt",&refpt_2);
    MC_unmatched->SetBranchAddress("refeta",&refeta_2);
    MC_unmatched->SetBranchAddress("refphi",&refphi_2);
    MC_unmatched->SetBranchAddress("refdrjt",&refdrjt_2);
    if( kSpecies == "pp" ){
      MC_unmatched->SetBranchAddress("jet40",&jet40_2);
      MC_unmatched->SetBranchAddress("jet60",&jet60_2);
      MC_unmatched->SetBranchAddress("jet80",&jet80_2);
      MC_unmatched->SetBranchAddress("jet40_prescl",&jet40_p_2);
      MC_unmatched->SetBranchAddress("jet60_prescl",&jet60_p_2);
      MC_unmatched->SetBranchAddress("jet80_prescl",&jet80_p_2);
    }else{
      MC_unmatched->SetBranchAddress("hiBin",&hiBin_2);
      MC_unmatched->SetBranchAddress("jet55",&jet55_2);
      MC_unmatched->SetBranchAddress("jet65",&jet65_2);
      MC_unmatched->SetBranchAddress("jet80",&jet80_2);
      MC_unmatched->SetBranchAddress("jet55_prescl",&jet55_p_2);
      MC_unmatched->SetBranchAddress("jet65_prescl",&jet65_p_2);
      MC_unmatched->SetBranchAddress("jet80_prescl",&jet80_p_2);
    }

    //fout->mkdir(Form("%sJetAnalyzer",(kAlgName+srad[nj]+kjetType).c_str()));
    //fout->cd(Form("%sJetAnalyzer",(kAlgName+srad[nj]+kjetType).c_str()));

    //! JEC
    TH1F *hrescrpt[2][ncen][nbins], *hrescrpt_m[2][ncen][nbins], *hrescrpt_um[2][ncen][nbins];
    
    //! Efficiency & Fake
    TH1F *hPtAll [ncen], *hPtEff [2][ncen];
    TH1F *hPtAll_etabin[ncen][neta], *hPtEff_etabin[2][ncen][neta];    
    TH1F *hEtaAll[ncen], *hEtaEff[2][ncen];
    TH1F *hPhiAll[ncen], *hPhiEff[2][ncen];

    TH1F *hPtFakeAll[ncen], *hPtFake[2][ncen];
    TH1F *hPtFakeAll_etabin[ncen][neta], *hPtFake_etabin[2][ncen][neta];
    TH1F *hEtaFakeAll_20[ncen],*hEtaFakeAll_30[ncen], *hEtaFakeAll_40[ncen],*hEtaFakeAll_45[ncen], *hEtaFakeAll_50[ncen], *hEtaFakeAll_60[ncen];
    TH1F *hPhiFakeAll_20[ncen],*hPhiFakeAll_30[ncen], *hPhiFakeAll_40[ncen],*hPhiFakeAll_45[ncen], *hPhiFakeAll_50[ncen], *hPhiFakeAll_60[ncen];
    TH1F *hEtaFake_20[2][ncen],*hEtaFake_30[2][ncen], *hEtaFake_40[2][ncen],*hEtaFake_45[2][ncen], *hEtaFake_50[2][ncen], *hEtaFake_60[2][ncen];
    TH1F *hPhiFake_20[2][ncen],*hPhiFake_30[2][ncen], *hPhiFake_40[2][ncen],*hPhiFake_45[2][ncen], *hPhiFake_50[2][ncen], *hPhiFake_60[2][ncen];

// i is the with or without jetID loop, NOT the nj loop! 0 == no JetID, 1== JetID for the fakes and efficiency
// for the background plots, i is 0 == Data, 1== MC
    for(int i=0; i<2; i++){
      for(int ic=0; ic<ncen; ic++){
    	if(i==0){
    	  hPtAll[ic] = new TH1F(Form("hPtAll_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic),Form("Denominator pT for algorithm %s %s",(kAlgName+srad[nj]+kjetType).c_str(),ccent[ic]),nbins,ptbins);
    	  hPtAll[ic]->Sumw2();
    	  hEtaAll[ic] = new TH1F(Form("hEtaAll_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic),Form("Denominator eta  for algorithm %s %s",(kAlgName+srad[nj]+kjetType).c_str(),ccent[ic]), 20, -2.0,2.0);
    	  hEtaAll[ic]->Sumw2();
    	  hPhiAll[ic] = new TH1F(Form("hPhiAll_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic),Form("Denominator  phi  for algorithm %s %s",(kAlgName+srad[nj]+kjetType).c_str(),ccent[ic]),18,-pi,pi);
    	  hPhiAll[ic]->Sumw2();

    	  hPtFakeAll[ic] = new TH1F(Form("hPtFakeAll_%s_%d",(kAlgName+srad[nj]+kjetType).c_str(),ic),Form("Fake All Denominator pT for algorithm %s %s",(kAlgName+srad[nj]+kjetType).c_str(),ccent[ic]),nbins,ptbins);
    	  hPtFakeAll[ic]->Sumw2();


           for(int in=0; in<neta; in++){
    	    hPtFakeAll_etabin[ic][in] = new TH1F(Form("hPtFakeAll_etabin%d_%s_%d",in,(kAlgName+srad[nj]+kjetType).c_str(),ic),Form("Fake All Denominator pT for algorithm %s %s, %s",(kAlgName+srad[nj]+kjetType).c_str(),ccent[ic],seta[in]),nbins,ptbins);
    	    hPtFakeAll_etabin[ic][in]->Sumw2();    	  
    	    hPtAll_etabin[ic][in] = new TH1F(Form("hPtAll_etabin%d_%s_%d",in,(kAlgName+srad[nj]+kjetType).c_str(),ic),Form("Denominator pT for algorithm %s %s, %s",(kAlgName+srad[nj]+kjetType).c_str(),ccent[ic],seta[in]),nbins,ptbins);
    	    hPtAll_etabin[ic][in]->Sumw2();
    	  }
    	}
    	hPtEff [i][ic] = new TH1F(Form("hPtEff_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic),Form("Numerator eff pT for algorithm %s %s",(kAlgName+srad[nj]+kjetType).c_str(),ccent[ic]),nbins,ptbins);
    	hPtEff [i][ic]->Sumw2();
    	hEtaEff[i][ic] = new TH1F(Form("hEtaEff_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic),Form("Numerator eff eta  for algorithm %s %s",(kAlgName+srad[nj]+kjetType).c_str(),ccent[ic]), 20, -2.0,2.0);
    	hEtaEff[i][ic]->Sumw2();
    	hPhiEff[i][ic] = new TH1F(Form("hPhiEff_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic),Form("Numerator  eff phi  for algorithm %s %s",(kAlgName+srad[nj]+kjetType).c_str(),ccent[ic]),18,-pi,pi);
    	hPhiEff[i][ic]->Sumw2();
      
    	hPtFake [i][ic] = new TH1F(Form("hPtFake_%s_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic),Form("Numerator fake pT for algorithm %s %s",(kAlgName+srad[nj]+kjetType).c_str(),ccent[ic]),nbins,ptbins);
    	hPtFake [i][ic]->Sumw2();

    	
        for(int in=0; in<neta; in++){
    	   hPtEff_etabin[i][ic][in] = new TH1F(Form("hPtEff_etabin%d_%s_%d_%d",in,(kAlgName+srad[nj]+kjetType).c_str(),i,ic),Form("Numerator eff pT for algorithm %s %s, %s",(kAlgName+srad[nj]+kjetType).c_str(),ccent[ic],seta[in]),nbins,ptbins);
    	   hPtEff_etabin[i][ic][in]->Sumw2();    	   	
     	   hPtFake_etabin[i][ic][in] = new TH1F(Form("hPtFake_etabin%d_%s_%d_%d",in,(kAlgName+srad[nj]+kjetType).c_str(),i,ic),Form("Numerator fake pT for algorithm %s %s, %s",(kAlgName+srad[nj]+kjetType).c_str(),ccent[ic],seta[in]),nbins,ptbins);
    	   hPtFake_etabin[i][ic][in]->Sumw2();
        }



    	
    	for(int ip=0; ip<nbins; ip++){
	  
    	  hrescrpt[i][ic][ip]= new TH1F(Form("hrescrpt_%s_%d_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic,ip),Form("(Reco/Gen) jet p_{T} %s %s %0.0f < p_{T}^{REF} < %0.0f"
    									       ,(kAlgName+srad[nj]+kjetType).c_str(),ccent[ic],ptbins[ip],ptbins[ip+1]),rbins,rbinl,rbinh);
    	  hrescrpt_m[i][ic][ip]= new TH1F(Form("hrescrpt_m_%s_%d_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic,ip),Form("matched (Reco/Gen) jet p_{T} %s %s %0.0f < p_{T}^{REF} < %0.0f"
    									       ,(kAlgName+srad[nj]+kjetType).c_str(),ccent[ic],ptbins[ip],ptbins[ip+1]),rbins,rbinl,rbinh);
    	  hrescrpt_um[i][ic][ip]= new TH1F(Form("hrescrpt_um_%s_%d_%d_%d",(kAlgName+srad[nj]+kjetType).c_str(),i,ic,ip),Form("unmatched (Reco/Gen) jet p_{T} %s %s %0.0f < p_{T}^{REF} < %0.0f"
    									       ,(kAlgName+srad[nj]+kjetType).c_str(),ccent[ic],ptbins[ip],ptbins[ip+1]),rbins,rbinl,rbinh);
	}
      }
    }


    //! CutA
    //! matched   : calopt_1/pfpt_1 > 0.5 && calopt_1/pfpt_1 <= 0.85 && eMax_1/Sumcand < ((Float_t)18./7. *(Float_t)calopt_1/pfpt_1 - (Float_t)9./7.)
    //! unmatched : eMax_1/Sumcand < 0.05
    // data loop
    long entries = Data_matched->GetEntries();
    cout<<"matched Data ntuple: "<<entries<<" entries"<<endl;
    for(long nentry = 0; nentry < entries; nentry++){
      //if(nentry%100000 == 0) cout<<" nentry = "<<nentry<<endl;
      Data_matched->GetEntry(nentry);

      if( printDebug && nentry==1000 )break;
      //if( !(jet40_1==1 || jet60_1==1 || jet80_1==1) )continue;

      Float_t Sumcand = chSum_1 + phSum_1 + neSum_1 + muSum_1;
      Float_t ePFSel  = (18./7.*calopt_1/pfpt_1) - 9./7.;
      bool wJetId=false;
      if((calopt_1/pfpt_1  > 0.50) 
    	 && (calopt_1/pfpt_1 <= 0.85)
    	 && (eMax_1/Sumcand < ePFSel)
    	 //&& (chMax_1/Sumcand >= 0.02)
    	 )wJetId=true;

      if( pfpt_1 < kptrecocut )continue;

      int iCent = -1;
      if( kSpecies == "PbPb")iCent = GetCentBin(hiBin_1);
      else iCent = ncen-1;
      if(iCent<0 || iCent>=ncen)continue;

      int ipt = GetPtBin(pfpt_1);
      if(ipt < 0 || ipt >= nbins)continue;

      float sumPF = (chSum_1 + neSum_1 + phSum_1 + eSum_1 + muSum_1);
      float bkgd  = sumPF - pfrawpt_1;




    }

    // data unmatched loop:
    long duentries = Data_unmatched->GetEntries();
    cout<<"Unmatched Data ntuple: "<<duentries<<" entries"<<endl;
    for(long unentry = 0; unentry < duentries; unentry++ ){
      //if(unentry%100000 == 0) cout<<" unentry = "<<unentry<<endl;
      Data_unmatched->GetEntry(unentry);

      if( printDebug && unentry==1000 )break;
      //if( !(jet40_1==1 || jet60_1==1 || jet80_1==1) )continue;
    
      Float_t Sumcand = chSum_1 + phSum_1 + neSum_1 + muSum_1;
      bool wJetId=false;    
      if( (eMax_1/Sumcand < 0.05)
    	  //&& (chMax_1/Sumcand >= 0.02)
    	  )wJetId=true;

      if( pfpt_1 < kptrecocut )continue;

      int iCent = -1;
      if( kSpecies == "PbPb")iCent = GetCentBin(hiBin_1);
      else iCent = ncen-1;
      if(iCent<0 || iCent>=ncen)continue;

      int ipt = GetPtBin(pfpt_1);
      if(ipt < 0 || ipt >= nbins)continue;

      float sumPF = (chSum_1 + neSum_1 + phSum_1 + eSum_1 + muSum_1);
      float bkgd  = sumPF - pfrawpt_1;

    
      if( wJetId ) {
      }

    }

    //! MC part matched
    long mentries = MC_matched->GetEntries();
    cout<<" looking at matched MC ntuple: "<<mentries<<" entries"<<endl;
    for(long mnentry = 0; mnentry < mentries; mnentry++){
      //if(mnentry%50000 == 0) cout<<" mnentry = "<<mnentry<<endl;
      MC_matched->GetEntry(mnentry);

      if( printDebug && mnentry==1000 )break;

      Float_t Sumcand = chSum_2 + phSum_2 + neSum_2 + muSum_2;
      Float_t ePFSel  = (18./7.*calopt_1/pfpt_1) - 9./7.;
      myeta_2= GetEtaBin(pfeta_2);
//      cout<<"myeta_2: "<<myeta_2<<", pfeta_2: "<<pfeta_2<<endl;
      
      bool wJetId=false;
      if((calopt_2/pfpt_2  > 0.50) 
    	 && (calopt_2/pfpt_2 <= 0.85) 
    	 && (eMax_2/Sumcand < ePFSel)
    	 // && (chMax_2/Sumcand >= 0.02)
    	 )wJetId=true;
      
      if( refpt_2 > 2.*pthat_2 )continue;
      if( pfpt_2 < kptrecocut )continue;

      int iCent = -1;
      if( kSpecies == "PbPb")iCent = GetCentBin(hiBin_2);
      else iCent = ncen-1;
      if(iCent<0 || iCent>=ncen)continue;

      hPtFakeAll[iCent]->Fill(pfpt_2);
      if(fabs(pfeta_2)>=etabins[myeta_2] && fabs(pfeta_2)<etabins[myeta_2+1]){
//         cout<<"going to fill hPtFakeAll_etabin because of selection between: "<<etabins[myeta_2]<<", and "<<etabins[myeta_2+1]<<endl;
          hPtFakeAll_etabin[iCent][myeta_2]->Fill(pfpt_2);
      }
//      cout<<"did fill that histo hPtFakeAll_etabin"<<endl;
      if( refpt_2 < 0 ){
    	hPtFake [0][iCent]->Fill(pfpt_2);
    	if(fabs(pfeta_2)>=etabins[myeta_2] && fabs(pfeta_2)<etabins[myeta_2+1]){
//         cout<<"going to fill hPtFake_etabin noJetID because of selection between: "<<etabins[myeta_2]<<", and "<<etabins[myeta_2+1]<<endl;    	
    	 hPtFake_etabin[0][iCent][myeta_2]->Fill(pfpt_2);
    	}
    	if( wJetId ){
    	   hPtFake [1][iCent]->Fill(pfpt_2);
    	   if(fabs(pfeta_2)>=etabins[myeta_2] && fabs(pfeta_2)<etabins[myeta_2+1]){
 //   	    cout<<"going to fill hPtFake_etabin with jetID because of selection between: "<<etabins[myeta_2]<<", and "<<etabins[myeta_2+1]<<endl;
    	    hPtFake_etabin[1][iCent][myeta_2]->Fill(pfpt_2);
    	   }
    	}
      }

      if( subid_2 == 0 && refpt_2 > 0){
    	hPtAll  [iCent]->Fill(refpt_2,weight_2);
        if(fabs(pfeta_2)>=etabins[myeta_2] && fabs(pfeta_2)<etabins[myeta_2+1]){ 
 //         cout<<"going to fill hPtAll_etabin because of selection between: "<<etabins[myeta_2]<<", and "<<etabins[myeta_2+1]<<endl;   	
    	  hPtAll_etabin[iCent][myeta_2]->Fill(refpt_2,weight_2);
        }
    	hEtaAll [iCent]->Fill(refeta_2,weight_2);
    	hPhiAll [iCent]->Fill(refphi_2,weight_2);

    	if( refdrjt_2 < kdelrcut ){
    	  hPtEff[0][iCent]->Fill(refpt_2 ,weight_2);
    	  if(fabs(pfeta_2)>=etabins[myeta_2] && fabs(pfeta_2)<etabins[myeta_2+1]){
    	       hPtEff_etabin[0][iCent][myeta_2]->Fill(refpt_2 ,weight_2);
          }
    	  hEtaEff[0][iCent]->Fill(refeta_2,weight_2);
    	  hPhiEff[0][iCent]->Fill(refphi_2,weight_2);
    	  if( wJetId ){
    	    hPtEff[1][iCent]->Fill(refpt_2 ,weight_2);
    	    if(fabs(pfeta_2)>=etabins[myeta_2] && fabs(pfeta_2)<etabins[myeta_2+1]){
    	        hPtEff_etabin[1][iCent][myeta_2]->Fill(refpt_2 ,weight_2);
    	    }
    	    hEtaEff[1][iCent]->Fill(refeta_2,weight_2);
    	    hPhiEff[1][iCent]->Fill(refphi_2,weight_2);
    	  }
    	}
      }
//     cout<<"filled some histso, now check subid"<<endl;
      if ( subid_2 != 0 )continue;

      float sumPF = (chSum_2 + neSum_2 + phSum_2 + eSum_2 + muSum_2);
      float bkgd  = sumPF - pfrawpt_2;
    
      int ipt = GetPtBin(pfpt_2);

      int ipt_1 = GetPtBin(refpt_2);
      if ( ipt_1 < 0 || ipt_1 >= nbins )continue;
      double resp = pfpt_2/refpt_2;
      hrescrpt  [0][iCent][ipt_1]->Fill(resp,weight_2);
      hrescrpt_m[0][iCent][ipt_1]->Fill(resp,weight_2);
      if( wJetId ){
	hrescrpt  [1][iCent][ipt_1]->Fill(resp,weight_2);
	hrescrpt_m[1][iCent][ipt_1]->Fill(resp,weight_2);
      }
    }


    // MC loop unmatched jets
    long muentries = MC_unmatched->GetEntries();
    cout<<" looking at unmatched MC ntuple: "<<muentries<<" entries"<<endl;
    for(long munentry = 0; munentry < muentries; munentry++){
      //if(munentry%50000 == 0) cout<<" munentry = "<<munentry<<endl;
      MC_unmatched->GetEntry(munentry);

      if( printDebug && munentry==1000 )break;

      Float_t Sumcand = chSum_2 + phSum_2 + neSum_2 + muSum_2;
      bool wJetId=false;
      myeta_2= GetEtaBin(pfeta_2);
      if( (eMax_2/Sumcand < 0.05)
    	  //&& (chMax_2/Sumcand >= 0.02)
    	  )wJetId=true;

      if( refpt_2 > 2.*pthat_2 )continue;
      if( pfpt_2 < kptrecocut )continue;

      int iCent = -1;
      if( kSpecies == "PbPb")iCent = GetCentBin(hiBin_2);
      else iCent = ncen-1;
      if(iCent<0 || iCent>=ncen)continue;

      hPtFakeAll[iCent]->Fill(pfpt_2);
      if(fabs(pfeta_2)>=etabins[myeta_2] && fabs(pfeta_2)<etabins[myeta_2+1]){
            hPtFakeAll_etabin[iCent][myeta_2]->Fill(pfpt_2);
      }
      if( refpt_2 < 0 ){
    	hPtFake [0][iCent]->Fill(pfpt_2);
    	if(fabs(pfeta_2)>=etabins[myeta_2] && fabs(pfeta_2)<etabins[myeta_2+1]){
    	    hPtFake_etabin[0][iCent][myeta_2]->Fill(pfpt_2);
        }
    	if( wJetId ){
    	   hPtFake [1][iCent]->Fill(pfpt_2);
    	   if(fabs(pfeta_2)>=etabins[myeta_2] && fabs(pfeta_2)<etabins[myeta_2+1]){
    	      hPtFake_etabin[1][iCent][myeta_2]->Fill(pfpt_2);
    	   }
    	}
      }

      if( subid_2 == 0 && refpt_2 > 0 ){
    	hPtAll[iCent]->Fill(refpt_2,weight_2);
    	if(fabs(pfeta_2)>=etabins[myeta_2] && fabs(pfeta_2)<etabins[myeta_2+1]){
    	    	hPtAll_etabin[iCent][myeta_2]->Fill(refpt_2,weight_2);
	    }
    	hEtaAll [iCent]->Fill(refeta_2,weight_2);
    	hPhiAll [iCent]->Fill(refphi_2,weight_2);
      
    	if( refdrjt_2 < kdelrcut ){
	
    	  hPtEff[0][iCent]->Fill(refpt_2 ,weight_2);
    	  if(fabs(pfeta_2)>=etabins[myeta_2] && fabs(pfeta_2)<etabins[myeta_2+1]){
    	      	hPtEff_etabin[0][iCent][myeta_2]->Fill(refpt_2 ,weight_2);
          }
    	  hEtaEff[0][iCent]->Fill(refeta_2,weight_2);
    	  hPhiEff[0][iCent]->Fill(refphi_2,weight_2);
    	  if( wJetId ){
    	    hPtEff [1][iCent]->Fill(refpt_2,weight_2);
    	    if(fabs(pfeta_2)>=etabins[myeta_2] && fabs(pfeta_2)<etabins[myeta_2+1]){
    	       hPtEff_etabin[1][iCent][myeta_2]->Fill(refpt_2,weight_2);
    	    }
    	    hEtaEff[1][iCent]->Fill(refeta_2,weight_2);
    	    hPhiEff[1][iCent]->Fill(refphi_2,weight_2);
    	  }
    	}
      }

      if( subid_2 != 0 )continue;

      int ipt = GetPtBin(pfpt_2);
      if(ipt >=0 && ipt < nbins){
      
	float sumPF = (chSum_2 + neSum_2 + phSum_2 + eSum_2 + muSum_2);
	float bkgd  = sumPF - pfrawpt_2;
	
	
	
      }
      int ipt_1 = GetPtBin(refpt_2);
      if( ipt_1 < 0 || ipt_1 >= nbins )continue;
      double resp = pfpt_2/refpt_2;
      hrescrpt   [0][iCent][ipt_1]->Fill(resp,weight_2);
      hrescrpt_um[0][iCent][ipt_1]->Fill(resp,weight_2);
      if( wJetId ){
	hrescrpt   [1][iCent][ipt_1]->Fill(resp,weight_2);
	hrescrpt_um[1][iCent][ipt_1]->Fill(resp,weight_2);
      }
    }


    //fout->cd("../");
  }//! knj

  fout->cd();
  fout->Write();
  fout->Close();


  return 0;
}


int GetEtaBin(float eta)
{
  for(int ix=0;ix<neta;ix++){
    if(fabs(eta)>=etabins[ix] && fabs(eta)<etabins[ix+1]){
      return ix;
    }
  }
  return -1;
}
int GetPhiBin(float phi)
{
  for(int ix=0;ix<nphi;ix++){
    if(phi>=phibins[ix] && phi<phibins[ix+1]){
      return ix;
    }
  }
  return -1;
}

int GetPtBin(float pt)
{
  for(int ix=0;ix<nbins;ix++){
    if(pt>=ptbins[ix] && pt<ptbins[ix+1]){
      return ix;
    }
  }
  return -1;
}
double delphi(double phi1, double phi2)
{
  double dphi = phi2 - phi1;
  dphi = fabs(atan2(sin(dphi),cos(dphi)));
  return dphi;
}
int GetCentBin(int bin)
{
  int ibin=-1;
  //! centrality is defined as 0.5% bins of cross section
  //! in 0-200 bins
  if(bin<=10)ibin=0; //! 0-5%
  else if(bin>10  && bin<=20 )ibin=1; //! 5-10%
  else if(bin>20  && bin<=60 )ibin=2; //! 10-30%
  else if(bin>60  && bin<=100)ibin=3; //! 30-50%
  else if(bin>100 && bin<=140)ibin=4; //! 50-70%
  else if(bin>140 && bin<=180)ibin=5; //! 70-90%
  else if(bin<=200)ibin=6; //! 90-100%
  return ibin;
}
double deltaR(float eta1, float phi1, float eta2, float phi2)
{
  float deta = eta1 - eta2;
  float dphi = fabs(phi1 - phi2);
  if(dphi > pi)dphi -= 2*pi;
  double dr = sqrt(pow(deta,2) + pow(dphi,2));
  return dr;
}
void MakeIndHist(TH1F *&hist)
{
  hist->SetTitle("");
  hist->SetMinimum(0.01);
  hist->GetXaxis()->SetTitle("Jet bkgd p_{T} (GeV/c)");
  hist->GetXaxis()->SetTitleFont(42);
  hist->GetXaxis()->SetLabelFont(42);
  hist->GetXaxis()->SetLabelSize(0.08);
  hist->GetXaxis()->SetTitleSize(0.07);
  hist->GetXaxis()->SetNdivisions(505);
  hist->GetYaxis()->SetTitle("");
  hist->GetYaxis()->SetTitleFont(42);
  hist->GetYaxis()->SetLabelFont(42);
  hist->GetYaxis()->SetLabelSize(0.08);
  hist->GetYaxis()->SetNdivisions(505);
}
void MakeIndHist(TProfile *&hist)
{
  hist->SetTitle("");
  hist->SetMinimum(0.01);
  hist->GetXaxis()->SetTitle("Jet p_{T} (GeV/c)");
  hist->GetXaxis()->SetTitleFont(42);
  hist->GetXaxis()->SetLabelFont(42);
  hist->GetXaxis()->SetLabelSize(0.08);
  hist->GetXaxis()->SetTitleSize(0.07);
  hist->GetXaxis()->SetNdivisions(505);
  hist->GetYaxis()->SetTitle("");
  hist->GetYaxis()->SetTitleFont(42);
  hist->GetYaxis()->SetLabelFont(42);
  hist->GetYaxis()->SetLabelSize(0.08);
  hist->GetYaxis()->SetTitleSize(0.07);
  hist->GetYaxis()->SetNdivisions(505);
}
