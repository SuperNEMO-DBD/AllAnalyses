#include "/home/girardcarillo/Workdir/SNPlot/SNPlot.h"
#include <iostream>
#include <TStyle.h>
#include <TGaxis.h>


using namespace std;

SNPlot::SNPlot()
{
  return;
}

SNPlot::~SNPlot()
{
  return;
}

void SNPlot::Set_SNgstyle()
{
  gStyle->SetPaintTextFormat("4.2e");
  gStyle->SetOptStat(0);
  gStyle->SetLegendTextSize(0.05);
  TGaxis::SetMaxDigits(3);
  return;
}

void Set_SNaxis()
{
  TGaxis::SetMaxDigits(3);
  return;
}
