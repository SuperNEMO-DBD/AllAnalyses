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
std::ofstream efficiency_delta_t;
std::ofstream efficiency_proba;
std::ofstream efficiency_cut_proba;
std::ofstream efficiency_cut_delta_t;

void root_extract(Double_t gaus_sigma, Double_t sigma_L, string process, bool enable_drawing = 1, int cut1 = 0, bool cut2 = 0, double level_cut_proba = 0, double level_cut_delta_t = 0){

  cout << gaus_sigma << " " << level_cut_delta_t << " " << level_cut_proba << endl ;

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
  Double_t nbins = 30 ;
  // if (process=="0nubb") {
  //   nbins = 100;
  // }
  // else if (process=="208Tl") {
  //   nbins = 30;
  // }

  TH1F *hsigma_time_Emax = new TH1F("","",nbins,0,0.4);
  TH1F *hsigma_time_Emin = new TH1F("","",nbins,0,0.4);
  TH1F *htime_difference = new TH1F("calo_times","",nbins,-1,1);
  TH1F *hnoised_time_difference = new TH1F("smired_calo_times","",nbins,-6,8);
  TH1F *htime_Emin = new TH1F("time_Emin","Time of e-(Emin)",nbins,1,6);
  TH1F *htime_Emax = new TH1F("time_Emax","Time of e-(Emax)",nbins,1,6);
  TH1F *hEmin = new TH1F("minimal_energy","Minimal energy",80,0,4);
  TH1F *hEmax = new TH1F("maximal_energy","Maximal energy",80,0,4);
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
  TH1F *hrandom_Emax = new TH1F("random_Emax","",nbins,-1,1);
  TH1F *hrandom_Emin = new TH1F("random_Emin","",nbins,-1,1);
  TH1F *hrandom_diff = new TH1F("random_diff","",nbins,-1,1);
  TH1F *hmean_expogauss = new TH1F("mean_expogauss","",50,0.05,0.35);
  TH1F *hsigma_expogauss = new TH1F("sigma_expogauss","",50,0.05,0.35);
  TH1F *hdelta_t = new TH1F("delta_t","",nbins,-6,8);


  ///Fill trees with reconstructed data outputs
  TRandom *grandom1 = new TRandom(1234);
  TRandom *grandom2 = new TRandom(4321);

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
  double symmetric_noised_time_difference = 0. ;
  double mean_lower_bound = 0;
  double mean_upper_bound = 0;
  double ecart_moyenne = 0;

  double min_f = -4 ;
  double max_f = 4 ;

  TF1 *f_expogauss = new TF1("f_expogauss","([0]/2)*exp(([0]/2)*(2*[2]+[0]*pow([1],2)-2*(x)))*erfc(([2]+[0]*pow([1],2)-(x))/(sqrt(2)*[1]))",min_f,max_f);

  double nb_tot_events = 0;
  double nb_cut_delta_t = 0;
  double nb_cut_proba = 0;
  double nb_cut_energy = 0;

  cout << "total #event = " << newtree->GetEntries() << endl;


  ////////////////////// Creation tree

  Double_t out_time_Emin;
  Double_t out_time_Emax;
  Double_t out_probability;
  Double_t out_foil_vertices_distance_x ;
  Double_t out_foil_vertices_distance_y ;
  Double_t out_foil_vertices_distance_z ;
  Double_t out_length_Emin;
  Double_t out_length_Emax;
  Double_t out_minimal_energy;
  Double_t out_maximal_energy;
  Double_t out_sigma_time_Emin;
  Double_t out_sigma_time_Emax;

  TFile *hfile = hfile = TFile::Open(Form("/home/girardcarillo/Workdir/Analyses/SensitivityStudy/TlStudy/Sensitivity_%s.root",process.c_str()),"RECREATE");

  TTree *out_tree = new TTree("calorimeter_hit","test");
  out_tree->Branch("time_Emin",&out_time_Emin,"out_time_Emin/D");
  out_tree->Branch("time_Emax",&out_time_Emax,"out_time_Emax/D");
  out_tree->Branch("probability",&out_probability,"out_probability/D");
  out_tree->Branch("foil_vertices_distance_x",&out_foil_vertices_distance_x,"out_foil_vertices_distance_x/D");
  out_tree->Branch("foil_vertices_distance_y",&out_foil_vertices_distance_y,"out_foil_vertices_distance_y/D");
  out_tree->Branch("foil_vertices_distance_z",&out_foil_vertices_distance_z,"out_foil_vertices_distance_z/D");
  out_tree->Branch("length_Emin",&out_length_Emin,"out_length_Emin/D");
  out_tree->Branch("length_Emax",&out_length_Emax,"out_length_Emax/D");
  out_tree->Branch("minimal_energy",&out_minimal_energy,"out_minimal_energy/D");
  out_tree->Branch("maximal_energy",&out_maximal_energy,"out_maximal_energy/D");
  out_tree->Branch("sigma_time_Emin",&out_sigma_time_Emin,"out_sigma_time_Emin/D");
  out_tree->Branch("sigma_time_Emax",&out_sigma_time_Emax,"out_sigma_time_Emax/D");


  //////////////////////////////


  for (Long64_t i=0;i<newtree->GetEntries();i++) {
    newtree->GetEntry(i);
    if (i%100000==0) cout << "event " << i << endl ;

    nb_tot_events++ ;

    if (minimal_energy+maximal_energy>=0) {
    // if (maximal_energy>=2.4) {
      //   if (minimal_energy+maximal_energy<=3.2) {

      nb_cut_energy++ ;

      theoretical_time_Emax = GetTheoreticalTime(length_Emax,GetBeta(maximal_energy));
      theoretical_time_Emin = GetTheoreticalTime(length_Emin,GetBeta(minimal_energy));

      // random_Emax = GetRandomTime(grandom1->Gaus(0,gaus_sigma),maximal_energy);
      // random_Emin = GetRandomTime(grandom2->Gaus(0,gaus_sigma),minimal_energy);
      random_Emax = grandom1->Gaus(0,gaus_sigma/sqrt(maximal_energy));
      random_Emin = grandom2->Gaus(0,gaus_sigma/sqrt(minimal_energy));

      hrandom_Emin->Fill(random_Emin) ;
      hrandom_Emax->Fill(random_Emax) ;

      noised_time_Emin = time_Emin + random_Emin;
      noised_time_Emax = time_Emax + random_Emax;

      noised_time_difference = (noised_time_Emax - theoretical_time_Emax) - (noised_time_Emin - theoretical_time_Emin);
      time_difference = (time_Emax - theoretical_time_Emax) - (time_Emin - theoretical_time_Emin);

      sigma_beta_Emax = GetSigma_beta(theoretical_time_Emax,maximal_energy);
      sigma_beta_Emin = GetSigma_beta(theoretical_time_Emin,minimal_energy);

      sigma_time_Emax = GetSigma_time(gaus_sigma,maximal_energy) ;
      sigma_time_Emin = GetSigma_time(gaus_sigma,minimal_energy) ;

      sigma_tot = sqrt(pow(sigma_time_Emax,2)+pow(sigma_time_Emin,2)+pow(sigma_beta_Emax,2)+pow(sigma_beta_Emin,2)+pow(sigma_L,2)+pow(sigma_L,2));

      internal_Chi2 = GetInternal_Chi2(noised_time_difference,sigma_tot);
      calculated_internal_probability = GetInternalProbability(internal_Chi2);


      // // Computation exponential proba

      f_expogauss->SetParameters(slope,sigma_tot,0);

      maximumX = f_expogauss->GetMaximumX(min_f,max_f);
      evalY = f_expogauss->Eval(noised_time_difference);

      if (noised_time_difference <= maximumX) {
        symmetric_noised_time_difference = f_expogauss->GetX(evalY,maximumX,max_f) ;
        integral1 = f_expogauss->Integral(min_f,noised_time_difference);
        integral2 = f_expogauss->Integral(symmetric_noised_time_difference,max_f);
      }
      else {
        symmetric_noised_time_difference = f_expogauss->GetX(evalY,min_f,maximumX) ;
        integral1 = f_expogauss->Integral(noised_time_difference,max_f);
        integral2 = f_expogauss->Integral(min_f,symmetric_noised_time_difference);
      }

      integral = integral1+integral2;


      // // cut on delta_t
      bool cut_time_diff = 1 ;
      if (cut1==0) {
        cut_time_diff = 1 ;
      }
      else if (cut1==1) {
        cut_time_diff = noised_time_difference>level_cut_delta_t ;
      }
      else if (cut1==2) {
        cut_time_diff = noised_time_difference<level_cut_delta_t ;
      }
      else if (cut1==3) {
        cut_time_diff = (noised_time_difference>0)&&(noised_time_difference<f_expogauss->GetMaximumX(min_f,max_f)) ;
      }

      if (cut_time_diff) {

        nb_cut_delta_t++ ;

        bool cut_proba = 1 ;
        if (cut2==0) {
          cut_proba = 1 ;
          // cut_proba = calculated_internal_probability<0.04 ;
        }
        else if (cut2==1) {

          // cut_proba = integral>level_cut_proba*calculated_internal_probability ;
          // cut_proba = calculated_internal_probability<0.04;//integral>0.9 ;

          // // cuts proba quand d'abord on fait la coupure 2.7MeV
          // if (gaus_sigma==0) {
          //   cut_proba = ((integral<0.04)&&(calculated_internal_probability<0.04))||((calculated_internal_probability<0.15)&&(calculated_internal_probability>0.05)&&(integral>level_cut_proba)) ; // 0ps
          // }
          // if (gaus_sigma==0.1) {
          //   cut_proba = ((integral<0.01)&&(calculated_internal_probability<0.01))||((calculated_internal_probability<0.35)&&(calculated_internal_probability>0.25)&&(integral>level_cut_proba)) ; // 100ps
          // }
          // if (gaus_sigma==0.2) {
          //   cut_proba = ((integral<0.01)&&(calculated_internal_probability<0.01))||((calculated_internal_probability<0.55)&&(calculated_internal_probability>0.4)&&(integral>level_cut_proba)) ; // 200ps
          // }
          // if (gaus_sigma==0.3) {
          //   cut_proba = ((integral<0.01)&&(calculated_internal_probability<0.01))||((calculated_internal_probability<0.65)&&(calculated_internal_probability>0.45)&&(integral>level_cut_proba)) ; // 300ps
          // }
          // if (gaus_sigma==0.4) {
          //   cut_proba = ((integral<0.01)&&(calculated_internal_probability<0.01))||((calculated_internal_probability<0.7)&&(calculated_internal_probability>0.55)&&(integral>level_cut_proba)) ; // 400ps
          // }

          // sans coupure énergie
          if (gaus_sigma==0) {
            cut_proba = ((integral<0.04)&&(calculated_internal_probability<0.04))||((calculated_internal_probability<0.3)&&(calculated_internal_probability>0.05)&&(integral>level_cut_proba)) ; // 0ps
          }
          if (gaus_sigma==0.1) {
            cut_proba = ((integral<0.01)&&(calculated_internal_probability<0.01))||((calculated_internal_probability<0.6)&&(calculated_internal_probability>0.25)&&(integral>level_cut_proba)) ; // 100ps
          }
          if (gaus_sigma==0.2) {
            cut_proba = ((integral<0.01)&&(calculated_internal_probability<0.01))||((calculated_internal_probability<0.7)&&(calculated_internal_probability>0.4)&&(integral>level_cut_proba)) ; // 200ps
          }
          if (gaus_sigma==0.3) {
            cut_proba = ((integral<0.01)&&(calculated_internal_probability<0.01))||((calculated_internal_probability<0.8)&&(calculated_internal_probability>0.5)&&(integral>level_cut_proba)) ; // 300ps
          }
          if (gaus_sigma==0.4) {
            cut_proba = ((integral<0.01)&&(calculated_internal_probability<0.01))||((calculated_internal_probability<0.85)&&(calculated_internal_probability>0.55)&&(integral>level_cut_proba)) ; // 400ps
          }

        }

        if (cut_proba) {

          nb_cut_proba++ ;

          // // Filling histograms

          hintegrated_probability->Fill(integral);
          hcalculated_internal_probability->Fill(calculated_internal_probability);
          h2Probability->Fill(calculated_internal_probability,integral);
          hinternal_probability->Fill(probability);
          hinternal_Chi2->Fill(internal_Chi2);

          hnoised_time_difference->Fill(noised_time_difference);
          hdelta_t->Fill(noised_time_Emax - noised_time_Emin) ;

          htime_difference->Fill(time_difference) ;
          // htime_Emin->Fill(time_Emin);
          // htime_Emax->Fill(time_Emax);
          hEmin->Fill(minimal_energy);
          hEmax->Fill(maximal_energy);
          henergy_sum->Fill(maximal_energy+minimal_energy) ;

          hsigma_time_Emin->Fill(sigma_time_Emin);
          hsigma_time_Emax->Fill(sigma_time_Emax);
          hsigma_L->Fill(sigma_L);
          hsigma_beta_Emin->Fill(sigma_beta_Emin);
          hsigma_beta_Emax->Fill(sigma_beta_Emax);
          hsigma_tot->Fill(sigma_tot);

          hmean_expogauss->Fill(f_expogauss->GetMaximumX(min_f,max_f)) ;


          /////////////////////// writting in tree to work on sensitivity
          hfile->cd() ;


          out_time_Emin = time_Emin;
          out_time_Emax = time_Emax;
          out_probability = probability;
          out_foil_vertices_distance_x = foil_vertices_distance_x ;
          out_foil_vertices_distance_y = foil_vertices_distance_y ;
          out_foil_vertices_distance_z = foil_vertices_distance_z ;
          out_length_Emin = length_Emin;
          out_length_Emax = length_Emax;
          out_minimal_energy = minimal_energy;
          out_maximal_energy = maximal_energy;
          out_sigma_time_Emin = sigma_time_Emin;
          out_sigma_time_Emax = sigma_time_Emax;

          out_tree->Fill();

          ///////////////////////////////////////////



        }
      }


      //20000
      if (i > 20000) {
        cout << "BREAK" << endl ;
        break ;
      }

      //} // indiv energy cut
    } // total energy cut

  }

  // f_expogauss->Draw() ;

  out_tree->Write();

  delete hfile;

  // // // // evaluate Pint flatness with sigma_L paramater
  // TF1 *fit = new TF1("fit", "pol1",0.05,1);
  // hcalculated_internal_probability->Fit("fit","RQ") ;
  // flatness_Pint.open ("flatness_Pint.txt", std::ofstream::out | std::ofstream::app) ;
  // flatness_Pint << sigma_L << " " << fit->GetParameter(1) << " " << fit->GetParError(1) << endl ;
  // flatness_Pint.close() ;
  // hcalculated_internal_probability->GetFunction("fit")->SetLineWidth(0);
  // // //


  // TCanvas *c5 = new TCanvas("canvas","canvas");
  // c5->SaveAs("plots/tmp.pdf") ;

  // hmean_expogauss->Draw("HIST E") ;
  // int binmax = hmean_expogauss->GetMaximumBin(); double x = hmean_expogauss->GetXaxis()->GetBinCenter(binmax);
  // TLine* l0 = new TLine(x,0,x,hmean_expogauss->GetMaximum()) ;
  // l0->Draw("SAME") ;

  //  cout << "Mean expogauss " << f_expogauss->GetMaximumX(min_f,max_f) << endl;

  efficiency_cut_proba.open (Form("efficiency_cut_proba_%s.txt",process.c_str()), std::ofstream::out | std::ofstream::app) ;
  efficiency_cut_proba << level_cut_proba << " " << (nb_cut_proba/nb_cut_energy)*100. << endl ;
  efficiency_cut_proba.close() ;

  efficiency_cut_delta_t.open (Form("efficiency_cut_delta_t_%s.txt",process.c_str()), std::ofstream::out | std::ofstream::app) ;
  efficiency_cut_delta_t << level_cut_delta_t << " " << (nb_cut_delta_t/nb_cut_energy)*100. << endl ;
  efficiency_cut_delta_t.close() ;

  cout << "#total events = " << nb_tot_events << endl;
  cout << "#cut events = " << nb_cut_proba << endl;

  if (process=="208Tl") {
    cout << "Energy " << (nb_cut_energy/nb_tot_events)*100. << "% " << endl ;
    cout << "Rejection efficiency: " << "Delta t " << (nb_cut_delta_t/nb_cut_energy)*100. << "% " <<"Proba " << (nb_cut_proba/nb_cut_energy)*100. << "%" << endl;
  }
  else if (process=="0nubb") {
    cout << "Energy " << (nb_cut_energy/nb_tot_events)*100. << "% " << endl ;
    cout << "Selection efficiency: " << "Delta t " << (nb_cut_delta_t/nb_cut_energy)*100. << "% " <<"Proba " << (nb_cut_proba/nb_cut_energy)*100. << "%" << endl;
  }


  ///Normalization of probability histograms
  Double_t scale1 = 1./hnoised_time_difference->Integral();
  hnoised_time_difference->Scale(scale1);
  htime_difference->Scale(scale1);
  Double_t scale2 = 1./hdelta_t->Integral();
  hdelta_t->Scale(scale2);



  ///Drawing

  if (enable_drawing) {

    TCanvas *c5 = new TCanvas("canvas","canvas");
    c5->Range(-0.1896243,-1696.148,1.059034,11844.29);
    c5->SetFillColor(0);
    c5->SetBorderMode(0);
    c5->SetBorderSize(2);
    c5->SetLeftMargin(0.1518625);
    c5->SetRightMargin(0.04727794);
    c5->SetTopMargin(0.07430998);
    c5->SetBottomMargin(0.1252654);
    c5->SetFrameBorderMode(0);
    c5->SetFrameBorderMode(0);
    c5->SetLogy() ;

    config_histo1D(hEmin,"","Energy (MeV)","# Counts (Arbitrary normalisation)",2,1,kOrange+8) ;
    hEmin->SetTitle("") ;
    config_histo1D(hEmax,"SAME","","",2,1,kAzure+5) ;

    auto legend8 = new TLegend(0.5859599,0.7813163,0.9455587,0.9065817);
    legend8->SetBorderSize(0) ;
    legend8->AddEntry(hEmax,"Maximal energy hit","l");
    legend8->AddEntry(hEmin,"Minimal energy hit","l");
    legend8->Draw() ;

    c5->SaveAs(Form("../plots/energy_spect_min_max_%s.pdf",process.c_str())) ;

    TCanvas *c3 = new TCanvas("canvas","canvas");
    c3->Divide(2,3);

    c3->cd(1) ;
    config_histo1D(hsigma_time_Emax,"","#sigma_{t} (ns)","# Counts",1,1,1) ;
    config_histo1D(hsigma_time_Emin,"SAME","","",1,1,2) ;

    // auto legend1 = new TLegend(0.663481,0.566934,0.979752,0.769829);
    // legend1->AddEntry(hsigma_time_Emax,"sigma_t(Emax)","l");
    // legend1->AddEntry(hsigma_time_Emin,"sigma_t(Emin)","l");
    // legend1->Draw() ;

    c3->cd(2) ;
    config_histo1D(hsigma_beta_Emax,"","#sigma_{#beta} (ns)","# Counts",1,1,1) ;
    config_histo1D(hsigma_beta_Emin,"SAME","","",1,1,2) ;

    auto legend2 = new TLegend(0.663481,0.566934,0.979752,0.769829);
    legend2->AddEntry(hsigma_beta_Emax,"sigma_beta(Emax)","l");
    legend2->AddEntry(hsigma_beta_Emin,"sigma_beta(Emin)","l");
    legend2->Draw() ;

    c3->cd(3) ;
    config_histo1D(htime_difference,"HIST","","",1,1,1) ;
    config_histo1D(hnoised_time_difference,"SAMEHIST","#sigma_{L}","# Counts",1,1,2) ;

    auto legend3 = new TLegend(0.663481,0.566934,0.979752,0.769829);
    legend3->AddEntry(hnoised_time_difference,"#Delta t (avec random #sigma_{t})","l");
    legend3->AddEntry(htime_difference,"#Delta t (avec #sigma_{t} = 0)","l");
    legend3->Draw() ;

    c3->cd(4) ;
    config_histo1D(hsigma_tot,"","#sigma_{tot} (ns)","# Counts",1,1,1) ;

    c3->cd(5) ;
    config_histo1D(hcalculated_internal_probability,"","Probability","# Counts",1,1,1) ;
    config_histo1D(hinternal_probability,"SAME","Probability","# Counts",1,1,2) ;

    auto legend4 = new TLegend(0.663481,0.566934,0.979752,0.769829);
    legend4->AddEntry(hcalculated_internal_probability,"Ma P_{int}","l");
    legend4->AddEntry(hinternal_probability,"Steven P_{int}","l");
    legend4->Draw() ;


    c3->SaveAs(Form("../plots/sigmas_%s.eps",process.c_str())) ;

    TCanvas *c_all = new TCanvas("canvas","canvas");
    TGaxis::SetMaxDigits(3);
    c_all->Divide(2,2);

    // SNPlot a_plot;
    // a_plot.Set_SNgstyle();

    c_all->cd(1);

    config_histo1D(hintegrated_probability,"HIST E SAME","Probability","# Counts",1,1,3) ;
    config_histo1D(hcalculated_internal_probability,"HIST E SAME","Probability","# Counts",1,1,1) ;
    config_histo1D(hinternal_probability,"HIST E SAME","Probability","# Counts",1,1,2) ;
    // hintegrated_probability->GetYaxis()->SetRangeUser(0,1e3) ;


    auto legend5 = new TLegend(0.2,0.7,0.55,0.9);
    legend5->AddEntry(hcalculated_internal_probability,"P_{int}","l");
    legend5->AddEntry(hinternal_probability,"Steven P_{int}","l");
    legend5->AddEntry(hintegrated_probability,"P_{exp}","l");
    legend5->Draw();


    c_all->cd(2);
    f_expogauss->Draw() ;
    // config_histo1D(hdelta_t,"EHIST","","",1,1,1) ;

    c_all->cd(3);
    config_histo1D(hnoised_time_difference,"EHIST","#Delta t distribution","#Delta t (ns)",1,1,2) ;

    c_all->cd(4);
    configF_histo2D(h2Probability,"", "P_{int}","P_{exp}","COLZ") ;

    c_all->Modified();
    c_all->SaveAs(Form("../plots/all_%s_%1.f.eps",process.c_str(),gaus_sigma*1000));

    TCanvas *c_biplot = new TCanvas("c_biplot", "c_biplot",67,80,1500,1000);
    gStyle->SetOptStat(0);
    c_biplot->Range(-0.5239852,-0.2496513,1.318573,1.104603);
    c_biplot->SetFillColor(0);
    c_biplot->SetBorderMode(0);
    c_biplot->SetBorderSize(2);
    c_biplot->SetLeftMargin(0.2843792);
    c_biplot->SetRightMargin(0.1728972);
    c_biplot->SetTopMargin(0.07723996);
    c_biplot->SetBottomMargin(0.184346);
    c_biplot->SetFrameBorderMode(0);
    c_biplot->SetFrameBorderMode(0);
    c_biplot->SetLogz() ;
    gStyle->SetPalette(20,python_viridis) ;

    configF_histo2D(h2Probability,"", "P_{int}","P_{exp}","COLZ") ;
    h2Probability->GetXaxis()->SetTitleSize(0.07) ;
    h2Probability->GetXaxis()->SetLabelSize(0.05);
    h2Probability->GetXaxis()->SetTitleOffset(1);

    h2Probability->GetYaxis()->SetTitleSize(0.07) ;
    h2Probability->GetYaxis()->SetLabelSize(0.05);
    h2Probability->GetYaxis()->SetTitleOffset(0.9);

    h2Probability->GetZaxis()->SetLabelSize(0.05);
    h2Probability->SetContour(99) ;


    gPad->Update();
    // TPaletteAxis *palette = (TPaletteAxis*)h2Probability->GetListOfFunctions()->FindObject("palette");

    // // the following lines moe the paletter. Choose the values you need for the position.
    // palette->SetX1NDC(0.85);
    // palette->SetX2NDC(0.9);
    // palette->SetY1NDC(0.19);
    // palette->SetY2NDC(0.926);
    // gPad->Modified();
    // gPad->Update();


    TLine *l3 = new TLine(0,0,1,1) ;
    l3->SetLineWidth(2) ;
    l3->Draw() ;

    // h2Probability->SetRangeUser()

    c_biplot->SaveAs(Form("../plots/PintVSPexp_%s.eps",process.c_str()));

    TCanvas *c1 = new TCanvas("c1","c1");
    config_histo1D(henergy_sum,"","Energy sum (MeV)","# Counts",1,1,1) ;
    c1->SetLogy() ;
    c1->SaveAs(Form("../plots/energy_spectrum_%s.pdf",process.c_str())) ;

    TCanvas *c2 = new TCanvas("c2", "c2",67,87,700,500);
    c2->Range(-0.1896243,-1696.148,1.059034,11844.29);
    c2->SetFillColor(0);
    c2->SetBorderMode(0);
    c2->SetBorderSize(2);
    c2->SetLeftMargin(0.1518625);
    c2->SetRightMargin(0.04727794);
    c2->SetTopMargin(0.07430998);
    c2->SetBottomMargin(0.1252654);
    c2->SetFrameBorderMode(0);
    c2->SetFrameBorderMode(0);

    config_histo1D(hinternal_probability,"","P_{int}","# Counts",2,1,kCyan+2) ;
    config_histo1D(hcalculated_internal_probability,"SAME","","",2,1,kTeal+5) ;

    hinternal_probability->GetYaxis()->SetRangeUser(0,4e3) ;

    auto legend6 = new TLegend(0.673352,0.787686,0.949857,0.921444);
    legend6->SetBorderSize(0) ;
    legend6->AddEntry(hinternal_probability,"#sigma_{l} = 70 ps","l");
    legend6->AddEntry(hcalculated_internal_probability,"#sigma_{l} = 27.8 ps","l");
    legend6->Draw() ;


    // TLine *l0 = new TLine(0,fit->GetParameter(0),1,fit->GetParameter(0)) ;
    // l0->SetLineStyle(7) ;
    // l0->SetLineWidth(2) ;
    // l0->Draw() ;

    c2->SaveAs(Form("../plots/Internal_proba_%s.pdf",process.c_str())) ;

    TCanvas *c4 = new TCanvas("c4", "c4",67,87,700,500);
    c4->Range(-0.1896243,-1696.148,1.059034,11844.29);
    c4->SetFillColor(0);
    c4->SetBorderMode(0);
    c4->SetBorderSize(2);
    c4->SetLeftMargin(0.1518625);
    c4->SetRightMargin(0.04727794);
    c4->SetTopMargin(0.07430998);
    c4->SetBottomMargin(0.1252654);
    c4->SetFrameBorderMode(0);
    c4->SetFrameBorderMode(0);

    c4->SetLogy() ;

    config_histo1D(hcalculated_internal_probability,"","P_{int}","# Counts",2,1,kTeal+5) ;
    config_histo1D(hintegrated_probability,"SAME","","",2,1,kRed) ;

    hcalculated_internal_probability->GetYaxis()->SetRangeUser(1,9e3) ;

    auto legend7 = new TLegend(0.673352,0.787686,0.949857,0.921444);
    legend7->SetBorderSize(0) ;
    legend7->AddEntry(hcalculated_internal_probability,"P_{int}","l");
    legend7->AddEntry(hintegrated_probability,"P_{e}","l");
    legend7->Draw() ;
    c4->SaveAs(Form("../plots/expo_int_proba_%s.pdf",process.c_str())) ;

    int sig = gaus_sigma*1000 ;
    hintegrated_probability->SaveAs(Form("ExpoProba/expo_proba_%s_%i_ps.root",process.c_str(),sig)) ;


    TCanvas *c6 = new TCanvas("c6", "c6",67,87,700,500);
    c6->Range(-0.1896243,-1696.148,1.059034,11844.29);
    c6->SetFillColor(0);
    c6->SetBorderMode(0);
    c6->SetBorderSize(2);
    c6->SetLeftMargin(0.1518625);
    c6->SetRightMargin(0.04727794);
    c6->SetTopMargin(0.07430998);
    c6->SetBottomMargin(0.1252654);
    c6->SetFrameBorderMode(0);
    c6->SetFrameBorderMode(0);

    config_histo1D(hnoised_time_difference,"HIST","#Delta t (ns)","# Counts",2,1,kOrange-3) ;
    config_histo1D(hdelta_t,"HIST SAME","","",2,1,kAzure+2) ;

    hnoised_time_difference->GetYaxis()->SetRangeUser(0,0.35) ;

    TF1 *fit1 = new TF1("fit1", "gaus",-6,8) ;
    hdelta_t->Fit("fit1","RQ") ;

    TF1 *fit2 = new TF1("fit2", "gaus",-6,8) ;
    hnoised_time_difference->Fit("fit2","RQ") ;

    TLine *l1 = new TLine(fit1->GetParameter(1),0,fit1->GetParameter(1),hnoised_time_difference->GetMaximum()) ;
    l1->SetLineStyle(7) ;
    l1->SetLineWidth(2) ;
    l1->SetLineColor(kAzure+2) ;
    l1->Draw() ;

    TLine *l2 = new TLine(fit2->GetParameter(1),0,fit2->GetParameter(1),hnoised_time_difference->GetMaximum()) ;
    l2->SetLineStyle(7) ;
    l2->SetLineWidth(2) ;
    l2->SetLineColor(kOrange-3) ;
    l2->Draw() ;

    auto leg8 = new TLegend(0.584527,0.592357,0.772206,0.906582);
    leg8->SetBorderSize(0) ;
    leg8->SetTextSize(0.04);
    leg8->AddEntry(hdelta_t,"Non-corrected","l");
    leg8->AddEntry((TObject*)0,Form("Mean = %2.f #pm %2.f ps",fit1->GetParameter(1)*1000, fit1->GetParError(1)*1000),"");
    leg8->AddEntry((TObject*)0,Form("Std dev = %2.f #pm %2.f ps",fit1->GetParameter(2)*1000, fit1->GetParError(2)*1000),"");
    leg8->AddEntry(hnoised_time_difference ,"Corrected","l");
    leg8->AddEntry((TObject*)0,Form("Mean = %2.f #pm %2.f ps",fit2->GetParameter(1)*1000, fit2->GetParError(1)*1000),"");
    leg8->AddEntry((TObject*)0,Form("Std dev = %2.f #pm %2.f ps",fit2->GetParameter(2)*1000, fit2->GetParError(2)*1000),"");
    leg8->Draw() ;

    c6->SaveAs(Form("../plots/%s_delta_t.eps",process.c_str())) ;

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
