//
//  N3Track.cpp
//  SNemoCoreExample
//
//  Created by Stefano Torre on 20/09/11.
//  Copyright 2011 Univesity College London. All rights reserved.
//

#include "NemoObjects/N3Track.h"
#include <iostream>

//-----------------------------------------------------------------------------
// Constructors and Assignment
//-----------------------------------------------------------------------------

N3Track::N3Track() :
TrackHelix(), intersectionOnFoil_(0), indexOfScintillator_(0), impactRegion_(0),
  corruptedGeiger_(false), corruptedCalo_(false),
versionRead_(version_) {
}

N3Track::N3Track(const N3Track& obj) :
TrackHelix(obj),
geigerHitList_(obj.geigerHitList_),
intersectionOnFoil_(obj.intersectionOnFoil_),
directionCosine_(obj.directionCosine_),
intersectionOnCalo_(obj.intersectionOnCalo_),
indexOfScintillator_(obj.indexOfScintillator_),
impactRegion_(obj.impactRegion_),
  corruptedGeiger_(obj.corruptedGeiger_),
  corruptedCalo_(obj.corruptedCalo_),
versionRead_(obj.versionRead_){
    
}

N3Track::~N3Track() {}

N3Track& N3Track::operator=(const N3Track& obj) {
    if (this != &obj) {
        versionRead_         = obj.versionRead_;
	centerOfCurvature_   = obj.centerOfCurvature_;
        radiusOfCurvature_   = obj.radiusOfCurvature_;
        helixPitch_          = obj.helixPitch_;
        sign_                = obj.sign_;
        thetaMin_            = obj.thetaMin_;
        thetaMax_            = obj.thetaMax_;        
        origin_              = obj.origin_;	
        geigerHitList_       = obj.geigerHitList_;
        intersectionOnFoil_  = obj.intersectionOnFoil_;
        directionCosine_     = obj.directionCosine_;
        intersectionOnCalo_  = obj.intersectionOnCalo_;
        indexOfScintillator_ = obj.indexOfScintillator_;
        impactRegion_        = obj.impactRegion_;
	corruptedCalo_       = obj.corruptedCalo_;
	corruptedGeiger_     = obj.corruptedGeiger_;
    }
    return (*this);
}

//-----------------------------------------------------------------------------
// Print and Streaming
//-----------------------------------------------------------------------------
void N3Track::print(std::ostream& output) const {
    output 
      << " Geiger Hits Fitted             : " << geigerHitList()->size() << "\n"
      << " There are corrupted geiger hits: " << corruptedGeiger() << "\n";
    TrackHelix::print(output);

    output
    << " Center of curvature  : (" 
    << centerOfCurvature().x() << "," 
    << centerOfCurvature().y() << "," 
    << centerOfCurvature().z() << ")\n"
    << " Radius od curvatore  : " << radiusOfCurvature() << "\n"
    << " Helix pitch          : " << helixPitch() << "\n"
    << " Origin               : (" 
    << origin().x() << ","  << origin().y() << ","  << origin().z() << ")\n"
    << " Theta min            : " << thetaMin() << "\n"
    << " Theta max            : " << thetaMax() << "\n"
    << " Foil Intersection    : (" 
    << intersectionOnFoil().x() << "," 
    << intersectionOnFoil().y() << "," 
    << intersectionOnFoil().z() << ")\n"
    << " Direction Cosines    : (" 
    << directionCosine().x() << "," << directionCosine().y() << "," 
    << directionCosine().z() << ")\n"
    << " Calorimeter Intersection    : (" 
    << intersectionOnCalo().x() << "," 
    << intersectionOnCalo().y() << "," 
    << intersectionOnCalo().z() << ")\n"    
    << " Calorimeter Block Id : " << indexOfScintillator() << "\n"
    << " Corrupted Calo Id    : " << corruptedCalo() << "\n" 
    << " Impact region        : " << impactRegion() << "\n";
}

std::ostream& operator << (std::ostream& os, const N3Track& obj) {
    obj.print(os);
    return os;
}

//-------------------------------------------------------------------------
// Classifiers
//-------------------------------------------------------------------------
std::string N3Track::class_name() const {
    return std::string("N3Track");
}

//-----------------------------------------------------------------------------
// ROOT Input/Output
//-----------------------------------------------------------------------------
void N3Track::Streamer(TBuffer& iobuffer) {
    if (iobuffer.IsReading()) {
        iobuffer >>versionRead_;
        if (versionRead_ == 1) {
            readFromBuffer(iobuffer, versionRead_);
        } else {
            std::cerr << "N3Track::Streamer(<isReading>): " 
            << "Unsupported N3Track version while reading"
            <<std::endl;
        }
    } else if (iobuffer.IsWriting()) {
        iobuffer << version_;
        writeToBuffer(iobuffer);
    } else {
        std::cerr << "N3Track::Streamer(<unknown action>)" << std::endl;
    }
}

//--------------------------------------------------------------------------
// readFromBuffer function
//      Given a TBuffer that is in input mode, reset my data members to have
//      the values dictated by the data read from the buffer.
//--------------------------------------------------------------------------
void N3Track::readFromBuffer(TBuffer& iobuffer, Version_t version) {
    size_t nHits = 0;
    iobuffer >> nHits;
    for (unsigned int i = 0; i < nHits; ++i) {
        int anId;
        iobuffer >> anId;
        geigerHitList_.push_back(anId);
    }
    
    TrackHelix::Streamer(iobuffer);
    
    double x, y, z;
    iobuffer >> x;
    iobuffer >> y;
    iobuffer >> z;
    intersectionOnFoil_ = CLHEP::Hep3Vector(x,y,z);
    
    iobuffer >> x;
    iobuffer >> y;
    iobuffer >> z;
    directionCosine_    = CLHEP::Hep3Vector(x,y,z);
    
    iobuffer >> x;
    iobuffer >> y;
    iobuffer >> z;
    intersectionOnCalo_ = CLHEP::Hep3Vector(x,y,z);
    
    iobuffer >> indexOfScintillator_;
    iobuffer >> impactRegion_;

    iobuffer >> corruptedCalo_;
    iobuffer >> corruptedGeiger_;
}    

bool N3Track::postread(EventRecord *p) {
    return true;
}

//--------------------------------------------------------------------------
// writeToBuffer function
//      Write my data to the given TBuffer
//--------------------------------------------------------------------------
void N3Track::writeToBuffer(TBuffer& iobuffer) {
    size_t nHits = geigerHitList_.size();
    iobuffer << nHits;
    
    for (unsigned int i = 0; i < nHits; ++i) {
        iobuffer << geigerHitList_.at(i);
    }
    
    TrackHelix::Streamer(iobuffer);
        
    iobuffer << intersectionOnFoil_.x();
    iobuffer << intersectionOnFoil_.y();
    iobuffer << intersectionOnFoil_.z();
    
    iobuffer << directionCosine_.x();
    iobuffer << directionCosine_.y();
    iobuffer << directionCosine_.z();
    
    iobuffer << intersectionOnCalo_.x();
    iobuffer << intersectionOnCalo_.y();
    iobuffer << intersectionOnCalo_.z();
    
    iobuffer << indexOfScintillator_;
    iobuffer << impactRegion_;

    iobuffer << corruptedCalo_;
    iobuffer << corruptedGeiger_;
}


