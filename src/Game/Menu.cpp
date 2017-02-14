#include "Menu.h"
#include "..\Application.h"

//----------------------------------------
//	ctor
//----------------------------------------
vsMenu::vsMenu( void ) {
}

//----------------------------------------
//	dtor
//----------------------------------------
vsMenu::~vsMenu( void ) {
}

//----------------------------------------
//	Update()
//----------------------------------------
void vsMenu::Update( bool_t keys[ 256 ], char mouseButtons ) {
	ProcessKeys( keys, mouseButtons );
}

//----------------------------------------
//	Render()
//----------------------------------------
void vsMenu::Render( void ) {
}

//----------------------------------------
//	ProcessKeys()
//----------------------------------------
void vsMenu::ProcessKeys( bool_t keys[ 256 ], char mouseButtons ) {
	if ( keys[ VK_ESCAPE ] )
		application->Exit();
}