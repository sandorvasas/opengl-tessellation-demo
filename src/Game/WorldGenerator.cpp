#include "WorldGenerator.h"


extern vsWorldGenerator * worldGenerator;

//---------------------------------------
//	GetVoxelTypeAtCoords
//---------------------------------------
voxelType_t vsWorldGenerator::GetVoxelTypeAtCoords( const vsVec3lli& coords ) {

	float height = ( vsMath::Sin( coords.x * 0.01f ) + vsMath::Cos( coords.z * 0.01f ) ) * 10.0;

	if ( coords.y > ( int )height )
		return AIR;

	return SOIL;
}
