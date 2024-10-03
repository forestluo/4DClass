///////////////////////////////////////////////////////////////////////////////
//
// JointRelationAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _JOINT_RELATION_ATTRIBUTE_H_
#define _JOINT_RELATION_ATTRIBUTE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "WorldObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// JointRelationAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CJointRelationAttribute
{
private:
	/**
	 * Child object.
	 *
	 * <p>A primitive or compound object.
	 * Must have a mass and must not be null.</p>
	 */
	CWorldObject* child;
	/**
	 * Parent object.
	 *
	 * <p>A primitive or compound object.
	 * Can be null or have a ZERO mass.</p>
	 */
	CWorldObject* parent;

public:
	CJointRelationAttribute(void);
	virtual ~CJointRelationAttribute(void);

public:

	/**
	 * Get child.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Child object.</p>
	 */
	CWorldObject* getJointChild() const;
	/**
	 * Set child.
	 *
	 * @param child Child object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setJointChild(CWorldObject* child);

public:

	/**
	 * Get parent.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Parent object.</p>
	 */
	CWorldObject* getJointParent() const;
	/**
	 * Set parent.
	 *
	 * @param parent Parent object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setJointParent(CWorldObject* parent);

};

///////////////////////////////////////////////////////////////////////////////
#endif //_JOINT_RELATION_ATTRIBUTE_H_
