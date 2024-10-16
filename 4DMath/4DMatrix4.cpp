///////////////////////////////////////////////////////////////////////////////
//
// 4DMatrix4.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "4DMatrix4.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DX10Math.h"

///////////////////////////////////////////////////////////////////////////////
//
// C4DMatrix4
//
///////////////////////////////////////////////////////////////////////////////

C4DMatrix4::C4DMatrix4(void)
{
	//Zero memory.
	ZeroMemory(values,sizeof(_FLOAT44));
}

///////////////////////////////////////////////////////////////////////////////
//
// C4DMatrix4
//
///////////////////////////////////////////////////////////////////////////////

C4DMatrix4::C4DMatrix4(const _FLOAT* floats)
{
	//Copy memory.
	memcpy(values,floats,sizeof(_FLOAT44));
}

///////////////////////////////////////////////////////////////////////////////
//
// C4DMatrix4
//
///////////////////////////////////////////////////////////////////////////////

C4DMatrix4::C4DMatrix4(const C4DMatrix4& matrix4)
{
	//Copy memory.
	memcpy(values,matrix4.values,sizeof(_FLOAT44));
}

///////////////////////////////////////////////////////////////////////////////
//
// C4DMatrix4
//
///////////////////////////////////////////////////////////////////////////////

C4DMatrix4::C4DMatrix4(_FLOAT _11,_FLOAT _12,_FLOAT _13,_FLOAT _14,
					   _FLOAT _21,_FLOAT _22,_FLOAT _23,_FLOAT _24,
					   _FLOAT _31,_FLOAT _32,_FLOAT _33,_FLOAT _34,
					   _FLOAT _41,_FLOAT _42,_FLOAT _43,_FLOAT _44)
{
	//Set values.
	values[0][0] = _11, values[0][1] = _12, values[0][2] = _13, values[0][3] = _14;
	values[1][0] = _21, values[1][1] = _22, values[1][2] = _23, values[1][3] = _24;
	values[2][0] = _31, values[2][1] = _32, values[2][2] = _33, values[2][3] = _34;
	values[3][0] = _41, values[3][1] = _42, values[3][2] = _43, values[3][3] = _44;
}

///////////////////////////////////////////////////////////////////////////////
//
// C4DMatrix4
//
///////////////////////////////////////////////////////////////////////////////

