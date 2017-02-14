#ifndef __VS_MODELMANAGER_H__
#define __VS_MODELMANAGER_H__

/*
-----------------------------------------------------


	vsModelManager


-----------------------------------------------------
*/

class vsModelManager {
public:
							vsModelManager( void );
							~vsModelManager( void );

	void					LoadSampleModel( const char* szName, const char* szFileName );
	void					LoadAnimation( const char* szName, const char* szFileName );
	vsMD5Model*				NewModelInstance( const char* szSampleName, const char* szName = NULL ); // if szName == NULL, new instance's name becomes <sampleName><instance_id>
	const vsMD5Anim*		GetAnimation( const char* szName ) const;			

private:
	vsList<vsMD5Model*>		sampleModels;
	vsList<vsMD5Model*>		models;
	vsList<vsMD5Anim*>		animations;
};

extern vsModelManager * modelManager;

#endif