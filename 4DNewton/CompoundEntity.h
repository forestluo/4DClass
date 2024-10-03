///////////////////////////////////////////////////////////////////////////////
//
// CompoundEntity.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _COMPOUND_ENTITY_H_
#define _COMPOUND_ENTITY_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsEntity.h"
#include "PhysicsManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// CompoundEntity
//
///////////////////////////////////////////////////////////////////////////////

class CCompoundEntity : public CPhysicsEntity
{
public:
	CCompoundEntity(void);
	CCompoundEntity(_FLOAT mass);
	virtual ~CCompoundEntity(void);

protected:

	/**
	 * Create shape.
	 *
	 * @param manager Physics manager.
	 * @param shapes Shapes of compound.
	 * @return
	 *     <p>Created shape.</p>
	 */
	virtual _OBJECT createShape(CPhysicsManager *manager,
								CListNodeContainer& shapes);

private:

	/**
	 * Create shape.
	 *
	 * @param manager Physics manager.
	 * @param object World object.
	 * @param shapes Create shapes.
	 * @param matrix Matrix of parent.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void createShapes(CPhysicsManager* manager,CWorldObject* object,
								CListNodeContainer& shapes,const C4DMatrix4& matrix);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_COMPOUND_ENTITY_H_
