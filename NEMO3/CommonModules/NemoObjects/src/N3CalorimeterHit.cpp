/*
 * Class        : N3CalorimeterHit
 * Description  : Definition of the object containing the data of the N3Calorimeter hit
 *                after the readout
 *
 *  Created by Stefano Torre on 02/07/11.
 *  Copyright 2011 Univesity College London. All rights reserved.
 */

#include "NemoObjects/N3CalorimeterHit.h"
#include <iostream>

//-----------------------------------------------------------------------------
// Constructors and Assignment
//-----------------------------------------------------------------------------

N3CalorimeterHit::N3CalorimeterHit() :
status_(0),
sectorNumber_(0), iobtFlag_(0), fcll_(0), blockNumber_(0),
adcCounter_(0), tdcCounter_(0), overThresholdFlag_(0),
blockCenter_(CLHEP::Hep3Vector(0,0,0)),energyDeposit_(0), 
versionRead_(version_) {
}

N3CalorimeterHit::N3CalorimeterHit(const N3CalorimeterHit& obj) :
status_(obj.status_),
sectorNumber_(obj.sectorNumber_),
iobtFlag_(obj.iobtFlag_),fcll_(obj.fcll_),blockNumber_(obj.blockNumber_),
adcCounter_(obj.adcCounter_), tdcCounter_(obj.tdcCounter_),
overThresholdFlag_(obj.overThresholdFlag_),blockCenter_(obj.blockCenter_),
energyDeposit_(obj.energyDeposit_),
versionRead_(obj.versionRead_){    
}

N3CalorimeterHit::~N3CalorimeterHit() {}

N3CalorimeterHit& N3CalorimeterHit::operator=(const N3CalorimeterHit& obj) {
    if (this != &obj) {
        versionRead_    = obj.versionRead_;
        status_         = obj.status_;
        sectorNumber_   = obj.sectorNumber_;
        iobtFlag_       = obj.iobtFlag_;
        fcll_           = obj.fcll_;
        blockNumber_    = obj.blockNumber_;
        adcCounter_     = obj.adcCounter_;
        tdcCounter_     = obj.tdcCounter_;
        overThresholdFlag_ = obj.overThresholdFlag_;
        blockCenter_    = obj.blockCenter_;
        energyDeposit_  = obj.energyDeposit_;
    }
    return (*this);
}

//-----------------------------------------------------------------------------
// Print and Streaming
//-----------------------------------------------------------------------------
int N3CalorimeterHit::pmtNumber() const {
  /* this code is copied from the function
     integer function NumbFromPos(se,or,co,bl)
     N3Db/db/prog/numeration.F
     c      
     c  Returns the consequent number of the PM calculated from the 
     c
     c  SEctor      (0-19)     
     c  ORientation (internal,external,bottom,top)=(0,1,2,3)
     c  COlumn      (0,2), (0,1,2), (0,1,2,3), (0,1,2,3)
     c  BLock       (0-16), (0-12), (0-2), (0-2)
     c
     c  The consequent number runs from 1 to 1940 for the PMs 
     c  on walls and petals.
     c  Extra PM's used for laser calibration are placed at the end 
     c  after the number 1940
     c  and have addresses:  se=19, or=3 co=3, bl=2+i
     c
     
     in rootana it was called as follows:

     nemo3::DbMgr::Db().Pos2Num("PM",sec,io,fcll,blk,&pmnum);
     so:
     se = sec = sector
     or = io = iobtFlag
     co = fcll 
     bl = blk = block
     
  */

  int nOrientation[] = {0, 34, 73, 85};
  int nBlock[]       = {17, 13, 3, 3};

  int column = (iobtFlag() == 0) ? fcll()/2 : fcll();
  return 
    sectorNumber() * 97 +
    nOrientation[iobtFlag()] +
    column * nBlock[iobtFlag()] +
    blockNumber() + 1;
}

int N3CalorimeterHit::blockSectorId() const {
  if (iobtFlag() == 0){
    // internal
    int layer = (fcll() == 2)? 1 : fcll();
    return sectorNumber() * 2 + layer;
  } else {
    // external, bottom/top petals
    //return sectorNumber() * 3 + fcll(); // WRONG! error imported from ROOTANA
    return sectorNumber() * 3 + ((iobtFlag() < 2) ? fcll() : blockNumber());
  }
}

int N3CalorimeterHit::blockLayerId() const {
  return (iobtFlag() < 2) ? blockNumber() : fcll();
}

