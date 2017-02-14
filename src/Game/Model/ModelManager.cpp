#include "ModelManager.h"


 vsModelManager * modelManager;

 //-----------------------------------
//	ctor
//-----------------------------------
vsModelManager::vsModelManager( void ) {
	
}

//-----------------------------------
//	dtor
//-----------------------------------
vsModelManager::~vsModelManager( void ) {
	int i;

	if ( animations.Length() > 0 )
		for ( i = 0; i < animations.Length(); ++i )
			delete animations[ i ];
	animations.Clear();

	if ( sampleModels.Length() > 0 )
		for ( i = 0; i < sampleModels.Length(); ++i )
			delete sampleModels[ i ];
	sampleModels.Clear();

	if ( models.Length() > 0 )
		for ( i = 0; i < models.Length(); ++i )
			delete models[ i ];
	models.Clear();
}

//-----------------------------------
//	LoadSampleModel
//-----------------------------------
void vsModelManager::LoadSampleModel( const char* szName, const char* szFileName ) {
	sampleModels.Append ( new vsMD5Model( szName, szFileName ) );
}

//-----------------------------------
//	LoadAnimation
//-----------------------------------
void vsModelManager::LoadAnimation( const char* szName, const char* szFileName ) {
	animations.Append( new vsMD5Animation( szName, szFileName ) );
}

//-----------------------------------
//	NewModelInstance
//-----------------------------------
vsMD5Model* vsModelManager::NewModelInstance( const char* szSampleName, const char* szName ) {
	// gets ample model and copy it to new model, append new model to models list
}

//-----------------------------------
//	GetAnimation
//-----------------------------------
const vsMD5Animation* vsModelManager::GetAnimation( const char* szName ) const {
	
}

