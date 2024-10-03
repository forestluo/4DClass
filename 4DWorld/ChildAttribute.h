///////////////////////////////////////////////////////////////////////////////
//
// ChildAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _CHILD_ATTRIBUTE_H_
#define _CHILD_ATTRIBUTE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "SimpleBox.h"
#include "SimpleSphere.h"

#include "NormalString.h"
#include "ListNodeEnumeration.h"

///////////////////////////////////////////////////////////////////////////////
//
// Delcaration
//
///////////////////////////////////////////////////////////////////////////////

class CWorldObject;

///////////////////////////////////////////////////////////////////////////////
//
// ChildAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CChildAttribute
{
private:
	/**
	 * Objects.
	 */
	_OBJECT objects;

public:
	CChildAttribute(void);
	virtual ~CChildAttribute(void);

public:

	/**
	 * Get count.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Count of object.</p>
	 */
	_INTEGER getCount() const;

	/**
	 * Add object.
	 *
	 * @param object World object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void addObject(CWorldObject* object);

	/**
	 * Remove object.
	 *
	 * @param object World object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void removeObject(CWorldObject* object);

	/**
	 * Whether object exists.
	 *
	 * @param object World object.
	 * @return
	 *     <p>Return true, if object exists.</p>
	 */
	_BOOL objectExists(CWorldObject* object) const;
	/**
	 * Get object.
	 *
	 * @param alias Alias of object.
	 * @return
	 *     <p>Object with specified name.</p>
	 */
	CWorldObject* getObject(const CNormalString& alias);

	/**
	 * Get enumeration.
	 *
	 * @param enumeration Enumeration.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void getEnumeration(CListNodeEnumeration& enumeration) const;

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
#endif //_CHILD_ATTRIBUTE_H_
