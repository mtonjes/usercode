#include "EventFilter/CastorRawToDigi/interface/ZdcUnpacker.h"
//#include "EventFilter/HcalRawToDigi/interface/HcalDCCHeader.h"
//#include "EventFilter/HcalRawToDigi/interface/HcalHTRData.h"
#include "EventFilter/CastorRawToDigi/interface/CastorCTDCHeader.h"
#include "EventFilter/CastorRawToDigi/interface/CastorTTPUnpacker.h"
#include "EventFilter/CastorRawToDigi/interface/CastorCORData.h"
#include "EventFilter/CastorRawToDigi/interface/CastorUnpacker.h"
#include "DataFormats/HcalDetId/interface/HcalOtherDetId.h"
#include "DataFormats/HcalDigi/interface/HcalQIESample.h"
#include "DataFormats/HcalDigi/interface/ZDCDataFrame.h"
#include "DataFormats/HcalDigi/interface/HcalTriggerPrimitiveSample.h"
#include <iostream>
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include <map>

namespace ZdcUnpacker_impl {
  template <class DigiClass>
  const HcalQIESample* unpack(const HcalQIESample* startPoint, const HcalQIESample* limit, DigiClass& digi, int presamples, const CastorElectronicsId& eid, int startSample, int endSample, int expectedTime, const CastorCORData& hhd) {
    // set parameters
    digi.setPresamples(presamples);
    int fiber=startPoint->fiber();
    int fiberchan=startPoint->fiberChan();
    uint32_t zsmask=hhd.zsBunchMask()>>startSample;
    digi.setZSInfo(hhd.isUnsuppressed(),hhd.wasMarkAndPassZS(fiber,fiberchan),zsmask);

    //   digi.setReadoutIds(eid);
    //   setReadoutIds is missing in  ZdcDataFrame class  digi.setReadoutIds(eid);
    if (expectedTime>=0 && !hhd.isUnsuppressed()) {
      // std::cout << hhd.getFibOrbMsgBCN(fiber) << " " << expectedTime << " fiber="<<fiber<< std::endl;
      digi.setFiberIdleOffset(hhd.getFibOrbMsgBCN(fiber)-expectedTime);
    }
    // what is my sample number?
    int myFiberChan=startPoint->fiberAndChan();
    int ncurr=0,ntaken=0;
    const HcalQIESample* qie_work=startPoint;
    while (qie_work!=limit && qie_work->fiberAndChan()==myFiberChan) {
      if (ncurr>=startSample && ncurr<=endSample) {
        digi.setSample(ntaken,*qie_work);
        ++ntaken;
      }
      ncurr++;
      qie_work++;
    } 
    digi.setSize(ntaken);
    return qie_work;
  }
}


namespace { inline bool isTPGSOI(const HcalTriggerPrimitiveSample& s) {
  return (s.raw()&0x200)!=0;
}
}


ZdcUnpacker::ZdcUnpacker(int sourceIdOffset, int beg, int end) : sourceIdOffset_(sourceIdOffset) , expectedOrbitMessageTime_(-1)
{
  if ( beg >= 0 && beg <= ZDCDataFrame::MAXSAMPLES -1 ) {
    startSample_ = beg;
  } else {
    startSample_ = 0;
  }
  if ( end >= 0 && end <= ZDCDataFrame::MAXSAMPLES -1 && end >= beg ) {
    endSample_ = end;
  } else {
    endSample_ = ZDCDataFrame::MAXSAMPLES -1;
  }
}

//static int slb(const HcalTriggerPrimitiveSample& theSample) { return ((theSample.raw()>>13)&0x7); }
//static int slbChan(const HcalTriggerPrimitiveSample& theSample) { return (theSample.raw()>>11)&0x3; }
//static int slbAndChan(const HcalTriggerPrimitiveSample& theSample) { return (theSample.raw()>>11)&0x1F; }



