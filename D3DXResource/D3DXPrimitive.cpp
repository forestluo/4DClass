///////////////////////////////////////////////////////////////////////////////
//
// D3DXPrimitive.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXPrimitive.h"

////////////////////////////////////////////////////////////////////////////////
//
// Including
//
////////////////////////////////////////////////////////////////////////////////

#include "DxMath.h"
#include "D3DXVertex.h"

#include "GridAttribute.h"
#include "ConeAttribute.h"
#include "SliceAttribute.h"
#include "CircleAttribute.h"
#include "SphereAttribute.h"
#include "PolygonAttribute.h"
#include "CuboidAttribute.h"
#include "CapsuleAttribute.h"
#include "FrustumAttribute.h"
#include "CylinderAttribute.h"
#include "TriangleAttribute.h"
#include "QuadrangleAttribute.h"
#include "HemisphereAttribute.h"
#include "ChamferCylinderAttribute.h"

////////////////////////////////////////////////////////////////////////////////
//
// XNA
//
////////////////////////////////////////////////////////////////////////////////

#include <xnamath.h>

#include "xnaCollision.h"
using namespace XNA;

//////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CD3DXPrimitive::base(L"CD3DXPrimitive",L"CD3DXRenderable");

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXPrimitive
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXPrimitive::CD3DXPrimitive(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXPrimitive
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXPrimitive::CD3DXPrimitive(_INTEGER type)
{
	//Set primitive attribute.
	setPrimitiveAttribute(type);
}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXPrimitive
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXPrimitive::CD3DXPrimitive(const CPrimitiveAttribute& attribute)
{
	//Set primitive attribute.
	setPrimitiveAttribute(attribute);
}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXPrimitive
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXPrimitive::~CD3DXPrimitive(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// GetIndexSize
//
/////////////////////////////////////////////////////////////////////////////////

_INTEGER CD3DXPrimitive::getIndexSize() const
{
	//Return result.
	return sizeof(_INTEGER3);
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetVertexSize
//
/////////////////////////////////////////////////////////////////////////////////

_INTEGER CD3DXPrimitive::getVertexSize() const
{
	//Return result.
	return sizeof(_4DVERTEX3);
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetRingsCount
//
/////////////////////////////////////////////////////////////////////////////////
	
_INTEGER CD3DXPrimitive::getRingsCount() const
{
	//Get type.
	_INTEGER type = attribute.getType();
#ifdef _DEBUG
	assert(type != CPrimitiveAttribute::nullPrimitive);
#endif
	//Check type.
	if(type == CPrimitiveAttribute::triangle0Primitive)
	{
		//Return result.
		return CTriangleAttribute::triangle0.getRings();
	}
	else if(type == CPrimitiveAttribute::grid4x3Primitive)
	{
		//Return result.
		return CGridAttribute::grid4x3.getRings();
	}
	else if(type == CPrimitiveAttribute::grid20x15Primitive)
	{
		//Return result.
		return CGridAttribute::grid20x15.getRings();
	}
	else if(type == CPrimitiveAttribute::ground80x60Primitive)
	{
		//Return result.
		return CGridAttribute::ground80x60.getRings();
	}
	else if(type == CPrimitiveAttribute::ground320x240Primitive)
	{
		//Return result.
		return CGridAttribute::ground320x240.getRings();
	}
	else if(type == CPrimitiveAttribute::ground640x480Primitive)
	{
		//Return result.
		return CGridAttribute::ground640x480.getRings();
	}
	else if(type == CPrimitiveAttribute::circle0Primitive)
	{
		//Return result.
		return CCircleAttribute::circle0.getRings();
	}
	else if(type == CPrimitiveAttribute::circle3Primitive)
	{
		//Return result.
		return CCircleAttribute::circle3.getRings();
	}
	else if(type == CPrimitiveAttribute::circle4Primitive)
	{
		//Return result.
		return CCircleAttribute::circle4.getRings();
	}
	else if(type == CPrimitiveAttribute::circle5Primitive)
	{
		//Return result.
		return CCircleAttribute::circle5.getRings();
	}
	else if(type == CPrimitiveAttribute::circle6Primitive)
	{
		//Return result.
		return CCircleAttribute::circle6.getRings();
	}
	else if(type == CPrimitiveAttribute::polygon4Primitive)
	{
		//Return result.
		return CPolygonAttribute::polygon4.getRings();
	}
	else if(type == CPrimitiveAttribute::polygon6Primitive)
	{
		//Return result.
		return CPolygonAttribute::polygon6.getRings();
	}
	else if(type == CPrimitiveAttribute::polygon8Primitive)
	{
		//Return result.
		return CPolygonAttribute::polygon8.getRings();
	}
	else if(type == CPrimitiveAttribute::polygon12Primitive)
	{
		//Return result.
		return CPolygonAttribute::polygon12.getRings();
	}
	else if(type == CPrimitiveAttribute::polygon20Primitive)
	{
		//Return result.
		return CPolygonAttribute::polygon20.getRings();
	}
	else if(type == CPrimitiveAttribute::quadrangle0Primitive)
	{
		//Return result.
		return CQuadrangleAttribute::quadrangle0.getRings();
	}
	else if(type == CPrimitiveAttribute::cone0Primitive)
	{
		//Return result.
		return CConeAttribute::cone0.getRings();
	}
	else if(type == CPrimitiveAttribute::cone3Primitive)
	{
		//Return result.
		return CConeAttribute::cone3.getRings();
	}
	else if(type == CPrimitiveAttribute::cone4Primitive)
	{
		//Return result.
		return CConeAttribute::cone4.getRings();
	}
	else if(type == CPrimitiveAttribute::cone6Primitive)
	{
		//Return result.
		return CConeAttribute::cone6.getRings();
	}
	else if(type == CPrimitiveAttribute::cuboid0Primitive)
	{
		//Return result.
		return CCuboidAttribute::cuboid0.getRings();
	}
	else if(type == CPrimitiveAttribute::floor0Primitive)
	{
		//Return result.
		return CSliceAttribute::floor0.getRings();
	}
	else if(type == CPrimitiveAttribute::capsule0Primitive)
	{
		//Return result.
		return CCapsuleAttribute::capsule0.getRings();
	}
	else if(type == CPrimitiveAttribute::chamferCylider0Primitive)
	{
		//Return result.
		return CChamferCylinderAttribute::chamferCylinder0.getRings();
	}
	else if(type == CPrimitiveAttribute::frustum0Primitive)
	{
		//Return result.
		return CFrustumAttribute::frustum0.getRings();
	}
	else if(type == CPrimitiveAttribute::frustum3Primitive)
	{
		//Return result.
		return CFrustumAttribute::frustum3.getRings();
	}
	else if(type == CPrimitiveAttribute::frustum4Primitive)
	{
		//Return result.
		return CFrustumAttribute::frustum4.getRings();
	}
	else if(type == CPrimitiveAttribute::frustum6Primitive)
	{
		//Return result.
		return CFrustumAttribute::frustum6.getRings();
	}
	else if(type == CPrimitiveAttribute::cylinder0Primitive)
	{
		//Return result.
		return CCylinderAttribute::cylinder0.getRings();
	}
	else if(type == CPrimitiveAttribute::cylinder3Primitive)
	{
		//Return result.
		return CCylinderAttribute::cylinder3.getRings();
	}
	else if(type == CPrimitiveAttribute::cylinder5Primitive)
	{
		//Return result.
		return CCylinderAttribute::cylinder5.getRings();
	}
	else if(type == CPrimitiveAttribute::cylinder6Primitive)
	{
		//Return result.
		return CCylinderAttribute::cylinder6.getRings();
	}
	else if(type == CPrimitiveAttribute::sphere0Primitive)
	{
		//Return result.
		return CSphereAttribute::sphere0.getRings();
	}
	else if(type == CPrimitiveAttribute::hemisphere0Primitive)
	{
		//Return result.
		return CHemisphereAttribute::hemisphere0.getRings();
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
	//Return result.
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetSegmentsCount
//
/////////////////////////////////////////////////////////////////////////////////
	
_INTEGER CD3DXPrimitive::getSegmentsCount() const
{
	//Get type.
	_INTEGER type = attribute.getType();
#ifdef _DEBUG
	assert(type != CPrimitiveAttribute::nullPrimitive);
#endif
	//Check type.
	if(type == CPrimitiveAttribute::triangle0Primitive)
	{
		//Return result.
		return CTriangleAttribute::triangle0.getSegments();
	}
	else if(type == CPrimitiveAttribute::grid4x3Primitive)
	{
		//Return result.
		return CGridAttribute::grid4x3.getSegments();
	}
	else if(type == CPrimitiveAttribute::grid20x15Primitive)
	{
		//Return result.
		return CGridAttribute::grid20x15.getSegments();
	}
	else if(type == CPrimitiveAttribute::ground80x60Primitive)
	{
		//Return result.
		return CGridAttribute::ground80x60.getSegments();
	}
	else if(type == CPrimitiveAttribute::ground320x240Primitive)
	{
		//Return result.
		return CGridAttribute::ground320x240.getSegments();
	}
	else if(type == CPrimitiveAttribute::ground640x480Primitive)
	{
		//Return result.
		return CGridAttribute::ground640x480.getSegments();
	}
	else if(type == CPrimitiveAttribute::circle0Primitive)
	{
		//Return result.
		return CCircleAttribute::circle0.getSegments();
	}
	else if(type == CPrimitiveAttribute::circle3Primitive)
	{
		//Return result.
		return CCircleAttribute::circle3.getSegments();
	}
	else if(type == CPrimitiveAttribute::circle4Primitive)
	{
		//Return result.
		return CCircleAttribute::circle4.getSegments();
	}
	else if(type == CPrimitiveAttribute::circle5Primitive)
	{
		//Return result.
		return CCircleAttribute::circle5.getSegments();
	}
	else if(type == CPrimitiveAttribute::circle6Primitive)
	{
		//Return result.
		return CCircleAttribute::circle6.getSegments();
	}
	else if(type == CPrimitiveAttribute::polygon4Primitive)
	{
		//Return result.
		return CPolygonAttribute::polygon4.getSegments();
	}
	else if(type == CPrimitiveAttribute::polygon6Primitive)
	{
		//Return result.
		return CPolygonAttribute::polygon6.getSegments();
	}
	else if(type == CPrimitiveAttribute::polygon8Primitive)
	{
		//Return result.
		return CPolygonAttribute::polygon8.getSegments();
	}
	else if(type == CPrimitiveAttribute::polygon12Primitive)
	{
		//Return result.
		return CPolygonAttribute::polygon12.getSegments();
	}
	else if(type == CPrimitiveAttribute::polygon20Primitive)
	{
		//Return result.
		return CPolygonAttribute::polygon20.getSegments();
	}
	else if(type == CPrimitiveAttribute::quadrangle0Primitive)
	{
		//Return result.
		return CQuadrangleAttribute::quadrangle0.getSegments();
	}
	else if(type == CPrimitiveAttribute::cone0Primitive)
	{
		//Return result.
		return CConeAttribute::cone0.getSegments();
	}
	else if(type == CPrimitiveAttribute::cone3Primitive)
	{
		//Return result.
		return CConeAttribute::cone3.getSegments();
	}
	else if(type == CPrimitiveAttribute::cone4Primitive)
	{
		//Return result.
		return CConeAttribute::cone4.getSegments();
	}
	else if(type == CPrimitiveAttribute::cone6Primitive)
	{
		//Return result.
		return CConeAttribute::cone6.getSegments();
	}
	else if(type == CPrimitiveAttribute::cuboid0Primitive)
	{
		//Return result.
		return CCuboidAttribute::cuboid0.getSegments();
	}
	else if(type == CPrimitiveAttribute::floor0Primitive)
	{
		//Return result.
		return CSliceAttribute::floor0.getSegments();
	}
	else if(type == CPrimitiveAttribute::capsule0Primitive)
	{
		//Return result.
		return CCapsuleAttribute::capsule0.getSegments();
	}
	else if(type == CPrimitiveAttribute::chamferCylider0Primitive)
	{
		//Return result.
		return CChamferCylinderAttribute::chamferCylinder0.getSegments();
	}
	else if(type == CPrimitiveAttribute::frustum0Primitive)
	{
		//Return result.
		return CFrustumAttribute::frustum0.getSegments();
	}
	else if(type == CPrimitiveAttribute::frustum3Primitive)
	{
		//Return result.
		return CFrustumAttribute::frustum3.getSegments();
	}
	else if(type == CPrimitiveAttribute::frustum4Primitive)
	{
		//Return result.
		return CFrustumAttribute::frustum4.getSegments();
	}
	else if(type == CPrimitiveAttribute::frustum6Primitive)
	{
		//Return result.
		return CFrustumAttribute::frustum6.getSegments();
	}
	else if(type == CPrimitiveAttribute::cylinder0Primitive)
	{
		//Return result.
		return CCylinderAttribute::cylinder0.getSegments();
	}
	else if(type == CPrimitiveAttribute::cylinder3Primitive)
	{
		//Return result.
		return CCylinderAttribute::cylinder3.getSegments();
	}
	else if(type == CPrimitiveAttribute::cylinder5Primitive)
	{
		//Return result.
		return CCylinderAttribute::cylinder5.getSegments();
	}
	else if(type == CPrimitiveAttribute::cylinder6Primitive)
	{
		//Return result.
		return CCylinderAttribute::cylinder6.getSegments();
	}
	else if(type == CPrimitiveAttribute::sphere0Primitive)
	{
		//Return result.
		return CSphereAttribute::sphere0.getSegments();
	}
	else if(type == CPrimitiveAttribute::hemisphere0Primitive)
	{
		//Return result.
		return CHemisphereAttribute::hemisphere0.getSegments();
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
	//Return result.
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetIndexCount
//
/////////////////////////////////////////////////////////////////////////////////

_INTEGER CD3DXPrimitive::getIndexCount() const
{
	//Get type.
	_INTEGER type = attribute.getType();
#ifdef _DEBUG
	assert(type != CPrimitiveAttribute::nullPrimitive);
#endif
	//Check type.
	if(type == CPrimitiveAttribute::triangle0Primitive)
	{
		//Return result.
		return CTriangleAttribute::triangle0.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::grid4x3Primitive)
	{
		//Return result.
		return CGridAttribute::grid4x3.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::grid20x15Primitive)
	{
		//Return result.
		return CGridAttribute::grid20x15.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::ground80x60Primitive)
	{
		//Return result.
		return CGridAttribute::ground80x60.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::ground320x240Primitive)
	{
		//Return result.
		return CGridAttribute::ground320x240.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::ground640x480Primitive)
	{
		//Return result.
		return CGridAttribute::ground640x480.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::circle0Primitive)
	{
		//Return result.
		return CCircleAttribute::circle0.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::circle3Primitive)
	{
		//Return result.
		return CCircleAttribute::circle3.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::circle4Primitive)
	{
		//Return result.
		return CCircleAttribute::circle4.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::circle5Primitive)
	{
		//Return result.
		return CCircleAttribute::circle5.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::circle6Primitive)
	{
		//Return result.
		return CCircleAttribute::circle6.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::polygon4Primitive)
	{
		//Return result.
		return CPolygonAttribute::polygon4.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::polygon6Primitive)
	{
		//Return result.
		return CPolygonAttribute::polygon6.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::polygon8Primitive)
	{
		//Return result.
		return CPolygonAttribute::polygon8.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::polygon12Primitive)
	{
		//Return result.
		return CPolygonAttribute::polygon12.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::polygon20Primitive)
	{
		//Return result.
		return CPolygonAttribute::polygon20.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::quadrangle0Primitive)
	{
		//Return result.
		return CQuadrangleAttribute::quadrangle0.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::cone0Primitive)
	{
		//Return result.
		return CConeAttribute::cone0.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::cone3Primitive)
	{
		//Return result.
		return CConeAttribute::cone3.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::cone4Primitive)
	{
		//Return result.
		return CConeAttribute::cone4.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::cone6Primitive)
	{
		//Return result.
		return CConeAttribute::cone6.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::cuboid0Primitive)
	{
		//Return result.
		return CCuboidAttribute::cuboid0.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::floor0Primitive)
	{
		//Return result.
		return CSliceAttribute::floor0.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::capsule0Primitive)
	{
		//Return result.
		return CCapsuleAttribute::capsule0.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::chamferCylider0Primitive)
	{
		//Return result.
		return CChamferCylinderAttribute::chamferCylinder0.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::frustum0Primitive)
	{
		//Return result.
		return CFrustumAttribute::frustum0.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::frustum3Primitive)
	{
		//Return result.
		return CFrustumAttribute::frustum3.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::frustum4Primitive)
	{
		//Return result.
		return CFrustumAttribute::frustum4.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::frustum6Primitive)
	{
		//Return result.
		return CFrustumAttribute::frustum6.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::cylinder0Primitive)
	{
		//Return result.
		return CCylinderAttribute::cylinder0.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::cylinder3Primitive)
	{
		//Return result.
		return CCylinderAttribute::cylinder3.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::cylinder5Primitive)
	{
		//Return result.
		return CCylinderAttribute::cylinder5.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::cylinder6Primitive)
	{
		//Return result.
		return CCylinderAttribute::cylinder6.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::sphere0Primitive)
	{
		//Return result.
		return CSphereAttribute::sphere0.getIndexCount();
	}
	else if(type == CPrimitiveAttribute::hemisphere0Primitive)
	{
		//Return result.
		return CHemisphereAttribute::hemisphere0.getIndexCount();
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
	//Return result.
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetVertexCount
//
/////////////////////////////////////////////////////////////////////////////////

_INTEGER CD3DXPrimitive::getVertexCount() const
{
	//Get type.
	_INTEGER type = attribute.getType();
#ifdef _DEBUG
	assert(type != CPrimitiveAttribute::nullPrimitive);
#endif
	//Check type.
	if(type == CPrimitiveAttribute::triangle0Primitive)
	{
		//Return result.
		return CTriangleAttribute::triangle0.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::grid4x3Primitive)
	{
		//Return result.
		return CGridAttribute::grid4x3.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::grid20x15Primitive)
	{
		//Return result.
		return CGridAttribute::grid20x15.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::ground80x60Primitive)
	{
		//Return result.
		return CGridAttribute::ground80x60.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::ground320x240Primitive)
	{
		//Return result.
		return CGridAttribute::ground320x240.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::ground640x480Primitive)
	{
		//Return result.
		return CGridAttribute::ground640x480.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::circle0Primitive)
	{
		//Return result.
		return CCircleAttribute::circle0.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::circle3Primitive)
	{
		//Return result.
		return CCircleAttribute::circle3.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::circle4Primitive)
	{
		//Return result.
		return CCircleAttribute::circle4.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::circle5Primitive)
	{
		//Return result.
		return CCircleAttribute::circle5.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::circle6Primitive)
	{
		//Return result.
		return CCircleAttribute::circle6.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::polygon4Primitive)
	{
		//Return result.
		return CPolygonAttribute::polygon4.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::polygon6Primitive)
	{
		//Return result.
		return CPolygonAttribute::polygon6.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::polygon8Primitive)
	{
		//Return result.
		return CPolygonAttribute::polygon8.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::polygon12Primitive)
	{
		//Return result.
		return CPolygonAttribute::polygon12.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::polygon20Primitive)
	{
		//Return result.
		return CPolygonAttribute::polygon20.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::quadrangle0Primitive)
	{
		//Return result.
		return CQuadrangleAttribute::quadrangle0.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::cone0Primitive)
	{
		//Return result.
		return CConeAttribute::cone0.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::cone3Primitive)
	{
		//Return result.
		return CConeAttribute::cone3.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::cone4Primitive)
	{
		//Return result.
		return CConeAttribute::cone4.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::cone6Primitive)
	{
		//Return result.
		return CConeAttribute::cone6.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::cuboid0Primitive)
	{
		//Return result.
		return CCuboidAttribute::cuboid0.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::floor0Primitive)
	{
		//Return result.
		return CSliceAttribute::floor0.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::capsule0Primitive)
	{
		//Return result.
		return CCapsuleAttribute::capsule0.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::chamferCylider0Primitive)
	{
		//Return result.
		return CChamferCylinderAttribute::chamferCylinder0.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::frustum0Primitive)
	{
		//Return result.
		return CFrustumAttribute::frustum0.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::frustum3Primitive)
	{
		//Return result.
		return CFrustumAttribute::frustum3.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::frustum4Primitive)
	{
		//Return result.
		return CFrustumAttribute::frustum4.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::frustum6Primitive)
	{
		//Return result.
		return CFrustumAttribute::frustum6.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::cylinder0Primitive)
	{
		//Return result.
		return CCylinderAttribute::cylinder0.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::cylinder3Primitive)
	{
		//Return result.
		return CCylinderAttribute::cylinder3.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::cylinder5Primitive)
	{
		//Return result.
		return CCylinderAttribute::cylinder5.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::cylinder6Primitive)
	{
		//Return result.
		return CCylinderAttribute::cylinder6.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::sphere0Primitive)
	{
		//Return result.
		return CSphereAttribute::sphere0.getVertexCount();
	}
	else if(type == CPrimitiveAttribute::hemisphere0Primitive)
	{
		//Return result.
		return CHemisphereAttribute::hemisphere0.getVertexCount();
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
	//Return result.
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetPrimitiveAttribute
//
/////////////////////////////////////////////////////////////////////////////////

CPrimitiveAttribute CD3DXPrimitive::getPrimitiveAttribute() const
{
	//Return result.
	return attribute;
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetPrimitiveAttribute
//
/////////////////////////////////////////////////////////////////////////////////

void CD3DXPrimitive::setPrimitiveAttribute(_INTEGER type)
{
#ifdef _DEBUG
	assert(type != CPrimitiveAttribute::nullPrimitive);
	assert(attribute.getType() == CPrimitiveAttribute::nullPrimitive);
#endif
	//Check type.
	if(type == CPrimitiveAttribute::triangle0Primitive)
	{
		//Copy box.
		copyBox(CTriangleAttribute::triangle0.getBoxAttribute());
		//Set attribute.
		attribute = CTriangleAttribute::triangle0.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::grid4x3Primitive)
	{
		//Copy box.
		copyBox(CGridAttribute::grid4x3.getBoxAttribute());
		//Set attribute.
		attribute = CGridAttribute::grid4x3.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::grid20x15Primitive)
	{
		//Copy box.
		copyBox(CGridAttribute::grid20x15.getBoxAttribute());
		//Set attribute.
		attribute = CGridAttribute::grid20x15.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::ground80x60Primitive)
	{
		//Copy box.
		copyBox(CGridAttribute::ground80x60.getBoxAttribute());
		//Set attribute.
		attribute = CGridAttribute::ground80x60.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::ground320x240Primitive)
	{
		//Copy box.
		copyBox(CGridAttribute::ground320x240.getBoxAttribute());
		//Set attribute.
		attribute = CGridAttribute::ground320x240.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::ground640x480Primitive)
	{
		//Copy box.
		copyBox(CGridAttribute::ground640x480.getBoxAttribute());
		//Set attribute.
		attribute = CGridAttribute::ground640x480.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::circle0Primitive)
	{
		//Copy box.
		copyBox(CCircleAttribute::circle0.getBoxAttribute());
		//Set attribute.
		attribute = CCircleAttribute::circle0.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::circle3Primitive)
	{
		//Copy box.
		copyBox(CCircleAttribute::circle3.getBoxAttribute());
		//Set attribute.
		attribute = CCircleAttribute::circle3.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::circle4Primitive)
	{
		//Copy box.
		copyBox(CCircleAttribute::circle4.getBoxAttribute());
		//Set attribute.
		attribute = CCircleAttribute::circle4.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::circle5Primitive)
	{
		//Copy box.
		copyBox(CCircleAttribute::circle5.getBoxAttribute());
		//Set attribute.
		attribute = CCircleAttribute::circle5.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::circle6Primitive)
	{
		//Copy box.
		copyBox(CCircleAttribute::circle6.getBoxAttribute());
		//Set attribute.
		attribute = CCircleAttribute::circle6.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::polygon4Primitive)
	{
		//Copy box.
		copyBox(CPolygonAttribute::polygon4.getBoxAttribute());
		//Set attribute.
		attribute = CPolygonAttribute::polygon4.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::polygon6Primitive)
	{
		//Copy box.
		copyBox(CPolygonAttribute::polygon6.getBoxAttribute());
		//Set attribute.
		attribute = CPolygonAttribute::polygon6.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::polygon8Primitive)
	{
		//Copy box.
		copyBox(CPolygonAttribute::polygon8.getBoxAttribute());
		//Set attribute.
		attribute = CPolygonAttribute::polygon8.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::polygon12Primitive)
	{
		//Copy box.
		copyBox(CPolygonAttribute::polygon12.getBoxAttribute());
		//Set attribute.
		attribute = CPolygonAttribute::polygon12.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::polygon20Primitive)
	{
		//Copy box.
		copyBox(CPolygonAttribute::polygon20.getBoxAttribute());
		//Set attribute.
		attribute = CPolygonAttribute::polygon20.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::quadrangle0Primitive)
	{
		//Copy box.
		copyBox(CQuadrangleAttribute::quadrangle0.getBoxAttribute());
		//Set attribute.
		attribute = CQuadrangleAttribute::quadrangle0.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::cone0Primitive)
	{
		//Copy box.
		copyBox(CConeAttribute::cone0.getBoxAttribute());
		//Set attribute.
		attribute = CConeAttribute::cone0.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::cone3Primitive)
	{
		//Copy box.
		copyBox(CConeAttribute::cone3.getBoxAttribute());
		//Set attribute.
		attribute = CConeAttribute::cone3.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::cone4Primitive)
	{
		//Copy box.
		copyBox(CConeAttribute::cone4.getBoxAttribute());
		//Set attribute.
		attribute = CConeAttribute::cone4.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::cone6Primitive)
	{
		//Copy box.
		copyBox(CConeAttribute::cone6.getBoxAttribute());
		//Set attribute.
		attribute = CConeAttribute::cone6.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::cuboid0Primitive)
	{
		//Copy box.
		copyBox(CCuboidAttribute::cuboid0.getBoxAttribute());
		//Set attribute.
		attribute = CCuboidAttribute::cuboid0.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::floor0Primitive)
	{
		//Copy box.
		copyBox(CSliceAttribute::floor0.getBoxAttribute());
		//Set attribute.
		attribute = CSliceAttribute::floor0.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::capsule0Primitive)
	{
		//Copy box.
		copyBox(CCapsuleAttribute::capsule0.getBoxAttribute());
		//Set attribute.
		attribute = CCapsuleAttribute::capsule0.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::chamferCylider0Primitive)
	{
		//Copy box.
		copyBox(CChamferCylinderAttribute::chamferCylinder0.getBoxAttribute());
		//Set attribute.
		attribute = CChamferCylinderAttribute::chamferCylinder0.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::frustum0Primitive)
	{
		//Copy box.
		copyBox(CFrustumAttribute::frustum0.getBoxAttribute());
		//Set attribute.
		attribute = CFrustumAttribute::frustum0.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::frustum3Primitive)
	{
		//Copy box.
		copyBox(CFrustumAttribute::frustum3.getBoxAttribute());
		//Set attribute.
		attribute = CFrustumAttribute::frustum3.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::frustum4Primitive)
	{
		//Copy box.
		copyBox(CFrustumAttribute::frustum4.getBoxAttribute());
		//Set attribute.
		attribute = CFrustumAttribute::frustum4.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::frustum6Primitive)
	{
		//Copy box.
		copyBox(CFrustumAttribute::frustum6.getBoxAttribute());
		//Set attribute.
		attribute = CFrustumAttribute::frustum6.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::cylinder0Primitive)
	{
		//Copy box.
		copyBox(CCylinderAttribute::cylinder0.getBoxAttribute());
		//Set attribute.
		attribute = CCylinderAttribute::cylinder0.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::cylinder3Primitive)
	{
		//Copy box.
		copyBox(CCylinderAttribute::cylinder3.getBoxAttribute());
		//Set attribute.
		attribute = CCylinderAttribute::cylinder3.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::cylinder5Primitive)
	{
		//Copy box.
		copyBox(CCylinderAttribute::cylinder5.getBoxAttribute());
		//Set attribute.
		attribute = CCylinderAttribute::cylinder5.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::cylinder6Primitive)
	{
		//Copy box.
		copyBox(CCylinderAttribute::cylinder6.getBoxAttribute());
		//Set attribute.
		attribute = CCylinderAttribute::cylinder6.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::sphere0Primitive)
	{
		//Copy box.
		copyBox(CSphereAttribute::sphere0.getBoxAttribute());
		//Set attribute.
		attribute = CSphereAttribute::sphere0.getPrimitiveAttribute();
	}
	else if(type == CPrimitiveAttribute::hemisphere0Primitive)
	{
		//Copy box.
		copyBox(CHemisphereAttribute::hemisphere0.getBoxAttribute());
		//Set attribute.
		attribute = CHemisphereAttribute::hemisphere0.getPrimitiveAttribute();
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetPrimitiveAttribute
//
/////////////////////////////////////////////////////////////////////////////////

void CD3DXPrimitive::setPrimitiveAttribute(const CPrimitiveAttribute& attribute)
{
#ifdef _DEBUG
	assert(attribute.getType() != CPrimitiveAttribute::nullPrimitive);
	assert(this->attribute.getType() == attribute.getType() ||
			this->attribute.getType() == CPrimitiveAttribute::nullPrimitive);
#endif
	//Set attribute.
	this->attribute = attribute;
}

/////////////////////////////////////////////////////////////////////////////////
//
// InitializeIndex
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXPrimitive::initializeIndex(LPDIRECT3DINDEXBUFFER9 pIndexBuffer)
{
	//Get type.
	_INTEGER type = attribute.getType();
#ifdef _DEBUG
	assert(type != CPrimitiveAttribute::nullPrimitive);
#endif
	//Check type.
	if(type == CPrimitiveAttribute::triangle0Primitive)
	{
		//Copy index.
		return copyIndex(CTriangleAttribute::triangle0);
	}
	else if(type == CPrimitiveAttribute::grid4x3Primitive)
	{
		//Copy index.
		return copyIndex(CGridAttribute::grid4x3);
	}
	else if(type == CPrimitiveAttribute::grid20x15Primitive)
	{
		//Copy index.
		return copyIndex(CGridAttribute::grid20x15);
	}
	else if(type == CPrimitiveAttribute::ground80x60Primitive)
	{
		//Copy index.
		return copyIndex(CGridAttribute::ground80x60);
	}
	else if(type == CPrimitiveAttribute::ground320x240Primitive)
	{
		//Copy index.
		return copyIndex(CGridAttribute::ground320x240);
	}
	else if(type == CPrimitiveAttribute::ground640x480Primitive)
	{
		//Copy index.
		return copyIndex(CGridAttribute::ground640x480);
	}
	else if(type == CPrimitiveAttribute::circle0Primitive)
	{
		//Copy index.
		return copyIndex(CCircleAttribute::circle0);
	}
	else if(type == CPrimitiveAttribute::circle3Primitive)
	{
		//Copy index.
		return copyIndex(CCircleAttribute::circle3);
	}
	else if(type == CPrimitiveAttribute::circle4Primitive)
	{
		//Copy index.
		return copyIndex(CCircleAttribute::circle4);
	}
	else if(type == CPrimitiveAttribute::circle5Primitive)
	{
		//Copy index.
		return copyIndex(CCircleAttribute::circle5);
	}
	else if(type == CPrimitiveAttribute::circle6Primitive)
	{
		//Copy index.
		return copyIndex(CCircleAttribute::circle6);
	}
	else if(type == CPrimitiveAttribute::polygon4Primitive)
	{
		//Copy index.
		return copyIndex(CPolygonAttribute::polygon4);
	}
	else if(type == CPrimitiveAttribute::polygon6Primitive)
	{
		//Copy index.
		return copyIndex(CPolygonAttribute::polygon6);
	}
	else if(type == CPrimitiveAttribute::polygon8Primitive)
	{
		//Copy index.
		return copyIndex(CPolygonAttribute::polygon8);
	}
	else if(type == CPrimitiveAttribute::polygon12Primitive)
	{
		//Copy index.
		return copyIndex(CPolygonAttribute::polygon12);
	}
	else if(type == CPrimitiveAttribute::polygon20Primitive)
	{
		//Copy index.
		return copyIndex(CPolygonAttribute::polygon20);
	}
	else if(type == CPrimitiveAttribute::quadrangle0Primitive)
	{
		//Copy index.
		return copyIndex(CQuadrangleAttribute::quadrangle0);
	}
	else if(type == CPrimitiveAttribute::cone0Primitive)
	{
		//Copy index.
		return copyIndex(CConeAttribute::cone0);
	}
	else if(type == CPrimitiveAttribute::cone3Primitive)
	{
		//Copy index.
		return copyIndex(CConeAttribute::cone3);
	}
	else if(type == CPrimitiveAttribute::cone4Primitive)
	{
		//Copy index.
		return copyIndex(CConeAttribute::cone4);
	}
	else if(type == CPrimitiveAttribute::cone6Primitive)
	{
		//Copy index.
		return copyIndex(CConeAttribute::cone6);
	}
	else if(type == CPrimitiveAttribute::cuboid0Primitive)
	{
		//Copy index.
		return copyIndex(CCuboidAttribute::cuboid0);
	}
	else if(type == CPrimitiveAttribute::floor0Primitive)
	{
		//Copy index.
		return copyIndex(CSliceAttribute::floor0);
	}
	else if(type == CPrimitiveAttribute::capsule0Primitive)
	{
		//Copy index.
		return copyIndex(CCapsuleAttribute::capsule0);
	}
	else if(type == CPrimitiveAttribute::chamferCylider0Primitive)
	{
		//Copy index.
		return copyIndex(CChamferCylinderAttribute::chamferCylinder0);
	}
	else if(type == CPrimitiveAttribute::frustum0Primitive)
	{
		//Copy index.
		return copyIndex(CFrustumAttribute::frustum0);
	}
	else if(type == CPrimitiveAttribute::frustum3Primitive)
	{
		//Copy index.
		return copyIndex(CFrustumAttribute::frustum3);
	}
	else if(type == CPrimitiveAttribute::frustum4Primitive)
	{
		//Copy index.
		return copyIndex(CFrustumAttribute::frustum4);
	}
	else if(type == CPrimitiveAttribute::frustum6Primitive)
	{
		//Copy index.
		return copyIndex(CFrustumAttribute::frustum6);
	}
	else if(type == CPrimitiveAttribute::cylinder0Primitive)
	{
		//Copy index.
		return copyIndex(CCylinderAttribute::cylinder0);
	}
	else if(type == CPrimitiveAttribute::cylinder3Primitive)
	{
		//Copy index.
		return copyIndex(CCylinderAttribute::cylinder3);
	}
	else if(type == CPrimitiveAttribute::cylinder5Primitive)
	{
		//Copy index.
		return copyIndex(CCylinderAttribute::cylinder5);
	}
	else if(type == CPrimitiveAttribute::cylinder6Primitive)
	{
		//Copy index.
		return copyIndex(CCylinderAttribute::cylinder6);
	}
	else if(type == CPrimitiveAttribute::sphere0Primitive)
	{
		//Copy index.
		return copyIndex(CSphereAttribute::sphere0);
	}
	else if(type == CPrimitiveAttribute::hemisphere0Primitive)
	{
		//Copy index.
		return copyIndex(CHemisphereAttribute::hemisphere0);
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
	//Return fail.
	return E_FAIL;
}

/////////////////////////////////////////////////////////////////////////////////
//
// InitializeVertex
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXPrimitive::initializeVertex(LPDIRECT3DVERTEXBUFFER9 pVertexBuffer)
{
	//Get type.
	_INTEGER type = attribute.getType();
#ifdef _DEBUG
	assert(type != CPrimitiveAttribute::nullPrimitive);
#endif
	//Check type.
	if(type == CPrimitiveAttribute::triangle0Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CTriangleAttribute::triangle0.getPrimitiveAttribute()))
		{
			//Triangle attribute.
			CTriangleAttribute triangle;
			//Initialize.
			triangle.setPrimitiveAttribute(attribute);
			//Copy box
			copyBox(triangle.getBoxAttribute());
			//Copy vertex.
			return copyVertex(triangle);
		}
		else
		{
			//Copy box.
			copyBox(CTriangleAttribute::triangle0.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CTriangleAttribute::triangle0);
		}
	}
	else if(type == CPrimitiveAttribute::grid4x3Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CGridAttribute::grid4x3.getPrimitiveAttribute()))
		{
			//Grid attribute.
			CGridAttribute grid(3,4);
			//Initialize.
			grid.setPrimitiveAttribute(attribute);
			//Copy box
			copyBox(grid.getBoxAttribute());
			//Copy vertex.
			return copyVertex(grid);
		}
		else
		{
			//Copy box.
			copyBox(CGridAttribute::grid4x3.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CGridAttribute::grid4x3);
		}
	}
	else if(type == CPrimitiveAttribute::grid20x15Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CGridAttribute::grid20x15.getPrimitiveAttribute()))
		{
			//Grid attribute.
			CGridAttribute grid(15,20);
			//Initialize.
			grid.setPrimitiveAttribute(attribute);
			//Copy box
			copyBox(grid.getBoxAttribute());
			//Copy vertex.
			return copyVertex(grid);
		}
		else
		{
			//Copy box.
			copyBox(CGridAttribute::grid20x15.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CGridAttribute::grid20x15);
		}
	}
	else if(type == CPrimitiveAttribute::ground80x60Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CGridAttribute::ground80x60.getPrimitiveAttribute()))
		{
			//Grid attribute.
			CGridAttribute grid(60,80);
			//Initialize.
			grid.setPrimitiveAttribute(attribute);
			//Copy box
			copyBox(grid.getBoxAttribute());
			//Copy vertex.
			return copyVertex(grid);
		}
		else
		{
			//Copy box.
			copyBox(CGridAttribute::ground80x60.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CGridAttribute::ground80x60);
		}
	}
	else if(type == CPrimitiveAttribute::ground320x240Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CGridAttribute::ground320x240.getPrimitiveAttribute()))
		{
			//Grid attribute.
			CGridAttribute grid(240,320);
			//Initialize.
			grid.setPrimitiveAttribute(attribute);
			//Copy box
			copyBox(grid.getBoxAttribute());
			//Copy vertex.
			return copyVertex(grid);
		}
		else
		{
			//Copy box.
			copyBox(CGridAttribute::ground320x240.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CGridAttribute::ground320x240);
		}
	}
	else if(type == CPrimitiveAttribute::ground640x480Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CGridAttribute::ground640x480.getPrimitiveAttribute()))
		{
			//Grid attribute.
			CGridAttribute grid(480,640);
			//Initialize.
			grid.setPrimitiveAttribute(attribute);
			//Copy box
			copyBox(grid.getBoxAttribute());
			//Copy vertex.
			return copyVertex(grid);
		}
		else
		{
			//Copy box.
			copyBox(CGridAttribute::ground640x480.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CGridAttribute::ground640x480);
		}
	}
	else if(type == CPrimitiveAttribute::circle0Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CCircleAttribute::circle0.getPrimitiveAttribute()))
		{
			//Circle attribute.
			CCircleAttribute circle;
			//Initialize.
			circle.setPrimitiveAttribute(attribute);
			//Copy box
			copyBox(circle.getBoxAttribute());
			//Copy vertex.
			return copyVertex(circle);
		}
		else
		{
			//Copy box.
			copyBox(CCircleAttribute::circle0.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CCircleAttribute::circle0);
		}
	}
	else if(type == CPrimitiveAttribute::circle3Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CCircleAttribute::circle3.getPrimitiveAttribute()))
		{
			//Circle attribute.
			CCircleAttribute circle(3);
			//Initialize.
			circle.setPrimitiveAttribute(attribute);
			//Copy box
			copyBox(circle.getBoxAttribute());
			//Copy vertex.
			return copyVertex(circle);
		}
		else
		{
			//Copy box.
			copyBox(CCircleAttribute::circle3.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CCircleAttribute::circle3);
		}
	}
	else if(type == CPrimitiveAttribute::circle4Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CCircleAttribute::circle4.getPrimitiveAttribute()))
		{
			//Circle attribute.
			CCircleAttribute circle(4);
			//Initialize.
			circle.setPrimitiveAttribute(attribute);
			//Copy box
			copyBox(circle.getBoxAttribute());
			//Copy vertex.
			return copyVertex(circle);
		}
		else
		{
			//Copy box.
			copyBox(CCircleAttribute::circle4.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CCircleAttribute::circle4);
		}
	}
	else if(type == CPrimitiveAttribute::circle5Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CCircleAttribute::circle5.getPrimitiveAttribute()))
		{
			//Circle attribute.
			CCircleAttribute circle(5);
			//Initialize.
			circle.setPrimitiveAttribute(attribute);
			//Copy box
			copyBox(circle.getBoxAttribute());
			//Copy vertex.
			return copyVertex(circle);
		}
		else
		{
			//Copy box.
			copyBox(CCircleAttribute::circle5.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CCircleAttribute::circle5);
		}
	}
	else if(type == CPrimitiveAttribute::circle6Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CCircleAttribute::circle6.getPrimitiveAttribute()))
		{
			//Circle attribute.
			CCircleAttribute circle(6);
			//Initialize.
			circle.setPrimitiveAttribute(attribute);
			//Copy box
			copyBox(circle.getBoxAttribute());
			//Copy vertex.
			return copyVertex(circle);
		}
		else
		{
			//Copy box.
			copyBox(CCircleAttribute::circle6.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CCircleAttribute::circle6);
		}
	}
	else if(type == CPrimitiveAttribute::polygon4Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CPolygonAttribute::polygon4.getPrimitiveAttribute()))
		{
			//Polygon attribute.
			CPolygonAttribute polygon(4);
			//Initialize.
			polygon.setPrimitiveAttribute(attribute);
			//Copy box
			copyBox(polygon.getBoxAttribute());
			//Copy vertex.
			return copyVertex(polygon);
		}
		else
		{
			//Copy box.
			copyBox(CPolygonAttribute::polygon4.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CPolygonAttribute::polygon4);
		}
	}
	else if(type == CPrimitiveAttribute::polygon6Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CPolygonAttribute::polygon6.getPrimitiveAttribute()))
		{
			//Polygon attribute.
			CPolygonAttribute polygon(6);
			//Initialize.
			polygon.setPrimitiveAttribute(attribute);
			//Copy box
			copyBox(polygon.getBoxAttribute());
			//Copy vertex.
			return copyVertex(polygon);
		}
		else
		{
			//Copy box.
			copyBox(CPolygonAttribute::polygon6.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CPolygonAttribute::polygon6);
		}
	}
	else if(type == CPrimitiveAttribute::polygon8Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CPolygonAttribute::polygon8.getPrimitiveAttribute()))
		{
			//Polygon attribute.
			CPolygonAttribute polygon(8);
			//Initialize.
			polygon.setPrimitiveAttribute(attribute);
			//Copy box
			copyBox(polygon.getBoxAttribute());
			//Copy vertex.
			return copyVertex(polygon);
		}
		else
		{
			//Copy box.
			copyBox(CPolygonAttribute::polygon8.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CPolygonAttribute::polygon8);
		}
	}
	else if(type == CPrimitiveAttribute::polygon12Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CPolygonAttribute::polygon12.getPrimitiveAttribute()))
		{
			//Polygon attribute.
			CPolygonAttribute polygon(12);
			//Initialize.
			polygon.setPrimitiveAttribute(attribute);
			//Copy box
			copyBox(polygon.getBoxAttribute());
			//Copy vertex.
			return copyVertex(polygon);
		}
		else
		{
			//Copy box.
			copyBox(CPolygonAttribute::polygon12.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CPolygonAttribute::polygon12);
		}
	}
	else if(type == CPrimitiveAttribute::polygon20Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CPolygonAttribute::polygon20.getPrimitiveAttribute()))
		{
			//Polygon attribute.
			CPolygonAttribute polygon(20);
			//Initialize.
			polygon.setPrimitiveAttribute(attribute);
			//Copy box
			copyBox(polygon.getBoxAttribute());
			//Copy vertex.
			return copyVertex(polygon);
		}
		else
		{
			//Copy box.
			copyBox(CPolygonAttribute::polygon20.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CPolygonAttribute::polygon20);
		}
	}
	else if(type == CPrimitiveAttribute::quadrangle0Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CQuadrangleAttribute::quadrangle0.getPrimitiveAttribute()))
		{
			//Quadrangle attribute.
			CQuadrangleAttribute quadrangle;
			//Initialize.
			quadrangle.setPrimitiveAttribute(attribute);
			//Copy box.
			copyBox(quadrangle.getBoxAttribute());
			//Copy vertex.
			return copyVertex(quadrangle);
		}
		else
		{
			//Copy box.
			copyBox(CQuadrangleAttribute::quadrangle0.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CQuadrangleAttribute::quadrangle0);
		}
	}
	else if(type == CPrimitiveAttribute::cone0Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CConeAttribute::cone0.getPrimitiveAttribute()))
		{
			//Cone attribute.
			CConeAttribute cone;
			//Initialize.
			cone.setPrimitiveAttribute(attribute);
			//Copy box.
			copyBox(cone.getBoxAttribute());
			//Copy vertex.
			return copyVertex(cone);
		}
		else
		{
			//Copy box.
			copyBox(CConeAttribute::cone0.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CConeAttribute::cone0);
		}
	}
	else if(type == CPrimitiveAttribute::cone3Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CConeAttribute::cone3.getPrimitiveAttribute()))
		{
			//Cone attribute.
			CConeAttribute cone(3);
			//Initialize.
			cone.setPrimitiveAttribute(attribute);
			//Copy box.
			copyBox(cone.getBoxAttribute());
			//Copy vertex.
			return copyVertex(cone);
		}
		else
		{
			//Copy box.
			copyBox(CConeAttribute::cone3.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CConeAttribute::cone3);
		}
	}
	else if(type == CPrimitiveAttribute::cone4Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CConeAttribute::cone4.getPrimitiveAttribute()))
		{
			//Cone attribute.
			CConeAttribute cone(4);
			//Initialize.
			cone.setPrimitiveAttribute(attribute);
			//Copy box.
			copyBox(cone.getBoxAttribute());
			//Copy vertex.
			return copyVertex(cone);
		}
		else
		{
			//copy box.
			copyBox(CConeAttribute::cone4.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CConeAttribute::cone4);
		}
	}
	else if(type == CPrimitiveAttribute::cone6Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CConeAttribute::cone6.getPrimitiveAttribute()))
		{
			//Cone attribute.
			CConeAttribute cone(6);
			//Initialize.
			cone.setPrimitiveAttribute(attribute);
			//Copy box.
			copyBox(cone.getBoxAttribute());
			//Copy vertex.
			return copyVertex(cone);
		}
		else
		{
			//Copy box.
			copyBox(CConeAttribute::cone6.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CConeAttribute::cone6);
		}
	}
	else if(type == CPrimitiveAttribute::cuboid0Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CCuboidAttribute::cuboid0.getPrimitiveAttribute()))
		{
			//Cuboid attribute.
			CCuboidAttribute cuboid;
			//Initialize.
			cuboid.setPrimitiveAttribute(attribute);
			//Copy box.
			copyBox(cuboid.getBoxAttribute());
			//Copy vertex.
			return copyVertex(cuboid);
		}
		else
		{
			//Copy box.
			copyBox(CCuboidAttribute::cuboid0.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CCuboidAttribute::cuboid0);
		}
	}
	else if(type == CPrimitiveAttribute::floor0Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CSliceAttribute::floor0.getPrimitiveAttribute()))
		{
			//Floor attribute.
			CSliceAttribute floor;
			//Initialize.
			floor.setPrimitiveAttribute(attribute);
			//Copy box.
			copyBox(floor.getBoxAttribute());
			//Copy vertex.
			return copyVertex(floor);
		}
		else
		{
			//Copy box.
			copyBox(CSliceAttribute::floor0.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CSliceAttribute::floor0);
		}
	}
	else if(type == CPrimitiveAttribute::capsule0Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CCapsuleAttribute::capsule0.getPrimitiveAttribute()))
		{
			//Capsule attribute.
			CCapsuleAttribute capsule;
			//Initialize.
			capsule.setPrimitiveAttribute(attribute);
			//Copy box.
			copyBox(capsule.getBoxAttribute());
			//Copy vertex.
			return copyVertex(capsule);
		}
		else
		{
			//Initialize box.
			copyBox(CCapsuleAttribute::capsule0.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CCapsuleAttribute::capsule0);
		}
	}
	else if(type == CPrimitiveAttribute::chamferCylider0Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CChamferCylinderAttribute::chamferCylinder0.getPrimitiveAttribute()))
		{
			//Capsule attribute.
			CChamferCylinderAttribute chamferCylinder;
			//Initialize.
			chamferCylinder.setPrimitiveAttribute(attribute);
			//Copy box.
			copyBox(chamferCylinder.getBoxAttribute());
			//Copy vertex.
			return copyVertex(chamferCylinder);
		}
		else
		{
			//Initialize box.
			copyBox(CChamferCylinderAttribute::chamferCylinder0.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CChamferCylinderAttribute::chamferCylinder0);
		}
	}
	else if(type == CPrimitiveAttribute::frustum0Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CFrustumAttribute::frustum0.getPrimitiveAttribute()))
		{
			//Frustum attribute.
			CFrustumAttribute frustum;
			//Initialize.
			frustum.setPrimitiveAttribute(attribute);
			//Copy box.
			copyBox(frustum.getBoxAttribute());
			//Copy vertex.
			return copyVertex(frustum);
		}
		else
		{
			//Copy box.
			copyBox(CFrustumAttribute::frustum0.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CFrustumAttribute::frustum0);
		}
	}
	else if(type == CPrimitiveAttribute::frustum3Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CFrustumAttribute::frustum3.getPrimitiveAttribute()))
		{
			//Frustum attribute.
			CFrustumAttribute frustum(3);
			//Initialize.
			frustum.setPrimitiveAttribute(attribute);
			//Copy box.
			copyBox(frustum.getBoxAttribute());
			//Copy vertex.
			return copyVertex(frustum);
		}
		else
		{
			//Copy box.
			copyBox(CFrustumAttribute::frustum3.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CFrustumAttribute::frustum3);
		}
	}
	else if(type == CPrimitiveAttribute::frustum4Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CFrustumAttribute::frustum4.getPrimitiveAttribute()))
		{
			//Frustum attribute.
			CFrustumAttribute frustum(4);
			//Initialize.
			frustum.setPrimitiveAttribute(attribute);
			//Copy box.
			copyBox(frustum.getBoxAttribute());
			//Copy vertex.
			return copyVertex(frustum);
		}
		else
		{
			//Copy box.
			copyBox(CFrustumAttribute::frustum4.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CFrustumAttribute::frustum4);
		}
	}
	else if(type == CPrimitiveAttribute::frustum6Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CFrustumAttribute::frustum6.getPrimitiveAttribute()))
		{
			//Frustum attribute.
			CFrustumAttribute frustum(6);
			//Initialize.
			frustum.setPrimitiveAttribute(attribute);
			//Copy box.
			copyBox(frustum.getBoxAttribute());
			//Copy vertex.
			return copyVertex(frustum);
		}
		else
		{
			//Copy box.
			copyBox(CFrustumAttribute::frustum6.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CFrustumAttribute::frustum6);
		}
	}
	else if(type == CPrimitiveAttribute::cylinder0Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CCylinderAttribute::cylinder0.getPrimitiveAttribute()))
		{
			//Cylinder attribute.
			CCylinderAttribute cylinder;
			//Initialize.
			cylinder.setPrimitiveAttribute(attribute);
			//Copy box.
			copyBox(cylinder.getBoxAttribute());
			//Copy vertex.
			return copyVertex(cylinder);
		}
		else
		{
			//Copy box.
			copyBox(CCylinderAttribute::cylinder0.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CCylinderAttribute::cylinder0);
		}
	}
	else if(type == CPrimitiveAttribute::cylinder3Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CCylinderAttribute::cylinder3.getPrimitiveAttribute()))
		{
			//Cylinder attribute.
			CCylinderAttribute cylinder(3);
			//Initialize.
			cylinder.setPrimitiveAttribute(attribute);
			//Copy box.
			copyBox(cylinder.getBoxAttribute());
			//Copy vertex.
			return copyVertex(cylinder);
		}
		else
		{
			//Copy box.
			copyBox(CCylinderAttribute::cylinder3.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CCylinderAttribute::cylinder3);
		}
	}
	else if(type == CPrimitiveAttribute::cylinder5Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CCylinderAttribute::cylinder5.getPrimitiveAttribute()))
		{
			//Cylinder attribute.
			CCylinderAttribute cylinder(5);
			//Initialize.
			cylinder.setPrimitiveAttribute(attribute);
			//Copy box.
			copyBox(cylinder.getBoxAttribute());
			//Copy vertex.
			return copyVertex(cylinder);
		}
		else
		{
			//Copy box.
			copyBox(CCylinderAttribute::cylinder5.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CCylinderAttribute::cylinder5);
		}
	}
	else if(type == CPrimitiveAttribute::cylinder6Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CCylinderAttribute::cylinder6.getPrimitiveAttribute()))
		{
			//Cylinder attribute.
			CCylinderAttribute cylinder(6);
			//Initialize.
			cylinder.setPrimitiveAttribute(attribute);
			//Copy box.
			copyBox(cylinder.getBoxAttribute());
			//Copy vertex.
			return copyVertex(cylinder);
		}
		else
		{
			//Copy box.
			copyBox(CCylinderAttribute::cylinder6.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CCylinderAttribute::cylinder6);
		}
	}
	else if(type == CPrimitiveAttribute::sphere0Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CSphereAttribute::sphere0.getPrimitiveAttribute()))
		{
			//Sphere attribute.
			CSphereAttribute sphere;
			//Initialize.
			sphere.setPrimitiveAttribute(attribute);
			//Copy box.
			copyBox(sphere.getBoxAttribute());
			//Copy vertex.
			return copyVertex(sphere);
		}
		else
		{
			//Copy box.
			copyBox(CSphereAttribute::sphere0.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CSphereAttribute::sphere0);
		}
	}
	else if(type == CPrimitiveAttribute::hemisphere0Primitive)
	{
		//Check attribute.
		if(!attribute.isEqual(CHemisphereAttribute::hemisphere0.getPrimitiveAttribute()))
		{
			//Hemisphere attribute.
			CHemisphereAttribute hemisphere;
			//Initialize.
			hemisphere.setPrimitiveAttribute(attribute);
			//Copy box.
			copyBox(hemisphere.getBoxAttribute());
			//Copy vertex.
			return copyVertex(hemisphere);
		}
		else
		{
			//Copy box.
			copyBox(CHemisphereAttribute::hemisphere0.getBoxAttribute());
			//Copy vertex.
			return copyVertex(CHemisphereAttribute::hemisphere0);
		}
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
	//Return fail.
	return E_FAIL;
}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateIndexBuffer
//
/////////////////////////////////////////////////////////////////////////////////

