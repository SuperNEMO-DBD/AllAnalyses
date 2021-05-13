#include <typeinfo>
#include <TH1F.h>
#include <TGraph.h>
#include <TTree.h>
#include <string>
#include <gsl/gsl_cdf.h>
#include <cmath>
#include <vector>
#include <stdlib.h>

#include "/home/girardcarillo/Workdir/SNPlot/RootDisplay.h"
#include "/home/girardcarillo/Workdir/Analyses/SensitivityStudy/contaminations/contaminations.h"
#include "/home/girardcarillo/Workdir/Analyses/SensitivityStudy/EventSelection/Cuts.h"

using namespace std;

double Na = 6.022 * pow(10,23);
double T_2nubb_82Se = 9.39 * pow(10,19);
double T_0nubb_82Se = 2.5 * pow(10,23);
double T_2nubb_150Nd = 9.11 * pow(10,18);
double T_0nubb_150Nd = 2.5 * pow(10,23); // é chercher
double exposure = 17.5; // 500

double scale_Nd = 0.0317396 ; // 0.0986686
double scale_Se = 0.0439913 ;

double volume_tracker = 15.3 ; //m^3

double mass_mol_82Se = 0.082; // kg/mol
double mass_mol_150Nd = 0.150;

// number of simulated events on the internal pads bulk only
double nb_ev_0nu_internal = 9574121. ;
double nb_ev_2nu_internal = 9655014 ; // 9656794
double nb_ev_2nu_2MeV_internal = 9583845 ;
double nb_ev_Tl_internal = 9771597 ; // 9773130.
double nb_ev_Bi_internal = 9777626 ; // 9778522.
double nb_ev_Rn = 9.7e7 ;

//output file
std::string const final_rate("final_rate.txt");
std::ofstream final_flux;

std::string const ev_counter("82Se/without_B/0nubb/ev_number_file0_0nu.txt");
std::ofstream test_ev_nb(ev_counter.c_str());

struct search_ROI{
  double Einf_ROI;
  double Esup_ROI;
  double T12_max;
};



TH1F *henergy_sum(string isotope, bool field, string process, double xmin, double xmax, int nbins);
TH1F *hefficiency(string isotope, bool field, string process, double xmin, double xmax, int nbins, TH1F *histo_energy_sum = 0) ;
double WindowMethodFindExpSigEvts(Double_t B);
Double_t sensitivity_FC(string isotope, int bin_emin, int bin_emax, TH1F *histo_energy_0nubb, TH1F *histo_tot);
double ErrorStatEfficiency(string process, string isotope, double efficiency);
double ErrorStatbdf(string process, string isotope, double nbr_bdf, double efficiency);
search_ROI get_ROI(TH2F *histo_demie_vie = 0);
double mbb_min(double T12_max, string isotope);
double mbb_max(double T12_max, string isotope);
// commenté le 22/06/20 car erreur de compil. Donc rajout de la déclaration de la fonction
// hefficiency avant le main
// TH1F *hefficiency(string isotope, bool field, string process, double xmin, double xmax, int nbins, TH1F *histo_energy_sum = 0);
TH1F *hN_background(string isotope, bool field, string process, double xmin, double xmax, int nbins, TH1F *histo_energy_sum = 0,TH1F *histo_efficiency = 0);




