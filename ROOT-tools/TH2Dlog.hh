#include "TH2D.h"
#include "TMath.h"

TH2D *TH2Dlogx(const char *name, const char *title, const int nbinsx, const double xmin, const double xmax, const int nbinsy, const double ymin, const double ymax)
{
  const double log_xmin  = TMath::Log10(xmin);
  const double log_xmax  = TMath::Log10(xmax);

  const double binx_width = (log_xmax-log_xmin)/nbinsx;
  const double biny_width = (ymax-ymin)/nbinsy;

  double xbins[nbinsx+1];
  double ybins[nbinsy+1];

  for (int i=0; i<=nbinsx; ++i)
    xbins[i] = TMath::Power(10, log_xmin + i*binx_width);

  for (int i=0; i<=nbinsy; ++i)
    ybins[i] = ymin + i*biny_width;
  
  return new TH2D(name, title, nbinsx, xbins, nbinsy, ybins);
}

TH2D *TH2Dlogy(const char *name, const char *title, const int nbinsx, const double xmin, const double xmax, const int nbinsy, const double ymin, const double ymax)
{
  const double log_ymin  = TMath::Log10(ymin);
  const double log_ymax  = TMath::Log10(ymax);

  const double binx_width = (xmax-xmin)/nbinsx;
  const double biny_width = (log_ymax-log_ymin)/nbinsy;

  double xbins[nbinsx+1];
  double ybins[nbinsy+1];

  for (int i=0; i<=nbinsx; ++i)
    xbins[i] = xmin + i*binx_width;

  for (int i=0; i<=nbinsy; ++i)
    ybins[i] = TMath::Power(10, log_ymin + i*biny_width);
  
  return new TH2D(name, title, nbinsx, xbins, nbinsy, ybins);
}

TH2D *TH2Dlogxy(const char *name, const char *title, const int nbinsx, const double xmin, const double xmax, const int nbinsy, const double ymin, const double ymax)
{
  const double log_xmin  = TMath::Log10(xmin);
  const double log_xmax  = TMath::Log10(xmax);

  const double log_ymin  = TMath::Log10(ymin);
  const double log_ymax  = TMath::Log10(ymax);

  const double binx_width = (log_xmax-log_xmin)/nbinsx;
  const double biny_width = (log_ymax-log_ymin)/nbinsy;

  double xbins[nbinsx+1];
  double ybins[nbinsy+1];

  for (int i=0; i<=nbinsx; ++i)
    xbins[i] = TMath::Power(10, log_xmin + i*binx_width);

  for (int i=0; i<=nbinsy; ++i)
    ybins[i] = TMath::Power(10, log_ymin + i*biny_width);

  return new TH2D(name, title, nbinsx, xbins, nbinsy, ybins);
}
