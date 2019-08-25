#include "pch.h"
#include <iostream>
#include <vector>
#include <stdarg.h>

#include "sample01.h"
using namespace std;

void debugEx( size_t i, size_t j, const vector<size_t>& v )
{
	cout << i << "," << j << " ";
	outputVector( v );
}

void debugEx( const char* key, ... )
{
	static unsigned long traceCounter = 0;
	static unsigned long deepCounter = 0;
	static unsigned long deepCounterMax = 0;
	static size_t deepCounterMaxRow = 0;
	static size_t deepCounterMaxCol = 0;
	string sKey = key;
	if( false ) {
	} else if( sKey == "trace 01 init" ) {
		deepCounter = 0;
	} else if( sKey == "trace 01 tick" ) {
		traceCounter++;
		deepCounter++;
	} else if( sKey == "trace 01 check" ) {
		if( deepCounterMax < deepCounter ) {
			deepCounterMax = deepCounter;
			va_list ap;
			va_start( ap, key );
			deepCounterMaxRow = va_arg( ap, size_t );
			deepCounterMaxCol = va_arg( ap, size_t );
			va_end( ap );
		}
	} else if( sKey == "trace output" ) {
		cout << "traceCounter = " << traceCounter << endl;
		cout << deepCounterMaxRow << "," << deepCounterMaxCol << " deepCounterMax = " << deepCounterMax << endl;
	}
}
