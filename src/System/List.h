#ifndef __VS_LIST_H__
#define __VS_LIST_H__

#include <Windows.h>
#include "System.h"


template < class T >
class vsList {
public:
					vsList( void );
					vsList( int len );
					~vsList( void );

	T&				operator[]( int i );
	const T&		operator[]( int i ) const;
	const bool_t&	operator==( vsList< T > b ) const;
	const bool_t&	operator!=( vsList< T > b ) const;

	const T*		List( void ) const;
	const int&		Length( void ) const;

	void			CopyTo( vsList< T >& list );
	void			MakeIdentical( vsList< T >& list );
	void			Resize( int len );
	void			Clear( void );
	void			Append( const T& elem );
	int				Find( const T& elem );
	void			Insert( const T& elem, int at );


private:
	T*				list;
	int				len;
};

//-----------------------------------
//	ctor
//-----------------------------------
template < class T >
VS_INLINE 
vsList< T >::vsList( void ) {
	len = 0;
	list = NULL;
}

//-----------------------------------
//	ctor
//-----------------------------------
template < class T >
VS_INLINE 
vsList< T >::vsList( int len ) {
	Resize( len );
}

//-----------------------------------
//	dtor
//-----------------------------------
template < class T >
VS_INLINE 
vsList< T >::~vsList( void ) {
	Clear();
}

//-----------------------------------
//	operator[]
//-----------------------------------
template < class T >
VS_INLINE 
T& vsList< T >::operator[]( int i ) {
	static T* err = NULL;

	if ( i < len && i >= 0 )
		return list[ i ];
	else
		return *err;
}

//-----------------------------------
//	operator[]
//-----------------------------------
template < class T >
VS_INLINE 
const T& vsList< T >::operator[]( int i ) const {
	const static T* err = NULL;

	if ( i < len && i >= 0 )
		return list[ i ];
	else
		return *err;
}

//-----------------------------------
//	CopyTo
//-----------------------------------
template < class T >
VS_INLINE 
void vsList< T >::CopyTo( vsList< T >& b ) {
	if ( len <= 0 )
		return;
	b.Clear();

	b.Resize( len );
	for ( int i = 0; i < b.len; ++i )
		b.list[ i ] = list[ i ];
}

//-----------------------------------
//	MakeIdentical
//-----------------------------------
template < class T >
VS_INLINE 
void vsList< T >::MakeIdentical( vsList< T >& b ) {
	if ( len <= 0 )
		return;
	b.Clear();
	b.len = len;
	b.list = list;
}

//-----------------------------------
//	operator==
//-----------------------------------
template < class T >
VS_INLINE 
const bool_t& vsList< T >::operator==( vsList< T > b ) const {
	if ( len != b.len )
		return false;

	for ( int i = 0; i < b.len; ++i )
		if ( list[ i ] != b.list[ i ] )
			return false;

	return true;
}

//-----------------------------------
//	operator!=
//-----------------------------------
template < class T >
VS_INLINE 
const bool_t& vsList< T >::operator!=( vsList< T > b ) const {
	return !( *this == b );
}

//-----------------------------------
//	Length
//-----------------------------------
template < class T >
VS_INLINE 
const int& vsList< T >::Length( void ) const {
	return len;
}

//-----------------------------------
//	Length
//-----------------------------------
template < class T >
VS_INLINE 
const T* vsList< T >::List( void ) const {
	return list;
}

//-----------------------------------
//	Resize
//-----------------------------------
template < class T >
VS_INLINE 
void vsList< T >::Resize( int len ) {
	if ( len <= 0 )
		return;

	if ( this->len == 0 ) {
		this->len = len;
		list = new T[ len ];
	}
	else
	if ( this->len > 0 ) {
		int L = ( this->len < len )? this->len : len;
		T* newArray = new T[ len ];
		int i;

		for ( i = 0; i < L; ++i )
			newArray[ i ] = list[ i ];

		this->len = len;

		delete [] list;
		list = newArray;
	}
}

//-----------------------------------
//	Clear
//-----------------------------------
template < class T >
VS_INLINE 
void vsList< T >::Clear( void ) {
	if ( len > 0 ) {
		delete [] list;
		list = NULL;
		len = 0;
	}
}

//-----------------------------------
//	Append
//-----------------------------------
template < class T >
VS_INLINE 
void vsList< T >::Append( const T& elem ) {
	Resize( len + 1 );
	list[ len - 1 ] = elem;
}

//-----------------------------------
//	Find
//-----------------------------------
template < class T >
VS_INLINE 
int vsList< T >::Find( const T& elem ) {
	for ( int i = 0; i < len; ++i )
		if ( elem == list[ i ] )
			return i;

	return -1;
}

//-----------------------------------
//	Insert
//-----------------------------------
template < class T >
VS_INLINE 
void vsList< T >::Insert( const T& elem, int at ) {
	Resize( len + 1 );

	for ( int i = len - 1; i > at; --i )
		list[ i ] = list[ i - 1 ];

	list[ at ] = elem;
}

#endif