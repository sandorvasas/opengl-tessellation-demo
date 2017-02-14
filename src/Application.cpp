#include "Application.h"
#include "Rendering\OpenGL\GLexp.h"
#include "Rendering\Renderer.h"
#include "System\Logger.h"


vsApplication* application;

// ------------------------------------------------
//	vsApplication
// ------------------------------------------------
vsApplication::vsApplication( const applicationParameters_t& params ) {
	ZeroMemory( bKeys, 256 );
	gameLocal = NULL;
	menu = NULL;
	mouseSpeed = 0.5f;

	resolution.width = params.resolution.width;
	resolution.height= params.resolution.height;
	resolution.bpp   = params.resolution.width;
	resolution.center.x = resolution.width / 2;
	resolution.center.y = resolution.height / 2;

	this->params = params;
}

// ------------------------------------------------
//	~vsApplication
// ------------------------------------------------
vsApplication::~vsApplication( void ) {
}

// ------------------------------------------------
//	Init
// ------------------------------------------------
void vsApplication::Init( void ) {
	WNDCLASSEX	wc;
	char		wndClassName[] = "vsWindowClassName";
	char		wndName[]	   = "_window_name_";

	hInstance = GetModuleHandle( 0 );

	wc.cbSize			= sizeof( wc );
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hbrBackground	= ( HBRUSH ) GetStockObject( 4 );
	wc.hCursor			= LoadCursor( NULL, IDC_ARROW );
	wc.hIcon			= LoadIcon( NULL, IDI_WINLOGO );
	wc.hIconSm			= wc.hIcon;
	wc.hInstance		= hInstance;
	wc.lpfnWndProc		= MainWndProc;
	wc.lpszClassName	= wndClassName;
	wc.lpszMenuName		= 0;
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	RegisterClassEx( &wc );
	
	hMainWnd = CreateWindowEx( WS_EX_APPWINDOW, 
							   wndClassName,
							   wndName,
							   WS_POPUP,
							   0, 0,
							   GetSystemMetrics( SM_CXSCREEN ),
							   GetSystemMetrics( SM_CYSCREEN ),
							   NULL, NULL,
							   hInstance,
							   0 );
	ShowWindow( hMainWnd, SW_SHOW );
	ShowCursor( false );
	SetCursorPos( resolution.center.x, resolution.center.y );

	vsLogger::Init();
	
	hDC = GetDC( hMainWnd );
							   
	// Init OpenGL -----------------------------------------------------------------
	PIXELFORMATDESCRIPTOR pfd;
	pfd.nSize = sizeof( pfd );
	pfd.nVersion = 1;
	//pfd.cAlphaBits = 8;
	pfd.cDepthBits = 32;
	pfd.cColorBits = 32;
	pfd.cStencilBits = 24;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.dwFlags	= PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
	
	int pf = ChoosePixelFormat( hDC, &pfd );
	SetPixelFormat( hDC, pf, &pfd );

	if ( params.GLVersion.major <= 2 ) {
		hRC = wglCreateContext( hDC );
		wglMakeCurrent( hDC, hRC );

		vsGL::LoadOpenGLCore_2_0();
	} else {
		HGLRC hTempRC = wglCreateContext( hDC );
		wglMakeCurrent( hDC, hTempRC );
		
		vsGL::LoadOpenGLCore_4_0();
	
		const int attribs[] = {
			// attribute					value
			WGL_CONTEXT_MAJOR_VERSION_ARB,	params.GLVersion.major,
			WGL_CONTEXT_MINOR_VERSION_ARB,	params.GLVersion.minor,
			WGL_CONTEXT_FLAGS_ARB,			WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			WGL_CONTEXT_PROFILE_MASK_ARB,	WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};
		hRC = wglCreateContextAttribsARB( hDC, hTempRC, attribs );
		wglDeleteContext( hTempRC );
		wglMakeCurrent( hDC, hRC );
	}


	glEnable( GL_DEPTH_TEST );
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	renderer = new vsRenderer( params.GLVersion.major, params.GLVersion.minor );

	vsMat4 proj;
	proj.Perspective( 120.0f, ( float )( resolution.height ) / ( float )( resolution.width ), 0.1f );
	renderer->LoadMatrix( PROJECTION_MATRIX, proj );


	// ---------------------------------------
	state = APPSTATE_IN_GAME;

	if ( state == APPSTATE_IN_GAME ) {
		gameLocal = new vsGameLocal();
		gameLocal->NewGame();
	}


	bRunning = true;
}


// ------------------------------------------------
//	Exit 
//		[ use this function to exit app ]
// ------------------------------------------------
void vsApplication::Exit( void ) {
	bRunning = false;
}

// ------------------------------------------------
//	Uninit
// ------------------------------------------------
void vsApplication::Uninit( void ) {
	if ( bRunning )
		return;

	if ( gameLocal )
		delete gameLocal;
	if ( menu )
		delete menu;
	if ( renderer )
		delete renderer;

	gameLocal = NULL;
	menu = NULL;

	wglMakeCurrent( hDC, 0 );
	wglDeleteContext( hRC );
	DeleteDC( hDC );
	DestroyWindow( hMainWnd );
}

// ------------------------------------------------
//	Run
// ------------------------------------------------
void vsApplication::Run( void ) {
	Init();

	MSG msg;

	while ( bRunning ) {
		if ( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) ) {
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		} else {
			Update();
		}
	}

	Uninit();
}

// ------------------------------------------------
//	Update
// ------------------------------------------------
void vsApplication::Update( void ) {
	ProcessKeys();

	if ( state == APPSTATE_IN_GAME ) {
		gameLocal->Update( bKeys, mouseButtons );
	} else {
		menu->Update( bKeys, mouseButtons );
	}
}


// ------------------------------------------------
//	ProcessKeys
// ------------------------------------------------
void vsApplication::ProcessKeys( void ) {
	if ( bKeys[ VK_ESCAPE ] ) {
		Exit();
	}
}

// ------------------------------------------------
//	ChangeResolution
// ------------------------------------------------
void vsApplication::ChangeResolution( int w, int h, int bpp ) {
	DEVMODE dm;

	EnumDisplaySettings( NULL, 0, &dm );
	dm.dmBitsPerPel = bpp;
	dm.dmPelsHeight = h;
	dm.dmPelsWidth  = w;
	dm.dmFields = DM_BITSPERPEL | DM_PELSHEIGHT | DM_PELSWIDTH;
	ChangeDisplaySettings( &dm, CDS_FULLSCREEN );

	resolution.width = w;
	resolution.height = h;
	resolution.bpp = bpp;
	resolution.center.x = w / 2;
	resolution.center.y = h / 2;
}

// ------------------------------------------------
//	MainWndProc
// ------------------------------------------------
LRESULT CALLBACK MainWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {
	switch ( uMsg ) {
		case WM_KEYDOWN:		application->bKeys[ wParam ] = true;
		break;
		case WM_KEYUP:			application->bKeys[ wParam ] = false;
		break;
		case WM_LBUTTONDOWN:	application->mouseButtons &= LDOWN;
		break;
		case WM_LBUTTONUP:		application->mouseButtons ^= LDOWN;
		break;
		case WM_RBUTTONDOWN:	application->mouseButtons &= RDOWN;
		break;
		case WM_RBUTTONUP:		application->mouseButtons ^= RDOWN;
		break;
		case WM_MBUTTONDOWN:	application->mouseButtons &= MDOWN;
		break;
		case WM_MBUTTONUP:		application->mouseButtons ^= MDOWN;
		break;
	}

	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

