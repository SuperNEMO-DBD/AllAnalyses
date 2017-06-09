//
//  N3TrueGeigerHitColl.cpp
//
//  Created by Stefano Torre on 02/07/11.
//

#include "NemoObjects/N3TrueGeigerHitColl.h"

//-------------------------------------------------------------------------
// Creation
//-------------------------------------------------------------------------
N3TrueGeigerHitColl::N3TrueGeigerHitColl() : StorableObject() {
    
}

N3TrueGeigerHitColl::N3TrueGeigerHitColl(const N3TrueGeigerHitColl& rhs) :
StorableObject(rhs),
container_(rhs.container_) {
    
}

N3TrueGeigerHitColl* N3TrueGeigerHitColl::clone() {
    return new N3TrueGeigerHitColl(*this);
}

//-------------------------------------------------------------------------
// Assignment
//-------------------------------------------------------------------------
N3TrueGeigerHitColl& N3TrueGeigerHitColl::operator=(const N3TrueGeigerHitColl& rhs) {
    if (this != &rhs) {
        container_ = rhs.container_;
    }
    return *this;
}

//-------------------------------------------------------------------------
// EDM requirements
//-------------------------------------------------------------------------
void N3TrueGeigerHitColl::destroy() {
    N3TrueGeigerHitColl::deallocate();
    delete this;
}

void N3TrueGeigerHitColl::deallocate() {
    StorableObject::deallocate();
}

//-------------------------------------------------------------------------
// Destruction
//-------------------------------------------------------------------------
N3TrueGeigerHitColl::~N3TrueGeigerHitColl() {
    
}

//-------------------------------------------------------------------------
// Classifiers
//-------------------------------------------------------------------------
std::string N3TrueGeigerHitColl::class_name() const {
    return N3TrueGeigerHitColl::Class_Name();
}

Version_t N3TrueGeigerHitColl::class_version() const {
    return N3TrueGeigerHitColl::Class_Version();
}

//-------------------------------------------------------------------------
// Iostream
//-------------------------------------------------------------------------
void N3TrueGeigerHitColl::print(std::ostream& os) const {
    os 
    << "===================================================================="
    << std::endl
    << "Contents of N3TrueGeigerHitColl: description = " << description()
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
bool N3TrueGeigerHitColl::postread(EventRecord* per) {
    bool status = true;
    
    for (N3TrueGeigerHitColl::iterator hitIter = contents().begin();
         hitIter != contents().end(); hitIter++) {
        status &= (*hitIter).postread(per);
    }
    
    return status;
}

//-------------------------------------------------------------------------
// StorableObject Locators
//-------------------------------------------------------------------------
bool N3TrueGeigerHitColl::find(EventRecord* pEvent, N3TrueGeigerHitColl_ch& crHandle) {
    EventRecord::ConstIterator ciEvent(pEvent, "N3TrueGeigerHitColl");
    if (ciEvent.is_invalid()) {
        return false;
    } else {
        crHandle = N3TrueGeigerHitColl_ch(ciEvent);
        return true;
    }
}

bool N3TrueGeigerHitColl::find(EventRecord* pEvent, N3TrueGeigerHitColl_ch& crHandle,
                            const std::string& description) {
    StorableObject::SelectByDescription selector(description);
    EventRecord::ConstIterator ciEvent(pEvent, selector);
    
    if (ciEvent.is_invalid()) {
        return false;
    } else  {
        crHandle = N3TrueGeigerHitColl_ch(ciEvent);
        return true;
    }
}

//-------------------------------------------------------------------------
// ROOT Input/Output
//-------------------------------------------------------------------------
void N3TrueGeigerHitColl::Streamer(TBuffer& iobuffer) {
    unsigned int start = 0;
    unsigned int byte_count = 0;
    
    //-------------------------------------------------------------------------
    // Read objects from buffer
    //-------------------------------------------------------------------------
    if (iobuffer.IsReading()) {
        Version_t original_version = iobuffer.ReadVersion(&start, &byte_count);
        StorableObject::Streamer(iobuffer);
        container_.Streamer(iobuffer);
        iobuffer.CheckByteCount(start, byte_count, N3TrueGeigerHitColl::IsA());
    } else if (iobuffer.IsWriting()) {
        byte_count = iobuffer.WriteVersion(N3TrueGeigerHitColl::IsA(), kTRUE);
        Version_t current_version = class_version();
        
        StorableObject::Streamer(iobuffer);
        container_.Streamer(iobuffer);
        
        iobuffer.SetByteCount(byte_count, kTRUE);
    } else {
        std::cerr 
        << " N3TrueGeigerHitColl::Streamer(TBuffer& iobuffer) - buffer in unknown state" 
        << std::endl;
    }
}

//-------------------------------------------------------------------------
// ROOT Input/Output Hook
//-------------------------------------------------------------------------
ClassImp(N3TrueGeigerHitColl)





