#include <stdio.h>
#include <TMath.h>
#include <TCanvas.h>
#include <iostream>
#include <TROOT.h>
#include <TChain.h>
#include <TObject.h>
#include <TRandom.h>
#include <TFile.h>
#include <math.h>
#include <TF1Convolution.h>
#include <TF1.h>
#include <TH1F.h>
#include <TGraph.h>
#include <TStopwatch.h>

using namespace std;

void draw_convol(double sigma_tot, double noised_time_difference, bool test=0)
{

  double min_f = -1.5 ;
  double max_f = 2.5 ;

  Double_t tau = 0.294; //ns
  Double_t slope = 1/tau;


  double maximumX = 0 ;
  double evalY = 0 ;
  double eval_ex = 0 ;
  double evalNearMax = 0 ;
  double symmetric_noised_time_difference = 0 ;
  double symmetric_ex = 0 ;
  double NearMax = 0 ;

  double integral1 = 0 ;
  double integral2 = 0 ;
  double integral = 0 ;

  TF1 *f_expogauss = new TF1("f_expogauss","([0]/2)*exp(([0]/2)*(2*[2]+[0]*pow([1],2)-2*(x)))*erfc(([2]+[0]*pow([1],2)-(x))/(sqrt(2)*[1]))",min_f,max_f);
  f_expogauss->SetParameters(slope,sigma_tot,0);
  TF1 *f_expogauss_left, *f_expogauss_right ;
  TF1 *f_expogauss_left_ex, *f_expogauss_right_ex ;

  maximumX = f_expogauss->GetMaximumX(min_f,max_f);
  evalY = f_expogauss->Eval(noised_time_difference);

  if (noised_time_difference<0) {

    cout << "case 1" << endl ;

    symmetric_noised_time_difference = f_expogauss->GetX(evalY,0,max_f) ;
    eval_ex = f_expogauss->Eval(0);
    symmetric_ex = f_expogauss->GetX(eval_ex,maximumX,max_f) ;

    f_expogauss_left = new TF1("f_expogauss","([0]/2)*exp(([0]/2)*(2*[2]+[0]*pow([1],2)-2*(x)))*erfc(([2]+[0]*pow([1],2)-(x))/(sqrt(2)*[1]))",min_f,noised_time_difference) ;
    f_expogauss_right = new TF1("f_expogauss","([0]/2)*exp(([0]/2)*(2*[2]+[0]*pow([1],2)-2*(x)))*erfc(([2]+[0]*pow([1],2)-(x))/(sqrt(2)*[1]))",symmetric_noised_time_difference,max_f) ;

    f_expogauss_left_ex = new TF1("f_expogauss","([0]/2)*exp(([0]/2)*(2*[2]+[0]*pow([1],2)-2*(x)))*erfc(([2]+[0]*pow([1],2)-(x))/(sqrt(2)*[1]))",min_f,0) ;
    f_expogauss_right_ex = new TF1("f_expogauss","([0]/2)*exp(([0]/2)*(2*[2]+[0]*pow([1],2)-2*(x)))*erfc(([2]+[0]*pow([1],2)-(x))/(sqrt(2)*[1]))",symmetric_ex,max_f) ;

  }
  else if (noised_time_difference>0) {

    if (noised_time_difference<maximumX) {

      cout << "case 3" << endl ;

      symmetric_noised_time_difference = f_expogauss->GetX(evalY,maximumX,max_f) ;
      NearMax = maximumX ;
      evalNearMax = f_expogauss->Eval(NearMax);
      symmetric_ex = f_expogauss->GetX(evalNearMax,maximumX,max_f) ;

      f_expogauss_left = new TF1("f_expogauss","([0]/2)*exp(([0]/2)*(2*[2]+[0]*pow([1],2)-2*(x)))*erfc(([2]+[0]*pow([1],2)-(x))/(sqrt(2)*[1]))",min_f,noised_time_difference) ;
      f_expogauss_right = new TF1("f_expogauss","([0]/2)*exp(([0]/2)*(2*[2]+[0]*pow([1],2)-2*(x)))*erfc(([2]+[0]*pow([1],2)-(x))/(sqrt(2)*[1]))",symmetric_noised_time_difference,max_f) ;

      f_expogauss_left_ex = new TF1("f_expogauss","([0]/2)*exp(([0]/2)*(2*[2]+[0]*pow([1],2)-2*(x)))*erfc(([2]+[0]*pow([1],2)-(x))/(sqrt(2)*[1]))",min_f,NearMax) ;
      f_expogauss_right_ex = new TF1("f_expogauss","([0]/2)*exp(([0]/2)*(2*[2]+[0]*pow([1],2)-2*(x)))*erfc(([2]+[0]*pow([1],2)-(x))/(sqrt(2)*[1]))",symmetric_ex,max_f) ;

    }

    else {

      cout << "case 2" << endl ;

      symmetric_noised_time_difference = f_expogauss->GetX(evalY,min_f,maximumX) ;
      NearMax = maximumX ;
      evalNearMax = f_expogauss->Eval(NearMax);
      symmetric_ex = f_expogauss->GetX(evalNearMax,maximumX,max_f) ;

      f_expogauss_left = new TF1("f_expogauss","([0]/2)*exp(([0]/2)*(2*[2]+[0]*pow([1],2)-2*(x)))*erfc(([2]+[0]*pow([1],2)-(x))/(sqrt(2)*[1]))",min_f,symmetric_noised_time_difference) ;
      f_expogauss_right = new TF1("f_expogauss","([0]/2)*exp(([0]/2)*(2*[2]+[0]*pow([1],2)-2*(x)))*erfc(([2]+[0]*pow([1],2)-(x))/(sqrt(2)*[1]))",noised_time_difference,max_f) ;

      f_expogauss_left_ex = new TF1("f_expogauss","([0]/2)*exp(([0]/2)*(2*[2]+[0]*pow([1],2)-2*(x)))*erfc(([2]+[0]*pow([1],2)-(x))/(sqrt(2)*[1]))",min_f,NearMax) ;
      f_expogauss_right_ex = new TF1("f_expogauss","([0]/2)*exp(([0]/2)*(2*[2]+[0]*pow([1],2)-2*(x)))*erfc(([2]+[0]*pow([1],2)-(x))/(sqrt(2)*[1]))",symmetric_ex,max_f) ;


    }
  }

  f_expogauss_left->SetParameters(slope,sigma_tot,0);
  f_expogauss_right->SetParameters(slope,sigma_tot,0);

  f_expogauss_left_ex->SetParameters(slope,sigma_tot,0);
  f_expogauss_right_ex->SetParameters(slope,sigma_tot,0);

  //   integral1 = f_expogauss->Integral(min_f,noised_time_difference);
  //   integral2 = f_expogauss->Integral(symmetric_noised_time_difference,max_f);


  // // draw integral
  TCanvas *c1 = new TCanvas("c1", "c1",67,87,700,500);
  c1->Range(-2.916816,-0.1752569,3.326476,0.9402293);
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetLeftMargin(0.1468481);
  c1->SetRightMargin(0.05229226);
  c1->SetTopMargin(0.04458599);
  c1->SetBottomMargin(0.1571125);
  c1->SetFrameBorderMode(0);
  c1->SetFrameBorderMode(0);

  if (!test) {

  f_expogauss->Draw() ;
  f_expogauss->GetXaxis()->SetTitle("#Delta t^{corr} (ns)") ;
  f_expogauss->GetYaxis()->SetTitle("(E #otimes G)_{#tau,#mu,#sigma}(#Delta t)") ;
  f_expogauss->SetTitle("") ;

  f_expogauss->SetLineColor(1) ;
  f_expogauss->SetLineWidth(3) ;

  f_expogauss->GetXaxis()->SetNdivisions(110);
  f_expogauss->GetYaxis()->SetNdivisions(110);
  f_expogauss->GetYaxis()->SetTitleSize(0.07);
  f_expogauss->GetXaxis()->SetTitleSize(0.07);
  f_expogauss->GetXaxis()->SetLabelSize(0.07);
  f_expogauss->GetYaxis()->SetLabelSize(0.07);

  f_expogauss->GetXaxis()->SetTickSize(0.025) ;
  f_expogauss->GetYaxis()->SetTickSize(0.015) ;
  f_expogauss->GetXaxis()->SetLabelFont(42) ;
  f_expogauss->GetYaxis()->SetLabelFont(42) ;
  f_expogauss->GetXaxis()->SetTitleFont(42) ;
  f_expogauss->GetYaxis()->SetTitleFont(42) ;


  f_expogauss_left->Draw("SAME FC") ;
  f_expogauss_left->SetLineColor(1) ;
  f_expogauss_left->SetFillColorAlpha(kRed+3,0.35) ;
  f_expogauss_left->SetFillStyle(1001);

  f_expogauss_right->Draw("SAME FC") ;
  f_expogauss_right->SetLineColor(1) ;
  f_expogauss_right->SetFillColorAlpha(kRed+3,0.35) ;
  f_expogauss_right->SetFillStyle(1001);

  f_expogauss_left_ex->Draw("SAME FC") ;
  f_expogauss_left_ex->SetLineColor(1) ;
  f_expogauss_left_ex->SetFillStyle(3663) ;
  f_expogauss_left_ex->SetFillColor(kRed+3) ;
  // f_expogauss_left_ex->SetFillColorAlpha(kRed+3,0.15) ;
  // f_expogauss_left_ex->SetFillStyle(1001);

  f_expogauss_right_ex->Draw("SAME FC") ;
  f_expogauss_right_ex->SetLineColor(1) ;
  f_expogauss_right_ex->SetFillStyle(3663) ;
  f_expogauss_right_ex->SetFillColor(kRed+3) ;
  // f_expogauss_right_ex->SetFillColorAlpha(kRed+3,0.15) ;
  // f_expogauss_right_ex->SetFillStyle(1001);

  if (noised_time_difference<0) {

    // f_expogauss_left->Draw("SAME FC") ;
    // f_expogauss_left->SetLineColor(1) ;
    // f_expogauss_left->SetFillColorAlpha(kRed+3,0.35) ;
    // f_expogauss_left->SetFillStyle(1001);

    // f_expogauss_right->Draw("SAME FC") ;
    // f_expogauss_right->SetLineColor(1) ;
    // f_expogauss_right->SetFillColorAlpha(kRed+3,0.35) ;
    // f_expogauss_right->SetFillStyle(1001);

    // f_expogauss_left_ex->Draw("SAME FC") ;
    // f_expogauss_left_ex->SetLineColor(1) ;
    // f_expogauss_left_ex->SetFillStyle(3663) ;
    // f_expogauss_left_ex->SetFillColor(kRed+3) ;
    // // f_expogauss_left_ex->SetFillColorAlpha(kRed+3,0.15) ;
    // // f_expogauss_left_ex->SetFillStyle(1001);

    // f_expogauss_right_ex->Draw("SAME FC") ;
    // f_expogauss_right_ex->SetLineColor(1) ;
    // f_expogauss_right_ex->SetFillStyle(3663) ;
    // f_expogauss_right_ex->SetFillColor(kRed+3) ;
    // // f_expogauss_right_ex->SetFillColorAlpha(kRed+3,0.15) ;
    // // f_expogauss_right_ex->SetFillStyle(1001);

    TLine *l0 = new TLine(noised_time_difference,0,noised_time_difference,evalY) ;
    l0->SetLineWidth(3) ;
    //l0->SetLineStyle(2) ;
    l0->Draw() ;
    TLine *l1 = new TLine(symmetric_noised_time_difference,0,symmetric_noised_time_difference,evalY) ;
    l1->SetLineWidth(3) ;
    // l1->SetLineStyle(2) ;
    l1->Draw() ;

    TLine *l2 = new TLine(min_f,evalY,symmetric_noised_time_difference,evalY) ;
    l2->SetLineWidth(3) ;
    // l2->SetLineStyle(2) ;
    l2->Draw() ;


    auto t1 = new TPaveText(0.3173352,0.003184713,0.4448424,0.07324841,"NDC");
    t1->SetBorderSize(0) ;
    t1->SetFillColor(0) ;
    t1->SetTextSize(0.07) ;
    t1->AddText("#Delta t^{meas} < 0") ;
    t1->Draw() ;

    auto t2 = new TPaveText(0.5415473,0.003184713,0.6690544,0.07324841,"NDC");
    t2->SetBorderSize(0) ;
    t2->SetFillColor(0) ;
    t2->SetTextSize(0.07) ;
    t2->AddText("#Delta t^{meas}_{sym}") ;
    t2->Draw() ;



    TLine *l3 = new TLine(0,0,0,eval_ex) ;
    l3->SetLineColor(kRed+3) ;
    l3->SetLineWidth(3) ;
    l3->SetLineStyle(7) ;
    l3->Draw() ;

    TLine *l4 = new TLine(symmetric_ex,0,symmetric_ex,eval_ex) ;
    l4->SetLineColor(kRed+3) ;
    l4->SetLineWidth(3) ;
    l4->SetLineStyle(7) ;
    l4->Draw() ;

    TLine *l5 = new TLine(symmetric_ex,eval_ex,min_f,eval_ex) ;
    l5->SetLineColor(kRed+3) ;
    l5->SetLineWidth(3) ;
    l5->SetLineStyle(7) ;
    l5->Draw() ;


    auto leg = new TLegend(0.6647564,0.7834395,0.9383954,0.9087049);
    leg->SetBorderSize(0) ;
    leg->AddEntry(f_expogauss_left_ex,"Maximal area","f");
    leg->AddEntry(f_expogauss_left,"Example","f");
    leg->Draw() ;

    c1->SaveAs("../plots/proba_expo_1.pdf") ;

  }


  else if (noised_time_difference>0) {

    if (noised_time_difference>maximumX) {

      TLine *l0 = new TLine(noised_time_difference,0,noised_time_difference,evalY) ;
      l0->SetLineWidth(3) ;
      l0->Draw() ;

      TLine *l1 = new TLine(symmetric_noised_time_difference,0,symmetric_noised_time_difference,evalY) ;
      l1->SetLineWidth(3) ;
      l1->Draw() ;

      TLine *l2 = new TLine(min_f,evalY,noised_time_difference,evalY) ;
      l2->SetLineWidth(3) ;
      l2->Draw() ;


      auto t1 = new TPaveText(0.3173352,0.003184713,0.4448424,0.07324841,"NDC");
      t1->SetBorderSize(0) ;
      t1->SetFillColor(0) ;
      t1->SetTextSize(0.07) ;
      t1->AddText("#Delta t^{meas}_{sym}") ;
      t1->Draw() ;

      auto t2 = new TPaveText(0.5415473,0.003184713,0.6690544,0.07324841,"NDC");
      t2->SetBorderSize(0) ;
      t2->SetFillColor(0) ;
      t2->SetTextSize(0.07) ;
      t2->AddText("#Delta t^{meas} > 0") ;
      t2->Draw() ;


      auto t3 = new TPaveText(0.2363897,0.8301486,0.3638968,0.9002123,"NDC");
      t3->SetBorderSize(0) ;
      t3->SetFillColor(0) ;
      t3->SetTextColor(kRed+3) ;
      t3->SetTextSize(0.07) ;
      t3->AddText("Max") ;
      t3->Draw() ;

      TLine *l3 = new TLine(maximumX,f_expogauss->GetMaximum(),min_f,f_expogauss->GetMaximum()) ;
      l3->SetLineColor(kRed+3) ;
      l3->SetLineWidth(3) ;
      l3->SetLineStyle(7) ;
      l3->Draw() ;

      auto leg = new TLegend(0.6647564,0.7834395,0.9383954,0.9087049);
      leg->SetBorderSize(0) ;
      leg->AddEntry(f_expogauss_left_ex,"Maximal area","f");
      leg->AddEntry(f_expogauss_left,"Example","f");
      leg->Draw() ;

      c1->SaveAs("../plots/proba_expo_2.pdf") ;

    }

    else {

      // f_expogauss_left->Draw("SAME FC") ;
      // f_expogauss_left->SetLineColor(1) ;
      // f_expogauss_left->SetFillColorAlpha(kRed+3,0.35) ;
      // f_expogauss_left->SetFillStyle(1001);

      // f_expogauss_right->Draw("SAME FC") ;
      // f_expogauss_right->SetLineColor(1) ;
      // f_expogauss_right->SetFillColorAlpha(kRed+3,0.35) ;
      // f_expogauss_right->SetFillStyle(1001);

      TLine *l0 = new TLine(noised_time_difference,0,noised_time_difference,evalY) ;
      l0->SetLineWidth(3) ;
      l0->Draw() ;

      TLine *l1 = new TLine(symmetric_noised_time_difference,0,symmetric_noised_time_difference,evalY) ;
      l1->SetLineWidth(3) ;
      l1->Draw() ;

      TLine *l2 = new TLine(min_f,evalY,symmetric_noised_time_difference,evalY) ;
      l2->SetLineWidth(3) ;
      l2->Draw() ;



      auto t1 = new TPaveText(0.3424069,0.004246285,0.469914,0.0743099,"NDC");
      t1->SetBorderSize(0) ;
      t1->SetFillColor(0) ;
      t1->SetTextSize(0.07) ;
      t1->AddText("#Delta t^{meas}") ;
      t1->Draw() ;

      auto t2 = new TPaveText(0.5243553,0.003184713,0.6518625,0.07324841,"NDC");
      t2->SetBorderSize(0) ;
      t2->SetTextSize(0.07) ;
      t2->AddText("#Delta t^{meas}_{sym}") ;
      t2->SetFillColor(0) ;
      t2->Draw() ;

      auto t3 = new TPaveText(0.2363897,0.8619958,0.3638968,0.9044586,"NDC");
      t3->SetBorderSize(0) ;
      t3->SetFillColor(0) ;
      t3->SetTextColor(kRed+3) ;
      t3->SetTextSize(0.07) ;
      t3->AddText("Max") ;
      t3->Draw() ;

      // f_expogauss_left_ex->Draw("SAME FC") ;
      // f_expogauss_left_ex->SetLineColor(1) ;
      // f_expogauss_left_ex->SetFillColorAlpha(kRed+3,0.15) ;
      // f_expogauss_left_ex->SetFillStyle(1001);

      // f_expogauss_right_ex->Draw("SAME FC") ;
      // f_expogauss_right_ex->SetLineColor(1) ;
      // f_expogauss_right_ex->SetFillColorAlpha(kRed+3,0.15) ;
      // f_expogauss_right_ex->SetFillStyle(1001);

      TLine *l3 = new TLine(maximumX,f_expogauss->GetMaximum(),min_f,f_expogauss->GetMaximum()) ;
      l3->SetLineColor(kRed+3) ;
      l3->SetLineWidth(3) ;
      l3->SetLineStyle(7) ;
      l3->Draw() ;

      auto leg = new TLegend(0.6647564,0.7834395,0.9383954,0.9087049);
      leg->SetBorderSize(0) ;
      leg->AddEntry(f_expogauss_left_ex,"Maximal area","f");
      leg->AddEntry(f_expogauss_left,"Example","f");
      leg->Draw() ;

      c1->SaveAs("../plots/proba_expo_3.pdf") ;

    }
  }
  }

  else{


    f_expogauss->Draw() ;
    f_expogauss->GetXaxis()->SetTitle("#Delta t (ns)") ;
    f_expogauss->GetYaxis()->SetTitle("(E #otimes G)_{#tau,#mu,#sigma}(#Delta t)") ;
    f_expogauss->SetTitle("") ;

    f_expogauss->SetLineColor(1) ;
    f_expogauss->SetLineWidth(3) ;

    f_expogauss->GetXaxis()->SetNdivisions(110);
    f_expogauss->GetYaxis()->SetNdivisions(110);
    f_expogauss->GetYaxis()->SetTitleSize(0.07);
    f_expogauss->GetXaxis()->SetTitleSize(0.07);
    f_expogauss->GetXaxis()->SetLabelSize(0.07);
    f_expogauss->GetYaxis()->SetLabelSize(0.07);

    f_expogauss->GetXaxis()->SetTickSize(0.025) ;
    f_expogauss->GetYaxis()->SetTickSize(0.015) ;
    f_expogauss->GetXaxis()->SetLabelFont(42) ;
    f_expogauss->GetYaxis()->SetLabelFont(42) ;
    f_expogauss->GetXaxis()->SetTitleFont(42) ;
    f_expogauss->GetYaxis()->SetTitleFont(42) ;



    f_expogauss_left->Draw("SAME FC") ;
    f_expogauss_left->SetLineColor(1) ;
    f_expogauss_left->SetFillColorAlpha(kRed+3,0.35) ;
    f_expogauss_left->SetFillStyle(1001);

    f_expogauss_right->Draw("SAME FC") ;
    f_expogauss_right->SetLineColor(1) ;
    f_expogauss_right->SetFillColorAlpha(kRed+3,0.35) ;
    f_expogauss_right->SetFillStyle(1001);

    TLine *l0 = new TLine(noised_time_difference,0,noised_time_difference,evalY) ;
    l0->SetLineWidth(2) ;
    l0->SetLineStyle(2) ;
    l0->Draw() ;
    TLine *l1 = new TLine(symmetric_noised_time_difference,0,symmetric_noised_time_difference,evalY) ;
    l1->SetLineWidth(2) ;
    l1->SetLineStyle(2) ;
    l1->Draw() ;

    TLine *l2 = new TLine(min_f,evalY,symmetric_noised_time_difference,evalY) ;
    l2->SetLineWidth(2) ;
    l2->SetLineStyle(2) ;
    l2->Draw() ;


    auto t1 = new TPaveText(0.3832378,0.02229299,0.510745,0.09235669,"NDC");
    t1->SetBorderSize(0) ;
    t1->SetFillColor(0) ;
    t1->SetTextSize(0.07) ;
    t1->AddText("#Delta t^{meas}") ;
    t1->Draw() ;

    auto t2 = new TPaveText(0.5286533,0.005307856,0.6561605,0.07537155,"NDC");
    t2->SetBorderSize(0) ;
    t2->SetFillColor(0) ;
    t2->SetTextSize(0.07) ;
    t2->AddText("#Delta t^{meas}_{sym}") ;
    t2->Draw() ;

    c1->SaveAs("../plots/proba_expo_test.pdf") ;

  }

}
