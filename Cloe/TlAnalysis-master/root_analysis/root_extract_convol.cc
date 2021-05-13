#include <TH1F.h>
#include <TH2F.h>
#include <TGraph.h>
#include <TTree.h>
#include <string>
#include <cmath>
#include "/home/girardcarillo/Workdir/SNPlot/SNPlot.cc"
#include "root_extract.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <TList.h>
#include <TFile.h>
#include <TRandom.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TGaxis.h>
#include <TStyle.h>
#include <TLegend.h>

#include "/home/girardcarillo/Workdir/SNPlot/RootDisplay.h"


Double_t A_208Tl = 54*31.5;//2*31.5;
Double_t exposure = 17.5;
Double_t nb_simulated_events = 0;
Double_t real_efficiency = 0.00312;

using namespace std;

Double_t GetBeta(Double_t energy);
Double_t GetTheoreticalTime(Double_t length, Double_t beta);
Double_t GetRandomTime(Double_t random, Double_t energy);
Double_t GetSigma_beta(Double_t theoretical_time, Double_t energy);
Double_t GetSigma_time(Double_t gaus_sigma, Double_t energy) ;
Double_t GetInternal_Chi2(Double_t delta_t, Double_t sigma);
Double_t GetInternalProbability(Double_t internal_Chi2);

//output file
std::ofstream flatness_Pint;

