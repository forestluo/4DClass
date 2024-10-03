///////////////////////////////////////////////////////////////////////////////
//
// 4DMatrix4.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _4D_MATRIX4_H_
#define _4D_MATRIX4_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DQuaternion.h"

///////////////////////////////////////////////////////////////////////////////
//
// Declaration
//
///////////////////////////////////////////////////////////////////////////////

class C4DQuaternion;

///////////////////////////////////////////////////////////////////////////////
//
// 4DMatrix4
//
///////////////////////////////////////////////////////////////////////////////

class C4DMatrix4
{
private:
	//Values
	_FLOAT44 values;

public:
	C4DMatrix4(void);
	C4DMatrix4(const _FLOAT* floats);
	C4DMatrix4(const C4DMatrix4& matrix4);
	C4DMatrix4(_FLOAT _11,_FLOAT _12,_FLOAT _13,_FLOAT _14,
			   _FLOAT _21,_FLOAT _22,_FLOAT _23,_FLOAT _24,
			   _FLOAT _31,_FLOAT _32,_FLOAT _33,_FLOAT _34,
			   _FLOAT _41,_FLOAT _42,_FLOAT _43,_FLOAT _44);
	virtual ~C4DMatrix4(void);

	_FLOAT _11();
	_FLOAT _11(_FLOAT value);
	_FLOAT _12();
	_FLOAT _12(_FLOAT value);
	_FLOAT _13();
	_FLOAT _13(_FLOAT value);
	_FLOAT _14();
	_FLOAT _14(_FLOAT value);

	_FLOAT _21();
	_FLOAT _21(_FLOAT value);
	_FLOAT _22();
	_FLOAT _22(_FLOAT value);
	_FLOAT _23();
	_FLOAT _23(_FLOAT value);
	_FLOAT _24();
	_FLOAT _24(_FLOAT value);

	_FLOAT _31();
	_FLOAT _31(_FLOAT value);
	_FLOAT _32();
	_FLOAT _32(_FLOAT value);
	_FLOAT _33();
	_FLOAT _33(_FLOAT value);
	_FLOAT _34();
	_FLOAT _34(_FLOAT value);

	_FLOAT _41();
	_FLOAT _41(_FLOAT value);
	_FLOAT _42();
	_FLOAT _42(_FLOAT value);
	_FLOAT _43();
	_FLOAT _43(_FLOAT value);
	_FLOAT _44();
	_FLOAT _44(_FLOAT value);

	void identity();

	void transpose();
	C4DMatrix4 transpose() const;

	void inverse();
	C4DMatrix4 inverse() const;

	void xRotate(_FLOAT angle);
	void yRotate(_FLOAT angle);
	void zRotate(_FLOAT angle);
	void scale(_FLOAT sx,_FLOAT sy,_FLOAT sz);
	void rotate(const C4DQuaternion& rotation);
	void translate(_FLOAT dx,_FLOAT dy,_FLOAT dz);

    _FLOAT& operator () (_INTEGER row,_INTEGER col);
    _FLOAT operator () (_INTEGER row,_INTEGER col) const;

    operator _FLOAT* ();
    operator const _FLOAT* () const;

    C4DMatrix4& operator *= (const C4DMatrix4& matrix4);
    C4DMatrix4& operator += (const C4DMatrix4& matrix4);
    C4DMatrix4& operator -= (const C4DMatrix4& matrix4);
    C4DMatrix4& operator *= (_FLOAT value);
    C4DMatrix4& operator /= (_FLOAT value);

    C4DMatrix4 operator + () const;
    C4DMatrix4 operator - () const;

    C4DMatrix4 operator * (const C4DMatrix4& matrix4) const;
    C4DMatrix4 operator + (const C4DMatrix4& matrix4) const;
    C4DMatrix4 operator - (const C4DMatrix4& matrix4) const;
    C4DMatrix4 operator * (_FLOAT value) const;
    C4DMatrix4 operator / (_FLOAT value) const;

    _BOOL operator == (const C4DMatrix4& matrix4) const;
    _BOOL operator != (const C4DMatrix4& matrix4) const;

    friend C4DMatrix4 operator * (_FLOAT value,const C4DMatrix4& matrix4);
	friend C4DVector3 operator * (const C4DVector3& vector,const C4DMatrix4& matrix4);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_4D_MATRIX4_H_