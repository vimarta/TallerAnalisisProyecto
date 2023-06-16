//
// Created by vimarta on 18/05/2023.
//

#ifndef PROYECTO_IERS_H
#define PROYECTO_IERS_H

#include <tuple>
#include "Matrix.h"

std::tuple<double, double, double, double> IERS(Matrix eop, double Mjd_TT);

#endif //PROYECTO_IERS_H
