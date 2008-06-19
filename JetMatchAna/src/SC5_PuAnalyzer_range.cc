// -*- C++ -*-
//
// Package:    SC5_PuAnalyzer_range
// Class:      SC5_PuAnalyzer_range
// 
/**\class SC5_PuAnalyzer_range SC5_PuAnalyzer_range.cc MTonjes/JetMatchAna/src/SC5_PuAnalyzer_range.cc

 Description: <one line class summary>

 Implementation:
     calculates histograms mainly based on pT
     original form based on dEnterria's UserCode
*/
//
// Original Author:  "Marguerite Tonjes"
//         Created:  Wed Feb 27 18:12:33 CST 2008
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

class SC5_PuAnalyzer_range : public edm::EDAnalyzer {
   public:
      explicit SC5_PuAnalyzer_range(const edm::ParameterSet&);
      ~SC5_PuAnalyzer_range();
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
    TH1F* 	    ratiopT;
    TH1F*       sigmapTrpTm;
    TH1F*		pTresolution;
    TH1F* 		pThist [6];
 
     TH1F* 	    ratiopTOld;
    TH1F*       sigmapTrpTmOld;
    TH1F*		pTresolutionOld;
    TH1F* 		pThistOld [13];

    TH1F* 	    ratiopT_dRltpt1;
    TH1F*       sigmapTrpTm_dRltpt1;
    TH1F*		pTresolution_dRltpt1;
    TH1F* 		pThist_dRltpt1 [6];
    TH1F* 	    ratiopT_dRltpt1Old;
    TH1F*       sigmapTrpTm_dRltpt1Old;
    TH1F*		pTresolution_dRltpt1Old;
    TH1F* 		pThist_dRltpt1Old [13];

 // barrel specific
     TH1F* 	    ratiopT_etacut0;
    TH1F*       sigmapTrpTm_etacut0;
    TH1F*		pTresolution_etacut0;
    TH1F* 		pThist_etacut0 [6];
 
     TH1F* 	    ratiopT_etacut0Old;
    TH1F*       sigmapTrpTm_etacut0Old;
    TH1F*		pTresolution_etacut0Old;
    TH1F* 		pThist_etacut0Old [13];
//    
     TH1F* 	    ratiopT_etacut1;
    TH1F*       sigmapTrpTm_etacut1;
    TH1F*		pTresolution_etacut1;
    TH1F* 		pThist_etacut1 [6];
 
     TH1F* 	    ratiopT_etacut1Old;
    TH1F*       sigmapTrpTm_etacut1Old;
    TH1F*		pTresolution_etacut1Old;
    TH1F* 		pThist_etacut1Old [13];
//

// position resolution:
    TH1F*       ratioeta;
    TH1F*       sigmaeta;
    TH1F* 		etahist [6];
    TH1F*       ratioPhi;
    TH1F*       sigmaphi;
    TH1F* 		phihist [6];
    TH1F*       ratioeta_etacut0;
    TH1F*       sigmaeta_etacut0;
    TH1F* 		etahist_etacut0 [6];    
    TH1F*       ratioPhi_etacut0;
    TH1F*       sigmaphi_etacut0;
    TH1F* 		phihist_etacut0[6];
    TH1F*       ratioeta_etacut1;
    TH1F*       sigmaeta_etacut1;
    TH1F* 		etahist_etacut1 [6];      
    TH1F*       ratioPhi_etacut1;
    TH1F*       sigmaphi_etacut1;
    TH1F* 		phihist_etacut1[6];   
//      TH1F* 	    ratiopt;
//     TH1F*       sigmapTrpTm_pt;
//     TH1F*		pTresolution;
//     TH1F* 		pThist [6];   
//  
//      TH1F* 	    ratiopt_etacut1;
//     TH1F*       sigmapTrpTm_pt_etacut1;
//     TH1F*		pTresolution_etacut1;
//     TH1F* 		pThist_etacut1 [6];   
//     
//      TH1F* 	    ratioptOld;
//     TH1F*       sigmapTrpTm_ptOld;
//     TH1F*		pTresolutionOld;
//    TH1F* 		pThistOld[6];     
    char nameHist [50];
    char label [500];  
   Double_t limBins[6];
   //= {10,20,30,40,50,60,70,80,100.0,120.,150.,200};   
   Double_t limBinsOld[13];
   // = {20,30,40,50,60,70,80,90,100,125,150,175,200,250};
   
    TH2F*		hSimpleResolution_pt; // (p_{T} Reco)/(p_{T} Gen) vs. p_{T} Gen  (what Korea group did) 
//    TH2F* 		hSimpleEfficiency_Energy; // (#matched jets)/(# reco jets) vs. p_{T} Gen  (what Korea group did)
    TH1F*       hAllGenJets_et;
//    TH1F*       hAllGenJets_pt_etacut0;
    TH1F*       hAllGenJets_et_etacut0;

    TH1F*		hAllSC5Jets_et;
    TH1F*		hMatchGenJets_dRltpt2_et;
     TH1F*		hMatchGenJets_dRltpt1_et;   
    TH1F*		hMatchGenJets_et;
    TH1F*		hMatchSC5Jets_dRltpt2_et;
    TH1F*		hMatchSC5Jets_dRltpt1_et;
    TH1F*		hMatchSC5Jets_et;  
 
    TH1F*		hAllSC5Jets_et_etacut0;
    TH1F*		hMatchGenJets_dRltpt2_et_etacut0;
    TH1F*		hMatchGenJets_dRltpt1_et_etacut0;    
    TH1F*		hMatchGenJets_et_etacut0;
    TH1F*		hMatchSC5Jets_dRltpt2_et_etacut0;
    TH1F*		hMatchSC5Jets_dRltpt1_et_etacut0;    
    TH1F*		hMatchSC5Jets_et_etacut0;  
  
    TH1F*       hAllGenJets_pt;
    TH1F*		hAllSC5Jets_pt;
    TH1F*		hMatchGenJets_dRltpt2_pt;
    TH1F*		hMatchGenJets_dRltpt1_pt;    
    TH1F*		hMatchGenJets_pt;
    TH1F*		hMatchSC5Jets_dRltpt2_pt;
    TH1F*		hMatchSC5Jets_dRltpt1_pt;
    TH1F*		hMatchSC5Jets_pt;  
    TH1F*       hUnMatchedSC5Jets_pt;
    TH1F*       hUnMatchedSC5Jets_pt_etacut0;
    TH1F*       hUnMatchedSC5Jets_pt_etacut1;
    
    Int_t    SC5Jets_unmatchstat[100];
    Double_t    SC5Jets_eta_unmatch[100];
    Double_t    SC5Jets_pt_unmatch[100];
    
    TH1F*       hUnMatchedSC5Jets_eta;
    TH1F*       hUnMatchedSC5Jets_eta_etacut0;
    TH1F*       hUnMatchedSC5Jets_eta_etacut1;
//    TH1F*       hUnMatchedSC5Jets_dRltpt2_et;
//    TH1F*       hUnMatchedSC5Jets_dRltpt2_et_etacut0;
//    TH1F*       hUnMatchedSC5Jets_dRltpt2_et_etacut1;
//    TH1F* 		hMatchedGenGNumEv_pt_Ratio;

    TH1F*		hMatchGenJets_pt_etacut0;
    TH1F*		hAllSC5Jets_pt_etacut0;
    TH1F*       hAllGenJets_pt_etacut0;
    TH1F*		hMatchGenJets_dRltpt2_pt_etacut0;
    TH1F*		hMatchSC5Jets_dRltpt2_pt_etacut0;
    TH1F*		hMatchGenJets_dRltpt1_pt_etacut0;
    TH1F*		hMatchSC5Jets_dRltpt1_pt_etacut0;
    TH1F*		hMatchSC5Jets_pt_etacut0;     
//    TH1F* 		hMatchedGenGNumEv_pt_Ratio_etacut0;

 // endcap plots
    TH1F*       hAllGenJets_et_etacut1;
    TH1F*		hAllSC5Jets_et_etacut1;
    TH1F*		hMatchGenJets_dRltpt2_et_etacut1;
    TH1F*		hMatchGenJets_dRltpt1_et_etacut1;
    TH1F*		hMatchGenJets_et_etacut1;
    TH1F*		hMatchSC5Jets_dRltpt2_et_etacut1;
    TH1F*		hMatchSC5Jets_dRltpt1_et_etacut1;
    TH1F*		hMatchSC5Jets_et_etacut1;     
//    TH1F* 		hMatchedGenGNumEv_et_Ratio_etacut1;  
    
     TH1F*       hAllGenJets_pt_etacut1;
     TH1F*		hAllSC5Jets_pt_etacut1;
     TH1F*		hMatchGenJets_dRltpt2_pt_etacut1;
     TH1F*		hMatchGenJets_pt_etacut1;
     TH1F*		hMatchSC5Jets_dRltpt2_pt_etacut1;
     TH1F*		hMatchSC5Jets_pt_etacut1;     
     TH1F* 		hMatchedGenGNumEv_pt_Ratio_etacut1;   
    
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
//    TH1F* 		hMatchedGenNumEv_Ratio; // (# matched SC5 Jets)/(# All GenJets)
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
    
//    TH1F*		hMatchedCaloNumEv_Ratio; // (# matched SC5 Jets)/(# All SC5 Jets)
//    TH1F*		hMatchedGCaloNumEv_Ratio; // (# matched GenJets)/(# All SC5 Jets)
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
SC5_PuAnalyzer_range::SC5_PuAnalyzer_range(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
  source_          = iConfig.getParameter<InputTag> ("src");
  matched_         = iConfig.getParameter<InputTag> ("matched");
  matchedjetsOne_  = iConfig.getParameter<InputTag> ("matchMapOne");
  fOutputFileName_ = iConfig.getUntrackedParameter<string>("HistOutFile",std::string("testMatch.root"));

}

int SC5_PuAnalyzer_range::determineIndex(Double_t* limBins, Double_t data, unsigned int nbreBins)
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

SC5_PuAnalyzer_range::~SC5_PuAnalyzer_range()
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
SC5_PuAnalyzer_range::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
//   Double_t limBins4[]  = {10,20,30,40,50,60,70,80,100.0,120.,150.,200};
//   Double_t limBins4[]  = {1,5,10,15,20,30,40};
	Double_t limBins4[]  = {10,25,50,75,100,150,200};
	// 10,25,50,100,150,200,250
   Double_t limBinsOld4[] = {20,30,40,50,60,70,80,90,100,125,150,175,200,250};

