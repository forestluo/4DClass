///////////////////////////////////////////////////////////////////////////////
//
// 4DVector3.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _4D_VECTOR3_H_
#define _4D_VECTOR3_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DType.h"

///////////////////////////////////////////////////////////////////////////////
//
// 4DVector3
//
///////////////////////////////////////////////////////////////////////////////

class C4DVector3
{
private:
	//Values
	_FLOAT3 values;

public:
	C4DVector3(void);
	C4DVector3(const _FLOAT* floats);
	C4DVector3(const C4DVector3& vector3);
	C4DVector3(_FLOAT x,_FLOAT y,_FLOAT z);
	virtual ~C4DVector3(void);

	_FLOAT& x();
	_FLOAT x() const;
	_FLOAT& y();
	_FLOAT y() const;
	_FLOAT& z();
	_FLOAT z() const;

	_FLOAT length() const;

	C4DVector3& normalize();
	C4DVector3 normalize() const;

	float dot(const C4DVector3& vector3) const;
	static float dot(const C4DVector3& v1,const C4DVector3& v2);

	C4DVector3 cross(const C4DVector3& vector3) const;
	static C4DVector3 cross(const C4DVector3& v1,const C4DVector3& v2);

	_FLOAT& operator [] (_INTEGER index);
	_FLOAT operator [] (_INTEGER index) const;

    operator _FLOAT* ();
    operator const _FLOAT* () const;

    C4DVector3& operator += (const C4DVector3& vector3);
    C4DVector3& operator -= (const C4DVector3& vector3);
    C4DVector3& operator *= (_FLOAT value);
    C4DVector3& operator /= (_FLOAT value);

    C4DVector3 operator + () const;
    C4DVector3 operator - () const;

    C4DVector3 operator + (const C4DVector3& vector3) const;
    C4DVector3 operator - (const C4DVector3& vector3) const;
    C4DVector3 operator * (_FLOAT value) const;
    C4DVector3 operator / (_FLOAT value) const;

    _BOOL operator == (const C4DVector3& vector3) const;
    _BOOL operator != (const C4DVector3& vector3) const;

	friend C4DVector3 operator * (_FLOAT value,const C4DVector3& vector3);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_4D_VECTOR3_H_