//
//  N3TrueVertex.cpp
//
//  Created by Stefano Torre on 19/09/11.
//

#include "NemoObjects/N3TrueVertex.h"
#include <iostream>

//-----------------------------------------------------------------------------
// Constructors and Assignment
//-----------------------------------------------------------------------------

N3TrueVertex::N3TrueVertex() :
position_(CLHEP::Hep3Vector(0,0,0)),
time_(0),
isVirtual_(0),
versionRead_(version_){    
}

N3TrueVertex::N3TrueVertex(const N3TrueVertex& obj) :
position_(obj.position_), time_(obj.time_),
isVirtual_(obj.isVirtual_),
versionRead_(obj.versionRead_) {
}

N3TrueVertex::~N3TrueVertex() {}

N3TrueVertex& N3TrueVertex::operator=(const N3TrueVertex &obj) {
    if (this != &obj) {
        position_                = obj.position_;
        time_                    = obj.time_;
        isVirtual_               = obj.isVirtual_;
        versionRead_             = obj.versionRead_;
    }
    return (*this);
}

//-----------------------------------------------------------------------------
// Print and Streaming
//-----------------------------------------------------------------------------
void N3TrueVertex::print(std::ostream& output) const {
    output 
    << " Position               : (" 
    << position().x() << "," 
    << position().y() << "," 
    << position().z() << ")\n"
    << " Time                   : " << time() << "\n"
    << " Is Virtual             : " << isVirtual() << "\n";
}

std::ostream& operator << (std::ostream& os, const N3TrueVertex& obj) {
    obj.print(os);
    return os;
}

//-------------------------------------------------------------------------
// Classifiers
//-------------------------------------------------------------------------
std::string N3TrueVertex::class_name() const {
    return std::string("N3TrueVertex");
}


//-----------------------------------------------------------------------------
// ROOT Input/Output
//-----------------------------------------------------------------------------
void N3TrueVertex::Streamer(TBuffer& iobuffer) {
    if (iobuffer.IsReading()) {
        iobuffer >>versionRead_;
        if (versionRead_ == 1) {
            readFromBuffer(iobuffer, versionRead_);
        } else {
            std::cerr << "N3TrueVertex::Streamer(<isReading>): " 
            << "Unsupported N3TrueVertex version while reading"
            <<std::endl;
        }
    } else if (iobuffer.IsWriting()) {
        iobuffer << version_;
        writeToBuffer(iobuffer);
    } else {
        std::cerr << "N3TrueVertex::Streamer(<unknown action>)" << std::endl;
    }
}

//--------------------------------------------------------------------------
// readFromBuffer function
//      Given a TBuffer that is in input mode, reset my data members to have
//      the values dictated by the data read from the buffer.
//--------------------------------------------------------------------------
void N3TrueVertex::readFromBuffer(TBuffer& iobuffer, Version_t version) {
    double x, y, z;
    iobuffer >> x;
    iobuffer >> y;
    iobuffer >> z;
    position_ = CLHEP::Hep3Vector(x,y,z);
    iobuffer >> time_;
    iobuffer >> isVirtual_;
}    

bool N3TrueVertex::postread(EventRecord *p) {
    return true;
}

//--------------------------------------------------------------------------
// writeToBuffer function
//      Write my data to the given TBuffer
//--------------------------------------------------------------------------
void N3TrueVertex::writeToBuffer(TBuffer& iobuffer) {
    iobuffer << position_.x();
    iobuffer << position_.y();
    iobuffer << position_.z();
    iobuffer << time_;
    iobuffer << isVirtual_;
}


