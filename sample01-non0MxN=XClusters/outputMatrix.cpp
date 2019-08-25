#include "pch.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include "sample01.h"
#include "matrix.h"
#include <windows.h>

WORD defaultColors = 0;
inline std::ostream& colorsOFF( std::ostream &s )
{
	HANDLE hStdout = GetStdHandle( STD_OUTPUT_HANDLE );
	if( !defaultColors ) {
		CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
		GetConsoleScreenBufferInfo( hStdout, &csbiInfo );
		defaultColors = csbiInfo.wAttributes;
	}
	SetConsoleTextAttribute( hStdout, defaultColors );
	return s;
}
inline std::ostream& colorsON( std::ostream &s )
{
	HANDLE hStdout = GetStdHandle( STD_OUTPUT_HANDLE );
	if( !defaultColors ) {
		CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
		GetConsoleScreenBufferInfo( hStdout, &csbiInfo );
		defaultColors = csbiInfo.wAttributes;
	}
	SetConsoleTextAttribute( hStdout, BACKGROUND_BLUE
		| BACKGROUND_GREEN | BACKGROUND_INTENSITY );
	return s;
}
using namespace std;

void demoMatrix( const nonZeroMxNMatrix& m )
{	
	const char* itemsSeparator = "";
	const char* zeroItem = "";
	const int itemWith = 2;
	const char fill = ' ';
	auto oName = "matrix";
	assert( 0 < m.size() );
	assert( 0 < m[0].size() );
	cout << oName << "[" << m.size() << "," << m[0].size() << "] = {" << endl;
	for_each( m.begin(), m.end(), [=]( const std::array<size_t, N>& row ) {
		int count = 0;
		cout << " {";
		for_each( row.begin(), row.end(), [=, &count]( const size_t item ) {
			cout << ( count++ ? itemsSeparator : " " );
			if( item ) {
				cout << setfill( fill ) << setw( itemWith ) << colorsON << item << colorsOFF;
			} else {
				cout << setfill( fill ) << setw( itemWith ) << zeroItem;
			}
		} );
		cout << " }" << endl;
	} );
	cout << "}" << endl;
}

void outputMatrix( const nonZeroMxNMatrix& m )
{
	const char* itemsSeparator = ";";
	for_each( m.begin(), m.end(), [=]( const std::array<size_t, N>& row )
	{
		int count = 0;
		for_each( row.begin(), row.end(), [=, &count]( const size_t item )
		{
			cout << ( count++ ? itemsSeparator : "" ) << item;
		} );
		cout << endl;
	} );
}

void demoVector( const vector<size_t>& v )
{
	auto on = "ev"; cout << on << "[" << v.size() << "] = {";
	int count = 0;
	for_each( v.begin(), v.end(), [&count]( const size_t item ) {
		cout << ( count++ ? "," : "" ) << item;
	} );
	cout << "}" << endl;
}
