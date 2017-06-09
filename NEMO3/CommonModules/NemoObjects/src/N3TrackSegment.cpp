//
//  N3TrackSegment.cpp
//
//  Created by Stefano Torre on 15/02/12.
//

#include "NemoObjects/N3TrackSegment.h"
#include <iostream>

//-----------------------------------------------------------------------------
// Constructors and Assignment
//-----------------------------------------------------------------------------
N3TrackSegment::N3TrackSegment() :
algorithm_(-1), 
  isAssociatedToFoil_(false), 
  indexOfScintillator_(-1), impactRegion_(-1),
  versionRead_(version_) {    
  }

N3TrackSegment::N3TrackSegment(const N3TrackSegment& obj) :
algorithm_(obj.algorithm_), 
  isAssociatedToFoil_(obj.isAssociatedToFoil_), 
  indexOfScintillator_(obj.indexOfScintillator_), 
  impactRegion_(obj.impactRegion_),
  versionRead_(obj.versionRead_) {    
  geigerHitList_             = obj.geigerHitList_;
  globalFit_                 = obj.globalFit_;
  localCaloFit_              = obj.localCaloFit_;
  localFoilFit_              = obj.localFoilFit_;
  intersectionOnFoil_global_ = obj.intersectionOnFoil_global_;
  intersectionOnFoil_foil_   = obj.intersectionOnFoil_foil_;
  directionCosine_global_    = obj.directionCosine_global_;
  directionCosine_foil_      = obj.directionCosine_foil_;
  directionCosine_scint_     = obj.directionCosine_scint_;
  isAssociatedToFoil_        = obj.isAssociatedToFoil_;
  foilCenter_                = obj.foilCenter_;
  intersectionOnScint_global_= obj.intersectionOnScint_global_;
  intersectionOnScint_scint_ = obj.intersectionOnScint_scint_;
  indexOfScintillator_       = obj.indexOfScintillator_;
  impactRegion_              = obj.impactRegion_;
}

N3TrackSegment::~N3TrackSegment() {}

N3TrackSegment& N3TrackSegment::operator=(const N3TrackSegment& obj) {
  if (this != &obj) {
    versionRead_               = obj.versionRead_;
    algorithm_                 = obj.algorithm_;
    geigerHitList_             = obj.geigerHitList_;
    globalFit_                 = obj.globalFit_;
    localCaloFit_              = obj.localCaloFit_;
    localFoilFit_              = obj.localFoilFit_;
    intersectionOnFoil_global_ = obj.intersectionOnFoil_global_;
    intersectionOnFoil_foil_   = obj.intersectionOnFoil_foil_;
    directionCosine_global_    = obj.directionCosine_global_;
    directionCosine_foil_      = obj.directionCosine_foil_;
    directionCosine_scint_     = obj.directionCosine_scint_;
    isAssociatedToFoil_        = obj.isAssociatedToFoil_;
    foilCenter_                = obj.foilCenter_;
    intersectionOnScint_global_= obj.intersectionOnScint_global_;
    intersectionOnScint_scint_ = obj.intersectionOnScint_scint_;
    indexOfScintillator_       = obj.indexOfScintillator_;
    impactRegion_              = obj.impactRegion_;
  }
  return (*this);
}

