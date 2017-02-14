#include <stdio.h>
#include "OpenGL\GLexp.h"
#include "Shader.h"
#include "..\System\Logger.h"

// ------------------------------------------------
//	vsShader
// ------------------------------------------------
vsShader::vsShader( void ) {
	vsEntity::vsEntity();
	Handle = 0;
}

// ------------------------------------------------
//	~vsShader
// ------------------------------------------------
vsShader::~vsShader( void ) {
	glDeleteProgram( Handle );
}

// ------------------------------------------------
//	operator=
// ------------------------------------------------
vsShader& vsShader::operator=( const vsShader& shader ) {
	vsEntity::operator=( shader );
	Handle = shader.Handle;

	return *this;
}

// ------------------------------------------------
//	operator==
// ------------------------------------------------
bool_t vsShader::operator==( const vsShader& shader ) {
	return vsEntity::operator==( shader ) && Handle == shader.Handle;
}


// ------------------------------------------------
//	operator!=
// ------------------------------------------------
bool_t vsShader::operator!=( const vsShader& shader ) {
	return !( *this == shader );
}

// ------------------------------------------------
//	LoadFromFile
// ------------------------------------------------
bool_t vsShader::LoadFromFile( const char* szName, const char* szFileName ) {
	FILE*		 f;

	if ( fopen_s( &f, szFileName, "r" ) ) {
		vsLogger::Log( MSG_ERROR, "Failed to load shader: %s", szFileName );
		return false;
	}

	int			 i, params;
	unsigned int fs=0, vs=0, gs=0, tc=0, te=0;
	char		 **fsCode;
	char		 **vsCode;
	char		 **gsCode;
	char		 **tcCode;
	char		 **teCode;
	char		 line[ 150 ];

	fsCode = new char*[ 300 ];
	vsCode = new char*[ 300 ];
	gsCode = new char*[ 300 ];
	teCode = new char*[ 300 ];
	tcCode = new char*[ 300 ];

	for ( i = 0; i < 300; ++i ) {
		fsCode[ i ] = new char[ 150 ];
		vsCode[ i ] = new char[ 150 ];
		gsCode[ i ] = new char[ 150 ];
		teCode[ i ] = new char[ 150 ];
		tcCode[ i ] = new char[ 150 ];
	}

	while ( ! feof( f ) )
	{
		fgets( line, 150, f );

		// Fragment shader ----------------------------------------
		if ( strstr( line, "#FS_BEGIN" ) ) {
			i = -1;
			do {	
				fgets( fsCode[ ++i ], 150, f );
			} while ( !strstr( fsCode[ i ], "#FS_END" ) );
			fsCode[ i ][ 0 ] = '\0';

			fs = glCreateShader( GL_FRAGMENT_SHADER );
			glShaderSource( fs, i-1, ( const char** ) fsCode, NULL );
			glCompileShader( fs );
			
			glGetShaderiv( fs, GL_COMPILE_STATUS, &params );
			if ( params == GL_FALSE ) {
				vsLogger::Log("Failed to compile fragment shader of %s", szFileName );
				char err_str[ 1024 ];
				int length;
				glGetShaderInfoLog( fs, 1024, &length, err_str );
				vsLogger::Log( "\t%s", err_str );
			}
		} else 
		// Vertex Shader ------------------------------------------
		if ( strstr( line, "#VS_BEGIN" ) ) {
			i = -1;
			do {
				fgets( vsCode[ ++i ], 150, f );
			} while ( !strstr( vsCode[ i ], "#VS_END" ) );
			vsCode[ i ][ 0 ] = '\0';

			vs = glCreateShader( GL_VERTEX_SHADER );
			glShaderSource( vs, i-1, ( const char** ) vsCode, NULL );
			glCompileShader( vs );

			glGetShaderiv( fs, GL_COMPILE_STATUS, &params );
			if ( params == GL_FALSE ) {
				vsLogger::Log("Failed to compile vertex shader of %s", szFileName );
				char err_str[ 1024 ];
				int length;
				glGetShaderInfoLog( vs, 1024, &length, err_str );
				vsLogger::Log( "\t%s", err_str );
			}
		} else 
		// Geometry Shader ----------------------------------------
		if ( strstr( line, "#GS_BEGIN" ) ) {
			i = -1;
			do {
				fgets( gsCode[ ++i ], 150, f );
			} while ( !strstr( gsCode[ i ], "#GS_END" ) );
			gsCode[ i ][ 0 ] = '\0';

			gs = glCreateShader( GL_GEOMETRY_SHADER );
			glShaderSource( gs, i-1, ( const char** ) gsCode, NULL );
			glCompileShader( gs );

			glGetShaderiv( gs, GL_COMPILE_STATUS, &params );
			if ( params == GL_FALSE ) {
				vsLogger::Log("Failed to compile geometry shader of %s", szFileName );
				char err_str[ 1024 ];
				int length;
				glGetShaderInfoLog( gs, 1024, &length, err_str );
				vsLogger::Log( "\t%s", err_str );
			}
		} else 
		// Tessellation Control Shader ----------------------------------------
		if ( strstr( line, "#TC_BEGIN" ) ) {
			i = -1;
			do {
				fgets( tcCode[ ++i ], 150, f );
			} while ( !strstr( tcCode[ i ], "#TC_END" ) );
			tcCode[ i ][ 0 ] = '\0';

			tc = glCreateShader( GL_TESS_CONTROL_SHADER );
			glShaderSource( tc, i-1, ( const char** ) tcCode, NULL );
			glCompileShader( tc );

			glGetShaderiv( tc, GL_COMPILE_STATUS, &params );
			if ( params == GL_FALSE ) {
				vsLogger::Log("Failed to compile tessellation control shader of %s", szFileName );
				char err_str[ 1024 ];
				int length;
				glGetShaderInfoLog( tc, 1024, &length, err_str );
				vsLogger::Log( "\t%s", err_str );
			}
		} else 
		// Tessellation Evaluation Shader ----------------------------------------
		if ( strstr( line, "#TE_BEGIN" ) ) {
			i = -1;
			do {
				fgets( teCode[ ++i ], 150, f );
			} while ( !strstr( teCode[ i ], "#TE_END" ) );
			teCode[ i ][ 0 ] = '\0';

			te = glCreateShader( GL_TESS_EVALUATION_SHADER );
			glShaderSource( te, i-1, ( const char** ) teCode, NULL );
			glCompileShader( te );

			glGetShaderiv( te, GL_COMPILE_STATUS, &params );
			if ( params == GL_FALSE ) {
				vsLogger::Log("Failed to compile tessellation evaluation shader of %s", szFileName );
				char err_str[ 1024 ];
				int length;
				glGetShaderInfoLog( te, 1024, &length, err_str );
				vsLogger::Log( "\t%s", err_str );
			}
		}
	}

	Handle = glCreateProgram();
	if ( fs ) glAttachShader( Handle, fs );
	if ( vs ) glAttachShader( Handle, vs );
	if ( gs ) glAttachShader( Handle, gs );
	if ( tc ) glAttachShader( Handle, tc );
	if ( te ) glAttachShader( Handle, te );
	glLinkProgram( Handle );


	for ( i = 0; i < 300; ++i ) {
		delete [] fsCode[ i ];
		delete [] vsCode[ i ];
		delete [] gsCode[ i ];
		delete [] tcCode[ i ];
		delete [] teCode[ i ];
	}

	delete [] fsCode;
	delete [] gsCode;
	delete [] vsCode;
	delete [] teCode;
	delete [] tcCode;

	strcpy_s( this->name, szName );

	return true;
}

