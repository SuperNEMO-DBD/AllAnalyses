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

Int_t createHistograms_ExtEG(){
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
  TFile* outfile = new TFile("./Histograms_ExtEG.root","RECREATE");
  outfile->Close();
  delete outfile;

  // Add Data Histogram
  addHistogramToFile("Data/","Data","./Histograms_ExtEG.root");
  addHistogramToFile("Data/","Data_Neutrons","./Histograms_ExtEG.root");

  // Add Signal Histograms
  //  addHistogramToFile("Signal/","2b2n","./Histograms_ExtEG.root");
  addHistogramToFile("Signal/","2b2n_SeNew","./Histograms_ExtEG.root");
  addHistogramToFile("Signal/","2b2n_SeOld","./Histograms_ExtEG.root");
  //  addHistogramToFile("Signal/","2b2n_SSD","./Histograms_ExtEG.root");
  addHistogramToFile("Signal/","2b2n_SeNew_SSD","./Histograms_ExtEG.root");
  addHistogramToFile("Signal/","2b2n_SeOld_SSD","./Histograms_ExtEG.root");
  //  addHistogramToFile("Signal/","2b0n_m1","./Histograms_ExtEG.root");

  // Add different Internal MC samples
  addHistogramToFile("InternalBackgrounds/","SeNew_Ac228", "./Histograms_ExtEG.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Bi212", "./Histograms_ExtEG.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Bi214", "./Histograms_ExtEG.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_K40",   "./Histograms_ExtEG.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Pa234m","./Histograms_ExtEG.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Pa234m_OldGenBB","./Histograms_ExtEG.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Pb211", "./Histograms_ExtEG.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Pb214", "./Histograms_ExtEG.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Tl207", "./Histograms_ExtEG.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Tl208", "./Histograms_ExtEG.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Sr90",  "./Histograms_ExtEG.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Y90",   "./Histograms_ExtEG.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Ac228", "./Histograms_ExtEG.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Bi212", "./Histograms_ExtEG.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Bi214", "./Histograms_ExtEG.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_K40",   "./Histograms_ExtEG.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Pa234m","./Histograms_ExtEG.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Pa234m_OldGenBB","./Histograms_ExtEG.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Pb211", "./Histograms_ExtEG.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Pb214", "./Histograms_ExtEG.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Tl207", "./Histograms_ExtEG.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Tl208", "./Histograms_ExtEG.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Sr90",  "./Histograms_ExtEG.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Y90",   "./Histograms_ExtEG.root");
  addHistogramToFile("InternalBackgrounds/","Mylar_Bi214", "./Histograms_ExtEG.root");
  addHistogramToFile("InternalBackgrounds/","Mylar_Pb214", "./Histograms_ExtEG.root");

  // Add different External MC samples
  addHistogramToFile("ExternalBackgrounds/","PMT_K40",          "./Histograms_ExtEG.root");
  addHistogramToFile("ExternalBackgrounds/","PMT_Bi214",        "./Histograms_ExtEG.root");
  addHistogramToFile("ExternalBackgrounds/","PMT_Tl208",        "./Histograms_ExtEG.root");
  addHistogramToFile("ExternalBackgrounds/","PMT_Ac228",        "./Histograms_ExtEG.root");
  addHistogramToFile("ExternalBackgrounds/","MuMetal_Co60",     "./Histograms_ExtEG.root");
  addHistogramToFile("ExternalBackgrounds/","CuPetals_Co60",    "./Histograms_ExtEG.root");
  addHistogramToFile("ExternalBackgrounds/","CuTower_Co60",     "./Histograms_ExtEG.root");
  addHistogramToFile("ExternalBackgrounds/","FeShield_Tl208",   "./Histograms_ExtEG.root");
  addHistogramToFile("ExternalBackgrounds/","FeShield_Bi214",   "./Histograms_ExtEG.root");
  addHistogramToFile("ExternalBackgrounds/","FeShield_Ac228",   "./Histograms_ExtEG.root");
  addHistogramToFile("ExternalBackgrounds/","ScintInn_K40",     "./Histograms_ExtEG.root");
  addHistogramToFile("ExternalBackgrounds/","ScintOut_K40",     "./Histograms_ExtEG.root");
  addHistogramToFile("ExternalBackgrounds/","ScintPet_K40",     "./Histograms_ExtEG.root");
  addHistogramToFile("ExternalBackgrounds/","SteelFrame_K40",   "./Histograms_ExtEG.root");
  addHistogramToFile("ExternalBackgrounds/","SteelFrame_Bi214", "./Histograms_ExtEG.root");
  addHistogramToFile("ExternalBackgrounds/","SteelFrame_Tl208", "./Histograms_ExtEG.root");
  addHistogramToFile("ExternalBackgrounds/","SteelFrame_Ac228", "./Histograms_ExtEG.root");
  addHistogramToFile("ExternalBackgrounds/","SteelFrame_Co60",  "./Histograms_ExtEG.root");
  addHistogramToFile("ExternalBackgrounds/","MuMetal_g1000",    "./Histograms_ExtEG.root");
  addHistogramToFile("ExternalBackgrounds/","SScin_Pa234m",     "./Histograms_ExtEG.root");

  // Add different radon MC samples
  addHistogramToFile("RadonBackgrounds/","SFoil_Bi214",         "./Histograms_ExtEG.root");
  addHistogramToFile("RadonBackgrounds/","SFoil_Pb214",         "./Histograms_ExtEG.root");
  addHistogramToFile("RadonBackgrounds/","SFoil_SeNew_Bi210",   "./Histograms_ExtEG.root");
  addHistogramToFile("RadonBackgrounds/","SFoil_SeOld_Bi210",   "./Histograms_ExtEG.root");
  addHistogramToFile("RadonBackgrounds/","SFoil_Strip_Bi210",   "./Histograms_ExtEG.root");
  addHistogramToFile("RadonBackgrounds/","SWire_Bi214",         "./Histograms_ExtEG.root");
  addHistogramToFile("RadonBackgrounds/","SWire_Pb214",         "./Histograms_ExtEG.root");
  addHistogramToFile("RadonBackgrounds/","SWire_Bi210",         "./Histograms_ExtEG.root");
  addHistogramToFile("RadonBackgrounds/","SWire_Tl208",         "./Histograms_ExtEG.root");
  addHistogramToFile("RadonBackgrounds/","SScin_Bi214",         "./Histograms_ExtEG.root");
  addHistogramToFile("RadonBackgrounds/","SScin_Pb214",         "./Histograms_ExtEG.root");
  addHistogramToFile("RadonBackgrounds/","SScin_Bi210",         "./Histograms_ExtEG.root");
  addHistogramToFile("RadonBackgrounds/","Air_Bi214",           "./Histograms_ExtEG.root");
  addHistogramToFile("RadonBackgrounds/","Air_Pb214",           "./Histograms_ExtEG.root");
  addHistogramToFile("RadonBackgrounds/","Air_Tl208",           "./Histograms_ExtEG.root");

  return 0;
}

