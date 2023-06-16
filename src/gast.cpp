//
// Created by vimarta on 31/05/2023.
//

#include "../include/gast.h"
#include "../include/gmst.h"
#include "../include/EqnEquinox.h"
#include "../include/Sat_const.h"
#include <cmath>

double gast(double Mjd_UT1){
    return  fmod( gmst(Mjd_UT1) + EqnEquinox(Mjd_UT1), 2*pi );
}