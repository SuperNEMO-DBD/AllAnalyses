//
//  N3TrueParticleColl.h
//
//  Created by Stefano Torre on 19/09/11.
//
#ifndef N3TRUEPARTICLECOLL_H_
#define N3TRUEPARTICLECOLL_H_

#include "Hereward/Edm/StorableObject.h"
#include "Hereward/Edm/ConstHandle.h"
#include "Hereward/Edm/Handle.h"
#include "Hereward/Edm/Link.h"
#include "Hereward/Edm/ConstLink.h"
#include "Hereward/Edm/Handle.h"
#include "Hereward/StorableContainers/ValueVector.h"
#include "NemoObjects/N3TrueParticle.h"

class EventRecord;
class N3TrueParticleColl;

typedef Handle<N3TrueParticleColl>        N3TrueParticleColl_h;
typedef ConstHandle<N3TrueParticleColl>   N3TrueParticleColl_ch;
typedef Link<N3TrueParticleColl>          N3TrueParticleColl_l;
typedef ConstLink<N3TrueParticleColl>     N3TrueParticleColl_cl;
    
class N3TrueParticleColl : public StorableObject {

public:
    //-------------------------------------------------------------------------
    // typedef's for the collection
    //-------------------------------------------------------------------------
    typedef N3TrueParticle                            value_type;
    typedef std::vector<value_type>                  N3TrueParticleList;
    typedef N3TrueParticleList::iterator              iterator;
    typedef N3TrueParticleList::const_iterator        const_iterator;
    typedef N3TrueParticle&                           reference;
    typedef const N3TrueParticle&                     const_reference;
    typedef N3TrueParticle*                           pointer;
    typedef const N3TrueParticle*                     const_pointer;
    typedef N3TrueParticleList::difference_type       difference_type;
    typedef N3TrueParticleList::size_type             size_type;
    typedef N3TrueParticleList                        CollType;
    typedef N3TrueParticleList                        collection_type;
    
    //-------------------------------------------------------------------------
    // Creation
    //-------------------------------------------------------------------------
    N3TrueParticleColl();
    N3TrueParticleColl(const N3TrueParticleColl& rhs);
    
    virtual N3TrueParticleColl* clone(void);
    
    //-------------------------------------------------------------------------
    // EDM requirements
    //-------------------------------------------------------------------------
    virtual void destroy();
    virtual void deallocate();
    
    //-------------------------------------------------------------------------
    // Assignemnt
    //-------------------------------------------------------------------------
    N3TrueParticleColl& operator = (const N3TrueParticleColl& rhs);
    
    //-------------------------------------------------------------------------
    // Additional functions to make class functional
    //-------------------------------------------------------------------------
    N3TrueParticleList& contents();
    const N3TrueParticleList& contents() const;
    void add(N3TrueParticle& particle);
    
    static bool find(EventRecord*, N3TrueParticleColl_ch&);
    static bool find(EventRecord*, N3TrueParticleColl_ch&, const std::string& );
    
    virtual std::string     class_name() const;
    virtual Version_t       class_version() const;
    virtual void            print(std::ostream& os = std::cout) const;
    
    virtual bool postread(EventRecord* p);
    
protected:
    virtual ~N3TrueParticleColl();
    
private:
    ValueVector<N3TrueParticle>   container_;
    ClassDef(N3TrueParticleColl, 1)
};

inline N3TrueParticleColl::N3TrueParticleList& N3TrueParticleColl::contents() {
    return container_.contents();
}

inline const 
N3TrueParticleColl::N3TrueParticleList& N3TrueParticleColl::contents() const {
    return container_.contents();
}

inline void N3TrueParticleColl::add(N3TrueParticle& particle) {
    container_.contents().push_back(particle);
}

#endif
