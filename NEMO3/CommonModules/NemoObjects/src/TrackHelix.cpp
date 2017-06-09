//
//  TrackHelix.cpp
//
//  Created by Stefano Torre on 15/02/12.
//

#include <iostream>
#include "NemoObjects/TrackHelix.h"
#include "CLHEP/Vector/TwoVector.h"

#define _USE_MATH_DEFINES
#include <cmath>
//-----------------------------------------------------------------------------
// Constructors and Assignment
//-----------------------------------------------------------------------------

TrackHelix::TrackHelix(double x, double y, double z, double r, 
		       double h, double c) :
centerOfCurvature_(CLHEP::Hep3Vector(x,y,z)), radiusOfCurvature_(r), 
helixPitch_(h), sign_(c), 
thetaMin_(0), thetaMax_(0),
origin_(CLHEP::Hep3Vector(r, 0, z)),
versionRead_(version_) {
}

TrackHelix::TrackHelix(double x, double y, double z, double r, 
                       double h, double c, double thmin, double thmax) :
centerOfCurvature_(CLHEP::Hep3Vector(x,y,z)), radiusOfCurvature_(r), 
helixPitch_(h), sign_(c), thetaMin_(thmin), thetaMax_(thmax),
origin_(CLHEP::Hep3Vector(r, 0, z)),
versionRead_(version_){
}

TrackHelix::TrackHelix(double x, double y, double z, double r, 
                       double h, double c, 
                       double x0, double y0, double z0) :
centerOfCurvature_(CLHEP::Hep3Vector(x,y,z)), radiusOfCurvature_(r), 
helixPitch_(h), sign_(c), thetaMin_(0), thetaMax_(0),
origin_(CLHEP::Hep3Vector(x0, y0, z0)),
versionRead_(version_){
}

TrackHelix::TrackHelix(double x, double y, double z, double r, 
                       double h, double c, double thmin, double thmax,
                       double x0, double y0, double z0) :
centerOfCurvature_(CLHEP::Hep3Vector(x,y,z)), radiusOfCurvature_(r),
helixPitch_(h), sign_(c), thetaMin_(thmin), thetaMax_(thmax),
origin_(CLHEP::Hep3Vector(x0,y0,z0)), versionRead_(version_) {
}


TrackHelix::TrackHelix(const TrackHelix& obj) :
centerOfCurvature_(obj.centerOfCurvature_),
radiusOfCurvature_(obj.radiusOfCurvature_),
helixPitch_(obj.helixPitch_), sign_(obj.sign_),
thetaMin_(obj.thetaMin_), thetaMax_(obj.thetaMax_), origin_(obj.origin_),
versionRead_(obj.versionRead_){
    
}

TrackHelix::TrackHelix() {
    TrackHelix(0,0,0,0,0,0,0,0,0);
}

TrackHelix::~TrackHelix() {}

TrackHelix& TrackHelix::operator=(const TrackHelix &obj) {
    if (this != &obj) {
        versionRead_        = obj.versionRead_;
        centerOfCurvature_  = obj.centerOfCurvature_;
        radiusOfCurvature_  = obj.radiusOfCurvature_;
        helixPitch_         = obj.helixPitch_;
        sign_               = obj.sign_;
        thetaMin_           = obj.thetaMin_;
        thetaMax_           = obj.thetaMax_;        
        origin_             = obj.origin_;
    }
    return (*this);
}

//-----------------------------------------------------------------------------
// Print and Streaming
//-----------------------------------------------------------------------------
void TrackHelix::print(std::ostream& output) const {
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
    << " Theta max            : " << thetaMax() 
    << std::endl;
}

std::ostream& operator << (std::ostream& os, const TrackHelix& obj) {
    obj.print(os);
    return os;
}

//-------------------------------------------------------------------------
// Classifiers
//-------------------------------------------------------------------------
std::string TrackHelix::class_name() const {
    return std::string("TrackHelix");
}

//-----------------------------------------------------------------------------
// ROOT Input/Output
//-----------------------------------------------------------------------------
void TrackHelix::Streamer(TBuffer& iobuffer) {
    if (iobuffer.IsReading()) {
        iobuffer >>versionRead_;
        if (versionRead_ == 1) {
            readFromBuffer(iobuffer, versionRead_);
        } else {
            std::cerr << "TrackHelix::Streamer(<isReading>): " 
            << "Unsupported TrackHelix version while reading"
            <<std::endl;
        }
    } else if (iobuffer.IsWriting()) {
        iobuffer << version_;
        writeToBuffer(iobuffer);
    } else {
        std::cerr << "TrackHelix::Streamer(<unknown action>)" << std::endl;
    }
}