LPDIRECT3DINDEXBUFFER9 CD3DXPrimitive::createIndexBuffer(IDirect3DDevice9* pd3dDevice)
{
	//Set maximum.
	_INTEGER maximum = getIndexCount();
	//Index buffer.
	LPDIRECT3DINDEXBUFFER9 pIndexBuffer;

#ifdef _DEBUG
	assert(pd3dDevice != NULL && maximum >= 1);
#endif
	//Return result.
    return FAILED(pd3dDevice->CreateIndexBuffer(maximum * getIndexSize(),
												//Usage
												D3DUSAGE_DYNAMIC,
												//Format
												D3DFMT_INDEX32,
												//Pool
												D3DPOOL_DEFAULT,
												//Index Buffer
												&pIndexBuffer,NULL)) ? NULL : pIndexBuffer;
}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateVertexBuffer
//
/////////////////////////////////////////////////////////////////////////////////

LPDIRECT3DVERTEXBUFFER9 CD3DXPrimitive::createVertexBuffer(IDirect3DDevice9* pd3dDevice)
{
	//Set maximum.
	_INTEGER maximum = getVertexCount();
	//Vertex buffer.
	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;

#ifdef _DEBUG
	assert(pd3dDevice != NULL && maximum >= 3);
#endif
	//Return result
    return FAILED(pd3dDevice->CreateVertexBuffer(maximum * getVertexSize(),
												 //Usage
												 D3DUSAGE_DYNAMIC,
												 //FVF
												 D3DFVF_4DVERTEX3,
												 //Pool
												 D3DPOOL_DEFAULT,
												 //Vertex Buffer
												 &pVertexBuffer,NULL)) ? NULL : pVertexBuffer;
}

