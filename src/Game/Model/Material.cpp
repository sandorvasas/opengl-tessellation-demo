#include "Material.h"
#include "..\..\System\Logger.h"
#include "..\GameLocal.h"
#include <stdio.h>


vsMaterialLibrary * materialLibrary;

/*
-----------------------------------------------------
	ctor
		Loads materials from library file
-----------------------------------------------------
*/
vsMaterialLibrary::vsMaterialLibrary( const char* szFileName ) {
	FILE * f;

	if ( fopen_s( &f, szFileName, "r" ) ) {
		vsLogger::Log( "Failed to open material library" );
		return;
	}

	char line[ 512 ];
	int	 tmp, current = 0;
	Material_t * mat;

	while ( !feof( f ) ) 
	{
		fgets( line, 512, f );

		if ( strstr( line, "numMaterials" ) ) {
			sscanf_s( line, "numMaterials %d", &tmp );
			materials.Resize( tmp );
		} else
		if ( strstr( line, "material {" ) ) {
			mat = &materials[ current++ ];

			if ( current >= materials.Length() )
				break;

			fscanf_s( f, "\tname %s", mat->name, 64 );

			fscanf_s( f, "\tshader %s", line, 512 );
			mat->shader = gameLocal->GetShader( line );

			fscanf_s( f, "\tdiffusemap %s", line, 512 );
			mat->diffusemap = gameLocal->GetTexture( line );

			fscanf_s( f, "\tnormalmap %s", line, 512 );
			mat->normalmap = gameLocal->GetTexture( line );

			fscanf_s( f, "\tspecularmap %s", line, 512 );
			mat->specularmap = gameLocal->GetTexture( line );

			fscanf_s( f, "\tdiffuse %f %f %f", &mat->diffuse.x, &mat->diffuse.y, &mat->diffuse.z );
			fscanf_s( f, "\tambient %f %f %f", &mat->ambient.x, &mat->ambient.y, &mat->ambient.z );
			fscanf_s( f, "\tspecular %f %f %f", &mat->specular.x, &mat->specular.y, &mat->specular.z );
			fscanf_s( f, "\tshininess %f", &mat->shininess );
		}
	}


	fclose( f );
}

/*
-----------------------------------------------------
	dtor
-----------------------------------------------------
*/
vsMaterialLibrary::~vsMaterialLibrary( void ) {
	materials.Clear();
}

/*
-----------------------------------------------------
	GetMaterial
-----------------------------------------------------
*/
const Material_t* vsMaterialLibrary::GetMaterial( const char* szName ) const {
	for ( int i = 0; i < materials.Length(); ++i )
		if ( strcmp( szName, materials[ i ].name ) == 0 )
			return &materials[ i ];

	return NULL;
}