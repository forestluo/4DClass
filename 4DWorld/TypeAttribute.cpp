///////////////////////////////////////////////////////////////////////////////
//
// TypeAttribute.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "TypeAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////
	
const _INTEGER CTypeAttribute::nullObject					= 0;
const _INTEGER CTypeAttribute::jointObject					= 1;
const _INTEGER CTypeAttribute::compoundObject				= 2;
const _INTEGER CTypeAttribute::primitiveObject				= 3;

///////////////////////////////////////////////////////////////////////////////
//
// CTypeAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CTypeAttribute::CTypeAttribute(void)
{
	//Set type.
	this->objectType = nullObject;
}

///////////////////////////////////////////////////////////////////////////////
//
// CTypeAttribute
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CTypeAttribute::~CTypeAttribute(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// GetObjectType
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CTypeAttribute::getObjectType() const
{
	//Return result.
	return objectType;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetObjectType
//
///////////////////////////////////////////////////////////////////////////////

void CTypeAttribute::setObjectType(_INTEGER objectType)
{
	//Set result.
	this->objectType = objectType;
}

///////////////////////////////////////////////////////////////////////////////
//
// IsJointObject
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CTypeAttribute::isJointObject() const
{
	//Return result.
	return objectType == jointObject;
}

///////////////////////////////////////////////////////////////////////////////
//
// IsCompoundObject
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CTypeAttribute::isCompoundObject() const
{
	//Return result.
	return objectType == compoundObject;
}

///////////////////////////////////////////////////////////////////////////////
//
// IsPrimitiveObject
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CTypeAttribute::isPrimitiveObject() const
{
	//Return result.
	return objectType == primitiveObject;
}
