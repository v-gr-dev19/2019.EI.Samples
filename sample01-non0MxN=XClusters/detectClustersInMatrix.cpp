#include "pch.h"
#include <cassert>
#include <vector>
#include "sample01.h"
#include "matrix.h"
using namespace std;

// ���������� 8-������� �������� �� ������ � �������
// ���������:
// 	m0 - �������� ������� � 0,1
// 	m1 - �������������� ������� � �������� ��������� ������ 1, �������� �������� � 1
// 	eqVector - ������ ���������������� ���������, eqVector[i-1] = k => k-� ������� ������������ i-�� ��������
void detectClustersInMatrix( const nonZeroMxNMatrix& m0, nonZeroMxNMatrix& m1, vector<size_t>& eqVector, size_t& numberOfClusters ) {
	assert( m0.size() == m1.size() );
	if( 0 < m0.size() ) {
		assert( m0[0].size() == m1[0].size() );
	}
	
	// ��� �������� ���������� �������
	size_t mergeCounter = 0;

	// �������� �� ������� �������� �������
	for( size_t i = 0; i < m0.size(); i++ ) {
		for( size_t j = 0; j < m0[i].size(); j++ ) {
			// ��������� �������� �������� �� ��������������� �������
			if( 0 == m0[i][j] ) {
				m1[i][j] = 0;
			} else {
			// ��������� ������� �������
				size_t assignedCluster = 0; // ����� �������� ����� �������� �������� �������� �������
				if( 0 < j && m0[i][j-1] && ( 0 == assignedCluster || eqVector[m1[i][j-1] - 1] < assignedCluster ) ) {
					// ����� ����� �������� �����
					assignedCluster = m1[i][j-1];
					m1[i][j] = assignedCluster;
				}
				if( 0 < i && m0[i-1][j] && ( 0 == assignedCluster || eqVector[m1[i-1][j] - 1] < assignedCluster ) ) {
					// ����� ����� �������� ������
					assignedCluster = m1[i-1][j];
					m1[i][j] = assignedCluster;
				}
				if( 0 < i && 0 < j && m0[i-1][j-1] && ( 0 == assignedCluster || eqVector[m1[i-1][j-1] - 1] < assignedCluster ) ) {
					// ����� ����� �������� ������-�����
					assignedCluster = m1[i-1][j-1];
					m1[i][j] = assignedCluster;
				}
				if( 0 < i && j+1 < m0[i].size() && m0[i-1][j+1] ) {
					if( 0 == assignedCluster ) {
						// ����� ����� �������� ������-������
						assignedCluster = m1[i-1][j+1];
						m1[i][j] = assignedCluster;
					} else {
						// �������� � ������� ���������������� ���� ������� ���������
						if( assignedCluster < m1[i-1][j+1] ) {
							if( m1[i-1][j+1] == eqVector[m1[i-1][j+1] - 1] ) {
								mergeCounter++; // ������������ ������������� ����������� ��������
							}
							// ������������ ������� "�� �������� � ��������"
							eqVector[m1[i-1][j+1] - 1] = assignedCluster;
						} else {
							if( m1[i-1][j+1] < assignedCluster ) {
								if( assignedCluster == eqVector[assignedCluster - 1] ) {
									mergeCounter++; // ������������ ������������� ����������� ��������
								}
								// ������������ ������� "�� �������� � ��������"
								eqVector[assignedCluster - 1] = m1[i-1][j+1];
							}
						}
					}
				}
				// � ������� ������� ������� - ����� ���������� �������
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
