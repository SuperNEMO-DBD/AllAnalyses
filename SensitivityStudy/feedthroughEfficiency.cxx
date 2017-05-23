#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TText.h"
#include "TMath.h"
#include "TLegend.h"
#include "TStyle.h"
#include <iostream>

using namespace std;

bool lowEnergy=false;
bool caloWrapper=false;
bool shielding=false;

enum Isotope { SE82, ND150};
enum Location{FEEDTHRU,SHIELD,CALOWRAP};

class Interaction{
  string legendText_;
  int lineColor_;
  int fillColor_;
  TTree *tree_;
  string directoryText_;
  Isotope isotope_;
  Location location_;
  string energyText_;
  string locationText_;
  string isotopeText_;
public:
  Interaction(string legendText, int lineColor, int fillColor, string fileName, string filenameText);
  Interaction(Isotope isotope, Location location, int energy);
  Interaction();
  TTree *GetTree(){return tree_;}
  int GetLineColor(){return lineColor_;}
  int GetFillColor(){return fillColor_;}
  Isotope GetIsotope(){return isotope_;}
  string GetIsotopeText(){return isotopeText_;}
  string GetLegendText(){return legendText_;}
  string GetDirectoryText(){return directoryText_;}
};
Interaction::Interaction()
{
  isotopeText_="Undefined";
  legendText_="Undefined";
  directoryText_="Undefined";
  lineColor_=kGray+2;
  fillColor_=kGray;
  tree_=new TTree();
}

Interaction::Interaction(string legendText, int lineColor, int fillColor, string fileName, string directoryText)
  {
    legendText_=legendText;
    isotopeText_=legendText;
    directoryText_=directoryText;
    fillColor_=fillColor;
    lineColor_=lineColor;
    TFile *f=new TFile(fileName.c_str());
    tree_ = (TTree*) f->Get("Sensitivity");
  }
Interaction::Interaction(Isotope isotope, Location location, int energy)
{
  isotope_=isotope;
  isotopeText_=((isotope==SE82)?"Se82":"Nd150");
  location_=location;
  if (location==CALOWRAP)
    {
      locationText_="calowrap";
      if (energy==4)
	{
	  lineColor_=kOrange+3;
	  fillColor_=kOrange-8;
	}
      else
	{
	  lineColor_=kPink-8;
	  fillColor_=kPink-4;
	}
    }
    if (location==FEEDTHRU)
    {
      locationText_="feedthroughs";
      if (energy==4)
	{
	  lineColor_=kCyan+2;
	  fillColor_=kCyan-3;
	}
      else
	{
	  lineColor_=kOrange+2;
	  fillColor_=kOrange-2;
	}
    }
    if (location==SHIELD)
    {
      locationText_="shielding";
      if (energy==4)
	{
	  lineColor_=kGreen+2;
	  fillColor_=kGreen-10;
	}
      else
	{
	  lineColor_=kMagenta+3;
	  fillColor_=kViolet+6;
	}
    }
    
    string fileName=Form("/Users/cpatrick/SuperNEMO/rootfiles/rootfiles_gamma%s",((isotope==SE82)?"/":"_nd150/nd150_"))+locationText_+"_"+(energy==4?"4":"7_8")+"_MeV_sensitivity.root";
    TFile *f=new TFile(fileName.c_str());
    tree_ = (TTree*) f->Get("Sensitivity");
    
    directoryText_=locationText_+"_"+(energy==4?"4":"7_8")+"MeV";
    legendText_=locationText_+" "+(energy==4?"4":"7_8")+"MeV";
}

