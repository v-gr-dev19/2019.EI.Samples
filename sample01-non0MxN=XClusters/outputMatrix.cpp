#include "pch.h"
#include <iostream>
#include <cassert>
#include <vector>
#include "sample01.h"
#include "matrix.h"
using namespace std;

void outputMatrix( const nonZeroMxNMatrix& m ) {
	auto oName = "matrix";
	assert( 0 < m.size() );
	cout << oName << "[" << m.size() << "," << m[0].size() << "]={" << endl;
	for_each( m.begin(), m.end(), [](const std::array<unsigned, N>& row ) {
		int count = 0;
		for_each( row.begin(), row.end(), [&count]( const unsigned item ) {
			cout << ( count++ ? " " : "{ " ) << item;
		} );
		cout << " }" << endl;
	} );
	cout << "}" << endl;
}

void outputVector( const vector<unsigned>& v ) {
	auto on = "ev"; cout << on << "[" << v.size() << "]={";
	int count = 0;
	for_each( v.begin(), v.end(), [&count]( const int item ) {
		cout << ( count++ ? "," : "") << item;
	} );
	cout << "}" << endl;
}
