/// REGULAR EXPRESSION TO REPLACE ;
///  {\n	\n}\n\n//-----------------------------------\n//	\n//-----------------------------------


#include "GameLocal.h"
#include "..\Application.h"
#include "..\Rendering\OpenGL\GLexp.h"
#include "..\Rendering\Colors.h"
#include "..\System\Logger.h"
#include "..\Rendering\Renderer.h"
#include "Model\Material.h"


vsGameLocal* gameLocal;

//-----------------------------------
//	ctor
//-----------------------------------
vsGameLocal::vsGameLocal( void ) {
}

//-----------------------------------
//	dtor
//-----------------------------------
vsGameLocal::~vsGameLocal( void ) {
	delete world;
	delete player;
	delete materialLibrary;
}

//-----------------------------------
//	NewGame()
//-----------------------------------
void vsGameLocal::NewGame( void ) {
	LoadResources( "data/resources.txt" );

	deltaTime = 1.0f / 60.0f;
	fps = 60.0f;
	time = 0.0f;

	player = new vsPlayer();
	world  = new vsWorld();

	baseFont = vsPrinter::NewFont( "Franklin Gothic Medium", 20 );

	testShader = GetShader( "default" );
	testShader.Enable();
	testShader.Uniform1i( "diffuse1", 0 );
	testShader.Uniform1i( "normalmap", 1 );
	testShader.Disable();

	testTexture = GetTexture( "stone_wall1_d" );
	normalmap	= GetTexture( "water_displacement" );

	player->SetOrigin( vsVec3f( -10.0f, 5.0f, 10.0f ) );
	player->Spawn();

	lightPos = vsVec3f( 0.0f, 10.0f, 0.0f );

	testMesh.wireframe = 0;
	testMesh.vert.Resize( 2400 );
	int j = 0;
	for ( float z, x = -100.0f; x < 100.0f; x+=10.f )
	for ( z = -100.0f; z < 100.0f; z+=10.f ) {
		testMesh.vert[ j++ ] = vsVec3f( x, 0.0f, z );
		testMesh.vert[ j++ ] = vsVec3f( x+10.f, 0.0f, z );
		testMesh.vert[ j++ ] = vsVec3f( x+10.f, 0.0f, z+10.f );

		testMesh.vert[ j++ ] = vsVec3f( x, 0.0f, z );
		testMesh.vert[ j++ ] = vsVec3f( x+10.f, 0.0f, z+10.f );
		testMesh.vert[ j++ ] = vsVec3f( x, 0.0f, z+10.f );
	}

	glGenVertexArrays( 1, &testMesh.vao );
	glBindVertexArray( testMesh.vao );

	glGenBuffers( 1, &testMesh.vbo );
	glBindBuffer( GL_ARRAY_BUFFER, testMesh.vbo );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vsVec3f ) * testMesh.vert.Length(), testMesh.vert.List(), GL_STATIC_DRAW );

	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, false, 3 * sizeof( float ), NULL );
	glBindVertexArray( 0 );

	/// mesh 2
	glGenVertexArrays( 1, &testMesh2.vao );
	glBindVertexArray( testMesh2.vao );

	testMesh2.vert.Resize( 6 );
	testMesh2.vert[ 0 ].pos = vsVec3f( -100.0f, 0.0f, -100.0f );
	testMesh2.vert[ 1 ].pos = vsVec3f(  100.0f, 0.0f, -100.0f );
	testMesh2.vert[ 2 ].pos = vsVec3f(  100.0f, 0.0f,  100.0f );

	testMesh2.vert[ 3 ].pos = vsVec3f( -100.0f, 0.0f, -100.0f );
	testMesh2.vert[ 4 ].pos = vsVec3f(  100.0f, 0.0f,  100.0f );
	testMesh2.vert[ 5 ].pos = vsVec3f( -100.0f, 0.0f,  100.0f );

	testMesh2.vert[ 0 ].uv = vsVec2f( 0.0f, 0.0f );
	testMesh2.vert[ 1 ].uv = vsVec2f( 1.0f, 0.0f );
	testMesh2.vert[ 2 ].uv = vsVec2f( 1.0f, 1.0f );

	testMesh2.vert[ 3 ].uv = vsVec2f( 0.0f, 0.0f );
	testMesh2.vert[ 4 ].uv = vsVec2f( 1.0f, 1.0f );
	testMesh2.vert[ 5 ].uv = vsVec2f( 0.0f, 1.0f );

	testMesh2.tessLevel = 2.0;

	glGenBuffers( 1, &testMesh2.vbo );
	glBindBuffer( GL_ARRAY_BUFFER, testMesh2.vbo );
	glBufferData( GL_ARRAY_BUFFER, ( sizeof( vsVec3f )+sizeof( vsVec2f ) ) * testMesh2.vert.Length(), testMesh2.vert.List(), GL_STATIC_DRAW );
	
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, false, 5 * sizeof( float ), NULL );
	
	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer( 1, 2, GL_FLOAT, false, 5 * sizeof( float ), ( const void* ) (sizeof(float)*3) );
	
	glBindVertexArray( 0 );

	testMesh2.vert.Clear();

	testMesh2.disp1 = gameLocal->GetTexture( "disp1" );
	testMesh2.disp2 = gameLocal->GetTexture( "disp2" );
	testMesh2.dispF = gameLocal->GetTexture( "dispf" );

	testMesh2.shader = gameLocal->GetShader( "displace" );
	testMesh2.shader.Enable();
	testMesh2.shader.Uniform1i( "map_Displacement1", 0 );
	testMesh2.shader.Uniform1i( "map_Displacement2", 1 );
	testMesh2.shader.Uniform1i( "map_Blend", 2 );
	testMesh2.shader.Disable();

}

