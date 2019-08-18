// Дано: матрица из 0 и 1 размера M x N. Найти: количество X "географических" кластеров в матрице, состоящих только из 1,
//		 каждая из которых соседствует хотя бы с одной 1. Н-р случаи соседства:
//		 11 10 10 01
//		 00 10 01 10

#include "pch.h"
#include <iostream>
#include <cassert>
#include "sample01.h"
using namespace std;
void generate01Matrix( nonZeroMxNMatrix &m, size_t fullness, size_t rows = M, size_t cols = N );

void outputMatrix(const nonZeroMxNMatrix& m) {
	auto oName = "matrix";
	assert( 0 < m.size() );
	cout << oName << "[" << m.size() << "," << m[0].size() << "]={" << endl;
	for_each( m.begin(), m.end(), [](const std::array<unsigned, N>& row) {
		int count = 0;
		for_each( row.begin(), row.end(), [&count](const unsigned item ) {
			cout << ( count++ ? " " : "{ " ) << item;
		});
		cout << " }" << endl;
	});
	cout << "}" << endl;
}
const double fullnessPercent = 20;
const auto fullness = static_cast<size_t>( double( M*N ) * fullnessPercent / 100 );

int main()
{
	auto* pm = new nonZeroMxNMatrix;
	assert( pm );
	auto& m = *pm;
    generate01Matrix( m, fullness );
	outputMatrix( m );
}