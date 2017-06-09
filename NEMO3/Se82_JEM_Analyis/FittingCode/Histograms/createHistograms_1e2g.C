#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TTree.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TMath.h>
#include <iostream>
#include <TGaxis.h>
#include <TRandom3.h>

using namespace std;

void addHistogramToFile(string directory, string sample, string outfilename, string suffix);
void addHistogramToFileP1P2(string directory, string sample, string outfilename, string suffix);
void addHistogramToFileInOutP1P2(string directory, string sample, string outfilename, string suffix);

Int_t createHistograms_1e2g(){
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
  TFile* outfile = new TFile("./Histograms_1e2g.root","RECREATE");
  outfile->Close();
  delete outfile;

  // SeNew Histograms
  addHistogramToFile("Data/"               ,"Data"            , "./Histograms_1e2g.root", "_SeNew");
  addHistogramToFile("Data/"               ,"Data_Neutrons"   , "./Histograms_1e2g.root", "_SeNew");
  addHistogramToFile("InternalBackgrounds/","SeNew_Bi214"     , "./Histograms_1e2g.root", "_SeNew");
  addHistogramToFile("InternalBackgrounds/","SeOld_Bi214"     , "./Histograms_1e2g.root", "_SeNew");
  addHistogramToFile("InternalBackgrounds/","SeNew_Tl208"     , "./Histograms_1e2g.root", "_SeNew");
  addHistogramToFile("InternalBackgrounds/","SeOld_Tl208"     , "./Histograms_1e2g.root", "_SeNew");
  addHistogramToFile("InternalBackgrounds/","Mylar_Bi214"     , "./Histograms_1e2g.root", "_SeNew");
  addHistogramToFile("ExternalBackgrounds/","PMT_Tl208"       , "./Histograms_1e2g.root", "_SeNew");
  addHistogramToFile("ExternalBackgrounds/","SteelFrame_Tl208", "./Histograms_1e2g.root", "_SeNew");
  addHistogramToFile("RadonBackgrounds/"   ,"SFoil_Bi214"     , "./Histograms_1e2g.root", "_SeNew");
  addHistogramToFile("RadonBackgrounds/"   ,"SWire_Bi214"     , "./Histograms_1e2g.root", "_SeNew");
  addHistogramToFile("RadonBackgrounds/"   ,"SWire_Tl208"     , "./Histograms_1e2g.root", "_SeNew");
  addHistogramToFile("RadonBackgrounds/"   ,"Air_Tl208"       , "./Histograms_1e2g.root", "_SeNew");
  addHistogramToFile("RadonBackgrounds/"   ,"Air_Bi214"       , "./Histograms_1e2g.root", "_SeNew");

  // SeOld Histograms
  addHistogramToFile("Data/"               ,"Data"            , "./Histograms_1e2g.root", "_SeOld");
  addHistogramToFile("Data/"               ,"Data_Neutrons"   , "./Histograms_1e2g.root", "_SeOld");
  addHistogramToFile("InternalBackgrounds/","SeNew_Bi214"     , "./Histograms_1e2g.root", "_SeOld");
  addHistogramToFile("InternalBackgrounds/","SeOld_Bi214"     , "./Histograms_1e2g.root", "_SeOld");
  addHistogramToFile("InternalBackgrounds/","SeNew_Tl208"     , "./Histograms_1e2g.root", "_SeOld");
  addHistogramToFile("InternalBackgrounds/","SeOld_Tl208"     , "./Histograms_1e2g.root", "_SeOld");
  addHistogramToFile("InternalBackgrounds/","Mylar_Bi214"     , "./Histograms_1e2g.root", "_SeOld");
  addHistogramToFile("ExternalBackgrounds/","PMT_Tl208"       , "./Histograms_1e2g.root", "_SeOld");
  addHistogramToFile("ExternalBackgrounds/","SteelFrame_Tl208", "./Histograms_1e2g.root", "_SeOld");
  addHistogramToFile("RadonBackgrounds/"   ,"SFoil_Bi214"     , "./Histograms_1e2g.root", "_SeOld");
  addHistogramToFile("RadonBackgrounds/"   ,"SWire_Bi214"     , "./Histograms_1e2g.root", "_SeOld");
  addHistogramToFile("RadonBackgrounds/"   ,"SWire_Tl208"     , "./Histograms_1e2g.root", "_SeOld");
  addHistogramToFile("RadonBackgrounds/"   ,"Air_Bi214"       , "./Histograms_1e2g.root", "_SeOld");
  addHistogramToFile("RadonBackgrounds/"   ,"Air_Tl208"       , "./Histograms_1e2g.root", "_SeOld");

  return 0;
}


