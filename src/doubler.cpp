//
// Created by vimarta on 31/05/2023.
//

#include <cmath>
#include "../include/doubler.h"
std::tuple<Matrix, Matrix, double, double, double, double, double, double, double> doubler
        (double cc1, double cc2,double magrsite1,double magrsite2, double magr1in,double magr2in,
         Matrix los1,Matrix los2,Matrix los3, Matrix rsite1,Matrix rsite2,Matrix rsite3,
         double t1,double t3, char direct) {

    double rho1 = (-cc1 + sqrt(cc1 * cc1 - 4 * (magrsite1 * magrsite1 - magr1in * magr1in))) / 2.0;
    double rho2 = (-cc2 + sqrt(cc2 * cc2 - 4 * (magrsite2 * magrsite2 - magr2in * magr2in))) / 2.0;

    Matrix r1(3);
    Matrix r2(3);
    Matrix r3(3);
    r1 = los1 * rho1 + rsite1;
    r2 = los2 * rho2 + rsite2;

    double magr1 = Matrix::norm(r1);
    double magr2 = Matrix::norm(r2);
    Matrix w(3);
    if (direct == 'y')
    {
        w = Matrix::cross(r1, r2) / (magr1 * magr2);
    }else{
        w = Matrix::cross(r1, r2) / (magr1 * magr2)*(-1);
    }

    double dot1 = Matrix::dot(rsite3,w);

    double dot2 = Matrix::dot(los3,w);

    double rho3 =  Matrix::dot(rsite3,w) * (-1)/ Matrix::dot(los3,w);
    r3 = los3*rho3 + rsite3;
    double magr3 = Matrix::norm(r3);

    double cosdv21 = Matrix::dot(r2,r1)/(magr2*magr1);
    double sindv21 = Matrix::norm(Matrix::cross(r2,r1))/(magr2*magr1);
    double dv21 = atan2(sindv21,cosdv21);

    double cosdv31 = Matrix::dot(r3,r1)/(magr3*magr1);
    double sindv31 = sqrt(1.0 - cosdv31*cosdv31);
    double dv31 = atan2(sindv31,cosdv31);

    double cosdv32 = Matrix::dot(r3,r2)/(magr3*magr2);
    double sindv32 = Matrix::norm(Matrix::cross(r3,r2))/(magr3*magr2);
    double dv32 = atan2(sindv32,cosdv32);
    double c1,c3,p;

    if (dv31 > pi) {
        c1 = (magr2 * sindv32) / (magr1 * sindv31);
        c3 = (magr2 * sindv21) / (magr3 * sindv31);
        p = (c1 * magr1 + c3 * magr3 - magr2) / (c1 + c3 - 1);
    }else {
        c1 = (magr1 * sindv31) / (magr2 * sindv32);
        c3 = (magr1 * sindv21) / (magr3 * sindv32);
        p = (c3 * magr3 - c1 * magr2 + magr1) / (-c1 + c3 + 1);
    }
    double ecosv1 = p/magr1-1;
    double ecosv2 = p/magr2-1;
    double ecosv3 = p/magr3-1;

    double esinv2;

    if (dv21 != pi) {
        esinv2 = (-cosdv21 * ecosv2 + ecosv1) / sindv21;
    }else {
        esinv2 = (cosdv32 * ecosv2 - ecosv3) / sindv31;
    }

    double e = sqrt(ecosv2*ecosv2+esinv2*esinv2);
    double a = p/(1-e*e);

    double n,s,c,sinde32,cosde32,deltae32, sinde21,cosde21,deltae21,deltam32,deltam12, sindh32, sindh21,deltah32, deltah21;
    if (e*e < 0.99) {
        n = sqrt(GM_Earth / (a*a*a));

        s = magr2 / p * sqrt(1 - (e*e)) * esinv2;
        c = magr2 / p * ((e*e) + ecosv2);

        sinde32 = magr3 / sqrt(a * p) * sindv32 - magr3 / p * (1 - cosdv32) * s;
        cosde32 = 1 - magr2 * magr3 / (a * p) * (1 - cosdv32);
        deltae32 = atan2(sinde32, cosde32);

        sinde21 = magr1 / sqrt(a * p) * sindv21 + magr1 / p * (1 - cosdv21) * s;
        cosde21 = 1 - magr2 * magr1 / (a * p) * (1 - cosdv21);
        deltae21 = atan2(sinde21, cosde21);

        deltam32 = deltae32 + 2 * s * ((sin(deltae32 / 2)) * (sin(deltae32 / 2))) - c * sin(deltae32);
        deltam12 = -deltae21 + 2 * s * ((sin(deltae21 / 2)) * (sin(deltae21 / 2))) + c * sin(deltae21);

    }else {
        n = sqrt(GM_Earth / (-a*a*a));

        s = magr2 / p * sqrt((e*e) - 1) * esinv2;
        c = magr2 / p * ((e*e) + ecosv2);

        sindh32 = magr3 / sqrt(-a * p) * sindv32 - magr3 / p * (1 - cosdv32) * s;
        sindh21 = magr1 / sqrt(-a * p) * sindv21 + magr1 / p * (1 - cosdv21) * s;

        deltah32 = log(sindh32 + sqrt(sindh32 * sindh32 + 1));
        deltah21 = log(sindh21 + sqrt(sindh21 * sindh21 + 1));

        deltam32 = -deltah32 + 2 * s * ((sinh(deltah32 / 2))*(sinh(deltah32 / 2))) + c * sinh(deltah32);
        deltam12 = deltah21 + 2 * s * ((sinh(deltah21 / 2))*(sinh(deltah21 / 2)))  - c * sinh(deltah21);

        deltae32 = deltah32;
    }
    double f1 = t1-deltam12/n;
    double f2 = t3-deltam32/n;

    double q1 = sqrt(f1*f1+f2*f2);
    return std::tie(r2,r3,f1,f2,q1,magr1,magr2,a,deltae32);


}