//-----------------------------------------------------------------------------
// Print and Streaming
//-----------------------------------------------------------------------------
void N3TrackSegment::print(std::ostream &output) const {
  output
    << " Tracking Algo                     : " << algorithm()              << "\n"
    << " Geiger Hits Fitted                : " << geigerHitList()->size()  << "\n"
    << " Global Fit Results ------------------------------\n"
    << globalFit()
    << " Local Fit Near Foil Results ---------------------\n"
    << localFoilFit()
    << " Local Fit Near Calo Results ---------------------\n"
    << localCaloFit()
    << " Found intersection with foil      : " << isAssociatedToFoil() << "\n"
    << " Position of intersection (global) : (" 
    << intersectionOnFoil().x() << ", " << intersectionOnFoil().y() << ", "
    << intersectionOnFoil().z() << ")\n"
    << " Position of intersection (foil)   : (" 
    << intersectionOnFoil(true).x() << ", " << intersectionOnFoil(true).y() << ", "
    << intersectionOnFoil(true).z() << ")\n"
    << " Direction cosines (global)        : ("
    << directionCosine(0).x() << ", " << directionCosine(0).y() << ", "
    << directionCosine(0).z() << ")\n"
    << " Direction cosines (foil)          : ("
    << directionCosine(1).x() << ", " << directionCosine(1).y() << ", "
    << directionCosine(1).z() << ")\n"
    << " Direction cosines (scintillator)  : ("
    << directionCosine(2).x() << ", " << directionCosine(2).y() << ", "
    << directionCosine(2).z() << ")\n"
    << " Center of the associated foid  : ("
    << foilCenter().x() << ", " << foilCenter().y() << ", "
    << foilCenter().z() << ")\n"
    << " Index of scintillator          : " << indexOfScintillator() << "\n"
    << " Scintillator region            : " << impactRegion()        << "\n"
    << " Intersection on scintillator (global)  : ("
    << intersectionOnScint().x() << ", " << intersectionOnScint().y() << ", "
    << intersectionOnScint().z() << ")\n"
    << " Intersection on scintillator (scint)   : ("
    << intersectionOnScint(true).x() << ", " << intersectionOnScint(true).y() << ", "
    << intersectionOnScint(true).z() << ")\n"
    << std::endl;
}

std::ostream& operator << (std::ostream& os, const N3TrackSegment& obj) {
  obj.print(os);
  return os;
}

//-------------------------------------------------------------------------
// Classifiers
//-------------------------------------------------------------------------
std::string N3TrackSegment::class_name() const {
  return std::string("N3TrackSegment");
}

//-----------------------------------------------------------------------------
// ROOT Input/Output
//-----------------------------------------------------------------------------
void N3TrackSegment::Streamer(TBuffer& iobuffer) {
  if (iobuffer.IsReading()) {
    iobuffer >>versionRead_;
    if (versionRead_ == 1) {
      readFromBuffer(iobuffer, versionRead_);
    } else {
      std::cerr << "N3TrackSegment::Streamer(<isReading>): " 
		<< "Unsupported N3TrackSegment version while reading"
		<<std::endl;
    }
  } else if (iobuffer.IsWriting()) {
    iobuffer << version_;
    writeToBuffer(iobuffer);
  } else {
    std::cerr << "N3TrackSegment::Streamer(<unknown action>)" << std::endl;
  }
}

//--------------------------------------------------------------------------
// readFromBuffer function
//      Given a TBuffer that is in input mode, reset my data members to have
//      the values dictated by the data read from the buffer.
//--------------------------------------------------------------------------
void N3TrackSegment::readFromBuffer(TBuffer& iobuffer, Version_t version) {
  iobuffer >> algorithm_;
    
  size_t nHits = 0;
  iobuffer >> nHits;
  for (unsigned int i = 0; i < nHits; ++i) {
    int anId;
    iobuffer >> anId;
    geigerHitList_.push_back(anId);
  }
    
  globalFit_.Streamer(iobuffer);
  localFoilFit_.Streamer(iobuffer);
  localCaloFit_.Streamer(iobuffer);
    
  double x, y, z;
  iobuffer >> x;
  iobuffer >> y;
  iobuffer >> z;
  intersectionOnFoil_global_ = CLHEP::Hep3Vector(x,y,z);

  iobuffer >> x;
  iobuffer >> y;
  iobuffer >> z;
  intersectionOnFoil_foil_ = CLHEP::Hep3Vector(x,y,z);
    
  iobuffer >> x;
  iobuffer >> y;
  iobuffer >> z;
  directionCosine_global_ = CLHEP::Hep3Vector(x,y,z);
    
  iobuffer >> x;
  iobuffer >> y;
  iobuffer >> z;
  directionCosine_foil_ = CLHEP::Hep3Vector(x,y,z);

  iobuffer >> x;
  iobuffer >> y;
  iobuffer >> z;
  directionCosine_scint_ = CLHEP::Hep3Vector(x,y,z);

  iobuffer >> isAssociatedToFoil_;
    
  iobuffer >> x;
  iobuffer >> y;
  iobuffer >> z;
  foilCenter_         = CLHEP::Hep3Vector(x,y,z);
    
  iobuffer >> x;
  iobuffer >> y;
  iobuffer >> z;
  intersectionOnScint_global_= CLHEP::Hep3Vector(x,y,z);
    
  iobuffer >> x;
  iobuffer >> y;
  iobuffer >> z;
  intersectionOnScint_scint_= CLHEP::Hep3Vector(x,y,z);

  iobuffer >> indexOfScintillator_;
  iobuffer >> impactRegion_;
}    

