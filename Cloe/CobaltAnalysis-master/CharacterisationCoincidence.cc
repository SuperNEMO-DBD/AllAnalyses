// Author Cloé Girard-Carillo girardcarillo@lal.in2p3.fr

#include <limits>
#include <string>
#include <iostream>
#include <fstream>

#include <TTree.h>
#include <TFile.h>
#include <TObject.h>
#include <TH1.h>
#include <TH2.h>

#include "/home/girardcarillo/Workdir/SNPlot/RootDisplay.h"
#include "/home/girardcarillo/Workdir/SNPlot/EventTree.h"

using namespace std ;

typedef numeric_limits<double> dbl ;

const int row_tot_number=13 ;
const int column_tot_number=20 ;

void fit_delta_t(TH1F* histo, double *fit_parameters) ;
void SetPaveStat(TH1F *histo) ;
bool select_PM(vector<int> *vect_column,vector<int> *vect_row,int selected_column_1,int selected_row_1,int selected_column_2,int selected_row_2,int *hit,int *hit2) ;
void SetStat(TCanvas *c,double x1,double y1,double x2,double y2,Color_t a_tcolor) ;

void CharacterisationCoincidence(string filename,string correctedTimesFilename,int selected_column_1,int selected_row_1,int selected_column_2,int selected_row_2,double energy_cut_min=0,double energy_cut_max=0, bool enable_drawing = 0){
  cout.precision(dbl::max_digits10) ;
  TGaxis::SetMaxDigits(2) ;

  // corrected times from reflecto files
  TTree *tree_correctedTimes = new TTree("ntuple_correctedTimes","corrected times from reflecto") ;

  tree_correctedTimes->ReadFile(correctedTimesFilename.c_str(),"wall/I:col/I:row/I:CT/F") ;

  Int_t wall,col,row ;
  Float_t CT ;
  tree_correctedTimes->SetBranchAddress("wall",&wall) ;
  tree_correctedTimes->SetBranchAddress("col",&col) ;
  tree_correctedTimes->SetBranchAddress("row",&row) ;
  tree_correctedTimes->SetBranchAddress("CT",&CT) ;

  // // High Voltages
  // TTree *tree_highVoltages = new TTree("ntuple_highVoltages","High Voltages applied during run") ;

  // tree_highVoltages->ReadFile(correctedTimesFilename.c_str(),"OM_id:HV_ch:HV_pin:OM:HV",' ') ;

  // string OM_id ;
  // Float_t HV ;
  // tree_highVoltages->SetBranchAddress("OM_id",&OM_id) ;
  // tree_highVoltages->SetBranchAddress("HV",&HV) ;


  // for (int i=0; i<tree_highVoltages->GetEntries(); i++){
  //   tree_highVoltages->GetEntry(i);

  //   cout << OM_id << " " << HV << endl ;
  // }


  //data file
  TFile *DataFile = new TFile(filename.c_str(),"READ") ;
  TTree *theTree = nullptr ;
  DataFile->GetObject("T",theTree) ;

  if (DataFile->IsOpen()) {
    cout << "File " << filename << " opened sucessfully" << endl ;
  }

  theTree = (TTree*)DataFile->Get("DataCut") ;

  theTree->SetBranchAddress("trigger_id",&trigger_id) ;
  theTree->SetBranchAddress("calo_row",&calo_row) ;
  theTree->SetBranchAddress("calo_column",&calo_column) ;
  theTree->SetBranchAddress("calo_id",&calo_id) ;
  theTree->SetBranchAddress("calo_module",&calo_module) ;
  theTree->SetBranchAddress("channel_raw_tdc", &channel_raw_tdc) ;
  theTree->SetBranchAddress("calo_time",&calo_time) ;
  theTree->SetBranchAddress("calo_energy",&calo_energy) ;
  theTree->SetBranchAddress("calo_peak",&calo_peak) ;
  theTree->SetBranchAddress("calo_number",&calo_number) ;
  theTree->SetBranchAddress("cut_multiplicity", &cut_multiplicity) ;

  cout << theTree->GetEntries() << " entries"<< endl ;

  TH1F *henergy_spectrum_first = new TH1F(Form("Energy spectrum OM [%d:%d]",selected_column_1,selected_row_1),"",50, 0, 3) ;
  TH1F *henergy_spectrum_second = new TH1F(Form("Energy spectrum OM [%d:%d]",selected_column_2,selected_row_2),"",50, 0, 3) ;
  TH1F *hdeltat = new TH1F("Delta t not corrected from cable lenghts","",50, -10, 10) ;
  TH1F *hdeltat_corrected = new TH1F("Delta t corrected with cable lengths","",50, -10, 10) ;

  int counter_event = 0 ;
  int counter_loop = 0 ;


  for (Long64_t i=0 ;i<theTree->GetEntries() ;i++) {
    counter_loop++ ;
    theTree->GetEntry(i) ;
    if (i%100000==0) cout << "event " << i << endl ;

    if (isnan(calo_energy->at(0)) || isnan(calo_energy->at(1))){
      continue ;
    }

    else {

      //Fill avec Emin/Emax
      double Emin = 0., Emax = 0. ;
      double t_Emin = 0., t_Emax = 0. ;
      double Delta_t = 0. ;

      if (calo_energy->at(0) < calo_energy->at(1)) {
        Emin = calo_energy->at(0) ; Emax = calo_energy->at(1) ;
        t_Emin = calo_time->at(0) ; t_Emax = calo_time->at(1) ;
      }
      else if (calo_energy->at(0)>calo_energy->at(1)) {
        Emax=calo_energy->at(0) ; Emin=calo_energy->at(1) ;
        t_Emax=calo_time->at(0) ; t_Emin=calo_time->at(1) ;
      }

      // test cut energy different pour Emin et Emax 18/12/19
      bool flag_energy = 1 ;
      for (int i_energy = 0 ; i_energy < calo_energy->size() ; ++i_energy) {
        if (Emin < energy_cut_min || Emax < energy_cut_max) {
          flag_energy=0 ;
        }
      }


      if (flag_energy) {
        int hit1=-1 ;
        int hit2=-1 ;
        bool selected_PMT = select_PM(calo_column,calo_row,selected_column_1,selected_row_1,selected_column_2,selected_row_2,&hit1,&hit2) ;

        if (selected_PMT) {

          //delta t à corriger!!
          counter_event++ ;

          henergy_spectrum_first->Fill(calo_energy->at(hit1)) ;
          henergy_spectrum_second->Fill(calo_energy->at(hit2)) ;

          //delta t distribution non corrected times from cable lengths
          double dt=calo_time->at(hit1)-calo_time->at(hit2) ;
          hdeltat->Fill(dt) ;


          //// test with corrected times from reflecto (10/01/20)
          for (int i=0; i<tree_correctedTimes->GetEntries(); i++){
            tree_correctedTimes->GetEntry(i);
            if (col==calo_column->at(0)&&row==calo_row->at(0)) {
              calo_time->at(0) = calo_time->at(0) - CT ;
            }
            if (col==calo_column->at(1)&&row==calo_row->at(1)) {
              calo_time->at(1) = calo_time->at(1) - CT ;
            }
          }
          ////

          //delta t distribution corrected
          double dt_corrected = calo_time->at(hit1)-calo_time->at(hit2) ;
          hdeltat_corrected->Fill(dt_corrected) ;

        }
      }

      // if (i > 10000) {
      //   cout << "\033[1;31mwarning break at \033[0m" << i << endl ;
      //   break ;
      // }

    }
  }

  cout << counter_event << " selected on " << counter_loop << endl ;

  // Fitting Delta t distributions
  double fit_parameters[2] ;
  double fit_parameters_corrected[2] ;
  fit_delta_t(hdeltat,fit_parameters) ;
  fit_delta_t(hdeltat_corrected,fit_parameters) ;


  // ///Drawing

  if (enable_drawing) {

    TCanvas *c1 = new TCanvas("c1","c1",10,10,2000,1000) ;

    config_histo1D(henergy_spectrum_second,"","Energy (MeV)","#counts",2,1,8) ;
    henergy_spectrum_second->GetYaxis()->SetRangeUser(0,henergy_spectrum_second->GetMaximum()+henergy_spectrum_second->GetMaximum()*0.5) ;
    gStyle->SetOptFit();

    SetStat(c1,0.78,0.61,0.98,0.77,8) ;

    config_histo1D(henergy_spectrum_first,"SAMES","Energy (MeV)","#counts",2,1,9) ;
    SetStat(c1,0.78,0.77,0.98,0.93,9) ;

    gStyle->SetOptStat(1) ;


    c1->SaveAs(Form("plots_data/energy_coinc_%d-%d_%d-%d.pdf",selected_column_1,selected_row_1,selected_column_2,selected_row_2)) ;

    TCanvas *c2 = new TCanvas("c2","c2",10,10,2000,1000) ;
    config_histo1D(hdeltat,"","Delta t (ns)","#counts",2,1,8) ;
    SetStat(c2,0.78,0.61,0.98,0.77,8) ;

    config_histo1D(hdeltat_corrected,"SAMES","Delta t (ns)","#counts",2,1,9) ;
    SetStat(c2,0.78,0.77,0.98,0.93,9) ;

    gStyle->SetOptStat(1110) ;
    gStyle->SetOptFit(1111) ;

    hdeltat->GetYaxis()->SetRangeUser(0,hdeltat->GetMaximum()+hdeltat->GetMaximum()*0.5) ;

    c2->SaveAs(Form("plots_data/deltat_coinc_%d-%d_%d-%d.pdf",selected_column_1,selected_row_1,selected_column_2,selected_row_2)) ;

  }

  theTree->ResetBranchAddresses() ;
}

