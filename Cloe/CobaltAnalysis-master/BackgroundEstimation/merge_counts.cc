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

double distance_OM(int col1,int row1,int col2,int row2) ;

void merge_counts(const char* file_data,const char* file_bdf){

  int source_column = 0 ;
  int source_row = 6 ;

  TFile *theDataFile = new TFile(file_data,"READ") ;
  TH2F *h2data = new TH2F ("h2data","", column_tot_number+2, -1, column_tot_number+1, row_tot_number+2, -1, row_tot_number+1) ;
  h2data = (TH2F*)theDataFile->Get("counts") ;

  TFile *theBdfFile = new TFile(file_bdf,"READ") ;
  TH2F *h2bdf = new TH2F ("h2bdf","", column_tot_number+2, -1, column_tot_number+1, row_tot_number+2, -1, row_tot_number+1) ;
  h2bdf = (TH2F*)theBdfFile->Get("counts") ;

  TFile *theBdfFile_simus = new TFile("root_files/counts/simus/counts_bkg.root","READ") ;
  TH2F *h2bdf_simus = new TH2F ("h2bdf_simus","", column_tot_number+2, -1, column_tot_number+1, row_tot_number+2, -1, row_tot_number+1) ;
  h2bdf_simus = (TH2F*)theBdfFile_simus->Get("counts") ;

  TFile *theDataFile_simus = new TFile("root_files/counts/simus/counts_data.root","READ") ;
  TH2F *h2data_simus = new TH2F ("h2data_simus","", column_tot_number+2, -1, column_tot_number+1, row_tot_number+2, -1, row_tot_number+1) ;
  h2data_simus = (TH2F*)theDataFile_simus->Get("counts") ;

  TProfile *hratio = new TProfile ("hratio","", 10, 1, 10, 0, 30/*,"S"*/) ;
  TProfile *hdata = new TProfile ("hdata","", 20, 0, 20, 0, 1e6) ;
  TProfile *hdata_simus = new TProfile ("hdata_simus","", 20, 0, 20, 0, 1e6) ;
  TProfile *hbdf = new TProfile ("hbdf","", 20, 0, 20, 0, 1e6) ;
  TProfile *hbdf_simus = new TProfile ("hbdf_simus","", 20, 0, 20, 0, 1e6) ;
  TProfile *hdata_tot = new TProfile ("data_tot","", 20, 0, 20, 0, 1e6) ;
  TProfile *hsimus_tot = new TProfile ("simus_tot","", 20, 0, 20, 0, 1e6) ;

  double bdf = 0. ;
  double bdf_simus = 0. ;
  double data = 0. ;
  double data_simus = 0. ;
  double number_events_bdf = 0 ;
  double number_events_bdf_simus = 0 ;
  double number_events_data = 0 ;
  double number_events_data_simus = 0 ;


  for (int i = 0 ; i < column_tot_number ; ++i) {
    for (int j = 0 ; j < row_tot_number ; ++j) {
      if (distance_OM(i,j,source_column,source_row) < 10) {

        number_events_bdf += h2bdf->GetBinContent(i+2,j+2) ;
        number_events_bdf_simus += h2bdf_simus->GetBinContent(i+2,j+2) ;
        number_events_data += h2data->GetBinContent(i+2,j+2) ;
        number_events_data_simus += h2data_simus->GetBinContent(i+2,j+2) ;
        bdf = h2bdf->GetBinContent(i+2,j+2) ;
        bdf_simus = h2bdf_simus->GetBinContent(i+2,j+2) ;
        data = h2data->GetBinContent(i+2,j+2) ;
        data_simus = h2data_simus->GetBinContent(i+2,j+2) ;


        hbdf->Fill(distance_OM(19-i,j,source_column,source_row),bdf) ;
        hbdf_simus->Fill(distance_OM(19-i,j,source_column,source_row),bdf_simus) ;
        hdata->Fill(distance_OM(i,j,source_column,source_row),data) ;
        hdata_simus->Fill(distance_OM(i,j,source_column,source_row),data_simus) ;

        // remplir histos finaux
        hsimus_tot->Fill(distance_OM(i,j,source_column,source_row),data_simus) ;
        hsimus_tot->Fill(distance_OM(19-i,j,source_column,source_row),bdf_simus) ;
        hdata_tot->Fill(distance_OM(i,j,source_column,source_row),data) ;
        hdata_tot->Fill(distance_OM(19-i,j,source_column,source_row),bdf) ;


        if (h2data->GetBinContent(i+2,j+2) != 0 && h2bdf->GetBinContent(i+2,j+2) != 0) {
          hratio->Fill(distance_OM(i,j,source_column,source_row),h2data->GetBinContent(i+2,j+2)/h2bdf->GetBinContent(i+2,j+2)) ;
        }

      }

      // if (distance_OM(i,j,source_column,source_row) > 10) {
      //   if (h2data->GetBinContent(i+2,j+2) != 0 && h2bdf->GetBinContent(i+2,j+2) != 0) {
      //     hratio->Fill(distance_OM(19-i,j,source_column,source_row),h2data->GetBinContent(i+2,j+2)/h2bdf->GetBinContent(i+2,j+2)) ;
      //   }

      // }
    }
  }

  cout << "far data = " <<  number_events_bdf << " close data = " <<  number_events_data << " far simus = " << number_events_bdf_simus << " close simus = " << number_events_data_simus << endl ;


  // gStyle->SetTextFont(42) ;

  TCanvas *c = new TCanvas("c","c",10,10,2000,1000) ;
  c->SetLeftMargin(0.1307401);
  c->SetRightMargin(0.06969206);
  c->SetTopMargin(0.0813253);
  c->SetBottomMargin(0.1184739);
  c->SetLogy() ;

  config_profile(hsimus_tot,"","D_{ source} (OM units)","#Counts","hist",2,kAzure+9) ;
  hsimus_tot->SetMinimum(0.1) ;
  hsimus_tot->SetMaximum(1e4) ;
  hsimus_tot->GetYaxis()->SetTitleOffset(0.75) ;
  hsimus_tot->SetMarkerStyle(20) ;
  hsimus_tot->SetMarkerSize(1.5) ;

  config_profile(hdata_tot,"","D_{ source} (OM units)","#Counts","SAME",2,kOrange-3) ;
  hdata_tot->SetMarkerSize(1.5) ;
  hdata_tot->SetMarkerStyle(20) ;


  // config_profile(hbdf_simus,"","D_{ source} (OM units)","#Counts","hist",2,kAzure+9) ;
  // hbdf_simus->SetMinimum(0.1) ;
  // hbdf_simus->SetMaximum(1e4) ;
  // hbdf_simus->GetYaxis()->SetTitleOffset(0.75) ;
  // hbdf_simus->SetMarkerStyle(20) ;
  // hbdf_simus->SetMarkerSize(1.5) ;
  // config_profile(hdata_simus,"","D_{ source} (OM units)","#Counts","SAMEhist",2,kAzure+9) ;
  // hdata_simus->SetMarkerStyle(20) ;
  // hdata_simus->SetMarkerSize(1.5) ;

  // config_profile(hdata,"","D_{ source} (OM units)","#Counts","SAME",2,kOrange-3) ;
  // config_profile(hbdf,"","D_{ source} (OM units)","#Counts","SAME",2,kOrange-3) ;
  // hdata->SetMarkerSize(1.5) ;
  // hdata->SetMarkerStyle(20) ;
  // hbdf->SetMarkerSize(1.5) ;
  // hbdf->SetMarkerStyle(20) ;
  // c->SetLogy() ;


  TLegend* l = new TLegend(0.205,0.331,0.354,0.458) ;
  // l->SetBorderSize(0) ;
  l->SetTextSize(0.04);
  l->AddEntry(hsimus_tot,"Monte Carlo","l");
  l->AddEntry(hdata_tot,"Data","lep");
  l->SetTextSize(0.04);
  l->Draw() ;

  TLine* line = new TLine(10,0,10,1e4) ;
  line->SetLineStyle(2) ;
  line->Draw("SAME") ;

  TPaveText *pt = new TPaveText(0.6334412,11000.58,9.655592,38113.11,"br");
  pt->SetBorderSize(0);
  pt->SetTextSize(0.04);
  pt->SetLineColor(1);
  pt->SetLineStyle(1);
  pt->SetLineWidth(1);
  pt->SetFillColor(0);
  pt->SetFillStyle(1001);
  pt->AddText("Events close to Cobalt source");
  pt->Draw("same") ;

  pt = new TPaveText(10.3174,11000.58,19.33955,38113.11,"br");
  pt->SetBorderSize(0);
  pt->SetTextSize(0.04);
  pt->SetLineColor(1);
  pt->SetLineStyle(1);
  pt->SetLineWidth(1);
  pt->SetFillColor(0);
  pt->SetFillStyle(1001);
  pt->AddText("Events far from Cobalt source");
  pt->Draw("same") ;




  c->SaveAs("plots_data/merge_data_bdf.eps") ;

  TCanvas *c1 = new TCanvas("c1","c1",10,10,2000,1000) ;
  config_canvas_classic(c1) ;
  config_profile(hratio,"","D_{ source} (OM units)","S/B","0 L E3",2,kCyan-2) ;
  // config_profile(hratio,"","D_{ source} (OM units)","S/B","same",2,kCyan-2) ;
  hratio->SetFillColorAlpha(kCyan-2,0.35) ;
  hratio->SetLineStyle(2) ;
  hratio->SetMarkerStyle(23) ;
  hratio->SetMarkerSize(2) ;
  hratio->SetMarkerColor(kCyan+3) ;
  // TFrame* f = (TFrame*) c1->FindObject("TFrame");
  // config_frame(f) ;
  c1->SaveAs("plots_data/ratio_distance.pdf") ;


}


double distance_OM(int col1,int row1,int col2,int row2){

  return sqrt(pow((col2-col1),2)+pow((row2-row1),2)) ;

}
