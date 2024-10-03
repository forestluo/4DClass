///////////////////////////////////////////////////////////////////////////////
//
// ShapeManager.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _SHAPE_MANAGER_H_
#define _SHAPE_MANAGER_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DMatrix4.h"
#include "PhysicsWorld.h"
#include "ListNodeContainer.h"

///////////////////////////////////////////////////////////////////////////////
//
// CShapeManager
//
///////////////////////////////////////////////////////////////////////////////

class CShapeManager : public virtual CPhysicsWorld
{
public:
	CShapeManager(void);
	virtual ~CShapeManager(void);

public:

	/**
	 * Destroy shape.
	 * 
	 * @param collisionShape Collision shape.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void destroyShape(_OBJECT collisionShape);

public:

	/**
	 * Create compound shape.
	 *
	 * @param shapes Shapes of compound.
	 * @return
	 *     <p>Compound shape for collision.</p>
	 */
	_OBJECT createCompoundShape(CListNodeContainer& shapes);

public:

	/**
	 * Create cone shape.
	 *
	 * @param r Radius.
	 * @param h Height.
	 * @return
	 *     <p>Cone shape for collision.</p>
	 */
	_OBJECT createConeShape(_FLOAT r,_FLOAT h);

	/**
	 * Create capsule shape.
	 *
	 * @param r Radius.
	 * @param h Height.
	 * @return
	 *     <p>Capsule shape for collision.</p>
	 */
	_OBJECT createCapsuleShape(_FLOAT r,_FLOAT h);

	/**
	 * Create chamfer cylinder shape.
	 *
	 * @param r Radius.
	 * @param h Height.
	 * @return
	 *     <p>Chamfer cylinder shape for collision.</p>
	 */
	_OBJECT createChamferCylinderShape(_FLOAT r,_FLOAT h);

	/**
	 * Create cylinder shape.
	 *
	 * @param r Radius.
	 * @param h Height.
	 * @return
	 *     <p>Cylinder shape for collision.</p>
	 */
	_OBJECT createCylinderShape(_FLOAT r,_FLOAT h);

	/**
	 * Create box shape.
	 *
	 * @param dx X extents.
	 * @param dy Y extents.
	 * @param dz Z extents.
	 * @return
	 *     <p>Box shape for collision.</p>
	 */
	_OBJECT createBoxShape(_FLOAT dx,_FLOAT dy,_FLOAT dz);

	/**
	 * Create sphere shape.
	 *
	 * @param rx X radius.
	 * @param ry Y radius.
	 * @param rz Z radius.
	 * @return
	 *     <p>Box shape for collision.</p>
	 */
	_OBJECT createSphereShape(_FLOAT rx,_FLOAT ry,_FLOAT rz);

	/**
	 * Create convex shape.
	 *
	 * @param count Count of vertex.
	 * @param vertices Vectors of vertices.
	 * @return
	 *     <p>Box shape for collision.</p>
	 */
	_OBJECT createConvexShape(_INTEGER count,const _FLOAT* vertices);

public:

	/**
	 * Create box shape.
	 *
	 * @param dx X extents.
	 * @param dy Y extents.
	 * @param dz Z extents.
	 * @param matrix Matrix of shape.
	 * @return
	 *     <p>Box shape for collision.</p>
	 */
	_OBJECT createBoxShape(_FLOAT dx,_FLOAT dy,_FLOAT dz,const C4DMatrix4& matrix);

	/**
	 * Create cone shape.
	 *
	 * @param r Radius.
	 * @param h Height.
	 * @param matrix Matrix of shape.
	 * @return
	 *     <p>Cone shape for collision.</p>
	 */
	_OBJECT createConeShape(_FLOAT r,_FLOAT h,const C4DMatrix4& matrix);

	/**
	 * Create capsule shape.
	 *
	 * @param r Radius.
	 * @param h Height.
	 * @param matrix Matrix of shape.
	 * @return
	 *     <p>Capsule shape for collision.</p>
	 */
	_OBJECT createCapsuleShape(_FLOAT r,_FLOAT h,const C4DMatrix4& matrix);

	/**
	 * Create chamfer cylinder shape.
	 *
	 * @param r Radius.
	 * @param h Height.
	 * @param matrix Matrix of shape.
	 * @return
	 *     <p>Chamfer cylinder shape for collision.</p>
	 */
	_OBJECT createChamferCylinderShape(_FLOAT r,_FLOAT h,const C4DMatrix4& matrix);

	/**
	 * Create cylinder shape.
	 *
	 * @param r Radius.
	 * @param h Height.
	 * @param matrix Matrix of shape.
	 * @return
	 *     <p>Cylinder shape for collision.</p>
	 */
	_OBJECT createCylinderShape(_FLOAT r,_FLOAT h,const C4DMatrix4& matrix);

	/**
	 * Create sphere shape.
	 *
	 * @param rx X radius.
	 * @param ry Y radius.
	 * @param rz Z radius.
	 * @param matrix Matrix of shape.
	 * @return
	 *     <p>Sphere shape for collision.</p>
	 */
	_OBJECT createSphereShape(_FLOAT rx,_FLOAT ry,_FLOAT rz,const C4DMatrix4& matrix);

	/**
	 * Create convex shape.
	 *
	 * @param count Count of vertex.
	 * @param vertices Vectors of vertices.
	 * @param matrix Matrix of shape.
	 * @return
	 *     <p>Convex shape for collision.</p>
	 */
	_OBJECT createConvexShape(_INTEGER count,const _FLOAT* vertices,const C4DMatrix4& matrix);

public:

	/**
	 * Create mesh shape.
	 *
	 * @param count Count of index.
	 * @param indices Index of mesh.
	 * @param vertices Vertex of mesh.
	 * @return
	 *     <p>Shape for collision.</p>
	 */
	_OBJECT createMeshShape(_INTEGER count,_SHORT* indices,_FLOAT* vertices);

	/**
	 * Create height field shape.
	 *
	 * @param rows Row of grid.
	 * @param columns Column of grid.
	 * @param quadWidth Width of quad.
	 * @param quadHeight Height of quad.
	 * @param vertices Vertex of quad.
	 * @return
	 *     <p>Shape for collision.</p>
	 */
	_OBJECT createHeightFieldShape(_INTEGER rows,_INTEGER columns,_FLOAT quadWidth,_FLOAT quadHeight,_FLOAT* vertices);

};

///////////////////////////////////////////////////////////////////////////////
#endif //_SHAPE_MANAGER_H_
