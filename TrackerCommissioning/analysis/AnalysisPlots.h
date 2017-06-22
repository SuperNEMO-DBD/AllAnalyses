#ifndef AnalysisPlots_h
#define AnalysisPlots_h

#include "../ntuplizer/GHbase.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <sstream>
#include <string>

#define startlayer 0
#define endlayer 9
#define startcolumn 0
#define endcolumn 56

#define hotcelloccupancy 5
#define coldcelloccupancy 0.5

#define mincathodeoccupancy 30

#define timebins 102
#define maxtime 80000
#define maxanodetime 30240
#define cellCutoffPercent 0
#define nHitsLow 0
#define nHitsHigh 100

class AnalysisPlots :public GHbase {
  public :
    AnalysisPlots(TTree *tree=0);
    void     Loop();

    static const int layers = endlayer-startlayer;
    static const int columns = endcolumn-startcolumn;

/*  C0
    static const int nRedCells = 6;
    static const int nAltRedCells = 1;
    static const int nAltRedCellsPartial = 7;
    static const int nAmberCells = 0;*/

//  C1
    static const int nRedCells = 5;
    static const int nAltRedCells = 3;
    static const int nAltRedCellsPartial = 3;
    static const int nAmberCells = 0;

    int runnum;

    
    // histograms
    TH2F *numTriggers, *occupancy, *driftTime, *occupancyPercent;
    TH2F *occupancyAnodeCtGood, *occupancyAnodeCbGood, *occupancyAnodeCBothGood, *occupancyAnodeCEitherGood, *occupancyCathodeSum;
    TH2F *driftTimect, *driftTimecb, *driftTimeCathodeTotal;
    TH2F *anStat, *ctStat, *cbStat;
    TH1F *hotCellTime, *normalCellTime;
    TH1F *occupiedCells;
    TH1F *anDriftTime, *propTime;
    TH2F *occupancyFT;

    //time offset histograms
    TH2F *timeOffsetLeft,*timeOffsetDown, *timeOffsetRight, *timeOffsetUp;
    TH2F *occupancyLeft,*occupancyDown,*occupancyUp,*occupancyRight;

    //1D statistics plots
    TH1F *occupancyDist, *driftTimeDist, *propTimeDist;
    TH1F *occupancyCBothDist, *occupancyCEitherDist, *occupancyCbDist, *occupancyCtDist;


    //overlays
    TGraphErrors *trafficLights[7];
    TGraphErrors *trafficLightsFT[7];

    TGraphErrors *cellHighlight;
    
    /* Traffic Lights:
      0: green (good) 
      1: dark green (good, hot)
      2: light green (no data, connected)
      3: amber (status uncertain)
      4: red (dead)
      5: dark red (channel trips)
      6: partially dark red/light green (one channel in this set of cells trips)
    currently only is right if drawn in order 0->5 */

    int multiRunMode;

    //functions
    int isCellOnForRun(int col, int layer, int runnum, int multiRunMode);
    void cassette_to_FT(int cassetteColA, int cassetteLayer, int* xOffset, int* yOffset);
        void RemapColumns();
    

};

#endif

