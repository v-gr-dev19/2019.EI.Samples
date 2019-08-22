#include "pch.h"
#include <vector>
#include "sample01.h"
#include "matrix.h"
using namespace std;

void normalizeClustersInMatrix( nonZeroMxNMatrix& m1, vector<size_t>& ev )
{
	// TODO: ����� �������� � ���������������� ���� �� O(MxN)
	// ���� ��� �� �����, ��� ����� ������������ ������ ��������� ��������� ������ O(AS-IS)

	// ������ ���������������� �������� � ����: ��� ������ �������� - ������ �����
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

	// ��������������� ������ ��� ������������ ������� ����������������
	vector<size_t> ev1( ev.size(), 0 );

	size_t uniqCounter = 0; // ��� �������� ���������� ��������� ���������
	for( size_t i = 0; i < ev.size(); i++ ) {
		if( 0 == ev1[ev[i] - 1] ) {
			ev1[ev[i] - 1] = ++uniqCounter;
		}
		else {
			ev1[i] = ev1[ev[i] - 1];
		}
	}

	// ������ ���������������� ������������
	ev = ev1;
	// �������� ��������������� ������� � ������������ � ����������� �������� ����������������
	for( size_t i = 0; i < m1.size(); i++ ) {
		for( size_t j = 0; j < m1[i].size(); j++ ) {
			if( m1[i][j] ) {
				m1[i][j] = ev[m1[i][j] - 1];
			}
		}
	}
}
