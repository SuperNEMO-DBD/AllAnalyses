//
//  N3CalorimeterHitColl.cpp
//  SNemoCoreExample
//
//  Created by Stefano Torre on 02/07/11.
//  Copyright 2011 Univesity College London. All rights reserved.
//

#include "NemoObjects/N3CalorimeterHitColl.h"

//-------------------------------------------------------------------------
// Creation
//-------------------------------------------------------------------------
N3CalorimeterHitColl::N3CalorimeterHitColl() : StorableObject(){
}

N3CalorimeterHitColl::N3CalorimeterHitColl(const N3CalorimeterHitColl& rhs) :
StorableObject(rhs), 
container_(rhs.container_)
{
}

N3CalorimeterHitColl* N3CalorimeterHitColl::clone() {
    return new N3CalorimeterHitColl(*this);
}

//-------------------------------------------------------------------------
// Assignment
//-------------------------------------------------------------------------
N3CalorimeterHitColl& N3CalorimeterHitColl::operator=(const N3CalorimeterHitColl& rhs) {
    if (this != &rhs) {
        container_ = rhs.container_;
    }
    return *this;
}

//-------------------------------------------------------------------------
// EDM requirements
//-------------------------------------------------------------------------
void N3CalorimeterHitColl::destroy() {
    N3CalorimeterHitColl::deallocate();
    delete this;
}

void N3CalorimeterHitColl::deallocate() {
    StorableObject::deallocate();
}

//-------------------------------------------------------------------------
// Destruction
//-------------------------------------------------------------------------
N3CalorimeterHitColl::~N3CalorimeterHitColl() {
    
}

//-------------------------------------------------------------------------
// Classifiers
//-------------------------------------------------------------------------
std::string N3CalorimeterHitColl::class_name() const {
    return N3CalorimeterHitColl::Class_Name();
}

Version_t N3CalorimeterHitColl::class_version() const {
    return N3CalorimeterHitColl::Class_Version();
}

//-------------------------------------------------------------------------
// Iostream
//-------------------------------------------------------------------------
void N3CalorimeterHitColl::print(std::ostream& os) const {
    os 
    << "===================================================================="
    << std::endl
    << "Contents of N3CalorimeterHitColl: description = " << description()
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
bool N3CalorimeterHitColl::postread(EventRecord* per) {
    bool status = true;
    
    for (N3CalorimeterHitColl::iterator hitIter = contents().begin();
         hitIter != contents().end(); hitIter++) {
        status &= (*hitIter).postread(per);
    }

    return status;
}

//-------------------------------------------------------------------------
// StorableObject Locators
//-------------------------------------------------------------------------
bool N3CalorimeterHitColl::find(EventRecord* pEvent, N3CalorimeterHitColl_ch& crHandle) {
    EventRecord::ConstIterator ciEvent(pEvent, "N3CalorimeterHitColl");
    if (ciEvent.is_invalid()) {
        return false;
    } else {
        crHandle = N3CalorimeterHitColl_ch(ciEvent);
        return true;
    }
}

bool N3CalorimeterHitColl::find(EventRecord* pEvent, N3CalorimeterHitColl_ch& crHandle,
                            const std::string& description) {
    StorableObject::SelectByDescription selector(description);
    EventRecord::ConstIterator ciEvent(pEvent, selector);
    
    if (ciEvent.is_invalid()) {
        return false;
    } else  {
        crHandle = N3CalorimeterHitColl_ch(ciEvent);
        return true;
    }
}


//-------------------------------------------------------------------------
// ROOT Input/Output
//-------------------------------------------------------------------------
void N3CalorimeterHitColl::Streamer(TBuffer& iobuffer) {
    unsigned int start = 0;
    unsigned int byte_count = 0;
    
    //-------------------------------------------------------------------------
    // Read objects from buffer
    //-------------------------------------------------------------------------
    if (iobuffer.IsReading()) {
        Version_t original_version = iobuffer.ReadVersion(&start, &byte_count);
        StorableObject::Streamer(iobuffer);
        container_.Streamer(iobuffer);
        iobuffer.CheckByteCount(start, byte_count, N3CalorimeterHitColl::IsA());
    } else if (iobuffer.IsWriting()) {
        byte_count = iobuffer.WriteVersion(N3CalorimeterHitColl::IsA(), kTRUE);
        Version_t current_version = class_version();
        
        StorableObject::Streamer(iobuffer);
        container_.Streamer(iobuffer);
        
        iobuffer.SetByteCount(byte_count, kTRUE);
    } else {
        std::cerr 
        << " N3CalorimeterHitColl::Streamer(TBuffer& iobuffer) - buffer in unknown state" 
        << std::endl;
    }
}

//-------------------------------------------------------------------------
// ROOT Input/Output Hook
//-------------------------------------------------------------------------
ClassImp(N3CalorimeterHitColl)





