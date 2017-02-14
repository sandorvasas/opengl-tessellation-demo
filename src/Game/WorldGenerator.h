#ifndef __VS_WORLD_GENERATOR_H__
#define __VS_WORLD_GENERATOR_H__

#include "..\Math\Math.h"

// basic voxel types ----
typedef enum {
	AIR = 0,
	SOIL,
	GRASS,
	ROCK,
	WATER
} voxelType_t;

/*
=======================================================================


	vsWorldGenerator


=======================================================================
*/
class vsWorldGenerator {
public:
							vsWorldGenerator( void );						// Initialization
							~vsWorldGenerator( void );

	voxelType_t				GetVoxelTypeAtCoords( const vsVec3lli& coords );


private:
	//vsNoise				noise3d;
};

extern vsWorldGenerator * worldGenerator;

#endif