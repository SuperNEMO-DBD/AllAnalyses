// map_true_sigmas.C
// Author: Cloé Girard-Carillo <girardcarillo@lal.in2p3.fr>

// This macro aims to create a map of true sigmas from Cobalt analysis, for either data or simulations
// root 'map_true_sigmas.cc("true_sigmas.txt")' -b -q

#include <iostream>
#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include <TROOT.h>
#include <TLine.h>
#include <TStyle.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TH2D.h>
#include <TMathText.h>
#include <TRandom.h>

#include "/home/girardcarillo/Workdir/SNPlot/RootDisplay.h"

using namespace std;

//----------------------------//

const int row_tot_number=13 ;
const int column_tot_number=20 ;

int transform_index(int x, int y) ;
double WeightedMean(vector<double> val, vector<double> var) ;

void map_true_sigmas (string filename) {

  TTree *tree = new TTree("ntuple","sigmas") ;

  tree->ReadFile(filename.c_str(),"col/F:row/F:sigma/F:var/F") ;

  Float_t col,row ;
  Float_t sigma, var ;
  tree->SetBranchAddress("col",&col) ;
  tree->SetBranchAddress("row",&row) ;
  tree->SetBranchAddress("sigma",&sigma) ;
  tree->SetBranchAddress("var",&var) ;

  TH2D *h2counts = new TH2D ("counts","", column_tot_number+2, -1, column_tot_number+1, row_tot_number+2, -1, row_tot_number+1) ;
  TH2D *h2sigma = new TH2D ("h2sigmas","", column_tot_number+2, -1, column_tot_number+1, row_tot_number+2, -1, row_tot_number+1) ;
  TH2D *h2variance = new TH2D ("h2variance","", column_tot_number+2, -1, column_tot_number+1, row_tot_number+2, -1, row_tot_number+1) ;
  TH1F *hsigma = new TH1F ("sigmas","", 30, 0, 1.2) ;
  TH1F *hsigma_w = new TH1F ("sigmas w weigths","", 30, 0, 1.2) ;
  TH2D *h2sigma_OM = new TH2D ("h2sigma_OM","", 262, -1, 260, 100, 0, 1.4) ;

  vector <vector <vector <double> > > sigmas(column_tot_number) ;
  vector <vector <vector <double> > > vars(column_tot_number) ;
  for (int i = 0; i < column_tot_number; ++i) {
    sigmas[i]=vector<vector <double> >(row_tot_number) ;
    vars[i]=vector<vector <double> >(row_tot_number) ;
  }

  cout << tree->GetEntries() << " entries" << endl ;

  int index_wall = 0 ;
  for (int i=0; i<tree->GetEntries(); i++){

    tree->GetEntry(i);

    index_wall = transform_index(col,row) ;

    h2counts->SetBinContent(col+2,row+2,h2counts->GetBinContent(col+2,row+2)+1) ;
    h2variance->SetBinContent(col+2,row+2,h2variance->GetBinContent(col+2,row+2)+var) ;
    hsigma->Fill(sigma) ;
    hsigma_w->Fill(sigma,1/var) ;
    h2sigma_OM->Fill(index_wall,sigma);

    sigmas[col][row].push_back(sigma) ;
    vars[col][row].push_back(var) ;
  }


  double w_mean_sigma = 0. ;
  for (int i = 0; i < column_tot_number; ++i) {
    for (int j = 0; j < row_tot_number; ++j) {
      w_mean_sigma = WeightedMean(sigmas[i][j],vars[i][j]) ;

      h2sigma->SetBinContent(i+2,j+2,w_mean_sigma) ;
      h2variance->SetBinContent(i+2,j+2,h2variance->GetBinContent(i+2,j+2)/h2counts->GetBinContent(i+2,j+2)) ;
    }
  }

  TCanvas *c = new TCanvas("c","c",10,10,2000,1000) ;
  gStyle->SetPaintTextFormat("1.3f") ;
  gStyle->SetPalette(20,python_viridis) ;

  config_histo2D(h2counts, "", "Column","Row","COLZTEXT") ; c->SaveAs("plots/map_counts.pdf") ;
  config_histo2D(h2sigma, "", "Column","Row","COLZTEXT") ; c->SaveAs("plots/map_sigmas.pdf") ; h2sigma->SaveAs("plots/map_sigmas.root") ;
  config_histo2D(h2variance, "", "Column","Row","COLZTEXT") ; c->SaveAs("plots/map_variance.pdf") ;
  gStyle->SetOptStat(1) ;
  config_histo2D(h2sigma_OM, "", "OM index","Sigma (ns)","COLZ") ; c->SaveAs("plots/map_sigmas_OM.pdf") ;
  config_histo1D(hsigma_w,"hist","Sigma (ns)","",2,1,2) ; c->SaveAs("plots/sigmas_weights.pdf") ;
  config_histo1D(hsigma,"hist","Sigma (ns)","",2,1,1) ; c->SaveAs("plots/sigmas.pdf") ;

  c->BuildLegend() ;


  gStyle->SetOptStat(1) ;
}//end macro



int transform_index(int x, int y){

  int index = -1 ;

  int matrice [column_tot_number][row_tot_number] ;
  for (int i = 0; i < column_tot_number; ++i) {
    for (int j = 0; j < row_tot_number; ++j) {
      matrice[i][j] = i*row_tot_number+j ;
    }
  }

  if (x<column_tot_number && y<row_tot_number) {
    index = matrice[x][y] ;
  }
  else {
    cout << "Function transform_index(int channel, int slot): Bad channel or slot number!!" << endl ;
  }

  return index ;
}

double WeightedMean(vector<double> val, vector<double> var){
  double w_mean = 0. ;
  double w = 0. ;
  for (int i = 0; i < val.size(); ++i) {
    w_mean += val.at(i)*var.at(i) ;
    w += var.at(i) ;
  }

  w_mean /= w ;

  return w_mean;
}
