#ifndef ntsh_h
#define ntsh_h
///////////////////////////////////////////////////////////////
//
// Nothing to see here! (geddit!)
//
// Simple event display based on tracker commissioning ROOT tree
// written by plotraw.
//
#include "GHbase.h"
#include "CellGeom.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TEllipse.h>
#include <TMarker.h>
#include <TGaxis.h>
#ifndef ROOT_RQ_OBJECT
#include "RQ_OBJECT.h"
#endif

// Header file for the classes stored in the TTree if any.
#include <vector>

class ntsh :public GHbase {
  RQ_OBJECT("ntsh")
  public :
    ntsh(TTree *tree=0);
    void     Loop();
    void show();  // display current event
    void zoom(bool doit=true);  // zoomed view choice.
    void wires(bool on=true) { _showWires = on; }
    bool next();  // read next event (false if EOF reached)
    void setRot(int rot) { _irot = rot; }

    // helper methods: users should not usually call these directly
    //
    void clickXY(int, int, int); // handle mouse event in canvas XY.
    void clickXZ(int, int, int); // handle mouse event in canvas XZ.
    void doClickXY(Int_t ev, Int_t x, Int_t y, TObject* selected);
    void doClickXZ(Int_t ev, Int_t x, Int_t z, TObject* selected);
    void hilite(double dist, int closest);  // highlight selected primitive.
    void hitCoords(int h, double& x, double& y);  // get wire positions.
    void rotate(double &x, double&y); // map coordinates to rotated view.
    void setZoom(); // adjust canvas range according to zoom setting.

    // wrappers for ROOT functions to handle view rotation.
    //
    void memClean();
    void NTRange(TCanvas*, double, double, double, double);
    TLine* NTLine(double, double, double, double);
    TEllipse* NTEllipse(double, double, double, double);
    TMarker* NTMarker(double, double, int);
    TGaxis* NTGaxis(double, double, double, double, double, double,
      int ndiv=510, char* chopt=0, double gridlength=0);

    // Geiger Cell geometry containers
    //
    CellGeom* _geo[2];

    // ROOT canvases.
    //
    TCanvas* _xyCanvas;
    TCanvas* _xzCanvas;
    bool _isZoomed;  // flag for zoom state.
    bool _showWires; // flag for display of anode wires.
    double _xl, _xh, _yl, _yh, _zl, _zh;  // range for zoom views
    double _XL, _XH, _YL, _YH, _ZL, _ZH;  // range for full views
    int _xyWid, _xyHgt, _xzWid, _xzHgt;   // canvas sizes
    int _xylb, _xyrb, _xytb, _xybb;       // canvas borders for axes
    int _xzlb, _xzrb, _xztb, _xzbb;       // canvas borders for axes
    int _irot;  // view rotation: (0,1,-1) = (none,clockwise,anti-clockwise)

    //
    // containers for hit association to ROOT primitives
    //
    std::vector<int> _hitToRoot;
    std::vector<TEllipse*> _xyhit;
    std::vector<TLine*> _xzhit;

    // keep track of allocated primitives for memory management
    //
    std::vector<TEllipse*> _meme;
    std::vector<TLine*> _meml;
    std::vector<TMarker*> _memm;
    std::vector<TGaxis*> _mema;
};

#endif

#ifdef ntsh_cxx
ntsh::ntsh(TTree *tree) : GHbase(tree)
{
  _geo[0] = 0;
  _geo[1] = 0;
  _xyWid =  500;
  _xyHgt =  500;
  _xzWid =  500;
  _xzHgt = 500;
  _xylb = 20;
  _xyrb = 20;
  _xytb = 20;
  _xybb =  20;
  _xzlb = 20;
  _xzrb = 20;
  _xztb = 20;
  _xzbb = 20;
  _XL = -250.;
  _XH = 250.;
  _YL = 0.;
  _YH = 500.;
  _ZL = -150.;
  _ZH = 150.;
  _xyCanvas = new TCanvas("xy", "Event Display (X-Y)", _xyWid, _xyHgt);
  _xyCanvas->Range(_XL, _YL, _XH, _YH);
  _xzCanvas = new TCanvas("xz", "Event Display (X-Z)", _xzWid, _xzHgt);
  _xzCanvas->Range(-150., _ZL, 150., _ZH);
  _irot = 0;
  _isZoomed = false;
  _showWires = false;

  GetEntry(0);

  // connect mouse click events in the canvas
  //
  _xyCanvas->Connect(
    "ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "ntsh", this,
    "doClickXY(Int_t,Int_t,Int_t,TObject*)");
  _xzCanvas->Connect(
    "ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "ntsh", this,
    "doClickXZ(Int_t,Int_t,Int_t,TObject*)");

}

#endif // #ifdef ntsh_cxx
