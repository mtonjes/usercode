// -*- C++ -*-
//
// Package:    ZSP_Pu_JPTAnalyzer
// Class:      ZSP_Pu_JPTAnalyzer
// 
/**\class ZSP_Pu_JPTAnalyzer ZSP_Pu_JPTAnalyzer.cc MTonjes/JetMatchAna/src/ZSP_Pu_JPTAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     calculates histograms mainly based on ET
*/
//
// Original Author:  "Marguerite Tonjes"
//         Created:  Wed May 21 16:11:40 CDT 2008
// $Id$
//
//


// system include files
#include <memory>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/JetReco/interface/Jet.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleCandidate.h"

#include "DataFormats/Candidate/interface/CandMatchMap.h"
#include "PhysicsTools/Utilities/interface/deltaPhi.h"

#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TCanvas.h"
#include <cmath>

#include <Math/VectorUtil.h>

using namespace std;
using namespace reco;
using namespace edm;
using namespace ROOT::Math::VectorUtil;

typedef GenJetCollection::const_iterator GenJetIter;
//
// class decleration
//

class ZSP_Pu_JPTAnalyzer : public edm::EDAnalyzer {
   public:
      explicit ZSP_Pu_JPTAnalyzer(const edm::ParameterSet&);
      ~ZSP_Pu_JPTAnalyzer();
      virtual int determineIndex(Double_t* limBins, Double_t data, unsigned int nbreBins);  

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

    InputTag source_;
    InputTag matched_;
    InputTag matchedjetsOne_;   
    string   fOutputFileName_;            

    Handle<CandidateCollection> source;
    Handle<CandidateCollection> matched;
    Handle<CandMatchMap>        matchedjetsOne;
    
    Bool_t HaveMatchMap;

// histograms are for the barrel abs(eta Jet MC) <= 1.3
// unless they have _etacut1 in them, in which case they are for the 
//   endcap (1.3 < eta jet MC < 3
    TFile*      hOutputFile ;
    TH1D*       hTotalLenght;
    TH1F*       hdeltaR;
    TH1F*       hdeltaR_etacut0;
    TH1F*       hdeltaR_etacut1;
    TH1F* 	    ratioE;
    TH1F*       sigmaErEm;
    TH1F*		ETresolution;
    TH1F* 		EThist [6];
 
     TH1F* 	    ratioEOld;
    TH1F*       sigmaErEmOld;
    TH1F*		ETresolutionOld;
    TH1F* 		EThistOld [13];

    TH1F* 	    ratioE_dRltpt1;
    TH1F*       sigmaErEm_dRltpt1;
    TH1F*		ETresolution_dRltpt1;
    TH1F* 		EThist_dRltpt1 [6];
    TH1F* 	    ratioE_dRltpt1Old;
    TH1F*       sigmaErEm_dRltpt1Old;
    TH1F*		ETresolution_dRltpt1Old;
    TH1F* 		EThist_dRltpt1Old [13];

 // barrel specific
     TH1F* 	    ratioE_etacut0;
    TH1F*       sigmaErEm_etacut0;
    TH1F*		ETresolution_etacut0;
    TH1F* 		EThist_etacut0 [6];
 
     TH1F* 	    ratioE_etacut0Old;
    TH1F*       sigmaErEm_etacut0Old;
    TH1F*		ETresolution_etacut0Old;
    TH1F* 		EThist_etacut0Old [13];
//    
     TH1F* 	    ratioE_etacut1;
    TH1F*       sigmaErEm_etacut1;
    TH1F*		ETresolution_etacut1;
    TH1F* 		EThist_etacut1 [6];
 
     TH1F* 	    ratioE_etacut1Old;
    TH1F*       sigmaErEm_etacut1Old;
    TH1F*		ETresolution_etacut1Old;
    TH1F* 		EThist_etacut1Old [13];
//

// position resolution:
    TH1F*       ratioEta;
    TH1F*       sigmaeta;
    TH1F*		etaResolution;
    TH1F* 		etahist [6];
    TH1F*       ratioPhi;
    TH1F*       sigmaphi;
    TH1F*		phiResolution;
    TH1F* 		phihist [6];
    TH1F*       ratioEta_etacut0;
    TH1F*       sigmaeta_etacut0;
    TH1F*		etaResolution_etacut0;
    TH1F* 		etahist_etacut0 [6];    
    TH1F*       ratioPhi_etacut0;
    TH1F*       sigmaphi_etacut0;
    TH1F*		phiResolution_etacut0;
    TH1F* 		phihist_etacut0[6];
    TH1F*       ratioEta_etacut1;
    TH1F*       sigmaeta_etacut1;
    TH1F*		etaResolution_etacut1;
    TH1F* 		etahist_etacut1 [6];      
    TH1F*       ratioPhi_etacut1;
    TH1F*       sigmaphi_etacut1;
    TH1F*		phiResolution_etacut1;
    TH1F* 		phihist_etacut1[6];   
//      TH1F* 	    ratiopt;
//     TH1F*       sigmaErEm_pt;
//     TH1F*		pTresolution;
//     TH1F* 		pThist [6];   
//  
//      TH1F* 	    ratiopt_etacut1;
//     TH1F*       sigmaErEm_pt_etacut1;
//     TH1F*		pTresolution_etacut1;
//     TH1F* 		pThist_etacut1 [6];   
//     
//      TH1F* 	    ratioptOld;
//     TH1F*       sigmaErEm_ptOld;
//     TH1F*		pTresolutionOld;
//    TH1F* 		pThistOld[6];     
    char nameHist [50];
    char label [500];  
   Double_t limBins[6];
   //= {10,20,30,40,50,60,70,80,100.0,120.,150.,200};   
   Double_t limBinsOld[13];
   // = {20,30,40,50,60,70,80,100,120,150,200,250,300,350};
   
    TH2F*		hSimpleResolution_Energy; // (E_{T} Reco)/(E_{T} Gen) vs. E_{T} Gen  (what Korea group did) 
//    TH2F* 		hSimpleEfficiency_Energy; // (#matched jets)/(# reco jets) vs. E_{T} Gen  (what Korea group did)
    TH1F*       hAllGenJets_et;
//    TH1F*       hAllGenJets_pt_etacut0;
    TH1F*       hAllGenJets_et_etacut0;

    TH1F*		hAllZSPJPTiC5Jets_et;
    TH1F*		hMatchGenJets_dRltpt2_et;
     TH1F*		hMatchGenJets_dRltpt1_et;   
    TH1F*		hMatchGenJets_et;
    TH1F*		hMatchZSPJPTiC5Jets_dRltpt2_et;
    TH1F*		hMatchZSPJPTiC5Jets_dRltpt1_et;
    TH1F*		hMatchZSPJPTiC5Jets_et;  
 
    TH1F*		hAllZSPJPTiC5Jets_et_etacut0;
    TH1F*		hMatchGenJets_dRltpt2_et_etacut0;
    TH1F*		hMatchGenJets_dRltpt1_et_etacut0;    
    TH1F*		hMatchGenJets_et_etacut0;
    TH1F*		hMatchZSPJPTiC5Jets_dRltpt2_et_etacut0;
    TH1F*		hMatchZSPJPTiC5Jets_dRltpt1_et_etacut0;    
    TH1F*		hMatchZSPJPTiC5Jets_et_etacut0;  
  
    TH1F*       hAllGenJets_pt;
    TH1F*		hAllZSPJPTiC5Jets_pt;
    TH1F*		hMatchGenJets_dRltpt2_pt;
    TH1F*		hMatchGenJets_dRltpt1_pt;    
    TH1F*		hMatchGenJets_pt;
    TH1F*		hMatchZSPJPTiC5Jets_dRltpt2_pt;
    TH1F*		hMatchZSPJPTiC5Jets_dRltpt1_pt;
    TH1F*		hMatchZSPJPTiC5Jets_pt;  
    TH1F*       hUnMatchedZSPJPTiC5Jets_et;
    TH1F*       hUnMatchedZSPJPTiC5Jets_et_etacut0;
    TH1F*       hUnMatchedZSPJPTiC5Jets_et_etacut1;
    
    Int_t    ZSPJPTiC5Jets_unmatchstat[100];
    Double_t    ZSPJPTiC5Jets_eta_unmatch[100];
    Double_t    ZSPJPTiC5Jets_et_unmatch[100];
    
    TH1F*       hUnMatchedZSPJPTiC5Jets_eta;
    TH1F*       hUnMatchedZSPJPTiC5Jets_eta_etacut0;
    TH1F*       hUnMatchedZSPJPTiC5Jets_eta_etacut1;
//    TH1F*       hUnMatchedZSPJPTiC5Jets_dRltpt2_et;
//    TH1F*       hUnMatchedZSPJPTiC5Jets_dRltpt2_et_etacut0;
//    TH1F*       hUnMatchedZSPJPTiC5Jets_dRltpt2_et_etacut1;
//    TH1F* 		hMatchedGenGNumEv_pt_Ratio;

    TH1F*		hMatchGenJets_pt_etacut0;
    TH1F*		hAllZSPJPTiC5Jets_pt_etacut0;
    TH1F*       hAllGenJets_pt_etacut0;
    TH1F*		hMatchGenJets_dRltpt2_pt_etacut0;
    TH1F*		hMatchZSPJPTiC5Jets_dRltpt2_pt_etacut0;
    TH1F*		hMatchGenJets_dRltpt1_pt_etacut0;
    TH1F*		hMatchZSPJPTiC5Jets_dRltpt1_pt_etacut0;
    TH1F*		hMatchZSPJPTiC5Jets_pt_etacut0;     
//    TH1F* 		hMatchedGenGNumEv_pt_Ratio_etacut0;

 // endcap plots
    TH1F*       hAllGenJets_et_etacut1;
    TH1F*		hAllZSPJPTiC5Jets_et_etacut1;
    TH1F*		hMatchGenJets_dRltpt2_et_etacut1;
    TH1F*		hMatchGenJets_dRltpt1_et_etacut1;
    TH1F*		hMatchGenJets_et_etacut1;
    TH1F*		hMatchZSPJPTiC5Jets_dRltpt2_et_etacut1;
    TH1F*		hMatchZSPJPTiC5Jets_dRltpt1_et_etacut1;
    TH1F*		hMatchZSPJPTiC5Jets_et_etacut1;     
//    TH1F* 		hMatchedGenGNumEv_et_Ratio_etacut1;  
    
//     TH1F*       hAllGenJets_pt_etacut1;
//     TH1F*		hAllZSPJPTiC5Jets_pt_etacut1;
//     TH1F*		hMatchGenJets_dRltpt2_pt_etacut1;
//     TH1F*		hMatchGenJets_pt_etacut1;
//     TH1F*		hMatchZSPJPTiC5Jets_dRltpt2_pt_etacut1;
//     TH1F*		hMatchZSPJPTiC5Jets_pt_etacut1;     
//     TH1F* 		hMatchedGenGNumEv_pt_Ratio_etacut1;   
    
    TH2F*		hRecoVsGen_pt_etacut1;
    TH2F*		hRecoVsGen_et_etacut1;
    TH2F*		hRecoVsGen_eta_etacut1;
    TH2F*		hRecoVsGen_phi_etacut1;
    TH2F*		hRecoVsGen_dRltpt2_pt_etacut1;
    TH2F*		hRecoVsGen_dRltpt2_et_etacut1;
    TH2F*		hRecoVsGen_dRltpt2_eta_etacut1;
    TH2F*		hRecoVsGen_dRltpt2_phi_etacut1;    
    TH2F*		hRecoVsGen_dRltpt1_pt_etacut1;
    TH2F*		hRecoVsGen_dRltpt1_et_etacut1;
    TH2F*		hRecoVsGen_dRltpt1_eta_etacut1;
    TH2F*		hRecoVsGen_dRltpt1_phi_etacut1;  
    TH1F* 		hMatchedGenGNumEv_Ratio_etacut1; // (# matched GenJets)/(# All GenJets) --> this is the one
    
// end endcap plots

    TH2F*		hRecoVsGen_pt_etacut0;
    TH2F*		hRecoVsGen_et_etacut0;
    TH2F*		hRecoVsGen_eta_etacut0;
    TH2F*		hRecoVsGen_phi_etacut0;
    TH2F*		hRecoVsGen_dRltpt2_pt_etacut0;
    TH2F*		hRecoVsGen_dRltpt2_et_etacut0;
    TH2F*		hRecoVsGen_dRltpt2_eta_etacut0;
    TH2F*		hRecoVsGen_dRltpt2_phi_etacut0;
    TH2F*		hRecoVsGen_dRltpt1_pt_etacut0;
    TH2F*		hRecoVsGen_dRltpt1_et_etacut0;
    TH2F*		hRecoVsGen_dRltpt1_eta_etacut0;
    TH2F*		hRecoVsGen_dRltpt1_phi_etacut0;    
//    TH1F* 		hMatchedGenNumEv_Ratio; // (# matched ZSPJPTiC5 Jets)/(# All GenJets)
    TH1F* 		hMatchedGenGNumEv_Ratio; // (# matched GenJets)/(# All GenJets) --> this is the one
    TH1F* 		hMatchedGenGNumEv_Ratio_etacut0; // (# matched GenJets)/(# All GenJets) --> this is the one
    TH1F* 		hMatchedGenGNumEv_Ratio_dRltpt1; // (# matched GenJets)/(# All GenJets) --> this is the one
    TH1F* 		hMatchedGenGNumEv_Ratio_dRltpt1_etacut0; // (# matched GenJets)/(# All GenJets) --> this is the one
    TH1F*       hFakeRatio;
    TH1F*       hFakeRatio_etacut0;
    TH1F*       hFakeRatio_etacut1;
//    TH1F*       hFakeRatio_dRltpt2;
//    TH1F*       hFakeRatio_dRltpt2_etacut0;
//    TH1F*       hFakeRatio_dRltpt2_etacut1;
    
//    TH1F*		hMatchedCaloNumEv_Ratio; // (# matched ZSPJPTiC5 Jets)/(# All ZSPJPTiC5 Jets)
//    TH1F*		hMatchedGCaloNumEv_Ratio; // (# matched GenJets)/(# All ZSPJPTiC5 Jets)
    TH2F*		hRecoVsGen_pt;
    TH2F*		hRecoVsGen_et;
    TH2F*		hRecoVsGen_eta;
    TH2F*		hRecoVsGen_phi;
    TH2F*		hRecoVsGen_dRltpt2_pt;
    TH2F*		hRecoVsGen_dRltpt2_et;
    TH2F*		hRecoVsGen_dRltpt2_eta;
    TH2F*		hRecoVsGen_dRltpt2_phi;    
    TH2F*		hRecoVsGen_dRltpt1_pt;
    TH2F*		hRecoVsGen_dRltpt1_et;
    TH2F*		hRecoVsGen_dRltpt1_eta;
    TH2F*		hRecoVsGen_dRltpt1_phi;  
//     TH2F*		hRecoVsGen_dRltpt5_pt;
//     TH2F*		hRecoVsGen_dRltpt5_et;
//     TH2F*		hRecoVsGen_dRltpt5_eta;
//     TH2F*		hRecoVsGen_dRltpt5_phi; 
//     TH2F*		hRecoVsGen_dRlt1_pt;
//     TH2F*		hRecoVsGen_dRlt1_et;
//     TH2F*		hRecoVsGen_dRlt1_eta;
//     TH2F*		hRecoVsGen_dRlt1_phi;     


      // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
ZSP_Pu_JPTAnalyzer::ZSP_Pu_JPTAnalyzer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
  source_          = iConfig.getParameter<InputTag> ("src");
  matched_         = iConfig.getParameter<InputTag> ("matched");
  matchedjetsOne_  = iConfig.getParameter<InputTag> ("matchMapOne");
  fOutputFileName_ = iConfig.getUntrackedParameter<string>("HistOutFile",std::string("testMatch.root"));

}

int ZSP_Pu_JPTAnalyzer::determineIndex(Double_t* limBins, Double_t data, unsigned int nbreBins)
{
  
   int result =-1;
   if(data<limBins[0]) return result;
  
   for(unsigned int i = 0; i<nbreBins;i++){
    if(limBins[i]<= data && data<limBins[i+1]){
      result=i;
      break;}
    result=i;
   }

   return result;
  
}

ZSP_Pu_JPTAnalyzer::~ZSP_Pu_JPTAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
//   hOutputFile->cd() ;

   return;

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
ZSP_Pu_JPTAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
//   Double_t limBins4[]  = {10,20,30,40,50,60,70,80,100.0,120.,150.,200};
   Double_t limBins4[]  = {1,5,10,15,20,30,40};
   Double_t limBinsOld4[] = {20,30,40,50,60,70,80,100,120,150,200,250,300,350};

  cout << "[ZSP_Pu_JPTAnalyzer] analysing event " << iEvent.id() << endl;
  HaveMatchMap = kTRUE;
  try {
    iEvent.getByLabel (source_,source);
    iEvent.getByLabel (matched_,matched);
  } catch(std::exception& ce) {
    cerr << "[ZSP_Pu_JPTAnalyzer] caught std::exception " << ce.what() << endl;
    return;   
  }
  try {
     iEvent.getByLabel (matchedjetsOne_ , matchedjetsOne );
  } catch(std::exception& ce) {
    cerr << "[ZSP_Pu_JPTAnalyzer] caught std::exception " << ce.what() << endl;
    HaveMatchMap = kFALSE;
    return;
  }
  //
  // Printout for Raw Jets
  //
    int nGenJets=source->size();
    int nRecoJets=matched->size();
    int nMatchedRecoJets=matchedjetsOne->size();
   cout << "**********************" << endl;
   cout << "* Raw Jets Printout  *" << endl;
   cout << "**********************" << endl;
   cout << "In this Event: "<<iEvent.id()<<", there are: "<<nGenJets<<" GenJets (pass cfg file analysis cut-sometimes pt>20) and "<<nRecoJets<<" "<<matched_<<" (pass cfg file analysis cut-sometimes pt>20)"<<endl;
   cout << "  There are also: "<<nMatchedRecoJets<< " matched "<<matched_<<" (pass cfg file analysis cut-sometimes pt>20)."<<endl;
 
//    hMatchedGenNumEv_Ratio->Fill(nMatchedRecoJets/nGenJets);
 //   hMatchedCaloNumEv_Ratio->Fill(nMatchedRecoJets/nRecoJets);
    
  double GenEtaAll = 990.;
    
   for (CandidateCollection::const_iterator ijet=source->begin(); ijet!=source->end(); ijet++) {

//     Double_t GenJetEt = ijet->et();
      hAllGenJets_et->Fill(ijet->et());
      hAllGenJets_pt->Fill(ijet->pt());      
      GenEtaAll=ijet->eta();
      if (fabs(GenEtaAll)<=1.3){
        hAllGenJets_et_etacut0->Fill(ijet->et());
        hAllGenJets_pt_etacut0->Fill(ijet->pt());
     } else if (fabs(GenEtaAll) >1.3 && fabs(GenEtaAll)<3){
        cout<<"[ZSP_Pu_JPTAnalyzer::analyze, have an endcap jet, will fill hAllGenJets_et_etacut1 with Et: "<<ijet->et()<<endl;
        hAllGenJets_et_etacut1->Fill(ijet->et());
//        hAllGenJets_pt_etacut1->Fill(ijet->pt());   
     }
//     cout<<"   GenJetEt: "<<GenJetEt<<endl; 
   }
  double RecoEtaAll = 990.; 
        for(int iset=0; iset<100; iset++){
          ZSPJPTiC5Jets_unmatchstat[iset]=5;  // 0 = matched, 1 = unmatched, 5 = error
          ZSPJPTiC5Jets_eta_unmatch[iset]=9999.;  // eta of those recojets corresponding to index above
          ZSPJPTiC5Jets_et_unmatch[iset]=0.;   // et of those recojets corresponding to index above  
        }
          Int_t totalZSPJPTiC5Jets=0;
   for (CandidateCollection::const_iterator imjet=matched->begin(); imjet!=matched->end(); imjet++) {
 
       RecoEtaAll = imjet->eta();
      if(!HaveMatchMap){
        hUnMatchedZSPJPTiC5Jets_et->Fill(imjet->et());
        hUnMatchedZSPJPTiC5Jets_eta->Fill(imjet->eta());
          if (fabs(RecoEtaAll)<=1.3){
            hUnMatchedZSPJPTiC5Jets_et_etacut0->Fill(imjet->et());         
            hUnMatchedZSPJPTiC5Jets_eta_etacut0->Fill(imjet->eta());         
          } else if (fabs(RecoEtaAll) >1.3 && fabs(RecoEtaAll)<3){
            hUnMatchedZSPJPTiC5Jets_et_etacut1->Fill(imjet->et());                   
            hUnMatchedZSPJPTiC5Jets_eta_etacut1->Fill(imjet->eta());                   
          }
      } else {
          ZSPJPTiC5Jets_unmatchstat[totalZSPJPTiC5Jets]=1;
          ZSPJPTiC5Jets_eta_unmatch[totalZSPJPTiC5Jets]=imjet->eta();  // eta of those recojets corresponding to index above
          ZSPJPTiC5Jets_et_unmatch[totalZSPJPTiC5Jets]=imjet->et();   // et of those recojets corresponding to index above
          totalZSPJPTiC5Jets++;
    }
      hAllZSPJPTiC5Jets_et->Fill(imjet->et());     
      hAllZSPJPTiC5Jets_pt->Fill(imjet->pt());
      if (fabs(RecoEtaAll)<=1.3){
        hAllZSPJPTiC5Jets_et_etacut0->Fill(imjet->et());
        hAllZSPJPTiC5Jets_pt_etacut0->Fill(imjet->pt());
     } else if (fabs(RecoEtaAll) >1.3 && fabs(RecoEtaAll)<3){
        cout<<"[ZSP_Pu_JPTAnalyzer::analyze, have an endcap jet, will fill hAllZSPJPTiC5Jets_et_etacut1 with Et: "<<imjet->et()<<endl;
        hAllZSPJPTiC5Jets_et_etacut1->Fill(imjet->et());
 //       hAllZSPJPTiC5Jets_pt_etacut1->Fill(imjet->pt());   
     }           
 //    cout<<"   RecoJetEt: "<<RecoJetEt<<endl;
   }   
  //
  // Printout for OneToOne matcher
  //
  double dR=-1.;
  double GenEta = 9990.;
  double RecoEta = 9990.;
