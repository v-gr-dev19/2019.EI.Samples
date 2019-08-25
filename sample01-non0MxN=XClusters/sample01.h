#pragma once
#include <vector>
#include "matrix.h"

const size_t M = 50;
const size_t N = 20;

const double fullnessPercent = 50;

typedef Matrix<size_t, M, N> nonZeroMxNMatrix;

void generate01Matrix( nonZeroMxNMatrix& m, size_t fullness, size_t rows = M, size_t cols = N );
void set01Matrix( nonZeroMxNMatrix& m, size_t rows = M, size_t cols = N );
void outputMatrix( const nonZeroMxNMatrix& );
void demoMatrix( const nonZeroMxNMatrix& );
void demoVector( const std::vector<size_t>& );
void detectClustersInMatrix( const nonZeroMxNMatrix& m0, nonZeroMxNMatrix& m1, std::vector<size_t>& eqVector, size_t& mergeCounter );
void normalizeClustersInMatrix( nonZeroMxNMatrix& m1, std::vector<size_t>& ev );
