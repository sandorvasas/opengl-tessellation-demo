#pragma once

#include "..\System\System.h"
#include "..\System\List.h"
#include "..\Rendering\Font.h"
#include "..\Rendering\Shader.h"
#include "..\Rendering\Texture.h"
#include "Player.h"
#include "World.h"

using namespace vsPrinter;
using namespace vsTexture;

//-----------------------------------------
//
//	vsGameLocal
//
//-----------------------------------------
class vsGameLocal {
public:
						vsGameLocal( void );
						~vsGameLocal( void );

	void				NewGame( void );
	void				RestoreGame( const char* szRestoreFile );
	void				SaveGame( const char* szSaveFile );
	void				Update( bool_t keys[ 256 ], char mouseButtons );
	void				LoadResources( const char* szResourceDataBase );

	const float&		GetTime( void ) const;
	const float&		GetDeltaTime( void ) const;
	const texture_t&	GetTexture( const char* szName );
	const vsShader&		GetShader( const char* szName );

private:
	void				UpdateShaderVariables( void );
	void				RenderToBuffer( void );
	void				Render( void );
	void				ProcessKeys( bool_t keys[ 256 ], char mouseButtons );
	void				UpdatePhysics( void );
	void				CountFPS( void );

private:
	// variables
	float				fps;
	float				deltaTime;
	float				time;
	font_t				baseFont;

	vsShader			testShader;
	texture_t			testTexture;
	texture_t			normalmap;

	vsWorld*			world;
	vsVec3f				lightPos;

	// RESOURCES	--------
	struct {
		vsList<texture_t>	textures;
		vsList<vsShader>	shaders;
		//vsList<md5Anim_t>	animations;
		//vsList<md5Model_t>	models;
		//vsList<sound_t>		sounds;
	}					resources;


	struct {
		vsList<vsVec3f>	vert;
		unsigned int	vao;
		unsigned int	vbo;
		bool_t			wireframe;
	}					testMesh;

	struct {
		typedef struct { vsVec3f pos; vsVec2f uv; } vertex_t;
		vsList<vertex_t>vert;
		unsigned int	vao;
		unsigned int	vbo;
		bool_t			wireframe;
		texture_t		disp1, disp2, dispF;
		vsShader		shader;
		int				tessLevel;
	}				testMesh2;
};

extern vsGameLocal*		gameLocal;

//-----------------------------------
//	GetTime
//-----------------------------------
inline
const float& vsGameLocal::GetTime( void ) const {
	return time;
}


//-----------------------------------
//	GetDeltaTime
//-----------------------------------
inline
const float& vsGameLocal::GetDeltaTime( void ) const {
	return deltaTime;
}

