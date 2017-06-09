//
//  NemorHeader.cpp
//
//  Created by Stefano Torre on 26/04/12.
//

#include "NemoObjects/NemorHeader.h"
//-----------------------------------------------------------------------------
// Constructors and Assignment
//-----------------------------------------------------------------------------

NemorHeader::NemorHeader() : 
StorableObject(),
runDuration_(0), 
numberGeneratedEvents_(0),
scintillationTime_(0),
eventTimeStamp_(0) {
}

NemorHeader::NemorHeader(const NemorHeader &obj) :
StorableObject(obj), 
runDuration_(obj.runDuration_), 
numberGeneratedEvents_(obj.numberGeneratedEvents_),
scintillationTime_(obj.scintillationTime_),
eventTimeStamp_(obj.eventTimeStamp_) {
}

NemorHeader& NemorHeader::operator =(const NemorHeader& obj) {
    return (*this);
}

//-----------------------------------------------------------------------------
// Getters and Setters
//-----------------------------------------------------------------------------

void NemorHeader::setEventTimeStamp(int evntime, int date){

  // convert timestamp from nemor format (hhmnss*1000) to TTimestamp;
  int dayNemor   =       date       - ((int) date/100)*100;
  int monthNemor = (int) date/100   - ((int) date/10000)*100;
  int yearNemor  = (int) date/10000;
  
  int msNemor =         evntime               -   ((int) ( evntime / 1000 ))*1000;
  int sNemor  =  (int) (evntime / 1000)       -   ((int) ( evntime / 100000))*100;
  int mNemor  = ((int) (evntime / 100000))    -   ((int) ( evntime / 10000000))*100;
  int hNemor  = ((int) (evntime / 10000000));
  
  eventTimeStamp_ = TTimeStamp(yearNemor, monthNemor, dayNemor, hNemor, mNemor, sNemor, (int)(msNemor*1e6));
}

//-----------------------------------------------------------------------------
// Print and Streaming
//-----------------------------------------------------------------------------
void NemorHeader::print(std::ostream& output) const {
    StorableObject::print(output);
    output 
      << "N. Generated Events : " << numberOfGeneratedEvents() << "\n"
      << "Run Duration:         " << runDuration() << "\n"
      << "Scintillator Tau    : " << scintillationTime() << "\n"
      << "Event Time Stamp    : " << eventTimeStamp() << "\n";
}


std::ostream& operator << (std::ostream& os, const NemorHeader & obj) {
    obj.print(os);
    return os;
}

//-----------------------------------------------------------------------------
// Classifiers
//-----------------------------------------------------------------------------
std::string NemorHeader::class_name() const  {
    return (NemorHeader::Class_Name());
}

Version_t NemorHeader::class_version() const {
    return (NemorHeader::Class_Version());
}

//-----------------------------------------------------------------------------
// ROOT Input/Output
//-----------------------------------------------------------------------------
void NemorHeader::Streamer(TBuffer& iobuffer) {
    unsigned int start = 0;
    unsigned int byte_count = 0;
    
    if (iobuffer.IsReading()) {
        Version_t original_version = iobuffer.ReadVersion(&start, &byte_count) ;
        StorableObject::Streamer(iobuffer);
	iobuffer >> numberGeneratedEvents_;
	iobuffer >> runDuration_;
	iobuffer >> scintillationTime_;
	iobuffer >> eventTimeStamp_;
        iobuffer.CheckByteCount(start, byte_count, NemorHeader::IsA());
    } else if (iobuffer.IsWriting()) {
        byte_count = iobuffer.WriteVersion(NemorHeader::IsA(), kTRUE);
        Version_t current_version = NemorHeader::class_version();
        StorableObject::Streamer(iobuffer);
	iobuffer << numberGeneratedEvents_;
	iobuffer << runDuration_;
	iobuffer << scintillationTime_;
	iobuffer << eventTimeStamp_;
        iobuffer.SetByteCount(byte_count, kTRUE);
    }
}

//-----------------------------------------------------------------------------
// ROOT Handle
//-----------------------------------------------------------------------------
ClassImp(NemorHeader)
