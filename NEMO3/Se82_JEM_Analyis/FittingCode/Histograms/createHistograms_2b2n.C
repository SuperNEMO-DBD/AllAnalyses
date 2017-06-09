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
  addHistogramToFile("Signal/","2b2n_SeNew","./Histograms_2b2n.root");
  addHistogramToFile("Signal/","2b2n_SeOld","./Histograms_2b2n.root");
  addHistogramToFile("Signal/","2b2n_SeNew_SSD","./Histograms_2b2n.root");
  addHistogramToFile("Signal/","2b2n_SeOld_SSD","./Histograms_2b2n.root");
  //  addHistogramToFile("Signal/","2b0n_m1","./Histograms_2b2n.root");

  // Add different Internal MC samples
  addHistogramToFile("InternalBackgrounds/","SeNew_Ac228", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Bi212", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Bi214", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_K40",   "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Pa234m","./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Pa234m_OldGenBB","./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Pb211", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Pb214", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Tl207", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Tl208", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Sr90", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeNew_Y90", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Ac228", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Bi212", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Bi214", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_K40",   "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Pa234m","./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Pa234m_OldGenBB","./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Pb211", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Pb214", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Tl207", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Tl208", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Sr90", "./Histograms_2b2n.root");
  addHistogramToFile("InternalBackgrounds/","SeOld_Y90", "./Histograms_2b2n.root");
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
  TH1D* hTotEnergySeOld       = new TH1D("hTotEnergySeOld","Total Electron Energy", 35, 0, 3.5);
  TH1D* hTotEnergySeNew       = new TH1D("hTotEnergySeNew","Total Electron Energy", 35, 0, 3.5);
  hTotEnergySeOld->Sumw2();
  hTotEnergySeNew->Sumw2();
  hTotEnergySeOld->SetTitle(";E_{1} + E_{2} / MeV; No. Events / 0.1 MeV");
  hTotEnergySeNew->SetTitle(";E_{1} + E_{2} / MeV; No. Events / 0.1 MeV");

  TH1D* hSingleEnergySeOld       = new TH1D("hSingleEnergySeOld","Single Electron Energy", 25, 0, 2.5);
  TH1D* hSingleEnergySeNew       = new TH1D("hSingleEnergySeNew","Single Electron Energy", 25, 0, 2.5);
  hSingleEnergySeOld->Sumw2();
  hSingleEnergySeNew->Sumw2();
  hSingleEnergySeOld->SetTitle(";E_{e} / MeV; No. Events / 0.1 MeV");
  hSingleEnergySeNew->SetTitle(";E_{e} / MeV; No. Events / 0.1 MeV");

  TH1D* hMinEnergySeOld       = new TH1D("hMinEnergySeOld","Min Electron Energy", 25, 0, 2.5);
  TH1D* hMinEnergySeNew       = new TH1D("hMinEnergySeNew","Min Electron Energy", 25, 0, 2.5);
  hMinEnergySeOld->Sumw2();
  hMinEnergySeNew->Sumw2();
  hMinEnergySeOld->SetTitle(";Min E_{e} / MeV; No. Events / 0.1 MeV");
  hMinEnergySeNew->SetTitle(";Min E_{e} / MeV; No. Events / 0.1 MeV");

  TH1D* hMaxEnergySeOld       = new TH1D("hMaxEnergySeOld","Max Electron Energy", 25, 0, 2.5);
  TH1D* hMaxEnergySeNew       = new TH1D("hMaxEnergySeNew","Max Electron Energy", 25, 0, 2.5);
  hMaxEnergySeOld->Sumw2();
  hMaxEnergySeNew->Sumw2();
  hMaxEnergySeOld->SetTitle(";Max E_{e} / MeV; No. Events / 0.1 MeV");
  hMaxEnergySeNew->SetTitle(";Max E_{e} / MeV; No. Events / 0.1 MeV");

  // Write out input file name
  string inputfile = "/unix/nemo3/users/jmott/SeleniumAnalysis/ProcessedData/Signal/2b2n/";
  inputfile.append(directory);
  if(std::string::npos != sample.find("SSD")){inputfile.append("2b2n_SSD");}
  else if(std::string::npos != sample.find("2b2n_Se")){inputfile.append("2b2n");}
  else {inputfile.append(sample);}
  inputfile.append("/Sig_Se_2b2n_output.root");

  // Open file and get hold of branches and assign them to relevant names
  TFile* f = new TFile(inputfile.c_str(),"READ");
  TObject* obj = f->Get("Se2b2nCuts");
  string treeName = obj->InheritsFrom("TDirectory") ? "Se2b2nCuts/Se2b2nCuts" : "Se2b2nCuts";
  TTree* tree = (TTree*)f->Get(treeName.c_str());
 
  int run, nNACaloHits, vertexLocation, scintLocation[2], event;
  double energy[2], trackLength[2], trackSign[2], probInt, probExt, cosTheta, cosThetaWeight, vertexR, vertexZ, vertexSector, trueVertexZ, trueVertexSector, radonWeight, bi210Weight, totGammaEnergy, eventTime;
  int nGammas;
  double gammaEnergy[10];

  tree->SetBranchAddress("b_run", &run);
  tree->SetBranchAddress("b_event", &event);
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
  tree->SetBranchAddress("b_trueVertexZ", &trueVertexZ);
  tree->SetBranchAddress("b_trueVertexSector", &trueVertexSector);
  tree->SetBranchAddress("b_radonWeight", &radonWeight);
  tree->SetBranchAddress("b_bi210Weight", &bi210Weight);
  tree->SetBranchAddress("b_nNACaloHits", &nNACaloHits);
  tree->SetBranchAddress("b_totGammaEnergy", &totGammaEnergy);
  tree->SetBranchAddress("b_vertexLocation", &vertexLocation);
  tree->SetBranchAddress("b_scintLocation", &scintLocation);
  tree->SetBranchAddress("b_eventTime", &eventTime);
  tree->SetBranchAddress("b_nNACaloHits", &nGammas);
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

    // Separate out 2b2n sample based on SeOld/SeNew
    bool fill = true;
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

    if(fill){

      if(vertexLocation < 1){
	hTotEnergySeOld->Fill(energy[0]+energy[1],radWeight);
	hSingleEnergySeOld->Fill(energy[0],radWeight);
	hSingleEnergySeOld->Fill(energy[1],radWeight);
	hMinEnergySeOld->Fill(energy[0] > energy[1] ? energy[1] : energy[0],radWeight);
	hMaxEnergySeOld->Fill(energy[0] > energy[1] ? energy[0] : energy[1],radWeight);
      } else {
	hTotEnergySeNew->Fill(energy[0]+energy[1],radWeight);
	hSingleEnergySeNew->Fill(energy[0],radWeight);
	hSingleEnergySeNew->Fill(energy[1],radWeight);
	hMinEnergySeNew->Fill(energy[0] > energy[1] ? energy[1] : energy[0],radWeight);
	hMaxEnergySeNew->Fill(energy[0] > energy[1] ? energy[0] : energy[1],radWeight);
      }

    }
  }

  TFile* outfile = new TFile(outfilename.c_str(),"UPDATE");
  char histname[100];

  strcpy(histname,"hTotEnergySeOld_");
  TH1D *hTotEnergySeOldClone = (TH1D*)hTotEnergySeOld->Clone(strcat(histname,sample.c_str()));
  hTotEnergySeOldClone->Write();

  strcpy(histname,"hTotEnergySeNew_");
  TH1D *hTotEnergySeNewClone = (TH1D*)hTotEnergySeNew->Clone(strcat(histname,sample.c_str()));
  hTotEnergySeNewClone->Write();

  strcpy(histname,"hSingleEnergySeOld_");
  TH1D *hSingleEnergySeOldClone = (TH1D*)hSingleEnergySeOld->Clone(strcat(histname,sample.c_str()));
  hSingleEnergySeOldClone->Write();

  strcpy(histname,"hSingleEnergySeNew_");
  TH1D *hSingleEnergySeNewClone = (TH1D*)hSingleEnergySeNew->Clone(strcat(histname,sample.c_str()));
  hSingleEnergySeNewClone->Write();

  strcpy(histname,"hMinEnergySeOld_");
  TH1D *hMinEnergySeOldClone = (TH1D*)hMinEnergySeOld->Clone(strcat(histname,sample.c_str()));
  hMinEnergySeOldClone->Write();

  strcpy(histname,"hMinEnergySeNew_");
  TH1D *hMinEnergySeNewClone = (TH1D*)hMinEnergySeNew->Clone(strcat(histname,sample.c_str()));
  hMinEnergySeNewClone->Write();

  strcpy(histname,"hMaxEnergySeOld_");
  TH1D *hMaxEnergySeOldClone = (TH1D*)hMaxEnergySeOld->Clone(strcat(histname,sample.c_str()));
  hMaxEnergySeOldClone->Write();

  strcpy(histname,"hMaxEnergySeNew_");
  TH1D *hMaxEnergySeNewClone = (TH1D*)hMaxEnergySeNew->Clone(strcat(histname,sample.c_str()));
  hMaxEnergySeNewClone->Write();

  outfile->Close();
  delete outfile;

  delete hTotEnergySeOld;
  delete hTotEnergySeNew;

  delete hSingleEnergySeOld;
  delete hSingleEnergySeNew;

  delete hMinEnergySeOld;
  delete hMinEnergySeNew;

  delete hMaxEnergySeOld;
  delete hMaxEnergySeNew;

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
  TH1D* hTotEnergySeOldP1       = new TH1D("hTotEnergySeOldP1","Total Electron Energy", 35, 0, 3.5);
  TH1D* hTotEnergySeOldP2       = new TH1D("hTotEnergySeOldP2","Total Electron Energy", 35, 0, 3.5);
  TH1D* hTotEnergySeNewP1       = new TH1D("hTotEnergySeNewP1","Total Electron Energy", 35, 0, 3.5);
  TH1D* hTotEnergySeNewP2       = new TH1D("hTotEnergySeNewP2","Total Electron Energy", 35, 0, 3.5);
  hTotEnergySeOldP1->Sumw2();
  hTotEnergySeOldP2->Sumw2();
  hTotEnergySeNewP1->Sumw2();
  hTotEnergySeNewP2->Sumw2();
  hTotEnergySeOldP1->SetTitle(";E_{1} + E_{2} / MeV; No. Events / 0.1 MeV");
  hTotEnergySeOldP2->SetTitle(";E_{1} + E_{2} / MeV; No. Events / 0.1 MeV");
  hTotEnergySeNewP1->SetTitle(";E_{1} + E_{2} / MeV; No. Events / 0.1 MeV");
  hTotEnergySeNewP2->SetTitle(";E_{1} + E_{2} / MeV; No. Events / 0.1 MeV");

  TH1D* hSingleEnergySeOldP1       = new TH1D("hSingleEnergySeOldP1","Single Electron Energy", 25, 0, 2.5);
  TH1D* hSingleEnergySeOldP2       = new TH1D("hSingleEnergySeOldP2","Single Electron Energy", 25, 0, 2.5);
  TH1D* hSingleEnergySeNewP1       = new TH1D("hSingleEnergySeNewP1","Single Electron Energy", 25, 0, 2.5);
  TH1D* hSingleEnergySeNewP2       = new TH1D("hSingleEnergySeNewP2","Single Electron Energy", 25, 0, 2.5);
  hSingleEnergySeOldP1->Sumw2();
  hSingleEnergySeOldP2->Sumw2();
  hSingleEnergySeNewP1->Sumw2();
  hSingleEnergySeNewP2->Sumw2();
  hSingleEnergySeOldP1->SetTitle(";E_{e} / MeV; No. Events / 0.1 MeV");
  hSingleEnergySeOldP2->SetTitle(";E_{e} / MeV; No. Events / 0.1 MeV");
  hSingleEnergySeNewP1->SetTitle(";E_{e} / MeV; No. Events / 0.1 MeV");
  hSingleEnergySeNewP2->SetTitle(";E_{e} / MeV; No. Events / 0.1 MeV");

  TH1D* hMinEnergySeOldP1       = new TH1D("hMinEnergySeOldP1","Min Electron Energy", 25, 0, 2.5);
  TH1D* hMinEnergySeOldP2       = new TH1D("hMinEnergySeOldP2","Min Electron Energy", 25, 0, 2.5);
  TH1D* hMinEnergySeNewP1       = new TH1D("hMinEnergySeNewP1","Min Electron Energy", 25, 0, 2.5);
  TH1D* hMinEnergySeNewP2       = new TH1D("hMinEnergySeNewP2","Min Electron Energy", 25, 0, 2.5);
  hMinEnergySeOldP1->Sumw2();
  hMinEnergySeOldP2->Sumw2();
  hMinEnergySeNewP1->Sumw2();
  hMinEnergySeNewP2->Sumw2();
  hMinEnergySeOldP1->SetTitle(";Min E_{e} / MeV; No. Events / 0.1 MeV");
  hMinEnergySeOldP2->SetTitle(";Min E_{e} / MeV; No. Events / 0.1 MeV");
  hMinEnergySeNewP1->SetTitle(";Min E_{e} / MeV; No. Events / 0.1 MeV");
  hMinEnergySeNewP2->SetTitle(";Min E_{e} / MeV; No. Events / 0.1 MeV");

  TH1D* hMaxEnergySeOldP1       = new TH1D("hMaxEnergySeOldP1","Max Electron Energy", 25, 0, 2.5);
  TH1D* hMaxEnergySeOldP2       = new TH1D("hMaxEnergySeOldP2","Max Electron Energy", 25, 0, 2.5);
  TH1D* hMaxEnergySeNewP1       = new TH1D("hMaxEnergySeNewP1","Max Electron Energy", 25, 0, 2.5);
  TH1D* hMaxEnergySeNewP2       = new TH1D("hMaxEnergySeNewP2","Max Electron Energy", 25, 0, 2.5);
  hMaxEnergySeOldP1->Sumw2();
  hMaxEnergySeOldP2->Sumw2();
  hMaxEnergySeNewP1->Sumw2();
  hMaxEnergySeNewP2->Sumw2();
  hMaxEnergySeOldP1->SetTitle(";Max E_{e} / MeV; No. Events / 0.1 MeV");
  hMaxEnergySeOldP2->SetTitle(";Max E_{e} / MeV; No. Events / 0.1 MeV");
  hMaxEnergySeNewP1->SetTitle(";Max E_{e} / MeV; No. Events / 0.1 MeV");
  hMaxEnergySeNewP2->SetTitle(";Max E_{e} / MeV; No. Events / 0.1 MeV");

  // Write out input file name
  string inputfile = "/unix/nemo3/users/jmott/SeleniumAnalysis/ProcessedData/Signal/2b2n/";
  inputfile.append(directory);
  if(std::string::npos != sample.find("SFoil") && std::string::npos != sample.find("210")){inputfile.append("SFoil_Bi210");}
  else {inputfile.append(sample);}
  inputfile.append("/Sig_Se_2b2n_output.root");

  // Open file and get hold of branches and assign them to relevant names
  TFile* f = new TFile(inputfile.c_str(),"READ");
  TObject* obj = f->Get("Se2b2nCuts");
  string treeName = obj->InheritsFrom("TDirectory") ? "Se2b2nCuts/Se2b2nCuts" : "Se2b2nCuts";
  TTree* tree = (TTree*)f->Get(treeName.c_str());
 
  int run, nNACaloHits, vertexLocation, scintLocation[2];
  double energy[2], trackLength[2], trackSign[2], probInt, probExt, cosTheta, cosThetaWeight, vertexR, vertexZ, vertexSector, trueVertexZ, trueVertexSector, radonWeight, bi210Weight, totGammaEnergy, eventTime;
  int nGammas;
  double gammaEnergy[10];

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
  tree->SetBranchAddress("b_nNACaloHits", &nGammas);
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

  if(std::string::npos != sample.find("Data") ){
    cout << "Events above 2.6 MeV:" << endl;
  }

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
	if(vertexLocation < 1){
	  hTotEnergySeOldP1->Fill(energy[0]+energy[1],radWeight);
	  hSingleEnergySeOldP1->Fill(energy[0],radWeight);
	  hSingleEnergySeOldP1->Fill(energy[1],radWeight);
	  hMinEnergySeOldP1->Fill(energy[0] > energy[1] ? energy[1] : energy[0],radWeight);
	  hMaxEnergySeOldP1->Fill(energy[0] > energy[1] ? energy[0] : energy[1],radWeight);
	} else {
	  hTotEnergySeNewP1->Fill(energy[0]+energy[1],radWeight);
	  hSingleEnergySeNewP1->Fill(energy[0],radWeight);
	  hSingleEnergySeNewP1->Fill(energy[1],radWeight);
	  hMinEnergySeNewP1->Fill(energy[0] > energy[1] ? energy[1] : energy[0],radWeight);
	  hMaxEnergySeNewP1->Fill(energy[0] > energy[1] ? energy[0] : energy[1],radWeight);
	}
      }
      else if(run > 3395){
	if(vertexLocation < 1){
	  hTotEnergySeOldP2->Fill(energy[0]+energy[1],radWeight);
	  hSingleEnergySeOldP2->Fill(energy[0],radWeight);
	  hSingleEnergySeOldP2->Fill(energy[1],radWeight);
	  hMinEnergySeOldP2->Fill(energy[0] > energy[1] ? energy[1] : energy[0],radWeight);
	  hMaxEnergySeOldP2->Fill(energy[0] > energy[1] ? energy[0] : energy[1],radWeight);
	} else {
	  hTotEnergySeNewP2->Fill(energy[0]+energy[1],radWeight);
	  hSingleEnergySeNewP2->Fill(energy[0],radWeight);
	  hSingleEnergySeNewP2->Fill(energy[1],radWeight);
	  hMinEnergySeNewP2->Fill(energy[0] > energy[1] ? energy[1] : energy[0],radWeight);
	  hMaxEnergySeNewP2->Fill(energy[0] > energy[1] ? energy[0] : energy[1],radWeight);
	}
      }
    }

  }

  TFile* outfile = new TFile(outfilename.c_str(),"UPDATE");
  char histname[100];

  string sampleP1 = sample + std::string("_P1");
  strcpy(histname,"hTotEnergySeOld_");
  TH1D *hTotEnergySeOldP1Clone = (TH1D*)hTotEnergySeOldP1->Clone(strcat(histname,sampleP1.c_str()));
  hTotEnergySeOldP1Clone->Write();

  strcpy(histname,"hTotEnergySeNew_");
  TH1D *hTotEnergySeNewP1Clone = (TH1D*)hTotEnergySeNewP1->Clone(strcat(histname,sampleP1.c_str()));
  hTotEnergySeNewP1Clone->Write();

  strcpy(histname,"hSingleEnergySeOld_");
  TH1D *hSingleEnergySeOldP1Clone = (TH1D*)hSingleEnergySeOldP1->Clone(strcat(histname,sampleP1.c_str()));
  hSingleEnergySeOldP1Clone->Write();

  strcpy(histname,"hSingleEnergySeNew_");
  TH1D *hSingleEnergySeNewP1Clone = (TH1D*)hSingleEnergySeNewP1->Clone(strcat(histname,sampleP1.c_str()));
  hSingleEnergySeNewP1Clone->Write();

  strcpy(histname,"hMinEnergySeOld_");
  TH1D *hMinEnergySeOldP1Clone = (TH1D*)hMinEnergySeOldP1->Clone(strcat(histname,sampleP1.c_str()));
  hMinEnergySeOldP1Clone->Write();

  strcpy(histname,"hMinEnergySeNew_");
  TH1D *hMinEnergySeNewP1Clone = (TH1D*)hMinEnergySeNewP1->Clone(strcat(histname,sampleP1.c_str()));
  hMinEnergySeNewP1Clone->Write();

  strcpy(histname,"hMaxEnergySeOld_");
  TH1D *hMaxEnergySeOldP1Clone = (TH1D*)hMaxEnergySeOldP1->Clone(strcat(histname,sampleP1.c_str()));
  hMaxEnergySeOldP1Clone->Write();

  strcpy(histname,"hMaxEnergySeNew_");
  TH1D *hMaxEnergySeNewP1Clone = (TH1D*)hMaxEnergySeNewP1->Clone(strcat(histname,sampleP1.c_str()));
  hMaxEnergySeNewP1Clone->Write();

  string sampleP2 = sample + std::string("_P2");
  strcpy(histname,"hTotEnergySeOld_");
  TH1D *hTotEnergySeOldP2Clone = (TH1D*)hTotEnergySeOldP2->Clone(strcat(histname,sampleP2.c_str()));
  hTotEnergySeOldP2Clone->Write();

  strcpy(histname,"hTotEnergySeNew_");
  TH1D *hTotEnergySeNewP2Clone = (TH1D*)hTotEnergySeNewP2->Clone(strcat(histname,sampleP2.c_str()));
  hTotEnergySeNewP2Clone->Write();

  strcpy(histname,"hSingleEnergySeOld_");
  TH1D *hSingleEnergySeOldP2Clone = (TH1D*)hSingleEnergySeOldP2->Clone(strcat(histname,sampleP2.c_str()));
  hSingleEnergySeOldP2Clone->Write();

  strcpy(histname,"hSingleEnergySeNew_");
  TH1D *hSingleEnergySeNewP2Clone = (TH1D*)hSingleEnergySeNewP2->Clone(strcat(histname,sampleP2.c_str()));
  hSingleEnergySeNewP2Clone->Write();

  strcpy(histname,"hMinEnergySeOld_");
  TH1D *hMinEnergySeOldP2Clone = (TH1D*)hMinEnergySeOldP2->Clone(strcat(histname,sampleP2.c_str()));
  hMinEnergySeOldP2Clone->Write();

  strcpy(histname,"hMinEnergySeNew_");
  TH1D *hMinEnergySeNewP2Clone = (TH1D*)hMinEnergySeNewP2->Clone(strcat(histname,sampleP2.c_str()));
  hMinEnergySeNewP2Clone->Write();

  strcpy(histname,"hMaxEnergySeOld_");
  TH1D *hMaxEnergySeOldP2Clone = (TH1D*)hMaxEnergySeOldP2->Clone(strcat(histname,sampleP2.c_str()));
  hMaxEnergySeOldP2Clone->Write();

  strcpy(histname,"hMaxEnergySeNew_");
  TH1D *hMaxEnergySeNewP2Clone = (TH1D*)hMaxEnergySeNewP2->Clone(strcat(histname,sampleP2.c_str()));
  hMaxEnergySeNewP2Clone->Write();

  outfile->Close();
  delete outfile;

  delete hTotEnergySeOldP1;
  delete hTotEnergySeOldP2;
  delete hTotEnergySeNewP1;
  delete hTotEnergySeNewP2;

  delete hSingleEnergySeOldP1;
  delete hSingleEnergySeOldP2;
  delete hSingleEnergySeNewP1;
  delete hSingleEnergySeNewP2;

  delete hMinEnergySeOldP1;
  delete hMinEnergySeOldP2;
  delete hMinEnergySeNewP1;
  delete hMinEnergySeNewP2;

  delete hMaxEnergySeOldP1;
  delete hMaxEnergySeOldP2;
  delete hMaxEnergySeNewP1;
  delete hMaxEnergySeNewP2;

  f->Close("R");
  delete f;

}

