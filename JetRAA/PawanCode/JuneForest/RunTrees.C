

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


using namespace std;

#ifdef _MAKECINT_
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#endif

#define pi 3.14159265
#define nmax 500


void MakeIndHist(TProfile *&/*hist*/);
void MakeIndHist(TH1D *&/*hist*/);

int GetPhiBin(float /*phi*/);
int GetEtaBin(float /*eta*/);
int GetEtaJECBin(float /*eta*/);
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

const double ptbins[] = {
  3, 4, 5, 7, 9, 12,
  15, 18, 21, 24, 28,
  32, 37, 43, 49, 56,
  64, 74, 84, 97, 114,
  133, 153, 174, 196,
  220, 245, 300,
  330, 362, 395,
  430, 468, 507,
  548
};
const int nbins = sizeof(ptbins)/sizeof(double) - 1;

const double etabins[] = {0.00, 1.00, 1.80, 2.00};
const int neta = sizeof(etabins)/sizeof(double) - 1;

const double etabins_ref[] = {-2.000, -1.4000, -0.4500, 0.000, 0.4500, 1.400, 2.000};
const int neta_ref = sizeof(etabins_ref)/sizeof(double) - 1;


const double phibins[] = {-3.141,-2.100,-1.500,-0.800,-0.300,0.300,0.800,1.500,2.100,3.141};
const int nphi = sizeof(phibins)/sizeof(double) - 1;

int rbins=50;
double rbinl=0.0;
double rbinh=2.0;

