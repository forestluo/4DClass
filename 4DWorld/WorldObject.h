///////////////////////////////////////////////////////////////////////////////
//
// WorldObject.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _WORLD_OBJECT_H_
#define _WORLD_OBJECT_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "BoxAttribute.h"
#include "TypeAttribute.h"
#include "ChildAttribute.h"
#include "ControlAttribute.h"
#include "IdentityAttribute.h"
#include "PositionAttribute.h"
#include "RelationAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// WorldObject
//
///////////////////////////////////////////////////////////////////////////////

class CWorldObject :
	public CBoxAttribute,
	public CTypeAttribute,
	public CChildAttribute,
	public CControlAttribute,
	public CIdentityAttribute,
	public CPositionAttribute,
	public CRelationAttribute
{
public:
	CWorldObject(void);
	virtual ~CWorldObject(void);

public:

	/**
	 * Add object.
	 *
	 * @param object Basic object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void addObject(CWorldObject* object);

public:

	/**
	 * Initialize matrix.
	 *
	 * @param matrix World matrix.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void initializeMatrix(C4DMatrix4& matrix) const;

public:

	/**
	 * Get box in world.
	 *
	 * @param box Box.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	virtual _BOOL getWorldBox(CSimpleBox& box) const;
	/**
	 * Get sphere in world.
	 *
	 * @param sphere Sphere.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	virtual _BOOL getWorldSphere(CSimpleSphere& sphere) const;

};

///////////////////////////////////////////////////////////////////////////////
#endif //_WORLD_OBJECT_H_
