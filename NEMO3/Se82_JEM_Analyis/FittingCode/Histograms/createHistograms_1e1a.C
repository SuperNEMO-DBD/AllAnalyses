#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TTree.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TMath.h>
#include <iostream>
#include <TGaxis.h>
#include <string>

using namespace std;

void addHistogramToFile(string directory, string sample, string outfilename, int reqdAlphaSide, int reqdElectronSide, string suffix);
void addHistogramToFileInOut(string directory, string sample, string outfilename, int reqdAlphaSide, int reqdElectronSide, string suffix);

Int_t createHistograms_1e1a(){
  // Sort out root's horrible defaults
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  gStyle->SetCanvasBorderMode(0);

  // Set canvas margins and stats options to make plots nicer
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetTitleOffset(1.2,"y");
  gStyle->SetStatBorderSize(0);
  gStyle->SetOptStat(10);
  gStyle->SetStatX(0.946);
  gStyle->SetStatY(0.936);
  TGaxis::SetMaxDigits(3);

  // Open output file for histograms
  TFile* outfile = new TFile("./Histograms_1e1a.root","RECREATE");
  outfile->Close();
  delete outfile;

  int alphaSide = 1;
  int electronSide = 1;

  // Four different histogram combinations
  alphaSide = 1;
  electronSide = 1;
  addHistogramToFile("Data/","Data","./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteOut_Sector6");
  addHistogramToFile("InternalBackgrounds/","SeNew_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteOut_Sector6");
  addHistogramToFile("InternalBackgrounds/","SeOld_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteOut_Sector6");
  addHistogramToFile("InternalBackgrounds/","Mylar_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteOut_Sector6");
  addHistogramToFile("RadonBackgrounds/",   "SFoil_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteOut_Sector6");
  addHistogramToFile("RadonBackgrounds/",   "SWire_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteOut_Sector6");

  alphaSide = 1;
  electronSide = 0;
  addHistogramToFile("Data/","Data","./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteIn_Sector6");
  addHistogramToFile("InternalBackgrounds/","SeNew_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteIn_Sector6");
  addHistogramToFile("InternalBackgrounds/","SeOld_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteIn_Sector6");
  addHistogramToFile("InternalBackgrounds/","Mylar_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteIn_Sector6");
  addHistogramToFile("RadonBackgrounds/",   "SFoil_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteIn_Sector6");
  addHistogramToFile("RadonBackgrounds/",   "SWire_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteIn_Sector6");

  alphaSide = 0;
  electronSide = 1;
  addHistogramToFile("Data/","Data","./Histograms_1e1a.root", alphaSide, electronSide, "_aIneOut_Sector6");
  addHistogramToFile("InternalBackgrounds/","SeNew_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneOut_Sector6");
  addHistogramToFile("InternalBackgrounds/","SeOld_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneOut_Sector6");
  addHistogramToFile("InternalBackgrounds/","Mylar_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneOut_Sector6");
  addHistogramToFile("RadonBackgrounds/",   "SFoil_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneOut_Sector6");
  addHistogramToFile("RadonBackgrounds/",   "SWire_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneOut_Sector6");

  alphaSide = 0;
  electronSide = 0;
  addHistogramToFile("Data/","Data","./Histograms_1e1a.root", alphaSide, electronSide, "_aIneIn_Sector6");
  addHistogramToFile("InternalBackgrounds/","SeNew_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneIn_Sector6");
  addHistogramToFile("InternalBackgrounds/","SeOld_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneIn_Sector6");
  addHistogramToFile("InternalBackgrounds/","Mylar_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneIn_Sector6");
  addHistogramToFile("RadonBackgrounds/",   "SFoil_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneIn_Sector6");
  addHistogramToFile("RadonBackgrounds/",   "SWire_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneIn_Sector6");

  // Four different histogram combinations
  alphaSide = 1;
  electronSide = 1;
  addHistogramToFile("Data/","Data","./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteOut_Sector7");
  addHistogramToFile("InternalBackgrounds/","SeNew_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteOut_Sector7");
  addHistogramToFile("InternalBackgrounds/","SeOld_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteOut_Sector7");
  addHistogramToFile("InternalBackgrounds/","Mylar_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteOut_Sector7");
  addHistogramToFile("RadonBackgrounds/",   "SFoil_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteOut_Sector7");
  addHistogramToFile("RadonBackgrounds/",   "SWire_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteOut_Sector7");

  alphaSide = 1;
  electronSide = 0;
  addHistogramToFile("Data/","Data","./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteIn_Sector7");
  addHistogramToFile("InternalBackgrounds/","SeNew_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteIn_Sector7");
  addHistogramToFile("InternalBackgrounds/","SeOld_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteIn_Sector7");
  addHistogramToFile("InternalBackgrounds/","Mylar_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteIn_Sector7");
  addHistogramToFile("RadonBackgrounds/",   "SFoil_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteIn_Sector7");
  addHistogramToFile("RadonBackgrounds/",   "SWire_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteIn_Sector7");

  alphaSide = 0;
  electronSide = 1;
  addHistogramToFile("Data/","Data","./Histograms_1e1a.root", alphaSide, electronSide, "_aIneOut_Sector7");
  addHistogramToFile("InternalBackgrounds/","SeNew_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneOut_Sector7");
  addHistogramToFile("InternalBackgrounds/","SeOld_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneOut_Sector7");
  addHistogramToFile("InternalBackgrounds/","Mylar_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneOut_Sector7");
  addHistogramToFile("RadonBackgrounds/",   "SFoil_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneOut_Sector7");
  addHistogramToFile("RadonBackgrounds/",   "SWire_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneOut_Sector7");

  alphaSide = 0;
  electronSide = 0;
  addHistogramToFile("Data/","Data","./Histograms_1e1a.root", alphaSide, electronSide, "_aIneIn_Sector7");
  addHistogramToFile("InternalBackgrounds/","SeNew_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneIn_Sector7");
  addHistogramToFile("InternalBackgrounds/","SeOld_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneIn_Sector7");
  addHistogramToFile("InternalBackgrounds/","Mylar_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneIn_Sector7");
  addHistogramToFile("RadonBackgrounds/",   "SFoil_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneIn_Sector7");
  addHistogramToFile("RadonBackgrounds/",   "SWire_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneIn_Sector7");

  // Four different histogram combinations
  alphaSide = 1;
  electronSide = 1;
  addHistogramToFile("Data/","Data","./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteOut_Sector8");
  addHistogramToFile("InternalBackgrounds/","SeNew_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteOut_Sector8");
  addHistogramToFile("InternalBackgrounds/","SeOld_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteOut_Sector8");
  addHistogramToFile("InternalBackgrounds/","Mylar_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteOut_Sector8");
  addHistogramToFile("RadonBackgrounds/",   "SFoil_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteOut_Sector8");
  addHistogramToFile("RadonBackgrounds/",   "SWire_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteOut_Sector8");

  alphaSide = 1;
  electronSide = 0;
  addHistogramToFile("Data/","Data","./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteIn_Sector8");
  addHistogramToFile("InternalBackgrounds/","SeNew_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteIn_Sector8");
  addHistogramToFile("InternalBackgrounds/","SeOld_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteIn_Sector8");
  addHistogramToFile("InternalBackgrounds/","Mylar_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteIn_Sector8");
  addHistogramToFile("RadonBackgrounds/",   "SFoil_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteIn_Sector8");
  addHistogramToFile("RadonBackgrounds/",   "SWire_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aOuteIn_Sector8");

  alphaSide = 0;
  electronSide = 1;
  addHistogramToFile("Data/","Data","./Histograms_1e1a.root", alphaSide, electronSide, "_aIneOut_Sector8");
  addHistogramToFile("InternalBackgrounds/","SeNew_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneOut_Sector8");
  addHistogramToFile("InternalBackgrounds/","SeOld_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneOut_Sector8");
  addHistogramToFile("InternalBackgrounds/","Mylar_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneOut_Sector8");
  addHistogramToFile("RadonBackgrounds/",   "SFoil_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneOut_Sector8");
  addHistogramToFile("RadonBackgrounds/",   "SWire_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneOut_Sector8");

  alphaSide = 0;
  electronSide = 0;
  addHistogramToFile("Data/","Data","./Histograms_1e1a.root", alphaSide, electronSide, "_aIneIn_Sector8");
  addHistogramToFile("InternalBackgrounds/","SeNew_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneIn_Sector8");
  addHistogramToFile("InternalBackgrounds/","SeOld_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneIn_Sector8");
  addHistogramToFile("InternalBackgrounds/","Mylar_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneIn_Sector8");
  addHistogramToFile("RadonBackgrounds/",   "SFoil_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneIn_Sector8");
  addHistogramToFile("RadonBackgrounds/",   "SWire_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_aIneIn_Sector8");


  // All 4 combinations together to show how good fit is.
  alphaSide = -1;
  electronSide = -1;
  addHistogramToFile("Data/","Data","./Histograms_1e1a.root", alphaSide, electronSide, "_AllEvents_Sector6");
  addHistogramToFile("InternalBackgrounds/","SeNew_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_AllEvents_Sector6");
  addHistogramToFile("InternalBackgrounds/","SeOld_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_AllEvents_Sector6");
  addHistogramToFile("InternalBackgrounds/","Mylar_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_AllEvents_Sector6");
  addHistogramToFile("RadonBackgrounds/",   "SFoil_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_AllEvents_Sector6");
  addHistogramToFile("RadonBackgrounds/",   "SWire_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_AllEvents_Sector6");

  alphaSide = -1;
  electronSide = -1;
  addHistogramToFile("Data/","Data","./Histograms_1e1a.root", alphaSide, electronSide, "_AllEvents_Sector7");
  addHistogramToFile("InternalBackgrounds/","SeNew_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_AllEvents_Sector7");
  addHistogramToFile("InternalBackgrounds/","SeOld_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_AllEvents_Sector7");
  addHistogramToFile("InternalBackgrounds/","Mylar_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_AllEvents_Sector7");
  addHistogramToFile("RadonBackgrounds/",   "SFoil_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_AllEvents_Sector7");
  addHistogramToFile("RadonBackgrounds/",   "SWire_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_AllEvents_Sector7");

  alphaSide = -1;
  electronSide = -1;
  addHistogramToFile("Data/","Data","./Histograms_1e1a.root", alphaSide, electronSide, "_AllEvents_Sector8");
  addHistogramToFile("InternalBackgrounds/","SeNew_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_AllEvents_Sector8");
  addHistogramToFile("InternalBackgrounds/","SeOld_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_AllEvents_Sector8");
  addHistogramToFile("InternalBackgrounds/","Mylar_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_AllEvents_Sector8");
  addHistogramToFile("RadonBackgrounds/",   "SFoil_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_AllEvents_Sector8");
  addHistogramToFile("RadonBackgrounds/",   "SWire_Bi214", "./Histograms_1e1a.root", alphaSide, electronSide, "_AllEvents_Sector8");

  return 0;
}


