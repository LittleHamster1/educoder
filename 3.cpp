//
//  main.cpp
//  step3
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
            printf("%.4lf", this->val[i][0] + eps);
            for (int j = 1; j < n; j++) {
                printf(" %.4lf", this->val[i][j] + eps);
            }
            printf("\n");
        }
    }

    Matrix Elementary_Row_Transformation() {

        Matrix R = Matrix(this->n, this->n * 2);
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->n; j++)
                R.val[i][j] = this->val[i][j];
            for (int j = this->n; j < this->n * 2; j++)
                R.val[i][j] = ((j - this->n) == i) ? 1 : 0;
        }
        // 请在这里补充代码，完成本关任务
        /********* Begin *********/
        for (int i = 0; i < R.m; i++) {
            double flag = R.val[i][i];
            for (int j = i; j < R.n; j++) {
                R.val[i][j] /= flag;
            }
            for (int k = i + 1; k < R.m; k++) {
                flag = R.val[k][i];
                for (int j = i; j < R.n; j++) {
                    R.val[k][j] -= flag * R.val[i][j];
                }
            }
        }

        for (int i = R.m - 1; i >= 0; i--) {
            double flag = R.val[i][i];
            for (int j = i; j < R.n; j++) {
                R.val[i][j] /= flag;
            }
            for (int k = i - 1; k >= 0; k--) {
                flag = R.val[k][i];
                for (int j = k; j < R.n; j++) {
                    R.val[k][j] -= flag * R.val[i][j];
                }
            }
        }

        /********* End *********/

        return R;
    }

    Matrix Elementary_Col_Transformation() {

        Matrix C = Matrix(this->n * 2, this->n);
        for (int j = 0; j < this->n; j++) {
            for (int i = 0; i < this->n; i++)
                C.val[i][j] = this->val[i][j];
            for (int i = this->n; i < this->n * 2; i++)
                C.val[i][j] = ((i - this->n) == j) ? 1 : 0;
        }
        // 请在这里补充代码，完成本关任务
        /********* Begin *********/
        for (int j = 0; j < C.n; j++) {
            double flag = C.val[j][j];
            for (int i = j; i < C.m; i++) {
                C.val[i][j] /= flag;
            }
            for (int k = j + 1; k < C.n; k++) {
                flag = C.val[j][k];
                for (int i = j; i < C.m; i++) {
                    C.val[i][k] -= flag * C.val[i][j];
                }
            }
        }

        for (int j = C.n - 1; j >= 0; j--) {
            double flag = C.val[j][j];
            for (int i = j; i < C.m; i++) {
                C.val[i][j] /= flag;
            }
            for (int k = j - 1; k >= 0; k--) {
                double flag = C.val[j][k];
                for (int i = j; i < C.m; i++) {
                    C.val[i][k] -= flag * C.val[i][j];
                }
            }
        }

        /********* End *********/

        return C;
    }
};

int main(int argc, const char* argv[]) {

    int n;
    scanf("%d", &n);
    Matrix A(n, n);
    A.in();

    Matrix R = Matrix(n, n * 2);
    R = A.Elementary_Row_Transformation();
    R.out();
    printf("\n");

    Matrix C = Matrix(n * 2, n);
    C = A.Elementary_Col_Transformation();
    C.out();
    printf("\n");

    return 0;
}


