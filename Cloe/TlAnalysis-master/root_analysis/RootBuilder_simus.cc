// Author: Cloé Girard-Carillo girardcarillo@lal.in2p3.fr
// Macro to study 208Tl simulations for timing analysis

#include <TTree.h>
#include <string>
#include <TFile.h>
#include <iostream>
#include <TObject.h>
#include <TH1.h>
#include <TH2.h>
#include <sstream>

#include "EventTree.h"

/*------------------------------------------------------------*/

using namespace std;

const double LET=0.150;
const double HET=0.300;

void RootBuilder_simus(string filename, bool cut_multiplicity){

  TFile *theInFile = new TFile(filename.c_str(),"READ");
  TTree *theInTree = nullptr;
  theInFile->GetObject("T",theInTree);

  if (theInFile->IsOpen()) {
    cout << "File " << theInFile->GetName() << " opened sucessfully" << endl;
  }

  const char* nameOutFile = "Cut_60Co.root";

  TFile *theOutFile = new TFile(nameOutFile, "RECREATE", "Output file of cut Simulation data");
  theOutFile->cd();

  if (theOutFile->IsOpen()) {
    cout << "File " << theOutFile->GetName() << " opened sucessfully" << endl;
  }

  theInTree = (TTree*)theInFile->Get("SimData");

  theInTree->SetBranchAddress("calo.type",&InCalo_type);
  theInTree->SetBranchAddress("calo.row",&InCalo_row);
  theInTree->SetBranchAddress("calo.column",&InCalo_column);
  theInTree->SetBranchAddress("calo.id",&InCalo_id);
  theInTree->SetBranchAddress("calo.side",&InCalo_side);
  theInTree->SetBranchAddress("calo.wall",&InCalo_wall);
  theInTree->SetBranchAddress("calo.time",&InCalo_time);
  theInTree->SetBranchAddress("calo.energy",&InCalo_energy);
  //theInTree->SetBranchAddress("calo.sigmaenergy",&InCalo_sigmaenergy);

  TTree *theOutTree = new TTree("DataCut","DataCut");
  theOutTree->SetDirectory(theOutFile);

  vector<int> trigger_id;
  vector<int> calo_type;
  vector<int> calo_row;
  vector<int> calo_column;
  vector<int> calo_id;
  vector<int> calo_side;
  vector<int> calo_wall;
  vector<double> calo_time;
  vector<double> calo_energy;
  //vector<double> calo_sigmaenergy;

  theOutTree->Branch("trigger_id", &trigger_id);
  theOutTree->Branch("calo_type", &calo_type);
  theOutTree->Branch("calo_row", &calo_row);
  theOutTree->Branch("calo_column", &calo_column);
  theOutTree->Branch("calo_side", &calo_side);
  theOutTree->Branch("calo_wall", &calo_wall);
  theOutTree->Branch("calo_time", &calo_time);
  theOutTree->Branch("calo_energy", &calo_energy);
  //theOutTree->Branch("calo_sigmaenergy", &calo_sigmaenergy);
  theOutTree->Branch("cut_multiplicity", &cut_multiplicity);

  cout << theInTree->GetEntries() << " entries"<< endl;

  // theInTree->Print();

  for (Long64_t i_event=0;i_event<theInTree->GetEntries();i_event++) {
    theInTree->GetEntry(i_event);

    trigger_id.clear();
    calo_type.clear();
    calo_row.clear();
    calo_column.clear();
    calo_id.clear();
    calo_side.clear();
    calo_wall.clear();
    calo_time.clear();
    calo_energy.clear();

    if (i_event%100000==0) cout << "event " << i_event << endl;

    bool condition_multiplicity;
    if (cut_multiplicity) {
      condition_multiplicity=InCalo_row->size()==2;
    }
    else {
      condition_multiplicity=true;
    }

    bool flag_main_wall=1;
    for (int k = 0; k < InCalo_row->size(); ++k) {
      if (InCalo_type->at(k)!=0) {
        flag_main_wall=0;
      }
    }

    // bool flag_side=1;
    // for (int k = 0; k < InCalo_row->size(); ++k) {
    //   if (InCalo_side->at(k)!=side) {
    //     flag_side=0;
    //   }
    // }

    // energy threshold
    bool flag_energy_threshold = 0;
    if (condition_multiplicity) {
      for (int i_energy = 0; i_energy < InCalo_energy->size(); ++i_energy) {
        if (InCalo_energy->at(0)>LET&&InCalo_energy->at(1)>LET) {
          if (InCalo_energy->at(0)>HET||InCalo_energy->at(1)>HET) {
            flag_energy_threshold=1;
          }
        }
      }
    }

    if (flag_energy_threshold) {
      //if (flag_side) {
      if (flag_main_wall) {
        if (condition_multiplicity) {
          for (int k = 0; k < InCalo_row->size(); ++k) {
            trigger_id.push_back(i_event);
            calo_type.push_back(InCalo_type->at(k));
            calo_row.push_back(InCalo_row->at(k));
            calo_column.push_back(InCalo_column->at(k));
            calo_id.push_back(InCalo_id->at(k));
            calo_side.push_back(InCalo_side->at(k));
            calo_wall.push_back(InCalo_wall->at(k));
            calo_time.push_back(InCalo_time->at(k));
            calo_energy.push_back(InCalo_energy->at(k));
          }
          theOutTree->Fill();
        }

      }// end multiplicity
    }// end flag main wall
    //}// end flag side

    // if (i_event==1000) {
    //   break;
    // }

  }// end for loop on tree events

  theOutFile->Write();

  theInTree->ResetBranchAddresses();

  theInFile->Close();
  theOutFile->Close();
  if (!theInFile->IsOpen()) {
    cout << "File " << theInFile->GetName() << " closed sucessfully" << endl;
  }
  if (!theOutFile->IsOpen()) {
    cout << "File " << theOutFile->GetName() << " closed sucessfully" << endl;
  }
  delete theInFile;
  delete theOutFile;

}
