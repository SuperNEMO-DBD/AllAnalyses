#ifndef EasyTrack_h
#define EasyTrack_h

#include "GHbase.h"
#include "CellGeom.h"
#include "raderr.C"
#include <TMinuit.h>
#include <iostream>
#include <cmath>
#include <vector>

// Simple track finding/fitting class.
//
class EasyTrack
{
  public:
    typedef std::vector<int> Cluster;
    typedef std::vector<Cluster> clulist;
    struct Track{double m; double c; double chisq;
      double mz; double cz; int iclu; };
    typedef std::vector<Track> trklist;

    EasyTrack(GHbase* b) : _bp(b) { _geo[0] = _geo[1] = 0; }

    int makeClusters();
    int fitTracks();
    int nClus() const { return _clusters.size(); }
    const Cluster& getCluster(int i) const { return _clusters[i]; }
    int nTracks() const { return _tracks.size(); }
    const Track& getTrack(int i) const { return _tracks[i]; }
    double hitDist(int id, double m, double c);
    double getChisq(int cluId, double m, double c) const;
    void setFitData(int cluId, double &m, double &c, double &mz, double &cz);

    // following methods aren't callable via CINT. It's too dumb to
    // understand the return types.
    //
    const clulist& getClusters() const { return _clusters; }
    const trklist& getTracks() const { return _tracks; }

    std::vector<double> _xM, _yM, _rM, _drM, _zM;  // for fit data.

  private:
    GHbase *_bp;        // access to ROOT tree data.
    CellGeom* _geo[2];  // Geiger cell geometry.
    clulist _clusters;  // lists of candidate hit clusters.
    trklist _tracks;    // list of reconstrated tracks.
};

void xyFCN(Int_t & /*npar*/, Double_t * /*gin*/, Double_t &fval, Double_t *par,
  Int_t /*iflag*/)
{
  double m = par[0];
  double c = par[1];
  EasyTrack *et = reinterpret_cast<EasyTrack*>(gMinuit->GetObjectFit());
  fval = 0.0;
  for (unsigned i=0; i<et->_xM.size(); i++)
  {
    double dist = std::abs(m*et->_xM[i] - et->_yM[i] + c)/std::sqrt(m*m + 1.);
    double err = raderr(et->_rM[i]);
    double delta = (dist - et->_rM[i])/err;
    fval += delta*delta;
  }
}

void xzFCN(Int_t & /*npar*/, Double_t * /*gin*/, Double_t &fval, Double_t *par,
  Int_t /*iflag*/)
{
  double m = par[0];
  double c = par[1];
  EasyTrack *et = reinterpret_cast<EasyTrack*>(gMinuit->GetObjectFit());
  fval = 0.0;
  for (unsigned i=0; i<et->_xM.size(); i++)
  {
    double dist = std::abs(m*et->_xM[i] - et->_zM[i] + c)/std::sqrt(m*m + 1.);
    fval += dist*dist;
  }
}

void EasyTrack::setFitData(int cluId, double &m, double &c,
  double &mz, double &cz)
{
  // fill the data used for the track fit and make initial estimate
  // of parameters.
  //
  double xav(0.0), yav(0.0), zav(0.0); 
  double xlo(1.e6), ylo(1.e6), zlo(1.e6), xhi(-1.e6), yhi(-1.e6), zhi(-1.e6);
  _xM.clear();
  _yM.clear();
  _rM.clear();
  _drM.clear();
  _zM.clear();
  Cluster clus = _clusters[cluId];
  for (unsigned ic=0; ic<clus.size(); ic++)
  {
    int bi = clus[ic];
    int side = _bp->v_side->at(bi);
    int layer = _bp->v_layer->at(bi);
    int column = _bp->v_column->at(bi);
    double r = _bp->v_r->at(bi);
    double dr = raderr(r);
    double z = _bp->v_z->at(bi);
    if (!_geo[side]) _geo[side] = new CellGeom(side);
    CellGeom::Wpos wire = _geo[side]->getPos(layer, column);
    _xM.push_back(wire.x);
    _yM.push_back(wire.y);
    _rM.push_back(r);
    _drM.push_back(dr);
    _zM.push_back(z);
    if (wire.x<xlo)
    {
      xlo = wire.x;
      ylo = wire.y;
      zlo = z;
    }
    if (wire.x>xhi)
    {
      xhi = wire.x;
      yhi = wire.y;
      zhi = z;
    }
    xav += wire.x;
    yav += wire.y;
    zav += z;
  }
  xav /= clus.size();
  yav /= clus.size();
  zav /= clus.size();
  m = (yhi-ylo)/(xhi-xlo);
  c = yav - m*xav;
  mz = (zhi-zlo)/(xhi-xlo);
  cz = zav - mz*xav;
}

