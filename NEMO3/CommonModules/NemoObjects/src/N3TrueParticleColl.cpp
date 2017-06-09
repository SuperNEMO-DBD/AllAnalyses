//
//  N3TrueParticleColl.cpp
//
//  Created by Stefano Torre on 19/09/11.
//

#include "NemoObjects/N3TrueParticleColl.h"

//-------------------------------------------------------------------------
// Creation
//-------------------------------------------------------------------------
N3TrueParticleColl::N3TrueParticleColl() : StorableObject() {
    
}

N3TrueParticleColl::N3TrueParticleColl(const N3TrueParticleColl& rhs) :
StorableObject(rhs),
container_(rhs.container_) {
    
}

N3TrueParticleColl* N3TrueParticleColl::clone() {
    return new N3TrueParticleColl(*this);
}

//-------------------------------------------------------------------------
// Assignment
//-------------------------------------------------------------------------
N3TrueParticleColl& N3TrueParticleColl::operator=(const N3TrueParticleColl& rhs) {
    if (this != &rhs) {
        container_ = rhs.container_;
    }
    return *this;
}

//-------------------------------------------------------------------------
// EDM requirements
//-------------------------------------------------------------------------
void N3TrueParticleColl::destroy() {
    N3TrueParticleColl::deallocate();
    delete this;
}

void N3TrueParticleColl::deallocate() {
    StorableObject::deallocate();
}

//-------------------------------------------------------------------------
// Destruction
//-------------------------------------------------------------------------
N3TrueParticleColl::~N3TrueParticleColl() {
    
}

//-------------------------------------------------------------------------
// Classifiers
//-------------------------------------------------------------------------
std::string N3TrueParticleColl::class_name() const {
    return N3TrueParticleColl::Class_Name();
}

Version_t N3TrueParticleColl::class_version() const {
    return N3TrueParticleColl::Class_Version();
}

//-------------------------------------------------------------------------
// Iostream
//-------------------------------------------------------------------------
void N3TrueParticleColl::print(std::ostream& os) const {
    os 
    << "===================================================================="
    << std::endl
    << "Contents of N3TrueParticleColl: description = " << description()
    << " process name = " << process_name() << std::endl
    << "  Number of N3True Particles in collection = " << container_.contents().size()
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
bool N3TrueParticleColl::postread(EventRecord* per) {
    bool status = true;
    
    for (N3TrueParticleColl::iterator hitIter = contents().begin();
         hitIter != contents().end(); hitIter++) {
        status &= (*hitIter).postread(per);
    }
    
    return status;
}

//-------------------------------------------------------------------------
// StorableObject Locators
//-------------------------------------------------------------------------
bool N3TrueParticleColl::find(EventRecord* pEvent, N3TrueParticleColl_ch& crHandle) {
    EventRecord::ConstIterator ciEvent(pEvent, "N3TrueParticleColl");
    if (ciEvent.is_invalid()) {
        return false;
    } else {
        crHandle = N3TrueParticleColl_ch(ciEvent);
        return true;
    }
}

bool N3TrueParticleColl::find(EventRecord* pEvent, N3TrueParticleColl_ch& crHandle,
                             const std::string& description) {
    StorableObject::SelectByDescription selector(description);
    EventRecord::ConstIterator ciEvent(pEvent, selector);
    
    if (ciEvent.is_invalid()) {
        return false;
    } else  {
        crHandle = N3TrueParticleColl_ch(ciEvent);
        return true;
    }
}

//-------------------------------------------------------------------------
// ROOT Input/Output
//-------------------------------------------------------------------------
void N3TrueParticleColl::Streamer(TBuffer& iobuffer) {
    unsigned int start = 0;
    unsigned int byte_count = 0;
    
    //-------------------------------------------------------------------------
    // Read objects from buffer
    //-------------------------------------------------------------------------
    if (iobuffer.IsReading()) {
        Version_t original_version = iobuffer.ReadVersion(&start, &byte_count);
        StorableObject::Streamer(iobuffer);
        container_.Streamer(iobuffer);
        iobuffer.CheckByteCount(start, byte_count, N3TrueParticleColl::IsA());
    } else if (iobuffer.IsWriting()) {
        byte_count = iobuffer.WriteVersion(N3TrueParticleColl::IsA(), kTRUE);
        Version_t current_version = class_version();
        
        StorableObject::Streamer(iobuffer);
        container_.Streamer(iobuffer);
        
        iobuffer.SetByteCount(byte_count, kTRUE);
    } else {
        std::cerr 
        << " N3TrueParticleColl::Streamer(TBuffer& iobuffer) - buffer in unknown state" 
        << std::endl;
    }
}

//-------------------------------------------------------------------------
// ROOT Input/Output Hook
//-------------------------------------------------------------------------
ClassImp(N3TrueParticleColl)





