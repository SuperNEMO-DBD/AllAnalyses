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


void Bdf_comparison(const char* file_data,const char* file_bdf){

  TFile *theDataFile = new TFile(file_data,"READ") ;
  TH2F *h2data = new TH2F ("h2data","", column_tot_number+2, -1, column_tot_number+1, row_tot_number+2, -1, row_tot_number+1) ;
  h2data = (TH2F*)theDataFile->Get("counts") ;

  TFile *theBdfFile = new TFile(file_bdf,"READ") ;
  TH2F *h2bdf = new TH2F ("h2bdf","", column_tot_number+2, -1, column_tot_number+1, row_tot_number+2, -1, row_tot_number+1) ;
  h2bdf = (TH2F*)theBdfFile->Get("counts") ;

  // TH1F *hdata = new TH1F("hdata","",25, 0, 5000) ;
  // TH1F *hbdf = new TH1F("hbdf","",25, 0, 400) ;
  TH1F *hratio = new TH1F("hratio","",25, -10, 110) ;

  double bdf = 0. ;
  double data = 0. ;
  double ratio = 0. ;
  for (int i = 0 ; i < column_tot_number ; ++i) {
    for (int j = 0 ; j < row_tot_number ; ++j) {
      bdf = h2bdf->GetBinContent(i+2,j+2) ;
      data = h2data->GetBinContent(i+2,j+2) ;
      if (bdf != 0) {
        // hbdf->Fill(bdf) ;
        if (data != 0) {
          // hdata->Fill(data) ;
          ratio = data/bdf ;
          hratio->Fill(ratio) ;
        }
      }
    }
  }

  // hdata->Draw() ;
  // hbdf->Draw("SAME") ;

  hratio->Draw() ;

  // TCanvas *c = new TCanvas("c","c",10,10,2000,1000) ;
  // c->Range(-0.0875,-23.60853,1.788514,160.0954);
  // c->SetFillColor(0);
  // c->SetBorderMode(0);
  // c->SetBorderSize(2);
  // c->SetTopMargin(0.07128514);
  // c->SetBottomMargin(0.1285141);
  // c->SetFrameBorderMode(0);
  // c->SetFrameBorderMode(0);

  // config_histo1D(hbdf,"HIST","#sigma_{t} (ns)","#Counts",2,1,MultiPlotColors(0)) ;
  // config_histo1D(hdata,"HISTSAME","#sigma_{t} (ns)","#Counts",2,1,MultiPlotColors(2)) ;


  // gStyle->SetOptFit(0) ;
  // gStyle->SetOptStat(0) ;

  // TF1 *f1 = new TF1("f1","gaus",0.5,1.6) ;
  // hdata->Fit("f1") ;
  // // f1->Draw("SAME") ;
  // // f1->SetLineColor(MultiPlotColors(1)) ;
  // // f1->SetLineStyle(2) ;

  // TF1 *f = new TF1("f","gaus",0.1,0.5) ;
  // hbdf->Fit("f") ;
  // // f->Draw("SAME") ;
  // // f->SetLineColor(MultiPlotColors(1)) ;
  // // f->SetLineStyle(2) ;

  // float f1_chi2 = f1->GetChisquare() ;
  // float f1_ndf = f1->GetNDF() ;
  // float f2_chi2 = f->GetChisquare() ;
  // float f2_ndf = f->GetNDF() ;

  // cout << "fit data: " << f1_chi2 << "/" << f1_ndf << endl ;
  // cout << "fit bdf: " << f2_chi2 << "/" << f2_ndf << endl ;

  // TLegend* legend1 = new TLegend(0.458,0.531,0.891,0.917);
  // // legend1->SetNColumns(2);
  // legend1->SetBorderSize(0) ;

  // legend1->AddEntry(hdata,Form("Data: %1.f entries",hdata->GetEntries()),"l");
  // legend1->AddEntry((TObject*)0,Form("Mean = %1.3f ns",f1->GetParameter(1)),"");
  // legend1->AddEntry((TObject*)0,Form("Std dev = %1.3f ns",f1->GetParameter(2)),"");
  // legend1->AddEntry(hbdf,Form("Simulations: %1.f entries",hbdf->GetEntries()),"l");
  // legend1->AddEntry((TObject*)0,Form("Mean = %1.3f ns",f->GetParameter(1)),"");
  // legend1->AddEntry((TObject*)0,Form("Std dev = %1.3f ns",f->GetParameter(2)),"");

  // // legend1->AddEntry(/*gr_celerity->GetFunction("f1")*/f1,"Gaussian fit","");
  // // legend1->AddEntry(/*gr_celerity->GetFunction("f")*/f,"Gaussian fit","");
  // // legend1->AddEntry((TObject*)0,Form("#chi^{2}/ndf = %1.1f/%1.f",f1_chi2,f1_ndf),"");
  // // legend1->AddEntry((TObject*)0,Form("#chi^{2}/ndf = %1.1f/%1.f",f2_chi2,f2_ndf),"");
  // // legend1->AddEntry((TObject*)0,Form("Mean = %1.3f #pm %1.3f ns",f1->GetParameter(1),f1->GetParError(1)),"");
  // // legend1->AddEntry((TObject*)0,Form("Mean = %1.3f #pm %1.3f ns",f->GetParameter(1),f->GetParError(1)),"");
  // // legend1->AddEntry((TObject*)0,Form("  #sigma_{t}     = %1.3f #pm %1.3f ns",f1->GetParameter(2),f1->GetParError(2)),"");
  // // legend1->AddEntry((TObject*)0,Form("  #sigma_{t}     = %1.3f #pm %1.3f ns",f->GetParameter(2),f->GetParError(2)),"");

  // legend1->Draw() ;

  // c->SaveAs("plots/Sigma.eps") ;

}
