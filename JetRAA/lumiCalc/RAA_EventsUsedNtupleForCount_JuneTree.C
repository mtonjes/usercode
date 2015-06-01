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
// root -l -q -b  RAA_EventsUsedNtupleForCount_JuneTree.C+ >& out_ak3PuPF_PbPb_DATA_PawanNtupleJune1.txt &
// root -l -q -b  'RAA_EventsUsedNtupleForCount_JuneTree.C+("pp","DATA","PF","3")' >& out_ak3PF_pp_DATA_PawanNtupleJune1.txt &
// edit out_ak3PuPF_PbPb_DATA_PawanNtupleJune1.txt to remove any root lines printed that aren't run, lumi
// python CMSSW_5_3_20/src/FWCore/PythonUtilities/scripts/csv2json.py out_ak3PuPF_PbPb_DATA_PawanNtupleJune1.txt >& json_PawanNtuple_June1_PbPbData_fromcsv.txt
// lumiCalc2.py recorded -i json_PawanNtuple_June1_PbPbData_fromcsv.txt --hltpath "HLT_HIJet80_v1"
// lumiCalc2.py recorded -i json_PawanNtuple_June1_ppData_fromcsv.txt --hltpath "HLT_PAJet80_NoJetID_v1"

static const int nbins_cent = 7;
static const Double_t boundaries_cent[nbins_cent+1] = {0,2,4,12,20,28,36,40};// multiply by 2.5 to get your actual centrality % (old 2011 data) 
//now we have to multiply by 5, since centrality goes from 0-200. 

const double ketacut=2.0;
const double kptrawcut =0.0;
const double kptrecocut=1.0;
const double kdelrcut=0.3;

const int ncen=8;
const char *cdir [ncen] = {"05","510","1030","3050","5070","7090","90100","pp"};
const char *ccent[ncen] = {"0-5%","5-10%","10-30%","30-50%","50-70%","70-90%","90-100%","pp"};
#define pi 3.14159265
#define nmax 500
double delphi(double /*phi1*/, double /*phi2*/);
double deltaR(float /*eta1*/, float /*phi1*/,
              float /*eta2*/, float /*phi2*/);
 int GetCentBin(int /*hiBin*/);
             
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

// float deltaR(float eta1, float phi1, float eta2, float phi2)
// {
//   float pi=TMath::Pi();
//   
//   float deta = eta1 - eta2;
//   float dphi = fabs(phi1 - phi2);
//   if(dphi > pi)dphi -= 2*pi;
//   float dr = sqrt(pow(deta,2) + pow(dphi,2));
//   return dr;
// }
double deltaR(float eta1, float phi1, float eta2, float phi2)
{
  float deta = eta1 - eta2;
  float dphi = fabs(phi1 - phi2);
  if(dphi > pi)dphi -= 2*pi;
  double dr = sqrt(pow(deta,2) + pow(dphi,2));
  return dr;
}
double delphi(double phi1, double phi2)
{
  double dphi = phi2 - phi1;
  dphi = fabs(atan2(sin(dphi),cos(dphi)));
  return dphi;
}
// 
// float deltaphi(float phi1, float phi2)
// {
//   float pi=TMath::Pi();
//  
//   float dphi = fabs(phi1 - phi2);
//   if(dphi > pi)dphi -= 2*pi;
//   return dphi;
// }

static const int nbins_pt = 30;
static const double boundaries_pt[nbins_pt+1] = {  3, 4, 5, 7, 9, 12, 15, 18, 21, 24, 28,  32, 37, 43, 49, 56,  64, 74, 84, 97, 114,  133, 153, 174, 196,  220, 245, 300, 330, 362, 395};



using namespace std;