C4DMatrix4::~C4DMatrix4(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// _11
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_11()
{
	//Return result.
	return values[0][0];
}

///////////////////////////////////////////////////////////////////////////////
//
// _11
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_11(_FLOAT value)
{
	//Set value.
	values[0][0] = value;
	//Return result.
	return value;
}

///////////////////////////////////////////////////////////////////////////////
//
// _12
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_12()
{
	//Return result.
	return values[0][1];
}

///////////////////////////////////////////////////////////////////////////////
//
// _12
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_12(_FLOAT value)
{
	//Set value.
	values[0][1] = value;
	//Return result.
	return value;
}

///////////////////////////////////////////////////////////////////////////////
//
// _13
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_13()
{
	//Return result.
	return values[0][2];
}

///////////////////////////////////////////////////////////////////////////////
//
// _13
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_13(_FLOAT value)
{
	//Set value.
	values[0][2] = value;
	//Return result.
	return value;
}

///////////////////////////////////////////////////////////////////////////////
//
// _14
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_14()
{
	//Return result.
	return values[0][3];
}

///////////////////////////////////////////////////////////////////////////////
//
// _14
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_14(_FLOAT value)
{
	//Set value.
	values[0][3] = value;
	//Return result.
	return value;
}

///////////////////////////////////////////////////////////////////////////////
//
// _21
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_21()
{
	//Return result.
	return values[1][0];
}

///////////////////////////////////////////////////////////////////////////////
//
// _21
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_21(_FLOAT value)
{
	//Set value.
	values[1][0] = value;
	//Return result.
	return value;
}

///////////////////////////////////////////////////////////////////////////////
//
// _22
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_22()
{
	//Return result.
	return values[1][1];
}

///////////////////////////////////////////////////////////////////////////////
//
// _22
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_22(_FLOAT value)
{
	//Set value.
	values[1][1] = value;
	//Return result.
	return value;
}

///////////////////////////////////////////////////////////////////////////////
//
// _23
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_23()
{
	//Return result.
	return values[1][2];
}

///////////////////////////////////////////////////////////////////////////////
//
// _23
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_23(_FLOAT value)
{
	//Set value.
	values[1][2] = value;
	//Return result.
	return value;
}

///////////////////////////////////////////////////////////////////////////////
//
// _24
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_24()
{
	//Return result.
	return values[1][3];
}

///////////////////////////////////////////////////////////////////////////////
//
// _24
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_24(_FLOAT value)
{
	//Set value.
	values[1][3] = value;
	//Return result.
	return value;
}

///////////////////////////////////////////////////////////////////////////////
//
// _31
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_31()
{
	//Return result.
	return values[2][0];
}

///////////////////////////////////////////////////////////////////////////////
//
// _31
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_31(_FLOAT value)
{
	//Set value.
	values[2][0] = value;
	//Return result.
	return value;
}

///////////////////////////////////////////////////////////////////////////////
//
// _32
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_32()
{
	//Return result.
	return values[2][1];
}

///////////////////////////////////////////////////////////////////////////////
//
// _32
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_32(_FLOAT value)
{
	//Set value.
	values[2][1] = value;
	//Return result.
	return value;
}

///////////////////////////////////////////////////////////////////////////////
//
// _33
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_33()
{
	//Return result.
	return values[2][2];
}

///////////////////////////////////////////////////////////////////////////////
//
// _33
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_33(_FLOAT value)
{
	//Set value.
	values[2][2] = value;
	//Return result.
	return value;
}

///////////////////////////////////////////////////////////////////////////////
//
// _34
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_34()
{
	//Return result.
	return values[2][3];
}

///////////////////////////////////////////////////////////////////////////////
//
// _34
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_34(_FLOAT value)
{
	//Set value.
	values[2][3] = value;
	//Return result.
	return value;
}

///////////////////////////////////////////////////////////////////////////////
//
// _41
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_41()
{
	//Return result.
	return values[3][0];
}

///////////////////////////////////////////////////////////////////////////////
//
// _41
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_41(_FLOAT value)
{
	//Set value.
	values[3][0] = value;
	//Return result.
	return value;
}

///////////////////////////////////////////////////////////////////////////////
//
// _42
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_42()
{
	//Return result.
	return values[3][1];
}

///////////////////////////////////////////////////////////////////////////////
//
// _42
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_42(_FLOAT value)
{
	//Set value.
	values[3][1] = value;
	//Return result.
	return value;
}

///////////////////////////////////////////////////////////////////////////////
//
// _43
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_43()
{
	//Return result.
	return values[3][2];
}

///////////////////////////////////////////////////////////////////////////////
//
// _43
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_43(_FLOAT value)
{
	//Set value.
	values[3][2] = value;
	//Return result.
	return value;
}

///////////////////////////////////////////////////////////////////////////////
//
// _44
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_44()
{
	//Return result.
	return values[3][3];
}

///////////////////////////////////////////////////////////////////////////////
//
// _44
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::_44(_FLOAT value)
{
	//Set value.
	values[3][3] = value;
	//Return result.
	return value;
}

///////////////////////////////////////////////////////////////////////////////
//
// Identity
//
///////////////////////////////////////////////////////////////////////////////

void C4DMatrix4::identity()
{
	//Matrix.
	D3DXMATRIX m;
	//Initialize.
	D3DXMatrixIdentity(&m);
	//Copy values.
	memcpy(values,(_FLOAT *)m,sizeof(_FLOAT44));
}

///////////////////////////////////////////////////////////////////////////////
//
// Transpose
//
///////////////////////////////////////////////////////////////////////////////

void C4DMatrix4::transpose()
{
	//Matrix in.
	D3DXMATRIX mIn((_FLOAT *)values);
	//Matrix out.
	D3DXMATRIX mOut;
	//Transpose.
	D3DXMatrixTranspose(&mOut,&mIn);
	//Set value.
	memcpy(values,(_FLOAT *)mOut,sizeof(_FLOAT44));
}

///////////////////////////////////////////////////////////////////////////////
//
// Transpose
//
///////////////////////////////////////////////////////////////////////////////

C4DMatrix4 C4DMatrix4::transpose() const
{
	//Matrix in.
	D3DXMATRIX mIn((_FLOAT *)values);
	//Matrix out.
	D3DXMATRIX mOut;
	//Transpose.
	D3DXMatrixTranspose(&mOut,&mIn);
	//Return result.
	return C4DMatrix4((_FLOAT *)mOut);
}

///////////////////////////////////////////////////////////////////////////////
//
// Inverse
//
///////////////////////////////////////////////////////////////////////////////

void C4DMatrix4::inverse()
{
	//Matrix in.
	D3DXMATRIX mIn((_FLOAT *)values);
	//Matrix out.
	D3DXMATRIX mOut;
	//Inverse.
	D3DXMatrixInverse(&mOut,NULL,&mIn);
	//Set value.
	memcpy(values,(_FLOAT *)mOut,sizeof(_FLOAT44));
}

///////////////////////////////////////////////////////////////////////////////
//
// Inverse
//
///////////////////////////////////////////////////////////////////////////////

C4DMatrix4 C4DMatrix4::inverse() const
{
	//Matrix in.
	D3DXMATRIX mIn((_FLOAT *)values);
	//Matrix out.
	D3DXMATRIX mOut;
	//Inverse.
	D3DXMatrixInverse(&mOut,NULL,&mIn);
	//Return result.
	return C4DMatrix4((_FLOAT *)mOut);
}

///////////////////////////////////////////////////////////////////////////////
//
// XRotation
//
///////////////////////////////////////////////////////////////////////////////

void C4DMatrix4::xRotate(_FLOAT angle)
{
	//Matrix.
	D3DXMATRIX m;
	//Initialize.
	D3DXMatrixRotationX(&m,angle);
	//Set values.
	memcpy(values,(_FLOAT *)m,sizeof(_FLOAT44));
}

///////////////////////////////////////////////////////////////////////////////
//
// yRotation
//
///////////////////////////////////////////////////////////////////////////////

void C4DMatrix4::yRotate(_FLOAT angle)
{
	//Matrix.
	D3DXMATRIX m;
	//Initialize.
	D3DXMatrixRotationY(&m,angle);
	//Set values.
	memcpy(values,(_FLOAT *)m,sizeof(_FLOAT44));
}

///////////////////////////////////////////////////////////////////////////////
//
// zRotation
//
///////////////////////////////////////////////////////////////////////////////

void C4DMatrix4::zRotate(_FLOAT angle)
{
	//Matrix.
	D3DXMATRIX m;
	//Initialize.
	D3DXMatrixRotationZ(&m,angle);
	//Set values.
	memcpy(values,(_FLOAT *)m,sizeof(_FLOAT44));
}

///////////////////////////////////////////////////////////////////////////////
//
// Scale
//
///////////////////////////////////////////////////////////////////////////////

void C4DMatrix4::scale(_FLOAT sx,_FLOAT sy,_FLOAT sz)
{
	//Matrix.
	D3DXMATRIX m;
	//Initialize.
	D3DXMatrixScaling(&m,sx,sy,sz);
	//Set values.
	memcpy(values,(_FLOAT *)m,sizeof(_FLOAT44));
}

///////////////////////////////////////////////////////////////////////////////
//
// Rotate
//
///////////////////////////////////////////////////////////////////////////////

void C4DMatrix4::rotate(const C4DQuaternion& rotation)
{
	//Matrix.
	D3DXMATRIX m;
	//Initialize.
	D3DXMatrixRotationQuaternion(&m,&D3DXQUATERNION(rotation));
	//Set values.
	memcpy(values,(_FLOAT *)m,sizeof(_FLOAT44));
}

///////////////////////////////////////////////////////////////////////////////
//
// Translate.
//
///////////////////////////////////////////////////////////////////////////////

void C4DMatrix4::translate(_FLOAT dx,_FLOAT dy,_FLOAT dz)
{
	//Matrix.
	D3DXMATRIX m;
	//Initialize.
	D3DXMatrixTranslation(&m,dx,dy,dz);
	//Set values.
	memcpy(values,(_FLOAT *)m,sizeof(_FLOAT44));
}

///////////////////////////////////////////////////////////////////////////////
//
// Operator
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT& C4DMatrix4::operator () (_INTEGER row,_INTEGER col)
{
#ifdef _DEBUG
	assert(row >= 0 && row < 4);
	assert(col >= 0 && col < 4);
#endif
	//Return result.
	return values[row][col];
}

///////////////////////////////////////////////////////////////////////////////
//
// Operator
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT C4DMatrix4::operator () (_INTEGER row,_INTEGER col) const
{
#ifdef _DEBUG
	assert(row >= 0 && row < 4);
	assert(col >= 0 && col < 4);
#endif
	//Return result.
	return values[row][col];
}

///////////////////////////////////////////////////////////////////////////////
//
// Casting
//
///////////////////////////////////////////////////////////////////////////////

C4DMatrix4::operator _FLOAT* ()
{
	//Return result.
	return (_FLOAT *)values;
}

///////////////////////////////////////////////////////////////////////////////
//
// Casting
//
///////////////////////////////////////////////////////////////////////////////
   
C4DMatrix4::operator const _FLOAT* () const
{
	//Return result.
	return (const _FLOAT *)values;
}

///////////////////////////////////////////////////////////////////////////////
//
// Operator
//
///////////////////////////////////////////////////////////////////////////////

C4DMatrix4& C4DMatrix4::operator *= (const C4DMatrix4& matrix4)
{
	D3DXMATRIX m1((_FLOAT *)values);
	D3DXMATRIX m2((_FLOAT *)matrix4.values);
	//Multiply.
	m1 *= m2;
	//Set value.
	memcpy(values,(_FLOAT *)m1,sizeof(_FLOAT44));
	//Return this.
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//
// Operator
//
///////////////////////////////////////////////////////////////////////////////

C4DMatrix4& C4DMatrix4::operator += (const C4DMatrix4& matrix4)
{
	D3DXMATRIX m1((_FLOAT *)values);
	D3DXMATRIX m2((_FLOAT *)matrix4.values);
	//Multiply.
	m1 += m2;
	//Set value.
	memcpy(values,(_FLOAT *)m1,sizeof(_FLOAT44));
	//Return this.
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//
// Operator
//
///////////////////////////////////////////////////////////////////////////////

C4DMatrix4& C4DMatrix4::operator -= (const C4DMatrix4& matrix4)
{
	D3DXMATRIX m1((_FLOAT *)values);
	D3DXMATRIX m2((_FLOAT *)matrix4.values);
	//Multiply.
	m1 -= m2;
	//Set value.
	memcpy(values,(_FLOAT *)m1,sizeof(_FLOAT44));
	//Return this.
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//
// Operator
//
///////////////////////////////////////////////////////////////////////////////

C4DMatrix4& C4DMatrix4::operator *= (_FLOAT value)
{
	D3DXMATRIX m((_FLOAT *)values);
	//Multiply.
	m *= value;
	//Set value.
	memcpy(values,(_FLOAT *)m,sizeof(_FLOAT44));
	//Return this.
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//
// Operator
//
///////////////////////////////////////////////////////////////////////////////

C4DMatrix4& C4DMatrix4::operator /= (_FLOAT value)
{
	D3DXMATRIX m((_FLOAT *)values);
	//Multiply.
	m /= value;
	//Set value.
	memcpy(values,(_FLOAT *)m,sizeof(_FLOAT44));
	//Return this.
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//
// Operator
//
///////////////////////////////////////////////////////////////////////////////

C4DMatrix4 C4DMatrix4::operator + () const
{
	//Get value.
	_FLOAT44 values;
	//Set positive.
	for(int i = 0;i < 4;i ++)
	{
		for(int j = 0;j < 4;j ++)
		{
			//Set positive.
			values[i][j] = this->values[i][j];
		}
	}
	//Return result.
	return C4DMatrix4((_FLOAT *)values);
}

///////////////////////////////////////////////////////////////////////////////
//
// Operator
//
///////////////////////////////////////////////////////////////////////////////

C4DMatrix4 C4DMatrix4::operator - () const
{
	//Get value.
	_FLOAT44 values;
	//Set negative.
	for(int i = 0;i < 4;i ++)
	{
		for(int j = 0;j < 4;j ++)
		{
			//Set negative.
			values[i][j] = -this->values[i][j];
		}
	}
	//Return result.
	return C4DMatrix4((_FLOAT *)values);
}

///////////////////////////////////////////////////////////////////////////////
//
// Operator
//
///////////////////////////////////////////////////////////////////////////////

C4DMatrix4 C4DMatrix4::operator * (const C4DMatrix4& matrix4) const
{
	//Initialize matrix.
	C4DMatrix4 mOut(*this);
	//Multiply.
	mOut *= matrix4;
	//Return result.
	return mOut;
}

///////////////////////////////////////////////////////////////////////////////
//
// Operator
//
///////////////////////////////////////////////////////////////////////////////

C4DMatrix4 C4DMatrix4::operator + (const C4DMatrix4& matrix4) const
{
	//Initialize matrix.
	C4DMatrix4 mOut(*this);
	//Multiply.
	mOut += matrix4;
	//Return result.
	return mOut;
}

///////////////////////////////////////////////////////////////////////////////
//
// Operator
//
///////////////////////////////////////////////////////////////////////////////

C4DMatrix4 C4DMatrix4::operator - (const C4DMatrix4& matrix4) const
{
	//Initialize matrix.
	C4DMatrix4 mOut(*this);
	//Multiply.
	mOut -= matrix4;
	//Return result.
	return mOut;
}

///////////////////////////////////////////////////////////////////////////////
//
// Operator
//
///////////////////////////////////////////////////////////////////////////////

C4DMatrix4 C4DMatrix4::operator * (_FLOAT value) const
{
	//Initialize matrix.
	C4DMatrix4 mOut(*this);
	//Multiply.
	mOut *= value;
	//Return result.
	return mOut;
}

///////////////////////////////////////////////////////////////////////////////
//
// Operator
//
///////////////////////////////////////////////////////////////////////////////

C4DMatrix4 C4DMatrix4::operator / (_FLOAT value) const
{
	//Initialize matrix.
	C4DMatrix4 mOut(*this);
	//Multiply.
	mOut /= value;
	//Return result.
	return mOut;
}

///////////////////////////////////////////////////////////////////////////////
//
// Operator
//
///////////////////////////////////////////////////////////////////////////////

_BOOL C4DMatrix4::operator == (const C4DMatrix4& matrix4) const
{
	//Return result.
	return D3DXMATRIX((_FLOAT *)values) == D3DXMATRIX((_FLOAT *)matrix4.values);
}

///////////////////////////////////////////////////////////////////////////////
//
// Operator
//
///////////////////////////////////////////////////////////////////////////////

_BOOL C4DMatrix4::operator != (const C4DMatrix4& matrix4) const
{
	//Return result.
	return D3DXMATRIX((_FLOAT *)values) != D3DXMATRIX((_FLOAT *)matrix4.values);
}

///////////////////////////////////////////////////////////////////////////////
//
// Operator
//
///////////////////////////////////////////////////////////////////////////////

C4DMatrix4 operator * (_FLOAT value,const C4DMatrix4& matrix4)
{
	//Initialize matrix.
	C4DMatrix4 mOut(matrix4);
	//Multiply.
	mOut *= value;
	//Return result.
	return mOut;
}

///////////////////////////////////////////////////////////////////////////////
//
// Operator
//
///////////////////////////////////////////////////////////////////////////////

C4DVector3 operator * (const C4DVector3& vector,const C4DMatrix4& matrix4)
{
	//Coordinate.
	D3DXVECTOR3 coordinate;
	//Create matrix.
	D3DXMATRIX mWorld(matrix4);
	//Transform coordinates.
	D3DXVec3TransformCoord(&coordinate,&D3DXVECTOR3(vector),&mWorld);
	//Return result.
	return C4DVector3(coordinate);
}