int N3CalorimeterHit::checkNeighbour(const N3CalorimeterHit& other) const {
  // 0 - other is not a neighbour
  // 1 - other is on the side of this
  // 2 - other is on the diagonal of this
  if (iobtFlag() != other.iobtFlag()) {
    return 0;
  }
  
  // boundary conditions:
  // on the inner wall there are 40 blocks (0 to 39) all around, while on the
  // other walls thare are 60 (0 to 59)
  int prevSectorId = blockSectorId() - 1;
  if (blockSectorId() == 0) {
    prevSectorId = (iobtFlag() == 0) ? 39 : 59;
  }
  
  int nextSectorId = (blockSectorId() == 59) ? 0 : blockSectorId() + 1;
  if (iobtFlag() == 0 and blockSectorId() == 39) {
    nextSectorId = 0;
  }

  int nextLayerId = blockLayerId() + 1;
  int prevLayerId = blockLayerId() - 1;
  
  if (other.blockLayerId() == this->blockLayerId()) {
    if ((other.blockSectorId() == nextSectorId) or 
	(other.blockSectorId() == prevSectorId)) {
      // blocks side by side along the sector
      return 1;
    }
  } 
  if (other.blockSectorId() == this->blockSectorId()) {
    if ((other.blockLayerId() == nextLayerId) or 
	(other.blockLayerId() == prevLayerId)) {
      // blocks side by side along the layer
      return 1;
    }
  }
  if (other.blockLayerId() == nextLayerId) {
    if ((other.blockSectorId() == nextSectorId) or
	(other.blockSectorId() == prevSectorId))
      // block are neighbours along the diaganoal
      return 2;
  }
  if (other.blockLayerId() == prevLayerId) {
    if ((other.blockSectorId() == nextSectorId) or
	(other.blockSectorId() == prevSectorId))
      // block are neighbours along the diaganoal
      return 2;
  }
  return 0;
}
//-----------------------------------------------------------------------------
// Print and Streaming
//-----------------------------------------------------------------------------
void N3CalorimeterHit::print(std::ostream& output) const {
    output 
    << " Sector          : " << sectorNumber() << "\n"
    << " IOBT Flag       : " << iobtFlag() << "\n"
    << " FCLL            : " << fcll() << "\n"
    << " Block Number    : " << blockNumber() << "\n"
    << " Status          : " << status() << "\n"
    << " (x,y,z) of block: " 
    << blockCenter().x() << "," 
    << blockCenter().y() << "," << blockCenter().z() << ")\n"
    << " energy deposit  : " << energyDeposit() << "\n"
    << " Threshold Passed: " << overThresholdFlag() << "\n"
    << " ADC Count       : " << adcCounter() << "\n"
    << " TDC Count       : " << tdcCounter() << "\n";
}

std::ostream& operator << (std::ostream& os, const N3CalorimeterHit& obj) {
    obj.print(os);
    return os;
}

//-------------------------------------------------------------------------
// Classifiers
//-------------------------------------------------------------------------
std::string N3CalorimeterHit::class_name() const {
    return std::string("N3CalorimeterHit");
}

//-----------------------------------------------------------------------------
// ROOT Input/Output
//-----------------------------------------------------------------------------
void N3CalorimeterHit::Streamer(TBuffer& iobuffer) {
    if (iobuffer.IsReading()) {
        iobuffer >>versionRead_;
        if (versionRead_ == 1) {
            readFromBuffer(iobuffer, versionRead_);
        } else {
            std::cerr << "N3CalorimeterHit::Streamer(<isReading>): " 
            << "Unsupported N3CalorimeterHit version while reading"
            <<std::endl;
        }
    } else if (iobuffer.IsWriting()) {
        iobuffer << version_;
        writeToBuffer(iobuffer);
    } else {
        std::cerr << "N3CalorimeterHit::Streamer(<unknown action>)" << std::endl;
    }
}

//--------------------------------------------------------------------------
// readFromBuffer function
//      Given a TBuffer that is in input mode, reset my data members to have
//      the values dictated by the data read from the buffer.
//--------------------------------------------------------------------------
void N3CalorimeterHit::readFromBuffer(TBuffer& iobuffer, Version_t version) {
    iobuffer >> status_;
    iobuffer >> sectorNumber_;
    iobuffer >> iobtFlag_;
    iobuffer >> fcll_;
    iobuffer >> blockNumber_;
    iobuffer >> adcCounter_;
    iobuffer >> tdcCounter_;
    iobuffer >> overThresholdFlag_;
    double x,y,z;
    iobuffer >> x; iobuffer >> y; iobuffer >> z;
    blockCenter_ = CLHEP::Hep3Vector(x,y,z);
    iobuffer >> energyDeposit_;
}    

bool N3CalorimeterHit::postread(EventRecord *p) {
    return true;
}

//--------------------------------------------------------------------------
// writeToBuffer function
//      Write my data to the given TBuffer
//--------------------------------------------------------------------------
void N3CalorimeterHit::writeToBuffer(TBuffer& iobuffer) {
    iobuffer << status_;
    iobuffer << sectorNumber_;
    iobuffer << iobtFlag_;
    iobuffer << fcll_;
    iobuffer << blockNumber_;
    iobuffer << adcCounter_;
    iobuffer << tdcCounter_;
    iobuffer << overThresholdFlag_;
    iobuffer << blockCenter_.x();
    iobuffer << blockCenter_.y();
    iobuffer << blockCenter_.z();
    iobuffer << energyDeposit_;
}


