//
//  GammaClusterColl.cpp
//
//  Created by Summer Blot 20.6.13
//

#include "NemoObjects/GammaClusterColl.h"

//-------------------------------------------------------------------------
// Creation
//-------------------------------------------------------------------------
GammaClusterColl::GammaClusterColl() : StorableObject() {
    
}

GammaClusterColl::GammaClusterColl(const GammaClusterColl& rhs) :
StorableObject(rhs),
container_(rhs.container_) {
    
}

GammaClusterColl* GammaClusterColl::clone() {
    return new GammaClusterColl(*this);
}

//-------------------------------------------------------------------------
// Assignment
//-------------------------------------------------------------------------
GammaClusterColl& GammaClusterColl::operator=(const GammaClusterColl& rhs) {
    if (this != &rhs) {
        container_ = rhs.container_;
    }
    return *this;
}

//-------------------------------------------------------------------------
// EDM requirements
//-------------------------------------------------------------------------
void GammaClusterColl::destroy() {
    GammaClusterColl::deallocate();
    delete this;
}

void GammaClusterColl::deallocate() {
    StorableObject::deallocate();
}

//-------------------------------------------------------------------------
// Destruction
//-------------------------------------------------------------------------
GammaClusterColl::~GammaClusterColl() {
    
}

//-------------------------------------------------------------------------
// Classifiers
//-------------------------------------------------------------------------
std::string GammaClusterColl::class_name() const {
    return GammaClusterColl::Class_Name();
}

Version_t GammaClusterColl::class_version() const {
    return GammaClusterColl::Class_Version();
}

//-------------------------------------------------------------------------
// Iostream
//-------------------------------------------------------------------------
void GammaClusterColl::print(std::ostream& os) const {
    os 
    << "===================================================================="
    << std::endl
    << "Contents of GammaClusterColl: description = " << description()
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
bool GammaClusterColl::postread(EventRecord* per) {
    bool status = true;
    
    for (GammaClusterColl::iterator hitIter = contents().begin();
         hitIter != contents().end(); hitIter++) {
        status &= (*hitIter).postread(per);
    }
    
    return status;
}

//-------------------------------------------------------------------------
// StorableObject Locators
//-------------------------------------------------------------------------
bool GammaClusterColl::find(EventRecord* pEvent, GammaClusterColl_ch& crHandle) {
    EventRecord::ConstIterator ciEvent(pEvent, "GammaClusterColl");
    if (ciEvent.is_invalid()) {
        return false;
    } else {
        crHandle = GammaClusterColl_ch(ciEvent);
        return true;
    }
}

bool GammaClusterColl::find(EventRecord* pEvent, GammaClusterColl_ch& crHandle,
                            const std::string& description) {
    StorableObject::SelectByDescription selector(description);
    EventRecord::ConstIterator ciEvent(pEvent, selector);
    
    if (ciEvent.is_invalid()) {
        return false;
    } else  {
        crHandle = GammaClusterColl_ch(ciEvent);
        return true;
    }
}

//-------------------------------------------------------------------------
// ROOT Input/Output
//-------------------------------------------------------------------------
void GammaClusterColl::Streamer(TBuffer& iobuffer) {
    unsigned int start = 0;
    unsigned int byte_count = 0;
    
    //-------------------------------------------------------------------------
    // Read objects from buffer
    //-------------------------------------------------------------------------
    if (iobuffer.IsReading()) {
        Version_t original_version = iobuffer.ReadVersion(&start, &byte_count);
        StorableObject::Streamer(iobuffer);
        container_.Streamer(iobuffer);
        iobuffer.CheckByteCount(start, byte_count, GammaClusterColl::IsA());
    } else if (iobuffer.IsWriting()) {
        byte_count = iobuffer.WriteVersion(GammaClusterColl::IsA(), kTRUE);
        Version_t current_version = class_version();
        
        StorableObject::Streamer(iobuffer);
        container_.Streamer(iobuffer);
        
        iobuffer.SetByteCount(byte_count, kTRUE);
    } else {
        std::cerr 
        << " GammaClusterColl::Streamer(TBuffer& iobuffer) - buffer in unknown state" 
        << std::endl;
    }
}

//-------------------------------------------------------------------------
// ROOT Input/Output Hook
//-------------------------------------------------------------------------
ClassImp(GammaClusterColl)





