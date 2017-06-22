#define ntsh_cxx
#include "ntsh.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <iomanip>

using namespace std;

void ntsh::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L ntsh.C
//      Root > ntsh t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);
      if (nb == 0) continue;
      if (ientry < 10)
      {
        cout << ientry << ' ' << v_column->size() << endl;
      }
   }
}

void ntsh::zoom(bool doit)
{
  // zoom current view
  //
  _isZoomed = doit;
  setZoom();
}

void ntsh::setZoom()
{
  cout << "Zoom set to " << _isZoomed << endl;
  if (_isZoomed)
  {
    NTRange(_xyCanvas, _xl, _yl, _xh, _yh);
    NTRange(_xzCanvas, _xl, _zl, _xh, _zh);
    cout << "Range " << ' ' <<_xl << ' ' <<_yl
    << ' ' <<_xh << ' ' <<_yh << ' ' << _zl << ' ' << _zh << endl;
  }
  else
  {
    NTRange(_xyCanvas, _XL, _YL, _XH, _YH);
    NTRange(_xzCanvas, -150., _ZL, 150., _ZH);
    cout << "Range default" << endl;
  }
  _xyCanvas->Modified();
  _xyCanvas->Update();
  _xzCanvas->Modified();
  _xzCanvas->Update();
}

bool ntsh::next()
{
  Long64_t nb = GetEntry(evnum+1);
  if (nb == 0) return false;
  return true;
}

void ntsh::show()
{
  memClean();
  TLine *xlo = NTLine(-50., 0., -50., 500.);
  TLine *xhi = NTLine(+50., 0., +50., 500.);
  TLine *zlo = NTLine(-50., -145., -50., 145.);
  TLine *zhi = NTLine(+50., -145., +50., 145.);
  TLine *foilxy = NTLine(0., 0., 0., 500.);
  TLine *foilxz = NTLine(0., -145., 0., 145.);
  xlo->SetLineWidth(2);
  xhi->SetLineWidth(2);
  zlo->SetLineWidth(2);
  zhi->SetLineWidth(2);
  foilxy->SetLineColor(kRed);
  foilxz->SetLineColor(kRed);
  _xzCanvas->Clear();
  zlo->Draw();
  zhi->Draw();
  foilxz->Draw();
  _xyCanvas->Clear();
  xlo->Draw();
  xhi->Draw();
  foilxy->Draw();
  cout << "Display event # " << evnum << endl;
  cout << "         x         y      dist         z\n"
       << "----------------------------------------" << endl;
  _xl = 999.;
  _xh = -999.;
  _yl = 999.;
  _yh = -999.;
  _zl = 999.;
  _zh = -999.;

  // create a cross-reference between event data and drawn primitives
  //
  int nh = v_r->size();
  std::vector<int> hitIds;
  std::vector<TEllipse*> ellipses;
  std::vector<TLine*> lines;
  hitIds.reserve(nh);
  ellipses.reserve(nh);
  lines.reserve(nh);
  int fID = 0;
  for (int it=0; it<nh; ++it)
  {
    double x, y, r, z;
    hitCoords(it, x, y);
    r = (*v_r)[it];
    z = (*v_z)[it];
    cout << right << setw(10) << x << setw(10) << y << setw(10) << r
      << setw(10) << z << endl;
    TEllipse* e = NTEllipse(x, y, r, r);
    e->SetUniqueID(fID);
    e->SetFillStyle(0);
    e->Draw();

    // calculate the maximum range of points
    //
    if (x < _xl) _xl = x;
    if (x > _xh) _xh = x;
    if (y < _yl) _yl = y;
    if (y > _yh) _yh = y;
    if (z < _zl) _zl = z;
    if (z > _zh) _zh = z;

    // draw the x-z view
    //
    _xzCanvas->cd();
    double dx = 0.5*r;
    TLine* l = NTLine(x-dx, z, x+dx, z);
    l->SetUniqueID(fID);
    l->Draw();
    _xyCanvas->cd();

    // link the primitives to the hit.
    //
    hitIds.push_back(it);
    ellipses.push_back(e);
    lines.push_back(l);
    fID++;
  }
  _hitToRoot.swap(hitIds);
  _xyhit.swap(ellipses);
  _xzhit.swap(lines);

  // adjust the zoom range to preserve aspect ratio and provide a border
  //
  _xl -= 10.;
  _xh += 10.;
  _yl -= 10.;
  _yh += 10.;
  _zl -= 10.;
  _zh += 10.;
  double dx = _xh - _xl;
  double dy = _yh - _yl;
  double dz = _zh - _zl;
  if (dx > dy)
  {
    double d2 = 0.5*(dx - dy);
    _yl -= d2;
    _yh += d2;
  }
  else if (dy > dx)
  {
    double d2 = 0.5*(dy - dx);
    _xl -= d2;
    _xh += d2;
  }
  if (dx > dz)
  {
    double d2 = 0.5*(dx - dz);
    _zl -= d2;
    _zh += d2;
  }
  setZoom();

  // Optionally draw the wires in the X-Y view
  //
  if ( _isZoomed &&_showWires )
  {
    _xyCanvas->cd();
    CellGeom* geo = 0;
    if (_geo[0] != 0) geo = _geo[0];
    else if (_geo[1] != 0) geo = _geo[1];
    if (geo != 0)
    {
      for (int layer=0; layer<9; layer++)
      {
        for (int column=0; column<112; column++)
        {
          CellGeom::Wpos pos = geo->getPos(layer, column);
          TMarker *m = NTMarker(pos.x, pos.y, 7);
          m->Draw();
        }
      }
    }
  }

  _xyCanvas->Update();
  _xzCanvas->Update();
}

