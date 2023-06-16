//
// Created by vimarta on 27/04/2023.
//

#include "../include/Mjday.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/Position.h"
#include <tuple>
#include <fstream>
#include "../include/Geodetic.h"
#include "../include/LTC.h"
#include "../include/IERS.h"
#include "../include/Sat_const.h"
#include "../include/timediff.h"
#include "../include/PrecMatrix.h"
#include "../include/NutMatrix.h"
#include "../include/anglesdr.h"
#include "../include/NutAngles.h"
#include "../include/PoleMatrix.h"
#include "../include/EqnEquinox.h"
#include "../include/gast.h"
#include "../include/gmst.h"
#include "../include/GHAMatrix.h"
#include "../include/doubler.h"



int tests_run = 0;

#define FAIL() printf("\nfailure in %s() line %d\n", __func__, __LINE__)
#define _assert(test) do { if (!(test)) { FAIL(); return 1; } } while(0)
#define _verify(test) do { int r=test(); tests_run++; if(r) return r; } while(0)

Matrix eopdata(0);


int LTC()
{
    double lat = 0.376551295459273;
    double lon =  -2.76234307910694;

    Matrix M(3,3);
    M = LTC(lon, lat);

    _assert(abs(M(0,0) - 0.370223471399199) < pow(10,-7));
    _assert(abs(M(0,1) + 0.928942722252092) < pow(10,-7));
    _assert(abs(M(0,2) + 0                ) < pow(10,-7));
    _assert(abs(M(1,0) - 0.341586711932422) < pow(10,-7));
    _assert(abs(M(1,1) - 0.136136938528208) < pow(10,-7));
    _assert(abs(M(1,2) - 0.929938305587722) < pow(10,-7));
    _assert(abs(M(2,0) + 0.863859421119156) < pow(10,-7));
    _assert(abs(M(2,1) + 0.344284987681776) < pow(10,-7));
    _assert(abs(M(2,2) - 0.367715580035218) < pow(10,-7));

    return(0);
}

int Position()
{
    double lat = 0.376551295459273;
    double lon =  -2.76234307910694;
    double alt = 300.2;
    Matrix Rs = Position(lon, lat, alt);

    _assert(abs(Rs(0,0) + 5512568.44501153) < pow(10,-7));
    _assert(abs(Rs(1,0) + 2196994.68777797) < pow(10,-7));
    _assert(abs(Rs(2,0) - 2330805.22194045) < pow(10,-7));


    return 0;
}
int Geodetic()
{
    double lat = 0.376551295459273;
    double lon =  -2.76234307910694;
    double alt = 300.2;
    Matrix Rs(3,1);
    Rs = Position(lon, lat, alt);
    double lon1, lat1, h1;


    std::tie(lon1, lat1, h1) = Geodetic(Rs);

    _assert(abs(lon1 + 2.76234307910694 )< pow(10,-7));
    _assert(abs(lat1 - 0.376551295459273) < pow(10,-7));
    _assert(abs(h1 - 300.199999999255   )< pow(10,-7));


    return 0;
}

int IERS()
{
    double Mjd_UTC = 49746.1101504629;
    double UT1_UTC, TAI_UTC,  x_pole, y_pole;

    std::tie(UT1_UTC, TAI_UTC, x_pole, y_pole) = IERS(eopdata, Mjd_UTC);

    _assert(abs(UT1_UTC - 0.3261154          )  < pow(10,-7));
    _assert(abs(TAI_UTC - 29                 )  < pow(10,-7));
    _assert(abs(x_pole + 5.59693154156904e-07)  < pow(10,-7));
    _assert(abs(y_pole - 2.33443120404734e-06)  < pow(10,-7));

    return 0;
}

int timediff()
{
    double UT1_UTC = 0.3261154;
    double TAI_UTC = 29;
    double UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC;

    std::tie(UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC) = timediff(UT1_UTC, TAI_UTC);
    _assert(abs(UT1_TAI + 28.6738846)    < pow(10,-7));
    _assert(abs(UTC_GPS + 10        )    < pow(10,-7));
    _assert(abs(UT1_GPS + 9.6738846 )    < pow(10,-7));
    _assert(abs(TT_UTC - 61.184     )    < pow(10,-7));
    _assert(abs(GPS_UTC - 10        )    < pow(10,-7));

    return 0;
}

