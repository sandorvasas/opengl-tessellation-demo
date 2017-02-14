#ifndef __VS_CHUNK_H__
#define __VS_CHUNK_H__

#include "..\System\List.h"
#include "..\Math\Math.h"

#define CHUNK_SIZE_X	64
#define CHUNK_SIZE_Z	64
#define CHUNK_SIZE_Y	64
#define CHUNK_SCALE		10.0f


enum CHUNK_NEIGHBORS {
	TOP = 0,
	BOTTOM,
	LEFT,
	RIGHT,
	FRONT,
	BACK
};

// ------------------------------------------------
//	chunkVertex_t
// ------------------------------------------------
typedef struct {
	vsVec3f			position;
	vsVec3f			normal;
	vsVec3f			tangent;
	vsVec2f			texCoords;
} chunkVertex_t;

// ------------------------------------------------
//	chunkNode_t
// ------------------------------------------------
enum { NODE_LEAF = 1, NODE_BRANCH };
typedef struct chunkNode_s{
	int				type;

	chunkNode_s*	nodes[ 8 ];
} chunkNode_t;

// ------------------------------------------------
//
//	vsChunk
//
// ------------------------------------------------
class vsChunk {
public:
							vsChunk( const vsVec3li& chunkOffset );
							~vsChunk( void );

	void					SetChunkOffset( const vsVec3li& chunkOffset );
	void					Generate( void );
	void					SaveToFile( void );
	void					RestoreFromFile( void );
	void					Render( void );

private:
	chunkNode_t				octree;

	vsVec3f					realOffset;					// [realOffset]  = floats
	vsVec3lli				worldOffset;				// [worldOffset] = blocks
	vsVec3li				chunkOffset;				// [chunkOffset] = chunks
	char					voxels[ CHUNK_SIZE_X ][ CHUNK_SIZE_Y ][ CHUNK_SIZE_Z ];

	vsList<chunkVertex_t>	vertices;
	vsList<unsigned int>	indices;

	unsigned int			vbo[ 2 ];
	unsigned int			vao;
};



#endif