/*
 * Class        : N3GeigerHit
 * Description  : Definition of the object containing the data of the Geiger hit
 *                after the readout
 *
 *  Created by Stefano Torre on 02/07/11.
 *  Copyright 2011 Univesity College London. All rights reserved.
 */

#include "NemoObjects/N3GeigerHit.h"
#include <iostream>

//-----------------------------------------------------------------------------
// Constructors and Assignment
//-----------------------------------------------------------------------------

N3GeigerHit::N3GeigerHit() :
status_(0), sectorNumber_(0), side_(0), layer_(0), cellNumber_(0), 
fastTdcContent_(0), slowTdcContent_(0), bottomTdcContent_(0), topTdcContent_(0),
z_(0), zError_(0), anodeInformation_(0), weightReciprocal_(0), 
anodePosition_(CLHEP::Hep3Vector(0,0,0)),
versionRead_(version_) {
    
}

N3GeigerHit::N3GeigerHit(const N3GeigerHit& obj) :
status_(obj.status_), sectorNumber_(obj.sectorNumber_),
side_(obj.side_), layer_(obj.layer_), cellNumber_(obj.cellNumber_),
fastTdcContent_(obj.fastTdcContent_), slowTdcContent_(obj.slowTdcContent_),
bottomTdcContent_(obj.bottomTdcContent_), topTdcContent_(obj.topTdcContent_),
z_(obj.z_), zError_(obj.zError_), anodeInformation_(obj.anodeInformation_),
weightReciprocal_(obj.weightReciprocal_), anodePosition_(obj.anodePosition_),
versionRead_(obj.versionRead_){
    
}

N3GeigerHit::~N3GeigerHit() {}

N3GeigerHit& N3GeigerHit::operator=(const N3GeigerHit& obj) {
    if (this != &obj) {
        versionRead_        = obj.versionRead_;
        status_             = obj.status_;
        sectorNumber_       = obj.sectorNumber_;
        side_               = obj.side_;
        layer_              = obj.layer_;
        cellNumber_         = obj.cellNumber_;
        fastTdcContent_     = obj.fastTdcContent_;
        slowTdcContent_     = obj.slowTdcContent_;
        bottomTdcContent_   = obj.bottomTdcContent_;
        topTdcContent_      = obj.topTdcContent_;
        z_                  = obj.z_;
        zError_             = obj.zError_;
        anodeInformation_   = obj.anodeInformation_;
        weightReciprocal_   = obj.weightReciprocal_;
        anodePosition_      = obj.anodePosition_;
    }
    return (*this);
}

//-----------------------------------------------------------------------------
// Print and Streaming
//-----------------------------------------------------------------------------
void N3GeigerHit::print(std::ostream& output) const {
    output 
    << " Sector Number          : " << sectorNumber() << "\n"
    << " Side                   : " << side() << "\n"
    << " Layer                  : " << layer() << "\n"
    << " Cell Number            : " << cellNumber() << "\n"
    << " Status                 : " << status() << "\n"
    << " (x,y) of anode         : (" 
    << anodePosition().x() << "," << anodePosition().y() << ")\n"
    << " Fast TDC content       : " << fastTdcContent() << "\n"
    << " Slow TDC content       : " << slowTdcContent() << "\n"
    << " Bottom TDC content     : " << bottomTdcContent() << "\n"
    << " Top TDC content        : " << topTdcContent() << "\n"
    << " Drift time             : " << driftDistance() << "\n"
    << " Weigth of circle fit   : " << weightReciprocal() << "\n"
    << " z of hit               : " << z() << "+-" << zError() << "\n";

}

std::ostream& operator << (std::ostream& os, const N3GeigerHit& obj) {
    obj.print(os);
    return os;
}

bool N3GeigerHit::isPrompt() const {
  // the anode information produced by NEMOR corresponds to a drift 
  // distance if the the fast TDC has content betwen 220 and 307 
  // corresponting to 4.4us and 6.15us.
  // In the case the slowTDC started after the stopA then the content 
  // of the first 12bit of that TDC is not equal to the content of the fastTDC
  //
  // the code below follows the implementation in rootana

  // s.torre 27/07/2012 amend using the code from NEMOR as a reference
  // bool goodFastTdc = (fastTdcContent() >= 0 && fastTdcContent() <= 307);
  // long fastTdcBitsInSlowTdcCounter = slowTdcContent() % 4096;
  // bool consistenFastAndSlowTdcs = 
  // (fastTdcBitsInSlowTdcCounter == fastTdcContent());
  // return (goodFastTdc && (slowTdcContent() == 0 || !consistenFastAndSlowTdcs));

  // bool result = false;
  // if (slowTdcContent() == 0) {
  //   if (fastTdcContent() > 0 and fastTdcContent() <= 307) {
  //     result = true;
  //   }
  // } else {
  //   if (fastTdcContent() != (slowTdcContent() & 0xfff)) {
  //     if (fastTdcContent() > 0 and fastTdcContent() <= 307) {
  // 	result = true;
  //     }
  //   }
  // }

  return (status() == 1);
}