void efficiency(string isotope, bool field, bool enable_drawing = 0){

  ///Total backgrounds
  TH1F *Nbackground_tot_spectrum = new TH1F("h_nbr_bdf_tot","Total expected number of background events",80,0,4);


  /// 0nubb
  TH1F *energy_spectrum_0nubb = henergy_sum(isotope, field,"0nubb",0,4,80);
  TH1F *efficiency_spectrum_0nubb = hefficiency(isotope, field,"0nubb",0,4,80,energy_spectrum_0nubb);


  double scale_2nu = 0. ;
  double nb_ev_0nu = 0 ;
  double nb_ev_2nu = 0 ;
  double nb_ev_Tl = 0 ;
  double nb_ev_Bi = 0 ;
  double T12_0nu = 0. ;
  double T12_2nu = 0. ;
  double mass_mol = 0. ;

  double borne_inf_min_ROI = 0. ;
  double borne_sup_min_ROI = 0. ;
  double borne_sup_max_ROI = 0. ;

  if (isotope == "82Se") {

    scale_2nu = scale_Se ;
    nb_ev_0nu = 1.e7 ;
    nb_ev_2nu = 1.e7 ;
    nb_ev_Tl = 1.e7 ;
    nb_ev_Bi = 1.e7 ;
    T12_0nu = T_0nubb_82Se ;
    T12_2nu = T_2nubb_82Se ;
    mass_mol = mass_mol_82Se ;
    borne_inf_min_ROI = 2.45 ;
    borne_sup_min_ROI = 2.95 ;
    borne_sup_max_ROI = 3.45 ;

  }

  if (isotope == "150Nd") {

    scale_2nu = scale_Nd ;
    nb_ev_0nu = nb_ev_0nu_internal ;
    nb_ev_2nu = nb_ev_2nu_2MeV_internal ;
    nb_ev_Tl = nb_ev_Tl_internal ;
    nb_ev_Bi = nb_ev_Bi_internal ;
    T12_0nu = T_0nubb_150Nd ;
    T12_2nu = T_2nubb_150Nd ;
    mass_mol = mass_mol_150Nd ;
    borne_inf_min_ROI = 2.85 ;
    borne_sup_min_ROI = 3.35 ;
    borne_sup_max_ROI = 3.85 ;

  }



  TH1F *energy_spectrum_2nubb = henergy_sum(isotope, field,"2nubb_2MeV",0,4,80);
  energy_spectrum_2nubb->Scale(scale_2nu) ;

  TH1F *efficiency_spectrum_2nubb = hefficiency(isotope, field,"2nubb",0,4,80,energy_spectrum_2nubb);
  TH1F *Nbackground_spectrum_2nubb = hN_background(isotope, field,"2nubb",0,4,80,energy_spectrum_2nubb,efficiency_spectrum_2nubb);

  TH1F *energy_spectrum_214Bi = henergy_sum(isotope, field,"214Bi",0,4,80);
  TH1F *efficiency_spectrum_214Bi = hefficiency(isotope, field,"214Bi",0,4,80,energy_spectrum_214Bi);
  TH1F *Nbackground_spectrum_214Bi = hN_background(isotope, field,"214Bi",0,4,80,energy_spectrum_214Bi,efficiency_spectrum_214Bi);

  TH1F *energy_spectrum_208Tl = henergy_sum(isotope, field,"208Tl",0,4,80);
  TH1F *efficiency_spectrum_208Tl = hefficiency(isotope, field,"208Tl",0,4,80,energy_spectrum_208Tl);
  TH1F *Nbackground_spectrum_208Tl = hN_background(isotope, field,"208Tl",0,4,80,energy_spectrum_208Tl,efficiency_spectrum_208Tl);

  TH1F *energy_spectrum_222Rn = henergy_sum(isotope, field,"222Rn",0,4,80);
  TH1F *efficiency_spectrum_222Rn = hefficiency(isotope, field,"222Rn",0,4,80,energy_spectrum_222Rn);
  TH1F *Nbackground_spectrum_222Rn = hN_background(isotope, field,"222Rn",0,4,80,energy_spectrum_222Rn,efficiency_spectrum_222Rn);


  TH2F *sensitivity_spectrum = new TH2F("h2_ROI","low bound vs up bound",10,borne_inf_min_ROI,borne_sup_min_ROI,20,borne_inf_min_ROI,borne_sup_max_ROI);

  Double_t Nbackground = 0;
  Double_t Nbackground_2nubb = 0;
  Double_t Nbackground_208Tl = 0;
  Double_t Nbackground_222Rn = 0;
  Double_t Nbackground_214Bi = 0;
  Double_t sensitivity = 0;
  Double_t efficiency_0nubb = 0;
  Double_t efficiency_2nubb = 0;
  Double_t efficiency_208Tl = 0;
  Double_t efficiency_222Rn = 0;
  Double_t efficiency_214Bi = 0;
  Double_t expectedSignalEventLimit = 0;

  for (int i=Nbackground_tot_spectrum->GetXaxis()->FindBin(borne_inf_min_ROI);i<=Nbackground_tot_spectrum->GetXaxis()->FindBin(borne_sup_min_ROI);i++) {
    for (int j=i+1;j<=Nbackground_tot_spectrum->GetXaxis()->FindBin(borne_sup_max_ROI);j++) {

      efficiency_0nubb += energy_spectrum_0nubb->Integral(i,j);
      efficiency_0nubb *= 1./nb_ev_0nu;

      efficiency_2nubb += energy_spectrum_2nubb->Integral(i,j);
      efficiency_2nubb *= 1./nb_ev_2nu;
      Nbackground_2nubb = ((Na*log(2))/mass_mol)*((efficiency_2nubb*exposure)/T12_2nu);

      efficiency_214Bi += energy_spectrum_214Bi->Integral(i,j);
      efficiency_214Bi *= 1./nb_ev_Bi;
      Nbackground_214Bi = A_214Bi*efficiency_214Bi*exposure;

      efficiency_208Tl+= energy_spectrum_208Tl->Integral(i,j);
      efficiency_208Tl *= 1./nb_ev_Tl;
      Nbackground_208Tl = A_208Tl*efficiency_208Tl*exposure;

      efficiency_222Rn += energy_spectrum_222Rn->Integral(i,j);
      efficiency_222Rn *= 1./nb_ev_Rn;
      if (exposure == 17.5) {
        Nbackground_222Rn = A_222Rn*efficiency_222Rn*volume_tracker*2.5;
      }
      if (exposure == 500) {
        Nbackground_222Rn = A_222Rn*efficiency_222Rn*volume_tracker*100;
      }

      Nbackground = Nbackground_2nubb+Nbackground_208Tl+Nbackground_214Bi+Nbackground_222Rn;
      if (Nbackground > 200.) {
        expectedSignalEventLimit = TMath::Sqrt(Nbackground);
      }
      else {
        expectedSignalEventLimit = WindowMethodFindExpSigEvts(Nbackground);
      }

      sensitivity = ((Na*log(2))/mass_mol)*((efficiency_0nubb*exposure)/expectedSignalEventLimit);

      sensitivity_spectrum->SetBinContent(i+1-Nbackground_tot_spectrum->GetXaxis()->FindBin(borne_inf_min_ROI),j+2-Nbackground_tot_spectrum->GetXaxis()->FindBin(borne_inf_min_ROI+0.05),sensitivity);

    }
  }


  cout << "T12 = " << get_ROI(sensitivity_spectrum).T12_max << endl;
  cout << "mbb = " << "[" << mbb_min(get_ROI(sensitivity_spectrum).T12_max,isotope) << "," << mbb_max(get_ROI(sensitivity_spectrum).T12_max,isotope) << "]" << endl;

  double efficiency_0nubb_ROI = energy_spectrum_0nubb->Integral(Nbackground_tot_spectrum->GetXaxis()->FindBin(get_ROI(sensitivity_spectrum).Einf_ROI),Nbackground_tot_spectrum->GetXaxis()->FindBin(get_ROI(sensitivity_spectrum).Esup_ROI));
  cout << "0nubb " << "[" << get_ROI(sensitivity_spectrum).Einf_ROI << "," << get_ROI(sensitivity_spectrum).Esup_ROI << "] = " << efficiency_0nubb_ROI/nb_ev_0nu << endl;


  double efficiency_2nubb_ROI = energy_spectrum_2nubb->Integral(Nbackground_tot_spectrum->GetXaxis()->FindBin(get_ROI(sensitivity_spectrum).Einf_ROI),Nbackground_tot_spectrum->GetXaxis()->FindBin(get_ROI(sensitivity_spectrum).Esup_ROI));
  double Nbackground_2nubb_ROI = ((Na*log(2))/mass_mol)*((efficiency_2nubb_ROI*exposure)/T12_2nu);
  cout << "2nubb " << "[" << get_ROI(sensitivity_spectrum).Einf_ROI << "," << get_ROI(sensitivity_spectrum).Esup_ROI << "] = " << Nbackground_2nubb_ROI/nb_ev_2nu << endl;


  double efficiency_208Tl_ROI = energy_spectrum_208Tl->Integral(Nbackground_tot_spectrum->GetXaxis()->FindBin(get_ROI(sensitivity_spectrum).Einf_ROI),Nbackground_tot_spectrum->GetXaxis()->FindBin(get_ROI(sensitivity_spectrum).Esup_ROI));
  double Nbackground_208Tl_ROI = A_208Tl*efficiency_208Tl_ROI*exposure;
  cout << "208Tl " << "[" << get_ROI(sensitivity_spectrum).Einf_ROI << "," << get_ROI(sensitivity_spectrum).Esup_ROI << "] = " << Nbackground_208Tl_ROI/nb_ev_Tl << endl;


  double efficiency_214Bi_ROI = energy_spectrum_214Bi->Integral(Nbackground_tot_spectrum->GetXaxis()->FindBin(get_ROI(sensitivity_spectrum).Einf_ROI),Nbackground_tot_spectrum->GetXaxis()->FindBin(get_ROI(sensitivity_spectrum).Esup_ROI));
  double Nbackground_214Bi_ROI = A_214Bi*efficiency_214Bi_ROI*exposure;
  cout << "214Bi " << "[" << get_ROI(sensitivity_spectrum).Einf_ROI << "," << get_ROI(sensitivity_spectrum).Esup_ROI << "] = " << Nbackground_214Bi_ROI/nb_ev_Bi << endl;


  double efficiency_222Rn_ROI = energy_spectrum_222Rn->Integral(Nbackground_tot_spectrum->GetXaxis()->FindBin(get_ROI(sensitivity_spectrum).Einf_ROI),Nbackground_tot_spectrum->GetXaxis()->FindBin(get_ROI(sensitivity_spectrum).Esup_ROI));
  double Nbackground_222Rn_ROI = 0. ;
  if (exposure == 17.5) {
    Nbackground_222Rn_ROI = A_222Rn*efficiency_222Rn_ROI*volume_tracker*2.5;
  }
  if (exposure == 500) {
    Nbackground_222Rn_ROI = A_222Rn*efficiency_222Rn_ROI*volume_tracker*100;
  }

  cout << "222Rn " << "[" << get_ROI(sensitivity_spectrum).Einf_ROI << "," << get_ROI(sensitivity_spectrum).Esup_ROI << "] = " << Nbackground_222Rn_ROI/nb_ev_Rn << endl;

  double NbkgTot = Nbackground_2nubb_ROI/nb_ev_2nu + Nbackground_208Tl_ROI/nb_ev_Tl + Nbackground_214Bi_ROI/nb_ev_Bi + Nbackground_222Rn_ROI/nb_ev_Rn ;
  NbkgTot = NbkgTot/(get_ROI(sensitivity_spectrum).Esup_ROI-get_ROI(sensitivity_spectrum).Einf_ROI)*1e-3/exposure ;

  cout << "Nbkg tot = " << NbkgTot << endl ;

  final_flux.open ("InfluenceContaminations/results.txt", std::ofstream::out | std::ofstream::app) ;
  final_flux << get_ROI(sensitivity_spectrum).Einf_ROI << " " << get_ROI(sensitivity_spectrum).Esup_ROI << " " << get_ROI(sensitivity_spectrum).T12_max << endl ;
  final_flux.close() ;



  // /// Drawing


  if (enable_drawing) {


    TCanvas *c_energy_spectrum = new TCanvas("canvas1","canvas1");
    c_energy_spectrum->Range(-0.4891892,-1.046424,4.513513,6.451694);
    c_energy_spectrum->SetFillColor(0);
    c_energy_spectrum->SetBorderMode(0);
    c_energy_spectrum->SetBorderSize(2);
    c_energy_spectrum->SetTopMargin(0.06024097);
    c_energy_spectrum->SetBottomMargin(0.1395582);
    c_energy_spectrum->SetFrameBorderMode(0);
    c_energy_spectrum->SetFrameBorderMode(0);

    TCanvas *c_efficiency_spectrum = new TCanvas("canvas2","canvas2");
    c_efficiency_spectrum->Range(-0.4891892,-1.046424,4.513513,6.451694);
    c_efficiency_spectrum->SetFillColor(0);
    c_efficiency_spectrum->SetBorderMode(0);
    c_efficiency_spectrum->SetBorderSize(2);
    c_efficiency_spectrum->SetLogy();
    c_efficiency_spectrum->SetTopMargin(0.06024097);
    c_efficiency_spectrum->SetBottomMargin(0.1395582);
    c_efficiency_spectrum->SetFrameBorderMode(0);
    c_efficiency_spectrum->SetFrameBorderMode(0);

    TCanvas *c_Nbackground_spectrum = new TCanvas("canvas3","canvas3");
    c_Nbackground_spectrum->Range(-0.4891892,-1.046424,4.513513,6.451694);
    c_Nbackground_spectrum->SetFillColor(0);
    c_Nbackground_spectrum->SetBorderMode(0);
    c_Nbackground_spectrum->SetBorderSize(2);
    c_Nbackground_spectrum->SetLogy();
    c_Nbackground_spectrum->SetTopMargin(0.06024097);
    c_Nbackground_spectrum->SetBottomMargin(0.1395582);
    c_Nbackground_spectrum->SetFrameBorderMode(0);
    c_Nbackground_spectrum->SetFrameBorderMode(0);

    TCanvas *c_sensitivity_spectrum = new TCanvas("canvas4","canvas4");
    gStyle->SetOptStat(0);
    c_sensitivity_spectrum->Range(2.273232,2.252703,3.154545,3.525676);
    c_sensitivity_spectrum->SetFillColor(0);
    c_sensitivity_spectrum->SetBorderMode(0);
    c_sensitivity_spectrum->SetBorderSize(2);
    c_sensitivity_spectrum->SetLeftMargin(0.2005731);
    c_sensitivity_spectrum->SetRightMargin(0.2320917);
    c_sensitivity_spectrum->SetTopMargin(0.05944798);
    c_sensitivity_spectrum->SetBottomMargin(0.1549894);
    c_sensitivity_spectrum->SetFrameBorderMode(0);
    c_sensitivity_spectrum->SetFrameBorderMode(0);


    // /// energy spectra


    energy_spectrum_0nubb->Scale((((Na*log(2))/mass_mol)*(exposure/T12_0nu))/nb_ev_0nu) ;
    energy_spectrum_2nubb->Scale((((Na*log(2))/mass_mol)*(exposure/T12_2nu))/nb_ev_2nu) ;
    energy_spectrum_208Tl->Scale(A_208Tl*exposure/nb_ev_Tl) ;
    energy_spectrum_214Bi->Scale(A_214Bi*exposure/nb_ev_Bi) ;
    if (exposure == 17.5) {
      energy_spectrum_222Rn->Scale(A_222Rn*volume_tracker*2.5/nb_ev_Rn) ;
    }
    if (exposure == 500) {
      energy_spectrum_222Rn->Scale(A_222Rn*volume_tracker*100/nb_ev_Rn) ;
    }


    // TH1F *energy_tot_bkg = new TH1F("h_nbr_bdf_tot","Total expected number of background events",80,0,4);

    // energy_tot_bkg->Add(energy_spectrum_2nubb);
    // energy_tot_bkg->Add(energy_spectrum_208Tl);
    // energy_tot_bkg->Add(energy_spectrum_214Bi);
    // energy_tot_bkg->Add(energy_spectrum_222Rn);

    c_energy_spectrum->cd();
    gPad->SetLogy();

    THStack *hs = new THStack("hs","");

    hs->Add(energy_spectrum_208Tl,"EHIST") ;
    energy_spectrum_208Tl->SetFillColorAlpha(kOrange+2,0.9) ;
    energy_spectrum_208Tl->SetLineColor(kCyan+4) ;
    hs->Add(energy_spectrum_214Bi,"EHIST") ;
    energy_spectrum_214Bi->SetFillColorAlpha(kYellow-3,0.9) ;
    energy_spectrum_214Bi->SetLineColor(kCyan+4) ;
    hs->Add(energy_spectrum_222Rn,"EHIST") ;
    energy_spectrum_222Rn->SetFillColorAlpha(kTeal+2,0.9) ;
    energy_spectrum_222Rn->SetLineColor(kCyan+4) ;
    hs->Add(energy_spectrum_2nubb,"EHIST") ;
    energy_spectrum_2nubb->SetFillColorAlpha(kCyan+3,0.9) ;
    energy_spectrum_2nubb->SetLineColor(kCyan+4) ;

    hs->SetMinimum(9e-4) ;
    hs->SetMaximum(2e3) ;

    config_hstack(hs,"","Total energy (MeV)","# Counts") ;

    ///

    // hs->SetMinimum(1e-3) ;
    // hs->SetMaximum(1e2) ;

    // hs->GetXaxis()->SetLimits(get_ROI(sensitivity_spectrum).Einf_ROI,get_ROI(sensitivity_spectrum).Esup_ROI) ;

    TLine* line0 = new TLine(get_ROI(sensitivity_spectrum).Einf_ROI,0,get_ROI(sensitivity_spectrum).Einf_ROI,4e3) ;
    TLine* line1 = new TLine(get_ROI(sensitivity_spectrum).Esup_ROI,0,get_ROI(sensitivity_spectrum).Esup_ROI,4e3) ;
    line0->SetLineStyle(2) ;
    line1->SetLineStyle(2) ;
    line0->SetLineColor(kGray+1) ;
    line1->SetLineColor(kGray+1) ;
    line0->SetLineWidth(2) ;

    line1->SetLineWidth(2) ;
    line0->Draw("SAME") ;
    line1->Draw("SAME") ;

    ///

    config_histo1D(energy_spectrum_0nubb,"ESAME","","",1,1,kGreen+4) ;
    energy_spectrum_0nubb->SetMarkerStyle(8) ;
    energy_spectrum_0nubb->SetMarkerSize(0.6) ;
    energy_spectrum_0nubb->SetMarkerColor(kGreen+4) ;

    auto legend1 = new TLegend(0.811,0.573,0.990,0.974);
    legend1->SetBorderSize(1) ;
    legend1->AddEntry(energy_spectrum_0nubb,"0#nu#beta#beta","lep");
    legend1->AddEntry(energy_spectrum_2nubb,"2#nu#beta#beta","f");
    legend1->AddEntry(energy_spectrum_222Rn,"^{222}Rn","f");
    legend1->AddEntry(energy_spectrum_214Bi,"^{214}Bi","f");
    legend1->AddEntry(energy_spectrum_208Tl,"^{208}Tl","f");
    legend1->Draw() ;


    // /// efficiency spectra

    c_efficiency_spectrum->cd();
    gPad->SetLogy();

    config_histo1D(efficiency_spectrum_0nubb,"L","E>E_{min} (MeV)","Cumulative efficiency",2,1,kGreen+4) ;
    efficiency_spectrum_0nubb->SetLineStyle(7) ;
    efficiency_spectrum_0nubb->SetTitle("");
    efficiency_spectrum_0nubb->GetYaxis()->SetRangeUser(1e-8,1) ;

    config_histo1D(efficiency_spectrum_2nubb,"SAMEL","","",2,1,kCyan+3) ;
    config_histo1D(efficiency_spectrum_214Bi,"SAMEL","","",2,1,kYellow-3) ;
    config_histo1D(efficiency_spectrum_208Tl,"SAMEL","","",2,1,kOrange+2) ;
    config_histo1D(efficiency_spectrum_222Rn,"SAMEL","","",2,1,kTeal+2) ;


    TLine* l0 = new TLine(get_ROI(sensitivity_spectrum).Einf_ROI,0,get_ROI(sensitivity_spectrum).Einf_ROI,1) ;
    TLine* l1 = new TLine(get_ROI(sensitivity_spectrum).Esup_ROI,0,get_ROI(sensitivity_spectrum).Esup_ROI,1) ;
    l0->SetLineStyle(2) ;
    l1->SetLineStyle(2) ;
    l0->SetLineColor(kGray+1) ;
    l1->SetLineColor(kGray+1) ;
    l0->SetLineWidth(2) ;

    l1->SetLineWidth(2) ;
    l0->Draw("SAME") ;
    l1->Draw("SAME") ;

    auto legend2 = new TLegend(0.811,0.573,0.990,0.974);
    legend2->AddEntry(efficiency_spectrum_0nubb,"0#nu#beta#beta","l");
    legend2->AddEntry(efficiency_spectrum_2nubb,"2#nu#beta#beta","l");
    legend2->AddEntry(efficiency_spectrum_222Rn,"^{222}Rn","l");
    legend2->AddEntry(efficiency_spectrum_214Bi,"^{214}Bi","l");
    legend2->AddEntry(efficiency_spectrum_208Tl,"^{208}Tl","l");
    legend2->Draw();



    // /// Nbackground spectra

    c_Nbackground_spectrum->cd();
    gPad->SetLogy();

    config_histo1D(Nbackground_spectrum_2nubb,"L","E>E_{min} (MeV)","#Background events",2,1,kCyan+3) ;
    Nbackground_spectrum_2nubb->SetTitle("");

    config_histo1D(Nbackground_spectrum_214Bi,"SAMEL","","",2,1,kYellow-3) ;
    config_histo1D(Nbackground_spectrum_208Tl,"SAMEL","","",2,1,kOrange+2) ;
    config_histo1D(Nbackground_spectrum_222Rn,"SAMEL","","",2,1,kTeal+2) ;

    Nbackground_spectrum_2nubb->GetYaxis()->SetRangeUser(1e-3,1e4);

    Nbackground_tot_spectrum->Add(Nbackground_spectrum_2nubb);
    Nbackground_tot_spectrum->Add(Nbackground_spectrum_208Tl);
    Nbackground_tot_spectrum->Add(Nbackground_spectrum_214Bi);
    Nbackground_tot_spectrum->Add(Nbackground_spectrum_222Rn);
    config_histo1D(Nbackground_tot_spectrum,"SAMEL","","",2,1,kBlack) ;

    TLine* l2 = new TLine(get_ROI(sensitivity_spectrum).Einf_ROI,0,get_ROI(sensitivity_spectrum).Einf_ROI,1e4) ;
    TLine* l3 = new TLine(get_ROI(sensitivity_spectrum).Esup_ROI,0,get_ROI(sensitivity_spectrum).Esup_ROI,1e4) ;
    l2->SetLineStyle(2) ;
    l3->SetLineStyle(2) ;
    l2->SetLineColor(kGray+1) ;
    l3->SetLineColor(kGray+1) ;
    l2->SetLineWidth(2) ;

    l3->SetLineWidth(2) ;
    l2->Draw("SAME") ;
    l3->Draw("SAME") ;

    auto legend3= new TLegend(0.811,0.573,0.990,0.974);

    legend3->AddEntry(Nbackground_spectrum_2nubb,"2#nu#beta#beta","l");
    legend3->AddEntry(Nbackground_spectrum_222Rn,"^{222}Rn","l");
    legend3->AddEntry(Nbackground_spectrum_214Bi,"^{214}Bi","l");
    legend3->AddEntry(Nbackground_spectrum_208Tl,"^{208}Tl","l");
    legend3->AddEntry(Nbackground_tot_spectrum,"Total","l");
    legend3->Draw();



    // /// sensitivity spectra

    c_sensitivity_spectrum->cd();
    TGaxis::SetMaxDigits(3);
    gStyle->SetPalette(20,python_viridis) ;
    sensitivity_spectrum->Scale(1./1e24) ;
    configF_histo2D(sensitivity_spectrum,"", "E_{min} (MeV)","E_{max} (MeV)","COLZTEXT") ;
    sensitivity_spectrum->SetMarkerSize(1) ;
    sensitivity_spectrum->SetTitle("") ;
    gStyle->SetPaintTextFormat("1.5f") ;

    TLine* line2 = new TLine(get_ROI(sensitivity_spectrum).Einf_ROI,borne_inf_min_ROI,get_ROI(sensitivity_spectrum).Einf_ROI,borne_sup_max_ROI) ;
    TLine* line3 = new TLine(borne_inf_min_ROI,get_ROI(sensitivity_spectrum).Esup_ROI,borne_sup_min_ROI,get_ROI(sensitivity_spectrum).Esup_ROI) ;

    line2->SetLineWidth(2) ;
    line3->SetLineWidth(2) ;
    line2->Draw("SAME") ;
    line3->Draw("SAME") ;


    auto text = new TPaveText(0.823,0.936,0.946,0.995,"NDC");
    text->SetBorderSize(0) ;
    text->SetFillColor(0) ;
    text->AddText("x 10^{24} (y)") ;
    text->Draw() ;

    if (field) {
      c_energy_spectrum->SaveAs(Form("plots/energy_spectrum_with_B_%s.pdf",isotope.c_str()));
      c_efficiency_spectrum->SaveAs(Form("plots/efficiency_spectrum_with_B_%s.pdf",isotope.c_str()));
      c_Nbackground_spectrum->SaveAs(Form("plots/Nbackground_spectrum_with_B_%s.pdf",isotope.c_str()));
      c_sensitivity_spectrum->SaveAs(Form("plots/sensitivity_spectrum_with_B_%s.pdf",isotope.c_str()));
    }

    else if (!field) {
      c_energy_spectrum->SaveAs(Form("plots/energy_spectrum_without_B_%s.pdf",isotope.c_str()));
      c_efficiency_spectrum->SaveAs(Form("plots/efficiency_spectrum_without_B_%s.pdf",isotope.c_str()));
      c_Nbackground_spectrum->SaveAs(Form("plots/Nbackground_spectrum_without_B_%s.pdf",isotope.c_str()));
      c_sensitivity_spectrum->SaveAs(Form("plots/sensitivity_spectrum_without_B_%s.pdf",isotope.c_str()));
    }


  }

  // energy_spectrum_0nubb->SaveAs("root_outpute/energy_spectrum_with_B_82Se_0nubb.root");
  // energy_spectrum_2nubb->SaveAs("root_outpute/energy_spectrum_with_B_82Se_2nubb.root");
  // energy_spectrum_208Tl->SaveAs("root_outpute/energy_spectrum_with_B_82Se_208Tl.root");
  // energy_spectrum_214Bi->SaveAs("root_outpute/energy_spectrum_with_B_82Se_214Bi.root");

  // efficiency_spectrum_0nubb->SaveAs("root_outpute/efficiency_spectrum_with_B_82Se_0nubb.root");
  // efficiency_spectrum_2nubb->SaveAs("root_outpute/efficiency_spectrum_with_B_82Se_2nubb.root");
  // efficiency_spectrum_208Tl->SaveAs("root_outpute/efficiency_spectrum_with_B_82Se_208Tl.root");
  // efficiency_spectrum_214Bi->SaveAs("root_outpute/efficiency_spectrum_with_B_82Se_214Bi.root");

  // Nbackground_spectrum_2nubb->SaveAs("root_outpute/Nbackground_spectrum_with_B_82Se_2nubb.root");
  // Nbackground_spectrum_208Tl->SaveAs("root_outpute/Nbackground_spectrum_with_B_82Se_208Tl.root");
  // Nbackground_spectrum_214Bi->SaveAs("root_outpute/Nbackground_spectrum_with_B_82Se_214Bi.root");

} // end of macro


