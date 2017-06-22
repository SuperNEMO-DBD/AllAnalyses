#ifndef Anal_h
#define Anal_h

#include "GHbase.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>

class Anal :public GHbase {
public :
   Anal(TTree *tree=0);
   void     Loop();
};

#endif

#ifdef Anal_cxx
Anal::Anal(TTree *tree) : GHbase(tree)
{
}

#endif // #ifdef Anal_cxx
