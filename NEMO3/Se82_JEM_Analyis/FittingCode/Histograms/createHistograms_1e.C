#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
#include <TStyle.h>
#include <TROOT.h>
#include <iostream>
#include <TGaxis.h>
#include <TRandom3.h>

using namespace std;

void addHistogramToFile(string directory, string sample, string outfilename);
void addHistogramToFileInOut(string directory, string sample, string outfilename);

Int_t createHistograms_1e(){
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
  TFile* outfile = new TFile("./Histograms_1e.root","RECREATE");
  outfile->Close();
  delete outfile;

  // Add Data Histogram
  addHistogramToFile("Data/","Data","./Histograms_1e.root");
  addHistogramToFile("Data/","Data_Neutrons","./Histograms_1e.root");

  // Add Signal Histograms
  //  addHistogramToFile("Signal/","2b2n","./Histograms_1e.root");
  addHistogramToFile("Signal/","2b2n_SeNew","./Histograms_1e.root");
  addHistogramToFile("Signal/","2b2n_SeOld","./Histograms_1e.root");
  //  addHistogramToFile("Signal/","2b2n_SSD","./Histograms_1e.root");
  addHistogramToFile("Signal/","2b2n_SeNew_SSD","./Histograms_1e.root");
  addHistogramToFile("Signal/","2b2n_SeOld_SSD","./Histograms_1e.root");
  //  addHistogramToFile("Signal/","2b0n_m1","./Histograms_1e.root");

  // Add different Internal MC samples
  addHistogramToFile("InternalBackgrounds/","SeNew_Ac228", "./Histograms_1e.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Bi212", "./Histograms_1e.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Bi214", "./Histograms_1e.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_K40",   "./Histograms_1e.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Pa234m","./Histograms_1e.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Pa234m_OldGenBB","./Histograms_1e.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Pb211", "./Histograms_1e.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Pb214", "./Histograms_1e.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Tl207", "./Histograms_1e.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Tl208", "./Histograms_1e.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Sr90",  "./Histograms_1e.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Y90",   "./Histograms_1e.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Ac228", "./Histograms_1e.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Bi212", "./Histograms_1e.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Bi214", "./Histograms_1e.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_K40",   "./Histograms_1e.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Pa234m","./Histograms_1e.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Pa234m_OldGenBB","./Histograms_1e.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Pb211", "./Histograms_1e.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Pb214", "./Histograms_1e.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Tl207", "./Histograms_1e.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Tl208", "./Histograms_1e.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Sr90",  "./Histograms_1e.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Y90",   "./Histograms_1e.root");
  addHistogramToFile("InternalBackgrounds/","Mylar_Bi214", "./Histograms_1e.root");
  addHistogramToFile("InternalBackgrounds/","Mylar_Pb214", "./Histograms_1e.root");

  // Add different External MC samples
  addHistogramToFile("ExternalBackgrounds/","PMT_K40",          "./Histograms_1e.root");
  addHistogramToFile("ExternalBackgrounds/","PMT_Bi214",        "./Histograms_1e.root");
  addHistogramToFile("ExternalBackgrounds/","PMT_Tl208",        "./Histograms_1e.root");
  addHistogramToFile("ExternalBackgrounds/","PMT_Ac228",        "./Histograms_1e.root");
  addHistogramToFile("ExternalBackgrounds/","MuMetal_Co60",     "./Histograms_1e.root");
  addHistogramToFile("ExternalBackgrounds/","CuPetals_Co60",    "./Histograms_1e.root");
  addHistogramToFile("ExternalBackgrounds/","CuTower_Co60",     "./Histograms_1e.root");
  addHistogramToFile("ExternalBackgrounds/","FeShield_Tl208",   "./Histograms_1e.root");
  addHistogramToFile("ExternalBackgrounds/","FeShield_Bi214",   "./Histograms_1e.root");
  addHistogramToFile("ExternalBackgrounds/","FeShield_Ac228",   "./Histograms_1e.root");
  addHistogramToFile("ExternalBackgrounds/","ScintInn_K40",     "./Histograms_1e.root");
  addHistogramToFile("ExternalBackgrounds/","ScintOut_K40",     "./Histograms_1e.root");
  addHistogramToFile("ExternalBackgrounds/","ScintPet_K40",     "./Histograms_1e.root");
  addHistogramToFile("ExternalBackgrounds/","SteelFrame_K40",   "./Histograms_1e.root");
  addHistogramToFile("ExternalBackgrounds/","SteelFrame_Bi214", "./Histograms_1e.root");
  addHistogramToFile("ExternalBackgrounds/","SteelFrame_Tl208", "./Histograms_1e.root");
  addHistogramToFile("ExternalBackgrounds/","SteelFrame_Ac228", "./Histograms_1e.root");
  addHistogramToFile("ExternalBackgrounds/","SteelFrame_Co60",  "./Histograms_1e.root");
  addHistogramToFile("ExternalBackgrounds/","MuMetal_g1000",    "./Histograms_1e.root");
  addHistogramToFile("ExternalBackgrounds/","SScin_Pa234m",     "./Histograms_1e.root");

  // Add different radon MC samples
  addHistogramToFile("RadonBackgrounds/","SFoil_Bi214",         "./Histograms_1e.root");
  addHistogramToFile("RadonBackgrounds/","SFoil_Pb214",         "./Histograms_1e.root");
  addHistogramToFile("RadonBackgrounds/","SFoil_SeNew_Bi210",   "./Histograms_1e.root");
  addHistogramToFile("RadonBackgrounds/","SFoil_SeOld_Bi210",   "./Histograms_1e.root");
  addHistogramToFile("RadonBackgrounds/","SFoil_Strip_Bi210",   "./Histograms_1e.root");
  addHistogramToFile("RadonBackgrounds/","SWire_Bi214",         "./Histograms_1e.root");
  addHistogramToFile("RadonBackgrounds/","SWire_Pb214",         "./Histograms_1e.root");
  addHistogramToFile("RadonBackgrounds/","SWire_Bi210",         "./Histograms_1e.root");
  addHistogramToFile("RadonBackgrounds/","SWire_Tl208",         "./Histograms_1e.root");
  addHistogramToFile("RadonBackgrounds/","SScin_Bi214",         "./Histograms_1e.root");
  addHistogramToFile("RadonBackgrounds/","SScin_Pb214",         "./Histograms_1e.root");
  addHistogramToFile("RadonBackgrounds/","SScin_Bi210",         "./Histograms_1e.root");
  addHistogramToFile("RadonBackgrounds/","Air_Bi214",           "./Histograms_1e.root");
  addHistogramToFile("RadonBackgrounds/","Air_Pb214",           "./Histograms_1e.root");
  addHistogramToFile("RadonBackgrounds/","Air_Tl208",           "./Histograms_1e.root");

  return 0;
}