//-----------------------------------
//	RestoreGame()
//-----------------------------------
void vsGameLocal::RestoreGame( const char* szRestoreFile ) {
	
}

//-----------------------------------
//	SaveGame()
//-----------------------------------
void vsGameLocal::SaveGame( const char* szSaveFile ) {
	
}

//-----------------------------------
//	Update()
//-----------------------------------
void vsGameLocal::Update( bool_t keys[ 256 ], char mouseButtons ) {
	ProcessKeys( keys, mouseButtons );
	UpdatePhysics();
	Render();
}

//-----------------------------------
//	ProcessKeys()
//-----------------------------------
void vsGameLocal::ProcessKeys( bool_t keys[ 256 ], char mouseButtons ) {
	int dirs = 0;

	if ( keys[ 'W' ] ) dirs |= PLAYER_MOVE_FORWARD;
	if ( keys[ 'S' ] ) dirs |= PLAYER_MOVE_BACKWARD;
	if ( keys[ 'D' ] ) dirs |= PLAYER_MOVE_RIGHT;
	if ( keys[ 'A' ] ) dirs |= PLAYER_MOVE_LEFT;
	if ( keys[ 'E' ] ) dirs |= PLAYER_MOVE_UP;
	if ( keys[ 'Q' ] ) dirs |= PLAYER_MOVE_DOWN;

	float s = 0.1f;
	if ( keys[ VK_UP ] )	lightPos.z += s;
	if ( keys[ VK_DOWN ] )	lightPos.z -= s;
	if ( keys[ VK_LEFT ] )	lightPos.x += s;
	if ( keys[ VK_RIGHT ] )	lightPos.x -= s;
	if ( keys[ 'Y' ] )	lightPos.y += s;
	if ( keys[ 'X' ] )	lightPos.y -= s;

	if ( keys[ VK_ADD ] )		 { 
		keys[ VK_ADD ] = 0; testMesh2.tessLevel++; }
	if ( keys[ VK_SUBTRACT ] )	 { keys[ VK_SUBTRACT ] = 0; testMesh2.tessLevel--; }

	if ( keys[ '1' ] ) {
		keys[ '1' ] = false;
		testMesh.wireframe = 1 - testMesh.wireframe;
	}

	player->SetMoveDirection( dirs );
}

