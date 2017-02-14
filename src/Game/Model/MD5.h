#ifndef __VS_MD5_H__
#define __VS_MD5_H__

#include "..\..\System\Entity.h"
#include "..\..\System\List.h"
#include "..\..\Math\Math.h"
#include "..\..\Boundings\AABB.h"
#include "Material.h"


class vsMD5Animation;
class vsMD5Model;



typedef struct {
	vsVec2f		texCoord;
	int			startWeight;
	int			countWeight;
} MD5Vertex_t;


typedef struct {
	char			name[ 64 ];
	int				parentIndex;
	vsVec3f			pos;
	vsQuaternion	orient;
} MD5Joint_t;


typedef struct {
	vsList<MD5Joint_t>		joints;
} MD5Skeleton_t;


typedef struct {
	unsigned int	a, b, c;
} MD5Triangle_t;


typedef struct {
	int			jointIndex;
	float		bias;
	vsVec3f		position;
} MD5Weight_t;


typedef struct {
	Material_t*					material;
	vsList<MD5Triangle_t>		triangles;
	vsList<MD5Vertex_t>			vert;
	vsList<MD5Weight_t>			weights;
} MD5Mesh_t;


typedef struct {
	int						frame1;
	int						frame2;
	float					lerp;
} MD5FrameBlend_t;


typedef struct {
	const vsMD5Animation*	anim;
	float					time;
} MD5AnimInstance_t;

/*
-----------------------------------------------------


	vsMD5Model


-----------------------------------------------------
*/
class vsMD5Model : public vsEntity {
public:
								vsMD5Model( const char* szName, const char* szFileName );
		explicit				vsMD5Model( const vsMD5Model& model );
								~vsMD5Model( void );

		void					Render( const float& deltaTime );							// own deltaTime - not sure about its usefullness.
		void					Render( void );												// gets deltaTime from gameLocal

		// transformations
		void					SetOrigin( const vsVec3f& origin );
		void					SetAxis( const vsQuaternion& axis );
		void					SetScale( const vsVec3f& s );
		void					Translate( const vsVec3f& delta );
		void					Rotate( const vsQuaternion& q );
		void					Scale( const vsVec3f& s );
		const vsVec3f&			GetOrigin( void ) const;
		const vsQuaternion&		GetAxis( void ) const;
		const vsVec3f&			GetScale( void ) const;

		// animation-related
		void					SetAnimation( const vsMD5Animation* anim, float blendTime = 1.0f );

private:
		void					Animate( const float& deltaTime );
		void					BuildModel( const MD5Skeleton_t& skeleton );

private:
		vsVec3f					origin;
		vsQuaternion			axis;
		vsVec3f					scale;

		vsList<MD5Joint_t>		joints;
		vsList<MD5Mesh_t>		meshes;
		
		struct {
			MD5AnimInstance_t		current;
			MD5AnimInstance_t		next;
			float					blendTime;				// duration of transition between the two animations
		}	animation;
		
		struct {
			MD5Skeleton_t			bindpose;
			MD5Skeleton_t			current;
		}	skeleton;
};


VS_INLINE void vsMD5Model::SetOrigin( const vsVec3f& origin ) {
	this->origin = origin;
}


VS_INLINE void vsMD5Model::SetAxis( const vsQuaternion& axis ) {
	this->axis = axis;
}


VS_INLINE void vsMD5Model::SetScale( const vsVec3f& s ) {
	scale = s;
}


VS_INLINE void vsMD5Model::Translate( const vsVec3f& delta ) {
	origin += delta;
}


VS_INLINE void vsMD5Model::Rotate( const vsQuaternion& q ) {
	axis *= q;
}


VS_INLINE void vsMD5Model::Scale( const vsVec3f& s ) {
	scale *= s;
}


VS_INLINE const vsVec3f& vsMD5Model::GetOrigin( void ) const {
	return origin;
}


VS_INLINE const vsQuaternion& vsMD5Model::GetAxis( void ) const {
	return axis;
}


VS_INLINE const vsVec3f& vsMD5Model::GetScale( void ) const {
	return scale;
}




// animation  -------------------------------------------------------------

typedef struct {
	vsVec3f			position;
	vsQuaternion	orient;
} MD5JointInfo_t;


typedef struct {
	vsList<float>	components;
} MD5Frame_t;

/*
-----------------------------------------------------


	vsMD5Animation


-----------------------------------------------------
*/
class vsMD5Animation {
public:
									vsMD5Animation( const char* szName, const char* szFileName );
									~vsMD5Animation( void );

	void							GetFrameBlend( const float& time, MD5FrameBlend_t& frameBlend ) const;
	void							GetSkeleton( float time, MD5Skeleton_t& skeleton ) const;
	const float&					GetLength( void ) const;
	const int&						GetFrameRate( void ) const;

private:
	vsList<MD5JointInfo_t>			jointInfos;// dont store! REMOVE  \
	vsList<MD5Frame_t>				frames;	// dont store! REMOVE	 -- only have to store skeletons of frames
	vsList<MD5Skeleton_t>			frameSkeletons;
	vsList<vsBox>					bounds;
	float							length;
	int								frameRate;
};


VS_INLINE const float& vsMD5Animation::GetLength( void ) const {
	return length;
}

VS_INLINE const int& vsMD5Animation::GetFrameRate( void ) const {
	return frameRate;
}

#endif