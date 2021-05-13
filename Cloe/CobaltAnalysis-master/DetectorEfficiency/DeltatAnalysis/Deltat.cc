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



void Deltat(const char* file_data,const char* file_simus){

  TFile *theDataFile = new TFile(file_data,"READ");
  TH1F *htime_data = (TH1F*)theDataFile->Get("tmp");

  TFile *theSimusFile = new TFile(file_simus,"READ");
  TH1F *htime_simus = (TH1F*)theSimusFile->Get("tmp");

  double scale = 0.72 ;
  htime_simus->Scale(scale) ; // 7.2 pour 1e8 simus ; 0.72 pour 1e9 simus

  htime_data->Rebin(6) ;
  htime_simus->Rebin(6) ;


  gStyle->SetOptStat(0) ;
  TCanvas *c = new TCanvas("c","c",10,10,2000,1000) ;

  config_histo1D(htime_simus,"HIST","#Delta t (ns)","#Counts",2,1,MultiPlotColors(0)) ;
  config_histo1D(htime_data,"HISTSAME","#Delta t (ns)","#Counts",2,1,MultiPlotColors(2)) ;

  TLegend* legend1 = new TLegend(0.123,0.721,0.640,0.967);
  // legend1->SetBorderSize(0) ;
  legend1->SetNColumns(2);

  gStyle->SetOptFit(0) ;
  TF1 *f1 = new TF1("f1","gaus",-7,-1) ;
  htime_data->Fit("f1") ;
  f1->Draw("SAME") ;
  f1->SetLineColor(MultiPlotColors(10)) ;
  f1->SetLineStyle(2) ;

  TF1 *f = new TF1("f","gaus",-2,2) ;
  htime_simus->Fit("f") ;
  f->Draw("SAME") ;
  f->SetLineColor(MultiPlotColors(1)) ;
  f->SetLineStyle(2) ;

  float f1_chi2 = f1->GetChisquare() ;
  float f1_ndf = f1->GetNDF() ;
  float f2_chi2 = f->GetChisquare() ;
  float f2_ndf = f->GetNDF() ;

  legend1->AddEntry(htime_data,Form("Data: %1.f entries",htime_data->GetEntries()),"l");
  legend1->AddEntry(htime_simus,Form("Simulations: %1.f entries",htime_simus->GetEntries()*scale),"l");

  legend1->AddEntry(f1,"Gaussian fit","l");
  legend1->AddEntry(f,"Gaussian fit","l");

  legend1->AddEntry((TObject*)0,Form("#chi^{2}/ndf = %1.1f/%1.f",f1_chi2,f1_ndf),"");
  legend1->AddEntry((TObject*)0,Form("#chi^{2}/ndf = %1.1f/%1.f",f2_chi2,f2_ndf),"");

  legend1->AddEntry((TObject*)0,Form("Mean = %1.3f #pm %1.3f ns",f1->GetParameter(1),f1->GetParError(1)),"");
  legend1->AddEntry((TObject*)0,Form("Mean = %1.3f #pm %1.3f ns",f->GetParameter(1),f->GetParError(1)),"");

  legend1->AddEntry((TObject*)0,Form("  #sigma_{t}     = %1.3f #pm %1.3f ns",f1->GetParameter(2),f1->GetParError(2)),"");
  legend1->AddEntry((TObject*)0,Form("  #sigma_{t}     = %1.3f #pm %1.3f ns",f->GetParameter(2),f->GetParError(2)),"");

  legend1->Draw() ;

  c->SaveAs("plots/Deltat.eps") ;


}