bool select_PM(vector<int> *vect_column,vector<int> *vect_row,int selected_column_1,int selected_row_1,int selected_column_2,int selected_row_2,int *hit1,int *hit2){
  bool flag_test=0 ;

  for (int i = 0; i < vect_row->size(); ++i) {

    if (vect_column->at(i)==selected_column_1 && vect_row->at(i)==selected_row_1) {

      if (vect_column->at(abs(i-1))==selected_column_2 && vect_row->at(abs(i-1))==selected_row_2) {
        *hit1=i ;
        *hit2=abs(i-1) ;
        flag_test=1 ;
      }

    }

  }

  return flag_test ;

}

void fit_delta_t(TH1F* histo, double fit_parameters[2]){

  TF1 *f1 = new TF1("f1","gaus",-20,20) ;

  f1->SetParameter(1,histo->GetMean()) ;
  f1->SetParameter(2,histo->GetRMS()) ;

  histo->Fit("f1","QR") ;

  fit_parameters[0] = f1->GetParameter(2) ;
  fit_parameters[1] = f1->GetParError(2) ;

  delete f1 ;

}

void SetStat(TCanvas *c,double x1,double y1,double x2,double y2,Color_t a_tcolor){

  c->Modified(); c->Update();
  TPaveStats *stats =(TPaveStats*)c->GetPrimitive("stats");
  stats->SetName("h1stats");
  stats->SetX1NDC(x1) ; stats->SetX2NDC(x2) ;
  stats->SetY1NDC(y1) ; stats->SetY2NDC(y2) ;
  stats->SetTextColor(a_tcolor);

}
