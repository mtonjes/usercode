#ifndef EVENTFILTER_CASTORRAWTODIGI_CASTORTTPUNPACKER_H
#define EVENTFILTER_CASTORRAWTODIGI_CASTORTTPUNPACKER_H 1

#include "DataFormats/HcalDigi/interface/HcalTTPDigi.h"
#include "EventFilter/CastorRawToDigi/interface/CastorCORData.h"

/** \class CastorTTPUnpacker
  *  
  * \author J. Mans - Minnesota
  */
class CastorTTPUnpacker {
public:
  bool unpack(const CastorCORData& data, HcalTTPDigi& digi);

};
#endif
