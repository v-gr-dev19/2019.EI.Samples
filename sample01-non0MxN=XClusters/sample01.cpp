// Дано: матрица из 0 и 1 размера M x N.
// Найти: количество X "географических" кластеров в матрице, состоящих только из 1,
//		 каждая из которых соседствует хотя бы с одной 1 из 8-ми. Примеры соседства:
//		 000	 | 	010	 | 	100	 | 	001
//		 110	 | 	010	 | 	010	 | 	010
//		 000	 | 	000	 | 	000	 | 	000
// Время и память - O(MxN).

#include "pch.h"
#include <iostream>
#include <cassert>
#include <vector>
#include "sample01.h"
using namespace std;

const auto fullness = static_cast<size_t>( double( M*N ) * fullnessPercent / 100 );

int main()
{	// генерируем исходную матрицу из 0 и 1
	auto* pm0 = new nonZeroMxNMatrix;
	assert( pm0 );
	generate01Matrix( *pm0, fullness );
	// отладка на специальном примере
	// set01Matrix( *pm0 );
	const auto& m0 = *pm0;
	
	// вспомогательная матрица
	auto* pm1 = new nonZeroMxNMatrix;
	assert( pm1 );
	auto& m1 = *pm1;

	// вектор эквивалентностей кластеров
	vector<size_t> ev;

	// находим кластеры
	size_t clustersCount = 0;
	detectClustersInMatrix( m0, m1, ev, clustersCount );
		
	// показываем вспомогательную матрицу и вектор эквивалентностей
	outputMatrix( m1 );
	demoVector( ev );
	
	// нормализуем вектор эквивалентности и вспомогательную матрицу
	normalizeClustersInMatrix( m1, ev ); 
	demoVector( ev );
	demoMatrix( m1 );
	

	// Ответ:
	cout << "The number of clusters is " << clustersCount << endl;
	
	delete &m0;
	delete &m1;
}