/////////////////////////////////////////////////////////////////////////////////
//
// Pick
//
/////////////////////////////////////////////////////////////////////////////////

CPickIntersection* CD3DXPrimitive::pick(CPickRay& pickRay)
{
#ifdef _DEBUG
	assert(getIndexCount() > 0);
#endif
	//Return result.
	return pick3(getIndexBuffer(),getVertexBuffer(),pickRay,getIndexCount());
}

///////////////////////////////////////////////////////////////////////////////
//
// Render
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXPrimitive::render(IDirect3DDevice9* pd3dDevice,CD3DXEffect* pEffect)
{
	//Result.
	HRESULT hr;

#ifdef _DEBUG
	assert(pd3dDevice != NULL && pEffect != NULL);
#endif

	//Get effect.
	ID3DXEffect* lpEffect = pEffect->getEffectHandle();

#ifdef _DEBUG
	assert(lpEffect != NULL);
#endif

	//Get index buffer.
	LPDIRECT3DINDEXBUFFER9 pIndexBuffer = getIndexBuffer();

#ifdef _DEBUG
	assert(pIndexBuffer != NULL);
#endif

	//Get vertex buffer.
	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer = getVertexBuffer();

#ifdef _DEBUG
	assert(pVertexBuffer != NULL);
#endif

	//Pass count.
	UINT nPassCount = 0;
	//Beginning of technique.
	V_RETURN(lpEffect->Begin(&nPassCount,0)); //Use default pass.

	//Set stream source.
	V_RETURN(pd3dDevice->SetStreamSource(0,pVertexBuffer,0,sizeof(_4DVERTEX3)));
	//Set flex vertex format.
	V_RETURN(pd3dDevice->SetFVF(D3DFVF_4DVERTEX3));
	//Set index.
	V_RETURN(pd3dDevice->SetIndices(pIndexBuffer));

	//Do while.
	for(UINT i = 0;i < nPassCount;i ++)
	{
		//Begin pass.
		lpEffect->BeginPass(i);
		//Draw primitive.
		pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,getVertexCount(),0,getIndexCount());
		//End pass.
		lpEffect->EndPass();
	}

	//End of technique.
	V_RETURN(lpEffect->End());
	//Return OK.
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXPrimitive::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Result.
	HRESULT hr;

	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	//Release D3D9 resources created in the OnD3D9ResetDevice callback.
	case d3dxOnD3D9LostDevice:
		//Handle message.
		V_RETURN(CD3DXIndexAttribute::handleMessage(d3dxEvent));
		//Handle message.
		V_RETURN(CD3DXVertexAttribute::handleMessage(d3dxEvent));
		break;
	//Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) or that are tied to the back buffer size.
	case d3dxOnD3D9ResetDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxResetDevice9.pd3dDevice != NULL);
#endif
		//Handle message.
		V_RETURN(CD3DXVertexAttribute::handleMessage(d3dxEvent));
		//Handle message.
		V_RETURN(CD3DXIndexAttribute::handleMessage(d3dxEvent));
		break;
	}
	//Return result.
	return CD3DXRenderable::handleMessage(d3dxEvent);
}
