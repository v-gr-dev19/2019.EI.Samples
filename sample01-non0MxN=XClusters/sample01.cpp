// Дано: матрица из 0 и 1 размера M x N. Найти: количество X "географических" кластеров в матрице, состоящих только из 1,
//		 каждая из которых соседствует хотя бы с одной 1. Н-р случаи соседства:
//		 11 10 10 01
//		 00 10 01 10

#include "pch.h"
#include <iostream>
#include <cassert>
#include <vector>
#include "sample01.h"
using namespace std;
void generate01Matrix( nonZeroMxNMatrix& m, size_t fullness, size_t rows = M, size_t cols = N );
void outputMatrix( const nonZeroMxNMatrix& );
void outputVector( const vector<unsigned>& );
void detectClustersInMatrix( const nonZeroMxNMatrix& m, nonZeroMxNMatrix& m1, vector<unsigned>& e );
size_t getClustersCount( const vector<unsigned>& );

const double fullnessPercent = 20;
const auto fullness = static_cast<size_t>( double( M*N ) * fullnessPercent / 100 );

int main()
{	// генерируем исходную матрицу из 0 и 1
	auto* pm = new nonZeroMxNMatrix;
	assert( pm );
	generate01Matrix( *pm, fullness );
	const auto& m = *pm;
	
	// получаем вспомогательную матрицу и вектор эквивалентности кластеров
	auto* pm1 = new nonZeroMxNMatrix;
	assert( pm1 );
	auto& m1 = *pm1;

	// вектор эквивалентности кластеров
	vector<unsigned> ev;

	// находим кластеры
	detectClustersInMatrix( m, m1, ev );
	size_t clustersCount = getClustersCount( ev );

	// показываем вспомогательную матрицу и вектор эквивалентности
	outputMatrix( m1 );
	outputVector( ev );
	
	// Ответ:
	cout << "The number of clusters is " << clustersCount << endl;
	
	delete &m;
	delete &m1;
}