void addHistogramToFile(string directory, string sample, string outfilename){

  cout << "Adding histograms for " << sample << "..." << endl; 

  if(std::string::npos != sample.find("SFoil") && std::string::npos != sample.find("214")){
    addHistogramToFileInOut(directory, sample, outfilename);
    return;
  }

  // Write out input file names
  string inputfile = "/unix/nemo3/users/jmott/SeleniumAnalysis/ProcessedData/Backgrounds/ExtEG/";
  inputfile.append(directory);
  if(std::string::npos != sample.find("SFoil") && std::string::npos != sample.find("210")){inputfile.append("SFoil_Bi210");}
  else {inputfile.append(sample);}
  inputfile.append("/ExtBG_Se_ExtEG_output.root");

  // Open file and get hold of branches and assign them to relevant names
  TFile* f = new TFile(inputfile.c_str(),"READ");
  string treename = "SeExtEGCuts";
  TDirectoryFile* f1 = (TDirectoryFile*)f->Get(treename.c_str());
  TTree* tree = (TTree*)f1->Get(treename.c_str());

  // Fit electron energy for ExtEG
  TH1D* hTotEnergyP1_Inner;
  TH1D* hTotEnergyP2_Inner;
  hTotEnergyP1_Inner  = new TH1D("hTotEnergyP1_Inner","Total Energy", 80, 0, 4.0);
  hTotEnergyP2_Inner  = new TH1D("hTotEnergyP2_Inner","Total Energy", 80, 0, 4.0);
  hTotEnergyP1_Inner->SetTitle(";E_{e} + E_{#gamma} / MeV; No. Events / 0.05 MeV");
  hTotEnergyP2_Inner->SetTitle(";E_{e} + E_{#gamma} / MeV; No. Events / 0.05 MeV");
  hTotEnergyP1_Inner->Sumw2();
  hTotEnergyP2_Inner->Sumw2();

  TH1D* hTotEnergyP1_Outer;
  TH1D* hTotEnergyP2_Outer;
  hTotEnergyP1_Outer  = new TH1D("hTotEnergyP1_Outer","Total Energy", 80, 0, 4.0);
  hTotEnergyP2_Outer  = new TH1D("hTotEnergyP2_Outer","Total Energy", 80, 0, 4.0);
  hTotEnergyP1_Outer->SetTitle(";E_{e} + E_{#gamma} / MeV; No. Events / 0.05 MeV");
  hTotEnergyP2_Outer->SetTitle(";E_{e} + E_{#gamma} / MeV; No. Events / 0.05 MeV");
  hTotEnergyP1_Outer->Sumw2();
  hTotEnergyP2_Outer->Sumw2();

  TH1D* hTotEnergyP1_Petal;
  TH1D* hTotEnergyP2_Petal;
  hTotEnergyP1_Petal  = new TH1D("hTotEnergyP1_Petal","Total Energy", 40, 0, 4.0);
  hTotEnergyP2_Petal  = new TH1D("hTotEnergyP2_Petal","Total Energy", 40, 0, 4.0);
  hTotEnergyP1_Petal->SetTitle(";E_{e} + E_{#gamma} / MeV; No. Events / 0.1 MeV");
  hTotEnergyP2_Petal->SetTitle(";E_{e} + E_{#gamma} / MeV; No. Events / 0.1 MeV");
  hTotEnergyP1_Petal->Sumw2();
  hTotEnergyP2_Petal->Sumw2();

  int run, foilSide, vertexLocation, entryPoint;
  double electronEnergy, gammaEnergy, radonWeight, bi210Weight, trackLength, trackSign;
  double trueVertexZ, trueVertexSector, eventTime;

  tree->SetBranchAddress("b_run", &run);
  tree->SetBranchAddress("b_electronEnergy", &electronEnergy);
  tree->SetBranchAddress("b_gammaEnergy", &gammaEnergy);
  tree->SetBranchAddress("b_radonWeight", &radonWeight);
  tree->SetBranchAddress("b_bi210Weight", &bi210Weight);
  tree->SetBranchAddress("b_foilSide", &foilSide);
  tree->SetBranchAddress("b_trackLength", &trackLength);
  tree->SetBranchAddress("b_trackSign", &trackSign);
  tree->SetBranchAddress("b_vertexLocation", &vertexLocation);
  tree->SetBranchAddress("b_trueVertexSector", &trueVertexSector);
  tree->SetBranchAddress("b_trueVertexZ", &trueVertexZ);
  tree->SetBranchAddress("b_eventTime", &eventTime);
  tree->SetBranchAddress("b_entryPoint", &entryPoint);
 
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
      if(entryPoint == 0){
	if(run < 3396){
	  hTotEnergyP1_Inner->Fill(electronEnergy+gammaEnergy,radWeight);
	} else {
	  hTotEnergyP2_Inner->Fill(electronEnergy+gammaEnergy,radWeight);
	}
      } else if (entryPoint == 1){
	if(run < 3396){
	  hTotEnergyP1_Outer->Fill(electronEnergy+gammaEnergy,radWeight);
	} else {
	  hTotEnergyP2_Outer->Fill(electronEnergy+gammaEnergy,radWeight);
	}
      } else {
	if(run < 3396){
	  hTotEnergyP1_Petal->Fill(electronEnergy+gammaEnergy,radWeight);
	} else {
	  hTotEnergyP2_Petal->Fill(electronEnergy+gammaEnergy,radWeight);
	}
      }
    }
  }

  TFile* outfile = new TFile(outfilename.c_str(),"UPDATE");
  char histname[200];

  string sampleP1_Inner = sample + std::string("_P1_Inner");
  strcpy(histname,"hTotEnergy_");
  TH1D *hTotEnergyP1_Inner_Clone = (TH1D*)hTotEnergyP1_Inner->Clone(strcat(histname,sampleP1_Inner.c_str()));
  hTotEnergyP1_Inner_Clone->Write();

  string sampleP2_Inner = sample + std::string("_P2_Inner");
  strcpy(histname,"hTotEnergy_");
  TH1D *hTotEnergyP2_Inner_Clone = (TH1D*)hTotEnergyP2_Inner->Clone(strcat(histname,sampleP2_Inner.c_str()));
  hTotEnergyP2_Inner_Clone->Write();

  string sampleP1_Outer = sample + std::string("_P1_Outer");
  strcpy(histname,"hTotEnergy_");
  TH1D *hTotEnergyP1_Outer_Clone = (TH1D*)hTotEnergyP1_Outer->Clone(strcat(histname,sampleP1_Outer.c_str()));
  hTotEnergyP1_Outer_Clone->Write();

  string sampleP2_Outer = sample + std::string("_P2_Outer");
  strcpy(histname,"hTotEnergy_");
  TH1D *hTotEnergyP2_Outer_Clone = (TH1D*)hTotEnergyP2_Outer->Clone(strcat(histname,sampleP2_Outer.c_str()));
  hTotEnergyP2_Outer_Clone->Write();

  string sampleP1_Petal = sample + std::string("_P1_Petal");
  strcpy(histname,"hTotEnergy_");
  TH1D *hTotEnergyP1_Petal_Clone = (TH1D*)hTotEnergyP1_Petal->Clone(strcat(histname,sampleP1_Petal.c_str()));
  hTotEnergyP1_Petal_Clone->Write();

  string sampleP2_Petal = sample + std::string("_P2_Petal");
  strcpy(histname,"hTotEnergy_");
  TH1D *hTotEnergyP2_Petal_Clone = (TH1D*)hTotEnergyP2_Petal->Clone(strcat(histname,sampleP2_Petal.c_str()));
  hTotEnergyP2_Petal_Clone->Write();

  outfile->Close();
  delete outfile;

  delete hTotEnergyP1_Inner;
  delete hTotEnergyP2_Inner;
  delete hTotEnergyP1_Outer;
  delete hTotEnergyP2_Outer;
  delete hTotEnergyP1_Petal;
  delete hTotEnergyP2_Petal;

  f->Close("R");
  delete f;

}