void saveAPlot(Interaction *interaction, string title, string filename, string cut)
{
  TTree *tree=interaction->GetTree();

  gStyle->SetOptStat(0);
  TCanvas *c = new TCanvas("supernemo","supernemo",900,600);
  TH1D *plot=new TH1D(filename.c_str(),title.c_str(),100,0,5.);
  plot->GetXaxis()->SetTitle("Total calorimetric energy (MeV)");
  plot->GetYaxis()->SetTitle("Events");
  plot->SetLineColor(interaction->GetLineColor());
  plot->SetFillColor(interaction->GetFillColor());
  plot->SetLineWidth(1);

  tree->Draw(("sensitivity.total_calorimeter_energy >> "+filename).c_str(), cut.c_str());

  c->Update();
  TLine *line=new TLine();
  line->SetLineWidth(3);
  line->SetLineStyle(9);
  line->SetLineColor(kBlack);
  
  if (interaction->GetIsotope()==SE82)
    {
  // Se82 ROI
      line->DrawLine(2.8,0,2.8,gPad->GetUymax());
      c->Update();
    }
  else
    // Nd150 ROI
    {
      line->DrawLine(3.6,0,3.6,gPad->GetUymax());
      c->Update();
    }
  line->DrawLine(3.2,0,3.2,gPad->GetUymax());
  c->Update();
  double integral=plot->Integral();
  double integralSe82ROI=plot->Integral(plot->FindBin(2.80001),plot->FindBin(3.19999));
  double integralNd150ROI=plot->Integral(plot->FindBin(3.20001),plot->FindBin(3.59999));
  double total=tree->GetEntries();
  string legend=Form("Total events: %.0f of %.0f (%.3f of 9k)",integral,total,integral/total*9000);
  
  TText *label = new TText(0.12, 0.8, legend.c_str());
  label->SetNDC();
  label->SetTextSize(0.035);
  label->Draw();

  string legend2=Form("In Se82 ROI: %.0f of %.0f (%.3f of 9k)",integralSe82ROI,total,integralSe82ROI/total*9000);
  if (interaction->GetIsotope()==ND150)
    {
      legend2=Form("In Nd150 ROI: %.0f of %.0f (%.3f of 9k)",integralNd150ROI,total,integralNd150ROI/total*9000);
    }
  label = new TText(0.12, 0.75, legend2.c_str());
  label->SetNDC();
  label->SetTextSize(0.035);
  label->Draw();

  if (interaction->GetIsotope()==SE82)
    {
      label = new TText(0.56, 0.17, "Se82");
    }
  if (interaction->GetIsotope()==ND150)
    {
      label = new TText(0.615, 0.17, "Nd150");

    }
  label->SetNDC();
  label->SetTextSize(0.032);
  label->Draw();
  string outputFile="feedthroughplots/"+interaction->GetIsotopeText()+"/"+interaction->GetDirectoryText()+"/"+filename+".png";

  system("mkdir -m 777 -p -m a+rwx feedthroughplots");
  system(("mkdir -m 777 -p -m a+rwx feedthroughplots/"+interaction->GetIsotopeText()).c_str());
  system(("mkdir -m 777 -p -m a+rwx feedthroughplots/"+interaction->GetIsotopeText()+"/"+interaction->GetDirectoryText()).c_str());
  c->SaveAs(outputFile.c_str());
}

