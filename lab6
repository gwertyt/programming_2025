#include <iostream>
#include <cstdlib>

using namespace std;

int** matrix1(int A, int B, int C, int D){
    int rows = 2 + A;
    int cols = 2 + B;

    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }

    matrix[0][0] = A;
    matrix[0][1] = B;
    matrix[1][0] = C;
    matrix[1][1] = D;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!(i < 2 && j < 2)) {
                matrix[i][j] = i * C + j * D;
            }
        }
    }

    return matrix;
}

int* findZeroColumns(int** matrix, int rows, int cols, int& zeroCount) {
    int* zeroColumns = 0;
    zeroCount = 0;

    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            if (matrix[i][j] == 0) {
                zeroCount++;
                break;
            }
        }
    }

    if (zeroCount > 0) {
        zeroColumns = (int*)malloc(zeroCount * sizeof(int));
        if (zeroColumns == 0) {
            return 0;
        }

        int index = 0;
        for (int j = 0; j < cols; j++) {
            for (int i = 0; i < rows; i++) {
                if (matrix[i][j] == 0) {
                    zeroColumns[index++] = j;
                    break;
                }
            }
        }
    }
    return zeroColumns;
}

int** removeColumns(int** matrix, int rows, int& cols, int* ubratCols, int ubratCount) {
    if (ubratCount == 0 || ubratCols == 0) {
        return matrix;
    }

    int newCols = cols - ubratCount;
    int** newMatrix = (int**)malloc(rows * sizeof(int*));
    if (newMatrix == 0) {
        return matrix;
    }

    for (int i = 0; i < rows; i++) {
        newMatrix[i] = (int*)malloc(newCols * sizeof(int));
        if (newMatrix[i] == 0) {
            for (int k = 0; k < i; k++) {
                free(newMatrix[k]);
            }
            free(newMatrix);
            return matrix;
        }
    }

    for (int i = 0; i < rows; i++) {
        int indexCol = 0;
        for (int j = 0; j < cols; j++) {
            bool skip = false;
            for (int k = 0; k < ubratCount; k++) {
                if (j == ubratCols[k]) {
                    skip = true;
                    break;
                }
            }
            if (!skip) {
                newMatrix[i][indexCol++] = matrix[i][j];
            }
        }
    }

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    cols = newCols;
    return newMatrix;
}

void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}


int main() {
    int A, B, C, D;

    while (true) {
        cout << "Введите A: ";
        cin >> A;
        if (A < 0) {
            cout << "A должно быть >=0." << endl;
        }
        else {
            break;
        }
    }

    while (true) {
        cout << "Введите B: ";
        cin >> B;
        if (B < 0) {
            cout << "B должно быть >=0." << endl;
        }
        else {
            break;
        }
    }

    cout << "Введите C: ";
    cin >> C;
    cout << "Введите D: ";
    cin >> D;

    int rows = 2 + A;
    int cols = 2 + B;

    int** matrix = matrix1(A, B, C, D);

    int zeroCount = 0;
    int* zeroColumns = findZeroColumns(matrix, rows, cols, zeroCount);

    if (zeroCount > 0) {
        matrix = removeColumns(matrix, rows, cols, zeroColumns, zeroCount);
        free(zeroColumns);
    }

    printMatrix(matrix, rows, cols);

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}

/*
int main(){
    double a, b;
    cout << "A = ";
    cin >> a;
    cout << "B = ";
    cin >> b;

    double* A = new double(a);
    double* B = new double(b);

    *A *= 3;

    double vr = *A;
    *A = *B;
    *B = vr;

    cout << "Result: " << endl;
    cout << "A = " << *A << endl;
    cout << "B = " << *B << endl;

    delete A;
    delete B;

    return 0;
}
*/
