#ifndef __VS_TEXTURE_H__
#define __VS_TEXTURE_H__

#include <Windows.h>
#include "..\System\Entity.h"


namespace vsTexture {
	// -------------------------------------------------
	//	texture_t
	// -------------------------------------------------
	class texture_t : public vsEntity {
	public:
						texture_t( void ) : handle( 0 ) { vsEntity::vsEntity();  };

						texture_t( const char* name, unsigned int handle ) {
							strcpy_s( this->name, name );
							this->handle = handle;
						};

						~texture_t( void ) {};

	public:
		unsigned int	handle;
	};

	const texture_t	nullTexture = texture_t();

	texture_t		LoadTexture( const char* szName, const char* szFileName );
};


#define FOURCC_DXT1	MAKEFOURCC( 'D', 'X', 'T', '1' )
#define FOURCC_DXT3	MAKEFOURCC( 'D', 'X', 'T', '3' )
#define FOURCC_DXT5	MAKEFOURCC( 'D', 'X', 'T', '5' )

/*
================================================

	DDSURFACEDESC2 struct from MSDN

	Contains information about 
	.DDS texture files.

================================================
*/
struct DDSURFACEDESC2 {
		DWORD			dwSize;
		DWORD			dwFlags;
		DWORD			dwHeight;
		DWORD			dwWidth;
		DWORD			dwPitchOrLinearSize;
		DWORD			dwDepth;
		DWORD			dwMipMapCount;
		DWORD			dwReserved[11];
	
		struct {
			DWORD	dwSize;
			DWORD	dwFlags;
			DWORD	dwFourCC;
			DWORD	dwRGBBitCount;
			DWORD	dwRBitMask;
			DWORD	dwGBitMask;
			DWORD	dwBBitMask;
			DWORD	dwRGBAlphaBitMask;	
		} ddpfPixelFormat;

		struct  {
			DWORD	dwCaps1;
			DWORD	dwCaps2;
			DWORD	dwReserved[2];
		} ddsCaps;

		DWORD			dwReserved2;
};

#endif