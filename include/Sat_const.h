#ifndef _SATCONST_
#define _SATCONST_

// Mathematical constants
const double pi        = 3.14159265358979324;
const double pi2       = 2.0*pi;              // 2pi
const double Rad       = pi/180.0;            // Radians per degree
const double Deg       = 180.0/pi;            // Degrees per radian
const double Arcs      = 3600.0*180.0/pi;     // Arcseconds per radian

// General
const double MJD_J2000 = 51544.5;             // Modif. Julian Date of J2000.0
const double T_B1950   = -0.500002108;        // Epoch B1950
const double c_light   = 299792457.999999984; // Speed of light  [m/s]; DE200
const double AU        = 149597870659.999996; // Astronomical unit [m]; DE200

// Physical parameters of the Earth, Sun and Moon

// Equatorial radius and flattening
const double R_Earth   =   6378.137e3;        // Radius Earth [m]; WGS-84
const double f_Earth   = 1.0/298.257223563;   // Flattening; WGS-84
const double R_Sun     = 696000.0e3;          // Radius Sun [m]; Seidelmann 1992
const double R_Moon    =   1738.0e3;          // Radius Moon [m]

// Earth rotation (derivative of GMST at J2000; differs from inertial period by precession)
const double omega_Earth = 7.2921158553e-5;   // [rad/s]; Aoki 1982, NIMA 1997

// Gravitational coefficients
const double GM_Earth    = 398600.4418e9;                // [m^3/s^2]; WGS-84
const double GM_Sun      = 1.327124399354841e20;         // [m^3/s^2]; DE200
const double GM_Moon     = GM_Earth/81.3005869999999931; // [m^3/s^2]; DE200
const double GM_Mercury  = 22032.08047272131e9;          // [m^3/s^2]; DE200
const double GM_Venus    = 324858.7656168717e9;          // [m^3/s^2]; DE200
const double GM_Mars     = 42828.28658876890e9;          // [m^3/s^2]; DE200
const double GM_Jupiter  = 126712597.0817946e9;          // [m^3/s^2]; DE200
const double GM_Saturn   = 37939519.70882996e9;          // [m^3/s^2]; DE200
const double GM_Uranus   = 5780158.533597719e9;          // [m^3/s^2]; DE200
const double GM_Neptune  = 6871307.771479524e9;          // [m^3/s^2]; DE200
const double GM_Pluto    = 1020.864920706286e9;          // [m^3/s^2]; DE200
              
// Solar radiation pressure at 1 AU
const double P_Sol       = 4.560e-6;          // [N/m^2] (~1367 W/m^2); IERS 96


//valor e eps

const double eps = 2.22044604925031e-16;

#endif
