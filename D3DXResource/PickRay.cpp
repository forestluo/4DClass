///////////////////////////////////////////////////////////////////////////////
//
// PickRay.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "PickRay.h"

///////////////////////////////////////////////////////////////////////////////
//
// CPickRay
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CPickRay::CPickRay(void)
	: direction(0.0f,0.0f,1.0f),
	  pickOrigin(0.0f,0.0f,0.0f),
	  pickDirection(0.0f,0.0f,1.0f)
{
	//Set default value.
	allHits = _FALSE;
	//Initialize view matrix.
	viewMatrix.identity();
}

///////////////////////////////////////////////////////////////////////////////
//
// CPickRay
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CPickRay::CPickRay(const CPickRay& pickRay)
{
	allHits = pickRay.allHits;
	//Set value.
	direction = pickRay.direction;
	viewMatrix = pickRay.viewMatrix;
	//Set value.
	pickOrigin = pickRay.pickOrigin;
	pickDirection = pickRay.pickDirection;
}

///////////////////////////////////////////////////////////////////////////////
//
// CPickRay
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CPickRay::~CPickRay(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// Operator
//
/////////////////////////////////////////////////////////////////////////////////

const CPickRay& CPickRay::operator = (const CPickRay& pickRay)
{
	//Set flag.
	allHits = pickRay.allHits;
	//Set direction.
	direction = pickRay.direction;
	viewMatrix = pickRay.viewMatrix;
	//Set pick ray.
	pickOrigin = pickRay.pickOrigin;
	pickDirection = pickRay.pickDirection;
	//Return.
	return *this;
}

/////////////////////////////////////////////////////////////////////////////////
//
// IsAllHitsNeeded
//
/////////////////////////////////////////////////////////////////////////////////

_BOOL CPickRay::isAllHitsNeeded() const
{
	//Return value.
	return allHits;
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetAllHits
//
/////////////////////////////////////////////////////////////////////////////////

void CPickRay::setAllHits(_BOOL allHits)
{
	//Set all hits.
	this->allHits = allHits;
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetPickParameters
//
/////////////////////////////////////////////////////////////////////////////////

void CPickRay::setPickParameters(const C4DMatrix4& viewMatrix,const C4DVector3& direction)
{
	//Set value.
	this->direction = direction;
	this->viewMatrix = viewMatrix;
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetPickOrigin
//
/////////////////////////////////////////////////////////////////////////////////

const C4DVector3& CPickRay::getPickOrigin() const
{
	//Return result.
	return pickOrigin;
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetPickDirection
//
/////////////////////////////////////////////////////////////////////////////////

const C4DVector3& CPickRay::getPickDirection() const
{
	//Return result.
	return pickDirection;
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetWorldMatrix
//
/////////////////////////////////////////////////////////////////////////////////

void CPickRay::setWorldMatrix(const C4DMatrix4& worldMatrix)
{
	//Get the inverse view matrix.
	C4DMatrix4 matrix = worldMatrix * viewMatrix;
	//Inverse.
	matrix.inverse();
	//Transform the screen space pick ray into 3D space.
	//Set pick origin.
	pickOrigin.x() = matrix._41();
	pickOrigin.y() = matrix._42();
	pickOrigin.z() = matrix._43();
	//Set pick direction.
	pickDirection.x() = direction.x() * matrix._11() + direction.y() * matrix._21() + direction.z() * matrix._31();
	pickDirection.y() = direction.x() * matrix._12() + direction.y() * matrix._22() + direction.z() * matrix._32();
	pickDirection.z() = direction.x() * matrix._13() + direction.y() * matrix._23() + direction.z() * matrix._33();
}
