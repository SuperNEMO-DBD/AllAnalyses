/*
 * Class        : CalibCaloHit
 * Description  : Definition of the object containing calorimeter information
 *                with all calibration and corrections applied to it
 *
 *  Created by Stefano Torre on 25/04/2012.
 */

#include "NemoObjects/CalibCaloHit.h"
#include <iostream>

//-----------------------------------------------------------------------------
// Constructors and Assignment
//-----------------------------------------------------------------------------

CalibCaloHit::CalibCaloHit() :
status_(0),
pmtNumber_(0),
hitId_(0),
overThresholdFlag_(0),
sectorNumber_(0),
iobt_(0),
fcll_(0),
blockNumber_(0),
goodFlag_(0),
leFlag_(0),
ldFlag_(0),
ldCorr_(0), ldCorrErr_(0),
hsFlag_(0),
blockCenter_(CLHEP::Hep3Vector(0,0,0)),
energyDeposit_(0), 
fwhm_(0),
hitTime_(0),
gammaScintillationTime_(0),
electronScintillationTime_(0),
gammaTimeError_(0),
electronTimeError_(0),
alpha_(0),
alphaEr_(0),
versionRead_(version_) {
}

CalibCaloHit::CalibCaloHit(const CalibCaloHit& obj) :
status_(obj.status_),
pmtNumber_(obj.pmtNumber_),
hitId_(obj.hitId_),
overThresholdFlag_(obj.overThresholdFlag_),
sectorNumber_(obj.sectorNumber_),
iobt_(obj.iobt_),
fcll_(obj.fcll_),
blockNumber_(obj.blockNumber_),
goodFlag_(obj.goodFlag_),
leFlag_(obj.leFlag_),
ldFlag_(obj.ldFlag_),
ldCorr_(obj.ldCorr_),
ldCorrErr_(obj.ldCorrErr_),
hsFlag_(obj.hsFlag_),
blockCenter_(obj.blockCenter_),
energyDeposit_(obj.energyDeposit_),
fwhm_(obj.fwhm_),
hitTime_(obj.hitTime_),
gammaScintillationTime_(obj.gammaScintillationTime_),
electronScintillationTime_(obj.electronScintillationTime_),
gammaTimeError_(obj.gammaTimeError_),
electronTimeError_(obj.electronTimeError_),
alpha_(obj.alpha_),
alphaEr_(obj.alphaEr_),
versionRead_(obj.versionRead_){    
}

CalibCaloHit::CalibCaloHit(const N3CalorimeterHit& obj){    
  status_            = obj.status();
  pmtNumber_         = obj.pmtNumber();
  overThresholdFlag_ = obj.overThresholdFlag();
  blockCenter_       = obj.blockCenter();
  energyDeposit_     = obj.energyDeposit();
  sectorNumber_      = obj.sectorNumber();
  iobt_              = obj.iobtFlag();
  fcll_              = obj.fcll();
  blockNumber_       = obj.blockNumber();
  versionRead_       = version_;
}

CalibCaloHit::~CalibCaloHit() {}

CalibCaloHit& CalibCaloHit::operator=(const CalibCaloHit& obj) {
    if (this != &obj) {
        versionRead_               = obj.versionRead_;
        status_                    = obj.status_;
        pmtNumber_                 = obj.pmtNumber_;
        hitId_                     = obj.hitId_;
        overThresholdFlag_         = obj.overThresholdFlag_;
        sectorNumber_              = obj.sectorNumber_;
        iobt_                      = obj.iobt_;
        fcll_                      = obj.fcll_;
        blockNumber_               = obj.blockNumber_;
        goodFlag_                  = obj.goodFlag_;
        leFlag_                    = obj.leFlag_;
        ldFlag_                    = obj.ldFlag_;
        ldCorr_                    = obj.ldCorr_;
        ldCorrErr_                 = obj.ldCorrErr_;
        hsFlag_                    = obj.hsFlag_;
        blockCenter_               = obj.blockCenter_;
        energyDeposit_             = obj.energyDeposit_;
        fwhm_                      = obj.fwhm_;
        hitTime_                   = obj.hitTime_;
        gammaScintillationTime_    = obj.gammaScintillationTime_   ;
        electronScintillationTime_ = obj.electronScintillationTime_;
        gammaTimeError_            = obj.gammaTimeError_           ;
        electronTimeError_         = obj.electronTimeError_        ;
        alpha_                     = obj.alpha_                    ;
        alphaEr_                   = obj.alphaEr_                  ;
    }
    return (*this);
}