int PrecMatrix()
{
    double Mjd_TT = 49746.1108586111;
    Matrix P(3,3);

    P = PrecMatrix(MJD_J2000,Mjd_TT);
    _assert(abs(P(0,0) - 0.999999279427994      ) < pow(10,-7));
    _assert(abs(P(0,1) - 0.00110101213826256    ) < pow(10,-7));
    _assert(abs(P(0,2) - 0.000478451421900454   ) < pow(10,-7));
    _assert(abs(P(1,0) + 0.00110101213826363    ) < pow(10,-7));
    _assert(abs(P(1,1) - 0.999999393885917      ) < pow(10,-7));
    _assert(abs(P(1,2) + 2.63388277345423e-07   ) < pow(10,-5));
    _assert(abs(P(2,0) + 0.000478451421898      ) < pow(10,-3));
    _assert(abs(P(2,1) + 2.6339273552669e-07    ) < pow(10,-5));
    _assert(abs(P(2,2) - 0.999999885542077      ) < pow(10,-7));

    return 0;
}

int Mjday()
{

    _assert(abs(Mjday(2023,4,27,18,34,21) - 60061.7738541667 ) < pow(10,-10));
    _assert(abs(Mjday(2023,4,27,18,40,30) - 60061.7781250002 ) < pow(10,-10));

    return 0;
}

int NutMatrix()
{
    double Mjd_TT = 49746.1108586111;
    Matrix N(3, 3);

    N = NutMatrix(Mjd_TT);

    _assert(abs(N(0, 0) - 0.999999998058923    ) < pow(10, -7));
    _assert(abs(N(0, 1) + 5.71652123829452e-05 ) < pow(10, -7));
    _assert(abs(N(0, 2) + 2.47849116934142e-05 ) < pow(10, -7));
    _assert(abs(N(1, 0) - 5.71660825669244e-05 ) < pow(10, -7));
    _assert(abs(N(1, 1) - 0.999999997749659    ) < pow(10, -7));
    _assert(abs(N(1, 2) - 3.51101374659879e-05 ) < pow(10, -7));
    _assert(abs(N(2, 0) - 2.47829045591746e-05 ) < pow(10, -7));
    _assert(abs(N(2, 1) + 3.51115542541192e-05 ) < pow(10, -7));
    _assert(abs(N(2, 2) - 0.999999999076493    ) < pow(10, -7));
    return 0;
}
int MeanObliquity()
{
    double Mjd_TT = 49746.1108586111;
    double epsTest = MeanObliquity(Mjd_TT);

    _assert(abs(epsTest - 0.40910397936384) < pow(10, -7));
    return 0;
}
int NutAngles()
{
    double Mjd_TT = 49746.1108586111;
    double dpsi, deps;
    std::tie(dpsi,deps) = NutAngles(Mjd_TT);

    _assert(abs(dpsi - 6.23069286633653e-05) < pow(10, -10));
    _assert(abs(deps + 3.51108659887327e-05) < pow(10, -10));
    return 0;
}

int R_x()
{
    double testx = -0.409068868517938;
    Matrix N(3, 3);

    N = R_x(testx);

    _assert(abs(N(0, 0) - 1                  )   < pow(10, -7));
    _assert(abs(N(0, 1) + 0                  )   < pow(10, -7));
    _assert(abs(N(0, 2) + 0                  )   < pow(10, -7));
    _assert(abs(N(1, 0) - 0                  )   < pow(10, -7));
    _assert(abs(N(1, 1) - 0.917491582882778  )   < pow(10, -7));
    _assert(abs(N(1, 2) + 0.397755195238547  )   < pow(10, -7));
    _assert(abs(N(2, 0) - 0                  )   < pow(10, -7));
    _assert(abs(N(2, 1) - 0.397755195238547  )   < pow(10, -7));
    _assert(abs(N(2, 2) - 0.917491582882778  )   < pow(10, -7));
    return 0;
}

