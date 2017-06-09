//
//  TrueVertexLocation.h
//
//  Created by James Mott from 15/11/12
//

#ifndef TRUEVERTEXLOCATION_H_
#define TRUEVERTEXLOCATION_H_
#include "Hereward/SuperNemoProcessing/RootOutputManager.h"
#include "Hereward/DataProcPipeline/AppModule.h"
#include "NemoUtils/SectorData.h"

class TrueVertexLocation : public AppModule {
public:
    //-------------------------------------------------------------------------
    // Constructors and Destructor
    //-------------------------------------------------------------------------
    TrueVertexLocation(const std::string theName = "TrueVertexLocation",
                   const std::string theDescription = "");
    virtual ~TrueVertexLocation();
  
    //-------------------------------------------------------------------------
    // Operations
    //-------------------------------------------------------------------------
    AppResult beginJob(AppEvent* aJob);
    AppResult beginRun(AppEvent* aRun);
    AppResult event(AppEvent* anEvent);
    AppResult endRun(AppEvent* aRun);
    AppResult endJob(AppEvent* aJob);

    //-------------------------------------------------------------------------
    // Accessors
    //-------------------------------------------------------------------------

private:

    double trueVertexR_, trueVertexZ_, trueVertexSector_;
    int    trueVertexLocation_;

    SectorData* sectorInfo_;

    int     TotalNumEvents_;

    TTree* tree_;

};

#endif
