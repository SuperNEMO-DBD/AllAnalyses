//
// CutFlowManager.h
//
// CV - 28/10.13
//
// This is a module to help manage the cut flow.
//

#ifndef NEMO_CUTFLOWMANAGER_H_
#define NEMO_CUTFLOWMANAGER_H_

#include "Hereward/DataProcPipeline/AppModule.h"
#include "Hereward/SuperNemoProcessing/RootOutputManager.h"
#include <map>
#include <vector>
#include "TH1D.h"

class CutFlowManager : public AppModule {

 public : 
  // Public members go here
  
  //--------------------------------------------------------------------------------
  // Constructor and Destructor
  //--------------------------------------------------------------------------------

  CutFlowManager(const std::string theName = "CutFlowManager",
		 const std::string theDescription = "Manages the cut flow and related output");
  
  virtual ~CutFlowManager();

  //--------------------------------------------------------------------------------
  // Operations
  //--------------------------------------------------------------------------------

  AppResult beginJob(AppEvent* aJob);
  AppResult beginRun(AppEvent* aRun);
  AppResult event(AppEvent* anEvent);
  AppResult endRun(AppEvent* aRun);
  AppResult endJob(AppEvent* aJob);

  //--------------------------------------------------------------------------------
  // Accessors
  //--------------------------------------------------------------------------------
  
  static CutFlowManager* instance();

  void AddHistogram(std::string name, double * var, int nBins, double xMin, double xMax);
  
  void PassCut( std::string cutName );
  
 private :
  // private members go here
  static CutFlowManager * cutFlowMan_;
  
  // Have two maps for easier look up. clumsy but effective (I hope!)
  std::map<std::string, int> cutNames_;
  std::map<int, std::string> cutNames_reverse_;

  std::vector<double> cutEvents_;
  
  std::vector<std::vector<TH1D*> > varHists_;
  std::vector<TH1D*> tempHistVec_;
  std::vector<std::string> histNames_;
  std::vector<double*> vars_;
  std::vector<int> nBins_;
  std::vector<double> xMins_;
  std::vector<double> xMaxs_;

  TH1D* hCutFlow_;

  std::string validXML(std::string in);

  RootOutputManager * nTupleManager_;

};


#endif
