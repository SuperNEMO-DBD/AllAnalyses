//
//  N3GeigerHitColl.h
//  SNemoCoreExample
//
//  Created by Stefano Torre on 02/07/11.
//  Copyright 2011 Univesity College London. All rights reserved.
//
#ifndef NEMO_N3GEIGERHITCOLL_H_
#define NEMO_N3GEIGERHITCOLL_H_

#include "Hereward/Edm/StorableObject.h"
#include "Hereward/Edm/ConstHandle.h"
#include "Hereward/Edm/Handle.h"
#include "Hereward/StorableContainers/ValueVector.h"
#include "NemoObjects/N3GeigerHit.h"

class EventRecord;
class N3GeigerHitColl;

typedef ConstHandle<N3GeigerHitColl> N3GeigerHitColl_ch;

class N3GeigerHitColl : public StorableObject {
    
public:
    //-------------------------------------------------------------------------
    // typedef's for the collection
    //-------------------------------------------------------------------------
    typedef N3GeigerHit                            value_type;
    typedef std::vector<value_type>                 N3GeigerHitList;
    typedef N3GeigerHitList::iterator              iterator;
    typedef N3GeigerHitList::const_iterator        const_iterator;
    typedef N3GeigerHit&                           reference;
    typedef const N3GeigerHit&                     const_reference;
    typedef N3GeigerHit*                           pointer;
    typedef const N3GeigerHit*                     const_pointer;
    typedef N3GeigerHitList::difference_type       difference_type;
    typedef N3GeigerHitList::size_type             size_type;
    typedef N3GeigerHitList                        CollType;
    typedef N3GeigerHitList                        collection_type;
    
    //-------------------------------------------------------------------------
    // Creation
    //-------------------------------------------------------------------------
    N3GeigerHitColl();
    N3GeigerHitColl(const N3GeigerHitColl& rhs);
    
    virtual N3GeigerHitColl* clone(void);
    
    //-------------------------------------------------------------------------
    // EDM requirements
    //-------------------------------------------------------------------------
    virtual void destroy();
    virtual void deallocate();
    
    //-------------------------------------------------------------------------
    // Assignemnt
    //-------------------------------------------------------------------------
    N3GeigerHitColl& operator = (const N3GeigerHitColl& rhs);
    
    //-------------------------------------------------------------------------
    // Additional functions to make class functional
    //-------------------------------------------------------------------------
    N3GeigerHitList& contents();
    const N3GeigerHitList& contents() const;
    void add(N3GeigerHit& hit);
    
    static bool find(EventRecord*, N3GeigerHitColl_ch&);
    static bool find(EventRecord*, N3GeigerHitColl_ch&, const std::string& );
    
    virtual std::string     class_name() const;
    virtual Version_t       class_version() const;
    virtual void            print(std::ostream& os = std::cout) const;
    
    virtual bool postread(EventRecord* p);
    
protected:
    virtual ~N3GeigerHitColl();
    
private:
    ValueVector<N3GeigerHit>   container_;
    ClassDef(N3GeigerHitColl, 1)
};

inline N3GeigerHitColl::N3GeigerHitList& N3GeigerHitColl::contents() {
    return container_.contents();
}

inline const 
N3GeigerHitColl::N3GeigerHitList& N3GeigerHitColl::contents() const {
    return container_.contents();
}

inline void N3GeigerHitColl::add(N3GeigerHit& hit) {
    container_.contents().push_back(hit);
}

#endif
