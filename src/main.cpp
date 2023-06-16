#include <iostream>
#include <fstream>
#include <valarray>
#include <vector>


#include "EKF_GEOS3.h"


using namespace std;

void imprimirMatriz(const vector<vector<float>>& matriz) {
    int n = matriz.size();
    int m = matriz[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            //if(matriz[i][j] > pow(10,-12) and matriz[i][j] < pow(10, 12)){
                cout << matriz[i][j] << " ";
            //}

        }
        cout << endl;
    }
}

/*int main() {

    leerFichero();

    vector<vector<float>> matriz = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    vector<vector<float>> matriz2 = {{1}, {2}, {3}};

    cout << "Matriz original:" << endl;
    imprimirMatriz(matriz);
    vector<vector<float>> traspuestaMatriz = traspuesta(matriz);
    cout << "Traspuesta de la matriz:" << endl;
    imprimirMatriz(traspuestaMatriz);

    vector<vector<float>> matrizMultiplicacion = multiplicacion(matriz, traspuestaMatriz);
    vector<vector<float>> matrizMultiplicacion2 = multiplicacion(matriz, matriz2);

    cout << "Multiplicacion de las matrices:" << endl;
    imprimirMatriz(matrizMultiplicacion);

    cout << "Multiplicacion de las matrices:" << endl;
    imprimirMatriz(matrizMultiplicacion2);

    float angulo = -2.33443120404734e-06;

    vector<vector<float>> matrizR_x = R_x(angulo);

    cout << "rotacion de la matriz:" << endl;
    imprimirMatriz(matrizR_x);

    return 0;
}
*/