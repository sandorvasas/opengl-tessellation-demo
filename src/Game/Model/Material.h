#ifndef __VS_MATERIAL_H__
#define __VS_MATERIAL_H__

#include "..\..\Rendering\Shader.h"
#include "..\..\Math\Math.h"
#include "..\..\Rendering\Texture.h"
#include "..\..\System\List.h"

using namespace vsTexture;

/*
-----------------------------------------------------
	Material_t
-----------------------------------------------------
*/
typedef struct {
	char		name[ 64 ];
	vsVec3f		ambient;
	vsVec3f		diffuse;
	vsVec3f		specular;
	float		shininess;
	texture_t	diffusemap;
	texture_t	normalmap;
	texture_t	specularmap;
	vsShader	shader;
} Material_t;


/*
-----------------------------------------------------


	vsMaterialLibrary


-----------------------------------------------------
*/
class vsMaterialLibrary {
public:
							vsMaterialLibrary( const char* szFileName );
							~vsMaterialLibrary( void );

	const Material_t*		GetMaterial( const char* szName ) const;

private:
	vsList<Material_t>		materials;
};

extern vsMaterialLibrary * materialLibrary;

#endif