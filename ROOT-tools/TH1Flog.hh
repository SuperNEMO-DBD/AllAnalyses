#include "TH1F.h"
#include "TMath.h"

TH1F *TH1Flog(const char *name, const char *title, const int nbinsx, const float xmin, const float xmax)
{
  const float log_xmin  = TMath::Log10(xmin);
  const float log_xmax  = TMath::Log10(xmax);
  const float bin_width = (log_xmax-log_xmin)/nbinsx;

  float xbins[nbinsx+1];

  for (int i=0; i<=nbinsx; ++i)
    xbins[i] = TMath::Power(10, log_xmin + i*bin_width);
  
  return new TH1F(name, title, nbinsx, xbins);
}
