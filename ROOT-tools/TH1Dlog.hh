#include "TH1D.h"
#include "TMath.h"

TH1D *TH1Dlog(const char *name, const char *title, const int nbinsx, const double xmin, const double xmax)
{
  const double log_xmin  = TMath::Log10(xmin);
  const double log_xmax  = TMath::Log10(xmax);
  const double bin_width = (log_xmax-log_xmin)/nbinsx;

  double xbins[nbinsx+1];

  for (int i=0; i<=nbinsx; ++i)
    xbins[i] = TMath::Power(10, log_xmin + i*bin_width);
  
  return new TH1D(name, title, nbinsx, xbins);
}