void root_extract_convol(Double_t gaus_sigma, Double_t sigma_L, string process, bool enable_drawing = 1, int IC=0){

  string const final_rate("final_rate.txt");
  ofstream final_flux(final_rate.c_str());

  Double_t tau = 0.294; //ns
  Double_t slope = 1/tau;

  string file_path = "$WORKDIR/Analyses/TlAnalysis/"+process+("/root_file_")+process+string("_tot.root");
  //data file
  TFile *DataFile = new TFile(file_path.c_str(),"READ") ;
  TTree *newtree = nullptr ;
  DataFile->GetObject("T",newtree) ;

  if (DataFile->IsOpen()) {
    cout << "File " << file_path << " opened sucessfully" << endl ;
  }

  newtree = (TTree*)DataFile->Get("calorimeter_hit") ;

  Double_t time_difference_E;
  Double_t time;
  Double_t time_Emin;
  Double_t time_Emax;
  Double_t probability;
  Double_t length_Emin;// = 1049.02;
  Double_t length_Emax;// = 905.924;
  Double_t minimal_energy;// = 0.62446;
  Double_t maximal_energy;// = 2.45767;
  Int_t event_counter;
  Double_t foil_vertices_distance_x ;
  Double_t foil_vertices_distance_y ;
  Double_t foil_vertices_distance_z ;
  Double_t calo_vertices_distance_x ;
  Double_t calo_vertices_distance_y ;
  Double_t calo_vertices_distance_z ;

  newtree->SetBranchAddress("time_difference_E",&time_difference_E);
  newtree->SetBranchAddress("time_Emin",&time_Emin);
  newtree->SetBranchAddress("time_Emax",&time_Emax);
  newtree->SetBranchAddress("probability",&probability);
  newtree->SetBranchAddress("length_Emin",&length_Emin);
  newtree->SetBranchAddress("length_Emax",&length_Emax);
  newtree->SetBranchAddress("minimal_energy",&minimal_energy);
  newtree->SetBranchAddress("maximal_energy",&maximal_energy);
  newtree->SetBranchAddress("event_counter",&event_counter);
  newtree->SetBranchAddress("foil_vertices_distance_x",&foil_vertices_distance_x);
  newtree->SetBranchAddress("foil_vertices_distance_y",&foil_vertices_distance_y);
  newtree->SetBranchAddress("foil_vertices_distance_z",&foil_vertices_distance_z);
  newtree->SetBranchAddress("calo_vertices_distance_x",&calo_vertices_distance_x);
  newtree->SetBranchAddress("calo_vertices_distance_y",&calo_vertices_distance_y);
  newtree->SetBranchAddress("calo_vertices_distance_z",&calo_vertices_distance_z);

  ///Create histograms to be filled with reconstructed data outputs
  Long64_t nentries = newtree->GetEntries();
  Double_t nbins = 0;
  if (process=="0nubb") {
    nbins = 100;
  }
  else if (process=="208Tl") {
    nbins = 30;
  }

  TH1F *hsigma_time_Emax = new TH1F("","",nbins,0,0.4);
  TH1F *hsigma_time_Emin = new TH1F("","",nbins,0,0.4);
  TH1F *htime_difference = new TH1F("calo_times","",nbins,-1,1);
  TH1F *hnoised_time_difference = new TH1F("smired_calo_times","",nbins,-1,1);
  TH1F *htime_Emin = new TH1F("time_Emin","Time of e-(Emin)",nbins,1,6);
  TH1F *htime_Emax = new TH1F("time_Emax","Time of e-(Emax)",nbins,1,6);
  TH1F *hEmin = new TH1F("minimal_energy","Minimal energy",nbins,0,3);
  TH1F *hEmax = new TH1F("maximal_energy","Maximal energy",nbins,0,3);
  TH1F *hinternal_probability = new TH1F("internal_probability","",nbins,0,1);
  TH1F *hintegrated_probability = new TH1F("integrated_probability","Integrated probability",nbins,0,1);
  TH1F *hcalculated_internal_probability = new TH1F("calculated_internal_probability","",nbins,0,1);
  TH1F *hinternal_Chi2 = new TH1F("Internal_Chi2","Calculated internal Chi2",nbins,0,1);
  TH2F *h2Probability = new TH2F("Biplot","P_{exp}(P_{int})",nbins,0,1,nbins,0,1);
  TH1F *hsigma_L = new TH1F("sigma_L","",nbins,0.03,0.05);
  TH1F *hsigma_beta_Emax = new TH1F("","",nbins,0,0.07);
  TH1F *hsigma_beta_Emin = new TH1F("","",nbins,0,0.07);
  TH1F *hsigma_tot = new TH1F("","",nbins,0,0);
  TH1F *henergy_sum = new TH1F("","",nbins,0,4);



  ///Fill trees with reconstructed data outputs
  TRandom *grandom1 = new TRandom(1234);
  TRandom *grandom2 = new TRandom(1234);

  Double_t noised_time_Emin = 0;
  Double_t noised_time_Emax = 0;
  Double_t random_Emax = 0;
  Double_t random_Emin = 0;
  Double_t theoretical_time_Emax = 0;
  Double_t theoretical_time_Emin = 0;
  Double_t noised_time_difference = 0;
  Double_t time_difference = 0;
  Double_t sigma_beta_Emax = 0;
  Double_t sigma_beta_Emin = 0;
  Double_t sigma_time_Emax = 0;
  Double_t sigma_time_Emin = 0;
  // Double_t tau_sc = 2.500;//ns
  // Double_t FWHM_TTS = 2.250;//ns
  Double_t sigma_tot = 0;
  Double_t internal_Chi2 = 0;
  int counter_test = 0;
  Double_t calculated_internal_probability = 0;
  double maximumX = 0;
  double evalY = 0;
  double integral1 = 0;
  double integral2 = 0;
  double integral = 0;
  double mean_lower_bound = 0;
  double mean_upper_bound = 0;
  double ecart_moyenne = 0;

  TF1 *f_expogauss = new TF1("f_expogauss","([0]/2)*exp(([0]/2)*(2*[2]+[0]*pow([1],2)-2*(x)))*erfc(([2]+[0]*pow([1],2)-(x))/(sqrt(2)*[1]))",-6,6);

  TF1Convolution *f_conv = new TF1Convolution("expo","gaus",-6,6,true);
  f_conv->SetRange(-6,6);
  f_conv->SetNofPointsFFT(1000);
  TF1   *f = new TF1("f",*f_conv, -5, 5, f_conv->GetNpar());
  // f->SetParameters(0.,-0.294,0.,2);

  double nb_tot_events = 0;
  double nb_cut_events = 0;

  cout << "total #event = " << newtree->GetEntries() << endl;

  for (Long64_t i=0;i<newtree->GetEntries();i++) {
    newtree->GetEntry(i);
    if (i%100000==0) cout << "event " << i << endl ;

    cout << i << endl ;

    theoretical_time_Emax = GetTheoreticalTime(length_Emax,GetBeta(maximal_energy));
    theoretical_time_Emin = GetTheoreticalTime(length_Emin,GetBeta(minimal_energy));

    random_Emax = GetRandomTime(grandom1->Gaus(0,gaus_sigma),maximal_energy);
    random_Emin = GetRandomTime(grandom2->Gaus(0,gaus_sigma),minimal_energy);

    noised_time_Emin = time_Emin + random_Emin;
    noised_time_Emax = time_Emax + random_Emax;

    noised_time_difference = (noised_time_Emax - theoretical_time_Emax) - (noised_time_Emin - theoretical_time_Emin);
    time_difference = (time_Emax - theoretical_time_Emax) - (time_Emin - theoretical_time_Emin);

    sigma_beta_Emax = GetSigma_beta(theoretical_time_Emax,maximal_energy);
    sigma_beta_Emin = GetSigma_beta(theoretical_time_Emin,minimal_energy);

    sigma_time_Emax = GetSigma_time(gaus_sigma,maximal_energy) ;
    sigma_time_Emin = GetSigma_time(gaus_sigma,minimal_energy) ;

    sigma_tot = sqrt(pow(sigma_time_Emax,2)+pow(sigma_time_Emin,2)+pow(sigma_beta_Emax,2)+pow(sigma_beta_Emin,2)+pow(sigma_L,2));

    internal_Chi2 = GetInternal_Chi2(noised_time_difference,sigma_tot);
    calculated_internal_probability = GetInternalProbability(internal_Chi2);

    // new TCanvas("c","c",800,1000);

    f->SetParameters(0.,-tau,0.,sigma_tot);

    cout << "sigma_tot " << sigma_tot << endl ;
    f->Draw() ;
    f->SetLineColor(1) ;
    f_expogauss->SetParameters(slope,sigma_tot,0);
    f_expogauss->Draw("SAME") ;


    // maximumX = f_expogauss->GetMaximumX(-6,6);
    // evalY = f_expogauss->Eval(noised_time_difference);

    // if (noised_time_difference <= maximumX) {
    //   integral1 = f_expogauss->Integral(-6,noised_time_difference);
    //   integral2 = f_expogauss->Integral(f_expogauss->GetX(evalY,maximumX,6),6);
    // }
    // else {
    //   integral1 = f_expogauss->Integral(noised_time_difference,6);
    //   integral2 = f_expogauss->Integral(-6,f_expogauss->GetX(evalY,-6,maximumX));
    // }

    // integral = integral1+integral2;

    //200000
    if (i > 1) {
      cout << "BREAK" << endl ;
      break ;
    }


  }

}


