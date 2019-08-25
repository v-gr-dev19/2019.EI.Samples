#include "pch.h"
#include <cassert>
#include <vector>
#include "sample01.h"
#include "matrix.h"
#include "debug.h"
using namespace std;
// Определяем 8-связные кластеры из единиц в матрице
// Параметры:
// 	m0 - исходная матрица с 0,1
// 	m1 - результирующая матрица с номерами кластеров вместо 1, кластеры нумеруем с 1
// 	eqVector - вектор эквивалентностей кластеров, eqVector[i-1] = k => k-й кластер эквивалентен i-му кластеру
//	numberOfClusters - возвращаем количество кластеров
void detectClustersInMatrix( const nonZeroMxNMatrix& m0, nonZeroMxNMatrix& m1, vector<size_t>& eqVector, size_t& numberOfClusters )
{
	assert( m0.size() == m1.size() );
	if( 0 < m0.size() ) {
		assert( m0[0].size() == m1[0].size() );
	}
	
	// для подсчета количества слияний
	size_t mergesCounter = 0;

	// проходим по каждому элементу матрицы
	for( size_t i = 0; i < m0.size(); i++ ) {
		for( size_t j = 0; j < m0[i].size(); j++ ) {
			// переносим нулевыей элементы во вспомогательную матрицу
			if( 0 == m0[i][j] ) {
				m1[i][j] = 0;
			} else {
			// ненулевой элемент матрицы
				size_t assignedCluster = 0; // номер кластера будет присвоен текущему элементу матрицы
				if( 0 < j && m0[i][j-1] && 0 == assignedCluster ) {
					// берем номер кластера слева
					assignedCluster = m1[i][j-1];
					m1[i][j] = assignedCluster;
				}
				if( 0 < i && m0[i-1][j] && 0 == assignedCluster ) {
					// берем номер кластера сверху
					assignedCluster = m1[i-1][j];
					m1[i][j] = assignedCluster;
				}
				if( 0 < i && 0 < j && m0[i-1][j-1] && 0 == assignedCluster ) {
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
						// слияние кластеров
						auto rightCluster = m1[i-1][j+1];
						if( assignedCluster != rightCluster ) {
							auto rightParentCluster = eqVector[m1[i-1][j+1] - 1];
							auto leftParentCluster = eqVector[assignedCluster - 1];
							decltype( assignedCluster ) pushedCluster = 0;
							decltype( assignedCluster ) poppedCluster = 0;
							if( leftParentCluster != rightParentCluster ) {
								if( leftParentCluster < rightParentCluster ) {
									pushedCluster = leftParentCluster;
									poppedCluster = rightCluster;
								} else {
									pushedCluster = rightParentCluster;
									poppedCluster = assignedCluster;
								}
								debug(( "trace 01 init" ));
								while( pushedCluster < poppedCluster ) {
									auto parentCluster = eqVector[poppedCluster - 1];
									if( parentCluster == poppedCluster ) {
										mergesCounter++; // подсчитываем присоединение уникального кластера
									}
									// присоединяем кластеры "больший к меньшему"
									eqVector[poppedCluster - 1] = pushedCluster;
									poppedCluster = parentCluster;
									debug(( "trace 01 tick" ));
								}
								debug(( "trace 01 check", i, j ));
								// debug(( i, j, eqVector ));
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
	numberOfClusters = eqVector.size() - mergesCounter;
}