//   cout << "**********************" << endl;
//   cout << "* OneToOne Printout  *" << endl;
//   cout << "**********************" << endl;
  if(HaveMatchMap){
  for( CandMatchMap::const_iterator f  = matchedjetsOne->begin();
                                    f != matchedjetsOne->end();
                                    f++) {

      const Candidate *sourceRef = &*(f->key);
      const Candidate *matchRef  = &*(f->val);
      dR= DeltaR( sourceRef->p4() , matchRef->p4() );
      hdeltaR->Fill(dR);
//       printf("[ZSP_Pu_JPTAnalyzer] (et,eta,phi) source = %6.2f %5.2f %5.2f matched = %6.2f %5.2f %5.2f dR=%5.3f\n",
// 	     sourceRef->et(),
// 	     sourceRef->eta(),
// 	     sourceRef->phi(), 
// 	     matchRef->et(), 
// 	     matchRef->eta(),
// 	     matchRef->phi(), 
// 	     dR);
//      printf("[ZSP_Pu_JPTAnalyzer] (pt) source = %6.2f matched = %6.2f dR=%5.3f\n",
// 	     sourceRef->pt(),
// 	     matchRef->pt(), 
// 	     dR);

      GenEta = sourceRef->eta();
      RecoEta = matchRef->eta();
      hMatchGenJets_et->Fill(sourceRef->et());
      hMatchZSPJPTiC5Jets_et->Fill(matchRef->et());    
      hMatchGenJets_pt->Fill(sourceRef->pt());
      hMatchZSPJPTiC5Jets_pt->Fill(matchRef->pt());

	  hRecoVsGen_et->Fill(sourceRef->et(),matchRef->et());
	  hRecoVsGen_pt->Fill(sourceRef->pt(),matchRef->pt());
 	  hRecoVsGen_eta->Fill(sourceRef->eta(),matchRef->eta());
      hRecoVsGen_phi->Fill(sourceRef->phi(),matchRef->phi());
      
      if (dR<=0.2){
          hMatchGenJets_dRltpt2_et->Fill(sourceRef->et());
          hMatchZSPJPTiC5Jets_dRltpt2_et->Fill(matchRef->et());
          hMatchGenJets_dRltpt2_pt->Fill(sourceRef->pt());
          hMatchZSPJPTiC5Jets_dRltpt2_pt->Fill(matchRef->pt());
    	  hRecoVsGen_dRltpt2_et->Fill(sourceRef->et(),matchRef->et());
 	      hRecoVsGen_dRltpt2_pt->Fill(sourceRef->pt(),matchRef->pt());
 	      hRecoVsGen_dRltpt2_eta->Fill(sourceRef->eta(),matchRef->eta());
          hRecoVsGen_dRltpt2_phi->Fill(sourceRef->phi(),matchRef->phi()); 
          for(int imatched = 0;imatched<totalZSPJPTiC5Jets;imatched++){
             if(ZSPJPTiC5Jets_et_unmatch[imatched]==matchRef->et()) {
                ZSPJPTiC5Jets_unmatchstat[imatched]=0;
             }
          }
          Double_t ESim=sourceRef->et();
          if(determineIndex(limBins4,ESim,6)!=-1){
		     EThist[ determineIndex(limBins4,ESim,6)]->Fill((matchRef->et())/(sourceRef->et() ));
		     etahist[ determineIndex(limBins4,ESim,6)]->Fill(fabs(matchRef->eta())-fabs(sourceRef->eta() ));
		     phihist[ determineIndex(limBins4,ESim,6)]->Fill(deltaPhi(matchRef->phi(),sourceRef->phi()));
//		     if (fabs(matchRef->phi()-sourceRef->phi())
	      }          
          if(determineIndex(limBinsOld4,ESim,13)!=-1){
		     EThistOld[ determineIndex(limBinsOld4,ESim,13)]->Fill((matchRef->et())/(sourceRef->et() ));
	      }   
//	      cout<<"did ethist"<<endl;
//           Double_t pSim=sourceRef->pt();
//           if(determineIndex(limBins4,pSim,6)!=-1){
// 		     pThist[ determineIndex(limBins4,pSim,6)]->Fill((matchRef->pt())/(sourceRef->pt() ));
// 	      } 	 
//	      cout<<"did pthist"<<endl;
        if (dR<=0.1){
           hMatchGenJets_dRltpt1_et->Fill(sourceRef->et());
          hMatchZSPJPTiC5Jets_dRltpt1_et->Fill(matchRef->et());
          hMatchGenJets_dRltpt1_pt->Fill(sourceRef->pt());
          hMatchZSPJPTiC5Jets_dRltpt1_pt->Fill(matchRef->pt());
    	  hRecoVsGen_dRltpt1_et->Fill(sourceRef->et(),matchRef->et());
 	      hRecoVsGen_dRltpt1_pt->Fill(sourceRef->pt(),matchRef->pt());
 	      hRecoVsGen_dRltpt1_eta->Fill(sourceRef->eta(),matchRef->eta());
          hRecoVsGen_dRltpt1_phi->Fill(sourceRef->phi(),matchRef->phi()); 
          Double_t ESim=sourceRef->et();
          if(determineIndex(limBins4,ESim,6)!=-1){
		     EThist_dRltpt1[ determineIndex(limBins4,ESim,6)]->Fill((matchRef->et())/(sourceRef->et() ));
	      }          
          if(determineIndex(limBinsOld4,ESim,13)!=-1){
		     EThist_dRltpt1Old[ determineIndex(limBinsOld4,ESim,13)]->Fill((matchRef->et())/(sourceRef->et() ));
	      }             
        }
      } else {
//         hUnMatchedZSPJPTiC5Jets_et->Fill(matchRef->et());
//         hUnMatchedZSPJPTiC5Jets_eta->Fill(matchRef->eta());
//           if (fabs(RecoEta)<=1.3){
//             hUnMatchedZSPJPTiC5Jets_et_etacut0->Fill(matchRef->et());         
//             hUnMatchedZSPJPTiC5Jets_eta_etacut0->Fill(matchRef->eta());         
//           } else if (fabs(RecoEta) >1.3 && fabs(RecoEta)<3){
//             hUnMatchedZSPJPTiC5Jets_eta_etacut1->Fill(matchRef->eta());                   
//             hUnMatchedZSPJPTiC5Jets_eta_etacut1->Fill(matchRef->eta());                   
//           }
      }
 // Barrel     
    if(fabs(GenEta)<=1.3){
       hdeltaR_etacut0->Fill(dR);
	  hRecoVsGen_et_etacut0->Fill(sourceRef->et(),matchRef->et());
	  hRecoVsGen_pt_etacut0->Fill(sourceRef->pt(),matchRef->pt());
 	  hRecoVsGen_eta_etacut0->Fill(sourceRef->eta(),matchRef->eta());
      hRecoVsGen_phi_etacut0->Fill(sourceRef->phi(),matchRef->phi());
      hMatchGenJets_et_etacut0->Fill(sourceRef->et());
      hMatchZSPJPTiC5Jets_et_etacut0->Fill(matchRef->et());    
      
      hMatchGenJets_pt_etacut0->Fill(sourceRef->pt());
      hMatchZSPJPTiC5Jets_pt_etacut0->Fill(matchRef->pt());  

     if(dR<=0.2) {
    	  hRecoVsGen_dRltpt2_et_etacut0->Fill(sourceRef->et(),matchRef->et());
 	      hRecoVsGen_dRltpt2_pt_etacut0->Fill(sourceRef->pt(),matchRef->pt());
 	      hRecoVsGen_dRltpt2_eta_etacut0->Fill(sourceRef->eta(),matchRef->eta());
          hRecoVsGen_dRltpt2_phi_etacut0->Fill(sourceRef->phi(),matchRef->phi()); 
          Double_t ResFrac=(matchRef->et())/(sourceRef->et());
          hSimpleResolution_Energy->Fill(sourceRef->et(),ResFrac);
          hMatchGenJets_dRltpt2_et_etacut0->Fill(sourceRef->et());
          hMatchZSPJPTiC5Jets_dRltpt2_et_etacut0->Fill(matchRef->et());
          hMatchGenJets_dRltpt2_pt_etacut0->Fill(sourceRef->pt());
          hMatchZSPJPTiC5Jets_dRltpt2_pt_etacut0->Fill(matchRef->pt());
          Double_t ESim_etacut0=sourceRef->et();
          if(determineIndex(limBins4,ESim_etacut0,6)!=-1){
		     EThist_etacut0[ determineIndex(limBins4,ESim_etacut0,6)]->Fill((matchRef->et())/(sourceRef->et() ));
		     etahist_etacut0[ determineIndex(limBins4,ESim_etacut0,6)]->Fill(fabs(matchRef->eta())-fabs(sourceRef->eta() ));
		     phihist_etacut0[ determineIndex(limBins4,ESim_etacut0,6)]->Fill(deltaPhi(matchRef->phi(),sourceRef->phi() ));
	      }          
          if(determineIndex(limBinsOld4,ESim_etacut0,13)!=-1){
		     EThist_etacut0Old[ determineIndex(limBinsOld4,ESim_etacut0,13)]->Fill((matchRef->et())/(sourceRef->et() ));
	      }   
	      if(dR<=0.1){
    	    hRecoVsGen_dRltpt1_et_etacut0->Fill(sourceRef->et(),matchRef->et());
 	        hRecoVsGen_dRltpt1_pt_etacut0->Fill(sourceRef->pt(),matchRef->pt());
 	        hRecoVsGen_dRltpt1_eta_etacut0->Fill(sourceRef->eta(),matchRef->eta());
            hRecoVsGen_dRltpt1_phi_etacut0->Fill(sourceRef->phi(),matchRef->phi()); 
            hMatchGenJets_dRltpt1_et_etacut0->Fill(sourceRef->et());
            hMatchZSPJPTiC5Jets_dRltpt1_et_etacut0->Fill(matchRef->et());
            hMatchGenJets_dRltpt1_pt_etacut0->Fill(sourceRef->pt());
            hMatchZSPJPTiC5Jets_dRltpt1_pt_etacut0->Fill(matchRef->pt());	      	      
	      }
//	      cout<<"did ethistold"<<endl;	      
//           if(determineIndex(limBinsOld4,pSim,13)!=-1){
// 		     pThistOld[ determineIndex(limBinsOld4,pSim,13)]->Fill((matchRef->pt())/(sourceRef->pt() ));
// 	      } 	      
// 	      cout<<"did pthistold"<<endl;
     }  
//      if(dR<=0.5) {
//     	  hRecoVsGen_dRltpt5_et->Fill(sourceRef->et(),matchRef->et());
//  	      hRecoVsGen_dRltpt5_pt->Fill(sourceRef->pt(),matchRef->pt());
//  	      hRecoVsGen_dRltpt5_eta->Fill(sourceRef->eta(),matchRef->eta());
//           hRecoVsGen_dRltpt5_phi->Fill(sourceRef->phi(),matchRef->phi());     
//      }  
//      if(dR<=1.0) {
//     	  hRecoVsGen_dRlt1_et->Fill(sourceRef->et(),matchRef->et());
//  	      hRecoVsGen_dRlt1_pt->Fill(sourceRef->pt(),matchRef->pt());
//  	      hRecoVsGen_dRlt1_eta->Fill(sourceRef->eta(),matchRef->eta());
//           hRecoVsGen_dRlt1_phi->Fill(sourceRef->phi(),matchRef->phi());     
//      } 
    } 
// endcap
    else if(fabs(GenEta) >1.3 && fabs(GenEta)<3){
           hdeltaR_etacut1->Fill(dR);
	  hRecoVsGen_et_etacut1->Fill(sourceRef->et(),matchRef->et());
	  hRecoVsGen_pt_etacut1->Fill(sourceRef->pt(),matchRef->pt());
 	  hRecoVsGen_eta_etacut1->Fill(sourceRef->eta(),matchRef->eta());
      hRecoVsGen_phi_etacut1->Fill(sourceRef->phi(),matchRef->phi());
      hMatchGenJets_et_etacut1->Fill(sourceRef->et());
      hMatchZSPJPTiC5Jets_et_etacut1->Fill(matchRef->et());    
      
//      hMatchGenJets_pt_etacut1->Fill(sourceRef->pt());
//      hMatchZSPJPTiC5Jets_pt_etacut1->Fill(matchRef->pt());  

     if(dR<=0.2) {
    	  hRecoVsGen_dRltpt2_et_etacut1->Fill(sourceRef->et(),matchRef->et());
 	      hRecoVsGen_dRltpt2_pt_etacut1->Fill(sourceRef->pt(),matchRef->pt());
 	      hRecoVsGen_dRltpt2_eta_etacut1->Fill(sourceRef->eta(),matchRef->eta());
          hRecoVsGen_dRltpt2_phi_etacut1->Fill(sourceRef->phi(),matchRef->phi()); 
//          Double_t ResFrac_etacut1=(matchRef->et())/(sourceRef->et());
   //       hSimpleResolution_Energy_etacut1->Fill(sourceRef->et(),ResFrac_etacut1);
        cout<<"[ZSP_Pu_JPTAnalyzer::analyze, have a matched endcap jet DeltaR<=0.1, will fill hMatchGenJets_dRltpt2_et_etacut1 with Et: "<<sourceRef->et()<<" and hMatchZSPJPTiC5Jets_dRltpt2_et_etacut1 with Et: "<<matchRef->et()<<endl;
          hMatchGenJets_dRltpt2_et_etacut1->Fill(sourceRef->et());
          hMatchZSPJPTiC5Jets_dRltpt2_et_etacut1->Fill(matchRef->et());
//          hMatchGenJets_dRltpt2_pt_etacut1->Fill(sourceRef->pt());
//          hMatchZSPJPTiC5Jets_dRltpt2_pt_etacut1->Fill(matchRef->pt());
          Double_t ESim_etacut1=sourceRef->et();
          if(determineIndex(limBins4,ESim_etacut1,6)!=-1){
		     EThist_etacut1[ determineIndex(limBins4,ESim_etacut1,6)]->Fill((matchRef->et())/(sourceRef->et() ));
		     etahist_etacut1[ determineIndex(limBins4,ESim_etacut1,6)]->Fill(fabs(matchRef->eta())-fabs(sourceRef->eta() ));
		     phihist_etacut1[ determineIndex(limBins4,ESim_etacut1,6)]->Fill(deltaPhi(matchRef->phi(),sourceRef->phi()));
	      }          	 
          if(determineIndex(limBinsOld4,ESim_etacut1,13)!=-1){
		     EThist_etacut1Old[ determineIndex(limBinsOld4,ESim_etacut1,13)]->Fill((matchRef->et())/(sourceRef->et() ));
	      }   
	      if(dR<=0.1){
    	    hRecoVsGen_dRltpt1_et_etacut1->Fill(sourceRef->et(),matchRef->et());
 	        hRecoVsGen_dRltpt1_pt_etacut1->Fill(sourceRef->pt(),matchRef->pt());
 	        hRecoVsGen_dRltpt1_eta_etacut1->Fill(sourceRef->eta(),matchRef->eta());
            hRecoVsGen_dRltpt1_phi_etacut1->Fill(sourceRef->phi(),matchRef->phi()); 
            hMatchGenJets_dRltpt1_et_etacut1->Fill(sourceRef->et());
            hMatchZSPJPTiC5Jets_dRltpt1_et_etacut1->Fill(matchRef->et());
	      }	      
     }  
    }
  }
   for(int imatchedjets = 0;imatchedjets<totalZSPJPTiC5Jets;imatchedjets++){
      if(ZSPJPTiC5Jets_unmatchstat[imatchedjets]==1) {
        hUnMatchedZSPJPTiC5Jets_et->Fill(ZSPJPTiC5Jets_et_unmatch[imatchedjets]);
        hUnMatchedZSPJPTiC5Jets_eta->Fill(ZSPJPTiC5Jets_eta_unmatch[imatchedjets]);
          if (fabs(ZSPJPTiC5Jets_eta_unmatch[imatchedjets])<=1.3){
            hUnMatchedZSPJPTiC5Jets_et_etacut0->Fill(ZSPJPTiC5Jets_et_unmatch[imatchedjets]);         
            hUnMatchedZSPJPTiC5Jets_eta_etacut0->Fill(ZSPJPTiC5Jets_eta_unmatch[imatchedjets]);         
          } else if (fabs(ZSPJPTiC5Jets_eta_unmatch[imatchedjets]) >1.3 && fabs(ZSPJPTiC5Jets_eta_unmatch[imatchedjets])<3){
            hUnMatchedZSPJPTiC5Jets_et_etacut1->Fill(ZSPJPTiC5Jets_et_unmatch[imatchedjets]);                   
            hUnMatchedZSPJPTiC5Jets_eta_etacut1->Fill(ZSPJPTiC5Jets_eta_unmatch[imatchedjets]);                   
          }             
       } else if(ZSPJPTiC5Jets_unmatchstat[imatchedjets]==5){
         cout<<"[ZSP_Pu_JPTAnalyzer::analyze, Error (5) in ZSPJPTiC5Jets_unmatchstat for imatchedjets = "<<imatchedjets<<endl;
       }
   }
 } else {
    cout<<"no MatchMap for this event: "<<iEvent.id()<<endl;
 }
  hTotalLenght->Fill( dR );

 cout<<"[ZSP_Pu_JPTAnalyzer]:: end analyze"<<endl;