int R_z()
{
    double testz = -6.2306928663362e-05;
    Matrix N(3, 3);

    N = R_z(testz);

    _assert(abs(N(0, 0) - 0.999999998058923     )    < pow(10, -7));
    _assert(abs(N(0, 1) + 6.23069286230478e-05 )    < pow(10, -7));
    _assert(abs(N(0, 2) + 0                     )    < pow(10, -7));
    _assert(abs(N(1, 0) - 6.23069286230478e-05  )    < pow(10, -7));
    _assert(abs(N(1, 1) - 0.999999998058923     )    < pow(10, -7));
    _assert(abs(N(1, 2) + 0                     )    < pow(10, -7));
    _assert(abs(N(2, 0) - 0                     )    < pow(10, -7));
    _assert(abs(N(2, 1) - 0                     )    < pow(10, -7));
    _assert(abs(N(2, 2) - 1                     )    < pow(10, -7));
    return 0;
}

int PoleMatrix()
{
    double x_pole = -5.59693154156904e-07;
    double y_pole = 2.33443120404734e-06;
    Matrix N(3, 3);

    N = PoleMatrix(x_pole, y_pole);

    _assert(abs(N(0, 0) - 0.999999999999843   )  < pow(10, -7));
    _assert(abs(N(0, 1) + 1.3065651637543e-12 ) < pow(10, -7));
    _assert(abs(N(0, 2) + 5.5969315415535e-07 ) < pow(10, -7));
    _assert(abs(N(1, 0) - 0)  < pow(10, -7));
    _assert(abs(N(1, 1) - 0.999999999997275   )  < pow(10, -7));
    _assert(abs(N(1, 2) + 2.33443120404522e-06)  < pow(10, -7));
    _assert(abs(N(2, 0) - 5.59693154156875e-07)  < pow(10, -7));
    _assert(abs(N(2, 1) - 2.33443120404485e-06)  < pow(10, -7));
    _assert(abs(N(2, 2) - 0.999999999997119   )  < pow(10, -7));
    return 0;
}

int EqnEquinox()
{
    double Mjd_UT1 = 49746.1125384968;
    double Test = EqnEquinox(Mjd_UT1);

    _assert(abs(Test - 5.71659648303605e-05 )< pow(10, -7));
    return 0;
}

int gast()
{
    double Mjd_UT1 = 49746.1125384968;
    double Test = gast(Mjd_UT1);

    _assert(abs(Test - 2.9391674215588) < pow(10, -10));
    return 0;
}

int gmst()
{
    double Mjd_UT1 = 49746.1125384968;
    double Test = gmst(Mjd_UT1);

    _assert(abs(Test - 2.93911025559397 ) < pow(10, -7));
    return 0;
}

int GHAMatrix()
{
    double Mjd_UT1 = 49746.1125384968;
    Matrix N(3, 3);

    N = GHAMatrix(Mjd_UT1);

    _assert(abs(N(0, 0) + 0.979581876846078)    < pow(10, -7));
    _assert(abs(N(0, 1) - 0.201045633015777)    < pow(10, -7));
    _assert(abs(N(0, 2) + 0                )    < pow(10, -7));
    _assert(abs(N(1, 0) + 0.201045633015777)    < pow(10, -7));
    _assert(abs(N(1, 1) + 0.979581876846078)    < pow(10, -7));
    _assert(abs(N(1, 2) + 0                )    < pow(10, -7));
    _assert(abs(N(2, 0) - 0                )    < pow(10, -7));
    _assert(abs(N(2, 1) - 0                )    < pow(10, -7));
    _assert(abs(N(2, 2) - 1                )    < pow(10, -7));
    return 0;
}

