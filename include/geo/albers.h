#pragma once
/*!
  \file ALBERS.H - Definition of \ref Albers "Albers Equal Area" projection

*/

#include "projection.h"

#ifdef MLIBSPACE
namespace MLIBSPACE {
#endif

/// %Albers Equal Area
class Albers : public ConicalProjection
{
public:
  Albers ();
  Albers (const ProjParams& params);
  Albers& operator= (const ProjParams& p);

  errc xy_geo (double x, double y, double *lat, double *lon) const;
  errc geo_xy (double *x, double *y, double lat, double lon) const;

  double h (double lat, double lon) const;
  double k (double lat, double lon) const;

private:
  void init ();
  double n, c_big, rho0;
};

#ifdef MLIBSPACE
};
#endif

