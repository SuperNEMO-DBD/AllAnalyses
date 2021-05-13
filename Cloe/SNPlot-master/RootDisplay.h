// Author: Cloé Girard-Carillo <girardcarillo@lal.in2p3.fr>

#include <TH1F.h>
#include <TH2F.h>

#include "python_colors.h"

using namespace std;

//-----------------------------------------//


void config_canvas(TCanvas *c){
  c->SetLeftMargin(0.1734198);
  c->SetRightMargin(0.02701243);
  c->SetTopMargin(0.04016064);
  c->SetBottomMargin(0.1596386);
}

void config_histo1D(TH1F *histo,const char * draw_type,const char * XaxisTitle=0, const char *YaxisTitle=0,int linewidth=0,int linestyle=0,Color_t linecolor=0)
{
  gStyle->SetOptStat(0);

  histo->GetXaxis()->SetNdivisions(110);
  histo->GetYaxis()->SetNdivisions(110);
  histo->Draw(draw_type);
  histo->GetYaxis()->SetTitleSize(0.05);
  histo->GetXaxis()->SetTitleSize(0.05);
  histo->GetXaxis()->SetTitle(XaxisTitle);
  histo->GetYaxis()->SetTitle(YaxisTitle);
  histo->GetXaxis()->SetLabelSize(0.05);
  histo->GetYaxis()->SetLabelSize(0.05);
  histo->SetLineWidth(linewidth);
  histo->SetLineStyle(linestyle);
  histo->SetLineColor(linecolor);

}


void config_profile(TProfile *profile, const char *profileTitle, const char * XaxisTitle, const char *YaxisTitle,const char * draw_type,int linewidth=0,Color_t linecolor=0){

  profile->GetYaxis()->SetNdivisions(110);
  profile->GetXaxis()->SetNdivisions(110);
  profile->GetYaxis()->SetTitleOffset(0.7) ;
  profile->Draw(draw_type);
  profile->GetYaxis()->SetTitleSize(0.048);
  profile->GetXaxis()->SetTitleSize(0.048);
  profile->SetTitle(profileTitle);
  profile->GetXaxis()->SetTitle(XaxisTitle);
  profile->GetYaxis()->SetTitle(YaxisTitle);
  profile->SetLineColor(linecolor);
  profile->SetLineWidth(linewidth);

  //gStyle->SetOptStat(0);
}


void config_graph(TGraph *graph, const char *graphTitle, const char * XaxisTitle, const char *YaxisTitle,const char * draw_type,double markersize=0,int markerstyle=0,Color_t markercolor=0)
{
  graph->GetYaxis()->SetTitleOffset(0.5) ;
  graph->Draw(draw_type);
  graph->GetYaxis()->SetTitleSize(0.048);
  graph->GetXaxis()->SetTitleSize(0.048);
  graph->SetTitle(graphTitle);
  graph->GetXaxis()->SetTitle(XaxisTitle);
  graph->GetYaxis()->SetTitle(YaxisTitle);
  graph->SetMarkerColor(markercolor);
  graph->SetMarkerStyle(markerstyle);
  graph->SetMarkerSize(markersize);

  //gStyle->SetOptStat(0);
}


void config_histo2D(TH2D *histo, const char *histoTitle, const char * XaxisTitle, const char *YaxisTitle,const char * draw_type)
{
  histo->GetXaxis()->SetNdivisions(110);
  histo->GetYaxis()->SetNdivisions(110);
  histo->Draw(draw_type);
  histo->GetYaxis()->SetTitleSize(0.048);
  histo->GetXaxis()->SetTitleSize(0.048);
  histo->SetTitle(histoTitle);
  histo->GetXaxis()->SetTitle(XaxisTitle);
  histo->GetYaxis()->SetTitle(YaxisTitle);

  // gStyle->SetOptStat(0);
}


void SetPaveStat(TH1F *histo){
  TPaveStats *st0 = new TPaveStats() ;
  st0 = (TPaveStats*)histo->GetListOfFunctions()->FindObject("stats") ;
  if (st0 != NULL) {
    st0->SetX1NDC(.78) ;  // left
    st0->SetY1NDC(.87) ;  // bottom
    st0->SetX2NDC(.98) ;  // right
    st0->SetY2NDC(.94) ;  // top
  }
  delete st0 ;
}

void SetPaveStat(TH1F *histo,double l,double b,double r,double t){
  TPaveStats *st0 = new TPaveStats() ;
  st0 = (TPaveStats*)histo->GetListOfFunctions()->FindObject("stats") ;
  if (st0 != NULL) {
    st0->SetX1NDC(l) ;  // left
    st0->SetY1NDC(b) ;  // bottom
    st0->SetX2NDC(r) ;  // right
    st0->SetY2NDC(t) ;  // top
  }
  delete st0 ;
}

