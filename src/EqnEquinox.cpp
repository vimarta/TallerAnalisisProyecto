//
// Created by vimarta on 31/05/2023.
//

#include <cmath>
#include "../include/EqnEquinox.h"

double EqnEquinox(double Mjd_TT){
    // Nutation in longitude and obliquity
    double dpsi, deps;

    std::tie(dpsi,deps) = NutAngles(Mjd_TT);

    // Equation of the equinoxes
    return dpsi * cos ( MeanObliquity(Mjd_TT) );
}