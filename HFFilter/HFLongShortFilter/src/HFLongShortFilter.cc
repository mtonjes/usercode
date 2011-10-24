// -*- C++ -*-
//
// Package:    HFLongShortFilter
// Class:      HFLongShortFilter
// 
/**\class HFLongShortFilter HFLongShortFilter.cc HFFilter/HFLongShortFilter/src/HFLongShortFilter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  
//         Created:  Sun Oct 23 20:51:27 EDT 2011
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
// My additions
// Rechit collections
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
// flag labels
#include "RecoLocalCalo/HcalRecAlgos/interface/HcalCaloFlagLabels.h"
//
// class declaration
//

class HFLongShortFilter : public edm::EDFilter {
   public:
      explicit HFLongShortFilter(const edm::ParameterSet&);
      ~HFLongShortFilter();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      virtual bool beginRun(edm::Run&, edm::EventSetup const&);
      virtual bool endRun(edm::Run&, edm::EventSetup const&);
      virtual bool beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual bool endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

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
HFLongShortFilter::HFLongShortFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed

}


HFLongShortFilter::~HFLongShortFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
HFLongShortFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   
   edm::Handle<HFRecHitCollection> hf_rechit;
   iEvent.getByLabel("hfreco",  hf_rechit);
   bool EventHasHFLongShortFlag=false;
   
   if (hf_rechit.isValid())
     {
       for (HFRecHitCollection::const_iterator HFiter=hf_rechit->begin(); 
	    HFiter !=hf_rechit->end(); 
	    ++HFiter)
	 { // loop over all hits  
	 
	   if (HFiter->flagField(HcalCaloFlagLabels::HFLongShort))
	     {
           EventHasHFLongShortFlag=true;
	     }
	 }
     }	 
// #ifdef THIS_IS_AN_EVENT_EXAMPLE
//    Handle<ExampleData> pIn;
//    iEvent.getByLabel("example",pIn);
// #endif
// 
// #ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
//    ESHandle<SetupData> pSetup;
//    iSetup.get<SetupRecord>().get(pSetup);
// #endif
   return EventHasHFLongShortFlag;
}

// ------------ method called once each job just before starting event loop  ------------
void 
HFLongShortFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
HFLongShortFilter::endJob() {
}

// ------------ method called when starting to processes a run  ------------
bool 
HFLongShortFilter::beginRun(edm::Run&, edm::EventSetup const&)
{ 
  return true;
}

// ------------ method called when ending the processing of a run  ------------
bool 
HFLongShortFilter::endRun(edm::Run&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when starting to processes a luminosity block  ------------
bool 
HFLongShortFilter::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when ending the processing of a luminosity block  ------------
bool 
HFLongShortFilter::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
HFLongShortFilter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(HFLongShortFilter);
