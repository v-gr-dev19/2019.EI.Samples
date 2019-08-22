#include "pch.h"
#include <cassert>
#include <vector>
#include "sample01.h"
#include "matrix.h"
using namespace std;

// Определяем 8-связные кластеры из единиц в матрице
// Параметры:
// 	m0 - исходная матрица с 0,1
// 	m1 - результирующая матрица с номерами кластеров вместо 1, кластеры нумеруем с 1
// 	eqVector - вектор эквивалентностей кластеров, eqVector[i-1] = k => k-й кластер эквивалентен i-му кластеру
void detectClustersInMatrix( const nonZeroMxNMatrix& m0, nonZeroMxNMatrix& m1, vector<size_t>& eqVector, size_t& numberOfClusters )
{
	assert( m0.size() == m1.size() );
	if( 0 < m0.size() ) {
		assert( m0[0].size() == m1[0].size() );
	}
	
	// для подсчета количества слияний
	size_t mergeCounter = 0;

	// проходим по каждому элементу матрицы
	for( size_t i = 0; i < m0.size(); i++ ) {
		for( size_t j = 0; j < m0[i].size(); j++ ) {
			// переносим нулевыей элементы во вспомогательную матрицу
			if( 0 == m0[i][j] ) {
				m1[i][j] = 0;
			} else {
			// ненулевой элемент матрицы
				size_t assignedCluster = 0; // номер кластера будет присвоен текущему элементу матрицы
				if( 0 < j && m0[i][j-1] && ( 0 == assignedCluster || eqVector[m1[i][j-1] - 1] < assignedCluster ) ) {
					// берем номер кластера слева
					assignedCluster = m1[i][j-1];
					m1[i][j] = assignedCluster;
				}
				if( 0 < i && m0[i-1][j] && ( 0 == assignedCluster || eqVector[m1[i-1][j] - 1] < assignedCluster ) ) {
					// берем номер кластера сверху
					assignedCluster = m1[i-1][j];
					m1[i][j] = assignedCluster;
				}
				if( 0 < i && 0 < j && m0[i-1][j-1] && ( 0 == assignedCluster || eqVector[m1[i-1][j-1] - 1] < assignedCluster ) ) {
					// берем номер кластера сверху-слева
					assignedCluster = m1[i-1][j-1];
					m1[i][j] = assignedCluster;
				}
				if( 0 < i && j+1 < m0[i].size() && m0[i-1][j+1] ) {
					if( 0 == assignedCluster ) {
						// берем номер кластера сверху-справа
						assignedCluster = m1[i-1][j+1];
						m1[i][j] = assignedCluster;
					} else {
						// отмечаем в векторе эквивалентностей факт слияния кластеров
						if( assignedCluster < m1[i-1][j+1] ) {
							if( m1[i-1][j+1] == eqVector[m1[i-1][j+1] - 1] ) {
								mergeCounter++; // подсчитываем присоединение уникального кластера
							}
							// присоединяем кластер "от большего к меньшему"
							eqVector[m1[i-1][j+1] - 1] = assignedCluster;
						} else {
							if( m1[i-1][j+1] < assignedCluster ) {
								if( assignedCluster == eqVector[assignedCluster - 1] ) {
									mergeCounter++; // подсчитываем присоединение уникального кластера
								}
								// присоединяем кластер "от большего к меньшему"
								eqVector[assignedCluster - 1] = m1[i-1][j+1];
							}
						}
					}
				}
				// в текущей позиции матрицы - новый уникальный кластер
				if( 0 == assignedCluster ) {
					assignedCluster = eqVector.size() + 1;
					eqVector.push_back( assignedCluster );
					m1[i][j] = assignedCluster;
				}
			}
		}
	}
	numberOfClusters = eqVector.size() - mergeCounter;
}