///A function that create an histogram filled with electrons' energy sums for the corresponding
///process/isotope/field -> energy spectra
TH1F *henergy_sum(string isotope, bool field, string process, double xmin, double xmax, int nbins){

  string file_path;
  if (field == 1) {
    file_path = "$WORKDIR/Analyses/SensitivityStudy/"+isotope+string("/with_B/")+process+string("/root_file_")+process+string("_tot.root");
    // file_path = "$WORKDIR/Analyses/SensitivityStudy/"+isotope+string("/with_B/")+process+string("/root_file_0.root");
  }
  else if (field == 0) {
    file_path = "$WORKDIR/Analyses/SensitivityStudy/"+isotope+string("/without_B/")+process+string("/root_file_")+process+string("_tot.root");
    // file_path = "$WORKDIR/Analyses/SensitivityStudy/"+isotope+string("/without_B/")+process+string("/root_file_0.root");
  }
  else {
    cout << "From function henergy_sum: file does not exist" << endl ;
  }

  //data file
  TFile *DataFile = new TFile(file_path.c_str(),"READ") ;
  TTree *newtree = nullptr ;
  DataFile->GetObject("T",newtree) ;

  if (DataFile->IsOpen()) {
    cout << "File " << file_path << " opened sucessfully" << endl ;
  }

  newtree = (TTree*)DataFile->Get("calorimeter_hit") ;


  int event_counter;
  int event_counter_ytrue;
  Double_t time_difference_E;
  Double_t energy_sum;
  Double_t time_Emin;
  Double_t time_Emax;
  Double_t probability;
  Double_t foil_vertices_distance_x ;
  Double_t foil_vertices_distance_y ;
  Double_t foil_vertices_distance_z ;
  Double_t calo_vertices_distance_x ;
  Double_t calo_vertices_distance_y ;
  Double_t calo_vertices_distance_z ;
  Double_t length_Emin;
  Double_t length_Emax;
  Double_t minimal_energy;
  Double_t maximal_energy;
  Double_t sigma_time_Emin;
  Double_t sigma_time_Emax;

  newtree->SetBranchAddress("event_counter",&event_counter);
  if (process == "150Nd") {
    newtree->SetBranchAddress("event_counter_ytrue",&event_counter_ytrue);
  }
  newtree->SetBranchAddress("time_difference_E",&time_difference_E);
  newtree->SetBranchAddress("time_Emin",&time_Emin);
  newtree->SetBranchAddress("time_Emax",&time_Emax);
  newtree->SetBranchAddress("probability",&probability);
  newtree->SetBranchAddress("foil_vertices_distance_x",&foil_vertices_distance_x);
  newtree->SetBranchAddress("foil_vertices_distance_y",&foil_vertices_distance_y);
  newtree->SetBranchAddress("foil_vertices_distance_z",&foil_vertices_distance_z);
  newtree->SetBranchAddress("calo_vertices_distance_x",&calo_vertices_distance_x);
  newtree->SetBranchAddress("calo_vertices_distance_y",&calo_vertices_distance_y);
  newtree->SetBranchAddress("calo_vertices_distance_z",&calo_vertices_distance_z);
  newtree->SetBranchAddress("energy_sum",&energy_sum);
  newtree->SetBranchAddress("length_Emin",&length_Emin);
  newtree->SetBranchAddress("length_Emax",&length_Emax);
  newtree->SetBranchAddress("minimal_energy",&minimal_energy);
  newtree->SetBranchAddress("maximal_energy",&maximal_energy);
  newtree->SetBranchAddress("sigma_time_Emin",&sigma_time_Emin);
  newtree->SetBranchAddress("sigma_time_Emax",&sigma_time_Emax);


  ///Create histograms to be filled with reconstructed data outputs

  TH1F *henergy_sum = new TH1F("energy_sum","Energy sum histogram",nbins,xmin,xmax);
  TH1F *hproba = new TH1F("proba","proba",50,0,9);
  TH1F *hvertexY = new TH1F("vertexY","vertexY",100,0,3000);
  TH1F *hvertexZ = new TH1F("vertexZ","vertexZ",100,0,3000);

  int nbr_events_tot = 0 ;
  int nbr_events_Pint = 0 ;
  int nbr_events_vertex = 0 ;

  for (Long64_t i=0;i<newtree->GetEntries();i++) {
    newtree->GetEntry(i);

    nbr_events_tot++;

    if (probability > cut_proba_int) {
      nbr_events_Pint++;

      if (foil_vertices_distance_y < cut_vertex_y && foil_vertices_distance_z < cut_vertex_z) {
        nbr_events_vertex++;

        henergy_sum->Fill(energy_sum);
        hproba->Fill(10*probability);
        hvertexY->Fill(foil_vertices_distance_y);
        hvertexZ->Fill(foil_vertices_distance_z);

      }
    }


    // if (i > 100000) {
    //   cout << "BREAK" << endl ;
    //   break ;
    // }

  }

  cout << process << "  " << setprecision(9) <<  " " << nbr_events_tot << " " << nbr_events_Pint << " " << nbr_events_vertex << endl;

  // if (process == "2nubb_2MeV") {
  //   if (isotope == "82Se") {
  //     henergy_sum->Scale(scale_Se);
  //   }
  //   else if (isotope == "150Nd"){
  //     henergy_sum->Scale(scale_Nd); // 0.0986686
  //   }
  // }

  hproba->SaveAs(Form("InternalProba/root_files/Pint_%s.root",process.c_str())) ;
  hvertexY->SaveAs(Form("Vertex/root_files/Vertex_Y_%s.root",process.c_str())) ;
  hvertexZ->SaveAs(Form("Vertex/root_files/Vertex_Z_%s.root",process.c_str())) ;

  return henergy_sum;
}

