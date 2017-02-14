#pragma once

#include "..\Math\Math.h"
#include "..\System\Entity.h"
#include "..\Boundings\Frustum.h"


enum {
	PLAYER_MOVE_FORWARD = 1,
	PLAYER_MOVE_BACKWARD= 2,
	PLAYER_MOVE_LEFT	= 4,
	PLAYER_MOVE_RIGHT	= 8,
	PLAYER_MOVE_UP		= 16,
	PLAYER_MOVE_DOWN	= 32
};

typedef struct playerStates_s {
	unsigned	running		: 1;
	unsigned	inAir		: 1;
	unsigned	jumping		: 1;
	unsigned	godMode		: 1;
	unsigned	spectating	: 1;
	unsigned	noClip		: 1;
	unsigned	spawned		: 1;
	unsigned	reserved	: 1;
} playerStates_t;


//-----------------------------------------
//
//	vsPlayer
//
//-----------------------------------------
class vsPlayer : public vsEntity {
public:
						vsPlayer( void );
						~vsPlayer( void );

	void				Spawn( void );
	void				UpdateRotation( void );
	void				Look( void );
	void				SetMoveDirection( int directions );
	void				MoveToDestination( void );

	void				SetMaxHealth( float f );
	void				SetWalkingSpeed( float f );
	void				SetRunningSpeed( float f );
	void				SetJumpHeight( float f );
	void				SetOrigin( const vsVec3f& o );
	//void				SetAngles( const vsQuaternion& q );
	void				SetAngles( const float& rx, const float& ry, const float& rz );
	void				ChangeAngles( const float& rx, const float& ry, const float& rz );

	const vsMat4&		GetAngles( void ) const;
//	const vsMat3&		GetAnglesMatrix3( void ) const;
//	const vsMat4&		GetAnglesMatrix4( void ) const;
//	const vsVec3f&		GetAnglesVector3( void ) const;
	const vsVec3f&		GetOrigin( void ) const;
	const vsVec3f&		GetDeltaShift( void ) const;
	vsVec3f				GetDestination( void ) const;
	const float&		GetHealth( void ) const;

	// state control
	void				Run( void );
	void				Walk( void );
	void				Jump( void );
	void				GodMode( bool_t trusefalse );
	void				Spectate( bool_t truefalse );
	void				NoClip( bool_t truefalse );
	void				Heal( float hp );
	void				Damage( float hp );

	bool_t				IsInAir( void ) const;
	bool_t				IsJumping( void ) const;
	bool_t				IsGodMode( void ) const;
	bool_t				IsRunning( void ) const;
	bool_t				IsClipping( void ) const;
	bool_t				IsDead( void ) const;

public:
	vsFrustum			frustum;
private:
	vsVec3f				origin;
	vsMat3				axis;
	vsVec3f				eyeDirection;
	vsVec3f				xzDirection;
	vsVec3f				angles;
	vsVec3f				deltaShift;

	float				walkingSpeed;
	float				runningSpeed;
	float				jumpHeight;
	float				jumpTime;
	float				jumpDuration;
	playerStates_t		states;

	float				health;
	float				maxHealth;
};


extern vsPlayer * player;


//-----------------------------------
//	Spawn
//-----------------------------------
inline
void vsPlayer::Spawn( void ) {
	states.spawned = true;
}

//-----------------------------------
//	SetMaxHealth
//-----------------------------------
inline
void vsPlayer::SetMaxHealth( float f ) {
	maxHealth = f;
}

//-----------------------------------
//	SetWalkingSpeed
//-----------------------------------
inline 
void vsPlayer::SetWalkingSpeed( float f ) {
	walkingSpeed = f;
}

//-----------------------------------
//	SetRunningSpeed
//-----------------------------------
inline 
void vsPlayer::SetRunningSpeed( float f ) {
	runningSpeed = f;
}

//-----------------------------------
//	SetJumpHeight
//-----------------------------------
inline 
void vsPlayer::SetJumpHeight( float f ) {
	jumpHeight = f;
}

//-----------------------------------
//	SetOrigin
//-----------------------------------
inline 
void vsPlayer::SetOrigin( const vsVec3f& o ) {
	origin = o;
}
/*
//-----------------------------------
//	SetAngles
//-----------------------------------
inline 
void vsPlayer::SetAngles( const vsQuaternion& q ) {
	axis = q;
}

//-----------------------------------
//	GetAngles
//-----------------------------------
inline 
const vsQuaternion& vsPlayer::GetAngles( void ) const {
	return axis;
}
*/
//-----------------------------------
//	GetOrigin
//-----------------------------------
inline 
const vsVec3f& vsPlayer::GetOrigin( void ) const {
	return origin;
}

//-----------------------------------
//	GetDeltaShift
//-----------------------------------
inline 
const vsVec3f& vsPlayer::GetDeltaShift( void ) const {
	return deltaShift;
}

//-----------------------------------
//	GetDestination
//-----------------------------------
inline 
vsVec3f vsPlayer::GetDestination( void ) const {
	return origin + deltaShift;
}

//-----------------------------------
//	GetHealth
//-----------------------------------
inline 
const float& vsPlayer::GetHealth( void ) const {
	return health;
}

//-----------------------------------
//	Run
//-----------------------------------
inline
void vsPlayer::Run( void ) {
	states.running = true;
}

//-----------------------------------
//	Walk
//-----------------------------------
inline
void vsPlayer::Walk( void ) {
	states.running = false;
}

//-----------------------------------
//	Jump
//-----------------------------------
inline
void vsPlayer::Jump( void ) {
	states.jumping = true;
	jumpTime = 0.0f;
}

//-----------------------------------
//	GodMode
//-----------------------------------
inline
void vsPlayer::GodMode( bool_t truefalse ) {
	states.godMode = truefalse;
}

//-----------------------------------
//	Spectate
//-----------------------------------
inline
void vsPlayer::Spectate( bool_t truefalse ) {
	states.spectating = truefalse;
}

//-----------------------------------
//	NoClip
//-----------------------------------
inline
void vsPlayer::NoClip( bool_t truefalse ) {
	states.noClip = truefalse;
}

//-----------------------------------
//	Heal
//-----------------------------------
inline
void vsPlayer::Heal( float hp ) {
	health += hp;
	if ( health > maxHealth )
		health = maxHealth;
}

//-----------------------------------
//	Damage
//-----------------------------------
inline
void vsPlayer::Damage( float hp ) {
	health -= hp;
}

//-----------------------------------
//	IsInAir
//-----------------------------------
inline
bool_t vsPlayer::IsInAir( void ) const {
	return states.inAir;
}

//-----------------------------------
//	IsJumping
//-----------------------------------
inline
bool_t vsPlayer::IsJumping( void ) const {
	return states.jumping;
}

//-----------------------------------
//	IsGodMode
//-----------------------------------
inline
bool_t vsPlayer::IsGodMode( void ) const {
	return states.godMode;
}

//-----------------------------------
//	IsRunning
//-----------------------------------
inline
bool_t vsPlayer::IsRunning( void ) const {
	return states.running;
}

//-----------------------------------
//	IsClipping
//-----------------------------------
inline
bool_t vsPlayer::IsClipping( void ) const {
	return !states.noClip;
}

//-----------------------------------
//	IsDead
//-----------------------------------
inline
bool_t vsPlayer::IsDead( void ) const {
	return health <= 0.0f;
}

