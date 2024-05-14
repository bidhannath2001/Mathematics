#include<bits/stdc++.h>
#include <iostream>
#include <cmath>
#define MAX_SIZE 20
using namespace std;

float determinant(float matrix[MAX_SIZE][MAX_SIZE], int n);
void transpose(float matrix[MAX_SIZE][MAX_SIZE], float factor[MAX_SIZE][MAX_SIZE], int n);
void cofactor(float matrix[MAX_SIZE][MAX_SIZE], int n);

int main() {
    int n;
    cout << "Enter the dimension of the square matrix: ";
    cin >> n;

    if (n <= 0 || n > MAX_SIZE) {
        cout << "Invalid matrix size." << endl;
        return 1;
    }

    float matrix[MAX_SIZE][MAX_SIZE];
    cout << "Enter the elements of the matrix: \n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }

    float d = determinant(matrix, n);
    cout << "\nDeterminant: " << d<<"\n\n";
    
    if (d == 0) {
        cout << "Inverse matrix not possible\n";
    } 
    else {
        cofactor(matrix, n);
    }

    return 0;
}

float determinant(float matrix[MAX_SIZE][MAX_SIZE], int n) {
    float det = 0, s = 1;
    float temp[MAX_SIZE][MAX_SIZE];

    if (n == 1) {
        return matrix[0][0];
    } 
    else if (n == 2) {
        return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
    } 
    else {
        for (int col = 0; col < n; col++) {
            int x = 0, y = 0;
            for (int i = 1; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (j != col) {
                        temp[x][y] = matrix[i][j];
                        y++;
                        if (y == n - 1) {
                            x++;
                            y = 0;
                        }
                    }
                }
            }
            det += s * matrix[0][col] * determinant(temp, n - 1);
            s = -s;
        }
    }
    return det;
}

void cofactor(float matrix[MAX_SIZE][MAX_SIZE], int n) {
    float factor[MAX_SIZE][MAX_SIZE], temp[MAX_SIZE][MAX_SIZE];
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            int x = 0, y = 0;
            for (int i = 0; i < n; i++) {
                if (i != row) {
                    for (int j = 0; j < n; j++) {
                        if (j != col) {
                            temp[x][y++] = matrix[i][j];
                            if (y == n - 1) {
                                x++;
                                y = 0;
                            }
                        }
                    }
                }
            }
            factor[row][col] = pow(-1, row + col) * determinant(temp, n - 1);
        }
    }
    transpose(matrix, factor, n);
}


void transpose(float matrix[MAX_SIZE][MAX_SIZE], float factor[MAX_SIZE][MAX_SIZE], int n) {
    float inverse[MAX_SIZE][MAX_SIZE];
    float det = determinant(matrix, n);

    if (det == 0) {
        cout << "Inverse matrix not possible\n";
        return;
    }
    //transpose
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            inverse[i][j] = factor[j][i];
        }
    }

    cout<<"Adjoint matrix:\n\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<< setw(5) << right<< inverse[i][j]<<"\t";
        }
        cout<<endl;
    }

    cout << "\nInverse matrix:\n\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            float ans = inverse[i][j]/det;
            if(ans==-0) ans=0;
            cout << setw(10) <<right<< fixed<<setprecision(1)<<ans;
        }
        cout << endl;
    }
}
