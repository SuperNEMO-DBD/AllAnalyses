/*
 * Class        : GammaCluster
 * Description  : Definition of the object representing a gamma cluster gamma
 *
 *  Created by Summer Blot on 16/04/2013.
 *
 *  Please see NemoObjects/GammaCLuster.h for complete description of all methods.
 *  Also checking out NemoObjects/Gamma.h, NemoMods/GammaFinder.h and 
 *  NemoMods/CaloClusterFinder.h are useful to fully understand all methods.
 */

#include "NemoObjects/N3CalorimeterHit.h"
#include "NemoObjects/GammaCluster.h"
#include "NemoObjects/Gamma.h"
#include <iostream>

//-----------------------------------------------------------------------------
// Constructors and Assignment
//-----------------------------------------------------------------------------

GammaCluster::GammaCluster() :
  energy_(0), dEnergy_(0), versionRead_(version_), timeSpan_(-1), measTime_(0), dMeasTime_(0), dPathLength_(0), 
  hitPosition_(CLHEP::Hep3Vector(0,0,0)), iobt_(0), fcll_(0), clusterProb_(-1), cluster_(0), scintToPMTTime_(0),
  clusterId_(-1), goodPMTStatuses_(false),goodLDFlags_(false), goodHSFlags_(false),hasLDCorrs_(false), hasLDCorrErrs_(false),
   numNeighbours_(0) {
}

GammaCluster::GammaCluster(const GammaCluster& obj) :
  cluster_(obj.cluster_), energy_(obj.energy_), dEnergy_(obj.dEnergy_), 
  versionRead_(versionRead_), earliestHit_(obj.earliestHit_),
  latestHit_(obj.latestHit_), timeSpan_(obj.timeSpan_), measTime_(obj.measTime_),
  dMeasTime_(obj.dMeasTime_), dPathLength_(obj.dPathLength_),
  hitPosition_(obj.hitPosition_), iobt_(obj.iobt_), fcll_(obj.fcll_), scintToPMTTime_(obj.scintToPMTTime_),
  clusterProb_(obj.clusterProb_), clusterId_(obj.clusterId_), goodPMTStatuses_(obj.goodPMTStatuses_), goodLDFlags_(obj.goodLDFlags_),
  goodHSFlags_(obj.goodHSFlags_), hasLDCorrs_(obj.hasLDCorrs_), hasLDCorrErrs_(obj.hasLDCorrErrs_), numNeighbours_(obj.numNeighbours()) {}

GammaCluster::~GammaCluster() {}

GammaCluster& GammaCluster::operator=(const GammaCluster& obj) {
  if (this != &obj) {
    versionRead_       = obj.versionRead_      ;
    energy_            = obj.energy_           ;
    dEnergy_           = obj.dEnergy_          ;
    cluster_           = obj.cluster_          ;
    earliestHit_       = obj.earliestHit_      ; 
    latestHit_         = obj.latestHit_        ;
    timeSpan_          = obj.timeSpan_         ;
    dMeasTime_         = obj.dMeasTime_        ; 
    measTime_          = obj.measTime_         ; 
    dPathLength_       = obj.dPathLength_      ;
    scintToPMTTime_    = obj.scintToPMTTime_   ;
    hitPosition_       = obj.hitPosition_      ; 
    iobt_              = obj.iobt_             ; 
    fcll_              = obj.fcll_             ;
    clusterProb_       = obj.clusterProb_      ;
    clusterId_         = obj.clusterId_        ; 
    goodPMTStatuses_   = obj.goodPMTStatuses_  ; 
    goodLDFlags_       = obj.goodLDFlags_      ;
    goodHSFlags_       = obj.goodHSFlags_      ;
    hasLDCorrs_        = obj.hasLDCorrs_       ;
    hasLDCorrErrs_     = obj.hasLDCorrErrs_    ;
    numNeighbours_     = obj.numNeighbours_    ;
  }
  return (*this);
}

