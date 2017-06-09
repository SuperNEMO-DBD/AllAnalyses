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

void addHistogramToFile(string directory, string sample, string outfilename);
void addHistogramToFileP1P2(string directory, string sample, string outfilename);
void addHistogramToFileInOutP1P2(string directory, string sample, string outfilename);

Int_t createHistograms_2b2n(){
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
  TFile* outfile = new TFile("./Histograms_2b2n.root","RECREATE");
  outfile->Close();
  delete outfile;

  // Add Data Histogram
  addHistogramToFile("Data/","Data","./Histograms_2b2n.root");
  addHistogramToFile("Data/","Data_Neutrons","./Histograms_2b2n.root");

  // Add Signal Histograms
  addHistogramToFile("Signal/","2b2n","./Histograms_2b2n.root");
  addHistogramToFile("Signal/","2b0n_m1","./Histograms_2b2n.root");

  // Add different Internal MC samples
  addHistogramToFile("InternalBackgrounds/","SeNew_Ac228", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Bi212", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Bi214", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_K40",   "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Pa234m","./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Pb211", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Pb214", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Tl207", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Tl208", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Ac228", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Bi212", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Bi214", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_K40",   "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Pa234m","./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Pb211", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Pb214", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Tl207", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Tl208", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","Mylar_Bi214", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","Mylar_Pb214", "./Histograms_2b2n.root");

  // Add different External MC samples
  addHistogramToFile("ExternalBackgrounds/","PMT_K40",          "./Histograms_2b2n.root");
  addHistogramToFile("ExternalBackgrounds/","PMT_Bi214",        "./Histograms_2b2n.root");
  addHistogramToFile("ExternalBackgrounds/","PMT_Tl208",        "./Histograms_2b2n.root");
  addHistogramToFile("ExternalBackgrounds/","PMT_Ac228",        "./Histograms_2b2n.root");
  addHistogramToFile("ExternalBackgrounds/","MuMetal_Co60",     "./Histograms_2b2n.root");
  addHistogramToFile("ExternalBackgrounds/","CuPetals_Co60",    "./Histograms_2b2n.root");
  addHistogramToFile("ExternalBackgrounds/","CuTower_Co60",     "./Histograms_2b2n.root");
  addHistogramToFile("ExternalBackgrounds/","FeShield_Tl208",   "./Histograms_2b2n.root");
  addHistogramToFile("ExternalBackgrounds/","FeShield_Bi214",   "./Histograms_2b2n.root");
  addHistogramToFile("ExternalBackgrounds/","FeShield_Ac228",   "./Histograms_2b2n.root");
  addHistogramToFile("ExternalBackgrounds/","ScintInn_K40",     "./Histograms_2b2n.root");
  addHistogramToFile("ExternalBackgrounds/","ScintOut_K40",     "./Histograms_2b2n.root");
  addHistogramToFile("ExternalBackgrounds/","ScintPet_K40",     "./Histograms_2b2n.root");
  addHistogramToFile("ExternalBackgrounds/","SteelFrame_K40",   "./Histograms_2b2n.root");
  addHistogramToFile("ExternalBackgrounds/","SteelFrame_Bi214", "./Histograms_2b2n.root");
  addHistogramToFile("ExternalBackgrounds/","SteelFrame_Tl208", "./Histograms_2b2n.root");
  addHistogramToFile("ExternalBackgrounds/","SteelFrame_Ac228", "./Histograms_2b2n.root");
  addHistogramToFile("ExternalBackgrounds/","SteelFrame_Co60",  "./Histograms_2b2n.root");
  addHistogramToFile("ExternalBackgrounds/","MuMetal_g1000",    "./Histograms_2b2n.root");
  addHistogramToFile("ExternalBackgrounds/","SScin_Pa234m",     "./Histograms_2b2n.root");

  // Add different radon MC samples
  addHistogramToFile("RadonBackgrounds/","SFoil_Bi214",         "./Histograms_2b2n.root");
  addHistogramToFile("RadonBackgrounds/","SFoil_Pb214",         "./Histograms_2b2n.root");
  addHistogramToFile("RadonBackgrounds/","SFoil_SeNew_Bi210",   "./Histograms_2b2n.root");
  addHistogramToFile("RadonBackgrounds/","SFoil_SeOld_Bi210",   "./Histograms_2b2n.root");
  addHistogramToFile("RadonBackgrounds/","SFoil_Strip_Bi210",   "./Histograms_2b2n.root");
  addHistogramToFile("RadonBackgrounds/","SWire_Bi214",         "./Histograms_2b2n.root");
  addHistogramToFile("RadonBackgrounds/","SWire_Pb214",         "./Histograms_2b2n.root");
  addHistogramToFile("RadonBackgrounds/","SWire_Bi210",         "./Histograms_2b2n.root");
  addHistogramToFile("RadonBackgrounds/","SWire_Tl208",         "./Histograms_2b2n.root");
  addHistogramToFile("RadonBackgrounds/","SScin_Bi214",         "./Histograms_2b2n.root");
  addHistogramToFile("RadonBackgrounds/","SScin_Pb214",         "./Histograms_2b2n.root");
  addHistogramToFile("RadonBackgrounds/","SScin_Bi210",         "./Histograms_2b2n.root");
  addHistogramToFile("RadonBackgrounds/","Air_Bi214",           "./Histograms_2b2n.root");
  addHistogramToFile("RadonBackgrounds/","Air_Pb214",           "./Histograms_2b2n.root");
  addHistogramToFile("RadonBackgrounds/","Air_Tl208",           "./Histograms_2b2n.root");

  return 0;
}

void addHistogramToFile(string directory, string sample, string outfilename){

  cout << "Adding histograms for " << sample << "..." << endl; 

  if((std::string::npos != sample.find("SWire") || std::string::npos != sample.find("SFoil") || std::string::npos != sample.find("SScin") || std::string::npos != sample.find("Air") || std::string::npos != sample.find("g1000") || std::string::npos != sample.find("Neutrons"))&&!(std::string::npos != sample.find("SScin_Pa234m"))){
    addHistogramToFileP1P2(directory,sample,outfilename);
    return;
  }

  // Create histograms that are wanted
  TH1D* hTotEnergy       = new TH1D("hTotEnergy","Total Electron Energy", 35, 0, 3.5);
  hTotEnergy->Sumw2();
  hTotEnergy->SetTitle(";E_{1} + E_{2} / MeV; No. Events / 0.1 MeV");

  // Write out input file name
  string inputfile = "/unix/nemo3/users/jmott/SeleniumAnalysis/ProcessedData/Signal/2b2n/";
  inputfile.append(directory);
  inputfile.append(sample);
  inputfile.append("/Sig_Se_2b2n_output.root");

  // Open file and get hold of branches and assign them to relevant names
  TFile* f = new TFile(inputfile.c_str(),"READ");
  TTree* tree = (TTree*)f->Get("Se2b2nCuts");
 
  int run, nNACaloHits, scintLocation[2];
  double energy[2], trackLength[2], trackSign[2], probInt, probExt, cosTheta, cosThetaWeight, vertexR, vertexZ, vertexSector, radonWeight, bi210Weight, totGammaEnergy, eventTime, gammaEnergy[10];

  tree->SetBranchAddress("b_run", &run);
  tree->SetBranchAddress("b_energy", &energy);
  tree->SetBranchAddress("b_trackLength", &trackLength);
  tree->SetBranchAddress("b_trackSign", &trackSign);
  tree->SetBranchAddress("b_probInt", &probInt);
  tree->SetBranchAddress("b_probExt", &probExt);
  tree->SetBranchAddress("b_cosTheta", &cosTheta);
  tree->SetBranchAddress("b_cosThetaWeight", &cosThetaWeight);
  tree->SetBranchAddress("b_vertexR", &vertexR);
  tree->SetBranchAddress("b_vertexZ", &vertexZ);
  tree->SetBranchAddress("b_vertexSector", &vertexSector);
  tree->SetBranchAddress("b_radonWeight", &radonWeight);
  tree->SetBranchAddress("b_bi210Weight", &bi210Weight);
  tree->SetBranchAddress("b_nNACaloHits", &nNACaloHits);
  tree->SetBranchAddress("b_totGammaEnergy", &totGammaEnergy);
  tree->SetBranchAddress("b_scintLocation", &scintLocation);
  tree->SetBranchAddress("b_eventTime", &eventTime);
  tree->SetBranchAddress("b_gammaEnergy", &gammaEnergy);

  Int_t N = tree->GetEntries();
  cout << "Entries = " << N << endl;

  // FILL HISTOGRAMS
  for (int iEvt = 0; iEvt < N; iEvt ++){
    if(iEvt % 500000 == 0){cout << "Processing Event " << iEvt << "..." << endl;}
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

    // Take into account half-lives for Bi210 and Co60
    if(std::string::npos != sample.find("Bi210")){
      radWeight *= exp(-(log(2)/(22.3*365.25*86400.0))*eventTime);
    }
    if(std::string::npos != sample.find("Co60")){
      radWeight *= exp(-(log(2)/(1925.2*86400.0))*eventTime);
    }

    bool fill = true;

    if(fill){
      hTotEnergy->Fill(energy[0]+energy[1],radWeight);;
    }
  }

  TFile* outfile = new TFile(outfilename.c_str(),"UPDATE");
  char histname[100];

  strcpy(histname,"hTotEnergy_");
  TH1D *hTotEnergyClone = (TH1D*)hTotEnergy->Clone(strcat(histname,sample.c_str()));
  hTotEnergyClone->Write();

  outfile->Close();
  delete outfile;

  delete hTotEnergy;

  f->Close("R");
  delete f;

}

void addHistogramToFileP1P2(string directory, string sample, string outfilename){

  // If it's got SFoil and 214 in the sample name, then break it up into in and out contributions
  if(std::string::npos != sample.find("214") && std::string::npos != sample.find("SFoil")){
    addHistogramToFileInOutP1P2(directory, sample, outfilename);
    return;
  }

  // Create histograms that are wanted
  TH1D* hTotEnergyP1       = new TH1D("hTotEnergyP1","Total Electron Energy", 35, 0, 3.5);
  TH1D* hTotEnergyP2       = new TH1D("hTotEnergyP2","Total Electron Energy", 35, 0, 3.5);
  hTotEnergyP1->Sumw2();
  hTotEnergyP2->Sumw2();

  hTotEnergyP1->SetTitle(";E_{1} + E_{2} / MeV; No. Events / 0.1 MeV");
  hTotEnergyP2->SetTitle(";E_{1} + E_{2} / MeV; No. Events / 0.1 MeV");

  // Write out input file name
  string inputfile = "/unix/nemo3/users/jmott/SeleniumAnalysis/ProcessedData/Signal/2b2n/";
  inputfile.append(directory);
  if(std::string::npos != sample.find("SFoil") && std::string::npos != sample.find("210")){inputfile.append("SFoil_Bi210");}
  else {inputfile.append(sample);}
  inputfile.append("/Sig_Se_2b2n_output.root");

  // Open file and get hold of branches and assign them to relevant names
  TFile* f = new TFile(inputfile.c_str(),"READ");
  TTree* tree = (TTree*)f->Get("Se2b2nCuts");
 
  int run, nNACaloHits, vertexLocation, scintLocation[2];
  double energy[2], trackLength[2], trackSign[2], probInt, probExt, cosTheta, cosThetaWeight, vertexR, vertexZ, vertexSector, trueVertexZ, trueVertexSector, radonWeight, bi210Weight, totGammaEnergy, eventTime, gammaEnergy[10];

  tree->SetBranchAddress("b_run", &run);
  tree->SetBranchAddress("b_energy", &energy);
  tree->SetBranchAddress("b_trackLength", &trackLength);
  tree->SetBranchAddress("b_trackSign", &trackSign);
  tree->SetBranchAddress("b_probInt", &probInt);
  tree->SetBranchAddress("b_probExt", &probExt);
  tree->SetBranchAddress("b_cosTheta", &cosTheta);
  tree->SetBranchAddress("b_cosThetaWeight", &cosThetaWeight);
  tree->SetBranchAddress("b_vertexR", &vertexR);
  tree->SetBranchAddress("b_vertexZ", &vertexZ);
  tree->SetBranchAddress("b_vertexSector", &vertexSector);
  tree->SetBranchAddress("b_radonWeight", &radonWeight);
  tree->SetBranchAddress("b_bi210Weight", &bi210Weight);
  tree->SetBranchAddress("b_nNACaloHits", &nNACaloHits);
  tree->SetBranchAddress("b_totGammaEnergy", &totGammaEnergy);
  tree->SetBranchAddress("b_vertexLocation", &vertexLocation);
  tree->SetBranchAddress("b_trueVertexZ", &trueVertexZ);
  tree->SetBranchAddress("b_trueVertexSector", &trueVertexSector);
  tree->SetBranchAddress("b_scintLocation", &scintLocation);
  tree->SetBranchAddress("b_eventTime", &eventTime);
  tree->SetBranchAddress("b_gammaEnergy", &gammaEnergy);

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

    // Take into account half-lives for Bi210 and Co60
    if(std::string::npos != sample.find("Bi210")){
      radWeight *= exp(-(log(2)/(22.3*365.25*86400.0))*eventTime);
    }
    if(std::string::npos != sample.find("Co60")){
      radWeight *= exp(-(log(2)/(1925.2*86400.0))*eventTime);
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
      if(run < 3396){
	hTotEnergyP1->Fill(energy[0]+energy[1],radWeight);
      }
      else if(run > 3395){
	hTotEnergyP2->Fill(energy[0]+energy[1],radWeight);
      }
    }

  }

  TFile* outfile = new TFile(outfilename.c_str(),"UPDATE");
  char histname[100];

  string sampleP1 = sample + std::string("_P1");
  strcpy(histname,"hTotEnergy_");
  TH1D *hTotEnergyP1Clone = (TH1D*)hTotEnergyP1->Clone(strcat(histname,sampleP1.c_str()));
  hTotEnergyP1Clone->Write();

  string sampleP2 = sample + std::string("_P2");
  strcpy(histname,"hTotEnergy_");
  TH1D *hTotEnergyP2Clone = (TH1D*)hTotEnergyP2->Clone(strcat(histname,sampleP2.c_str()));
  hTotEnergyP2Clone->Write();

  outfile->Close();
  delete outfile;

  delete hTotEnergyP1;
  delete hTotEnergyP2;

  f->Close("R");
  delete f;

}