void addHistogramToFile(string directory, string sample, string outfilename, int reqdAlphaSide, int reqdElectronSide, string suffix){

  cout << "Adding histograms for " << sample << "..." << endl; 

  // If it's got SFoil in sample name, then add it as inner and outer contributions
  if(std::string::npos != sample.find("SFoil") ){
    addHistogramToFileInOut(directory, sample, outfilename, reqdAlphaSide, reqdElectronSide, suffix);
    return;
  }

  // Want to fit alpha length for both P1 and P2
  TH1D* hAlphaLength_P1 = new TH1D("hAlphaLength_P1","Alpha Length", 55, 0, 55);
  hAlphaLength_P1->Sumw2();
  hAlphaLength_P1->SetTitle(";Alpha Length / cm; No. Events / cm");

  TH1D* hAlphaLength_P2 = new TH1D("hAlphaLength_P2","Alpha Length", 55, 0, 55);
  hAlphaLength_P2->Sumw2();
  hAlphaLength_P2->SetTitle(";Alpha Length / cm; No. Events / cm");

  // Write out input file name
  string inputfile = "/unix/nemo3/users/jmott/SeleniumAnalysis/ProcessedData/Backgrounds/1e1a/";
  inputfile.append(directory);
  inputfile.append(sample);
  inputfile.append("/IntBG_Se_1e1a_output.root");

  // Open file and get hold of branches and assign them to relevant names
  TFile* f = new TFile(inputfile.c_str(),"READ");
  TDirectoryFile* f1 = (TDirectoryFile*)f->Get("Se1e1aCuts");
  TTree* tree = (TTree*)f1->Get("Se1e1aCuts");

  double alphaLength, radonWeight, vertexSector;
  int alphaNHits, alphaSide, electronSide, foilSide, run, scintLocation;
  tree->SetBranchAddress("b_run", &run);
  tree->SetBranchAddress("b_alphaNHits", &alphaNHits);
  tree->SetBranchAddress("b_alphaLength", &alphaLength);
  tree->SetBranchAddress("b_alphaSide", &alphaSide);
  tree->SetBranchAddress("b_electronSide", &electronSide);
  tree->SetBranchAddress("b_foilSide", &foilSide);
  tree->SetBranchAddress("b_radonWeight", &radonWeight);
  tree->SetBranchAddress("b_vertexSector", &vertexSector);
  tree->SetBranchAddress("b_scintLocation", &scintLocation);

  int N = tree->GetEntries();
  cout << "Entries = " << N << endl;

  // FILL HISTOGRAMS
  for (int iEvt = 0; iEvt < N; iEvt ++){

    if(iEvt % 500000 == 0){cout << "Processing event " << iEvt << "..." << endl;}

    tree->GetEntry(iEvt);

    double radWeight = 1;
    if(std::string::npos != sample.find("SWire")){radWeight = radonWeight;}

    bool fill = true;

    if(std::string::npos != suffix.find("Sector6")){
      if(vertexSector >= 7){fill = false;}
    }
    if(std::string::npos != suffix.find("Sector7")){
      if(vertexSector < 7 || vertexSector >= 8){fill = false;}
    }
    if(std::string::npos != suffix.find("Sector8")){
      if(vertexSector < 8){fill = false;}
    }

    if (reqdAlphaSide >= 0 && reqdElectronSide >= 0){
      if(alphaSide != reqdAlphaSide){fill = false;}
      if(electronSide != reqdElectronSide){fill = false;}
    }

    if(fill && run < 3396){
      hAlphaLength_P1->Fill(alphaLength,radWeight);
    }
    if(fill && run >= 3396){
      hAlphaLength_P2->Fill(alphaLength,radWeight);
    }

  }

  f->Close("R");
  delete f;
  

  TFile* outfile = new TFile(outfilename.c_str(),"UPDATE");
  char histname[200];

  string sample_P1 = sample + std::string("_P1");
  strcpy(histname,"hAlphaLength_");
  TH1D* hAlphaLength_P1Clone   = (TH1D*)hAlphaLength_P1->Clone(strcat(histname,(sample_P1+suffix).c_str()));
  hAlphaLength_P1Clone->Write();

  string sample_P2 = sample + std::string("_P2");
  strcpy(histname,"hAlphaLength_");
  TH1D* hAlphaLength_P2Clone   = (TH1D*)hAlphaLength_P2->Clone(strcat(histname,(sample_P2+suffix).c_str()));
  hAlphaLength_P2Clone->Write();

  outfile->Close();
  delete outfile;

  delete hAlphaLength_P1;
  delete hAlphaLength_P2;

}

