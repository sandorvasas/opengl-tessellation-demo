#pragma once


#include <Windows.h>
#include "Game\GameLocal.h"
#include "Game\Menu.h"
#include "System\System.h"


enum {
	APPSTATE_IN_GAME	= 1
};

enum {
	LDOWN = 1,
	RDOWN = 2,
	MDOWN = 4
};

// --------------------------------------
//	resolution_t
// --------------------------------------
typedef struct resolution_s {
	int		width;
	int		height;
	int		bpp;
	vsVec2i	center;
} resolution_t;


// --------------------------------------
//	applicationParameters_t
// --------------------------------------
typedef struct {
	struct {
		int width, height, bpp;
	} resolution;

	struct {
		char major, minor;
	} GLVersion;
} applicationParameters_t;


// ===================================================
//
//		vsApplication
//
// ===================================================
class vsApplication {
	friend class vsGameLocal;
	friend class vsMenu;
public:
								vsApplication( const applicationParameters_t& params );
								~vsApplication( void );

	void						Init( void );
	void						Run( void );
	void						Exit( void );
	void						Uninit( void );
	void						Update( void );

	const resolution_t&			GetResolution( void ) const;
	const float&				GetMouseSpeed( void ) const;
	void						SetMouseSpeed( float newSpeed );

private:
	void						ProcessKeys( void );
	void						ChangeResolution( int w, int h, int bpp );

	friend static LRESULT CALLBACK	MainWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

private:
	applicationParameters_t		params;
	HWND						hMainWnd;
	HDC							hDC;
	HGLRC						hRC;
	HINSTANCE					hInstance;
	bool_t						bKeys[ 256 ];
	char						mouseButtons;
	bool_t						bRunning;

	resolution_t				resolution;
	float						mouseSpeed;

	int							state;

	vsMenu*						menu;
};


extern vsApplication* application;



//-----------------------------------
//	GetResolution
//-----------------------------------
inline
const resolution_t& vsApplication::GetResolution( void ) const {
	return resolution;
}

//-----------------------------------
//	GetMouseSpeed
//-----------------------------------
inline
const float& vsApplication::GetMouseSpeed( void ) const {
	return mouseSpeed;
}

//-----------------------------------
//	SetMouseSpeed
//-----------------------------------
inline
void vsApplication::SetMouseSpeed( float newSpeed ) {
	mouseSpeed = newSpeed;
}