#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
ZSP_Pu_JPTAnalyzer::beginJob(const edm::EventSetup&)
{
 cout<<"[ZSP_Pu_JPTAnalyzer]:: start beginJob"<<endl;

   Double_t limBins2[]  = {1,5,10,15,20,30,40};
   Double_t limBinsOld2[] = {20,30,40,50,60,70,80,100,120,150,200,250,300,350};
   hOutputFile   = new TFile( fOutputFileName_.c_str(), "RECREATE" ) ;
   hTotalLenght  = new TH1D( "hTotalLenght", "Total Lenght", 100,  0., 5. );
   hdeltaR = new TH1F("hdeltaR","All #DeltaR_{m} values, all #eta",1000,0.,5);
   hdeltaR_etacut0 = new TH1F("hdeltaR_etacut0","All #DeltaR_{m} |#eta|<=1.3",1000,0.,5);
   hdeltaR_etacut1 = new TH1F("hdeltaR_etacut1","All #DeltaR_{m} 1.3 <| #eta | <3)",1000,0.,5);
   ratioE = new TH1F ("ratioE", "E^{JetPlusTrackZSPCorJetIcone5}_{T}/E^{GenJets}_{T}, all #eta",6,limBins2);
   ratioE->Sumw2();
   sigmaErEm = new TH1F ("sigmaErEm", "sigma(E^{JetPlusTrackZSPCorJetIcone5}_{T}/E^{GenJets}_{T}) matched OneToOne #DeltaR_{m}<=0.2, all #eta",6,limBins2);
   sigmaErEm->Sumw2();
   ETresolution = new TH1F ("ETresolution", "E_{T} Resolution matched OneToOne #DeltaR_{m}<=0.2, all #eta",6,limBins2);
   ETresolution->Sumw2();   
    for (unsigned int indexH=0;indexH<6;indexH++)  {
      sprintf(nameHist,"ETdistribution%i",indexH);
      sprintf(label,"ET(reco)/ET(gen) ET(gen) #in #left[%f , %f #right] GeV, all #eta",limBins2[indexH],limBins2[indexH+1]);
      EThist[indexH]=new TH1F(nameHist,label,100,0., 2);
      EThist[indexH]->Sumw2();
      EThist[indexH]->GetXaxis()->SetTitle("E_{T}^{reco}/E_{t}^{gen}");
      EThist[indexH]->GetYaxis()->SetTitle("#");
     }

   ratioEOld = new TH1F ("ratioEOld", "E^{JetPlusTrackZSPCorJetIcone5}_{T}/E^{GenJets}_{T} (different bins), all #eta",13,limBinsOld2);
   ratioEOld->Sumw2();
   sigmaErEmOld = new TH1F ("sigmaErEmOld", "sigma(E^{JetPlusTrackZSPCorJetIcone5}_{T}/E^{GenJets}_{T}) matched OneToOne #DeltaR_{m}<=0.2 (diff bins), all #eta",13,limBinsOld2);
   sigmaErEmOld->Sumw2();
   ETresolutionOld = new TH1F ("ETresolutionOld", "E_{T} Resolution matched OneToOne #DeltaR_{m}<=0.2 (different bins), all #eta",13,limBinsOld2);
   ETresolutionOld->Sumw2();   
    for (unsigned int indexHOld=0;indexHOld<13;indexHOld++)  {
      sprintf(nameHist,"ETdistributionOld%i",indexHOld);
      sprintf(label,"ET(reco)/ET(gen) ET(gen) #in #left[%f , %f #right] GeV (different bins), all #eta",limBinsOld2[indexHOld],limBinsOld2[indexHOld+1]);
      EThistOld[indexHOld]=new TH1F(nameHist,label,100,0., 2);
      EThistOld[indexHOld]->Sumw2();
      EThistOld[indexHOld]->GetXaxis()->SetTitle("E_{T}^{reco}/E_{t}^{gen}");
      EThistOld[indexHOld]->GetYaxis()->SetTitle("#");
     }
   ratioE_dRltpt1 = new TH1F ("ratioE_dRltpt1", "E^{JetPlusTrackZSPCorJetIcone5}_{T}/E^{GenJets}_{T}, all #eta, #DeltaR_{m}<=0.1",6,limBins2);
   ratioE_dRltpt1->Sumw2();
   sigmaErEm_dRltpt1 = new TH1F ("sigmaErEm_dRltpt1", "sigma(E^{JetPlusTrackZSPCorJetIcone5}_{T}/E^{GenJets}_{T}) matched OneToOne #DeltaR_{m}<=0.1, all #eta",6,limBins2);
   sigmaErEm_dRltpt1->Sumw2();
   ETresolution_dRltpt1 = new TH1F ("ETresolution_dRltpt1", "E_{T} Resolution matched OneToOne #DeltaR_{m}<=0.1, all #eta",6,limBins2);
   ETresolution_dRltpt1->Sumw2();   
    for (unsigned int indexH=0;indexH<6;indexH++)  {
      sprintf(nameHist,"ETdistribution_dRltpt1%i",indexH);
      sprintf(label,"ET(reco)/ET(gen) ET(gen) #in #left[%f , %f #right] GeV, all #eta",limBins2[indexH],limBins2[indexH+1]);
      EThist_dRltpt1[indexH]=new TH1F(nameHist,label,100,0., 2);
      EThist_dRltpt1[indexH]->Sumw2();
      EThist_dRltpt1[indexH]->GetXaxis()->SetTitle("E_{T}^{reco}/E_{t}^{gen}");
      EThist_dRltpt1[indexH]->GetYaxis()->SetTitle("#");
     }

   ratioE_dRltpt1Old = new TH1F ("ratioE_dRltpt1Old", "E^{JetPlusTrackZSPCorJetIcone5}_{T}/E^{GenJets}_{T} (different bins), all #eta, #DeltaR_{m}<=0.1",13,limBinsOld2);
   ratioE_dRltpt1Old->Sumw2();
   sigmaErEm_dRltpt1Old = new TH1F ("sigmaErEm_dRltpt1Old", "sigma(E^{JetPlusTrackZSPCorJetIcone5}_{T}/E^{GenJets}_{T}) matched OneToOne #DeltaR_{m}<=0.1 (diff bins), all #eta",13,limBinsOld2);
   sigmaErEm_dRltpt1Old->Sumw2();
   ETresolution_dRltpt1Old = new TH1F ("ETresolution_dRltpt1Old", "E_{T} Resolution matched OneToOne #DeltaR_{m}<=0.1 (different bins), all #eta",13,limBinsOld2);
   ETresolution_dRltpt1Old->Sumw2();   
    for (unsigned int indexHOld=0;indexHOld<13;indexHOld++)  {
      sprintf(nameHist,"ETdistribution_dRltpt1Old%i",indexHOld);
      sprintf(label,"ET(reco)/ET(gen) ET(gen) #in #left[%f , %f #right] GeV (different bins), all #eta, #DeltaR_{m}<=0.1",limBinsOld2[indexHOld],limBinsOld2[indexHOld+1]);
      EThist_dRltpt1Old[indexHOld]=new TH1F(nameHist,label,100,0., 2);
      EThist_dRltpt1Old[indexHOld]->Sumw2();
      EThist_dRltpt1Old[indexHOld]->GetXaxis()->SetTitle("E_{T}^{reco}/E_{t}^{gen}");
      EThist_dRltpt1Old[indexHOld]->GetYaxis()->SetTitle("#");
     }    

// barrel plots make:
   ratioE_etacut0 = new TH1F ("ratioE_etacut0", "E^{JetPlusTrackZSPCorJetIcone5}_{T}/E^{GenJets}_{T}, 0<= | #eta | <=1.3",6,limBins2);
   ratioE_etacut0->Sumw2();
   sigmaErEm_etacut0 = new TH1F ("sigmaErEm_etacut0", "sigma(E^{JetPlusTrackZSPCorJetIcone5}_{T}/E^{GenJets}_{T}) matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",6,limBins2);
   sigmaErEm_etacut0->Sumw2();
   ETresolution_etacut0 = new TH1F ("ETresolution_etacut0", "E_{T} Resolution matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",6,limBins2);
   ETresolution_etacut0->Sumw2();   
    for (unsigned int indexH=0;indexH<6;indexH++)  {
      sprintf(nameHist,"ETdistribution_etacut0%i",indexH);
      sprintf(label,"ET(reco)/ET(gen) ET(gen) #in #left[%f , %f #right] GeV, 0<= | #eta | <=1.3",limBins2[indexH],limBins2[indexH+1]);
      EThist_etacut0[indexH]=new TH1F(nameHist,label,100,0., 2);
      EThist_etacut0[indexH]->Sumw2();
      EThist_etacut0[indexH]->GetXaxis()->SetTitle("E_{T}^{reco}/E_{t}^{gen}");
      EThist_etacut0[indexH]->GetYaxis()->SetTitle("#");
     }

   ratioE_etacut0Old = new TH1F ("ratioE_etacut0Old", "E^{JetPlusTrackZSPCorJetIcone5}_{T}/E^{GenJets}_{T} (different bins), 0<= | #eta | <=1.3",13,limBinsOld2);
   ratioE_etacut0Old->Sumw2();
   sigmaErEm_etacut0Old = new TH1F ("sigmaErEm_etacut0Old", "sigma(E^{JetPlusTrackZSPCorJetIcone5}_{T}/E^{GenJets}_{T}) matched OneToOne #DeltaR_{m}<=0.2 (diff bins), 0<= | #eta | <=1.3",13,limBinsOld2);
   sigmaErEm_etacut0Old->Sumw2();
   ETresolution_etacut0Old = new TH1F ("ETresolution_etacut0Old", "E_{T} Resolution matched OneToOne #DeltaR_{m}<=0.2 (different bins), 0<= | #eta | <=1.3",13,limBinsOld2);
   ETresolution_etacut0Old->Sumw2();   
    for (unsigned int indexHOld=0;indexHOld<13;indexHOld++)  {
      sprintf(nameHist,"ETdistribution_etacut0Old%i",indexHOld);
      sprintf(label,"ET(reco)/ET(gen) ET(gen) #in #left[%f , %f #right] GeV (different bins), 0<= | #eta | <=1.3",limBinsOld2[indexHOld],limBinsOld2[indexHOld+1]);
      EThist_etacut0Old[indexHOld]=new TH1F(nameHist,label,100,0., 2);
      EThist_etacut0Old[indexHOld]->Sumw2();
      EThist_etacut0Old[indexHOld]->GetXaxis()->SetTitle("E_{T}^{reco}/E_{t}^{gen}");
      EThist_etacut0Old[indexHOld]->GetYaxis()->SetTitle("#");
     }
// endcap plots make:
   ratioE_etacut1 = new TH1F ("ratioE_etacut1", "E^{JetPlusTrackZSPCorJetIcone5}_{T}/E^{GenJets}_{T}, 1.3 <| #eta | <3",6,limBins2);
   ratioE_etacut1->Sumw2();
   sigmaErEm_etacut1 = new TH1F ("sigmaErEm_etacut1", "sigma(E^{JetPlusTrackZSPCorJetIcone5}_{T}/E^{GenJets}_{T}) matched OneToOne #DeltaR_{m}<=0.2, 1.3 <| #eta | <3",6,limBins2);
   sigmaErEm_etacut1->Sumw2();
   ETresolution_etacut1 = new TH1F ("ETresolution_etacut1", "E_{T} Resolution matched OneToOne #DeltaR_{m}<=0.2, 1.3 <| #eta | <3",6,limBins2);
   ETresolution_etacut1->Sumw2();   
    for (unsigned int indexH=0;indexH<6;indexH++)  {
      sprintf(nameHist,"ETdistribution_etacut1%i",indexH);
      sprintf(label,"ET(reco)/ET(gen) ET(gen) #in #left[%f , %f #right] GeV, 1.3 <| #eta | <3",limBins2[indexH],limBins2[indexH+1]);
      EThist_etacut1[indexH]=new TH1F(nameHist,label,100,0., 2);
      EThist_etacut1[indexH]->Sumw2();
      EThist_etacut1[indexH]->GetXaxis()->SetTitle("E_{T}^{reco}/E_{t}^{gen}");
      EThist_etacut1[indexH]->GetYaxis()->SetTitle("#");
     }

   ratioE_etacut1Old = new TH1F ("ratioE_etacut1Old", "E^{JetPlusTrackZSPCorJetIcone5}_{T}/E^{GenJets}_{T} (different bins), 1.3 <| #eta | <3",13,limBinsOld2);
   ratioE_etacut1Old->Sumw2();
   sigmaErEm_etacut1Old = new TH1F ("sigmaErEm_etacut1Old", "sigma(E^{JetPlusTrackZSPCorJetIcone5}_{T}/E^{GenJets}_{T}) matched OneToOne #DeltaR_{m}<=0.2 (diff bins), 1.3 <| #eta | <3",13,limBinsOld2);
   sigmaErEm_etacut1Old->Sumw2();
   ETresolution_etacut1Old = new TH1F ("ETresolution_etacut1Old", "E_{T} Resolution matched OneToOne #DeltaR_{m}<=0.2 (different bins), 1.3 <| #eta | <3",13,limBinsOld2);
   ETresolution_etacut1Old->Sumw2();   
    for (unsigned int indexHOld=0;indexHOld<13;indexHOld++)  {
      sprintf(nameHist,"ETdistribution_etacut1Old%i",indexHOld);
      sprintf(label,"ET(reco)/ET(gen) ET(gen) #in #left[%f , %f #right] GeV (different bins), 1.3 <| #eta | <3",limBinsOld2[indexHOld],limBinsOld2[indexHOld+1]);
      EThist_etacut1Old[indexHOld]=new TH1F(nameHist,label,100,0., 2);
      EThist_etacut1Old[indexHOld]->Sumw2();
      EThist_etacut1Old[indexHOld]->GetXaxis()->SetTitle("E_{T}^{reco}/E_{t}^{gen}");
      EThist_etacut1Old[indexHOld]->GetYaxis()->SetTitle("#");
     }
//
// position resolution:
   ratioEta = new TH1F ("ratioEta", "<|#eta(JetPlusTrackZSPCorJetIcone5)|-|#eta(GenJets)|>, all #eta",6,limBins2);
   ratioEta->Sumw2();
   sigmaeta = new TH1F ("sigmaeta", "sigma(|#eta(JetPlusTrackZSPCorJetIcone5)|-|#eta(GenJets)|) matched OneToOne #DeltaR_{m}<=0.2, all #eta",6,limBins2);
   sigmaeta->Sumw2();
   etaResolution = new TH1F ("etaResolution", "#eta Resolution (sigma/mean - useless: use sigma) matched OneToOne #DeltaR_{m}<=0.2, all #eta",6,limBins2);
   etaResolution->Sumw2();   
    for (unsigned int indexH=0;indexH<6;indexH++)  {
      sprintf(nameHist,"etaDistribution%i",indexH);
      sprintf(label,"|#eta(reco)|-|#eta(gen)| ET(gen) #in #left[%f , %f #right] GeV, all #eta",limBins2[indexH],limBins2[indexH+1]);
      etahist[indexH]=new TH1F(nameHist,label,100,-1., 1.);
      etahist[indexH]->Sumw2();
      etahist[indexH]->GetXaxis()->SetTitle("|#eta(reco)|-|#eta(gen)|");
      etahist[indexH]->GetYaxis()->SetTitle("#");
     }
   ratioEta_etacut0 = new TH1F ("ratioEta_etacut0", "<|#eta(JetPlusTrackZSPCorJetIcone5)|-|#eta(GenJets)|>, 0<= | #eta | <=1.3",6,limBins2);
   ratioEta_etacut0->Sumw2();
   sigmaeta_etacut0 = new TH1F ("sigmaeta_etacut0", "sigma(|#eta(JetPlusTrackZSPCorJetIcone5)|-|#eta(GenJets)|) matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",6,limBins2);
   sigmaeta_etacut0->Sumw2();
   etaResolution_etacut0 = new TH1F ("etaResolution_etacut0", "#eta Resolution(sigma/mean - useless: use sigma) matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",6,limBins2);
   etaResolution_etacut0->Sumw2();   
    for (unsigned int indexH=0;indexH<6;indexH++)  {
      sprintf(nameHist,"etaDistribution_etacut0%i",indexH);
      sprintf(label,"|#eta(reco)|-|#eta(gen)| ET(gen) #in #left[%f , %f #right] GeV, 0<= | #eta | <=1.3",limBins2[indexH],limBins2[indexH+1]);
      etahist_etacut0[indexH]=new TH1F(nameHist,label,100,-1., 1.);
      etahist_etacut0[indexH]->Sumw2();
      etahist_etacut0[indexH]->GetXaxis()->SetTitle("|#eta(reco)|-|#eta(gen)|");
      etahist_etacut0[indexH]->GetYaxis()->SetTitle("#");
     }
   ratioEta_etacut1 = new TH1F ("ratioEta_etacut1", "<|#eta(JetPlusTrackZSPCorJetIcone5)|-|#eta(GenJets)|>, 1.3 <| #eta | <3",6,limBins2);
   ratioEta_etacut1->Sumw2();
   sigmaeta_etacut1 = new TH1F ("sigmaeta_etacut1", "sigma(|#eta(JetPlusTrackZSPCorJetIcone5)|-|#eta(GenJets)|) matched OneToOne #DeltaR_{m}<=0.2, 1.3 <| #eta | <3",6,limBins2);
   sigmaeta_etacut1->Sumw2();
   etaResolution_etacut1 = new TH1F ("etaResolution_etacut1", "#eta Resolution(sigma/mean - useless: use sigma) matched OneToOne #DeltaR_{m}<=0.2, 1.3 <| #eta | <3",6,limBins2);
   etaResolution_etacut1->Sumw2();   
    for (unsigned int indexH=0;indexH<6;indexH++)  {
      sprintf(nameHist,"etaDistribution_etacut1%i",indexH);
      sprintf(label,"|#eta(reco)|-|#eta(gen)| ET(gen) #in #left[%f , %f #right] GeV, 1.3 <| #eta | <3",limBins2[indexH],limBins2[indexH+1]);
      etahist_etacut1[indexH]=new TH1F(nameHist,label,100,-1., 1.);
      etahist_etacut1[indexH]->Sumw2();
      etahist_etacut1[indexH]->GetXaxis()->SetTitle("|#eta(reco)|-|#eta(gen)|");
      etahist_etacut1[indexH]->GetYaxis()->SetTitle("#");
     }
   ratioPhi = new TH1F ("ratioPhi", "<#phi(JetPlusTrackZSPCorJetIcone5)-#phi(GenJets)>, all #eta",6,limBins2);
   ratioPhi->Sumw2();
   sigmaphi = new TH1F ("sigmaphi", "sigma(#phi(JetPlusTrackZSPCorJetIcone5)-#phi(GenJets)) matched OneToOne #DeltaR_{m}<=0.2, all #eta",6,limBins2);
   sigmaphi->Sumw2();
   phiResolution = new TH1F ("phiResolution", "#phi Resolution(sigma/mean - useless: use sigma) matched OneToOne #DeltaR_{m}<=0.2, all #eta",6,limBins2);
   phiResolution->Sumw2();   
    for (unsigned int indexH=0;indexH<6;indexH++)  {
      sprintf(nameHist,"phiDistribution%i",indexH);
      sprintf(label,"#phi(reco)-#phi(gen) ET(gen) #in #left[%f , %f #right] GeV, all #eta",limBins2[indexH],limBins2[indexH+1]);
      phihist[indexH]=new TH1F(nameHist,label,100,-1., 1.);
      phihist[indexH]->Sumw2();
      phihist[indexH]->GetXaxis()->SetTitle("#phi(reco)-#phi(gen)");
      phihist[indexH]->GetYaxis()->SetTitle("#");
     }
   ratioPhi_etacut0 = new TH1F ("ratioPhi_etacut0", "<#phi(JetPlusTrackZSPCorJetIcone5)-#phi(GenJets)>, 0<= | #eta | <=1.3",6,limBins2);
   ratioPhi_etacut0->Sumw2();
   sigmaphi_etacut0 = new TH1F ("sigmaphi_etacut0", "sigma(#phi(JetPlusTrackZSPCorJetIcone5)-#phi(GenJets)) matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",6,limBins2);
   sigmaphi_etacut0->Sumw2();
   phiResolution_etacut0 = new TH1F ("phiResolution_etacut0", "#phi Resolution(sigma/mean - useless: use sigma) matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",6,limBins2);
   phiResolution_etacut0->Sumw2();   
    for (unsigned int indexH=0;indexH<6;indexH++)  {
      sprintf(nameHist,"phiDistribution_etacut0%i",indexH);
      sprintf(label,"#phi(reco)-#phi(gen) ET(gen) #in #left[%f , %f #right] GeV, 0<= | #eta | <=1.3",limBins2[indexH],limBins2[indexH+1]);
      phihist_etacut0[indexH]=new TH1F(nameHist,label,100,-1., 1.);
      phihist_etacut0[indexH]->Sumw2();
      phihist_etacut0[indexH]->GetXaxis()->SetTitle("#phi(reco)-#phi(gen)");
      phihist_etacut0[indexH]->GetYaxis()->SetTitle("#");
     }
   ratioPhi_etacut1 = new TH1F ("ratioPhi_etacut1", "<#phi(JetPlusTrackZSPCorJetIcone5)-#phi(GenJets)>, 1.3 <| #eta | <3",6,limBins2);
   ratioPhi_etacut1->Sumw2();
   sigmaphi_etacut1 = new TH1F ("sigmaphi_etacut1", "sigma(#phi(JetPlusTrackZSPCorJetIcone5)-#phi(GenJets)) matched OneToOne #DeltaR_{m}<=0.2, 1.3 <| #eta | <3",6,limBins2);
   sigmaphi_etacut1->Sumw2();
   phiResolution_etacut1 = new TH1F ("phiResolution_etacut1", "#phi Resolution(sigma/mean - useless: use sigma) matched OneToOne #DeltaR_{m}<=0.2, 1.3 <| #eta | <3",6,limBins2);
   phiResolution_etacut1->Sumw2();   
    for (unsigned int indexH=0;indexH<6;indexH++)  {
      sprintf(nameHist,"phiDistribution_etacut1%i",indexH);
      sprintf(label,"#phi(reco)-#phi(gen) ET(gen) #in #left[%f , %f #right] GeV, 1.3 <| #eta | <3",limBins2[indexH],limBins2[indexH+1]);
      phihist_etacut1[indexH]=new TH1F(nameHist,label,100,-1., 1.);
      phihist_etacut1[indexH]->Sumw2();
      phihist_etacut1[indexH]->GetXaxis()->SetTitle("#phi(reco)-#phi(gen)");
      phihist_etacut1[indexH]->GetYaxis()->SetTitle("#");
     }

   hSimpleResolution_Energy = new TH2F("hSimpleResolution_Energy","E_{T} Reco)/(E_{T} Gen (Event by Event) vs. E_{T} Gen - matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",50,0,125,50,0,3);
//   hSimpleEfficiency_Energy = new TH2F("hSimpleEfficiency_Energy","(# matched jets)/(# All ZSPJPTiC5 jets) vs. E_{T} Gen - matched OneToOne #DeltaR_{m}<=0.2",50,0,5,50,0,125);
///   hMatchedGenNumEv_Ratio = new TH1F("hMatchedGenNumEv_Ratio","(# matched ZSPJPTiC5 Jets)/(# All GenJets) - matched OneToOne #DeltaR_{m}<=0.2, All #eta",100,0,125);
//   hMatchedGenNumEv_Ratio->Sumw2();
 //  hMatchedCaloNumEv_Ratio = new TH1F("hMatchedCaloNumEv_Ratio","(# matched ZSPJPTiC5 Jets)/(# All ZSPJPTiC5 Jets) - matched OneToOne #DeltaR_{m}<=0.2, All #eta",100,0,125);
//   hMatchedCaloNumEv_Ratio->Sumw2();
   hMatchedGenGNumEv_Ratio = new TH1F("hMatchedGenGNumEv_Ratio","(# matched GenJets)/(# All GenJets) - matched OneToOne #DeltaR_{m}<=0.2, All #eta",100,0,125);
   hMatchedGenGNumEv_Ratio->Sumw2();

   hMatchedGenGNumEv_Ratio_dRltpt1 = new TH1F("hMatchedGenGNumEv_Ratio_dRltpt1","(# matched GenJets)/(# All GenJets) - matched OneToOne #DeltaR_{m}<=0.1, All #eta",100,0,125);
   hMatchedGenGNumEv_Ratio_dRltpt1->Sumw2();

   hFakeRatio = new TH1F("hFakeRatio","(# unmatched ZSPCorICone5Jets)/(# All ZSPCorICone5Jets), All #eta",100,0,125);
   hFakeRatio->Sumw2();
   hFakeRatio_etacut0 = new TH1F("hFakeRatio_etacut0","(# unmatched ZSPCorICone5Jets)/(# All ZSPCorICone5Jets), 0<= | #eta | <=1.3",100,0,125);
   hFakeRatio_etacut0->Sumw2();
   hFakeRatio_etacut1 = new TH1F("hFakeRatio_etacut1","(# unmatched ZSPCorICone5Jets)/(# All ZSPCorICone5Jets), 1.3 <| #eta | <3",100,0,125);
   hFakeRatio_etacut1->Sumw2();

   hAllGenJets_et = new TH1F("hAllGenJets_et","All GenJets E_{T}, All #eta",100,0,125);
   hAllGenJets_et->Sumw2();
   hMatchGenJets_dRltpt2_et = new TH1F("hMatchGenJets_dRltpt2_et","GenJets E_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.2, All #eta",100,0,125);
   hMatchGenJets_dRltpt2_et->Sumw2();
   hMatchGenJets_et = new TH1F("hMatchGenJets_et","GenJets E_{T} - which have a OneToOne Match, no #DeltaR_{m} cut, All #eta",100,0,125);
   hMatchGenJets_et->Sumw2();
   hMatchZSPJPTiC5Jets_dRltpt2_et = new TH1F("hMatchZSPJPTiC5Jets_dRltpt2_et","JetPlusTrackZSPCorJetIcone5 E_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.2, All #eta",100,0,125);
   hMatchZSPJPTiC5Jets_dRltpt2_et->Sumw2();
   hMatchZSPJPTiC5Jets_et = new TH1F("hMatchZSPJPTiC5Jets_et","GenJets E_{T} - which have a OneToOne Match, no #DeltaR_{m} cut, All #eta",100,0,125);
   hMatchZSPJPTiC5Jets_et->Sumw2();
   hAllZSPJPTiC5Jets_et = new TH1F("hAllZSPJPTiC5Jets_et","All JetPlusTrackZSPCorJetIcone5 E_{T}, All #eta",100,0,125);
   hAllZSPJPTiC5Jets_et->Sumw2();   

   hUnMatchedZSPJPTiC5Jets_et = new TH1F("hUnMatchedZSPJPTiC5Jets_et","Unmatched JetPlusTrackZSPCorJetIcone5 E_{T}, All #eta",100,0,125);
//   hUnMatchedZSPJPTiC5Jets_dRltpt2_et = new TH1F("hUnMatchedZSPJPTiC5Jets_dRltpt2_et","Unmatched JetPlusTrackZSPCorJetIcone5 E_{T}, outside of #DeltaR_{m}<=0.2 cut, All #eta",100,0,125);
   hUnMatchedZSPJPTiC5Jets_et_etacut0 = new TH1F("hUnMatchedZSPJPTiC5Jets_et_etacut0","Unmatched JetPlusTrackZSPCorJetIcone5 E_{T}, 0<= | #eta | <=1.3",100,0,125);
//   hUnMatchedZSPJPTiC5Jets_dRltpt2_et_etacut0 = new TH1F("hUnMatchedZSPJPTiC5Jets_dRltpt2_et_etacut0","Unmatched JetPlusTrackZSPCorJetIcone5 E_{T}, outside of #DeltaR_{m}<=0.2 cut, 0<= | #eta | <=1.3",100,0,125);
   hUnMatchedZSPJPTiC5Jets_et_etacut1 = new TH1F("hUnMatchedZSPJPTiC5Jets_et_etacut1","Unmatched JetPlusTrackZSPCorJetIcone5 E_{T}, 1.3 <| #eta | <3",100,0,125);
//   hUnMatchedZSPJPTiC5Jets_dRltpt2_et_etacut1 = new TH1F("hUnMatchedZSPJPTiC5Jets_dRltpt2_et_etacut1","Unmatched JetPlusTrackZSPCorJetIcone5 E_{T}, outside of #DeltaR_{m}<=0.2 cut, 1.3 <| #eta | <3",100,0,125);

   hUnMatchedZSPJPTiC5Jets_eta = new TH1F("hUnMatchedZSPJPTiC5Jets_eta","Unmatched JetPlusTrackZSPCorJetIcone5 #eta, All #eta",100,-3,3);
   hUnMatchedZSPJPTiC5Jets_eta_etacut0 = new TH1F("hUnMatchedZSPJPTiC5Jets_eta_etacut0","Unmatched JetPlusTrackZSPCorJetIcone5 #eta, 0<= | #eta | <=1.3",100,-0.5,0.5);
   hUnMatchedZSPJPTiC5Jets_eta_etacut1 = new TH1F("hUnMatchedZSPJPTiC5Jets_eta_etacut1","Unmatched JetPlusTrackZSPCorJetIcone5 #eta, 1.3 <| #eta | <3",100,-2,2);

   hMatchedGenGNumEv_Ratio_etacut0 = new TH1F("hMatchedGenGNumEv_Ratio_etacut0","(# matched GenJets)/(# All GenJets) - matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",100,0,125);
   hMatchedGenGNumEv_Ratio_etacut0->Sumw2();

   hMatchedGenGNumEv_Ratio_dRltpt1_etacut0 = new TH1F("hMatchedGenGNumEv_Ratio_dRltpt1_etacut0","(# matched GenJets)/(# All GenJets) - matched OneToOne #DeltaR_{m}<=0.1, 0<= | #eta | <=1.3",100,0,125);
   hMatchedGenGNumEv_Ratio_dRltpt1_etacut0->Sumw2();

   hAllGenJets_et_etacut0 = new TH1F("hAllGenJets_et_etacut0","All GenJets E_{T}, 0<= | #eta | <=1.3",100,0,125);
   hAllGenJets_et_etacut0->Sumw2();   
   hMatchGenJets_dRltpt2_et_etacut0 = new TH1F("hMatchGenJets_dRltpt2_et_etacut0","GenJets E_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",100,0,125);
   hMatchGenJets_dRltpt2_et_etacut0->Sumw2();
   hMatchGenJets_et_etacut0 = new TH1F("hMatchGenJets_et_etacut0","GenJets E_{T} - which have a OneToOne Match, no #DeltaR_{m} cut, 0<= | #eta | <=1.3",100,0,125);
   hMatchGenJets_et_etacut0->Sumw2();
   hMatchZSPJPTiC5Jets_dRltpt2_et_etacut0 = new TH1F("hMatchZSPJPTiC5Jets_dRltpt2_et_etacut0","JetPlusTrackZSPCorJetIcone5 E_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",100,0,125);
   hMatchZSPJPTiC5Jets_dRltpt2_et_etacut0->Sumw2();
   hMatchZSPJPTiC5Jets_et_etacut0 = new TH1F("hMatchZSPJPTiC5Jets_et_etacut0","GenJets E_{T} - which have a OneToOne Match, no #DeltaR_{m} cut, 0<= | #eta | <=1.3",100,0,125);
   hMatchZSPJPTiC5Jets_et_etacut0->Sumw2();
   hAllZSPJPTiC5Jets_et_etacut0 = new TH1F("hAllZSPJPTiC5Jets_et_etacut0","All JetPlusTrackZSPCorJetIcone5 E_{T}, 0<= | #eta | <=1.3",100,0,125);
   hAllZSPJPTiC5Jets_et_etacut0->Sumw2();   


   hMatchedGenGNumEv_Ratio_etacut1 = new TH1F("hMatchedGenGNumEv_Ratio_etacut1","Et (# matched GenJets)/(# All GenJets) - matched OneToOne #DeltaR_{m}<=0.2, 1.3 <| #eta | <3",100,0,125);
   hMatchedGenGNumEv_Ratio_etacut1->Sumw2();
   hAllGenJets_et_etacut1 = new TH1F("hAllGenJets_et_etacut1","All GenJets E_{T}, 1.3 <| #eta | <3",100,0,125);
   hAllGenJets_et_etacut1->Sumw2();
   hMatchGenJets_dRltpt2_et_etacut1 = new TH1F("hMatchGenJets_dRltpt2_et_etacut1","GenJets E_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.2, 1.3 <| #eta | <3",100,0,125);
   hMatchGenJets_dRltpt2_et_etacut1->Sumw2();
   hMatchGenJets_et_etacut1 = new TH1F("hMatchGenJets_et_etacut1","GenJets E_{T} - which have a OneToOne Match, no #DeltaR_{m} cut, 1.3 <| #eta | <3",100,0,125);
   hMatchGenJets_et_etacut1->Sumw2();
   hAllZSPJPTiC5Jets_et_etacut1 = new TH1F("hAllZSPJPTiC5Jets_et_etacut1","All JetPlusTrackZSPCorJetIcone5 E_{T}, 1.3 <| #eta | <3",100,0,125);
   hAllZSPJPTiC5Jets_et_etacut1->Sumw2();
   hMatchZSPJPTiC5Jets_dRltpt2_et_etacut1 = new TH1F("hMatchZSPJPTiC5Jets_dRltpt2_et_etacut1","JetPlusTrackZSPCorJetIcone5 E_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.2, 1.3 <| #eta | <3",100,0,125);
   hMatchZSPJPTiC5Jets_dRltpt2_et_etacut1->Sumw2();
   hMatchZSPJPTiC5Jets_et_etacut1 = new TH1F("hMatchZSPJPTiC5Jets_et_etacut1","GenJets E_{T} - which have a OneToOne Match, no #DeltaR_{m} cut, 1.3 <| #eta | <3",100,0,125);
   hMatchZSPJPTiC5Jets_et_etacut1->Sumw2(); 

// pt plots
   hAllGenJets_pt = new TH1F("hAllGenJets_pt","All GenJets p_{T}, All #eta",100,0,125);
   hAllGenJets_pt->Sumw2();
   hMatchGenJets_pt = new TH1F("hMatchGenJets_pt","GenJets p_{T} - which have a OneToOne Match, no #DeltaR_{m} cut, All #eta",100,0,125);
   hMatchGenJets_pt->Sumw2(); 
   hAllZSPJPTiC5Jets_pt = new TH1F("hAllZSPJPTiC5Jets_pt","All JetPlusTrackZSPCorJetIcone5 p_{T}, All #eta",100,0,125);
   hAllZSPJPTiC5Jets_pt->Sumw2();
   hMatchZSPJPTiC5Jets_pt = new TH1F("hMatchZSPJPTiC5Jets_pt","GenJets p_{T} - which have a OneToOne Match, no #DeltaR_{m} cut, All #eta",100,0,125);
   hMatchZSPJPTiC5Jets_pt->Sumw2();
//   hMatchedGenGNumEv_pt_Ratio = new TH1F("hMatchedGenGNumEv_pt_Ratio","pt (# matched GenJets)/(# All GenJets) - matched OneToOne #DeltaR_{m}<=0.2, All #eta",100,0,125);
//   hMatchedGenGNumEv_pt_Ratio->Sumw2();
   hMatchGenJets_dRltpt2_pt = new TH1F("hMatchGenJets_dRltpt2_pt","GenJets p_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.2, All #eta",100,0,125);
   hMatchGenJets_dRltpt2_pt->Sumw2();
   hMatchZSPJPTiC5Jets_dRltpt2_pt = new TH1F("hMatchZSPJPTiC5Jets_dRltpt2_pt","JetPlusTrackZSPCorJetIcone5 p_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.2, All #eta",100,0,125);
   hMatchZSPJPTiC5Jets_dRltpt2_pt->Sumw2();

   hAllGenJets_pt_etacut0 = new TH1F("hAllGenJets_pt_etacut0","All GenJets p_{T}, 0<= | #eta | <=1.3",100,0,125);
   hAllGenJets_pt_etacut0->Sumw2();
   hMatchGenJets_pt_etacut0 = new TH1F("hMatchGenJets_pt_etacut0","GenJets p_{T} - which have a OneToOne Match, no #DeltaR_{m} cut, 0<= | #eta | <=1.3",100,0,125);
   hMatchGenJets_pt_etacut0->Sumw2(); 
   hAllZSPJPTiC5Jets_pt_etacut0 = new TH1F("hAllZSPJPTiC5Jets_pt_etacut0","All JetPlusTrackZSPCorJetIcone5 p_{T}, 0<= | #eta | <=1.3",100,0,125);
   hAllZSPJPTiC5Jets_pt_etacut0->Sumw2();
   hMatchZSPJPTiC5Jets_pt_etacut0 = new TH1F("hMatchZSPJPTiC5Jets_pt_etacut0","GenJets p_{T} - which have a OneToOne Match, no #DeltaR_{m} cut, 0<= | #eta | <=1.3",100,0,125);
   hMatchZSPJPTiC5Jets_pt_etacut0->Sumw2();
//   hMatchedGenGNumEv_pt_Ratio_etacut0 = new TH1F("hMatchedGenGNumEv_pt_Ratio_etacut0","pt (# matched GenJets)/(# All GenJets) - matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",100,0,125);
//   hMatchedGenGNumEv_pt_Ratio_etacut0->Sumw2();
   hMatchGenJets_dRltpt2_pt_etacut0 = new TH1F("hMatchGenJets_dRltpt2_pt_etacut0","GenJets p_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",100,0,125);
   hMatchGenJets_dRltpt2_pt_etacut0->Sumw2();
   hMatchZSPJPTiC5Jets_dRltpt2_pt_etacut0 = new TH1F("hMatchZSPJPTiC5Jets_dRltpt2_pt_etacut0","JetPlusTrackZSPCorJetIcone5 p_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",100,0,125);
   hMatchZSPJPTiC5Jets_dRltpt2_pt_etacut0->Sumw2();
   
//    hAllGenJets_pt_etacut1 = new TH1F("hAllGenJets_pt_etacut1","All GenJets p_{T}, 1.3 <| #eta | <3",100,0,125);
//    hAllGenJets_pt_etacut1->Sumw2();
//    hAllZSPJPTiC5Jets_pt_etacut1 = new TH1F("hAllZSPJPTiC5Jets_pt_etacut1","All JetPlusTrackZSPCorJetIcone5 p_{T}, 1.3 <| #eta | <3",100,0,125);
//    hAllZSPJPTiC5Jets_pt_etacut1->Sumw2();

//     ratiopt = new TH1F ("ratiopt", "p^{JetPlusTrackZSPCorJetIcone5}_{T}/p^{GenJets}_{T}, 0<= | #eta | <=1.3",6, 0, 125);
//    ratiopt->Sumw2();
//    sigmaErEm_pt = new TH1F ("sigmaErEm_pt", "sigma(p^{JetPlusTrackZSPCorJetIcone5}_{T}/p^{GenJets}_{T}) matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",7, 0, 125);
//    sigmaErEm_pt->Sumw2();
//    pTresolution = new TH1F ("pTresolution", "p_{T} Resolution matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",7, 0, 125);
//    pTresolution->Sumw2();
//     for (unsigned int indexH=0;indexH<7;indexH++)  {
//       sprintf(nameHist,"pTdistribution%i",indexH);
//       sprintf(label,"pT(reco)/pT(sim) pT(sim) #in #left[%f , %f #right] GeV, 0<= | #eta | <=1.3",limBins2[indexH],limBins2[indexH+1]);
//       pThist[indexH]=new TH1F(nameHist,label,100,0., 2);
//       pThist[indexH]->Sumw2();
//       pThist[indexH]->GetXaxis()->SetTitle("p_{T}^{reco}/p_{t}^{gen}");
//       pThist[indexH]->GetYaxis()->SetTitle("#");
//      }
// 
//    ratiopt_etacut1 = new TH1F ("ratiopt_etacut1", "p^{JetPlusTrackZSPCorJetIcone5}_{T}/p^{GenJets}_{T}, 1.3 <| #eta | <3",7, 0, 125);
//    ratiopt_etacut1->Sumw2();
//    sigmaErEm_pt_etacut1 = new TH1F ("sigmaErEm_pt_etacut1", "sigma(p^{JetPlusTrackZSPCorJetIcone5}_{T}/p^{GenJets}_{T}) matched OneToOne #DeltaR_{m}<=0.2, 1.3 <| #eta | <3",7, 0, 125);
//    sigmaErEm_pt_etacut1->Sumw2();
//    pTresolution_etacut1 = new TH1F ("pTresolution_etacut1", "p_{T} Resolution matched OneToOne #DeltaR_{m}<=0.2, 1.3 <| #eta | <3",7, 0, 125);
//    pTresolution_etacut1->Sumw2();
//     for (unsigned int indexH=0;indexH<7;indexH++)  {
//       sprintf(nameHist,"pTdistribution_etacut1%i",indexH);
//       sprintf(label,"pT(reco)/pT(sim) pT(sim) #in #left[%f , %f #right] GeV, 1.3 <| #eta | <3",limBins2[indexH],limBins2[indexH+1]);
//       pThist_etacut1[indexH]=new TH1F(nameHist,label,100,0., 2);
//       pThist_etacut1[indexH]->Sumw2();
//       pThist_etacut1[indexH]->GetXaxis()->SetTitle("p_{T}^{reco}/p_{t}^{gen}");
//       pThist_etacut1[indexH]->GetYaxis()->SetTitle("#");
//      }
//      
//      ratioptOld = new TH1F ("ratioptOld", "p^{JetPlusTrackZSPCorJetIcone5}_{T}/p^{GenJets}_{T} (different bins)",13, 0, 350);
//    ratioptOld->Sumw2();
//    sigmaErEm_ptOld = new TH1F ("sigmaErEm_ptOld", "sigma(p^{JetPlusTrackZSPCorJetIcone5}_{T}/p^{GenJets}_{T}) matched OneToOne #DeltaR_{m}<=0.2 (diff bins)",13, 0, 350);
//    sigmaErEm_ptOld->Sumw2();
//    pTresolutionOld = new TH1F ("pTresolutionOld", "p_{T} Resolution matched OneToOne #DeltaR_{m}<=0.2 (diff bins)",13, 0, 350);
//    pTresolutionOld->Sumw2();
//     for (unsigned int indexHOld=0;indexHOld<13;indexHOld++)  {
//       sprintf(nameHist,"pTdistributionOld%i",indexHOld);
//       sprintf(label,"pT(reco)/pT(sim) pT(sim) #in #left[%f , %f #right] GeV (diff bins)",limBinsOld2[indexHOld],limBinsOld2[indexHOld+1]);
//       pThistOld[indexHOld]=new TH1F(nameHist,label,100,0., 2);
//       pThistOld[indexHOld]->Sumw2();
//       pThistOld[indexHOld]->GetXaxis()->SetTitle("p_{T}^{reco}/p_{t}^{gen}");
//       pThistOld[indexHOld]->GetYaxis()->SetTitle("#");
//      }    
//   hSimpleResolution_Energy = new TH2F("hSimpleResolution_Energy","E_{T} Reco)/(E_{T} Gen (Event by Event) vs. E_{T} Gen - matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",50,0,125,50,0,3);
//    hMatchedGenGNumEv_pt_Ratio_etacut1 = new TH1F("hMatchedGenGNumEv_pt_Ratio_etacut1","pt (# matched GenJets)/(# All GenJets) - matched OneToOne #DeltaR_{m}<=0.2, 1.3 <| #eta | <3",100,0,125);
//    hMatchedGenGNumEv_pt_Ratio_etacut1->Sumw2();
//    hMatchGenJets_dRltpt2_pt_etacut1 = new TH1F("hMatchGenJets_dRltpt2_pt_etacut1","GenJets p_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.2, 1.3 <| #eta | <3",100,0,125);
//    hMatchGenJets_dRltpt2_pt_etacut1->Sumw2();
//    hMatchGenJets_pt_etacut1 = new TH1F("hMatchGenJets_pt_etacut1","GenJets p_{T} - which have a OneToOne Match, no #DeltaR_{m} cut, 1.3 <| #eta | <3",100,0,125);
//    hMatchGenJets_pt_etacut1->Sumw2();
//    hMatchZSPJPTiC5Jets_dRltpt2_pt_etacut1 = new TH1F("hMatchZSPJPTiC5Jets_dRltpt2_pt_etacut1","JetPlusTrackZSPCorJetIcone5 p_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.2, 1.3 <| #eta | <3",100,0,125);
//    hMatchZSPJPTiC5Jets_dRltpt2_pt_etacut1->Sumw2();
//    hMatchZSPJPTiC5Jets_pt_etacut1 = new TH1F("hMatchZSPJPTiC5Jets_pt_etacut1","GenJets p_{T} - which have a OneToOne Match, no #DeltaR_{m} cut, 1.3 <| #eta | <3",100,0,125);
//    hMatchZSPJPTiC5Jets_pt_etacut1->Sumw2();
   
   hRecoVsGen_et_etacut1 = new TH2F( "RecoVsGen_et_etacut1", "JetPlusTrackZSPCorJetIcone5 E_{T} vs. GenJets E_{T} - matched OneToOne, 1.3 <| #eta | <3", 50, 0, 125, 50, 0, 125);
   hRecoVsGen_pt_etacut1 = new TH2F( "RecoVsGen_pt_etacut1", "JetPlusTrackZSPCorJetIcone5 p_{T} vs. GenJets p_{T} - matched OneToOne, 1.3 <| #eta | <3", 50, 0, 125, 50, 0, 125);
   hRecoVsGen_eta_etacut1 = new TH2F( "RecoVsGen_eta_etacut1", "JetPlusTrackZSPCorJetIcone5 #eta vs. GenJets #eta - matched OneToOne, 1.3 <| #eta | <3", 50, -3, 3, 50, -3, 3 );
   hRecoVsGen_phi_etacut1 = new TH2F( "RecoVsGen_phi_etacut1", "JetPlusTrackZSPCorJetIcone5 #phi vs. GenJets #phi - matched OneToOne, 1.3 <| #eta | <3", 50,  -M_PI, M_PI, 50,  -M_PI, M_PI );
   hRecoVsGen_dRltpt2_et_etacut1 = new TH2F( "RecoVsGen_dRltpt2_et_etacut1", "JetPlusTrackZSPCorJetIcone5 E_{T} vs. GenJets E_{T} - matched OneToOne #DeltaR_{m}<=0.2, 1.3 <| #eta | <3", 50, 0, 125, 50, 0, 125);
   hRecoVsGen_dRltpt2_pt_etacut1 = new TH2F( "RecoVsGen_dRltpt2_pt_etacut1", "JetPlusTrackZSPCorJetIcone5 p_{T} vs. GenJets p_{T} - matched OneToOne #DeltaR_{m}<=0.2, 1.3 <| #eta | <3", 50, 0, 125, 50, 0, 125);
   hRecoVsGen_dRltpt2_eta_etacut1 = new TH2F( "RecoVsGen_dRltpt2_eta_etacut1", "JetPlusTrackZSPCorJetIcone5 #eta vs. GenJets #eta - matched OneToOne #DeltaR_{m}<=0.2, 1.3 <| #eta | <3", 50, -3, 3, 50, -3, 3 );
   hRecoVsGen_dRltpt2_phi_etacut1 = new TH2F( "RecoVsGen_dRltpt2_phi_etacut1", "JetPlusTrackZSPCorJetIcone5 #phi vs. GenJets #phi - matched OneToOne #DeltaR_{m}<=0.2, 1.3 <| #eta | <3", 50,  -M_PI, M_PI, 50,  -M_PI, M_PI );

 
   hRecoVsGen_et_etacut0 = new TH2F( "RecoVsGen_et_etacut0", "JetPlusTrackZSPCorJetIcone5 E_{T} vs. GenJets E_{T} - matched OneToOne, 0<= | #eta | <=1.3", 50, 0, 125, 50, 0, 125);
   hRecoVsGen_pt_etacut0 = new TH2F( "RecoVsGen_pt_etacut0", "JetPlusTrackZSPCorJetIcone5 p_{T} vs. GenJets p_{T} - matched OneToOne, 0<= | #eta | <=1.3", 50, 0, 125, 50, 0, 125);
   hRecoVsGen_eta_etacut0 = new TH2F( "RecoVsGen_eta_etacut0", "JetPlusTrackZSPCorJetIcone5 #eta vs. GenJets #eta - matched OneToOne, 0<= | #eta | <=1.3", 50, -3, 3, 50, -3, 3 );
   hRecoVsGen_phi_etacut0 = new TH2F( "RecoVsGen_phi_etacut0", "JetPlusTrackZSPCorJetIcone5 #phi vs. GenJets #phi - matched OneToOne, 0<= | #eta | <=1.3", 50,  -M_PI, M_PI, 50,  -M_PI, M_PI );
   hRecoVsGen_dRltpt2_et_etacut0 = new TH2F( "RecoVsGen_dRltpt2_et_etacut0", "JetPlusTrackZSPCorJetIcone5 E_{T} vs. GenJets E_{T} - matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3", 50, 0, 125, 50, 0, 125);
   hRecoVsGen_dRltpt2_pt_etacut0 = new TH2F( "RecoVsGen_dRltpt2_pt_etacut0", "JetPlusTrackZSPCorJetIcone5 p_{T} vs. GenJets p_{T} - matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3", 50, 0, 125, 50, 0, 125);
   hRecoVsGen_dRltpt2_eta_etacut0 = new TH2F( "RecoVsGen_dRltpt2_eta_etacut0", "JetPlusTrackZSPCorJetIcone5 #eta vs. GenJets #eta - matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3", 50, -3, 3, 50, -3, 3 );
   hRecoVsGen_dRltpt2_phi_etacut0 = new TH2F( "RecoVsGen_dRltpt2_phi_etacut0", "JetPlusTrackZSPCorJetIcone5 #phi vs. GenJets #phi - matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3", 50,  -M_PI, M_PI, 50,  -M_PI, M_PI );
 
   hRecoVsGen_et = new TH2F( "RecoVsGen_et", "JetPlusTrackZSPCorJetIcone5 E_{T} vs. GenJets E_{T} - matched OneToOne, All #eta", 50, 0, 125, 50, 0, 125);
   hRecoVsGen_pt = new TH2F( "RecoVsGen_pt", "JetPlusTrackZSPCorJetIcone5 p_{T} vs. GenJets p_{T} - matched OneToOne, All #eta", 50, 0, 125, 50, 0, 125);
   hRecoVsGen_eta = new TH2F( "RecoVsGen_eta", "JetPlusTrackZSPCorJetIcone5 #eta vs. GenJets #eta - matched OneToOne, All #eta", 50, -3, 3, 50, -3, 3 );
   hRecoVsGen_phi = new TH2F( "RecoVsGen_phi", "JetPlusTrackZSPCorJetIcone5 #phi vs. GenJets #phi - matched OneToOne, All #eta", 50,  -M_PI, M_PI, 50,  -M_PI, M_PI );
   hRecoVsGen_dRltpt2_et = new TH2F( "RecoVsGen_dRltpt2_et", "JetPlusTrackZSPCorJetIcone5 E_{T} vs. GenJets E_{T} - matched OneToOne #DeltaR_{m}<=0.2, All #eta", 50, 0, 125, 50, 0, 125);
   hRecoVsGen_dRltpt2_pt = new TH2F( "RecoVsGen_dRltpt2_pt", "JetPlusTrackZSPCorJetIcone5 p_{T} vs. GenJets p_{T} - matched OneToOne #DeltaR_{m}<=0.2, All #eta", 50, 0, 125, 50, 0, 125);
   hRecoVsGen_dRltpt2_eta = new TH2F( "RecoVsGen_dRltpt2_eta", "JetPlusTrackZSPCorJetIcone5 #eta vs. GenJets #eta - matched OneToOne #DeltaR_{m}<=0.2, All #eta", 50, -3, 3, 50, -3, 3 );
   hRecoVsGen_dRltpt2_phi = new TH2F( "RecoVsGen_dRltpt2_phi", "JetPlusTrackZSPCorJetIcone5 #phi vs. GenJets #phi - matched OneToOne #DeltaR_{m}<=0.2, All #eta", 50,  -M_PI, M_PI, 50,  -M_PI, M_PI );
// setup deltaR<=0.05 plots:
   hMatchGenJets_dRltpt1_et = new TH1F("hMatchGenJets_dRltpt1_et","GenJets E_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.1, All #eta",100,0,125);
   hMatchGenJets_dRltpt1_et->Sumw2();
   hMatchZSPJPTiC5Jets_dRltpt1_et = new TH1F("hMatchZSPJPTiC5Jets_dRltpt1_et","JetPlusTrackZSPCorJetIcone5 E_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.1, All #eta",100,0,125);
   hMatchZSPJPTiC5Jets_dRltpt1_et->Sumw2();
   hMatchGenJets_dRltpt1_et_etacut0 = new TH1F("hMatchGenJets_dRltpt1_et_etacut0","GenJets E_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.1, 0<= | #eta | <=1.3",100,0,125);
   hMatchGenJets_dRltpt1_et_etacut0->Sumw2();
   hMatchZSPJPTiC5Jets_dRltpt1_et_etacut0 = new TH1F("hMatchZSPJPTiC5Jets_dRltpt1_et_etacut0","JetPlusTrackZSPCorJetIcone5 E_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.1, 0<= | #eta | <=1.3",100,0,125);
   hMatchZSPJPTiC5Jets_dRltpt1_et_etacut0->Sumw2();
   hMatchGenJets_dRltpt1_et_etacut1 = new TH1F("hMatchGenJets_dRltpt1_et_etacut1","GenJets E_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.1, 1.3 <| #eta | <3",100,0,125);
   hMatchGenJets_dRltpt1_et_etacut1->Sumw2();
   hMatchZSPJPTiC5Jets_dRltpt1_et_etacut1 = new TH1F("hMatchZSPJPTiC5Jets_dRltpt1_et_etacut1","JetPlusTrackZSPCorJetIcone5 E_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.1, 1.3 <| #eta | <3",100,0,125);
   hMatchZSPJPTiC5Jets_dRltpt1_et_etacut1->Sumw2();
   hMatchGenJets_dRltpt1_pt = new TH1F("hMatchGenJets_dRltpt1_pt","GenJets p_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.1, All #eta",100,0,125);
   hMatchGenJets_dRltpt1_pt->Sumw2();
   hMatchZSPJPTiC5Jets_dRltpt1_pt = new TH1F("hMatchZSPJPTiC5Jets_dRltpt1_pt","JetPlusTrackZSPCorJetIcone5 p_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.1, All #eta",100,0,125);
   hMatchZSPJPTiC5Jets_dRltpt1_pt->Sumw2();
   hMatchGenJets_dRltpt1_pt_etacut0 = new TH1F("hMatchGenJets_dRltpt1_pt_etacut0","GenJets p_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.1, 0<= | #eta | <=1.3",100,0,125);
   hMatchGenJets_dRltpt1_pt_etacut0->Sumw2();
   hMatchZSPJPTiC5Jets_dRltpt1_pt_etacut0 = new TH1F("hMatchZSPJPTiC5Jets_dRltpt1_pt_etacut0","JetPlusTrackZSPCorJetIcone5 p_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.1, 0<= | #eta | <=1.3",100,0,125);
   hMatchZSPJPTiC5Jets_dRltpt1_pt_etacut0->Sumw2();
   hRecoVsGen_dRltpt1_et_etacut1 = new TH2F( "RecoVsGen_dRltpt1_et_etacut1", "JetPlusTrackZSPCorJetIcone5 E_{T} vs. GenJets E_{T} - matched OneToOne #DeltaR_{m}<=0.1, 1.3 <| #eta | <3", 50, 0, 125, 50, 0, 125);
   hRecoVsGen_dRltpt1_pt_etacut1 = new TH2F( "RecoVsGen_dRltpt1_pt_etacut1", "JetPlusTrackZSPCorJetIcone5 p_{T} vs. GenJets p_{T} - matched OneToOne #DeltaR_{m}<=0.1, 1.3 <| #eta | <3", 50, 0, 125, 50, 0, 125);
   hRecoVsGen_dRltpt1_eta_etacut1 = new TH2F( "RecoVsGen_dRltpt1_eta_etacut1", "JetPlusTrackZSPCorJetIcone5 #eta vs. GenJets #eta - matched OneToOne #DeltaR_{m}<=0.1, 1.3 <| #eta | <3", 50, -3, 3, 50, -3, 3 );
   hRecoVsGen_dRltpt1_phi_etacut1 = new TH2F( "RecoVsGen_dRltpt1_phi_etacut1", "JetPlusTrackZSPCorJetIcone5 #phi vs. GenJets #phi - matched OneToOne #DeltaR_{m}<=0.1, 1.3 <| #eta | <3", 50,  -M_PI, M_PI, 50,  -M_PI, M_PI );
   hRecoVsGen_dRltpt1_et_etacut0 = new TH2F( "RecoVsGen_dRltpt1_et_etacut0", "JetPlusTrackZSPCorJetIcone5 E_{T} vs. GenJets E_{T} - matched OneToOne #DeltaR_{m}<=0.1, 0<= | #eta | <=1.3", 50, 0, 125, 50, 0, 125);
   hRecoVsGen_dRltpt1_pt_etacut0 = new TH2F( "RecoVsGen_dRltpt1_pt_etacut0", "JetPlusTrackZSPCorJetIcone5 p_{T} vs. GenJets p_{T} - matched OneToOne #DeltaR_{m}<=0.1, 0<= | #eta | <=1.3", 50, 0, 125, 50, 0, 125);
   hRecoVsGen_dRltpt1_eta_etacut0 = new TH2F( "RecoVsGen_dRltpt1_eta_etacut0", "JetPlusTrackZSPCorJetIcone5 #eta vs. GenJets #eta - matched OneToOne #DeltaR_{m}<=0.1, 0<= | #eta | <=1.3", 50, -3, 3, 50, -3, 3 );
   hRecoVsGen_dRltpt1_phi_etacut0 = new TH2F( "RecoVsGen_dRltpt1_phi_etacut0", "JetPlusTrackZSPCorJetIcone5 #phi vs. GenJets #phi - matched OneToOne #DeltaR_{m}<=0.1, 0<= | #eta | <=1.3", 50,  -M_PI, M_PI, 50,  -M_PI, M_PI );
   hRecoVsGen_dRltpt1_et = new TH2F( "RecoVsGen_dRltpt1_et", "JetPlusTrackZSPCorJetIcone5 E_{T} vs. GenJets E_{T} - matched OneToOne #DeltaR_{m}<=0.1, All #eta", 50, 0, 125, 50, 0, 125);
   hRecoVsGen_dRltpt1_pt = new TH2F( "RecoVsGen_dRltpt1_pt", "JetPlusTrackZSPCorJetIcone5 p_{T} vs. GenJets p_{T} - matched OneToOne #DeltaR_{m}<=0.1, All #eta", 50, 0, 125, 50, 0, 125);
   hRecoVsGen_dRltpt1_eta = new TH2F( "RecoVsGen_dRltpt1_eta", "JetPlusTrackZSPCorJetIcone5 #eta vs. GenJets #eta - matched OneToOne #DeltaR_{m}<=0.1, All #eta", 50, -3, 3, 50, -3, 3 );
   hRecoVsGen_dRltpt1_phi = new TH2F( "RecoVsGen_dRltpt1_phi", "JetPlusTrackZSPCorJetIcone5 #phi vs. GenJets #phi - matched OneToOne #DeltaR_{m}<=0.1, All #eta", 50,  -M_PI, M_PI, 50,  -M_PI, M_PI );   
//    hRecoVsGen_dRltpt5_et = new TH2F( "RecoVsGen_dRltpt5_et", "JetPlusTrackZSPCorJetIcone5 E_{T} vs. GenJets E_{T} - matched OneToOne #DeltaR_{m}<=0.5, 0<= | #eta | <=1.3", 50, 0, 125, 50, 0, 125);
//    hRecoVsGen_dRltpt5_pt = new TH2F( "RecoVsGen_dRltpt5_pt", "JetPlusTrackZSPCorJetIcone5 p_{T} vs. GenJets p_{T} - matched OneToOne #DeltaR_{m}<=0.5, 0<= | #eta | <=1.3", 50, 0, 125, 50, 0, 125);
//    hRecoVsGen_dRltpt5_eta = new TH2F( "RecoVsGen_dRltpt5_eta", "JetPlusTrackZSPCorJetIcone5 #eta vs. GenJets #eta - matched OneToOne #DeltaR_{m}<=0.5, 0<= | #eta | <=1.3", 50, -3, 3, 50, -3, 3 );
//    hRecoVsGen_dRltpt5_phi = new TH2F( "RecoVsGen_dRltpt5_phi", "JetPlusTrackZSPCorJetIcone5 #phi vs. GenJets #phi - matched OneToOne #DeltaR_{m}<=0.5, 0<= | #eta | <=1.3", 50,  -M_PI, M_PI, 50,  -M_PI, M_PI );
//    hRecoVsGen_dRlt1_et = new TH2F( "RecoVsGen_dRlt1_et", "JetPlusTrackZSPCorJetIcone5 E_{T} vs. GenJets E_{T} - matched OneToOne #DeltaR_{m}<=1.0, 0<= | #eta | <=1.3", 50, 0, 125, 50, 0, 125);
//    hRecoVsGen_dRlt1_pt = new TH2F( "RecoVsGen_dRlt1_pt", "JetPlusTrackZSPCorJetIcone5 p_{T} vs. GenJets p_{T} - matched OneToOne #DeltaR_{m}<=1.0, 0<= | #eta | <=1.3", 50, 0, 125, 50, 0, 125);
//    hRecoVsGen_dRlt1_eta = new TH2F( "RecoVsGen_dRlt1_eta", "JetPlusTrackZSPCorJetIcone5 #eta vs. GenJets #eta - matched OneToOne #DeltaR_{m}<=1.0, 0<= | #eta | <=1.3", 50, -3, 3, 50, -3, 3 );
//    hRecoVsGen_dRlt1_phi = new TH2F( "RecoVsGen_dRlt1_phi", "JetPlusTrackZSPCorJetIcone5 #phi vs. GenJets #phi - matched OneToOne #DeltaR_{m}<=1.0, 0<= | #eta | <=1.3", 50,  -M_PI, M_PI, 50,  -M_PI, M_PI );
   cout<<"[ZSP_Pu_JPTAnalyzer]:: finish beginJob"<<endl;
     return ;
}

