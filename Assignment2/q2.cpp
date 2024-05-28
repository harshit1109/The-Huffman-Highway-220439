#include <iostream>
#include <vector>
using namespace std;

class Matrix {
private:
    vector<vector<double>> data;
    int rows, cols;

public:
    // Constructor to initialize the matrix with given dimensions
    Matrix(int m, int n) : rows(m), cols(n) {
        data.resize(m, vector<double>(n, 0));
    }

    // Function to input matrix values from the user
    void input() {
        cout << "Enter the values for a " << rows << "x" << cols << " matrix:" << endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cin >> data[i][j];
            }
        }
    }

    // Function to print the matrix
    void print() const {
        cout << "Matrix (" << rows << "x" << cols << "):" << endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Operator overloading for matrix multiplication
    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw invalid_argument("Matrix dimensions do not match for multiplication.");
        }

        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                for (int k = 0; k < cols; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }

        return result;
    }
};

int main() {
    int m, n;
    cout << "Enter dimensions for the first matrix (m n): ";
    cin >> m >> n;

    Matrix matA(m, n);
    matA.input();

    Matrix matB(n, m);
    matB.input();

    Matrix matC(m, m);
    matC = matA * matB;

    matA.print();
    matB.print();
    matC.print();

    return 0;
}
