#include "pch.h"
#include "matrix.h"
#include "sample01.h"
#include <random>
#include <ctime>

using namespace std;
void generate01Matrix( nonZeroMxNMatrix &m, size_t fullness, size_t rows = M, size_t cols = N )
{
	for( size_t i = 0; i < rows; i++ )
		for( size_t j = 0; j < cols; j++ )
			m[i][j] = 0;
	size_t countOf1 = 0;
	
	default_random_engine generator;
	uniform_int_distribution<size_t> distribution(0, rows*cols - 1);
	generator.seed( time( 0 ) );
	generator();

	while( countOf1 < fullness && countOf1 < rows*cols ) {
		size_t next = distribution( generator );
		size_t i = next / cols;
		size_t j = next % cols;
		if( 0 == m[i][j] ) {
			m[i][j] = 1;
			countOf1++;
		}
	}
}
