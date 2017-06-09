//
//  CalibCaloHitColl.cpp
//  SNemoCoreExample
//
//  Created by Stefano Torre on 02/07/11.
//  Copyright 2011 Univesity College London. All rights reserved.
//

#include "NemoObjects/CalibCaloHitColl.h"

//-------------------------------------------------------------------------
// Creation
//-------------------------------------------------------------------------
CalibCaloHitColl::CalibCaloHitColl() : StorableObject() {
    
}

CalibCaloHitColl::CalibCaloHitColl(const CalibCaloHitColl& rhs) :
StorableObject(rhs),
container_(rhs.container_) {
    
}

CalibCaloHitColl* CalibCaloHitColl::clone() {
    return new CalibCaloHitColl(*this);
}

//-------------------------------------------------------------------------
// Assignment
//-------------------------------------------------------------------------
CalibCaloHitColl& CalibCaloHitColl::operator=(const CalibCaloHitColl& rhs) {
    if (this != &rhs) {
        container_ = rhs.container_;
    }
    return *this;
}

//-------------------------------------------------------------------------
// EDM requirements
//-------------------------------------------------------------------------
void CalibCaloHitColl::destroy() {
    CalibCaloHitColl::deallocate();
    delete this;
}

void CalibCaloHitColl::deallocate() {
    StorableObject::deallocate();
}

//-------------------------------------------------------------------------
// Destruction
//-------------------------------------------------------------------------
CalibCaloHitColl::~CalibCaloHitColl() {
    
}

//-------------------------------------------------------------------------
// Classifiers
//-------------------------------------------------------------------------
std::string CalibCaloHitColl::class_name() const {
    return CalibCaloHitColl::Class_Name();
}

Version_t CalibCaloHitColl::class_version() const {
    return CalibCaloHitColl::Class_Version();
}

//-------------------------------------------------------------------------
// Iostream
//-------------------------------------------------------------------------
void CalibCaloHitColl::print(std::ostream& os) const {
    os 
    << "===================================================================="
    << std::endl
    << "Contents of CalibCaloHitColl: description = " << description()
    << " process name = " << process_name() << std::endl
    << "  Number of Calorimeter Hits in collection = " << container_.contents().size()
    << std::endl;
    container_.print(os);
    os 
    << std::endl
    << "===================================================================="
    << std::endl;
}

//-------------------------------------------------------------------------
// EDM input/output
//-------------------------------------------------------------------------
bool CalibCaloHitColl::postread(EventRecord* per) {
    bool status = true;
    
    for (CalibCaloHitColl::iterator hitIter = contents().begin();
         hitIter != contents().end(); hitIter++) {
        status &= (*hitIter).postread(per);
    }
    
    return status;
}

//-------------------------------------------------------------------------
// StorableObject Locators
//-------------------------------------------------------------------------
bool CalibCaloHitColl::find(EventRecord* pEvent, CalibCaloHitColl_ch& crHandle) {
    EventRecord::ConstIterator ciEvent(pEvent, "CalibCaloHitColl");
    if (ciEvent.is_invalid()) {
        return false;
    } else {
        crHandle = CalibCaloHitColl_ch(ciEvent);
        return true;
    }
}

bool CalibCaloHitColl::find(EventRecord* pEvent, CalibCaloHitColl_ch& crHandle,
                            const std::string& description) {
    StorableObject::SelectByDescription selector(description);
    EventRecord::ConstIterator ciEvent(pEvent, selector);
    
    if (ciEvent.is_invalid()) {
        return false;
    } else  {
        crHandle = CalibCaloHitColl_ch(ciEvent);
        return true;
    }
}

//-------------------------------------------------------------------------
// ROOT Input/Output
//-------------------------------------------------------------------------
void CalibCaloHitColl::Streamer(TBuffer& iobuffer) {
    unsigned int start = 0;
    unsigned int byte_count = 0;
    
    //-------------------------------------------------------------------------
    // Read objects from buffer
    //-------------------------------------------------------------------------
    if (iobuffer.IsReading()) {
        Version_t original_version = iobuffer.ReadVersion(&start, &byte_count);
        StorableObject::Streamer(iobuffer);
        container_.Streamer(iobuffer);
        iobuffer.CheckByteCount(start, byte_count, CalibCaloHitColl::IsA());
    } else if (iobuffer.IsWriting()) {
        byte_count = iobuffer.WriteVersion(CalibCaloHitColl::IsA(), kTRUE);
        Version_t current_version = class_version();
        
        StorableObject::Streamer(iobuffer);
        container_.Streamer(iobuffer);
        
        iobuffer.SetByteCount(byte_count, kTRUE);
    } else {
        std::cerr 
        << " CalibCaloHitColl::Streamer(TBuffer& iobuffer) - buffer in unknown state" 
        << std::endl;
    }
}

//-------------------------------------------------------------------------
// ROOT Input/Output Hook
//-------------------------------------------------------------------------
ClassImp(CalibCaloHitColl)





