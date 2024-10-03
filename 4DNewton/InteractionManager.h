///////////////////////////////////////////////////////////////////////////////
//
// InteractionManager.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _INTERACTION_MANAGER_H_
#define _INTERACTION_MANAGER_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsWorld.h"

///////////////////////////////////////////////////////////////////////////////
//
// CInteractionManager
//
///////////////////////////////////////////////////////////////////////////////

class CInteractionManager : public virtual CPhysicsWorld
{
private:
	/**
	 * Items.
	 */
	_OBJECT items;

public:
	CInteractionManager(void);
	virtual ~CInteractionManager(void);

private:

	/**
	 * Release all.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void releaseAll();

protected:

	/**
	 * Clear controllers.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void clearControllers();

	/**
	 * Clear controller.
	 *
	 * @param body Collision body.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void clearController(_OBJECT body);

	/**
	 * Whether controlled.
	 *
	 * @param body Collision body.
	 * @return
	 *     <p>No results returned.</p>
	 */
	_BOOL isControlled(_OBJECT body) const;

protected:

	/**
	 * Pick object by body pick controller.
	 *
	 * @param body A picked body.
	 * @param point Picked point.
	 * @param
	 *     <p>No results returned.</p>
	 */
	void pickBody(_OBJECT body,const C4DVector3& point);

	/**
	 * Drag object by body pick controller.
	 *
	 * @param body A picked body.
	 * @param direction Direction for moving.
	 * @param
	 *     <p>No results returned.</p>
	 */
	void moveBody(_OBJECT body,const C4DVector3& direction);

};

///////////////////////////////////////////////////////////////////////////////
#endif //_INTERACTION_MANAGER_H_
