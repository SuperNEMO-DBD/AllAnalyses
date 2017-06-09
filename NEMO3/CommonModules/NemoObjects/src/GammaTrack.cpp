/*
 * Class        : GammaTrack
 * Description  : Definition of the object for tracked gamma - used by NemoUtil/GammaTracker
 *
 *  Created by Summer Blot on 26/06/2013.
 */

#include "NemoObjects/GammaTrack.h"
//#include "NemoObjects/GammaCluster.h"
#include "NemoObjects/Gamma.h"
#include <iostream>

//-----------------------------------------------------------------------------
// Constructors and Assignment
//-----------------------------------------------------------------------------

GammaTrack::GammaTrack() :
  energy_(0), dEnergy_(0), prob_(0), gtLength_(0), chisq_(0), versionRead_(version_) {
}

GammaTrack::GammaTrack(const GammaTrack& obj) :
  trackedGammas_(obj.trackedGammas_), clusters_(obj.clusters_), energy_(obj.energy_), dEnergy_(obj.dEnergy_), 
  prob_(obj.prob_), versionRead_(versionRead_), firstHitPos_(obj.firstHitPos_),
  chisq_(obj.chisq_), gtLength_(obj.gtLength_) {
}

GammaTrack::~GammaTrack() {}

GammaTrack& GammaTrack::operator=(const GammaTrack& obj) {
  if (this != &obj) {
    versionRead_      = obj.versionRead_      ;
    energy_           = obj.energy_           ;
    dEnergy_          = obj.dEnergy_          ;
    prob_             = obj.prob_             ;
    chisq_            = obj.chisq_            ;
    gtLength_         = obj.gtLength_         ;
    trackedGammas_    = obj.trackedGammas_    ;
    clusters_         = obj.clusters_         ;
    firstHitPos_      = obj.firstHitPos_      ; 
  }
  return (*this);
}

//-----------------------------------------------------------------------------
// Print and Streaming
//-----------------------------------------------------------------------------
void GammaTrack::print(std::ostream& output) const {
  output
    << " Ngammas in track   : " << trackedGammas().size()    << "\n"
    << " total GT Prob      : " << prob() << "\n"
    << " total GT chisq     : " << chisq() << "\n"
    << " total GT length    : " << gtLength() << "\n"
    << " cluster energy     : " << energy() << " +- " << dEnergy() << "\n";
}

std::ostream& operator << (std::ostream& os, const GammaTrack& obj) {
   obj.print(os);
   return os;
}

//-------------------------------------------------------------------------
// Classifiers
//-------------------------------------------------------------------------
std::string GammaTrack::class_name() const {
  return std::string("GammaTrack");
}

//-----------------------------------------------------------------------------
// ROOT Input/Output
//-----------------------------------------------------------------------------
void GammaTrack::Streamer(TBuffer& iobuffer) {
  if (iobuffer.IsReading()) {
    iobuffer >> versionRead_;
    if (versionRead_ == 1) {
      readFromBuffer(iobuffer, versionRead_);
    } else {
      std::cerr << "GammaTrack::Streamer(<isReading>): " 
		<< "Unsupported GammaTrack version while reading"
		<<std::endl;
    }
  } else if (iobuffer.IsWriting()) {
    iobuffer << version_;
    writeToBuffer(iobuffer);
  } else {
    std::cerr << "GammaTrack::Streamer(<unknown action>)" << std::endl;
  }
}

//--------------------------------------------------------------------------
// readFromBuffer function
//      Given a TBuffer that is in input mode, reset my data members to have
//      the values dictated by the data read from the buffer.
//--------------------------------------------------------------------------
void GammaTrack::readFromBuffer(TBuffer& iobuffer, Version_t version) {
  iobuffer >> prob_            ;
  iobuffer >> chisq_           ;
  iobuffer >> gtLength_        ;
  //std::vector<Gamma> tmp         ;
  //iobuffer >> tmp;
  //cluster_ = std::vector<Gamma>(tmp);
  iobuffer >> energy_           ;
  iobuffer >> dEnergy_          ;
  double x, y, z;
  iobuffer >> x; iobuffer >> y; iobuffer >> z;
  // Gamma gamma_;
  //iobuffer >> firstHitPos_;
}    

bool GammaTrack::postread(EventRecord *p) {
  return true;
}

//--------------------------------------------------------------------------
// writeToBuffer function
//      Write my data to the given TBuffer
//--------------------------------------------------------------------------
void GammaTrack::writeToBuffer(TBuffer& iobuffer) {
  iobuffer << prob_             ;
  iobuffer << chisq_            ;
  iobuffer << gtLength_         ;
  //iobuffer << cluster_          ;
  iobuffer << energy_           ;
  iobuffer << dEnergy_          ;
}