void ntsh::hitCoords(int h, double& x, double& y)
{
  int side = (*v_side)[h];      // 0 = -ve X, 1 = +ve X.

  // Initialise the cell layout on demand.
  //
  if (!_geo[side]) _geo[side] = new CellGeom(side);
  CellGeom &geo = *_geo[side];

  geo.hitCoords(this, h, x, y);
}

void ntsh::rotate(double &x, double&y)
{
  if (_irot == 0) return; // no rotation
  else if (_irot == 1)    // rotate 90 degrees clockwise
  {
    double a = x, b = y;
    x = b;
    y = -a;
  }
  else if (_irot == -1)   // rotate 90 degrees anti-clockwise
  {
    double a = x, b = y;
    x = -b;
    y = a;
  }
  else throw "Rotation value not implemented!";
}

void ntsh::doClickXY(Int_t ev, Int_t x, Int_t y, TObject* /*selected*/)
{
  clickXY(ev, x, y);
}

void ntsh::doClickXZ(Int_t ev, Int_t x, Int_t z, TObject* /*selected*/)
{
  clickXZ(ev, x, z);
}

void ntsh::clickXY(int ev, int px, int py)
{
  if (ev != 1) return;  // button1 down
  double x = _xyCanvas->PixeltoX(px);
  double y = _xyCanvas->PixeltoY(py - _xyCanvas->GetWh());  // don't ask!

  // Find the closest primitive to the mouse event.
  //
  double d2min = 999.;
  int closest = 0;
  for (unsigned int i=0; i<_xyhit.size(); ++i)
  {
    TEllipse* e = _xyhit[i];
    double dx = x - e->GetX1();
    double dy = y - e->GetY1();
    double d2 = dx*dx + dy*dy;
    if (d2 < d2min)
    {
      d2min = d2;
      closest = i;
    }
  }
  hilite(d2min, closest);
}

void ntsh::clickXZ(int ev, int px, int pz)
{
  if (ev != 1) return;  // button1 down
  double x = _xzCanvas->PixeltoX(px);
  double y = _xzCanvas->PixeltoY(pz - _xzCanvas->GetWh());  // don't ask!

  // Find the closest primitive to the mouse event.
  //
  double d2min = 999.;
  int closest = 0;
  for (unsigned int i=0; i<_xzhit.size(); ++i)
  {
    TLine* l = _xzhit[i];
    double dx = x - 0.5*(l->GetX1() + l->GetX2());
    double dy = y - l->GetY1();
    double d2 = dx*dx + dy*dy;
    if (d2 < d2min)
    {
      d2min = d2;
      closest = i;
    }
  }
  hilite(d2min, closest);
}

