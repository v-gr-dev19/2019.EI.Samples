#pragma once
#include <vector>
#ifdef _DEBUG
#define debug( a1 ) debugEx a1 
#else
#define debug( args ) {}
#endif
void debugEx( size_t i, size_t j, const std::vector<size_t>& v );
void debugEx( const char* key, ... );
