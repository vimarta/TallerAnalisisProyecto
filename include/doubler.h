//
// Created by vimarta on 31/05/2023.
//

#ifndef PROYECTO_DOUBLER_H
#define PROYECTO_DOUBLER_H

#include <tuple>
#include "Matrix.h"
#include "Sat_const.h"

std::tuple<Matrix, Matrix, double, double, double, double, double, double, double> doubler
(double cc1, double cc2,double magrsite1,double magrsite2, double magr1in,double magr2in, Matrix los1,Matrix los2,Matrix los3, Matrix rsite1,Matrix rsite2,Matrix rsite3,double t1,double t3, char direct);

#endif //PROYECTO_DOUBLER_H
