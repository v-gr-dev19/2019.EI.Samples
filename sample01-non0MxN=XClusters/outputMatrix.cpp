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
	assert( 0 < m[0].size() );
	cout << oName << "[" << m.size() << "," << m[0].size() << "] = {" << endl;
	for_each( m.begin(), m.end(), []( const std::array<size_t, N>& row ) {
		int count = 0;
		cout << " {";
		for_each( row.begin(), row.end(), [&count]( const size_t item ) {
			cout << ( count++ ? " " : " " );
			if( item ) {
				cout << item;
			} else {
				cout << ".";
			}
		} );
		cout << " }" << endl;
	} );
	cout << "}" << endl;
}

void outputVector( const vector<size_t>& v ) {
	auto on = "ev"; cout << on << "[" << v.size() << "] = {";
	int count = 0;
	for_each( v.begin(), v.end(), [&count]( const size_t item ) {
		cout << ( count++ ? "," : "" ) << item;
	} );
	cout << "}" << endl;
}
