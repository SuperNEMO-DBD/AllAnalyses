#ifndef CellGeom_h
#define CellGeom_h

#include "GHbase.h"
#include <iostream>
#include <fstream>
#include <string>

// Class for setting/getting (x,y) positions of Geiger cell anodes.
//
// Initialise all wire positions via ideal geometry but allow modification
// of individual cell positions from external calibration files.
//
class CellGeom
{
  public :
    struct Wpos{double x; double y;};

    CellGeom(int side=0, const std::string& calib_file="");
    Wpos getPos(int layer, int column) const;
    double getX(int layer, int column) const;
    double getY(int layer, int column) const;
    void hitCoords(GHbase* bp, int h, double& x, double& y);

  private:
    void okat(int layer, int column) const; // verify address
    int _side;
    double _pitch; // cell and anode wire pitch
    double _xoff;  // offset from X wall (y=0)
    double _yoff;  // offset from calorimeter wall (x=0)

    Wpos _pos[9][112];  // [layer][column] positions.
};

#endif

#ifdef CellGeom_cxx
CellGeom::CellGeom(int side, const std::string& calib_file)
{
  // side: 0 => negative X coords.
  //       1 => positive X coords.
  //
  _side = side;
  _pitch = 4.4;
  _xoff = 1.4;
  _yoff = 1.0;

  // Fill default geometry.
  //
  for (int layer=0; layer<9; layer++)
  {
    double x = (layer + 0.5)*_pitch + _xoff;
    if (side ==0) x = -x;
    for (int column=0; column<112; column++)
    {
      double y = (column + 0.5)*_pitch + _yoff;
      _pos[layer][column].x = x;
      _pos[layer][column].y = y;
    }
  }

  // Do something here for reading external calibration file.
  //
  if (calib_file != "")
  {
    std::ifstream inp(calib_file.c_str());
    if (!inp.good())
    {
      std::string error("Failed to open calibration file: ");
      error += calib_file;
      throw error.c_str();
    }
    int l, c;
    double dx, dy;
    while (inp >> l >> c >> dx >> dy)
    {
      okat(l, c);
      _pos[l][c].x += dx;
      _pos[l][c].y += dy;
    }
    inp.close();
  }
}

#endif // #ifdef CellGeom_cxx
