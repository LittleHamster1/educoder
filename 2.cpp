//
//  main.cpp
//  step2
//
//  Created by ljpc on 2018/11/29.
//  Copyright © 2018年 ljpc. All rights reserved.
//

#include <iostream>
#include <algorithm>

using namespace std;

#define eps 1e-8
inline int sig(double x) { return (x > eps) - (x < -eps); }

struct Matrix {
    int m, n;
    double** val;
    Matrix() {}
    Matrix(int m_, int n_) {
        m = m_;
        n = n_;
        this->val = (double**)malloc(sizeof(double*) * m);
        for (int i = 0; i < m; i++) {
            this->val[i] = (double*)malloc(sizeof(double) * n);
        }
    }
    void in() {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%lf", &this->val[i][j]);
            }
        }
    }
    void out() {
        for (int i = 0; i < m; i++) {
            printf("%.4lf", this->val[i][0]);
            for (int j = 1; j < n; j++) {
                printf(" %.4lf", this->val[i][j]);
            }
            printf("\n");
        }
    }
    Matrix operator * (const double r)const {
        int m_ = this->m;
        int n_ = this->n;
        Matrix A = *this;
        Matrix M(m_, n_);
        for (int i = 0; i < m_; i++) {
            for (int j = 0; j < n_; j++) {
                M.val[i][j] = A.val[i][j] * r;
            }
        }
        return M;
    }
    Matrix operator * (const Matrix B)const {
        Matrix A = *this;
        Matrix M(A.m, B.n);
        if (A.n != B.m) {
            printf("error\n");
        }
        for (int i = 0; i < A.m; i++) {
            for (int j = 0; j < B.n; j++) {
                double sum = 0;
                for (int k = 0; k < A.n; k++) {
                    sum += A.val[i][k] * B.val[k][j];
                }
                M.val[i][j] = sum;
            }
        }
        return M;
    }
    int Inverse_Number(int n, int arr[]) {
        int num = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (arr[j] > arr[i]) {
                    num++;
                }
            }
        }
        return num;
    }
    double Determinant() {
        Matrix D = *this;
        double det = 0;
        int* arr;
        arr = (int*)malloc(sizeof(int) * D.n);
        for (int i = 0; i < D.n; i++) {
            arr[i] = i;
        }
        do {
            int inv = Inverse_Number(D.n, arr);
            double tmp = (inv % 2 == 0) ? 1 : -1;
            for (int i = 0; i < D.n; i++) {
                tmp *= D.val[i][arr[i]];
            }
            det += tmp;
        } while (next_permutation(arr, arr + D.n));
        return det;
    }


    double Cofactor(int x, int y) {
        // 请在这里补充代码，完成本关任务
        /********* Begin *********/
        Matrix C = Matrix(this->n - 1, this->n - 1);
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                C.val[i][j] = this->val[i][j];
            }
        }
        for (int i = 0; i < x; i++) {
            for (int j = y + 1; j < this->n; j++) {
                C.val[i][j - 1] = this->val[i][j];
            }
        }
        for (int i = x + 1; i < this->n; i++) {
            for (int j = 0; j < y; j++) {
                C.val[i - 1][j] = this->val[i][j];
            }
        }
        for (int i = x + 1; i < this->n; i++) {
            for (int j = y + 1; j < this->n; j++) {
                C.val[i - 1][j - 1] = this->val[i][j];
            }
        }
        double det_c = C.Determinant();
        return det_c;
        /********* End *********/
    }

    Matrix Adjugate_Matrix() {
        // 请在这里补充代码，完成本关任务
        /********* Begin *********/
        Matrix A = Matrix(this->n, this->n);
        for (int i = 0; i < A.n; i++) {
            for (int j = 0; j < A.n; j++) {
                int flag = ((i + j) % 2 == 0) ? 1 : -1;
                int M_ij = Cofactor(i, j);
                A.val[j][i] = flag * M_ij;
            }
        }
        return A;
        /********* End *********/
    }

    Matrix Inverse_Matrix() {
        // 请在这里补充代码，完成本关任务
        /********* Begin *********/
        double det = Determinant();
        if (det == 0) {
            printf("error\n");
            return Matrix();
        }
        Matrix I = Matrix(this->n, this->n);
        Matrix A = Matrix(this->n, this->n);
        A = Adjugate_Matrix();
        I = A * (1. / det);
        return I;
        /********* End *********/
    }

    bool Identity_Matrix() {
        // 请在这里补充代码，完成本关任务
        /********* Begin *********/
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->n; j++) {
                if (i == j) {
                    if (sig(this->val[i][j] - 1) != 0) {
                        return false;
                    }
                }
                else {
                    if (sig(this->val[i][j] - 0) != 0) {
                        return false;
                    }
                }
            }
        }
        return true;
        /********* End *********/
    }

};

int main(int argc, const char* argv[]) {

    int n;
    scanf("%d", &n);
    Matrix A(n, n);
    A.in();

    Matrix I(n, n);
    I = A.Inverse_Matrix();
    I.out();

    Matrix E1(n, n);
    Matrix E2(n, n);
    E1 = A * I;
    E2 = I * A;
    if (E1.Identity_Matrix() == false) {
        printf("A*I error\n");
        E1.out();
    }
    if (E2.Identity_Matrix() == false) {
        printf("I*A error\n");
        E2.out();
    }

    return 0;
}


