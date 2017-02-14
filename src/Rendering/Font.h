#ifndef __VS_FONT_H__
#define __VS_FONT_H__

#include <Windows.h>
#include "..\Math\Math.h"

// -----------------------------------------------------
//
//	vsPrinter
//
// -----------------------------------------------------
namespace vsPrinter {

	typedef unsigned int font_t;

	font_t		NewFont( const char * szFontName, int size );
	font_t		NewFontFromFile( const char * szFileName, const char* szFontName, int size );

	void		PrintToQueue( const font_t& font, const vsVec4f& color, float x, float y, char* format, ... );
	void		PrintQueue( void );
	void		Print( const font_t& font, const vsVec4f& color, float x, float y, char* format, ... );
	void		Print( const font_t& font, float x, float y, char* format, ... );
};

#endif