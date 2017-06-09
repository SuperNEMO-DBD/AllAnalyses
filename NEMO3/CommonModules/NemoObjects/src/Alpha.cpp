/*
 * Class        : Alpha
 * Description  : Definition of the object representing an electron
 *
 *  Created by Stefano Torre on 09/05/2012.
 */

#include "NemoObjects/Alpha.h"
#include <iostream>

//-----------------------------------------------------------------------------
// Constructors and Assignment
//-----------------------------------------------------------------------------

Alpha::Alpha() :
  geigerHitList_(0), trackId_(-1), nDelayedHits_(-1), time_(-1), side_(-1),
  lowestLayer_(-1), maxDelayedTimeDiff_(-1),
  nearFoil_(false), foilClosestHitId_(-1),  foilFurthestHitId_(-1),
  foilClosestHitVector_(CLHEP::Hep3Vector(0,0,0)),
  foilFurthestHitVector_(CLHEP::Hep3Vector(0,0,0)),
  nearWire_(false), wireClosestHitId_(-1), wireFurthestHitId_(-1),
  wireClosestHitVector_(CLHEP::Hep3Vector(0,0,0)),
  wireFurthestHitVector_(CLHEP::Hep3Vector(0,0,0)),
  foilVertex_(CLHEP::Hep3Vector(0,0,0)), trackVector_(CLHEP::Hep3Vector(0,0,0)),
  versionRead_(version_) {
}

Alpha::Alpha(const Alpha& obj) :
  geigerHitList_(obj.geigerHitList_), trackId_(obj.trackId_),
  nDelayedHits_(obj.nDelayedHits_),  time_(obj.time_), side_(obj.side_),
  lowestLayer_(obj.lowestLayer_), maxDelayedTimeDiff_(obj.maxDelayedTimeDiff_),
  nearFoil_(obj.nearFoil_), foilClosestHitId_(obj.foilClosestHitId_),
  foilFurthestHitId_(obj.foilFurthestHitId_), foilClosestHitVector_(obj.foilClosestHitVector_),
  foilFurthestHitVector_(obj.foilFurthestHitVector_),
  nearWire_(obj.nearWire_), wireClosestHitId_(obj.wireClosestHitId_),
  wireFurthestHitId_(obj.wireFurthestHitId_), wireClosestHitVector_(obj.wireClosestHitVector_),
  wireFurthestHitVector_(obj.wireFurthestHitVector_),
  foilVertex_(obj.foilVertex_), trackVector_(obj.trackVector_),
  versionRead_(versionRead_) {
}

Alpha::~Alpha() {}

Alpha& Alpha::operator=(const Alpha& obj) {
  if (this != &obj) {
    versionRead_           = obj.versionRead_;
    geigerHitList_         = obj.geigerHitList_;
    trackId_               = obj.trackId_;
    nDelayedHits_          = obj.nDelayedHits_;
    time_                  = obj.time_;
    side_                  = obj.side_;
    lowestLayer_           = obj.lowestLayer_;
    maxDelayedTimeDiff_    = obj.maxDelayedTimeDiff_;
    nearFoil_              = obj.nearFoil_;
    foilClosestHitId_      = obj.foilClosestHitId_;
    foilFurthestHitId_     = obj.foilFurthestHitId_;
    foilClosestHitVector_  = obj.foilClosestHitVector_;
    foilFurthestHitVector_ = obj.foilFurthestHitVector_;
    nearWire_              = obj.nearWire_;
    wireClosestHitId_      = obj.wireClosestHitId_;
    wireFurthestHitId_     = obj.wireFurthestHitId_;
    wireClosestHitVector_  = obj.wireClosestHitVector_;
    wireFurthestHitVector_ = obj.wireFurthestHitVector_;
    foilVertex_            = obj.foilVertex_;
    trackVector_           = obj.trackVector_;
  }
  return (*this);
}

//-----------------------------------------------------------------------------
// Print and Streaming
//-----------------------------------------------------------------------------
void Alpha::print(std::ostream& output) const {
  output
    << " Track ID                 : " << trackId()    << "\n"
    << " Num Delayed Hits         : " << nDelayedHits() << "\n"
    << " Time of decay            : " << time() << "\n"
    << " Side                     : " << side() << "\n"
    << " Lowest Layer Hit         : " << lowestLayer() << "\n"
    << " Max Time Diff            : " << maxDelayedTimeDiff() << "\n"
    << " Cluster near foil        : " << nearFoil() << "\n"
    << " Closest foil hit ID      : " << foilClosestHitId() << "\n"
    << " Furthest foil hit ID     : " << foilFurthestHitId() << "\n"
    << " Closest foil hit vector  : " << foilClosestHitVector() << "\n"
    << " Furthest foil hit vector : " << foilFurthestHitVector() << "\n"
    << " Cluster near wire        : " << nearWire() << "\n"
    << " Closest wire hit ID      : " << wireClosestHitId() << "\n"
    << " Furthest wire hit ID     : " << wireFurthestHitId() << "\n"
    << " Closest wire hit vector  : " << wireClosestHitVector() << "\n"
    << " Furthest wire hit vector : " << wireFurthestHitVector() << "\n"
    << " Track-foil intersection  : " << foilVertex() << "\n"
    << " Track vector             : " << trackVector() << "\n";
}