void addHistogramToFileInOut(string directory, string sample, string outfilename, int reqdAlphaSide, int reqdElectronSide, string suffix){

  // Want to fit alpha length
  TH1D* hAlphaLength_P1_In         = new TH1D("hAlphaLength_P1_In","Alpha Length", 55, 0, 55);
  hAlphaLength_P1_In->Sumw2();
  hAlphaLength_P1_In->SetTitle(";Alpha Length / cm; No. Events / cm");

  TH1D* hAlphaLength_P1_Out         = new TH1D("hAlphaLength_P1_Out","Alpha Length", 55, 0, 55);
  hAlphaLength_P1_Out->Sumw2();
  hAlphaLength_P1_Out->SetTitle(";Alpha Length / cm; No. Events / cm");

  TH1D* hAlphaLength_P2_In         = new TH1D("hAlphaLength_P2_In","Alpha Length", 55, 0, 55);
  hAlphaLength_P2_In->Sumw2();
  hAlphaLength_P2_In->SetTitle(";Alpha Length / cm; No. Events / cm");

  TH1D* hAlphaLength_P2_Out         = new TH1D("hAlphaLength_P2_Out","Alpha Length", 55, 0, 55);
  hAlphaLength_P2_Out->Sumw2();
  hAlphaLength_P2_Out->SetTitle(";Alpha Length / cm; No. Events / cm");

  // Write out input file name
  string inputfile = "/unix/nemo3/users/jmott/SeleniumAnalysis/ProcessedData/Backgrounds/1e1a/";
  inputfile.append(directory);
  inputfile.append(sample);
  inputfile.append("/IntBG_Se_1e1a_output.root");
    
  // Open file and get hold of branches and assign them to relevant names
  TFile* f = new TFile(inputfile.c_str(),"READ");
  TDirectoryFile* f1 = (TDirectoryFile*)f->Get("Se1e1aCuts");
  TTree* tree = (TTree*)f1->Get("Se1e1aCuts");

  int alphaNHits, alphaSide, electronSide, foilSide, run, scintLocation;
  double alphaLength, vertexSector;
  tree->SetBranchAddress("b_run", &run);
  tree->SetBranchAddress("b_alphaNHits", &alphaNHits);
  tree->SetBranchAddress("b_alphaLength", &alphaLength);
  tree->SetBranchAddress("b_alphaSide", &alphaSide);
  tree->SetBranchAddress("b_electronSide", &electronSide);
  tree->SetBranchAddress("b_foilSide", &foilSide);
  tree->SetBranchAddress("b_vertexSector", &vertexSector);
  tree->SetBranchAddress("b_scintLocation", &scintLocation);

  int N = tree->GetEntries();
  cout << "Entries = " << N << endl;

  // FILL HISTOGRAMS
  for (int iEvt = 0; iEvt < N; iEvt ++){

    if(iEvt % 500000 == 0){cout << "Processing event " << iEvt << "..." << endl;}

    tree->GetEntry(iEvt);

    bool fill = true;

    if(std::string::npos != suffix.find("Sector6")){
      if(vertexSector >= 7){fill = false;}
    }
    if(std::string::npos != suffix.find("Sector7")){
      if(vertexSector < 7 || vertexSector >= 8){fill = false;}
    }
    if(std::string::npos != suffix.find("Sector8")){
      if(vertexSector < 8){fill = false;}
    }

    if(reqdAlphaSide >= 0 && reqdElectronSide >= 0){
      if(alphaSide != reqdAlphaSide){fill = false;}
      if(electronSide != reqdElectronSide){fill = false;}
    }

    if(fill && run < 3396){
      if(foilSide == 0){hAlphaLength_P1_In->Fill(alphaLength);}
      else{hAlphaLength_P1_Out->Fill(alphaLength);}
    }

    if(fill && run >= 3396){
      if(foilSide == 0){hAlphaLength_P2_In->Fill(alphaLength);}
      else{hAlphaLength_P2_Out->Fill(alphaLength);}
    }

  }

  f->Close("R");
  delete f;

  TFile* outfile = new TFile(outfilename.c_str(),"UPDATE");
  char histname[200];

  string sample_P1_In = sample + std::string("_P1_In");
  strcpy(histname,"hAlphaLength_");
  TH1D* hAlphaLength_P1_InClone = (TH1D*)hAlphaLength_P1_In->Clone(strcat(histname,(sample_P1_In+suffix).c_str()));
  hAlphaLength_P1_InClone->Write();

  string sample_P1_Out = sample + std::string("_P1_Out");
  strcpy(histname,"hAlphaLength_");
  TH1D* hAlphaLength_P1_OutClone = (TH1D*)hAlphaLength_P1_Out->Clone(strcat(histname,(sample_P1_Out+suffix).c_str()));
  hAlphaLength_P1_OutClone->Write();

  string sample_P2In = sample + std::string("_P2_In");
  strcpy(histname,"hAlphaLength_");
  TH1D* hAlphaLength_P2_InClone = (TH1D*)hAlphaLength_P2_In->Clone(strcat(histname,(sample_P2In+suffix).c_str()));
  hAlphaLength_P2_InClone->Write();

  string sample_P2Out = sample + std::string("_P2_Out");
  strcpy(histname,"hAlphaLength_");
  TH1D* hAlphaLength_P2_OutClone = (TH1D*)hAlphaLength_P2_Out->Clone(strcat(histname,(sample_P2Out+suffix).c_str()));
  hAlphaLength_P2_OutClone->Write();

  outfile->Close();
  delete outfile;

  delete hAlphaLength_P1_In;
  delete hAlphaLength_P1_Out;
  delete hAlphaLength_P2_In;
  delete hAlphaLength_P2_Out;

}