Color_t MultiPlotColors(int color_code, TH1F *histo = 0){

  Color_t color_tab[17]={kRed+2,kOrange-3,kSpring-6,kCyan,kViolet,kBlue+2,kOrange,kMagenta+3,kOrange+10,kPink-9,kTeal-5,kBlack,kAzure+7,kGray,kSpring-2,kGray+2} ;

  int test = color_code/17 ;
  if (histo) {
    histo->SetFillColorAlpha(color_tab[color_code%17], 0.1);
  }

  return color_tab[color_code%17] ;

}

void ReverseXAxis (TH2 *h)
{
  // Remove the current axis
  h->GetXaxis()->SetLabelOffset(999);
  h->GetXaxis()->SetTickLength(0);

  // Redraw the new axis
  gPad->Update();
  TGaxis *newaxis = new TGaxis(gPad->GetUxmax(),
                               gPad->GetUymin(),
                               gPad->GetUxmin(),
                               gPad->GetUymin(),
                               h->GetXaxis()->GetXmin(),
                               h->GetXaxis()->GetXmax(),
                               510,"-");
  newaxis->SetLabelOffset(-0.03);
  newaxis->Draw();
}

void RatioCanvas(TH1F *histo1, TH1F *histo2, string histoname1, string histoname2, string Xaxisname, string Yaxisname, string plotname){

  // Define the Canvas
  TCanvas *c = new TCanvas("c", "canvas",10,10,2000,1000);
  gStyle->SetOptStat(0);
  // Upper plot will be in pad1
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetTopMargin(0.0172117);
  pad1->SetBottomMargin(0.008892714);
  pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad

  THStack *hs = new THStack("hs","");
  hs->Add(histo1,"HIST") ;
  histo1->SetLineColor(kMagenta+2) ;
  histo1->SetFillColor(0) ;
  hs->Add(histo2,"HIST") ;
  histo2->SetLineColor(kOrange+7) ;
  histo2->SetFillColor(0) ;
  hs->Draw("nostack");
  hs->GetYaxis()->SetTitle("#Counts") ;
  hs->GetYaxis()->SetTitleSize(0.06);
  hs->GetYaxis()->SetTitleOffset(0.7);
  hs->GetYaxis()->SetLabelSize(0.05);
  hs->GetXaxis()->SetRangeUser(0.71,4) ;
  pad1->SetLogy();

  auto legend = new TLegend(0.64,0.71,0.89,0.97);
  legend->AddEntry(histo1,histoname1.c_str(),"l");
  legend->AddEntry(histo2,histoname2.c_str(),"l");
  legend->Draw();
  // plot will be in pad2
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.005, 1, 0.303);
  pad2->SetTopMargin(0.02287);
  pad2->SetBottomMargin(0.3235088);
  pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  pad2->SetLogy();

  // Define the ratio plot
  TH1F *hRatio = (TH1F*)histo1->Clone("hRatio");
  // hRatio->Sumw2();
  hRatio->SetStats(0);      // No statistics on lower plot
  hRatio->Divide(histo2);
  TLine *line = new TLine(0.71,1,4,1);
  config_histo1D(hRatio,"HIST",Xaxisname.c_str(),Yaxisname.c_str(),2,1,1);
  hRatio->SetMarkerStyle(8) ;
  hRatio->SetMarkerSize(0.5) ;
  hRatio->SetMarkerColor(MultiPlotColors(0)) ;
  hRatio->GetXaxis()->SetRangeUser(0.71,4) ;

  hRatio->GetXaxis()->SetTitleSize(0.15);
  hRatio->GetYaxis()->SetTitleSize(0.15);
  hRatio->GetYaxis()->SetTitleOffset(0.3);
  hRatio->GetXaxis()->SetLabelSize(0.13);
  hRatio->GetYaxis()->SetLabelSize(0.13);
  hRatio->SetStats(0);
  hRatio->SetTitle("");
  line->Draw("SAME");

  c->SaveAs(plotname.c_str());



}

THStack *config_hstack(TH1F *histo1, TH1F *histo2, string histoname1, string histoname2, string Xaxisname, string Yaxisname, int linecolor, string plotname){

  TCanvas *c = new TCanvas("c", "canvas",10,10,2000,1000);
  gStyle->SetOptStat(0);

  THStack *hs = new THStack("hs","");
  hs->Add(histo1,"HIST") ;
  histo1->SetLineColor(MultiPlotColors(0)) ;
  histo1->SetFillColor(0) ;
  hs->Add(histo2,"HIST") ;
  histo2->SetLineColor(MultiPlotColors(2)) ;
  histo2->SetFillColor(0) ;
  hs->Draw("nostack");
  hs->GetYaxis()->SetTitle(Yaxisname.c_str()) ;
  hs->GetXaxis()->SetTitle(Xaxisname.c_str()) ;
  hs->GetYaxis()->SetTitleSize(0.05);
  hs->GetYaxis()->SetLabelSize(0.05);
  hs->GetYaxis()->SetTitleOffset(0.7);
  hs->GetXaxis()->SetTitleSize(0.05);
  hs->GetXaxis()->SetLabelSize(0.05);


  c->SaveAs(plotname.c_str());

  return hs ;
}
