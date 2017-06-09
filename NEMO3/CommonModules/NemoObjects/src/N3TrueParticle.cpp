//
//  N3TrueParticle.cpp
//
//  Created by Stefano Torre on 19/09/11.
//

#include "NemoObjects/N3TrueParticle.h"
#include <iostream>

//-----------------------------------------------------------------------------
// Constructors and Assignment
//-----------------------------------------------------------------------------

N3TrueParticle::N3TrueParticle() :
momentum_(CLHEP::Hep3Vector(0,0,0)),
generationTime_(0),
indexOfAttachedVertex_(0),
geantParticleId_(0),
entryPointInCalorimeter_(CLHEP::Hep3Vector(0,0,0)),
addressOfFirstHit_(0), numberOfGeigerHits_(0),
versionRead_(version_){    
}

N3TrueParticle::N3TrueParticle(const N3TrueParticle& obj) :
momentum_(obj.momentum_), generationTime_(obj.generationTime_),
indexOfAttachedVertex_(obj.indexOfAttachedVertex_),
geantParticleId_(obj.geantParticleId_),
entryPointInCalorimeter_(obj.entryPointInCalorimeter_),
addressOfFirstHit_(obj.addressOfFirstHit_),
numberOfGeigerHits_(obj.numberOfGeigerHits_),
versionRead_(obj.versionRead_) {
}

N3TrueParticle::~N3TrueParticle() {}

N3TrueParticle& N3TrueParticle::operator=(const N3TrueParticle &obj) {
    if (this != &obj) {
        momentum_                = obj.momentum_;
        generationTime_          = obj.generationTime_;
        indexOfAttachedVertex_   = obj.indexOfAttachedVertex_;
        geantParticleId_         = obj.geantParticleId_;
        entryPointInCalorimeter_ = obj.entryPointInCalorimeter_;
        addressOfFirstHit_       = obj.addressOfFirstHit_;
        numberOfGeigerHits_      = obj.numberOfGeigerHits_;
        versionRead_             = obj.versionRead_;
    }
    return (*this);
}

//-----------------------------------------------------------------------------
// Print and Streaming
//-----------------------------------------------------------------------------
void N3TrueParticle::print(std::ostream& output) const {
    output 
    << " Momentum               : (" 
    << momentum().x() << "," 
    << momentum().y() << "," 
    << momentum().z() << ")\n"
    << " Time of Generation     : " << generationTime() << "\n"
    << " Index of Attached Vtx  : " << indexOfAttachedVertex() << "\n"
    << " GEANT Particle Id      : " << geantParticleId() << "\n"
    << " Entry point in calo    : (" 
    << entryPointInCalorimeter().x() << "," 
    << entryPointInCalorimeter().y() << "," 
    << entryPointInCalorimeter().z() << ")\n";
}

std::ostream& operator << (std::ostream& os, const N3TrueParticle& obj) {
    obj.print(os);
    return os;
}

//-------------------------------------------------------------------------
// Classifiers
//-------------------------------------------------------------------------
std::string N3TrueParticle::class_name() const {
    return std::string("N3TrueParticle");
}


//-----------------------------------------------------------------------------
// ROOT Input/Output
//-----------------------------------------------------------------------------
void N3TrueParticle::Streamer(TBuffer& iobuffer) {
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
void N3TrueParticle::readFromBuffer(TBuffer& iobuffer, Version_t version) {
    double x, y, z;
    iobuffer >> x;
    iobuffer >> y;
    iobuffer >> z;
    momentum_ = CLHEP::Hep3Vector(x,y,z);
    iobuffer >> generationTime_;
    iobuffer >> indexOfAttachedVertex_;
    iobuffer >> geantParticleId_;
    iobuffer >> x;
    iobuffer >> y;
    iobuffer >> z;
    entryPointInCalorimeter_ = CLHEP::Hep3Vector(x,y,z);
    iobuffer >> addressOfFirstHit_;
    iobuffer >> numberOfGeigerHits_;
}    

bool N3TrueParticle::postread(EventRecord *p) {
    return true;
}

//--------------------------------------------------------------------------
// writeToBuffer function
//      Write my data to the given TBuffer
//--------------------------------------------------------------------------
void N3TrueParticle::writeToBuffer(TBuffer& iobuffer) {
    iobuffer << momentum_.x();
    iobuffer << momentum_.y();
    iobuffer << momentum_.z();
    iobuffer << generationTime_;
    iobuffer << indexOfAttachedVertex_;
    iobuffer << geantParticleId_;
    iobuffer << entryPointInCalorimeter_.x();
    iobuffer << entryPointInCalorimeter_.y();
    iobuffer << entryPointInCalorimeter_.z();
    iobuffer << addressOfFirstHit_;
    iobuffer << numberOfGeigerHits_;
}


