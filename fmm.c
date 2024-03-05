#include "fmm.h"

#define L1POWEROF2 17
#define L2POWEROF2 23
#define L3POWEROF2 27

// assuming b1 and b2 divide n
// b1 are rows in A, 'i' is first row of b1
// b2 are cols in B, 'j' is first col of b2
// the resulting block is C[i:i+b1][j:j+b2]

void help (int i, int b1, int j, int b2, int n) {
    // on A well use a block of width b2, and height b1. call it B1
    // on B well use a block of width b1, and height b2. call it B2

    // how many times each block fits in its own matrix
    int nr = n/b2;

    // make jumps of size nr
    for (int a = 0; a < nr; ++a) {
        // take row of B1 and multiply it with the columns of B2
        // loop through the rows of B1
        for (int r = 0; r < b1; ++r) {
            // loop through the columns of B2
            for (int c = 0; c < b1; ++c) {
                // multiply the given partial row and column
                // vectors of B1 and B2, and put result into C
                int t = 0;
                for (int k = 0; k < b2; ++k) {
//                    t += A[i+r][a*b2 + k] * B[a*b2 + k][j+b];
                    t += A[n*(i+r) + a*b2 + k] * B[n*(a*b2 + k) + j+c];
                }
                C[i+r][j+b] = t;
            }
        }
    }
    // note that we are mostly using B2 to calculate,
    // thus we want B2 to fit into L1, and B1 into L2.

    // and we won't need to transpose B,
    // because all the block's contents fit into the cache
}

// Slow fmm :slight_smile:
void fmm(int n, int* A, int* B, int* C) {

    // divide C into blocks that fit into L3
    // (that the rows of A and columns of B needed, fit into L3)
    //      if we want to calc block of size k*k in C
    //      that will cost 2*k*n space in L3

    // and we want to divide each row/col into
    // partial rows/cols blocks that fit into L2

    // each of those blocks into tiny calculation
    // blocks that fit into L1

    // obviously, if the caches are big enough well make less blocks
    // and maybe even fit the whole matrix into the caches


    int b3 = n*n / (1 << L3POWEROF2)
    b3 = (b3 == 0) ? 1 : b3;
    // the length of the block side in the matrix C
    int l3 = l2/b3;

    int b2 = l3*l3 / (1 << L2POWEROF2)
    b2 = (b2 == 0) ? 1 : b2;
    // the length of the block side in the matrix C
    int l2 = l3/b2;

    // how many times does the reg fit into the matrix ?
    int b1 = l2*l2 / (1 << L1POWEROF2)
    b1 = (b1 == 0) ? 1 : b1;
    // the length of the block side in the matrix C
    int l1 = l2/b1;


    // loop through the big L3 blocks on the final matrix
    for (int i = 0; i < b3; ++i) {
        for (int j = 0; j < b3; ++j) {
            help (i * l3, )
        }
    }
}