// ------------ method called once each job just after ending the event loop  ------------
void 
ZSP_Pu_JPTAnalyzer::endJob() {
 //  hOutputFile->cd() ;
//   Double_t limBins3[]  = {10,20,30,40,50,60,70,80,100.0,120.,150.,200};
   Double_t limBins3[]  = {1,5,10,15,20,30,40};
   Double_t limBinsOld3[] = {20,30,40,50,60,70,80,100,120,150,200,250,300,350};
  cout<<"[ZSP_Pu_JPTAnalyzer::endJob]: just made our limBins"<<endl;
//   hMatchedGenNumEv_Ratio->Divide(hMatchZSPJPTiC5Jets_dRltpt2_et,hAllGenJets_et,1.,1.,"B");
   hMatchedGenGNumEv_Ratio->Divide(hMatchGenJets_dRltpt2_et,hAllGenJets_et,1.,1.,"B");
  cout<<"[ZSP_Pu_JPTAnalyzer::endJob]: just made hMatchedGenGNumEv_Ratio"<<endl;
   hMatchedGenGNumEv_Ratio_etacut0->Divide(hMatchGenJets_dRltpt2_et_etacut0,hAllGenJets_et_etacut0,1.,1.,"B");
  cout<<"[ZSP_Pu_JPTAnalyzer::endJob]:going to make hMatchedGenGNumEv_Ratio_dRltpt1 and hMatchedGenGNumEv_Ratio_dRltpt1_etacut0"<<endl;
   hMatchedGenGNumEv_Ratio_dRltpt1->Divide(hMatchGenJets_dRltpt1_et,hAllGenJets_et,1.,1.,"B");
   hMatchedGenGNumEv_Ratio_dRltpt1_etacut0->Divide(hMatchGenJets_dRltpt1_et_etacut0,hAllGenJets_et_etacut0,1.,1.,"B");
  cout<<"[ZSP_Pu_JPTAnalyzer::endJob]:made hMatchedGenGNumEv_Ratio_dRltpt1 and hMatchedGenGNumEv_Ratio_dRltpt1_etacut0, next fake ratios"<<endl;
   hFakeRatio->Divide(hUnMatchedZSPJPTiC5Jets_et,hAllZSPJPTiC5Jets_et,1.,1.,"B");
   hFakeRatio_etacut0->Divide(hUnMatchedZSPJPTiC5Jets_et_etacut0,hAllZSPJPTiC5Jets_et_etacut0,1.,1.,"B");
   hFakeRatio_etacut1->Divide(hUnMatchedZSPJPTiC5Jets_et_etacut1,hAllZSPJPTiC5Jets_et_etacut1,1.,1.,"B");
   cout<<"[ZSP_Pu_JPTAnalyzer::endJob]: made FakeRatio plots, next lines are commented out"<<endl;
//   hMatchedGenGNumEv_pt_Ratio->Divide(hMatchGenJets_dRltpt2_pt,hAllGenJets_pt_etacut0,1.,1.,"B");
//  cout<<"[ZSP_Pu_JPTAnalyzer::endJob]: just made hMatchedGenGNumEv_pt_Ratio"<<endl;

//   hMatchedCaloNumEv_Ratio->Divide(hMatchZSPJPTiC5Jets_dRltpt2_et,hAllZSPJPTiC5Jets_et,1.,1.,"B");
//   hMatchedGCaloNumEv_Ratio->Divide(hMatchGenJets_dRltpt2_et,hAllZSPJPTiC5Jets_et,1.,1.,"B");

//   hMatchedGenGNumEv_pt_Ratio->Divide(hMatchGenJets_dRltpt2_pt,hAllGenJets_pt,1.,1.,"B");
 // endcap
//   hMatchedGenGNumEv_pt_Ratio_etacut1->Divide(hMatchGenJets_dRltpt2_pt_etacut1,hAllGenJets_pt_etacut1,1.,1.,"B");
  cout<<"[ZSP_Pu_JPTAnalyzer::endJob]: about to make hMatchedGenGNumEv_Ratio_etacut1"<<endl;

   hMatchedGenGNumEv_Ratio_etacut1->Divide(hMatchGenJets_dRltpt2_et_etacut1,hAllGenJets_et_etacut1,1.,1.,"B"); 
   //--> for no apparent reason this line crashes the program!
  cout<<"[ZSP_Pu_JPTAnalyzer::endJob]: did hMatchedGenGNumEv_Ratio_etacut1"<<endl;

  cout<<"[ZSP_Pu_JPTAnalyzer::endJob]: about to loop over 6 bins in outputI"<<endl;
  for(unsigned int outputI=0;outputI<6;outputI++){
    EThist[outputI]->Fit("gaus","RIE","",EThist[outputI]->GetMean()-2*EThist[outputI]->GetRMS(),EThist[outputI]->GetMean()+2*EThist[outputI]->GetRMS());
   cout<<"[ZSP_Pu_JPTAnalyzer::endJob]: just did gaussian fit for EThist for bin: "<<outputI<<endl;
    const TF1* fit =(TF1*) (EThist[outputI]->GetFunction("gaus"));
    Double_t mean = fit->GetParameter(1);
    Double_t meanErr = fit->GetParError(1);
    Double_t sigma = fit->GetParameter(2);
    Double_t sigmaErr = fit->GetParError(2);
    Double_t x=(limBins3[outputI]+limBins3[outputI+1])/2;
    cout<<"x is "<<x<<" outputI: "<<outputI<<" limBins3[outputI] "<<limBins3[outputI]<<" limBins3[outputI+1] "<<limBins3[outputI+1]<<endl;
//     if(outputI==0){
//     sigmaErEm->SetBinContent(ratioE->GetXaxis()->FindBin(x),0);
//     sigmaErEm->SetBinError(ratioE->GetXaxis()->FindBin(x),0);
//     ratioE->SetBinContent(ratioE->GetXaxis()->FindBin(x),-100);
//     ratioE->SetBinError(ratioE->GetXaxis()->FindBin(x),1);    
//     } else {
    sigmaErEm->SetBinContent(ratioE->GetXaxis()->FindBin(x),sigma);
    sigmaErEm->SetBinError(ratioE->GetXaxis()->FindBin(x),sigmaErr);
    ratioE->SetBinContent(ratioE->GetXaxis()->FindBin(x),mean);
    ratioE->SetBinError(ratioE->GetXaxis()->FindBin(x),meanErr);
    cout<<"outputI "<<outputI<<", ratioE->GetXaxis()->FindBin(x) "<<ratioE->GetXaxis()->FindBin(x)<<" mean "<<mean<<" meanErr "<<meanErr<<" sigma "<<sigma<<" sigmaErr "<<sigmaErr<<endl;
//    }
//    EThist[outputI]->Write();
    cout<<"[ZSP_Pu_JPTAnalyzer::endJob]: Just wrote out EThist for bin: "<<outputI<<endl;

    EThist_dRltpt1[outputI]->Fit("gaus","RIE","",EThist_dRltpt1[outputI]->GetMean()-2*EThist_dRltpt1[outputI]->GetRMS(),EThist_dRltpt1[outputI]->GetMean()+2*EThist_dRltpt1[outputI]->GetRMS());
   cout<<"[ZSP_Pu_JPTAnalyzer::endJob]: just did gaussian fit for EThist_dRltpt1 for bin: "<<outputI<<endl;
    const TF1* fit_dRltpt1 =(TF1*) (EThist_dRltpt1[outputI]->GetFunction("gaus"));
    Double_t mean_dRltpt1 = fit_dRltpt1->GetParameter(1);
    Double_t meanErr_dRltpt1 = fit_dRltpt1->GetParError(1);
    Double_t sigma_dRltpt1 = fit_dRltpt1->GetParameter(2);
    Double_t sigmaErr_dRltpt1 = fit_dRltpt1->GetParError(2);
    Double_t x_dRltpt1=(limBins3[outputI]+limBins3[outputI+1])/2;
//         if(outputI==0){
//     sigmaErEm_dRltpt1->SetBinContent(ratioE_dRltpt1->GetXaxis()->FindBin(x_dRltpt1),0);
//     sigmaErEm_dRltpt1->SetBinError(ratioE_dRltpt1->GetXaxis()->FindBin(x_dRltpt1),0);
//     ratioE_dRltpt1->SetBinContent(ratioE_dRltpt1->GetXaxis()->FindBin(x_dRltpt1),-100);
//     ratioE_dRltpt1->SetBinError(ratioE_dRltpt1->GetXaxis()->FindBin(x_dRltpt1),1);
//     } else {
    sigmaErEm_dRltpt1->SetBinContent(ratioE_dRltpt1->GetXaxis()->FindBin(x_dRltpt1),sigma_dRltpt1);
    sigmaErEm_dRltpt1->SetBinError(ratioE_dRltpt1->GetXaxis()->FindBin(x_dRltpt1),sigmaErr_dRltpt1);
    ratioE_dRltpt1->SetBinContent(ratioE_dRltpt1->GetXaxis()->FindBin(x_dRltpt1),mean_dRltpt1);
    ratioE_dRltpt1->SetBinError(ratioE_dRltpt1->GetXaxis()->FindBin(x_dRltpt1),meanErr_dRltpt1);
//    }
    
//    EThist_dRltpt1[outputI]->Write();
    cout<<"[ZSP_Pu_JPTAnalyzer::endJob]: Just wrote out EThist_dRltpt1 for bin: "<<outputI<<endl;

    EThist_etacut0[outputI]->Fit("gaus","RIE","",EThist_etacut0[outputI]->GetMean()-2*EThist_etacut0[outputI]->GetRMS(),EThist_etacut0[outputI]->GetMean()+2*EThist_etacut0[outputI]->GetRMS());
 
    const TF1* fit_etacut0 =(TF1*) (EThist_etacut0[outputI]->GetFunction("gaus"));
    Double_t mean_etacut0 = fit_etacut0->GetParameter(1);
    Double_t mean_etacut0Err = fit_etacut0->GetParError(1);
    Double_t sigma_etacut0 = fit_etacut0->GetParameter(2);
    Double_t sigma_etacut0Err = fit_etacut0->GetParError(2);
    Double_t x_etacut0=(limBins3[outputI]+limBins3[outputI+1])/2;
//             if(outputI==0){
//     sigmaErEm_etacut0->SetBinContent(ratioE_etacut0->GetXaxis()->FindBin(x_etacut0),0);
//     sigmaErEm_etacut0->SetBinError(ratioE_etacut0->GetXaxis()->FindBin(x_etacut0),0);
//     ratioE_etacut0->SetBinContent(ratioE_etacut0->GetXaxis()->FindBin(x_etacut0),-100);
//     ratioE_etacut0->SetBinError(ratioE_etacut0->GetXaxis()->FindBin(x_etacut0),1);
//    } else {
    sigmaErEm_etacut0->SetBinContent(ratioE_etacut0->GetXaxis()->FindBin(x_etacut0),sigma_etacut0);
    sigmaErEm_etacut0->SetBinError(ratioE_etacut0->GetXaxis()->FindBin(x_etacut0),sigma_etacut0Err);
    ratioE_etacut0->SetBinContent(ratioE_etacut0->GetXaxis()->FindBin(x_etacut0),mean_etacut0);
    ratioE_etacut0->SetBinError(ratioE_etacut0->GetXaxis()->FindBin(x_etacut0),mean_etacut0Err);
    cout<<"outputI "<<outputI<<", ratioE_etacut0->GetXaxis()->FindBin(x) "<<ratioE_etacut0->GetXaxis()->FindBin(x_etacut0)<<" mean "<<mean_etacut0<<" mean_etacut0Err "<<mean_etacut0Err<<" sigma_etacut0 "<<sigma_etacut0<<" sigma_etacut0Err "<<sigma_etacut0Err<<endl;
//    }

//    EThist_etacut0[outputI]->Write();
//     
//     pThist[outputI]->Fit("gaus","RIE","",pThist[outputI]->GetMean()-2*pThist[outputI]->GetRMS(),pThist[outputI]->GetMean()+2*pThist[outputI]->GetRMS());
//  
//     const TF1* ptfit =(TF1*) (pThist[outputI]->GetFunction("gaus"));
//     Double_t ptmean = ptfit->GetParameter(1);
//     Double_t ptmeanErr = ptfit->GetParError(1);
//     Double_t ptsigma = ptfit->GetParameter(2);
//     Double_t ptsigmaErr = ptfit->GetParError(2);
//     Double_t ptx=(limBins3[outputI]+limBins3[outputI+1])/2;
//     sigmaErEm_pt->SetBinContent(ratiopt->GetXaxis()->FindBin(ptx),ptsigma);
//     sigmaErEm_pt->SetBinError(ratiopt->GetXaxis()->FindBin(ptx),ptsigmaErr);
//     ratiopt->SetBinContent(ratiopt->GetXaxis()->FindBin(ptx),ptmean);
//     ratiopt->SetBinError(ratiopt->GetXaxis()->FindBin(ptx),ptmeanErr);
//     pThist[outputI]->Write();    

// endcap
    EThist_etacut1[outputI]->Fit("gaus","RIE","",EThist_etacut1[outputI]->GetMean()-2*EThist_etacut1[outputI]->GetRMS(),EThist_etacut1[outputI]->GetMean()+2*EThist_etacut1[outputI]->GetRMS());
 
    const TF1* fit_etacut1 =(TF1*) (EThist_etacut1[outputI]->GetFunction("gaus"));
    Double_t mean_etacut1 = fit_etacut1->GetParameter(1);
    Double_t mean_etacut1Err = fit_etacut1->GetParError(1);
    Double_t sigma_etacut1 = fit_etacut1->GetParameter(2);
    Double_t sigma_etacut1Err = fit_etacut1->GetParError(2);
    Double_t x_etacut1=(limBins3[outputI]+limBins3[outputI+1])/2;
//                 if(outputI==0){
//     sigmaErEm_etacut1->SetBinContent(ratioE_etacut1->GetXaxis()->FindBin(x_etacut1),0);
//     sigmaErEm_etacut1->SetBinError(ratioE_etacut1->GetXaxis()->FindBin(x_etacut1),0);
//     ratioE_etacut1->SetBinContent(ratioE_etacut1->GetXaxis()->FindBin(x_etacut1),-100);
//     ratioE_etacut1->SetBinError(ratioE_etacut1->GetXaxis()->FindBin(x_etacut1),1);
// 	} else {
    sigmaErEm_etacut1->SetBinContent(ratioE_etacut1->GetXaxis()->FindBin(x_etacut1),sigma_etacut1);
    sigmaErEm_etacut1->SetBinError(ratioE_etacut1->GetXaxis()->FindBin(x_etacut1),sigma_etacut1Err);
    ratioE_etacut1->SetBinContent(ratioE_etacut1->GetXaxis()->FindBin(x_etacut1),mean_etacut1);
    ratioE_etacut1->SetBinError(ratioE_etacut1->GetXaxis()->FindBin(x_etacut1),mean_etacut1Err);
//    }

//    EThist_etacut1[outputI]->Write();
    
//     pThist_etacut1[outputI]->Fit("gaus","RIE","",pThist_etacut1[outputI]->GetMean()-2*pThist_etacut1[outputI]->GetRMS(),pThist_etacut1[outputI]->GetMean()+2*pThist_etacut1[outputI]->GetRMS());
//  
//     const TF1* ptfit_etacut1 =(TF1*) (pThist_etacut1[outputI]->GetFunction("gaus"));
//     Double_t ptmean_etacut1 = ptfit_etacut1->GetParameter(1);
//     Double_t ptmean_etacut1Err = ptfit_etacut1->GetParError(1);
//     Double_t ptsigma_etacut1 = ptfit_etacut1->GetParameter(2);
//     Double_t ptsigma_etacut1Err = ptfit_etacut1->GetParError(2);
//     Double_t ptx_etacut1=(limBins3[outputI]+limBins3[outputI+1])/2;
//     sigmaErEm_pt->SetBinContent(ratiopt_etacut1->GetXaxis()->FindBin(ptx_etacut1),ptsigma_etacut1);
//     sigmaErEm_pt->SetBinError(ratiopt_etacut1->GetXaxis()->FindBin(ptx_etacut1),ptsigma_etacut1Err);
//     ratiopt_etacut1->SetBinContent(ratiopt_etacut1->GetXaxis()->FindBin(ptx_etacut1),ptmean_etacut1);
//     ratiopt_etacut1->SetBinError(ratiopt_etacut1->GetXaxis()->FindBin(ptx_etacut1),ptmean_etacut1Err);
//     pThist_etacut1[outputI]->Write(); 
//

// position eta
    etahist[outputI]->Fit("gaus","RIE","",etahist[outputI]->GetMean()-2*etahist[outputI]->GetRMS(),etahist[outputI]->GetMean()+2*etahist[outputI]->GetRMS());
   cout<<"[ZSP_Pu_JPTAnalyzer::endJob]: just did gaussian fit for etahist for bin: "<<outputI<<endl;
    const TF1* fiteta =(TF1*) (etahist[outputI]->GetFunction("gaus"));
    Double_t meaneta = fiteta->GetParameter(1);
    Double_t meanetaErr = fiteta->GetParError(1);
    Double_t actual_sigmaeta = fiteta->GetParameter(2);
    Double_t sigmaetaErr = fiteta->GetParError(2);
    Double_t xeta=(limBins3[outputI]+limBins3[outputI+1])/2;
    cout<<"xeta is "<<xeta<<" outputI: "<<outputI<<" limBins3[outputI] "<<limBins3[outputI]<<" limBins3[outputI+1] "<<limBins3[outputI+1]<<endl;
//     if(outputI==0){
//     sigmaeta->SetBinContent(ratioEta->GetXaxis()->FindBin(xeta),0.);
//     sigmaeta->SetBinError(ratioEta->GetXaxis()->FindBin(xeta),0.);
//     ratioEta->SetBinContent(ratioEta->GetXaxis()->FindBin(xeta),-100.);
//     ratioEta->SetBinError(ratioEta->GetXaxis()->FindBin(xeta),1.);    
//     } else {
    sigmaeta->SetBinContent(ratioEta->GetXaxis()->FindBin(xeta),actual_sigmaeta);
    sigmaeta->SetBinError(ratioEta->GetXaxis()->FindBin(xeta),sigmaetaErr);
    ratioEta->SetBinContent(ratioEta->GetXaxis()->FindBin(xeta),meaneta);
    ratioEta->SetBinError(ratioEta->GetXaxis()->FindBin(xeta),meanetaErr);
    cout<<"outputI "<<outputI<<", ratioEta->GetXaxis()->FindBin(xeta) "<<ratioEta->GetXaxis()->FindBin(xeta)<<" meaneta "<<meaneta<<" meanetaErr "<<meanetaErr<<" sigmaeta "<<actual_sigmaeta<<" sigmaetaErr "<<sigmaetaErr<<endl;
//    }
//    etahist[outputI]->Write();
    cout<<"[ZSP_Pu_JPTAnalyzer::endJob]: Just wrote out etahist for bin: "<<outputI<<endl;
// barrel
    etahist_etacut0[outputI]->Fit("gaus","RIE","",etahist_etacut0[outputI]->GetMean()-2*etahist_etacut0[outputI]->GetRMS(),etahist_etacut0[outputI]->GetMean()+2*etahist_etacut0[outputI]->GetRMS());
 
    const TF1* fiteta_etacut0 =(TF1*) (etahist_etacut0[outputI]->GetFunction("gaus"));
    Double_t meaneta_etacut0 = fiteta_etacut0->GetParameter(1);
    Double_t meaneta_etacut0Err = fiteta_etacut0->GetParError(1);
    Double_t actual_sigmaeta_etacut0 = fiteta_etacut0->GetParameter(2);
    Double_t sigmaeta_etacut0Err = fiteta_etacut0->GetParError(2);
    Double_t xeta_etacut0=(limBins3[outputI]+limBins3[outputI+1])/2;
//             if(outputI==0){
//     sigmaeta_etacut0->SetBinContent(ratioEta_etacut0->GetXaxis()->FindBin(xeta_etacut0),0);
//     sigmaeta_etacut0->SetBinError(ratioEta_etacut0->GetXaxis()->FindBin(xeta_etacut0),0);
//     ratioEta_etacut0->SetBinContent(ratioEta_etacut0->GetXaxis()->FindBin(xeta_etacut0),-100);
//     ratioEta_etacut0->SetBinError(ratioEta_etacut0->GetXaxis()->FindBin(xeta_etacut0),1);
//    } else {
    sigmaeta_etacut0->SetBinContent(ratioEta_etacut0->GetXaxis()->FindBin(xeta_etacut0),actual_sigmaeta_etacut0);
    sigmaeta_etacut0->SetBinError(ratioEta_etacut0->GetXaxis()->FindBin(xeta_etacut0),sigmaeta_etacut0Err);
    ratioEta_etacut0->SetBinContent(ratioEta_etacut0->GetXaxis()->FindBin(xeta_etacut0),meaneta_etacut0);
    ratioEta_etacut0->SetBinError(ratioEta_etacut0->GetXaxis()->FindBin(xeta_etacut0),meaneta_etacut0Err);
    cout<<"outputI "<<outputI<<", ratioEta_etacut0->GetXaxis()->FindBin(xeta) "<<ratioEta_etacut0->GetXaxis()->FindBin(xeta_etacut0)<<" meaneta "<<meaneta_etacut0<<" meaneta_etacut0Err "<<meaneta_etacut0Err<<" sigmaeta_etacut0 "<<actual_sigmaeta_etacut0<<" sigmaeta_etacut0Err "<<sigmaeta_etacut0Err<<endl;
//    }

 //   etahist_etacut0[outputI]->Write();
    
// endcap
    etahist_etacut1[outputI]->Fit("gaus","RIE","",etahist_etacut1[outputI]->GetMean()-2*etahist_etacut1[outputI]->GetRMS(),etahist_etacut1[outputI]->GetMean()+2*etahist_etacut1[outputI]->GetRMS());
 
    const TF1* fiteta_etacut1 =(TF1*) (etahist_etacut1[outputI]->GetFunction("gaus"));
    Double_t meaneta_etacut1 = fiteta_etacut1->GetParameter(1);
    Double_t meaneta_etacut1Err = fiteta_etacut1->GetParError(1);
    Double_t actual_sigmaeta_etacut1 = fiteta_etacut1->GetParameter(2);
    Double_t sigmaeta_etacut1Err = fiteta_etacut1->GetParError(2);
    Double_t xeta_etacut1=(limBins3[outputI]+limBins3[outputI+1])/2;
//                 if(outputI==0){
//     sigmaeta_etacut1->SetBinContent(ratioEta_etacut1->GetXaxis()->FindBin(xeta_etacut1),0);
//     sigmaeta_etacut1->SetBinError(ratioEta_etacut1->GetXaxis()->FindBin(xeta_etacut1),0);
//     ratioEta_etacut1->SetBinContent(ratioEta_etacut1->GetXaxis()->FindBin(xeta_etacut1),-100);
//     ratioEta_etacut1->SetBinError(ratioEta_etacut1->GetXaxis()->FindBin(xeta_etacut1),1);
// 	} else {
    sigmaeta_etacut1->SetBinContent(ratioEta_etacut1->GetXaxis()->FindBin(xeta_etacut1),actual_sigmaeta_etacut1);
    sigmaeta_etacut1->SetBinError(ratioEta_etacut1->GetXaxis()->FindBin(xeta_etacut1),sigmaeta_etacut1Err);
    ratioEta_etacut1->SetBinContent(ratioEta_etacut1->GetXaxis()->FindBin(xeta_etacut1),meaneta_etacut1);
    ratioEta_etacut1->SetBinError(ratioEta_etacut1->GetXaxis()->FindBin(xeta_etacut1),meaneta_etacut1Err);
//    }

 //   etahist_etacut1[outputI]->Write();

// position phi
    phihist[outputI]->Fit("gaus","RIE","",phihist[outputI]->GetMean()-2*phihist[outputI]->GetRMS(),phihist[outputI]->GetMean()+2*phihist[outputI]->GetRMS());
   cout<<"[ZSP_Pu_JPTAnalyzer::endJob]: just did gaussian fit for phihist for bin: "<<outputI<<endl;
    const TF1* fitphi =(TF1*) (phihist[outputI]->GetFunction("gaus"));
    Double_t meanphi = fitphi->GetParameter(1);
    Double_t meanphiErr = fitphi->GetParError(1);
    Double_t actual_sigmaphi = fitphi->GetParameter(2);
    Double_t sigmaphiErr = fitphi->GetParError(2);
    Double_t xphi=(limBins3[outputI]+limBins3[outputI+1])/2;
    cout<<"xphi is "<<xphi<<" outputI: "<<outputI<<" limBins3[outputI] "<<limBins3[outputI]<<" limBins3[outputI+1] "<<limBins3[outputI+1]<<endl;
//     if(outputI==0){
//     sigmaphi->SetBinContent(ratioPhi->GetXaxis()->FindBin(xphi),0);
//     sigmaphi->SetBinError(ratioPhi->GetXaxis()->FindBin(xphi),0);
//     ratioPhi->SetBinContent(ratioPhi->GetXaxis()->FindBin(xphi),-100);
//     ratioPhi->SetBinError(ratioPhi->GetXaxis()->FindBin(xphi),1);    
//     } else {
    sigmaphi->SetBinContent(ratioPhi->GetXaxis()->FindBin(xphi),actual_sigmaphi);
    sigmaphi->SetBinError(ratioPhi->GetXaxis()->FindBin(xphi),sigmaphiErr);
    ratioPhi->SetBinContent(ratioPhi->GetXaxis()->FindBin(xphi),meanphi);
    ratioPhi->SetBinError(ratioPhi->GetXaxis()->FindBin(xphi),meanphiErr);
    cout<<"outputI "<<outputI<<", ratioPhi->GetXaxis()->FindBin(xphi) "<<ratioPhi->GetXaxis()->FindBin(xphi)<<" meanphi "<<meanphi<<" meanphiErr "<<meanphiErr<<" sigmaphi "<<actual_sigmaphi<<" sigmaphiErr "<<sigmaphiErr<<endl;
//    }
 //   phihist[outputI]->Write();
    cout<<"[ZSP_Pu_JPTAnalyzer::endJob]: Just wrote out phihist for bin: "<<outputI<<endl;
// barrel
    phihist_etacut0[outputI]->Fit("gaus","RIE","",phihist_etacut0[outputI]->GetMean()-2*phihist_etacut0[outputI]->GetRMS(),phihist_etacut0[outputI]->GetMean()+2*phihist_etacut0[outputI]->GetRMS());
 
    const TF1* fitphi_etacut0 =(TF1*) (phihist_etacut0[outputI]->GetFunction("gaus"));
    Double_t meanphi_etacut0 = fitphi_etacut0->GetParameter(1);
    Double_t meanphi_etacut0Err = fitphi_etacut0->GetParError(1);
    Double_t actual_sigmaphi_etacut0 = fitphi_etacut0->GetParameter(2);
    Double_t sigmaphi_etacut0Err = fitphi_etacut0->GetParError(2);
    Double_t xphi_etacut0=(limBins3[outputI]+limBins3[outputI+1])/2;
//             if(outputI==0){
//     sigmaphi_etacut0->SetBinContent(ratioPhi_etacut0->GetXaxis()->FindBin(xphi_etacut0),0);
//     sigmaphi_etacut0->SetBinError(ratioPhi_etacut0->GetXaxis()->FindBin(xphi_etacut0),0);
//     ratioPhi_etacut0->SetBinContent(ratioPhi_etacut0->GetXaxis()->FindBin(xphi_etacut0),-100);
//     ratioPhi_etacut0->SetBinError(ratioPhi_etacut0->GetXaxis()->FindBin(xphi_etacut0),1);
//    } else {
    sigmaphi_etacut0->SetBinContent(ratioPhi_etacut0->GetXaxis()->FindBin(xphi_etacut0),actual_sigmaphi_etacut0);
    sigmaphi_etacut0->SetBinError(ratioPhi_etacut0->GetXaxis()->FindBin(xphi_etacut0),sigmaphi_etacut0Err);
    ratioPhi_etacut0->SetBinContent(ratioPhi_etacut0->GetXaxis()->FindBin(xphi_etacut0),meanphi_etacut0);
    ratioPhi_etacut0->SetBinError(ratioPhi_etacut0->GetXaxis()->FindBin(xphi_etacut0),meanphi_etacut0Err);
    cout<<"outputI "<<outputI<<", ratioPhi_etacut0->GetXaxis()->FindBin(xphi) "<<ratioPhi_etacut0->GetXaxis()->FindBin(xphi_etacut0)<<" meanphi "<<meanphi_etacut0<<" meanphi_etacut0Err "<<meanphi_etacut0Err<<" sigmaphi_etacut0 "<<actual_sigmaphi_etacut0<<" sigmaphi_etacut0Err "<<sigmaphi_etacut0Err<<endl;
//    }

 //   phihist_etacut0[outputI]->Write();
    
// endcap
    phihist_etacut1[outputI]->Fit("gaus","RIE","",phihist_etacut1[outputI]->GetMean()-2*phihist_etacut1[outputI]->GetRMS(),phihist_etacut1[outputI]->GetMean()+2*phihist_etacut1[outputI]->GetRMS());
 
    const TF1* fitphi_etacut1 =(TF1*) (phihist_etacut1[outputI]->GetFunction("gaus"));
    Double_t meanphi_etacut1 = fitphi_etacut1->GetParameter(1);
    Double_t meanphi_etacut1Err = fitphi_etacut1->GetParError(1);
    Double_t actual_sigmaphi_etacut1 = fitphi_etacut1->GetParameter(2);
    Double_t sigmaphi_etacut1Err = fitphi_etacut1->GetParError(2);
    Double_t xphi_etacut1=(limBins3[outputI]+limBins3[outputI+1])/2;
//                 if(outputI==0){
//     sigmaphi_etacut1->SetBinContent(ratioPhi_etacut1->GetXaxis()->FindBin(xphi_etacut1),0);
//     sigmaphi_etacut1->SetBinError(ratioPhi_etacut1->GetXaxis()->FindBin(xphi_etacut1),0);
//     ratioPhi_etacut1->SetBinContent(ratioPhi_etacut1->GetXaxis()->FindBin(xphi_etacut1),-100);
//     ratioPhi_etacut1->SetBinError(ratioPhi_etacut1->GetXaxis()->FindBin(xphi_etacut1),1);
// 	} else {
    sigmaphi_etacut1->SetBinContent(ratioPhi_etacut1->GetXaxis()->FindBin(xphi_etacut1),actual_sigmaphi_etacut1);
    sigmaphi_etacut1->SetBinError(ratioPhi_etacut1->GetXaxis()->FindBin(xphi_etacut1),sigmaphi_etacut1Err);
    ratioPhi_etacut1->SetBinContent(ratioPhi_etacut1->GetXaxis()->FindBin(xphi_etacut1),meanphi_etacut1);
    ratioPhi_etacut1->SetBinError(ratioPhi_etacut1->GetXaxis()->FindBin(xphi_etacut1),meanphi_etacut1Err);
//    }

//    phihist_etacut1[outputI]->Write();    
  }
  
  for(unsigned int outputIOld=0;outputIOld<13;outputIOld++){
    EThistOld[outputIOld]->Fit("gaus","RIE","",EThistOld[outputIOld]->GetMean()-2*EThistOld[outputIOld]->GetRMS(),EThistOld[outputIOld]->GetMean()+2*EThistOld[outputIOld]->GetRMS());
 
    const TF1* fitOld =(TF1*) (EThistOld[outputIOld]->GetFunction("gaus"));
    Double_t meanOld = fitOld->GetParameter(1);
    Double_t meanErrOld = fitOld->GetParError(1);
    Double_t sigmaOld = fitOld->GetParameter(2);
    Double_t sigmaErrOld = fitOld->GetParError(2);
    Double_t xOld=(limBinsOld3[outputIOld]+limBinsOld3[outputIOld+1])/2;
    sigmaErEmOld->SetBinContent(ratioEOld->GetXaxis()->FindBin(xOld),sigmaOld);
    sigmaErEmOld->SetBinError(ratioEOld->GetXaxis()->FindBin(xOld),sigmaErrOld);
    ratioEOld->SetBinContent(ratioEOld->GetXaxis()->FindBin(xOld),meanOld);
    ratioEOld->SetBinError(ratioEOld->GetXaxis()->FindBin(xOld),meanErrOld);
//    EThistOld[outputIOld]->Write(); 
    
    EThist_dRltpt1Old[outputIOld]->Fit("gaus","RIE","",EThist_dRltpt1Old[outputIOld]->GetMean()-2*EThist_dRltpt1Old[outputIOld]->GetRMS(),EThist_dRltpt1Old[outputIOld]->GetMean()+2*EThist_dRltpt1Old[outputIOld]->GetRMS());
 
    const TF1* fit_dRltpt1Old =(TF1*) (EThist_dRltpt1Old[outputIOld]->GetFunction("gaus"));
    Double_t meanOld_dRltpt1 = fit_dRltpt1Old->GetParameter(1);
    Double_t meanErrOld_dRltpt1 = fit_dRltpt1Old->GetParError(1);
    Double_t sigmaOld_dRltpt1 = fit_dRltpt1Old->GetParameter(2);
    Double_t sigmaErrOld_dRltpt1 = fit_dRltpt1Old->GetParError(2);
    Double_t x_dRltpt1Old=(limBinsOld3[outputIOld]+limBinsOld3[outputIOld+1])/2;
    sigmaErEm_dRltpt1Old->SetBinContent(ratioE_dRltpt1Old->GetXaxis()->FindBin(x_dRltpt1Old),sigmaOld_dRltpt1);
    sigmaErEm_dRltpt1Old->SetBinError(ratioE_dRltpt1Old->GetXaxis()->FindBin(x_dRltpt1Old),sigmaErrOld_dRltpt1);
    ratioE_dRltpt1Old->SetBinContent(ratioE_dRltpt1Old->GetXaxis()->FindBin(x_dRltpt1Old),meanOld_dRltpt1);
    ratioE_dRltpt1Old->SetBinError(ratioE_dRltpt1Old->GetXaxis()->FindBin(x_dRltpt1Old),meanErrOld_dRltpt1);
//    EThist_dRltpt1Old[outputIOld]->Write();  

// barrel:
    EThist_etacut0Old[outputIOld]->Fit("gaus","RIE","",EThist_etacut0Old[outputIOld]->GetMean()-2*EThist_etacut0Old[outputIOld]->GetRMS(),EThist_etacut0Old[outputIOld]->GetMean()+2*EThist_etacut0Old[outputIOld]->GetRMS());
 
    const TF1* fit_etacut0Old =(TF1*) (EThist_etacut0Old[outputIOld]->GetFunction("gaus"));
    Double_t mean_etacut0Old = fit_etacut0Old->GetParameter(1);
    Double_t mean_etacut0OldErr = fit_etacut0Old->GetParError(1);
    Double_t sigma_etacut0Old = fit_etacut0Old->GetParameter(2);
    Double_t sigma_etacut0OldErr = fit_etacut0Old->GetParError(2);
    Double_t x_etacut0Old=(limBinsOld3[outputIOld]+limBinsOld3[outputIOld+1])/2;
    sigmaErEm_etacut0Old->SetBinContent(ratioE_etacut0Old->GetXaxis()->FindBin(x_etacut0Old),sigma_etacut0Old);
    sigmaErEm_etacut0Old->SetBinError(ratioE_etacut0Old->GetXaxis()->FindBin(x_etacut0Old),sigma_etacut0OldErr);
    ratioE_etacut0Old->SetBinContent(ratioE_etacut0Old->GetXaxis()->FindBin(x_etacut0Old),mean_etacut0Old);
    ratioE_etacut0Old->SetBinError(ratioE_etacut0Old->GetXaxis()->FindBin(x_etacut0Old),mean_etacut0OldErr);
//    EThist_etacut0Old[outputIOld]->Write();
// endcap:
    EThist_etacut1Old[outputIOld]->Fit("gaus","RIE","",EThist_etacut1Old[outputIOld]->GetMean()-2*EThist_etacut1Old[outputIOld]->GetRMS(),EThist_etacut1Old[outputIOld]->GetMean()+2*EThist_etacut1Old[outputIOld]->GetRMS());
 
    const TF1* fit_etacut1Old =(TF1*) (EThist_etacut1Old[outputIOld]->GetFunction("gaus"));
    Double_t mean_etacut1Old = fit_etacut1Old->GetParameter(1);
    Double_t mean_etacut1OldErr = fit_etacut1Old->GetParError(1);
    Double_t sigma_etacut1Old = fit_etacut1Old->GetParameter(2);
    Double_t sigma_etacut1OldErr = fit_etacut1Old->GetParError(2);
    Double_t x_etacut1Old=(limBinsOld3[outputIOld]+limBinsOld3[outputIOld+1])/2;
    sigmaErEm_etacut1Old->SetBinContent(ratioE_etacut1Old->GetXaxis()->FindBin(x_etacut1Old),sigma_etacut1Old);
    sigmaErEm_etacut1Old->SetBinError(ratioE_etacut1Old->GetXaxis()->FindBin(x_etacut1Old),sigma_etacut1OldErr);
    ratioE_etacut1Old->SetBinContent(ratioE_etacut1Old->GetXaxis()->FindBin(x_etacut1Old),mean_etacut1Old);
    ratioE_etacut1Old->SetBinError(ratioE_etacut1Old->GetXaxis()->FindBin(x_etacut1Old),mean_etacut1OldErr);
//    EThist_etacut1Old[outputIOld]->Write();
//
//     pThistOld[outputIOld]->Fit("gaus","RIE","",pThistOld[outputIOld]->GetMean()-2*pThistOld[outputIOld]->GetRMS(),pThistOld[outputIOld]->GetMean()+2*pThistOld[outputIOld]->GetRMS());
//  
//     const TF1* ptfitOld =(TF1*) (pThistOld[outputIOld]->GetFunction("gaus"));
//     Double_t ptmeanOld = ptfitOld->GetParameter(1);
//     Double_t ptmeanErrOld = ptfitOld->GetParError(1);
//     Double_t ptsigmaOld = ptfitOld->GetParameter(2);
//     Double_t ptsigmaErrOld = ptfitOld->GetParError(2);
//     Double_t ptxOld=(limBinsOld3[outputIOld]+limBinsOld3[outputIOld+1])/2;
//     sigmaErEm_ptOld->SetBinContent(ratioptOld->GetXaxis()->FindBin(ptxOld),ptsigmaOld);
//     sigmaErEm_ptOld->SetBinError(ratioptOld->GetXaxis()->FindBin(ptxOld),ptsigmaErrOld);
//     ratioptOld->SetBinContent(ratioptOld->GetXaxis()->FindBin(ptxOld),ptmeanOld);
//     ratioptOld->SetBinError(ratioptOld->GetXaxis()->FindBin(ptxOld),ptmeanErrOld);
//     pThistOld[outputIOld]->Write();     
  }  
//  ETresolution = (TH1F*)sigmaErEm->Clone();
  ETresolution->Divide(sigmaErEm,ratioE,1.,1.,"B");
//  ETresolution->SetName("ETresolution");
//  ETresolution->SetTitle("E_{T} resolution matched OneToOne #DeltaR_{m}<=0.2");
//  ETresolution->GetXaxis()->SetRangeUser(0,125);
  ETresolution->GetXaxis()->SetTitle("E^{MC}_{T}/ #left[GeV#right]");
  ETresolution->GetYaxis()->SetTitle("#sigma#left(E^{reco}_{T}/E^{MC}_{T}#right)_{fit}/<E^{reco}_{T}/E^{MC}_{T}>_{fit}");
//  ETresolution->Write();

  ratioE->GetXaxis()->SetTitle("E^{MC}_{T} #left[GeV#right]");
  ratioE->GetYaxis()->SetTitle("E^{reco}_{T}/E^{MC}_{T}");

//  ratioE->Write();   


  ETresolution_dRltpt1->Divide(sigmaErEm_dRltpt1,ratioE_dRltpt1,1.,1.,"B");
  ETresolution_dRltpt1->GetXaxis()->SetTitle("E^{MC}_{T}/ #left[GeV#right]");
  ETresolution_dRltpt1->GetYaxis()->SetTitle("#sigma#left(E^{reco}_{T}/E^{MC}_{T}#right)_{fit}/<E^{reco}_{T}/E^{MC}_{T}>_{fit}");
//  ETresolution_dRltpt1->Write();

  ratioE_dRltpt1->GetXaxis()->SetTitle("E^{MC}_{T} #left[GeV#right]");
  ratioE_dRltpt1->GetYaxis()->SetTitle("E^{reco}_{T}/E^{MC}_{T}");

//  ratioE_dRltpt1->Write(); 
 
//   pTresolution->Divide(sigmaErEm_pt,ratiopt,1.,1.,"B");
//   pTresolution->GetXaxis()->SetTitle("p^{MC}_{T}/ #left[GeV#right]");
//   pTresolution->GetYaxis()->SetTitle("#sigma#left(p^{reco}_{T}/p^{MC}_{T}#right)_{fit}/<p^{reco}_{T}/p^{MC}_{T}>_{fit}");
//   pTresolution->Write();
// 
//   ratiopt->GetXaxis()->SetTitle("p^{MC}_{T} #left[GeV#right]");
//   ratiopt->GetYaxis()->SetTitle("p^{reco}_{T}/p^{MC}_{T}");
// 
//   ratiopt->Write(); 

  ETresolutionOld->Divide(sigmaErEmOld,ratioEOld,1.,1.,"B");
  ETresolutionOld->GetXaxis()->SetTitle("E^{MC}_{T}/ #left[GeV#right]");
  ETresolutionOld->GetYaxis()->SetTitle("#sigma#left(E^{reco}_{T}/E^{MC}_{T}#right)_{fit}/<E^{reco}_{T}/E^{MC}_{T}>_{fit}");
//  ETresolutionOld->Write();

  ratioEOld->GetXaxis()->SetTitle("E^{MC}_{T} #left[GeV#right]");
  ratioEOld->GetYaxis()->SetTitle("E^{reco}_{T}/E^{MC}_{T}");

//  ratioEOld->Write(); 

  ETresolution_dRltpt1Old->Divide(sigmaErEm_dRltpt1Old,ratioE_dRltpt1Old,1.,1.,"B");
  ETresolution_dRltpt1Old->GetXaxis()->SetTitle("E^{MC}_{T}/ #left[GeV#right]");
  ETresolution_dRltpt1Old->GetYaxis()->SetTitle("#sigma#left(E^{reco}_{T}/E^{MC}_{T}#right)_{fit}/<E^{reco}_{T}/E^{MC}_{T}>_{fit}");
//  ETresolution_dRltpt1Old->Write();

  ratioE_dRltpt1Old->GetXaxis()->SetTitle("E^{MC}_{T} #left[GeV#right]");
  ratioE_dRltpt1Old->GetYaxis()->SetTitle("E^{reco}_{T}/E^{MC}_{T}");
//  ratioE_dRltpt1Old->Write();
// barrel:  
  ETresolution_etacut0Old->Divide(sigmaErEm_etacut0Old,ratioE_etacut0Old,1.,1.,"B");
  ETresolution_etacut0Old->GetXaxis()->SetTitle("E^{MC}_{T}/ #left[GeV#right]");
  ETresolution_etacut0Old->GetYaxis()->SetTitle("#sigma#left(E^{reco}_{T}/E^{MC}_{T}#right)_{fit}/<E^{reco}_{T}/E^{MC}_{T}>_{fit}");
//  ETresolution_etacut0Old->Write();

  ratioE_etacut0Old->GetXaxis()->SetTitle("E^{MC}_{T} #left[GeV#right]");
  ratioE_etacut0Old->GetYaxis()->SetTitle("E^{reco}_{T}/E^{MC}_{T}");

//  ratioE_etacut0Old->Write(); 

  ETresolution_etacut0->Divide(sigmaErEm_etacut0,ratioE_etacut0,1.,1.,"B");
  ETresolution_etacut0->GetXaxis()->SetTitle("E^{MC}_{T}/ #left[GeV#right]");
  ETresolution_etacut0->GetYaxis()->SetTitle("#sigma#left(E^{reco}_{T}/E^{MC}_{T}#right)_{fit}/<E^{reco}_{T}/E^{MC}_{T}>_{fit}");
//  ETresolution_etacut0->Write();

  ratioE_etacut0->GetXaxis()->SetTitle("E^{MC}_{T} #left[GeV#right]");
  ratioE_etacut0->GetYaxis()->SetTitle("E^{reco}_{T}/E^{MC}_{T}");

//  ratioE_etacut0->Write(); 
// endcap:
  ETresolution_etacut1Old->Divide(sigmaErEm_etacut1Old,ratioE_etacut1Old,1.,1.,"B");
  ETresolution_etacut1Old->GetXaxis()->SetTitle("E^{MC}_{T}/ #left[GeV#right]");
  ETresolution_etacut1Old->GetYaxis()->SetTitle("#sigma#left(E^{reco}_{T}/E^{MC}_{T}#right)_{fit}/<E^{reco}_{T}/E^{MC}_{T}>_{fit}");
//  ETresolution_etacut1Old->Write();

  ratioE_etacut1Old->GetXaxis()->SetTitle("E^{MC}_{T} #left[GeV#right]");
  ratioE_etacut1Old->GetYaxis()->SetTitle("E^{reco}_{T}/E^{MC}_{T}");

//  ratioE_etacut1Old->Write(); 

  ETresolution_etacut1->Divide(sigmaErEm_etacut1,ratioE_etacut1,1.,1.,"B");
  ETresolution_etacut1->GetXaxis()->SetTitle("E^{MC}_{T}/ #left[GeV#right]");
  ETresolution_etacut1->GetYaxis()->SetTitle("#sigma#left(E^{reco}_{T}/E^{MC}_{T}#right)_{fit}/<E^{reco}_{T}/E^{MC}_{T}>_{fit}");
//  ETresolution_etacut1->Write();

  ratioE_etacut1->GetXaxis()->SetTitle("E^{MC}_{T} #left[GeV#right]");
  ratioE_etacut1->GetYaxis()->SetTitle("E^{reco}_{T}/E^{MC}_{T}");

//  ratioE_etacut1->Write(); 

// position resolution bits:
  etaResolution->Divide(sigmaeta,ratioEta,1.,1.,"B");
//  etaResolution->SetName("etaResolution");
//  etaResolution->SetTitle("#eta resolution matched OneToOne #DeltaR_{m}<=0.2");
//  etaResolution->GetXaxis()->SetRangeUser(0,125);
  etaResolution->GetXaxis()->SetTitle("E^{MC}_{T}/ #left[GeV#right]");
  etaResolution->GetYaxis()->SetTitle("#sigma#left(|#eta(reco)|-|#eta(gen)|#right)_{fit}/<|#eta(reco)|-|#eta(gen)|>_{fit}");
//  etaResolution->Write();

  ratioEta->GetXaxis()->SetTitle("E^{MC}_{T} #left[GeV#right]");
  ratioEta->GetYaxis()->SetTitle("<|#eta(reco)|-|#eta(gen)|>");

//  ratioEta->Write();   

  etaResolution_etacut0->Divide(sigmaeta_etacut0,ratioEta_etacut0,1.,1.,"B");
  etaResolution_etacut0->GetXaxis()->SetTitle("E^{MC}_{T}/ #left[GeV#right]");
  etaResolution_etacut0->GetYaxis()->SetTitle("#sigma#left(|#eta(reco)|-|#eta(gen)|#right)_{fit}/<|#eta(reco)|-|#eta(gen)|>_{fit}");
//  etaResolution_etacut0->Write();

  ratioEta_etacut0->GetXaxis()->SetTitle("E^{MC}_{T} #left[GeV#right]");
  ratioEta_etacut0->GetYaxis()->SetTitle("|#eta(reco)|-|#eta(gen)|");

//  ratioEta_etacut0->Write(); 
  
  etaResolution_etacut1->Divide(sigmaeta_etacut1,ratioEta_etacut1,1.,1.,"B");
  etaResolution_etacut1->GetXaxis()->SetTitle("E^{MC}_{T}/ #left[GeV#right]");
  etaResolution_etacut1->GetYaxis()->SetTitle("#sigma#left(|#eta(reco)|-|#eta(gen)|#right)_{fit}/<|#eta(reco)|-|#eta(gen)|>_{fit}");
//  etaResolution_etacut1->Write();

  ratioEta_etacut1->GetXaxis()->SetTitle("E^{MC}_{T} #left[GeV#right]");
  ratioEta_etacut1->GetYaxis()->SetTitle("|#eta(reco)|-|#eta(gen)|");

//  ratioEta_etacut1->Write(); 
  
  phiResolution->Divide(sigmaphi,ratioPhi,1.,1.,"B");
//  phiResolution->SetName("phiResolution");
//  phiResolution->SetTitle("#phi resolution matched OneToOne #DeltaR_{m}<=0.2");
//  phiResolution->GetXaxis()->SetRangeUser(0,125);
  phiResolution->GetXaxis()->SetTitle("E^{MC}_{T}/ #left[GeV#right]");
  phiResolution->GetYaxis()->SetTitle("#sigma#left(#phi(reco)-#phi(gen)#right)_{fit}/<#phi(reco)-#phi(gen)>_{fit}");
//  phiResolution->Write();

  ratioPhi->GetXaxis()->SetTitle("E^{MC}_{T} #left[GeV#right]");
  ratioPhi->GetYaxis()->SetTitle("#phi(reco)-#phi(gen)");

//  ratioPhi->Write();   

  phiResolution_etacut0->Divide(sigmaphi_etacut0,ratioPhi_etacut0,1.,1.,"B");
  phiResolution_etacut0->GetXaxis()->SetTitle("E^{MC}_{T}/ #left[GeV#right]");
  phiResolution_etacut0->GetYaxis()->SetTitle("#sigma#left(#phi(reco)-#phi(gen)#right)_{fit}/<#phi(reco)-#phi(gen)>_{fit}");
  phiResolution_etacut0->Write();

  ratioPhi_etacut0->GetXaxis()->SetTitle("E^{MC}_{T} #left[GeV#right]");
  ratioPhi_etacut0->GetYaxis()->SetTitle("#phi(reco)-#phi(gen)");

//  ratioPhi_etacut0->Write(); 
  
  phiResolution_etacut1->Divide(sigmaphi_etacut1,ratioPhi_etacut1,1.,1.,"B");
  phiResolution_etacut1->GetXaxis()->SetTitle("E^{MC}_{T}/ #left[GeV#right]");
  phiResolution_etacut1->GetYaxis()->SetTitle("#sigma#left(#phi(reco)-#phi(gen)#right)_{fit}/<#phi(reco)-#phi(gen)>_{fit}");
//  phiResolution_etacut1->Write();

  ratioPhi_etacut1->GetXaxis()->SetTitle("E^{MC}_{T} #left[GeV#right]");
  ratioPhi_etacut1->GetYaxis()->SetTitle("#phi(reco)-#phi(gen)");

//  ratioPhi_etacut1->Write();   
//   pTresolution_etacut1->Divide(sigmaErEm_pt_etacut1,ratiopt_etacut1,1.,1.,"B");
//   pTresolution_etacut1->GetXaxis()->SetTitle("p^{MC}_{T}/ #left[GeV#right]");
//   pTresolution_etacut1->GetYaxis()->SetTitle("#sigma#left(p^{reco}_{T}/p^{MC}_{T}#right)_{fit}/<p^{reco}_{T}/p^{MC}_{T}>_{fit}");
//   pTresolution_etacut1->Write();
// 
//   ratiopt_etacut1->GetXaxis()->SetTitle("p^{MC}_{T} #left[GeV#right]");
//   ratiopt_etacut1->GetYaxis()->SetTitle("p^{reco}_{T}/p^{MC}_{T}");
// 
//   ratiopt_etacut1->Write();   
//
//   pTresolutionOld->Divide(sigmaErEm_ptOld,ratioptOld,1.,1.,"B");
//   pTresolutionOld->GetXaxis()->SetTitle("p^{MC}_{T}/ #left[GeV#right]");
//   pTresolutionOld->GetYaxis()->SetTitle("#sigma#left(p^{reco}_{T}/p^{MC}_{T}#right)_{fit}/<p^{reco}_{T}/p^{MC}_{T}>_{fit}");
//   pTresolutionOld->Write();
// 
//   ratioptOld->GetXaxis()->SetTitle("p^{MC}_{T} #left[GeV#right]");
//   ratioptOld->GetYaxis()->SetTitle("p^{reco}_{T}/p^{MC}_{T}");
// 
//   ratioptOld->Write();  
//   hOutputFile->Write() ;
cout<<"[ZSP_Pu_JPTAnalyzer]:: start doing Write histos as part of destruction"<<endl;
		 hTotalLenght->Write();
		hdeltaR->Write();
		hdeltaR_etacut0->Write();
		hdeltaR_etacut1->Write();
		ratioE->Write();
		sigmaErEm->Write();
		ETresolution->Write();
		EThist [6]->Write();
 
		ratioEOld->Write();
		sigmaErEmOld->Write();
		ETresolutionOld->Write();
		EThistOld [13]->Write();

		ratioE_dRltpt1->Write();
		sigmaErEm_dRltpt1->Write();
		ETresolution_dRltpt1->Write();
		EThist_dRltpt1 [6]->Write();
		ratioE_dRltpt1Old->Write();
		sigmaErEm_dRltpt1Old->Write();
		ETresolution_dRltpt1Old->Write();
		EThist_dRltpt1Old [13]->Write();
cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote basic histos as part of destruction"<<endl;

 // barrel specific
		ratioE_etacut0->Write();
		sigmaErEm_etacut0->Write();
		ETresolution_etacut0->Write();
		EThist_etacut0 [6]->Write();
 
		ratioE_etacut0Old->Write();
		sigmaErEm_etacut0Old->Write();
		ETresolution_etacut0Old->Write();
		EThist_etacut0Old [13]->Write();
//    
		ratioE_etacut1->Write();
		sigmaErEm_etacut1->Write();
		ETresolution_etacut1->Write();
		EThist_etacut1 [6]->Write();
 
		ratioE_etacut1Old->Write();
		sigmaErEm_etacut1Old->Write();
		ETresolution_etacut1Old->Write();
		EThist_etacut1Old [13]->Write();
//
cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote barrel+endcap histos as part of destruction"<<endl;

// position resolution:
		ratioEta->Write();
//				cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote		ratioEta->Write();histos as part of destruction"<<endl;
		sigmaeta->Write();
//		cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote		sigmaeta->Write();histos as part of destruction"<<endl;
		etaResolution->Write();
//		cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote		etaResolution->Write();histos as part of destruction"<<endl;
		etahist [6]->Write();
//		cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote		etahist [6]->Write();histos as part of destruction"<<endl;
		ratioPhi->Write();
//		cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote		ratioPhi->Write();histos as part of destruction"<<endl;
		sigmaphi->Write();
//		cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote		sigmaphi->Write();histos as part of destruction"<<endl;
		phiResolution->Write();
//		cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote		phiResolution->Write();histos as part of destruction"<<endl;
		phihist [6]->Write();
//		cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote		phihist [6]->Write();histos as part of destruction"<<endl;
		ratioEta_etacut0->Write();
//		cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote		ratioEta_etacut0->Write();histos as part of destruction"<<endl;
		sigmaeta_etacut0->Write();
//		cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote		sigmaeta_etacut0->Write();histos as part of destruction"<<endl;
		etaResolution_etacut0->Write();
//		cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote		etaResolution_etacut0->Write();histos as part of destruction"<<endl;
		etahist_etacut0 [6]->Write();    
//		cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote		etahist_etacut0 [6]->Write();    histos as part of destruction"<<endl;
		ratioPhi_etacut0->Write();
//		cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote		ratioPhi_etacut0->Write();histos as part of destruction"<<endl;
		sigmaphi_etacut0->Write();
//		cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote		sigmaphi_etacut0->Write();histos as part of destruction"<<endl;
		phiResolution_etacut0->Write();
//		cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote		phiResolution_etacut0->Write();histos as part of destruction"<<endl;		
		phihist_etacut0[6]->Write();
//		cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote		phihist_etacut0[6]->Write();histos as part of destruction"<<endl;
		ratioEta_etacut1->Write();
//		cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote		ratioEta_etacut1->Write();histos as part of destruction"<<endl;
		sigmaeta_etacut1->Write();
//		cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote		sigmaeta_etacut1->Write();histos as part of destruction"<<endl;
		etaResolution_etacut1->Write();
//		cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote		etaResolution_etacut1->Write();histos as part of destruction"<<endl;
		etahist_etacut1 [6]->Write();      
//		cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote		etahist_etacut1 [6]->Write();      histos as part of destruction"<<endl;
		ratioPhi_etacut1->Write();
//		cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote		ratioPhi_etacut1->Write();histos as part of destruction"<<endl;
		sigmaphi_etacut1->Write();
//		cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote		sigmaphi_etacut1->Write();histos as part of destruction"<<endl;
		phiResolution_etacut1->Write();
//		cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote		phiResolution_etacut1->Write();histos as part of destruction"<<endl;
//	    phihist_etacut1[6]->Write();   
//		cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote		phihist_etacut1[6]->Write();   histos as part of destruction"<<endl;
		cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote position histos as part of destruction"<<endl;

// 		ratiopt->Write();
// 		sigmaErEm_pt->Write();
// 		pTresolution->Write();
// 		pThist [6]->Write();   
//  
// 		ratiopt_etacut1->Write();
// 		sigmaErEm_pt_etacut1->Write();
// 		pTresolution_etacut1->Write();
// 		pThist_etacut1 [6]->Write();   
//     
// 		ratioptOld->Write();
// 		sigmaErEm_ptOld->Write();
// 		pTresolutionOld->Write();
//		pThistOld[6]->Write();     
		hSimpleResolution_Energy->Write(); // (E_{T} Reco)/(E_{T} Gen) vs. E_{T} Gen  (what Korea group did) 
//    TH2F* 		hSimpleEfficiency_Energy->Write(); // (#matched jets)/(# reco jets) vs. E_{T} Gen  (what Korea group did)
		hAllGenJets_et->Write();
//		hAllGenJets_pt_etacut0->Write();
		hAllGenJets_et_etacut0->Write();

		hAllZSPJPTiC5Jets_et->Write();
		hMatchGenJets_dRltpt2_et->Write();
 		hMatchGenJets_dRltpt1_et->Write();   
		hMatchGenJets_et->Write();
		hMatchZSPJPTiC5Jets_dRltpt2_et->Write();
		hMatchZSPJPTiC5Jets_dRltpt1_et->Write();
		hMatchZSPJPTiC5Jets_et->Write();  
 
		hAllZSPJPTiC5Jets_et_etacut0->Write();
		hMatchGenJets_dRltpt2_et_etacut0->Write();
		hMatchGenJets_dRltpt1_et_etacut0->Write();    
		hMatchGenJets_et_etacut0->Write();
		hMatchZSPJPTiC5Jets_dRltpt2_et_etacut0->Write();
		hMatchZSPJPTiC5Jets_dRltpt1_et_etacut0->Write();    
		hMatchZSPJPTiC5Jets_et_etacut0->Write();  
 		cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote match histos as part of destruction"<<endl;
 
		hAllGenJets_pt->Write();
		hAllZSPJPTiC5Jets_pt->Write();
		hMatchGenJets_dRltpt2_pt->Write();
		hMatchGenJets_dRltpt1_pt->Write();    
		hMatchGenJets_pt->Write();
		hMatchZSPJPTiC5Jets_dRltpt2_pt->Write();
		hMatchZSPJPTiC5Jets_dRltpt1_pt->Write();
		hMatchZSPJPTiC5Jets_pt->Write();  
		hUnMatchedZSPJPTiC5Jets_et->Write();
		hUnMatchedZSPJPTiC5Jets_et_etacut0->Write();
		hUnMatchedZSPJPTiC5Jets_et_etacut1->Write();
        
		hUnMatchedZSPJPTiC5Jets_eta->Write();
		hUnMatchedZSPJPTiC5Jets_eta_etacut0->Write();
		hUnMatchedZSPJPTiC5Jets_eta_etacut1->Write();
//		hUnMatchedZSPJPTiC5Jets_dRltpt2_et->Write();
//		hUnMatchedZSPJPTiC5Jets_dRltpt2_et_etacut0->Write();
//		hUnMatchedZSPJPTiC5Jets_dRltpt2_et_etacut1->Write();
//		hMatchedGenGNumEv_pt_Ratio->Write();

		hMatchGenJets_pt_etacut0->Write();
		hAllZSPJPTiC5Jets_pt_etacut0->Write();
		hAllGenJets_pt_etacut0->Write();
		hMatchGenJets_dRltpt2_pt_etacut0->Write();
		hMatchZSPJPTiC5Jets_dRltpt2_pt_etacut0->Write();
		hMatchGenJets_dRltpt1_pt_etacut0->Write();
		hMatchZSPJPTiC5Jets_dRltpt1_pt_etacut0->Write();
		hMatchZSPJPTiC5Jets_pt_etacut0->Write();     
//		hMatchedGenGNumEv_pt_Ratio_etacut0->Write();

 // endcap plots
		hAllGenJets_et_etacut1->Write();
		hAllZSPJPTiC5Jets_et_etacut1->Write();
		hMatchGenJets_dRltpt2_et_etacut1->Write();
		hMatchGenJets_dRltpt1_et_etacut1->Write();
		hMatchGenJets_et_etacut1->Write();
		hMatchZSPJPTiC5Jets_dRltpt2_et_etacut1->Write();
		hMatchZSPJPTiC5Jets_dRltpt1_et_etacut1->Write();
		hMatchZSPJPTiC5Jets_et_etacut1->Write();     
//		hMatchedGenGNumEv_et_Ratio_etacut1->Write();  
    
// 		hAllGenJets_pt_etacut1->Write();
// 		hAllZSPJPTiC5Jets_pt_etacut1->Write();
// 		hMatchGenJets_dRltpt2_pt_etacut1->Write();
// 		hMatchGenJets_pt_etacut1->Write();
// 		hMatchZSPJPTiC5Jets_dRltpt2_pt_etacut1->Write();
// 		hMatchZSPJPTiC5Jets_pt_etacut1->Write();     
// 		hMatchedGenGNumEv_pt_Ratio_etacut1->Write();   
  		cout<<"[ZSP_Pu_JPTAnalyzer]:: Wrote more match histos as part of destruction"<<endl;
   
		hRecoVsGen_pt_etacut1->Write();
		hRecoVsGen_et_etacut1->Write();
		hRecoVsGen_eta_etacut1->Write();
		hRecoVsGen_phi_etacut1->Write();
		hRecoVsGen_dRltpt2_pt_etacut1->Write();
		hRecoVsGen_dRltpt2_et_etacut1->Write();
		hRecoVsGen_dRltpt2_eta_etacut1->Write();
		hRecoVsGen_dRltpt2_phi_etacut1->Write();    
		hRecoVsGen_dRltpt1_pt_etacut1->Write();
		hRecoVsGen_dRltpt1_et_etacut1->Write();
		hRecoVsGen_dRltpt1_eta_etacut1->Write();
		hRecoVsGen_dRltpt1_phi_etacut1->Write();  
		hMatchedGenGNumEv_Ratio_etacut1->Write(); // (# matched GenJets)/(# All GenJets) --> this is the one
    
// end endcap plots

		hRecoVsGen_pt_etacut0->Write();
		hRecoVsGen_et_etacut0->Write();
		hRecoVsGen_eta_etacut0->Write();
		hRecoVsGen_phi_etacut0->Write();
		hRecoVsGen_dRltpt2_pt_etacut0->Write();
		hRecoVsGen_dRltpt2_et_etacut0->Write();
		hRecoVsGen_dRltpt2_eta_etacut0->Write();
		hRecoVsGen_dRltpt2_phi_etacut0->Write();
		hRecoVsGen_dRltpt1_pt_etacut0->Write();
		hRecoVsGen_dRltpt1_et_etacut0->Write();
		hRecoVsGen_dRltpt1_eta_etacut0->Write();
		hRecoVsGen_dRltpt1_phi_etacut0->Write();    
//		hMatchedGenNumEv_Ratio->Write(); // (# matched ZSPJPTiC5 Jets)/(# All GenJets)
		hMatchedGenGNumEv_Ratio->Write(); // (# matched GenJets)/(# All GenJets) --> this is the one
		hMatchedGenGNumEv_Ratio_etacut0->Write(); // (# matched GenJets)/(# All GenJets) --> this is the one
		hMatchedGenGNumEv_Ratio_dRltpt1->Write(); // (# matched GenJets)/(# All GenJets) --> this is the one
		hMatchedGenGNumEv_Ratio_dRltpt1_etacut0->Write(); // (# matched GenJets)/(# All GenJets) --> this is the one
		hFakeRatio->Write();
		hFakeRatio_etacut0->Write();
		hFakeRatio_etacut1->Write();
//		hFakeRatio_dRltpt2->Write();
//		hFakeRatio_dRltpt2_etacut0->Write();
//		hFakeRatio_dRltpt2_etacut1->Write();
    
//		hMatchedCaloNumEv_Ratio->Write(); // (# matched ZSPJPTiC5 Jets)/(# All ZSPJPTiC5 Jets)
//		hMatchedGCaloNumEv_Ratio->Write(); // (# matched GenJets)/(# All ZSPJPTiC5 Jets)
		hRecoVsGen_pt->Write();
		hRecoVsGen_et->Write();
		hRecoVsGen_eta->Write();
		hRecoVsGen_phi->Write();
		hRecoVsGen_dRltpt2_pt->Write();
		hRecoVsGen_dRltpt2_et->Write();
		hRecoVsGen_dRltpt2_eta->Write();
		hRecoVsGen_dRltpt2_phi->Write();    
		hRecoVsGen_dRltpt1_pt->Write();
		hRecoVsGen_dRltpt1_et->Write();
		hRecoVsGen_dRltpt1_eta->Write();
		hRecoVsGen_dRltpt1_phi->Write();  
cout<<"[ZSP_Pu_JPTAnalyzer]:: finish doing Write histos as part of destruction"<<endl;
   hOutputFile->Write() ;
 cout<<"[ZSP_Pu_JPTAnalyzer]:: going to close File part of destruction"<<endl;

//   hOutputFile->Close() ; 
 cout<<"[ZSP_Pu_JPTAnalyzer]:: end destruction"<<endl;
cout<<"[ZSP_Pu_JPTAnalyzer]:: finished endJob"<<endl;
   return ;
}

//define this as a plug-in
DEFINE_FWK_MODULE(ZSP_Pu_JPTAnalyzer);