//-----------------------------------------------------------------------------
// Print and Streaming
//-----------------------------------------------------------------------------
void CalibCaloHit::print(std::ostream& output) const {
    output 
      << " Hit ID                       : " << hitId() << "\n"
      << " PMT Number                   : " << pmtNumber() << "\n"
      << " Status                       : " << status() << "\n"
      << " (x,y,z) of block             : " 
      << blockCenter().x() << "," 
      << blockCenter().y() << "," << blockCenter().z() << ")\n"
      << " Energy deposit               : " << energyDeposit() << "\n"
      << " FWHM                         : " << fwhm() << "\n"
      << " Hit Time                     : " << hitTime() << "\n"
      << " Threshold Passed             : " << overThresholdFlag() << "\n"
      << " Good PMT Flag                : " << goodFlag() << "\n"
      << " LEC Flag                     : " << leFlag() << "\n"
      << " LD Flag                      : " << ldFlag() << "\n"
      << " LD Correction                : " << ldCorr() << "\n"
      << " LD Correction Error          : " << ldCorrErr() << "\n"
      << " HS Flag                      : " << hsFlag() << "\n"
      << " Scintillation Time (photon)  : " << gammaScintillationTime() << "\n"
      << " Scintillation Time (electron): " << electronScintillationTime() << "\n"
      << " Error on time (photon)       : " << gammaTimeError() << "\n"
      << " Error on time (electron)     : " << electronTimeError() << "\n"
      << " Alpha                        : " << alpha() << "\n"
      << " Alpha Error                  : " << alphaEr() << "\n";
}

std::ostream& operator << (std::ostream& os, const CalibCaloHit& obj) {
    obj.print(os);
    return os;
}

//-------------------------------------------------------------------------
// Classifiers
//-------------------------------------------------------------------------
std::string CalibCaloHit::class_name() const {
    return std::string("CalibCaloHit");
}

//-----------------------------------------------------------------------------
// ROOT Input/Output
//-----------------------------------------------------------------------------
void CalibCaloHit::Streamer(TBuffer& iobuffer) {
    if (iobuffer.IsReading()) {
        iobuffer >>versionRead_;
        if (versionRead_ == 1) {
            readFromBuffer(iobuffer, versionRead_);
        } else {
            std::cerr << "CalibCaloHit::Streamer(<isReading>): " 
            << "Unsupported CalibCaloHit version while reading"
            <<std::endl;
        }
    } else if (iobuffer.IsWriting()) {
        iobuffer << version_;
        writeToBuffer(iobuffer);
    } else {
        std::cerr << "CalibCaloHit::Streamer(<unknown action>)" << std::endl;
    }
}

//--------------------------------------------------------------------------
// readFromBuffer function
//      Given a TBuffer that is in input mode, reset my data members to have
//      the values dictated by the data read from the buffer.
//--------------------------------------------------------------------------
void CalibCaloHit::readFromBuffer(TBuffer& iobuffer, Version_t version) {
    iobuffer >> status_;
    iobuffer >> pmtNumber_;
    iobuffer >> hitId_;
    iobuffer >> overThresholdFlag_;
    iobuffer >> sectorNumber_;
    iobuffer >> iobt_;
    iobuffer >> fcll_;
    iobuffer >> blockNumber_;
    iobuffer >> goodFlag_;
    iobuffer >> leFlag_;
    iobuffer >> ldFlag_;
    iobuffer >> ldCorr_;
    iobuffer >> ldCorrErr_;
    iobuffer >> hsFlag_;
    double x,y,z;
    iobuffer >> x; iobuffer >> y; iobuffer >> z;
    blockCenter_ = CLHEP::Hep3Vector(x,y,z);
    iobuffer >> energyDeposit_;
    iobuffer >> fwhm_;
    iobuffer >> hitTime_;
    iobuffer >> gammaScintillationTime_;
    iobuffer >> electronScintillationTime_;
    iobuffer >> gammaTimeError_;
    iobuffer >> electronTimeError_;
    iobuffer >> alpha_;
    iobuffer >> alphaEr_;
}    

bool CalibCaloHit::postread(EventRecord *p) {
    return true;
}

//--------------------------------------------------------------------------
// writeToBuffer function
//      Write my data to the given TBuffer
//--------------------------------------------------------------------------
void CalibCaloHit::writeToBuffer(TBuffer& iobuffer) {
    iobuffer << status_;
    iobuffer << pmtNumber_;
    iobuffer << hitId_;
    iobuffer << overThresholdFlag_;
    iobuffer << sectorNumber_;
    iobuffer << iobt_;
    iobuffer << fcll_;
    iobuffer << blockNumber_;
    iobuffer << goodFlag_;
    iobuffer << leFlag_;
    iobuffer << ldFlag_;
    iobuffer << ldCorr_;
    iobuffer << ldCorrErr_;
    iobuffer << hsFlag_;
    iobuffer << blockCenter_.x();
    iobuffer << blockCenter_.y();
    iobuffer << blockCenter_.z();
    iobuffer << energyDeposit_;
    iobuffer << fwhm_;
    iobuffer << hitTime_;
    iobuffer << gammaScintillationTime_;
    iobuffer << electronScintillationTime_;
    iobuffer << gammaTimeError_;
    iobuffer << electronTimeError_;
    iobuffer << alpha_;
    iobuffer << alphaEr_;
}


