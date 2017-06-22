#define CellGeom_cxx
#include <vector>
using std::vector;

#include "CellGeom.h"
#include <sstream>

CellGeom::Wpos CellGeom::getPos(int layer, int column) const
{
  okat(layer, column);
  return _pos[layer][column];
}

double CellGeom::getX(int layer, int column) const
{
  okat(layer, column);
  return _pos[layer][column].x;
}

double CellGeom::getY(int layer, int column) const
{
  okat(layer, column);
  return _pos[layer][column].y;
}

void CellGeom::okat(int layer, int column) const
{
  if (layer<0 || layer>8 || column<0 || column>111)
  {
    std::stringstream ss;
    ss << "Invalid cell address: (layer, column) = ("
       << layer << ", " << column << ")";
    throw ss.str().c_str();
  }
  return;
}

void CellGeom::hitCoords(GHbase* bp, int h, double& x, double& y)
{
  // Calculate the physical location of a Geiger cell. (distances in cm).
  //
  // Source foil lies in the y-z plane
  //
  //int module = h.module();  // ignoring this, always 0 for demonstrator.
  GHbase &base = *bp;
  int side = (*base.v_side)[h];      // 0 = -ve X, 1 = +ve X.
  if (side != _side) throw "CellGeom::hitCoords wrong side geometry!";
  int layer = (*base.v_layer)[h];    // X index, 0 to 8.
  int column = (*base.v_column)[h];  // Y index, 0 to 112.

  x = getX(layer, column);
  y = getY(layer, column);
}
