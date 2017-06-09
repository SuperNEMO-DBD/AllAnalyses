/*
 * Class        : Electron
 * Description  : Definition of the object representing an electron
 *
 *  Created by Stefano Torre on 09/05/2012.
 */

#include "NemoObjects/Electron.h"
#include <iostream>

//-----------------------------------------------------------------------------
// Constructors and Assignment
//-----------------------------------------------------------------------------

Electron::Electron() :
  hitId_(0), trackId_(0), firstGeigerHit_(0),
  intersectTheFoil_(0), impactRegion_(0),
  vertex_(CLHEP::Hep3Vector(0,0,0)),
  caloIP_(CLHEP::Hep3Vector(0,0,0)),
  measTime_(0), dMeasTime_(0), scintToPMTTime_(0),
  energy_(0), energyLoss_(0), dEnergy_(0), pathLength_(0),
  versionRead_(version_) {
}

Electron::Electron(const Electron& obj) :
  hitId_(obj.hitId_), trackId_(obj.trackId_), firstGeigerHit_(obj.firstGeigerHit_),
  intersectTheFoil_(obj.intersectTheFoil_), impactRegion_(obj.impactRegion_),
  vertex_(obj.vertex_), caloIP_(obj.caloIP_),
  measTime_(obj.measTime_), dMeasTime_(obj.dMeasTime_), 
  scintToPMTTime_(obj.scintToPMTTime_),
  energy_(obj.energy_), energyLoss_(obj.energyLoss_), dEnergy_(obj.dEnergy_), 
  pathLength_(obj.pathLength_),
  versionRead_(versionRead_) {
}

Electron::~Electron() {}

Electron& Electron::operator=(const Electron& obj) {
  if (this != &obj) {
    versionRead_      = obj.versionRead_      ;
    hitId_            = obj.hitId_            ;
    trackId_          = obj.trackId_          ;
    firstGeigerHit_   = obj.firstGeigerHit_   ;
    intersectTheFoil_ = obj.intersectTheFoil_ ;
    impactRegion_     = obj.impactRegion_     ;
    vertex_           = obj.vertex_           ;
    caloIP_           = obj.caloIP_           ;
    measTime_         = obj.measTime_         ;
    dMeasTime_        = obj.dMeasTime_        ;
    scintToPMTTime_   = obj.scintToPMTTime_   ;
    energy_           = obj.energy_           ;
    energyLoss_       = obj.energyLoss_       ;
    dEnergy_          = obj.dEnergy_          ;
    pathLength_       = obj.pathLength_       ;
  }
  return (*this);
}

//-----------------------------------------------------------------------------
// Print and Streaming
//-----------------------------------------------------------------------------
void Electron::print(std::ostream& output) const {
  output
    << " PMT ID             : " << hitId()    << "\n"
    << " Track ID           : " << trackId()  << "\n"
    << " First GG hit ID    : " << firstGeigerHit() << "\n"
    << " Intersect the foil : " << intersectTheFoil() << "\n"
    << " Vertex             : " << vertex() << "\n"
    << " Impact Region      : " << impactRegion() << "\n"
    << " Impact Point       : " << caloIP() << "\n"
    << " Measure Time       : " << measTime() << " +- " << dMeasTime() << "\n"
    << " Theoretical TOF    : " << thTof() << " +- " << dThTof() << "\n"
    << " Scint. to PMT Time : " << scintToPMTTime() << "\n"
    << " Energy             : " << energy() << " +- " << dEnergy() << "\n"
    << " dE/dx              : " << energyLoss() << "\n"
    << " Beta               : " << beta() << " +- " << dBeta() << "\n"
    << " Path length        : " << pathLength() << "\n";
}

std::ostream& operator << (std::ostream& os, const Electron& obj) {
   obj.print(os);
   return os;
}

//-------------------------------------------------------------------------
// Classifiers
//-------------------------------------------------------------------------
std::string Electron::class_name() const {
  return std::string("Electron");
}

//-----------------------------------------------------------------------------
// ROOT Input/Output
//-----------------------------------------------------------------------------
void Electron::Streamer(TBuffer& iobuffer) {
  if (iobuffer.IsReading()) {
    iobuffer >> versionRead_;
    if (versionRead_ == 1) {
      readFromBuffer(iobuffer, versionRead_);
    } else {
      std::cerr << "Electron::Streamer(<isReading>): " 
		<< "Unsupported Electron version while reading"
		<<std::endl;
    }
  } else if (iobuffer.IsWriting()) {
    iobuffer << version_;
    writeToBuffer(iobuffer);
  } else {
    std::cerr << "Electron::Streamer(<unknown action>)" << std::endl;
  }
}

//--------------------------------------------------------------------------
// readFromBuffer function
//      Given a TBuffer that is in input mode, reset my data members to have
//      the values dictated by the data read from the buffer.
//--------------------------------------------------------------------------
void Electron::readFromBuffer(TBuffer& iobuffer, Version_t version) {
  iobuffer >> hitId_            ;
  iobuffer >> trackId_          ;
  iobuffer >> firstGeigerHit_   ;
  iobuffer >> intersectTheFoil_ ;
  iobuffer >> impactRegion_     ;
  double x, y, z;
  iobuffer >> x; iobuffer >> y; iobuffer >> z;
  vertex_ = CLHEP::Hep3Vector(x,y,z);
  iobuffer >> x; iobuffer >> y; iobuffer >> z;
  caloIP_ = CLHEP::Hep3Vector(x,y,z);
  iobuffer >> measTime_         ;
  iobuffer >> dMeasTime_        ;
  iobuffer >> scintToPMTTime_   ;
  iobuffer >> energy_           ;
  iobuffer >> energyLoss_       ;
  iobuffer >> dEnergy_          ;
  iobuffer >> pathLength_       ;
}    

bool Electron::postread(EventRecord *p) {
  return true;
}

//--------------------------------------------------------------------------
// writeToBuffer function
//      Write my data to the given TBuffer
//--------------------------------------------------------------------------
void Electron::writeToBuffer(TBuffer& iobuffer) {
  iobuffer << hitId_            ;
  iobuffer << trackId_          ;
  iobuffer << firstGeigerHit_   ;
  iobuffer << intersectTheFoil_ ;
  iobuffer << impactRegion_     ;
  iobuffer << vertex_.x(); 
  iobuffer << vertex_.y(); 
  iobuffer << vertex_.z();
  iobuffer << caloIP_.x(); 
  iobuffer << caloIP_.y(); 
  iobuffer << caloIP_.z();
  iobuffer << measTime_         ;
  iobuffer << dMeasTime_        ;
  iobuffer << scintToPMTTime_   ;
  iobuffer << energy_           ;
  iobuffer << energyLoss_       ;
  iobuffer << dEnergy_          ;
  iobuffer << pathLength_       ;
}

