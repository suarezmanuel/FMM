#include "fmm.h"

// Slow fmm :)
void fmm(int n, int* m1, int* m2, int* result) {

    int *_m2 = (int*) malloc (n*n*sizeof(int));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i*n+j] = 0;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            _m2[i*n+j] = m2[j*n+i];
        }
    }
//
//    int *a = (int*) malloc (8*sizeof(int));
//    int *b = (int*) malloc (8*sizeof(int));

//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            for (int k = 0; k < n; k++) {
//                result[i * n + j] += m1[i * n + k] * _m2[j * n + k];
//            }
//        }
//    }

    int t = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k+=8) {
                t += m1[i * n + k] * _m2[j * n + k];
                t += m1[i * n + k+1] * _m2[j * n + k+1];
                t += m1[i * n + k+2] * _m2[j * n + k+2];
                t += m1[i * n + k+3] * _m2[j * n + k+3];
                t += m1[i * n + k+4] * _m2[j * n + k+4];
                t += m1[i * n + k+5] * _m2[j * n + k+5];
                t += m1[i * n + k+6] * _m2[j * n + k+6];
                t += m1[i * n + k+7] * _m2[j * n + k+7];
            }
            result[i * n + j] = t;
            t=0;
        }
    }
}

