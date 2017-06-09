//
//  NemoCATInterface.h
//
//  Created by Federico Nova on 16/02/12.
//

#ifndef NEMO_CATINTERFACE_H_
#define NEMO_CATINTERFACE_H_
#include "Hereward/DataProcPipeline/AppModule.h"
#include "Hereward/SuperNemoData/EventHeader.h"
#include "Hereward/SuperNemoData/UnitSystem.h"
#include "Hereward/SuperNemoData/NPConstants.h"
#include "CATAlgorithm/clusterizer.h"
#include "CATAlgorithm/sequentiator.h"
#include "CATAlgorithm/calorimeter_hit.h"
#include "CATUtils/EventDisplay.h"
#include "NemoObjects/N3GeigerHitColl.h"
#include "NemoObjects/N3CalorimeterHitColl.h"
#include "NemoObjects/N3TrackColl.h"
#include "Hereward/SuperNemoData/ConfigFile.h"
#include "Hereward/SuperNemoData/TrueVertexColl.h"
#include "Hereward/SuperNemoTracking/CATclusterColl.h"
#include "Hereward/SuperNemoTracking/CATnode.h"
#include <CATUtils/ntupler.h>

//using namespace CAT;

class NemoCATInterface : public AppModule {
public:
    //-------------------------------------------------------------------------
    // Constructors and Destructor
    //-------------------------------------------------------------------------
    NemoCATInterface(const std::string theName = "NemoCATInterface",
                 const std::string theDescription = "");
    virtual ~NemoCATInterface();
    
    //-------------------------------------------------------------------------
    // Operations
    //-------------------------------------------------------------------------
    AppResult beginJob(AppEvent* aJob);
    AppResult beginRun(AppEvent* aRun);
    AppResult event(AppEvent* anEvent);
    AppResult endRun(AppEvent* aRun);
    AppResult endJob(AppEvent* aJob);
    
    //-------------------------------------------------------------------------
    // Getters and setters
    //-------------------------------------------------------------------------
    void set_outfilename(string aValue) { outfilename_ = aValue; }
    void set_pmax(double aValue) { pmax_ = aValue; }
    void set_MaxTime(double aValue) { MaxTime_ = aValue; }
    void set_PrintMode(bool aValue) { PrintMode_ = aValue; }
    void set_SmallRadius(double aValue) { SmallRadius_ = aValue; }
    void set_TangentPhi(double aValue) { TangentPhi_ = aValue; }
    void set_TangentTheta(double aValue) { TangentTheta_ = aValue; }
    void set_SmallNumber(double aValue) { SmallNumber_ = aValue; }
    void set_QuadrantAngle(double aValue) { QuadrantAngle_ = aValue; }
    void set_Ratio(double aValue) { Ratio_ = aValue; }
    void set_CompatibilityDistance(double aValue) { CompatibilityDistance_ = aValue; }
    void set_MaxChi2(double aValue) { MaxChi2_ = aValue; }
    void set_hfile(string aValue) { hfile_ = aValue; }
    void set_nsigma(double aValue) { nsigma_ = aValue; }
    void set_level(string aValue) { level_ = aValue; }
    void set_nofflayers(size_t aValue) { nofflayers_ = aValue; }
    void set_type(string aValue) { type_ = aValue; }
    void set_len(double aValue) { len_ = aValue; }
    void set_rad(double aValue) { rad_ = aValue; }
    void set_vel(double aValue) { vel_ = aValue; }
    void set_CellDistance(double aValue) { CellDistance_ = aValue; }
    void set_FoilRadius(double aValue) { FoilRadius_ = aValue; }
    void set_modulo(int aValue) { modulo_ = aValue; }
    void set_first_event(int aValue) { first_event_ = aValue; }
    void set_InnerRadius(double aValue) { InnerRadius_ = aValue; }
    void set_OuterRadius(double aValue) { OuterRadius_ = aValue; }

