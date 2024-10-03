///////////////////////////////////////////////////////////////////////////////
//
// CollisionMethod.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _COLLISION_METHOD_H_
#define _COLLISION_METHOD_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "SimpleBox.h"
#include "SimpleSphere.h"

#include "BoxObject.h"
#include "MultiBoxObject.h"
#include "SingleBoxObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// CollisionMethod
//
///////////////////////////////////////////////////////////////////////////////

class CCollisionMethod
{
public:
	//Status 
	static const _INTEGER unknow;
	//Inside
	static const _INTEGER inside;
	//Contact
	static const _INTEGER contact;
	//Depature
	static const _INTEGER depature;
	//Intersect
	static const _INTEGER intersect;

public:
	CCollisionMethod(void);
	virtual ~CCollisionMethod(void);

private:

	/**
	 * Collision1.
	 *
	 * <p>Process with classic function.</p>
	 *
	 * @param b1 First box.
	 * @param b2 Second box.
	 * @return
	 *     <p>Status of collision.
	 *     Only depature and intersect.</p>
	 */
	_INTEGER collision1(CSimpleBox* b1,CSimpleBox* b2);

	/**
	 * Collision2.
	 *
	 * <p>Process with self created function.</p>
	 *
	 * @param b1 First box.
	 * @param b2 Second box.
	 * @return
	 *     <p>Status of collision.
	 *     Only depature and intersect.</p>
	 */
	_INTEGER collision2(CSimpleBox* b1,CSimpleBox* b2);

private:

	/**
	 * Collision1.
	 *
	 * <p>Process with classic function.</p>
	 *
	 * @param s1 First sphere.
	 * @param s2 Second sphere.
	 * @return
	 *     <p>Status of collision.
	 *     Only depature and intersect.</p>
	 */
	_INTEGER collision1(CSimpleSphere* s1,CSimpleSphere* s2);

	/**
	 * Collision2.
	 *
	 * <p>Process with self created function.</p>
	 *
	 * @param s1 First sphere.
	 * @param s2 Second sphere.
	 * @return
	 *     <p>Status of collision.
	 *     Only depature and intersect.</p>
	 */
	_INTEGER collision2(CSimpleSphere* s1,CSimpleSphere* s2);

private:

	/**
	 * Collision2.
	 *
	 * <p>Process with self created function.</p>
	 *
	 * @param b1 First box.
	 * @param b2 Second box.
	 * @return
	 *     <p>Status of collision.
	 *     Only depature and intersect.</p>
	 */
	_INTEGER collision2(CMultiBoxObject* o1,CMultiBoxObject* o2);

	/**
	 * Collision2.
	 *
	 * <p>Process with self created function.</p>
	 *
	 * @param b1 First box.
	 * @param b2 Second box.
	 * @return
	 *     <p>Status of collision.
	 *     Only depature and intersect.</p>
	 */
	_INTEGER collision2(CMultiBoxObject* o1,CSingleBoxObject* o2);

	/**
	 * Collision2.
	 *
	 * <p>Process with self created function.</p>
	 *
	 * @param b1 First box.
	 * @param b2 Second box.
	 * @return
	 *     <p>Status of collision.
	 *     Only depature and intersect.</p>
	 */
	_INTEGER collision2(CSingleBoxObject* o1,CSingleBoxObject* o2);

	/**
	 * Collision.
	 *
	 * <p>Only compare box simplely.</p>
	 *
	 * @param o1 First object.
	 * @param o2 Second object.
	 * @return
	 *     <p>Status of collision.
	 *     Only depature and intersect.</p>
	 */
	_INTEGER collision1(CBoxObject* o1,CBoxObject* o2);

public:

	/**
	 * Collision.
	 *
	 * <p>Compare box tree recursively.</p>
	 *
	 * @param o1 First object.
	 * @param o2 Second object.
	 * @return
	 *     <p>Status of collision.
	 *     Only depature and intersect.</p>
	 */
	_INTEGER collision3(CBoxObject* o1,CBoxObject* o2);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_COLLISION_METHOD_H_
