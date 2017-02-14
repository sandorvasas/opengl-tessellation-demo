#ifndef __VS_WORLD_H__
#define __VS_WORLD_H__

#include "..\Math\Math.h"
#include "Chunk.h"
#include "..\Rendering\Shader.h"


// -----------------------------------------------
//
//	vsWorld
//
// -----------------------------------------------
class vsWorld {
	friend class vsGameLocal;
public:
						vsWorld( void );
						~vsWorld( void );

	void				UpdatePhysics( void );
	void				Render( void );

private:
	void				CreateSkybox( const vsVec3f& offset, float size );
	void				RenderSkybox( void );

private:
	struct {
		unsigned int	vertexBuffer,
						vao,
						texture;
		vsShader		shader;
		
	}					skybox;

	vsList<vsChunk*>	chunks;
};

#endif