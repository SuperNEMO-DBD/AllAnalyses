#include <TH1F.h>
#include <TGraph.h>
#include <TTree.h>
#include <string>
#include <gsl/gsl_cdf.h>
#include <cmath>
#include <vector>
#include <stdlib.h>

using namespace std;


void mbb_graph(){


  TH3F *mbb_spectrum = new TH3F("h2_ROI","low bound vs up bound",4,0,4,20,0,1,4,0,4);
  mbb_spectrum->SetBinContent(1,1,1,0.2);

  new TCanvas;
  mbb_spectrum->Draw("BOX");

}
