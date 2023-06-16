//
// Created by vimarta on 31/05/2023.
//

#include "../include/GHAMatrix.h"
#include "../include/gast.h"

Matrix GHAMatrix(double Mjd_UT1){
    return R_z(gast(Mjd_UT1));
}