//-----------------------------------
//	UpdatePhysics
//-----------------------------------
void vsGameLocal::UpdatePhysics( void ) {
	// collision checks & responses
	player->MoveToDestination();

	time += deltaTime;
}

//-----------------------------------
//	UpdateShaderVariables()
//-----------------------------------
void vsGameLocal::UpdateShaderVariables( void ) {
	testShader.Enable();
		testShader.Uniform1f( "in_Time", time );
		testShader.Uniform3fv( "in_ViewPos", player->GetOrigin().ToTypePtr() );
		testShader.Uniform3fv( "in_LightPos", lightPos.ToTypePtr() );
		testShader.UniformMatrix4fv( "in_MVPMatrix", renderer->ModelViewProjectionMatrix().ToTypePtr() );
	testShader.Disable();

	testMesh2.shader.Enable();
		testMesh2.shader.Uniform1f( "in_Time", time );
		testMesh2.shader.Uniform3fv( "in_ViewPos", player->GetOrigin().ToTypePtr() );
		testMesh2.shader.Uniform3fv( "in_LightPos", lightPos.ToTypePtr() );
		testMesh2.shader.Uniform1f( "in_TessLevel", testMesh2.tessLevel );
		testMesh2.shader.UniformMatrix4fv( "in_MVPMatrix", renderer->ModelViewProjectionMatrix().ToTypePtr() );
	testMesh2.shader.Disable();
}

//-----------------------------------
//	RenderToBuffer()
//-----------------------------------
void vsGameLocal::RenderToBuffer( void ) {
	
}

//-----------------------------------
//	Render()
//-----------------------------------
void vsGameLocal::Render( void ) {
	UpdateShaderVariables();

	glClearColor( 0.5f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	
	vsPrinter::Print( baseFont, vsColors::White, 5.0f, 20.0f, "FPS: %5.0f", 9/4 );
	
	player->UpdateRotation();
	player->Look();

	world->Render();

	glLineWidth( 3.0f );
	if ( testMesh.wireframe == 1 )
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	else 
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	/*testShader.Enable();

	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, testTexture.handle );
	glActiveTexture( GL_TEXTURE1 );
	glBindTexture( GL_TEXTURE_2D, normalmap.handle );

	glBindVertexArray( testMesh.vao );

	glPatchParameteri( GL_PATCH_VERTICES, 3 );
//	glDrawArrays( GL_PATCHES, 0, testMesh.vert.Length() );

	glBindVertexArray( 0 );

	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, 0 );
	glActiveTexture( GL_TEXTURE1 );
	glBindTexture( GL_TEXTURE_2D, 0 );

	testShader.Disable();*/
	
	/// ====================================================================================
	/// testmesh 2 
	/// ====================================================================================

	testMesh2.shader.Enable();

	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, testMesh2.disp1.handle );
	glActiveTexture( GL_TEXTURE1 );
	glBindTexture( GL_TEXTURE_2D, testMesh2.disp2.handle );
	glActiveTexture( GL_TEXTURE2 );
	glBindTexture( GL_TEXTURE_2D, testMesh2.dispF.handle );
	

	glBindVertexArray( testMesh2.vao );

	glPatchParameteri( GL_PATCH_VERTICES, 3 );
	glDrawArrays( GL_PATCHES, 0, 6 );

	glBindVertexArray( 0 );

	
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, 0 );
	glActiveTexture( GL_TEXTURE1 );
	glBindTexture( GL_TEXTURE_2D, 0 );
	glActiveTexture( GL_TEXTURE2 );
	glBindTexture( GL_TEXTURE_2D, 0 );
	
	testMesh2.shader.Disable();


	SwapBuffers( application->hDC );
	CountFPS();
}

