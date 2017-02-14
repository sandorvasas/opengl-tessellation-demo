#ifndef __VS_SHADER_H__
#define __VS_SHADER_H__

#include "..\System\System.h"
#include "OpenGL\GLexp.h"
#include "..\System\Entity.h"

// ==================================================================
//
//		vsShader
//
// ==================================================================
class vsShader : public vsEntity {
public:
					vsShader( void );
					~vsShader( void );

	vsShader&		operator=( const vsShader& shader );
	bool_t			operator==( const vsShader& shader );
	bool_t			operator!=( const vsShader& shader );

	bool_t			LoadFromFile( const char* szName, const char* szFileName );
	void			Enable( void );
	void			Disable( void );

	unsigned int	GetUniformLocation( const char* szUniName );
	unsigned int	GetAttribLocation( const char* szUniName );
	void			BindFragDataLocation( const char* szName, const unsigned int& colorNumber );
	void			Uniform1i( const char* szUniName, int value );
	void			Uniform2i( const char* szUniName, int x, int y );
	void			Uniform3i( const char* szUniName, int x, int y, int z );
	void			Uniform4i( const char* szUniName, int x, int y, int z, int w );
	void			Uniform2iv( const char* szUniName, const int* values );
	void			Uniform3iv( const char* szUniName, const int* values );
	void			Uniform4iv( const char* szUniName, const int* values );
	void			Uniform1f( const char* szUniName, float value );
	void			Uniform2f( const char* szUniName, float x, float y );
	void			Uniform3f( const char* szUniName, float x, float y, float z );
	void			Uniform4f( const char* szUniName, float x, float y, float z, float w );
	void			Uniform2fv( const char* szUniName, const float* values );
	void			Uniform3fv( const char* szUniName, const float* values );
	void			Uniform4fv( const char* szUniName, const float* values );
	void			Uniform1i( int uniformLocation, int value );
	void			Uniform2i( int uniformLocation, int x, int y );
	void			Uniform3i( int uniformLocation, int x, int y, int z );
	void			Uniform4i( int uniformLocation, int x, int y, int z, int w );
	void			Uniform2iv( int uniformLocation, const int* values );
	void			Uniform3iv( int uniformLocation, const int* values );
	void			Uniform4iv( int uniformLocation, const int* values );
	void			Uniform1f( int uniformLocation, float value );
	void			Uniform2f( int uniformLocation, float x, float y );
	void			Uniform3f( int uniformLocation, float x, float y, float z );
	void			Uniform4f( int uniformLocation, float x, float y, float z, float w );
	void			Uniform2fv( int uniformLocation, const float* values );
	void			Uniform3fv( int uniformLocation, const float* values );
	void			Uniform4fv( int uniformLocation, const float* values );
	void			UniformMatrix2fv( const char* szUniName, const float* matrix );
	void			UniformMatrix3fv( const char* szUniName, const float* matrix );
	void			UniformMatrix4fv( const char* szUniName, const float* matrix );
	void			UniformMatrix2fv( int uniformLocation, const float* matrix );
	void			UniformMatrix3fv( int uniformLocation, const float* matrix );
	void			UniformMatrix4fv( int uniformLocation, const float* matrix );

	
public:
	unsigned int	Handle;
};






//-----------------------------------
//	Enable
//-----------------------------------
VS_INLINE void vsShader::Enable( void ) {
	glUseProgram( Handle );
}

//-----------------------------------
//	Disable
//-----------------------------------
VS_INLINE void vsShader::Disable( void ) {
	glUseProgram( 0 );
}

//-----------------------------------
//	GetUniformLocation
//-----------------------------------

VS_INLINE unsigned int vsShader::GetUniformLocation( const char* szUniName ) {
	return glGetUniformLocation( Handle, szUniName );
}

//-----------------------------------
//	GetAttribLocation
//-----------------------------------
VS_INLINE unsigned int vsShader::GetAttribLocation( const char* szUniName ) {
	return glGetAttribLocation( Handle, szUniName );
}

//-----------------------------------
//	BindFragDataLocation
//-----------------------------------
VS_INLINE void vsShader::BindFragDataLocation( const char* szName, const unsigned int& colorNumber ) {
	glBindFragDataLocation( Handle, colorNumber, name );
}

