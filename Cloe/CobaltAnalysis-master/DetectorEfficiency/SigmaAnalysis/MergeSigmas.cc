// Author Cloé Girard-Carillo girardcarillo@lal.in2p3.fr
// macro to draw two 1d histograms (data + simus) in same canvas: files sigma_i_j.root
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

void MergeSigmas(){

  TH1F *hdata = new TH1F("hdata","",100, 0.1, 1.6) ;
  string file_data ;
  TFile *theDataFile ;
  TH2F *h2data ;

  TH1F *hsimus = new TH1F("hsimus","",100, 0.1, 1.6) ;
  string file_simus ;
  TFile *theSimusFile ;
  TH2F *h2simus ;

  TProfile *hsigma_distance_data = new TProfile ("sigma_data vs distance","", 50, -1, 12, -1, 260) ;
  TProfile *hsigma_distance_simus = new TProfile ("sigma_simus vs distance","", 50, -1, 12, -1, 260) ;
  TH1F *hstat_data = new TH1F("stat_data","",25, 0, 260) ;
  TH1F *hstat_simus = new TH1F("stat_simus","",25, 0, 260) ;

  for (int i = 0; i < column_tot_number; ++i) {
    for (int j = 0; j < row_tot_number; ++j) {

      file_data = Form("data/sigma_%d-%d.root",i,j) ;
      theDataFile  = new TFile(file_data.c_str(),"READ") ;
      h2data =  new TH2F ("h2data","", column_tot_number+2, -1, column_tot_number+1, row_tot_number+2, -1, row_tot_number+1) ;
      h2data = (TH2F*)theDataFile->Get("sigma") ;

      file_simus = Form("simus/sigma_%d-%d.root",i,j) ;
      theSimusFile  = new TFile(file_simus.c_str(),"READ") ;
      h2simus =  new TH2F ("h2simus","", column_tot_number+2, -1, column_tot_number+1, row_tot_number+2, -1, row_tot_number+1) ;
      h2simus = (TH2F*)theSimusFile->Get("sigma") ;

      double data = 0. ;
      int stat_data = h2data->GetEntries() ;
      hstat_data->Fill(stat_data) ;
      hsigma_distance_data->Fill(distance_OM(9,6,i,j),stat_data) ;
      double simus = 0. ;
      int stat_simus = h2simus->GetEntries() ;
      hstat_simus->Fill(stat_simus) ;
      hsigma_distance_simus->Fill(distance_OM(9,6,i,j),stat_simus) ;
      for (int k = 0 ; k < column_tot_number ; ++k) {
        for (int l = 0 ; l < row_tot_number ; ++l) {
          data = h2data->GetBinContent(k+2,l+2) ;
          if (data != 0) {
            hdata->Fill(data) ;
          }
          simus = h2simus->GetBinContent(k+2,l+2) ;
          if (simus != 0) {
            hsimus->Fill(simus) ;
          }

        }
      }
    }
  }


  // TF1 *f1 = new TF1("f1","gaus",0,10) ;
  // hsigma_distance_data->Fit("f1") ;
  // f1->Draw("SAME") ;
  // f1->SetLineColor(MultiPlotColors(1)) ;
  // f1->SetLineStyle(2) ;

  gStyle->SetOptStat(0) ;
  TCanvas *c1 = new TCanvas("c1","c1",10,10,2000,1000) ;

  config_profile(hsigma_distance_simus, "", "Distance from source (a.u.)", "Number of characterised OM pairs","",2,MultiPlotColors(0)) ;
  config_profile(hsigma_distance_data, "", "Distance from source (a.u.)", "Number of characterised OM pairs","SAME",2,MultiPlotColors(2)) ;



  TF1 *f2 = new TF1("f2","gaus",0.2,1.6) ;
  hsigma_distance_data->Fit("f2") ;
  f2->Draw("SAME") ;
  f2->SetLineColor(MultiPlotColors(1)) ;
  f2->SetLineStyle(2) ;

  TF1 *f3 = new TF1("f3","gaus",0.1,0.5) ;
  hsigma_distance_simus->Fit("f3") ;
  f3->Draw("SAME") ;
  f3->SetLineColor(MultiPlotColors(1)) ;
  f3->SetLineStyle(2) ;



  hsigma_distance_data->SetMarkerStyle(8) ;
  hsigma_distance_simus->SetMarkerStyle(8) ;

  TLegend* legend1 = new TLegend(0.662,0.769,0.984,0.964);

  legend1->AddEntry(hsigma_distance_data,"Data","lep");
  legend1->AddEntry(hsigma_distance_simus,"Simulations","lep");

  legend1->Draw() ;

  //c1->SetLogy() ;

  c1->SaveAs("plots/sigma_distance.eps") ;



  TCanvas *c = new TCanvas("c","c",10,10,2000,1000) ;
  c->Range(-0.0875,-23.60853,1.788514,160.0954);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(2);
  c->SetTopMargin(0.07128514);
  c->SetBottomMargin(0.1285141);
  c->SetFrameBorderMode(0);
  c->SetFrameBorderMode(0);

  config_histo1D(hsimus,"HIST","#sigma_{t} (ns)","#Counts",2,1,MultiPlotColors(0)) ;
  config_histo1D(hdata,"HISTSAME","#sigma_{t} (ns)","#Counts",2,1,MultiPlotColors(2)) ;

  gStyle->SetOptFit(0) ;
  gStyle->SetOptStat(0) ;

  TF1 *f1 = new TF1("f1","gaus",0.2,1.6) ;
  hdata->Fit("f1") ;
  // f1->Draw("SAME") ;
  // f1->SetLineColor(MultiPlotColors(1)) ;
  // f1->SetLineStyle(2) ;

  TF1 *f = new TF1("f","gaus",0.1,0.5) ;
  hsimus->Fit("f") ;
  // f->Draw("SAME") ;
  // f->SetLineColor(MultiPlotColors(1)) ;
  // f->SetLineStyle(2) ;

  float f1_chi2 = f1->GetChisquare() ;
  float f1_ndf = f1->GetNDF() ;
  float f2_chi2 = f->GetChisquare() ;
  float f2_ndf = f->GetNDF() ;

  cout << "fit data: " << f1_chi2 << "/" << f1_ndf << endl ;
  cout << "fit simus: " << f2_chi2 << "/" << f2_ndf << endl ;

  TLegend* legend = new TLegend(0.458,0.531,0.891,0.917);
  // legend->SetNColumns(2);
  legend->SetBorderSize(0) ;

  legend->AddEntry(hdata,Form("Data: %1.f entries",hdata->GetEntries()),"l");
  legend->AddEntry((TObject*)0,Form("Mean = %1.3f ns",f1->GetParameter(1)),"");
  legend->AddEntry((TObject*)0,Form("Std dev = %1.3f ns",f1->GetParameter(2)),"");
  legend->AddEntry(hsimus,Form("Simulations: %1.f entries",hsimus->GetEntries()),"l");
  legend->AddEntry((TObject*)0,Form("Mean = %1.3f ns",f->GetParameter(1)),"");
  legend->AddEntry((TObject*)0,Form("Std dev = %1.3f ns",f->GetParameter(2)),"");

  // legend->AddEntry(/*gr_celerity->GetFunction("f1")*/f1,"Gaussian fit","");
  // legend->AddEntry(/*gr_celerity->GetFunction("f")*/f,"Gaussian fit","");
  // legend->AddEntry((TObject*)0,Form("#chi^{2}/ndf = %1.1f/%1.f",f1_chi2,f1_ndf),"");
  // legend->AddEntry((TObject*)0,Form("#chi^{2}/ndf = %1.1f/%1.f",f2_chi2,f2_ndf),"");
  // legend->AddEntry((TObject*)0,Form("Mean = %1.3f #pm %1.3f ns",f1->GetParameter(1),f1->GetParError(1)),"");
  // legend->AddEntry((TObject*)0,Form("Mean = %1.3f #pm %1.3f ns",f->GetParameter(1),f->GetParError(1)),"");
  // legend->AddEntry((TObject*)0,Form("  #sigma_{t}     = %1.3f #pm %1.3f ns",f1->GetParameter(2),f1->GetParError(2)),"");
  // legend->AddEntry((TObject*)0,Form("  #sigma_{t}     = %1.3f #pm %1.3f ns",f->GetParameter(2),f->GetParError(2)),"");

  legend->Draw() ;

  c->SaveAs("plots/Sigma.eps") ;



  // hdata->SaveAs("data/Sigma_tot.root") ;
  // hsimus->SaveAs("simus/Sigma_tot.root") ;

}


double distance_OM(int col1,int row1,int col2,int row2){

  return sqrt(pow((col2-col1),2)+pow((row2-row1),2)) ;

}
