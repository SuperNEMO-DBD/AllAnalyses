//
//  N3CalorimeterHitColl.h
//  SNemoCoreExample
//
//  Created by Stefano Torre on 02/07/11.
//  Copyright 2011 Univesity College London. All rights reserved.
//
#ifndef NEMO_N3CALORIMETERHITCOLL_H_
#define NEMO_N3CALORIMETERHITCOLL_H_

#include "Hereward/Edm/StorableObject.h"
#include "Hereward/Edm/ConstHandle.h"
#include "Hereward/Edm/Handle.h"
#include "StorableContainers/ValueVector.h"
#include "NemoObjects/N3CalorimeterHit.h"

#include <map>
#include <vector>

class EventRecord;
class N3CalorimeterHitColl;

typedef ConstHandle<N3CalorimeterHitColl> N3CalorimeterHitColl_ch;
typedef Handle<N3CalorimeterHitColl> N3CalorimeterHitColl_h;

class N3CalorimeterHitColl : public StorableObject {
    
public:
    //-------------------------------------------------------------------------
    // typedef's for the collection
    //-------------------------------------------------------------------------
    typedef N3CalorimeterHit                        value_type;
    typedef std::vector<value_type>                 N3CalorimeterHitList;
    typedef N3CalorimeterHitList::iterator          iterator;
    typedef N3CalorimeterHitList::const_iterator    const_iterator;
    typedef N3CalorimeterHit&                       reference;
    typedef const N3CalorimeterHit&                 const_reference;
    typedef N3CalorimeterHit*                       pointer;
    typedef const N3CalorimeterHit*                 const_pointer;
    typedef N3CalorimeterHitList::difference_type   difference_type;
    typedef N3CalorimeterHitList::size_type         size_type;
    typedef N3CalorimeterHitList                    CollType;
    typedef N3CalorimeterHitList                    collection_type;
    
    //-------------------------------------------------------------------------
    // Creation
    //-------------------------------------------------------------------------
    N3CalorimeterHitColl();
    N3CalorimeterHitColl(const N3CalorimeterHitColl& rhs);
    
    virtual N3CalorimeterHitColl* clone(void);
    
    //-------------------------------------------------------------------------
    // EDM requirements
    //-------------------------------------------------------------------------
    virtual void destroy();
    virtual void deallocate();
    
    //-------------------------------------------------------------------------
    // Assignemnt
    //-------------------------------------------------------------------------
    N3CalorimeterHitColl& operator = (const N3CalorimeterHitColl& rhs);
    
    //-------------------------------------------------------------------------
    // Additional functions to make class functional
    //-------------------------------------------------------------------------
    N3CalorimeterHitList& contents();
    const N3CalorimeterHitList& contents() const;
    void add(N3CalorimeterHit& hit);
    
    static bool find(EventRecord*, N3CalorimeterHitColl_ch&);
    static bool find(EventRecord*, N3CalorimeterHitColl_ch&, const std::string& );
    
    virtual std::string     class_name() const;
    virtual Version_t       class_version() const;
    virtual void            print(std::ostream& os = std::cout) const;
    
    virtual bool postread(EventRecord* p);
    

protected:
    virtual ~N3CalorimeterHitColl();
    
private:
    ValueVector<N3CalorimeterHit>   container_;
    ClassDef(N3CalorimeterHitColl, 1)
};

inline N3CalorimeterHitColl::N3CalorimeterHitList& N3CalorimeterHitColl::contents() {
    return container_.contents();
}

inline const 
N3CalorimeterHitColl::N3CalorimeterHitList& N3CalorimeterHitColl::contents() const {
    return container_.contents();
}

inline void N3CalorimeterHitColl::add(N3CalorimeterHit& hit) {
    container_.contents().push_back(hit);
}

#endif
