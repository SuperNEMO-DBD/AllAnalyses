//
//  AlphaColl.cpp
//
//  Created by Stefano Torre on 09/05/12.
//

#include "NemoObjects/AlphaColl.h"

//-------------------------------------------------------------------------
// Creation
//-------------------------------------------------------------------------
AlphaColl::AlphaColl() : StorableObject() {
    
}

AlphaColl::AlphaColl(const AlphaColl& rhs) :
StorableObject(rhs),
container_(rhs.container_) {
    
}

AlphaColl* AlphaColl::clone() {
    return new AlphaColl(*this);
}

//-------------------------------------------------------------------------
// Assignment
//-------------------------------------------------------------------------
AlphaColl& AlphaColl::operator=(const AlphaColl& rhs) {
    if (this != &rhs) {
        container_ = rhs.container_;
    }
    return *this;
}

//-------------------------------------------------------------------------
// EDM requirements
//-------------------------------------------------------------------------
void AlphaColl::destroy() {
    AlphaColl::deallocate();
    delete this;
}

void AlphaColl::deallocate() {
    StorableObject::deallocate();
}

//-------------------------------------------------------------------------
// Destruction
//-------------------------------------------------------------------------
AlphaColl::~AlphaColl() {
    
}

//-------------------------------------------------------------------------
// Classifiers
//-------------------------------------------------------------------------
std::string AlphaColl::class_name() const {
    return AlphaColl::Class_Name();
}

Version_t AlphaColl::class_version() const {
    return AlphaColl::Class_Version();
}

//-------------------------------------------------------------------------
// Iostream
//-------------------------------------------------------------------------
void AlphaColl::print(std::ostream& os) const {
    os 
    << "===================================================================="
    << std::endl
    << "Contents of AlphaColl: description = " << description()
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
bool AlphaColl::postread(EventRecord* per) {
    bool status = true;
    
    for (AlphaColl::iterator hitIter = contents().begin();
         hitIter != contents().end(); hitIter++) {
        status &= (*hitIter).postread(per);
    }
    
    return status;
}

//-------------------------------------------------------------------------
// StorableObject Locators
//-------------------------------------------------------------------------
bool AlphaColl::find(EventRecord* pEvent, AlphaColl_ch& crHandle) {
    EventRecord::ConstIterator ciEvent(pEvent, "AlphaColl");
    if (ciEvent.is_invalid()) {
        return false;
    } else {
        crHandle = AlphaColl_ch(ciEvent);
        return true;
    }
}

bool AlphaColl::find(EventRecord* pEvent, AlphaColl_ch& crHandle,
                            const std::string& description) {
    StorableObject::SelectByDescription selector(description);
    EventRecord::ConstIterator ciEvent(pEvent, selector);
    
    if (ciEvent.is_invalid()) {
        return false;
    } else  {
        crHandle = AlphaColl_ch(ciEvent);
        return true;
    }
}

//-------------------------------------------------------------------------
// ROOT Input/Output
//-------------------------------------------------------------------------
void AlphaColl::Streamer(TBuffer& iobuffer) {
    unsigned int start = 0;
    unsigned int byte_count = 0;
    
    //-------------------------------------------------------------------------
    // Read objects from buffer
    //-------------------------------------------------------------------------
    if (iobuffer.IsReading()) {
        Version_t original_version = iobuffer.ReadVersion(&start, &byte_count);
        StorableObject::Streamer(iobuffer);
        container_.Streamer(iobuffer);
        iobuffer.CheckByteCount(start, byte_count, AlphaColl::IsA());
    } else if (iobuffer.IsWriting()) {
        byte_count = iobuffer.WriteVersion(AlphaColl::IsA(), kTRUE);
        Version_t current_version = class_version();
        
        StorableObject::Streamer(iobuffer);
        container_.Streamer(iobuffer);
        
        iobuffer.SetByteCount(byte_count, kTRUE);
    } else {
        std::cerr 
        << " AlphaColl::Streamer(TBuffer& iobuffer) - buffer in unknown state" 
        << std::endl;
    }
}

//-------------------------------------------------------------------------
// ROOT Input/Output Hook
//-------------------------------------------------------------------------
ClassImp(AlphaColl)





