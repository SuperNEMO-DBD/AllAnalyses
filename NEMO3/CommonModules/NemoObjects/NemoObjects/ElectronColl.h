//
//  ElectronColl.h
//
//  Created by Stefano Torre on 09/05/12.
//
#ifndef NEMO_ELECTRONCOLL_H_
#define NEMO_ELECTRONCOLL_H_

#include "Hereward/Edm/StorableObject.h"
#include "Hereward/Edm/ConstHandle.h"
#include "Hereward/Edm/Handle.h"
#include "StorableContainers/ValueVector.h"
#include "NemoObjects/Electron.h"

class EventRecord;
class ElectronColl;

typedef ConstHandle<ElectronColl> ElectronColl_ch;
typedef Handle<ElectronColl> ElectronColl_h;

class ElectronColl : public StorableObject {
    
public:
    //-------------------------------------------------------------------------
    // typedef's for the collection
    //-------------------------------------------------------------------------
    typedef Electron                            value_type;
    typedef std::vector<value_type>                 ElectronList;
    typedef ElectronList::iterator              iterator;
    typedef ElectronList::const_iterator        const_iterator;
    typedef Electron&                           reference;
    typedef const Electron&                     const_reference;
    typedef Electron*                           pointer;
    typedef const Electron*                     const_pointer;
    typedef ElectronList::difference_type       difference_type;
    typedef ElectronList::size_type             size_type;
    typedef ElectronList                        CollType;
    typedef ElectronList                        collection_type;
    
    //-------------------------------------------------------------------------
    // Creation
    //-------------------------------------------------------------------------
    ElectronColl();
    ElectronColl(const ElectronColl& rhs);
    
    virtual ElectronColl* clone(void);
    
    //-------------------------------------------------------------------------
    // EDM requirements
    //-------------------------------------------------------------------------
    virtual void destroy();
    virtual void deallocate();
    
    //-------------------------------------------------------------------------
    // Assignemnt
    //-------------------------------------------------------------------------
    ElectronColl& operator = (const ElectronColl& rhs);
    
    //-------------------------------------------------------------------------
    // Additional functions to make class functional
    //-------------------------------------------------------------------------
    ElectronList& contents();
    const ElectronList& contents() const;
    void add(Electron& hit);
    
    static bool find(EventRecord*, ElectronColl_ch&);
    static bool find(EventRecord*, ElectronColl_ch&, const std::string& );
    
    virtual std::string     class_name() const;
    virtual Version_t       class_version() const;
    virtual void            print(std::ostream& os = std::cout) const;
    
    virtual bool postread(EventRecord* p);
    
protected:
    virtual ~ElectronColl();
    
private:
    ValueVector<Electron>   container_;
    ClassDef(ElectronColl, 1)
};

inline ElectronColl::ElectronList& ElectronColl::contents() {
    return container_.contents();
}

inline const 
ElectronColl::ElectronList& ElectronColl::contents() const {
    return container_.contents();
}

inline void ElectronColl::add(Electron& hit) {
    container_.contents().push_back(hit);
}

#endif
