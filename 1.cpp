//
//  main.cpp
//  step1
//
//  Created by ljpc on 2018/11/29.
//  Copyright © 2018年 ljpc. All rights reserved.
//

#include <iostream>
#include <algorithm>

using namespace std;

int det(int n, int** mat)
{
    int mov = 0;
    int flag;
    int sum = 0;
    if (n == 1) return mat[0][0];
    int** b = new int* [n - 1];
    for (int z = 0; z < n - 1; ++z)
        b[z] = new int[n - 1];
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n - 1; ++j) {
            mov = i > j ? 0 : 1;
            for (int k = 0; k < n - 1; ++k)
                b[j][k] = mat[j + mov][k + 1];
        }
        if (i % 2 == 0) flag = 1;
        else flag = -1;
        sum += flag * mat[i][0] * det(n - 1, b);
    }
    delete[] b;
    return sum;
}

struct Matrix {
    int m, n;
    int** val;
    Matrix() {}
    Matrix(int m_, int n_) {
        m = m_;
        n = n_;
        this->val = (int**)malloc(sizeof(int*) * m);
        for (int i = 0; i < m; i++) {
            this->val[i] = (int*)malloc(sizeof(int) * n);
        }
    }
    void in() {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &this->val[i][j]);
            }
        }
    }
    void out() {
        for (int i = 0; i < m; i++) {
            printf("%d", this->val[i][0]);
            for (int j = 1; j < n; j++) {
                printf(" %d", this->val[i][j]);
            }
            printf("\n");
        }
    }
    int Determinant_1() {
        // 请在这里补充代码，完成本关任务
        /********* Begin *********/
        return val[0][0];
        /********* End *********/
    }
    int Determinant_2() {
        // 请在这里补充代码，完成本关任务
        /********* Begin *********/
        return (val[0][0] * val[1][1] - val[0][1] * val[1][0]);
        /********* End *********/
    }
    int Determinant_3() {
        // 请在这里补充代码，完成本关任务
        /********* Begin *********/
        int left = val[0][0] * val[1][1] * val[2][2] + val[0][1] * val[1][2] * val[2][0] + val[1][0] * val[2][1] * val[0][2];
        int right = val[2][0] * val[1][1] * val[0][2] + val[1][0] * val[0][1] * val[2][2] + val[2][1] * val[1][2] * val[0][0];
        return left - right;
        /********* End *********/
    }
    int Inverse_Number(int n, int arr[]) {
        // 请在这里补充代码，完成本关任务
        /********* Begin *********/
        int count = 0;
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (arr[i] > arr[j]) {
                    count++;
                    break;
                }
            }
        }
        return count;
        /********* End *********/
    }
    int Determinant_n() {
        // 请在这里补充代码，完成本关任务
        /********* Begin *********/
        int res = det(this->n, this->val);
        return res;
        /********* End *********/
    }

    int Determinant() {
        if (this->n == 1) {
            return Determinant_1();
        }
        else if (this->n == 2) {
            return Determinant_2();
        }
        else if (this->n == 3) {
            return Determinant_3();
        }
        else {
            return Determinant_n();
        }
    }

};

int main(int argc, const char* argv[]) {

    int n;
    scanf("%d", &n);
    Matrix A(n, n);
    A.in();

    int det = A.Determinant();
    printf("Det(A)=%d\n", det);

    return 0;
}


