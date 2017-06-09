/*
 * Class        : N3TrueCalorimeterHit
 * Description  : Definition of the object containing the data of the Geiger hit
 *                after the readout
 *
 *  Created by Stefano Torre on 31/12/11.
 */

#include "NemoObjects/N3TrueCalorimeterHit.h"
#include <iostream>

//-----------------------------------------------------------------------------
// Constructors and Assignment
//-----------------------------------------------------------------------------

N3TrueCalorimeterHit::N3TrueCalorimeterHit() :
blockType_(0),
blockModule_(0),
blockSide_(0),
blockColumn_(0),
blockRow_(0),
hitPosition_(CLHEP::Hep3Vector(0,0,0)),
hitTime_(0),
energy_(0),
versionRead_(version_) {
}

N3TrueCalorimeterHit::N3TrueCalorimeterHit(const N3TrueCalorimeterHit& obj) :
blockType_(obj.blockType_),
blockModule_(obj.blockModule_),
blockSide_(obj.blockSide_),
blockColumn_(obj.blockColumn_),
blockRow_(obj.blockRow_),
hitPosition_(obj.hitPosition_),
hitTime_(obj.hitTime_),
energy_(obj.energy_),
versionRead_(obj.versionRead_){
    
}

N3TrueCalorimeterHit::~N3TrueCalorimeterHit() {}

N3TrueCalorimeterHit& N3TrueCalorimeterHit::operator=(const N3TrueCalorimeterHit& obj) {
    if (this != &obj) {
        versionRead_    = obj.versionRead_;
        blockType_      = obj.blockType_;
        blockModule_    = obj.blockModule_;
        blockSide_      = obj.blockSide_;
        blockColumn_    = obj.blockColumn_;
        blockRow_       = obj.blockRow_;
        hitPosition_    = obj.hitPosition_;
        hitTime_        = obj.hitTime_;
        energy_         = obj.energy_;
    }
    return (*this);
}

//-----------------------------------------------------------------------------
// Print and Streaming
//-----------------------------------------------------------------------------
void N3TrueCalorimeterHit::print(std::ostream& output) const {
    output 
    << " BlockType       : " << blockType() << "\n"
    << " BlockModule     : " << blockModule() << "\n"
    << " BlockSide       : " << blockSide() << "\n"
    << " BlockRow        : " << blockRow() << "\n"
    << " CellColumn      : " << blockColumn() << "\n"
    << " (x,y,z)         : (" 
    << hitPosition().x() << "," 
    << hitPosition().y() << "," 
    << hitPosition().z() << ")\n"
    << " t               : " << hitTime() << "\n"
    << " energy          : " << energy() << "\n";
}

std::ostream& operator << (std::ostream& os, const N3TrueCalorimeterHit& obj) {
    obj.print(os);
    return os;
}

//-------------------------------------------------------------------------
// Classifiers
//-------------------------------------------------------------------------
std::string N3TrueCalorimeterHit::class_name() const {
    return std::string("N3TrueCalorimeterHit");
}

//-----------------------------------------------------------------------------
// ROOT Input/Output
//-----------------------------------------------------------------------------
void N3TrueCalorimeterHit::Streamer(TBuffer& iobuffer) {
    if (iobuffer.IsReading()) {
        iobuffer >>versionRead_;
        if (versionRead_ == 1) {
            readFromBuffer(iobuffer, versionRead_);
        } else {
            std::cerr << "N3TrueCalorimeterHit::Streamer(<isReading>): " 
            << "Unsupported N3TrueCalorimeterHit version while reading"
            <<std::endl;
        }
    } else if (iobuffer.IsWriting()) {
        iobuffer << version_;
        writeToBuffer(iobuffer);
    } else {
        std::cerr << "N3TrueCalorimeterHit::Streamer(<unknown action>)" << std::endl;
    }
}

//--------------------------------------------------------------------------
// readFromBuffer function
//      Given a TBuffer that is in input mode, reset my data members to have
//      the values dictated by the data read from the buffer.
//--------------------------------------------------------------------------
void N3TrueCalorimeterHit::readFromBuffer(TBuffer& iobuffer, Version_t version) {
    iobuffer >> blockType_;
    iobuffer >> blockModule_;
    iobuffer >> blockColumn_;
    iobuffer >> blockRow_;
    iobuffer >> blockSide_;
    double x, y, z;
    iobuffer >> x;
    iobuffer >> y;
    iobuffer >> z;
    hitPosition_ = CLHEP::Hep3Vector(x,y,z);
    iobuffer >> hitTime_;
    iobuffer >> energy_;
}    

bool N3TrueCalorimeterHit::postread(EventRecord *p) {
    return true;
}

//--------------------------------------------------------------------------
// writeToBuffer function
//      Write my data to the given TBuffer
//--------------------------------------------------------------------------
void N3TrueCalorimeterHit::writeToBuffer(TBuffer& iobuffer) {
    iobuffer << blockType_;
    iobuffer << blockModule_;
    iobuffer << blockColumn_;
    iobuffer << blockRow_;
    iobuffer << blockSide_;
    iobuffer << hitPosition_.x();
    iobuffer << hitPosition_.y();
    iobuffer << hitPosition_.z();
    iobuffer << hitTime_;
    iobuffer << energy_;
}


