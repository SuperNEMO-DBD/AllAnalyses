/*
 * Class        : Gamma
 * Description  : Definition of the object representing an electron
 *
 *  Created by Stefano Torre on 09/05/2012.
 */

#include "NemoObjects/Gamma.h"
#include <iostream>

//-----------------------------------------------------------------------------
// Constructors and Assignment
//-----------------------------------------------------------------------------

Gamma::Gamma() :
  rawHitId_(0), calibHitId_(0), hitPosition_(CLHEP::Hep3Vector(0,0,0)),
  measTime_(0), dMeasTime_(0), geomError_(0),
  energy_(0), dEnergy_(0), dPathLength_(0), blockType_(0),
  width_(0), height_(0), thickness_(0), scintToPMTTime_(0),
  versionRead_(version_) {
}

Gamma::Gamma(const Gamma& obj) :
  rawHitId_(obj.rawHitId_), calibHitId_(obj.calibHitId_), hitPosition_(obj.hitPosition_), measTime_(obj.measTime_), 
  dMeasTime_(obj.dMeasTime_), energy_(obj.energy_), dEnergy_(obj.dEnergy_), geomError_(obj.geomError_), 
  dPathLength_(obj.dPathLength_), blockType_(obj.blockType_), width_(obj.width_),
  height_(obj.height_), thickness_(obj.thickness_), scintToPMTTime_(obj.scintToPMTTime_),
  versionRead_(versionRead_) {
}

Gamma::~Gamma() {}

Gamma& Gamma::operator=(const Gamma& obj) {
  if (this != &obj) {
    versionRead_      = obj.versionRead_      ;
    rawHitId_         = obj.rawHitId_            ;
    calibHitId_       = obj.calibHitId_            ;
    hitPosition_      = obj.hitPosition_           ;
    measTime_         = obj.measTime_              ;
    dMeasTime_        = obj.dMeasTime_             ;
    energy_           = obj.energy_           ;
    dEnergy_          = obj.dEnergy_          ;
    dPathLength_      = obj.dPathLength_      ;
    geomError_        = obj.geomError_        ;
    thickness_        = obj.thickness_        ; 
    width_            = obj.width_            ;
    height_           = obj.height_           ;
    scintToPMTTime_   = obj.scintToPMTTime_   ;
    blockType_        = obj.blockType_   ;
  }
  return (*this);
}

//-----------------------------------------------------------------------------
// Print and Streaming
//-----------------------------------------------------------------------------
void Gamma::print(std::ostream& output) const {
  output
    << " raw calo hit ID    : " << rawHitId()    << "\n"
    << " calib calo hit ID  : " << calibHitId()    << "\n"
    << " Hit Position       : " << hitPosition() << "\n"
    << " Measure Time       : " << measTime() << " +- " << dMeasTime() << "\n"
    << " Energy             : " << energy() << " +- " << dEnergy() << "\n"
    << " block type         : " << blockType() << "\n"
    << " block thickness    : " << thickness() << "\n"
    << " block width        : " << blockWidth() << "\n"
    << " block height       : " << blockHeight()<<" \n"
    << " 2D path length err : " << geomError()<<" \n"
    << " time scint_face->PMT : " << scintToPMTTime() ;
}

std::ostream& operator << (std::ostream& os, const Gamma& obj) {
   obj.print(os);
   return os;
}

//-------------------------------------------------------------------------
// Classifiers
//-------------------------------------------------------------------------
std::string Gamma::class_name() const {
  return std::string("Gamma");
}

//-----------------------------------------------------------------------------
// ROOT Input/Output
//-----------------------------------------------------------------------------
void Gamma::Streamer(TBuffer& iobuffer) {
  if (iobuffer.IsReading()) {
    iobuffer >> versionRead_;
    if (versionRead_ == 1) {
      readFromBuffer(iobuffer, versionRead_);
    } else {
      std::cerr << "Gamma::Streamer(<isReading>): " 
		<< "Unsupported Gamma version while reading"
		<<std::endl;
    }
  } else if (iobuffer.IsWriting()) {
    iobuffer << version_;
    writeToBuffer(iobuffer);
  } else {
    std::cerr << "Gamma::Streamer(<unknown action>)" << std::endl;
  }
}

//--------------------------------------------------------------------------
// readFromBuffer function
//      Given a TBuffer that is in input mode, reset my data members to have
//      the values dictated by the data read from the buffer.
//--------------------------------------------------------------------------
void Gamma::readFromBuffer(TBuffer& iobuffer, Version_t version) {
  iobuffer >> rawHitId_            ;
  iobuffer >> calibHitId_            ;
  double x, y, z;
  iobuffer >> x; iobuffer >> y; iobuffer >> z;
  hitPosition_ = CLHEP::Hep3Vector(x,y,z);
  iobuffer >> measTime_         ;
  iobuffer >> dMeasTime_        ;
  iobuffer >> energy_           ;
  iobuffer >> dEnergy_          ;
  iobuffer >> dPathLength_      ;
  iobuffer >> geomError_        ;
  iobuffer >> width_            ; 
  iobuffer >> thickness_        ;
  iobuffer >> height_           ;
  iobuffer >> scintToPMTTime_   ;
  iobuffer >> blockType_   ;
}    

bool Gamma::postread(EventRecord *p) {
  return true;
}

//--------------------------------------------------------------------------
// writeToBuffer function
//      Write my data to the given TBuffer
//--------------------------------------------------------------------------
void Gamma::writeToBuffer(TBuffer& iobuffer) {
  iobuffer << rawHitId_            ;
  iobuffer << calibHitId_            ;
  iobuffer << hitPosition_.x(); 
  iobuffer << hitPosition_.y(); 
  iobuffer << hitPosition_.z();
  iobuffer << measTime_         ;
  iobuffer << dMeasTime_        ;
  iobuffer << energy_           ;
  iobuffer << dEnergy_          ;
  iobuffer << dPathLength_      ;
  iobuffer << geomError_        ;
  iobuffer << width_            ;
  iobuffer << thickness_        ; 
  iobuffer << height_           ;
  iobuffer << scintToPMTTime_   ;
  iobuffer << blockType_        ;
}

