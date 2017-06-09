//
//  N3TrueN3TrueGeigerHitColl.h
//
//  Created by Stefano Torre on 02/07/11.
//
#ifndef N3TRUEGEIGERHITCOLL_H_
#define N3TRUEGEIGERHITCOLL_H_

#include "Hereward/Edm/StorableObject.h"
#include "Hereward/Edm/ConstHandle.h"
#include "Hereward/Edm/Handle.h"
#include "Hereward/Edm/Link.h"
#include "Hereward/Edm/ConstLink.h"
#include "Hereward/Edm/Handle.h"
#include "Hereward/StorableContainers/ValueVector.h"
#include "NemoObjects/N3TrueGeigerHit.h"

class EventRecord;
class N3TrueGeigerHitColl;

typedef ConstHandle<N3TrueGeigerHitColl>  N3TrueGeigerHitColl_ch;
typedef Handle<N3TrueGeigerHitColl>       N3TrueGeigerHitColl_h;
typedef ConstLink<N3TrueGeigerHitColl>    N3TrueGeigerHitColl_cl;
typedef Link<N3TrueGeigerHitColl>         N3TrueGeigerHitColl_l;

class N3TrueGeigerHitColl : public StorableObject {
    
public:
    //-------------------------------------------------------------------------
    // typedef's for the collection
    //-------------------------------------------------------------------------
    typedef N3TrueGeigerHit                            value_type;
    typedef std::vector<value_type>                  N3TrueGeigerHitList;
    typedef N3TrueGeigerHitList::iterator              iterator;
    typedef N3TrueGeigerHitList::const_iterator        const_iterator;
    typedef N3TrueGeigerHit&                           reference;
    typedef const N3TrueGeigerHit&                     const_reference;
    typedef N3TrueGeigerHit*                           pointer;
    typedef const N3TrueGeigerHit*                     const_pointer;
    typedef N3TrueGeigerHitList::difference_type       difference_type;
    typedef N3TrueGeigerHitList::size_type             size_type;
    typedef N3TrueGeigerHitList                        CollType;
    typedef N3TrueGeigerHitList                        collection_type;
    
    //-------------------------------------------------------------------------
    // Creation
    //-------------------------------------------------------------------------
    N3TrueGeigerHitColl();
    N3TrueGeigerHitColl(const N3TrueGeigerHitColl& rhs);
    
    virtual N3TrueGeigerHitColl* clone(void);
    
    //-------------------------------------------------------------------------
    // EDM requirements
    //-------------------------------------------------------------------------
    virtual void destroy();
    virtual void deallocate();
    
    //-------------------------------------------------------------------------
    // Assignemnt
    //-------------------------------------------------------------------------
    N3TrueGeigerHitColl& operator = (const N3TrueGeigerHitColl& rhs);
    
    //-------------------------------------------------------------------------
    // Additional functions to make class functional
    //-------------------------------------------------------------------------
    N3TrueGeigerHitList& contents();
    const N3TrueGeigerHitList& contents() const;
    void add(N3TrueGeigerHit& hit);
    
    static bool find(EventRecord*, N3TrueGeigerHitColl_ch&);
    static bool find(EventRecord*, N3TrueGeigerHitColl_ch&, const std::string& );
    
    virtual std::string     class_name() const;
    virtual Version_t       class_version() const;
    virtual void            print(std::ostream& os = std::cout) const;
    
    virtual bool postread(EventRecord* p);
    
protected:
    virtual ~N3TrueGeigerHitColl();
    
private:
    ValueVector<N3TrueGeigerHit>   container_;
    ClassDef(N3TrueGeigerHitColl, 1)
};

inline N3TrueGeigerHitColl::N3TrueGeigerHitList& N3TrueGeigerHitColl::contents() {
    return container_.contents();
}

inline const 
N3TrueGeigerHitColl::N3TrueGeigerHitList& N3TrueGeigerHitColl::contents() const {
    return container_.contents();
}

inline void N3TrueGeigerHitColl::add(N3TrueGeigerHit& hit) {
    container_.contents().push_back(hit);
}

#endif
