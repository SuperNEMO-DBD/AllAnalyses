/*******************************************
 * Cheryl Patrick , Oct 2016               *
 * Plot time delay between 2 calo hits     *
 * for gammas from feedthroughs vs 0nubb,  *
 * 2nubb, and gammas from calo wrapper     *
 * and shielding                           *
 *******************************************/
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TLegend.h"
#include "TStyle.h"
#include <iostream>

using namespace std;

class Interaction{
  string legendText_;
  int color_;
  TTree *tree_;
  string filenameText_;
public:
  Interaction(string legendText, int color, string fileName, string filenameText);
  Interaction();
  TTree *GetTree(){return tree_;}
  int GetColor(){return color_;}
  string GetLegendText(){return legendText_;}
  string GetFilenameText(){return filenameText_;}
};

Interaction::Interaction()
{
  legendText_="Undefined";
  filenameText_="Undefined";
  color_=kBlue;
  tree_=new TTree();
}
Interaction::Interaction(string legendText, int color, string fileName, string filenameText)
  {
    legendText_=legendText;
    filenameText_=filenameText;
    color_=color;
    TFile *f=new TFile(fileName.c_str());
    tree_ = (TTree*) f->Get("Sensitivity");
  }

void compareTimeDifferenceForCut(string cut, string directory, string title);



TH1D *MakeCustomHist(TTree *tree, string title, int color, string cut, TLegend *legend, string drawString, string heading, string xtitle, double maximum, bool normalized=true)
{
  TCanvas *c1=new TCanvas("supernemo2","supernemo2",900,600);
  c1->cd();
  TH1D *hist = new TH1D("h",heading.c_str(),50,0,maximum);
  tree->Draw((drawString+" >>h").c_str(),cut.c_str());
  hist->SetLineColor(color);
  hist->SetLineWidth(2);
  if (normalized){
    hist->Scale(1./tree->GetEntries(cut.c_str()));
    hist->GetYaxis()->SetTitle("Events (area normalized to 1)");
  }
  else
    {
      hist->Scale(1./tree->GetEntries());
      hist->GetYaxis()->SetTitle("Events (normalized total entries)");
    }
  hist->GetXaxis()->SetTitle(xtitle.c_str());
  legend->AddEntry(hist,title.c_str(),"L");
  return hist;
}

// TH1D *MakeEfficiencyHist(TH1D *timeHist)
// {
//   TH1D *efficiencyHist=(TH1D*)timeHist->Clone();
//   efficiencyHist->Reset();
//   int nbins=efficiencyHist->GetNbinsX();
//   for (int i=1;i<=nbins;i++)
//     {
//       efficiencyHist->SetBinContent(i,timeHist->Integral(1,i));
//     }
//   efficiencyHist->GetYaxis()->SetTitle("Efficiency of just this cut");
//   efficiencyHist->GetXaxis()->SetTitle("Maximum time delay");
//   return efficiencyHist;
// }

TH2D *MakeInternalExternalProbabilityHist(TTree *tree, string cut,string heading, double xMax, double yMax , bool normalized=true)
{
  
  TCanvas *c1=new TCanvas("supernemo2","supernemo2",900,600);
  c1->cd();
  TH2D *hist=new TH2D("h",heading.c_str(),50,0,xMax,50,0,yMax);
  hist->GetXaxis()->SetTitle("Internal probability");
  hist->GetYaxis()->SetTitle("External probability");
  tree->Draw("sensitivity.external_probability:sensitivity.internal_probability >>h",cut.c_str());
  if (normalized){
    hist->Scale(1./tree->GetEntries(cut.c_str()));
  }
  else
    {
      hist->Scale(1./tree->GetEntries());
    }
  return hist;
}

