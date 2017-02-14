#include "World.h"
#include "..\Rendering\OpenGL\GLexp.h"
#include "..\Math\Math.h"
#include "GameLocal.h"
#include "..\Rendering\Renderer.h"

//-----------------------------------
//	vsWorld()
//-----------------------------------
vsWorld::vsWorld( void ) {
	CreateSkybox( NULLVEC3F, 10000.0f );
}

//-----------------------------------
//	~vsWorld()
//-----------------------------------
vsWorld::~vsWorld( void ) {
}

//-----------------------------------
//	UpdatePhysics()
//-----------------------------------
void vsWorld::UpdatePhysics( void ) {
}

//-----------------------------------
//	Render()
//-----------------------------------
void vsWorld::Render( void ) {
	RenderSkybox();
}

//-----------------------------------
//	CreateSkybox()
//-----------------------------------
void vsWorld::CreateSkybox( const vsVec3f& offset, float size ) {
	float vertices[ 36 ][ 5 ] = {
		{ offset.x - size, offset.y - size, offset.z - size, 0.25f, 0.50f },
		{ offset.x + size, offset.y - size, offset.z - size, 0.50f, 0.50f },
		{ offset.x + size, offset.y - size, offset.z + size, 0.50f, 0.75f },
		{ offset.x - size, offset.y - size, offset.z - size, 0.25f, 0.50f },
		{ offset.x + size, offset.y - size, offset.z + size, 0.50f, 0.75f },
		{ offset.x - size, offset.y - size, offset.z + size, 0.25f, 0.75f },

		{ offset.x - size, offset.y + size, offset.z - size, 0.25f,  0.0f },
		{ offset.x + size, offset.y + size, offset.z - size, 0.50f,  0.0f },
		{ offset.x + size, offset.y + size, offset.z + size, 0.50f,  0.25f },
		{ offset.x - size, offset.y + size, offset.z - size, 0.25f,  0.0f },
		{ offset.x + size, offset.y + size, offset.z + size, 0.50f,  0.25f },
		{ offset.x - size, offset.y + size, offset.z + size, 0.25f,  0.25f },

		{ offset.x - size, offset.y - size, offset.z + size, 0.25f, 0.50f },
		{ offset.x + size, offset.y - size, offset.z + size, 0.50f, 0.50f },
		{ offset.x + size, offset.y + size, offset.z + size, 0.50f, 0.25f },
		{ offset.x - size, offset.y - size, offset.z + size, 0.25f, 0.50f },
		{ offset.x + size, offset.y + size, offset.z + size, 0.50f, 0.25f },
		{ offset.x - size, offset.y + size, offset.z + size, 0.25f, 0.25f },

		{ offset.x - size, offset.y - size, offset.z - size, 0.25f, 0.75f },
		{ offset.x + size, offset.y - size, offset.z - size, 0.00f, 0.75f },
		{ offset.x + size, offset.y + size, offset.z - size, 0.00f, 0.50f },
		{ offset.x - size, offset.y - size, offset.z - size, 0.25f, 0.75f },
		{ offset.x + size, offset.y + size, offset.z - size, 0.00f, 0.50f },
		{ offset.x - size, offset.y + size, offset.z - size, 0.25f, 0.50f },

		{ offset.x - size, offset.y - size, offset.z - size, 0.00f, 0.50f },
		{ offset.x - size, offset.y + size, offset.z - size, 0.00f, 0.25f },
		{ offset.x - size, offset.y + size, offset.z + size, 0.25f, 0.25f },
		{ offset.x - size, offset.y - size, offset.z - size, 0.00f, 0.50f },
		{ offset.x - size, offset.y + size, offset.z + size, 0.25f, 0.25f },
		{ offset.x - size, offset.y - size, offset.z + size, 0.25f, 0.50f },

		{ offset.x + size, offset.y - size, offset.z - size, 0.25f, 0.25f },
		{ offset.x + size, offset.y + size, offset.z - size, 0.25f, 0.f },
		{ offset.x + size, offset.y + size, offset.z + size, 0.00f, 0.f },
		{ offset.x + size, offset.y - size, offset.z - size, 0.25f, 0.25f },
		{ offset.x + size, offset.y + size, offset.z + size, 0.00f, 0.f },
		{ offset.x + size, offset.y - size, offset.z + size, 0.00f, 0.25f },
	};


	skybox.texture = gameLocal->GetTexture( "skybox" ).handle;
	skybox.shader = gameLocal->GetShader( "passthru" );

	glGenVertexArrays( 1, &skybox.vao );
	glBindVertexArray( skybox.vao );

	glGenBuffers( 1, &skybox.vertexBuffer );
	glBindBuffer( GL_ARRAY_BUFFER, skybox.vertexBuffer );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

	glEnableVertexAttribArray( 0 );
	glEnableVertexAttribArray( 1 );

	glVertexAttribPointer( 0, 3, GL_FLOAT, false, 5 * sizeof( float ), 0 );
	glVertexAttribPointer( 1, 3, GL_FLOAT, false, 5 * sizeof( float ), ( const void * ) ( 3 * sizeof( float ) ) );

	glBindVertexArray( 0 );
}

//-----------------------------------
//	RenderSkybox()
//-----------------------------------
void vsWorld::RenderSkybox( void ) {

	skybox.shader.Enable();
	skybox.shader.UniformMatrix4fv( 0, renderer->ModelViewProjectionMatrix().ToTypePtr() );
	
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, skybox.texture );


	glBindVertexArray( skybox.vao );
	glDrawArrays( GL_TRIANGLES, 0, 36 );
	glBindVertexArray( skybox.vao );

	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, 0 );


	skybox.shader.Disable();
}