void addHistogramToFileInOut(string directory, string sample, string outfilename){

  // Write out input file names
  string inputfile = "/unix/nemo3/users/jmott/SeleniumAnalysis/ProcessedData/Backgrounds/ExtEG/";
  inputfile.append(directory);
  inputfile.append(sample);
  inputfile.append("/ExtBG_Se_ExtEG_output.root");

  // Open file and get hold of branches and assign them to relevant names
  TFile* f = new TFile(inputfile.c_str(),"READ");
  string treename = "SeExtEGCuts";
  TDirectoryFile* f1 = (TDirectoryFile*)f->Get(treename.c_str());
  TTree* tree = (TTree*)f1->Get(treename.c_str());

  // Fit electron energy for ExtEG
  TH1D* hTotEnergyP1_In_Inner;
  TH1D* hTotEnergyP2_In_Inner;
  hTotEnergyP1_In_Inner  = new TH1D("hTotEnergyP1_In_Inner","Total Energy", 80, 0, 4.0);
  hTotEnergyP2_In_Inner  = new TH1D("hTotEnergyP2_In_Inner","Total Energy", 80, 0, 4.0);
  hTotEnergyP1_In_Inner->SetTitle(";E_{e} + E_{#gamma} / MeV; No. Events / 0.05 MeV");
  hTotEnergyP2_In_Inner->SetTitle(";E_{e} + E_{#gamma} / MeV; No. Events / 0.05 MeV");
  hTotEnergyP1_In_Inner->Sumw2();
  hTotEnergyP2_In_Inner->Sumw2();

  TH1D* hTotEnergyP1_Out_Inner;
  TH1D* hTotEnergyP2_Out_Inner;
  hTotEnergyP1_Out_Inner  = new TH1D("hTotEnergyP1_Out_Inner","Total Energy", 80, 0, 4.0);
  hTotEnergyP2_Out_Inner  = new TH1D("hTotEnergyP2_Out_Inner","Total Energy", 80, 0, 4.0);
  hTotEnergyP1_Out_Inner->SetTitle(";E_{e} + E_{#gamma} / MeV; No. Events / 0.05 MeV");
  hTotEnergyP2_Out_Inner->SetTitle(";E_{e} + E_{#gamma} / MeV; No. Events / 0.05 MeV");
  hTotEnergyP1_Out_Inner->Sumw2();
  hTotEnergyP2_Out_Inner->Sumw2();

  TH1D* hTotEnergyP1_In_Outer;
  TH1D* hTotEnergyP2_In_Outer;
  hTotEnergyP1_In_Outer  = new TH1D("hTotEnergyP1_In_Outer","Total Energy", 80, 0, 4.0);
  hTotEnergyP2_In_Outer  = new TH1D("hTotEnergyP2_In_Outer","Total Energy", 80, 0, 4.0);
  hTotEnergyP1_In_Outer->SetTitle(";E_{e} + E_{#gamma} / MeV; No. Events / 0.05 MeV");
  hTotEnergyP2_In_Outer->SetTitle(";E_{e} + E_{#gamma} / MeV; No. Events / 0.05 MeV");
  hTotEnergyP1_In_Outer->Sumw2();
  hTotEnergyP2_In_Outer->Sumw2();

  TH1D* hTotEnergyP1_Out_Outer;
  TH1D* hTotEnergyP2_Out_Outer;
  hTotEnergyP1_Out_Outer  = new TH1D("hTotEnergyP1_Out_Outer","Total Energy", 80, 0, 4.0);
  hTotEnergyP2_Out_Outer  = new TH1D("hTotEnergyP2_Out_Outer","Total Energy", 80, 0, 4.0);
  hTotEnergyP1_Out_Outer->SetTitle(";E_{e} + E_{#gamma} / MeV; No. Events / 0.05 MeV");
  hTotEnergyP2_Out_Outer->SetTitle(";E_{e} + E_{#gamma} / MeV; No. Events / 0.05 MeV");
  hTotEnergyP1_Out_Outer->Sumw2();
  hTotEnergyP2_Out_Outer->Sumw2();

  TH1D* hTotEnergyP1_In_Petal;
  TH1D* hTotEnergyP2_In_Petal;
  hTotEnergyP1_In_Petal  = new TH1D("hTotEnergyP1_In_Petal","Total Energy", 40, 0, 4.0);
  hTotEnergyP2_In_Petal  = new TH1D("hTotEnergyP2_In_Petal","Total Energy", 40, 0, 4.0);
  hTotEnergyP1_In_Petal->SetTitle(";E_{e} + E_{#gamma} / MeV; No. Events / 0.1 MeV");
  hTotEnergyP2_In_Petal->SetTitle(";E_{e} + E_{#gamma} / MeV; No. Events / 0.1 MeV");
  hTotEnergyP1_In_Petal->Sumw2();
  hTotEnergyP2_In_Petal->Sumw2();

  TH1D* hTotEnergyP1_Out_Petal;
  TH1D* hTotEnergyP2_Out_Petal;
  hTotEnergyP1_Out_Petal  = new TH1D("hTotEnergyP1_Out_Petal","Total Energy", 40, 0, 4.0);
  hTotEnergyP2_Out_Petal  = new TH1D("hTotEnergyP2_Out_Petal","Total Energy", 40, 0, 4.0);
  hTotEnergyP1_Out_Petal->SetTitle(";E_{e} + E_{#gamma} / MeV; No. Events / 0.1 MeV");
  hTotEnergyP2_Out_Petal->SetTitle(";E_{e} + E_{#gamma} / MeV; No. Events / 0.1 MeV");
  hTotEnergyP1_Out_Petal->Sumw2();
  hTotEnergyP2_Out_Petal->Sumw2();

  int run, foilSide, vertexLocation, entryPoint;
  double electronEnergy,  gammaEnergy, radonWeight, bi210Weight, trackLength, trackSign;

  tree->SetBranchAddress("b_run", &run);
  tree->SetBranchAddress("b_electronEnergy", &electronEnergy);
  tree->SetBranchAddress("b_gammaEnergy", &gammaEnergy);
  tree->SetBranchAddress("b_radonWeight", &radonWeight);
  tree->SetBranchAddress("b_bi210Weight", &bi210Weight);
  tree->SetBranchAddress("b_foilSide", &foilSide);
  tree->SetBranchAddress("b_trackLength", &trackLength);
  tree->SetBranchAddress("b_trackSign", &trackSign);
  tree->SetBranchAddress("b_vertexLocation", &vertexLocation);
  tree->SetBranchAddress("b_entryPoint", &entryPoint);
 
  Int_t N = tree->GetEntries();
  cout << "Entries = " << N << endl;

  // FILL HISTOGRAMS
  for (int iEvt = 0; iEvt < N; iEvt ++){

    if(iEvt % 500000 == 0){cout << "Processing event " << iEvt << "..." << endl;}

    tree->GetEntry(iEvt);

    double radWeight = 1;

    bool fill = true;

    if(fill){
      if(entryPoint == 0){
	if(foilSide == 0){
	  if(run < 3396){
	    hTotEnergyP1_In_Inner->Fill(electronEnergy+gammaEnergy,radWeight);
	  } else{
	    hTotEnergyP2_In_Inner->Fill(electronEnergy+gammaEnergy,radWeight);
	  }
	} else {
	  if(run < 3396){
	    hTotEnergyP1_Out_Inner->Fill(electronEnergy+gammaEnergy,radWeight);
	  } else {
	    hTotEnergyP2_Out_Inner->Fill(electronEnergy+gammaEnergy,radWeight);
	  }
	}
      } else if(entryPoint == 1){
	if(foilSide == 0){
	  if(run < 3396){
	    hTotEnergyP1_In_Outer->Fill(electronEnergy+gammaEnergy,radWeight);
	  } else{
	    hTotEnergyP2_In_Outer->Fill(electronEnergy+gammaEnergy,radWeight);
	  }
	} else {
	  if(run < 3396){
	    hTotEnergyP1_Out_Outer->Fill(electronEnergy+gammaEnergy,radWeight);
	  } else {
	    hTotEnergyP2_Out_Outer->Fill(electronEnergy+gammaEnergy,radWeight);
	  }
	}
      } else {
	if(foilSide == 0){
	  if(run < 3396){
	    hTotEnergyP1_In_Petal->Fill(electronEnergy+gammaEnergy,radWeight);
	  } else{
	    hTotEnergyP2_In_Petal->Fill(electronEnergy+gammaEnergy,radWeight);
	  }
	} else {
	  if(run < 3396){
	    hTotEnergyP1_Out_Petal->Fill(electronEnergy+gammaEnergy,radWeight);
	  } else {
	    hTotEnergyP2_Out_Petal->Fill(electronEnergy+gammaEnergy,radWeight);
	  }
	}
      }
    }
  }

  TFile* outfile = new TFile(outfilename.c_str(),"UPDATE");
  char histname[200];

  string sampleP1_In_Inner = sample + std::string("_In_P1_Inner");
  strcpy(histname,"hTotEnergy_");
  TH1D *hTotEnergyP1_In_InnerClone = (TH1D*)hTotEnergyP1_In_Inner->Clone(strcat(histname,sampleP1_In_Inner.c_str()));
  hTotEnergyP1_In_InnerClone->Write();

  string sampleP1_Out_Inner = sample + std::string("_Out_P1_Inner");
  strcpy(histname,"hTotEnergy_");
  TH1D *hTotEnergyP1_Out_InnerClone = (TH1D*)hTotEnergyP1_Out_Inner->Clone(strcat(histname,sampleP1_Out_Inner.c_str()));
  hTotEnergyP1_Out_InnerClone->Write();

  string sampleP2_In_Inner = sample + std::string("_In_P2_Inner");
  strcpy(histname,"hTotEnergy_");
  TH1D *hTotEnergyP2_In_InnerClone = (TH1D*)hTotEnergyP2_In_Inner->Clone(strcat(histname,sampleP2_In_Inner.c_str()));
  hTotEnergyP2_In_InnerClone->Write();

  string sampleP2_Out_Inner = sample + std::string("_Out_P2_Inner");
  strcpy(histname,"hTotEnergy_");
  TH1D *hTotEnergyP2_Out_InnerClone = (TH1D*)hTotEnergyP2_Out_Inner->Clone(strcat(histname,sampleP2_Out_Inner.c_str()));
  hTotEnergyP2_Out_InnerClone->Write();

  string sampleP1_In_Outer = sample + std::string("_In_P1_Outer");
  strcpy(histname,"hTotEnergy_");
  TH1D *hTotEnergyP1_In_OuterClone = (TH1D*)hTotEnergyP1_In_Outer->Clone(strcat(histname,sampleP1_In_Outer.c_str()));
  hTotEnergyP1_In_OuterClone->Write();

  string sampleP1_Out_Outer = sample + std::string("_Out_P1_Outer");
  strcpy(histname,"hTotEnergy_");
  TH1D *hTotEnergyP1_Out_OuterClone = (TH1D*)hTotEnergyP1_Out_Outer->Clone(strcat(histname,sampleP1_Out_Outer.c_str()));
  hTotEnergyP1_Out_OuterClone->Write();

  string sampleP2_In_Outer = sample + std::string("_In_P2_Outer");
  strcpy(histname,"hTotEnergy_");
  TH1D *hTotEnergyP2_In_OuterClone = (TH1D*)hTotEnergyP2_In_Outer->Clone(strcat(histname,sampleP2_In_Outer.c_str()));
  hTotEnergyP2_In_OuterClone->Write();

  string sampleP2_Out_Outer = sample + std::string("_Out_P2_Outer");
  strcpy(histname,"hTotEnergy_");
  TH1D *hTotEnergyP2_Out_OuterClone = (TH1D*)hTotEnergyP2_Out_Outer->Clone(strcat(histname,sampleP2_Out_Outer.c_str()));
  hTotEnergyP2_Out_OuterClone->Write();

  string sampleP1_In_Petal = sample + std::string("_In_P1_Petal");
  strcpy(histname,"hTotEnergy_");
  TH1D *hTotEnergyP1_In_PetalClone = (TH1D*)hTotEnergyP1_In_Petal->Clone(strcat(histname,sampleP1_In_Petal.c_str()));
  hTotEnergyP1_In_PetalClone->Write();

  string sampleP1_Out_Petal = sample + std::string("_Out_P1_Petal");
  strcpy(histname,"hTotEnergy_");
  TH1D *hTotEnergyP1_Out_PetalClone = (TH1D*)hTotEnergyP1_Out_Petal->Clone(strcat(histname,sampleP1_Out_Petal.c_str()));
  hTotEnergyP1_Out_PetalClone->Write();

  string sampleP2_In_Petal = sample + std::string("_In_P2_Petal");
  strcpy(histname,"hTotEnergy_");
  TH1D *hTotEnergyP2_In_PetalClone = (TH1D*)hTotEnergyP2_In_Petal->Clone(strcat(histname,sampleP2_In_Petal.c_str()));
  hTotEnergyP2_In_PetalClone->Write();

  string sampleP2_Out_Petal = sample + std::string("_Out_P2_Petal");
  strcpy(histname,"hTotEnergy_");
  TH1D *hTotEnergyP2_Out_PetalClone = (TH1D*)hTotEnergyP2_Out_Petal->Clone(strcat(histname,sampleP2_Out_Petal.c_str()));
  hTotEnergyP2_Out_PetalClone->Write();

  outfile->Close();
  delete outfile;

  delete hTotEnergyP1_In_Inner;
  delete hTotEnergyP2_In_Inner;
  delete hTotEnergyP1_Out_Inner;
  delete hTotEnergyP2_Out_Inner;
  delete hTotEnergyP1_In_Outer;
  delete hTotEnergyP2_In_Outer;
  delete hTotEnergyP1_Out_Outer;
  delete hTotEnergyP2_Out_Outer;
  delete hTotEnergyP1_In_Petal;
  delete hTotEnergyP2_In_Petal;
  delete hTotEnergyP1_Out_Petal;
  delete hTotEnergyP2_Out_Petal;

  f->Close("R");
  delete f;

}



