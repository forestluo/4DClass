///////////////////////////////////////////////////////////////////////////////
//
// BoxAttribute.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "BoxAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// CBoxAttribute
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CBoxAttribute::CBoxAttribute(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CBoxAttribute
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CBoxAttribute::CBoxAttribute(const CBoxAttribute& attribute)
{
	//Copy box.
	copyBox(attribute);
}

///////////////////////////////////////////////////////////////////////////////
//
// CBoxAttribute
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CBoxAttribute::~CBoxAttribute(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// Operator
//
///////////////////////////////////////////////////////////////////////////////

CBoxAttribute& CBoxAttribute::operator = (const CBoxAttribute& attribute)
{
	//Copy box.
	copyBox(attribute);
	//Return this.
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//
// CopyBox
//
///////////////////////////////////////////////////////////////////////////////

void CBoxAttribute::copyBox(const CBoxAttribute& attribute)
{
	//Set box.
	box = attribute.box;
	//Set sphere.
	sphere = attribute.sphere;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetBox
//
///////////////////////////////////////////////////////////////////////////////

void CBoxAttribute::setBox(const CSimpleBox& box)
{
	//Set value.
	this->box = box;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetSphere
//
///////////////////////////////////////////////////////////////////////////////

void CBoxAttribute::setSphere(const CSimpleSphere& sphere)
{
	//Set value.
	this->sphere = sphere;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetBox
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CBoxAttribute::getBox(CSimpleBox& box) const
{
	//Set value.
	box = this->box;
	//Return result.
	return _TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetSphere
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CBoxAttribute::getSphere(CSimpleSphere& sphere) const
{
	//Set value.
	sphere = this->sphere;
	//Return result.
	return _TRUE;
}