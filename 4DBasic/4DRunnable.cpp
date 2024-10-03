///////////////////////////////////////////////////////////////////////////////
//
// 4DRunnable.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "4DType.h"
#include "4DRunnable.h"

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Quiet
const _INTEGER C4DRunnable::quiet							= -1;
//Accerelated
const _INTEGER C4DRunnable::accelerated						= 1;
//Running
const _INTEGER C4DRunnable::running							= 2;
//Decelerated
const _INTEGER C4DRunnable::decelerated						= 3;
//Stopped
const _INTEGER C4DRunnable::stopped							= 4;

///////////////////////////////////////////////////////////////////////////////
//
// C4DRunnable
//
///////////////////////////////////////////////////////////////////////////////

C4DRunnable::C4DRunnable(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// C4DRunnable
//
///////////////////////////////////////////////////////////////////////////////

C4DRunnable::C4DRunnable(_STRING name)
{
#ifdef _DEBUG
	assert(name != _NULL);
#endif
	//Set name.
	this->name.append(name);
}

///////////////////////////////////////////////////////////////////////////////
//
// ~C4DRunnable
//
///////////////////////////////////////////////////////////////////////////////

C4DRunnable::~C4DRunnable(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// GetName
//
///////////////////////////////////////////////////////////////////////////////

_STRING C4DRunnable::getName()
{
	//Return result.
	return name.getCString();
}

///////////////////////////////////////////////////////////////////////////////
//
// SetName
//
///////////////////////////////////////////////////////////////////////////////

void C4DRunnable::setName(_STRING name)
{
#ifdef _DEBUG
	assert(name != _NULL);
#endif
	//Clear all.
	this->name.clearAll();
	//Append name.
	this->name.append(name);
}
