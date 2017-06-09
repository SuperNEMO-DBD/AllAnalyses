//
//  GammaColl.cpp
//
//  Created by Stefano Torre on 09/05/12.
//

#include "NemoObjects/GammaColl.h"

//-------------------------------------------------------------------------
// Creation
//-------------------------------------------------------------------------
GammaColl::GammaColl() : StorableObject() {
    
}

GammaColl::GammaColl(const GammaColl& rhs) :
StorableObject(rhs),
container_(rhs.container_) {
    
}

GammaColl* GammaColl::clone() {
    return new GammaColl(*this);
}

//-------------------------------------------------------------------------
// Assignment
//-------------------------------------------------------------------------
GammaColl& GammaColl::operator=(const GammaColl& rhs) {
    if (this != &rhs) {
        container_ = rhs.container_;
    }
    return *this;
}

//-------------------------------------------------------------------------
// EDM requirements
//-------------------------------------------------------------------------
void GammaColl::destroy() {
    GammaColl::deallocate();
    delete this;
}

void GammaColl::deallocate() {
    StorableObject::deallocate();
}

//-------------------------------------------------------------------------
// Destruction
//-------------------------------------------------------------------------
GammaColl::~GammaColl() {
    
}

//-------------------------------------------------------------------------
// Classifiers
//-------------------------------------------------------------------------
std::string GammaColl::class_name() const {
    return GammaColl::Class_Name();
}

Version_t GammaColl::class_version() const {
    return GammaColl::Class_Version();
}

//-------------------------------------------------------------------------
// Iostream
//-------------------------------------------------------------------------
void GammaColl::print(std::ostream& os) const {
    os 
    << "===================================================================="
    << std::endl
    << "Contents of GammaColl: description = " << description()
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
bool GammaColl::postread(EventRecord* per) {
    bool status = true;
    
    for (GammaColl::iterator hitIter = contents().begin();
         hitIter != contents().end(); hitIter++) {
        status &= (*hitIter).postread(per);
    }
    
    return status;
}

//-------------------------------------------------------------------------
// StorableObject Locators
//-------------------------------------------------------------------------
bool GammaColl::find(EventRecord* pEvent, GammaColl_ch& crHandle) {
    EventRecord::ConstIterator ciEvent(pEvent, "GammaColl");
    if (ciEvent.is_invalid()) {
        return false;
    } else {
        crHandle = GammaColl_ch(ciEvent);
        return true;
    }
}

bool GammaColl::find(EventRecord* pEvent, GammaColl_ch& crHandle,
                            const std::string& description) {
    StorableObject::SelectByDescription selector(description);
    EventRecord::ConstIterator ciEvent(pEvent, selector);
    
    if (ciEvent.is_invalid()) {
        return false;
    } else  {
        crHandle = GammaColl_ch(ciEvent);
        return true;
    }
}

//-------------------------------------------------------------------------
// ROOT Input/Output
//-------------------------------------------------------------------------
void GammaColl::Streamer(TBuffer& iobuffer) {
    unsigned int start = 0;
    unsigned int byte_count = 0;
    
    //-------------------------------------------------------------------------
    // Read objects from buffer
    //-------------------------------------------------------------------------
    if (iobuffer.IsReading()) {
        Version_t original_version = iobuffer.ReadVersion(&start, &byte_count);
        StorableObject::Streamer(iobuffer);
        container_.Streamer(iobuffer);
        iobuffer.CheckByteCount(start, byte_count, GammaColl::IsA());
    } else if (iobuffer.IsWriting()) {
        byte_count = iobuffer.WriteVersion(GammaColl::IsA(), kTRUE);
        Version_t current_version = class_version();
        
        StorableObject::Streamer(iobuffer);
        container_.Streamer(iobuffer);
        
        iobuffer.SetByteCount(byte_count, kTRUE);
    } else {
        std::cerr 
        << " GammaColl::Streamer(TBuffer& iobuffer) - buffer in unknown state" 
        << std::endl;
    }
}

//-------------------------------------------------------------------------
// ROOT Input/Output Hook
//-------------------------------------------------------------------------
ClassImp(GammaColl)





