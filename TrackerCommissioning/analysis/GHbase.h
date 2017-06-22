//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Apr 19 16:29:18 2015 by ROOT version 5.34/28
// from TTree raw/Commissioning Raw Tracker Data
// found on file: nothings.root
//////////////////////////////////////////////////////////

#ifndef GHbase_h
#define GHbase_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.

class GHbase {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   ULong64_t       evnum;
   ULong64_t       evtime;
   vector<int>     *v_module;
   vector<int>     *v_side;
   vector<int>     *v_layer;
   vector<int>     *v_column;
   vector<int>     *v_asicval;
   vector<int>     *v_asicstat;
   vector<int>     *v_anode;
   vector<int>     *v_cattop;
   vector<int>     *v_catbot;
   vector<int>     *v_alpha;
   vector<float>   *v_time;
   vector<float>   *v_r;
   vector<float>   *v_z;

   // List of branches
   TBranch        *b_evnum;   //!
   TBranch        *b_evtime;   //!
   TBranch        *b_v_module;   //!
   TBranch        *b_v_side;   //!
   TBranch        *b_v_layer;   //!
   TBranch        *b_v_column;   //!
   TBranch        *b_v_asicval;   //!
   TBranch        *b_v_asicstat;   //!
   TBranch        *b_v_anode;   //!
   TBranch        *b_v_cattop;   //!
   TBranch        *b_v_catbot;   //!
   TBranch        *b_v_alpha;   //!
   TBranch        *b_v_time;   //!
   TBranch        *b_v_r;   //!
   TBranch        *b_v_z;   //!

   GHbase(TTree *tree=0);
   virtual ~GHbase();
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef GHbase_cxx
GHbase::GHbase(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("nothings.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("nothings.root");
      }
      f->GetObject("raw",tree);

   }
   Init(tree);
}

GHbase::~GHbase()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t GHbase::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t GHbase::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void GHbase::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   v_module = 0;
   v_side = 0;
   v_layer = 0;
   v_column = 0;
   v_asicval = 0;
   v_asicstat = 0;
   v_anode = 0;
   v_cattop = 0;
   v_catbot = 0;
   v_alpha = 0;
   v_time = 0;
   v_r = 0;
   v_z = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("evnum", &evnum, &b_evnum);
   fChain->SetBranchAddress("evtime", &evtime, &b_evtime);
   fChain->SetBranchAddress("v_module", &v_module, &b_v_module);
   fChain->SetBranchAddress("v_side", &v_side, &b_v_side);
   fChain->SetBranchAddress("v_layer", &v_layer, &b_v_layer);
   fChain->SetBranchAddress("v_column", &v_column, &b_v_column);
   fChain->SetBranchAddress("v_asicval", &v_asicval, &b_v_asicval);
   fChain->SetBranchAddress("v_asicstat", &v_asicstat, &b_v_asicstat);
   fChain->SetBranchAddress("v_anode", &v_anode, &b_v_anode);
   fChain->SetBranchAddress("v_cattop", &v_cattop, &b_v_cattop);
   fChain->SetBranchAddress("v_catbot", &v_catbot, &b_v_catbot);
   fChain->SetBranchAddress("v_alpha", &v_alpha, &b_v_alpha);
   fChain->SetBranchAddress("v_time", &v_time, &b_v_time);
   fChain->SetBranchAddress("v_r", &v_r, &b_v_r);
   fChain->SetBranchAddress("v_z", &v_z, &b_v_z);
   Notify();
}

Bool_t GHbase::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void GHbase::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
#endif // #ifdef GHbase_cxx