void addHistogramToFileInOutP1P2(string directory, string sample, string outfilename){

  // Create histograms that are wanted
  TH1D* hTotEnergySeOldIn_P1       = new TH1D("hTotEnergySeOldIn_P1","Total Electron Energy", 35, 0, 3.5);
  TH1D* hTotEnergySeOldOut_P1       = new TH1D("hTotEnergySeOldOut_P1","Total Electron Energy", 35, 0, 3.5);
  TH1D* hTotEnergySeOldIn_P2       = new TH1D("hTotEnergySeOldIn_P2","Total Electron Energy", 35, 0, 3.5);
  TH1D* hTotEnergySeOldOut_P2       = new TH1D("hTotEnergySeOldOut_P2","Total Electron Energy", 35, 0, 3.5);
  TH1D* hTotEnergySeNewIn_P1       = new TH1D("hTotEnergySeNewIn_P1","Total Electron Energy", 35, 0, 3.5);
  TH1D* hTotEnergySeNewOut_P1       = new TH1D("hTotEnergySeNewOut_P1","Total Electron Energy", 35, 0, 3.5);
  TH1D* hTotEnergySeNewIn_P2       = new TH1D("hTotEnergySeNewIn_P2","Total Electron Energy", 35, 0, 3.5);
  TH1D* hTotEnergySeNewOut_P2       = new TH1D("hTotEnergySeNewOut_P2","Total Electron Energy", 35, 0, 3.5);

  hTotEnergySeOldIn_P1->Sumw2();
  hTotEnergySeOldOut_P1->Sumw2();
  hTotEnergySeOldIn_P2->Sumw2();
  hTotEnergySeOldOut_P2->Sumw2();
  hTotEnergySeNewIn_P1->Sumw2();
  hTotEnergySeNewOut_P1->Sumw2();
  hTotEnergySeNewIn_P2->Sumw2();
  hTotEnergySeNewOut_P2->Sumw2();

  hTotEnergySeOldIn_P1->SetTitle(";E_{1} + E_{2} / MeV; No. Events / 0.1 MeV");
  hTotEnergySeOldOut_P1->SetTitle(";E_{1} + E_{2} / MeV; No. Events / 0.1 MeV");
  hTotEnergySeOldIn_P2->SetTitle(";E_{1} + E_{2} / MeV; No. Events / 0.1 MeV");
  hTotEnergySeOldOut_P2->SetTitle(";E_{1} + E_{2} / MeV; No. Events / 0.1 MeV");
  hTotEnergySeNewIn_P1->SetTitle(";E_{1} + E_{2} / MeV; No. Events / 0.1 MeV");
  hTotEnergySeNewOut_P1->SetTitle(";E_{1} + E_{2} / MeV; No. Events / 0.1 MeV");
  hTotEnergySeNewIn_P2->SetTitle(";E_{1} + E_{2} / MeV; No. Events / 0.1 MeV");
  hTotEnergySeNewOut_P2->SetTitle(";E_{1} + E_{2} / MeV; No. Events / 0.1 MeV");

  TH1D* hSingleEnergySeOldIn_P1       = new TH1D("hSingleEnergySeOldIn_P1","Single Electron Energy", 25, 0, 2.5);
  TH1D* hSingleEnergySeOldOut_P1       = new TH1D("hSingleEnergySeOldOut_P1","Single Electron Energy", 25, 0, 2.5);
  TH1D* hSingleEnergySeOldIn_P2       = new TH1D("hSingleEnergySeOldIn_P2","Single Electron Energy", 25, 0, 2.5);
  TH1D* hSingleEnergySeOldOut_P2       = new TH1D("hSingleEnergySeOldOut_P2","Single Electron Energy", 25, 0, 2.5);
  TH1D* hSingleEnergySeNewIn_P1       = new TH1D("hSingleEnergySeNewIn_P1","Single Electron Energy", 25, 0, 2.5);
  TH1D* hSingleEnergySeNewOut_P1       = new TH1D("hSingleEnergySeNewOut_P1","Single Electron Energy", 25, 0, 2.5);
  TH1D* hSingleEnergySeNewIn_P2       = new TH1D("hSingleEnergySeNewIn_P2","Single Electron Energy", 25, 0, 2.5);
  TH1D* hSingleEnergySeNewOut_P2       = new TH1D("hSingleEnergySeNewOut_P2","Single Electron Energy", 25, 0, 2.5);

  hSingleEnergySeOldIn_P1->Sumw2();
  hSingleEnergySeOldOut_P1->Sumw2();
  hSingleEnergySeOldIn_P2->Sumw2();
  hSingleEnergySeOldOut_P2->Sumw2();
  hSingleEnergySeNewIn_P1->Sumw2();
  hSingleEnergySeNewOut_P1->Sumw2();
  hSingleEnergySeNewIn_P2->Sumw2();
  hSingleEnergySeNewOut_P2->Sumw2();

  hSingleEnergySeOldIn_P1->SetTitle(";E_{e} / MeV; No. Events / 0.1 MeV");
  hSingleEnergySeOldOut_P1->SetTitle(";E_{e} / MeV; No. Events / 0.1 MeV");
  hSingleEnergySeOldIn_P2->SetTitle(";E_{e} / MeV; No. Events / 0.1 MeV");
  hSingleEnergySeOldOut_P2->SetTitle(";E_{e} / MeV; No. Events / 0.1 MeV");
  hSingleEnergySeNewIn_P1->SetTitle(";E_{e} / MeV; No. Events / 0.1 MeV");
  hSingleEnergySeNewOut_P1->SetTitle(";E_{e} / MeV; No. Events / 0.1 MeV");
  hSingleEnergySeNewIn_P2->SetTitle(";E_{e} / MeV; No. Events / 0.1 MeV");
  hSingleEnergySeNewOut_P2->SetTitle(";E_{e} / MeV; No. Events / 0.1 MeV");

  TH1D* hMinEnergySeOldIn_P1       = new TH1D("hMinEnergySeOldIn_P1","Min Electron Energy", 25, 0, 2.5);
  TH1D* hMinEnergySeOldOut_P1       = new TH1D("hMinEnergySeOldOut_P1","Min Electron Energy", 25, 0, 2.5);
  TH1D* hMinEnergySeOldIn_P2       = new TH1D("hMinEnergySeOldIn_P2","Min Electron Energy", 25, 0, 2.5);
  TH1D* hMinEnergySeOldOut_P2       = new TH1D("hMinEnergySeOldOut_P2","Min Electron Energy", 25, 0, 2.5);
  TH1D* hMinEnergySeNewIn_P1       = new TH1D("hMinEnergySeNewIn_P1","Min Electron Energy", 25, 0, 2.5);
  TH1D* hMinEnergySeNewOut_P1       = new TH1D("hMinEnergySeNewOut_P1","Min Electron Energy", 25, 0, 2.5);
  TH1D* hMinEnergySeNewIn_P2       = new TH1D("hMinEnergySeNewIn_P2","Min Electron Energy", 25, 0, 2.5);
  TH1D* hMinEnergySeNewOut_P2       = new TH1D("hMinEnergySeNewOut_P2","Min Electron Energy", 25, 0, 2.5);

  hMinEnergySeOldIn_P1->Sumw2();
  hMinEnergySeOldOut_P1->Sumw2();
  hMinEnergySeOldIn_P2->Sumw2();
  hMinEnergySeOldOut_P2->Sumw2();
  hMinEnergySeNewIn_P1->Sumw2();
  hMinEnergySeNewOut_P1->Sumw2();
  hMinEnergySeNewIn_P2->Sumw2();
  hMinEnergySeNewOut_P2->Sumw2();

  hMinEnergySeOldIn_P1->SetTitle(";Min E_{e} / MeV; No. Events / 0.1 MeV");
  hMinEnergySeOldOut_P1->SetTitle(";Min E_{e} / MeV; No. Events / 0.1 MeV");
  hMinEnergySeOldIn_P2->SetTitle(";Min E_{e} / MeV; No. Events / 0.1 MeV");
  hMinEnergySeOldOut_P2->SetTitle(";Min E_{e} / MeV; No. Events / 0.1 MeV");
  hMinEnergySeNewIn_P1->SetTitle(";Min E_{e} / MeV; No. Events / 0.1 MeV");
  hMinEnergySeNewOut_P1->SetTitle(";Min E_{e} / MeV; No. Events / 0.1 MeV");
  hMinEnergySeNewIn_P2->SetTitle(";Min E_{e} / MeV; No. Events / 0.1 MeV");
  hMinEnergySeNewOut_P2->SetTitle(";Min E_{e} / MeV; No. Events / 0.1 MeV");

  TH1D* hMaxEnergySeOldIn_P1       = new TH1D("hMaxEnergySeOldIn_P1","Max Electron Energy", 25, 0, 2.5);
  TH1D* hMaxEnergySeOldOut_P1       = new TH1D("hMaxEnergySeOldOut_P1","Max Electron Energy", 25, 0, 2.5);
  TH1D* hMaxEnergySeOldIn_P2       = new TH1D("hMaxEnergySeOldIn_P2","Max Electron Energy", 25, 0, 2.5);
  TH1D* hMaxEnergySeOldOut_P2       = new TH1D("hMaxEnergySeOldOut_P2","Max Electron Energy", 25, 0, 2.5);
  TH1D* hMaxEnergySeNewIn_P1       = new TH1D("hMaxEnergySeNewIn_P1","Max Electron Energy", 25, 0, 2.5);
  TH1D* hMaxEnergySeNewOut_P1       = new TH1D("hMaxEnergySeNewOut_P1","Max Electron Energy", 25, 0, 2.5);
  TH1D* hMaxEnergySeNewIn_P2       = new TH1D("hMaxEnergySeNewIn_P2","Max Electron Energy", 25, 0, 2.5);
  TH1D* hMaxEnergySeNewOut_P2       = new TH1D("hMaxEnergySeNewOut_P2","Max Electron Energy", 25, 0, 2.5);

  hMaxEnergySeOldIn_P1->Sumw2();
  hMaxEnergySeOldOut_P1->Sumw2();
  hMaxEnergySeOldIn_P2->Sumw2();
  hMaxEnergySeOldOut_P2->Sumw2();
  hMaxEnergySeNewIn_P1->Sumw2();
  hMaxEnergySeNewOut_P1->Sumw2();
  hMaxEnergySeNewIn_P2->Sumw2();
  hMaxEnergySeNewOut_P2->Sumw2();

  hMaxEnergySeOldIn_P1->SetTitle(";Max E_{e} / MeV; No. Events / 0.1 MeV");
  hMaxEnergySeOldOut_P1->SetTitle(";Max E_{e} / MeV; No. Events / 0.1 MeV");
  hMaxEnergySeOldIn_P2->SetTitle(";Max E_{e} / MeV; No. Events / 0.1 MeV");
  hMaxEnergySeOldOut_P2->SetTitle(";Max E_{e} / MeV; No. Events / 0.1 MeV");
  hMaxEnergySeNewIn_P1->SetTitle(";Max E_{e} / MeV; No. Events / 0.1 MeV");
  hMaxEnergySeNewOut_P1->SetTitle(";Max E_{e} / MeV; No. Events / 0.1 MeV");
  hMaxEnergySeNewIn_P2->SetTitle(";Max E_{e} / MeV; No. Events / 0.1 MeV");
  hMaxEnergySeNewOut_P2->SetTitle(";Max E_{e} / MeV; No. Events / 0.1 MeV");

  // Write out input file name
  string inputfile = "/unix/nemo3/users/jmott/SeleniumAnalysis/ProcessedData/Signal/2b2n/";
  inputfile.append(directory);
  inputfile.append(sample);
  inputfile.append("/Sig_Se_2b2n_output.root");

  // Open file and get hold of branches and assign them to relevant names
  TFile* f = new TFile(inputfile.c_str(),"READ");
  TObject* obj = f->Get("Se2b2nCuts");
  string treeName = obj->InheritsFrom("TDirectory") ? "Se2b2nCuts/Se2b2nCuts" : "Se2b2nCuts";
  TTree* tree = (TTree*)f->Get(treeName.c_str());
 
  int run, nNACaloHits, vertexLocation, foilSide, scintLocation[2];
  double energy[2], trackLength[2], trackSign[2], probInt, probExt, cosTheta, cosThetaWeight, vertexR, vertexZ, vertexSector, radonWeight, bi210Weight, totGammaEnergy;
  int nGammas;
  double gammaEnergy[10];

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
  tree->SetBranchAddress("b_nNACaloHits", &nGammas);
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
	if(foilSide == 0){
	  if(vertexLocation < 1){
	    hTotEnergySeOldIn_P1->Fill(energy[0]+energy[1],radWeight);
	    hSingleEnergySeOldIn_P1->Fill(energy[0],radWeight);
	    hSingleEnergySeOldIn_P1->Fill(energy[1],radWeight);
	    hMinEnergySeOldIn_P1->Fill(energy[0] > energy[1] ? energy[1] : energy[0],radWeight);
	    hMaxEnergySeOldIn_P1->Fill(energy[0] > energy[1] ? energy[0] : energy[1],radWeight);
	  } else {
	    hTotEnergySeNewIn_P1->Fill(energy[0]+energy[1],radWeight);
	    hSingleEnergySeNewIn_P1->Fill(energy[0],radWeight);
	    hSingleEnergySeNewIn_P1->Fill(energy[1],radWeight);
	    hMinEnergySeNewIn_P1->Fill(energy[0] > energy[1] ? energy[1] : energy[0],radWeight);
	    hMaxEnergySeNewIn_P1->Fill(energy[0] > energy[1] ? energy[0] : energy[1],radWeight);
	  }
	}
	else {
	  if(vertexLocation < 1){
	    hTotEnergySeOldOut_P1->Fill(energy[0]+energy[1],radWeight);
	    hSingleEnergySeOldOut_P1->Fill(energy[0],radWeight);
	    hSingleEnergySeOldOut_P1->Fill(energy[1],radWeight);
	    hMinEnergySeOldOut_P1->Fill(energy[0] > energy[1] ? energy[1] : energy[0],radWeight);
	    hMaxEnergySeOldOut_P1->Fill(energy[0] > energy[1] ? energy[0] : energy[1],radWeight);
	  } else {
	    hTotEnergySeNewOut_P1->Fill(energy[0]+energy[1],radWeight);
	    hSingleEnergySeNewOut_P1->Fill(energy[0],radWeight);
	    hSingleEnergySeNewOut_P1->Fill(energy[1],radWeight);
	    hMinEnergySeNewOut_P1->Fill(energy[0] > energy[1] ? energy[1] : energy[0],radWeight);
	    hMaxEnergySeNewOut_P1->Fill(energy[0] > energy[1] ? energy[0] : energy[1],radWeight);
	  }
	}
      } else if(run >= 3396){
	if(foilSide == 0){
	  if(vertexLocation < 1){
	    hTotEnergySeOldIn_P2->Fill(energy[0]+energy[1],radWeight);
	    hSingleEnergySeOldIn_P2->Fill(energy[0],radWeight);
	    hSingleEnergySeOldIn_P2->Fill(energy[1],radWeight);
	    hMinEnergySeOldIn_P2->Fill(energy[0] > energy[1] ? energy[1] : energy[0],radWeight);
	    hMaxEnergySeOldIn_P2->Fill(energy[0] > energy[1] ? energy[0] : energy[1],radWeight);
	  } else {
	    hTotEnergySeNewIn_P2->Fill(energy[0]+energy[1],radWeight);
	    hSingleEnergySeNewIn_P2->Fill(energy[0],radWeight);
	    hSingleEnergySeNewIn_P2->Fill(energy[1],radWeight);
	    hMinEnergySeNewIn_P2->Fill(energy[0] > energy[1] ? energy[1] : energy[0],radWeight);
	    hMaxEnergySeNewIn_P2->Fill(energy[0] > energy[1] ? energy[0] : energy[1],radWeight);
	  }
	} else {
	  if(vertexLocation < 1){
	    hTotEnergySeOldOut_P2->Fill(energy[0]+energy[1],radWeight);
	    hSingleEnergySeOldOut_P2->Fill(energy[0],radWeight);
	    hSingleEnergySeOldOut_P2->Fill(energy[1],radWeight);
	    hMinEnergySeOldOut_P2->Fill(energy[0] > energy[1] ? energy[1] : energy[0],radWeight);
	    hMaxEnergySeOldOut_P2->Fill(energy[0] > energy[1] ? energy[0] : energy[1],radWeight);
	  } else {
	    hTotEnergySeNewOut_P2->Fill(energy[0]+energy[1],radWeight);
	    hSingleEnergySeNewOut_P2->Fill(energy[0],radWeight);
	    hSingleEnergySeNewOut_P2->Fill(energy[1],radWeight);
	    hMinEnergySeNewOut_P2->Fill(energy[0] > energy[1] ? energy[1] : energy[0],radWeight);
	    hMaxEnergySeNewOut_P2->Fill(energy[0] > energy[1] ? energy[0] : energy[1],radWeight);
	  }
	}
      }
    }

  }

  TFile* outfile = new TFile(outfilename.c_str(),"UPDATE");
  char histname[100];

  string sampleIn_P1 = sample + std::string("_In_P1");
  strcpy(histname,"hTotEnergySeOld_");
  TH1D *hTotEnergySeOldIn_P1Clone = (TH1D*)hTotEnergySeOldIn_P1->Clone(strcat(histname,sampleIn_P1.c_str()));
  hTotEnergySeOldIn_P1Clone->Write();

  strcpy(histname,"hTotEnergySeNew_");
  TH1D *hTotEnergySeNewIn_P1Clone = (TH1D*)hTotEnergySeNewIn_P1->Clone(strcat(histname,sampleIn_P1.c_str()));
  hTotEnergySeNewIn_P1Clone->Write();

  strcpy(histname,"hSingleEnergySeOld_");
  TH1D *hSingleEnergySeOldIn_P1Clone = (TH1D*)hSingleEnergySeOldIn_P1->Clone(strcat(histname,sampleIn_P1.c_str()));
  hSingleEnergySeOldIn_P1Clone->Write();

  strcpy(histname,"hSingleEnergySeNew_");
  TH1D *hSingleEnergySeNewIn_P1Clone = (TH1D*)hSingleEnergySeNewIn_P1->Clone(strcat(histname,sampleIn_P1.c_str()));
  hSingleEnergySeNewIn_P1Clone->Write();

  strcpy(histname,"hMinEnergySeOld_");
  TH1D *hMinEnergySeOldIn_P1Clone = (TH1D*)hMinEnergySeOldIn_P1->Clone(strcat(histname,sampleIn_P1.c_str()));
  hMinEnergySeOldIn_P1Clone->Write();

  strcpy(histname,"hMinEnergySeNew_");
  TH1D *hMinEnergySeNewIn_P1Clone = (TH1D*)hMinEnergySeNewIn_P1->Clone(strcat(histname,sampleIn_P1.c_str()));
  hMinEnergySeNewIn_P1Clone->Write();

  strcpy(histname,"hMaxEnergySeOld_");
  TH1D *hMaxEnergySeOldIn_P1Clone = (TH1D*)hMaxEnergySeOldIn_P1->Clone(strcat(histname,sampleIn_P1.c_str()));
  hMaxEnergySeOldIn_P1Clone->Write();

  strcpy(histname,"hMaxEnergySeNew_");
  TH1D *hMaxEnergySeNewIn_P1Clone = (TH1D*)hMaxEnergySeNewIn_P1->Clone(strcat(histname,sampleIn_P1.c_str()));
  hMaxEnergySeNewIn_P1Clone->Write();

  string sampleOut_P1 = sample + std::string("_Out_P1");
  strcpy(histname,"hTotEnergySeOld_");
  TH1D *hTotEnergySeOldOut_P1Clone = (TH1D*)hTotEnergySeOldOut_P1->Clone(strcat(histname,sampleOut_P1.c_str()));
  hTotEnergySeOldOut_P1Clone->Write();

  strcpy(histname,"hTotEnergySeNew_");
  TH1D *hTotEnergySeNewOut_P1Clone = (TH1D*)hTotEnergySeNewOut_P1->Clone(strcat(histname,sampleOut_P1.c_str()));
  hTotEnergySeNewOut_P1Clone->Write();

  strcpy(histname,"hSingleEnergySeOld_");
  TH1D *hSingleEnergySeOldOut_P1Clone = (TH1D*)hSingleEnergySeOldOut_P1->Clone(strcat(histname,sampleOut_P1.c_str()));
  hSingleEnergySeOldOut_P1Clone->Write();

  strcpy(histname,"hSingleEnergySeNew_");
  TH1D *hSingleEnergySeNewOut_P1Clone = (TH1D*)hSingleEnergySeNewOut_P1->Clone(strcat(histname,sampleOut_P1.c_str()));
  hSingleEnergySeNewOut_P1Clone->Write();

  strcpy(histname,"hMinEnergySeOld_");
  TH1D *hMinEnergySeOldOut_P1Clone = (TH1D*)hMinEnergySeOldOut_P1->Clone(strcat(histname,sampleOut_P1.c_str()));
  hMinEnergySeOldOut_P1Clone->Write();

  strcpy(histname,"hMinEnergySeNew_");
  TH1D *hMinEnergySeNewOut_P1Clone = (TH1D*)hMinEnergySeNewOut_P1->Clone(strcat(histname,sampleOut_P1.c_str()));
  hMinEnergySeNewOut_P1Clone->Write();

  strcpy(histname,"hMaxEnergySeOld_");
  TH1D *hMaxEnergySeOldOut_P1Clone = (TH1D*)hMaxEnergySeOldOut_P1->Clone(strcat(histname,sampleOut_P1.c_str()));
  hMaxEnergySeOldOut_P1Clone->Write();

  strcpy(histname,"hMaxEnergySeNew_");
  TH1D *hMaxEnergySeNewOut_P1Clone = (TH1D*)hMaxEnergySeNewOut_P1->Clone(strcat(histname,sampleOut_P1.c_str()));
  hMaxEnergySeNewOut_P1Clone->Write();

  string sampleIn_P2 = sample + std::string("_In_P2");
  strcpy(histname,"hTotEnergySeOld_");
  TH1D *hTotEnergySeOldIn_P2Clone = (TH1D*)hTotEnergySeOldIn_P2->Clone(strcat(histname,sampleIn_P2.c_str()));
  hTotEnergySeOldIn_P2Clone->Write();

  strcpy(histname,"hTotEnergySeNew_");
  TH1D *hTotEnergySeNewIn_P2Clone = (TH1D*)hTotEnergySeNewIn_P2->Clone(strcat(histname,sampleIn_P2.c_str()));
  hTotEnergySeNewIn_P2Clone->Write();

  strcpy(histname,"hSingleEnergySeOld_");
  TH1D *hSingleEnergySeOldIn_P2Clone = (TH1D*)hSingleEnergySeOldIn_P2->Clone(strcat(histname,sampleIn_P2.c_str()));
  hSingleEnergySeOldIn_P2Clone->Write();

  strcpy(histname,"hSingleEnergySeNew_");
  TH1D *hSingleEnergySeNewIn_P2Clone = (TH1D*)hSingleEnergySeNewIn_P2->Clone(strcat(histname,sampleIn_P2.c_str()));
  hSingleEnergySeNewIn_P2Clone->Write();

  strcpy(histname,"hMinEnergySeOld_");
  TH1D *hMinEnergySeOldIn_P2Clone = (TH1D*)hMinEnergySeOldIn_P2->Clone(strcat(histname,sampleIn_P2.c_str()));
  hMinEnergySeOldIn_P2Clone->Write();

  strcpy(histname,"hMinEnergySeNew_");
  TH1D *hMinEnergySeNewIn_P2Clone = (TH1D*)hMinEnergySeNewIn_P2->Clone(strcat(histname,sampleIn_P2.c_str()));
  hMinEnergySeNewIn_P2Clone->Write();

  strcpy(histname,"hMaxEnergySeOld_");
  TH1D *hMaxEnergySeOldIn_P2Clone = (TH1D*)hMaxEnergySeOldIn_P2->Clone(strcat(histname,sampleIn_P2.c_str()));
  hMaxEnergySeOldIn_P2Clone->Write();

  strcpy(histname,"hMaxEnergySeNew_");
  TH1D *hMaxEnergySeNewIn_P2Clone = (TH1D*)hMaxEnergySeNewIn_P2->Clone(strcat(histname,sampleIn_P2.c_str()));
  hMaxEnergySeNewIn_P2Clone->Write();

  string sampleOut_P2 = sample + std::string("_Out_P2");
  strcpy(histname,"hTotEnergySeOld_");
  TH1D *hTotEnergySeOldOut_P2Clone = (TH1D*)hTotEnergySeOldOut_P2->Clone(strcat(histname,sampleOut_P2.c_str()));
  hTotEnergySeOldOut_P2Clone->Write();

  strcpy(histname,"hTotEnergySeNew_");
  TH1D *hTotEnergySeNewOut_P2Clone = (TH1D*)hTotEnergySeNewOut_P2->Clone(strcat(histname,sampleOut_P2.c_str()));
  hTotEnergySeNewOut_P2Clone->Write();

  strcpy(histname,"hSingleEnergySeOld_");
  TH1D *hSingleEnergySeOldOut_P2Clone = (TH1D*)hSingleEnergySeOldOut_P2->Clone(strcat(histname,sampleOut_P2.c_str()));
  hSingleEnergySeOldOut_P2Clone->Write();

  strcpy(histname,"hSingleEnergySeNew_");
  TH1D *hSingleEnergySeNewOut_P2Clone = (TH1D*)hSingleEnergySeNewOut_P2->Clone(strcat(histname,sampleOut_P2.c_str()));
  hSingleEnergySeNewOut_P2Clone->Write();

  strcpy(histname,"hMinEnergySeOld_");
  TH1D *hMinEnergySeOldOut_P2Clone = (TH1D*)hMinEnergySeOldOut_P2->Clone(strcat(histname,sampleOut_P2.c_str()));
  hMinEnergySeOldOut_P2Clone->Write();

  strcpy(histname,"hMinEnergySeNew_");
  TH1D *hMinEnergySeNewOut_P2Clone = (TH1D*)hMinEnergySeNewOut_P2->Clone(strcat(histname,sampleOut_P2.c_str()));
  hMinEnergySeNewOut_P2Clone->Write();

  strcpy(histname,"hMaxEnergySeOld_");
  TH1D *hMaxEnergySeOldOut_P2Clone = (TH1D*)hMaxEnergySeOldOut_P2->Clone(strcat(histname,sampleOut_P2.c_str()));
  hMaxEnergySeOldOut_P2Clone->Write();

  strcpy(histname,"hMaxEnergySeNew_");
  TH1D *hMaxEnergySeNewOut_P2Clone = (TH1D*)hMaxEnergySeNewOut_P2->Clone(strcat(histname,sampleOut_P2.c_str()));
  hMaxEnergySeNewOut_P2Clone->Write();

  outfile->Close();
  delete outfile;

  delete hTotEnergySeOldIn_P1;
  delete hTotEnergySeOldOut_P1;
  delete hTotEnergySeOldIn_P2;
  delete hTotEnergySeOldOut_P2;
  delete hTotEnergySeNewIn_P1;
  delete hTotEnergySeNewOut_P1;
  delete hTotEnergySeNewIn_P2;
  delete hTotEnergySeNewOut_P2;
  delete hSingleEnergySeOldIn_P1;
  delete hSingleEnergySeOldOut_P1;
  delete hSingleEnergySeOldIn_P2;
  delete hSingleEnergySeOldOut_P2;
  delete hSingleEnergySeNewIn_P1;
  delete hSingleEnergySeNewOut_P1;
  delete hSingleEnergySeNewIn_P2;
  delete hSingleEnergySeNewOut_P2;
  delete hMinEnergySeOldIn_P1;
  delete hMinEnergySeOldOut_P1;
  delete hMinEnergySeOldIn_P2;
  delete hMinEnergySeOldOut_P2;
  delete hMinEnergySeNewIn_P1;
  delete hMinEnergySeNewOut_P1;
  delete hMinEnergySeNewIn_P2;
  delete hMinEnergySeNewOut_P2;
  delete hMaxEnergySeOldIn_P1;
  delete hMaxEnergySeOldOut_P1;
  delete hMaxEnergySeOldIn_P2;
  delete hMaxEnergySeOldOut_P2;
  delete hMaxEnergySeNewIn_P1;
  delete hMaxEnergySeNewOut_P1;
  delete hMaxEnergySeNewIn_P2;
  delete hMaxEnergySeNewOut_P2;

  f->Close("R");
  delete f;

}
