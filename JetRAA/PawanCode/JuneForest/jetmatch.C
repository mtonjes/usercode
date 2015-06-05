
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

#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <utility>

#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"


using namespace std;

#ifdef _MAKECINT_
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#endif


//! constants
#define iYear 2015

#define pi 3.14159265

#define  ketacut    2.0
#define  kptrawcut  0.0
#define  kptrecocut 0.0
#define  kdelrmatch 0.2
#define  kdelrcut   0.3
#define  kvzcut     15.0


void AddInputFiles(TChain */*ch*/, string /*iname*/, string /*inputTree*/);

int GetPhiBin(float /*phi*/);
int GetEtaBin(float /*eta*/);
int GetPtBin(float /*pt*/);
int GetCentBin(int /*hiBin*/);
float delphi(float /*phi1*/, float /*phi2*/);
float deltaR(float /*eta1*/, float /*phi1*/, 
	      float /*eta2*/, float /*phi2*/);

double GetXsec(double /*maxpthat*/);
void GetCentWeight(TH1D */*hCentWeight*/);


struct Jet{
  int id;
  float pt;
  float eta;
  float phi;
};

bool compare_pt(Jet jet1, Jet jet2);
bool compare_pt(Jet jet1, Jet jet2){
  return jet1.pt > jet2.pt;
}

typedef std::pair< Jet, Jet > CaloPFJetPair;
struct CompareMatchedJets {
  //! Calo-PF match
  bool operator()(const CaloPFJetPair &A1, const CaloPFJetPair &A2){
    
    Jet cj1 = A1.first;  //! CaloJet 1st pair
    Jet pf1 = A1.second; //! PFJet   1st pair
    
    Jet cj2 = A2.first;  //! CaloJet 2nd pair
    Jet pf2 = A2.second; //! PFJet   2nd pair

    float delr1 = deltaR(cj1.eta, cj1.phi, pf1.eta, pf1.phi);
    float delr2 = deltaR(cj2.eta, cj2.phi, pf2.eta, pf2.phi);

    //float delpt1 = fabs(cj1.pt - pf1.pt);
    //float delpt2 = fabs(cj2.pt - pf2.pt);
    
    return ((delr1 < delr2) && (cj1.pt > cj2.pt));
  }
};

typedef std::multiset< CaloPFJetPair, CompareMatchedJets > CaloPFMatchedJets;
typedef std::multiset< CaloPFJetPair >::iterator CPFItr;
//typedef std::multiset< CaloPFJetPair >::value_type CPFJet;



const int ncen=7;
const char *cdir [ncen] = {"05","510","1030","3050","5070","7090","90100"};
const char *ccent[ncen] = {"0-5%","5-10%","10-30%","30-50%","50-70%","70-90%","90-100%"};

const int ncand=5;
const char *ccand[ncand] = {"h^{#pm}","e^{#pm}","#mu^{#pm}","#gamma","h0"};


//! pt binning
double ptbins[] ={24, 28, 32, 37, 43, 49, 56, 64, 74, 84, 97, 
		  114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 
		  395, 430, 468, 507, 548, 592, 638, 686, 1000};
const int nbins = sizeof(ptbins)/sizeof(double) - 1;

const double ptbins_wide[]={30,50,80,120,200,340,548};
const int nbins_wide = sizeof(ptbins_wide)/sizeof(double) - 1;

const double etabins[] = {-2.000, -1.4000, -0.4500, 0.000, 0.4500, 1.400, 2.000};
const int neta = sizeof(etabins)/sizeof(double) - 1;
const double phibins[] = {-3.141,-2.100,-1.500,-0.800,-0.300, 
 			  0.300,0.800,1.500,2.100,3.141
};
const int nphi = sizeof(phibins)/sizeof(double) - 1;

double xsec[12][3] ={{2.034e-01,15.  ,30.},   //! 15     0   
		     {1.075e-02,30.  ,50.},   //! 30     1   
		     {1.025e-03,50.  ,80.},   //! 50     2   
		     {9.865e-05,80.  ,120.},  //! 80     3  
		     {1.129e-05,120. ,170.},  //! 120    4  
		     {1.465e-06,170. ,220.},  //! 170    5  
		     {2.837e-07,220. ,280.},  //! 220    6  
		     {5.323e-08,280. ,370.},  //! 280    7  
		     {5.934e-09,370. ,460.},  //! 370    8 
		     {8.125e-10,460. ,540.},  //! 460    9
		     {1.467e-10,540. ,9999.}, //! 540    10
		     {0.0000000,9999.,9999.}  //         11 
};


//! PuPtMin values 
// akPu1PFJets.puPtMin = 10
// akPu2PFJets.puPtMin = 10
// akPu3PFJets.puPtMin = 15
// akPu4PFJets.puPtMin = 20
// akPu5PFJets.puPtMin = 25
// akPu6PFJets.puPtMin = 30
// akPu6PFJets.puPtMin = 35


TStopwatch timer;

