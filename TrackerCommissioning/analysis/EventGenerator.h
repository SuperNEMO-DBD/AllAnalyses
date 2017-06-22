#ifndef EventGenerator_h
#define EventGenerator_h

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TF1.h>
#include <TRandom3.h>
#include <TMath.h>
#include <TGeoManager.h>
#include <TGeoVolume.h>
#include <TGeoMaterial.h>
#include <TGeoMedium.h>
#include <TGeoBuilder.h>
#include <TGeoBBox.h>
#include <TCanvas.h>
#include <TPolyLine3D.h>
#include <TGeoTrack.h>
#include <TVector3.h>

class EventGenerator{
public :

	EventGenerator();

	void GenerateEvents(int nEvents = 100);
  void GenerateEvent(int evnum = 0);
  void GenerateRay(TVector3 *rayVector);
	void GenerateEndPoint(TVector3 *endPoint);

  TCanvas *c1;

	TFile *file;
   TTree *tree;

  ULong64_t evnum, evtime;
  Int_t runnum;
  std::vector<int> *v_module;
  std::vector<int> *v_side;
  std::vector<int> *v_layer;
  std::vector<int> *v_column;
  std::vector<int> *v_asicval;
  std::vector<int> *v_asicstat;
  std::vector<int> *v_anode;
  std::vector<int> *v_cattop;
  std::vector<int> *v_catbot;
  std::vector<int> *v_alpha;
  std::vector<float> *v_time;
  std::vector<float> *v_r;
  std::vector<float> *v_z;



    TF1 *cosmicDistribution, *driftModel;
    TRandom3 *random;

        //shapes for 3D event drawing
    TGeoVolume *top;
    TGeoManager *geom;
    TGeoMaterial *mat;   
    TGeoMedium *med;
    TGeoBBox *box;
private:
    //centre of scintillator plane offset from edges of detector
    double scXOffset;
    double scYOffset;
    double scZOffset;

    double spanX;
    double spanY;
    double spanZ;

    double cellWidth;
    int numColumns;

};

#endif

#ifdef EventGenerator_cxx
EventGenerator::EventGenerator(){

  scXOffset = 87.8;
  scYOffset = 0;
  scZOffset = -37.8;

  spanX = 246.4; 
  spanY = 300;
  spanZ = 39.6;

  cellWidth = 4.4;  //offset along wires
  numColumns = (int)(spanX/cellWidth);

  random = new TRandom3(0);
  gRandom->SetSeed(0);
  cosmicDistribution = new TF1("cosmicDistribution","cos(x)*cos(x)",-1*TMath::PiOver2(),1*TMath::PiOver2());
  driftModel = new TF1("driftModel","((0.6759*x)/((x^0.84)+287.09))+0.0188",0,50000);

  file = new TFile("generated.root","RECREATE","generated commissioning events");
  tree = new TTree("raw","raw");

  v_module = new std::vector<int>(10);
  v_side = new std::vector<int>(10);
  v_layer = new std::vector<int>(10);
  v_column = new std::vector<int>(10);
  v_asicval = new std::vector<int>(10);
  v_asicstat = new std::vector<int>(10);
  v_anode = new std::vector<int>(10);
  v_cattop = new std::vector<int>(10);
  v_catbot = new std::vector<int>(10);
  v_alpha = new std::vector<int>(10);
  v_time = new std::vector<float>(10);
  v_r = new std::vector<float>(10);
  v_z = new std::vector<float>(10);

	tree->Branch("evnum", &evnum, "evnum/l");
	tree->Branch("evtime", &evtime, "evtime/l");
	tree->Branch("runnum", &runnum, "runnum/I");
	tree->Branch("v_module", "vector<int>", &v_module);
	tree->Branch("v_side", "vector<int>", &v_side);
	tree->Branch("v_layer", "vector<int>", &v_layer);
	tree->Branch("v_column", "vector<int>", &v_column);
	tree->Branch("v_asicval", "vector<int>", &v_asicval);
	tree->Branch("v_asicstat", "vector<int>", &v_asicstat);
	tree->Branch("v_anode", "vector<int>", &v_anode);
	tree->Branch("v_cattop", "vector<int>", &v_cattop);
	tree->Branch("v_catbot", "vector<int>", &v_catbot);
	tree->Branch("v_alpha", "vector<int>", &v_alpha);
	tree->Branch("v_time", "vector<float>", &v_time);
	tree->Branch("v_r", "vector<float>", &v_r);
	tree->Branch("v_z", "vector<float>", &v_z);

  c1 = new TCanvas("c1", "Occupancy Percentage", 1300, 707);

  Double_t geomOrigin[3] = {spanX/2,0,spanZ/2};

  geom = new TGeoManager("myGlobe", "Globe");
  geom->SetVerboseLevel(0);
  mat = new TGeoMaterial("vacuum",0,0,0);    
  med = new TGeoMedium("vacuum", 1, mat);
  box = new TGeoBBox("BOX",spanX/2,spanY/2,spanZ/2,geomOrigin);
  top = new TGeoVolume("TOP",box,med);
  geom->SetTopVolume(top);
  top->SetLineColor(kMagenta);
  geom->SetTopVisible();

  TGeoVolume *hit = geom->MakeBox("HIT",med,cellWidth/2,spanY/2,cellWidth/2);
  hit->SetLineColorAlpha(kGray,0.4);

  for (int i=0; i<504;i++) {
    TGeoTranslation *hitPos = new TGeoTranslation((cellWidth*(i%numColumns)) + cellWidth/2 ,0,(cellWidth*(i/numColumns)) + cellWidth/2);
    top->AddNode(hit,i,hitPos); 
  }

  hit = geom->MakeBox("SCINT",med,50,50,1);

  TGeoTranslation *scintPos = new TGeoTranslation(scXOffset ,0,scZOffset);
  top->AddNode(hit,505,scintPos);
  scintPos = new TGeoTranslation(scXOffset ,0,scZOffset-4);
  top->AddNode(hit,506,scintPos);


  top->Draw("BOX");

}
#endif // #ifdef EventGenerator_cxx
