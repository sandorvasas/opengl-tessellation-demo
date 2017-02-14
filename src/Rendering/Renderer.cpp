#include "Renderer.h"
#include "OpenGL\GLexp.h"

vsRenderer * renderer;

// ------------------------------------------------
//	ctor
// ------------------------------------------------
vsRenderer::vsRenderer( char majorVer, char minorVer ) {
	contextVersion.minor = minorVer;
	contextVersion.major = majorVer;
	projectionMatrixStackLen = 0;
	modelViewMatrixStackLen = 0;
}

// ------------------------------------------------
//	dtor
// ------------------------------------------------
vsRenderer::~vsRenderer( void ) {
}

// ------------------------------------------------
//	OrthoMode
// ------------------------------------------------
void vsRenderer::OrthoMode( bool_t b ) {
	
	if ( contextVersion.major > 2 ) {
		if ( b ) {
			PushMatrix( PROJECTION_MATRIX );
			projectionMatrix.Ortho( 0.0f, 1600.0f, 900.0f, 0.0f, -1.0f, 1.0f );
			LoadMatrix( PROJECTION_MATRIX, projectionMatrix );
		} else {
			PopMatrix( PROJECTION_MATRIX );
		}

	} else {
		if ( b ) {
			glMatrixMode( GL_PROJECTION );
			glPushMatrix();
			glLoadIdentity();
			glOrtho( 0.0f, 1600.0f, 900.0f, 0.0f, -1.0f, 1.0f );
			glPushMatrix();
		} else {
			glPopMatrix();
			glPopMatrix();
			glMatrixMode( GL_MODELVIEW );
		}
	}
}

// ------------------------------------------------
//	LoadMatrix
// ------------------------------------------------
void vsRenderer::LoadMatrix( const matrixType_t& which, const vsMat4& matrix ) {
	switch ( which ) {
	case MODELVIEW_MATRIX:
		if ( contextVersion.major > 2 )
			modelViewMatrix = matrix;
		else
		{
			int mode;
			glGetIntegerv( GL_MATRIX_MODE, &mode );
			glMatrixMode( GL_MODELVIEW );
			glLoadMatrixf( matrix.ToTypePtr() );
			glMatrixMode( mode );
		}
	break;
	case PROJECTION_MATRIX:
		if ( contextVersion.major > 2 )
			projectionMatrix = matrix;
		else
		{
			int mode;
			glGetIntegerv( GL_MATRIX_MODE, &mode );
			glMatrixMode( GL_PROJECTION );
			glLoadMatrixf( matrix.ToTypePtr() );
			glMatrixMode( mode );
		}
	break;
	}
}

// ------------------------------------------------
//	MultiplyMatrix
// ------------------------------------------------
void vsRenderer::MultiplyMatrix( const matrixType_t& which, const vsMat4& matrix ) {
	switch ( which ) {
	case MODELVIEW_MATRIX:
		if ( contextVersion.major > 2 )
			modelViewMatrix *= matrix;
		else
		{
			int mode;
			glGetIntegerv( GL_MATRIX_MODE, &mode );
			glMatrixMode( GL_MODELVIEW );
			glMultMatrixf( matrix.ToTypePtr() );
			glMatrixMode( mode );
		}
	break;
	case PROJECTION_MATRIX:
		if ( contextVersion.major > 2 )
			projectionMatrix *= matrix;
		else
		{
			int mode;
			glGetIntegerv( GL_MATRIX_MODE, &mode );
			glMatrixMode( GL_PROJECTION );
			glMultMatrixf( matrix.ToTypePtr() );
			glMatrixMode( mode );
		}
	break;
	}
}

// ------------------------------------------------
//	PushMatrix
// ------------------------------------------------
void vsRenderer::PushMatrix( const matrixType_t& which ) {
	switch ( which ) {

	case MODELVIEW_MATRIX:
		if ( modelViewMatrixStackLen + 1 < MATRIX_STACK_SIZE ) {
			modelViewMatrixStack[ modelViewMatrixStackLen++ ] = modelViewMatrix;
			modelViewMatrix.LoadIdentity();
		}
	break;

	case PROJECTION_MATRIX:
		if ( projectionMatrixStackLen + 1 < MATRIX_STACK_SIZE ) {
			projectionMatrixStack[ projectionMatrixStackLen++ ] = projectionMatrix;
			projectionMatrix.LoadIdentity();
		}
	break;
	}
}

// ------------------------------------------------
//	PopMatrix
// ------------------------------------------------
void vsRenderer::PopMatrix( const matrixType_t& which ) {
	switch ( which ) {

	case MODELVIEW_MATRIX:
		if ( modelViewMatrixStackLen - 1 >= 0 ) {
			--modelViewMatrixStackLen;
			modelViewMatrix = modelViewMatrixStack[ modelViewMatrixStackLen ];
		}
	break;

	case PROJECTION_MATRIX:
		if ( projectionMatrixStackLen - 1 >= 0 ) {
			--projectionMatrixStackLen;
			projectionMatrix = projectionMatrixStack[ projectionMatrixStackLen ];
		}
	break;
	}
}