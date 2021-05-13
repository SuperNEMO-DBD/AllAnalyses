#include <TGraph.h>

void efficiency_graph(){

  double x[5], y[5];

  x[0]=0.899;x[1]=0.824;x[2]=0.769;x[3]=0.742;x[4]=0.712;
  y[0]=0.567;y[1]=0.705;y[2]=0.733;y[3]=0.732;y[4]=0.724;

  TGraph* gr = new TGraph(20,x,y);

  gr->Draw("AC");
}