int doubler()
{
    Matrix r2(3);
    Matrix r3(3);
    Matrix los1(3);
    los1(0,0) = -0.0514407301715203;
    los1(1,0) = 0.838593164440367;
    los1(2,0) = 0.54232403213698;

    Matrix los2(3);
    los2(0,0) = 0.185350425424354;
    los2(1,0) = 0.924321659182723;
    los2(2,0) = 0.333578611665541;

    Matrix los3(3);
    los3(0,0) = 0.48999206372453;
    los3(1,0) = 0.865773547227108;
    los3(2,0) = -0.10170517395279;

    Matrix rsite1(3);
    rsite1(0,0) = 5854667.7577933;
    rsite1(1,0) = 962016.736146505;
    rsite1(2,0) = 2333503.53479825;

    Matrix rsite2(3);
    rsite2(0,0) = 5847642.87233096;
    rsite2(1,0) = 1003838.42368066;
    rsite2(2,0) = 2333501.82312028;

    Matrix rsite3(3);
    rsite3(0,0) = 5839555.2146941;
    rsite3(1,0) = 1049868.17436044;
    rsite3(2,0) = 2333499.77773523;

    double f1, f2, q1, magr1, magr2, a, deltae32;
    double cc1 = 3542174.64126966;
    double cc2 = 5580277.97983915;
    double magrsite1 = 6375566.60240377;
    double magrsite2 = 6375566.60240377;
    double magr1in = 7015950.7;
    double magr2in = 7079732.07;
    double t1 = -97.9999914765358;
    double t3 = 108.000017702579;
    char direct = 'y';
    std::tie(r2,r3, f1, f2, q1, magr1, magr2, a, deltae32) = doubler(cc1, cc2, magrsite1, magrsite2, magr1in, magr2in,los1, los2, los3, rsite1, rsite2, rsite3, t1, t3, direct);

    _assert(abs(r2(0, 0) - 6100522.45717325) < pow(10, -7));
    _assert(abs(r2(1, 0) - 2264920.38181335) < pow(10, -7));
    _assert(abs(r2(2, 0) - 2788613.92031198) < pow(10, -7));

    _assert(abs(r3(0, 0) - 6455956.51848352) < pow(10, -7));
    _assert(abs(r3(1, 0) - 2138995.9027581) < pow(10, -7));
    _assert(abs(r3(2, 0) - 2205556.47728644) < pow(10, -7));

    _assert(abs(f1 + 18.5921446051542) < pow(10, -7));
    _assert(abs(f2 - 7.86861985501643) < pow(10, -7));
    _assert(abs(q1 - 20.188685431244) < pow(10, -7));
    _assert(abs(magr1 - 7015950.7) < pow(10, -7));
    _assert(abs(magr2 - 7079732.07) < pow(10, -7));
    _assert(abs(a - 6238411.00963291) < pow(10, -5));
    _assert(abs(deltae32 - 0.11248279851753) < pow(10, -7));

    return 0;
}

int anglesdr()
{

    double obs12 = 1.0559084894933;
    double obs92 = 1.36310214580757;
    double obs182 = 1.97615602688759;
    double obs13 = 0.282624656433946;
    double obs93 = 0.453434794338875;
    double obs183 = 0.586427138011591;
    double Mjd1 = 49746.1101504629;
    double Mjd2 = 49746.1112847221;
    double Mjd3 = 49746.1125347223;

    Matrix Rs(3);
    Rs(0,0) = -5512568.44501153;
    Rs(1,0) = -2196994.68777797;
    Rs(2,0) = 2330805.22194045;

    Matrix r2(3);
    Matrix v2(3);

    std::tie(r2,v2) = anglesdr ( obs12, obs92,obs182,obs13,obs93,obs183,Mjd1,Mjd2,Mjd3,Rs,Rs,Rs );

    _assert(abs(r2(0, 0) - 6147304.28) < pow(10, -1));
    _assert(abs(r2(1, 0) - 2498216.05) < pow(10, -1));
    _assert(abs(r2(2, 0) - 2872808.0) < pow(10, -1));

    _assert(abs(v2(0, 0) - 3764.63) < pow(10, -1));
    _assert(abs(v2(1, 0) + 2217.85) < pow(10, -1));
    _assert(abs(v2(2, 0) + 6141.47) < pow(10, -1));

    return 0;
}

