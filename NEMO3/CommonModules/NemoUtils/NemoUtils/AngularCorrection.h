//
//  AngularCorrection.h
//
//  Created by James Mott on 08/10/12.
//

#ifndef ANGULARCORRECTION_H_
#define ANGULARCORRECTION_H_
#include <string>
#include <map>
#include <TRandom3.h>

class AngularCorrection {
public:
    AngularCorrection();
    ~AngularCorrection();
    double CosWeight(double cosine) const;
    
private:
    double   CorrFactor[50];
    double   CorrFactor_Err[50];
    TRandom3* RandomNumGen;

};

#endif