  cout << "[SC5_PuAnalyzer_range] analysing event " << iEvent.id() << endl;
  HaveMatchMap = kTRUE;
  try {
    iEvent.getByLabel (source_,source);
    iEvent.getByLabel (matched_,matched);
  } catch(std::exception& ce) {
    cerr << "[SC5_PuAnalyzer_range] caught std::exception " << ce.what() << endl;
    return;   
  }
  try {
     iEvent.getByLabel (matchedjetsOne_ , matchedjetsOne );
  } catch(std::exception& ce) {
    cerr << "[SC5_PuAnalyzer_range] caught std::exception " << ce.what() << endl;
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
        cout<<"[SC5_PuAnalyzer_range::analyze, have an endcap jet, will fill hAllGenJets_pt_etacut1 with pT: "<<ijet->pt()<<endl;
        hAllGenJets_pt_etacut1->Fill(ijet->pt());
//        hAllGenJets_pt_etacut1->Fill(ijet->pt());   
     }
//     cout<<"   GenJetEt: "<<GenJetEt<<endl; 
   }
  double RecoEtaAll = 990.; 
        for(int iset=0; iset<100; iset++){
          SC5Jets_unmatchstat[iset]=5;  // 0 = matched, 1 = unmatched, 5 = error
          SC5Jets_eta_unmatch[iset]=9999.;  // eta of those recojets corresponding to index above
          SC5Jets_pt_unmatch[iset]=0.;   // et of those recojets corresponding to index above  
        }
          Int_t totalSC5Jets=0;
   for (CandidateCollection::const_iterator imjet=matched->begin(); imjet!=matched->end(); imjet++) {
 
       RecoEtaAll = imjet->eta();
      if(!HaveMatchMap){
        hUnMatchedSC5Jets_pt->Fill(imjet->pt());
        hUnMatchedSC5Jets_eta->Fill(imjet->eta());
          if (fabs(RecoEtaAll)<=1.3){
            hUnMatchedSC5Jets_pt_etacut0->Fill(imjet->pt());         
            hUnMatchedSC5Jets_eta_etacut0->Fill(imjet->eta());         
          } else if (fabs(RecoEtaAll) >1.3 && fabs(RecoEtaAll)<3){
            hUnMatchedSC5Jets_pt_etacut1->Fill(imjet->pt());                   
            hUnMatchedSC5Jets_eta_etacut1->Fill(imjet->eta());                   
          }
      } else {
          SC5Jets_unmatchstat[totalSC5Jets]=1;
          SC5Jets_eta_unmatch[totalSC5Jets]=imjet->eta();  // eta of those recojets corresponding to index above
          SC5Jets_pt_unmatch[totalSC5Jets]=imjet->pt();   // et of those recojets corresponding to index above
          totalSC5Jets++;
    }
      hAllSC5Jets_et->Fill(imjet->et());     
      hAllSC5Jets_pt->Fill(imjet->pt());
      if (fabs(RecoEtaAll)<=1.3){
        hAllSC5Jets_et_etacut0->Fill(imjet->et());
        hAllSC5Jets_pt_etacut0->Fill(imjet->pt());
     } else if (fabs(RecoEtaAll) >1.3 && fabs(RecoEtaAll)<3){
        cout<<"[SC5_PuAnalyzer_range::analyze, have an endcap jet, will fill hAllSC5Jets_pt_etacut1 with pT: "<<imjet->pt()<<endl;
        hAllSC5Jets_et_etacut1->Fill(imjet->et());
        hAllSC5Jets_pt_etacut1->Fill(imjet->pt());   
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
//       printf("[SC5_PuAnalyzer_range] (et,eta,phi) source = %6.2f %5.2f %5.2f matched = %6.2f %5.2f %5.2f dR=%5.3f\n",
// 	     sourceRef->et(),
// 	     sourceRef->eta(),
// 	     sourceRef->phi(), 
// 	     matchRef->et(), 
// 	     matchRef->eta(),
// 	     matchRef->phi(), 
// 	     dR);
//      printf("[SC5_PuAnalyzer_range] (pt) source = %6.2f matched = %6.2f dR=%5.3f\n",
// 	     sourceRef->pt(),
// 	     matchRef->pt(), 
// 	     dR);

      GenEta = sourceRef->eta();
      RecoEta = matchRef->eta();
      hMatchGenJets_et->Fill(sourceRef->et());
      hMatchSC5Jets_et->Fill(matchRef->et());    
      hMatchGenJets_pt->Fill(sourceRef->pt());
      hMatchSC5Jets_pt->Fill(matchRef->pt());

	  hRecoVsGen_et->Fill(sourceRef->et(),matchRef->et());
	  hRecoVsGen_pt->Fill(sourceRef->pt(),matchRef->pt());
 	  hRecoVsGen_eta->Fill(sourceRef->eta(),matchRef->eta());
      hRecoVsGen_phi->Fill(sourceRef->phi(),matchRef->phi());
      
      if (dR<=0.2){
          hMatchGenJets_dRltpt2_et->Fill(sourceRef->et());
          hMatchSC5Jets_dRltpt2_et->Fill(matchRef->et());
          hMatchGenJets_dRltpt2_pt->Fill(sourceRef->pt());
          hMatchSC5Jets_dRltpt2_pt->Fill(matchRef->pt());
    	  hRecoVsGen_dRltpt2_et->Fill(sourceRef->et(),matchRef->et());
 	      hRecoVsGen_dRltpt2_pt->Fill(sourceRef->pt(),matchRef->pt());
 	      hRecoVsGen_dRltpt2_eta->Fill(sourceRef->eta(),matchRef->eta());
          hRecoVsGen_dRltpt2_phi->Fill(sourceRef->phi(),matchRef->phi()); 
          for(int imatched = 0;imatched<totalSC5Jets;imatched++){
             if(SC5Jets_pt_unmatch[imatched]==matchRef->pt()) {
                SC5Jets_unmatchstat[imatched]=0;
             }
          }
          Double_t ESim=sourceRef->et();
          if(determineIndex(limBins4,ESim,6)!=-1){
		     pThist[ determineIndex(limBins4,ESim,6)]->Fill((matchRef->pt())/(sourceRef->pt() ));
		     etahist[ determineIndex(limBins4,ESim,6)]->Fill(fabs(matchRef->eta())-fabs(sourceRef->eta() ));
		     phihist[ determineIndex(limBins4,ESim,6)]->Fill(deltaPhi(matchRef->phi(),sourceRef->phi()));
//		     if (fabs(matchRef->phi()-sourceRef->phi())
	      }          
          if(determineIndex(limBinsOld4,ESim,13)!=-1){
		     pThistOld[ determineIndex(limBinsOld4,ESim,13)]->Fill((matchRef->pt())/(sourceRef->pt() ));
	      }   
//	      cout<<"did pThist"<<endl;
//           Double_t pSim=sourceRef->pt();
//           if(determineIndex(limBins4,pSim,6)!=-1){
// 		     pThist[ determineIndex(limBins4,pSim,6)]->Fill((matchRef->pt())/(sourceRef->pt() ));
// 	      } 	 
//	      cout<<"did pthist"<<endl;
        if (dR<=0.1){
           hMatchGenJets_dRltpt1_et->Fill(sourceRef->et());
          hMatchSC5Jets_dRltpt1_et->Fill(matchRef->et());
          hMatchGenJets_dRltpt1_pt->Fill(sourceRef->pt());
          hMatchSC5Jets_dRltpt1_pt->Fill(matchRef->pt());
    	  hRecoVsGen_dRltpt1_et->Fill(sourceRef->et(),matchRef->et());
 	      hRecoVsGen_dRltpt1_pt->Fill(sourceRef->pt(),matchRef->pt());
 	      hRecoVsGen_dRltpt1_eta->Fill(sourceRef->eta(),matchRef->eta());
          hRecoVsGen_dRltpt1_phi->Fill(sourceRef->phi(),matchRef->phi()); 
          Double_t ESim=sourceRef->et();
          if(determineIndex(limBins4,ESim,6)!=-1){
		     pThist_dRltpt1[ determineIndex(limBins4,ESim,6)]->Fill((matchRef->pt())/(sourceRef->pt() ));
	      }          
          if(determineIndex(limBinsOld4,ESim,13)!=-1){
		     pThist_dRltpt1Old[ determineIndex(limBinsOld4,ESim,13)]->Fill((matchRef->pt())/(sourceRef->pt() ));
	      }             
        }
      } else {
//         hUnMatchedSC5Jets_pt->Fill(matchRef->et());
//         hUnMatchedSC5Jets_eta->Fill(matchRef->eta());
//           if (fabs(RecoEta)<=1.3){
//             hUnMatchedSC5Jets_pt_etacut0->Fill(matchRef->et());         
//             hUnMatchedSC5Jets_eta_etacut0->Fill(matchRef->eta());         
//           } else if (fabs(RecoEta) >1.3 && fabs(RecoEta)<3){
//             hUnMatchedSC5Jets_eta_etacut1->Fill(matchRef->eta());                   
//             hUnMatchedSC5Jets_eta_etacut1->Fill(matchRef->eta());                   
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
      hMatchSC5Jets_et_etacut0->Fill(matchRef->et());    
      
      hMatchGenJets_pt_etacut0->Fill(sourceRef->pt());
      hMatchSC5Jets_pt_etacut0->Fill(matchRef->pt());  

     if(dR<=0.2) {
    	  hRecoVsGen_dRltpt2_et_etacut0->Fill(sourceRef->et(),matchRef->et());
 	      hRecoVsGen_dRltpt2_pt_etacut0->Fill(sourceRef->pt(),matchRef->pt());
 	      hRecoVsGen_dRltpt2_eta_etacut0->Fill(sourceRef->eta(),matchRef->eta());
          hRecoVsGen_dRltpt2_phi_etacut0->Fill(sourceRef->phi(),matchRef->phi()); 
          Double_t ResFrac=(matchRef->pt())/(sourceRef->pt());
          hSimpleResolution_pt->Fill(sourceRef->pt(),ResFrac);
          hMatchGenJets_dRltpt2_et_etacut0->Fill(sourceRef->et());
          hMatchSC5Jets_dRltpt2_et_etacut0->Fill(matchRef->et());
          hMatchGenJets_dRltpt2_pt_etacut0->Fill(sourceRef->pt());
          hMatchSC5Jets_dRltpt2_pt_etacut0->Fill(matchRef->pt());
          Double_t ESim_etacut0=sourceRef->et();
          if(determineIndex(limBins4,ESim_etacut0,6)!=-1){
		     pThist_etacut0[ determineIndex(limBins4,ESim_etacut0,6)]->Fill((matchRef->pt())/(sourceRef->pt() ));
		     etahist_etacut0[ determineIndex(limBins4,ESim_etacut0,6)]->Fill(fabs(matchRef->eta())-fabs(sourceRef->eta() ));
		     phihist_etacut0[ determineIndex(limBins4,ESim_etacut0,6)]->Fill(deltaPhi(matchRef->phi(),sourceRef->phi() ));
	      }          
          if(determineIndex(limBinsOld4,ESim_etacut0,13)!=-1){
		     pThist_etacut0Old[ determineIndex(limBinsOld4,ESim_etacut0,13)]->Fill((matchRef->pt())/(sourceRef->pt() ));
	      }   
	      if(dR<=0.1){
    	    hRecoVsGen_dRltpt1_et_etacut0->Fill(sourceRef->et(),matchRef->et());
 	        hRecoVsGen_dRltpt1_pt_etacut0->Fill(sourceRef->pt(),matchRef->pt());
 	        hRecoVsGen_dRltpt1_eta_etacut0->Fill(sourceRef->eta(),matchRef->eta());
            hRecoVsGen_dRltpt1_phi_etacut0->Fill(sourceRef->phi(),matchRef->phi()); 
            hMatchGenJets_dRltpt1_et_etacut0->Fill(sourceRef->et());
            hMatchSC5Jets_dRltpt1_et_etacut0->Fill(matchRef->et());
            hMatchGenJets_dRltpt1_pt_etacut0->Fill(sourceRef->pt());
            hMatchSC5Jets_dRltpt1_pt_etacut0->Fill(matchRef->pt());	      	      
	      }
//	      cout<<"did pThistold"<<endl;	      
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
      hMatchSC5Jets_et_etacut1->Fill(matchRef->et());    
      
      hMatchGenJets_pt_etacut1->Fill(sourceRef->pt());
//      hMatchSC5Jets_pt_etacut1->Fill(matchRef->pt());  

     if(dR<=0.2) {
    	  hRecoVsGen_dRltpt2_et_etacut1->Fill(sourceRef->et(),matchRef->et());
 	      hRecoVsGen_dRltpt2_pt_etacut1->Fill(sourceRef->pt(),matchRef->pt());
 	      hRecoVsGen_dRltpt2_eta_etacut1->Fill(sourceRef->eta(),matchRef->eta());
          hRecoVsGen_dRltpt2_phi_etacut1->Fill(sourceRef->phi(),matchRef->phi()); 
//          Double_t ResFrac_etacut1=(matchRef->et())/(sourceRef->et());
   //       hSimpleResolution_Energy_etacut1->Fill(sourceRef->et(),ResFrac_etacut1);
        cout<<"[SC5_PuAnalyzer_range::analyze, have a matched endcap jet DeltaR<=0.1, will fill hMatchGenJets_dRltpt2_pt_etacut1 with Et: "<<sourceRef->pt()<<" and hMatchSC5Jets_dRltpt2_pt_etacut1 with pT: "<<matchRef->pt()<<endl;
          hMatchGenJets_dRltpt2_et_etacut1->Fill(sourceRef->et());
          hMatchSC5Jets_dRltpt2_et_etacut1->Fill(matchRef->et());
          hMatchGenJets_dRltpt2_pt_etacut1->Fill(sourceRef->pt());
          hMatchSC5Jets_dRltpt2_pt_etacut1->Fill(matchRef->pt());
          Double_t ESim_etacut1=sourceRef->et();
          if(determineIndex(limBins4,ESim_etacut1,6)!=-1){
		     pThist_etacut1[ determineIndex(limBins4,ESim_etacut1,6)]->Fill((matchRef->pt())/(sourceRef->pt() ));
		     etahist_etacut1[ determineIndex(limBins4,ESim_etacut1,6)]->Fill(fabs(matchRef->eta())-fabs(sourceRef->eta() ));
		     phihist_etacut1[ determineIndex(limBins4,ESim_etacut1,6)]->Fill(deltaPhi(matchRef->phi(),sourceRef->phi()));
	      }          	 
          if(determineIndex(limBinsOld4,ESim_etacut1,13)!=-1){
		     pThist_etacut1Old[ determineIndex(limBinsOld4,ESim_etacut1,13)]->Fill((matchRef->pt())/(sourceRef->pt() ));
	      }   
	      if(dR<=0.1){
    	    hRecoVsGen_dRltpt1_et_etacut1->Fill(sourceRef->et(),matchRef->et());
 	        hRecoVsGen_dRltpt1_pt_etacut1->Fill(sourceRef->pt(),matchRef->pt());
 	        hRecoVsGen_dRltpt1_eta_etacut1->Fill(sourceRef->eta(),matchRef->eta());
            hRecoVsGen_dRltpt1_phi_etacut1->Fill(sourceRef->phi(),matchRef->phi()); 
            hMatchGenJets_dRltpt1_et_etacut1->Fill(sourceRef->et());
            hMatchSC5Jets_dRltpt1_et_etacut1->Fill(matchRef->et());
	      }	      
     }  
    }
  }
   for(int imatchedjets = 0;imatchedjets<totalSC5Jets;imatchedjets++){
      if(SC5Jets_unmatchstat[imatchedjets]==1) {
        hUnMatchedSC5Jets_pt->Fill(SC5Jets_pt_unmatch[imatchedjets]);
        hUnMatchedSC5Jets_eta->Fill(SC5Jets_eta_unmatch[imatchedjets]);
          if (fabs(SC5Jets_eta_unmatch[imatchedjets])<=1.3){
            hUnMatchedSC5Jets_pt_etacut0->Fill(SC5Jets_pt_unmatch[imatchedjets]);         
            hUnMatchedSC5Jets_eta_etacut0->Fill(SC5Jets_eta_unmatch[imatchedjets]);         
          } else if (fabs(SC5Jets_eta_unmatch[imatchedjets]) >1.3 && fabs(SC5Jets_eta_unmatch[imatchedjets])<3){
            hUnMatchedSC5Jets_pt_etacut1->Fill(SC5Jets_pt_unmatch[imatchedjets]);                   
            hUnMatchedSC5Jets_eta_etacut1->Fill(SC5Jets_eta_unmatch[imatchedjets]);                   
          }             
       } else if(SC5Jets_unmatchstat[imatchedjets]==5){
         cout<<"[SC5_PuAnalyzer_range::analyze, Error (5) in SC5Jets_unmatchstat for imatchedjets = "<<imatchedjets<<endl;
       }
   }
 } else {
    cout<<"no MatchMap for this event: "<<iEvent.id()<<endl;
 }
  hTotalLenght->Fill( dR );

 cout<<"[SC5_PuAnalyzer_range]:: end analyze"<<endl;


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
SC5_PuAnalyzer_range::beginJob(const edm::EventSetup&)
{
 cout<<"[SC5_PuAnalyzer_range]:: start beginJob"<<endl;

   Double_t limBins2[]  = {10,25,50,75,100,150,200};
   //{1,5,10,15,20,30,40};
   Double_t limBinsOld2[] = {20,30,40,50,60,70,80,90,100,125,150,175,200,250};
   hOutputFile   = new TFile( fOutputFileName_.c_str(), "RECREATE" ) ;
   hTotalLenght  = new TH1D( "hTotalLenght", "Total Lenght", 100,  0., 5. );
   hdeltaR = new TH1F("hdeltaR","All #DeltaR_{m} values, all #eta",1000,0.,5);
   hdeltaR_etacut0 = new TH1F("hdeltaR_etacut0","All #DeltaR_{m} |#eta|<=1.3",1000,0.,5);
   hdeltaR_etacut1 = new TH1F("hdeltaR_etacut1","All #DeltaR_{m} 1.3 <| #eta | <3)",1000,0.,5);
   ratiopT = new TH1F ("ratiopT", "p^{SISCone5Jet}_{T}/p^{GenJets}_{T}, all #eta",6,limBins2);
   ratiopT->Sumw2();
   sigmapTrpTm = new TH1F ("sigmapTrpTm", "sigma(p^{SISCone5Jet}_{T}/p^{GenJets}_{T}) matched OneToOne #DeltaR_{m}<=0.2, all #eta",6,limBins2);
   sigmapTrpTm->Sumw2();
   pTresolution = new TH1F ("pTresolution", "p_{T} Resolution matched OneToOne #DeltaR_{m}<=0.2, all #eta",6,limBins2);
   pTresolution->Sumw2();   
    for (unsigned int indexH=0;indexH<6;indexH++)  {
      sprintf(nameHist,"pTdistribution%i",indexH);
      sprintf(label,"pT(reco)/pT(gen) pT(gen) #in #left[%f , %f #right] GeV, all #eta",limBins2[indexH],limBins2[indexH+1]);
      pThist[indexH]=new TH1F(nameHist,label,100,0., 2);
      pThist[indexH]->Sumw2();
      pThist[indexH]->GetXaxis()->SetTitle("p_{T}^{reco}/p_{t}^{gen}");
      pThist[indexH]->GetYaxis()->SetTitle("#");
     }

   ratiopTOld = new TH1F ("ratiopTOld", "p^{SISCone5Jet}_{T}/p^{GenJets}_{T} (different bins), all #eta",13,limBinsOld2);
   ratiopTOld->Sumw2();
   sigmapTrpTmOld = new TH1F ("sigmapTrpTmOld", "sigma(p^{SISCone5Jet}_{T}/p^{GenJets}_{T}) matched OneToOne #DeltaR_{m}<=0.2 (diff bins), all #eta",13,limBinsOld2);
   sigmapTrpTmOld->Sumw2();
   pTresolutionOld = new TH1F ("pTresolutionOld", "p_{T} Resolution matched OneToOne #DeltaR_{m}<=0.2 (different bins), all #eta",13,limBinsOld2);
   pTresolutionOld->Sumw2();   
    for (unsigned int indexHOld=0;indexHOld<13;indexHOld++)  {
      sprintf(nameHist,"pTdistributionOld%i",indexHOld);
      sprintf(label,"pT(reco)/pT(gen) pT(gen) #in #left[%f , %f #right] GeV (different bins), all #eta",limBinsOld2[indexHOld],limBinsOld2[indexHOld+1]);
      pThistOld[indexHOld]=new TH1F(nameHist,label,100,0., 2);
      pThistOld[indexHOld]->Sumw2();
      pThistOld[indexHOld]->GetXaxis()->SetTitle("p_{T}^{reco}/p_{t}^{gen}");
      pThistOld[indexHOld]->GetYaxis()->SetTitle("#");
     }
   ratiopT_dRltpt1 = new TH1F ("ratiopT_dRltpt1", "p^{SISCone5Jet}_{T}/p^{GenJets}_{T}, all #eta, #DeltaR_{m}<=0.1",6,limBins2);
   ratiopT_dRltpt1->Sumw2();
   sigmapTrpTm_dRltpt1 = new TH1F ("sigmapTrpTm_dRltpt1", "sigma(p^{SISCone5Jet}_{T}/p^{GenJets}_{T}) matched OneToOne #DeltaR_{m}<=0.1, all #eta",6,limBins2);
   sigmapTrpTm_dRltpt1->Sumw2();
   pTresolution_dRltpt1 = new TH1F ("pTresolution_dRltpt1", "p_{T} Resolution matched OneToOne #DeltaR_{m}<=0.1, all #eta",6,limBins2);
   pTresolution_dRltpt1->Sumw2();   
    for (unsigned int indexH=0;indexH<6;indexH++)  {
      sprintf(nameHist,"pTdistribution_dRltpt1%i",indexH);
      sprintf(label,"pT(reco)/pT(gen) pT(gen) #in #left[%f , %f #right] GeV, all #eta",limBins2[indexH],limBins2[indexH+1]);
      pThist_dRltpt1[indexH]=new TH1F(nameHist,label,100,0., 2);
      pThist_dRltpt1[indexH]->Sumw2();
      pThist_dRltpt1[indexH]->GetXaxis()->SetTitle("p_{T}^{reco}/p_{t}^{gen}");
      pThist_dRltpt1[indexH]->GetYaxis()->SetTitle("#");
     }

   ratiopT_dRltpt1Old = new TH1F ("ratiopT_dRltpt1Old", "p^{SISCone5Jet}_{T}/p^{GenJets}_{T} (different bins), all #eta, #DeltaR_{m}<=0.1",13,limBinsOld2);
   ratiopT_dRltpt1Old->Sumw2();
   sigmapTrpTm_dRltpt1Old = new TH1F ("sigmapTrpTm_dRltpt1Old", "sigma(p^{SISCone5Jet}_{T}/p^{GenJets}_{T}) matched OneToOne #DeltaR_{m}<=0.1 (diff bins), all #eta",13,limBinsOld2);
   sigmapTrpTm_dRltpt1Old->Sumw2();
   pTresolution_dRltpt1Old = new TH1F ("pTresolution_dRltpt1Old", "p_{T} Resolution matched OneToOne #DeltaR_{m}<=0.1 (different bins), all #eta",13,limBinsOld2);
   pTresolution_dRltpt1Old->Sumw2();   
    for (unsigned int indexHOld=0;indexHOld<13;indexHOld++)  {
      sprintf(nameHist,"pTdistribution_dRltpt1Old%i",indexHOld);
      sprintf(label,"pT(reco)/pT(gen) pT(gen) #in #left[%f , %f #right] GeV (different bins), all #eta, #DeltaR_{m}<=0.1",limBinsOld2[indexHOld],limBinsOld2[indexHOld+1]);
      pThist_dRltpt1Old[indexHOld]=new TH1F(nameHist,label,100,0., 2);
      pThist_dRltpt1Old[indexHOld]->Sumw2();
      pThist_dRltpt1Old[indexHOld]->GetXaxis()->SetTitle("p_{T}^{reco}/p_{t}^{gen}");
      pThist_dRltpt1Old[indexHOld]->GetYaxis()->SetTitle("#");
     }    

// barrel plots make:
   ratiopT_etacut0 = new TH1F ("ratiopT_etacut0", "p^{SISCone5Jet}_{T}/p^{GenJets}_{T}, 0<= | #eta | <=1.3",6,limBins2);
   ratiopT_etacut0->Sumw2();
   sigmapTrpTm_etacut0 = new TH1F ("sigmapTrpTm_etacut0", "sigma(p^{SISCone5Jet}_{T}/p^{GenJets}_{T}) matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",6,limBins2);
   sigmapTrpTm_etacut0->Sumw2();
   pTresolution_etacut0 = new TH1F ("pTresolution_etacut0", "p_{T} Resolution matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",6,limBins2);
   pTresolution_etacut0->Sumw2();   
    for (unsigned int indexH=0;indexH<6;indexH++)  {
      sprintf(nameHist,"pTdistribution_etacut0%i",indexH);
      sprintf(label,"pT(reco)/pT(gen) pT(gen) #in #left[%f , %f #right] GeV, 0<= | #eta | <=1.3",limBins2[indexH],limBins2[indexH+1]);
      pThist_etacut0[indexH]=new TH1F(nameHist,label,100,0., 2);
      pThist_etacut0[indexH]->Sumw2();
      pThist_etacut0[indexH]->GetXaxis()->SetTitle("p_{T}^{reco}/p_{t}^{gen}");
      pThist_etacut0[indexH]->GetYaxis()->SetTitle("#");
     }

   ratiopT_etacut0Old = new TH1F ("ratiopT_etacut0Old", "p^{SISCone5Jet}_{T}/p^{GenJets}_{T} (different bins), 0<= | #eta | <=1.3",13,limBinsOld2);
   ratiopT_etacut0Old->Sumw2();
   sigmapTrpTm_etacut0Old = new TH1F ("sigmapTrpTm_etacut0Old", "sigma(p^{SISCone5Jet}_{T}/p^{GenJets}_{T}) matched OneToOne #DeltaR_{m}<=0.2 (diff bins), 0<= | #eta | <=1.3",13,limBinsOld2);
   sigmapTrpTm_etacut0Old->Sumw2();
   pTresolution_etacut0Old = new TH1F ("pTresolution_etacut0Old", "p_{T} Resolution matched OneToOne #DeltaR_{m}<=0.2 (different bins), 0<= | #eta | <=1.3",13,limBinsOld2);
   pTresolution_etacut0Old->Sumw2();   
    for (unsigned int indexHOld=0;indexHOld<13;indexHOld++)  {
      sprintf(nameHist,"pTdistribution_etacut0Old%i",indexHOld);
      sprintf(label,"pT(reco)/pT(gen) pT(gen) #in #left[%f , %f #right] GeV (different bins), 0<= | #eta | <=1.3",limBinsOld2[indexHOld],limBinsOld2[indexHOld+1]);
      pThist_etacut0Old[indexHOld]=new TH1F(nameHist,label,100,0., 2);
      pThist_etacut0Old[indexHOld]->Sumw2();
      pThist_etacut0Old[indexHOld]->GetXaxis()->SetTitle("p_{T}^{reco}/p_{t}^{gen}");
      pThist_etacut0Old[indexHOld]->GetYaxis()->SetTitle("#");
     }
// endcap plots make:
   ratiopT_etacut1 = new TH1F ("ratiopT_etacut1", "p^{SISCone5Jet}_{T}/p^{GenJets}_{T}, 1.3 <| #eta | <3",6,limBins2);
   ratiopT_etacut1->Sumw2();
   sigmapTrpTm_etacut1 = new TH1F ("sigmapTrpTm_etacut1", "sigma(p^{SISCone5Jet}_{T}/p^{GenJets}_{T}) matched OneToOne #DeltaR_{m}<=0.2, 1.3 <| #eta | <3",6,limBins2);
   sigmapTrpTm_etacut1->Sumw2();
   pTresolution_etacut1 = new TH1F ("pTresolution_etacut1", "p_{T} Resolution matched OneToOne #DeltaR_{m}<=0.2, 1.3 <| #eta | <3",6,limBins2);
   pTresolution_etacut1->Sumw2();   
    for (unsigned int indexH=0;indexH<6;indexH++)  {
      sprintf(nameHist,"pTdistribution_etacut1%i",indexH);
      sprintf(label,"pT(reco)/pT(gen) pT(gen) #in #left[%f , %f #right] GeV, 1.3 <| #eta | <3",limBins2[indexH],limBins2[indexH+1]);
      pThist_etacut1[indexH]=new TH1F(nameHist,label,100,0., 2);
      pThist_etacut1[indexH]->Sumw2();
      pThist_etacut1[indexH]->GetXaxis()->SetTitle("p_{T}^{reco}/p_{t}^{gen}");
      pThist_etacut1[indexH]->GetYaxis()->SetTitle("#");
     }

   ratiopT_etacut1Old = new TH1F ("ratiopT_etacut1Old", "p^{SISCone5Jet}_{T}/p^{GenJets}_{T} (different bins), 1.3 <| #eta | <3",13,limBinsOld2);
   ratiopT_etacut1Old->Sumw2();
   sigmapTrpTm_etacut1Old = new TH1F ("sigmapTrpTm_etacut1Old", "sigma(p^{SISCone5Jet}_{T}/p^{GenJets}_{T}) matched OneToOne #DeltaR_{m}<=0.2 (diff bins), 1.3 <| #eta | <3",13,limBinsOld2);
   sigmapTrpTm_etacut1Old->Sumw2();
   pTresolution_etacut1Old = new TH1F ("pTresolution_etacut1Old", "p_{T} Resolution matched OneToOne #DeltaR_{m}<=0.2 (different bins), 1.3 <| #eta | <3",13,limBinsOld2);
   pTresolution_etacut1Old->Sumw2();   
    for (unsigned int indexHOld=0;indexHOld<13;indexHOld++)  {
      sprintf(nameHist,"pTdistribution_etacut1Old%i",indexHOld);
      sprintf(label,"pT(reco)/pT(gen) pT(gen) #in #left[%f , %f #right] GeV (different bins), 1.3 <| #eta | <3",limBinsOld2[indexHOld],limBinsOld2[indexHOld+1]);
      pThist_etacut1Old[indexHOld]=new TH1F(nameHist,label,100,0., 2);
      pThist_etacut1Old[indexHOld]->Sumw2();
      pThist_etacut1Old[indexHOld]->GetXaxis()->SetTitle("p_{T}^{reco}/p_{t}^{gen}");
      pThist_etacut1Old[indexHOld]->GetYaxis()->SetTitle("#");
     }
//
// position resolution:
   ratioeta = new TH1F ("ratioeta", "<|#eta(SISCone5Jet)|-|#eta(GenJets)|>, all #eta",6,limBins2);
   ratioeta->Sumw2();
   sigmaeta = new TH1F ("sigmaeta", "sigma(|#eta(SISCone5Jet)|-|#eta(GenJets)|) matched OneToOne #DeltaR_{m}<=0.2, all #eta",6,limBins2);
   sigmaeta->Sumw2();  
    for (unsigned int indexH=0;indexH<6;indexH++)  {
      sprintf(nameHist,"etaDistribution%i",indexH);
      sprintf(label,"|#eta(reco)|-|#eta(gen)| ET(gen) #in #left[%f , %f #right] GeV, all #eta",limBins2[indexH],limBins2[indexH+1]);
      etahist[indexH]=new TH1F(nameHist,label,100,-1., 1.);
      etahist[indexH]->Sumw2();
      etahist[indexH]->GetXaxis()->SetTitle("|#eta(reco)|-|#eta(gen)|");
      etahist[indexH]->GetYaxis()->SetTitle("#");
     }
   ratioeta_etacut0 = new TH1F ("ratioeta_etacut0", "<|#eta(SISCone5Jet)|-|#eta(GenJets)|>, 0<= | #eta | <=1.3",6,limBins2);
   ratioeta_etacut0->Sumw2();
   sigmaeta_etacut0 = new TH1F ("sigmaeta_etacut0", "sigma(|#eta(SISCone5Jet)|-|#eta(GenJets)|) matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",6,limBins2);
   sigmaeta_etacut0->Sumw2();
    for (unsigned int indexH=0;indexH<6;indexH++)  {
      sprintf(nameHist,"etaDistribution_etacut0%i",indexH);
      sprintf(label,"|#eta(reco)|-|#eta(gen)| ET(gen) #in #left[%f , %f #right] GeV, 0<= | #eta | <=1.3",limBins2[indexH],limBins2[indexH+1]);
      etahist_etacut0[indexH]=new TH1F(nameHist,label,100,-1., 1.);
      etahist_etacut0[indexH]->Sumw2();
      etahist_etacut0[indexH]->GetXaxis()->SetTitle("|#eta(reco)|-|#eta(gen)|");
      etahist_etacut0[indexH]->GetYaxis()->SetTitle("#");
     }
   ratioeta_etacut1 = new TH1F ("ratioeta_etacut1", "<|#eta(SISCone5Jet)|-|#eta(GenJets)|>, 1.3 <| #eta | <3",6,limBins2);
   ratioeta_etacut1->Sumw2();
   sigmaeta_etacut1 = new TH1F ("sigmaeta_etacut1", "sigma(|#eta(SISCone5Jet)|-|#eta(GenJets)|) matched OneToOne #DeltaR_{m}<=0.2, 1.3 <| #eta | <3",6,limBins2);
   sigmaeta_etacut1->Sumw2();
    for (unsigned int indexH=0;indexH<6;indexH++)  {
      sprintf(nameHist,"etaDistribution_etacut1%i",indexH);
      sprintf(label,"|#eta(reco)|-|#eta(gen)| ET(gen) #in #left[%f , %f #right] GeV, 1.3 <| #eta | <3",limBins2[indexH],limBins2[indexH+1]);
      etahist_etacut1[indexH]=new TH1F(nameHist,label,100,-1., 1.);
      etahist_etacut1[indexH]->Sumw2();
      etahist_etacut1[indexH]->GetXaxis()->SetTitle("|#eta(reco)|-|#eta(gen)|");
      etahist_etacut1[indexH]->GetYaxis()->SetTitle("#");
     }
   ratioPhi = new TH1F ("ratioPhi", "<#phi(SISCone5Jet)-#phi(GenJets)>, all #eta",6,limBins2);
   ratioPhi->Sumw2();
   sigmaphi = new TH1F ("sigmaphi", "sigma(#phi(SISCone5Jet)-#phi(GenJets)) matched OneToOne #DeltaR_{m}<=0.2, all #eta",6,limBins2);
   sigmaphi->Sumw2();  
    for (unsigned int indexH=0;indexH<6;indexH++)  {
      sprintf(nameHist,"phiDistribution%i",indexH);
      sprintf(label,"#phi(reco)-#phi(gen) ET(gen) #in #left[%f , %f #right] GeV, all #eta",limBins2[indexH],limBins2[indexH+1]);
      phihist[indexH]=new TH1F(nameHist,label,100,-1., 1.);
      phihist[indexH]->Sumw2();
      phihist[indexH]->GetXaxis()->SetTitle("#phi(reco)-#phi(gen)");
      phihist[indexH]->GetYaxis()->SetTitle("#");
     }
   ratioPhi_etacut0 = new TH1F ("ratioPhi_etacut0", "<#phi(SISCone5Jet)-#phi(GenJets)>, 0<= | #eta | <=1.3",6,limBins2);
   ratioPhi_etacut0->Sumw2();
   sigmaphi_etacut0 = new TH1F ("sigmaphi_etacut0", "sigma(#phi(SISCone5Jet)-#phi(GenJets)) matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",6,limBins2);
   sigmaphi_etacut0->Sumw2(); 
    for (unsigned int indexH=0;indexH<6;indexH++)  {
      sprintf(nameHist,"phiDistribution_etacut0%i",indexH);
      sprintf(label,"#phi(reco)-#phi(gen) ET(gen) #in #left[%f , %f #right] GeV, 0<= | #eta | <=1.3",limBins2[indexH],limBins2[indexH+1]);
      phihist_etacut0[indexH]=new TH1F(nameHist,label,100,-1., 1.);
      phihist_etacut0[indexH]->Sumw2();
      phihist_etacut0[indexH]->GetXaxis()->SetTitle("#phi(reco)-#phi(gen)");
      phihist_etacut0[indexH]->GetYaxis()->SetTitle("#");
     }
   ratioPhi_etacut1 = new TH1F ("ratioPhi_etacut1", "<#phi(SISCone5Jet)-#phi(GenJets)>, 1.3 <| #eta | <3",6,limBins2);
   ratioPhi_etacut1->Sumw2();
   sigmaphi_etacut1 = new TH1F ("sigmaphi_etacut1", "sigma(#phi(SISCone5Jet)-#phi(GenJets)) matched OneToOne #DeltaR_{m}<=0.2, 1.3 <| #eta | <3",6,limBins2);
   sigmaphi_etacut1->Sumw2();
  
    for (unsigned int indexH=0;indexH<6;indexH++)  {
      sprintf(nameHist,"phiDistribution_etacut1%i",indexH);
      sprintf(label,"#phi(reco)-#phi(gen) ET(gen) #in #left[%f , %f #right] GeV, 1.3 <| #eta | <3",limBins2[indexH],limBins2[indexH+1]);
      phihist_etacut1[indexH]=new TH1F(nameHist,label,100,-1., 1.);
      phihist_etacut1[indexH]->Sumw2();
      phihist_etacut1[indexH]->GetXaxis()->SetTitle("#phi(reco)-#phi(gen)");
      phihist_etacut1[indexH]->GetYaxis()->SetTitle("#");
     }

   hSimpleResolution_pt = new TH2F("hSimpleResolution_pt","p_{T} Reco)/(p_{T} Gen (Event by Event) vs. p_{T} Gen - matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",50,0,225,50,0,3);
//   hSimpleEfficiency_Energy = new TH2F("hSimpleEfficiency_Energy","(# matched jets)/(# All SC5 jets) vs. p_{T} Gen - matched OneToOne #DeltaR_{m}<=0.2",50,0,5,50,0,225);
///   hMatchedGenNumEv_Ratio = new TH1F("hMatchedGenNumEv_Ratio","(# matched SC5 Jets)/(# All GenJets) - matched OneToOne #DeltaR_{m}<=0.2, All #eta",100,0,225);
//   hMatchedGenNumEv_Ratio->Sumw2();
 //  hMatchedCaloNumEv_Ratio = new TH1F("hMatchedCaloNumEv_Ratio","(# matched SC5 Jets)/(# All SC5 Jets) - matched OneToOne #DeltaR_{m}<=0.2, All #eta",100,0,225);
//   hMatchedCaloNumEv_Ratio->Sumw2();
   hMatchedGenGNumEv_Ratio = new TH1F("hMatchedGenGNumEv_Ratio","(# matched GenJets)/(# All GenJets) - matched OneToOne #DeltaR_{m}<=0.2, All #eta",100,0,225);
   hMatchedGenGNumEv_Ratio->Sumw2();

   hMatchedGenGNumEv_Ratio_dRltpt1 = new TH1F("hMatchedGenGNumEv_Ratio_dRltpt1","(# matched GenJets)/(# All GenJets) - matched OneToOne #DeltaR_{m}<=0.1, All #eta",100,0,225);
   hMatchedGenGNumEv_Ratio_dRltpt1->Sumw2();

   hFakeRatio = new TH1F("hFakeRatio","(# unmatched SISCone5Jets)/(# All SISCone5Jets), All #eta",100,0,225);
   hFakeRatio->Sumw2();
   hFakeRatio_etacut0 = new TH1F("hFakeRatio_etacut0","(# unmatched SISCone5Jets)/(# All SISCone5Jets), 0<= | #eta | <=1.3",100,0,225);
   hFakeRatio_etacut0->Sumw2();
   hFakeRatio_etacut1 = new TH1F("hFakeRatio_etacut1","(# unmatched SISCone5Jets)/(# All SISCone5Jets), 1.3 <| #eta | <3",100,0,225);
   hFakeRatio_etacut1->Sumw2();

   hAllGenJets_et = new TH1F("hAllGenJets_et","All GenJets E_{T}, All #eta",100,0,225);
   hAllGenJets_et->Sumw2();
   hMatchGenJets_dRltpt2_et = new TH1F("hMatchGenJets_dRltpt2_et","GenJets E_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.2, All #eta",100,0,225);
   hMatchGenJets_dRltpt2_et->Sumw2();
   hMatchGenJets_et = new TH1F("hMatchGenJets_et","GenJets E_{T} - which have a OneToOne Match, no #DeltaR_{m} cut, All #eta",100,0,225);
   hMatchGenJets_et->Sumw2();
   hMatchSC5Jets_dRltpt2_et = new TH1F("hMatchSC5Jets_dRltpt2_et","SISCone5Jet E_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.2, All #eta",100,0,225);
   hMatchSC5Jets_dRltpt2_et->Sumw2();
   hMatchSC5Jets_et = new TH1F("hMatchSC5Jets_et","GenJets E_{T} - which have a OneToOne Match, no #DeltaR_{m} cut, All #eta",100,0,225);
   hMatchSC5Jets_et->Sumw2();
   hAllSC5Jets_et = new TH1F("hAllSC5Jets_et","All SISCone5Jet E_{T}, All #eta",100,0,225);
   hAllSC5Jets_et->Sumw2();   

   hUnMatchedSC5Jets_pt = new TH1F("hUnMatchedSC5Jets_pt","Unmatched SISCone5Jet p_{T}, All #eta",100,0,225);
//   hUnMatchedSC5Jets_dRltpt2_et = new TH1F("hUnMatchedSC5Jets_dRltpt2_et","Unmatched SISCone5Jet p_{T}, outside of #DeltaR_{m}<=0.2 cut, All #eta",100,0,225);
   hUnMatchedSC5Jets_pt_etacut0 = new TH1F("hUnMatchedSC5Jets_pt_etacut0","Unmatched SISCone5Jet p_{T}, 0<= | #eta | <=1.3",100,0,225);
//   hUnMatchedSC5Jets_dRltpt2_et_etacut0 = new TH1F("hUnMatchedSC5Jets_dRltpt2_et_etacut0","Unmatched SISCone5Jet p_{T}, outside of #DeltaR_{m}<=0.2 cut, 0<= | #eta | <=1.3",100,0,225);
   hUnMatchedSC5Jets_pt_etacut1 = new TH1F("hUnMatchedSC5Jets_pt_etacut1","Unmatched SISCone5Jet p_{T}, 1.3 <| #eta | <3",100,0,225);
//   hUnMatchedSC5Jets_dRltpt2_et_etacut1 = new TH1F("hUnMatchedSC5Jets_dRltpt2_et_etacut1","Unmatched SISCone5Jet p_{T}, outside of #DeltaR_{m}<=0.2 cut, 1.3 <| #eta | <3",100,0,225);

   hUnMatchedSC5Jets_eta = new TH1F("hUnMatchedSC5Jets_eta","Unmatched SISCone5Jet #eta, All #eta",100,-3,3);
   hUnMatchedSC5Jets_eta_etacut0 = new TH1F("hUnMatchedSC5Jets_eta_etacut0","Unmatched SISCone5Jet #eta, 0<= | #eta | <=1.3",100,-0.5,0.5);
   hUnMatchedSC5Jets_eta_etacut1 = new TH1F("hUnMatchedSC5Jets_eta_etacut1","Unmatched SISCone5Jet #eta, 1.3 <| #eta | <3",100,-2,2);

   hMatchedGenGNumEv_Ratio_etacut0 = new TH1F("hMatchedGenGNumEv_Ratio_etacut0","(# matched GenJets)/(# All GenJets) - matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",100,0,225);
   hMatchedGenGNumEv_Ratio_etacut0->Sumw2();

   hMatchedGenGNumEv_Ratio_dRltpt1_etacut0 = new TH1F("hMatchedGenGNumEv_Ratio_dRltpt1_etacut0","(# matched GenJets)/(# All GenJets) - matched OneToOne #DeltaR_{m}<=0.1, 0<= | #eta | <=1.3",100,0,225);
   hMatchedGenGNumEv_Ratio_dRltpt1_etacut0->Sumw2();

   hAllGenJets_et_etacut0 = new TH1F("hAllGenJets_et_etacut0","All GenJets E_{T}, 0<= | #eta | <=1.3",100,0,225);
   hAllGenJets_et_etacut0->Sumw2();   
   hMatchGenJets_dRltpt2_et_etacut0 = new TH1F("hMatchGenJets_dRltpt2_et_etacut0","GenJets E_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",100,0,225);
   hMatchGenJets_dRltpt2_et_etacut0->Sumw2();
   hMatchGenJets_et_etacut0 = new TH1F("hMatchGenJets_et_etacut0","GenJets E_{T} - which have a OneToOne Match, no #DeltaR_{m} cut, 0<= | #eta | <=1.3",100,0,225);
   hMatchGenJets_et_etacut0->Sumw2();
   hMatchSC5Jets_dRltpt2_et_etacut0 = new TH1F("hMatchSC5Jets_dRltpt2_et_etacut0","SISCone5Jet E_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",100,0,225);
   hMatchSC5Jets_dRltpt2_et_etacut0->Sumw2();
   hMatchSC5Jets_et_etacut0 = new TH1F("hMatchSC5Jets_et_etacut0","GenJets E_{T} - which have a OneToOne Match, no #DeltaR_{m} cut, 0<= | #eta | <=1.3",100,0,225);
   hMatchSC5Jets_et_etacut0->Sumw2();
   hAllSC5Jets_et_etacut0 = new TH1F("hAllSC5Jets_et_etacut0","All SISCone5Jet E_{T}, 0<= | #eta | <=1.3",100,0,225);
   hAllSC5Jets_et_etacut0->Sumw2();   


   hMatchedGenGNumEv_Ratio_etacut1 = new TH1F("hMatchedGenGNumEv_Ratio_etacut1","ratio (# matched GenJets)/(# All GenJets) - matched OneToOne #DeltaR_{m}<=0.2, 1.3 <| #eta | <3",100,0,225);
   hMatchedGenGNumEv_Ratio_etacut1->Sumw2();
   hAllGenJets_et_etacut1 = new TH1F("hAllGenJets_et_etacut1","All GenJets E_{T}, 1.3 <| #eta | <3",100,0,225);
   hAllGenJets_et_etacut1->Sumw2();
   hMatchGenJets_dRltpt2_et_etacut1 = new TH1F("hMatchGenJets_dRltpt2_et_etacut1","GenJets E_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.2, 1.3 <| #eta | <3",100,0,225);
   hMatchGenJets_dRltpt2_et_etacut1->Sumw2();
   hMatchGenJets_et_etacut1 = new TH1F("hMatchGenJets_et_etacut1","GenJets E_{T} - which have a OneToOne Match, no #DeltaR_{m} cut, 1.3 <| #eta | <3",100,0,225);
   hMatchGenJets_et_etacut1->Sumw2();
   hAllSC5Jets_et_etacut1 = new TH1F("hAllSC5Jets_et_etacut1","All SISCone5Jet E_{T}, 1.3 <| #eta | <3",100,0,225);
   hAllSC5Jets_et_etacut1->Sumw2();
   hMatchSC5Jets_dRltpt2_et_etacut1 = new TH1F("hMatchSC5Jets_dRltpt2_et_etacut1","SISCone5Jet E_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.2, 1.3 <| #eta | <3",100,0,225);
   hMatchSC5Jets_dRltpt2_et_etacut1->Sumw2();
   hMatchSC5Jets_et_etacut1 = new TH1F("hMatchSC5Jets_et_etacut1","GenJets E_{T} - which have a OneToOne Match, no #DeltaR_{m} cut, 1.3 <| #eta | <3",100,0,225);
   hMatchSC5Jets_et_etacut1->Sumw2(); 

// pt plots
   hAllGenJets_pt = new TH1F("hAllGenJets_pt","All GenJets p_{T}, All #eta",100,0,225);
   hAllGenJets_pt->Sumw2();
   hMatchGenJets_pt = new TH1F("hMatchGenJets_pt","GenJets p_{T} - which have a OneToOne Match, no #DeltaR_{m} cut, All #eta",100,0,225);
   hMatchGenJets_pt->Sumw2(); 
   hAllSC5Jets_pt = new TH1F("hAllSC5Jets_pt","All SISCone5Jet p_{T}, All #eta",100,0,225);
   hAllSC5Jets_pt->Sumw2();
   hMatchSC5Jets_pt = new TH1F("hMatchSC5Jets_pt","GenJets p_{T} - which have a OneToOne Match, no #DeltaR_{m} cut, All #eta",100,0,225);
   hMatchSC5Jets_pt->Sumw2();
//   hMatchedGenGNumEv_pt_Ratio = new TH1F("hMatchedGenGNumEv_pt_Ratio","pt (# matched GenJets)/(# All GenJets) - matched OneToOne #DeltaR_{m}<=0.2, All #eta",100,0,225);
//   hMatchedGenGNumEv_pt_Ratio->Sumw2();
   hMatchGenJets_dRltpt2_pt = new TH1F("hMatchGenJets_dRltpt2_pt","GenJets p_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.2, All #eta",100,0,225);
   hMatchGenJets_dRltpt2_pt->Sumw2();
   hMatchSC5Jets_dRltpt2_pt = new TH1F("hMatchSC5Jets_dRltpt2_pt","SISCone5Jet p_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.2, All #eta",100,0,225);
   hMatchSC5Jets_dRltpt2_pt->Sumw2();

   hAllGenJets_pt_etacut0 = new TH1F("hAllGenJets_pt_etacut0","All GenJets p_{T}, 0<= | #eta | <=1.3",100,0,225);
   hAllGenJets_pt_etacut0->Sumw2();
   hMatchGenJets_pt_etacut0 = new TH1F("hMatchGenJets_pt_etacut0","GenJets p_{T} - which have a OneToOne Match, no #DeltaR_{m} cut, 0<= | #eta | <=1.3",100,0,225);
   hMatchGenJets_pt_etacut0->Sumw2(); 
   hAllSC5Jets_pt_etacut0 = new TH1F("hAllSC5Jets_pt_etacut0","All SISCone5Jet p_{T}, 0<= | #eta | <=1.3",100,0,225);
   hAllSC5Jets_pt_etacut0->Sumw2();
   hMatchSC5Jets_pt_etacut0 = new TH1F("hMatchSC5Jets_pt_etacut0","GenJets p_{T} - which have a OneToOne Match, no #DeltaR_{m} cut, 0<= | #eta | <=1.3",100,0,225);
   hMatchSC5Jets_pt_etacut0->Sumw2();
//   hMatchedGenGNumEv_pt_Ratio_etacut0 = new TH1F("hMatchedGenGNumEv_pt_Ratio_etacut0","pt (# matched GenJets)/(# All GenJets) - matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",100,0,225);
//   hMatchedGenGNumEv_pt_Ratio_etacut0->Sumw2();
   hMatchGenJets_dRltpt2_pt_etacut0 = new TH1F("hMatchGenJets_dRltpt2_pt_etacut0","GenJets p_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",100,0,225);
   hMatchGenJets_dRltpt2_pt_etacut0->Sumw2();
   hMatchSC5Jets_dRltpt2_pt_etacut0 = new TH1F("hMatchSC5Jets_dRltpt2_pt_etacut0","SISCone5Jet p_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",100,0,225);
   hMatchSC5Jets_dRltpt2_pt_etacut0->Sumw2();
   
    hAllGenJets_pt_etacut1 = new TH1F("hAllGenJets_pt_etacut1","All GenJets p_{T}, 1.3 <| #eta | <3",100,0,225);
    hAllGenJets_pt_etacut1->Sumw2();
    hAllSC5Jets_pt_etacut1 = new TH1F("hAllSC5Jets_pt_etacut1","All SISCone5Jet p_{T}, 1.3 <| #eta | <3",100,0,225);
    hAllSC5Jets_pt_etacut1->Sumw2();

//     ratiopt = new TH1F ("ratiopt", "p^{SISCone5Jet}_{T}/p^{GenJets}_{T}, 0<= | #eta | <=1.3",6, 0, 225);
//    ratiopt->Sumw2();
//    sigmapTrpTm_pt = new TH1F ("sigmapTrpTm_pt", "sigma(p^{SISCone5Jet}_{T}/p^{GenJets}_{T}) matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",7, 0, 225);
//    sigmapTrpTm_pt->Sumw2();
//    pTresolution = new TH1F ("pTresolution", "p_{T} Resolution matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",7, 0, 225);
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
//    ratiopt_etacut1 = new TH1F ("ratiopt_etacut1", "p^{SISCone5Jet}_{T}/p^{GenJets}_{T}, 1.3 <| #eta | <3",7, 0, 225);
//    ratiopt_etacut1->Sumw2();
//    sigmapTrpTm_pt_etacut1 = new TH1F ("sigmapTrpTm_pt_etacut1", "sigma(p^{SISCone5Jet}_{T}/p^{GenJets}_{T}) matched OneToOne #DeltaR_{m}<=0.2, 1.3 <| #eta | <3",7, 0, 225);
//    sigmapTrpTm_pt_etacut1->Sumw2();
//    pTresolution_etacut1 = new TH1F ("pTresolution_etacut1", "p_{T} Resolution matched OneToOne #DeltaR_{m}<=0.2, 1.3 <| #eta | <3",7, 0, 225);
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
//      ratioptOld = new TH1F ("ratioptOld", "p^{SISCone5Jet}_{T}/p^{GenJets}_{T} (different bins)",13, 0, 350);
//    ratioptOld->Sumw2();
//    sigmapTrpTm_ptOld = new TH1F ("sigmapTrpTm_ptOld", "sigma(p^{SISCone5Jet}_{T}/p^{GenJets}_{T}) matched OneToOne #DeltaR_{m}<=0.2 (diff bins)",13, 0, 350);
//    sigmapTrpTm_ptOld->Sumw2();
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
//   hSimpleResolution_Energy = new TH2F("hSimpleResolution_Energy","p_{T} Reco)/(p_{T} Gen (Event by Event) vs. p_{T} Gen - matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3",50,0,225,50,0,3);
//    hMatchedGenGNumEv_pt_Ratio_etacut1 = new TH1F("hMatchedGenGNumEv_pt_Ratio_etacut1","pt (# matched GenJets)/(# All GenJets) - matched OneToOne #DeltaR_{m}<=0.2, 1.3 <| #eta | <3",100,0,225);
//    hMatchedGenGNumEv_pt_Ratio_etacut1->Sumw2();
    hMatchGenJets_dRltpt2_pt_etacut1 = new TH1F("hMatchGenJets_dRltpt2_pt_etacut1","GenJets p_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.2, 1.3 <| #eta | <3",100,0,225);
    hMatchGenJets_dRltpt2_pt_etacut1->Sumw2();
    hMatchGenJets_pt_etacut1 = new TH1F("hMatchGenJets_pt_etacut1","GenJets p_{T} - which have a OneToOne Match, no #DeltaR_{m} cut, 1.3 <| #eta | <3",100,0,225);
    hMatchGenJets_pt_etacut1->Sumw2();
    hMatchSC5Jets_dRltpt2_pt_etacut1 = new TH1F("hMatchSC5Jets_dRltpt2_pt_etacut1","SISCone5Jet p_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.2, 1.3 <| #eta | <3",100,0,225);
    hMatchSC5Jets_dRltpt2_pt_etacut1->Sumw2();
//    hMatchSC5Jets_pt_etacut1 = new TH1F("hMatchSC5Jets_pt_etacut1","GenJets p_{T} - which have a OneToOne Match, no #DeltaR_{m} cut, 1.3 <| #eta | <3",100,0,225);
//    hMatchSC5Jets_pt_etacut1->Sumw2();
   
   hRecoVsGen_et_etacut1 = new TH2F( "RecoVsGen_et_etacut1", "SISCone5Jet E_{T} vs. GenJets E_{T} - matched OneToOne, 1.3 <| #eta | <3", 100, 0, 225, 100, 0, 225);
   hRecoVsGen_pt_etacut1 = new TH2F( "RecoVsGen_pt_etacut1", "SISCone5Jet p_{T} vs. GenJets p_{T} - matched OneToOne, 1.3 <| #eta | <3", 100, 0, 225, 100, 0, 225);
   hRecoVsGen_eta_etacut1 = new TH2F( "RecoVsGen_eta_etacut1", "SISCone5Jet #eta vs. GenJets #eta - matched OneToOne, 1.3 <| #eta | <3", 100, -3, 3, 100, -3, 3 );
   hRecoVsGen_phi_etacut1 = new TH2F( "RecoVsGen_phi_etacut1", "SISCone5Jet #phi vs. GenJets #phi - matched OneToOne, 1.3 <| #eta | <3", 100,  -M_PI, M_PI, 100,  -M_PI, M_PI );
   hRecoVsGen_dRltpt2_et_etacut1 = new TH2F( "RecoVsGen_dRltpt2_et_etacut1", "SISCone5Jet E_{T} vs. GenJets E_{T} - matched OneToOne #DeltaR_{m}<=0.2, 1.3 <| #eta | <3", 100, 0, 225, 100, 0, 225);
   hRecoVsGen_dRltpt2_pt_etacut1 = new TH2F( "RecoVsGen_dRltpt2_pt_etacut1", "SISCone5Jet p_{T} vs. GenJets p_{T} - matched OneToOne #DeltaR_{m}<=0.2, 1.3 <| #eta | <3", 100, 0, 225, 100, 0, 225);
   hRecoVsGen_dRltpt2_eta_etacut1 = new TH2F( "RecoVsGen_dRltpt2_eta_etacut1", "SISCone5Jet #eta vs. GenJets #eta - matched OneToOne #DeltaR_{m}<=0.2, 1.3 <| #eta | <3", 100, -3, 3, 100, -3, 3 );
   hRecoVsGen_dRltpt2_phi_etacut1 = new TH2F( "RecoVsGen_dRltpt2_phi_etacut1", "SISCone5Jet #phi vs. GenJets #phi - matched OneToOne #DeltaR_{m}<=0.2, 1.3 <| #eta | <3", 100,  -M_PI, M_PI, 100,  -M_PI, M_PI );

 
   hRecoVsGen_et_etacut0 = new TH2F( "RecoVsGen_et_etacut0", "SISCone5Jet E_{T} vs. GenJets E_{T} - matched OneToOne, 0<= | #eta | <=1.3", 100, 0, 225, 100, 0, 225);
   hRecoVsGen_pt_etacut0 = new TH2F( "RecoVsGen_pt_etacut0", "SISCone5Jet p_{T} vs. GenJets p_{T} - matched OneToOne, 0<= | #eta | <=1.3", 100, 0, 225, 100, 0, 225);
   hRecoVsGen_eta_etacut0 = new TH2F( "RecoVsGen_eta_etacut0", "SISCone5Jet #eta vs. GenJets #eta - matched OneToOne, 0<= | #eta | <=1.3", 100, -3, 3, 100, -3, 3 );
   hRecoVsGen_phi_etacut0 = new TH2F( "RecoVsGen_phi_etacut0", "SISCone5Jet #phi vs. GenJets #phi - matched OneToOne, 0<= | #eta | <=1.3", 100,  -M_PI, M_PI, 100,  -M_PI, M_PI );
   hRecoVsGen_dRltpt2_et_etacut0 = new TH2F( "RecoVsGen_dRltpt2_et_etacut0", "SISCone5Jet E_{T} vs. GenJets E_{T} - matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3", 100, 0, 225, 100, 0, 225);
   hRecoVsGen_dRltpt2_pt_etacut0 = new TH2F( "RecoVsGen_dRltpt2_pt_etacut0", "SISCone5Jet p_{T} vs. GenJets p_{T} - matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3", 100, 0, 225, 100, 0, 225);
   hRecoVsGen_dRltpt2_eta_etacut0 = new TH2F( "RecoVsGen_dRltpt2_eta_etacut0", "SISCone5Jet #eta vs. GenJets #eta - matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3", 100, -3, 3, 100, -3, 3 );
   hRecoVsGen_dRltpt2_phi_etacut0 = new TH2F( "RecoVsGen_dRltpt2_phi_etacut0", "SISCone5Jet #phi vs. GenJets #phi - matched OneToOne #DeltaR_{m}<=0.2, 0<= | #eta | <=1.3", 100,  -M_PI, M_PI, 100,  -M_PI, M_PI );
 
   hRecoVsGen_et = new TH2F( "RecoVsGen_et", "SISCone5Jet E_{T} vs. GenJets E_{T} - matched OneToOne, All #eta", 100, 0, 225, 100, 0, 225);
   hRecoVsGen_pt = new TH2F( "RecoVsGen_pt", "SISCone5Jet p_{T} vs. GenJets p_{T} - matched OneToOne, All #eta", 100, 0, 225, 100, 0, 225);
   hRecoVsGen_eta = new TH2F( "RecoVsGen_eta", "SISCone5Jet #eta vs. GenJets #eta - matched OneToOne, All #eta", 100, -3, 3, 100, -3, 3 );
   hRecoVsGen_phi = new TH2F( "RecoVsGen_phi", "SISCone5Jet #phi vs. GenJets #phi - matched OneToOne, All #eta", 100,  -M_PI, M_PI, 100,  -M_PI, M_PI );
   hRecoVsGen_dRltpt2_et = new TH2F( "RecoVsGen_dRltpt2_et", "SISCone5Jet E_{T} vs. GenJets E_{T} - matched OneToOne #DeltaR_{m}<=0.2, All #eta", 100, 0, 225, 100, 0, 225);
   hRecoVsGen_dRltpt2_pt = new TH2F( "RecoVsGen_dRltpt2_pt", "SISCone5Jet p_{T} vs. GenJets p_{T} - matched OneToOne #DeltaR_{m}<=0.2, All #eta", 100, 0, 225, 100, 0, 225);
   hRecoVsGen_dRltpt2_eta = new TH2F( "RecoVsGen_dRltpt2_eta", "SISCone5Jet #eta vs. GenJets #eta - matched OneToOne #DeltaR_{m}<=0.2, All #eta", 100, -3, 3, 100, -3, 3 );
   hRecoVsGen_dRltpt2_phi = new TH2F( "RecoVsGen_dRltpt2_phi", "SISCone5Jet #phi vs. GenJets #phi - matched OneToOne #DeltaR_{m}<=0.2, All #eta", 100,  -M_PI, M_PI, 100,  -M_PI, M_PI );
// setup deltaR<=0.05 plots:
   hMatchGenJets_dRltpt1_et = new TH1F("hMatchGenJets_dRltpt1_et","GenJets E_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.1, All #eta",100,0,225);
   hMatchGenJets_dRltpt1_et->Sumw2();
   hMatchSC5Jets_dRltpt1_et = new TH1F("hMatchSC5Jets_dRltpt1_et","SISCone5Jet E_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.1, All #eta",100,0,225);
   hMatchSC5Jets_dRltpt1_et->Sumw2();
   hMatchGenJets_dRltpt1_et_etacut0 = new TH1F("hMatchGenJets_dRltpt1_et_etacut0","GenJets E_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.1, 0<= | #eta | <=1.3",100,0,225);
   hMatchGenJets_dRltpt1_et_etacut0->Sumw2();
   hMatchSC5Jets_dRltpt1_et_etacut0 = new TH1F("hMatchSC5Jets_dRltpt1_et_etacut0","SISCone5Jet E_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.1, 0<= | #eta | <=1.3",100,0,225);
   hMatchSC5Jets_dRltpt1_et_etacut0->Sumw2();
   hMatchGenJets_dRltpt1_et_etacut1 = new TH1F("hMatchGenJets_dRltpt1_et_etacut1","GenJets E_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.1, 1.3 <| #eta | <3",100,0,225);
   hMatchGenJets_dRltpt1_et_etacut1->Sumw2();
   hMatchSC5Jets_dRltpt1_et_etacut1 = new TH1F("hMatchSC5Jets_dRltpt1_et_etacut1","SISCone5Jet E_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.1, 1.3 <| #eta | <3",100,0,225);
   hMatchSC5Jets_dRltpt1_et_etacut1->Sumw2();
   hMatchGenJets_dRltpt1_pt = new TH1F("hMatchGenJets_dRltpt1_pt","GenJets p_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.1, All #eta",100,0,225);
   hMatchGenJets_dRltpt1_pt->Sumw2();
   hMatchSC5Jets_dRltpt1_pt = new TH1F("hMatchSC5Jets_dRltpt1_pt","SISCone5Jet p_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.1, All #eta",100,0,225);
   hMatchSC5Jets_dRltpt1_pt->Sumw2();
   hMatchGenJets_dRltpt1_pt_etacut0 = new TH1F("hMatchGenJets_dRltpt1_pt_etacut0","GenJets p_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.1, 0<= | #eta | <=1.3",100,0,225);
   hMatchGenJets_dRltpt1_pt_etacut0->Sumw2();
   hMatchSC5Jets_dRltpt1_pt_etacut0 = new TH1F("hMatchSC5Jets_dRltpt1_pt_etacut0","SISCone5Jet p_{T} - which have a OneToOne Match within #DeltaR_{m}<=0.1, 0<= | #eta | <=1.3",100,0,225);
   hMatchSC5Jets_dRltpt1_pt_etacut0->Sumw2();
   hRecoVsGen_dRltpt1_et_etacut1 = new TH2F( "RecoVsGen_dRltpt1_et_etacut1", "SISCone5Jet E_{T} vs. GenJets E_{T} - matched OneToOne #DeltaR_{m}<=0.1, 1.3 <| #eta | <3", 100, 0, 225, 100, 0, 225);
   hRecoVsGen_dRltpt1_pt_etacut1 = new TH2F( "RecoVsGen_dRltpt1_pt_etacut1", "SISCone5Jet p_{T} vs. GenJets p_{T} - matched OneToOne #DeltaR_{m}<=0.1, 1.3 <| #eta | <3", 100, 0, 225, 100, 0, 225);
   hRecoVsGen_dRltpt1_eta_etacut1 = new TH2F( "RecoVsGen_dRltpt1_eta_etacut1", "SISCone5Jet #eta vs. GenJets #eta - matched OneToOne #DeltaR_{m}<=0.1, 1.3 <| #eta | <3", 100, -3, 3, 100, -3, 3 );
   hRecoVsGen_dRltpt1_phi_etacut1 = new TH2F( "RecoVsGen_dRltpt1_phi_etacut1", "SISCone5Jet #phi vs. GenJets #phi - matched OneToOne #DeltaR_{m}<=0.1, 1.3 <| #eta | <3", 100,  -M_PI, M_PI, 100,  -M_PI, M_PI );
   hRecoVsGen_dRltpt1_et_etacut0 = new TH2F( "RecoVsGen_dRltpt1_et_etacut0", "SISCone5Jet E_{T} vs. GenJets E_{T} - matched OneToOne #DeltaR_{m}<=0.1, 0<= | #eta | <=1.3", 100, 0, 225, 100, 0, 225);
   hRecoVsGen_dRltpt1_pt_etacut0 = new TH2F( "RecoVsGen_dRltpt1_pt_etacut0", "SISCone5Jet p_{T} vs. GenJets p_{T} - matched OneToOne #DeltaR_{m}<=0.1, 0<= | #eta | <=1.3", 100, 0, 225, 100, 0, 225);
   hRecoVsGen_dRltpt1_eta_etacut0 = new TH2F( "RecoVsGen_dRltpt1_eta_etacut0", "SISCone5Jet #eta vs. GenJets #eta - matched OneToOne #DeltaR_{m}<=0.1, 0<= | #eta | <=1.3", 100, -3, 3, 100, -3, 3 );
   hRecoVsGen_dRltpt1_phi_etacut0 = new TH2F( "RecoVsGen_dRltpt1_phi_etacut0", "SISCone5Jet #phi vs. GenJets #phi - matched OneToOne #DeltaR_{m}<=0.1, 0<= | #eta | <=1.3", 100,  -M_PI, M_PI, 100,  -M_PI, M_PI );
   hRecoVsGen_dRltpt1_et = new TH2F( "RecoVsGen_dRltpt1_et", "SISCone5Jet E_{T} vs. GenJets E_{T} - matched OneToOne #DeltaR_{m}<=0.1, All #eta", 100, 0, 225, 100, 0, 225);
   hRecoVsGen_dRltpt1_pt = new TH2F( "RecoVsGen_dRltpt1_pt", "SISCone5Jet p_{T} vs. GenJets p_{T} - matched OneToOne #DeltaR_{m}<=0.1, All #eta", 100, 0, 225, 100, 0, 225);
   hRecoVsGen_dRltpt1_eta = new TH2F( "RecoVsGen_dRltpt1_eta", "SISCone5Jet #eta vs. GenJets #eta - matched OneToOne #DeltaR_{m}<=0.1, All #eta", 100, -3, 3, 100, -3, 3 );
   hRecoVsGen_dRltpt1_phi = new TH2F( "RecoVsGen_dRltpt1_phi", "SISCone5Jet #phi vs. GenJets #phi - matched OneToOne #DeltaR_{m}<=0.1, All #eta", 100,  -M_PI, M_PI, 100,  -M_PI, M_PI );   
//    hRecoVsGen_dRltpt5_et = new TH2F( "RecoVsGen_dRltpt5_et", "SISCone5Jet E_{T} vs. GenJets E_{T} - matched OneToOne #DeltaR_{m}<=0.5, 0<= | #eta | <=1.3", 100, 0, 225, 100, 0, 225);
//    hRecoVsGen_dRltpt5_pt = new TH2F( "RecoVsGen_dRltpt5_pt", "SISCone5Jet p_{T} vs. GenJets p_{T} - matched OneToOne #DeltaR_{m}<=0.5, 0<= | #eta | <=1.3", 100, 0, 225, 100, 0, 225);
//    hRecoVsGen_dRltpt5_eta = new TH2F( "RecoVsGen_dRltpt5_eta", "SISCone5Jet #eta vs. GenJets #eta - matched OneToOne #DeltaR_{m}<=0.5, 0<= | #eta | <=1.3", 100, -3, 3, 100, -3, 3 );
//    hRecoVsGen_dRltpt5_phi = new TH2F( "RecoVsGen_dRltpt5_phi", "SISCone5Jet #phi vs. GenJets #phi - matched OneToOne #DeltaR_{m}<=0.5, 0<= | #eta | <=1.3", 100,  -M_PI, M_PI, 100,  -M_PI, M_PI );
//    hRecoVsGen_dRlt1_et = new TH2F( "RecoVsGen_dRlt1_et", "SISCone5Jet E_{T} vs. GenJets E_{T} - matched OneToOne #DeltaR_{m}<=1.0, 0<= | #eta | <=1.3", 100, 0, 225, 100, 0, 225);
//    hRecoVsGen_dRlt1_pt = new TH2F( "RecoVsGen_dRlt1_pt", "SISCone5Jet p_{T} vs. GenJets p_{T} - matched OneToOne #DeltaR_{m}<=1.0, 0<= | #eta | <=1.3", 100, 0, 225, 100, 0, 225);
//    hRecoVsGen_dRlt1_eta = new TH2F( "RecoVsGen_dRlt1_eta", "SISCone5Jet #eta vs. GenJets #eta - matched OneToOne #DeltaR_{m}<=1.0, 0<= | #eta | <=1.3", 100, -3, 3, 100, -3, 3 );
//    hRecoVsGen_dRlt1_phi = new TH2F( "RecoVsGen_dRlt1_phi", "SISCone5Jet #phi vs. GenJets #phi - matched OneToOne #DeltaR_{m}<=1.0, 0<= | #eta | <=1.3", 100,  -M_PI, M_PI, 100,  -M_PI, M_PI );
   cout<<"[SC5_PuAnalyzer_range]:: finish beginJob"<<endl;
         return ;
}

// ------------ method called once each job just after ending the event loop  ------------
void 
SC5_PuAnalyzer_range::endJob() {
 //  hOutputFile->cd() ;
//   Double_t limBins3[]  = {10,20,30,40,50,60,70,80,100.0,120.,150.,200};
   Double_t limBins3[]  = {10,25,50,75,100,150,200};
   //{1,5,10,15,20,30,40};
   // {20,30,40,50,60,70,80,100,120,150,200,250,300,350}
   Double_t limBinsOld3[] = {20,30,40,50,60,70,80,90,100,125,150,175,200,250};
  cout<<"[SC5_PuAnalyzer_range::endJob]: just made our limBins"<<endl;
//   hMatchedGenNumEv_Ratio->Divide(hMatchSC5Jets_dRltpt2_et,hAllGenJets_et,1.,1.,"B");
   hMatchedGenGNumEv_Ratio->Divide(hMatchGenJets_dRltpt2_pt,hAllGenJets_pt,1.,1.,"B");
  cout<<"[SC5_PuAnalyzer_range::endJob]: just made hMatchedGenGNumEv_Ratio"<<endl;
   hMatchedGenGNumEv_Ratio_etacut0->Divide(hMatchGenJets_dRltpt2_pt_etacut0,hAllGenJets_pt_etacut0,1.,1.,"B");
  cout<<"[SC5_PuAnalyzer_range::endJob]:going to make hMatchedGenGNumEv_Ratio_dRltpt1 and hMatchedGenGNumEv_Ratio_dRltpt1_etacut0"<<endl;
   hMatchedGenGNumEv_Ratio_dRltpt1->Divide(hMatchGenJets_dRltpt1_pt,hAllGenJets_pt,1.,1.,"B");
   hMatchedGenGNumEv_Ratio_dRltpt1_etacut0->Divide(hMatchGenJets_dRltpt1_pt_etacut0,hAllGenJets_pt_etacut0,1.,1.,"B");
  cout<<"[SC5_PuAnalyzer_range::endJob]:made hMatchedGenGNumEv_Ratio_dRltpt1 and hMatchedGenGNumEv_Ratio_dRltpt1_etacut0, next fake ratios"<<endl;
   hFakeRatio->Divide(hUnMatchedSC5Jets_pt,hAllSC5Jets_pt,1.,1.,"B");
   hFakeRatio_etacut0->Divide(hUnMatchedSC5Jets_pt_etacut0,hAllSC5Jets_pt_etacut0,1.,1.,"B");
   hFakeRatio_etacut1->Divide(hUnMatchedSC5Jets_pt_etacut1,hAllSC5Jets_pt_etacut1,1.,1.,"B");
   cout<<"[SC5_PuAnalyzer_range::endJob]: made FakeRatio plots, next lines are commented out"<<endl;
//   hMatchedGenGNumEv_pt_Ratio->Divide(hMatchGenJets_dRltpt2_pt,hAllGenJets_pt_etacut0,1.,1.,"B");
//  cout<<"[SC5_PuAnalyzer_range::endJob]: just made hMatchedGenGNumEv_pt_Ratio"<<endl;

//   hMatchedCaloNumEv_Ratio->Divide(hMatchSC5Jets_dRltpt2_et,hAllSC5Jets_et,1.,1.,"B");
//   hMatchedGCaloNumEv_Ratio->Divide(hMatchGenJets_dRltpt2_et,hAllSC5Jets_et,1.,1.,"B");

//   hMatchedGenGNumEv_pt_Ratio->Divide(hMatchGenJets_dRltpt2_pt,hAllGenJets_pt,1.,1.,"B");
 // endcap
//   hMatchedGenGNumEv_pt_Ratio_etacut1->Divide(hMatchGenJets_dRltpt2_pt_etacut1,hAllGenJets_pt_etacut1,1.,1.,"B");
  cout<<"[SC5_PuAnalyzer_range::endJob]: about to make hMatchedGenGNumEv_Ratio_etacut1"<<endl;

   hMatchedGenGNumEv_Ratio_etacut1->Divide(hMatchGenJets_dRltpt2_pt_etacut1,hAllGenJets_pt_etacut1,1.,1.,"B"); 
   //--> for no apparent reason this line crashes the program!
  cout<<"[SC5_PuAnalyzer_range::endJob]: did hMatchedGenGNumEv_Ratio_etacut1"<<endl;

  cout<<"[SC5_PuAnalyzer_range::endJob]: about to loop over 6 bins in outputI"<<endl;
  for(unsigned int outputI=0;outputI<6;outputI++){
    pThist[outputI]->Fit("gaus","RIE","",pThist[outputI]->GetMean()-2*pThist[outputI]->GetRMS(),pThist[outputI]->GetMean()+2*pThist[outputI]->GetRMS());
   cout<<"[SC5_PuAnalyzer_range::endJob]: just did gaussian fit for pThist for bin: "<<outputI<<endl;
    const TF1* fit =(TF1*) (pThist[outputI]->GetFunction("gaus"));
    Double_t mean = fit->GetParameter(1);
    Double_t meanErr = fit->GetParError(1);
    Double_t sigma = fit->GetParameter(2);
    Double_t sigmaErr = fit->GetParError(2);
    Double_t x=(limBins3[outputI]+limBins3[outputI+1])/2;
    cout<<"x is "<<x<<" outputI: "<<outputI<<" limBins3[outputI] "<<limBins3[outputI]<<" limBins3[outputI+1] "<<limBins3[outputI+1]<<endl;
//     if(outputI==0){
//     sigmapTrpTm->SetBinContent(ratiopT->GetXaxis()->FindBin(x),0);
//     sigmapTrpTm->SetBinError(ratiopT->GetXaxis()->FindBin(x),0);
//     ratiopT->SetBinContent(ratiopT->GetXaxis()->FindBin(x),-100);
//     ratiopT->SetBinError(ratiopT->GetXaxis()->FindBin(x),1);    
//     } else {
    sigmapTrpTm->SetBinContent(ratiopT->GetXaxis()->FindBin(x),sigma);
    sigmapTrpTm->SetBinError(ratiopT->GetXaxis()->FindBin(x),sigmaErr);
    ratiopT->SetBinContent(ratiopT->GetXaxis()->FindBin(x),mean);
    ratiopT->SetBinError(ratiopT->GetXaxis()->FindBin(x),meanErr);
    cout<<"outputI "<<outputI<<", ratiopT->GetXaxis()->FindBin(x) "<<ratiopT->GetXaxis()->FindBin(x)<<" mean "<<mean<<" meanErr "<<meanErr<<" sigma "<<sigma<<" sigmaErr "<<sigmaErr<<endl;
//    }
//    pThist[outputI]->Write();
    cout<<"[SC5_PuAnalyzer_range::endJob]: Just wrote out pThist for bin: "<<outputI<<endl;

    pThist_dRltpt1[outputI]->Fit("gaus","RIE","",pThist_dRltpt1[outputI]->GetMean()-2*pThist_dRltpt1[outputI]->GetRMS(),pThist_dRltpt1[outputI]->GetMean()+2*pThist_dRltpt1[outputI]->GetRMS());
   cout<<"[SC5_PuAnalyzer_range::endJob]: just did gaussian fit for pThist_dRltpt1 for bin: "<<outputI<<endl;
    const TF1* fit_dRltpt1 =(TF1*) (pThist_dRltpt1[outputI]->GetFunction("gaus"));
    Double_t mean_dRltpt1 = fit_dRltpt1->GetParameter(1);
    Double_t meanErr_dRltpt1 = fit_dRltpt1->GetParError(1);
    Double_t sigma_dRltpt1 = fit_dRltpt1->GetParameter(2);
    Double_t sigmaErr_dRltpt1 = fit_dRltpt1->GetParError(2);
    Double_t x_dRltpt1=(limBins3[outputI]+limBins3[outputI+1])/2;
//         if(outputI==0){
//     sigmapTrpTm_dRltpt1->SetBinContent(ratiopT_dRltpt1->GetXaxis()->FindBin(x_dRltpt1),0);
//     sigmapTrpTm_dRltpt1->SetBinError(ratiopT_dRltpt1->GetXaxis()->FindBin(x_dRltpt1),0);
//     ratiopT_dRltpt1->SetBinContent(ratiopT_dRltpt1->GetXaxis()->FindBin(x_dRltpt1),-100);
//     ratiopT_dRltpt1->SetBinError(ratiopT_dRltpt1->GetXaxis()->FindBin(x_dRltpt1),1);
//     } else {
    sigmapTrpTm_dRltpt1->SetBinContent(ratiopT_dRltpt1->GetXaxis()->FindBin(x_dRltpt1),sigma_dRltpt1);
    sigmapTrpTm_dRltpt1->SetBinError(ratiopT_dRltpt1->GetXaxis()->FindBin(x_dRltpt1),sigmaErr_dRltpt1);
    ratiopT_dRltpt1->SetBinContent(ratiopT_dRltpt1->GetXaxis()->FindBin(x_dRltpt1),mean_dRltpt1);
    ratiopT_dRltpt1->SetBinError(ratiopT_dRltpt1->GetXaxis()->FindBin(x_dRltpt1),meanErr_dRltpt1);
//    }
    
//    pThist_dRltpt1[outputI]->Write();
    cout<<"[SC5_PuAnalyzer_range::endJob]: Just wrote out pThist_dRltpt1 for bin: "<<outputI<<endl;

    pThist_etacut0[outputI]->Fit("gaus","RIE","",pThist_etacut0[outputI]->GetMean()-2*pThist_etacut0[outputI]->GetRMS(),pThist_etacut0[outputI]->GetMean()+2*pThist_etacut0[outputI]->GetRMS());
 
    const TF1* fit_etacut0 =(TF1*) (pThist_etacut0[outputI]->GetFunction("gaus"));
    Double_t mean_etacut0 = fit_etacut0->GetParameter(1);
    Double_t mean_etacut0Err = fit_etacut0->GetParError(1);
    Double_t sigma_etacut0 = fit_etacut0->GetParameter(2);
    Double_t sigma_etacut0Err = fit_etacut0->GetParError(2);
    Double_t x_etacut0=(limBins3[outputI]+limBins3[outputI+1])/2;
//             if(outputI==0){
//     sigmapTrpTm_etacut0->SetBinContent(ratiopT_etacut0->GetXaxis()->FindBin(x_etacut0),0);
//     sigmapTrpTm_etacut0->SetBinError(ratiopT_etacut0->GetXaxis()->FindBin(x_etacut0),0);
//     ratiopT_etacut0->SetBinContent(ratiopT_etacut0->GetXaxis()->FindBin(x_etacut0),-100);
//     ratiopT_etacut0->SetBinError(ratiopT_etacut0->GetXaxis()->FindBin(x_etacut0),1);
//    } else {
    sigmapTrpTm_etacut0->SetBinContent(ratiopT_etacut0->GetXaxis()->FindBin(x_etacut0),sigma_etacut0);
    sigmapTrpTm_etacut0->SetBinError(ratiopT_etacut0->GetXaxis()->FindBin(x_etacut0),sigma_etacut0Err);
    ratiopT_etacut0->SetBinContent(ratiopT_etacut0->GetXaxis()->FindBin(x_etacut0),mean_etacut0);
    ratiopT_etacut0->SetBinError(ratiopT_etacut0->GetXaxis()->FindBin(x_etacut0),mean_etacut0Err);
    cout<<"outputI "<<outputI<<", ratiopT_etacut0->GetXaxis()->FindBin(x) "<<ratiopT_etacut0->GetXaxis()->FindBin(x_etacut0)<<" mean "<<mean_etacut0<<" mean_etacut0Err "<<mean_etacut0Err<<" sigma_etacut0 "<<sigma_etacut0<<" sigma_etacut0Err "<<sigma_etacut0Err<<endl;
//    }

//    pThist_etacut0[outputI]->Write();
//     
//     pThist[outputI]->Fit("gaus","RIE","",pThist[outputI]->GetMean()-2*pThist[outputI]->GetRMS(),pThist[outputI]->GetMean()+2*pThist[outputI]->GetRMS());
//  
//     const TF1* ptfit =(TF1*) (pThist[outputI]->GetFunction("gaus"));
//     Double_t ptmean = ptfit->GetParameter(1);
//     Double_t ptmeanErr = ptfit->GetParError(1);
//     Double_t ptsigma = ptfit->GetParameter(2);
//     Double_t ptsigmaErr = ptfit->GetParError(2);
//     Double_t ptx=(limBins3[outputI]+limBins3[outputI+1])/2;
//     sigmapTrpTm_pt->SetBinContent(ratiopt->GetXaxis()->FindBin(ptx),ptsigma);
//     sigmapTrpTm_pt->SetBinError(ratiopt->GetXaxis()->FindBin(ptx),ptsigmaErr);
//     ratiopt->SetBinContent(ratiopt->GetXaxis()->FindBin(ptx),ptmean);
//     ratiopt->SetBinError(ratiopt->GetXaxis()->FindBin(ptx),ptmeanErr);
//     pThist[outputI]->Write();    

// endcap
    pThist_etacut1[outputI]->Fit("gaus","RIE","",pThist_etacut1[outputI]->GetMean()-2*pThist_etacut1[outputI]->GetRMS(),pThist_etacut1[outputI]->GetMean()+2*pThist_etacut1[outputI]->GetRMS());
 
    const TF1* fit_etacut1 =(TF1*) (pThist_etacut1[outputI]->GetFunction("gaus"));
    Double_t mean_etacut1 = fit_etacut1->GetParameter(1);
    Double_t mean_etacut1Err = fit_etacut1->GetParError(1);
    Double_t sigma_etacut1 = fit_etacut1->GetParameter(2);
    Double_t sigma_etacut1Err = fit_etacut1->GetParError(2);
    Double_t x_etacut1=(limBins3[outputI]+limBins3[outputI+1])/2;
//                 if(outputI==0){
//     sigmapTrpTm_etacut1->SetBinContent(ratiopT_etacut1->GetXaxis()->FindBin(x_etacut1),0);
//     sigmapTrpTm_etacut1->SetBinError(ratiopT_etacut1->GetXaxis()->FindBin(x_etacut1),0);
//     ratiopT_etacut1->SetBinContent(ratiopT_etacut1->GetXaxis()->FindBin(x_etacut1),-100);
//     ratiopT_etacut1->SetBinError(ratiopT_etacut1->GetXaxis()->FindBin(x_etacut1),1);
// 	} else {
    sigmapTrpTm_etacut1->SetBinContent(ratiopT_etacut1->GetXaxis()->FindBin(x_etacut1),sigma_etacut1);
    sigmapTrpTm_etacut1->SetBinError(ratiopT_etacut1->GetXaxis()->FindBin(x_etacut1),sigma_etacut1Err);
    ratiopT_etacut1->SetBinContent(ratiopT_etacut1->GetXaxis()->FindBin(x_etacut1),mean_etacut1);
    ratiopT_etacut1->SetBinError(ratiopT_etacut1->GetXaxis()->FindBin(x_etacut1),mean_etacut1Err);
//    }

//    pThist_etacut1[outputI]->Write();
    
//     pThist_etacut1[outputI]->Fit("gaus","RIE","",pThist_etacut1[outputI]->GetMean()-2*pThist_etacut1[outputI]->GetRMS(),pThist_etacut1[outputI]->GetMean()+2*pThist_etacut1[outputI]->GetRMS());
//  
//     const TF1* ptfit_etacut1 =(TF1*) (pThist_etacut1[outputI]->GetFunction("gaus"));
//     Double_t ptmean_etacut1 = ptfit_etacut1->GetParameter(1);
//     Double_t ptmean_etacut1Err = ptfit_etacut1->GetParError(1);
//     Double_t ptsigma_etacut1 = ptfit_etacut1->GetParameter(2);
//     Double_t ptsigma_etacut1Err = ptfit_etacut1->GetParError(2);
//     Double_t ptx_etacut1=(limBins3[outputI]+limBins3[outputI+1])/2;
//     sigmapTrpTm_pt->SetBinContent(ratiopt_etacut1->GetXaxis()->FindBin(ptx_etacut1),ptsigma_etacut1);
//     sigmapTrpTm_pt->SetBinError(ratiopt_etacut1->GetXaxis()->FindBin(ptx_etacut1),ptsigma_etacut1Err);
//     ratiopt_etacut1->SetBinContent(ratiopt_etacut1->GetXaxis()->FindBin(ptx_etacut1),ptmean_etacut1);
//     ratiopt_etacut1->SetBinError(ratiopt_etacut1->GetXaxis()->FindBin(ptx_etacut1),ptmean_etacut1Err);
//     pThist_etacut1[outputI]->Write(); 
//

// position eta
    etahist[outputI]->Fit("gaus","RIE","",etahist[outputI]->GetMean()-2*etahist[outputI]->GetRMS(),etahist[outputI]->GetMean()+2*etahist[outputI]->GetRMS());
   cout<<"[SC5_PuAnalyzer_range::endJob]: just did gaussian fit for etahist for bin: "<<outputI<<endl;
    const TF1* fiteta =(TF1*) (etahist[outputI]->GetFunction("gaus"));
    Double_t meaneta = fiteta->GetParameter(1);
    Double_t meanetaErr = fiteta->GetParError(1);
    Double_t actual_sigmaeta = fiteta->GetParameter(2);
    Double_t sigmaetaErr = fiteta->GetParError(2);
    Double_t xeta=(limBins3[outputI]+limBins3[outputI+1])/2;
    cout<<"xeta is "<<xeta<<" outputI: "<<outputI<<" limBins3[outputI] "<<limBins3[outputI]<<" limBins3[outputI+1] "<<limBins3[outputI+1]<<endl;
//     if(outputI==0){
//     sigmaeta->SetBinContent(ratioeta->GetXaxis()->FindBin(xeta),0.);
//     sigmaeta->SetBinError(ratioeta->GetXaxis()->FindBin(xeta),0.);
//     ratioeta->SetBinContent(ratioeta->GetXaxis()->FindBin(xeta),-100.);
//     ratioeta->SetBinError(ratioeta->GetXaxis()->FindBin(xeta),1.);    
//     } else {
    sigmaeta->SetBinContent(ratioeta->GetXaxis()->FindBin(xeta),actual_sigmaeta);
    sigmaeta->SetBinError(ratioeta->GetXaxis()->FindBin(xeta),sigmaetaErr);
    ratioeta->SetBinContent(ratioeta->GetXaxis()->FindBin(xeta),meaneta);
    ratioeta->SetBinError(ratioeta->GetXaxis()->FindBin(xeta),meanetaErr);
    cout<<"outputI "<<outputI<<", ratioeta->GetXaxis()->FindBin(xeta) "<<ratioeta->GetXaxis()->FindBin(xeta)<<" meaneta "<<meaneta<<" meanetaErr "<<meanetaErr<<" sigmaeta "<<actual_sigmaeta<<" sigmaetaErr "<<sigmaetaErr<<endl;
//    }
//    etahist[outputI]->Write();
    cout<<"[SC5_PuAnalyzer_range::endJob]: Just wrote out etahist for bin: "<<outputI<<endl;
// barrel
    etahist_etacut0[outputI]->Fit("gaus","RIE","",etahist_etacut0[outputI]->GetMean()-2*etahist_etacut0[outputI]->GetRMS(),etahist_etacut0[outputI]->GetMean()+2*etahist_etacut0[outputI]->GetRMS());
 
    const TF1* fiteta_etacut0 =(TF1*) (etahist_etacut0[outputI]->GetFunction("gaus"));
    Double_t meaneta_etacut0 = fiteta_etacut0->GetParameter(1);
    Double_t meaneta_etacut0Err = fiteta_etacut0->GetParError(1);
    Double_t actual_sigmaeta_etacut0 = fiteta_etacut0->GetParameter(2);
    Double_t sigmaeta_etacut0Err = fiteta_etacut0->GetParError(2);
    Double_t xeta_etacut0=(limBins3[outputI]+limBins3[outputI+1])/2;
//             if(outputI==0){
//     sigmaeta_etacut0->SetBinContent(ratioeta_etacut0->GetXaxis()->FindBin(xeta_etacut0),0);
//     sigmaeta_etacut0->SetBinError(ratioeta_etacut0->GetXaxis()->FindBin(xeta_etacut0),0);
//     ratioeta_etacut0->SetBinContent(ratioeta_etacut0->GetXaxis()->FindBin(xeta_etacut0),-100);
//     ratioeta_etacut0->SetBinError(ratioeta_etacut0->GetXaxis()->FindBin(xeta_etacut0),1);
//    } else {
    sigmaeta_etacut0->SetBinContent(ratioeta_etacut0->GetXaxis()->FindBin(xeta_etacut0),actual_sigmaeta_etacut0);
    sigmaeta_etacut0->SetBinError(ratioeta_etacut0->GetXaxis()->FindBin(xeta_etacut0),sigmaeta_etacut0Err);
    ratioeta_etacut0->SetBinContent(ratioeta_etacut0->GetXaxis()->FindBin(xeta_etacut0),meaneta_etacut0);
    ratioeta_etacut0->SetBinError(ratioeta_etacut0->GetXaxis()->FindBin(xeta_etacut0),meaneta_etacut0Err);
    cout<<"outputI "<<outputI<<", ratioeta_etacut0->GetXaxis()->FindBin(xeta) "<<ratioeta_etacut0->GetXaxis()->FindBin(xeta_etacut0)<<" meaneta "<<meaneta_etacut0<<" meaneta_etacut0Err "<<meaneta_etacut0Err<<" sigmaeta_etacut0 "<<actual_sigmaeta_etacut0<<" sigmaeta_etacut0Err "<<sigmaeta_etacut0Err<<endl;
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
//     sigmaeta_etacut1->SetBinContent(ratioeta_etacut1->GetXaxis()->FindBin(xeta_etacut1),0);
//     sigmaeta_etacut1->SetBinError(ratioeta_etacut1->GetXaxis()->FindBin(xeta_etacut1),0);
//     ratioeta_etacut1->SetBinContent(ratioeta_etacut1->GetXaxis()->FindBin(xeta_etacut1),-100);
//     ratioeta_etacut1->SetBinError(ratioeta_etacut1->GetXaxis()->FindBin(xeta_etacut1),1);
// 	} else {
    sigmaeta_etacut1->SetBinContent(ratioeta_etacut1->GetXaxis()->FindBin(xeta_etacut1),actual_sigmaeta_etacut1);
    sigmaeta_etacut1->SetBinError(ratioeta_etacut1->GetXaxis()->FindBin(xeta_etacut1),sigmaeta_etacut1Err);
    ratioeta_etacut1->SetBinContent(ratioeta_etacut1->GetXaxis()->FindBin(xeta_etacut1),meaneta_etacut1);
    ratioeta_etacut1->SetBinError(ratioeta_etacut1->GetXaxis()->FindBin(xeta_etacut1),meaneta_etacut1Err);
//    }

 //   etahist_etacut1[outputI]->Write();

// position phi
    phihist[outputI]->Fit("gaus","RIE","",phihist[outputI]->GetMean()-2*phihist[outputI]->GetRMS(),phihist[outputI]->GetMean()+2*phihist[outputI]->GetRMS());
   cout<<"[SC5_PuAnalyzer_range::endJob]: just did gaussian fit for phihist for bin: "<<outputI<<endl;
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
    cout<<"[SC5_PuAnalyzer_range::endJob]: Just wrote out phihist for bin: "<<outputI<<endl;
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
    pThistOld[outputIOld]->Fit("gaus","RIE","",pThistOld[outputIOld]->GetMean()-2*pThistOld[outputIOld]->GetRMS(),pThistOld[outputIOld]->GetMean()+2*pThistOld[outputIOld]->GetRMS());
 
    const TF1* fitOld =(TF1*) (pThistOld[outputIOld]->GetFunction("gaus"));
    Double_t meanOld = fitOld->GetParameter(1);
    Double_t meanErrOld = fitOld->GetParError(1);
    Double_t sigmaOld = fitOld->GetParameter(2);
    Double_t sigmaErrOld = fitOld->GetParError(2);
    Double_t xOld=(limBinsOld3[outputIOld]+limBinsOld3[outputIOld+1])/2;
    sigmapTrpTmOld->SetBinContent(ratiopTOld->GetXaxis()->FindBin(xOld),sigmaOld);
    sigmapTrpTmOld->SetBinError(ratiopTOld->GetXaxis()->FindBin(xOld),sigmaErrOld);
    ratiopTOld->SetBinContent(ratiopTOld->GetXaxis()->FindBin(xOld),meanOld);
    ratiopTOld->SetBinError(ratiopTOld->GetXaxis()->FindBin(xOld),meanErrOld);
//    pThistOld[outputIOld]->Write(); 
    
    pThist_dRltpt1Old[outputIOld]->Fit("gaus","RIE","",pThist_dRltpt1Old[outputIOld]->GetMean()-2*pThist_dRltpt1Old[outputIOld]->GetRMS(),pThist_dRltpt1Old[outputIOld]->GetMean()+2*pThist_dRltpt1Old[outputIOld]->GetRMS());
 
    const TF1* fit_dRltpt1Old =(TF1*) (pThist_dRltpt1Old[outputIOld]->GetFunction("gaus"));
    Double_t meanOld_dRltpt1 = fit_dRltpt1Old->GetParameter(1);
    Double_t meanErrOld_dRltpt1 = fit_dRltpt1Old->GetParError(1);
    Double_t sigmaOld_dRltpt1 = fit_dRltpt1Old->GetParameter(2);
    Double_t sigmaErrOld_dRltpt1 = fit_dRltpt1Old->GetParError(2);
    Double_t x_dRltpt1Old=(limBinsOld3[outputIOld]+limBinsOld3[outputIOld+1])/2;
    sigmapTrpTm_dRltpt1Old->SetBinContent(ratiopT_dRltpt1Old->GetXaxis()->FindBin(x_dRltpt1Old),sigmaOld_dRltpt1);
    sigmapTrpTm_dRltpt1Old->SetBinError(ratiopT_dRltpt1Old->GetXaxis()->FindBin(x_dRltpt1Old),sigmaErrOld_dRltpt1);
    ratiopT_dRltpt1Old->SetBinContent(ratiopT_dRltpt1Old->GetXaxis()->FindBin(x_dRltpt1Old),meanOld_dRltpt1);
    ratiopT_dRltpt1Old->SetBinError(ratiopT_dRltpt1Old->GetXaxis()->FindBin(x_dRltpt1Old),meanErrOld_dRltpt1);
//    pThist_dRltpt1Old[outputIOld]->Write();  

// barrel:
    pThist_etacut0Old[outputIOld]->Fit("gaus","RIE","",pThist_etacut0Old[outputIOld]->GetMean()-2*pThist_etacut0Old[outputIOld]->GetRMS(),pThist_etacut0Old[outputIOld]->GetMean()+2*pThist_etacut0Old[outputIOld]->GetRMS());
 
    const TF1* fit_etacut0Old =(TF1*) (pThist_etacut0Old[outputIOld]->GetFunction("gaus"));
    Double_t mean_etacut0Old = fit_etacut0Old->GetParameter(1);
    Double_t mean_etacut0OldErr = fit_etacut0Old->GetParError(1);
    Double_t sigma_etacut0Old = fit_etacut0Old->GetParameter(2);
    Double_t sigma_etacut0OldErr = fit_etacut0Old->GetParError(2);
    Double_t x_etacut0Old=(limBinsOld3[outputIOld]+limBinsOld3[outputIOld+1])/2;
    sigmapTrpTm_etacut0Old->SetBinContent(ratiopT_etacut0Old->GetXaxis()->FindBin(x_etacut0Old),sigma_etacut0Old);
    sigmapTrpTm_etacut0Old->SetBinError(ratiopT_etacut0Old->GetXaxis()->FindBin(x_etacut0Old),sigma_etacut0OldErr);
    ratiopT_etacut0Old->SetBinContent(ratiopT_etacut0Old->GetXaxis()->FindBin(x_etacut0Old),mean_etacut0Old);
    ratiopT_etacut0Old->SetBinError(ratiopT_etacut0Old->GetXaxis()->FindBin(x_etacut0Old),mean_etacut0OldErr);
//    pThist_etacut0Old[outputIOld]->Write();
// endcap:
    pThist_etacut1Old[outputIOld]->Fit("gaus","RIE","",pThist_etacut1Old[outputIOld]->GetMean()-2*pThist_etacut1Old[outputIOld]->GetRMS(),pThist_etacut1Old[outputIOld]->GetMean()+2*pThist_etacut1Old[outputIOld]->GetRMS());
 
    const TF1* fit_etacut1Old =(TF1*) (pThist_etacut1Old[outputIOld]->GetFunction("gaus"));
    Double_t mean_etacut1Old = fit_etacut1Old->GetParameter(1);
    Double_t mean_etacut1OldErr = fit_etacut1Old->GetParError(1);
    Double_t sigma_etacut1Old = fit_etacut1Old->GetParameter(2);
    Double_t sigma_etacut1OldErr = fit_etacut1Old->GetParError(2);
    Double_t x_etacut1Old=(limBinsOld3[outputIOld]+limBinsOld3[outputIOld+1])/2;
    sigmapTrpTm_etacut1Old->SetBinContent(ratiopT_etacut1Old->GetXaxis()->FindBin(x_etacut1Old),sigma_etacut1Old);
    sigmapTrpTm_etacut1Old->SetBinError(ratiopT_etacut1Old->GetXaxis()->FindBin(x_etacut1Old),sigma_etacut1OldErr);
    ratiopT_etacut1Old->SetBinContent(ratiopT_etacut1Old->GetXaxis()->FindBin(x_etacut1Old),mean_etacut1Old);
    ratiopT_etacut1Old->SetBinError(ratiopT_etacut1Old->GetXaxis()->FindBin(x_etacut1Old),mean_etacut1OldErr);
//    pThist_etacut1Old[outputIOld]->Write();
//
//     pThistOld[outputIOld]->Fit("gaus","RIE","",pThistOld[outputIOld]->GetMean()-2*pThistOld[outputIOld]->GetRMS(),pThistOld[outputIOld]->GetMean()+2*pThistOld[outputIOld]->GetRMS());
//  
//     const TF1* ptfitOld =(TF1*) (pThistOld[outputIOld]->GetFunction("gaus"));
//     Double_t ptmeanOld = ptfitOld->GetParameter(1);
//     Double_t ptmeanErrOld = ptfitOld->GetParError(1);
//     Double_t ptsigmaOld = ptfitOld->GetParameter(2);
//     Double_t ptsigmaErrOld = ptfitOld->GetParError(2);
//     Double_t ptxOld=(limBinsOld3[outputIOld]+limBinsOld3[outputIOld+1])/2;
//     sigmapTrpTm_ptOld->SetBinContent(ratioptOld->GetXaxis()->FindBin(ptxOld),ptsigmaOld);
//     sigmapTrpTm_ptOld->SetBinError(ratioptOld->GetXaxis()->FindBin(ptxOld),ptsigmaErrOld);
//     ratioptOld->SetBinContent(ratioptOld->GetXaxis()->FindBin(ptxOld),ptmeanOld);
//     ratioptOld->SetBinError(ratioptOld->GetXaxis()->FindBin(ptxOld),ptmeanErrOld);
//     pThistOld[outputIOld]->Write();     
  }  
//  pTresolution = (TH1F*)sigmapTrpTm->Clone();
  pTresolution->Divide(sigmapTrpTm,ratiopT,1.,1.,"B");
//  pTresolution->SetName("pTresolution");
//  pTresolution->SetTitle("p_{T} Resolution matched OneToOne #DeltaR_{m}<=0.2");
//  pTresolution->GetXaxis()->SetRangeUser(0,225);
  pTresolution->GetXaxis()->SetTitle("p^{MC}_{T}/ #left[GeV#right]");
  pTresolution->GetYaxis()->SetTitle("#sigma#left(p^{reco}_{T}/p^{MC}_{T}#right)_{fit}/<p^{reco}_{T}/p^{MC}_{T}>_{fit}");
//  pTresolution->Write();

  ratiopT->GetXaxis()->SetTitle("p^{MC}_{T} #left[GeV#right]");
  ratiopT->GetYaxis()->SetTitle("p^{reco}_{T}/p^{MC}_{T}");

//  ratiopT->Write();   


  pTresolution_dRltpt1->Divide(sigmapTrpTm_dRltpt1,ratiopT_dRltpt1,1.,1.,"B");
  pTresolution_dRltpt1->GetXaxis()->SetTitle("p^{MC}_{T}/ #left[GeV#right]");
  pTresolution_dRltpt1->GetYaxis()->SetTitle("#sigma#left(p^{reco}_{T}/p^{MC}_{T}#right)_{fit}/<p^{reco}_{T}/p^{MC}_{T}>_{fit}");
//  pTresolution_dRltpt1->Write();

  ratiopT_dRltpt1->GetXaxis()->SetTitle("p^{MC}_{T} #left[GeV#right]");
  ratiopT_dRltpt1->GetYaxis()->SetTitle("p^{reco}_{T}/p^{MC}_{T}");

//  ratiopT_dRltpt1->Write(); 
 
//   pTresolution->Divide(sigmapTrpTm_pt,ratiopt,1.,1.,"B");
//   pTresolution->GetXaxis()->SetTitle("p^{MC}_{T}/ #left[GeV#right]");
//   pTresolution->GetYaxis()->SetTitle("#sigma#left(p^{reco}_{T}/p^{MC}_{T}#right)_{fit}/<p^{reco}_{T}/p^{MC}_{T}>_{fit}");
//   pTresolution->Write();
// 
//   ratiopt->GetXaxis()->SetTitle("p^{MC}_{T} #left[GeV#right]");
//   ratiopt->GetYaxis()->SetTitle("p^{reco}_{T}/p^{MC}_{T}");
// 
//   ratiopt->Write(); 

  pTresolutionOld->Divide(sigmapTrpTmOld,ratiopTOld,1.,1.,"B");
  pTresolutionOld->GetXaxis()->SetTitle("p^{MC}_{T}/ #left[GeV#right]");
  pTresolutionOld->GetYaxis()->SetTitle("#sigma#left(p^{reco}_{T}/p^{MC}_{T}#right)_{fit}/<p^{reco}_{T}/p^{MC}_{T}>_{fit}");
//  pTresolutionOld->Write();

  ratiopTOld->GetXaxis()->SetTitle("p^{MC}_{T} #left[GeV#right]");
  ratiopTOld->GetYaxis()->SetTitle("p^{reco}_{T}/p^{MC}_{T}");

//  ratiopTOld->Write(); 

  pTresolution_dRltpt1Old->Divide(sigmapTrpTm_dRltpt1Old,ratiopT_dRltpt1Old,1.,1.,"B");
  pTresolution_dRltpt1Old->GetXaxis()->SetTitle("p^{MC}_{T}/ #left[GeV#right]");
  pTresolution_dRltpt1Old->GetYaxis()->SetTitle("#sigma#left(p^{reco}_{T}/p^{MC}_{T}#right)_{fit}/<p^{reco}_{T}/p^{MC}_{T}>_{fit}");
//  pTresolution_dRltpt1Old->Write();

  ratiopT_dRltpt1Old->GetXaxis()->SetTitle("p^{MC}_{T} #left[GeV#right]");
  ratiopT_dRltpt1Old->GetYaxis()->SetTitle("p^{reco}_{T}/p^{MC}_{T}");
//  ratiopT_dRltpt1Old->Write();
// barrel:  
  pTresolution_etacut0Old->Divide(sigmapTrpTm_etacut0Old,ratiopT_etacut0Old,1.,1.,"B");
  pTresolution_etacut0Old->GetXaxis()->SetTitle("p^{MC}_{T}/ #left[GeV#right]");
  pTresolution_etacut0Old->GetYaxis()->SetTitle("#sigma#left(p^{reco}_{T}/p^{MC}_{T}#right)_{fit}/<p^{reco}_{T}/p^{MC}_{T}>_{fit}");
//  pTresolution_etacut0Old->Write();

  ratiopT_etacut0Old->GetXaxis()->SetTitle("p^{MC}_{T} #left[GeV#right]");
  ratiopT_etacut0Old->GetYaxis()->SetTitle("p^{reco}_{T}/p^{MC}_{T}");

//  ratiopT_etacut0Old->Write(); 

  pTresolution_etacut0->Divide(sigmapTrpTm_etacut0,ratiopT_etacut0,1.,1.,"B");
  pTresolution_etacut0->GetXaxis()->SetTitle("p^{MC}_{T}/ #left[GeV#right]");
  pTresolution_etacut0->GetYaxis()->SetTitle("#sigma#left(p^{reco}_{T}/p^{MC}_{T}#right)_{fit}/<p^{reco}_{T}/p^{MC}_{T}>_{fit}");
//  pTresolution_etacut0->Write();

  ratiopT_etacut0->GetXaxis()->SetTitle("p^{MC}_{T} #left[GeV#right]");
  ratiopT_etacut0->GetYaxis()->SetTitle("p^{reco}_{T}/p^{MC}_{T}");

//  ratiopT_etacut0->Write(); 
// endcap:
  pTresolution_etacut1Old->Divide(sigmapTrpTm_etacut1Old,ratiopT_etacut1Old,1.,1.,"B");
  pTresolution_etacut1Old->GetXaxis()->SetTitle("p^{MC}_{T}/ #left[GeV#right]");
  pTresolution_etacut1Old->GetYaxis()->SetTitle("#sigma#left(p^{reco}_{T}/p^{MC}_{T}#right)_{fit}/<p^{reco}_{T}/p^{MC}_{T}>_{fit}");
//  pTresolution_etacut1Old->Write();

  ratiopT_etacut1Old->GetXaxis()->SetTitle("p^{MC}_{T} #left[GeV#right]");
  ratiopT_etacut1Old->GetYaxis()->SetTitle("p^{reco}_{T}/p^{MC}_{T}");

//  ratiopT_etacut1Old->Write(); 

  pTresolution_etacut1->Divide(sigmapTrpTm_etacut1,ratiopT_etacut1,1.,1.,"B");
  pTresolution_etacut1->GetXaxis()->SetTitle("p^{MC}_{T}/ #left[GeV#right]");
  pTresolution_etacut1->GetYaxis()->SetTitle("#sigma#left(p^{reco}_{T}/p^{MC}_{T}#right)_{fit}/<p^{reco}_{T}/p^{MC}_{T}>_{fit}");
//  pTresolution_etacut1->Write();

  ratiopT_etacut1->GetXaxis()->SetTitle("p^{MC}_{T} #left[GeV#right]");
  ratiopT_etacut1->GetYaxis()->SetTitle("p^{reco}_{T}/p^{MC}_{T}");

//  ratiopT_etacut1->Write(); 

// position resolution bits:
//  etaResolution->Divide(sigmaeta,ratioeta,1.,1.,"B");
//  etaResolution->SetName("etaResolution");
//  etaResolution->SetTitle("#eta resolution matched OneToOne #DeltaR_{m}<=0.2");
//  etaResolution->GetXaxis()->SetRangeUser(0,225);
//  etaResolution->GetXaxis()->SetTitle("p^{MC}_{T}/ #left[GeV#right]");
//  etaResolution->GetYaxis()->SetTitle("#sigma#left(|#eta(reco)|-|#eta(gen)|#right)_{fit}/<|#eta(reco)|-|#eta(gen)|>_{fit}");
//  etaResolution->Write();

  ratioeta->GetXaxis()->SetTitle("p^{MC}_{T} #left[GeV#right]");
  ratioeta->GetYaxis()->SetTitle("<|#eta(reco)|-|#eta(gen)|>");

//  ratioeta->Write();   

//  etaResolution_etacut0->Divide(sigmaeta_etacut0,ratioeta_etacut0,1.,1.,"B");
//  etaResolution_etacut0->GetXaxis()->SetTitle("p^{MC}_{T}/ #left[GeV#right]");
//  etaResolution_etacut0->GetYaxis()->SetTitle("#sigma#left(|#eta(reco)|-|#eta(gen)|#right)_{fit}/<|#eta(reco)|-|#eta(gen)|>_{fit}");
//  etaResolution_etacut0->Write();

  ratioeta_etacut0->GetXaxis()->SetTitle("p^{MC}_{T} #left[GeV#right]");
  ratioeta_etacut0->GetYaxis()->SetTitle("|#eta(reco)|-|#eta(gen)|");

//  ratioeta_etacut0->Write(); 
  
//  etaResolution_etacut1->Divide(sigmaeta_etacut1,ratioeta_etacut1,1.,1.,"B");
//  etaResolution_etacut1->GetXaxis()->SetTitle("p^{MC}_{T}/ #left[GeV#right]");
//  etaResolution_etacut1->GetYaxis()->SetTitle("#sigma#left(|#eta(reco)|-|#eta(gen)|#right)_{fit}/<|#eta(reco)|-|#eta(gen)|>_{fit}");
//  etaResolution_etacut1->Write();

  ratioeta_etacut1->GetXaxis()->SetTitle("p^{MC}_{T} #left[GeV#right]");
  ratioeta_etacut1->GetYaxis()->SetTitle("|#eta(reco)|-|#eta(gen)|");

//  ratioeta_etacut1->Write(); 
  
//  phiResolution->Divide(sigmaphi,ratioPhi,1.,1.,"B");
//  phiResolution->SetName("phiResolution");
//  phiResolution->SetTitle("#phi resolution matched OneToOne #DeltaR_{m}<=0.2");
//  phiResolution->GetXaxis()->SetRangeUser(0,225);
//  phiResolution->GetXaxis()->SetTitle("p^{MC}_{T}/ #left[GeV#right]");
//  phiResolution->GetYaxis()->SetTitle("#sigma#left(#phi(reco)-#phi(gen)#right)_{fit}/<#phi(reco)-#phi(gen)>_{fit}");
//  phiResolution->Write();

  ratioPhi->GetXaxis()->SetTitle("p^{MC}_{T} #left[GeV#right]");
  ratioPhi->GetYaxis()->SetTitle("#phi(reco)-#phi(gen)");

//  ratioPhi->Write();   

//  phiResolution_etacut0->Divide(sigmaphi_etacut0,ratioPhi_etacut0,1.,1.,"B");
//  phiResolution_etacut0->GetXaxis()->SetTitle("p^{MC}_{T}/ #left[GeV#right]");
//  phiResolution_etacut0->GetYaxis()->SetTitle("#sigma#left(#phi(reco)-#phi(gen)#right)_{fit}/<#phi(reco)-#phi(gen)>_{fit}");
//  phiResolution_etacut0->Write();

  ratioPhi_etacut0->GetXaxis()->SetTitle("p^{MC}_{T} #left[GeV#right]");
  ratioPhi_etacut0->GetYaxis()->SetTitle("#phi(reco)-#phi(gen)");

//  ratioPhi_etacut0->Write(); 
  
//  phiResolution_etacut1->Divide(sigmaphi_etacut1,ratioPhi_etacut1,1.,1.,"B");
//  phiResolution_etacut1->GetXaxis()->SetTitle("p^{MC}_{T}/ #left[GeV#right]");
//  phiResolution_etacut1->GetYaxis()->SetTitle("#sigma#left(#phi(reco)-#phi(gen)#right)_{fit}/<#phi(reco)-#phi(gen)>_{fit}");
//  phiResolution_etacut1->Write();

  ratioPhi_etacut1->GetXaxis()->SetTitle("p^{MC}_{T} #left[GeV#right]");
  ratioPhi_etacut1->GetYaxis()->SetTitle("#phi(reco)-#phi(gen)");

//  ratioPhi_etacut1->Write();   
//   pTresolution_etacut1->Divide(sigmapTrpTm_pt_etacut1,ratiopt_etacut1,1.,1.,"B");
//   pTresolution_etacut1->GetXaxis()->SetTitle("p^{MC}_{T}/ #left[GeV#right]");
//   pTresolution_etacut1->GetYaxis()->SetTitle("#sigma#left(p^{reco}_{T}/p^{MC}_{T}#right)_{fit}/<p^{reco}_{T}/p^{MC}_{T}>_{fit}");
//   pTresolution_etacut1->Write();
// 
//   ratiopt_etacut1->GetXaxis()->SetTitle("p^{MC}_{T} #left[GeV#right]");
//   ratiopt_etacut1->GetYaxis()->SetTitle("p^{reco}_{T}/p^{MC}_{T}");
// 
//   ratiopt_etacut1->Write();   
//
//   pTresolutionOld->Divide(sigmapTrpTm_ptOld,ratioptOld,1.,1.,"B");
//   pTresolutionOld->GetXaxis()->SetTitle("p^{MC}_{T}/ #left[GeV#right]");
//   pTresolutionOld->GetYaxis()->SetTitle("#sigma#left(p^{reco}_{T}/p^{MC}_{T}#right)_{fit}/<p^{reco}_{T}/p^{MC}_{T}>_{fit}");
//   pTresolutionOld->Write();
// 
//   ratioptOld->GetXaxis()->SetTitle("p^{MC}_{T} #left[GeV#right]");
//   ratioptOld->GetYaxis()->SetTitle("p^{reco}_{T}/p^{MC}_{T}");
// 
//   ratioptOld->Write();  
//   hOutputFile->Write() ;
cout<<"[SC5_PuAnalyzer_range]:: start doing Write histos as part of destruction"<<endl;
		 hTotalLenght->Write();
		hdeltaR->Write();
		hdeltaR_etacut0->Write();
		hdeltaR_etacut1->Write();
		ratiopT->Write();
		sigmapTrpTm->Write();
		pTresolution->Write();
		pThist [6]->Write();
 
		ratiopTOld->Write();
		sigmapTrpTmOld->Write();
		pTresolutionOld->Write();
		pThistOld [13]->Write();

		ratiopT_dRltpt1->Write();
		sigmapTrpTm_dRltpt1->Write();
		pTresolution_dRltpt1->Write();
		pThist_dRltpt1 [6]->Write();
		ratiopT_dRltpt1Old->Write();
		sigmapTrpTm_dRltpt1Old->Write();
		pTresolution_dRltpt1Old->Write();
		pThist_dRltpt1Old [13]->Write();
cout<<"[SC5_PuAnalyzer_range]:: Wrote basic histos as part of destruction"<<endl;

 // barrel specific
		ratiopT_etacut0->Write();
		sigmapTrpTm_etacut0->Write();
		pTresolution_etacut0->Write();
		pThist_etacut0 [6]->Write();
 
		ratiopT_etacut0Old->Write();
		sigmapTrpTm_etacut0Old->Write();
		pTresolution_etacut0Old->Write();
		pThist_etacut0Old [13]->Write();
//    
		ratiopT_etacut1->Write();
		sigmapTrpTm_etacut1->Write();
		pTresolution_etacut1->Write();
		pThist_etacut1 [6]->Write();
 
		ratiopT_etacut1Old->Write();
		sigmapTrpTm_etacut1Old->Write();
		pTresolution_etacut1Old->Write();
		pThist_etacut1Old [13]->Write();
//
cout<<"[SC5_PuAnalyzer_range]:: Wrote barrel+endcap histos as part of destruction"<<endl;

// position resolution:
		ratioeta->Write();
//				cout<<"[SC5_PuAnalyzer_range]:: Wrote		ratioeta->Write();histos as part of destruction"<<endl;
		sigmaeta->Write();
//		cout<<"[SC5_PuAnalyzer_range]:: Wrote		sigmaeta->Write();histos as part of destruction"<<endl;
		etahist [6]->Write();
//		cout<<"[SC5_PuAnalyzer_range]:: Wrote		etahist [6]->Write();histos as part of destruction"<<endl;
		ratioPhi->Write();
//		cout<<"[SC5_PuAnalyzer_range]:: Wrote		ratioPhi->Write();histos as part of destruction"<<endl;
		sigmaphi->Write();
//		cout<<"[SC5_PuAnalyzer_range]:: Wrote		sigmaphi->Write();histos as part of destruction"<<endl;
		phihist [6]->Write();
//		cout<<"[SC5_PuAnalyzer_range]:: Wrote		phihist [6]->Write();histos as part of destruction"<<endl;
		ratioeta_etacut0->Write();
//		cout<<"[SC5_PuAnalyzer_range]:: Wrote		ratioeta_etacut0->Write();histos as part of destruction"<<endl;
		sigmaeta_etacut0->Write();
//		cout<<"[SC5_PuAnalyzer_range]:: Wrote		sigmaeta_etacut0->Write();histos as part of destruction"<<endl;
		etahist_etacut0 [6]->Write();    
//		cout<<"[SC5_PuAnalyzer_range]:: Wrote		etahist_etacut0 [6]->Write();    histos as part of destruction"<<endl;
		ratioPhi_etacut0->Write();
//		cout<<"[SC5_PuAnalyzer_range]:: Wrote		ratioPhi_etacut0->Write();histos as part of destruction"<<endl;
		sigmaphi_etacut0->Write();
//		cout<<"[SC5_PuAnalyzer_range]:: Wrote		sigmaphi_etacut0->Write();histos as part of destruction"<<endl;
		phihist_etacut0[6]->Write();
//		cout<<"[SC5_PuAnalyzer_range]:: Wrote		phihist_etacut0[6]->Write();histos as part of destruction"<<endl;
		ratioeta_etacut1->Write();
//		cout<<"[SC5_PuAnalyzer_range]:: Wrote		ratioeta_etacut1->Write();histos as part of destruction"<<endl;
		sigmaeta_etacut1->Write();
//		cout<<"[SC5_PuAnalyzer_range]:: Wrote		sigmaeta_etacut1->Write();histos as part of destruction"<<endl;
		etahist_etacut1 [6]->Write();      
//		cout<<"[SC5_PuAnalyzer_range]:: Wrote		etahist_etacut1 [6]->Write();      histos as part of destruction"<<endl;
		ratioPhi_etacut1->Write();
//		cout<<"[SC5_PuAnalyzer_range]:: Wrote		ratioPhi_etacut1->Write();histos as part of destruction"<<endl;
		sigmaphi_etacut1->Write();
//		cout<<"[SC5_PuAnalyzer_range]:: Wrote		sigmaphi_etacut1->Write();histos as part of destruction"<<endl;
//	    phihist_etacut1[6]->Write();   
//		cout<<"[SC5_PuAnalyzer_range]:: Wrote		phihist_etacut1[6]->Write();   histos as part of destruction"<<endl;
		cout<<"[SC5_PuAnalyzer_range]:: Wrote position histos as part of destruction"<<endl;

// 		ratiopt->Write();
// 		sigmapTrpTm_pt->Write();
// 		pTresolution->Write();
// 		pThist [6]->Write();   
//  
// 		ratiopt_etacut1->Write();
// 		sigmapTrpTm_pt_etacut1->Write();
// 		pTresolution_etacut1->Write();
// 		pThist_etacut1 [6]->Write();   
//     
// 		ratioptOld->Write();
// 		sigmapTrpTm_ptOld->Write();
// 		pTresolutionOld->Write();
//		pThistOld[6]->Write();     
		hSimpleResolution_pt->Write(); // (p_{T} Reco)/(p_{T} Gen) vs. p_{T} Gen  (what Korea group did) 
//    TH2F* 		hSimpleEfficiency_Energy->Write(); // (#matched jets)/(# reco jets) vs. p_{T} Gen  (what Korea group did)
		hAllGenJets_et->Write();
//		hAllGenJets_pt_etacut0->Write();
		hAllGenJets_et_etacut0->Write();

		hAllSC5Jets_et->Write();
		hMatchGenJets_dRltpt2_et->Write();
 		hMatchGenJets_dRltpt1_et->Write();   
		hMatchGenJets_et->Write();
		hMatchSC5Jets_dRltpt2_et->Write();
		hMatchSC5Jets_dRltpt1_et->Write();
		hMatchSC5Jets_et->Write();  
 
		hAllSC5Jets_et_etacut0->Write();
		hMatchGenJets_dRltpt2_et_etacut0->Write();
		hMatchGenJets_dRltpt1_et_etacut0->Write();    
		hMatchGenJets_et_etacut0->Write();
		hMatchSC5Jets_dRltpt2_et_etacut0->Write();
		hMatchSC5Jets_dRltpt1_et_etacut0->Write();    
		hMatchSC5Jets_et_etacut0->Write();  
 		cout<<"[SC5_PuAnalyzer_range]:: Wrote match histos as part of destruction"<<endl;
 
		hAllGenJets_pt->Write();
		cout<<"[SC5_PuAnalyzer_range]:: Wrote hAllGenJets_pt"<<endl;
		hAllSC5Jets_pt->Write();
				cout<<"[SC5_PuAnalyzer_range]:: Wrote hAllSC5Jets_pt"<<endl;
		hMatchGenJets_dRltpt2_pt->Write();
				cout<<"[SC5_PuAnalyzer_range]:: Wrote hAllSC5Jets_pt"<<endl;
		hMatchGenJets_dRltpt1_pt->Write();    
		cout<<"[SC5_PuAnalyzer_range]:: Wrote hMatchGenJets_dRltpt1_pt"<<endl;
		hMatchGenJets_pt->Write();
		cout<<"[SC5_PuAnalyzer_range]:: Wrote hMatchGenJets_pt"<<endl;
		hMatchSC5Jets_dRltpt2_pt->Write();
		cout<<"[SC5_PuAnalyzer_range]:: Wrote hMatchSC5Jets_dRltpt2_pt"<<endl;
		hMatchSC5Jets_dRltpt1_pt->Write();
		cout<<"[SC5_PuAnalyzer_range]:: Wrote hMatchSC5Jets_dRltpt1_pt"<<endl;
		hMatchSC5Jets_pt->Write();  
		cout<<"[SC5_PuAnalyzer_range]:: Wrote hMatchSC5Jets_pt"<<endl;
		hUnMatchedSC5Jets_pt->Write();
		cout<<"[SC5_PuAnalyzer_range]:: Wrote hUnMatchedSC5Jets_pt"<<endl;
		hUnMatchedSC5Jets_pt_etacut0->Write();
		cout<<"[SC5_PuAnalyzer_range]:: Wrote hUnMatchedSC5Jets_pt_etacut0"<<endl;
		hUnMatchedSC5Jets_pt_etacut1->Write();
        cout<<"[SC5_PuAnalyzer_range]:: Wrote hUnMatchedSC5Jets_pt_etacut1"<<endl;
		hUnMatchedSC5Jets_eta->Write();
		cout<<"[SC5_PuAnalyzer_range]:: Wrote hUnMatchedSC5Jets_eta"<<endl;
		hUnMatchedSC5Jets_eta_etacut0->Write();
		cout<<"[SC5_PuAnalyzer_range]:: Wrote hUnMatchedSC5Jets_eta_etacut0"<<endl;
		hUnMatchedSC5Jets_eta_etacut1->Write();
		cout<<"[SC5_PuAnalyzer_range]:: Wrote hUnMatchedSC5Jets_eta_etacut1"<<endl;
//		hUnMatchedSC5Jets_dRltpt2_et->Write();
//		hUnMatchedSC5Jets_dRltpt2_et_etacut0->Write();
//		hUnMatchedSC5Jets_dRltpt2_et_etacut1->Write();
//		hMatchedGenGNumEv_pt_Ratio->Write();

		hMatchGenJets_pt_etacut0->Write();
		cout<<"[SC5_PuAnalyzer_range]:: Wrote hMatchGenJets_pt_etacut0"<<endl;
		hAllSC5Jets_pt_etacut0->Write();
		cout<<"[SC5_PuAnalyzer_range]:: Wrote hAllSC5Jets_pt_etacut0"<<endl;
		hAllGenJets_pt_etacut0->Write();
		cout<<"[SC5_PuAnalyzer_range]:: Wrote hAllGenJets_pt_etacut0"<<endl;
		hMatchGenJets_dRltpt2_pt_etacut0->Write();
		cout<<"[SC5_PuAnalyzer_range]:: Wrote hMatchGenJets_dRltpt2_pt_etacut0"<<endl;
		hMatchSC5Jets_dRltpt2_pt_etacut0->Write();
		cout<<"[SC5_PuAnalyzer_range]:: Wrote hMatchSC5Jets_dRltpt2_pt_etacut0"<<endl;
		hMatchGenJets_dRltpt1_pt_etacut0->Write();
		cout<<"[SC5_PuAnalyzer_range]:: Wrote hMatchGenJets_dRltpt1_pt_etacut0"<<endl;
		hMatchSC5Jets_dRltpt1_pt_etacut0->Write();
		cout<<"[SC5_PuAnalyzer_range]:: Wrote hMatchSC5Jets_dRltpt1_pt_etacut0"<<endl;
		hMatchSC5Jets_pt_etacut0->Write();     
		cout<<"[SC5_PuAnalyzer_range]:: Wrote hMatchSC5Jets_pt_etacut0"<<endl;
//		hMatchedGenGNumEv_pt_Ratio_etacut0->Write();

 // endcap plots
//		hAllGenJets_et_etacut1->Write();
//		cout<<"[SC5_PuAnalyzer_range]:: Wrote hAllGenJets_et_etacut1"<<endl;
//		hAllSC5Jets_et_etacut1->Write();
//		cout<<"[SC5_PuAnalyzer_range]:: Wrote hAllSC5Jets_et_etacut1"<<endl;
		hMatchGenJets_dRltpt2_et_etacut1->Write();
		cout<<"[SC5_PuAnalyzer_range]:: Wrote hMatchGenJets_dRltpt2_et_etacut1"<<endl;
		hMatchGenJets_dRltpt1_et_etacut1->Write();
		cout<<"[SC5_PuAnalyzer_range]:: Wrote hMatchGenJets_dRltpt1_et_etacut1"<<endl;
		hMatchGenJets_et_etacut1->Write();
		cout<<"[SC5_PuAnalyzer_range]:: Wrote hMatchGenJets_et_etacut1"<<endl;
		hMatchSC5Jets_dRltpt2_et_etacut1->Write();
		cout<<"[SC5_PuAnalyzer_range]:: Wrote 	hMatchSC5Jets_dRltpt2_et_etacut1"<<endl;
		hMatchSC5Jets_dRltpt1_et_etacut1->Write();
		cout<<"[SC5_PuAnalyzer_range]:: Wrote hMatchSC5Jets_dRltpt1_et_etacut1"<<endl;
		hMatchSC5Jets_et_etacut1->Write();     
		cout<<"[SC5_PuAnalyzer_range]:: Wrote hMatchSC5Jets_et_etacut1"<<endl;
//		hMatchedGenGNumEv_et_Ratio_etacut1->Write();  
    
 		hAllGenJets_pt_etacut1->Write();
 		cout<<"[SC5_PuAnalyzer_range]:: Wrote hAllGenJets_pt_etacut1"<<endl;
 		hAllSC5Jets_pt_etacut1->Write();
 		cout<<"[SC5_PuAnalyzer_range]:: Wrote hAllSC5Jets_pt_etacut1"<<endl;
 		hMatchGenJets_dRltpt2_pt_etacut1->Write();
 		cout<<"[SC5_PuAnalyzer_range]:: Wrote hMatchGenJets_dRltpt2_pt_etacut1"<<endl;
 		hMatchGenJets_pt_etacut1->Write();
 		cout<<"[SC5_PuAnalyzer_range]:: Wrote hMatchGenJets_pt_etacut1"<<endl;
// 		hMatchSC5Jets_dRltpt2_pt_etacut1->Write();
// 		hMatchSC5Jets_pt_etacut1->Write();     
// 		hMatchedGenGNumEv_pt_Ratio_etacut1->Write();   
  		cout<<"[SC5_PuAnalyzer_range]:: Wrote more match histos as part of destruction"<<endl;
   
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
//		hMatchedGenNumEv_Ratio->Write(); // (# matched SC5 Jets)/(# All GenJets)
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
    
//		hMatchedCaloNumEv_Ratio->Write(); // (# matched SC5 Jets)/(# All SC5 Jets)
//		hMatchedGCaloNumEv_Ratio->Write(); // (# matched GenJets)/(# All SC5 Jets)
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
cout<<"[SC5_PuAnalyzer_range]:: finish doing Write histos as part of destruction"<<endl;
   hOutputFile->Write() ;
// cout<<"[SC5_PuAnalyzer_range]:: going to close File part of destruction"<<endl;

//   hOutputFile->Close() ; 
 cout<<"[SC5_PuAnalyzer_range]:: end destruction"<<endl;

cout<<"[SC5_PuAnalyzer_range]:: finished endJob"<<endl;
   return ;
}

//define this as a plug-in
DEFINE_FWK_MODULE(SC5_PuAnalyzer_range);