//--------------------------------------------------------------------------
// readFromBuffer function
//      Given a TBuffer that is in input mode, reset my data members to have
//      the values dictated by the data read from the buffer.
//--------------------------------------------------------------------------
void TrackHelix::readFromBuffer(TBuffer& iobuffer, Version_t version) {
    double x, y, z;    
    iobuffer >> x;
    iobuffer >> y;
    iobuffer >> z;
    centerOfCurvature_ = CLHEP::Hep3Vector(x,y,z);
    
    iobuffer >> radiusOfCurvature_;
    iobuffer >> helixPitch_;
    iobuffer >> sign_;
    iobuffer >> thetaMin_;
    iobuffer >> thetaMax_;
    iobuffer >> x;
    iobuffer >> y;
    iobuffer >> z;
    origin_ = CLHEP::Hep3Vector(x,y,z);
}    

bool TrackHelix::postread(EventRecord *p) {
    return true;
}

//--------------------------------------------------------------------------
// writeToBuffer function
//      Write my data to the given TBuffer
//--------------------------------------------------------------------------
void TrackHelix::writeToBuffer(TBuffer& iobuffer) {
    iobuffer << centerOfCurvature_.x();
    iobuffer << centerOfCurvature_.y();
    iobuffer << centerOfCurvature_.z();
    iobuffer << radiusOfCurvature_;
    iobuffer << helixPitch_;
    iobuffer << sign_;
    iobuffer << thetaMin_;
    iobuffer << thetaMax_;
    iobuffer << origin_.x();
    iobuffer << origin_.y();
    iobuffer << origin_.z();
}

//-----------------------------------------------------------------------------
// Getters
//-----------------------------------------------------------------------------
CLHEP::Hep3Vector TrackHelix::centerOfCurvature() const {
    return centerOfCurvature_;
}

double TrackHelix::radiusOfCurvature() const {
    return radiusOfCurvature_;
}

double TrackHelix::helixPitch() const {
    return helixPitch_;
}

double TrackHelix::sign() const {
    return sign_;
}

double TrackHelix::thetaMin() const {
    return thetaMin_;    
}

double TrackHelix::thetaMax() const {
    return thetaMax_;
}

CLHEP::Hep3Vector TrackHelix::origin() const  {
    return origin_;
}

//-------------------------------------------------------------------------
// Algorithms
//-------------------------------------------------------------------------
double TrackHelix::dTheta(double dZ) const { 
  return dZ/helixPitch();     
}

CLHEP::Hep3Vector   TrackHelix::pointAtZ(double z) const {
    // 1) calculate distance in z w.r.t. the z of center of curvature
    double dz = z - origin().z();
    
    // 2) get the 2D projection on the XY plane of the vector pointing to the 
    //    origin of the track, from the center of curvature
    CLHEP::Hep2Vector radius = CLHEP::Hep2Vector(origin() - centerOfCurvature());
    
    // 3) rotate the radius by the chagne in the theta
    radius.rotate(dTheta(dz));

    // 4) calculate the end point adding up all changes
    CLHEP::Hep3Vector endPoint = origin() + radius + CLHEP::Hep3Vector(0,0,dz);
    
    return endPoint;
}

double  TrackHelix::dS(double dTheta) const {
    double dZ       = helixPitch() * dTheta;
    double dCirc    = radiusOfCurvature() * dTheta;
    return sqrt(pow(dZ, 2) + pow(dCirc, 2));
}

double  TrackHelix::distanceAlongTrack(CLHEP::Hep3Vector start,
                                       CLHEP::Hep3Vector stop) const {
    // calculates the distance between two points, supposedly along the track
    // does not perform any check on whether the two points are on the track,
    // just calculates the angular distance and ues that to calculate the track

    // 1) calculate the projections on the XY plane of the vectors form the 
    // center of curvature to the starting and stopping point
    CLHEP::Hep2Vector centerToStart = CLHEP::Hep2Vector(start - centerOfCurvature());
    CLHEP::Hep2Vector centerToStop  = CLHEP::Hep2Vector(stop  - centerOfCurvature());
    
    // 2) calculate angle between the two points
    double angle = centerToStop.angle(centerToStart);
    return dS(angle);
}

double  TrackHelix::distanceFromOrigin(CLHEP::Hep3Vector stop) const {
    return distanceAlongTrack(origin(), stop);
}

CLHEP::Hep3Vector   TrackHelix::versorAt(CLHEP::Hep3Vector point)       const {

}

CLHEP::Hep3Vector   TrackHelix::pointClosestTo(CLHEP::Hep3Vector point) const {    
}
                                                                               