void addHistogramToFile(string directory, string sample, string outfilename, string suffix){

  cout << "Adding histograms for " << sample << "..." << endl; 

  // If it's got SWire, SFoil or Neutrons in the sample name, then break it up into P1 and P2 contributions
  if(std::string::npos != sample.find("SWire") || std::string::npos != sample.find("SFoil") || std::string::npos != sample.find("Neutrons") ){
    addHistogramToFileP1P2(directory, sample, outfilename, suffix);
    return;
  }

  // Create histograms
  TH1D* hRun             = new TH1D("hRun","Run Number", 42, 1100,9500);
  TH1D* hElectronEnergy  = new TH1D("hElectronEnergy","Electron Energy", 30, 0, 3);
  TH1D* hGammaEnergyMin  = new TH1D("hGammaEnergyMin","Gamma Min Energy", 30, 0.0, 3);
  TH1D* hGammaEnergyMax  = new TH1D("hGammaEnergyMax","Gamma Max Energy", 30, 1.0, 4);
  TH1D* hElectronGammaSum= new TH1D("hElectronGammaSum","Electron + Gamma Energy", 30, 2.0, 5);
  TH1D* hLowGammaEnergy  = new TH1D("hLowGammaEnergy","Low Energy Gamma Total", 20, 0.0, 1);
  TH1D* hNLowEGammas     = new TH1D("hNLowEGammas","Number of Low Energy Gammas", 10, -0.5, 9.5);
  TH1D* hTotalEnergy     = new TH1D("hTotalEnergy","Total Event Energy", 30, 2.0, 5);
  TH1D* hTrackLength     = new TH1D("hTrackLength","Individual Track Lengths", 50, 0, 200);
  TH1D* hVertexSector    = new TH1D("hVertexSector","Reconstructed vertex position", 36, 5.8, 8.7);
  TH1D* hVertexZ         = new TH1D("hVertexZ","Reconstructed vertex position", 16,-160, 160);
  TH1D* hProbInt         = new TH1D("hProbInt","Internal Probability", 25, 0.0, 1.0);
  TH1D* hCosThetaEGMin   = new TH1D("hCosThetaEGMin","Cosine Angle Electron Gamma Min", 12, 0.0, 1.0);
  TH1D* hCosThetaEGMax   = new TH1D("hCosThetaEGMax","Cosine Angle Electron Gamma Max", 12, 0.0, 1.0);
  TH1D* hCosThetaGG      = new TH1D("hCosThetaGG","Cosine Angle Gamma Gamma", 12, 0.0, 1.0);

  hRun->Sumw2();              
  hElectronEnergy->Sumw2();   
  hGammaEnergyMin->Sumw2();   
  hGammaEnergyMax->Sumw2();   
  hElectronGammaSum->Sumw2(); 
  hLowGammaEnergy->Sumw2();   
  hNLowEGammas->Sumw2();      
  hTotalEnergy->Sumw2();      
  hTrackLength->Sumw2();      
  hVertexSector->Sumw2();     
  hVertexZ->Sumw2();          
  hProbInt->Sumw2();          
  hCosThetaEGMin->Sumw2();   
  hCosThetaEGMax->Sumw2();    
  hCosThetaGG->Sumw2();       

  hRun->SetTitle(";Run Number; No. Events");              
  hElectronEnergy->SetTitle(";E_{e} / MeV; No. Events / 0.1 MeV");   
  hGammaEnergyMin->SetTitle(";Min E_{#gamma} / MeV; No. Events / 0.1 MeV");   
  hGammaEnergyMax->SetTitle(";Max E_{#gamma} / MeV; No. Events / 0.1 MeV");   
  hElectronGammaSum->SetTitle(";E_{e} + Min E_{#gamma} + Max E_{#gamma} / MeV; No. Events / 0.1 MeV");   
  hLowGammaEnergy->SetTitle(";#SigmaE_{#gamma} (E_{#gamma} < 150keV) / MeV; No. Events / 0.05 MeV");   
  hNLowEGammas->SetTitle(";Unassociated Calo Hits (E_{#gamma} < 150keV); No. Events");      
  hTotalEnergy->SetTitle(";Total Event Energy / MeV; No. Events / 0.1 MeV");
  hTrackLength->SetTitle(";Track Length / cm; No. Tracks / 4.0 cm");
  hVertexSector->SetTitle(";Sector Number; No. Events");
  hVertexZ->SetTitle(";Z / cm; No. Events / 20.0 cm");       
  hProbInt->SetTitle(";Internal Probability; No. Events");
  hCosThetaEGMin->SetTitle(";Cos(#theta) e-#gamma_{Min}; No. Events");  
  hCosThetaEGMax->SetTitle(";Cos(#theta) e-#gamma_{Max}; No. Events");  
  hCosThetaGG->SetTitle(";Cos(#theta) #gamma-#gamma; No. Events");  

  // Write out input file name
  string inputfile="/unix/nemo3/users/jmott/SeleniumAnalysis/ProcessedData/Backgrounds/1e2g/";
  inputfile.append(directory);
  inputfile.append(sample);
  inputfile.append("/IntBG_Se_1e2g_output.root");

  // Open file and get hold of branches and assign them to relevant names
  TFile* f = new TFile(inputfile.c_str(),"READ");
  TDirectoryFile* f1 = (TDirectoryFile*)f->Get("Se1e2gCuts");
  TTree* tree = (TTree*)f1->Get("Se1e2gCuts");

  int run, nLowEGammas, foilSide, vertexLocation, scintLocation;
  double electronEnergy, gammaEnergyMin, gammaEnergyMax, trackLength, vertexR, vertexZ, vertexSector, radonWeight, bi210Weight, gammaLowEnergy[10], probIntMin, probExtMin, probIntMax, probExtMax, cosThetaEGMin, cosThetaEGMax, cosThetaGG, trackSign;

  tree->SetBranchAddress("b_run", &run);
  tree->SetBranchAddress("b_electronEnergy", &electronEnergy);
  tree->SetBranchAddress("b_gammaEnergyMin", &gammaEnergyMin);
  tree->SetBranchAddress("b_gammaEnergyMax", &gammaEnergyMax);
  tree->SetBranchAddress("b_trackLength", &trackLength);
  tree->SetBranchAddress("b_trackSign", &trackSign);
  tree->SetBranchAddress("b_vertexR", &vertexR);
  tree->SetBranchAddress("b_vertexZ", &vertexZ);
  tree->SetBranchAddress("b_vertexSector", &vertexSector);
  tree->SetBranchAddress("b_vertexLocation", &vertexLocation);
  tree->SetBranchAddress("b_scintLocation", &scintLocation);
  tree->SetBranchAddress("b_radonWeight", &radonWeight);
  tree->SetBranchAddress("b_bi210Weight", &bi210Weight);
  tree->SetBranchAddress("b_foilSide", &foilSide);
  tree->SetBranchAddress("b_nLowEGammas", &nLowEGammas);
  tree->SetBranchAddress("b_gammaLowEnergy", &gammaLowEnergy);
  tree->SetBranchAddress("b_probIntMin", &probIntMin);
  tree->SetBranchAddress("b_probExtMin", &probExtMin);
  tree->SetBranchAddress("b_probIntMax", &probIntMax);
  tree->SetBranchAddress("b_probExtMax", &probExtMax);
  tree->SetBranchAddress("b_cosThetaEGMin", &cosThetaEGMin);
  tree->SetBranchAddress("b_cosThetaEGMax", &cosThetaEGMax);
  tree->SetBranchAddress("b_cosThetaGG", &cosThetaGG);
 
  Int_t N = tree->GetEntries();
  cout << "Entries = " << N << endl;

  // FILL HISTOGRAMS
  for (int iEvt = 0; iEvt < N; iEvt ++){

    if(iEvt % 500000 == 0){cout << "Processing event " << iEvt << "..." << endl;}

    tree->GetEntry(iEvt);

    double radWeight = 1;

    bool fill = true;

    if(std::string::npos != suffix.find("SeOld") && !(vertexLocation == 0)){fill = false;}
    if(std::string::npos != suffix.find("SeNew") && !(vertexLocation == 1 || vertexLocation == 2)){fill = false;}

    if(fill){

      hRun->Fill(run,radWeight);

      hElectronEnergy->Fill(electronEnergy,radWeight);
      hGammaEnergyMin->Fill(gammaEnergyMin,radWeight);
      hGammaEnergyMax->Fill(gammaEnergyMax,radWeight);
      hElectronGammaSum->Fill(electronEnergy+gammaEnergyMin+gammaEnergyMax,radWeight);
      hNLowEGammas->Fill(nLowEGammas, radWeight);
      double totLowGammaE = 0;
      for (int i = 0; i < 10; i++){totLowGammaE += gammaLowEnergy[i];}
      if (totLowGammaE > 0){hLowGammaEnergy->Fill(totLowGammaE,radWeight);}
      hTotalEnergy->Fill(electronEnergy+gammaEnergyMin+gammaEnergyMax+totLowGammaE,radWeight);

      hTrackLength->Fill(trackLength,radWeight);
      hVertexSector->Fill(vertexSector,radWeight);
      hVertexZ->Fill(vertexZ,radWeight);

      hProbInt->Fill(probIntMin,radWeight);
      hProbInt->Fill(probIntMax,radWeight);

      hCosThetaEGMin->Fill(cosThetaEGMin,radWeight);
      hCosThetaEGMax->Fill(cosThetaEGMax,radWeight);
      hCosThetaGG->Fill(cosThetaGG,radWeight);
    }
  }


  TFile* outfile = new TFile(outfilename.c_str(),"UPDATE");
  char histname[200];

  strcpy(histname,"hRun_");
  TH1D *hRunClone = (TH1D*)hRun->Clone(strcat(histname,(sample+suffix).c_str()));
  hRunClone->Write();
  strcpy(histname,"hElectronEnergy_");
  TH1D *hElectronEnergyClone = (TH1D*)hElectronEnergy->Clone(strcat(histname,(sample+suffix).c_str()));
  hElectronEnergyClone->Write();
  strcpy(histname,"hGammaEnergyMin_");
  TH1D *hGammaEnergyMinClone = (TH1D*)hGammaEnergyMin->Clone(strcat(histname,(sample+suffix).c_str()));
  hGammaEnergyMinClone->Write();
  strcpy(histname,"hGammaEnergyMax_");
  TH1D *hGammaEnergyMaxClone = (TH1D*)hGammaEnergyMax->Clone(strcat(histname,(sample+suffix).c_str()));
  hGammaEnergyMaxClone->Write();
  strcpy(histname,"hElectronGammaSum_");
  TH1D *hElectronGammaSumClone = (TH1D*)hElectronGammaSum->Clone(strcat(histname,(sample+suffix).c_str()));
  hElectronGammaSumClone->Write();
  strcpy(histname,"hLowGammaEnergy_");
  TH1D *hLowGammaEnergyClone = (TH1D*)hLowGammaEnergy->Clone(strcat(histname,(sample+suffix).c_str()));
  hLowGammaEnergyClone->Write();
  strcpy(histname,"hTotalEnergy_");
  TH1D *hTotalEnergyClone = (TH1D*)hTotalEnergy->Clone(strcat(histname,(sample+suffix).c_str()));
  hTotalEnergyClone->Write();
  strcpy(histname,"hNLowEGammas_");
  TH1D *hNLowEGammasClone = (TH1D*)hNLowEGammas->Clone(strcat(histname,(sample+suffix).c_str()));
  hNLowEGammasClone->Write();
  strcpy(histname,"hTrackLength_");
  TH1D *hTrackLengthClone = (TH1D*)hTrackLength->Clone(strcat(histname,(sample+suffix).c_str()));
  hTrackLengthClone->Write();
  strcpy(histname,"hVertexSector_");
  TH1D *hVertexSectorClone = (TH1D*)hVertexSector->Clone(strcat(histname,(sample+suffix).c_str()));
  hVertexSectorClone->Write();
  strcpy(histname,"hVertexZ_");
  TH1D *hVertexZClone = (TH1D*)hVertexZ->Clone(strcat(histname,(sample+suffix).c_str()));
  hVertexZClone->Write();
  strcpy(histname,"hProbInt_");
  TH1D *hProbIntClone = (TH1D*)hProbInt->Clone(strcat(histname,(sample+suffix).c_str()));
  hProbIntClone->Write();
  strcpy(histname,"hCosThetaEGMin_");
  TH1D *hCosThetaEGMinClone = (TH1D*)hCosThetaEGMin->Clone(strcat(histname,(sample+suffix).c_str()));
  hCosThetaEGMinClone->Write();
  strcpy(histname,"hCosThetaEGMax_");
  TH1D *hCosThetaEGMaxClone = (TH1D*)hCosThetaEGMax->Clone(strcat(histname,(sample+suffix).c_str()));
  hCosThetaEGMaxClone->Write();
  strcpy(histname,"hCosThetaGG_");
  TH1D *hCosThetaGGClone = (TH1D*)hCosThetaGG->Clone(strcat(histname,(sample+suffix).c_str()));
  hCosThetaGGClone->Write();
  outfile->Close();
  delete outfile;

  delete hRun;              
  delete hElectronEnergy;   
  delete hGammaEnergyMin;   
  delete hGammaEnergyMax;   
  delete hElectronGammaSum; 
  delete hLowGammaEnergy;   
  delete hNLowEGammas;      
  delete hTotalEnergy;      
  delete hTrackLength;      
  delete hVertexSector;     
  delete hVertexZ;          
  delete hProbInt;          
  delete hCosThetaEGMin;   
  delete hCosThetaEGMax;    
  delete hCosThetaGG;       

  f->Close("R");
  delete f;

}

