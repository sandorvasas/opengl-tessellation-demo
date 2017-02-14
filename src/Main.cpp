#include "Application.h"



int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int ) {

	applicationParameters_t params;
	params.GLVersion.major   = 4;
	params.GLVersion.minor   = 1;
	params.resolution.width  = GetSystemMetrics( SM_CXSCREEN );
	params.resolution.height = GetSystemMetrics( SM_CYSCREEN );
	params.resolution.bpp	 = 32;

	application = new vsApplication( params );

	application->Run();

	delete application;

	return 0;
}