//-----------------------------------
//	Uniform1i
//-----------------------------------
VS_INLINE void vsShader::Uniform1i( const char* szUniName, int value ) {
	glUniform1i( GetUniformLocation( szUniName ), value );
}

//-----------------------------------
//	Uniform2i
//-----------------------------------
VS_INLINE void vsShader::Uniform2i( const char* szUniName, int x, int y ) {
	glUniform2i( GetUniformLocation( szUniName ), x, y );
}

//-----------------------------------
//	Uniform3i
//-----------------------------------
VS_INLINE void vsShader::Uniform3i( const char* szUniName, int x, int y, int z ) {
	glUniform3i( GetUniformLocation( szUniName ), x, y, z );
}

//-----------------------------------
//	Uniform4i
//-----------------------------------
VS_INLINE void vsShader::Uniform4i( const char* szUniName, int x, int y, int z, int w ) {
	glUniform4i( GetUniformLocation( szUniName ), x, y, z, w );
}


//-----------------------------------
//	Uniform2iv
//-----------------------------------
VS_INLINE void vsShader::Uniform2iv( const char* szUniName, const int* values ) {
	glUniform2iv( GetUniformLocation( szUniName ), 2, values );
}

//-----------------------------------
//	Uniform3iv
//-----------------------------------
VS_INLINE void vsShader::Uniform3iv( const char* szUniName, const int* values ) {
	glUniform3iv( GetUniformLocation( szUniName ), 3, values );
}

//-----------------------------------
//	Uniform4iv
//-----------------------------------
VS_INLINE void vsShader::Uniform4iv( const char* szUniName, const int* values ) {
	glUniform4iv( GetUniformLocation( szUniName ), 4, values );
}

//-----------------------------------
//	Uniform1f
//-----------------------------------
VS_INLINE void vsShader::Uniform1f( const char* szUniName, float value ) {
	glUniform1f( GetUniformLocation( szUniName ), value );
}

//-----------------------------------
//	Uniform2f
//-----------------------------------
VS_INLINE void vsShader::Uniform2f( const char* szUniName, float x, float y ) {
	glUniform2f( GetUniformLocation( szUniName ), x, y );
}

//-----------------------------------
//	Uniform3f
//-----------------------------------
VS_INLINE void vsShader::Uniform3f( const char* szUniName, float x, float y, float z ) {
	glUniform3f( GetUniformLocation( szUniName ), x, y, z );
}

//-----------------------------------
//	Uniform4f
//-----------------------------------
VS_INLINE void vsShader::Uniform4f( const char* szUniName, float x, float y, float z, float w ) {
	glUniform4f( GetUniformLocation( szUniName ), x, y, z, w );
}

//-----------------------------------
//	Uniform2fv
//-----------------------------------
VS_INLINE void vsShader::Uniform2fv( const char* szUniName, const float* values ) {
	glUniform2fv( GetUniformLocation( szUniName ), 2, values );
}

//-----------------------------------
//	Uniform3fv
//-----------------------------------
VS_INLINE void vsShader::Uniform3fv( const char* szUniName, const float* values ) {
	glUniform3fv( GetUniformLocation( szUniName ), 3, values );
}

//-----------------------------------
//	Uniform4fv
//-----------------------------------
VS_INLINE void vsShader::Uniform4fv( const char* szUniName, const float* values ) {
	glUniform4fv( GetUniformLocation( szUniName ), 4, values );
}

//-----------------------------------
//	Uniform1i
//-----------------------------------
VS_INLINE void vsShader::Uniform1i( int uniformLocation, int value ) {
	glUniform1i( uniformLocation, value );
}

//-----------------------------------
//	Uniform2i
//-----------------------------------
VS_INLINE void vsShader::Uniform2i( int uniformLocation, int x, int y ) {
	glUniform2i( uniformLocation, x, y );
}

//-----------------------------------
//	Uniform3i
//-----------------------------------
VS_INLINE void vsShader::Uniform3i( int uniformLocation, int x, int y, int z ) {
	glUniform3i( uniformLocation, x, y, z );
}

