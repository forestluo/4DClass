///////////////////////////////////////////////////////////////////////////////
//
// ArrayManager.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _ARRAY_MANAGER_H_
#define _ARRAY_MANAGER_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "WorldGroup.h"
#include "ResourceManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// ArrayManager
//
///////////////////////////////////////////////////////////////////////////////

class CArrayManager :
	public virtual CWorldGroup
{
public:
	/**
	 * Types of array.
	 */
	static const _INTEGER xVerticalArray;
	static const _INTEGER yVerticalArray;
	static const _INTEGER zVerticalArray;

public:
	CArrayManager(void);
	virtual ~CArrayManager(void);

private:

	/**
	 * Create floor.
	 *
	 * @param resourceManager Resource manager.
	 * @param row Row count.
	 * @param column Column count.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void createYVerticalFloor(CResourceManager* resourceManager,
							_INTEGER row = 1,_INTEGER column = 1,
							const C4DVector3& origin = C4DVector3(0.0f,0.0f,0.0f));

	/**
	 * Create floor.
	 *
	 * @param resourceManager Resource manager.
	 * @param row Row count.
	 * @param column Column count.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void createXVerticalFloor(CResourceManager* resourceManager,
							_INTEGER row = 1,_INTEGER column = 1,
							const C4DVector3& origin = C4DVector3(0.0f,0.0f,0.0f));

	/**
	 * Create floor.
	 *
	 * @param resourceManager Resource manager.
	 * @param row Row count.
	 * @param column Column count.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void createZVerticalFloor(CResourceManager* resouceManager,
							_INTEGER row = 1,_INTEGER column = 1,
							const C4DVector3& origin = C4DVector3(0.0f,0.0f,0.0f));

public:

	/**
	 * Create floor.
	 *
	 * @param resourceManager Resource manager.
	 * @param arrayType Type of array.
	 * @param row Row count.
	 * @param column Column count.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void createFloor(CResourceManager* resouceManager,
						_INTEGER arrayType,_INTEGER row = 1,_INTEGER column = 1,
						const C4DVector3& origin = C4DVector3(0.0f,0.0f,0.0f));

private:

	/**
	 * Create ball.
	 *
	 * @param resourceManager Resource manager.
	 * @param row Row count.
	 * @param column Column count.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void createYVerticalBall(CResourceManager* resourceManager,
							_INTEGER row = 1,_INTEGER column = 1,
							const C4DVector3& origin = C4DVector3(0.0f,0.0f,0.0f));

public:

	/**
	 * Create sphere array.
	 *
	 * @param resourceManager Resource manager.
	 * @param arrayType Type of array.
	 * @param row Row count.
	 * @param column Column count.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void createSphereArray(CResourceManager* resouceManager,
							_INTEGER arrayType,_INTEGER row = 1,_INTEGER column = 1,
							const C4DVector3& origin = C4DVector3(0.0f,0.0f,0.0f));

private:

	/**
	 * Create cuboid.
	 *
	 * @param resourceManager Resource manager.
	 * @param row Row count.
	 * @param column Column count.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void createYVerticalCuboid(CResourceManager* resourceManager,
							_INTEGER row = 1,_INTEGER column = 1,
							const C4DVector3& origin = C4DVector3(0.0f,0.0f,0.0f));

public:

	/**
	 * Create cuboid array.
	 *
	 * @param resourceManager Resource manager.
	 * @param arrayType Type of array.
	 * @param row Row count.
	 * @param column Column count.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void createCuboidArray(CResourceManager* resouceManager,
							_INTEGER arrayType,_INTEGER row = 1,_INTEGER column = 1,
							const C4DVector3& origin = C4DVector3(0.0f,0.0f,0.0f));
};

///////////////////////////////////////////////////////////////////////////////
#endif //_ARRAY_MANAGER_H_
