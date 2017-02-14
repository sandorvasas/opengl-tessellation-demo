#include "MD5.h"


//-----------------------------------
//	ctor1
//-----------------------------------
vsMD5Model::vsMD5Model( const char* szName, const char* szFileName ) {
	animation.current.time = 0.f;
	animation.current.anim = NULL;
	animation.next.time = 0.f;
	animation.next.anim = NULL;
	animation.blendTime = 0.0f;
}

//-----------------------------------
//	ctor2
//-----------------------------------
vsMD5Model::vsMD5Model( const vsMD5Model& model ) {
	
}

//-----------------------------------
//	dtor
//-----------------------------------
vsMD5Model::~vsMD5Model( void ) {
	
}

//-----------------------------------
//	Render
//-----------------------------------
void vsMD5Model::Render( const float& deltaTime ) {
	
}

//-----------------------------------
//	Render
//-----------------------------------							
void vsMD5Model::Render( void ) {
	
}

//-----------------------------------
//	SetAnimation
//-----------------------------------	
void vsMD5Model::SetAnimation( const vsMD5Animation* anim, float blendTime ) {
	
}

//-----------------------------------
//	Animate
//-----------------------------------
void vsMD5Model::Animate( const float& deltaTime ) {
	
}

//-----------------------------------
//	BuildModel
//-----------------------------------
void vsMD5Model::BuildModel( const MD5Skeleton_t& skeleton ) {
	
}



/*
-----------------------------------------------------


	vsMD5Animation


-----------------------------------------------------
*/
vsMD5Animation::vsMD5Animation( const char* szName, const char* szFileName ) {
	
}

//-----------------------------------
//	BuildModel
//-----------------------------------
vsMD5Animation::~vsMD5Animation( void ) {
	
}

//-----------------------------------
//	BuildModel
//-----------------------------------
void vsMD5Animation::GetFrameBlend( const float& time, MD5FrameBlend_t& frameBlend ) const {
	
}

//-----------------------------------
//	BuildModel
//-----------------------------------
void vsMD5Animation::GetSkeleton( float time, MD5Skeleton_t& skeleton ) const {
	
}

