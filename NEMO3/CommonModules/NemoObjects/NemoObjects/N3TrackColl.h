//
//  N3TrackColl.h
//  SNemoCoreExample
//
//  Created by Stefano Torre on 02/07/11.
//  Copyright 2011 Univesity College London. All rights reserved.
//
#ifndef NEMO_N3TRACKCOLL_H_
#define NEMO_N3TRACKCOLL_H_

#include "Hereward/Edm/StorableObject.h"
#include "Hereward/Edm/ConstHandle.h"
#include "Hereward/Edm/Handle.h"
#include "Hereward/StorableContainers/ValueVector.h"
#include "NemoObjects/N3Track.h"

class EventRecord;
class N3TrackColl;

typedef ConstHandle<N3TrackColl> N3TrackColl_ch;

class N3TrackColl : public StorableObject {
    
public:
    //-------------------------------------------------------------------------
    // typedef's for the collection
    //-------------------------------------------------------------------------
    typedef N3Track                            value_type;
    typedef std::vector<value_type>                 N3TrackList;
    typedef N3TrackList::iterator              iterator;
    typedef N3TrackList::const_iterator        const_iterator;
    typedef N3Track&                           reference;
    typedef const N3Track&                     const_reference;
    typedef N3Track*                           pointer;
    typedef const N3Track*                     const_pointer;
    typedef N3TrackList::difference_type       difference_type;
    typedef N3TrackList::size_type             size_type;
    typedef N3TrackList                        CollType;
    typedef N3TrackList                        collection_type;
    
    //-------------------------------------------------------------------------
    // Creation
    //-------------------------------------------------------------------------
    N3TrackColl();
    N3TrackColl(const N3TrackColl& rhs);
    
    virtual N3TrackColl* clone(void);
    
    //-------------------------------------------------------------------------
    // EDM requirements
    //-------------------------------------------------------------------------
    virtual void destroy();
    virtual void deallocate();
    
    //-------------------------------------------------------------------------
    // Assignemnt
    //-------------------------------------------------------------------------
    N3TrackColl& operator = (const N3TrackColl& rhs);
    
    //-------------------------------------------------------------------------
    // Additional functions to make class functional
    //-------------------------------------------------------------------------
    N3TrackList& contents();
    const N3TrackList& contents() const;
    void add(N3Track& hit);
    
    static bool find(EventRecord*, N3TrackColl_ch&);
    static bool find(EventRecord*, N3TrackColl_ch&, const std::string& );
    
    virtual std::string     class_name() const;
    virtual Version_t       class_version() const;
    virtual void            print(std::ostream& os = std::cout) const;
    
    virtual bool postread(EventRecord* p);
    
protected:
    virtual ~N3TrackColl();
    
private:
    ValueVector<N3Track>   container_;
    ClassDef(N3TrackColl, 1)
};

inline N3TrackColl::N3TrackList& N3TrackColl::contents() {
    return container_.contents();
}

inline const 
N3TrackColl::N3TrackList& N3TrackColl::contents() const {
    return container_.contents();
}

inline void N3TrackColl::add(N3Track& hit) {
    container_.contents().push_back(hit);
}

#endif