void RAA_EventsUsedNtupleForCount_JuneTree(std::string kSpecies="PbPb", //! pp, PbPb, PbPb_MinBias
	     std::string kDataset="DATA",   //! MC, DATA
	     std::string kAlgo="PF",      //! PF, Calo
	     std::string kRadii="3"      //! 2,3,4
	     )
{

//  Int_t unm=1;
//  Int_t mat=1;
  Int_t Short=0;
  long TestEntries=100000;
  long entries;
// CMSSW/FWCore/PythonUtilities/python/LumiList.py  NOPE
// python CMSSW_5_3_20/src/FWCore/PythonUtilities/scripts/csv2json.py PartialCSV_Pawan.txt  YES
//  timer.Start();
  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();
 
 
   int mincen=0;
  int maxcen=ncen;
   
  std::string kAlgName="";
  if( kSpecies == "pp" ){
    kAlgName="ak";
    mincen=ncen-1;
    maxcen=ncen;
  }else{
    kAlgName="akPu";
    mincen=0;
    maxcen=ncen-1;
  }   
  // the cut is a 3 step cut based on the different value of the calopt/pfpt - copy the following lines into your loop (with the corresponding branch address set)
  // if(calopt/pfpt <= 0.5 && eMax/Sumcand < 0.05) hGood->Fill();
  // if(calopt/pfpt > 0.5 && calopt/pfpt <= 0.85 && eMax/Sumcand < (18/7 *(Float_t)calopt_1/pfpt_1 - 9/7)) ) hGood->Fill();
  // if(calopt/pfpt > 0.85 & eMax/Sumcand > 0.9) hGood->Fill();
  
  
  TFile *fin=0;
  TTree *tree=0;

  Float_t Jet55_prescl = 2.0475;
  Float_t Jet40_prescl = 9.275;
  if( kDataset == "MC" ){
    Jet55_prescl = 1;
    Jet40_prescl = 1;
  }

  fin = new TFile(Form("/mnt/hadoop/cms/store/user/pawan/trees/JetRaaTree_%s234_%s_%s.root",kAlgName.c_str(), kSpecies.c_str(), kDataset.c_str()),"r");
  tree = (TTree*)fin->Get(Form("%sJetAnalyzer/jetTree",(kAlgName+kRadii).c_str()));  

 // Declaration of leaf types                                                                                                                                               
  //! Event info
  Int_t           hiBin;
  Int_t           run_value;
  Int_t           evt_value;
  Int_t           lumi_value;
  Float_t         vz;
 // variables I don't use in this simple code 
//   Int_t           jet80;
//   Int_t           jet80_prescl;
//   Int_t           jet65;
//   Int_t           jet65_prescl;
//   Int_t           jet55;
//   Int_t           jet55_prescl;
//   Int_t           jet60;
//   Int_t           jet60_prescl;
//   Int_t           jet40;
//   Int_t           jet40_prescl;
//   Int_t           jetMB;
//   Int_t           jetMB_prescl;
//   Int_t           L1_MB;
//   Int_t           L1_MB_p;
//   Int_t           L1_sj36;
//   Int_t           L1_sj52;
//   Int_t           L1_sj36_p;
//   Int_t           L1_sj52_p;
// 
//   //! PF jets
//   Int_t           npf; 
//   Int_t           isCaloMatch[nmax]; //! Calo matched PF jet (bool)
//   Int_t           caloidx[nmax];     //! matched Calo jet index
//   Int_t           pfrefidx[nmax];    //! PF -> REF matched index
//   Float_t         deltar[nmax];      //! PF- CALO deltar (currently 0.2)
//   Float_t         calopt[nmax];      //! matched calo jet pt
//   Float_t         pfpt[nmax];       
//   Float_t         pfrawpt[nmax];    
//   Float_t         pfeta[nmax];      
//   Float_t         pfphi[nmax];      
//   Float_t         pfpu[nmax];       
//   Float_t         trMax[nmax];      
//   Float_t         chMax[nmax];      
//   Float_t         chSum[nmax];      
//   Float_t         phMax[nmax];      
//   Float_t         phSum[nmax];      
//   Float_t         neMax[nmax];      
//   Float_t         neSum[nmax];      
//   Float_t         muMax[nmax];      
//   Float_t         muSum[nmax];      
//   Float_t         eMax[nmax];       
//   Float_t         eSum[nmax];
//   Float_t         hcalSum[nmax];    
//   Float_t         ecalSum[nmax];    
// 
//   //! Calo jets
//   Int_t           ncalo;
//   Int_t           isPFMatch[nmax]; //! PF matched jet 
//   Int_t           pfidx[nmax];     //! PF matched index
//   Int_t           clrefidx[nmax];  //! CALO -> REF matched index
//   Float_t         calorecpt[nmax];
//   Float_t         calorawpt[nmax];
//   Float_t         caloeta[nmax];
//   Float_t         calophi[nmax];
//   Float_t         calopu[nmax];
//   Float_t         calohcalSum[nmax];
//   Float_t         caloecalSum[nmax];
// 
//   //! Ref MC jet
//   Float_t  pthat;
//   Double_t weight;
//   Int_t    nref;
//   Int_t    refpfid[nmax]; //! REF -> PF match index
//   Int_t    refclid[nmax]; //! REF -> CALO match index
//   Int_t    subid[nmax];
//   Float_t  refpt[nmax];
//   Float_t  refeta[nmax];
//   Float_t  refphi[nmax];
//   Float_t  refdrjt[nmax];                                   

  
  tree->SetBranchAddress("hiBin", &hiBin);
  tree->SetBranchAddress("run_value", &run_value);
  tree->SetBranchAddress("evt_value", &evt_value);
  tree->SetBranchAddress("lumi_value", &lumi_value);
  tree->SetBranchAddress("vz", &vz);
 // this is so simple, I don't even want the rest of the branches, so I won't even load them... 
//   if( kSpecies == "pp" ){
//     tree->SetBranchAddress("jet80", &jet80);
//     tree->SetBranchAddress("jet80_prescl", &jet80_prescl);
//     tree->SetBranchAddress("jet60", &jet60);
//     tree->SetBranchAddress("jet60_prescl", &jet60_prescl);
//     tree->SetBranchAddress("jet40", &jet40);
//     tree->SetBranchAddress("jet40_prescl", &jet40_prescl);
//   }else if( kSpecies == "PbPb" ){
//     tree->SetBranchAddress("jet80", &jet80);
//     tree->SetBranchAddress("jet80_prescl", &jet80_prescl);
//     tree->SetBranchAddress("jet65", &jet65);
//     tree->SetBranchAddress("jet65_prescl", &jet65_prescl);
//     tree->SetBranchAddress("jet55", &jet55);
//     tree->SetBranchAddress("jet55_prescl", &jet55_prescl);
//   }else if( kSpecies == "PbPb_MinBias" ){
//     tree->SetBranchAddress("jetMB", &jetMB);
//     tree->SetBranchAddress("jetMB_prescl", &jetMB_prescl);
//     tree->SetBranchAddress("L1_MB", &L1_MB);
//     tree->SetBranchAddress("L1_MB_p", &L1_MB_p);
//     tree->SetBranchAddress("L1_sj36", &L1_sj36);
//     tree->SetBranchAddress("L1_sj52", &L1_sj52);
//     tree->SetBranchAddress("L1_sj36_p", &L1_sj36_p);
//     tree->SetBranchAddress("L1_sj52_p", &L1_sj52_p);
//   }
//   tree->SetBranchAddress("npf", &npf);
//   tree->SetBranchAddress("isCaloMatch", isCaloMatch);
//   tree->SetBranchAddress("caloidx", caloidx);
//   tree->SetBranchAddress("deltar", deltar);
//   tree->SetBranchAddress("calopt", calopt);
//   tree->SetBranchAddress("pfpt", pfpt);
//   tree->SetBranchAddress("pfrawpt", pfrawpt);
//   tree->SetBranchAddress("pfeta", pfeta);
//   tree->SetBranchAddress("pfphi", pfphi);
//   tree->SetBranchAddress("pfpu", pfpu);
//   tree->SetBranchAddress("trMax", trMax);
//   tree->SetBranchAddress("chMax", chMax);
//   tree->SetBranchAddress("chSum", chSum);
//   tree->SetBranchAddress("phMax", phMax);
//   tree->SetBranchAddress("phSum", phSum);
//   tree->SetBranchAddress("neMax", neMax);
//   tree->SetBranchAddress("neSum", neSum);
//   tree->SetBranchAddress("muMax", muMax);
//   tree->SetBranchAddress("muSum", muSum);
//   tree->SetBranchAddress("eMax", eMax);
//   tree->SetBranchAddress("eSum", eSum);
//   tree->SetBranchAddress("hcalSum", hcalSum);
//   tree->SetBranchAddress("ecalSum", ecalSum);
// 
//   tree->SetBranchAddress("ncalo", &ncalo);
//   tree->SetBranchAddress("isPFMatch", isPFMatch);
//   tree->SetBranchAddress("pfidx", pfidx);
//   tree->SetBranchAddress("calorecpt", calorecpt);
//   tree->SetBranchAddress("calorawpt", calorawpt);
//   tree->SetBranchAddress("caloeta", caloeta);
//   tree->SetBranchAddress("calophi", calophi);
//   tree->SetBranchAddress("calopu", calopu);
//   tree->SetBranchAddress("calohcalSum", calohcalSum);
//   tree->SetBranchAddress("caloecalSum", caloecalSum);
// 
//   //! If you are not using calojets info just do not read and load them
//   tree->SetBranchStatus("ncalo", 0,0);
//   tree->SetBranchStatus("isPFMatch",0,0);
//   tree->SetBranchStatus("pfidx",0,0);
//   tree->SetBranchStatus("calorecpt",0,0);
//   tree->SetBranchStatus("calorawpt",0,0);
//   tree->SetBranchStatus("caloeta",0,0);
//   tree->SetBranchStatus("calophi",0,0);
//   tree->SetBranchStatus("calopu",0,0);
//   tree->SetBranchStatus("calohcalSum",0,0);
//   tree->SetBranchStatus("caloecalSum",0,0);
// 
// 
//   if( kDataset == "MC" ){
//     tree->SetBranchAddress("pthat", &pthat);
//     tree->SetBranchAddress("weight", &weight);
//     tree->SetBranchAddress("pfrefidx", pfrefidx); //! PF   -> REF match
//     tree->SetBranchAddress("clrefidx", clrefidx); //! Calo -> REF match
//     tree->SetBranchAddress("nref", &nref);
//     tree->SetBranchAddress("refpfid", refpfid);  //! REF -> PF match
//     tree->SetBranchAddress("refclid", refclid);  //! REF -> CALO match
//     tree->SetBranchAddress("subid", subid);
//     tree->SetBranchAddress("refpt", refpt);
//     tree->SetBranchAddress("refeta", refeta);
//     tree->SetBranchAddress("refphi", refphi);
//     tree->SetBranchAddress("refdrjt", refdrjt);
//   }


// run, lumi definitions
  Int_t maxrun=70,maxlumi=75000;
  Int_t eid=0;
  Int_t run[maxlumi];
  Int_t lumi[maxlumi];
  Int_t eidnow=0;
  Int_t matched=-999;
  
  for(int i=0;i<maxlumi;i++){
    run[i]=-999;
  }
  for(int j=0;j<maxlumi;j++){
    lumi[j]=-999;
  } 
  
// test mode is Short=1
  if(Short==1){
   entries=TestEntries;
  } else {
   entries = tree->GetEntries();
  }
  cout<<"Looping over tree "<<endl;

  for(long nentry = 0; nentry < entries; ++nentry ){

      
      tree->GetEntry(nentry);
 
  //     cout<<run_value<<","<<lumi_value<<","<<evt_value<<endl;     
       matched=-999;
  	 for(int ieid=0;ieid<(eidnow+1);ieid++){
  	   if(matched==1){ 
  	      continue; 
  	   }
	   if(run_value==run[ieid] && lumi_value==lumi[ieid]){
	    matched=1;
	   } else {
        matched=0;
	   }
	 }   
	 if(matched==0){
	     run[eidnow]=run_value;
	     lumi[eidnow]=lumi_value;
          cout<<run[eidnow]<<","<<lumi[eidnow]<<endl;     
	     eidnow++; 
    }  
	 
      // do we want event count before centrality selection? I think so...      
//      if(cBin == -1 || cBin >= nbins_cent) continue;
      
      
    
  }// end of looping over events

 

//   TFile fout("EventCounting.root","RECREATE");

//  fout.cd();
  // write some tree!

//  fout.Close();

    }
