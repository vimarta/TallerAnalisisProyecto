//
// Created by vimarta on 17/05/2023.
//

#include "../include/anglesdr.h"
#include "../include/Geodetic.h"
#include "../include/LTC.h"
#include "../include/IERS.h"
#include "../include/timediff.h"
#include <math.h>
#include "../include/PrecMatrix.h"
#include "../include/NutMatrix.h"
#include "../include/PoleMatrix.h"
#include "../include/GHAMatrix.h"
#include "../include/doubler.h"


extern Matrix eopdata;

std::tuple<Matrix, Matrix> anglesdr(double az1,double az2,double az3,double el1,
                                    double el2,double el3,double Mjd1,double Mjd2,
                                    double Mjd3, Matrix rsite1, Matrix rsite2, Matrix rsite3){
    double magr1in = 1.1* R_Earth;
    double magr2in = 1.11* R_Earth;
    char direct  = 'y';

    double tol    = 1e-8*R_Earth;
    double pctchg = 0.005;

    double t1 = (Mjd1 - Mjd2)*86400.0;
    double t3 = (Mjd3 - Mjd2)*86400.0;

    Matrix los1(3);
    los1(0,0) = cos(el1)*sin(az1);
    los1(1,0) = cos(el1)*cos(az1);
    los1(2,0) = sin(el1);
    Matrix los2(3);
    los2(0,0) = cos(el2)*sin(az2);
    los2(1,0) = cos(el2)*cos(az2);
    los2(2,0) =sin(el2);
    Matrix los3(3);
    los3(0,0) = cos(el3)*sin(az3);
    los3(1,0) = cos(el3)*cos(az3);
    los3(2,0) =sin(el3);

    double lon1, lat1, h1, lon2, lat2, h2, lon3, lat3, h3;

    std::tie(lon1, lat1, h1) = Geodetic(rsite1);
    std::tie(lon2, lat2, h2) = Geodetic(rsite2);
    std::tie(lon3, lat3, h3) = Geodetic(rsite3);

    Matrix M1(3,3);
    Matrix M2(3,3);
    Matrix M3(3,3);

    M1 = LTC(lon1, lat1);
    M2 = LTC(lon2, lat2);
    M3 = LTC(lon3, lat3);

    //body-fixed system
    los1 = M1.traspuesta()*los1;
    los2 = M1.traspuesta()*los2;
    los3 = M1.traspuesta()*los3;

    // mean of date system (J2000)
    double Mjd_UTC = Mjd1;
    double UT1_UTC, TAI_UTC,  x_pole, y_pole, UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC;

    std::tie(UT1_UTC, TAI_UTC, x_pole, y_pole) = IERS(eopdata, Mjd_UTC);
    std::tie(UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC) = timediff(UT1_UTC, TAI_UTC);
    double Mjd_TT = Mjd_UTC + TT_UTC/86400;
    double Mjd_UT1 = Mjd_TT + (UT1_UTC-TT_UTC)/86400.0;

    Matrix P(3,3);
    Matrix N(3,3);
    Matrix T(3,3);
    Matrix E(3,3);
    P = PrecMatrix(MJD_J2000,Mjd_TT);
    N = NutMatrix(Mjd_TT);
    T = N * P;
    E = PoleMatrix(x_pole,y_pole) * GHAMatrix(Mjd_UT1) * T;

    los1 = E.traspuesta()*los1;
    rsite1 = E.traspuesta()*rsite1;

    Mjd_UTC = Mjd2;
    std::tie(UT1_UTC, TAI_UTC, x_pole, y_pole) = IERS(eopdata, Mjd_UTC);
    std::tie(UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC) = timediff(UT1_UTC, TAI_UTC);
    Mjd_TT = Mjd_UTC + TT_UTC/86400;
    Mjd_UT1 = Mjd_TT + (UT1_UTC-TT_UTC)/86400.0;

    P = PrecMatrix(MJD_J2000,Mjd_TT);
    N = NutMatrix(Mjd_TT);
    T = N * P;
    E = PoleMatrix(x_pole,y_pole) * GHAMatrix(Mjd_UT1) * T;

    los2 = E.traspuesta()*los2;
    rsite2 = E.traspuesta()*rsite2;

    Mjd_UTC = Mjd3;
    std::tie(UT1_UTC, TAI_UTC, x_pole, y_pole) = IERS(eopdata, Mjd_UTC);
    std::tie(UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC) = timediff(UT1_UTC, TAI_UTC);
    Mjd_TT = Mjd_UTC + TT_UTC/86400;
    Mjd_UT1 = Mjd_TT + (UT1_UTC-TT_UTC)/86400.0;

    P = PrecMatrix(MJD_J2000,Mjd_TT);
    N = NutMatrix(Mjd_TT);
    T = N * P;
    E = PoleMatrix(x_pole,y_pole) * GHAMatrix(Mjd_UT1) * T;

    los3 = E.traspuesta()*los3;
    rsite3 = E.traspuesta()*rsite3;


    double magr1old  = 99999999.9;
    double magr2old  = 99999999.9;
    double magrsite1 = Matrix::norm(rsite1);
    double magrsite2 = Matrix::norm(rsite2);
    double magrsite3 = Matrix::norm(rsite3);

    double cc1 = 2.0*Matrix::dot(los1,rsite1);
    double cc2 = 2.0*Matrix::dot(los2,rsite2);
    double ktr = 0;

    Matrix r2(3);
    Matrix r3(3);
    Matrix v2(3);
    double f1, f2, q1, magr1, magr2, a, deltae32,f,g, magr1o, deltar1, f1delr1, f2delr1, q2, pf1pr1, pf2pr1, magr2o, deltar2, f1delr2, f2delr2, q3, pf1pr2, pf2pr2, delta, delta1, delta2 ;

    while (abs(magr1in-magr1old) > tol | abs(magr2in-magr2old) > tol) {

        ktr = ktr + 1;
        std::tie(r2, r3, f1, f2, q1, magr1, magr2, a, deltae32) = doubler(cc1, cc2, magrsite1, magrsite2, magr1in, magr2in,los1, los2, los3, rsite1, rsite2, rsite3, t1, t3, direct);

        f = 1.0 - a / magr2 * (1.0 - cos(deltae32));
        g = t3 - sqrt(a*a*a / GM_Earth) * (deltae32 - sin(deltae32));
        v2 = (r3 -  (r2*f)) / g;

        magr1o = magr1in;
        magr1in = (1.0 + pctchg) * magr1in;
        deltar1 = pctchg * magr1in;
        std::tie(r2, r3, f1delr1, f2delr1, q2, magr1, magr2, a, deltae32) = doubler(cc1, cc2, magrsite1, magrsite2, magr1in, magr2in,los1, los2, los3, rsite1, rsite2, rsite3, t1, t3, direct);
        pf1pr1 = (f1delr1 - f1) / deltar1;
        pf2pr1 = (f2delr1 - f2) / deltar1;

        magr1in = magr1o;
        deltar1 = pctchg * magr1in;
        magr2o = magr2in;
        magr2in = (1.0 + pctchg) * magr2in;
        deltar2 = pctchg * magr2in;
        std::tie(r2, r3, f1delr2, f2delr2, q3, magr1, magr2, a, deltae32) = doubler(cc1, cc2, magrsite1, magrsite2, magr1in, magr2in,los1, los2, los3, rsite1, rsite2, rsite3, t1, t3, direct);
        pf1pr2 = (f1delr2 - f1) / deltar2;
        pf2pr2 = (f2delr2 - f2) / deltar2;

        magr2in = magr2o;
        deltar2 = pctchg * magr2in;

        delta = pf1pr1 * pf2pr2 - pf2pr1 * pf1pr2;
        delta1 = pf2pr2 * f1 - pf1pr2 * f2;
        delta2 = pf1pr1 * f2 - pf2pr1 * f1;

        deltar1 = -delta1 / delta;
        deltar2 = -delta2 / delta;

        magr1old = magr1in;
        magr2old = magr2in;

        magr1in = magr1in + deltar1;
        magr2in = magr2in + deltar2;
    }

    std::tie(r2,r3,f1,f2,q1,magr1,magr2,a,deltae32) = doubler(cc1,cc2,magrsite1,magrsite2,magr1in,magr2in,los1,los2,los3,rsite1,rsite2,rsite3,t1,t3,direct);


    f  = 1.0 - a/magr2*(1.0-cos(deltae32));
    g  = t3 - sqrt((a*a*a)/GM_Earth)*(deltae32-sin(deltae32));
    v2 = (r3 - r2*f)/g;
    return std::tie(r2,v2);
}