//
//  AlphaColl.h
//
//  Created by Stefano Torre on 09/05/12.
//
#ifndef NEMO_ALPHACOLL_H_
#define NEMO_ALPHACOLL_H_

#include "Hereward/Edm/StorableObject.h"
#include "Hereward/Edm/ConstHandle.h"
#include "Hereward/Edm/Handle.h"
#include "StorableContainers/ValueVector.h"
#include "NemoObjects/Alpha.h"

class EventRecord;
class AlphaColl;

typedef ConstHandle<AlphaColl> AlphaColl_ch;
typedef Handle<AlphaColl> AlphaColl_h;

class AlphaColl : public StorableObject {
    
public:
    //-------------------------------------------------------------------------
    // typedef's for the collection
    //-------------------------------------------------------------------------
    typedef Alpha                            value_type;
    typedef std::vector<value_type>                 AlphaList;
    typedef AlphaList::iterator              iterator;
    typedef AlphaList::const_iterator        const_iterator;
    typedef Alpha&                           reference;
    typedef const Alpha&                     const_reference;
    typedef Alpha*                           pointer;
    typedef const Alpha*                     const_pointer;
    typedef AlphaList::difference_type       difference_type;
    typedef AlphaList::size_type             size_type;
    typedef AlphaList                        CollType;
    typedef AlphaList                        collection_type;
    
    //-------------------------------------------------------------------------
    // Creation
    //-------------------------------------------------------------------------
    AlphaColl();
    AlphaColl(const AlphaColl& rhs);
    
    virtual AlphaColl* clone(void);
    
    //-------------------------------------------------------------------------
    // EDM requirements
    //-------------------------------------------------------------------------
    virtual void destroy();
    virtual void deallocate();
    
    //-------------------------------------------------------------------------
    // Assignemnt
    //-------------------------------------------------------------------------
    AlphaColl& operator = (const AlphaColl& rhs);
    
    //-------------------------------------------------------------------------
    // Additional functions to make class functional
    //-------------------------------------------------------------------------
    AlphaList& contents();
    const AlphaList& contents() const;
    void add(Alpha& hit);
    
    static bool find(EventRecord*, AlphaColl_ch&);
    static bool find(EventRecord*, AlphaColl_ch&, const std::string& );
    
    virtual std::string     class_name() const;
    virtual Version_t       class_version() const;
    virtual void            print(std::ostream& os = std::cout) const;
    
    virtual bool postread(EventRecord* p);
    
protected:
    virtual ~AlphaColl();
    
private:
    ValueVector<Alpha>   container_;
    ClassDef(AlphaColl, 1)
};

inline AlphaColl::AlphaList& AlphaColl::contents() {
    return container_.contents();
}

inline const 
AlphaColl::AlphaList& AlphaColl::contents() const {
    return container_.contents();
}

inline void AlphaColl::add(Alpha& hit) {
    container_.contents().push_back(hit);
}

#endif
