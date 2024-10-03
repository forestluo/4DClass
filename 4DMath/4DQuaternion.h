///////////////////////////////////////////////////////////////////////////////
//
// 4DQuaternion.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _4D_QUATERNION_H_
#define _4D_QUATERNION_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DVector3.h"

///////////////////////////////////////////////////////////////////////////////
//
// Declaration
//
///////////////////////////////////////////////////////////////////////////////

class C4DVector3;

///////////////////////////////////////////////////////////////////////////////
//
// 4DQuaternion
//
///////////////////////////////////////////////////////////////////////////////

class C4DQuaternion
{
private:
	//Values
	_FLOAT4 values;

public:
	C4DQuaternion(void);
	C4DQuaternion(const _FLOAT* floats);
	C4DQuaternion(const C4DQuaternion& quaternion);
	C4DQuaternion(_FLOAT x,_FLOAT y,_FLOAT z,_FLOAT w);
	virtual ~C4DQuaternion(void);

	C4DQuaternion(const C4DVector3& omega);
	C4DQuaternion(const C4DVector3& axis,_FLOAT angle);
	C4DQuaternion(const C4DVector3& v1,const C4DVector3& v2);

	_FLOAT& x();
	_FLOAT x() const;
	_FLOAT& y();
	_FLOAT y() const;
	_FLOAT& z();
	_FLOAT z() const;
	_FLOAT& w();
	_FLOAT w() const;

	_FLOAT length() const;

	void identity();

	C4DQuaternion inverse() const;
	C4DQuaternion reverse() const;
	C4DQuaternion normalize() const;
	C4DQuaternion conjugate() const;

	C4DVector3 eular() const;
	void eular(const C4DVector3& omega);

	C4DVector3 rotate(const C4DVector3& vector3) const;
	void axisRotation(const C4DVector3& vector,_FLOAT angle);

	float dot(const C4DQuaternion& quaternion) const;
	static float dot(const C4DQuaternion& q1,const C4DQuaternion& q2);

	C4DQuaternion cross(const C4DQuaternion& quaternion) const;
	static C4DQuaternion cross(const C4DQuaternion& q1,const C4DQuaternion& q2);

	_FLOAT& operator [] (_INTEGER index);
	_FLOAT operator [] (_INTEGER index) const;

    operator _FLOAT* ();
    operator const _FLOAT* () const;

    C4DQuaternion& operator += (const C4DQuaternion& quaternion);
    C4DQuaternion& operator -= (const C4DQuaternion& quaternion);
    C4DQuaternion& operator *= (_FLOAT value);
    C4DQuaternion& operator /= (_FLOAT value);

    C4DQuaternion operator + () const;
    C4DQuaternion operator - () const;

    C4DQuaternion operator + (const C4DQuaternion& quaternion) const;
    C4DQuaternion operator - (const C4DQuaternion& quaternion) const;
    C4DQuaternion operator * (_FLOAT value) const;
    C4DQuaternion operator / (_FLOAT value) const;

    _BOOL operator == (const C4DQuaternion& quaternion) const;
    _BOOL operator != (const C4DQuaternion& quaternion) const;

	friend C4DQuaternion operator * (_FLOAT value,const C4DQuaternion& quaternion);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_4D_QUATERNION_H_