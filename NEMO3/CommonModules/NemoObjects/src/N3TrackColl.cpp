//
//  N3TrackColl.cpp
//  SNemoCoreExample
//
//  Created by Stefano Torre on 02/07/11.
//  Copyright 2011 Univesity College London. All rights reserved.
//

#include "NemoObjects/N3TrackColl.h"

//-------------------------------------------------------------------------
// Creation
//-------------------------------------------------------------------------
N3TrackColl::N3TrackColl() : StorableObject() {
    
}

N3TrackColl::N3TrackColl(const N3TrackColl& rhs) :
StorableObject(rhs),
container_(rhs.container_) {
    
}

N3TrackColl* N3TrackColl::clone() {
    return new N3TrackColl(*this);
}

//-------------------------------------------------------------------------
// Assignment
//-------------------------------------------------------------------------
N3TrackColl& N3TrackColl::operator=(const N3TrackColl& rhs) {
    if (this != &rhs) {
        container_ = rhs.container_;
    }
    return *this;
}

//-------------------------------------------------------------------------
// EDM requirements
//-------------------------------------------------------------------------
void N3TrackColl::destroy() {
    N3TrackColl::deallocate();
    delete this;
}

void N3TrackColl::deallocate() {
    StorableObject::deallocate();
}

//-------------------------------------------------------------------------
// Destruction
//-------------------------------------------------------------------------
N3TrackColl::~N3TrackColl() {
    
}

//-------------------------------------------------------------------------
// Classifiers
//-------------------------------------------------------------------------
std::string N3TrackColl::class_name() const {
    return N3TrackColl::Class_Name();
}

Version_t N3TrackColl::class_version() const {
    return N3TrackColl::Class_Version();
}

//-------------------------------------------------------------------------
// Iostream
//-------------------------------------------------------------------------
void N3TrackColl::print(std::ostream& os) const {
    os 
    << "===================================================================="
    << std::endl
    << "Contents of N3TrackColl: description = " << description()
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
bool N3TrackColl::postread(EventRecord* per) {
    bool status = true;
    
    for (N3TrackColl::iterator hitIter = contents().begin();
         hitIter != contents().end(); hitIter++) {
        status &= (*hitIter).postread(per);
    }
    
    return status;
}

//-------------------------------------------------------------------------
// StorableObject Locators
//-------------------------------------------------------------------------
bool N3TrackColl::find(EventRecord* pEvent, N3TrackColl_ch& crHandle) {
    EventRecord::ConstIterator ciEvent(pEvent, "N3TrackColl");
    if (ciEvent.is_invalid()) {
        return false;
    } else {
        crHandle = N3TrackColl_ch(ciEvent);
        return true;
    }
}

bool N3TrackColl::find(EventRecord* pEvent, N3TrackColl_ch& crHandle,
                            const std::string& description) {
    StorableObject::SelectByDescription selector(description);
    EventRecord::ConstIterator ciEvent(pEvent, selector);
    
    if (ciEvent.is_invalid()) {
        return false;
    } else  {
        crHandle = N3TrackColl_ch(ciEvent);
        return true;
    }
}

//-------------------------------------------------------------------------
// ROOT Input/Output
//-------------------------------------------------------------------------
void N3TrackColl::Streamer(TBuffer& iobuffer) {
    unsigned int start = 0;
    unsigned int byte_count = 0;
    
    //-------------------------------------------------------------------------
    // Read objects from buffer
    //-------------------------------------------------------------------------
    if (iobuffer.IsReading()) {
        Version_t original_version = iobuffer.ReadVersion(&start, &byte_count);
        StorableObject::Streamer(iobuffer);
        container_.Streamer(iobuffer);
        iobuffer.CheckByteCount(start, byte_count, N3TrackColl::IsA());
    } else if (iobuffer.IsWriting()) {
        byte_count = iobuffer.WriteVersion(N3TrackColl::IsA(), kTRUE);
        Version_t current_version = class_version();
        
        StorableObject::Streamer(iobuffer);
        container_.Streamer(iobuffer);
        
        iobuffer.SetByteCount(byte_count, kTRUE);
    } else {
        std::cerr 
        << " N3TrackColl::Streamer(TBuffer& iobuffer) - buffer in unknown state" 
        << std::endl;
    }
}

//-------------------------------------------------------------------------
// ROOT Input/Output Hook
//-------------------------------------------------------------------------
ClassImp(N3TrackColl)





