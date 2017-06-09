//
// CutFlowManager.cpp
//
// CV - 28/10.13
//
// This is a module to help manage the cut flow.
//


#include "NemoMods/CutFlowManager.h"

//#include "Hereward/DataProcPipeline/AppModule.h"
#include "Hereward/SuperNemoProcessing/RootOutputManager.h"

#include <map>
#include <vector>
#include <fstream>
#include <iomanip>

#include "TH1D.h"

CutFlowManager* CutFlowManager::cutFlowMan_ = 0;

//--------------------------------------------------------------------------------
// Constructor
//--------------------------------------------------------------------------------

CutFlowManager::CutFlowManager(const std::string theName, 
			       const std::string theDescription) : 
  AppModule(theName, theDescription) {

  cutFlowMan_ = this;

  cutNames_ = std::map<std::string,int>();
  cutNames_reverse_ = std::map<int, std::string>();

  cutEvents_ = std::vector<double>();

  varHists_ = std::vector< std::vector<TH1D*> >();
  tempHistVec_ = std::vector<TH1D*>();
  
  histNames_ = std::vector<std::string>();
  vars_ = std::vector<double*>();
  nBins_ = std::vector<int>();
  xMins_ = std::vector<double>();
  xMaxs_ = std::vector<double>();
 
}

//--------------------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------------------

CutFlowManager::~CutFlowManager(){

  cutNames_.clear();
  cutNames_reverse_.clear();
  cutEvents_.clear();
  varHists_.clear();
  tempHistVec_.clear();
  histNames_.clear();
  vars_.clear();
  nBins_.clear();
  xMins_.clear();
  xMaxs_.clear();
 
}

//--------------------------------------------------------------------------------
// Operations
//--------------------------------------------------------------------------------

AppResult CutFlowManager::beginJob(AppEvent *aJob) {
  nTupleManager_ = RootOutputManager::instance();
}
AppResult CutFlowManager::beginRun(AppEvent *aRun){;}
AppResult CutFlowManager::event(AppEvent *anEvent){;}
AppResult CutFlowManager::endRun(AppEvent *aRun){;}
AppResult CutFlowManager::endJob(AppEvent *aJob){
  
  // Write out cutFlow in xml
  std::ofstream cutFlowTxt("CutFlow.xml");
  if (cutFlowTxt.is_open()){
    cutFlowTxt << "<?xml version=\"1.0\"?>" << std::endl;
    cutFlowTxt << "<cutFlow>" << std::endl;

    // Don't want number of events to be rounded
    cutFlowTxt << std::setprecision(10);

    
    for (int i = 0; i < cutNames_reverse_.size(); i++){
      cutFlowTxt << "  <cut>\n"
		 << "    <number>" << i << "</number>\n"
                 << "    <name>" << validXML(cutNames_reverse_[i]) << "</name>\n"
                 << "    <passEvents>" << cutEvents_.at(i) << "</passEvents>\n"
                 << "  </cut>\n";
    }
    
    cutFlowTxt << "</cutFlow>" << std::endl;
    
  } else {
    std::cout << "CutFlowManager::endJob : could not write the report" << std::endl;
    return  AppResult::ERROR;
  }

  // Make cut flow histogram
  hCutFlow_ = nTupleManager_->addHistogram(name(), "hCutFlow_", cutNames_reverse_.size(),
					      0, cutNames_reverse_.size()+1);
  // Set bin labels and set bin contents
  for (int i = 1; i <= hCutFlow_->GetNbinsX(); i++){
    hCutFlow_->GetXaxis()->SetBinLabel(i,cutNames_reverse_.at(i-1).c_str());
    hCutFlow_->SetBinContent(i, cutEvents_.at(i-1));
  }
  
}

//--------------------------------------------------------------------------------
// Accessors
//--------------------------------------------------------------------------------

CutFlowManager * CutFlowManager::instance(){
  if (cutFlowMan_ == 0)
    cutFlowMan_ = new CutFlowManager();
  return cutFlowMan_;
}

void CutFlowManager::PassCut(std::string cutName){

  std::map<std::string, int>::iterator it;

  it = cutNames_.find(cutName);

  // Check if cut already exists:
  if ( it == cutNames_.end() ) {

    // Cut doesn't exist yet
    // Cut Number:
    int cutNum = cutNames_.size();

    // Add cut name to map:
    cutNames_[cutName] = cutNum;
    cutNames_reverse_[cutNum] = cutName;
    
    // Add new cut to vector with 1 event:
    cutEvents_.push_back(1);

    char nameBuff[100];
     
    // Loop through histograms and add one histogram
    for (int i = 0; i < vars_.size(); i++){

      sprintf(nameBuff, "%s_%i", histNames_.at(i).c_str(), cutNum);
      
      TH1D * tempHist_ = nTupleManager_->addHistogram(name(), 
						      nameBuff, 
						      nBins_.at(i), 
						      xMins_.at(i), 
						      xMaxs_.at(i));

      tempHistVec_.push_back( tempHist_);
     
      double * tempDbl = vars_.at(i);

      tempHistVec_.at(i)->Fill(*tempDbl);
      
    }

    varHists_.push_back(tempHistVec_);
    tempHistVec_.clear();

  } else {
    // Cut exists
    int cutNum = it->second;
    
    // Increment event count
    cutEvents_.at(cutNum) += 1;
    
    for (int i = 0; i < varHists_.at(cutNum).size(); i++){
      varHists_.at(cutNum).at(i)->Fill(*(vars_.at(i)));
    }
    
  }
}


void CutFlowManager::AddHistogram(std::string name, double *var, int nBins, double xMin, double xMax){

  histNames_.push_back(name);
  vars_.push_back(var);
  nBins_.push_back(nBins);
  xMins_.push_back(xMin);
  xMaxs_.push_back(xMax);
  
}

std::string CutFlowManager::validXML(std::string in){

  std::string buffer;

  buffer.reserve(in.size());

  for(size_t pos = 0; pos != in.size(); ++pos) {
    switch(in[pos]) {
    case '&':  buffer.append("&amp;");       break;
    case '\"': buffer.append("&quot;");      break;
    case '\'': buffer.append("&apos;");      break;
    case '<':  buffer.append("&lt;");        break;
    case '>':  buffer.append("&gt;");        break;
    default:   buffer.append(1, in[pos]); break;
    }
  }
  return buffer;
}