TH1F *hN_background(string isotope, bool field, string process, double xmin, double xmax, int nbins, TH1F *histo_energy_sum = 0,TH1F *histo_efficiency = 0){

  TH1F *hnbr_bdf = new TH1F("nbr_bdf","Nbackground histogram",nbins,xmin,xmax);

  if (!histo_energy_sum) {
    histo_energy_sum = henergy_sum(isotope, field,process,xmin,xmax,nbins);
  }

  if (!histo_efficiency) {
    histo_efficiency = hefficiency(isotope, field,process,xmin,xmax,nbins,histo_energy_sum);
  }

  int n_bins = histo_efficiency->GetNbinsX();

  double nbr_bdf = 0;
  for (int emin=1; emin<=n_bins; emin++){
    double efficiency = 0;
    efficiency = histo_efficiency->GetBinContent(emin);

    if (process == "2nubb_2MeV" || process == "2nubb") {
      if (isotope == "82Se") {
        nbr_bdf = ((Na*log(2))/mass_mol_82Se)*((efficiency*exposure)/T_2nubb_82Se);
      }
      else if (isotope == "150Nd") {
        nbr_bdf = ((Na*log(2))/mass_mol_150Nd)*((efficiency*exposure)/T_2nubb_150Nd);
      }
    }

    else if (process == "214Bi") {
      nbr_bdf = A_214Bi*efficiency*exposure;
    }

    else if (process == "208Tl") {
      nbr_bdf = A_208Tl*efficiency*exposure;
    }

    else if (process == "222Rn") {
      if (exposure == 17.5) {
        nbr_bdf = A_222Rn*efficiency*volume_tracker*2.5;
      }
      if (exposure == 500) {
        nbr_bdf = A_222Rn*efficiency*volume_tracker*100;
      }
    }

    else {
      cout << "Unknown process" << endl;
    }

    hnbr_bdf->SetBinContent(emin,nbr_bdf);

  }
  return hnbr_bdf;
}

