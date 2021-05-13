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

using namespace std;


void Contaminations_cut_vertex(string vertex){

  TProfile *hproba_int_nom = new TProfile ("proba_nom","", 10,-10,200,3e24,6e24) ;
  TProfile *hproba_int_wBi = new TProfile ("proba_wBi","", 10,-10,200,3e24,6e24) ;
  TProfile *hproba_int_woBi = new TProfile ("proba_woBi","", 10,-10,200,3e24,6e24) ;

  for (int i = 0; i < 3; ++i) {

    TTree *cut_proba = new TTree("t_cut_proba","t_cut_proba") ;

    if (i==0) {
      cut_proba->ReadFile(Form("results_cuts_%s_cont_nominales.txt",vertex.c_str()),"BorneInf/F:BorneSup/F:T12/F") ;
    }
    if (i==1) {
      cut_proba->ReadFile(Form("results_cuts_%s_cont_measured_wBi.txt",vertex.c_str()),"BorneInf/F:BorneSup/F:T12/F") ;
    }
    if (i==2) {
      cut_proba->ReadFile(Form("results_cuts_%s_cont_measured_woBi.txt",vertex.c_str()),"BorneInf/F:BorneSup/F:T12/F") ;
    }

    float BorneInf, BorneSup, T12 ;
    cut_proba->SetBranchAddress("BorneInf",&BorneInf) ;
    cut_proba->SetBranchAddress("BorneSup",&BorneSup) ;
    cut_proba->SetBranchAddress("T12",&T12) ;

    int tabk[10] = {0,20,40,60,80,100,120,140,160,180} ;

    for (int k=0; k<cut_proba->GetEntries(); k++){
      cut_proba->GetEntry(k);

      cout << tabk[k] << " " << T12 << endl;

      if (i==0) {
        hproba_int_nom->Fill(tabk[k],T12) ;
      }
      if (i==1) {
        hproba_int_wBi->Fill(tabk[k],T12) ;
      }
      if (i==2) {
        hproba_int_woBi->Fill(tabk[k],T12) ;
      }


    }

  }

  TCanvas *c = new TCanvas("canvas1","canvas1");
  c->Range(-0.4891892,-1.046424,4.513513,6.451694);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(2);
  c->SetTopMargin(0.06024097);
  c->SetBottomMargin(0.1395582);
  c->SetFrameBorderMode(0);
  c->SetFrameBorderMode(0);

  TGaxis::SetMaxDigits(3) ;

  config_profile(hproba_int_nom,"",Form("Cut #Delta %s (mm)",vertex.c_str()),"Best limit on T_{1/2} (y)","L",2,kCyan+2) ;
  config_profile(hproba_int_wBi,"","","","SAMEL",2,kSpring-6) ;
  config_profile(hproba_int_woBi,"","","","SAMEL",2,kOrange+7) ;

  hproba_int_nom->GetYaxis()->SetRangeUser(2.5e24,6.5e24) ;

  auto legend1 = new TLegend(0.57,0.817,0.989,0.974);
  legend1->SetBorderSize(1) ;
  legend1->AddEntry(hproba_int_nom,"Specified act.","l");
  legend1->AddEntry(hproba_int_woBi,"Measured act. w/o ^{214}Bi","l");
  legend1->AddEntry(hproba_int_wBi,"Measured act. w/ ^{214}Bi","l");
  legend1->Draw() ;

  double max = hproba_int_woBi->GetMaximum() ;
  int binmax = hproba_int_woBi->GetMaximumBin(); double xmax = hproba_int_woBi->GetXaxis()->GetBinCenter(binmax);

  // TLine* l0 = new TLine(-0.5,max,xmax,max) ;
  // TLine* l1 = new TLine(xmax,max,xmax,3e24) ;
  // TLine* l2 = new TLine(4,3e24,4,6e24) ;
  // // l0->SetLineStyle(2) ;
  // l0->SetLineColor(kGray+3) ;
  // l1->SetLineColor(kGray+3) ;
  // l2->SetLineStyle(7) ;
  // l0->Draw("SAME") ;
  // l1->Draw("SAME") ;
  // l2->Draw("SAME") ;

  c->SaveAs(Form("plots/cont_cut_%s.eps",vertex.c_str())) ;

}