void ntsh::hilite(double dist, int closest)
{
  // Hightlight the primitive index by closest in both views if we are
  // within dist.
  //
  // Cancel any highlighting if we clicked too far from any primitive
  //
  if (dist > 5.)
  {
    cout << "Nothing selected" << endl;
    for (unsigned int i=0; i<_xyhit.size(); ++i)
    {
      _xyhit[i]->SetLineWidth(1);
      _xzhit[i]->SetLineWidth(1);
    }
    _xyCanvas->Modified();
    _xyCanvas->Update();
    _xzCanvas->Modified();
    _xzCanvas->Update();
    return;
  }

  // Highlight the closest primitive in both views.
  //
  TEllipse* e = _xyhit[closest];
  TLine* l = _xzhit[closest];
  double x, y, r, z, time;
  int layer, column, anode, cattop, catbot, alpha;
  hitCoords(closest, x, y);
  r = (*v_r)[closest];
  z = (*v_z)[closest];
  layer = (*v_layer)[closest];
  column = (*v_column)[closest];
  anode = (*v_anode)[closest];
  cattop = (*v_cattop)[closest];
  catbot = (*v_catbot)[closest];
  time = (*v_time)[closest];
  alpha = (*v_alpha)[closest];
  cout << "Drift circle:\n"
  << "centre X: " << x << '\n'
  << "centre Y: " << y << '\n'
  << "radius:   " << r << '\n'
  << "Z coord:  " << z << '\n'
  << "time:     " << time << '\n'
  << "layer:    " << layer << '\n'
  << "column:   " << column << '\n'
  << "anode:    " << anode << '\n'
  << "cattop:   " << cattop << '\n'
  << "catbot:   " << catbot << '\n'
  << "alpha:    " << alpha << endl;
  e->SetLineWidth(2);
  _xyCanvas->Modified();
  _xyCanvas->Update();
  l->SetLineWidth(2);
  _xzCanvas->Modified();
  _xzCanvas->Update();
}

void ntsh::NTRange(TCanvas* c, double xl, double yl, double xh, double yh)
{
  rotate(xl, yl);
  rotate(xh, yh);
  if (_irot == 0) c->Range(xl, yl, xh, yh);
  else if (_irot == 1) c->Range(xl, yh, xh, yl);
  else if (_irot == -1) c->Range(xh, yl, xl, yh);
}

TLine* ntsh::NTLine(double x1, double y1, double x2, double y2)
{
  rotate(x1,y1);
  rotate(x2,y2);
  TLine *l =  new TLine(x1, y1, x2, y2);
  _meml.push_back(l);
  return l;
}

TEllipse* ntsh::NTEllipse(double x1, double y1, double r1, double r2)
{
  rotate(x1,y1);
  TEllipse *e =  new TEllipse(x1, y1, r1, r2);
  _meme.push_back(e);
  return e;
}

TMarker* ntsh::NTMarker(double x, double y, int mtype)
{
  rotate(x,y);
  TMarker *m = new TMarker(x, y, mtype);
  _memm.push_back(m);
  return m;
}

TGaxis* ntsh::NTGaxis(double xmin, double ymin, double xmax, double ymax,
  double wmin, double wmax, int ndiv, char* chopt, double gridlen)
{
  rotate(xmin, ymin);
  rotate(xmax, ymax);
  TGaxis *ax =  new TGaxis(xmin, ymin, xmax, ymax, wmin, wmax, ndiv, chopt, gridlen);
  _mema.push_back(ax);
  return ax;
}

void ntsh::memClean()
{
  std::vector<TEllipse*>::iterator ite;
  std::vector<TLine*>::iterator itl;
  std::vector<TMarker*>::iterator itm;
  std::vector<TGaxis*>::iterator ita;
  for (ite=_meme.begin(); ite!=_meme.end(); ++ite) { delete *ite; }
  for (itl=_meml.begin(); itl!=_meml.end(); ++itl) { delete *itl; }
  for (itm=_memm.begin(); itm!=_memm.end(); ++itm) { delete *itm; }
  for (ita=_mema.begin(); ita!=_mema.end(); ++ita) { delete *ita; }
  _meme.clear();
  _meml.clear();
  _memm.clear();
  _mema.clear();
}
