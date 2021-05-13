// Author Cloé Girard-Carillo girardcarillo@lal.in2p3.fr

#include <limits>
#include <string>
#include <iostream>

#include <TTree.h>
#include <TFile.h>
#include <TObject.h>
#include <TH1.h>
#include <TH2.h>

#include "/home/girardcarillo/Workdir/SNPlot/RootDisplay.h"

using namespace std;

const int row_tot_number=13 ;
const int column_tot_number=20 ;

void RatioSB(const char* file_data_bdf,const char* file_bdf){

  TFile *theDataFile = new TFile(file_data_bdf,"READ") ;
  TH2F *hcoincidence_data_bdf = new TH2F ("data_bdf","", column_tot_number+2, -1, column_tot_number+1, row_tot_number+2, -1, row_tot_number+1) ;
  hcoincidence_data_bdf = (TH2F*)theDataFile->Get("coincidence") ;

  TFile *theBdfFile = new TFile(file_bdf,"READ") ;
  TH2F *hcoincidence_bdf = new TH2F ("bdf","", column_tot_number+2, -1, column_tot_number+1, row_tot_number+2, -1, row_tot_number+1) ;
  hcoincidence_bdf = (TH2F*)theBdfFile->Get("coincidence") ;

  TH2D *h2ratio = new TH2D ("ratio2d","", column_tot_number+2, -1, column_tot_number+1, row_tot_number+2, -1, row_tot_number+1) ;
  TH1F *hratio = new TH1F("ratio1d","",10, -10, 100) ;

  // hcoincidence_bdf->Draw("COLZTEXT") ;
  // hcoincidence_data_bdf->Draw("COLZTEXT") ;

  double bdf = 0. ;
  double data = 0. ;
  for (int i = 0 ; i < column_tot_number ; ++i) {
    for (int j = 0 ; j < row_tot_number ; ++j) {
      bdf = hcoincidence_bdf->GetBinContent(i+2,j+2) ;
      data = hcoincidence_data_bdf->GetBinContent(i+2,j+2) ;

      if (hcoincidence_bdf->GetBinContent(i+2,j+2) != 0 && hcoincidence_data_bdf->GetBinContent(i+2,j+2) != 0) {
        hratio->Fill(data/bdf) ;
        h2ratio->SetBinContent(i+2,j+2,data/bdf) ;
        cout << data/bdf << endl ;
      }

    }
  }

  // TCanvas *c = new TCanvas("c","c",10,10,2000,1000) ;
  // gStyle->SetPaintTextFormat("1.2f") ;
  // config_histo2D(h2ratio, "Number of events in each PMT", "Column","Row","COLZTEXT") ;
  // c->SaveAs("plots/ratioSB.pdf") ;
  config_histo1D(hratio,"HIST","S/B","",2,1,1) ;

}
