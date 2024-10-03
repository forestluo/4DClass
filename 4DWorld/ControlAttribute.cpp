///////////////////////////////////////////////////////////////////////////////
//
// ControlAttribute.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "ControlAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// CControlAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CControlAttribute::CControlAttribute(void)
{
	//Set default value.
	movable = _TRUE;
	scalable = _TRUE;
	rotatable = _TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//
// CControlAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CControlAttribute::CControlAttribute(const CControlAttribute& attribute)
{
	//Set default value.
	movable = attribute.movable;
	scalable = attribute.scalable;
	rotatable = attribute.rotatable;
}

///////////////////////////////////////////////////////////////////////////////
//
// CControlAttribute
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CControlAttribute::~CControlAttribute(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// Operator
//
///////////////////////////////////////////////////////////////////////////////

CControlAttribute& CControlAttribute::operator = (const CControlAttribute& attribute)
{
	//Set default value.
	movable = attribute.movable;
	scalable = attribute.scalable;
	rotatable = attribute.rotatable;
	//Return this.
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//
// IsMovable
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CControlAttribute::isMovable() const
{
	//Return result.
	return movable;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetMovable
//
///////////////////////////////////////////////////////////////////////////////

void CControlAttribute::setMovable(_BOOL movable)
{
	//Set movable.
	this->movable = movable;
}

///////////////////////////////////////////////////////////////////////////////
//
// IsScalable
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CControlAttribute::isScalable() const
{
	//Return result.
	return scalable;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetScalable
//
///////////////////////////////////////////////////////////////////////////////

void CControlAttribute::setScalable(_BOOL scalable)
{
	//Set movable.
	this->scalable = scalable;
}

///////////////////////////////////////////////////////////////////////////////
//
// IsRotatable
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CControlAttribute::isRotatable() const
{
	//Return result.
	return rotatable;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetRotatable
//
///////////////////////////////////////////////////////////////////////////////

void CControlAttribute::setRotatable(_BOOL rotatable)
{
	//Set rotatable.
	this->rotatable = rotatable;
}
