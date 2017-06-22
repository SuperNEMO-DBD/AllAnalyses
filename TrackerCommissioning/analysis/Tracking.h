#ifndef Tracking_h
#define Tracking_h

#include "../ntuplizer/GHbase.h"
#include "../ntuplizer/CellGeom.C"
#include <map>
#include <TROOT.h>
#include <TMinuit.h>
#include <TLine.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TEllipse.h>
#include <TGeoManager.h>
#include <TGeoVolume.h>
#include <TGeoMaterial.h>
#include <TGeoMedium.h>
#include <TGeoBuilder.h>
#include <TGeoBBox.h>
#include <TPolyLine3D.h>
#include <sstream>
#include <string>

#define startlayer 0
#define endlayer 9
#define startcolumn 0
#define endcolumn 56

class Tracking :public GHbase {
  public:
    Tracking(TTree *tree=0);

    void Loop(int evnum_begin, int evnum_end, int drawEvent=1);
    void Loop(){Loop(0,-1);}          //overrides Loop() function in GHbase

    void Next();
    void NextNiceTrack();
    void Prev();
    void ShowEvent(int event_number);

    void SetDriftModel(double A, double B, double C, double D);
    void ResetDriftModel();
    void FitDriftModel();
    double fcnDriftModelWrapper(double *x, double *p);

    double timeIntegralFunction(double *x, double *p);

    static const int numlayers = endlayer-startlayer;
    static const int numcolumns = endcolumn-startcolumn;

    Double_t trackResidual;
    //drift model parameters
    double drA, drB, drC, drD;
    double driftRadiusError;

    Int_t runnum;
    Int_t writeTrackMap;
    Int_t writeChi2Map;

    int nGoodHits;

    // histograms
    TH3F *hitmap;
    TH2F *occupancy, *occupancyPercent;
    TH2F *numTriggers;
    TH2F *scintillatorHits2D;
    TH1F *scintillatorHits;
    TH1F *h_chi2;
    TH1F *times, *times2, *times3;

    TLine *track;
    TPolyLine3D *track3D;
    TCanvas *c1;
    TPad *pad1;
    TPad *pad2;

    int ev_num;
    std::map<int,double> track_chi2_map;

    int numGoodTracks;
    int numSmallHitTracks;
    unsigned long minMultiplicity;
    double smallHitTime;
    double maxChi2;
    int maxTime;

    bool goodTrack;

    TMinuit *minuitPointer;

private:
    void DrawSingleEvent(int statusXY);
    void DrawSingleEvent3D(int statusXY, int statusXZ);
    void DrawMultipleEvents();
    bool isTrackGood();
    void RemapColumns();
    int isCellOnForRun(int col, int layer, int runnum);
    bool isZGood(int i);
    void RecalculateDriftRadius();
    void RescaleZ();

    std::map<int,double> track_m_map;
    std::map<int,double> track_c_map;

    //contains the indeces of the hits in the v_column, v_layer etc vectors when sorted from bottom layer to top.
    vector<int> v_i;

    std::vector<int> *v_layer2;
    std::vector<int> *v_column2;

    int hitInTrack[numlayers][numcolumns];
    CellGeom *cell;

    //shapes for 3D event drawing
    TGeoManager *geom;
    TGeoMaterial *mat;   
    TGeoMedium *med;
    TGeoVolume *top;
    TGeoBBox *box;

};

#endif

#ifdef Tracking_cxx
Tracking::Tracking(TTree *tree) : GHbase(tree)
{
  
  writeTrackMap=1;
  writeChi2Map=1;
  numGoodTracks = 0;
  numSmallHitTracks = 0;
  minMultiplicity = 1;
  runnum = -1;
  ev_num=0;
  maxChi2 = 1e10;

  //drift model parameters
  drA = 0.6759;
  drB = 0.84;
  drC = 287.09;
  drD = 0.0188;
//  drD=0.0;

  driftRadiusError=0.2;
  smallHitTime = 300;
  maxTime = 10000;

  v_layer2 = new std::vector<int>(10);
  v_column2 = new std::vector<int>(10);

  times = new TH1F("times","Anode Times",10000,0,10000);
  times2 = new TH1F("times2","Anode Times",10000,0,10000);
  times3 = new TH1F("times3","Anode Times",10000,0,10000);

  occupancy = new TH2F("Occupancy","Occupancy",numcolumns,0,246.4,numlayers,0,39.6);
  occupancy->GetXaxis()->SetTitle("Column");
  occupancy->GetYaxis()->SetTitle("Layer");

  occupancyPercent = (TH2F*)occupancy->Clone();
  occupancyPercent->SetName("occupancyPercent");
  occupancyPercent->SetTitle("Occupancy %");
  occupancyPercent->SetMinimum(0);
  occupancyPercent->SetMaximum(15);

  numTriggers = (TH2F*)occupancy->Clone();
  numTriggers->SetName("numTriggers");
  numTriggers->SetTitle("Number of Triggers");

  hitmap = new TH3F("hitmap", "hitmap",numcolumns,0,246.4,300,0,300,numlayers,0,39.6);
  hitmap->GetXaxis()->SetTitle("Column");
  hitmap->GetZaxis()->SetTitle("Layer");
  hitmap->GetYaxis()->SetTitle("Z");

  scintillatorHits = new TH1F("scintillatorHits","",numcolumns,0,246.4);
  scintillatorHits2D = new TH2F("scintillatorHits2D","",numcolumns,0,246.4,300,0,300); 
  cell = new CellGeom(1);

  c1 = new TCanvas("c1", "Occupancy Percentage", 1300, 707);
  pad1 = new TPad("pad1","",0.0,0.2,1.0,1.0);
  pad2 = new TPad("pad2","",0.0,0.0,1.0,0.2);
  pad1->Draw();
  pad2->Draw();

  Double_t geomOrigin[3] = {123.2,150,20};

  geom = new TGeoManager("myGlobe", "Globe");
  geom->SetVerboseLevel(0);
  mat = new TGeoMaterial("vacuum",0,0,0);    
  med = new TGeoMedium("vacuum", 1, mat);
  box = new TGeoBBox("BOX",123.2,150,20,geomOrigin);
  top = new TGeoVolume("TOP",box,med);
  geom->SetTopVolume(top);
  //top->SetLineColor(kMagenta);
  //geom->SetTopVisible();

}
#endif // #ifdef Tracking_cxx

