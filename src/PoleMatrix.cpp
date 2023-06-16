//
// Created by vimarta on 31/05/2023.
//PoleMatrix.m
//
//Purpose:
//  Transformation from pseudo Earth-fixed to Earth-fixed coordinates
//  for a given date
//
//Input:
//  Pole coordinte(xp,yp)
//
//Output:
//  PoleMat   Pole matrix
//
//Last modified:   2015/08/12   M. Mahooti
//

#include "../include/PoleMatrix.h"
Matrix PoleMatrix(double xp, double yp){

    return R_y(-xp) * R_x(-yp);
}