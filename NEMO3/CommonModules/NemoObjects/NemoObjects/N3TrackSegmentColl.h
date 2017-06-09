//
//  N3TrackSegmentColl.h
//
//  Created by Stefano Torre on 17/02/12.
//
#ifndef NEMO_N3TRACKSEGMENTCOLL_H_
#define NEMO_N3TRACKSEGMENTCOLL_H_

#include "Hereward/Edm/StorableObject.h"
#include "Hereward/Edm/ConstHandle.h"
#include "Hereward/Edm/Handle.h"
#include "Hereward/StorableContainers/ValueVector.h"
#include "NemoObjects/N3TrackSegment.h"

class EventRecord;
class N3TrackSegmentColl;

typedef ConstHandle<N3TrackSegmentColl> N3TrackSegmentColl_ch;

class N3TrackSegmentColl : public StorableObject {
    
public:
    //-------------------------------------------------------------------------
    // typedef's for the collection
    //-------------------------------------------------------------------------
    typedef N3TrackSegment                            value_type;
    typedef std::vector<value_type>                   N3TrackSegmentList;
    typedef N3TrackSegmentList::iterator              iterator;
    typedef N3TrackSegmentList::const_iterator        const_iterator;
    typedef N3TrackSegment&                           reference;
    typedef const N3TrackSegment&                     const_reference;
    typedef N3TrackSegment*                           pointer;
    typedef const N3TrackSegment*                     const_pointer;
    typedef N3TrackSegmentList::difference_type       difference_type;
    typedef N3TrackSegmentList::size_type             size_type;
    typedef N3TrackSegmentList                        CollType;
    typedef N3TrackSegmentList                        collection_type;
    
    //-------------------------------------------------------------------------
    // Creation
    //-------------------------------------------------------------------------
    N3TrackSegmentColl();
    N3TrackSegmentColl(const N3TrackSegmentColl& rhs);
    
    virtual N3TrackSegmentColl* clone(void);
    
    //-------------------------------------------------------------------------
    // EDM requirements
    //-------------------------------------------------------------------------
    virtual void destroy();
    virtual void deallocate();
    
    //-------------------------------------------------------------------------
    // Assignemnt
    //-------------------------------------------------------------------------
    N3TrackSegmentColl& operator = (const N3TrackSegmentColl& rhs);
    
    //-------------------------------------------------------------------------
    // Additional functions to make class functional
    //-------------------------------------------------------------------------
    N3TrackSegmentList& contents();
    const N3TrackSegmentList& contents() const;
    void add(N3TrackSegment& hit);
    
    static bool find(EventRecord*, N3TrackSegmentColl_ch&);
    static bool find(EventRecord*, N3TrackSegmentColl_ch&, const std::string& );
    
    virtual std::string     class_name() const;
    virtual Version_t       class_version() const;
    virtual void            print(std::ostream& os = std::cout) const;
    
    virtual bool postread(EventRecord* p);
    
protected:
    virtual ~N3TrackSegmentColl();
    
private:
    ValueVector<N3TrackSegment>   container_;
    ClassDef(N3TrackSegmentColl, 1)
};

inline N3TrackSegmentColl::N3TrackSegmentList& N3TrackSegmentColl::contents() {
    return container_.contents();
}

inline const 
N3TrackSegmentColl::N3TrackSegmentList& N3TrackSegmentColl::contents() const {
    return container_.contents();
}

inline void N3TrackSegmentColl::add(N3TrackSegment& hit) {
    container_.contents().push_back(hit);
}

#endif
