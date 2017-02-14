#include "Player.h"
#include "GameLocal.h"
#include "..\Application.h"
#include <Windows.h>
#include "..\Rendering\OpenGL\GLexp.h"
#include "..\Rendering\Renderer.h"

vsPlayer* player;


//-----------------------------------
//	vsPlayer
//-----------------------------------
vsPlayer::vsPlayer( void ) {
	maxHealth = 100.0f;
	health = maxHealth;
	jumpHeight = 1.0f;
	jumpDuration = 1.0f;
	walkingSpeed = 5.0f;
	runningSpeed = 12.0f;

	ZeroMemory( &states, sizeof( unsigned char ) );
	states.spawned = false;
	states.spectating = false;

	angles = origin = deltaShift = NULLVEC3F;
}

//-----------------------------------
//	~vsPlayer
//-----------------------------------
vsPlayer::~vsPlayer( void ) {
	
}

//-----------------------------------
//	UpdateAxis
//-----------------------------------
void vsPlayer::UpdateRotation( void ) {
	POINT p;
	vsVec2i delta;

	GetCursorPos( &p );

	delta.x = p.x - application->GetResolution().center.x;
	delta.y = p.y - application->GetResolution().center.y;

	angles.x += delta.y * application->GetMouseSpeed();
	angles.y += delta.x * application->GetMouseSpeed();

	if ( angles.x > 90.0f  ) angles.x = 90.0f;
	if ( angles.x < -90.0f ) angles.x = -90.0f;
	if ( angles.y > 360.0f ) angles.y -= 360.0f;
	if ( angles.y <-360.0f ) angles.y += 360.0f;

	SetCursorPos( application->GetResolution().center.x, application->GetResolution().center.y );
}

//-----------------------------------
//	Look
//-----------------------------------
void vsPlayer::Look( void ) {
	vsMat4 m, t;
	vsMat3 m3;
	vsQuaternion qx, qy;

	qx.CreateFromEulerAnglesDEG( angles.x, 0.0f, 0.0f );
	qy.CreateFromEulerAnglesDEG( 0.0f, angles.y, 0.0f );
	//qz.CreateFromEulerAnglesDEG( 0.0f, 0.0f, angles.z );

	axis = ( qx * qy ).ToMat3();

	m = axis.ToMat4();
	t.Translate( -origin );

	renderer->LoadMatrix( MODELVIEW_MATRIX, m * t );

	eyeDirection.x = axis[ 6 ];
	eyeDirection.z = -axis[ 8 ];
	eyeDirection.y = qx.ToMat3()[ 7 ];

	m3 = qy.ToMat3();
	xzDirection.x = m3[ 6 ];
	xzDirection.z = -m3[ 8 ];
	xzDirection.y = 0.0f;
}

//-----------------------------------
//	SetMoveDirection
//-----------------------------------
void vsPlayer::SetMoveDirection( int directions ) {
	vsVec3f dir = ( states.spectating ) ? eyeDirection : xzDirection;
	deltaShift = NULLVEC3F;

	if ( directions & PLAYER_MOVE_FORWARD )
		deltaShift += dir;

	if ( directions & PLAYER_MOVE_BACKWARD )
		deltaShift -= dir;

	if ( directions & PLAYER_MOVE_LEFT )
		deltaShift -= xzDirection.GetOrthoXZ();

	if ( directions & PLAYER_MOVE_RIGHT )
		deltaShift += xzDirection.GetOrthoXZ();

	if ( directions & PLAYER_MOVE_UP )
		deltaShift.y += 1.0f;

	if ( directions & PLAYER_MOVE_DOWN )
		deltaShift.y -= 1.0f;

	if ( deltaShift != NULLVEC3F ) {
		deltaShift.Normalize();
		deltaShift *= ( states.running ? runningSpeed : walkingSpeed ) * gameLocal->GetDeltaTime();
	}
}

//-----------------------------------
//	MoveToDestination
//-----------------------------------
void vsPlayer::MoveToDestination( void ) {
	origin += deltaShift;
	deltaShift = NULLVEC3F;
}

//-----------------------------------
//	SetAngles
//-----------------------------------
void vsPlayer::SetAngles( const float& rx, const float& ry, const float& rz ) {
	angles = vsVec3f( rx, ry, rz );
}

//-----------------------------------
//	ChangeAngles
//-----------------------------------
void vsPlayer::ChangeAngles( const float& rx, const float& ry, const float& rz ) {
	angles += vsVec3f( rx, ry, rz );
}


//-----------------------------------
//	GetAnglesMatrix3
//-----------------------------------
/*const vsMat3& vsPlayer::GetAnglesMatrix3( void ) const {
	return axis.ToMat3();
}

//-----------------------------------
//	GetAnglesMatrix4
//-----------------------------------
const vsMat4& vsPlayer::GetAnglesMatrix4( void ) const {
	return axis.ToMat3().ToMat4();
}

//-----------------------------------
//	GetAnglesVector3
//-----------------------------------
const vsVec3f& vsPlayer::GetAnglesVector3( void ) const {
	return NULLVEC3;
}*/

