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


void Pint(){

  TCanvas *c = new TCanvas("canvas1","canvas1");
  c->Range(-0.4891892,-1.046424,4.513513,6.451694);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(2);
  c->SetTopMargin(0.06024097);
  c->SetBottomMargin(0.1395582);
  c->SetFrameBorderMode(0);
  c->SetFrameBorderMode(0);
  c->SetLogy() ;

  auto legend = new TLegend(0.811,0.573,0.990,0.974);
  legend->SetBorderSize(1) ;

  string process ;
  int color ;

  for (int i = 0; i < 5; ++i) {
    if (i==0) {
      process = "0nubb" ;
      color = kGreen+4 ;
    }
    if (i==1) {
      process = "2nubb" ;
      color = kCyan+3 ;
    }
    if (i==2) {
      process = "208Tl" ;
      color = kOrange+2 ;
    }
    if (i==3) {
      process = "214Bi" ;
      color = kYellow-3 ;
    }
    if (i==4) {
      process = "222Rn" ;
      color = kTeal+2 ;
    }


    string file_data = Form("~/Workdir/Analyses/SensitivityStudy/InternalProba/root_files/Pint_%s.root",process.c_str()) ;
    TFile *theDataFile = new TFile(file_data.c_str(),"READ") ;

    TH1F *hproba = (TH1F*)theDataFile->Get("proba");
    legend->AddEntry(hproba,process.c_str(),"l");

    if (i==0) {
      config_histo1D(hproba,"HIST","P_{int} (%)","Arbitrary normalisation",2,1,color) ;
      hproba->Scale(0.01) ;
      hproba->GetYaxis()->SetRangeUser(5e1,1e4) ;
      hproba->SetTitle("") ;
    }
    if (i==1) {
      hproba->Scale(0.01) ;
      config_histo1D(hproba,"HISTSAME","P_{int} (%)","Arbitrary normalisation",2,1,color) ;
    }
    else {
      config_histo1D(hproba,"HISTSAME","P_{int} (%)","Arbitrary normalisation",2,1,color) ;
    }
    // hproba->SetLineColor(color) ;
    // hproba->SetLineColor(color) ;

  }

  legend->Draw() ;

  c->SaveAs("plots/Pint.pdf") ;

}