void feedthroughEfficiency(Interaction *interaction)
{
  TTree * tree= interaction->GetTree();
  int totalEntries=tree->GetEntries();
 
  cout<<"Total events "<<totalEntries<<endl;
   
  // int passesCalCut=tree->GetEntries("sensitivity.passes_two_calorimeters");
  // cout<<"Two triggered calorimeters: "<<(double)passesCalCut/(double)totalEntries * 100<<"%"<<endl;

  // // 2 tracker clusters
  // int passesClusterCut=tree->GetEntries("sensitivity.passes_two_calorimeters && sensitivity.passes_two_clusters");
  // cout<<"Two tracker clusters with a minimum of 3 cells: "<<(double)passesClusterCut/(double)totalEntries * 100<<"%"<<endl;
  
  // // 2 reconstructed tracks
  // int passesTrackCut=tree->GetEntries("sensitivity.passes_two_calorimeters && sensitivity.passes_two_clusters && sensitivity.passes_two_tracks ");
  // cout<<"Two reconstructed tracks: "<<(double)passesTrackCut/(double)totalEntries * 100<<"%"<<endl;

  // Tracks have associated calorimeter hits
  
  int passesAssociatedCalCut=tree->GetEntries("sensitivity.passes_two_calorimeters && sensitivity.passes_two_clusters && sensitivity.passes_two_tracks && sensitivity.passes_associated_calorimeters");
  cout<<"Tracks have associated calorimeter hits: "<<(double)passesAssociatedCalCut/(double)totalEntries * 100<<"%"<<endl;

  // // Both tracks have negative charge reconstruction
  
  // int passesTwoElectronCut=tree->GetEntries("sensitivity.passes_two_calorimeters && sensitivity.passes_two_clusters && sensitivity.passes_two_tracks && sensitivity.passes_associated_calorimeters && sensitivity.number_of_electrons==2 ");
  // cout<<"Both tracks have negative charge: "<<(double)passesTwoElectronCut/(double)totalEntries * 100<<"% = "<<(double)passesTwoElectronCut/(double)totalEntries *9000<<" events in 9k"<<endl;


  // // 2.8-3.2 MeV, and time delay
  // string maxEnergyCutString="sensitivity.passes_two_calorimeters && sensitivity.passes_two_clusters && sensitivity.passes_two_tracks && sensitivity.passes_associated_calorimeters && sensitivity.number_of_electrons==2  && (sensitivity.lower_electron_energy+sensitivity.higher_electron_energy)>=2.8 &&  (sensitivity.lower_electron_energy+sensitivity.higher_electron_energy)<3.2 && sensitivity.time_delay<3";

  //  int passesMaxEnergyCut=tree->GetEntries(maxEnergyCutString.c_str());
  
  //  cout<<"Both tracks have negative charge, 2.8 MeV <total reconstructed energy < 3.2MeV (Se82 ROI) and time delay < 3ns: "<<(double)passesMaxEnergyCut/(double)totalEntries * 100<<"% = "<<(double)passesMaxEnergyCut/(double)totalEntries*9000<<" events in 9k"<<endl;
   
  // No negative charge requirement, 2.8-3.2 MeV
  string tightEnergyCutNoElectronCut=  "sensitivity.passes_two_calorimeters && sensitivity.passes_two_clusters && sensitivity.passes_two_tracks && sensitivity.passes_associated_calorimeters && (sensitivity.lower_electron_energy+sensitivity.higher_electron_energy)>=2.8 &&  (sensitivity.lower_electron_energy+sensitivity.higher_electron_energy)<3.2";
 int passesTightEnergyCutNoElectronCut=tree->GetEntries( tightEnergyCutNoElectronCut.c_str());
  
 cout<<"No charge requirement, 2.8 MeV <total reconstructed energy < 3.2MeV  (Se82 ROI): "<<(double)passesTightEnergyCutNoElectronCut/(double)totalEntries * 100<<"% = "<<(double)passesTightEnergyCutNoElectronCut/(double)totalEntries *9000<<" events in 9k"<<endl;


  // No negative charge requirement, 2.8-3.2 MeV plus time delay
  string tightEnergyAndTimeCut=  "sensitivity.passes_two_calorimeters && sensitivity.passes_two_clusters && sensitivity.passes_two_tracks && sensitivity.passes_associated_calorimeters && (sensitivity.lower_electron_energy+sensitivity.higher_electron_energy)>=2.8 &&  (sensitivity.lower_electron_energy+sensitivity.higher_electron_energy)<3.2 && sensitivity.time_delay<3";
 int passesTightEnergyAndTime=tree->GetEntries(tightEnergyAndTimeCut.c_str());
  
 cout<<"No charge requirement, 2.8 MeV <total reconstructed energy < 3.2MeV (Se82 ROI) and time delay < 3ns: "<<(double)passesTightEnergyAndTime/(double)totalEntries * 100<<"% = "<<(double)passesTightEnergyAndTime/(double)totalEntries*9000<<" events in 9k"<<endl;

 // External and internal prob cuts from nemo3 and ROI requirement
string roiAndInternalExternalProbCut= "sensitivity.passes_two_calorimeters && sensitivity.passes_two_clusters && sensitivity.passes_two_tracks && sensitivity.passes_associated_calorimeters && (sensitivity.lower_electron_energy+sensitivity.higher_electron_energy)>=2.8 &&  (sensitivity.lower_electron_energy+sensitivity.higher_electron_energy)<3.2 &&  sensitivity.external_probability<0.04 && sensitivity.internal_probability>0.01";
 int passesInternalExternalAndROI=tree->GetEntries(roiAndInternalExternalProbCut.c_str());
  
 cout<<"No charge requirement, 2.8 MeV <total reconstructed energy < 3.2MeV (Se82 ROI), external prob<0.04, internal >0.01: "<<(double)passesInternalExternalAndROI/(double)totalEntries * 100<<"% = "<<(double)passesInternalExternalAndROI/(double)totalEntries*9000<<" events in 9k"<<endl;

  
  saveAPlot(interaction,"No cuts","no_cuts","");
  saveAPlot(interaction,"No cuts, non-zero energy","non_zero_energy","sensitivity.total_calorimeter_energy>0");
  saveAPlot(interaction,"Two calorimeters","two_cals","sensitivity.passes_two_calorimeters");
  saveAPlot(interaction,"Two calorimeter-matched tracks","two_matched_tracks","sensitivity.passes_two_calorimeters && sensitivity.passes_two_clusters && sensitivity.passes_two_tracks && sensitivity.passes_associated_calorimeters");
  saveAPlot(interaction,"Two matched negative tracks","two_matched_negative_tracks","sensitivity.passes_two_calorimeters && sensitivity.passes_two_clusters && sensitivity.passes_two_tracks && sensitivity.passes_associated_calorimeters && sensitivity.number_of_electrons==2 ");
  saveAPlot(interaction,"Two matched negative tracks and time delay < 3ns","two_matched_negative_tracks_delay_3","sensitivity.passes_two_calorimeters && sensitivity.passes_two_clusters && sensitivity.passes_two_tracks && sensitivity.passes_associated_calorimeters && sensitivity.number_of_electrons==2  && sensitivity.time_delay<3");
  saveAPlot(interaction,"Time delay < 3ns, no charge requirement","tracks_delay_3_no_charge","sensitivity.passes_two_calorimeters && sensitivity.passes_two_clusters && sensitivity.passes_two_tracks && sensitivity.passes_associated_calorimeters  && sensitivity.time_delay<3");
  saveAPlot(interaction,"External prob < 1e-6, no charge requirement","tracks_ext_prob_no_charge","sensitivity.passes_two_calorimeters && sensitivity.passes_two_clusters && sensitivity.passes_two_tracks && sensitivity.passes_associated_calorimeters  && sensitivity.external_probability<1e-6");
  saveAPlot(interaction,"External prob < 1e-6 && internal prob > 1e-6 no charge requirement","tracks_int_ext_prob_no_charge","sensitivity.passes_two_calorimeters && sensitivity.passes_two_clusters && sensitivity.passes_two_tracks && sensitivity.passes_associated_calorimeters  && sensitivity.external_probability<1e-6 && sensitivity.internal_probability>1e-6");
  saveAPlot(interaction,"External prob < 0.04, internal prob > 0.01","tracks_int_ext_prob_nemo3","sensitivity.passes_two_calorimeters && sensitivity.passes_two_clusters && sensitivity.passes_two_tracks && sensitivity.passes_associated_calorimeters  && sensitivity.external_probability<0.04 && sensitivity.internal_probability>0.01");

}