int jetmatch(std::string kSpecies="pp",
	     std::string kAlgName="ak3",
	     std::string kDataset="mc",
	     //! PbPb
	     //std::string kFileList="/mnt/hadoop/cms/store/user/dgulhan/PYTHIA_HYDJET_Track9_Jet30_Pyquen_DiJet_TuneZ2_Unquenched_Hydjet1p8_2760GeV_merged/HiForest_PYTHIA_HYDJET_pthat80_Track9_Jet30_matchEqR_merged_forest_0.root",
	     //std::string kFileList="/mnt/hadoop/cms/store/user/belt/HiForest_jet55or65or80_JetRAA_v1_final/HiForest_jet55or65or80_JetRAA_v1_lumi9_Part8.root,/mnt/hadoop/cms/store/user/belt/HiForest_jet55or65or80_JetRAA_v1_final/HiForest_jet55or65or80_JetRAA_v1_lumi9_Part80.root,/mnt/hadoop/cms/store/user/belt/HiForest_jet55or65or80_JetRAA_v1_final/HiForest_jet55or65or80_JetRAA_v1_lumi9_Part81.root",
	     //! pp
	     std::string kFileList="/mnt/hadoop/cms/store/user/velicanu/HiForest_pp_Offical_MC_pthat_15_53X_STARTHI53_V29_5_3_20_correctJEC_pawan_30Nov2014_hadd/0.root",
	     //std::string kFileList="/mnt/hadoop/cms/store/user/velicanu/HiForest_pp_Offical_MC_pthat_15_53X_STARTHI53_V29_5_3_20_correctJEC_pawan_30Nov2014_hadd/0.root,/mnt/hadoop/cms/store/user/velicanu/HiForest_pp_Offical_MC_pthat_15_53X_STARTHI53_V29_5_3_20_correctJEC_pawan_30Nov2014_hadd/1.root,/mnt/hadoop/cms/store/user/velicanu/HiForest_pp_Offical_MC_pthat_15_53X_STARTHI53_V29_5_3_20_correctJEC_pawan_30Nov2014_hadd/2.root,/mnt/hadoop/cms/store/user/velicanu/HiForest_pp_Offical_MC_pthat_15_53X_STARTHI53_V29_5_3_20_correctJEC_pawan_30Nov2014_hadd/3.root",
	     //std::string kFileList="/mnt/hadoop/cms/store/user/velicanu/PPJet_ForestTag_PYTHIA_localdb_ppJEC_v29_hadd/0.root",
	     std::string kFoname="output_tree_mc_wofac.root", 
	     //std::string kFoname="outputhisto_data_sort.root", 
	     //std::string kFoname="JetRAA_akPu3_PbPb_Data_73.root",
	     //double kMaxpthat=9999
	     double kMaxpthat=30.
	     )
{
  
  timer.Start();

  std::cout << std::endl;
  bool printDebug=false;
  bool JECOnFly=false;
  std::string corrFileName="";

  JetCorrectorParameters *parHI_l2_PF=0, *parHI_l3_PF=0;
  vector<JetCorrectorParameters> vpar_HI_PF;
  FactorizedJetCorrector *_JEC_HI_PF = new FactorizedJetCorrector(vpar_HI_PF);

  JetCorrectorParameters *parHI_l2_Calo=0, *parHI_l3_Calo=0;
  vector<JetCorrectorParameters> vpar_HI_Calo;
  FactorizedJetCorrector *_JEC_HI_Calo = new FactorizedJetCorrector(vpar_HI_Calo);
  if( kSpecies == "pbpb_mb" ){
    JECOnFly=true;
    if(  kAlgName == "akPu2" )corrFileName = "AK2PFLocal";
    else if(  kAlgName == "akPu3" )corrFileName = "AK3PFLocal";
    else if(  kAlgName == "akPu4" )corrFileName = "AK4PFLocal";

    std::string L2NamePF = "JEC/JEC_2011RECO_STARTHI53_LV1_5_3_16_Track8_Jet29_L2Relative_"+corrFileName+".txt";
    std::string L3NamePF = "JEC/JEC_2011RECO_STARTHI53_LV1_5_3_16_Track8_Jet29_L3Absolute_"+corrFileName+".txt";

    std::string L2NameCalo = "JEC/JEC_2011RECO_STARTHI53_LV1_5_3_16_Track8_Jet29_L2Relative_AK3CaloLocal.txt";
    std::string L3NameCalo = "JEC/JEC_2011RECO_STARTHI53_LV1_5_3_16_Track8_Jet29_L3Absolute_AK3CaloLocal.txt";

    parHI_l2_PF = new JetCorrectorParameters(L2NamePF.c_str());
    parHI_l3_PF = new JetCorrectorParameters(L3NamePF.c_str());
    vpar_HI_PF.push_back(*parHI_l2_PF);
    vpar_HI_PF.push_back(*parHI_l3_PF);
    _JEC_HI_PF = new FactorizedJetCorrector(vpar_HI_PF);

    parHI_l2_Calo = new JetCorrectorParameters(L2NameCalo.c_str());
    parHI_l3_Calo = new JetCorrectorParameters(L3NameCalo.c_str());
    vpar_HI_Calo.push_back(*parHI_l2_Calo);
    vpar_HI_Calo.push_back(*parHI_l3_Calo);
    _JEC_HI_Calo = new FactorizedJetCorrector(vpar_HI_Calo);
  }

  //! For PbPb MC
  if( (kSpecies == "pbpb" || kSpecies == "pbpb_mb") && kDataset == "mc" ){
    xsec[8][2]=9999; //! 370 in PbPb
    xsec[9][0]=0.00000;  xsec[9][1]=9999;  xsec[9][2]=9999;
  }

  //tr_jet = (TTree*)fin->Get("akPu3PFJetAnalyzer/t");
  TChain *tch_pfjet = new TChain(Form("%sPFJetAnalyzer/t",kAlgName.c_str()));
  AddInputFiles(tch_pfjet,kFileList,Form("%sPFJetAnalyzer/t",kAlgName.c_str()));
  cout <<" # of events in PFJet   Tree : " <<  tch_pfjet->GetEntries() <<endl;

  //tr_jet = (TTree*)fin->Get("akPu3CaloJetAnalyzer/t");
  //TChain *tch_calojet = new TChain(Form("%sCaloJetAnalyzer/t",kAlgName.c_str()));
  //AddInputFiles(tch_calojet,kFileList,Form("%sCaloJetAnalyzer/t",kAlgName.c_str()));
  TChain *tch_calojet=0;
  if( kSpecies == "pbpb" || kSpecies == "pbpb_mb" ){
    tch_calojet = new TChain("akPu3CaloJetAnalyzer/t");
    AddInputFiles(tch_calojet,kFileList,"akPu3CaloJetAnalyzer/t");
    cout <<" # of events in CaloJet Tree : " <<  tch_calojet->GetEntries() <<endl;
  }else{
    tch_calojet = new TChain("ak3CaloJetAnalyzer/t");
    AddInputFiles(tch_calojet,kFileList,"ak3CaloJetAnalyzer/t");
    cout <<" # of events in CaloJet Tree : " <<  tch_calojet->GetEntries() <<endl;
  }
  //tr_ev = (TTree*)fin->Get("hiEvtAnalyzer/HiTree");
  TChain *tch_ev = new TChain("hiEvtAnalyzer/HiTree");
  AddInputFiles(tch_ev,kFileList,"hiEvtAnalyzer/HiTree");
  cout <<" # of events in Event   Tree : " <<  tch_ev->GetEntries() <<endl;

  //tr_hlt = (TTree*)fin->Get("hltanalysis/HltTree");
  TChain *tch_hlt = new TChain("hltanalysis/HltTree");
  AddInputFiles(tch_hlt,kFileList,"hltanalysis/HltTree");
  cout <<" # of events in HLT     Tree : " <<  tch_hlt->GetEntries() <<endl;

  //tr_skim = (TTree*)fin->Get("skimanalysis/HltTree");
  TChain *tch_skim = new TChain("skimanalysis/HltTree");
  AddInputFiles(tch_skim,kFileList,"skimanalysis/HltTree");
  cout <<" # of events in Skim    Tree : " <<  tch_skim->GetEntries() <<endl;

  //tr_trobj = (TTree*)fin->Get("hltobject/jetObjTree");  
  // TChain *tch_trgobj = new TChain("hltobject/jetObjTree");
  // AddInputFiles(tch_trgobj,kFileList,"hltobject/jetObjTree");
  // cout <<" # of events in TrigObj Tree : " <<  tch_trgobj->GetEntries() <<endl;
  // cout <<endl;


  //! Event Tree
  int run_value;
  int evt_value;
  int lumi_value;
  int hiNpix;
  int hiBin;
  float vz;

  tch_ev->SetBranchAddress("run",&run_value);  
  tch_ev->SetBranchAddress("evt",&evt_value);  
  tch_ev->SetBranchAddress("lumi",&lumi_value);  
  tch_ev->SetBranchAddress("hiBin",&hiBin);
  tch_ev->SetBranchAddress("hiNpix",&hiNpix);  
  tch_ev->SetBranchAddress("vz",&vz);


  //! HLT tree
  //! HI
  int jet55;
  int jet55_prescl;
  int jet65;
  int jet65_prescl;
  int jet80;
  int jet80_prescl;
  //! PP
  int jet40;
  int jet40_prescl;
  int jet60;
  int jet60_prescl;

  //! MinBias
  int L1_MB;
  int L1_MB_p;
  int L1_sj36;
  int L1_sj52;
  int jetMB;
  int jetMB_prescl;
  int L1_sj36_p;
  int L1_sj52_p;

  if ( kSpecies == "pbpb" || kSpecies == "pbpb_mb" ){
    if( kDataset == "data" ){
      tch_hlt->SetBranchAddress("HLT_HIJet55_v1",&jet55);
      tch_hlt->SetBranchAddress("HLT_HIJet55_v1_Prescl",&jet55_prescl);
      tch_hlt->SetBranchAddress("HLT_HIJet65_v1",&jet65);
      tch_hlt->SetBranchAddress("HLT_HIJet65_v1_Prescl",&jet65_prescl);
      tch_hlt->SetBranchAddress("HLT_HIJet80_v1",&jet80);
      tch_hlt->SetBranchAddress("HLT_HIJet80_v1_Prescl",&jet80_prescl);
      tch_hlt->SetBranchAddress("HLT_HIMinBiasHfOrBSC_v1",&jetMB);
      tch_hlt->SetBranchAddress("HLT_HIMinBiasHfOrBSC_v1_Prescl",&jetMB_prescl);
    }else{
      tch_hlt->SetBranchAddress("HLT_HIJet55_v7",&jet55);
      tch_hlt->SetBranchAddress("HLT_HIJet55_v7_Prescl",&jet55_prescl);
      tch_hlt->SetBranchAddress("HLT_HIJet65_v7",&jet65);
      tch_hlt->SetBranchAddress("HLT_HIJet65_v7_Prescl",&jet65_prescl);
      tch_hlt->SetBranchAddress("HLT_HIJet80_v7",&jet80);
      tch_hlt->SetBranchAddress("HLT_HIJet80_v7_Prescl",&jet80_prescl);
      tch_hlt->SetBranchAddress("HLT_HIMinBiasHfOrBSC_v4",&jetMB);
      tch_hlt->SetBranchAddress("HLT_HIMinBiasHfOrBSC_v4_Prescl",&jetMB_prescl);
    }
    tch_hlt->SetBranchAddress("L1_ZeroBias",&L1_MB);
    tch_hlt->SetBranchAddress("L1_ZeroBias_Prescl",&L1_MB_p);
    tch_hlt->SetBranchAddress("L1_SingleJet36_BptxAND",&L1_sj36);
    tch_hlt->SetBranchAddress("L1_SingleJet36_BptxAND_Prescl",&L1_sj36_p);
    tch_hlt->SetBranchAddress("L1_SingleJet52_BptxAND",&L1_sj52);
    tch_hlt->SetBranchAddress("L1_SingleJet52_BptxAND_Prescl",&L1_sj52_p);
  }else {
    tch_hlt->SetBranchAddress("HLT_PAJet40_NoJetID_v1",&jet40);
    tch_hlt->SetBranchAddress("HLT_PAJet40_NoJetID_v1_Prescl",&jet40_prescl);
    tch_hlt->SetBranchAddress("HLT_PAJet60_NoJetID_v1",&jet60);
    tch_hlt->SetBranchAddress("HLT_PAJet60_NoJetID_v1_Prescl",&jet60_prescl);
    tch_hlt->SetBranchAddress("HLT_PAJet80_NoJetID_v1",&jet80);
    tch_hlt->SetBranchAddress("HLT_PAJet80_NoJetID_v1_Prescl",&jet80_prescl);
  }
  // int L1_sj36_1;
  // int L1_sj36_p_1;
  // int L1_sj52_1;
  // int L1_sj52_p_1;
  // tch_hlt->SetBranchAddress("L1_SingleJet36_BptxAND",&L1_sj36_1);
  // tch_hlt->SetBranchAddress("L1_SingleJet36_BptxAND_Prescl",&L1_sj36_p_1);
  // tch_hlt->SetBranchAddress("L1_SingleJet52_BptxAND",&L1_sj52_1);
  // tch_hlt->SetBranchAddress("L1_SingleJet52_BptxAND_Prescl",&L1_sj52_p_1);


  //! Skim Tree
  int pcollisionEventSelection;
  int pHBHENoiseFilter;
  if( kSpecies == "pbpb" || kSpecies == "pbpb_mb" )tch_skim->SetBranchAddress("pcollisionEventSelection",&pcollisionEventSelection);
  else tch_skim->SetBranchAddress("pPAcollisionEventSelectionPA",&pcollisionEventSelection);
  tch_skim->SetBranchAddress("pHBHENoiseFilter",&pHBHENoiseFilter);

  //! Trigger object tree
  // float trgObj_id;
  // float trgObj_pt;
  // float trgObj_eta;
  // float trgObj_phi;
  // tch_trgobj->SetBranchAddress("id",&trgObj_id);
  // tch_trgobj->SetBranchAddress("pt",&trgObj_pt);
  // tch_trgobj->SetBranchAddress("eta",&trgObj_eta);
  // tch_trgobj->SetBranchAddress("phi",&trgObj_phi);


  //! CaloJet tree
  //Declaration of leaves types
  int   nref_calo;
  float jtpt_calo[1000];
  float rawpt_calo[1000];
  float jtpu_calo[1000];
  float jteta_calo[1000];
  float jtphi_calo[1000];
  float hcalSum_calo[1000];
  float ecalSum_calo[1000];
  
  int sid_calo[1000];
  float refpt_calo[1000];
  float refeta_calo[1000];
  float refphi_calo[1000];
  float refdrjt_calo[1000];

  tch_calojet->SetBranchAddress("nref",&nref_calo);
  tch_calojet->SetBranchAddress("rawpt",rawpt_calo);
  tch_calojet->SetBranchAddress("jtpt" ,jtpt_calo);
  tch_calojet->SetBranchAddress("jtpu" ,jtpu_calo);
  tch_calojet->SetBranchAddress("jteta",jteta_calo);
  tch_calojet->SetBranchAddress("jtphi",jtphi_calo);
  tch_calojet->SetBranchAddress("hcalSum",hcalSum_calo);
  tch_calojet->SetBranchAddress("ecalSum",ecalSum_calo);
  if( kDataset == "mc" ){
    tch_calojet->SetBranchAddress("subid" ,sid_calo);
    tch_calojet->SetBranchAddress("refpt" ,refpt_calo);
    tch_calojet->SetBranchAddress("refeta",refeta_calo);
    tch_calojet->SetBranchAddress("refphi",refphi_calo);
    tch_calojet->SetBranchAddress("refdrjt",refdrjt_calo);
  }


  //! PFJet tree
  //Declaration of leaves types
  int   nref_pf;
  float jtpt[1000];
  float rawpt[1000];
  float jteta[1000];
  float jtpu [1000];
  float jtphi[1000];
  float trackSum[1000];  
  float chargedSum[1000];
  float neutralSum[1000];
  float photonSum[1000];
  float eleSum[1000];
  float muonSum[1000];
  float trackMax[1000];  
  float chargedMax[1000];
  float neutralMax[1000];
  float photonMax[1000];
  float eleMax[1000];
  float muonMax[1000];
  float hcalSum_pf[1000];
  float ecalSum_pf[1000];

  float pthat;
  int   sid[1000];
  float pfrefpt[1000];
  float pfrefeta[1000];
  float pfrefphi[1000];
  float pfrefdrjt[1000];

  tch_pfjet->SetBranchAddress("nref",&nref_pf);
  tch_pfjet->SetBranchAddress("rawpt",rawpt);
  tch_pfjet->SetBranchAddress("jtpt" ,jtpt);
  tch_pfjet->SetBranchAddress("jtpu" ,jtpu);
  tch_pfjet->SetBranchAddress("jteta",jteta);
  tch_pfjet->SetBranchAddress("jtphi",jtphi);
  tch_pfjet->SetBranchAddress("trackSum",trackSum);
  tch_pfjet->SetBranchAddress("chargedSum",chargedSum);
  tch_pfjet->SetBranchAddress("neutralSum",neutralSum);
  tch_pfjet->SetBranchAddress("photonSum",photonSum);
  tch_pfjet->SetBranchAddress("eSum",eleSum);
  tch_pfjet->SetBranchAddress("muSum",muonSum);
  tch_pfjet->SetBranchAddress("trackMax",trackMax);
  tch_pfjet->SetBranchAddress("chargedMax",chargedMax);
  tch_pfjet->SetBranchAddress("neutralMax",neutralMax);
  tch_pfjet->SetBranchAddress("photonMax",photonMax);
  tch_pfjet->SetBranchAddress("eMax",eleMax);
  tch_pfjet->SetBranchAddress("muMax",muonMax);
  tch_pfjet->SetBranchAddress("hcalSum",hcalSum_pf);
  tch_pfjet->SetBranchAddress("ecalSum",ecalSum_pf);

  if( kDataset == "mc" ){
    tch_pfjet->SetBranchAddress("pthat",&pthat);    
    tch_pfjet->SetBranchAddress("subid" ,sid);
    tch_pfjet->SetBranchAddress("refpt" ,pfrefpt);
    tch_pfjet->SetBranchAddress("refeta",pfrefeta);
    tch_pfjet->SetBranchAddress("refphi",pfrefphi);
    tch_pfjet->SetBranchAddress("refdrjt",pfrefdrjt);
  }
  
  tch_pfjet->AddFriend(tch_ev);
  tch_pfjet->AddFriend(tch_hlt);
  tch_pfjet->AddFriend(tch_skim);
  //tch_pfjet->AddFriend(tch_trgobj);
  tch_pfjet->AddFriend(tch_calojet);

  //! Disable branches 
  //! Jet Tree
  tch_pfjet->SetBranchStatus("*",0,0);
  tch_pfjet->SetBranchStatus("nref" ,1,0);
  tch_pfjet->SetBranchStatus("rawpt",1,0);
  tch_pfjet->SetBranchStatus("jtpt" ,1,0);
  tch_pfjet->SetBranchStatus("jtpu" ,1,0);
  tch_pfjet->SetBranchStatus("jteta",1,0);
  tch_pfjet->SetBranchStatus("jtphi",1,0);
  tch_pfjet->SetBranchStatus("trackSum",1,0);
  tch_pfjet->SetBranchStatus("chargedSum",1,0);
  tch_pfjet->SetBranchStatus("neutralSum",1,0);
  tch_pfjet->SetBranchStatus("photonSum",1,0);
  tch_pfjet->SetBranchStatus("eSum",1,0);
  tch_pfjet->SetBranchStatus("muSum",1,0);
  tch_pfjet->SetBranchStatus("trackMax",1,0);
  tch_pfjet->SetBranchStatus("chargedMax",1,0);
  tch_pfjet->SetBranchStatus("neutralMax",1,0);
  tch_pfjet->SetBranchStatus("photonMax",1,0);
  tch_pfjet->SetBranchStatus("eMax",1,0);
  tch_pfjet->SetBranchStatus("muMax",1,0);
  tch_pfjet->SetBranchStatus("hcalSum",1,0);
  tch_pfjet->SetBranchStatus("ecalSum",1,0);

  tch_pfjet->SetBranchStatus("run",1,0);
  tch_pfjet->SetBranchStatus("evt",1,0);
  tch_pfjet->SetBranchStatus("lumi",1,0);
  tch_pfjet->SetBranchStatus("hiNpix",1,0);
  tch_pfjet->SetBranchStatus("hiBin",1,0);
  tch_pfjet->SetBranchStatus("vz",1,0);

  // tch_pfjet->SetBranchStatus("id",1,0);
  // tch_pfjet->SetBranchStatus("pt",1,0);
  // tch_pfjet->SetBranchStatus("eta",1,0);
  // tch_pfjet->SetBranchStatus("phi",1,0);

  if( kSpecies == "pbpb" || kSpecies == "pbpb_mb" ){
    if ( kDataset == "data" ){
      tch_pfjet->SetBranchStatus("HLT_HIJet55_v1",1,0);
      tch_pfjet->SetBranchStatus("HLT_HIJet55_v1_Prescl",1,0);
      tch_pfjet->SetBranchStatus("HLT_HIJet65_v1",1,0);
      tch_pfjet->SetBranchStatus("HLT_HIJet65_v1_Prescl",1,0);
      tch_pfjet->SetBranchStatus("HLT_HIJet80_v1",1,0);
      tch_pfjet->SetBranchStatus("HLT_HIJet80_v1_Prescl",1,0);
      tch_pfjet->SetBranchStatus("HLT_HIMinBiasHfOrBSC_v1",1,0);
      tch_pfjet->SetBranchStatus("HLT_HIMinBiasHfOrBSC_v1_Prescl",1,0);
    }else{
      tch_pfjet->SetBranchStatus("HLT_HIJet55_v7",1,0);
      tch_pfjet->SetBranchStatus("HLT_HIJet55_v7_Prescl",1,0);
      tch_pfjet->SetBranchStatus("HLT_HIJet65_v7",1,0);
      tch_pfjet->SetBranchStatus("HLT_HIJet65_v7_Prescl",1,0);
      tch_pfjet->SetBranchStatus("HLT_HIJet80_v7",1,0);
      tch_pfjet->SetBranchStatus("HLT_HIJet80_v7_Prescl",1,0);
      tch_pfjet->SetBranchStatus("HLT_HIMinBiasHfOrBSC_v4",1,0);
      tch_pfjet->SetBranchStatus("HLT_HIMinBiasHfOrBSC_v4_Prescl",1,0);
    }
    tch_pfjet->SetBranchStatus("pcollisionEventSelection",1,0);
    tch_pfjet->SetBranchStatus("L1_ZeroBias",1,0);
    tch_pfjet->SetBranchStatus("L1_ZeroBias_Prescl",1,0);
    tch_pfjet->SetBranchStatus("L1_SingleJet36_BptxAND",1,0);
    tch_pfjet->SetBranchStatus("L1_SingleJet36_BptxAND_Prescl",1,0);
    tch_pfjet->SetBranchStatus("L1_SingleJet52_BptxAND",1,0);
    tch_pfjet->SetBranchStatus("L1_SingleJet52_BptxAND_Prescl",1,0);
  }else{
    tch_pfjet->SetBranchStatus("HLT_PAJet40_NoJetID_v1",1,0);
    tch_pfjet->SetBranchStatus("HLT_PAJet40_NoJetID_v1_Prescl",1,0);
    tch_pfjet->SetBranchStatus("HLT_PAJet60_NoJetID_v1",1,0);
    tch_pfjet->SetBranchStatus("HLT_PAJet60_NoJetID_v1_Prescl",1,0);
    tch_pfjet->SetBranchStatus("HLT_PAJet80_NoJetID_v1",1,0);
    tch_pfjet->SetBranchStatus("HLT_PAJet80_NoJetID_v1_Prescl",1,0);
    tch_pfjet->SetBranchStatus("pPAcollisionEventSelectionPA",1,0);
  }
  tch_pfjet->SetBranchStatus("pHBHENoiseFilter",1,0);
  
  if( kDataset == "mc"){
    tch_pfjet->SetBranchStatus("pthat",1,0);    
    tch_pfjet->SetBranchStatus("subid" ,1,0);
    tch_pfjet->SetBranchStatus("refpt" ,1,0);
    tch_pfjet->SetBranchStatus("refeta",1,0);
    tch_pfjet->SetBranchStatus("refphi",1,0);
    tch_pfjet->SetBranchStatus("refdrjt",1,0);
  }


  
  //! Vertex re-weighting 
  TF1 *fVz=0;
  fVz = new TF1("fVz","[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x");
  if( kSpecies == "pbpb" || kSpecies=="pbpb_mb" )fVz->SetParameters(9.86748e-01, -8.91367e-03, 5.35416e-04, 2.67665e-06, -2.01867e-06);
  else fVz->SetParameters(8.41684e-01,-2.58609e-02,4.86550e-03,-3.10581e-04,2.07918e-05);

  //! Centrality re-weighting 
  TH1D *hCentWeight = new TH1D("hCentWeight","Centrality weight",200,0,200);
  GetCentWeight(hCentWeight);

  //! Create output file
  std::string outdir="";
  std::string outfile=outdir+kFoname;
  TFile *fout = new TFile(outfile.c_str(),"RECREATE");

  std::cout<<"\t"<<std::endl;
  std::cout<<"\t"<<std::endl;
  std::cout<<"**************************************************** "<<std::endl;
  std::cout<<Form("Dataset : %s, Species : %s, Jet Algorithm :  %s ",kDataset.c_str(), kSpecies.c_str(), kAlgName.c_str())<<std::endl;
  std::cout<<Form("Outfile : %s",outfile.c_str())<<std::endl;
  std::cout<<Form("vertex z (c.m.) cut : %0.3f ",kvzcut)<<std::endl;
  std::cout<<Form("Reco pT cut : %0.3f ; Reco eta cut : %0.3f ",kptrecocut, ketacut)<<std::endl;
  std::cout<<Form("CALO-PF jet matching delta R cut   : %0.3f ",kdelrmatch)<<std::endl;
  std::cout<<"**************************************************** "<<std::endl;
  std::cout<<"\t"<<std::endl;
  std::cout<<"\t"<<std::endl;

  //! 
  //! Define histograms here
  fout->mkdir(Form("%sJetAnalyzer",kAlgName.c_str()));
  fout->cd(Form("%sJetAnalyzer"   ,kAlgName.c_str()));

  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  //! Matched PF and calo jets
  Int_t npf;
  Int_t isCaloMatch[1000];
  Int_t caloidx[1000];
  Int_t pfrefidx[1000];
  Float_t deltar[1000];
  Float_t calopt[1000];
  Float_t pfpt[1000];
  Float_t pfrawpt[1000];
  Float_t pfeta[1000];
  Float_t pfphi[1000];
  Float_t pfpu[1000];
  Float_t trMax[1000], chMax[1000], phMax[1000], neMax[1000], muMax[1000], eMax[1000];  
  Float_t trSum[1000], chSum[1000], phSum[1000], neSum[1000], muSum[1000], eSum[1000];
  Float_t hcalSum[1000], ecalSum[1000];

  Int_t nref;
  Int_t subid[1000], refpfid[1000], refclid[1000];
  Double_t weight;
  Float_t refpt[1000], refeta[1000], refphi[1000], refdrjt[1000]; 

  //! calojets
  Int_t ncalo;
  Int_t isPFMatch[1000];
  Int_t pfidx[1000];
  Int_t clrefidx[1000];
  Float_t calorecpt[1000], calorawpt[1000];
  Float_t caloeta[1000], calophi  [1000];
  Float_t calopu [1000];
  Float_t caloecalSum[1000], calohcalSum[1000];


  TTree* jetTree = new TTree("jetTree",Form("jetTree %s %s %s",kSpecies.c_str(), kDataset.c_str(), kAlgName.c_str()));
  //! Matched and Unmatched PF jets
  jetTree->Branch("hiBin",&hiBin,"hiBin/I");
  jetTree->Branch("run_value",&run_value,"run_value/I");
  jetTree->Branch("evt_value",&evt_value,"evt_value/I");
  jetTree->Branch("lumi_value",&lumi_value,"lumi_value/I");
  jetTree->Branch("vz",&vz,"vz/F");
  if( kSpecies == "pbpb" || kSpecies == "pbpb_mb" ){
    jetTree->Branch("jet80",&jet80,"jet80/I"); jetTree->Branch("jet80_prescl",&jet80_prescl,"jet80_prescl/I");
    jetTree->Branch("jet65",&jet65,"jet65/I"); jetTree->Branch("jet65_prescl",&jet65_prescl,"jet65_prescl/I");
    jetTree->Branch("jet55",&jet55,"jet55/I"); jetTree->Branch("jet55_prescl",&jet55_prescl,"jet55_prescl/I");
    jetTree->Branch("jetMB",&jetMB,"jetMB/I");
    jetTree->Branch("jetMB_prescl",&jetMB_prescl,"jetMB_prescl/I");
    jetTree->Branch("L1_MB",&L1_MB,"L1_MB/I");
    jetTree->Branch("L1_MB_p",&L1_MB_p,"L1_MB_p/I");
    jetTree->Branch("L1_sj36",&L1_sj36,"L1_sj36/I");
    jetTree->Branch("L1_sj52",&L1_sj52,"L1_sj52/I");
    jetTree->Branch("L1_sj36_p",&L1_sj36_p,"L1_sj36_p/I");
    jetTree->Branch("L1_sj52_p",&L1_sj52_p,"L1_sj52_p/I");
  }else{
    jetTree->Branch("jet80",&jet80,"jet80/I"); jetTree->Branch("jet80_prescl",&jet80_prescl,"jet80_prescl/I");
    jetTree->Branch("jet60",&jet60,"jet60/I"); jetTree->Branch("jet60_prescl",&jet60_prescl,"jet60_prescl/I");
    jetTree->Branch("jet40",&jet40,"jet40/I"); jetTree->Branch("jet40_prescl",&jet40_prescl,"jet40_prescl/I");
  }
  jetTree->Branch("npf",&npf,"npf/I");
  jetTree->Branch("isCaloMatch",isCaloMatch,"isCaloMatch[npf]/I");
  jetTree->Branch("caloidx",caloidx,"caloidx[npf]/I");
  jetTree->Branch("deltar",deltar,"deltar[npf]/F"); 
  jetTree->Branch("calopt",calopt,"calopt[npf]/F");       	   
  jetTree->Branch("pfpt",pfpt,"pfpt[npf]/F");       	   
  jetTree->Branch("pfrawpt",pfrawpt,"pfrawpt[npf]/F");  
  jetTree->Branch("pfeta",pfeta,"pfeta[npf]/F");        
  jetTree->Branch("pfphi",pfphi,"pfphi[npf]/F");        
  jetTree->Branch("pfpu",pfpu,"pfpu[npf]/F");           
  jetTree->Branch("trMax",trMax,"trMax[npf]/F");       jetTree->Branch("trSum",trSum,"trSum[npf]/F");    
  jetTree->Branch("chMax",chMax,"chMax[npf]/F");       jetTree->Branch("chSum",chSum,"chSum[npf]/F");    
  jetTree->Branch("phMax",phMax,"phMax[npf]/F");       jetTree->Branch("phSum",phSum,"phSum[npf]/F");
  jetTree->Branch("neMax",neMax,"neMax[npf]/F");       jetTree->Branch("neSum",neSum,"neSum[npf]/F");
  jetTree->Branch("muMax",muMax,"muMax[npf]/F");       jetTree->Branch("muSum",muSum,"muSum[npf]/F");
  jetTree->Branch("eMax",eMax,"eMax[npf]/F");          jetTree->Branch("eSum",eSum,"eSum[npf]/F");
  jetTree->Branch("hcalSum",hcalSum,"hcalSum[npf]/F"); jetTree->Branch("ecalSum",ecalSum,"ecalSum[npf]/F");

  //! Calo jets
  jetTree->Branch("ncalo",&ncalo,"ncalo/I");
  jetTree->Branch("isPFMatch",isPFMatch,"isPFMatch[ncalo]/I");
  jetTree->Branch("pfidx",pfidx,"pfidx[ncalo]/I");
  jetTree->Branch("calorecpt",calorecpt,"calorecpt[ncalo]/F");
  jetTree->Branch("calorawpt",calorawpt,"calorawpt[ncalo]/F");
  jetTree->Branch("caloeta",caloeta,"caloeta[ncalo]/F"); 
  jetTree->Branch("calophi",calophi,"calophi[ncalo]/F"); 
  jetTree->Branch("calopu" ,calopu ,"calopu[ncalo]/F");    
  jetTree->Branch("calohcalSum",calohcalSum,"calohcalSum[ncalo]/F"); 
  jetTree->Branch("caloecalSum",caloecalSum,"caloecalSum[ncalo]/F");

  if( kDataset == "mc"){
    jetTree->Branch("pthat",&pthat,"pthat/F");       
    jetTree->Branch("weight",&weight,"weight/D");    
    jetTree->Branch("pfrefidx",pfrefidx,"pfrefidx[npf]/I");
    jetTree->Branch("clrefidx",clrefidx,"clrefidx[ncalo]/I");

    jetTree->Branch("nref",&nref,"nref/I");       
    jetTree->Branch("refpfid",refpfid,"refpfid[nref]/I");
    jetTree->Branch("refclid",refclid,"refclid[nref]/I");
    jetTree->Branch("subid",subid,"subid[nref]/I");    
    jetTree->Branch("refpt",refpt,"refpt[nref]/F");       
    jetTree->Branch("refeta",refeta,"refeta[nref]/F");       
    jetTree->Branch("refphi",refphi,"refphi[nref]/F");       
    jetTree->Branch("refdrjt",refdrjt,"refdrjt[nref]/F");       
  }

  TH1D *hEvents_Total = new TH1D("hEvents_Total","Total # of events Total ",10,0.,1.);
  hEvents_Total->Sumw2();
  TH1D *hEvents_pCollEvent = new TH1D("hEvents_pCollEvent","# of events pCollisionEvent",10,0.,1.);
  hEvents_pCollEvent->Sumw2();
  TH1D *hEvents_pHBHENoise = new TH1D("hEvents_pHBHENoise","# of events HBHENoise",10,0.,1.);
  hEvents_pHBHENoise->Sumw2();
  TH1D *hEvents_Vzcut = new TH1D("hEvents_Vzcut","# of events vz cut ",10,0.,1.);
  hEvents_Vzcut->Sumw2();
  TH1D *hEvents_Good = new TH1D("hEvents_Good","# of events of good events",10,0.,1.);
  hEvents_Good->Sumw2();
  TH1D *hEvents_bad = new TH1D("hEvents_bad","# of events bad ",10,0.,1.);
  hEvents_bad->Sumw2();
  TH1D *hEvents_supernova = new TH1D("hEvents_supernova","supernova # of events ",10,0.,1.);
  hEvents_supernova->Sumw2();
  TH1D *hEvents_nopfcalo = new TH1D("hEvents_nopfcalo","nopfcalo # of events ",10,0.,1.);
  hEvents_nopfcalo->Sumw2();
  TH1D *hEvents_maxpthat = new TH1D("hEvents_maxpthat","maxpthat # of events ",10,0.,1.);
  hEvents_maxpthat->Sumw2();

  TH1D *hEvents_jet40 = new TH1D("hEvents_jet40","# of events jet40",10,0.,1.);
  hEvents_jet40->Sumw2();
  TH1D *hEvents_jet60 = new TH1D("hEvents_jet60","# of events jet60",10,0.,1.);
  hEvents_jet60->Sumw2();
  TH1D *hEvents_jet55 = new TH1D("hEvents_jet55","# of events jet55",10,0.,1.);
  hEvents_jet55->Sumw2();
  TH1D *hEvents_jet65 = new TH1D("hEvents_jet65","# of events jet65",10,0.,1.);
  hEvents_jet65->Sumw2();
  TH1D *hEvents_jet80 = new TH1D("hEvents_jet80","# of events jet80",10,0.,1.);
  hEvents_jet80->Sumw2();

  TH1D *hEvents_jet40_nojet60_nojet80 = new TH1D("hEvents_jet40_nojet60_nojet80","# of events jet40 && !jet60 && !jet80",10,0.,1.);
  hEvents_jet40_nojet60_nojet80->Sumw2();
  TH1D *hEvents_jet60_nojet80 = new TH1D("hEvents_jet60_nojet80","# of events jet60 && !jet80",10,0.,1.);
  hEvents_jet60_nojet80->Sumw2();

  TH2F *hEvents_jet40_prescl = new TH2F("hEvents_jet40_prescl","prescaled # of events jet40",50,-0.5,50-0.5,10,0.,1.);
  hEvents_jet40_prescl->Sumw2();
  TH2F *hEvents_jet60_prescl = new TH2F("hEvents_jet60_prescl","prescaled # of events jet60",50,-0.5,50-0.5,10,0.,1.);
  hEvents_jet60_prescl->Sumw2();				
  TH2F *hEvents_jet55_prescl = new TH2F("hEvents_jet55_prescl","prescaled # of events jet55",50,-0.5,50-0.5,10,0.,1.);
  hEvents_jet55_prescl->Sumw2();				
  TH2F *hEvents_jet65_prescl = new TH2F("hEvents_jet65_prescl","prescaled # of events jet65",50,-0.5,50-0.5,10,0.,1.);
  hEvents_jet65_prescl->Sumw2();				
  TH2F *hEvents_jet80_prescl = new TH2F("hEvents_jet80_prescl","prescaled # of events jet80",50,-0.5,50-0.5,10,0.,1.);
  hEvents_jet80_prescl->Sumw2();
  
  TH1D *hEvents_jet55_nojet65_nojet80 = new TH1D("hEvents_jet55_nojet65_nojet80","# of events jet55 && !jet65 && !jet80",10,0.,1.);
  hEvents_jet55_nojet65_nojet80->Sumw2();
  TH1D *hEvents_jet65_nojet80 = new TH1D("hEvents_jet65_nojet80","# of events jet60 && !jet80",10,0.,1.);
  hEvents_jet65_nojet80->Sumw2();

  TH1D *hVz = new TH1D("hVz","Vertex z (in c.m.)",60,-15.,15.);
  hVz->Sumw2();

  TH1D *hBin = new TH1D("hBin","hiBin",200,-0.5,199.5);
  hBin->Sumw2();


  fout->cd("../");
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  std::cout<<"Initialized the histograms " <<std::endl;

  Long64_t nbytes=0;
  Long64_t nentries = tch_pfjet->GetEntries();
  std::cout<<Form("# of entries in TTree for %s %s : ",kAlgName.c_str(),kSpecies.c_str())<<nentries<<std::endl;

  double wxs=1.;
  if( kDataset == "mc" ){
    TEventList* el = new TEventList("el","el");
    stringstream selection; selection<<"pthat<="<<kMaxpthat;
    tch_pfjet->Draw(">>el",selection.str().c_str());
    double fentries = (double)el->GetN();
    std::cout<<"tree entries  :  "<<kAlgName.c_str()<<" algorithm : " << nentries<<" elist: "<< fentries <<std::endl;
    delete el;
    double tmpw = GetXsec(kMaxpthat);
    wxs = tmpw/fentries;
    //wxs = tmpw/(fentries/100000.);
  }

  //! Start event loop
  for (Long64_t i=0; i<nentries;i++) {
    nbytes += tch_pfjet->GetEntry(i);

    if(printDebug && i==10)break;

    float rndm=gRandom->Rndm();

    hEvents_Total->Fill(rndm);
    if( kSpecies == "pp" ){
      if(jet40)hEvents_jet40->Fill(rndm);
      if(jet40_prescl)hEvents_jet40_prescl->Fill(jet40_prescl,rndm);
      if(jet60)hEvents_jet60->Fill(rndm);
      if(jet60_prescl)hEvents_jet60_prescl->Fill(jet60_prescl,rndm);
      if(jet80)hEvents_jet80->Fill(rndm);
      if(jet80_prescl)hEvents_jet80_prescl->Fill(jet80_prescl,rndm);

      if(jet40==1 && jet60==0 && jet80==0)hEvents_jet40_nojet60_nojet80->Fill(rndm);
      if(jet60==1 && jet80==0)hEvents_jet60_nojet80->Fill(rndm);
    }else{
      if(jet55)hEvents_jet55->Fill(rndm);
      if(jet55_prescl)hEvents_jet55_prescl->Fill(jet55_prescl,rndm);
      if(jet65)hEvents_jet65->Fill(rndm);
      if(jet65_prescl)hEvents_jet65_prescl->Fill(jet65_prescl,rndm);
      if(jet80)hEvents_jet80->Fill(rndm);
      if(jet80_prescl)hEvents_jet80_prescl->Fill(jet80_prescl,rndm);

      if(jet55==1 && jet65==0 && jet80==0)hEvents_jet55_nojet65_nojet80->Fill(rndm);
      if(jet65==1 && jet80==0)hEvents_jet65_nojet80->Fill(rndm);
    }

    if( kDataset == "data" ){
      if(pcollisionEventSelection)hEvents_pCollEvent->Fill(rndm);
      if(pcollisionEventSelection && pHBHENoiseFilter)hEvents_pHBHENoise->Fill(rndm);
      if(pcollisionEventSelection && pHBHENoiseFilter && fabs(vz)<kvzcut )hEvents_Vzcut->Fill(rndm);
      if(pcollisionEventSelection==0 || pHBHENoiseFilter==0 || fabs(vz) > kvzcut){
	hEvents_bad->Fill(rndm);
	continue;
      }
    }else if( kDataset == "mc" ){//! HBHENoiseFilter
      if(pcollisionEventSelection)hEvents_pCollEvent->Fill(rndm);
      if(pcollisionEventSelection)hEvents_pHBHENoise->Fill(rndm);
      if(pcollisionEventSelection && fabs(vz)<kvzcut )hEvents_Vzcut->Fill(rndm);
      if(pcollisionEventSelection==0 || fabs(vz) > kvzcut){
	hEvents_bad->Fill(rndm);
	continue;
      }
    }
    
    int iCent = GetCentBin(hiBin);
    if(iCent<0 || iCent>=ncen)continue;

    if ( kSpecies == "pbpb" || kSpecies == "pbpb_mb" ){
      //! SuperNovae events use calo jets
      //int lowjetCounter=0;
      int jetCounter=0;
      for(int g = 0;g<nref_calo;g++){
	// if( fabs(jteta_calo[g]) < 2. && jtpt_calo[g]>=kptrecocut ){ //to select inside
	// 	lowjetCounter++;
	// }
	if( fabs(jteta_calo[g]) < ketacut && jtpt_calo[g]>=50. ){ //to select inside
	  jetCounter++;
	}//eta selection cut
      }// jet loop
      // apply the correct supernova selection cut rejection here:
      if( hiNpix > 38000 - 500*jetCounter ){
	hEvents_supernova->Fill(rndm);
	continue;
      }
    }
    if( nref_pf==0 && nref_calo==0 ){
      hEvents_nopfcalo->Fill(rndm);
      continue;
    }
    //if( lowjetCounter == 0 )continue;

    if( kDataset == "mc" && pthat > kMaxpthat ){
      hEvents_maxpthat->Fill(rndm);
      continue;
    }

    //! ----------------------------------------------------------------------------
    // int iStat=0;
    // for(int pj=0; pj<nref; pj++){ //! PFjet
    //   if( pfrefdrjt[pj] > 0.3 && sid[pj]==0 && pfrefpt[pj] > 50. && fabs(jteta[pj]) < ketacut){
    // 	std::cout << "\t\t Found an interesting cand : "<< i << " dr : " << pfrefdrjt[pj] << " refpt : " << pfrefpt[pj] << " recopt : " << jtpt[pj] << std::endl;
    // 	iStat=1;
    //   }
    // }
    // if( iStat )printDebug=true;
    // else printDebug=false;
    //! ----------------------------------------------------------------------------    

    if(printDebug)std::cout << "------------------------------------Start Event # " << i <<"------------------------------------------------------------------ " << std::endl;
    //std::cout<<" ***** Event # " <<i<<"\t vz  : "<<vz<<"\t hiBin : "<<hiBin<<"\t  # of PF jets "<<nref<<" # of calojets  "<<nref_calo<<std::endl;
    //if(i%50000==0)std::cout<<" ********** Event # " <<i<<"\t vz  : "<<vz<<"\t hiBin : "<<hiBin<<"\t  # of PF jets "<<nref<< "  # of Calo jets " <<nref_calo<<std::endl;
    
    int pfjets=0;
    int calojets=0;
    
    std::vector <Jet> vPFJets, vCaloJets;
    std::vector <int> pfid(nref_pf), caloid(nref_calo);
    
    if(printDebug)std::cout << " PF jets : " << std::endl;

    for(int pj=0; pj<nref_pf; pj++){ //! PFjet
      
      if( rawpt[pj] < kptrawcut || jtpt[pj] < kptrecocut ) continue;
      if( fabs(jteta[pj]) > ketacut ) continue;

      Jet pfj;
      pfj.id  = pj;
      pfj.eta = jteta[pj];
      pfj.phi = jtphi[pj];
      if( JECOnFly ){
        //! Correct jet energy with the latest db file
	_JEC_HI_PF->setJetEta(jteta[pj]);
        _JEC_HI_PF->setJetPt (rawpt[pj]);
        float corrfac = _JEC_HI_PF->getCorrection();
        pfj.pt  = rawpt[pj]*corrfac;
      }else{
        pfj.pt  = jtpt [pj];
      }

      if(printDebug){
	if( kDataset == "mc" )std::cout <<"\t" << pj << "  pt : " << jtpt[pj] << " eta : "  << jteta[pj] << " phi : " << jtphi[pj] << " subid : " << sid[pj] << " dr : " << pfrefdrjt[pj] << std::endl;
	else std::cout <<"\t"<< pj << "  pt : " << jtpt[pj] << " eta : "  << jteta[pj] << " phi : " << jtphi[pj] << std::endl;
      }
      vPFJets.push_back(pfj);
      pfjets++;
    }    

    if(printDebug){
      std::cout << std::endl;
      std::cout << " Calo jets : " << std::endl;
    }
    for(int cj=0; cj<nref_calo; cj++){ //! CaloJet
      if( rawpt_calo[cj] < kptrawcut || jtpt_calo[cj] < kptrecocut) continue;
      if( fabs(jteta_calo[cj]) > ketacut ) continue;
      
      Jet clj;
      clj.id  = cj;
      clj.eta = jteta_calo[cj];
      clj.phi = jtphi_calo[cj];

      if( JECOnFly ){
        //! Correct jet energy with the latest db file
        _JEC_HI_Calo->setJetEta(jteta_calo[cj]);
        _JEC_HI_Calo->setJetPt (rawpt_calo[cj]);
        float corrfac = _JEC_HI_Calo->getCorrection();
        clj.pt  = rawpt_calo[cj]*corrfac;
      }else{
        clj.pt  = jtpt_calo[cj];
      }

      if(printDebug){
	if( kDataset == "mc" )std::cout <<"\t" << cj << "  pt : " << jtpt_calo[cj] << " eta : "  << jteta_calo[cj] << " phi : " << jtphi_calo[cj] << " subid : " << sid_calo[cj] << " dr : " << refdrjt_calo[cj] << std::endl;
	else  std::cout <<"\t" << cj << "  pt : " << jtpt_calo[cj] << " eta : "  << jteta_calo[cj] << " phi : " << jtphi_calo[cj] << std::endl;
      }
      vCaloJets.push_back(clj);
      calojets++;
    }//! calo jet loop
    if(printDebug)std::cout << std::endl;
    if(pfjets==0 && calojets==0){
      if(printDebug){
	std::cout <<" XXXXXXXXXXX  No Calo and PF jets passed the cuts " << std::endl;
	std::cout << "------------------------------------End Event # " << i <<"------------------------------------------------------------------ " << "\n"<<std::endl;
      }
      hEvents_nopfcalo->Fill(rndm);
      continue;
    }

    hEvents_Good->Fill(rndm);
    hVz->Fill(vz);
    hBin->Fill(hiBin);

    //! Sort the jet containers in pt
    std::sort (vPFJets.begin(), vPFJets.end(), compare_pt);    
    std::sort (vCaloJets.begin(), vCaloJets.end(), compare_pt);    

    bool onlyCalo   = (pfjets==0 && calojets >0) ? true : false;
    bool onlyPF     = (pfjets>0  && calojets==0) ? true : false;
    bool bothPFCalo = (pfjets>0  && calojets >0) ? true : false;

    int matchedJets=0;
    int unmatchedPFJets=0;
    int unmatchedCaloJets=0;
    
    //! for jetTree
    npf=0;
    ncalo=0;
    nref=0;
    weight = 1.;
    if( kDataset == "mc" ){
      double wvz  = fVz->Eval(vz);
      double wcen = hCentWeight->GetBinContent(hCentWeight->FindBin(hiBin));
      if ( kSpecies == "pbpb" )weight = (wxs*wvz*wcen);
      else if( kSpecies == "pbpb_mb" )weight = (wvz*wcen);
      else weight = (wxs*wvz);
    }else weight = 1.;

    if(printDebug)std::cout <<" Total ==>  # of PF jets : " << pfjets << ", # of calojets : "  << calojets <<"\n"<<std::endl;

    std::vector < Jet >::const_iterator iJet, jJet;

    if( onlyPF ){
      
      for(iJet = vPFJets.begin(); iJet != vPFJets.end(); ++iJet){ //! PFjet

	int pj = (*iJet).id; 

	isCaloMatch[npf]=0;
	caloidx[npf]= -999;
    	deltar[npf] = -999;
    	calopt[npf] = -999;
	if( JECOnFly )pfpt[npf]   = (*iJet).pt;      //! Corrected JEC pt
        else pfpt[npf]   = jtpt [pj];
    	pfrawpt[npf]= rawpt[pj];
    	pfeta[npf]  = jteta[pj];
    	pfphi[npf]  = jtphi[pj];
    	pfpu [npf]  = jtpu [pj];
	
	trMax[npf]  = trackMax  [pj];
    	chMax[npf]  = chargedMax[pj];
    	phMax[npf]  = photonMax [pj];
    	neMax[npf]  = neutralMax[pj];
    	muMax[npf]  = muonMax   [pj];
    	eMax [npf]  = eleMax    [pj];

	trSum[npf]  = trackSum  [pj];	
    	chSum[npf]  = chargedSum[pj];
    	phSum[npf]  = photonSum [pj];
    	neSum[npf]  = neutralSum[pj];
    	muSum[npf]  = muonSum   [pj];
    	eSum [npf]  = eleSum    [pj];
	
    	hcalSum[npf] = hcalSum_pf[pj];
    	ecalSum[npf] = ecalSum_pf[pj];

	if( kDataset == "mc" ){
	  if( sid[pj] != -1 ){
	    pfrefidx[npf] =nref;
	    refpfid[nref] =npf;
	    refclid[nref] =-999;
	    subid  [nref] = sid[pj];
	    refpt  [nref] = pfrefpt[pj];
	    refeta [nref] = pfrefeta[pj];
	    refphi [nref] = pfrefphi[pj];
	    refdrjt[nref] = pfrefdrjt[pj];
	    nref++;
	  }else{
	    pfrefidx[npf] =-999;
	  }
	}
	
	if(printDebug){
	  if( kDataset == "mc" )std::cout <<" unmatched PF jets w ncalo=0 : " << unmatchedPFJets << "  pt : " << jtpt[pj] << " eta : "  << jteta[pj] << " phi : " << jtphi[pj] << " dr : " << pfrefdrjt[pj] <<std::endl;
	  else std::cout <<" unmatched PF jets w ncalo=0 : " << unmatchedPFJets << "  pt : " << jtpt[pj] << " eta : "  << jteta[pj] << " phi : " << jtphi[pj] << std::endl;
	}
    	unmatchedPFJets++;
	npf++;
      }
    }
    else if( onlyCalo ){
      for(iJet = vCaloJets.begin(); iJet != vCaloJets.end(); ++iJet){ //! Calojet

	int cj = (*iJet).id; 	

	isPFMatch[ncalo]=0;
	pfidx[ncalo] = -999;
	if( JECOnFly )calorecpt[ncalo]  = (*iJet).pt;      //! Corrected JEC pt
        else calorecpt[ncalo] = jtpt_calo [cj];
    	calorawpt[ncalo] = rawpt_calo[cj];
    	caloeta[ncalo]   = jteta_calo[cj];
    	calophi[ncalo]   = jtphi_calo[cj];
    	calopu[ncalo]    = jtpu_calo [cj];
	
    	hcalSum[ncalo]   = hcalSum_calo[cj];
    	ecalSum[ncalo]   = ecalSum_calo[cj];

	if( kDataset == "mc" ){
	  if( sid[cj] != -1 ){
	    clrefidx[ncalo]=nref;
	    refpfid[nref] = -999;
	    refclid[nref] = ncalo;
	    subid  [nref] = sid[cj];
	    refpt  [nref] = pfrefpt[cj];
	    refeta [nref] = pfrefeta[cj];
	    refphi [nref] = pfrefphi[cj];
	    refdrjt[nref] = pfrefdrjt[cj];
	    nref++;
	  }else{
	    clrefidx[ncalo]=-999;
	  }
	}
	if(printDebug){
	  if( kDataset == "mc" )std::cout <<" unmatched CALO jets w npf=0 : " << unmatchedCaloJets << "  pt : " << jtpt_calo[cj] << " eta : "  << jteta_calo[cj] << " phi : " << jtphi_calo[cj] << " dr : " << refdrjt_calo[cj] << std::endl;
	  else std::cout <<" unmatched CALO jets w npf=0 : " << unmatchedCaloJets << "  pt : " << jtpt_calo[cj] << " eta : "  << jteta_calo[cj] << " phi : " << jtphi_calo[cj] << std::endl;
	}
    	unmatchedCaloJets++;
	ncalo++;
      }
    }
    else if( bothPFCalo ){

      CaloPFMatchedJets mCaloPFMatchedJets;
      for(iJet = vCaloJets.begin(); iJet != vCaloJets.end(); ++iJet){ //! Calojet      
	
	for(jJet = vPFJets.begin(); jJet != vPFJets.end(); ++jJet){ //! PFjet
	  
	  mCaloPFMatchedJets.insert(std::make_pair(*iJet,*jJet));
	  
	}//! calo jet loop
      }//! PF jet loop

      CPFItr itr;
      //! Matched jets (PF jet matched to Calo jet)
      for(itr = mCaloPFMatchedJets.cbegin(); itr != mCaloPFMatchedJets.cend(); ++itr){
	
	CaloPFJetPair jetpair = (*itr);
	Jet clj = jetpair.first;
	Jet pfj = jetpair.second;
	
	float delr  = deltaR(clj.eta, clj.phi, pfj.eta, pfj.phi);
	//float delpt = fabs(clj.pt - pfj.pt);
	if( delr < kdelrmatch && caloid[clj.id]==0 ){
	
	  isCaloMatch[npf]=1;
	  caloidx[npf] = ncalo;
	  deltar[npf]  = delr;
	  if( JECOnFly ){      //! Corrected JEC pt
	    calopt[npf]  = clj.pt;
	    pfpt  [npf]  = pfj.pt;  
	  }else{
	    calopt[npf]  = jtpt_calo [clj.id];
	    pfpt  [npf]  = jtpt      [pfj.id];
	  }
	  pfrawpt[npf] = rawpt     [pfj.id];
	  pfeta  [npf] = jteta     [pfj.id];
	  pfphi  [npf] = jtphi     [pfj.id];
	  pfpu   [npf] = jtpu      [pfj.id];

	  isPFMatch[ncalo]=1;
	  pfidx[ncalo]=npf;

	  if( JECOnFly )calopt[ncalo]  = clj.pt;
	  else calorecpt[ncalo] = jtpt_calo [clj.id];	  

	  calorawpt[ncalo]   = rawpt_calo[clj.id];
	  caloeta[ncalo]     = jteta_calo[clj.id];
	  calophi[ncalo]     = jtphi_calo[clj.id];
	  calopu [ncalo]     = jtpu_calo [clj.id];
	  calohcalSum[ncalo] = hcalSum_pf[clj.id];
	  caloecalSum[ncalo] = ecalSum_pf[clj.id];
	
	  trMax[npf]  = trackMax  [pfj.id];
	  chMax[npf]  = chargedMax[pfj.id];
	  phMax[npf]  = photonMax [pfj.id];
	  neMax[npf]  = neutralMax[pfj.id];
	  muMax[npf]  = muonMax   [pfj.id];
	  eMax [npf]  = eleMax    [pfj.id];
	
	  trSum[npf]  = trackSum  [pfj.id];
	  chSum[npf]  = chargedSum[pfj.id];
	  phSum[npf]  = photonSum [pfj.id];
	  neSum[npf]  = neutralSum[pfj.id];
	  muSum[npf]  = muonSum   [pfj.id];
	  eSum [npf]  = eleSum    [pfj.id];
	
	  hcalSum[npf] = hcalSum_pf[clj.id];
	  ecalSum[npf] = ecalSum_pf[clj.id];

	  if( kDataset == "mc" ){
	    if( sid[pfj.id] != -1 ){
	      pfrefidx[npf]=nref;
	      clrefidx[ncalo]=nref;
	      refpfid[nref] = npf;
	      refclid[nref] = ncalo;
	      subid  [nref] = sid[pfj.id];
	      refpt  [nref] = pfrefpt[pfj.id];
	      refeta [nref] = pfrefeta[pfj.id];
	      refphi [nref] = pfrefphi[pfj.id];
	      refdrjt[nref] = pfrefdrjt[pfj.id];
	      nref++;
	    }else{
	      pfrefidx[npf]=-999;
	      clrefidx[ncalo]=-999;
	    }
	  }

	  if(printDebug){
	    if( kDataset == "data" )std::cout <<"\t *** Matched" << " id : " << pfj.id << " " << clj.id << " pfpt :  " << pfj.pt << " calopt : " << clj.pt << std::endl;
	    else std::cout <<"\t *** Matched" << " id : " << pfj.id << " " << clj.id << " pfpt :  " << pfj.pt << " calopt : " << clj.pt << " spf : " << sid[pfj.id] << " scj : " << sid [clj.id] << " dr : " << pfrefdrjt[pfj.id] << std::endl;
	  }
	  //if( sid[pfj.id]!=0 && pfpt>20 )std::cout <<"\t *** Matched" << " pthat : " << pthat << " refpt : " << refpt << " pfpt :  " << pfj.pt << " calopt : " << clj.pt << " spf : " << sid[pfj.id] << " scj : " << sid [clj.id] << std::endl;	  
	  matchedJets++;	  
	  npf++;
	  ncalo++;
	  pfid  [pfj.id] = 1;
	  caloid[clj.id] = 1;
	}
      }//! itr loop
      

      //! Unmatched jets
      for(itr = mCaloPFMatchedJets.cbegin(); itr != mCaloPFMatchedJets.cend(); ++itr){
	CaloPFJetPair jetpair = (*itr);
	
	Jet clj = jetpair.first;
	Jet pfj = jetpair.second;
	
	//float delr  = deltaR(pfj.eta, pfj.phi, clj.eta, clj.phi);
	//float delpt = fabs(pfj.pt - clj.pt);
	//if( pfid[pfj.id]==1 || caloid[clj.id]==1 )continue;
	
	if( pfid[pfj.id] == 0 ){//! Unmatched PF jet
	  
	  isCaloMatch[npf]=0;
	  caloidx[npf]=-999;
	  deltar [npf]=-999;
	  if( JECOnFly )pfpt[npf] = pfj.pt;
	  else pfpt[npf] = jtpt [pfj.id];
	  calopt [npf]   = -999;
	  pfrawpt[npf]   = rawpt[pfj.id];
	  pfeta  [npf]   = jteta[pfj.id];
	  pfphi  [npf]   = jtphi[pfj.id];
	  pfpu   [npf]   = jtpu [pfj.id];
	  
	  trMax[npf]  = trackMax  [pfj.id];
	  chMax[npf]  = chargedMax[pfj.id];
	  phMax[npf]  = photonMax [pfj.id];
	  neMax[npf]  = neutralMax[pfj.id];
	  muMax[npf]  = muonMax   [pfj.id];
	  eMax [npf]  = eleMax    [pfj.id];
	  
	  trSum[npf]  = trackSum  [pfj.id];	
	  chSum[npf]  = chargedSum[pfj.id];
	  phSum[npf]  = photonSum [pfj.id];
	  neSum[npf]  = neutralSum[pfj.id];
	  muSum[npf]  = muonSum   [pfj.id];
	  eSum [npf]  = eleSum    [pfj.id];
	  
	  hcalSum[npf] = hcalSum_pf[pfj.id];
	  ecalSum[npf] = ecalSum_pf[pfj.id];
	  
	  if( kDataset == "mc" ){
	    if( sid[pfj.id] != -1 ){
	      pfrefidx[npf]=nref;
	      refpfid[nref] = npf;
	      refclid[nref] = -999;
	      subid  [nref] = sid[pfj.id];
	      refpt  [nref] = pfrefpt[pfj.id];
	      refeta [nref] = pfrefeta[pfj.id];
	      refphi [nref] = pfrefphi[pfj.id];
	      refdrjt[nref] = pfrefdrjt[pfj.id];
	      nref++;
	    }else{
	      pfrefidx[npf]=-999;
	    }
	  }
	  
	  if(printDebug){
	    if( kDataset == "data" )std::cout <<"\t %%% UnMatched PF" << " id  : " << pfj.id << " pfpt :  " << pfj.pt << std::endl;
	    else std::cout <<"\t %%% UnMatched PF" << " id  : " << pfj.id << " pfpt :  " << pfj.pt << " subid : " << sid[pfj.id] << " dr : " << pfrefdrjt[pfj.id] << std::endl;
	  }
	  unmatchedPFJets++;	  	  
	  npf++;
	  pfid  [pfj.id] = 1;	  
	}
	
	if( caloid[clj.id] == 0 ){//! Unmatched Calo jet
	  
	  isPFMatch[ncalo]=0;
	  pfidx[ncalo] = -999;	  
	  if( JECOnFly )calorecpt[ncalo] = clj.pt;
	  else calorecpt[ncalo] = jtpt_calo [clj.id];
	  calorawpt[ncalo] = rawpt_calo[clj.id];
	  caloeta[ncalo]   = jteta_calo[clj.id];
	  calophi[ncalo]   = jtphi_calo[clj.id];
	  calopu[ncalo]    = jtpu_calo [clj.id];
	  
	  calohcalSum[ncalo] = hcalSum_pf[clj.id];
	  caloecalSum[ncalo] = ecalSum_pf[clj.id];
	  
	  if( kDataset == "mc" ){
	    if( sid_calo[clj.id] != -1 ){
	      clrefidx[ncalo]=nref;
	      refpfid[nref] = -999;
	      refclid[nref] = ncalo;
	      subid [nref]  = sid_calo    [clj.id];
	      refpt [nref]  = refpt_calo  [clj.id];
	      refeta[nref]  = refeta_calo [clj.id];
	      refphi[nref]  = refphi_calo [clj.id];
	      refdrjt[nref] = refdrjt_calo[clj.id];
	      nref++;
	    }else{
	      clrefidx[ncalo]=-999;
	    }
	  } 
	  if(printDebug){
	    if( kDataset == "mc" )std::cout <<"\t XXX UnMatched Calo" << " id : " << clj.id  << " calopt : " << clj.pt << " subid : " << sid_calo [clj.id] << " dr : " << refdrjt_calo[clj.id] << std::endl;
	    else std::cout <<"\t XXX UnMatched Calo" << " id : " << clj.id  << " calopt : " << clj.pt << std::endl;
	  }
	  unmatchedCaloJets++;	  	  
	  ncalo++;
	  caloid[clj.id] = 1;	  
	}
      }
    }//! bothPFCalo
    
    if(printDebug){
      std::cout << std::endl;
      if( bothPFCalo    )std::cout<<" ****** Both PFCalo Event # " <<i;/*<<" vz  : "<<vz<<" hiBin : "<<hiBin;*/
      else if( onlyCalo )std::cout<<" ****** Only Calo   Event # " <<i;/*<<" vz  : "<<vz<<" hiBin : "<<hiBin;*/
      else if( onlyPF   )std::cout<<" ****** Only PF     Event # " <<i;/*<<" vz  : "<<vz<<" hiBin : "<<hiBin;*/
      std::cout << " " 
		<<" All ==> PF : " << nref_pf <<", CALO : "<< nref_calo << ";"  
		<<" After cut ==> PF : " << pfjets << ", Calo : "  << calojets << ";"
		<<" mCALOPF : "<< matchedJets <<", unmPF : "<<  unmatchedPFJets <<", unmCalo : "<<  unmatchedCaloJets 
		<<std::endl;
      std::cout << "------------------------------------End Event # " << i <<"------------------------------------------------------------------ " << "\n"<<std::endl;
    }

    if(npf>0 || ncalo>0)jetTree->Fill();

  }//! event loop ends

  //! Delete JECOnFly things
  delete parHI_l2_PF;
  delete parHI_l3_PF;
  delete _JEC_HI_PF;

  delete parHI_l2_Calo;
  delete parHI_l3_Calo;
  delete _JEC_HI_Calo;


  //! Write to output file
  fout->cd();
  fout->Write();
  fout->Close();

  
  //! Check
  timer.Stop();
  double rtime  = timer.RealTime();
  double ctime  = timer.CpuTime();
  
  std::cout<<std::endl;
  std::cout<<Form("RealTime=%f seconds, CpuTime=%f seconds",rtime,ctime)<<std::endl;
  std::cout<<std::endl;
  std::cout<<"Good bye : " <<"\t"<<std::endl;
  return 1;
}