void MakeInternalExternalProbabilitySet(std::vector<Interaction*> interactions, string cut, string title, string outFilename, string directory,double xMax, double yMax, bool areaNormalize=true)
{
  TCanvas *c=new TCanvas("supernemo","supernemo",900,600);
  for (int i=0;i<interactions.size();i++){
    TH2D *hist= MakeInternalExternalProbabilityHist(interactions.at(i)->GetTree(), cut, title+": "+interactions.at(i)->GetLegendText(), xMax, yMax , areaNormalize);
    c->cd();
    hist->Draw("COLZ");
    string outNameDirectory="plots/feedthroughs/"+directory+"/"+interactions.at(i)->GetFilenameText()+"_"+outFilename;
    c->SaveAs(outNameDirectory.c_str());
    c->SetLogz(true);
    outNameDirectory="plots/feedthroughs/"+directory+"/log_"+interactions.at(i)->GetFilenameText()+"_"+outFilename;
    c->SaveAs(outNameDirectory.c_str());
    c->SetLogz(false);
  }
}
void compareTimeDifferencesFeedthroughs()
{
    string associatedCalCut="sensitivity.passes_two_calorimeters && sensitivity.passes_two_clusters && sensitivity.passes_two_tracks && sensitivity.passes_associated_calorimeters";
    string associatedCalPlusElectronCut="sensitivity.passes_two_calorimeters && sensitivity.passes_two_clusters && sensitivity.passes_two_tracks && sensitivity.passes_associated_calorimeters && sensitivity.number_of_electrons==2";

  string tightEnergyCutNoElectronCut=  "sensitivity.passes_two_calorimeters && sensitivity.passes_two_clusters && sensitivity.passes_two_tracks && sensitivity.passes_associated_calorimeters && (sensitivity.lower_electron_energy+sensitivity.higher_electron_energy)>=2.8 &&  (sensitivity.lower_electron_energy+sensitivity.higher_electron_energy)<3.2";

  string vertexCut="sensitivity.first_vertices_on_foil==2";
  
  string noCut="sensitivity.passes_two_calorimeters";

  compareTimeDifferenceForCut( associatedCalCut, "associated_tracks","Two calorimeter-matched tracks");
  //  compareTimeDifferenceForCut(noCut,"only_calo_cut","Two calorimeter hits");
  // compareTimeDifferenceForCut(vertexCut,"two_foil_vertices","Both vertices on foil");
  
}

void MakeHistogramSet(std::vector<Interaction*> interactions, string title, string cut, string drawString, string xTitle, string outFileName, string directory, double xMax,bool areaNormalize=true)
{
  TCanvas *c=new TCanvas("supernemo","supernemo",900,600);
  TLegend *legend = new TLegend(0.6,0.5,0.88,0.88);
  if (interactions.size()<4)
    {
      legend = new TLegend(0.6,0.65,0.88,0.88);
    }
  vector<TH1D*> histograms;
  double histogramHeight=-99999;
  int highestHistogram=-1;
  for (int i=0;i<interactions.size();i++)
    {
      TH1D *hist= new TH1D();
      hist=MakeCustomHist(interactions.at(i)->GetTree(),interactions.at(i)->GetLegendText(),interactions.at(i)->GetColor(),cut,legend,drawString,title,xTitle,xMax,areaNormalize);
      double yMax=hist->GetMaximum();
      if (yMax>histogramHeight)
	{
	  histogramHeight=yMax;
	  highestHistogram=i;
	}
      histograms.push_back(hist);
    }
  c->cd();
  histograms.at(highestHistogram)->Draw("HIST");
  for (int i=0;i<histograms.size();i++)
    {
      histograms.at(i)->Draw("HIST SAME");
    }
  
  legend->Draw();
  string outNameDirectory="plots/feedthroughs/"+directory+"/"+outFileName;
  c->SaveAs(outNameDirectory.c_str());
  c->SetLogy(true);
  outNameDirectory="plots/feedthroughs/"+directory+"/log_"+outFileName;
  c->SaveAs(outNameDirectory.c_str());
  c->SetLogy(false);
}

