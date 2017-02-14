#ifndef __VS_WATER_H__
#define __VS_WATER_H__

#include "..\Math\Math.h"
#include "..\Rendering\Shader.h"
#include "..\Rendering\Texture.h"
#include "..\System\Entity.h"
#include "..\System\List.h"

using namespace vsTexture;

//-----------------------------------------
//
//	vsWater
//
//-----------------------------------------
class vsWater : public vsEntity {
public:
						vsWater( const vsVec3f& start, const vsVec3f& end );
						~vsWater( void );

	void				UpdatePhysics( void );
	void				Render( void );
	void				SetWind( const vsVec3f& wind );

private:
	void				GenerateGeometry( void );
	void				GenerateQuadTree( void );
private:
	vsVec3f				start;
	vsVec3f				end;
	vsShader			shader;
	texture_t			textures[ 2 ];
	vsVec3f				wind;
	vsList<unsigned int>indices;
};

#endif