bool N3GeigerHit::isDelayed() const {
  // if the hit is delayed botht he fast and slow TDC are started after the 
  // stop-A signal and therefore the content of the first 12 bits of the slow 
  // TDC is the same as the content of the fast TDC 
  // long fastTdcBitsInSlowTdcCounter = slowTdcContent() % 4096;
  // bool consistenFastAndSlowTdcs = 
  // (fastTdcBitsInSlowTdcCounter == fastTdcContent());
    
  // return (slowTdcContent() != 0 && consistenFastAndSlowTdcs);
  // bool result = false;
  // if (fastTdcContent() == 0) {
  //   if (slowTdcContent() != 0) {
  //     result = true;
  //   } 
  // } else {
  //   if ( fastTdcContent() == slowTdcContent() & 0xfff ) {
  // 	result = true;
  //   }
  // }

  return (status() == 10);
}


bool N3GeigerHit::isNoise() const {
    return !isPrompt() && !isDelayed();
}

double N3GeigerHit::driftDistance() const {
    return (isPrompt()) ? anodeInformation_ : 0;
}

double N3GeigerHit::alphaTime() const {
    return (isDelayed()) ? anodeInformation_ : 0;
}

double N3GeigerHit::anodeInformation() const {
  return anodeInformation_;
}

//-------------------------------------------------------------------------
// Classifiers
//-------------------------------------------------------------------------
std::string N3GeigerHit::class_name() const {
    return std::string("N3GeigerHit");
}

//-----------------------------------------------------------------------------
// ROOT Input/Output
//-----------------------------------------------------------------------------
void N3GeigerHit::Streamer(TBuffer& iobuffer) {
    if (iobuffer.IsReading()) {
        iobuffer >>versionRead_;
        if (versionRead_ == 1) {
            readFromBuffer(iobuffer, versionRead_);
        } else {
            std::cerr << "N3GeigerHit::Streamer(<isReading>): " 
            << "Unsupported N3GeigerHit version while reading"
            <<std::endl;
        }
    } else if (iobuffer.IsWriting()) {
        iobuffer << version_;
        writeToBuffer(iobuffer);
    } else {
        std::cerr << "N3GeigerHit::Streamer(<unknown action>)" << std::endl;
    }
}

//--------------------------------------------------------------------------
// readFromBuffer function
//      Given a TBuffer that is in input mode, reset my data members to have
//      the values dictated by the data read from the buffer.
//--------------------------------------------------------------------------
void N3GeigerHit::readFromBuffer(TBuffer& iobuffer, Version_t version) {
    iobuffer >> status_;
    iobuffer >> sectorNumber_;
    iobuffer >> side_;
    iobuffer >> layer_;
    iobuffer >> cellNumber_;
    iobuffer >> fastTdcContent_;
    iobuffer >> slowTdcContent_;
    iobuffer >> bottomTdcContent_;
    iobuffer >> topTdcContent_;
    iobuffer >> z_;
    iobuffer >> zError_;
    iobuffer >> anodeInformation_;
    iobuffer >> weightReciprocal_;
    double x,y;
    iobuffer >> x; iobuffer >> y; 
    anodePosition_ = CLHEP::Hep3Vector(x,y,0);
}    

bool N3GeigerHit::postread(EventRecord *p) {
    return true;
}

//--------------------------------------------------------------------------
// writeToBuffer function
//      Write my data to the given TBuffer
//--------------------------------------------------------------------------
void N3GeigerHit::writeToBuffer(TBuffer& iobuffer) {
    iobuffer << status_;
    iobuffer << sectorNumber_;
    iobuffer << side_;
    iobuffer << layer_;
    iobuffer << cellNumber_;
    iobuffer << fastTdcContent_;
    iobuffer << slowTdcContent_;
    iobuffer << bottomTdcContent_;
    iobuffer << topTdcContent_;
    iobuffer << z_;
    iobuffer << zError_;
    iobuffer << anodeInformation_;
    iobuffer << weightReciprocal_;
    iobuffer << anodePosition_.x();
    iobuffer << anodePosition_.y();
}


