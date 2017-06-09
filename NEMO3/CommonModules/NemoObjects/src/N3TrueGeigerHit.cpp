/*
 * Class        : N3TrueGeigerHit
 * Description  : Definition of the object containing the data of the Geiger hit
 *                after the readout
 *
 *  Created by Stefano Torre on 02/07/11.
 */

#include "NemoObjects/N3TrueGeigerHit.h"
#include <iostream>

//-----------------------------------------------------------------------------
// Constructors and Assignment
//-----------------------------------------------------------------------------

N3TrueGeigerHit::N3TrueGeigerHit() :
cellSide_(0),
cellColumn_(0),
cellLayer_(0),
xOfAnodeWire_(0),
yOfAnodeWire_(0),
hitPosition_(CLHEP::Hep3Vector(0,0,0)),
hitTime_(0),
versionRead_(version_) {
}

N3TrueGeigerHit::N3TrueGeigerHit(const N3TrueGeigerHit& obj) :
cellSide_(obj.cellSide_),
cellColumn_(obj.cellColumn_),
cellLayer_(obj.cellLayer_),
xOfAnodeWire_(obj.xOfAnodeWire_),
yOfAnodeWire_(obj.yOfAnodeWire_),
hitPosition_(obj.hitPosition_),
hitTime_(obj.hitTime_),
versionRead_(obj.versionRead_){
    
}

N3TrueGeigerHit::~N3TrueGeigerHit() {}

N3TrueGeigerHit& N3TrueGeigerHit::operator=(const N3TrueGeigerHit& obj) {
    if (this != &obj) {
        versionRead_    = obj.versionRead_;
        cellSide_       = obj.cellSide_;
        cellColumn_     = obj.cellColumn_;
        cellLayer_      = obj.cellLayer_;
        xOfAnodeWire_   = obj.xOfAnodeWire_;
        yOfAnodeWire_   = obj.yOfAnodeWire_;
        hitPosition_    = obj.hitPosition_;
        hitTime_        = obj.hitTime_;
    }
    return (*this);
}

//-----------------------------------------------------------------------------
// Print and Streaming
//-----------------------------------------------------------------------------
void N3TrueGeigerHit::print(std::ostream& output) const {
    output 
    << " CellSide        : " << cellSide() << "\n"
    << " CellLayer       : " << cellLayer() << "\n"
    << " CellColumn      : " << cellColumn() << "\n"
    << " (x,y,z)         : (" 
    << hitPosition().x() << "," 
    << hitPosition().y() << "," 
    << hitPosition().z() << ")\n"
    << " t               : " << hitTime() << "\n";
}

std::ostream& operator << (std::ostream& os, const N3TrueGeigerHit& obj) {
    obj.print(os);
    return os;
}

//-------------------------------------------------------------------------
// Classifiers
//-------------------------------------------------------------------------
std::string N3TrueGeigerHit::class_name() const {
    return std::string("N3TrueGeigerHit");
}

//-----------------------------------------------------------------------------
// ROOT Input/Output
//-----------------------------------------------------------------------------
void N3TrueGeigerHit::Streamer(TBuffer& iobuffer) {
    if (iobuffer.IsReading()) {
        iobuffer >>versionRead_;
        if (versionRead_ == 1) {
            readFromBuffer(iobuffer, versionRead_);
        } else {
            std::cerr << "N3TrueGeigerHit::Streamer(<isReading>): " 
            << "Unsupported N3TrueGeigerHit version while reading"
            <<std::endl;
        }
    } else if (iobuffer.IsWriting()) {
        iobuffer << version_;
        writeToBuffer(iobuffer);
    } else {
        std::cerr << "N3TrueGeigerHit::Streamer(<unknown action>)" << std::endl;
    }
}

//--------------------------------------------------------------------------
// readFromBuffer function
//      Given a TBuffer that is in input mode, reset my data members to have
//      the values dictated by the data read from the buffer.
//--------------------------------------------------------------------------
void N3TrueGeigerHit::readFromBuffer(TBuffer& iobuffer, Version_t version) {
    iobuffer >> cellColumn_;
    iobuffer >> cellLayer_;
    iobuffer >> cellSide_;
    iobuffer >> xOfAnodeWire_;
    iobuffer >> yOfAnodeWire_;
    double x, y, z;
    iobuffer >> x;
    iobuffer >> y;
    iobuffer >> z;
    hitPosition_ = CLHEP::Hep3Vector(x,y,z);
    iobuffer >> hitTime_;
}    

bool N3TrueGeigerHit::postread(EventRecord *p) {
    return true;
}

//--------------------------------------------------------------------------
// writeToBuffer function
//      Write my data to the given TBuffer
//--------------------------------------------------------------------------
void N3TrueGeigerHit::writeToBuffer(TBuffer& iobuffer) {
    iobuffer << cellColumn_;
    iobuffer << cellLayer_;
    iobuffer << cellSide_;
    iobuffer << xOfAnodeWire_;
    iobuffer << yOfAnodeWire_;
    iobuffer << hitPosition_.x();
    iobuffer << hitPosition_.y();
    iobuffer << hitPosition_.z();
    iobuffer << hitTime_;
}


