//
//  TrackHelix.h
//
//  Created by Stefano Torre on 15/02/12.
//

#ifndef NEMO_TRACKHELIX_H_
#define NEMO_TRACKHELIX_H_
#include "Hereward/Edm/EventRecord.h"
#include "CLHEP/Vector/ThreeVector.h"

class TrackHelix {
public:
    //-------------------------------------------------------------------------
    // Constructors
    //-------------------------------------------------------------------------
    TrackHelix();
    TrackHelix(double x, double y, double z, double r, 
               double h, double c);
    TrackHelix(double x, double y, double z, double r, 
               double h, double c, double thmin, double thmax);
    TrackHelix(double x, double y, double z, double r, 
               double h, double c, 
               double x0, double y0, double z0);
    TrackHelix(double x, double y, double z, double r, 
               double h, double c, double thmin, double thmax,
               double x0, double y0, double z0);
    TrackHelix(const TrackHelix& obj);
    TrackHelix& operator = (const TrackHelix& obj);

    //-------------------------------------------------------------------------
    // Destructors
    //-------------------------------------------------------------------------
    virtual ~TrackHelix();
    
    //-------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------
    CLHEP::Hep3Vector centerOfCurvature()   const;
    double            radiusOfCurvature()   const;
    double            helixPitch()          const;
    double            sign()                const;
    double            thetaMin()            const;
    double            thetaMax()            const;    
    CLHEP::Hep3Vector origin()              const;

    //-------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------
    void setCenterOfCurvature(const CLHEP::Hep3Vector& aValue) { centerOfCurvature_ = aValue; }
    void setRadiusOfCurvature(const double&            aValue) { radiusOfCurvature_ = aValue; }
    void setHelixPitch       (const double&            aValue) { helixPitch_        = aValue; }
    void setSign             (const double&            aValue) { sign_              = aValue; }
    void setThetaMin         (const double&            aValue) { thetaMin_          = aValue; }
    void setThetaMax         (const double&            aValue) { thetaMax_          = aValue; }    
    void setOrigin           (const CLHEP::Hep3Vector& aValue) { origin_            = aValue; }

    //-------------------------------------------------------------------------
    // Algorithms
    //-------------------------------------------------------------------------
    double              dZ(double dTheta)   const { return helixPitch()*dTheta; }
    double              dTheta(double dZ)   const;
    CLHEP::Hep3Vector   pointAtZ(double z) const;
    CLHEP::Hep3Vector   pointClosestTo(CLHEP::Hep3Vector point) const;
    CLHEP::Hep3Vector   versorAt(CLHEP::Hep3Vector point)       const;
    double              distanceAlongTrack(CLHEP::Hep3Vector start,
                                           CLHEP::Hep3Vector stop) const;
    double              distanceFromOrigin(CLHEP::Hep3Vector stop) const;
    double              dS(double dTheta) const;

    //-------------------------------------------------------------------------
    // Print methods
    //-------------------------------------------------------------------------
    virtual void print(std::ostream &output = std::cout) const;
    
    //-------------------------------------------------------------------------
    // Classifiers
    //-------------------------------------------------------------------------
    std::string class_name() const;
    Version_t class_version() const {return version_; }
    
    //-------------------------------------------------------------------------
    // I/O Methods
    //-------------------------------------------------------------------------    
    void Streamer(TBuffer& iobuffer);    
    bool postread(EventRecord* p_record);
    void readFromBuffer(TBuffer& buf, Version_t version);
    void writeToBuffer(TBuffer& buf);
        
 protected:
    CLHEP::Hep3Vector   centerOfCurvature_;
    double              radiusOfCurvature_;
    double              helixPitch_;
    double              sign_;
    double              thetaMin_;
    double              thetaMax_;
    CLHEP::Hep3Vector   origin_;
 private:
    static const Version_t version_ = 1;
    Version_t versionRead_;
};

//-------------------------------------------------------------------------
// Streamer operator
//-------------------------------------------------------------------------
std::ostream& operator << (std::ostream& os, const TrackHelix& obj);

#endif