    void set_PlotEvent(bool aValue) { PlotEvent_ = aValue; }
    void set_PlotTopView(bool aValue) { PlotTopView_ = aValue; }
    void set_PlotSideView(bool aValue) { PlotSideView_ = aValue; }
    void set_PlotInitialHits(bool aValue) { PlotInitialHits_ = aValue; }
    void set_PlotTangents(bool aValue) { PlotTangents_ = aValue; }
    void set_PlotTriplets(bool aValue) { PlotTriplets_ = aValue; }
    void set_PlotTrueTracks(bool aValue) { PlotTrueTracks_ = aValue; }
    void set_PlotCats(bool aValue) { PlotCats_ = aValue; }
    void set_PlotNemoraTracks(bool aValue) { PlotNemoraTracks_ = aValue; }
    void set_PlotNemoTracks(bool aValue) { PlotNemoTracks_ = aValue; }
    void set_PlotCellIds(bool aValue) { PlotCellIds_ = aValue; }
    void set_PlotCellChi2s(bool aValue) { PlotCellChi2s_ = aValue; }
    void set_PlotCalos(bool aValue) { PlotCalos_ = aValue; }
    void set_PlotCaloEnergy(bool aValue) { PlotCaloEnergy_ = aValue; }
    void set_PlotHelices(bool aValue) { PlotHelices_ = aValue; }
    void set_PlotLegend(bool aValue) { PlotLegend_ = aValue; }
    void set_PlotFormat(string aValue) { PlotFormat_ = aValue; }
    void set_RootNtuple(bool aValue) { RootNtuple_ = aValue; }
    void set_xsize(double aValue) { xsize_ = aValue; }
    void set_ysize(double aValue) { ysize_ = aValue; }
    void set_zsize(double aValue) { zsize_ = aValue; }
    void set_CaloXsize(double aValue) { CaloXsize_ = aValue; }
    void set_CaloYsize(double aValue) { CaloYsize_ = aValue; }
    void set_CaloZsize(double aValue) { CaloZsize_ = aValue; }

    
private:
    

    CAT::topology::cell fill_hit_from_geigerhit(N3GeigerHit* thisHit, size_t id);
    CAT::topology::calorimeter_hit fill_calo_hit_from_n3calohit(N3CalorimeterHit* thisHit, size_t id);
    CAT::topology::sequence fill_sequence_from_n3track(N3Track* thisTrack, size_t id);
    int get_block_number(int layer_, int side_);
    CATclusterColl * get_clusters();
    CATnode node_from_topology_node(CAT::topology::node);

    
    CAT::clusterizer* clustering_machine_;
    CAT::sequentiator* sequentiating_machine_;
    CAT::EventDisplay* display_machine_;
    ntupler* ntuple_machine_;
    string outfilename_;
    CAT::topology::tracked_data tracked_data_;
    double pmax_ ;
    double MaxTime_;
    bool PrintMode_;
    double SmallRadius_;
    double TangentPhi_;
    double TangentTheta_;
    double SmallNumber_;
    double QuadrantAngle_;
    double Ratio_;
    double CompatibilityDistance_;
    double MaxChi2_;
    string hfile_;
    double nsigma_;
    string level_;
    size_t nofflayers_;
    string type_;
    double CaloXsize_, CaloYsize_, CaloZsize_;

    bool PlotEvent_;
    bool PlotTopView_;
    bool PlotSideView_;
    bool PlotInitialHits_;
    bool PlotTangents_;
    bool PlotTriplets_;
    bool PlotTrueTracks_;
    bool PlotCats_;
    bool PlotNemoraTracks_;
    bool PlotNemoTracks_;
    bool PlotCellIds_;
    bool PlotCellChi2s_;
    bool PlotCalos_;
    bool PlotCaloEnergy_;
    bool PlotHelices_;
    bool PlotLegend_;
    string PlotFormat_;
    bool RootNtuple_;

    double xsize_;
    double ysize_;
    double zsize_;


    double len_;
    double rad_;
    double vel_;
    double CellDistance_;
    double InnerRadius_;
    double FoilRadius_;
    double OuterRadius_;
    int modulo_;
    int first_event_;

    size_t nevents_;

 private:

    ConfigFile params;



};

#endif