TStopwatch timer;
int RunTrees(std::string kSpecies="PbPb", //! pp, PbPb, PbPb_MinBias
	     std::string kDataset="MC",   //! MC, DATA
	     std::string kAlgo="PF",      //! PF, Calo
	     std::string kRadii="3"      //! 2,3,4
	     )
{

  timer.Start();
  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();

  bool printDebug=false;

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
  Int_t           jet80;
  Int_t           jet80_prescl;
  Int_t           jet65;
  Int_t           jet65_prescl;
  Int_t           jet55;
  Int_t           jet55_prescl;
  Int_t           jet60;
  Int_t           jet60_prescl;
  Int_t           jet40;
  Int_t           jet40_prescl;
  Int_t           jetMB;
  Int_t           jetMB_prescl;
  Int_t           L1_MB;
  Int_t           L1_MB_p;
  Int_t           L1_sj36;
  Int_t           L1_sj52;
  Int_t           L1_sj36_p;
  Int_t           L1_sj52_p;

  //! PF jets
  Int_t           npf; 
  Int_t           isCaloMatch[nmax]; //! Calo matched PF jet (bool)
  Int_t           caloidx[nmax];     //! matched Calo jet index
  Int_t           pfrefidx[nmax];    //! PF -> REF matched index
  Float_t         deltar[nmax];      //! PF- CALO deltar (currently 0.2)
  Float_t         calopt[nmax];      //! matched calo jet pt
  Float_t         pfpt[nmax];       
  Float_t         pfrawpt[nmax];    
  Float_t         pfeta[nmax];      
  Float_t         pfphi[nmax];      
  Float_t         pfpu[nmax];       
  Float_t         trMax[nmax];      
  Float_t         chMax[nmax];      
  Float_t         chSum[nmax];      
  Float_t         phMax[nmax];      
  Float_t         phSum[nmax];      
  Float_t         neMax[nmax];      
  Float_t         neSum[nmax];      
  Float_t         muMax[nmax];      
  Float_t         muSum[nmax];      
  Float_t         eMax[nmax];       
  Float_t         eSum[nmax];
  Float_t         hcalSum[nmax];    
  Float_t         ecalSum[nmax];    

  //! Calo jets
  Int_t           ncalo;
  Int_t           isPFMatch[nmax]; //! PF matched jet 
  Int_t           pfidx[nmax];     //! PF matched index
  Int_t           clrefidx[nmax];  //! CALO -> REF matched index
  Float_t         calorecpt[nmax];
  Float_t         calorawpt[nmax];
  Float_t         caloeta[nmax];
  Float_t         calophi[nmax];
  Float_t         calopu[nmax];
  Float_t         calohcalSum[nmax];
  Float_t         caloecalSum[nmax];

  //! Ref MC jet
  Float_t  pthat;
  Double_t weight;
  Int_t    nref;
  Int_t    refpfid[nmax]; //! REF -> PF match index
  Int_t    refclid[nmax]; //! REF -> CALO match index
  Int_t    subid[nmax];
  Float_t  refpt[nmax];
  Float_t  refeta[nmax];
  Float_t  refphi[nmax];
  Float_t  refdrjt[nmax];                                   

  
  tree->SetBranchAddress("hiBin", &hiBin);
  tree->SetBranchAddress("run_value", &run_value);
  tree->SetBranchAddress("evt_value", &evt_value);
  tree->SetBranchAddress("lumi_value", &lumi_value);
  tree->SetBranchAddress("vz", &vz);
  if( kSpecies == "pp" ){
    tree->SetBranchAddress("jet80", &jet80);
    tree->SetBranchAddress("jet80_prescl", &jet80_prescl);
    tree->SetBranchAddress("jet60", &jet60);
    tree->SetBranchAddress("jet60_prescl", &jet60_prescl);
    tree->SetBranchAddress("jet40", &jet40);
    tree->SetBranchAddress("jet40_prescl", &jet40_prescl);
  }else if( kSpecies == "PbPb" ){
    tree->SetBranchAddress("jet80", &jet80);
    tree->SetBranchAddress("jet80_prescl", &jet80_prescl);
    tree->SetBranchAddress("jet65", &jet65);
    tree->SetBranchAddress("jet65_prescl", &jet65_prescl);
    tree->SetBranchAddress("jet55", &jet55);
    tree->SetBranchAddress("jet55_prescl", &jet55_prescl);
  }else if( kSpecies == "PbPb_MinBias" ){
    tree->SetBranchAddress("jetMB", &jetMB);
    tree->SetBranchAddress("jetMB_prescl", &jetMB_prescl);
    tree->SetBranchAddress("L1_MB", &L1_MB);
    tree->SetBranchAddress("L1_MB_p", &L1_MB_p);
    tree->SetBranchAddress("L1_sj36", &L1_sj36);
    tree->SetBranchAddress("L1_sj52", &L1_sj52);
    tree->SetBranchAddress("L1_sj36_p", &L1_sj36_p);
    tree->SetBranchAddress("L1_sj52_p", &L1_sj52_p);
  }
  tree->SetBranchAddress("npf", &npf);
  tree->SetBranchAddress("isCaloMatch", isCaloMatch);
  tree->SetBranchAddress("caloidx", caloidx);
  tree->SetBranchAddress("deltar", deltar);
  tree->SetBranchAddress("calopt", calopt);
  tree->SetBranchAddress("pfpt", pfpt);
  tree->SetBranchAddress("pfrawpt", pfrawpt);
  tree->SetBranchAddress("pfeta", pfeta);
  tree->SetBranchAddress("pfphi", pfphi);
  tree->SetBranchAddress("pfpu", pfpu);
  tree->SetBranchAddress("trMax", trMax);
  tree->SetBranchAddress("chMax", chMax);
  tree->SetBranchAddress("chSum", chSum);
  tree->SetBranchAddress("phMax", phMax);
  tree->SetBranchAddress("phSum", phSum);
  tree->SetBranchAddress("neMax", neMax);
  tree->SetBranchAddress("neSum", neSum);
  tree->SetBranchAddress("muMax", muMax);
  tree->SetBranchAddress("muSum", muSum);
  tree->SetBranchAddress("eMax", eMax);
  tree->SetBranchAddress("eSum", eSum);
  tree->SetBranchAddress("hcalSum", hcalSum);
  tree->SetBranchAddress("ecalSum", ecalSum);

  tree->SetBranchAddress("ncalo", &ncalo);
  tree->SetBranchAddress("isPFMatch", isPFMatch);
  tree->SetBranchAddress("pfidx", pfidx);
  tree->SetBranchAddress("calorecpt", calorecpt);
  tree->SetBranchAddress("calorawpt", calorawpt);
  tree->SetBranchAddress("caloeta", caloeta);
  tree->SetBranchAddress("calophi", calophi);
  tree->SetBranchAddress("calopu", calopu);
  tree->SetBranchAddress("calohcalSum", calohcalSum);
  tree->SetBranchAddress("caloecalSum", caloecalSum);

  //! If you are not using calojets info just do not read and load them
  tree->SetBranchStatus("ncalo", 0,0);
  tree->SetBranchStatus("isPFMatch",0,0);
  tree->SetBranchStatus("pfidx",0,0);
  tree->SetBranchStatus("calorecpt",0,0);
  tree->SetBranchStatus("calorawpt",0,0);
  tree->SetBranchStatus("caloeta",0,0);
  tree->SetBranchStatus("calophi",0,0);
  tree->SetBranchStatus("calopu",0,0);
  tree->SetBranchStatus("calohcalSum",0,0);
  tree->SetBranchStatus("caloecalSum",0,0);


  if( kDataset == "MC" ){
    tree->SetBranchAddress("pthat", &pthat);
    tree->SetBranchAddress("weight", &weight);
    tree->SetBranchAddress("pfrefidx", pfrefidx); //! PF   -> REF match
    tree->SetBranchAddress("clrefidx", clrefidx); //! Calo -> REF match
    tree->SetBranchAddress("nref", &nref);
    tree->SetBranchAddress("refpfid", refpfid);  //! REF -> PF match
    tree->SetBranchAddress("refclid", refclid);  //! REF -> CALO match
    tree->SetBranchAddress("subid", subid);
    tree->SetBranchAddress("refpt", refpt);
    tree->SetBranchAddress("refeta", refeta);
    tree->SetBranchAddress("refphi", refphi);
    tree->SetBranchAddress("refdrjt", refdrjt);
  }

  //! Histogram
  TFile *fout = new TFile(Form("OutputHist_%s_%s_%s.root",kSpecies.c_str(),kDataset.c_str(),(kAlgName+kRadii+kAlgo).c_str()),"RECREATE");

  TH1D *hgen_f[2][ncen], *hgen_rej_f[ncen];
  TH1D *hrec_f[2][ncen], *hrec_rej_f[ncen];
  TH2D *hmat_f[2][ncen], *hmat_rej_f[ncen];

  //! Train
  TH1D *hgen_f_t[2][ncen], *hgen_rej_f_t[ncen];
  TH1D *hrec_f_t[2][ncen], *hrec_rej_f_t[ncen];
  TH2D *hmat_f_t[2][ncen], *hmat_rej_f_t[ncen];

  //! Check
  TH1D *hgen_f_c[2][ncen], *hgen_rej_f_c[ncen];
  TH1D *hrec_f_c[2][ncen], *hrec_rej_f_c[ncen];
  TH2D *hmat_f_c[2][ncen], *hmat_rej_f_c[ncen];

  //! Avearge UE background 0 : Data  and 1 MC
  TH1F *havbkgpt[2][ncen][nbins], *havbkgpt_eta[2][ncen][nbins][neta];

  //! JEC          
  TH1F *hrescrpt[2][ncen][nbins], *hresrrpt[2][ncen][nbins];
  TH1F *hrescrpt_eta[2][ncen][nbins][neta_ref], *hresrrpt_eta[2][ncen][nbins][neta_ref];

  TH2D *hRefPt_PtHat;
  TH2D *hPFPt_PtHat;
  TH2D *hRefPt_PFPt;

  hRefPt_PtHat = new TH2D(Form("hRefPt_PtHat_%s_%s",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str()),
			  Form("hRefPt_PtHat_%s_%s",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str()),600,0.,600., 200,15.,415.);
  hPFPt_PtHat  = new TH2D(Form("hPFPt_PtHat_%s_%s",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str()),
			  Form("hPFPt_PtHat_%s_%s",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str()),600,0.,600., 200,15.,415.);
  hRefPt_PFPt  = new TH2D(Form("hRefPt_PFPt_%s_%s",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str()),
			  Form("hRefPt_PFPt_%s_%s",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str()),600,0.,600.,600,0.,600.);
  
  // i is the with or without jetID loop, NOT the nj loop! 0 == no JetID, 1== JetID
  for(int i=0; i<2; i++){
    for(int ic=0; ic<ncen; ic++){
      hgen_f[i][ic]    = new TH1D(Form("hgen_f_%s_%s_%d_%d",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),i,ic),
				  Form("hgen_fine_%s_%s_%d_%s",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),i,ccent[ic]), 600,0.,600.);

      hrec_f[i][ic]    = new TH1D(Form("hrec_f_%s_%s_%d_%d",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),i,ic),
				  Form("hrec_fine_%s_%s_%d_%s",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),i,ccent[ic]), 600,0.,600.);

      hmat_f[i][ic] = new TH2D(Form("hmat_f_%s_%s_%d_%d",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),i,ic),
			       Form("hmat_fine_%s_%s_%d_%s",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),i,ccent[ic]), 600,0,600., 600,0.,600.);

      //! Train
      hgen_f_t[i][ic]    = new TH1D(Form("hgen_f_t_%s_%s_%d_%d",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),i,ic),
				    Form("hgen_fine_train_%s_%s_%d_%s",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),i,ccent[ic]), 600,0.,600.);

      hrec_f_t[i][ic]    = new TH1D(Form("hrec_f_t_%s_%s_%d_%d",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),i,ic),
				    Form("hrec_fine_train_%s_%s_%d_%s",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),i,ccent[ic]), 600,0.,600.);

      hmat_f_t[i][ic] = new TH2D(Form("hmat_f_t_%s_%s_%d_%d",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),i,ic),
				 Form("hmat_fine_train_%s_%s_%d_%s",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),i,ccent[ic]), 600,0,600., 600,0.,600.);

      //! Check
      hgen_f_c[i][ic]    = new TH1D(Form("hgen_f_c_%s_%s_%d_%d",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),i,ic),
				    Form("hgen_fine_check_%s_%s_%d_%s",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),i,ccent[ic]), 600,0.,600.);
      
      hrec_f_c[i][ic]    = new TH1D(Form("hrec_f_c_%s_%s_%d_%d",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),i,ic),
				    Form("hrec_fine_check_%s_%s_%d_%s",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),i,ccent[ic]), 600,0.,600.);

      hmat_f_c[i][ic] = new TH2D(Form("hmat_f_c_%s_%s_%d_%d",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),i,ic),
				 Form("hmat_fine_check_%s_%s_%d_%s",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),i,ccent[ic]), 600,0,600., 600,0.,600.);


      //! Average background
      for(int ip=0; ip<nbins; ip++){
	havbkgpt[i][ic][ip]= new TH1F(Form("havbkgpt_%s_%d_%d_%d",(kAlgName+kRadii+kAlgo).c_str(),i,ic,ip),
				      Form("(<bkg>) jet p_{T} %s %s %0.0f < p_{T} < %0.0f",(kAlgName+kRadii+kAlgo).c_str(),ccent[ic],ptbins[ip],ptbins[ip+1]),100,0.,200.);
	hrescrpt[i][ic][ip]= new TH1F(Form("hrescrpt_%s_%d_%d_%d",(kAlgName+kRadii+kAlgo).c_str(),i,ic,ip),
				      Form("(Reco/Gen) jet p_{T} %s %s %0.0f < p_{T}^{REF} < %0.0f",(kAlgName+kRadii+kAlgo).c_str(),ccent[ic],ptbins[ip],ptbins[ip+1]),rbins,rbinl,rbinh);
	hresrrpt[i][ic][ip]= new TH1F(Form("hresrrpt_%s_%d_%d_%d",(kAlgName+kRadii+kAlgo).c_str(),i,ic,ip),
				      Form("(Raw/Gen) jet p_{T} %s %s %0.0f < p_{T}^{REF} < %0.0f",(kAlgName+kRadii+kAlgo).c_str(),ccent[ic],ptbins[ip],ptbins[ip+1]),rbins,rbinl,rbinh);

	for(int ie=0; ie<neta; ie++){
	  havbkgpt_eta[i][ic][ip][ie]= new TH1F(Form("havbkgpt_eta_%s_%d_%d_%d_%d",(kAlgName+kRadii+kAlgo).c_str(),i,ic,ip,ie),
						Form("(<bkg>) jet p_{T} %s %s %0.0f < p_{T} < %0.0f",(kAlgName+kRadii+kAlgo).c_str(),ccent[ic],ptbins[ip],ptbins[ip+1]),100,0.,200.);
	}

	for(int ie=0; ie<neta_ref; ie++){	
	  hrescrpt_eta[i][ic][ip][ie]= new TH1F(Form("hrescrpt_eta_%s_%d_%d_%d_%d",(kAlgName+kRadii+kAlgo).c_str(),i,ic,ip,ie),
						Form("(Reco/Gen) jet p_{T} %s %s %0.0f < p_{T}^{REF} < %0.0f, %0.1f < #eta < %0.1f",(kAlgName+kRadii+kAlgo).c_str(),ccent[ic],ptbins[ip],ptbins[ip+1],etabins_ref[ie],etabins_ref[ie+1]),rbins,rbinl,rbinh);
	  hresrrpt_eta[i][ic][ip][ie]= new TH1F(Form("hresrrpt_eta_%s_%d_%d_%d_%d",(kAlgName+kRadii+kAlgo).c_str(),i,ic,ip,ie),
						Form("(Raw/Gen) jet p_{T} %s %s %0.0f < p_{T}^{REF} < %0.0f, %0.1f < #eta < %0.1f",(kAlgName+kRadii+kAlgo).c_str(),ccent[ic],ptbins[ip],ptbins[ip+1],etabins_ref[ie],etabins_ref[ie+1]),rbins,rbinl,rbinh);
	}
      }

      if(i==0){
	hgen_rej_f[ic]   = new TH1D(Form("hgen_rej_f_%s_%s_%d",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),ic),
				    Form("hgen_rej_fine_%s_%s_%d_%s",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),i,ccent[ic]), 600,0.,600.);
	hrec_rej_f[ic]   = new TH1D(Form("hrec_rej_f_%s_%s_%d",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),ic),
				    Form("hrec_rej_fine_%s_%s_%d_%s",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),i,ccent[ic]), 600,0.,600.);
	hmat_rej_f[ic]   = new TH2D(Form("hmat_rej_f_%s_%s_%d",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),ic),
				    Form("hmat_rej_fine_%s_%s_%s",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),ccent[ic]), 600,0,600., 600,0.,600.);

	//! Train
	hgen_rej_f_t[ic]     = new TH1D(Form("hgen_rej_f_t_%s_%s_%d",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),ic),
					Form("hgen_rej_fine_train_%s_%s_%d_%s",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),i,ccent[ic]), 600,0.,600.);
	hrec_rej_f_t[ic]     = new TH1D(Form("hrec_rej_f_t_%s_%s_%d",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),ic),
					Form("hrec_rej_fine_train_%s_%s_%d_%s",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),i,ccent[ic]), 600,0.,600.);
	hmat_rej_f_t[ic]     = new TH2D(Form("hmat_rej_f_t_%s_%s_%d",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),ic),
					Form("hmat_rej_fine_train_%s_%s_%s",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),ccent[ic]), 600,0,600., 600,0.,600.);
	//! Check
	hgen_rej_f_c[ic]     = new TH1D(Form("hgen_rej_f_c_%s_%s_%d",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),ic),
					Form("hgen_rej_fine_check_%s_%s_%d_%s",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),i,ccent[ic]), 600,0.,600.);
	hrec_rej_f_c[ic]     = new TH1D(Form("hrec_rej_f_c_%s_%s_%d",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),ic),
					Form("hrec_rej_fine_check_%s_%s_%d_%s",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),i,ccent[ic]), 600,0.,600.);
	hmat_rej_f_c[ic]     = new TH2D(Form("hmat_rej_f_c_%s_%s_%d",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),ic),
					Form("hmat_rej_fine_check_%s_%s_%s",kSpecies.c_str(),(kAlgName+kRadii+kAlgo).c_str(),ccent[ic]), 600,0,600., 600,0.,600.);
      }
    }
  }
  
  
  //! CutA
  //! matched   : calopt_1/pfpt_1 > 0.5 && calopt_1/pfpt_1 <= 0.85 && eMax_1/Sumcand < ((Float_t)18./7. *(Float_t)calopt_1/pfpt_1 - (Float_t)9./7.)
  //! unmatched : eMax_1/Sumcand < 0.05

  long nb=0;
  long entries = tree->GetEntries();
  std::cout << kDataset.c_str() << "\t" << kSpecies.c_str()<< "\t" << (kAlgName+kRadii+kAlgo).c_str() << "\t" << tree->GetName() << "\t" << entries << std::endl;

  for(long nentry = 0; nentry < entries; nentry++){
    nb += tree->GetEntry(nentry);
    
    if( printDebug && nentry==1000 )break;
    if( nentry%100000 == 0)std::cout << Form(" Processing %s %s event : ", kDataset.c_str(), kSpecies.c_str())  << nentry << std::endl;
    
    bool iFill = (nentry%2);

    int iCent = -1;
    if( kSpecies == "pp" )iCent = ncen-1;
    else iCent = GetCentBin(hiBin);
    if(iCent<0 || iCent>=ncen)continue;
    if( printDebug )std::cout << " Passsed cent  "  << iCent << " " << hiBin << std::endl;

    int iTrig=0;
    double prescl_fac=1.0;
    if( kSpecies == "pp" ){
      if( jet40 ==1 && jet60 ==0 && jet80 ==0 ){iTrig=1; prescl_fac=Jet40_prescl;}
      if( jet60 ==1 && jet80==0 )iTrig=1;
      if( jet80 ==1 )iTrig=1;
    }else if( kSpecies == "PbPb" ){
      if( jet55 ==1 && jet65 ==0 && jet80 ==0 ){iTrig=1, prescl_fac=Jet55_prescl;}
      if( jet65 ==1 && jet80 ==0 )iTrig=1;      
      if( jet80 ==1 )iTrig=1;
    }else if( kSpecies == "PbPb_MinBias" ){ 
      if( jetMB ==1 )iTrig=1;
    }
    if ( !iTrig ) continue;

    if( printDebug )std::cout << " # of PF jets  "  << npf << std::endl;
    for ( int ipf=0; ipf<npf; ipf++){
      
      if( pfpt[ipf] < kptrecocut || pfrawpt[ipf] < kptrawcut || fabs(pfeta[ipf]) > ketacut )continue;    

      //! MC events
      int refid=-1;
      if ( kDataset == "MC" ){
	if( pfrefidx[ipf] >=0 ){//! Matched PF to REF jets 
	  refid=pfrefidx[ipf];
	  if( pfpt[ipf] > 2.*pthat )continue;
	  if( subid[refid] != 0 || fabs(refdrjt[refid]) > kdelrcut )continue;
	}else{
	  //! Can do fake calculations here
	  //! for unfolding check you can fill the reco pt here 
	  //! for fake subtraction from minbias
	  continue;
	}
	if( refid < 0 ) continue;
      }

      if( printDebug )std::cout << " Passed MC cuts "  <<  refid << std::endl;

      //! Jet ID
      bool wJetId=false;
      Float_t Sumcand = chSum[ipf] + phSum[ipf] + neSum[ipf] + muSum[ipf];
      if( kSpecies == "pp" ) wJetId=true;    
      else{
	if( isCaloMatch[ipf] ){ //! matched  jet ID
	  Float_t ePFSel  = (18./7.*calopt[ipf]/pfpt[ipf]) - 9./7.;
	  if((calopt[ipf]/pfpt[ipf]  > 0.50) 
	     && (calopt[ipf]/pfpt[ipf] <= 0.85)
	     && (eMax[ipf]/Sumcand < ePFSel)
	     )wJetId=true;
	}else if( (eMax[ipf]/Sumcand < 0.05) )wJetId=true; //! unmatched jet id
      }
      if( printDebug )std::cout << " Passed JetID cuts "  <<  wJetId << " pfpt " << pfpt[ipf] << " isMatch : " << isCaloMatch[ipf] << std::endl;


      int ipt = GetPtBin(pfpt[ipf]);
      //if(ipt < 0 || ipt >= nbins)continue;

      int ieta = GetEtaBin(fabs(pfeta[ipf]));
      //if(ieta < 0 || ieta >= neta)continue;


      float sumPF = (chSum[ipf] + neSum[ipf] + phSum[ipf] + eSum[ipf] + muSum[ipf]);
      float bkgd  = sumPF - pfrawpt[ipf];

      if( kDataset == "DATA" ){
	hrec_f  [0][iCent]->Fill(pfpt[ipf], prescl_fac*weight);
	hmat_f  [0][iCent]->Fill(pfrawpt[ipf], pfpt[ipf], prescl_fac*weight);
	
	//! For matched and unmatched PF jets with  CALO jets
	// if( isCaloMatch[ipf] ){
	// }else{
	// }
	if( (ipt >=0 && ipt<nbins) && (ieta>=0 && ieta<neta) ){
	  havbkgpt[0][iCent][ipt]->Fill(bkgd, prescl_fac*weight);
	  havbkgpt_eta[0][iCent][ipt][ieta]->Fill(bkgd, prescl_fac*weight);
	}
	
	if( wJetId ){
	  hrec_f  [1][iCent]->Fill(pfpt[ipf], prescl_fac*weight);
	  hmat_f  [1][iCent]->Fill(pfpt[ipf], pfrawpt[ipf], prescl_fac*weight);
	  if( (ipt >=0 && ipt<nbins) && (ieta>=0 && ieta<neta) ){	  
	    havbkgpt[1][iCent][ipt]->Fill(bkgd, prescl_fac*weight);
	    havbkgpt_eta[1][iCent][ipt][ieta]->Fill(bkgd, prescl_fac*weight);
	  }
	}else{
	  hrec_rej_f  [iCent]->Fill(pfpt[ipf], prescl_fac*weight);
	  hmat_rej_f  [iCent]->Fill(pfpt[ipf], pfrawpt[ipf], prescl_fac*weight);
	}
      }else{ //! MC
	
	//! For matched and unmatched PF jets with  CALO jets
	// if( isCaloMatch[ipf] ){
	// }else{
	// }


	int ipt_ref = GetPtBin(refpt[refid]);
	//if(ipt_ref < 0 || ipt_ref >= nbins)continue;
	
	int ieta_ref = GetEtaJECBin(refeta[refid]);
	//if(ieta_ref < 0 || ieta_ref >= neta)continue;
	
	if( iCent == 0 ){
	  hRefPt_PtHat->Fill(refpt[refid], pthat, prescl_fac*weight);
	  hPFPt_PtHat->Fill(pfpt[ipf], pthat, prescl_fac*weight);
	  hRefPt_PFPt->Fill(refpt[refid], pfpt[ipf], prescl_fac*weight);
	}

	hgen_f  [0][iCent]->Fill(refpt[refid], prescl_fac*weight);
	hmat_f  [0][iCent]->Fill(pfpt[ipf], refpt[refid], prescl_fac*weight);
	hrec_f  [0][iCent]->Fill(pfpt[ipf], prescl_fac*weight);

	if( (ipt >=0 && ipt<nbins) && (ieta>=0 && ieta<neta) ){
	  havbkgpt[0][iCent][ipt]->Fill(bkgd, prescl_fac*weight);
	  havbkgpt_eta[0][iCent][ipt][ieta]->Fill(bkgd, prescl_fac*weight);
	}

	if( (ipt_ref >=0 && ipt_ref<nbins) && (ieta_ref>=0 && ieta_ref<neta_ref) ){
	  hrescrpt[0][iCent][ipt_ref]->Fill(pfpt[ipf]/refpt[refid], prescl_fac*weight);
	  hresrrpt[0][iCent][ipt_ref]->Fill(pfrawpt[ipf]/refpt[refid], prescl_fac*weight);
	  hrescrpt_eta[0][iCent][ipt_ref][ieta_ref]->Fill(pfpt[ipf]/refpt[refid], prescl_fac*weight);
	  hresrrpt_eta[0][iCent][ipt_ref][ieta_ref]->Fill(pfrawpt[ipf]/refpt[refid], prescl_fac*weight);
	}	
	if( iFill ){
	  hgen_f_t  [0][iCent]->Fill(refpt[refid], prescl_fac*weight);
	  hrec_f_t  [0][iCent]->Fill(pfpt[ipf], prescl_fac*weight);
	  hmat_f_t  [0][iCent]->Fill(pfpt[ipf], refpt[refid], prescl_fac*weight);
	}else{
	  hgen_f_c  [0][iCent]->Fill(refpt[refid], prescl_fac*weight);
	  hrec_f_c  [0][iCent]->Fill(pfpt[ipf], prescl_fac*weight);
	  hmat_f_c  [0][iCent]->Fill(pfpt[ipf], refpt[refid], prescl_fac*weight);
	}
      
	if( wJetId ){
	  hgen_f  [1][iCent]->Fill(refpt[refid], prescl_fac*weight);
	  hrec_f  [1][iCent]->Fill(pfpt[ipf], prescl_fac*weight);
	  hmat_f  [1][iCent]->Fill(pfpt[ipf], refpt[refid], prescl_fac*weight);
	
	  if( (ipt >=0 && ipt<nbins) && (ieta>=0 && ieta<neta) ){
	    havbkgpt[1][iCent][ipt]->Fill(bkgd, prescl_fac*weight);
	    havbkgpt_eta[1][iCent][ipt][ieta]->Fill(bkgd, prescl_fac*weight);
	  }
	  if( (ipt_ref >=0 && ipt_ref < nbins) && (ieta_ref >= 0 && ieta_ref < neta_ref) ){
	    hrescrpt[1][iCent][ipt_ref]->Fill(pfpt[ipf]/refpt[refid], prescl_fac*weight);
	    hresrrpt[1][iCent][ipt_ref]->Fill(pfrawpt[ipf]/refpt[refid], prescl_fac*weight);
	    hrescrpt_eta[1][iCent][ipt_ref][ieta_ref]->Fill(pfpt[ipf]/refpt[refid], prescl_fac*weight);
	    hresrrpt_eta[1][iCent][ipt_ref][ieta_ref]->Fill(pfrawpt[ipf]/refpt[refid], prescl_fac*weight);
	  }

	  if( iFill ){ //! train
	    hgen_f_t  [1][iCent]->Fill(refpt[refid], prescl_fac*weight);
	    hrec_f_t  [1][iCent]->Fill(pfpt[ipf], prescl_fac*weight);
	    hmat_f_t  [1][iCent]->Fill(pfpt[ipf], refpt[refid], prescl_fac*weight);
	  
	  }else{//! check
	    hgen_f_c  [1][iCent]->Fill(refpt[refid], prescl_fac*weight);
	    hrec_f_c  [1][iCent]->Fill(pfpt[ipf], prescl_fac*weight);
	    hmat_f_c  [1][iCent]->Fill(pfpt[ipf], refpt[refid], prescl_fac*weight);
	  }
	}else{ //! rej Jetid
	  hgen_rej_f  [iCent]->Fill(refpt[refid], prescl_fac*weight);
	  hrec_rej_f  [iCent]->Fill(pfpt[ipf], prescl_fac*weight);
	  hmat_rej_f  [iCent]->Fill(pfpt[ipf], refpt[refid], prescl_fac*weight);
	
	  if( iFill ){
	    hgen_rej_f_t  [iCent]->Fill(refpt[refid], prescl_fac*weight);
	    hrec_rej_f_t  [iCent]->Fill(pfpt[ipf], prescl_fac*weight);
	    hmat_rej_f_t  [iCent]->Fill(pfpt[ipf], refpt[refid], prescl_fac*weight);
	  }else{
	    hgen_rej_f_c  [iCent]->Fill(refpt[refid], prescl_fac*weight);
	    hrec_rej_f_c  [iCent]->Fill(pfpt[ipf], prescl_fac*weight);
	    hmat_rej_f_c  [iCent]->Fill(pfpt[ipf], refpt[refid], prescl_fac*weight);
	  }
	}
      }
    }
  }


  fout->cd();
  if( kDataset == "DATA" ){
    for(int i=0; i<2; i++){
      for(int ic=mincen; ic<maxcen; ic++){
	hmat_f[i][ic]->Write();
	hrec_f[i][ic]->Write();

	for(int ip=0; ip<nbins; ip++){
	  havbkgpt[i][ic][ip]->Write();
	  for(int ie=0; ie<neta; ie++){
	    havbkgpt_eta[i][ic][ip][ie]->Write();
	  }
	}
	if(i==0){
	  hrec_rej_f[ic]->Write();
	  hmat_rej_f[ic]->Write();
	}
      }
    }
  }else{
    hRefPt_PtHat->Write();
    hPFPt_PtHat->Write();
    hRefPt_PFPt->Write();
    for(int i=0; i<2; i++){
      for(int ic=mincen; ic<maxcen; ic++){
	hgen_f[i][ic]->Write();
	hrec_f[i][ic]->Write();
	hmat_f[i][ic]->Write();
	for(int ip=0; ip<nbins; ip++){
	  havbkgpt[i][ic][ip]->Write();
	  hrescrpt[i][ic][ip]->Write();
	  hresrrpt[i][ic][ip]->Write();
	  for(int ie=0; ie<neta; ie++){
	    havbkgpt_eta[i][ic][ip][ie]->Write();
	  }
	  for(int ie=0; ie<neta_ref; ie++){
	    hrescrpt_eta[i][ic][ip][ie]->Write();
	    hresrrpt_eta[i][ic][ip][ie]->Write();
	  }
	}
	if(i==0){
	  hgen_rej_f[ic]->Write();
	  hrec_rej_f[ic]->Write();
	  hmat_rej_f[ic]->Write();
	}
      }
    }
  }
  fout->Close();

  timer.Stop();
  double mbytes = 0.000001*nb;
  double rtime  = timer.RealTime();
  double ctime  = timer.CpuTime();

  std::cout<<std::endl;
  std::cout<<Form("RealTime=%f seconds, CpuTime=%f seconds\n",rtime,ctime)<<std::endl;
  std::cout<<Form("You read %f Mbytes/RealTime seconds\n",mbytes/rtime)<<std::endl;
  std::cout<<Form("You read %f Mbytes/CpuTime  seconds\n",mbytes/ctime)<<std::endl;

  return 0;
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
int GetEtaJECBin(float eta)
{
  for(int ix=0;ix<neta_ref;ix++){
    if(eta>=etabins_ref[ix] && eta<etabins_ref[ix+1]){
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
void MakeIndHist(TH1D *&hist)
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
