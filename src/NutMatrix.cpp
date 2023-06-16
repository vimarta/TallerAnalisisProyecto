//
// Created by vimarta on 25/05/2023.
//

#include <tuple>
#include "../include/NutMatrix.h"
#include "../include/NutAngles.h"

Matrix NutMatrix(double Mjd_TT){
    // Mean obliquity of the ecliptic
    double epsN = MeanObliquity (Mjd_TT);

    // Nutation in longitude and obliquity
    double dpsi, deps;
    std::tie(dpsi,deps) = NutAngles(Mjd_TT);

    // Transformation from mean to true equator and equinox
    Matrix NutMat = R_x(-epsN-deps) * R_z(-dpsi) * R_x(+epsN);
    return NutMat;
}