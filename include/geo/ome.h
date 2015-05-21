#pragma once

/*!
  \file OME.H - ObliqueMercator class definition

*/

#include "projection.h"

#ifdef MLIBSPACE
namespace MLIBSPACE {
#endif

///Oblique %Mercator
class ObliqueMercator : public Projection
{
public:
  ObliqueMercator () {};
  ObliqueMercator (const ProjParams& params);

  ObliqueMercator& operator= (const ProjParams& p);

  double skew_azimuth () const;

  errc geo_xy( double *x, double *y, double lat, double lon ) const;
  errc xy_geo( double x, double y, double *lat, double *lon ) const;

  double h (double lat, double lon) const   { return k (lat, lon); };
  double k (double lat, double lon) const;

protected:
  virtual void init ();

  virtual void deskew( double u, double v, double *x, double *y ) const =0;
  virtual void skew( double *u, double *v, double x, double y ) const =0;
  double exptau (double val) const;
  double gamma0;

private:
  errc uvgeo (double u, double v, double *lat, double *lon) const;
  double A, B, E, lam1;
};


/// %Hotine Oblique %Mercator
class Hotine : public ObliqueMercator
{
public:
  Hotine () {};
  Hotine (const ProjParams& params) : ObliqueMercator (params) {};
  Hotine& operator= (const ProjParams& p);

protected:
  void deskew (double u, double v, double *x, double *y) const;
  void skew (double *u, double *v, double x, double y) const;
};

/// Rectified Skew Orthomorphic
class RSO : public ObliqueMercator
{
public:
  RSO () {};
  RSO (const ProjParams& params) : ObliqueMercator (params) {};
  RSO& operator= (const ProjParams& par);

protected:
  void deskew (double u, double v, double *x, double *y) const;
  void skew (double *u, double *v, double x, double y) const;
};

/*==================== INLINE FUNCTIONS ===========================*/

/// Return skew azimuth
inline
double ObliqueMercator::skew_azimuth () const { return par.skew_; }

inline
Hotine& Hotine::operator= (const ProjParams& par)
{
  ObliqueMercator::operator= (par);
  return *this;
};

inline
RSO& RSO::operator= (const ProjParams& par) 
{
  ObliqueMercator::operator= (par); 
  return *this;
};

#ifdef MLIBSPACE
};
#endif
