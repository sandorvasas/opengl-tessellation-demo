#include "Font.h"
#include "OpenGL\GLexp.h"
#include "Renderer.h"
#include "Colors.h"

using namespace vsPrinter;

#define QUEUE_MAXLEN	256
#define CONSOLE_MAXLEN	256

struct vsPrinterStaticData {
	struct queueElem_t {
		vsVec4f		color;
		font_t		font;
		vsVec2f		pos;
		char		text[ 256 ];
	}	queue[ QUEUE_MAXLEN ];

	int	queueLen;

	vsPrinterStaticData( void ) : queueLen( 0 ) {};
	~vsPrinterStaticData( void ) {};
};

vsPrinterStaticData printerData;

//-----------------------------------
//	NewFont
//-----------------------------------
font_t vsPrinter::NewFont( const char * szFontName, int size ) {
	HFONT font;
	unsigned int id;

	font = CreateFont(	size, 0, 0, 0, 0, 
						false, false, false, 
						ANSI_CHARSET, 
						OUT_TT_PRECIS, 
						CLIP_DEFAULT_PRECIS, 
						ANTIALIASED_QUALITY, 
						FF_DONTCARE | DEFAULT_PITCH, 
						szFontName );
	HDC dc = wglGetCurrentDC();

	SelectObject( dc, font );
	id = glGenLists( 256 );
	wglUseFontBitmaps( dc, 0, 256, id );
	SelectObject( dc, 0 );

	return id;
}

//-----------------------------------
//	NewFontFromFile
//-----------------------------------
font_t vsPrinter::NewFontFromFile( const char * szFileName, const char* szFontName, int size ) {
	return 0;
}

//-----------------------------------
//	PrintToQueue
//-----------------------------------
void vsPrinter::PrintToQueue( const vsPrinter::font_t& font, const vsVec4f& color, float x, float y, char* format, ... ) {
	if ( printerData.queueLen < QUEUE_MAXLEN ) {
		char text[ 256 ];
		va_list L;

		va_start( L, format );
			vsprintf_s( text, format, L );
		va_end( L );

		printerData.queue[ printerData.queueLen ].color = color;
		printerData.queue[ printerData.queueLen ].font = font;
		strcpy_s( printerData.queue[ printerData.queueLen ].text, text );
		printerData.queue[ printerData.queueLen ].pos.x = x;
		printerData.queue[ printerData.queueLen++ ].pos.y = y;
	}
}

//-----------------------------------
//	PrintQueue
//-----------------------------------
void vsPrinter::PrintQueue( void ) {
	if ( printerData.queueLen > 0 ) {
		vsPrinterStaticData::queueElem_t* elem;

		renderer->OrthoMode( true );

		REPEAT( printerData.queueLen ) {
			elem = &printerData.queue[ i ];

			glColor4fv( elem->color.ToTypePtr() );
			glRasterPos2fv( elem->pos.ToTypePtr() );
			glListBase( elem->font );

			glCallLists( strlen( elem->text ), GL_UNSIGNED_BYTE, elem->text );
		}

		renderer->OrthoMode( false );
		printerData.queueLen = 0;
	}
}


//-----------------------------------
//	Print
//-----------------------------------
void vsPrinter::Print( const vsPrinter::font_t& font, const vsVec4f& color, float x, float y, char* format, ... ) {
	char text[ 256 ];
	va_list L;

	va_start( L, format );
		vsprintf_s( text, format, L );
	va_end( L );

	renderer->OrthoMode( true );
		glColor4fv( color.ToTypePtr() );
		glRasterPos2f( x, y );
		glListBase( font );

		glCallLists( strlen( text ), GL_UNSIGNED_BYTE, text );
	renderer->OrthoMode( false );
}

//-----------------------------------
//	Print
//-----------------------------------
void vsPrinter::Print( const vsPrinter::font_t& font, float x, float y, char* format, ... ) {
	char text[ 256 ];
	va_list L;

	va_start( L, format );
		vsprintf_s( text, format, L );
	va_end( L );
	Print( font, vsColors::White, x, y, text );
}