#ifndef __VS_RENDERING_H__
#define __VS_RENDERING_H__

#include "..\System\System.h"
#include "..\Math\Math.h"

enum matrixType_t {
	MODELVIEW_MATRIX,
	PROJECTION_MATRIX,
	//TEXTURE_MATRIX
};

#define MATRIX_STACK_SIZE	16


// -----------------------------------------------------
//
//	vsRenderer
//
// -----------------------------------------------------
class vsRenderer {
public:
					vsRenderer( char majorVer, char minorVer );
					~vsRenderer( void );

	void			OrthoMode( bool_t truefalse );

	void			LoadMatrix( const matrixType_t& which, const vsMat4& matrix );
	void			MultiplyMatrix( const matrixType_t& which, const vsMat4& matrix );
	void			PushMatrix( const matrixType_t& which );
	void			PopMatrix( const matrixType_t& which );

	vsMat4&			ModelViewMatrix( void );
	vsMat4&			ProjectionMatrix( void );
	const vsMat4&	ModelViewProjectionMatrix( void );


private:
	vsMat4			modelViewMatrix;
	vsMat4			projectionMatrix;
	vsMat4			mvpMatrix;

	vsMat4			projectionMatrixStack[ MATRIX_STACK_SIZE ];
	vsMat4			modelViewMatrixStack[ MATRIX_STACK_SIZE ];
	unsigned char	projectionMatrixStackLen;
	unsigned char	modelViewMatrixStackLen;

	struct {
		char major, minor;
	}				contextVersion;
};


extern vsRenderer* renderer;


// ------------------------------------------------
//	ModelViewMatrix
// ------------------------------------------------
VS_INLINE vsMat4& vsRenderer::ModelViewMatrix( void )  {
	return modelViewMatrix;
}

// ------------------------------------------------
//	ProjectionMatrix
// ------------------------------------------------
VS_INLINE vsMat4& vsRenderer::ProjectionMatrix( void )  {
	return projectionMatrix;
}

// ------------------------------------------------
//	ModelViewProjectionMatrix
// ------------------------------------------------
VS_INLINE const vsMat4& vsRenderer::ModelViewProjectionMatrix( void ) {
	mvpMatrix = projectionMatrix * modelViewMatrix;
	return mvpMatrix;
}


#endif