std::ostream& operator << (std::ostream& os, const Alpha& obj) {
   obj.print(os);
   return os;
}

//-------------------------------------------------------------------------
// Classifiers
//-------------------------------------------------------------------------
std::string Alpha::class_name() const {
  return std::string("Alpha");
}

//-----------------------------------------------------------------------------
// ROOT Input/Output
//-----------------------------------------------------------------------------
void Alpha::Streamer(TBuffer& iobuffer) {
  if (iobuffer.IsReading()) {
    iobuffer >> versionRead_;
    if (versionRead_ == 1) {
      readFromBuffer(iobuffer, versionRead_);
    } else {
      std::cerr << "Alpha::Streamer(<isReading>): " 
		<< "Unsupported Alpha version while reading"
		<<std::endl;
    }
  } else if (iobuffer.IsWriting()) {
    iobuffer << version_;
    writeToBuffer(iobuffer);
  } else {
    std::cerr << "Alpha::Streamer(<unknown action>)" << std::endl;
  }
}

//--------------------------------------------------------------------------
// readFromBuffer function
//      Given a TBuffer that is in input mode, reset my data members to have
//      the values dictated by the data read from the buffer.
//--------------------------------------------------------------------------
void Alpha::readFromBuffer(TBuffer& iobuffer, Version_t version) {
  int entries;
  iobuffer >> entries;
  for (int i = 0; i  < entries; ++i) {
    int entry;
    iobuffer >> entry;
    geigerHitList_.push_back(entry);
  }
  iobuffer >> trackId_;
  iobuffer >> nDelayedHits_;
  iobuffer >> time_; 
  iobuffer >> side_;
  iobuffer >> lowestLayer_;
  iobuffer >> maxDelayedTimeDiff_;
  iobuffer >> nearFoil_;
  iobuffer >> foilClosestHitId_;
  iobuffer >> foilFurthestHitId_;
  double x,y,z;
  iobuffer >> x; iobuffer >> y; iobuffer >> z;
  foilClosestHitVector_ = CLHEP::Hep3Vector(x,y,z);
  iobuffer >> x; iobuffer >> y; iobuffer >> z;
  foilFurthestHitVector_ = CLHEP::Hep3Vector(x,y,z);
  iobuffer >> nearWire_;
  iobuffer >> wireClosestHitId_;
  iobuffer >> wireFurthestHitId_;
  iobuffer >> x; iobuffer >> y; iobuffer >> z;
  wireClosestHitVector_ = CLHEP::Hep3Vector(x,y,z);
  iobuffer >> x; iobuffer >> y; iobuffer >> z;
  wireFurthestHitVector_ = CLHEP::Hep3Vector(x,y,z);
  iobuffer >> x; iobuffer >> y; iobuffer >> z;
  foilVertex_ = CLHEP::Hep3Vector(x,y,z);
  iobuffer >> x; iobuffer >> y; iobuffer >> z;
  trackVector_ = CLHEP::Hep3Vector(x,y,z);

}    

bool Alpha::postread(EventRecord *p) {
  return true;
}

//--------------------------------------------------------------------------
// writeToBuffer function
//      Write my data to the given TBuffer
//--------------------------------------------------------------------------
void Alpha::writeToBuffer(TBuffer& iobuffer) {
  iobuffer << geigerHitList_.size();
  for (int i = 0; i < geigerHitList_.size(); ++i) {
    iobuffer << geigerHitList_.at(i);
  }
  iobuffer << trackId_;
  iobuffer << nDelayedHits_;
  iobuffer << time_;
  iobuffer << side_;
  iobuffer << lowestLayer_;
  iobuffer << maxDelayedTimeDiff_;
  iobuffer << nearFoil_;
  iobuffer << foilClosestHitId_;
  iobuffer << foilFurthestHitId_;
  iobuffer << foilClosestHitVector_.x();
  iobuffer << foilClosestHitVector_.y();
  iobuffer << foilClosestHitVector_.z();
  iobuffer << foilFurthestHitVector_.x();
  iobuffer << foilFurthestHitVector_.y();
  iobuffer << foilFurthestHitVector_.z();
  iobuffer << nearWire_;
  iobuffer << wireClosestHitId_;
  iobuffer << wireFurthestHitId_;
  iobuffer << wireClosestHitVector_.x();
  iobuffer << wireClosestHitVector_.y();
  iobuffer << wireClosestHitVector_.z();
  iobuffer << wireFurthestHitVector_.x();
  iobuffer << wireFurthestHitVector_.y();
  iobuffer << wireFurthestHitVector_.z();
  iobuffer << foilVertex_.x();
  iobuffer << foilVertex_.y();
  iobuffer << foilVertex_.z();
  iobuffer << trackVector_.x();
  iobuffer << trackVector_.y();
  iobuffer << trackVector_.z();
}

bool Alpha::intersectTheFoil() const {
  if (foilVertex_.mag() > 0){
    return true;
  } else {
    return false;
  }
}

double Alpha::lengthFromFoil() const {
  return (nDelayedHits_ == 1) ? foilClosestHitVector_.mag() : trackVector_.mag();
}
