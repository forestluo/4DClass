///////////////////////////////////////////////////////////////////////////////
//
// PickedAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PICKED_ATTRIBUTE_H_
#define _PICKED_ATTRIBUTE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// PickedAttribute
//
///////////////////////////////////////////////////////////////////////////////

#include "PickRay.h"
#include "PickResult.h"

#include "WorldGroup.h"

///////////////////////////////////////////////////////////////////////////////
//
// PickedAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CPickedAttribute :
	public virtual CWorldGroup
{
public:
	CPickedAttribute(void);
	virtual ~CPickedAttribute(void);

public:

	/**
	 * Clear picked.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void clearPicked();

	/**
	 * Set picked.
	 *
	 * @param alias Alias of picked object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setPicked(const CNormalString& alias);

public:

	/**
	 * Get object.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Picked object.</p>
	 */
	CWorldObject* getPickedObject();

	/**
	 * Pick object.
	 *
	 * @param pickRay Pick ray.
	 * @param result Result of pick.
	 */
	_BOOL pickObject(CPickRay& pickRay,CPickResult& result);

};

///////////////////////////////////////////////////////////////////////////////
#endif //_PICKED_ATTRIBUTE_H_