double WindowMethodFindExpSigEvts(Double_t B){

  //Find S using CL(S+B)/CL(B) = 0.1 with N_Obs = B
  Double_t Likelihood = 1.0;
  Double_t S = 0;
  Int_t NEvts = (int)B;

  while(Likelihood > 0.1){
    S += 0.001;
    Float_t CLsb = 0; Float_t CLb = 0;
    for (Int_t i=0; i<=NEvts; i++) {
      CLsb+=TMath::Poisson(i,S+B);
      CLb+=TMath::Poisson(i,B);
    }
    Likelihood =  CLsb/CLb;
  }
  return S;
}

Double_t sensitivity_FC(string isotope, int bin_emin, int bin_emax, TH1F *histo_energy_0nubb, TH1F *histo_tot) {
  Double_t sensitivity = 0;
  Double_t efficiency = 0;
  TFeldmanCousins f;
  Double_t Nobserved = 0;

  Double_t uplim = 0;
  Double_t lowlim = 0;

  Double_t Nbackground = 0;
  Nbackground = histo_tot->GetBinContent(bin_emin);
  Double_t fractpart = modf (Nbackground , &Nobserved);

  efficiency += histo_energy_0nubb->Integral(bin_emin,bin_emax);

  uplim = f.CalculateUpperLimit(Nobserved, Nbackground);

  if (isotope == "82Se") {
    sensitivity = ((Na*log(2))/mass_mol_82Se)*((efficiency*exposure)/uplim);
  }
  else {
    sensitivity = ((Na*log(2))/mass_mol_150Nd)*((efficiency*exposure)/uplim);
  }
  cout << "efficiency = " << efficiency << endl;
  cout << "sensitivity = " << sensitivity << endl;
  cout << "Nbackground = " << Nbackground << endl;
  cout << "Nobserved = " << Nobserved << endl;
  return sensitivity;
}


