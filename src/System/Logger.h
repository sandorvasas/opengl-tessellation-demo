#ifndef __VS_LOGGER_H__
#define __VS_LOGGER_H__

#include <Windows.h>
#include <stdio.h>
#include "System.h"

typedef enum {
		MSG_LOG = 0,
		MSG_ERROR,
		MSG_NOTIFY
} msgType_t;

namespace vsLogger {
	
	VS_INLINE
	void			Init( void ) {
		FILE * f;
		fopen_s( &f, "log.txt", "w+" );
		fclose( f );
	}

	VS_INLINE  
	void			Log( msgType_t t, char* format, ... ) {
		FILE * f;
		char text[ 2048 ];
		va_list L;

		fopen_s( &f, "log.txt", "a+" );

		va_start( L, format );
			vsprintf_s( text, format, L );
		va_end( L );

		fprintf( f, "%s\n", text );

		fclose( f );
	}

	VS_INLINE  
	void			Log( char* format, ... ) {
		FILE * f;
		char text[ 2048 ];
		va_list L;

		fopen_s( &f, "log.txt", "a+" );

		va_start( L, format );
			vsprintf_s( text, format, L );
		va_end( L );

		fprintf( f, "%s\n", text );

		fclose( f );
	}
};

#endif