void addHistogramToFile(string directory, string sample, string outfilename){

  cout << "Adding histograms for " << sample << "..." << endl; 

  if(std::string::npos != sample.find("SFoil") && std::string::npos != sample.find("214")){
    addHistogramToFileInOut(directory, sample, outfilename);
    return;
  }

  // Write out input file names
  string inputfile = "/unix/nemo3/users/jmott/SeleniumAnalysis/ProcessedData/Backgrounds/1e/";
  inputfile.append(directory);
  if(std::string::npos != sample.find("SFoil") && std::string::npos != sample.find("210")){inputfile.append("SFoil_Bi210");}
  else if(sample.find("2b2n_Se") != std::string::npos){
    if(sample.find("SSD") != std::string::npos) inputfile.append("2b2n_SSD");
    else                                        inputfile.append("2b2n");
  } else {
    inputfile.append(sample);
  }
  inputfile.append("/IntBG_Se_1e_output.root");

  // Open file and get hold of branches and assign them to relevant names
  TFile* f = new TFile(inputfile.c_str(),"READ");
  string treename = "Se1eCuts";
  TDirectoryFile* f1 = (TDirectoryFile*)f->Get(treename.c_str());
  TTree* tree = (TTree*)f1->Get(treename.c_str());

  // Fit electron energy for 1e
  TH1D* hElectronEnergyP1_SeOld;
  TH1D* hElectronEnergyP1_SeNew;
  TH1D* hElectronEnergyP1_Strip;
  TH1D* hElectronEnergyP2_SeOld;
  TH1D* hElectronEnergyP2_SeNew;
  TH1D* hElectronEnergyP2_Strip;
  hElectronEnergyP1_SeOld  = new TH1D("hElectronEnergyP1_SeOld","Electron Energy", 170, 0, 3.4);
  hElectronEnergyP2_SeOld  = new TH1D("hElectronEnergyP2_SeOld","Electron Energy", 170, 0, 3.4);
  hElectronEnergyP1_SeNew  = new TH1D("hElectronEnergyP1_SeNew","Electron Energy", 170, 0, 3.4);
  hElectronEnergyP2_SeNew  = new TH1D("hElectronEnergyP2_SeNew","Electron Energy", 170, 0, 3.4);
  hElectronEnergyP1_Strip  = new TH1D("hElectronEnergyP1_Strip","Electron Energy", 68,  0, 3.4);
  hElectronEnergyP2_Strip  = new TH1D("hElectronEnergyP2_Strip","Electron Energy", 68,  0, 3.4);
  hElectronEnergyP1_SeOld->SetTitle(";E_{e} / MeV; No. Events / 0.02 MeV");
  hElectronEnergyP2_SeOld->SetTitle(";E_{e} / MeV; No. Events / 0.02 MeV");
  hElectronEnergyP1_SeNew->SetTitle(";E_{e} / MeV; No. Events / 0.02 MeV");
  hElectronEnergyP2_SeNew->SetTitle(";E_{e} / MeV; No. Events / 0.02 MeV");
  hElectronEnergyP1_Strip->SetTitle(";E_{e} / MeV; No. Events / 0.05 MeV");
  hElectronEnergyP2_Strip->SetTitle(";E_{e} / MeV; No. Events / 0.05 MeV");
  hElectronEnergyP1_SeOld->Sumw2();
  hElectronEnergyP2_SeOld->Sumw2();
  hElectronEnergyP1_SeNew->Sumw2();
  hElectronEnergyP2_SeNew->Sumw2();
  hElectronEnergyP1_Strip->Sumw2();
  hElectronEnergyP2_Strip->Sumw2();

  int run, foilSide, vertexLocation, scintLocation;
  double electronEnergy, radonWeight, bi210Weight, trackLength, trueVertexSector, trueVertexZ, eventTime, trackSign;

  tree->SetBranchAddress("b_run", &run);
  tree->SetBranchAddress("b_electronEnergy", &electronEnergy);
  tree->SetBranchAddress("b_radonWeight", &radonWeight);
  tree->SetBranchAddress("b_bi210Weight", &bi210Weight);
  tree->SetBranchAddress("b_foilSide", &foilSide);
  tree->SetBranchAddress("b_trackLength", &trackLength);
  tree->SetBranchAddress("b_trackSign", &trackSign);
  tree->SetBranchAddress("b_vertexLocation", &vertexLocation);
  tree->SetBranchAddress("b_trueVertexSector", &trueVertexSector);
  tree->SetBranchAddress("b_trueVertexZ", &trueVertexZ);
  tree->SetBranchAddress("b_scintLocation", &scintLocation);
  tree->SetBranchAddress("b_eventTime", &eventTime);
 
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

    double radWeight;
    if(std::string::npos != sample.find("SWire") && std::string::npos != sample.find("214") ){
      radWeight = radonWeight;
    }
    else if(std::string::npos != sample.find("SWire") && std::string::npos != sample.find("210") ){
      radWeight = bi210Weight;
    }
    else {
      radWeight = 1;
    }

    // Take into account half-lives for Bi210, Co60 & Y90/Sr90
    if(std::string::npos != sample.find("Bi210")){
      radWeight *= exp(-(log(2)/(22.3*365.25*86400.0))*eventTime);
    }
    if(std::string::npos != sample.find("Co60")){
      radWeight *= exp(-(log(2)/(1925.2*86400.0))*eventTime);
    }
    if(std::string::npos != sample.find("Y90") or std::string::npos != sample.find("Sr90")){
      radWeight *= exp(-(log(2)/(10515.5*86400.0))*eventTime);
    }

    bool fill = true;

    if(std::string::npos != sample.find("SFoil") && std::string::npos != sample.find("Bi210")){

      int trueVertexLocation;

      if (trueVertexSector >= 6.0 && trueVertexSector <= 7.0){
	trueVertexLocation = 0;
      } else if(trueVertexSector >= 7.0 && trueVertexSector <= 8.0){
	trueVertexLocation = 1;
      } else if(trueVertexSector >=8.0 &&  trueVertexSector <= 8.2){
	  if(trueVertexZ <= -38.6){
	    trueVertexLocation = 2;
	  } else {
	    trueVertexLocation = 0;
	  }
      } else {
	trueVertexLocation = 0;
      }

      if(std::string::npos != sample.find("SFoil_SeOld_Bi210") && (trueVertexLocation != 0)){fill = false;}
      if(std::string::npos != sample.find("SFoil_SeNew_Bi210") && (trueVertexLocation != 1)){fill = false;}
      if(std::string::npos != sample.find("SFoil_Strip_Bi210") && (trueVertexLocation != 2)){fill = false;}

    }

    // Separate out 2b2n sample based on SeOld/SeNew
    if(std::string::npos != sample.find("2b2n_Se")){

      int trueVertexLocation;

      if (trueVertexSector >= 6.0 && trueVertexSector <= 7.0){
	trueVertexLocation = 0;
      } else if(trueVertexSector >= 7.0 && trueVertexSector <= 8.0){
	trueVertexLocation = 1;
      } else if(trueVertexSector >=8.0 &&  trueVertexSector <= 8.2){
	  if(trueVertexZ <= -38.6){
	    trueVertexLocation = 1;
	  } else {
	    trueVertexLocation = 0;
	  }
      } else {
	trueVertexLocation = 0;
      }

      if(std::string::npos != sample.find("2b2n_SeOld") && (trueVertexLocation != 0)){fill = false;}
      if(std::string::npos != sample.find("2b2n_SeNew") && (trueVertexLocation != 1)){fill = false;}
    }

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

    if(fill){
      if(vertexLocation == 0){
	if(run < 3396){ hElectronEnergyP1_SeOld->Fill(electronEnergy,radWeight); }
	else{           hElectronEnergyP2_SeOld->Fill(electronEnergy,radWeight);}
      }
      else if (vertexLocation == 1){
	if(run < 3396){ hElectronEnergyP1_SeNew->Fill(electronEnergy,radWeight); }
	else{           hElectronEnergyP2_SeNew->Fill(electronEnergy,radWeight);}
      }
      else if (vertexLocation == 2){
	if(run < 3396){ hElectronEnergyP1_Strip->Fill(electronEnergy,radWeight); }
	else{           hElectronEnergyP2_Strip->Fill(electronEnergy,radWeight);}
      }
    }
  }

  TFile* outfile = new TFile(outfilename.c_str(),"UPDATE");
  char histname[200];

  string sampleP1 = sample + std::string("_P1");
  strcpy(histname,"hElectronEnergy_");
  TH1D *hElectronEnergyP1_SeOldClone = (TH1D*)hElectronEnergyP1_SeOld->Clone(strcat(histname,(sampleP1+"_SeOld").c_str()));
  hElectronEnergyP1_SeOldClone->Write();

  strcpy(histname,"hElectronEnergy_");
  TH1D *hElectronEnergyP1_SeNewClone = (TH1D*)hElectronEnergyP1_SeNew->Clone(strcat(histname,(sampleP1+"_SeNew").c_str()));
  hElectronEnergyP1_SeNewClone->Write();

  strcpy(histname,"hElectronEnergy_");
  TH1D *hElectronEnergyP1_StripClone = (TH1D*)hElectronEnergyP1_Strip->Clone(strcat(histname,(sampleP1+"_Strip").c_str()));
  hElectronEnergyP1_StripClone->Write();

  string sampleP2 = sample + std::string("_P2");
  strcpy(histname,"hElectronEnergy_");
  TH1D *hElectronEnergyP2_SeOldClone = (TH1D*)hElectronEnergyP2_SeOld->Clone(strcat(histname,(sampleP2+"_SeOld").c_str()));
  hElectronEnergyP2_SeOldClone->Write();

  strcpy(histname,"hElectronEnergy_");
  TH1D *hElectronEnergyP2_SeNewClone = (TH1D*)hElectronEnergyP2_SeNew->Clone(strcat(histname,(sampleP2+"_SeNew").c_str()));
  hElectronEnergyP2_SeNewClone->Write();

  strcpy(histname,"hElectronEnergy_");
  TH1D *hElectronEnergyP2_StripClone = (TH1D*)hElectronEnergyP2_Strip->Clone(strcat(histname,(sampleP2+"_Strip").c_str()));
  hElectronEnergyP2_StripClone->Write();

  outfile->Close();
  delete outfile;

  delete hElectronEnergyP1_SeOld;
  delete hElectronEnergyP2_SeOld;
  delete hElectronEnergyP1_SeNew;
  delete hElectronEnergyP2_SeNew;
  delete hElectronEnergyP1_Strip;
  delete hElectronEnergyP2_Strip;

  f->Close("R");
  delete f;

}