void addHistogramToFileInOutP1P2(string directory, string sample, string outfilename){

  // Create histograms that are wanted
  TH1D* hTotEnergyIn_P1       = new TH1D("hTotEnergyIn_P1","Total Electron Energy", 35, 0, 3.5);
  TH1D* hTotEnergyOut_P1       = new TH1D("hTotEnergyOut_P1","Total Electron Energy", 35, 0, 3.5);
  TH1D* hTotEnergyIn_P2       = new TH1D("hTotEnergyIn_P2","Total Electron Energy", 35, 0, 3.5);
  TH1D* hTotEnergyOut_P2       = new TH1D("hTotEnergyOut_P2","Total Electron Energy", 35, 0, 3.5);

  hTotEnergyIn_P1->Sumw2();
  hTotEnergyOut_P1->Sumw2();
  hTotEnergyIn_P2->Sumw2();
  hTotEnergyOut_P2->Sumw2();

  hTotEnergyIn_P1->SetTitle(";E_{1} + E_{2} / MeV; No. Events / 0.1 MeV");
  hTotEnergyOut_P1->SetTitle(";E_{1} + E_{2} / MeV; No. Events / 0.1 MeV");
  hTotEnergyIn_P2->SetTitle(";E_{1} + E_{2} / MeV; No. Events / 0.1 MeV");
  hTotEnergyOut_P2->SetTitle(";E_{1} + E_{2} / MeV; No. Events / 0.1 MeV");

  // Write out input file name
  string inputfile = "/unix/nemo3/users/jmott/SeleniumAnalysis/ProcessedData/Signal/2b2n/";
  inputfile.append(directory);
  inputfile.append(sample);
  inputfile.append("/Sig_Se_2b2n_output.root");

  // Open file and get hold of branches and assign them to relevant names
  TFile* f = new TFile(inputfile.c_str(),"READ");
  TTree* tree = (TTree*)f->Get("Se2b2nCuts");
 
  int run, nNACaloHits, vertexLocation, foilSide, scintLocation[2];
  double energy[2], trackLength[2], trackSign[2], probInt, probExt, cosTheta, cosThetaWeight, vertexR, vertexZ, vertexSector, radonWeight, bi210Weight, totGammaEnergy, gammaEnergy[10];

  tree->SetBranchAddress("b_run", &run);
  tree->SetBranchAddress("b_energy", &energy);
  tree->SetBranchAddress("b_trackLength", &trackLength);
  tree->SetBranchAddress("b_trackSign", &trackSign);
  tree->SetBranchAddress("b_probInt", &probInt);
  tree->SetBranchAddress("b_probExt", &probExt);
  tree->SetBranchAddress("b_cosTheta", &cosTheta);
  tree->SetBranchAddress("b_cosThetaWeight", &cosThetaWeight);
  tree->SetBranchAddress("b_vertexR", &vertexR);
  tree->SetBranchAddress("b_vertexZ", &vertexZ);
  tree->SetBranchAddress("b_vertexSector", &vertexSector);
  tree->SetBranchAddress("b_radonWeight", &radonWeight);
  tree->SetBranchAddress("b_bi210Weight", &bi210Weight);
  tree->SetBranchAddress("b_nNACaloHits", &nNACaloHits);
  tree->SetBranchAddress("b_totGammaEnergy", &totGammaEnergy);
  tree->SetBranchAddress("b_vertexLocation", &vertexLocation);
  tree->SetBranchAddress("b_foilSide", &foilSide);
  tree->SetBranchAddress("b_scintLocation", &scintLocation);
  tree->SetBranchAddress("b_gammaEnergy", &gammaEnergy);

  Int_t N = tree->GetEntries();
  cout << "Entries = " << N << endl;

  // FILL HISTOGRAMS
  for (int iEvt = 0; iEvt < N; iEvt ++){

    tree->GetEntry(iEvt);

    double radWeight = 1;

    bool fill = true;

    if(fill){
      if (run < 3396){
	if(foilSide == 0){hTotEnergyIn_P1->Fill(energy[0]+energy[1],radWeight);}
	else {hTotEnergyOut_P1->Fill(energy[0]+energy[1],radWeight);}
      } else if(run >= 3396){
	if(foilSide == 0){hTotEnergyIn_P2->Fill(energy[0]+energy[1],radWeight);}
	else {hTotEnergyOut_P2->Fill(energy[0]+energy[1],radWeight);}
      }
    }

  }

  TFile* outfile = new TFile(outfilename.c_str(),"UPDATE");
  char histname[100];

  string sampleIn_P1 = sample + std::string("_In_P1");
  strcpy(histname,"hTotEnergy_");
  TH1D *hTotEnergyIn_P1Clone = (TH1D*)hTotEnergyIn_P1->Clone(strcat(histname,sampleIn_P1.c_str()));
  hTotEnergyIn_P1Clone->Write();

  string sampleOut_P1 = sample + std::string("_Out_P1");
  strcpy(histname,"hTotEnergy_");
  TH1D *hTotEnergyOut_P1Clone = (TH1D*)hTotEnergyOut_P1->Clone(strcat(histname,sampleOut_P1.c_str()));
  hTotEnergyOut_P1Clone->Write();

  string sampleIn_P2 = sample + std::string("_In_P2");
  strcpy(histname,"hTotEnergy_");
  TH1D *hTotEnergyIn_P2Clone = (TH1D*)hTotEnergyIn_P2->Clone(strcat(histname,sampleIn_P2.c_str()));
  hTotEnergyIn_P2Clone->Write();

  string sampleOut_P2 = sample + std::string("_Out_P2");
  strcpy(histname,"hTotEnergy_");
  TH1D *hTotEnergyOut_P2Clone = (TH1D*)hTotEnergyOut_P2->Clone(strcat(histname,sampleOut_P2.c_str()));
  hTotEnergyOut_P2Clone->Write();

  outfile->Close();
  delete outfile;

  delete hTotEnergyIn_P1;
  delete hTotEnergyOut_P1;
  delete hTotEnergyIn_P2;
  delete hTotEnergyOut_P2;

  f->Close("R");
  delete f;

}