//-----------------------------------
//	Uniform4i
//-----------------------------------
VS_INLINE void vsShader::Uniform4i( int uniformLocation, int x, int y, int z, int w ) {
	glUniform4i( uniformLocation, x, y, z, w );
}

//-----------------------------------
//	Uniform2iv
//-----------------------------------
VS_INLINE void vsShader::Uniform2iv( int uniformLocation, const int* values ) {
	glUniform2iv( uniformLocation, 2, values );
}

//-----------------------------------
//	Uniform3iv
//-----------------------------------
VS_INLINE void vsShader::Uniform3iv( int uniformLocation, const int* values ) {
	glUniform3iv( uniformLocation, 3, values );
}

//-----------------------------------
//	Uniform4iv
//-----------------------------------
VS_INLINE void vsShader::Uniform4iv( int uniformLocation, const int* values ) {
	glUniform4iv( uniformLocation, 4, values );
}

//-----------------------------------
//	Uniform1f
//-----------------------------------
VS_INLINE void vsShader::Uniform1f( int uniformLocation, float value ) {
	glUniform1f( uniformLocation, value );
}

//-----------------------------------
//	Uniform2f
//-----------------------------------
VS_INLINE void vsShader::Uniform2f( int uniformLocation, float x, float y ) {
	glUniform2f( uniformLocation, x, y );
}

//-----------------------------------
//	Uniform3f
//-----------------------------------
VS_INLINE void vsShader::Uniform3f( int uniformLocation, float x, float y, float z ) {
	glUniform3f( uniformLocation, x, y, z );
}

//-----------------------------------
//	Uniform4f
//-----------------------------------
VS_INLINE void vsShader::Uniform4f( int uniformLocation, float x, float y, float z, float w ) {
	glUniform4f( uniformLocation, x, y, z, w );
}

//-----------------------------------
//	Uniform2fv
//-----------------------------------
VS_INLINE void vsShader::Uniform2fv( int uniformLocation, const float* values ) {
	glUniform2fv( uniformLocation, 2, values );
}

//-----------------------------------
//	Uniform3fv
//-----------------------------------
VS_INLINE void vsShader::Uniform3fv( int uniformLocation, const float* values ) {
	glUniform3fv( uniformLocation, 3, values );
}

//-----------------------------------
//	Uniform4fv
//-----------------------------------
VS_INLINE void vsShader::Uniform4fv( int uniformLocation, const float* values ) {
	glUniform4fv( uniformLocation, 4, values );
}

//-----------------------------------
//	UniformMatrix2fv
//-----------------------------------
VS_INLINE void vsShader::UniformMatrix2fv( const char* szUniName, const float* matrix ) {
	glUniformMatrix2fv( GetUniformLocation( szUniName ), 1, false, matrix );
}

//-----------------------------------
//	UniformMatrix3fv
//-----------------------------------
VS_INLINE void vsShader::UniformMatrix3fv( const char* szUniName, const float* matrix ) {
	glUniformMatrix3fv( GetUniformLocation( szUniName ), 1, false, matrix );
}

//-----------------------------------
//	UniformMatrix4fv
//-----------------------------------
VS_INLINE void vsShader::UniformMatrix4fv( const char* szUniName, const float* matrix ) {
	glUniformMatrix4fv( GetUniformLocation( szUniName ), 1, false, matrix );
}

//-----------------------------------
//	UniformMatrix2fv
//-----------------------------------
VS_INLINE void vsShader::UniformMatrix2fv( int uniformLocation, const float* matrix ) {
	glUniformMatrix2fv( uniformLocation, 1, false, matrix );
}

//-----------------------------------
//	UniformMatrix3fv
//-----------------------------------
VS_INLINE void vsShader::UniformMatrix3fv( int uniformLocation, const float* matrix ) {
	glUniformMatrix3fv( uniformLocation, 1, false, matrix );
}

//-----------------------------------
//	UniformMatrix4fv
//-----------------------------------
VS_INLINE void vsShader::UniformMatrix4fv( int uniformLocation, const float* matrix ) {
	glUniformMatrix4fv( uniformLocation, 1, false, matrix );
}

#endif