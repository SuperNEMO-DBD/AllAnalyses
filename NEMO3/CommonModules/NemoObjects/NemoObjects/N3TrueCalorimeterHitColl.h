//
//  N3TrueN3TrueCalorimeterHitColl.h
//
//  Created by Stefano Torre on 31/12/11.
//
#ifndef N3TRUECALORIMETERHITCOLL_H_
#define N3TRUECALORIMETERHITCOLL_H_

#include "Hereward/Edm/StorableObject.h"
#include "Hereward/Edm/ConstHandle.h"
#include "Hereward/Edm/Handle.h"
#include "Hereward/Edm/Link.h"
#include "Hereward/Edm/ConstLink.h"
#include "Hereward/Edm/Handle.h"
#include "Hereward/StorableContainers/ValueVector.h"
#include "NemoObjects/N3TrueCalorimeterHit.h"

class EventRecord;
class N3TrueCalorimeterHitColl;

typedef ConstHandle<N3TrueCalorimeterHitColl>  N3TrueCalorimeterHitColl_ch;
typedef Handle<N3TrueCalorimeterHitColl>       N3TrueCalorimeterHitColl_h;
typedef ConstLink<N3TrueCalorimeterHitColl>    N3TrueCalorimeterHitColl_cl;
typedef Link<N3TrueCalorimeterHitColl>         N3TrueCalorimeterHitColl_l;

class N3TrueCalorimeterHitColl : public StorableObject {
    
public:
    //-------------------------------------------------------------------------
    // typedef's for the collection
    //-------------------------------------------------------------------------
    typedef N3TrueCalorimeterHit                            value_type;
    typedef std::vector<value_type>                  N3TrueCalorimeterHitList;
    typedef N3TrueCalorimeterHitList::iterator              iterator;
    typedef N3TrueCalorimeterHitList::const_iterator        const_iterator;
    typedef N3TrueCalorimeterHit&                           reference;
    typedef const N3TrueCalorimeterHit&                     const_reference;
    typedef N3TrueCalorimeterHit*                           pointer;
    typedef const N3TrueCalorimeterHit*                     const_pointer;
    typedef N3TrueCalorimeterHitList::difference_type       difference_type;
    typedef N3TrueCalorimeterHitList::size_type             size_type;
    typedef N3TrueCalorimeterHitList                        CollType;
    typedef N3TrueCalorimeterHitList                        collection_type;
    
    //-------------------------------------------------------------------------
    // Creation
    //-------------------------------------------------------------------------
    N3TrueCalorimeterHitColl();
    N3TrueCalorimeterHitColl(const N3TrueCalorimeterHitColl& rhs);
    
    virtual N3TrueCalorimeterHitColl* clone(void);
    
    //-------------------------------------------------------------------------
    // EDM requirements
    //-------------------------------------------------------------------------
    virtual void destroy();
    virtual void deallocate();
    
    //-------------------------------------------------------------------------
    // Assignemnt
    //-------------------------------------------------------------------------
    N3TrueCalorimeterHitColl& operator = (const N3TrueCalorimeterHitColl& rhs);
    
    //-------------------------------------------------------------------------
    // Additional functions to make class functional
    //-------------------------------------------------------------------------
    N3TrueCalorimeterHitList& contents();
    const N3TrueCalorimeterHitList& contents() const;
    void add(N3TrueCalorimeterHit& hit);
    
    static bool find(EventRecord*, N3TrueCalorimeterHitColl_ch&);
    static bool find(EventRecord*, N3TrueCalorimeterHitColl_ch&, const std::string& );
    
    virtual std::string     class_name() const;
    virtual Version_t       class_version() const;
    virtual void            print(std::ostream& os = std::cout) const;
    
    virtual bool postread(EventRecord* p);
    
protected:
    virtual ~N3TrueCalorimeterHitColl();
    
private:
    ValueVector<N3TrueCalorimeterHit>   container_;
    ClassDef(N3TrueCalorimeterHitColl, 1)
};

inline N3TrueCalorimeterHitColl::N3TrueCalorimeterHitList& N3TrueCalorimeterHitColl::contents() {
    return container_.contents();
}

inline const 
N3TrueCalorimeterHitColl::N3TrueCalorimeterHitList& N3TrueCalorimeterHitColl::contents() const {
    return container_.contents();
}

inline void N3TrueCalorimeterHitColl::add(N3TrueCalorimeterHit& hit) {
    container_.contents().push_back(hit);
}

#endif