bool N3TrackSegment::postread(EventRecord *p) {
  return true;
}

//--------------------------------------------------------------------------
// writeToBuffer function
//      Write my data to the given TBuffer
//--------------------------------------------------------------------------
void N3TrackSegment::writeToBuffer(TBuffer& iobuffer) {
  size_t nHits = geigerHitList_.size();
  iobuffer << nHits;
    
  for (unsigned int i = 0; i < nHits; ++i) {
    iobuffer << geigerHitList_.at(i);
  }
    
  globalFit_.Streamer(iobuffer);
  localFoilFit_.Streamer(iobuffer);
  localCaloFit_.Streamer(iobuffer);
    
  iobuffer << intersectionOnFoil_global_.x();
  iobuffer << intersectionOnFoil_global_.y();
  iobuffer << intersectionOnFoil_global_.z();
    
  iobuffer << intersectionOnFoil_foil_.x();
  iobuffer << intersectionOnFoil_foil_.y();
  iobuffer << intersectionOnFoil_foil_.z();
    
  iobuffer << directionCosine_global_.x();
  iobuffer << directionCosine_global_.y();
  iobuffer << directionCosine_global_.z();
    
  iobuffer << directionCosine_foil_.x();
  iobuffer << directionCosine_foil_.y();
  iobuffer << directionCosine_foil_.z();
    
  iobuffer << directionCosine_scint_.x();
  iobuffer << directionCosine_scint_.y();
  iobuffer << directionCosine_scint_.z();
    
  iobuffer << isAssociatedToFoil_;
    
  iobuffer << foilCenter_.x();
  iobuffer << foilCenter_.y();
  iobuffer << foilCenter_.z();
    
  iobuffer << intersectionOnScint_global_.x();
  iobuffer << intersectionOnScint_global_.y();
  iobuffer << intersectionOnScint_global_.z();
    
  iobuffer << intersectionOnScint_scint_.x();
  iobuffer << intersectionOnScint_scint_.y();
  iobuffer << intersectionOnScint_scint_.z();
    
  iobuffer << indexOfScintillator_;
  iobuffer << impactRegion_;
}



////-------------------------------------------------------------------------
//// Getters 
////-------------------------------------------------------------------------
//int                 algorithm()                 const;
//std::vector<int>*   geigerHitList()             const;
//TrackHelix*     globalFit()                 const;
//TrackHelix*     localFoilFit()              const;
//TrackHelix*     localCaloFit()              const;
//
//CLHEP::Hep3Vector*  intersectionOnFoil()        const;
//double              directionCosine(int dir)    const;
//bool                isAssociatedToFoil()        const;
//CLHEP::Hep3Vector*  foilCenter()                const;
//
//CLHEP::Hep3Vector*  intersectionOnScint()       const;
//int                 indexOfScintillator()       const;
//int                 impactRegion()              const;
//
////-------------------------------------------------------------------------
//// Setters 
////-------------------------------------------------------------------------
//void setAlgorithm(const int aValue) { algorithm_ = aValue; }
//void setGeigerHitList(const std::vector<int> aValue);
//void setGlobalFit(const TrackHelix aValue);
//void setLocalFoilFit(const TrackHelix aValue);
//void setLocalCaloFit(const TrackHelix aValue);
//
//void setIntersectionOnFoil(const CLHEP::Hep3Vector aValue);
//void setDirectionCosine(int it, const double aValue);
//void setIsAssociatedToFoil(bool aValue);
//void setFoilCenter(const CLHEP::Hep3Vector aValue);
//
//void setIntersectionOnScint(const CLHEP::Hep3Vector aValue);
//void setIndexOfScintillator(const int aValue);
//void setImpactRegion(const int aValue);