int GetEtaBin(float eta)
{
  for(int ix=0;ix<neta;ix++){
    if(eta>=etabins[ix] && eta<etabins[ix+1]){
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
float delphi(float phi1, float phi2)
{
  float dphi = phi2 - phi1;
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
  else if(bin>20  && bin<=60 )ibin=2;  //! 10-30%
  else if(bin>60  && bin<=100)ibin=3;  //! 30-50%
  else if(bin>100 && bin<=140)ibin=4;  //! 50-70%
  else if(bin>140 && bin<=180)ibin=5;  //! 70-90%
  else if(bin>180 && bin<=200)ibin=6;  //! 90-100%
  return ibin;
}
float deltaR(float eta1, float phi1, float eta2, float phi2)
{
  float deta = eta1 - eta2;
  float dphi = fabs(phi1 - phi2);
  if(dphi > pi)dphi -= 2*pi;
  float dr = sqrt(pow(deta,2) + pow(dphi,2));
  return dr;
}
double GetXsec(double maxpt)
{
  //std::cout << " GetXsec() ::: max pt hat : " << maxpt << std::endl;                                                                          
  double effxsec=0;
  for(int i=0; i<11; i++){
    if(fabs(maxpt - xsec[i][2]) < 1e-08){
      effxsec = xsec[i][0] - xsec[i+1][0];
      //effxsec = xsec[i][0];                                                                                                                   
      //std::cout <<"\t \t  effective xsec : " << effxsec << "\t"<<  xsec[i][0] << "\t pthat : "<< xsec[i][1] << std::endl;                     
      return effxsec;
    }
  }
  return  1;
}
void GetCentWeight(TH1D *hCentWeight)
{
  hCentWeight->SetBinContent(1,6.7634);
  hCentWeight->SetBinContent(2,8.9638);
  hCentWeight->SetBinContent(3,8.32666);
  hCentWeight->SetBinContent(4,8.85033);
  hCentWeight->SetBinContent(5,7.48557);
  hCentWeight->SetBinContent(6,7.07842);
  hCentWeight->SetBinContent(7,7.17439);
  hCentWeight->SetBinContent(8,7.39451);
  hCentWeight->SetBinContent(9,7.03825);
  hCentWeight->SetBinContent(10,8.04546);
  hCentWeight->SetBinContent(11,6.32941);
  hCentWeight->SetBinContent(12,4.84289);
  hCentWeight->SetBinContent(13,7.05322);
  hCentWeight->SetBinContent(14,5.6361);
  hCentWeight->SetBinContent(15,5.59001);
  hCentWeight->SetBinContent(16,4.90395);
  hCentWeight->SetBinContent(17,5.13768);
  hCentWeight->SetBinContent(18,4.98226);
  hCentWeight->SetBinContent(19,3.76756);
  hCentWeight->SetBinContent(20,4.44141);
  hCentWeight->SetBinContent(21,4.01054);
  hCentWeight->SetBinContent(22,3.29702);
  hCentWeight->SetBinContent(23,3.21606);
  hCentWeight->SetBinContent(24,3.60559);
  hCentWeight->SetBinContent(25,3.36325);
  hCentWeight->SetBinContent(26,2.6244);
  hCentWeight->SetBinContent(27,3.17479);
  hCentWeight->SetBinContent(28,2.6614);
  hCentWeight->SetBinContent(29,2.1703);
  hCentWeight->SetBinContent(30,2.5898);
  hCentWeight->SetBinContent(31,2.56079);
  hCentWeight->SetBinContent(32,2.4732);
  hCentWeight->SetBinContent(33,2.02533);
  hCentWeight->SetBinContent(34,2.03333);
  hCentWeight->SetBinContent(35,1.75553);
  hCentWeight->SetBinContent(36,1.61111);
  hCentWeight->SetBinContent(37,1.55114);
  hCentWeight->SetBinContent(38,1.63142);
  hCentWeight->SetBinContent(39,1.57826);
  hCentWeight->SetBinContent(40,1.45919);
  hCentWeight->SetBinContent(41,1.5094);
  hCentWeight->SetBinContent(42,1.32344);
  hCentWeight->SetBinContent(43,1.36376);
  hCentWeight->SetBinContent(44,1.00481);
  hCentWeight->SetBinContent(45,0.924943);
  hCentWeight->SetBinContent(46,1.04942);
  hCentWeight->SetBinContent(47,0.976863);
  hCentWeight->SetBinContent(48,0.864318);
  hCentWeight->SetBinContent(49,0.772694);
  hCentWeight->SetBinContent(50,0.864502);
  hCentWeight->SetBinContent(51,0.829401);
  hCentWeight->SetBinContent(52,0.75895);
  hCentWeight->SetBinContent(53,0.702901);
  hCentWeight->SetBinContent(54,0.545314);
  hCentWeight->SetBinContent(55,0.571537);
  hCentWeight->SetBinContent(56,0.447445);
  hCentWeight->SetBinContent(57,0.565426);
  hCentWeight->SetBinContent(58,0.411747);
  hCentWeight->SetBinContent(59,0.381474);
  hCentWeight->SetBinContent(60,0.389027);
  hCentWeight->SetBinContent(61,0.345071);
  hCentWeight->SetBinContent(62,0.39263);
  hCentWeight->SetBinContent(63,0.340061);
  hCentWeight->SetBinContent(64,0.363676);
  hCentWeight->SetBinContent(65,0.342351);
  hCentWeight->SetBinContent(66,0.311693);
  hCentWeight->SetBinContent(67,0.2503);
  hCentWeight->SetBinContent(68,0.258714);
  hCentWeight->SetBinContent(69,0.269137);
  hCentWeight->SetBinContent(70,0.278774);
  hCentWeight->SetBinContent(71,0.254098);
  hCentWeight->SetBinContent(72,0.198022);
  hCentWeight->SetBinContent(73,0.217276);
  hCentWeight->SetBinContent(74,0.233573);
  hCentWeight->SetBinContent(75,0.233931);
  hCentWeight->SetBinContent(76,0.205296);
  hCentWeight->SetBinContent(77,0.187256);
  hCentWeight->SetBinContent(78,0.206262);
  hCentWeight->SetBinContent(79,0.192841);
  hCentWeight->SetBinContent(80,0.174259);
  hCentWeight->SetBinContent(81,0.157487);
  hCentWeight->SetBinContent(82,0.1807);
  hCentWeight->SetBinContent(83,0.135957);
  hCentWeight->SetBinContent(84,0.143054);
  hCentWeight->SetBinContent(85,0.158412);
  hCentWeight->SetBinContent(86,0.158663);
  hCentWeight->SetBinContent(87,0.130637);
  hCentWeight->SetBinContent(88,0.105144);
  hCentWeight->SetBinContent(89,0.109533);
  hCentWeight->SetBinContent(90,0.115536);
  hCentWeight->SetBinContent(91,0.103691);
  hCentWeight->SetBinContent(92,0.0988995);
  hCentWeight->SetBinContent(93,0.0899957);
  hCentWeight->SetBinContent(94,0.091202);
  hCentWeight->SetBinContent(95,0.0947045);
  hCentWeight->SetBinContent(96,0.0990303);
  hCentWeight->SetBinContent(97,0.074485);
  hCentWeight->SetBinContent(98,0.0904833);
  hCentWeight->SetBinContent(99,0.0745771);
  hCentWeight->SetBinContent(100,0.0746246);
  hCentWeight->SetBinContent(101,0.0666776);
  hCentWeight->SetBinContent(102,0.0631808);
  hCentWeight->SetBinContent(103,0.0645528);
  hCentWeight->SetBinContent(104,0.0721828);
  hCentWeight->SetBinContent(105,0.0640522);
  hCentWeight->SetBinContent(106,0.0544978);
  hCentWeight->SetBinContent(107,0.0602298);
  hCentWeight->SetBinContent(108,0.052432);
  hCentWeight->SetBinContent(109,0.0499806);
  hCentWeight->SetBinContent(110,0.05452);
  hCentWeight->SetBinContent(111,0.0456856);
  hCentWeight->SetBinContent(112,0.0464227);
  hCentWeight->SetBinContent(113,0.0389109);
  hCentWeight->SetBinContent(114,0.0429926);
  hCentWeight->SetBinContent(115,0.0423068);
  hCentWeight->SetBinContent(116,0.0436439);
  hCentWeight->SetBinContent(117,0.032317);
  hCentWeight->SetBinContent(118,0.0351724);
  hCentWeight->SetBinContent(119,0.0378572);
  hCentWeight->SetBinContent(120,0.0356574);
  hCentWeight->SetBinContent(121,0.0300515);
  hCentWeight->SetBinContent(122,0.0294732);
  hCentWeight->SetBinContent(123,0.0279459);
  hCentWeight->SetBinContent(124,0.0275134);
  hCentWeight->SetBinContent(125,0.0274872);
  hCentWeight->SetBinContent(126,0.0262874);
  hCentWeight->SetBinContent(127,0.0228082);
  hCentWeight->SetBinContent(128,0.0268362);
  hCentWeight->SetBinContent(129,0.0235638);
  hCentWeight->SetBinContent(130,0.019708);
  hCentWeight->SetBinContent(131,0.0203582);
  hCentWeight->SetBinContent(132,0.0191097);
  hCentWeight->SetBinContent(133,0.0169256);
  hCentWeight->SetBinContent(134,0.018112);
  hCentWeight->SetBinContent(135,0.0175009);
  hCentWeight->SetBinContent(136,0.0144258);
  hCentWeight->SetBinContent(137,0.0155731);
  hCentWeight->SetBinContent(138,0.0135958);
  hCentWeight->SetBinContent(139,0.0129593);
  hCentWeight->SetBinContent(140,0.0134124);
  hCentWeight->SetBinContent(141,0.0102854);
  hCentWeight->SetBinContent(142,0.00902376);
  hCentWeight->SetBinContent(143,0.00938477);
  hCentWeight->SetBinContent(144,0.00979958);
  hCentWeight->SetBinContent(145,0.00981297);
  hCentWeight->SetBinContent(146,0.00830205);
  hCentWeight->SetBinContent(147,0.00828065);
  hCentWeight->SetBinContent(148,0.0075616);
  hCentWeight->SetBinContent(149,0.00721783);
  hCentWeight->SetBinContent(150,0.00742391);
  hCentWeight->SetBinContent(151,0.00668121);
  hCentWeight->SetBinContent(152,0.00490303);
  hCentWeight->SetBinContent(153,0.00689083);
  hCentWeight->SetBinContent(154,0.00620564);
  hCentWeight->SetBinContent(155,0.00501006);
  hCentWeight->SetBinContent(156,0.00467418);
  hCentWeight->SetBinContent(157,0.00358751);
  hCentWeight->SetBinContent(158,0.0043082);
  hCentWeight->SetBinContent(159,0.00353042);
  hCentWeight->SetBinContent(160,0.00356054);
  hCentWeight->SetBinContent(161,0.00277187);
  hCentWeight->SetBinContent(162,0.00259774);
  hCentWeight->SetBinContent(163,0.0026294);
  hCentWeight->SetBinContent(164,0.00266786);
  hCentWeight->SetBinContent(165,0.00251157);
  hCentWeight->SetBinContent(166,0.00218918);
  hCentWeight->SetBinContent(167,0.00229047);
  hCentWeight->SetBinContent(168,0.00178743);
  hCentWeight->SetBinContent(169,0.00182462);
  hCentWeight->SetBinContent(170,0.00204086);
  hCentWeight->SetBinContent(171,0.00189708);
  hCentWeight->SetBinContent(172,0.00203718);
  hCentWeight->SetBinContent(173,0.0020711);
  hCentWeight->SetBinContent(174,0.00180765);
  hCentWeight->SetBinContent(175,0.00159439);
  hCentWeight->SetBinContent(176,0.00216191);
  hCentWeight->SetBinContent(177,0.00136735);
  hCentWeight->SetBinContent(178,0.00182475);
  hCentWeight->SetBinContent(179,0.00160661);
  hCentWeight->SetBinContent(180,0.00138471);
  hCentWeight->SetBinContent(181,0.00156103);
  hCentWeight->SetBinContent(182,0.00200855);
  hCentWeight->SetBinContent(183,0.0023071);
  hCentWeight->SetBinContent(184,0.00211314);
  hCentWeight->SetBinContent(185,0.00155022);
  hCentWeight->SetBinContent(186,0.00204334);
  hCentWeight->SetBinContent(187,0.00180985);
  hCentWeight->SetBinContent(188,0.00165799);
  hCentWeight->SetBinContent(189,0.00253497);
  hCentWeight->SetBinContent(190,0.00271872);
  hCentWeight->SetBinContent(191,0.00223219);
  hCentWeight->SetBinContent(192,0.00272361);
  hCentWeight->SetBinContent(193,0.00296343);
  hCentWeight->SetBinContent(194,0.00455219);
  hCentWeight->SetBinContent(195,0.00947736);
  hCentWeight->SetBinContent(196,0.0159602);
  hCentWeight->SetBinContent(197,0.0463495);
  hCentWeight->SetBinContent(198,0.156464);
  hCentWeight->SetBinContent(199,0);
  hCentWeight->SetBinContent(200,0);
}


void AddInputFiles(TChain *tch, string inputname, string inputTree)
{
  //cout << " Add input files " << tch->GetName() << "  " << inputname.c_str() <<endl;
  //cout<<endl;
  std::stringstream tmpstr(inputname.c_str());
  std::string segment;
  std::vector<string> infiles;

  while(std::getline(tmpstr, segment, ',')){
    infiles.push_back(segment);
  }

  int im=0;
  for(std::vector<string>::iterator it=infiles.begin(); it!=infiles.end(); ++it, im++){
    std::string sFile = (*it);
    //   cout <<im<<"  "<< sFile.c_str() << endl;
    string stree = sFile+"/"+inputTree;
    tch->Add(stree.c_str());
  }
  //  cout<<endl;
}