#ifdef AnalysisPlots_cxx
AnalysisPlots::AnalysisPlots(TTree *tree) : GHbase(tree)
{
  if (tree==0){
    multiRunMode = 0;
      } else {
    multiRunMode = 1;
  }

/*   C0!
    //red overlay
    Double_t redCellsx[nRedCells] = {2.5,8.5,29.5,27.5,27.5,42.5};
    Double_t redCellsxErr[nRedCells]={0.5,0.5,0.5,0.5,0.5,0.5};
    Double_t redCellsy[nRedCells] = {3.5,3.5,4.5,8.5,6.5,8.5};
    Double_t redCellsyErr[nRedCells]= {0.5,0.5,0.5,0.5,0.5,0.5};

    //dark red
    Double_t altRedCellsx[nAltRedCells] = {2.5};//,43.5};
    Double_t altRedCellsxErr[nAltRedCells]={0.5};//,0.5};
    Double_t altRedCellsy[nAltRedCells] = {4.5};//,7.5};
    Double_t altRedCellsyErr[nAltRedCells]= {0.5};//,0.5};

    //dark red (partial)
    Double_t altRedCellsPartialx[nAltRedCellsPartial] = {43,43,43,43,43,43,43};
    Double_t altRedCellsPartialxErr[nAltRedCellsPartial]={0.5,0.5,0.5,0.5,0.5,0.5,0.5};
    Double_t altRedCellsPartialy[nAltRedCellsPartial] = {1.755,2.76,3.76,4.76,5.76,6.76,7.76};
    Double_t altRedCellsPartialyErr[nAltRedCellsPartial]= {0.5,0.5,0.5,0.5,0.5,0.5,0.5};

     //amber
    Double_t amberCellsx[nAmberCells] = {};
    Double_t amberCellsxErr[nAmberCells]={};
    Double_t amberCellsy[nAmberCells] = {};
    Double_t amberCellsyErr[nAmberCells]={};
*/

//   C1!
/*    //red overlay
    Double_t redCellsx[nRedCells] = {40.5};
    Double_t redCellsxErr[nRedCells]={0.5};
    Double_t redCellsy[nRedCells] = {0.5};
    Double_t redCellsyErr[nRedCells]= {0.5};

    //dark red
    Double_t altRedCellsx[nAltRedCells] = {};//,43.5};
    Double_t altRedCellsxErr[nAltRedCells]={};//,0.5};
    Double_t altRedCellsy[nAltRedCells] = {};//,7.5};
    Double_t altRedCellsyErr[nAltRedCells]= {};//,0.5};

    //dark red (partial)
    Double_t altRedCellsPartialx[nAltRedCellsPartial] = {};
    Double_t altRedCellsPartialxErr[nAltRedCellsPartial]={};
    Double_t altRedCellsPartialy[nAltRedCellsPartial] = {};
    Double_t altRedCellsPartialyErr[nAltRedCellsPartial]= {};

     //amber
    Double_t amberCellsx[nAmberCells] = {55};
    Double_t amberCellsxErr[nAmberCells]={1};
    Double_t amberCellsy[nAmberCells] = {4.5};
    Double_t amberCellsyErr[nAmberCells]={4.5};

    */

//   C2!
    Double_t redCellsx[nRedCells] = {26.5,39.5,49.5,49.5,55.5};
    Double_t redCellsxErr[nRedCells]={0.5,0.5,0.5,0.5,0.5};
    Double_t redCellsy[nRedCells] = {8.5,8.5,4.5,8.5,7.5};
    Double_t redCellsyErr[nRedCells]= {0.5,0.5,0.5,0.5,0.5};

    //dark red
    Double_t altRedCellsx[nAltRedCells] = {2.5,8.5,8.5};//,43.5};
    Double_t altRedCellsxErr[nAltRedCells]={0.5,0.5,0.5};//,0.5};
    Double_t altRedCellsy[nAltRedCells] = {2.5,0.5,1.5};//,7.5};
    Double_t altRedCellsyErr[nAltRedCells]= {0.5,0.5,0.5};//,0.5};

    //dark red (partial)
    Double_t altRedCellsPartialx[nAltRedCellsPartial] = {2.5,8.5,8.5};;
    Double_t altRedCellsPartialxErr[nAltRedCellsPartial]={0.5,0.5,0.5};
    Double_t altRedCellsPartialy[nAltRedCellsPartial] = {2.5,0.5,1.5};
    Double_t altRedCellsPartialyErr[nAltRedCellsPartial]= {0.5,0.5,0.5};

     //amber
    Double_t amberCellsx[nAmberCells] = {};
    Double_t amberCellsxErr[nAmberCells]={};
    Double_t amberCellsy[nAmberCells] = {};
    Double_t amberCellsyErr[nAmberCells]={};


// C3!
/*
    Double_t redCellsx[1] = {5.5};
    Double_t redCellsxErr[1]={0.5};
    Double_t redCellsy[1] = {3.5};
    Double_t redCellsyErr[1]= {0.5};
    //dark red
    Double_t altRedCellsx[nAltRedCells] = {};
    Double_t altRedCellsxErr[nAltRedCells]={};
    Double_t altRedCellsy[nAltRedCells] = {};
    Double_t altRedCellsyErr[nAltRedCells]= {};

    //dark red (partial)
    Double_t altRedCellsPartialx[nAltRedCellsPartial] = {};
    Double_t altRedCellsPartialxErr[nAltRedCellsPartial]={};
    Double_t altRedCellsPartialy[nAltRedCellsPartial] = {};
    Double_t altRedCellsPartialyErr[nAltRedCellsPartial]= {};

     //amber
    Double_t amberCellsx[nAmberCells] = {};
    Double_t amberCellsxErr[nAmberCells]={};
    Double_t amberCellsy[nAmberCells] = {};
    Double_t amberCellsyErr[nAmberCells]={};
    */


    //overlay for highlighting selected cells
    Double_t cellHighlightxErr[3]={0.5,0.5,0.5};
    Double_t cellHighlightyErr[3]={0.5,0.5,0.5};    

    Double_t cellHighlightx[3]={3.5,9.5,9.5};
    Double_t cellHighlighty[3]={2.5,0.5,1.5};

    cellHighlight = new TGraphErrors(3,cellHighlightx,cellHighlighty,cellHighlightxErr,cellHighlightyErr);
    cellHighlight->GetXaxis()->SetRange(startcolumn,endcolumn);
    cellHighlight->GetYaxis()->SetRange(startlayer,endlayer);

    
  for (int i_tl=0; i_tl<7; i_tl++){
    trafficLights[i_tl]=new TGraphErrors();
    if (i_tl==3) trafficLights[i_tl] = new TGraphErrors(nAmberCells,amberCellsx,amberCellsy,amberCellsxErr,amberCellsyErr);
    if (i_tl==4) trafficLights[i_tl] = new TGraphErrors(nRedCells,redCellsx,redCellsy,redCellsxErr,redCellsyErr);
    if (i_tl==5) trafficLights[i_tl] = new TGraphErrors(nAltRedCells,altRedCellsx,altRedCellsy,altRedCellsxErr,altRedCellsyErr);
    if (i_tl==6) trafficLights[i_tl] = new TGraphErrors(nAltRedCellsPartial,altRedCellsPartialx,altRedCellsPartialy,altRedCellsPartialxErr,altRedCellsPartialyErr);
    trafficLights[i_tl]->GetXaxis()->SetRange(startcolumn,endcolumn);
    trafficLights[i_tl]->GetYaxis()->SetRange(startlayer,endlayer);
  }
    
  occupancy = new TH2F("occupancy","Occupancy",columns,startcolumn,endcolumn,layers,startlayer,endlayer);
  occupancy->GetXaxis()->SetTitle("Column");
  occupancy->GetYaxis()->SetTitle("Layer");
  occupancy->GetYaxis()->SetNdivisions(10);

  numTriggers = (TH2F*)occupancy->Clone();
  numTriggers->SetName("numTriggers");
  numTriggers->SetTitle("Number of Triggers");
  
  occupancyPercent = (TH2F*)occupancy->Clone();
  occupancyPercent->SetName("occupancyPercent");
  occupancyPercent->SetTitle("Occupancy %");
  occupancyPercent->SetMinimum(0);
  occupancyPercent->SetMaximum(25);
  occupancyPercent->GetZaxis()->SetRangeUser(0.0, 25.0);

  occupancyFT = new TH2F("occupancyFT","Occupancy - FT layout",columns+(int)columns/2,startcolumn,endcolumn + (int)columns/2,layers,startlayer,endlayer);

  occupancyAnodeCtGood = (TH2F*)occupancy->Clone();
  occupancyAnodeCtGood->SetName("occupancyAnodeCtGood");
  occupancyAnodeCtGood->SetTitle("% Anode hits with associated top cathode signal");

  occupancyCathodeSum = (TH2F*)occupancy->Clone();
  occupancyCathodeSum->SetName("occupancyCathodeSum");
  occupancyCathodeSum->SetTitle("Sum of cathode efficiencies");

  occupancyAnodeCbGood = (TH2F*)occupancy->Clone();
  occupancyAnodeCbGood->SetName("occupancyAnodeCbGood");
  occupancyAnodeCbGood->SetTitle("% Anode hits with associated bottom cathode signal");

  occupancyAnodeCBothGood = new TH2F("occupancyAnodeCBothGood","% Anode hits with two cathode signals",columns,startcolumn,endcolumn,layers,startlayer,endlayer);
  occupancyAnodeCEitherGood = new TH2F("occupancyAnodeCEitherGood","% Anode hits with at least one cathode signal",columns,startcolumn,endcolumn,layers,startlayer,endlayer);

  driftTime= (TH2F*)occupancy->Clone();
  driftTime->SetName("driftTime");
  driftTime->SetTitle("Mean Anode Drift Time");
  driftTime->SetMinimum(0);

  driftTimect= (TH2F*)occupancy->Clone();
  driftTimect->SetName("driftTimeCathodeTop");
  driftTimect->SetTitle("Top Cathode Propagation Time");
  
  driftTimecb= (TH2F*)occupancy->Clone();
  driftTimecb->SetName("driftTimeCathodeBottom");
  driftTimecb->SetTitle("Bottom Cathode Propagation Time");
  
  driftTimeCathodeTotal = (TH2F*)occupancy->Clone();
  driftTimeCathodeTotal->SetName("driftTimeCathodeTotal");
  driftTimeCathodeTotal->SetTitle("Summed Cathode Propagation Time");

  anStat = new TH2F("anStat","Drift time vs Anode status bit",timebins,0,maxanodetime,2,0,2);
  ctStat = new TH2F("ctStat","Propagation time vs Cathode (Top) status bit",timebins,0,maxtime,2,0,2);
  cbStat = new TH2F("cbStat","Propagation time vs Cathode (Bottom) status bit",timebins,0,maxtime,2,0,2);

  hotCellTime = new TH1F("hotCellTime","Drift time (us)",timebins,0,maxanodetime/1000);
  normalCellTime = new TH1F("normalCellTime","Drift time (us)",timebins,0,maxanodetime/1000);

  occupiedCells = new TH1F("occupiedCells","Occupied cells per event",30,0,30);

  occupancyDist = new TH1F("occupancyDist", "Mean Anode Occupancy",30,0,15);
  occupancyDist->GetXaxis()->SetTitle("Mean Anode Occupancy (% of triggers)");
  occupancyDist->GetYaxis()->SetTitle("NCells");
  driftTimeDist = new TH1F("driftTimeDist", "Mean anode drift time (good cells)",30,0,15);
  driftTimeDist->GetXaxis()->SetTitle("Mean Drift Time (us)");
  driftTimeDist->GetYaxis()->SetTitle("NCells");
  propTimeDist = new TH1F("propTimeDist","Mean Plasma propagation time (good cells)",100,0,100);
  propTimeDist->GetXaxis()->SetTitle("Mean Plasma Propagation Time (us)");
  propTimeDist->GetYaxis()->SetTitle("NCells");

  occupancyCbDist = new TH1F("occupancyCbDist", "Mean Cathode Occupancy (bottom)",100,0,100);
  occupancyCbDist->GetXaxis()->SetTitle("Mean Cathode Occupancy (% of anode hits)");
  occupancyCbDist->GetYaxis()->SetTitle("NCells");
  occupancyCtDist = new TH1F("occupancyCtDist", "Mean Cathode Occupancy (top)",100,0,100);
  occupancyCtDist->GetXaxis()->SetTitle("Mean Cathode Occupancy (% of anode hits)");
  occupancyCtDist->GetYaxis()->SetTitle("NCells");
  occupancyCEitherDist = new TH1F("occupancyCEitherDist", "Mean Cathode Occupancy (either)",100,0,100);
  occupancyCEitherDist->GetXaxis()->SetTitle("Mean Cathode Occupancy (% of anode hits)");
  occupancyCEitherDist->GetYaxis()->SetTitle("NCells");
  occupancyCBothDist = new TH1F("occupancyCBothDist", "Mean Cathode Occupancy (both)",100,0,100);
  occupancyCBothDist->GetXaxis()->SetTitle("Mean Cathode Occupancy (% of anode hits)");
  occupancyCBothDist->GetYaxis()->SetTitle("NCells");


}

#endif // #ifdef AnalysisPlots_cxx