void addHistogramToFileP1P2(string directory, string sample, string outfilename, string suffix){

  // If it's got SWire or SFoil in the sample name, then break it up into P1 and P2 contributions
  if(std::string::npos != sample.find("214") && std::string::npos != sample.find("SFoil")){
    addHistogramToFileInOutP1P2(directory, sample, outfilename, suffix);
    return;
  }

  // Create histograms
  TH1D* hRunP1             = new TH1D("hRunP1","Run Number", 42, 1100,9500);
  TH1D* hElectronEnergyP1  = new TH1D("hElectronEnergyP1","Electron Energy", 30, 0, 3);
  TH1D* hGammaEnergyMinP1  = new TH1D("hGammaEnergyMinP1","Gamma Min Energy", 30, 0.0, 3);
  TH1D* hGammaEnergyMaxP1  = new TH1D("hGammaEnergyMaxP1","Gamma Max Energy", 30, 1.0, 4);
  TH1D* hElectronGammaSumP1= new TH1D("hElectronGammaSumP1","Electron + Gamma Energy", 30, 2.0, 5);
  TH1D* hLowGammaEnergyP1  = new TH1D("hLowGammaEnergyP1","Low Energy Gamma Total", 20, 0.0, 1);
  TH1D* hNLowEGammasP1     = new TH1D("hNLowEGammasP1","Number of Low Energy Gammas", 10, -0.5, 9.5);
  TH1D* hTotalEnergyP1     = new TH1D("hTotalEnergyP1","Total Event Energy", 30, 2.0, 5);
  TH1D* hTrackLengthP1     = new TH1D("hTrackLengthP1","Individual Track Lengths", 50, 0, 200);
  TH1D* hVertexSectorP1    = new TH1D("hVertexSectorP1","Reconstructed vertex position", 36, 5.8, 8.7);
  TH1D* hVertexZP1         = new TH1D("hVertexZP1","Reconstructed vertex position", 16,-160, 160);
  TH1D* hProbIntP1         = new TH1D("hProbIntP1","Internal Probability", 25, 0.0, 1.0);
  TH1D* hCosThetaEGMinP1   = new TH1D("hCosThetaEGMinP1","Cosine Angle Electron Gamma Min", 12, 0.0, 1.0);
  TH1D* hCosThetaEGMaxP1   = new TH1D("hCosThetaEGMaxP1","Cosine Angle Electron Gamma Max", 12, 0.0, 1.0);
  TH1D* hCosThetaGGP1      = new TH1D("hCosThetaGGP1","Cosine Angle Gamma Gamma", 12, 0.0, 1.0);

  TH1D* hRunP2             = new TH1D("hRunP2","Run Number", 42, 1100,9500);
  TH1D* hElectronEnergyP2  = new TH1D("hElectronEnergyP2","Electron Energy", 30, 0, 3);
  TH1D* hGammaEnergyMinP2  = new TH1D("hGammaEnergyMinP2","Gamma Min Energy", 30, 0.0, 3);
  TH1D* hGammaEnergyMaxP2  = new TH1D("hGammaEnergyMaxP2","Gamma Max Energy", 30, 1.0, 4);
  TH1D* hElectronGammaSumP2= new TH1D("hElectronGammaSumP2","Electron + Gamma Energy", 30, 2.0, 5);
  TH1D* hLowGammaEnergyP2  = new TH1D("hLowGammaEnergyP2","Low Energy Gamma Total", 20, 0.0, 1);
  TH1D* hNLowEGammasP2     = new TH1D("hNLowEGammasP2","Number of Low Energy Gammas", 10, -0.5, 9.5);
  TH1D* hTotalEnergyP2     = new TH1D("hTotalEnergyP2","Total Event Energy", 30, 2.0, 5);
  TH1D* hTrackLengthP2     = new TH1D("hTrackLengthP2","Individual Track Lengths", 50, 0, 200);
  TH1D* hVertexSectorP2    = new TH1D("hVertexSectorP2","Reconstructed vertex position", 36, 5.8, 8.7);
  TH1D* hVertexZP2         = new TH1D("hVertexZP2","Reconstructed vertex position", 16,-160, 160);
  TH1D* hProbIntP2         = new TH1D("hProbIntP2","Internal Probability", 25, 0.0, 1.0);
  TH1D* hCosThetaEGMinP2   = new TH1D("hCosThetaEGMinP2","Cosine Angle Electron Gamma Min", 12, 0.0, 1.0);
  TH1D* hCosThetaEGMaxP2   = new TH1D("hCosThetaEGMaxP2","Cosine Angle Electron Gamma Max", 12, 0.0, 1.0);
  TH1D* hCosThetaGGP2      = new TH1D("hCosThetaGGP2","Cosine Angle Gamma Gamma", 12, 0.0, 1.0);

  hRunP1->Sumw2();              
  hElectronEnergyP1->Sumw2();   
  hGammaEnergyMinP1->Sumw2();   
  hGammaEnergyMaxP1->Sumw2();   
  hElectronGammaSumP1->Sumw2(); 
  hLowGammaEnergyP1->Sumw2();   
  hNLowEGammasP1->Sumw2();      
  hTotalEnergyP1->Sumw2();      
  hTrackLengthP1->Sumw2();      
  hVertexSectorP1->Sumw2();     
  hVertexZP1->Sumw2();          
  hProbIntP1->Sumw2();          
  hCosThetaEGMinP1->Sumw2();   
  hCosThetaEGMaxP1->Sumw2();    
  hCosThetaGGP1->Sumw2();       

  hRunP2->Sumw2();              
  hElectronEnergyP2->Sumw2();   
  hGammaEnergyMinP2->Sumw2();   
  hGammaEnergyMaxP2->Sumw2();   
  hElectronGammaSumP2->Sumw2(); 
  hLowGammaEnergyP2->Sumw2();   
  hNLowEGammasP2->Sumw2();      
  hTotalEnergyP2->Sumw2();      
  hTrackLengthP2->Sumw2();      
  hVertexSectorP2->Sumw2();     
  hVertexZP2->Sumw2();          
  hProbIntP2->Sumw2();          
  hCosThetaEGMinP2->Sumw2();   
  hCosThetaEGMaxP2->Sumw2();    
  hCosThetaGGP2->Sumw2();       

  hRunP1->SetTitle(";Run Number; No. Events");              
  hElectronEnergyP1->SetTitle(";E_{e} / MeV; No. Events / 0.1 MeV");   
  hGammaEnergyMinP1->SetTitle(";Min E_{#gamma} / MeV; No. Events / 0.1 MeV");   
  hGammaEnergyMaxP1->SetTitle(";Max E_{#gamma} / MeV; No. Events / 0.1 MeV");   
  hElectronGammaSumP1->SetTitle(";E_{e} + Min E_{#gamma} + Max E_{#gamma} / MeV; No. Events / 0.1 MeV");   
  hLowGammaEnergyP1->SetTitle(";#SigmaE_{#gamma} (E_{#gamma} < 150keV) / MeV; No. Events / 0.05 MeV");   
  hNLowEGammasP1->SetTitle(";Unassociated Calo Hits (E_{#gamma} < 150keV); No. Events");      
  hTotalEnergyP1->SetTitle(";Total Event Energy / MeV; No. Events / 0.1 MeV");
  hTrackLengthP1->SetTitle(";Track Length / cm; No. Tracks / 4.0 cm");
  hVertexSectorP1->SetTitle(";Sector Number; No. Events");
  hVertexZP1->SetTitle(";Z / cm; No. Events / 20.0 cm");       
  hProbIntP1->SetTitle(";Internal Probability; No. Events");
  hCosThetaEGMinP1->SetTitle(";Cos(#theta) e-#gamma_{Min}; No. Events");  
  hCosThetaEGMaxP1->SetTitle(";Cos(#theta) e-#gamma_{Max}; No. Events");  
  hCosThetaGGP1->SetTitle(";Cos(#theta) #gamma-#gamma; No. Events");  

  hRunP2->SetTitle(";Run Number; No. Events");              
  hElectronEnergyP2->SetTitle(";E_{e} / MeV; No. Events / 0.1 MeV");   
  hGammaEnergyMinP2->SetTitle(";Min E_{#gamma} / MeV; No. Events / 0.1 MeV");   
  hGammaEnergyMaxP2->SetTitle(";Max E_{#gamma} / MeV; No. Events / 0.1 MeV");   
  hElectronGammaSumP2->SetTitle(";E_{e} + Min E_{#gamma} + Max E_{#gamma} / MeV; No. Events / 0.1 MeV");   
  hLowGammaEnergyP2->SetTitle(";#SigmaE_{#gamma} (E_{#gamma} < 150keV) / MeV; No. Events / 0.05 MeV");   
  hNLowEGammasP2->SetTitle(";Unassociated Calo Hits (E_{#gamma} < 150keV); No. Events");      
  hTotalEnergyP2->SetTitle(";Total Event Energy / MeV; No. Events / 0.1 MeV");
  hTrackLengthP2->SetTitle(";Track Length / cm; No. Tracks / 4.0 cm");
  hVertexSectorP2->SetTitle(";Sector Number; No. Events");
  hVertexZP2->SetTitle(";Z / cm; No. Events / 20.0 cm");       
  hProbIntP2->SetTitle(";Internal Probability; No. Events");
  hCosThetaEGMinP2->SetTitle(";Cos(#theta) e-#gamma_{Min}; No. Events");  
  hCosThetaEGMaxP2->SetTitle(";Cos(#theta) e-#gamma_{Max}; No. Events");  
  hCosThetaGGP2->SetTitle(";Cos(#theta) #gamma-#gamma; No. Events");  

  // Write out input file name
  string inputfile="/unix/nemo3/users/jmott/SeleniumAnalysis/ProcessedData/Backgrounds/1e2g/";
  inputfile.append(directory);
  inputfile.append(sample);
  inputfile.append("/IntBG_Se_1e2g_output.root");

  // Open file and get hold of branches and assign them to relevant names
  TFile* f = new TFile(inputfile.c_str(),"READ");
  TDirectoryFile* f1 = (TDirectoryFile*)f->Get("Se1e2gCuts");
  TTree* tree = (TTree*)f1->Get("Se1e2gCuts");

  int run, nLowEGammas, foilSide, vertexLocation, scintLocation;
  double electronEnergy, gammaEnergyMin, gammaEnergyMax, trackLength, vertexR, vertexZ, vertexSector, radonWeight, bi210Weight, gammaLowEnergy[10], probIntMin, probExtMin, probIntMax, probExtMax, cosThetaEGMin, cosThetaEGMax, cosThetaGG, trackSign;

  tree->SetBranchAddress("b_run", &run);
  tree->SetBranchAddress("b_electronEnergy", &electronEnergy);
  tree->SetBranchAddress("b_gammaEnergyMin", &gammaEnergyMin);
  tree->SetBranchAddress("b_gammaEnergyMax", &gammaEnergyMax);
  tree->SetBranchAddress("b_trackLength", &trackLength);
  tree->SetBranchAddress("b_trackSign", &trackSign);
  tree->SetBranchAddress("b_vertexR", &vertexR);
  tree->SetBranchAddress("b_vertexZ", &vertexZ);
  tree->SetBranchAddress("b_vertexSector", &vertexSector);
  tree->SetBranchAddress("b_vertexLocation", &vertexLocation);
  tree->SetBranchAddress("b_scintLocation", &scintLocation);
  tree->SetBranchAddress("b_radonWeight", &radonWeight);
  tree->SetBranchAddress("b_bi210Weight", &bi210Weight);
  tree->SetBranchAddress("b_foilSide", &foilSide);
  tree->SetBranchAddress("b_nLowEGammas", &nLowEGammas);
  tree->SetBranchAddress("b_gammaLowEnergy", &gammaLowEnergy);
  tree->SetBranchAddress("b_probIntMin", &probIntMin);
  tree->SetBranchAddress("b_probExtMin", &probExtMin);
  tree->SetBranchAddress("b_probIntMax", &probIntMax);
  tree->SetBranchAddress("b_probExtMax", &probExtMax);
  tree->SetBranchAddress("b_cosThetaEGMin", &cosThetaEGMin);
  tree->SetBranchAddress("b_cosThetaEGMax", &cosThetaEGMax);
  tree->SetBranchAddress("b_cosThetaGG", &cosThetaGG);
 
  Int_t N = tree->GetEntries();
  cout << "Entries = " << N << endl;

  // RNG and fractions for Neutrons
  TRandom3 rand(12345);
  double totArea = 1200*(2*63+5*65+2*63+5*65+65)+814*63+1586*63;
  double SeOldFrac = (1200.*(2*63+5*65+65)+1586*63)/totArea;
  double SeNewFrac = (1200.*(2*63+5*65))/totArea;
  double StripFrac = (814.*63)/totArea;
  double P1Frac = 33859178./167629292.;

  // FILL HISTOGRAMS
  for (int iEvt = 0; iEvt < N; iEvt ++){

    if(iEvt % 500000 == 0){cout << "Processing event " << iEvt << "..." << endl;}

    tree->GetEntry(iEvt);

    double radWeight = 1;
    if(std::string::npos != sample.find("SWire") && std::string::npos != sample.find("214") ){
      radWeight = radonWeight;
    } else {
      radWeight = 1;
    }

    bool fill = true;

    // Randomly assign neutrons sample and override vertex location and run
    if(std::string::npos != sample.find("Neutrons")){
      double randNum = rand.Uniform();
      if(randNum < SeOldFrac*P1Frac){
	vertexLocation = 0;
	run = 1;
      }	else if (randNum < SeOldFrac){
	vertexLocation = 0;
	run = 9499;
      } else if (randNum < (SeOldFrac + SeNewFrac*P1Frac)){
	vertexLocation = 1;
	run = 1;
      } else if (randNum < (SeOldFrac + SeNewFrac)){
	vertexLocation = 1;
	run = 9499;
      } else if (randNum < (SeOldFrac + SeNewFrac + StripFrac*P1Frac)){
	vertexLocation = 2;
	run = 1;
      } else {
	vertexLocation = 2;
	run = 9499;
      }
    }

    if(std::string::npos != suffix.find("SeOld") && !(vertexLocation == 0)){fill = false;}
    if(std::string::npos != suffix.find("SeNew") && !(vertexLocation == 1 || vertexLocation == 2)){fill = false;}

    if(fill){
      if (run < 3396){
	hRunP1->Fill(run,radWeight);

	hElectronEnergyP1->Fill(electronEnergy,radWeight);
	hGammaEnergyMinP1->Fill(gammaEnergyMin,radWeight);
	hGammaEnergyMaxP1->Fill(gammaEnergyMax,radWeight);
	hElectronGammaSumP1->Fill(electronEnergy+gammaEnergyMin+gammaEnergyMax,radWeight);
	hNLowEGammasP1->Fill(nLowEGammas, radWeight);
	double totLowGammaE = 0;
	for (int i = 0; i < 10; i++){totLowGammaE += gammaLowEnergy[i];}
	if (totLowGammaE > 0){hLowGammaEnergyP1->Fill(totLowGammaE,radWeight);}
	hTotalEnergyP1->Fill(electronEnergy+gammaEnergyMin+gammaEnergyMax+totLowGammaE,radWeight);

	hTrackLengthP1->Fill(trackLength,radWeight);
	hVertexSectorP1->Fill(vertexSector,radWeight);
	hVertexZP1->Fill(vertexZ,radWeight);

	hProbIntP1->Fill(probIntMin,radWeight);
	hProbIntP1->Fill(probIntMax,radWeight);

	hCosThetaEGMinP1->Fill(cosThetaEGMin,radWeight);
	hCosThetaEGMaxP1->Fill(cosThetaEGMax,radWeight);
	hCosThetaGGP1->Fill(cosThetaGG,radWeight);

      } else if(run >= 3396){
 
	hRunP2->Fill(run,radWeight);

	hElectronEnergyP2->Fill(electronEnergy,radWeight);
	hGammaEnergyMinP2->Fill(gammaEnergyMin,radWeight);
	hGammaEnergyMaxP2->Fill(gammaEnergyMax,radWeight);
	hElectronGammaSumP2->Fill(electronEnergy+gammaEnergyMin+gammaEnergyMax,radWeight);
	hNLowEGammasP2->Fill(nLowEGammas, radWeight);
	double totLowGammaE = 0;
	for (int i = 0; i < 10; i++){totLowGammaE += gammaLowEnergy[i];}
	if (totLowGammaE > 0){hLowGammaEnergyP2->Fill(totLowGammaE,radWeight);}
	hTotalEnergyP2->Fill(electronEnergy+gammaEnergyMin+gammaEnergyMax+totLowGammaE,radWeight);

	hTrackLengthP2->Fill(trackLength,radWeight);
	hVertexSectorP2->Fill(vertexSector,radWeight);
	hVertexZP2->Fill(vertexZ,radWeight);

	hProbIntP2->Fill(probIntMin,radWeight);
	hProbIntP2->Fill(probIntMax,radWeight);

	hCosThetaEGMinP2->Fill(cosThetaEGMin,radWeight);
	hCosThetaEGMaxP2->Fill(cosThetaEGMax,radWeight);
	hCosThetaGGP2->Fill(cosThetaGG,radWeight);
      }
    }
  }

  TFile* outfile = new TFile(outfilename.c_str(),"UPDATE");
  char histname[200];

  string sampleP1 = sample + std::string("_P1");
  strcpy(histname,"hRun_");
  TH1D *hRunP1Clone = (TH1D*)hRunP1->Clone(strcat(histname,(sampleP1+suffix).c_str()));
  hRunP1Clone->Write();
  strcpy(histname,"hElectronEnergy_");
  TH1D *hElectronEnergyP1Clone = (TH1D*)hElectronEnergyP1->Clone(strcat(histname,(sampleP1+suffix).c_str()));
  hElectronEnergyP1Clone->Write();
  strcpy(histname,"hGammaEnergyMin_");
  TH1D *hGammaEnergyMinP1Clone = (TH1D*)hGammaEnergyMinP1->Clone(strcat(histname,(sampleP1+suffix).c_str()));
  hGammaEnergyMinP1Clone->Write();
  strcpy(histname,"hGammaEnergyMax_");
  TH1D *hGammaEnergyMaxP1Clone = (TH1D*)hGammaEnergyMaxP1->Clone(strcat(histname,(sampleP1+suffix).c_str()));
  hGammaEnergyMaxP1Clone->Write();
  strcpy(histname,"hElectronGammaSum_");
  TH1D *hElectronGammaSumP1Clone = (TH1D*)hElectronGammaSumP1->Clone(strcat(histname,(sampleP1+suffix).c_str()));
  hElectronGammaSumP1Clone->Write();
  strcpy(histname,"hLowGammaEnergy_");
  TH1D *hLowGammaEnergyP1Clone = (TH1D*)hLowGammaEnergyP1->Clone(strcat(histname,(sampleP1+suffix).c_str()));
  hLowGammaEnergyP1Clone->Write();
  strcpy(histname,"hTotalEnergy_");
  TH1D *hTotalEnergyP1Clone = (TH1D*)hTotalEnergyP1->Clone(strcat(histname,(sampleP1+suffix).c_str()));
  hTotalEnergyP1Clone->Write();
  strcpy(histname,"hNLowEGammas_");
  TH1D *hNLowEGammasP1Clone = (TH1D*)hNLowEGammasP1->Clone(strcat(histname,(sampleP1+suffix).c_str()));
  hNLowEGammasP1Clone->Write();
  strcpy(histname,"hTrackLength_");
  TH1D *hTrackLengthP1Clone = (TH1D*)hTrackLengthP1->Clone(strcat(histname,(sampleP1+suffix).c_str()));
  hTrackLengthP1Clone->Write();
  strcpy(histname,"hVertexSector_");
  TH1D *hVertexSectorP1Clone = (TH1D*)hVertexSectorP1->Clone(strcat(histname,(sampleP1+suffix).c_str()));
  hVertexSectorP1Clone->Write();
  strcpy(histname,"hVertexZ_");
  TH1D *hVertexZP1Clone = (TH1D*)hVertexZP1->Clone(strcat(histname,(sampleP1+suffix).c_str()));
  hVertexZP1Clone->Write();
  strcpy(histname,"hProbInt_");
  TH1D *hProbIntP1Clone = (TH1D*)hProbIntP1->Clone(strcat(histname,(sampleP1+suffix).c_str()));
  hProbIntP1Clone->Write();
  strcpy(histname,"hCosThetaEGMin_");
  TH1D *hCosThetaEGMinP1Clone = (TH1D*)hCosThetaEGMinP1->Clone(strcat(histname,(sampleP1+suffix).c_str()));
  hCosThetaEGMinP1Clone->Write();
  strcpy(histname,"hCosThetaEGMax_");
  TH1D *hCosThetaEGMaxP1Clone = (TH1D*)hCosThetaEGMaxP1->Clone(strcat(histname,(sampleP1+suffix).c_str()));
  hCosThetaEGMaxP1Clone->Write();
  strcpy(histname,"hCosThetaGG_");
  TH1D *hCosThetaGGP1Clone = (TH1D*)hCosThetaGGP1->Clone(strcat(histname,(sampleP1+suffix).c_str()));
  hCosThetaGGP1Clone->Write();

  string sampleP2 = sample + std::string("_P2");
  strcpy(histname,"hRun_");
  TH1D *hRunP2Clone = (TH1D*)hRunP2->Clone(strcat(histname,(sampleP2+suffix).c_str()));
  hRunP2Clone->Write();
  strcpy(histname,"hElectronEnergy_");
  TH1D *hElectronEnergyP2Clone = (TH1D*)hElectronEnergyP2->Clone(strcat(histname,(sampleP2+suffix).c_str()));
  hElectronEnergyP2Clone->Write();
  strcpy(histname,"hGammaEnergyMin_");
  TH1D *hGammaEnergyMinP2Clone = (TH1D*)hGammaEnergyMinP2->Clone(strcat(histname,(sampleP2+suffix).c_str()));
  hGammaEnergyMinP2Clone->Write();
  strcpy(histname,"hGammaEnergyMax_");
  TH1D *hGammaEnergyMaxP2Clone = (TH1D*)hGammaEnergyMaxP2->Clone(strcat(histname,(sampleP2+suffix).c_str()));
  hGammaEnergyMaxP2Clone->Write();
  strcpy(histname,"hElectronGammaSum_");
  TH1D *hElectronGammaSumP2Clone = (TH1D*)hElectronGammaSumP2->Clone(strcat(histname,(sampleP2+suffix).c_str()));
  hElectronGammaSumP2Clone->Write();
  strcpy(histname,"hLowGammaEnergy_");
  TH1D *hLowGammaEnergyP2Clone = (TH1D*)hLowGammaEnergyP2->Clone(strcat(histname,(sampleP2+suffix).c_str()));
  hLowGammaEnergyP2Clone->Write();
  strcpy(histname,"hTotalEnergy_");
  TH1D *hTotalEnergyP2Clone = (TH1D*)hTotalEnergyP2->Clone(strcat(histname,(sampleP2+suffix).c_str()));
  hTotalEnergyP2Clone->Write();
  strcpy(histname,"hNLowEGammas_");
  TH1D *hNLowEGammasP2Clone = (TH1D*)hNLowEGammasP2->Clone(strcat(histname,(sampleP2+suffix).c_str()));
  hNLowEGammasP2Clone->Write();
  strcpy(histname,"hTrackLength_");
  TH1D *hTrackLengthP2Clone = (TH1D*)hTrackLengthP2->Clone(strcat(histname,(sampleP2+suffix).c_str()));
  hTrackLengthP2Clone->Write();
  strcpy(histname,"hVertexSector_");
  TH1D *hVertexSectorP2Clone = (TH1D*)hVertexSectorP2->Clone(strcat(histname,(sampleP2+suffix).c_str()));
  hVertexSectorP2Clone->Write();
  strcpy(histname,"hVertexZ_");
  TH1D *hVertexZP2Clone = (TH1D*)hVertexZP2->Clone(strcat(histname,(sampleP2+suffix).c_str()));
  hVertexZP2Clone->Write();
  strcpy(histname,"hProbInt_");
  TH1D *hProbIntP2Clone = (TH1D*)hProbIntP2->Clone(strcat(histname,(sampleP2+suffix).c_str()));
  hProbIntP2Clone->Write();
  strcpy(histname,"hCosThetaEGMin_");
  TH1D *hCosThetaEGMinP2Clone = (TH1D*)hCosThetaEGMinP2->Clone(strcat(histname,(sampleP2+suffix).c_str()));
  hCosThetaEGMinP2Clone->Write();
  strcpy(histname,"hCosThetaEGMax_");
  TH1D *hCosThetaEGMaxP2Clone = (TH1D*)hCosThetaEGMaxP2->Clone(strcat(histname,(sampleP2+suffix).c_str()));
  hCosThetaEGMaxP2Clone->Write();
  strcpy(histname,"hCosThetaGG_");
  TH1D *hCosThetaGGP2Clone = (TH1D*)hCosThetaGGP2->Clone(strcat(histname,(sampleP2+suffix).c_str()));
  hCosThetaGGP2Clone->Write();

  outfile->Close();
  delete outfile;

  delete hRunP1;              
  delete hElectronEnergyP1;   
  delete hGammaEnergyMinP1;   
  delete hGammaEnergyMaxP1;   
  delete hElectronGammaSumP1; 
  delete hLowGammaEnergyP1;   
  delete hNLowEGammasP1;      
  delete hTotalEnergyP1;      
  delete hTrackLengthP1;      
  delete hVertexSectorP1;     
  delete hVertexZP1;          
  delete hProbIntP1;          
  delete hCosThetaEGMinP1;   
  delete hCosThetaEGMaxP1;    
  delete hCosThetaGGP1;       

  delete hRunP2;              
  delete hElectronEnergyP2;   
  delete hGammaEnergyMinP2;   
  delete hGammaEnergyMaxP2;   
  delete hElectronGammaSumP2; 
  delete hLowGammaEnergyP2;   
  delete hNLowEGammasP2;      
  delete hTotalEnergyP2;      
  delete hTrackLengthP2;      
  delete hVertexSectorP2;     
  delete hVertexZP2;          
  delete hProbIntP2;          
  delete hCosThetaEGMinP2;   
  delete hCosThetaEGMaxP2;    
  delete hCosThetaGGP2;       

  f->Close("R");
  delete f;

}

