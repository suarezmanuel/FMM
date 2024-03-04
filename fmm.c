#include "fmm.h"
//#include <immintrin.h>

// we define a vector of 8 ints, using SIMD
typedef int vec __attribute__ (( vector_size(32) ));

// a helper function that allocates n vectors and initializes them with zeros
vec* alloc(int n) {
    vec* ptr = (vec*) aligned_alloc(32, 32 * n);
    memset(ptr, 0, 32 * n);
    return ptr;
}

void fmm(int n, int* m1, int* m2, int* result) {

    int n2 = n/8;

    // create two vectors
    vec *a = alloc(n*n2);
    vec *b = alloc(n*n2);

//    // init result to 0
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            result[i*n+j] = 0;
//        }
//    }

    // first matrix into a
    // transpose second matrix into b
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // a and b are arrays of vectors of len 8
            a[i*n + j][j % 8] = m1[i*n + j];
            b[i*n + j][j % 8] = m2[j*n + i];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            vec st = {0,0,0,0,0,0,0,0};

            for (int k = 0; k < n2; ++k) {
                // we are summing and multiplying vectors of len 8
                st += a[i*n2+k] * b[j*n2+k];
            }

            for (int k = 0; k < 8; ++k) {
                // each slot in st holds the cross-product
                // of two n/8 long vectors
                result[i*n+j] += st[k];
            }
        }
    }
}

