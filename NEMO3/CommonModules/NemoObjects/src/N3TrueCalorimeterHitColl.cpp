//
//  N3TrueCalorimeterHitColl.cpp
//
//  Created by Stefano Torre on 31/12/11.
//

#include "NemoObjects/N3TrueCalorimeterHitColl.h"

//-------------------------------------------------------------------------
// Creation
//-------------------------------------------------------------------------
N3TrueCalorimeterHitColl::N3TrueCalorimeterHitColl() : StorableObject() {
    
}

N3TrueCalorimeterHitColl::N3TrueCalorimeterHitColl(const N3TrueCalorimeterHitColl& rhs) :
StorableObject(rhs),
container_(rhs.container_) {
    
}

N3TrueCalorimeterHitColl* N3TrueCalorimeterHitColl::clone() {
    return new N3TrueCalorimeterHitColl(*this);
}

//-------------------------------------------------------------------------
// Assignment
//-------------------------------------------------------------------------
N3TrueCalorimeterHitColl& N3TrueCalorimeterHitColl::operator=(const N3TrueCalorimeterHitColl& rhs) {
    if (this != &rhs) {
        container_ = rhs.container_;
    }
    return *this;
}

//-------------------------------------------------------------------------
// EDM requirements
//-------------------------------------------------------------------------
void N3TrueCalorimeterHitColl::destroy() {
    N3TrueCalorimeterHitColl::deallocate();
    delete this;
}

void N3TrueCalorimeterHitColl::deallocate() {
    StorableObject::deallocate();
}

//-------------------------------------------------------------------------
// Destruction
//-------------------------------------------------------------------------
N3TrueCalorimeterHitColl::~N3TrueCalorimeterHitColl() {
    
}

//-------------------------------------------------------------------------
// Classifiers
//-------------------------------------------------------------------------
std::string N3TrueCalorimeterHitColl::class_name() const {
    return N3TrueCalorimeterHitColl::Class_Name();
}

Version_t N3TrueCalorimeterHitColl::class_version() const {
    return N3TrueCalorimeterHitColl::Class_Version();
}

//-------------------------------------------------------------------------
// Iostream
//-------------------------------------------------------------------------
void N3TrueCalorimeterHitColl::print(std::ostream& os) const {
    os 
    << "===================================================================="
    << std::endl
    << "Contents of N3TrueCalorimeterHitColl: description = " << description()
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
bool N3TrueCalorimeterHitColl::postread(EventRecord* per) {
    bool status = true;
    
    for (N3TrueCalorimeterHitColl::iterator hitIter = contents().begin();
         hitIter != contents().end(); hitIter++) {
        status &= (*hitIter).postread(per);
    }
    
    return status;
}

//-------------------------------------------------------------------------
// StorableObject Locators
//-------------------------------------------------------------------------
bool N3TrueCalorimeterHitColl::find(EventRecord* pEvent, N3TrueCalorimeterHitColl_ch& crHandle) {
    EventRecord::ConstIterator ciEvent(pEvent, "N3TrueCalorimeterHitColl");
    if (ciEvent.is_invalid()) {
        return false;
    } else {
        crHandle = N3TrueCalorimeterHitColl_ch(ciEvent);
        return true;
    }
}

bool N3TrueCalorimeterHitColl::find(EventRecord* pEvent, N3TrueCalorimeterHitColl_ch& crHandle,
                            const std::string& description) {
    StorableObject::SelectByDescription selector(description);
    EventRecord::ConstIterator ciEvent(pEvent, selector);
    
    if (ciEvent.is_invalid()) {
        return false;
    } else  {
        crHandle = N3TrueCalorimeterHitColl_ch(ciEvent);
        return true;
    }
}

//-------------------------------------------------------------------------
// ROOT Input/Output
//-------------------------------------------------------------------------
void N3TrueCalorimeterHitColl::Streamer(TBuffer& iobuffer) {
    unsigned int start = 0;
    unsigned int byte_count = 0;
    
    //-------------------------------------------------------------------------
    // Read objects from buffer
    //-------------------------------------------------------------------------
    if (iobuffer.IsReading()) {
        Version_t original_version = iobuffer.ReadVersion(&start, &byte_count);
        StorableObject::Streamer(iobuffer);
        container_.Streamer(iobuffer);
        iobuffer.CheckByteCount(start, byte_count, N3TrueCalorimeterHitColl::IsA());
    } else if (iobuffer.IsWriting()) {
        byte_count = iobuffer.WriteVersion(N3TrueCalorimeterHitColl::IsA(), kTRUE);
        Version_t current_version = class_version();
        
        StorableObject::Streamer(iobuffer);
        container_.Streamer(iobuffer);
        
        iobuffer.SetByteCount(byte_count, kTRUE);
    } else {
        std::cerr 
        << " N3TrueCalorimeterHitColl::Streamer(TBuffer& iobuffer) - buffer in unknown state" 
        << std::endl;
    }
}

//-------------------------------------------------------------------------
// ROOT Input/Output Hook
//-------------------------------------------------------------------------
ClassImp(N3TrueCalorimeterHitColl)