TH1F *hefficiency(string isotope, bool field, string process, double xmin, double xmax, int nbins, TH1F *histo_energy_sum = 0){

  TH1F *heff = new TH1F("efficiency","Efficiency histogram",nbins,xmin,xmax);

  if (!histo_energy_sum) {
    histo_energy_sum = henergy_sum(isotope,field, process,xmin,xmax,nbins);
  }

  int n_bins = histo_energy_sum->GetNbinsX();

  for (int emin=0; emin<n_bins; emin++){

    double efficiency = 0.;
    for (int bin_i=emin+1; bin_i<=n_bins; bin_i++){
      efficiency += histo_energy_sum->GetBinContent(bin_i);
    }

    // if (efficiency < 2.3){
    //   efficiency = 2.3;
    // }

    ///eff = Nev sélectionnés / Nev simulés
    if (isotope == "82Se") {
      /// Se simulé sur internal source pad bulks
      if (process == "222Rn") {
        efficiency *= 1./nb_ev_Rn;
      }
      else {
        efficiency *= 1./1e7;
      }
    }
    if (isotope == "150Nd") {
      /// Nd simulé sur source pad bulks, donc on doit retirer les év simulés sur les deux feuilles
      /// externes, ce qui retire qlqs év
      if (process == "0nubb") {
        efficiency *= 1./nb_ev_0nu_internal;
      }
      else if (process == "2nubb") {
        efficiency *= 1./nb_ev_2nu_internal;
      }
      else if (process == "2nubb_2MeV") {
        efficiency *= 1./nb_ev_2nu_2MeV_internal;
      }
      else if (process == "208Tl") {
        efficiency *= 1./nb_ev_Tl_internal;
      }
      else if (process == "214Bi") {
        efficiency *= 1./nb_ev_Bi_internal;
      }
      else if (process == "222Rn") {
        efficiency *= 1./nb_ev_Rn;
      }
      else {
        cout  << process << " Unknown process" << endl;
      }
    }

    heff->SetBinContent(emin+1, efficiency);
  }

  return heff;

}

