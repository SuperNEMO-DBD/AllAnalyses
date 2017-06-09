//
//  CalibCaloHitColl.h
//  SNemoCoreExample
//
//  Created by Stefano Torre on 02/07/11.
//  Copyright 2011 Univesity College London. All rights reserved.
//
#ifndef NEMO_CALIBCALOHITCOLL_H_
#define NEMO_CALIBCALOHITCOLL_H_

#include "Hereward/Edm/StorableObject.h"
#include "Hereward/Edm/ConstHandle.h"
#include "Hereward/Edm/Handle.h"
#include "StorableContainers/ValueVector.h"
#include "NemoObjects/CalibCaloHit.h"

class EventRecord;
class CalibCaloHitColl;

typedef ConstHandle<CalibCaloHitColl> CalibCaloHitColl_ch;

class CalibCaloHitColl : public StorableObject {
    
public:
    //-------------------------------------------------------------------------
    // typedef's for the collection
    //-------------------------------------------------------------------------
    typedef CalibCaloHit                            value_type;
    typedef std::vector<value_type>                 CalibCaloHitList;
    typedef CalibCaloHitList::iterator              iterator;
    typedef CalibCaloHitList::const_iterator        const_iterator;
    typedef CalibCaloHit&                           reference;
    typedef const CalibCaloHit&                     const_reference;
    typedef CalibCaloHit*                           pointer;
    typedef const CalibCaloHit*                     const_pointer;
    typedef CalibCaloHitList::difference_type       difference_type;
    typedef CalibCaloHitList::size_type             size_type;
    typedef CalibCaloHitList                        CollType;
    typedef CalibCaloHitList                        collection_type;
    
    //-------------------------------------------------------------------------
    // Creation
    //-------------------------------------------------------------------------
    CalibCaloHitColl();
    CalibCaloHitColl(const CalibCaloHitColl& rhs);
    
    virtual CalibCaloHitColl* clone(void);
    
    //-------------------------------------------------------------------------
    // EDM requirements
    //-------------------------------------------------------------------------
    virtual void destroy();
    virtual void deallocate();
    
    //-------------------------------------------------------------------------
    // Assignemnt
    //-------------------------------------------------------------------------
    CalibCaloHitColl& operator = (const CalibCaloHitColl& rhs);
    
    //-------------------------------------------------------------------------
    // Additional functions to make class functional
    //-------------------------------------------------------------------------
    CalibCaloHitList& contents();
    const CalibCaloHitList& contents() const;
    void add(CalibCaloHit& hit);
    
    static bool find(EventRecord*, CalibCaloHitColl_ch&);
    static bool find(EventRecord*, CalibCaloHitColl_ch&, const std::string& );
    
    virtual std::string     class_name() const;
    virtual Version_t       class_version() const;
    virtual void            print(std::ostream& os = std::cout) const;
    
    virtual bool postread(EventRecord* p);
    
protected:
    virtual ~CalibCaloHitColl();
    
private:
    ValueVector<CalibCaloHit>   container_;
    ClassDef(CalibCaloHitColl, 1)
};

inline CalibCaloHitColl::CalibCaloHitList& CalibCaloHitColl::contents() {
    return container_.contents();
}

inline const 
CalibCaloHitColl::CalibCaloHitList& CalibCaloHitColl::contents() const {
    return container_.contents();
}

inline void CalibCaloHitColl::add(CalibCaloHit& hit) {
    container_.contents().push_back(hit);
}

#endif
