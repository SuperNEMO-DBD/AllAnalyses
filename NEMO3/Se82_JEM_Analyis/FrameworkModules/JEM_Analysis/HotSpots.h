//
//  HotSpots.h
//
//  Created by James Mott on 14/11/12.
//

#ifndef HOTSPOTS_H_
#define HOTSPOTS_H_
#include "CLHEP/Vector/ThreeVector.h"

class HotSpots {
public:
    HotSpots();
    ~HotSpots();
    bool InHotSpot(CLHEP::Hep3Vector vertex) const;
    
private:

    double centre_Z[26];
    double centre_Sect[26];
    double semiAxis_Z[26];
    double semiAxis_Sect[26];

};

#endif
