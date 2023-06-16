//
// Created by vimarta on 18/05/2023.
//

#include "../include/IERS.h"
#include "../include/Sat_const.h"
#include <math.h>
#include <iostream>

using namespace std;

std::tuple<double, double, double, double> IERS(Matrix eop, double Mjd_TT){
    double Arcs = 3600.0*180.0/pi;  // Arcseconds per radian

    double mj = (round(Mjd_TT));
    double nop = eop.length();

    for (int i = 0; i < nop; i++) {
        if (mj == eop(3, i)) {
            for (int j = 0; j < 13; j++) {
                eop(j,0) = eop(j,i);
            }
            break;
        }
    }

    // Setting of IERS Earth rotation parameters
    // (UT1-UTC [s], TAI-UTC [s], x ["], y ["])
    double UT1_UTC = eop(6, 0);      // UT1-UTC time difference [s]
    double TAI_UTC = eop(12, 0);     // TAI-UTC time difference [s]
    double x_pole  = eop(4, 0)/Arcs; // Pole coordinate [rad]
    double y_pole  = eop(5, 0)/Arcs; // Pole coordinate [rad]
    tuple<double,double, double, double> t = std::make_tuple(UT1_UTC,TAI_UTC,x_pole, y_pole);
    return t;
}
