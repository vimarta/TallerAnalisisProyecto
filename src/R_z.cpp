//
// Created by vimarta on 18/05/2023.
//

#include "../include/R_z.h"
#include <math.h>

Matrix R_z(double angle){
    double C = cos(angle);
    double S = sin(angle);
    Matrix rotmat(3,3);

    rotmat(0,0) =      C;  rotmat(0,1) =   S;  rotmat(0,2) = 0.0;
    rotmat(1,0) = -1.0*S;  rotmat(1,1) =   C;  rotmat(1,2) = 0.0;
    rotmat(2,0) =    0.0;  rotmat(2,1) = 0.0;  rotmat(2,2) = 1.0;

    return rotmat;
}