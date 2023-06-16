//
// Created by vimarta on 18/05/2023.
//

#include "../include/LTC.h"
#include "../include/R_y.h"
#include "../include/R_z.h"


Matrix LTC(double lon, double lat){
    Matrix M(3,3);

    M = R_y(-1.0*lat)*R_z(lon);

    double Aux;

    for (int j=0; j < 3; j++) {
        Aux = M(0, j);
        M(0, j) = M(1, j);
        M(1, j) = M(2, j);
        M(2, j) = Aux;
    }
    return M;
}