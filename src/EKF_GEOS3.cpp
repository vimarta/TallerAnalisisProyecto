//
// Created by vimarta on 19/04/2023.
//

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tuple>

#include "../include/EKF_GEOS3.h"
#include "../include/Sat_const.h"
#include "../include/Position.h"
#include "../include/Mjday.h"
#include "anglesdr.h"

using namespace std;

/*Matrix eopdata(0);

int main(){
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

}*/
