///////////////////////////////////////////////////////////////////////////////
//
// PhysicsWorld.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PHYSICS_WORLD_H_
#define _PHYSICS_WORLD_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DVector3.h"

///////////////////////////////////////////////////////////////////////////////
//
// CPhysicsWorld
//
///////////////////////////////////////////////////////////////////////////////

class CPhysicsWorld
{
protected:
	/**
	 * Physics manager.
	 */
	_OBJECT physicsManager;

protected:
	/**
	 * World object.
	 */
	_OBJECT	world;
	/**
	 * Newton debugger.
	 */
	_OBJECT	debugger;

public:
	CPhysicsWorld(void);
	virtual ~CPhysicsWorld(void);

public:

	/**
	 * Set world size.
	 *
	 * @param minBox Minimum box.
	 * @param maxBox Maximum box.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setWorldSize(const C4DVector3& minBox,const C4DVector3& maxBox);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_PHYSICS_WORLD_H_
