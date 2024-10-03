///////////////////////////////////////////////////////////////////////////////
//
// PrimitiveAttribute.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PRIMITIVE_ATTRIBUTE_H_
#define _PRIMITIVE_ATTRIBUTE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DType.h"

///////////////////////////////////////////////////////////////////////////////
//
// PrimitiveAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CPrimitiveAttribute
{
public:

	/**
	 * All primitive types.
	 */
	static const _INTEGER nullPrimitive;

	static const _INTEGER polygon4Primitive;
	static const _INTEGER polygon6Primitive;
	static const _INTEGER polygon8Primitive;
	static const _INTEGER polygon12Primitive;
	static const _INTEGER polygon20Primitive;

	static const _INTEGER circle0Primitive;
	static const _INTEGER circle3Primitive;
	static const _INTEGER circle4Primitive;
	static const _INTEGER circle5Primitive;
	static const _INTEGER circle6Primitive;

	static const _INTEGER triangle0Primitive;
	static const _INTEGER quadrangle0Primitive;

	static const _INTEGER grid4x3Primitive;
	static const _INTEGER grid20x15Primitive;
	static const _INTEGER ground80x60Primitive;
	static const _INTEGER ground320x240Primitive;
	static const _INTEGER ground640x480Primitive;

	static const _INTEGER cone0Primitive;
	static const _INTEGER cone3Primitive;
	static const _INTEGER cone4Primitive;
	static const _INTEGER cone6Primitive;

	static const _INTEGER cylinder0Primitive;
	static const _INTEGER cylinder3Primitive;
	static const _INTEGER cylinder5Primitive;
	static const _INTEGER cylinder6Primitive;

	static const _INTEGER sphere0Primitive;
	static const _INTEGER hemisphere0Primitive;
	
	static const _INTEGER floor0Primitive;
	static const _INTEGER cuboid0Primitive;

	static const _INTEGER frustum0Primitive;
	static const _INTEGER frustum3Primitive;
	static const _INTEGER frustum4Primitive;
	static const _INTEGER frustum6Primitive;

	static const _INTEGER capsule0Primitive;
	static const _INTEGER chamferCylider0Primitive;

private:

	/**
	 * Type of primitive.
	 */
	_INTEGER type;

public:

	//Rings and segments.
	_INTEGER rings;
	_INTEGER segments;
	
	/**
	 * Union of primitive.
	 */
	union tagPrimitiveData
	{
		struct tagD3DXPolygon
		{
			_FLOAT radius;

		} polygon;

		struct tagD3DXSphere
		{
			_FLOAT radius;

		} sphere;

		struct tagD3DXHemisphere
		{
			_FLOAT radius;

		} hemisphere;

		struct tagD3DXCone
		{
			_FLOAT radius,height;

		} cone;

		struct tagD3DXCapsule
		{
			_FLOAT radius,height;

		} capsule;

		struct tagD3DXChamferCylinder
		{
			_FLOAT radius,height;

		} chamferCylinder;

		struct tagD3DXCylinder
		{
			_FLOAT radius,height;

		} cylinder;

		struct tagD3DXFrustum
		{
			_FLOAT topRadius;
			_FLOAT height;
			_FLOAT bottomRadius;

		} frustum;

		struct tagD3DXCuboid
		{
			_FLOAT width,height,depth;

		} cuboid;

		struct tagD3DXCircle
		{
			_FLOAT radius;

		} circle;

		struct tagD3DXTriangle
		{
			//Point(x,y,z)
			_FLOAT3 a,b,c;

		} triangle;

		struct tagD3DXQuadrangle
		{
			//Point(x,y)
			_FLOAT2 a,b,c,d;

		} quadrangle;

		struct tagD3DXGrid
		{
			//Width.
			//Width of quad.
			_FLOAT quadWidth;
			//Height.
			//Height of quad.
			_FLOAT quadHeight;

		} grid;

	} primitiveData;

public:
	CPrimitiveAttribute(void);
	CPrimitiveAttribute(const CPrimitiveAttribute& attribute);
	virtual ~CPrimitiveAttribute(void);

	CPrimitiveAttribute& operator = (const CPrimitiveAttribute& attribute);

public:

	/**
	 * Copy primitive.
	 *
	 * @param attribute Primitive attribute.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void copyPrimitive(const CPrimitiveAttribute& attribute);

public:

	/**
	 * Get type.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Type of primitive.</p>
	 */
	_INTEGER getType() const;

	/**
	 * Set type.
	 *
	 * @param type Type of primitive.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setType(_INTEGER type);

public:

	/**
	 * Whether is equal.
	 *
	 * @param attribute Primitive attribute.
	 * @return
	 *     <p>Return true, if it is equal.</p>
	 */
	_BOOL isEqual(const CPrimitiveAttribute& attribute) const;

};

///////////////////////////////////////////////////////////////////////////////
#endif //_PRIMITIVE_ATTRIBUTE_H_