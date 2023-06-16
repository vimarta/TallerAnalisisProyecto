//
// Created by vimarta on 17/05/2023.
//

#include "../include/Geodetic.h"
#include "../include/Sat_const.h"
#include <math.h>


std::tuple<double, double, double> Geodetic(Matrix r){
    double R_equ = R_Earth;
    double f     = f_Earth;

    double epsRequ = eps*R_equ;        // Convergence criterion
    double e2      = f*(2.0-f);        // Square of eccentricity

    double X = r(0,0);                   // Cartesian coordinates
    double Y = r(1,0);
    double Z = r(2,0);
    double rho2 = X*X + Y*Y;           // Square of distance from z-axis

    // Check validity of input data
    if (Matrix::norm(r) == 0.0) {
        throw(' invalid input in Geodetic constructor\n');
        double lon = 0.0;
        double lat = 0.0;
        double h = -R_Earth;
    }

    //Iteration
    double dZ = e2*Z;

    double ZdZ, Nh, SinPhi, N, dZ_new;

    while(true) {
        ZdZ = Z + dZ;
        Nh = sqrt(rho2 + ZdZ * ZdZ);
        SinPhi = ZdZ / Nh;            // Sine of geodetic latitude
        N = R_equ / sqrt(1.0 - e2 * SinPhi * SinPhi);
        dZ_new = N * e2 * SinPhi;
        if (abs(dZ - dZ_new) < epsRequ)
            break;
        dZ = dZ_new;
    }

    // Longitude, latitude, altitude
    double lon = atan2 ( Y, X );
    double lat = atan2 ( ZdZ, sqrt(rho2) );
    double h   = Nh - N;
    tuple<double,double, double> t = std::make_tuple(lon,lat,h);
    return t;

}