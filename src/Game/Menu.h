#pragma once

#include "..\System\System.h"

class vsMenu {
public:
						vsMenu( void );
						~vsMenu( void );

	void				Update( bool_t keys[ 256 ], char mouseButtons );

private:
	void				Render( void );
	void				ProcessKeys( bool_t keys[ 256 ], char mouseButtons );

private:
	// variables
};