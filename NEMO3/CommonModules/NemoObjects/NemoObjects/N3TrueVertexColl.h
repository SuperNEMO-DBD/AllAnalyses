//
//  N3TrueVertexColl.h
//
//  Created by Stefano Torre on 19/09/11.
//
#ifndef N3TRUEVERTEXCOLL_H_
#define N3TRUEVERTEXCOLL_H_

#include "Hereward/Edm/StorableObject.h"
#include "Hereward/Edm/ConstHandle.h"
#include "Hereward/Edm/Handle.h"
#include "Hereward/Edm/Link.h"
#include "Hereward/Edm/ConstLink.h"
#include "Hereward/Edm/Handle.h"
#include "Hereward/StorableContainers/ValueVector.h"
#include "NemoObjects/N3TrueVertex.h"

class EventRecord;
class N3TrueVertexColl;

typedef Handle<N3TrueVertexColl>        N3TrueVertexColl_h;
typedef ConstHandle<N3TrueVertexColl>   N3TrueVertexColl_ch;
typedef Link<N3TrueVertexColl>          N3TrueVertexColl_l;
typedef ConstLink<N3TrueVertexColl>     N3TrueVertexColl_cl;
    
class N3TrueVertexColl : public StorableObject {

public:
    //-------------------------------------------------------------------------
    // typedef's for the collection
    //-------------------------------------------------------------------------
    typedef N3TrueVertex                            value_type;
    typedef std::vector<value_type>                  N3TrueVertexList;
    typedef N3TrueVertexList::iterator              iterator;
    typedef N3TrueVertexList::const_iterator        const_iterator;
    typedef N3TrueVertex&                           reference;
    typedef const N3TrueVertex&                     const_reference;
    typedef N3TrueVertex*                           pointer;
    typedef const N3TrueVertex*                     const_pointer;
    typedef N3TrueVertexList::difference_type       difference_type;
    typedef N3TrueVertexList::size_type             size_type;
    typedef N3TrueVertexList                        CollType;
    typedef N3TrueVertexList                        collection_type;
    
    //-------------------------------------------------------------------------
    // Creation
    //-------------------------------------------------------------------------
    N3TrueVertexColl();
    N3TrueVertexColl(const N3TrueVertexColl& rhs);
    
    virtual N3TrueVertexColl* clone(void);
    
    //-------------------------------------------------------------------------
    // EDM requirements
    //-------------------------------------------------------------------------
    virtual void destroy();
    virtual void deallocate();
    
    //-------------------------------------------------------------------------
    // Assignemnt
    //-------------------------------------------------------------------------
    N3TrueVertexColl& operator = (const N3TrueVertexColl& rhs);
    
    //-------------------------------------------------------------------------
    // Additional functions to make class functional
    //-------------------------------------------------------------------------
    N3TrueVertexList& contents();
    const N3TrueVertexList& contents() const;
    void add(N3TrueVertex& particle);
    
    static bool find(EventRecord*, N3TrueVertexColl_ch&);
    static bool find(EventRecord*, N3TrueVertexColl_ch&, const std::string& );
    
    virtual std::string     class_name() const;
    virtual Version_t       class_version() const;
    virtual void            print(std::ostream& os = std::cout) const;
    
    virtual bool postread(EventRecord* p);
    
protected:
    virtual ~N3TrueVertexColl();
    
private:
    ValueVector<N3TrueVertex>   container_;
    ClassDef(N3TrueVertexColl, 1)
};

inline N3TrueVertexColl::N3TrueVertexList& N3TrueVertexColl::contents() {
    return container_.contents();
}

inline const 
N3TrueVertexColl::N3TrueVertexList& N3TrueVertexColl::contents() const {
    return container_.contents();
}

inline void N3TrueVertexColl::add(N3TrueVertex& particle) {
    container_.contents().push_back(particle);
}

#endif