void compareTimeDifferenceForCut(string cut, string directory, string title)
{
  gStyle->SetOptStat(0);

  Interaction *int0nubb=new Interaction("0#nu#beta#beta", kBlack, "/Users/cpatrick/SuperNEMO/rootfiles/rootfiles_se82/se82_0nubb_1M_sensitivity.root","se82_0nubb");
  Interaction *int2nubb=new Interaction("2#nu#beta#beta", kRed, "/Users/cpatrick/SuperNEMO/rootfiles/rootfiles_se82/se82_2nubbHE_1M_sensitivity.root","se82_2nubb");
  Interaction *intFeedthru4=new Interaction("4MeV feedthrough #gamma",kCyan+2,"/Users/cpatrick/SuperNEMO/rootfiles/rootfiles_gamma/feedthroughs_4_MeV_sensitivity.root","feedthru_4MeV");
  Interaction *intFeedthru78=new Interaction("7-8MeV feedthrough #gamma",kOrange+2,"/Users/cpatrick/SuperNEMO/rootfiles/rootfiles_gamma/feedthroughs_7_8_MeV_sensitivity.root","feedthru_7_8MeV");
  Interaction *intCalo78=new Interaction("7-8MeV calo wrapper #gamma",kPink-8,"/Users/cpatrick/SuperNEMO/rootfiles/rootfiles_gamma/calowrap_7_8_MeV_sensitivity.root","calowrap_7_8MeV");
  Interaction *intCalo4=new Interaction("4MeV calo wrapper #gamma",kOrange+3,"/Users/cpatrick/SuperNEMO/rootfiles/rootfiles_gamma/calowrap_4_MeV_sensitivity.root","calowrap_4MeV");
  Interaction *intShield78=new Interaction("7-8MeV shielding #gamma",kMagenta+3,"/Users/cpatrick/SuperNEMO/rootfiles/rootfiles_gamma/shielding_7_8_MeV_sensitivity.root","shielding_7_8MeV");
  Interaction *intShield4=new Interaction("4MeV shielding #gamma",kGreen+2,"/Users/cpatrick/SuperNEMO/rootfiles/rootfiles_gamma/shielding_4_MeV_sensitivity.root","shielding_4MeV");
  gStyle->SetLegendBorderSize(0);

  
  std::vector<Interaction*> allInteractions ;
  
  allInteractions.push_back(int0nubb);
  allInteractions.push_back(int2nubb);
  allInteractions.push_back(intCalo78);
  allInteractions.push_back(intCalo4);
  allInteractions.push_back(intShield78);
  allInteractions.push_back(intShield4);
  allInteractions.push_back(intFeedthru4);
  allInteractions.push_back(intFeedthru78);

  std::vector<Interaction*> gammaInteractions;
  gammaInteractions.push_back(intCalo78);
  gammaInteractions.push_back(intCalo4);
  gammaInteractions.push_back(intShield78);
  gammaInteractions.push_back(intShield4);
  gammaInteractions.push_back(intFeedthru4);
  gammaInteractions.push_back(intFeedthru78);


  MakeInternalExternalProbabilitySet(allInteractions, cut, title, "IntVsExt.png", directory,1,1, false);
  MakeInternalExternalProbabilitySet(allInteractions, cut, title, "ZoomIntVsExt.png", directory,1e-5,1e-5, false);
  
  MakeHistogramSet(allInteractions, "Calorimeter time delay: "+title,  cut, "sensitivity.time_delay", "Time delay (ns)", "TimeDelaysNew.png", directory,10);
  
  MakeHistogramSet(allInteractions, "Internal probability: "+title,  cut, "sensitivity.internal_probability", "Internal probability", "InternalProb.png", directory,1);
  MakeHistogramSet(allInteractions, "Internal probability, zoomed: "+title,  cut, "sensitivity.internal_probability", "Internal probability", "InternalProbZoom.png", directory,0.1);
  MakeHistogramSet(allInteractions, "External probability: "+title,  cut, "sensitivity.external_probability", "External probability", "ExternalProb.png", directory,1);
  MakeHistogramSet(allInteractions, "External probability, zoomed: "+title,  cut, "sensitivity.external_probability", "External probability", "ExternalProbZoom.png", directory,0.1);

  MakeHistogramSet(gammaInteractions, "Calorimeter time delay: "+title,  cut, "sensitivity.time_delay", "Time delay (ns)", "TimeDelaysGammasOnly.png", directory,10,false);
  MakeHistogramSet(gammaInteractions, "Internal Probability, zoomed: "+title,  cut, "sensitivity.internal_probability", "Time delay (ns)", "InternalProbZoomGammasOnly.png", directory,0.1,false);
  
  MakeHistogramSet(gammaInteractions, "External Probability: "+title,  cut, "sensitivity.external_probability", "Time delay (ns)", "ExternalProbGammasOnly.png", directory,1,false);
  return;
}

int main()
{
  compareTimeDifferencesFeedthroughs();
  return 0;
}
