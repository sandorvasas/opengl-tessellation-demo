#ifndef __VS_ENTITY_H__
#define __VS_ENTITY_H__

#include <Windows.h>
#include "System.h"

//-----------------------------------------
//
//	vsEntity
//		Base Class
//
//-----------------------------------------
class vsEntity {
public:
					vsEntity( void );
					~vsEntity( void );

	vsEntity&		operator=( const vsEntity& entity );
	bool_t			operator==( const vsEntity& entity );
	bool_t			operator!=( const vsEntity& entity );

public:
	char			name[ 64 ];
};


//-----------------------------------
//	vsEntity
//-----------------------------------
VS_INLINE vsEntity::vsEntity( void ) {
	ZeroMemory( name, 64 );
}


//-----------------------------------
//	~vsEntity
//-----------------------------------
VS_INLINE vsEntity::~vsEntity( void ) {
}

//-----------------------------------
//	operator=
//-----------------------------------
VS_INLINE vsEntity& vsEntity::operator=( const vsEntity& entity ) {
	strcpy_s( this->name, entity.name );
	return *this;
}

//-----------------------------------
//	operator==
//-----------------------------------
VS_INLINE bool_t vsEntity::operator==( const vsEntity& entity ) {
	return !strcmp( entity.name, this->name );
}

//-----------------------------------
//	operator!=
//-----------------------------------
VS_INLINE bool_t vsEntity::operator!=( const vsEntity& entity ) {
	return !( *this == entity );
}


#endif