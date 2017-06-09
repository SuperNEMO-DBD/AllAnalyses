//
//  ElectronColl.cpp
//
//  Created by Stefano Torre on 09/05/12.
//

#include "NemoObjects/ElectronColl.h"

//-------------------------------------------------------------------------
// Creation
//-------------------------------------------------------------------------
ElectronColl::ElectronColl() : StorableObject() {
    
}

ElectronColl::ElectronColl(const ElectronColl& rhs) :
StorableObject(rhs),
container_(rhs.container_) {
    
}

ElectronColl* ElectronColl::clone() {
    return new ElectronColl(*this);
}

//-------------------------------------------------------------------------
// Assignment
//-------------------------------------------------------------------------
ElectronColl& ElectronColl::operator=(const ElectronColl& rhs) {
    if (this != &rhs) {
        container_ = rhs.container_;
    }
    return *this;
}

//-------------------------------------------------------------------------
// EDM requirements
//-------------------------------------------------------------------------
void ElectronColl::destroy() {
    ElectronColl::deallocate();
    delete this;
}

void ElectronColl::deallocate() {
    StorableObject::deallocate();
}

//-------------------------------------------------------------------------
// Destruction
//-------------------------------------------------------------------------
ElectronColl::~ElectronColl() {
    
}

//-------------------------------------------------------------------------
// Classifiers
//-------------------------------------------------------------------------
std::string ElectronColl::class_name() const {
    return ElectronColl::Class_Name();
}

Version_t ElectronColl::class_version() const {
    return ElectronColl::Class_Version();
}

//-------------------------------------------------------------------------
// Iostream
//-------------------------------------------------------------------------
void ElectronColl::print(std::ostream& os) const {
    os 
    << "===================================================================="
    << std::endl
    << "Contents of ElectronColl: description = " << description()
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
bool ElectronColl::postread(EventRecord* per) {
    bool status = true;
    
    for (ElectronColl::iterator hitIter = contents().begin();
         hitIter != contents().end(); hitIter++) {
        status &= (*hitIter).postread(per);
    }
    
    return status;
}

//-------------------------------------------------------------------------
// StorableObject Locators
//-------------------------------------------------------------------------
bool ElectronColl::find(EventRecord* pEvent, ElectronColl_ch& crHandle) {
    EventRecord::ConstIterator ciEvent(pEvent, "ElectronColl");
    if (ciEvent.is_invalid()) {
        return false;
    } else {
        crHandle = ElectronColl_ch(ciEvent);
        return true;
    }
}

bool ElectronColl::find(EventRecord* pEvent, ElectronColl_ch& crHandle,
                            const std::string& description) {
    StorableObject::SelectByDescription selector(description);
    EventRecord::ConstIterator ciEvent(pEvent, selector);
    
    if (ciEvent.is_invalid()) {
        return false;
    } else  {
        crHandle = ElectronColl_ch(ciEvent);
        return true;
    }
}

//-------------------------------------------------------------------------
// ROOT Input/Output
//-------------------------------------------------------------------------
void ElectronColl::Streamer(TBuffer& iobuffer) {
    unsigned int start = 0;
    unsigned int byte_count = 0;
    
    //-------------------------------------------------------------------------
    // Read objects from buffer
    //-------------------------------------------------------------------------
    if (iobuffer.IsReading()) {
        Version_t original_version = iobuffer.ReadVersion(&start, &byte_count);
        StorableObject::Streamer(iobuffer);
        container_.Streamer(iobuffer);
        iobuffer.CheckByteCount(start, byte_count, ElectronColl::IsA());
    } else if (iobuffer.IsWriting()) {
        byte_count = iobuffer.WriteVersion(ElectronColl::IsA(), kTRUE);
        Version_t current_version = class_version();
        
        StorableObject::Streamer(iobuffer);
        container_.Streamer(iobuffer);
        
        iobuffer.SetByteCount(byte_count, kTRUE);
    } else {
        std::cerr 
        << " ElectronColl::Streamer(TBuffer& iobuffer) - buffer in unknown state" 
        << std::endl;
    }
}

//-------------------------------------------------------------------------
// ROOT Input/Output Hook
//-------------------------------------------------------------------------
ClassImp(ElectronColl)





