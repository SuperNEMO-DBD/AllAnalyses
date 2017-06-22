#define Plots_cxx
#include "Plots.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

using namespace std;

void Plots::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L Plots.C
//      Root > Plots t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nb = 0;

  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);
    if (nb == 0) continue;
    for (size_t i=0; i<v_column->size(); i++)
    {

      cout << "TEST: i = "<<i<<" size="<<v_column->size()<< endl;
      int layer = (*v_layer)[i];
      int col = (*v_column)[i];
      int ano = (*v_anode)[i];
      int tc  = (*v_cattop)[i];
      int tb  = (*v_catbot)[i];
      float zh  = (*v_z)[i];
      float rh  = (*v_r)[i];

      if (layer<9){
        occu[layer]->Fill(float(col));
        anod[layer]->Fill(float(ano));
        topc[layer]->Fill(float(tc));
        botc[layer]->Fill(float(tb));
        zpos[layer]->Fill(zh);
        rpos[layer]->Fill(rh);
      }
    }
    // occu, anod, topc, botc, zpos, rpos;
  }
}