double ErrorStatEfficiency(string process, string isotope, double efficiency){
  double statistic_error = 0;

  if (isotope == "82Se") {
    statistic_error = sqrt(efficiency/pow(10,7));
  }
  if (isotope == "150Nd") {
    if (process == "0nubb") {
      statistic_error = sqrt(efficiency/nb_ev_0nu_internal);
    }
    if (process == "2nubb_2MeV") {
      statistic_error = sqrt(efficiency/nb_ev_2nu_2MeV_internal);
    }
    if (process == "2nubb") {
      statistic_error = sqrt(efficiency/nb_ev_2nu_internal);
    }
    else if (process == "214Bi") {
      statistic_error = sqrt(efficiency/nb_ev_Bi_internal);
    }
    else if (process == "208Tl") {
      statistic_error = sqrt(efficiency/nb_ev_Tl_internal);
    }
  }
  return statistic_error;
}

double ErrorStatbdf(string process, string isotope, double nbr_bdf, double efficiency){
  double statistic_error = 0;

  statistic_error = (ErrorStatEfficiency(process, isotope, efficiency)*nbr_bdf)/efficiency;
  return statistic_error;
}

search_ROI get_ROI(TH2F *histo_sensitivity = 0){
  search_ROI bornes;
  double demie_vie_max = 0.;
  double Einf_ROI;
  double Esup_ROI;

  for (int i=0; i<histo_sensitivity->GetNbinsX(); i++) {
    double Einf = histo_sensitivity->GetXaxis()->GetBinLowEdge(i+1);
    for (int j=i+1; j<histo_sensitivity->GetNbinsY()-1; j++) {
      double Esup = histo_sensitivity->GetYaxis()->GetBinLowEdge(j+1);
      if (demie_vie_max < histo_sensitivity->GetBinContent(i+1, j+1)) {
        demie_vie_max = histo_sensitivity->GetBinContent(i+1, j+1);
        bornes.Einf_ROI = Einf;
        bornes.Esup_ROI = Esup;
        bornes.T12_max = demie_vie_max;
      }
    }
  }
  return bornes;
}