void ZdcUnpacker::unpack(const FEDRawData& raw, const CastorElectronicsMap& emap,
                         CastorRawCollections& colls, HcalUnpackerReport& report, bool silent) {

  if (raw.size()<16) {
    if (!silent) edm::LogWarning("Invalid Data") << "Empty/invalid DCC data, size = " << raw.size();
    return;
  }

  // get the DCC header
  const CastorCTDCHeader* dccHeader=(const CastorCTDCHeader*)(raw.data());
  //  int dccid=dccHeader->getSourceId()-sourceIdOffset_;
  //  std::cout<<dccid<<std::endl;
  // check the summary status

  // walk through the HTR data...
  CastorCORData htr;
  const unsigned short* daq_first, *daq_last, *tp_first, *tp_last;
  const HcalQIESample* qie_begin, *qie_end, *qie_work;
  //  const HcalTriggerPrimitiveSample *tp_begin, *tp_end, *tp_work;


  ///////////////////////////////////////////
  ///////////ATTEMPT A ZDC MAP///////////////
  ///////////////////////////////////////////
  std::map<CastorElectronicsId,uint32_t> myEMap;

  //PZDC
  /*  myEMap[CastorElectronicsId(0,1,12,22,12,8,1)]=0x54000051;//PZDC EM1
  myEMap[CastorElectronicsId(1,1,12,22,12,8,1)]=0x54000052;//PZDC EM2
  myEMap[CastorElectronicsId(2,1,12,22,12,8,1)]=0x54000053;//PZDC EM3
  myEMap[CastorElectronicsId(0,2,12,22,12,8,1)]=0x54000054;//PZDC EM4
  myEMap[CastorElectronicsId(1,2,12,22,12,8,1)]=0x54000055;//PZDC EM5
  myEMap[CastorElectronicsId(2,2,12,22,12,8,1)]=0x54000061;//PZDC HAD1
  myEMap[CastorElectronicsId(0,3,12,22,12,8,1)]=0x54000062;//PZDC HAD2
  myEMap[CastorElectronicsId(1,3,12,22,12,8,1)]=0x54000063;//PZDC HAD3
  myEMap[CastorElectronicsId(2,3,12,22,12,8,1)]=0x54000064;//PZDC HAD4

  //NZDC
  myEMap[CastorElectronicsId(0,1,13,22,12,8,0)]=0x54000011;//NZDC EM1
  myEMap[CastorElectronicsId(1,1,13,22,12,8,0)]=0x54000012;//NZDC EM2
  myEMap[CastorElectronicsId(2,1,13,22,12,8,0)]=0x54000013;//NZDC EM3
  myEMap[CastorElectronicsId(0,2,13,22,12,8,0)]=0x54000014;//NZDC EM4
  myEMap[CastorElectronicsId(1,2,13,22,12,8,0)]=0x54000015;//NZDC EM5
  myEMap[CastorElectronicsId(2,2,13,22,12,8,0)]=0x54000021;//NZDC HAD1
  myEMap[CastorElectronicsId(0,3,13,22,12,8,0)]=0x54000022;//NZDC HAD2
  myEMap[CastorElectronicsId(1,3,13,22,12,8,0)]=0x54000023;//NZDC HAD3
  myEMap[CastorElectronicsId(2,3,13,22,12,8,0)]=0x54000024;//NZDC HAD4*/


  //PZDC
  myEMap[CastorElectronicsId(0,1,0,3,18,8,1)]=0x54000051;//PZDC EM1
  myEMap[CastorElectronicsId(1,1,0,3,18,8,1)]=0x54000052;//PZDC EM2
  myEMap[CastorElectronicsId(2,1,0,3,18,8,1)]=0x54000053;//PZDC EM3
  myEMap[CastorElectronicsId(0,2,0,3,18,8,1)]=0x54000054;//PZDC EM4
  myEMap[CastorElectronicsId(1,2,0,3,18,8,1)]=0x54000055;//PZDC EM5
  myEMap[CastorElectronicsId(2,2,0,3,18,8,1)]=0x54000061;//PZDC HAD1
  myEMap[CastorElectronicsId(0,3,0,3,18,8,1)]=0x54000062;//PZDC HAD2
  myEMap[CastorElectronicsId(1,3,0,3,18,8,1)]=0x54000063;//PZDC HAD3
  myEMap[CastorElectronicsId(2,3,0,3,18,8,1)]=0x54000064;//PZDC HAD4

  //NZDC
  myEMap[CastorElectronicsId(0,1,1,3,18,8,0)]=0x54000011;//NZDC EM1
  myEMap[CastorElectronicsId(1,1,1,3,18,8,0)]=0x54000012;//NZDC EM2
  myEMap[CastorElectronicsId(2,1,1,3,18,8,0)]=0x54000013;//NZDC EM3
  myEMap[CastorElectronicsId(0,2,1,3,18,8,0)]=0x54000014;//NZDC EM4
  myEMap[CastorElectronicsId(1,2,1,3,18,8,0)]=0x54000015;//NZDC EM5
  myEMap[CastorElectronicsId(2,2,1,3,18,8,0)]=0x54000021;//NZDC HAD1
  myEMap[CastorElectronicsId(0,3,1,3,18,8,0)]=0x54000022;//NZDC HAD2
  myEMap[CastorElectronicsId(1,3,1,3,18,8,0)]=0x54000023;//NZDC HAD3
  myEMap[CastorElectronicsId(2,3,1,3,18,8,0)]=0x54000024;//NZDC HAD4

  //slot is 17
  


  for (int spigot=0; spigot<CastorCTDCHeader::SPIGOT_COUNT; spigot++) {
    if (!dccHeader->getSpigotPresent(spigot)) continue;

    int retval=dccHeader->getSpigotData(spigot,htr,raw.size());
    if (retval!=0) {
      if (retval==-1) {
        if (!silent) edm::LogWarning("Invalid Data") << "Invalid HTR data (data beyond payload size) observed on spigot " << spigot << " of DCC with source id " << dccHeader->getSourceId();
        report.countSpigotFormatError();
      }
      continue;
    }
    // check
    if (dccHeader->getSpigotCRCError(spigot)) {
      if (!silent)
        edm::LogWarning("Invalid Data") << "CRC Error on HTR data observed on spigot " << spigot << " of DCC with source id " << dccHeader->getSourceId();
      report.countSpigotFormatError();
      continue;
    }
    if (!htr.check()) {
      if (!silent)
        edm::LogWarning("Invalid Data") << "Invalid HTR data observed on spigot " << spigot << " of DCC with source id " << dccHeader->getSourceId();
      report.countSpigotFormatError();
      continue;
    }
    if (htr.isHistogramEvent()) {
      if (!silent)
        edm::LogWarning("Invalid Data") << "Histogram data passed to non-histogram unpacker on spigot " << spigot << " of DCC with source id " << dccHeader->getSourceId();
      continue;

    }
    if ((htr.getFirmwareFlavor()&0xE0)==0x80) { // some kind of TTP data
      if (colls.ttp!=0) {

        CastorTTPUnpacker ttpUnpack;
        colls.ttp->push_back(HcalTTPDigi());
        ttpUnpack.unpack(htr,colls.ttp->back());
      } else {
        LogDebug("ZdcUnpackerHcalTechTrigProcessor") << "Skipping data on spigot " << spigot << " of DCC with source id " << dccHeader->getSourceId() << " which is from the TechTrigProcessor (use separate unpacker!)";
      }
      continue;
    }
    if (htr.getFirmwareFlavor()>=0x80) {
      if (!silent) edm::LogWarning("ZdcUnpacker") << "Skipping data on spigot " << spigot << " of DCC with source id " << dccHeader->getSourceId() << " which is of unknown flavor " << htr.getFirmwareFlavor();
      continue;
    }
    // calculate "real" number of presamples
    //int nps=htr.getNPS()-startSample_;

    // get pointers
    htr.dataPointers(&daq_first,&daq_last,&tp_first,&tp_last);
    unsigned int smid=htr.getSubmodule();
    int htr_tb=smid&0x1;
    int htr_slot=(smid>>1)&0x1F;
    int htr_cr=(smid>>6)&0x1F;

    //    tp_begin=(HcalTriggerPrimitiveSample*)tp_first;
    //tp_end=(HcalTriggerPrimitiveSample*)(tp_last+1); // one beyond last..

    /// work through the samples
    //int currFiberChan=0x3F; // invalid fiber+channel...
    //int ncurr=0;
    //bool valid=false;
    //////////////////////////////////////////////
    // bool tpgSOIbitInUse=htr.getFormatVersion()>=3; // version 3 and later
    // bool isHOtpg=htr.getFormatVersion()>=3 && htr.getFirmwareFlavor()==0; // HO is flavor zero
    //int npre=0;
    /*
      Unpack the trigger primitives
    */
    // lookup the right channel
    /*            bool dotp = true;
                  CastorElectronicsId eid(0,1,spigot,dccid);
                  eid.setHTR(htr_cr,htr_slot,htr_tb);
                  DetId did=emap.lookup(eid);
                  if ( did.null() ) dotp = false;
                  HcalZDCDetId id1(did);
                  HcalZDCDetId id(id1.section(),(id1.zside()==0),id1.channel());
                  if ( id1.channel() > 12 ) dotp = false;
                  if ( dotp ) {
                  // std::cout << " tp_first="<< tp_first << " tp_last="<< tp_last<< " tb="<<htr_tb<<" slot="<<htr_slot<<" crate="<<htr_cr<<" dccid="<< dccid<< std::endl;
                  // regular TPs (not HO)
                  for (tp_work=tp_begin; tp_work!=tp_end; tp_work++) {
                  //      std::cout << "raw=0x"<<std::hex<< tp_work->raw()<<std::dec <<std::endl;
                  if (tp_work->raw()==0xFFFF) continue; // filler word
                  if (slbAndChan(*tp_work)!=currFiberChan) { // start new set
                  npre=0;
                  currFiberChan=slbAndChan(*tp_work);

                  // std::cout<< " NEW SET "<<std::endl;
                  //CastorElectronicsId eid(tp_work->slbChan(),tp_work->slb(),spigot,dccid,htr_cr,htr_slot,htr_tb);
                  //DetId did=emap.lookupTrigger(eid);
                  //if (did.null()) {
                  //report.countUnmappedTPDigi(eid);
                  //if (unknownIdsTrig_.find(eid)==unknownIdsTrig_.end()) {
                  //if (!silent) edm::LogWarning("HCAL") << "HcalUnpacker: No trigger primitive match found for electronics id :" << eid;
                  //unknownIdsTrig_.insert(eid);
                  //}
                  //valid=false;
                  //continue;
                  //} else if (did==HcalTrigTowerDetId::Undefined ||
                  //(did.det()==DetId::Hcal && did.subdetId()==0)) {
                  //// known to be unmapped
                  //valid=false;
                  //continue;
                  //}

                  //colls.tpCont->push_back(HcalTriggerPrimitiveDigi(id));
                  // set the various bits
                  //if (!tpgSOIbitInUse) colls.tpCont->back().setPresamples(nps);
                  //colls.tpCont->back().setZSInfo(htr.isUnsuppressed(),htr.wasMarkAndPassZSTP(slb(*tp_work),slbChan(*tp_work)));

                  // no hits recorded for current
                  ncurr=0;
                  valid=true;
                  }
                  // add the word (if within settings or recent firmware [recent firmware ignores startSample/endSample])
                  if (valid && ((tpgSOIbitInUse && ncurr<10) || (ncurr>=startSample_ && ncurr<=endSample_))) {
                  colls.tpCont->back().setSample(colls.tpCont->back().size(),*tp_work);
                  colls.tpCont->back().setSize(colls.tpCont->back().size()+1);
                  }
                  // set presamples,if SOI
                  if (valid && tpgSOIbitInUse && isTPGSOI(*tp_work)) {
                  colls.tpCont->back().setPresamples(ncurr);
                  }
                  ncurr++;
                  npre++;
                  }
                  }*/

    //////////////////////////////////////////////
    qie_begin=(HcalQIESample*)daq_first;
    qie_end=(HcalQIESample*)(daq_last+1); // one beyond last..
    // std::cout<<qie_end<<std::endl;
    /// work through the samples
    //currFiberChan=0x3F; // invalid fiber+channel...
    //ncurr=0;
    //valid=false;
    //int myiter=0;

    for (qie_work=qie_begin; qie_work!=qie_end;qie_work++) {
      if (qie_work->raw()==0xFFFF) {
        qie_work++;
        continue; // filler word
      }
      // always at the beginning ...
      //currFiberChan=qie_work->fiberAndChan();

      // lookup the right channel
      //CastorElectronicsId eid(qie_work->fiberChan(),qie_work->fiber(),spigot,22);
      CastorElectronicsId eid(qie_work->fiberChan(),qie_work->fiber(),spigot,3);
      //  std::cout<<qie_work->fiberChan()<<std::endl;
      eid.setHTR(htr_cr,htr_slot,htr_tb);

      // if (myEMap.find(CastorElectronicsId(qie_work->fiberChan(),qie_work->fiber(),spigot,22,htr_cr,htr_slot,htr_tb))->second > 0)
      //  {
      //  std::cout<<myEMap.find(CastorElectronicsId(qie_work->fiberChan(),qie_work->fiber(),spigot,22,htr_cr,htr_slot,htr_tb))->second<<std::endl;
      //  colls.zdcCont->push_back(ZDCDataFrame(HcalZDCDetId(myEMap.find(CastorElectronicsId(qie_work->fiberChan(),qie_work->fiber(),spigot,22,htr_cr,htr_slot,htr_tb))->second)));
      //qie_work=ZdcUnpacker_impl::unpack<ZDCDataFrame>(qie_work,qie_end,colls.zdcCont->back(),0,CastorElectronicsId(qie_work->fiberChan(),qie_work->fiber(),spigot,22,htr_cr,htr_slot,htr_tb),startSample_,endSample_,expectedOrbitMessageTime_,htr);

      //}

            if (myEMap.find(CastorElectronicsId(qie_work->fiberChan(),qie_work->fiber(),spigot,3,htr_cr,htr_slot,htr_tb))->second > 0)
        {
          //PZDC EM 1
          if(spigot==12 && qie_work->fiberChan()==0 && qie_work->fiber()==1 && htr_tb==1)
            {
              colls.zdcCont->push_back(ZDCDataFrame(HcalZDCDetId(myEMap.find(CastorElectronicsId(qie_work->fiberChan(),qie_work->fiber(),spigot,3,htr_cr,htr_slot,htr_tb))->second)));
              qie_work=ZdcUnpacker_impl::unpack<ZDCDataFrame>(qie_work,qie_end,colls.zdcCont->back(),0,eid,startSample_,endSample_,expectedOrbitMessageTime_,htr);
            }

          //PZDC EM 2
          else if(spigot==12 && qie_work->fiberChan()==1 && qie_work->fiber()==1 && htr_tb==1)
            {

              colls.zdcCont->push_back(ZDCDataFrame(HcalZDCDetId(myEMap.find(CastorElectronicsId(qie_work->fiberChan(),qie_work->fiber(),spigot,3,htr_cr,htr_slot,htr_tb))->second)));
              qie_work=ZdcUnpacker_impl::unpack<ZDCDataFrame>(qie_work,qie_end,colls.zdcCont->back(),0,eid,startSample_,endSample_,expectedOrbitMessageTime_,htr);
            }

          //PZDC EM 3
          else if(spigot==12 && qie_work->fiberChan()==2 && qie_work->fiber()==1 && htr_tb==1)
            {
              colls.zdcCont->push_back(ZDCDataFrame(HcalZDCDetId(myEMap.find(CastorElectronicsId(qie_work->fiberChan(),qie_work->fiber(),spigot,3,htr_cr,htr_slot,htr_tb))->second)));
              qie_work=ZdcUnpacker_impl::unpack<ZDCDataFrame>(qie_work,qie_end,colls.zdcCont->back(),0,eid,startSample_,endSample_,expectedOrbitMessageTime_,htr);
            }

          //PZDC EM 4
          else if(spigot==0 && qie_work->fiberChan()==0 && qie_work->fiber()==2 && htr_tb==1)
            {

              colls.zdcCont->push_back(ZDCDataFrame(HcalZDCDetId(myEMap.find(CastorElectronicsId(qie_work->fiberChan(),qie_work->fiber(),spigot,3,htr_cr,htr_slot,htr_tb))->second)));
              qie_work=ZdcUnpacker_impl::unpack<ZDCDataFrame>(qie_work,qie_end,colls.zdcCont->back(),0,eid,startSample_,endSample_,expectedOrbitMessageTime_,htr);
            }

          //PZDC EM 5
          else if(spigot==0 && qie_work->fiberChan()==1 && qie_work->fiber()==2 && htr_tb==1)
            {
              colls.zdcCont->push_back(ZDCDataFrame(HcalZDCDetId(myEMap.find(CastorElectronicsId(qie_work->fiberChan(),qie_work->fiber(),spigot,3,htr_cr,htr_slot,htr_tb))->second)));
              qie_work=ZdcUnpacker_impl::unpack<ZDCDataFrame>(qie_work,qie_end,colls.zdcCont->back(),0,eid,startSample_,endSample_,expectedOrbitMessageTime_,htr);
            }


          //PZDC HAD 1
          else if(spigot==0 && qie_work->fiberChan()==2 && qie_work->fiber()==2 && htr_tb==1)
            {
              colls.zdcCont->push_back(ZDCDataFrame(HcalZDCDetId(myEMap.find(CastorElectronicsId(qie_work->fiberChan(),qie_work->fiber(),spigot,3,htr_cr,htr_slot,htr_tb))->second)));
              qie_work=ZdcUnpacker_impl::unpack<ZDCDataFrame>(qie_work,qie_end,colls.zdcCont->back(),0,eid,startSample_,endSample_,expectedOrbitMessageTime_,htr);
            }

          //PZDC HAD 2
          else if(spigot==0 && qie_work->fiberChan()==0 && qie_work->fiber()==3 && htr_tb==1)
            {
              colls.zdcCont->push_back(ZDCDataFrame(HcalZDCDetId(myEMap.find(CastorElectronicsId(qie_work->fiberChan(),qie_work->fiber(),spigot,3,htr_cr,htr_slot,htr_tb))->second)));
              qie_work=ZdcUnpacker_impl::unpack<ZDCDataFrame>(qie_work,qie_end,colls.zdcCont->back(),0,eid,startSample_,endSample_,expectedOrbitMessageTime_,htr);
            }

          //PZDC HAD 3
          else if(spigot==0 && qie_work->fiberChan()==1 && qie_work->fiber()==3 && htr_tb==1)
            {
              colls.zdcCont->push_back(ZDCDataFrame(HcalZDCDetId(myEMap.find(CastorElectronicsId(qie_work->fiberChan(),qie_work->fiber(),spigot,3,htr_cr,htr_slot,htr_tb))->second)));
              qie_work=ZdcUnpacker_impl::unpack<ZDCDataFrame>(qie_work,qie_end,colls.zdcCont->back(),0,eid,startSample_,endSample_,expectedOrbitMessageTime_,htr);
            }


          //PZDC HAD 4
		  else if(spigot==0 && qie_work->fiberChan()==2 && qie_work->fiber()==3 && htr_tb==3)
            {
            std::cout<<"its pzdc had 4"<<std::endl;
              colls.zdcCont->push_back(ZDCDataFrame(HcalZDCDetId(myEMap.find(CastorElectronicsId(qie_work->fiberChan(),qie_work->fiber(),spigot,3,htr_cr,htr_slot,htr_tb))->second)));
              qie_work=ZdcUnpacker_impl::unpack<ZDCDataFrame>(qie_work,qie_end,colls.zdcCont->back(),0,eid,startSample_,endSample_,expectedOrbitMessageTime_,htr);
	      }

          //NZDC EM 1
          else if(spigot==1 && qie_work->fiberChan()==0 && qie_work->fiber()==1 && htr_tb==0)
            {
              colls.zdcCont->push_back(ZDCDataFrame(HcalZDCDetId(myEMap.find(CastorElectronicsId(qie_work->fiberChan(),qie_work->fiber(),spigot,3,htr_cr,htr_slot,htr_tb))->second)));
              qie_work=ZdcUnpacker_impl::unpack<ZDCDataFrame>(qie_work,qie_end,colls.zdcCont->back(),0,eid,startSample_,endSample_,expectedOrbitMessageTime_,htr);
            }

          //NZDC EM 2
          else if(spigot==1 && qie_work->fiberChan()==1 && qie_work->fiber()==1 && htr_tb==0)
            {

              colls.zdcCont->push_back(ZDCDataFrame(HcalZDCDetId(myEMap.find(CastorElectronicsId(qie_work->fiberChan(),qie_work->fiber(),spigot,3,htr_cr,htr_slot,htr_tb))->second)));
              qie_work=ZdcUnpacker_impl::unpack<ZDCDataFrame>(qie_work,qie_end,colls.zdcCont->back(),0,eid,startSample_,endSample_,expectedOrbitMessageTime_,htr);
            }

          //NZDC EM 3
          else if(spigot==1 && qie_work->fiberChan()==2 && qie_work->fiber()==1 && htr_tb==0)
            {
              colls.zdcCont->push_back(ZDCDataFrame(HcalZDCDetId(myEMap.find(CastorElectronicsId(qie_work->fiberChan(),qie_work->fiber(),spigot,3,htr_cr,htr_slot,htr_tb))->second)));
              qie_work=ZdcUnpacker_impl::unpack<ZDCDataFrame>(qie_work,qie_end,colls.zdcCont->back(),0,eid,startSample_,endSample_,expectedOrbitMessageTime_,htr);
            }

          //NZDC EM 4
          else if(spigot==1 && qie_work->fiberChan()==0 && qie_work->fiber()==2 && htr_tb==0)
            {

              colls.zdcCont->push_back(ZDCDataFrame(HcalZDCDetId(myEMap.find(CastorElectronicsId(qie_work->fiberChan(),qie_work->fiber(),spigot,3,htr_cr,htr_slot,htr_tb))->second)));
              qie_work=ZdcUnpacker_impl::unpack<ZDCDataFrame>(qie_work,qie_end,colls.zdcCont->back(),0,eid,startSample_,endSample_,expectedOrbitMessageTime_,htr);
            }

          //NZDC EM 5
          else if(spigot==1 && qie_work->fiberChan()==1 && qie_work->fiber()==2 && htr_tb==0)
            {
              colls.zdcCont->push_back(ZDCDataFrame(HcalZDCDetId(myEMap.find(CastorElectronicsId(qie_work->fiberChan(),qie_work->fiber(),spigot,3,htr_cr,htr_slot,htr_tb))->second)));
              qie_work=ZdcUnpacker_impl::unpack<ZDCDataFrame>(qie_work,qie_end,colls.zdcCont->back(),0,eid,startSample_,endSample_,expectedOrbitMessageTime_,htr);
            }


          //NZDC HAD 1
          else if(spigot==1 && qie_work->fiberChan()==2 && qie_work->fiber()==2 && htr_tb==0)
            {
              colls.zdcCont->push_back(ZDCDataFrame(HcalZDCDetId(myEMap.find(CastorElectronicsId(qie_work->fiberChan(),qie_work->fiber(),spigot,3,htr_cr,htr_slot,htr_tb))->second)));
              qie_work=ZdcUnpacker_impl::unpack<ZDCDataFrame>(qie_work,qie_end,colls.zdcCont->back(),0,eid,startSample_,endSample_,expectedOrbitMessageTime_,htr);
            }

          //NZDC HAD 2
          else if(spigot==1 && qie_work->fiberChan()==0 && qie_work->fiber()==3 && htr_tb==0)
            {
              colls.zdcCont->push_back(ZDCDataFrame(HcalZDCDetId(myEMap.find(CastorElectronicsId(qie_work->fiberChan(),qie_work->fiber(),spigot,3,htr_cr,htr_slot,htr_tb))->second)));
              qie_work=ZdcUnpacker_impl::unpack<ZDCDataFrame>(qie_work,qie_end,colls.zdcCont->back(),0,eid,startSample_,endSample_,expectedOrbitMessageTime_,htr);
            }

          //NZDC HAD 3
          else if(spigot==1 && qie_work->fiberChan()==1 && qie_work->fiber()==3 && htr_tb==0)
            {
              colls.zdcCont->push_back(ZDCDataFrame(HcalZDCDetId(myEMap.find(CastorElectronicsId(qie_work->fiberChan(),qie_work->fiber(),spigot,3,htr_cr,htr_slot,htr_tb))->second)));
              qie_work=ZdcUnpacker_impl::unpack<ZDCDataFrame>(qie_work,qie_end,colls.zdcCont->back(),0,eid,startSample_,endSample_,expectedOrbitMessageTime_,htr);
            }


          //NZDC HAD 4
          else if(spigot==1 && qie_work->fiberChan()==2 && qie_work->fiber()==3 && htr_tb==0)
            {

              colls.zdcCont->push_back(ZDCDataFrame(HcalZDCDetId(myEMap.find(CastorElectronicsId(qie_work->fiberChan(),qie_work->fiber(),spigot,3,htr_cr,htr_slot,htr_tb))->second)));
              qie_work=ZdcUnpacker_impl::unpack<ZDCDataFrame>(qie_work,qie_end,colls.zdcCont->back(),0,eid,startSample_,endSample_,expectedOrbitMessageTime_,htr);
            }

        }
    }//end of loop over qies
    //std::cout<<myiter<<std::endl;
  }//end of loop over spigots
}


//  LocalWords:  htr
