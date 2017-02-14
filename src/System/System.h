#pragma once

#include <string.h>

#define bool_t		char

#define VS_INLINE	inline

#define REPEAT( n ) for ( int i = 0; i < n; ++i )

#define DEF_OPERATORS( Class )									 \
	const Class& operator=( const Class& b ) {					 \
		memcpy_s( this, sizeof( Class ), &b, sizeof( Class ) );  \
		return *this;											 \
	};															 \
	bool operator==( const Class& b ) {							 \
		return memcmp( this, &b, sizeof( Class ) ) == 0;		 \
	};															 \
	bool operator!=( const Class& b ) {							 \
		return memcmp( this, &b, sizeof( Class ) ) != 0;		 \
	};															 


typedef char errval_t;