//-----------------------------------------------------------------------------
// Print and Streaming
//-----------------------------------------------------------------------------
void GammaCluster::print(std::ostream& output) const {
  output
    << " Cluster ID         : " << clusterId() << "\n"
    << " all good PMT Statuses : " << goodPMTStatuses() << "\n"
    << " all good LD Flags  : " << goodLDFlags() << "\n"
    << " all good HS Flags  : " << goodHSFlags() << "\n"
    << " all PMs LD corrs   : " << hasLDCorrs() << "\n"
    << " all PMs LD corr errs : " << hasLDCorrErrs() << "\n"
    << " Ngammas in cluster : " << cluster().size()    << "\n"
    << " first gamma hit    : " << earliestHit() << "\n"
    << " latest gamma hit   : " << latestHit() << "\n"
    << " Cluster Time Span  : " << timeSpan() << "\n"
    << " Avg time of cluster: " << measTime() << "\n"
    << " weighted time avg  : " << dMeasTime() << "\n"
    << " hit position       : " << hitPosition() << "\n"
    << " path length error  : " << dPathLength() << "\n"
    << " cluster energy     : " << energy() << " +- " << dEnergy() << "\n"
    << " IOBT flag          : " << iobt() << "\n"
    << " FCLL flag          : " << fcll() << "\n"
    << " extra delay in scint: " << scintToPMTTime() << "\n"
    << " cluster probability: " << clusterProb() << "\n"
    << " num neighbouring clustsers: " << numNeighbours();
}

std::ostream& operator << (std::ostream& os, const GammaCluster& obj) {
   obj.print(os);
   return os;
}

//-------------------------------------------------------------------------
// Classifiers
//-------------------------------------------------------------------------
std::string GammaCluster::class_name() const {
  return std::string("GammaCluster");
}


//-----------------------------------------------------------------------------
// ROOT Input/Output
//-----------------------------------------------------------------------------
void GammaCluster::Streamer(TBuffer& iobuffer) {
  if (iobuffer.IsReading()) {
    iobuffer >> versionRead_;
    if (versionRead_ == 1) {
      readFromBuffer(iobuffer, versionRead_);
    } else {
      std::cerr << "GammaCluster::Streamer(<isReading>): " 
		<< "Unsupported GammaCluster version while reading"
		<<std::endl;
    }
  } else if (iobuffer.IsWriting()) {
    iobuffer << version_;
    writeToBuffer(iobuffer);
  } else {
    std::cerr << "GammaCluster::Streamer(<unknown action>)" << std::endl;
  }
}

//--------------------------------------------------------------------------
// readFromBuffer function
//      Given a TBuffer that is in input mode, reset my data members to have
//      the values dictated by the data read from the buffer.
//--------------------------------------------------------------------------
void GammaCluster::readFromBuffer(TBuffer& iobuffer, Version_t version) {
  //std::vector<Gamma> tmp         ;
  //iobuffer >> tmp;
  //cluster_ = std::vector<Gamma>(tmp);
  iobuffer >> clusterId_          ; 
  iobuffer >> goodPMTStatuses_    ; 
  iobuffer >> goodLDFlags_        ;
  iobuffer >> goodHSFlags_        ; 
  iobuffer >> hasLDCorrs_          ;
  iobuffer >> hasLDCorrErrs_      ;
  iobuffer >> timeSpan_           ;
  iobuffer >> measTime_           ;
  iobuffer >> dMeasTime_          ;
  iobuffer >> energy_             ;
  iobuffer >> dEnergy_            ;
  iobuffer >> dPathLength_        ;
  iobuffer >> iobt_               ;
  iobuffer >> fcll_               ;
  double x, y, z;
  iobuffer >> x; iobuffer >> y; iobuffer >> z;
  // Gamma gamma_;
  hitPosition_ = CLHEP::Hep3Vector(x,y,z);
  iobuffer >> scintToPMTTime_     ;
  iobuffer >> numNeighbours_      ;
}    

bool GammaCluster::postread(EventRecord *p) {
  return true;
}

//--------------------------------------------------------------------------
// writeToBuffer function
//      Write my data to the given TBuffer
//--------------------------------------------------------------------------
void GammaCluster::writeToBuffer(TBuffer& iobuffer) {
  iobuffer << clusterId_           ;
  iobuffer << goodPMTStatuses_     ;
  iobuffer << goodLDFlags_         ;
  iobuffer << goodHSFlags_         ; 
  iobuffer << hasLDCorrs_          ;
  iobuffer << hasLDCorrErrs_       ; 
  iobuffer << timeSpan_            ;
  iobuffer << measTime_            ;
  iobuffer << dMeasTime_           ;
  //iobuffer << cluster_          ;
  iobuffer << energy_              ;
  iobuffer << dEnergy_             ;
  iobuffer << dPathLength_         ;
  iobuffer << iobt_                ; 
  iobuffer << fcll_                ;
  iobuffer << hitPosition_.x()     ; 
  iobuffer << hitPosition_.y()     ; 
  iobuffer << hitPosition_.z()     ;
  iobuffer << scintToPMTTime_      ;
  iobuffer << numNeighbours_       ;
}
