//
//  N3TrackSegmentColl.cpp
//
//  Created by Stefano Torre on 17/02/12.
//

#include "NemoObjects/N3TrackSegmentColl.h"

//-------------------------------------------------------------------------
// Creation
//-------------------------------------------------------------------------
N3TrackSegmentColl::N3TrackSegmentColl() : StorableObject() {
    
}

N3TrackSegmentColl::N3TrackSegmentColl(const N3TrackSegmentColl& rhs) :
StorableObject(rhs),
container_(rhs.container_) {
    
}

N3TrackSegmentColl* N3TrackSegmentColl::clone() {
    return new N3TrackSegmentColl(*this);
}

//-------------------------------------------------------------------------
// Assignment
//-------------------------------------------------------------------------
N3TrackSegmentColl& N3TrackSegmentColl::operator=(const N3TrackSegmentColl& rhs) {
    if (this != &rhs) {
        container_ = rhs.container_;
    }
    return *this;
}

//-------------------------------------------------------------------------
// EDM requirements
//-------------------------------------------------------------------------
void N3TrackSegmentColl::destroy() {
    N3TrackSegmentColl::deallocate();
    delete this;
}

void N3TrackSegmentColl::deallocate() {
    StorableObject::deallocate();
}

//-------------------------------------------------------------------------
// Destruction
//-------------------------------------------------------------------------
N3TrackSegmentColl::~N3TrackSegmentColl() {
    
}

//-------------------------------------------------------------------------
// Classifiers
//-------------------------------------------------------------------------
std::string N3TrackSegmentColl::class_name() const {
    return N3TrackSegmentColl::Class_Name();
}

Version_t N3TrackSegmentColl::class_version() const {
    return N3TrackSegmentColl::Class_Version();
}

//-------------------------------------------------------------------------
// Iostream
//-------------------------------------------------------------------------
void N3TrackSegmentColl::print(std::ostream& os) const {
    os 
    << "===================================================================="
    << std::endl
    << "Contents of N3TrackSegmentColl: description = " << description()
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
bool N3TrackSegmentColl::postread(EventRecord* per) {
    bool status = true;
    
    for (N3TrackSegmentColl::iterator hitIter = contents().begin();
         hitIter != contents().end(); hitIter++) {
        status &= (*hitIter).postread(per);
    }
    
    return status;
}

//-------------------------------------------------------------------------
// StorableObject Locators
//-------------------------------------------------------------------------
bool N3TrackSegmentColl::find(EventRecord* pEvent, N3TrackSegmentColl_ch& crHandle) {
    EventRecord::ConstIterator ciEvent(pEvent, "N3TrackSegmentColl");
    if (ciEvent.is_invalid()) {
        return false;
    } else {
        crHandle = N3TrackSegmentColl_ch(ciEvent);
        return true;
    }
}

bool N3TrackSegmentColl::find(EventRecord* pEvent, N3TrackSegmentColl_ch& crHandle,
                            const std::string& description) {
    StorableObject::SelectByDescription selector(description);
    EventRecord::ConstIterator ciEvent(pEvent, selector);
    
    if (ciEvent.is_invalid()) {
        return false;
    } else  {
        crHandle = N3TrackSegmentColl_ch(ciEvent);
        return true;
    }
}

//-------------------------------------------------------------------------
// ROOT Input/Output
//-------------------------------------------------------------------------
void N3TrackSegmentColl::Streamer(TBuffer& iobuffer) {
    unsigned int start = 0;
    unsigned int byte_count = 0;
    
    //-------------------------------------------------------------------------
    // Read objects from buffer
    //-------------------------------------------------------------------------
    if (iobuffer.IsReading()) {
        Version_t original_version = iobuffer.ReadVersion(&start, &byte_count);
        StorableObject::Streamer(iobuffer);
        container_.Streamer(iobuffer);
        iobuffer.CheckByteCount(start, byte_count, N3TrackSegmentColl::IsA());
    } else if (iobuffer.IsWriting()) {
        byte_count = iobuffer.WriteVersion(N3TrackSegmentColl::IsA(), kTRUE);
        Version_t current_version = class_version();
        
        StorableObject::Streamer(iobuffer);
        container_.Streamer(iobuffer);
        
        iobuffer.SetByteCount(byte_count, kTRUE);
    } else {
        std::cerr 
        << " N3TrackSegmentColl::Streamer(TBuffer& iobuffer) - buffer in unknown state" 
        << std::endl;
    }
}

//-------------------------------------------------------------------------
// ROOT Input/Output Hook
//-------------------------------------------------------------------------
ClassImp(N3TrackSegmentColl)





