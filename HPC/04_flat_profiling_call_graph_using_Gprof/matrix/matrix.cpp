#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    int size;

    size=1000;

     double matrix1[size][size];
     double matrix2[size][size];
     double result[size][size];

  srand(time(NULL));


cout << "Matrix 1:" << endl;
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            matrix1[i][j] = rand() % 10;
            cout << matrix1[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Matrix 2:" << endl;
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            matrix2[i][j] = rand() % 10;
            cout << matrix2[i][j] << " ";
        }
        cout << endl;
    }


 for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            result[i][j] = 0;
            for(int k=0; k<size; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }



cout << "Result:" << endl;
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}