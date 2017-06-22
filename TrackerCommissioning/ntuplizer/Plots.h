#ifndef Plots_h
#define Plots_h

#include "GHbase.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <sstream>
#include <string>

class Plots :public GHbase {
  public :
    Plots(TTree *tree=0);
    void     Loop();

    // histogrammes
    //
    TH1F *occu[9], *anod[9], *topc[9], *botc[9], *zpos[9], *rpos[9];
};

#endif

#ifdef Plots_cxx
Plots::Plots(TTree *tree) : GHbase(tree)
{
  for (int i=0; i<9; i++)
  {
    std::ostringstream ssh, sst;
    ssh << "occu" << i;
    sst << "Occupancy (layer " << i << ");column";
    occu[i] = new TH1F(ssh.str().c_str(), sst.str().c_str(), 60, 0., 60.);
  }

  for (int i=0; i<9; i++)
  {
    std::ostringstream ssh, sst;
    ssh << "anod" << i;
    sst << "Anode TDC (layer " << i << ");counts";
    anod[i] = new TH1F(ssh.str().c_str(), sst.str().c_str(), 100, 0., 350.);
  }

  for (int i=0; i<9; i++)
  {
    std::ostringstream ssh, sst;
    ssh << "topc" << i;
    sst << "Top Cathode TDC (layer " << i << ");counts";
    topc[i] = new TH1F(ssh.str().c_str(), sst.str().c_str(), 100, 0., 5000.);
  }

  for (int i=0; i<9; i++)
  {
    std::ostringstream ssh, sst;
    ssh << "botc" << i;
    sst << "Bottom Cathode TDC (layer " << i << ");counts";
    botc[i] = new TH1F(ssh.str().c_str(), sst.str().c_str(), 100, 0., 5000.);
  }

  for (int i=0; i<9; i++)
  {
    std::ostringstream ssh, sst;
    ssh << "zpos" << i;
    sst << "Z position (layer " << i << ");Z (cm)";
    zpos[i] = new TH1F(ssh.str().c_str(), sst.str().c_str(), 100, -150., 150.);
  }

  for (int i=0; i<9; i++)
  {
    std::ostringstream ssh, sst;
    ssh << "rpos" << i;
    sst << "R position (layer " << i << ");R (cm)";
    rpos[i] = new TH1F(ssh.str().c_str(), sst.str().c_str(), 100, 0., 2.5);
  }
}

#endif // #ifdef Plots_cxx