void addHistogramToFileInOutP1P2(string directory, string sample, string outfilename, string suffix){

  // Create histograms
  TH1D* hElectronEnergyP1_In  = new TH1D("hElectronEnergyP1_In","Electron Energy", 30, 0, 3);
  TH1D* hElectronEnergyP2_In  = new TH1D("hElectronEnergyP2_In","Electron Energy", 30, 0, 3);
  hElectronEnergyP1_In->Sumw2();   
  hElectronEnergyP2_In->Sumw2();   
  hElectronEnergyP1_In->SetTitle(";E_{e} / MeV; No. Events / 0.1 MeV");   
  hElectronEnergyP2_In->SetTitle(";E_{e} / MeV; No. Events / 0.1 MeV");   

  TH1D* hElectronEnergyP1_Out  = new TH1D("hElectronEnergyP1_Out","Electron Energy", 30, 0, 3);
  TH1D* hElectronEnergyP2_Out  = new TH1D("hElectronEnergyP2_Out","Electron Energy", 30, 0, 3);
  hElectronEnergyP1_Out->Sumw2();   
  hElectronEnergyP2_Out->Sumw2();   
  hElectronEnergyP1_Out->SetTitle(";E_{e} / MeV; No. Events / 0.1 MeV");   
  hElectronEnergyP2_Out->SetTitle(";E_{e} / MeV; No. Events / 0.1 MeV");   

  // Write out input file name
  string inputfile="/unix/nemo3/users/jmott/SeleniumAnalysis/ProcessedData/Backgrounds/1e2g/";
  inputfile.append(directory);
  inputfile.append(sample);
  inputfile.append("/IntBG_Se_1e2g_output.root");

  // Open file and get hold of branches and assign them to relevant names
  TFile* f = new TFile(inputfile.c_str(),"READ");
  TDirectoryFile* f1 = (TDirectoryFile*)f->Get("Se1e2gCuts");
  TTree* tree = (TTree*)f1->Get("Se1e2gCuts");

  int run, nLowEGammas, foilSide, vertexLocation, scintLocation;
  double electronEnergy, gammaEnergyMin, gammaEnergyMax, trackLength, vertexR, vertexZ, vertexSector, radonWeight, bi210Weight, gammaLowEnergy[10], probIntMin, probExtMin, probIntMax, probExtMax, cosThetaEGMin, cosThetaEGMax, cosThetaGG, trackSign;

  tree->SetBranchAddress("b_run", &run);
  tree->SetBranchAddress("b_electronEnergy", &electronEnergy);
  tree->SetBranchAddress("b_gammaEnergyMin", &gammaEnergyMin);
  tree->SetBranchAddress("b_gammaEnergyMax", &gammaEnergyMax);
  tree->SetBranchAddress("b_trackLength", &trackLength);
  tree->SetBranchAddress("b_trackSign", &trackSign);
  tree->SetBranchAddress("b_vertexR", &vertexR);
  tree->SetBranchAddress("b_vertexZ", &vertexZ);
  tree->SetBranchAddress("b_vertexSector", &vertexSector);
  tree->SetBranchAddress("b_vertexLocation", &vertexLocation);
  tree->SetBranchAddress("b_scintLocation", &scintLocation);
  tree->SetBranchAddress("b_radonWeight", &radonWeight);
  tree->SetBranchAddress("b_bi210Weight", &bi210Weight);
  tree->SetBranchAddress("b_foilSide", &foilSide);
  tree->SetBranchAddress("b_nLowEGammas", &nLowEGammas);
  tree->SetBranchAddress("b_gammaLowEnergy", &gammaLowEnergy);
  tree->SetBranchAddress("b_probIntMin", &probIntMin);
  tree->SetBranchAddress("b_probExtMin", &probExtMin);
  tree->SetBranchAddress("b_probIntMax", &probIntMax);
  tree->SetBranchAddress("b_probExtMax", &probExtMax);
  tree->SetBranchAddress("b_cosThetaEGMin", &cosThetaEGMin);
  tree->SetBranchAddress("b_cosThetaEGMax", &cosThetaEGMax);
  tree->SetBranchAddress("b_cosThetaGG", &cosThetaGG);
 
  Int_t N = tree->GetEntries();
  cout << "Entries = " << N << endl;

  // FILL HISTOGRAMS
  for (int iEvt = 0; iEvt < N; iEvt ++){

    if(iEvt % 500000 == 0){cout << "Processing event " << iEvt << "..." << endl;}

    tree->GetEntry(iEvt);

    double radWeight = 1;

    bool fill = true;

    if(std::string::npos != suffix.find("SeOld") && !(vertexLocation == 0)){fill = false;}
    if(std::string::npos != suffix.find("SeNew") && !(vertexLocation == 1 || vertexLocation == 2)){fill = false;}

    if(fill){
      if (run < 3396){
	if(foilSide == 0){hElectronEnergyP1_In->Fill(electronEnergy,radWeight);}
	else {hElectronEnergyP1_Out->Fill(electronEnergy,radWeight);}
      } else if(run >= 3396){
	if(foilSide == 0){hElectronEnergyP2_In->Fill(electronEnergy,radWeight);}
	else {hElectronEnergyP2_Out->Fill(electronEnergy,radWeight);}
      }
    }
  }

  TFile* outfile = new TFile(outfilename.c_str(),"UPDATE");
  char histname[200];

  string sampleP1_In = sample + std::string("_In_P1");
  strcpy(histname,"hElectronEnergy_");
  TH1D *hElectronEnergyP1_InClone = (TH1D*)hElectronEnergyP1_In->Clone(strcat(histname,(sampleP1_In+suffix).c_str()));
  hElectronEnergyP1_InClone->Write();

  string sampleP1_Out = sample + std::string("_Out_P1");
  strcpy(histname,"hElectronEnergy_");
  TH1D *hElectronEnergyP1_OutClone = (TH1D*)hElectronEnergyP1_Out->Clone(strcat(histname,(sampleP1_Out+suffix).c_str()));
  hElectronEnergyP1_OutClone->Write();

  string sampleP2_In = sample + std::string("_In_P2");
  strcpy(histname,"hElectronEnergy_");
  TH1D *hElectronEnergyP2_InClone = (TH1D*)hElectronEnergyP2_In->Clone(strcat(histname,(sampleP2_In+suffix).c_str()));
  hElectronEnergyP2_InClone->Write();

  string sampleP2_Out = sample + std::string("_Out_P2");
  strcpy(histname,"hElectronEnergy_");
  TH1D *hElectronEnergyP2_OutClone = (TH1D*)hElectronEnergyP2_Out->Clone(strcat(histname,(sampleP2_Out+suffix).c_str()));
  hElectronEnergyP2_OutClone->Write();


  outfile->Close();
  delete outfile;

  delete hElectronEnergyP1_In;
  delete hElectronEnergyP1_Out;
  delete hElectronEnergyP2_In;
  delete hElectronEnergyP2_Out;

  f->Close("R");
  delete f;

}