double mbb_min(double T12_max, string isotope){
  double matrix_element;
  double phase_space;
  double mbb;
  if (isotope == "82Se") {
    matrix_element = 5.4;
    phase_space = 10.16*pow(10,-15);
  }
  else if (isotope == "150Nd") {
    matrix_element = 5.6;
    phase_space = 63.03*pow(10,-15);
  }
  mbb = (511*pow(10,3)/(pow(1.27,2)*matrix_element))*sqrt(1/(T12_max*phase_space));
  return mbb;
}

double mbb_max(double T12_max, string isotope){
  double mbb= 0. ;
  double matrix_element;
  double phase_space;
  if (isotope == "82Se") {
    matrix_element = 2.79;
    phase_space = 10.16*pow(10,-15);
  }
  else if (isotope == "150Nd") {
    matrix_element = 1.71;
    phase_space = 63.03*pow(10,-15);
  }
  mbb = (511*pow(10,3)/(pow(1.27,2)*matrix_element))*sqrt(1/(T12_max*phase_space));
  return mbb;
}


// Double_t sensitivity_Poisson(string isotope, int bin_emin, int bin_emax, TH1F *histo_energy_0nubb, TH1F *histo_tot) {
//   Double_t Nbackground = histo_tot->Integral(bin_emin,bin_emax);
//   Double_t expectedSignalEventLimit = WindowMethodFindExpSigEvts(Nbackground);


//   // for (int emin=bin_emin; emin<bin_emax; emin++){
//   //   double efficiency = 0;
//   //   for (int bin_i=emin+1; bin_i<=bin_emax; bin_i++){
//   //     efficiency += histo_energy_sum->GetBinContent(bin_i);
//   //   }
//   //   efficiency *= 1./pow(10,7);
//   //   hefficiency->SetBinContent(emin, efficiency);
//   // }

//   efficiency += histo_energy_0nubb->Integral(bin_emin,bin_emax);

//   if (isotope == "82Se") {
//     Double_t sensitivity = ((Na*log(2))/mass_mol_82Se)*((efficiency*exposure)/expectedSignalEventLimit);
//   }
//   else {
//     Double_t sensitivity = ((Na*log(2))/mass_mol_150Nd)*((efficiency*exposure)/expectedSignalEventLimit);
//   }
//   // cout << "efficiency = " << efficiency << endl;
//   // cout << "sensitivity = " << sensitivity << endl;
//   // cout << "Nbackground = " << Nbackground << endl;
//   return sensitivity;
// }