int all_tests()
{

    _verify(Mjday);
    _verify(Position);
    _verify(Geodetic);
    _verify(LTC);
    _verify(IERS);
    _verify(timediff);
    _verify(PrecMatrix);
    _verify(MeanObliquity);
    _verify(NutAngles);
    _verify(R_z);
    _verify(R_x);
    _verify(NutMatrix);
    _verify(PoleMatrix);
    _verify(EqnEquinox);
    _verify(gmst);
    _verify(gast);
    _verify(GHAMatrix);
    _verify(doubler);
    _verify(anglesdr);


    return 0;
}


int main()
{
    Matrix Cnm(361,361);
    Matrix Snm(361,361);

    string tlinep;
    ifstream fichero;
    fichero.open("C:\\CLionProjects\\proyecto (2)\\data\\egm.txt");


    double temp[6];

    for (int n=0; n < 360; n++){
        for (int m=0; n < 360; n++){
            for(int k = 0; k < 6; k++) fichero >> temp[k];
            Cnm(n,m) = temp[2];
            Snm(n,m) = temp[3];
        }
    }
    fichero.close();

    // Initialize UT1-UTC and TAI-UTC time difference
    string filename1 = "C:\\CLionProjects\\proyecto (2)\\data\\eop19620101.txt";
    fichero.open(filename1);
    if(!fichero){
        cout << "error" << endl;
    }

    // | Date MJD x y UT1-UTC LOD dPsi dEpsilon dX dY DAT
    // | (0h UTC) " " s s " " " " s
    vector<vector<double>> eopdata2(0,vector<double>(13));
    double actu;
    while(fichero >> actu){
        vector<double> aux(13);
        aux[0] = actu;
        for(int i = 1; i < 13; i++) fichero >> aux[i];
        eopdata2.push_back(aux);
    }
    eopdata = Matrix(eopdata2.size(),eopdata2[0].size(),eopdata2).traspuesta();
    fichero.close();

    //for(int i = 0; i < 13; i++) cout << "dato " << eopdata[0][i] << endl;

    // read observations
    string filename2 = "C:\\CLionProjects\\proyecto (2)\\data\\GEOS3.txt";
    fichero.open(filename2);
    string tline;

    int Y,M,D,h,m;
    double s,az,el,Dist;

    Matrix obs(18, 4);

    for(int i = 0; i < 18 ;i++){
        getline(fichero, tline);
        Y = stoi(tline.substr(0,4));
        M = stoi(tline.substr(5,2));
        D = stoi(tline.substr(8,2));
        h = stoi(tline.substr(12,2));
        m = stoi(tline.substr(15,2));
        s = stod(tline.substr(18,5));
        az = stod(tline.substr(25,7));
        el = stod(tline.substr(35,6));
        Dist = stod(tline.substr(44,9));
        obs(i,0) = Mjday(Y,M,D,h,m,s);
        obs(i,1) = Rad*az;
        obs(i,2) = Rad*el;
        obs(i,3) = 1e3*Dist;
    }

    fichero.close();
    double sigma_range = 92.5;     // [m]
    double sigma_az = 0.0224*Rad;  // [rad]
    double sigma_el = 0.0139*Rad;  // [rad]

    // Kaena Point station
    double lat = Rad*21.5748;     // [rad]
    double lon = Rad*(-158.2706); // [rad]
    double alt = 300.20;          // [m]
    Matrix Rs = Position(lon, lat, alt);
    double Mjd1 = obs(0,0);
    double Mjd2 = obs(8,0);
    double Mjd3 = obs(17,0);

    Matrix r2(3);
    Matrix v2(3);

    std::tie(r2,v2) = anglesdr ( obs(0,1),obs(8,1),obs(17,1),obs(0,2),obs(8,2),obs(17,2),Mjd1,Mjd2,Mjd3,Rs,Rs,Rs );

    Matrix Y0_apr(6,1);
    Y0_apr(0,0) = r2(0,0);
    Y0_apr(1,0) = r2(1,0);
    Y0_apr(2,0) = r2(2,0);
    Y0_apr(3,0) = v2(0,0);
    Y0_apr(4,0) = v2(1,0);
    Y0_apr(5,0) = v2(2,0);

    Y0_apr.print();

    int result = all_tests();

    if (result == 0)
        printf("PASSED\n");

    printf("Tests run: %d\n", tests_run);


    return result != 0;
}