Double_t GetBeta(Double_t energy){
  Double_t beta;
  Double_t electron_mass = 0.511;
  beta = sqrt(energy * (energy + 2.*electron_mass)) / (energy + electron_mass);
  return beta;
}

Double_t GetTheoreticalTime(Double_t length, Double_t beta){
  Double_t theoretical_time;
  Double_t light_velocity = 2.99792458e+2;
  theoretical_time = length/(beta*light_velocity);
  return theoretical_time;
}

Double_t GetRandomTime(Double_t random, Double_t energy){
  Double_t random_sigma;
  random_sigma = random/sqrt(energy);
  return random_sigma;
}

Double_t GetSigma_beta(Double_t theoretical_time, Double_t energy){
  Double_t sigma_L;
  Double_t electron_mass = 0.511;
  Double_t sigma_E = (0.08*sqrt(energy))/(2*sqrt(2*log(2))) ;
  // sigma_L = (theoretical_time/(electron_mass*pow(energy/electron_mass+1,3)*pow(GetBeta(energy),3./2.)))*((0.08*sqrt(energy))/(2*sqrt(2*log(2)))); // mon calcul
  sigma_L = sqrt(pow((theoretical_time*pow(electron_mass,2))/(energy*(energy+electron_mass)*(energy+2*electron_mass)),2)*pow(sigma_E,2)) ; // extrait de la thèse de Christophe, page 124

  return sigma_L;
}

Double_t GetSigma_time(Double_t gaus_sigma, Double_t energy){
  Double_t sigma_t;

  sigma_t = gaus_sigma/sqrt(energy) ;

  return sigma_t;
}

Double_t GetInternal_Chi2(Double_t delta_t, Double_t sigma){
  Double_t valeur;
  valeur = pow(delta_t,2)/pow(sigma,2);
  return valeur;
}

Double_t GetInternalProbability(Double_t internal_Chi2){
  Double_t valeur;
  valeur = erfc(sqrt(internal_Chi2)/sqrt(2));
  return valeur;
}
