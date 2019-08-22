#include "pch.h"
#include <vector>
#include "sample01.h"
#include "matrix.h"
using namespace std;

void normalizeClustersInMatrix( nonZeroMxNMatrix& m1, vector<size_t>& ev )
{
	// TODO: хотим привести к нормализованному виду за O(MxN)
	// Пока это не умеем, для целей демонстрации работы основного алгоритма делаем O(AS-IS)

	// вектор эквивалентностей приводим к виду: для одного кластера - единый номер
	bool wasChangesFlag = false;
	do {
		wasChangesFlag = false;
		for( size_t i = 0; i < ev.size(); i++ ) {
			if( ev[ev[ev[i] - 1] - 1] < ev[ev[i] - 1] ) {
				ev[ev[i] - 1] = ev[ev[ev[i] - 1] - 1];
				wasChangesFlag = true;
			}
		}
	} while ( wasChangesFlag );

	// вспомогательный вектор для нормализации вектора эквивалентностей
	vector<size_t> ev1( ev.size(), 0 );

	size_t uniqCounter = 0; // для подсчета уникальных отдельных кластеров
	for( size_t i = 0; i < ev.size(); i++ ) {
		if( 0 == ev1[ev[i] - 1] ) {
			ev1[ev[i] - 1] = ++uniqCounter;
		}
		else {
			ev1[i] = ev1[ev[i] - 1];
		}
	}

	// вектор эквивалентностей нормализован
	ev = ev1;
	// приведем вспомогательную матрицу в соответствие с обновленным вектором эквивалентностей
	for( size_t i = 0; i < m1.size(); i++ ) {
		for( size_t j = 0; j < m1[i].size(); j++ ) {
			if( m1[i][j] ) {
				m1[i][j] = ev[m1[i][j] - 1];
			}
		}
	}
}
