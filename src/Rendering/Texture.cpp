#include "Texture.h"
#include "..\System\Logger.h"
#include "OpenGL\GLexp.h"
#include <stdio.h>
#include <math.h>

using namespace vsTexture;

typedef struct {
		unsigned char rgba[ 4 ];
} pixel_t;





texture_t	LoadBMPTexture( const char* szName, const char* szFileName );
texture_t	LoadDDSTexture( const char* szName, const char* szFileName );

// ------------------------------------------------
//	LoadTexture
// ------------------------------------------------
texture_t vsTexture::LoadTexture( const char* szName, const char* szFileName ) {
	size_t len = strlen( szFileName );
	

	if ( ( szFileName[ len - 3 ] == 'B'
	  && szFileName[ len - 2 ] == 'M'
	  && szFileName[ len - 1 ] == 'P' ) || 
	  ( szFileName[ len - 3 ] == 'b'
	  && szFileName[ len - 2 ] == 'm'
	  && szFileName[ len - 1 ] == 'p' ))  {
		return LoadBMPTexture( szName, szFileName );
	}
	else
	if ( ( szFileName[ len - 3 ] == 'D'
	  && szFileName[ len - 2 ] == 'D'
	  && szFileName[ len - 1 ] == 'S' ) ||
	  ( szFileName[ len - 3 ] == 'd'
	  && szFileName[ len - 2 ] == 'd'
	  && szFileName[ len - 1 ] == 's' ) )
		return LoadDDSTexture( szName, szFileName );

	return texture_t();
}

// ------------------------------------------------
//	LoadBMPFile
// ------------------------------------------------
texture_t LoadBMPTexture( const char* szName, const char* szFileName ) {
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
	FILE			 *f;

	if ( fopen_s( &f, szFileName, "rb" ) ) {
		vsLogger::Log( "Failed to load texture: %s", szFileName );
		return	texture_t();
	}


	int				width;
	int				height;
	int				numMipmaps;
	int				numComponents;
	pixel_t*		pixels;

	fread_s( &bmfh, sizeof( bmfh ), sizeof( bmfh ), 1, f );
	fread_s( &bmih, sizeof( bmih ), sizeof( bmih ), 1, f );

	width = bmih.biWidth;
	height = bmih.biHeight;
	numComponents = bmih.biBitCount / 8;
	numMipmaps = 1;

	int len = width * height;
	pixels = new pixel_t[ len ];

	for ( int j, i = 0; i < len; ++i ) {
		for ( j = 0; j < numComponents; j++ )
			fread_s( &pixels[ i ].rgba[ j ], 1, 1, 1, f );

		for ( j = numComponents; j < 4; j++ )
			pixels[ i ].rgba[ j ] = 255;
	}

	fclose( f );

	unsigned int id;
	glGenTextures( 1, &id );
	glBindTexture( GL_TEXTURE_2D, id );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexImage2D( GL_TEXTURE_2D, 0, 
					GL_RGBA, 
					width, 
					height, 
					0,
					GL_RGBA,
					GL_UNSIGNED_BYTE,
					pixels );
	
	if ( numMipmaps == 1 && width > 1 && height > 1 ) {
		pixel_t* mipmap;
		int i, w, h, stride;

		i = 0;
		while ( width > 1 && height > 1 ) {

			width /= 2;
			height /= 2;

			mipmap = new pixel_t[ width * height ];

			stride = ( int )powf( 2.f, ( float )++i );
			for ( w = 0; w < width; ++w )
			for ( h = 0; h < height; ++h ) 
				mipmap[ w * height + h ] = pixels[ w * stride * height * stride + h * stride ];
			

			glTexImage2D( GL_TEXTURE_2D, i, 
				    GL_RGBA, 
					width, 
					height, 
					0,
					GL_RGBA,
					GL_UNSIGNED_BYTE,
					mipmap );
					
			delete [] mipmap;
		}
	}
	delete [] pixels;

	return  texture_t( szName, id );
}


// ------------------------------------------------
//	LoadDDSFile
// ------------------------------------------------
texture_t LoadDDSTexture( const char* szName, const char* szFileName ) {
	DDSURFACEDESC2 ddsd;
	FILE * f;
	unsigned int  format;
	unsigned char*pixels;

	if ( fopen_s( &f, szFileName, "rb" ) )
		return texture_t();

	fseek( f, 4, SEEK_SET );	// magic number
	fread_s( &ddsd, sizeof( ddsd ), sizeof( ddsd ), 1, f );
	
	switch ( ddsd.ddpfPixelFormat.dwFourCC ) {
		case FOURCC_DXT1: format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;

		case FOURCC_DXT3: format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;

		case FOURCC_DXT5: format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	}

	long curPos = ftell( f );
	fseek( f, 0, SEEK_END );
	long endPos = ftell( f );
	fseek( f, curPos, SEEK_SET );

	long len = endPos - curPos;
	pixels = new unsigned char[ len ];

	for ( int i = 0; i < len; ++i ) 
		fread_s( &pixels[ i ], 1, 1, 1, f );

	fclose( f );



	
	unsigned int id;
	
	glGenTextures( 1, &id );
	glBindTexture( GL_TEXTURE_2D, id );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );


	int blockSize = ( format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ) ? 8 : 16;
	int offset = 0, mipSize;

	for ( unsigned int i = 0;  i < ddsd.dwMipMapCount; i++ ) {
		mipSize = (( ddsd.dwWidth + 3 ) / 4 ) * (( ddsd.dwHeight + 3 ) / 4 ) * blockSize;

		glCompressedTexImage2D( 
						GL_TEXTURE_2D, 
						i, 
						format, 
						ddsd.dwWidth, 
						ddsd.dwHeight, 
						0,
						mipSize,
						pixels + offset );

		ddsd.dwWidth /= 2;
		ddsd.dwHeight /= 2;
		offset += mipSize;
	}

	return texture_t( szName, id );
}



