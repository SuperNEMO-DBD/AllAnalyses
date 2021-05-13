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


void Contaminations_cut_Pint(){

  TProfile *hproba_int_nom = new TProfile ("nom","", 10,-0.5,9.5,3e24,6e24) ;
  TProfile *hproba_int_wBi = new TProfile ("wBi","", 10,-0.5,9.5,3e24,6e24) ;
  TProfile *hproba_int_woBi = new TProfile ("woBi","", 10,-0.5,9.5,3e24,6e24) ;

  for (int i = 0; i < 3; ++i) {

    TTree *cut_proba = new TTree("t_cut_proba","t_cut_proba") ;

    if (i==0) {
      cut_proba->ReadFile("results_cuts_cont_nominales.txt","BorneInf/F:BorneSup/F:T12/F") ;
    }
    if (i==1) {
      cut_proba->ReadFile("results_cuts_cont_measured_wBi.txt","BorneInf/F:BorneSup/F:T12/F") ;
    }
    if (i==2) {
      cut_proba->ReadFile("results_cuts_cont_measured_woBi.txt","BorneInf/F:BorneSup/F:T12/F") ;
    }

    float BorneInf, BorneSup, T12 ;
    cut_proba->SetBranchAddress("BorneInf",&BorneInf) ;
    cut_proba->SetBranchAddress("BorneSup",&BorneSup) ;
    cut_proba->SetBranchAddress("T12",&T12) ;


    for (int k=0; k<cut_proba->GetEntries(); k++){
      cut_proba->GetEntry(k);

      if (i==0) {
        hproba_int_nom->Fill(k,T12) ;
      }
      if (i==1) {
        hproba_int_wBi->Fill(k,T12) ;
      }
      if (i==2) {
        hproba_int_woBi->Fill(k,T12) ;
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

  TGaxis::SetMaxDigits(2) ;

  config_profile(hproba_int_nom,"","Cut P_{int} (%)","Best limit on T_{1/2} (y)","L",2,kCyan+2) ;
  config_profile(hproba_int_wBi,"","","","SAMEL",2,kSpring-6) ;
  config_profile(hproba_int_woBi,"","","","SAMEL",2,kOrange+7) ;



  auto legend1 = new TLegend(0.57,0.817,0.989,0.974);
  legend1->SetBorderSize(1) ;
  legend1->AddEntry(hproba_int_nom,"Specified act.","l");
  legend1->AddEntry(hproba_int_woBi,"Measured act. w/o ^{214}Bi","l");
  legend1->AddEntry(hproba_int_wBi,"Measured act. w/ ^{214}Bi","l");
  legend1->Draw() ;

  double max = 0. ;
  int binmax = 0. ;
  double xmax = 0. ;

  max = hproba_int_nom->GetMaximum() ;
  binmax = hproba_int_nom->GetMaximumBin() ;
  xmax = hproba_int_nom->GetXaxis()->GetBinCenter(binmax) ;
  TLine* l0 = new TLine(xmax,max,xmax,3e24) ;
  cout << "Nominal " << max << endl ;

  max = hproba_int_woBi->GetMaximum() ;
  binmax = hproba_int_woBi->GetMaximumBin() ;
  xmax = hproba_int_woBi->GetXaxis()->GetBinCenter(binmax) ;
  TLine* l1 = new TLine(xmax,max,xmax,3e24) ;
  cout << "Wo Bi " << max << endl ;

  max = hproba_int_wBi->GetMaximum() ;
  binmax = hproba_int_wBi->GetMaximumBin() ;
  xmax = hproba_int_wBi->GetXaxis()->GetBinCenter(binmax) ;
  TLine* l2 = new TLine(xmax,max,xmax,3e24) ;
  cout << "W Bi " << max << endl ;

  hproba_int_nom->GetYaxis()->SetRangeUser(3e24,6e24) ;

  l0->SetLineStyle(2) ;
  l1->SetLineStyle(2) ;
  l2->SetLineStyle(2) ;
  l0->SetLineColor(kGray+3) ;
  l1->SetLineColor(kGray+3) ;
  l0->Draw("SAME") ;
  l1->Draw("SAME") ;
  l2->Draw("SAME") ;

  c->SaveAs("plots/cont_cut.pdf") ;

}
