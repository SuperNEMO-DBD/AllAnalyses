// Author Cloé Girard-Carillo girardcarillo@lal.in2p3.fr
// routine to merge too TProfile generated with
// ~/Workdir/Analyses/CobaltAnalysis/BackgroundEstimation/GenerateBdfRun.cc

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

double distance_OM(int col1,int row1,int col2,int row2) ;

void merge_profile(const char* file_data,const char* file_bdf){


  TFile *the1File = new TFile(file_data,"READ");
  TProfile *hdata = (TProfile*)the1File->Get("distance_stat");

  TFile *the2File = new TFile(file_bdf,"READ");
  TProfile *hbdf = (TProfile*)the2File->Get("distance_stat");


  gStyle->SetOptStat(0) ;
  TCanvas *c = new TCanvas("c","c",10,10,2000,1000) ;

  config_profile(hdata,"","D (cm^{2})","#Counts","E",2,MultiPlotColors(10)) ;
  hdata->GetYaxis()->SetTitleOffset(1) ;
  config_profile(hbdf,"","D (cm^{2})","#Counts","ESAME",2,MultiPlotColors(9)) ;
  hbdf->SetMarkerStyle(8) ;
  hdata->SetMarkerStyle(8) ;
  hdata->SetMinimum(0.1) ;
  c->SetLogy() ;
  TLine* line = new TLine(100,0,100,1e5) ;
  line->SetLineStyle(2) ;
  line->Draw("SAME") ;


  TLegend* l = new TLegend(0.44,0.74,0.88,0.88) ;
  l->SetBorderSize(0) ;
  l->AddEntry(hdata,"Data events close to Cobalt source","lep");
  l->AddEntry(hbdf,"Data events far from Cobalt source","lep");


  // rajoute signal far from source simus
  TFile *the3File = new TFile("root_files/tprofiles/simus/tprofile_bkg.root","READ");
  TProfile *hsignal_far = (TProfile*)the3File->Get("distance_stat");
  config_profile(hsignal_far,"","D (cm^{2})","#Counts","ESAME",2,MultiPlotColors(6)) ;
  hsignal_far->SetMarkerStyle(8) ;
  l->AddEntry(hsignal_far,"Signal events far from Cobalt source (simus)","lep");

  // rajoute signal far from source simus
  TFile *the4File = new TFile("root_files/tprofiles/simus/tprofile_data.root","READ");
  TProfile *hsignal_close = (TProfile*)the4File->Get("distance_stat");
  config_profile(hsignal_close,"","D (cm^{2})","#Counts","ESAME",2,MultiPlotColors(5)) ;
  hsignal_close->SetMarkerStyle(8) ;
  l->AddEntry(hsignal_close,"Signal events close to Cobalt source (simus)","lep");


  l->Draw() ;


  c->SaveAs("plots_data/merge_data_bdf.eps") ;


}


double distance_OM(int col1,int row1,int col2,int row2){

  return sqrt(pow((col2-col1),2)+pow((row2-row1),2)) ;

}
