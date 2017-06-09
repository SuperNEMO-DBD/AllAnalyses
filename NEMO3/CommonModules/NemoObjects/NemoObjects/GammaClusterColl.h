//
//  GammaClusterColl.h
//
//  Created by Stefano Torre on 09/05/12.
//
#ifndef NEMO_GAMMACLUSTERCOLL_H_
#define NEMO_GAMMACLUSTERCOLL_H_

#include "Hereward/Edm/StorableObject.h"
#include "Hereward/Edm/ConstHandle.h"
#include "Hereward/Edm/Handle.h"
#include "StorableContainers/ValueVector.h"
#include "NemoObjects/GammaCluster.h"
#include "NemoObjects/Gamma.h"

class EventRecord;
class GammaClusterColl;

typedef ConstHandle<GammaClusterColl> GammaClusterColl_ch;
typedef Handle<GammaClusterColl> GammaClusterColl_h;

class GammaClusterColl : public StorableObject {
    
public:
    //-------------------------------------------------------------------------
    // typedef's for the collection
    //-------------------------------------------------------------------------
    typedef GammaCluster                     value_type;
    typedef std::vector<value_type>          ClusterList;
    typedef ClusterList::iterator            iterator;
    typedef ClusterList::const_iterator      const_iterator;
    typedef GammaCluster&                    reference;
    typedef const GammaCluster&              const_reference;
    typedef GammaCluster*                    pointer;
    typedef const GammaCluster*              const_pointer;
    typedef ClusterList::difference_type     difference_type;
    typedef ClusterList::size_type           size_type;
    typedef ClusterList                      CollType;
    typedef ClusterList                      collection_type;
    
    //-------------------------------------------------------------------------
    // Creation
    //-------------------------------------------------------------------------
    GammaClusterColl();
    GammaClusterColl(const GammaClusterColl& rhs);
    
    virtual GammaClusterColl* clone(void);
    
    //-------------------------------------------------------------------------
    // EDM requirements
    //-------------------------------------------------------------------------
    virtual void destroy();
    virtual void deallocate();
    
    //-------------------------------------------------------------------------
    // Assignemnt
    //-------------------------------------------------------------------------
    GammaClusterColl& operator = (const GammaClusterColl& rhs);
    
    //-------------------------------------------------------------------------
    // Additional functions to make class functional
    //-------------------------------------------------------------------------
    ClusterList& contents();
    const ClusterList& contents() const;
    void add(GammaCluster& hit);
    
    static bool find(EventRecord*, GammaClusterColl_ch&);
    static bool find(EventRecord*, GammaClusterColl_ch&, const std::string& );
    
    virtual std::string     class_name() const;
    virtual Version_t       class_version() const;
    virtual void            print(std::ostream& os = std::cout) const;
    
    virtual bool postread(EventRecord* p);
    
protected:
    virtual ~GammaClusterColl();
    
private:
    ValueVector<GammaCluster>   container_;
    ClassDef(GammaClusterColl, 1)
};

inline GammaClusterColl::ClusterList& GammaClusterColl::contents() {
    return container_.contents();
}

inline const 
GammaClusterColl::ClusterList& GammaClusterColl::contents() const {
    return container_.contents();
}

inline void GammaClusterColl::add(GammaCluster& hit) {
    container_.contents().push_back(hit);
}

#endif
