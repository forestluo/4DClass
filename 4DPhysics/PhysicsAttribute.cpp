///////////////////////////////////////////////////////////////////////////////
//
// PhysicsAttribute.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// CPhysicsAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CPhysicsAttribute::CPhysicsAttribute(void)
{
	//Set default value.
	mass = 0.0f;
}

///////////////////////////////////////////////////////////////////////////////
//
// CPhysicsAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CPhysicsAttribute::CPhysicsAttribute(const CPhysicsAttribute& attribute)
{
	//Set mass.
	mass = attribute.mass;
	//Set inertia.
	inertia = attribute.inertia;
}

///////////////////////////////////////////////////////////////////////////////
//
// CPhysicsAttribute
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CPhysicsAttribute::~CPhysicsAttribute(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// Operator
//
/////////////////////////////////////////////////////////////////////////////////

CPhysicsAttribute& CPhysicsAttribute::operator = (const CPhysicsAttribute& attribute)
{
	//Set mass.
	mass = attribute.mass;
	//Set inertia.
	inertia = attribute.inertia;
	//Return this.
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetMass
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT CPhysicsAttribute::getMass() const
{
	//Return result.
	return mass;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetMass
//
///////////////////////////////////////////////////////////////////////////////

void CPhysicsAttribute::setMass(_FLOAT mass)
{
	//Set value.
	this->mass = mass;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetInertia
//
///////////////////////////////////////////////////////////////////////////////
	
const C4DVector3& CPhysicsAttribute::getInertia() const
{
	//Return result.
	return inertia;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetInertia
//
///////////////////////////////////////////////////////////////////////////////
	
void CPhysicsAttribute::setInertia(const C4DVector3& inertia)
{
	//Set value.
	this->inertia = inertia;
}
