//
//  N3TrueVertexColl.cpp
//
//  Created by Stefano Torre on 19/09/11.
//

#include "NemoObjects/N3TrueVertexColl.h"

//-------------------------------------------------------------------------
// Creation
//-------------------------------------------------------------------------
N3TrueVertexColl::N3TrueVertexColl() : StorableObject() {
    
}

N3TrueVertexColl::N3TrueVertexColl(const N3TrueVertexColl& rhs) :
StorableObject(rhs),
container_(rhs.container_) {
    
}

N3TrueVertexColl* N3TrueVertexColl::clone() {
    return new N3TrueVertexColl(*this);
}

//-------------------------------------------------------------------------
// Assignment
//-------------------------------------------------------------------------
N3TrueVertexColl& N3TrueVertexColl::operator=(const N3TrueVertexColl& rhs) {
    if (this != &rhs) {
        container_ = rhs.container_;
    }
    return *this;
}

//-------------------------------------------------------------------------
// EDM requirements
//-------------------------------------------------------------------------
void N3TrueVertexColl::destroy() {
    N3TrueVertexColl::deallocate();
    delete this;
}

void N3TrueVertexColl::deallocate() {
    StorableObject::deallocate();
}

//-------------------------------------------------------------------------
// Destruction
//-------------------------------------------------------------------------
N3TrueVertexColl::~N3TrueVertexColl() {
    
}

//-------------------------------------------------------------------------
// Classifiers
//-------------------------------------------------------------------------
std::string N3TrueVertexColl::class_name() const {
    return N3TrueVertexColl::Class_Name();
}

Version_t N3TrueVertexColl::class_version() const {
    return N3TrueVertexColl::Class_Version();
}

//-------------------------------------------------------------------------
// Iostream
//-------------------------------------------------------------------------
void N3TrueVertexColl::print(std::ostream& os) const {
    os 
    << "===================================================================="
    << std::endl
    << "Contents of N3TrueVertexColl: description = " << description()
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
bool N3TrueVertexColl::postread(EventRecord* per) {
    bool status = true;
    
    for (N3TrueVertexColl::iterator hitIter = contents().begin();
         hitIter != contents().end(); hitIter++) {
        status &= (*hitIter).postread(per);
    }
    
    return status;
}

//-------------------------------------------------------------------------
// StorableObject Locators
//-------------------------------------------------------------------------
bool N3TrueVertexColl::find(EventRecord* pEvent, N3TrueVertexColl_ch& crHandle) {
    EventRecord::ConstIterator ciEvent(pEvent, "N3TrueVertexColl");
    if (ciEvent.is_invalid()) {
        return false;
    } else {
        crHandle = N3TrueVertexColl_ch(ciEvent);
        return true;
    }
}

bool N3TrueVertexColl::find(EventRecord* pEvent, N3TrueVertexColl_ch& crHandle,
                             const std::string& description) {
    StorableObject::SelectByDescription selector(description);
    EventRecord::ConstIterator ciEvent(pEvent, selector);
    
    if (ciEvent.is_invalid()) {
        return false;
    } else  {
        crHandle = N3TrueVertexColl_ch(ciEvent);
        return true;
    }
}

//-------------------------------------------------------------------------
// ROOT Input/Output
//-------------------------------------------------------------------------
void N3TrueVertexColl::Streamer(TBuffer& iobuffer) {
    unsigned int start = 0;
    unsigned int byte_count = 0;
    
    //-------------------------------------------------------------------------
    // Read objects from buffer
    //-------------------------------------------------------------------------
    if (iobuffer.IsReading()) {
        Version_t original_version = iobuffer.ReadVersion(&start, &byte_count);
        StorableObject::Streamer(iobuffer);
        container_.Streamer(iobuffer);
        iobuffer.CheckByteCount(start, byte_count, N3TrueVertexColl::IsA());
    } else if (iobuffer.IsWriting()) {
        byte_count = iobuffer.WriteVersion(N3TrueVertexColl::IsA(), kTRUE);
        Version_t current_version = class_version();
        
        StorableObject::Streamer(iobuffer);
        container_.Streamer(iobuffer);
        
        iobuffer.SetByteCount(byte_count, kTRUE);
    } else {
        std::cerr 
        << " N3TrueVertexColl::Streamer(TBuffer& iobuffer) - buffer in unknown state" 
        << std::endl;
    }
}

//-------------------------------------------------------------------------
// ROOT Input/Output Hook
//-------------------------------------------------------------------------
ClassImp(N3TrueVertexColl)