//-----------------------------------
//	CountFPS()
//-----------------------------------
void vsGameLocal::CountFPS( void ) {
	static long lastTime = GetTickCount();
	static long curTime = GetTickCount();
	static float curFps = 0.0f;

	++curFps;

	if ( ( curTime = GetTickCount() ) >= lastTime + 1000 ) {
		lastTime = curTime;
		fps = curFps;
		deltaTime = 1.0f / fps;
		curFps = 0.0f;
	}
}

//-----------------------------------
//	CountFPS()
//-----------------------------------
void vsGameLocal::LoadResources( const char* szResourceDataBase ) {
	FILE	*f;
	char	line[ 512 ], buf[ 512 ];
	int		num, i;

	if ( fopen_s( &f, szResourceDataBase, "r" ) ) {
		vsLogger::Log( MSG_ERROR, "Resource database ( %s ) not found.", szResourceDataBase );
		return;
	}

	while ( !feof( f ) ) {
		fgets( line, 512, f );

		if ( strstr( line, "numTextures" ) ) {
			sscanf_s( line, "numTextures\t%d", &num );
			resources.textures.Resize( num );
		} else
		if ( strstr( line, "numShaders" ) ) {
			sscanf_s( line, "numShaders\t%d", &num );
			resources.shaders.Resize( num );
		} else
		/*if ( strstr( line, "numAnimations" ) ) {
			sscanf_s( line, "numAnimations\t%d", &num );
			resources.animations.Resize( num );
		} else
		if ( strstr( line, "numModels" ) ) {
			sscanf_s( line, "numModels\t%d", &num );
			resources.models.Resize( num );
		} else
		if ( strstr( line, "numSounds" ) ) {
			sscanf_s( line, "numSounds\t%d", &num );
			resources.sounds.Resize( num );
		} else*/
		if ( strstr( line, "textures {" ) ) {
			for ( i = 0; i < resources.textures.Length(); ++i ) {
				fscanf_s( f, "\t%s\t\"%s\"", line, 512, buf, 512 );
				buf[ strlen( buf ) - 1 ] = '\0';
				resources.textures[ i ] = vsTexture::LoadTexture( line, buf );
				vsLogger::Log( "Resource loaded: [ texture ] %s", buf );
			}
		} else
		if ( strstr( line, "materials {" ) ) {
				fscanf_s( f, "\tlibrary\t\"%s\"",  buf, 512 );
				buf[ strlen( buf ) - 1 ] = '\0';
				materialLibrary = new vsMaterialLibrary( buf );
		} else
		if ( strstr( line, "shaders {" ) ) {
			for ( i = 0; i < resources.shaders.Length(); ++i ) {
				fscanf_s( f, "\t%s\t\"%s\"", line, 512, buf, 512 );
				buf[ strlen( buf ) - 1 ] = '\0';
				resources.shaders[ i ].LoadFromFile( line, buf );
				vsLogger::Log( "Resource loaded: [ shader ] %s", buf );
			}
		}/* else
		if ( strstr( line, "animations {" ) ) {
		} else
		if ( strstr( line, "models {" ) ) {
		} else
		if ( strstr( line, "sounds {" ) ) {
		} */

	}


	fclose( f );
}

//-----------------------------------
//	GetTexture()
//-----------------------------------
const texture_t& vsGameLocal::GetTexture( const char* szName ) {
	for ( int i = 0; i < resources.textures.Length(); ++i )
		if ( strcmp( szName, resources.textures[ i ].name ) == 0 )
			return resources.textures[ i ];
	return vsTexture::nullTexture;
}

//-----------------------------------
//	GetShader()
//-----------------------------------
const vsShader& vsGameLocal::GetShader( const char* szName ) {
	static const vsShader nullShd;

	for ( int i = 0; i < resources.shaders.Length(); ++i )
		if ( strcmp( szName, resources.shaders[ i ].name ) == 0 )
			return resources.shaders[ i ];
	return nullShd;
}