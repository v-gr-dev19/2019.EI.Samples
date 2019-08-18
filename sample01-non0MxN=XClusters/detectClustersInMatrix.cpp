#include "pch.h"
#include <cassert>
#include <vector>
#include "sample01.h"
#include "matrix.h"
using namespace std;

void detectClustersInMatrix( const nonZeroMxNMatrix& m, nonZeroMxNMatrix& m1, vector<unsigned>& ev ) {
	assert( m.size() == m1.size() );
	if ( 0 < m.size() ) {
		assert( m[0].size() == m1[0].size() );
	}
	
	for ( size_t i = 0; i < m.size(); i++ ) {
		for ( size_t j = 0; j < m[i].size(); j++ ) {
			if ( 0 == m[i][j] ) {
				m1[i][j] = 0;
			} else {
				size_t assignedCluster = 0;
				if ( 0 < i && m[i-1][j] ) {
					assignedCluster = m1[i-1][j];
					m1[i][j] = assignedCluster;
				}
				if ( 0 < j && m[i][j-1] && 0 == assignedCluster ) {
					assignedCluster = m1[i][j-1];
					m1[i][j] = assignedCluster;
				}
				if ( 0 < i && 0 < j && m[i-1][j-1] && 0 == assignedCluster ) {
					assignedCluster = m1[i-1][j-1];
					m1[i][j] = assignedCluster;
				}
				if ( 0 < i && j+1 < m[i].size() && m[i-1][j+1] ) {
					if ( 0 == assignedCluster ) {
						assignedCluster = m1[i-1][j+1];
						m1[i][j] = assignedCluster;
					} else {
						if( assignedCluster < m1[i-1][j+1] ) {
							ev[m1[i-1][j+1]-1] = assignedCluster;
						}
						else {
							if ( m1[i-1][j+1] < assignedCluster ) {
								ev[assignedCluster-1] = m1[i-1][j+1];
							}
						}
						
					}
				}
				if ( 0 == assignedCluster ) {
					assignedCluster = ev.size() + 1;
					ev.push_back( assignedCluster );
					m1[i][j] = assignedCluster;
				}
			}
		}
	}
}

size_t getClustersCount( const vector<unsigned>& ev ) {
	size_t clustersCount = 0;
	for ( size_t i = 0; i < ev.size(); i++ ) {
		if( i+1 == ev[i] ) {
			clustersCount++;
		}
	}
	return clustersCount;
}
