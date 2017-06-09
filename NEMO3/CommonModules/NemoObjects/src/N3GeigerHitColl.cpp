//
//  N3GeigerHitColl.cpp
//  SNemoCoreExample
//
//  Created by Stefano Torre on 02/07/11.
//  Copyright 2011 Univesity College London. All rights reserved.
//

#include "NemoObjects/N3GeigerHitColl.h"

//-------------------------------------------------------------------------
// Creation
//-------------------------------------------------------------------------
N3GeigerHitColl::N3GeigerHitColl() : StorableObject() {
    
}

N3GeigerHitColl::N3GeigerHitColl(const N3GeigerHitColl& rhs) :
StorableObject(rhs),
container_(rhs.container_) {
    
}

N3GeigerHitColl* N3GeigerHitColl::clone() {
    return new N3GeigerHitColl(*this);
}

//-------------------------------------------------------------------------
// Assignment
//-------------------------------------------------------------------------
N3GeigerHitColl& N3GeigerHitColl::operator=(const N3GeigerHitColl& rhs) {
    if (this != &rhs) {
        container_ = rhs.container_;
    }
    return *this;
}

//-------------------------------------------------------------------------
// EDM requirements
//-------------------------------------------------------------------------
void N3GeigerHitColl::destroy() {
    N3GeigerHitColl::deallocate();
    delete this;
}

void N3GeigerHitColl::deallocate() {
    StorableObject::deallocate();
}

//-------------------------------------------------------------------------
// Destruction
//-------------------------------------------------------------------------
N3GeigerHitColl::~N3GeigerHitColl() {
    
}

//-------------------------------------------------------------------------
// Classifiers
//-------------------------------------------------------------------------
std::string N3GeigerHitColl::class_name() const {
    return N3GeigerHitColl::Class_Name();
}

Version_t N3GeigerHitColl::class_version() const {
    return N3GeigerHitColl::Class_Version();
}

//-------------------------------------------------------------------------
// Iostream
//-------------------------------------------------------------------------
void N3GeigerHitColl::print(std::ostream& os) const {
    os 
    << "===================================================================="
    << std::endl
    << "Contents of N3GeigerHitColl: description = " << description()
    << " process name = " << process_name() << std::endl
    << "  Number of Geiger Hits in collection = " << container_.contents().size()
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
bool N3GeigerHitColl::postread(EventRecord* per) {
    bool status = true;
    
    for (N3GeigerHitColl::iterator hitIter = contents().begin();
         hitIter != contents().end(); hitIter++) {
        status &= (*hitIter).postread(per);
    }
    
    return status;
}

//-------------------------------------------------------------------------
// StorableObject Locators
//-------------------------------------------------------------------------
bool N3GeigerHitColl::find(EventRecord* pEvent, N3GeigerHitColl_ch& crHandle) {
    EventRecord::ConstIterator ciEvent(pEvent, "N3GeigerHitColl");
    if (ciEvent.is_invalid()) {
        return false;
    } else {
        crHandle = N3GeigerHitColl_ch(ciEvent);
        return true;
    }
}

bool N3GeigerHitColl::find(EventRecord* pEvent, N3GeigerHitColl_ch& crHandle,
                            const std::string& description) {
    StorableObject::SelectByDescription selector(description);
    EventRecord::ConstIterator ciEvent(pEvent, selector);
    
    if (ciEvent.is_invalid()) {
        return false;
    } else  {
        crHandle = N3GeigerHitColl_ch(ciEvent);
        return true;
    }
}

//-------------------------------------------------------------------------
// ROOT Input/Output
//-------------------------------------------------------------------------
void N3GeigerHitColl::Streamer(TBuffer& iobuffer) {
    unsigned int start = 0;
    unsigned int byte_count = 0;
    
    //-------------------------------------------------------------------------
    // Read objects from buffer
    //-------------------------------------------------------------------------
    if (iobuffer.IsReading()) {
        Version_t original_version = iobuffer.ReadVersion(&start, &byte_count);
        StorableObject::Streamer(iobuffer);
        container_.Streamer(iobuffer);
        iobuffer.CheckByteCount(start, byte_count, N3GeigerHitColl::IsA());
    } else if (iobuffer.IsWriting()) {
        byte_count = iobuffer.WriteVersion(N3GeigerHitColl::IsA(), kTRUE);
        Version_t current_version = class_version();
        
        StorableObject::Streamer(iobuffer);
        container_.Streamer(iobuffer);
        
        iobuffer.SetByteCount(byte_count, kTRUE);
    } else {
        std::cerr 
        << " N3GeigerHitColl::Streamer(TBuffer& iobuffer) - buffer in unknown state" 
        << std::endl;
    }
}

//-------------------------------------------------------------------------
// ROOT Input/Output Hook
//-------------------------------------------------------------------------
ClassImp(N3GeigerHitColl)





