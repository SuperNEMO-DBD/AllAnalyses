//
//  GammaColl.h
//
//  Created by Stefano Torre on 09/05/12.
//
#ifndef NEMO_GAMMACOLL_H_
#define NEMO_GAMMACOLL_H_

#include "Hereward/Edm/StorableObject.h"
#include "Hereward/Edm/ConstHandle.h"
#include "Hereward/Edm/Handle.h"
#include "StorableContainers/ValueVector.h"
#include "NemoObjects/Gamma.h"

class EventRecord;
class GammaColl;

typedef ConstHandle<GammaColl> GammaColl_ch;
typedef Handle<GammaColl> GammaColl_h;

class GammaColl : public StorableObject {
    
public:
    //-------------------------------------------------------------------------
    // typedef's for the collection
    //-------------------------------------------------------------------------
    typedef Gamma                            value_type;
    typedef std::vector<value_type>                 GammaList;
    typedef GammaList::iterator              iterator;
    typedef GammaList::const_iterator        const_iterator;
    typedef Gamma&                           reference;
    typedef const Gamma&                     const_reference;
    typedef Gamma*                           pointer;
    typedef const Gamma*                     const_pointer;
    typedef GammaList::difference_type       difference_type;
    typedef GammaList::size_type             size_type;
    typedef GammaList                        CollType;
    typedef GammaList                        collection_type;
    
    //-------------------------------------------------------------------------
    // Creation
    //-------------------------------------------------------------------------
    GammaColl();
    GammaColl(const GammaColl& rhs);
    
    virtual GammaColl* clone(void);
    
    //-------------------------------------------------------------------------
    // EDM requirements
    //-------------------------------------------------------------------------
    virtual void destroy();
    virtual void deallocate();
    
    //-------------------------------------------------------------------------
    // Assignemnt
    //-------------------------------------------------------------------------
    GammaColl& operator = (const GammaColl& rhs);
    
    //-------------------------------------------------------------------------
    // Additional functions to make class functional
    //-------------------------------------------------------------------------
    GammaList& contents();
    const GammaList& contents() const;
    void add(Gamma& hit);
    
    static bool find(EventRecord*, GammaColl_ch&);
    static bool find(EventRecord*, GammaColl_ch&, const std::string& );
    
    virtual std::string     class_name() const;
    virtual Version_t       class_version() const;
    virtual void            print(std::ostream& os = std::cout) const;
    
    virtual bool postread(EventRecord* p);
    
protected:
    virtual ~GammaColl();
    
private:
    ValueVector<Gamma>   container_;
    ClassDef(GammaColl, 1)
};

inline GammaColl::GammaList& GammaColl::contents() {
    return container_.contents();
}

inline const 
GammaColl::GammaList& GammaColl::contents() const {
    return container_.contents();
}

inline void GammaColl::add(Gamma& hit) {
    container_.contents().push_back(hit);
}

#endif