void addHistogramToFileInOut(string directory, string sample, string outfilename){

  // Write out input file names
  string inputfile = "/unix/nemo3/users/jmott/SeleniumAnalysis/ProcessedData/Backgrounds/1e/";
  inputfile.append(directory);
  inputfile.append(sample);
  inputfile.append("/IntBG_Se_1e_output.root");

  // Open file and get hold of branches and assign them to relevant names
  TFile* f = new TFile(inputfile.c_str(),"READ");
  string treename = "Se1eCuts";
  TDirectoryFile* f1 = (TDirectoryFile*)f->Get(treename.c_str());
  TTree* tree = (TTree*)f1->Get(treename.c_str());

  // Fit electron energy for 1e
  TH1D* hElectronEnergyP1_SeOld_In;
  TH1D* hElectronEnergyP1_SeNew_In;
  TH1D* hElectronEnergyP1_Strip_In;
  TH1D* hElectronEnergyP2_SeOld_In;
  TH1D* hElectronEnergyP2_SeNew_In;
  TH1D* hElectronEnergyP2_Strip_In;
  hElectronEnergyP1_SeOld_In  = new TH1D("hElectronEnergyP1_SeOld_In","Electron Energy", 170, 0, 3.4);
  hElectronEnergyP2_SeOld_In  = new TH1D("hElectronEnergyP2_SeOld_In","Electron Energy", 170, 0, 3.4);
  hElectronEnergyP1_SeNew_In  = new TH1D("hElectronEnergyP1_SeNew_In","Electron Energy", 170, 0, 3.4);
  hElectronEnergyP2_SeNew_In  = new TH1D("hElectronEnergyP2_SeNew_In","Electron Energy", 170, 0, 3.4);
  hElectronEnergyP1_Strip_In  = new TH1D("hElectronEnergyP1_Strip_In","Electron Energy", 68,  0, 3.4);
  hElectronEnergyP2_Strip_In  = new TH1D("hElectronEnergyP2_Strip_In","Electron Energy", 68,  0, 3.4);
  hElectronEnergyP1_SeOld_In->SetTitle(";E_{e} / MeV; No. Events / 0.02 MeV");
  hElectronEnergyP2_SeOld_In->SetTitle(";E_{e} / MeV; No. Events / 0.02 MeV");
  hElectronEnergyP1_SeNew_In->SetTitle(";E_{e} / MeV; No. Events / 0.02 MeV");
  hElectronEnergyP2_SeNew_In->SetTitle(";E_{e} / MeV; No. Events / 0.02 MeV");
  hElectronEnergyP1_Strip_In->SetTitle(";E_{e} / MeV; No. Events / 0.05 MeV");
  hElectronEnergyP2_Strip_In->SetTitle(";E_{e} / MeV; No. Events / 0.05 MeV");
  hElectronEnergyP1_SeOld_In->Sumw2();
  hElectronEnergyP2_SeOld_In->Sumw2();
  hElectronEnergyP1_SeNew_In->Sumw2();
  hElectronEnergyP2_SeNew_In->Sumw2();
  hElectronEnergyP1_Strip_In->Sumw2();
  hElectronEnergyP2_Strip_In->Sumw2();

  TH1D* hElectronEnergyP1_SeOld_Out;
  TH1D* hElectronEnergyP1_SeNew_Out;
  TH1D* hElectronEnergyP1_Strip_Out;
  TH1D* hElectronEnergyP2_SeOld_Out;
  TH1D* hElectronEnergyP2_SeNew_Out;
  TH1D* hElectronEnergyP2_Strip_Out;
  hElectronEnergyP1_SeOld_Out  = new TH1D("hElectronEnergyP1_SeOld_Out","Electron Energy", 170, 0, 3.4);
  hElectronEnergyP2_SeOld_Out  = new TH1D("hElectronEnergyP2_SeOld_Out","Electron Energy", 170, 0, 3.4);
  hElectronEnergyP1_SeNew_Out  = new TH1D("hElectronEnergyP1_SeNew_Out","Electron Energy", 170, 0, 3.4);
  hElectronEnergyP2_SeNew_Out  = new TH1D("hElectronEnergyP2_SeNew_Out","Electron Energy", 170, 0, 3.4);
  hElectronEnergyP1_Strip_Out  = new TH1D("hElectronEnergyP1_Strip_Out","Electron Energy", 68,  0, 3.4);
  hElectronEnergyP2_Strip_Out  = new TH1D("hElectronEnergyP2_Strip_Out","Electron Energy", 68,  0, 3.4);
  hElectronEnergyP1_SeOld_Out->SetTitle(";E_{e} / MeV; No. Events / 0.02 MeV");
  hElectronEnergyP2_SeOld_Out->SetTitle(";E_{e} / MeV; No. Events / 0.02 MeV");
  hElectronEnergyP1_SeNew_Out->SetTitle(";E_{e} / MeV; No. Events / 0.02 MeV");
  hElectronEnergyP2_SeNew_Out->SetTitle(";E_{e} / MeV; No. Events / 0.02 MeV");
  hElectronEnergyP1_Strip_Out->SetTitle(";E_{e} / MeV; No. Events / 0.05 MeV");
  hElectronEnergyP2_Strip_Out->SetTitle(";E_{e} / MeV; No. Events / 0.05 MeV");
  hElectronEnergyP1_SeOld_Out->Sumw2();
  hElectronEnergyP2_SeOld_Out->Sumw2();
  hElectronEnergyP1_SeNew_Out->Sumw2();
  hElectronEnergyP2_SeNew_Out->Sumw2();
  hElectronEnergyP1_Strip_Out->Sumw2();
  hElectronEnergyP2_Strip_Out->Sumw2();

  int run, foilSide, vertexLocation, scintLocation;
  double electronEnergy, radonWeight, bi210Weight, trackLength, trackSign;

  tree->SetBranchAddress("b_run", &run);
  tree->SetBranchAddress("b_electronEnergy", &electronEnergy);
  tree->SetBranchAddress("b_radonWeight", &radonWeight);
  tree->SetBranchAddress("b_bi210Weight", &bi210Weight);
  tree->SetBranchAddress("b_foilSide", &foilSide);
  tree->SetBranchAddress("b_trackLength", &trackLength);
  tree->SetBranchAddress("b_trackSign", &trackSign);
  tree->SetBranchAddress("b_vertexLocation", &vertexLocation);
  tree->SetBranchAddress("b_scintLocation", &scintLocation);
 
  Int_t N = tree->GetEntries();
  cout << "Entries = " << N << endl;

  // FILL HISTOGRAMS
  for (int iEvt = 0; iEvt < N; iEvt ++){

    if(iEvt % 500000 == 0){cout << "Processing event " << iEvt << "..." << endl;}

    tree->GetEntry(iEvt);

    double radWeight = 1;

    bool fill = true;

    if(fill){
      if(foilSide == 0){
	if(vertexLocation == 0){
	  if(run < 3396){ hElectronEnergyP1_SeOld_In->Fill(electronEnergy,radWeight); }
	  else{           hElectronEnergyP2_SeOld_In->Fill(electronEnergy,radWeight);}
	}
	else if (vertexLocation == 1){
	  if(run < 3396){ hElectronEnergyP1_SeNew_In->Fill(electronEnergy,radWeight); }
	  else{           hElectronEnergyP2_SeNew_In->Fill(electronEnergy,radWeight);}
	}
	else if (vertexLocation == 2){
	  if(run < 3396){ hElectronEnergyP1_Strip_In->Fill(electronEnergy,radWeight); }
	  else{           hElectronEnergyP2_Strip_In->Fill(electronEnergy,radWeight);}
	}
      } else {
	if(vertexLocation == 0){
	  if(run < 3396){ hElectronEnergyP1_SeOld_Out->Fill(electronEnergy,radWeight); }
	  else{           hElectronEnergyP2_SeOld_Out->Fill(electronEnergy,radWeight);}
	}
	else if (vertexLocation == 1){
	  if(run < 3396){ hElectronEnergyP1_SeNew_Out->Fill(electronEnergy,radWeight); }
	  else{           hElectronEnergyP2_SeNew_Out->Fill(electronEnergy,radWeight);}
	}
	else if (vertexLocation == 2){
	  if(run < 3396){ hElectronEnergyP1_Strip_Out->Fill(electronEnergy,radWeight); }
	  else{           hElectronEnergyP2_Strip_Out->Fill(electronEnergy,radWeight);}
	}
      }
    }
  }

  TFile* outfile = new TFile(outfilename.c_str(),"UPDATE");
  char histname[200];

  string sampleP1_In = sample + std::string("_In_P1");
  strcpy(histname,"hElectronEnergy_");
  TH1D *hElectronEnergyP1_SeOld_InClone = (TH1D*)hElectronEnergyP1_SeOld_In->Clone(strcat(histname,(sampleP1_In+"_SeOld").c_str()));
  hElectronEnergyP1_SeOld_InClone->Write();

  strcpy(histname,"hElectronEnergy_");
  TH1D *hElectronEnergyP1_SeNew_InClone = (TH1D*)hElectronEnergyP1_SeNew_In->Clone(strcat(histname,(sampleP1_In+"_SeNew").c_str()));
  hElectronEnergyP1_SeNew_InClone->Write();

  strcpy(histname,"hElectronEnergy_");
  TH1D *hElectronEnergyP1_Strip_InClone = (TH1D*)hElectronEnergyP1_Strip_In->Clone(strcat(histname,(sampleP1_In+"_Strip").c_str()));
  hElectronEnergyP1_Strip_InClone->Write();

 string sampleP1_Out = sample + std::string("_Out_P1");
  strcpy(histname,"hElectronEnergy_");
  TH1D *hElectronEnergyP1_SeOld_OutClone = (TH1D*)hElectronEnergyP1_SeOld_Out->Clone(strcat(histname,(sampleP1_Out+"_SeOld").c_str()));
  hElectronEnergyP1_SeOld_OutClone->Write();

  strcpy(histname,"hElectronEnergy_");
  TH1D *hElectronEnergyP1_SeNew_OutClone = (TH1D*)hElectronEnergyP1_SeNew_Out->Clone(strcat(histname,(sampleP1_Out+"_SeNew").c_str()));
  hElectronEnergyP1_SeNew_OutClone->Write();

  strcpy(histname,"hElectronEnergy_");
  TH1D *hElectronEnergyP1_Strip_OutClone = (TH1D*)hElectronEnergyP1_Strip_Out->Clone(strcat(histname,(sampleP1_Out+"_Strip").c_str()));
  hElectronEnergyP1_Strip_OutClone->Write();

 string sampleP2_In = sample + std::string("_In_P2");
  strcpy(histname,"hElectronEnergy_");
  TH1D *hElectronEnergyP2_SeOld_InClone = (TH1D*)hElectronEnergyP2_SeOld_In->Clone(strcat(histname,(sampleP2_In+"_SeOld").c_str()));
  hElectronEnergyP2_SeOld_InClone->Write();

  strcpy(histname,"hElectronEnergy_");
  TH1D *hElectronEnergyP2_SeNew_InClone = (TH1D*)hElectronEnergyP2_SeNew_In->Clone(strcat(histname,(sampleP2_In+"_SeNew").c_str()));
  hElectronEnergyP2_SeNew_InClone->Write();

  strcpy(histname,"hElectronEnergy_");
  TH1D *hElectronEnergyP2_Strip_InClone = (TH1D*)hElectronEnergyP2_Strip_In->Clone(strcat(histname,(sampleP2_In+"_Strip").c_str()));
  hElectronEnergyP2_Strip_InClone->Write();

 string sampleP2_Out = sample + std::string("_Out_P2");
  strcpy(histname,"hElectronEnergy_");
  TH1D *hElectronEnergyP2_SeOld_OutClone = (TH1D*)hElectronEnergyP2_SeOld_Out->Clone(strcat(histname,(sampleP2_Out+"_SeOld").c_str()));
  hElectronEnergyP2_SeOld_OutClone->Write();

  strcpy(histname,"hElectronEnergy_");
  TH1D *hElectronEnergyP2_SeNew_OutClone = (TH1D*)hElectronEnergyP2_SeNew_Out->Clone(strcat(histname,(sampleP2_Out+"_SeNew").c_str()));
  hElectronEnergyP2_SeNew_OutClone->Write();

  strcpy(histname,"hElectronEnergy_");
  TH1D *hElectronEnergyP2_Strip_OutClone = (TH1D*)hElectronEnergyP2_Strip_Out->Clone(strcat(histname,(sampleP2_Out+"_Strip").c_str()));
  hElectronEnergyP2_Strip_OutClone->Write();

  outfile->Close();
  delete outfile;

  delete hElectronEnergyP1_SeOld_In;
  delete hElectronEnergyP2_SeOld_In;
  delete hElectronEnergyP1_SeNew_In;
  delete hElectronEnergyP2_SeNew_In;
  delete hElectronEnergyP1_Strip_In;
  delete hElectronEnergyP2_Strip_In;
  delete hElectronEnergyP1_SeOld_Out;
  delete hElectronEnergyP2_SeOld_Out;
  delete hElectronEnergyP1_SeNew_Out;
  delete hElectronEnergyP2_SeNew_Out;
  delete hElectronEnergyP1_Strip_Out;
  delete hElectronEnergyP2_Strip_Out;

  f->Close("R");
  delete f;

}



