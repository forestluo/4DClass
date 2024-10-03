///////////////////////////////////////////////////////////////////////////////
//
// JointObjectSketcher.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _JOINT_OBJECT_SKETCHER_H_
#define _JOINT_OBJECT_SKETCHER_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ObjectSketcher.h"

///////////////////////////////////////////////////////////////////////////////
//
// JointObjectSketcher
//
///////////////////////////////////////////////////////////////////////////////

class CJointObjectSketcher : public CObjectSketcher
{
private:
	//Base description.
	static const C4DBase base;

public:

	/**
	 * Get class code.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Hash code of this class.</p>
	 */
	static _LONG getClassCode() {return base.classCode();}

	/**
	 * Get class code.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Hash code of this class.</p>
	 */
	virtual _LONG classCode() const {return base.classCode();}

public:
	/**
	 * Draw sphere.
	 */
	_BOOL drawJointSphere;
	/**
	 * Draw position.
	 */
	_BOOL drawJointPosition;
	/**
	 * Draw direction.
	 */
	_BOOL drawJointDirection;

public:
	CJointObjectSketcher(void);
	virtual ~CJointObjectSketcher(void);

protected:

	/**
	 * Attach sketch.
	 *
	 * @param resourceManager Resource manager.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void attachSketch(CResourceManager* resourceManager);
};

#define IS_JOINTOBJECTSKETCHER_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CJointObjectSketcher::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_JOINT_OBJECT_SKETCHER_H_