void ProcessInteraction(Isotope isotope,Location location,int energy)
{
  Interaction *interaction = new Interaction(isotope,location,energy);
  cout<<"Processing "<<interaction->GetDirectoryText()<<" for "<<interaction->GetIsotopeText()<<endl;
  
  feedthroughEfficiency(interaction);
  return ;
}


int main(int argc, char *argv[])
{
  // Parse the options
  Isotope isotope=SE82;
  Location location=FEEDTHRU;
  int energy=7;
  if(argc > 4 ) {
    cout<<"usage: "<< argv[0] <<" isotope(se,nd), location(ft, cw, sh or all), energy  \n";
    return 2;
  }

  if (argc>1)
    {
      string text = argv[1];
      if (text=="n" || text=="nd" || text=="Nd" || text=="nd150" || text=="Nd150") isotope=ND150;
    }
  if (argc > 2)
    {
      string text = argv[2];
      if (text=="all" || text=="ALL") // Loop through all the combinations
	{
	  ProcessInteraction(isotope,FEEDTHRU,4);
	  ProcessInteraction(isotope,FEEDTHRU,78);
	  ProcessInteraction(isotope,SHIELD,4);
	  ProcessInteraction(isotope,SHIELD,78);
	  if (isotope==SE82)
	    {
	      ProcessInteraction(isotope,CALOWRAP,4);
	      ProcessInteraction(isotope,CALOWRAP,78);
	    }
	  return 0;
	}
      // Else get the interaction we want to process
      if (text=="cw" || text=="CW" || text=="calowrap" || text=="calowrapper" )
        {
          location=CALOWRAP;
        }
      else if (text=="sh" || text=="shield" || text=="shielding")
        {
	  location=SHIELD;
        }
    }
  if (argc>3)
    {
      string text = argv[3];
      if (text=="4")
	{
	  energy=4;
	}
    }


  Interaction *interaction = new Interaction(isotope,location,energy);
  cout<<"Processing "<<interaction->GetDirectoryText()<<" for "<<(interaction->GetIsotopeText())<<endl;
  
  feedthroughEfficiency(interaction);
  return 0;
}