double EasyTrack::getChisq(int cluId, double m, double c) const
{
  // Calculate the chisquare for a Cluster and track parameters.
  // The track is represented by the line y = m*x +c.
  //
  Cluster clus = _clusters[cluId];

  // Get the position information for each hit in the Cluster
  //
  double chisq(0.0);

  for (unsigned ic=0; ic<clus.size(); ic++)
  {
    int bi = clus[ic];
    int side = _bp->v_side->at(bi);
    int layer = _bp->v_layer->at(bi);
    int column = _bp->v_column->at(bi);
    double r = _bp->v_r->at(bi);
    CellGeom::Wpos wire = _geo[side]->getPos(layer, column);
    double dist = std::abs(m*wire.x - wire.y + c)/std::sqrt(m*m + 1.);
    double err = raderr(r);
    double delta = (dist - r)/err;
    chisq += delta*delta;
  }
  return chisq;
}

double EasyTrack::hitDist(int id, double m, double c)
{
  // Calculate the distance from the wire position of hit id
  // to the line y = m*x +c.
  //
  int side = _bp->v_side->at(id);
  int layer = _bp->v_layer->at(id);
  int column = _bp->v_column->at(id);
  if (!_geo[side]) _geo[side] = new CellGeom(side);
  CellGeom::Wpos wire = _geo[side]->getPos(layer, column);
  double dist = std::abs(m*wire.x - wire.y + c)/std::sqrt(m*m + 1.);
  return dist;
}

int EasyTrack::makeClusters()
{
  // dummy implementation for testing.
  //
  _clusters.clear();
  int nh = _bp->v_r->size();
  Cluster clus;
  for (int i=0; i<nh; i++) clus.push_back(i);
  _clusters.push_back(clus);
  return _clusters.size(); // number of clusters found.
}

int EasyTrack::fitTracks()
{
  // Each Cluster represents a possible track.
  //
  _tracks.clear();
  for (int i=0; i<nClus(); i++)
  {
    // Create a fitter
    //
    Double_t m, c;    // initial estimates for parameters: y = m*x + c;
    Double_t mz, cz;  // initial estimates for parameters: z = mz*x + cz;
    Double_t m_err, c_err;
    Double_t mz_err, cz_err;
    setFitData(i, m, c, mz, cz);
    std::cout << "initial guess: m, c, mz, cz= "
      << m << ", " << c << ", " << mz << ", " << cz << std::endl;
    TMinuit *minuit = new TMinuit(2);
    minuit->SetPrintLevel(-1);
    minuit->SetFCN(xyFCN);
    minuit->SetObjectFit(reinterpret_cast<TObject*>(this));
    Int_t ierflg;
    minuit->mnparm(0, "m", m, .2, 0, 0, ierflg);
    minuit->mnparm(1, "c", c, 1., 0, 0, ierflg);
    minuit->Migrad();
    minuit->GetParameter(0, m, m_err);
    minuit->GetParameter(1, c, c_err);
    double chisq = getChisq(i, m, c);
    delete minuit;

    minuit = new TMinuit(2);
    minuit->SetPrintLevel(-1);
    minuit->SetFCN(xzFCN);
    minuit->SetObjectFit(reinterpret_cast<TObject*>(this));
    minuit->mnparm(0, "mz", mz, .2, 0, 0, ierflg);
    minuit->mnparm(1, "cz", cz, 1., 0, 0, ierflg);
    minuit->Migrad();
    minuit->GetParameter(0, mz, mz_err);
    minuit->GetParameter(1, cz, cz_err);
    // double chisq = getChisq(i, m, c);
    delete minuit;

    // Create a Track candidate from each Cluster.
    //
    std::cout << "fit results: m, c, mz, cz= "
      << m << ", " << c << ", " << mz << ", " << cz << std::endl;
    Track t;
    t.m = m;
    t.c = c;
    t.chisq = chisq;
    t.mz = mz;
    t.cz = cz;
    t.iclu = i;
    _tracks.push_back(t);
  }
  return _tracks.size();  // number of successfully fitted tracks.
}

#endif    /* EasyTrack_h */
