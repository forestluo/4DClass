///////////////////////////////////////////////////////////////////////////////
//
// RenderableAttribute.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "RenderableAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DX10Math.h"

#include "ConeAttribute.h"
#include "SliceAttribute.h"
#include "CircleAttribute.h"
#include "SphereAttribute.h"
#include "CuboidAttribute.h"
#include "PolygonAttribute.h"
#include "CapsuleAttribute.h"
#include "FrustumAttribute.h"
#include "CylinderAttribute.h"
#include "TriangleAttribute.h"
#include "QuadrangleAttribute.h"
#include "HemisphereAttribute.h"
#include "ChamferCylinderAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// XNA
//
///////////////////////////////////////////////////////////////////////////////

#include <xnamath.h>

#include "xnaCollision.h"
using namespace XNA;

///////////////////////////////////////////////////////////////////////////////
//
// CRenderableAttribute
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CRenderableAttribute::CRenderableAttribute(void)
{
	//Set rings.
	rings = 0;
	//Set segments.
	segments = 0;
	//Set type.
	type = CPrimitiveAttribute::nullPrimitive;
}

///////////////////////////////////////////////////////////////////////////////
//
// CRenderableAttribute
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CRenderableAttribute::CRenderableAttribute(const CRenderableAttribute& attribute)
{
	//Copy renderable.
	copyRenderable(attribute);
}

///////////////////////////////////////////////////////////////////////////////
//
// CRenderableAttribute
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CRenderableAttribute::~CRenderableAttribute(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// SwapRenderable
//
///////////////////////////////////////////////////////////////////////////////

void CRenderableAttribute::swapRenderable(CRenderableAttribute& attribute)
{
	//Copy renderable.
	copyRenderable(attribute);
	//Set reference.
	attribute.setReferenced(_TRUE);
	//Clear reference.
	CReferenceAttribute::setReferenced(_FALSE);
}

///////////////////////////////////////////////////////////////////////////////
//
// CopyRenderable
//
///////////////////////////////////////////////////////////////////////////////

void CRenderableAttribute::copyRenderable(const CRenderableAttribute& attribute)
{
#ifdef _DEBUG
	assert(rings == 0 && segments == 0);
	assert(getIndexType() == CIndexAttribute::nullIndex);
	assert(getVertexType() == CVertexAttribute::nullVertex);
	assert(getNormalType() == CNormalAttribute::nullNormal);
	assert(getTextureType() == CTextureAttribute::nullTexture);
#endif

	//Set type.
	type = attribute.type;
	//Set rings.
	rings = attribute.rings;
	//Set segments.
	segments = attribute.segments;

	//Copy index.
	copyIndex(attribute);
	//Copy vertex.
	copyVertex(attribute);
	//Copy normal.
	copyNormal(attribute);
	//Copy texture.
	copyTexture(attribute);
}

///////////////////////////////////////////////////////////////////////////////
//
// GetRings
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CRenderableAttribute::getRings() const
{
	//Return rings.
	return rings;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetSegments
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CRenderableAttribute::getSegments() const
{
	//Return segments.
	return segments;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetBoxAttribute
//
///////////////////////////////////////////////////////////////////////////////

CBoxAttribute CRenderableAttribute::getBoxAttribute() const
{
	CBoxAttribute attribute;

	//Get vertex pointer.
	_FLOAT3* vertex = CVertexAttribute::getFloat3Vertex();
#ifdef _DEBUG
	assert(vertex != _NULL);
#endif

	//Get vertex count.
	_INTEGER vertexCount = CVertexAttribute::getVertexCount();
#ifdef _DEBUG
	assert(vertexCount > 0);
	assert(CVertexAttribute::getVertexType() == CVertexAttribute::float3Vertex);
#endif

	//Set box.
	{
		//Box.
		XNA::AxisAlignedBox xnaBox;
		//Calculate AA box.
		::ComputeBoundingAxisAlignedBoxFromPoints(&xnaBox,vertexCount,(XMFLOAT3 *)vertex,sizeof(_FLOAT3));
		//Box.
		CSimpleBox box;
		//Set value.
		box.x() = xnaBox.Center.x;
		box.y() = xnaBox.Center.y;
		box.z() = xnaBox.Center.z;
		box.dx() = xnaBox.Extents.x;
		box.dy() = xnaBox.Extents.y;
		box.dz() = xnaBox.Extents.z;
		//Set box.
		attribute.setBox(box);
	}
	//Set sphere.
	{
		//Sphere.
		XNA::Sphere xnaSphere;
		//Calculate sphere.
		::ComputeBoundingSphereFromPoints(&xnaSphere,vertexCount,(XMFLOAT3 *)vertex,sizeof(_FLOAT3));

		//Sphere.
		CSimpleSphere sphere;
		//Set value.
		sphere.r() = xnaSphere.Radius;
		sphere.x() = xnaSphere.Center.x;
		sphere.y() = xnaSphere.Center.y;
		sphere.z() = xnaSphere.Center.z;
		//Set sphere.
		attribute.setSphere(sphere);
	}
	//Return attribute.
	return attribute;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetPrimitiveAttribute
//
///////////////////////////////////////////////////////////////////////////////

CPrimitiveAttribute CRenderableAttribute::getPrimitiveAttribute() const
{
#ifdef _DEBUG
	assert(_FALSE);
#endif
	//Return null primitive.
	return CPrimitiveAttribute();
}

///////////////////////////////////////////////////////////////////////////////
//
// SetPrimitiveAttribute
//
///////////////////////////////////////////////////////////////////////////////

void CRenderableAttribute::setPrimitiveAttribute(const CPrimitiveAttribute& attribute)
{
#ifdef _DEBUG
	assert(_FALSE);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateRenderableAttribute
//
///////////////////////////////////////////////////////////////////////////////

CRenderableAttribute* CRenderableAttribute::createRenderableAttribute(const CPrimitiveAttribute& attribute)
{
	//Renderable attribute.
	CRenderableAttribute* renderable;
#ifdef _DEBUG
	assert(attribute.getType() != CPrimitiveAttribute::nullPrimitive);
#endif
	//Get type.
	_INTEGER type = attribute.getType();
	//Check type.
	if(type == CPrimitiveAttribute::triangle0Primitive)
	{
		//Create attribute.
		renderable = new CTriangleAttribute();
	}
	else if(type == CPrimitiveAttribute::circle0Primitive)
	{
		//Create attribute.
		renderable = new CCircleAttribute();
	}
	else if(type == CPrimitiveAttribute::circle3Primitive)
	{
		//Create attribute.
		renderable = new CCircleAttribute(3);
	}
	else if(type == CPrimitiveAttribute::circle4Primitive)
	{
		//Create attribute.
		renderable = new CCircleAttribute(4);
	}
	else if(type == CPrimitiveAttribute::circle5Primitive)
	{
		//Create attribute.
		renderable = new CCircleAttribute(5);
	}
	else if(type == CPrimitiveAttribute::circle6Primitive)
	{
		//Create attribute.
		renderable = new CCircleAttribute(6);
	}
	else if(type == CPrimitiveAttribute::polygon4Primitive)
	{
		//Create attribute.
		renderable = new CPolygonAttribute(4);
	}
	else if(type == CPrimitiveAttribute::polygon6Primitive)
	{
		//Create attribute.
		renderable = new CPolygonAttribute(6);
	}
	else if(type == CPrimitiveAttribute::polygon8Primitive)
	{
		//Create attribute.
		renderable = new CPolygonAttribute(8);
	}
	else if(type == CPrimitiveAttribute::polygon12Primitive)
	{
		//Create attribute.
		renderable = new CPolygonAttribute(12);
	}
	else if(type == CPrimitiveAttribute::polygon20Primitive)
	{
		//Create attribute.
		renderable = new CPolygonAttribute(20);
	}
	else if(type == CPrimitiveAttribute::quadrangle0Primitive)
	{
		//Create attribute.
		renderable = new CQuadrangleAttribute();
	}
	else if(type == CPrimitiveAttribute::cone0Primitive)
	{
		//Create attribute.
		renderable = new CConeAttribute();
	}
	else if(type == CPrimitiveAttribute::cone3Primitive)
	{
		//Create attribute.
		renderable = new CConeAttribute(3);
	}
	else if(type == CPrimitiveAttribute::cone4Primitive)
	{
		//Create attribute.
		renderable = new CConeAttribute(4);
	}
	else if(type == CPrimitiveAttribute::cone6Primitive)
	{
		//Create attribute.
		renderable = new CConeAttribute(6);
	}
	else if(type == CPrimitiveAttribute::cuboid0Primitive)
	{
		//Create attribute.
		renderable = new CCuboidAttribute();
	}
	else if(type == CPrimitiveAttribute::floor0Primitive)
	{
		//Create attribute.
		renderable = new CSliceAttribute();
	}
	else if(type == CPrimitiveAttribute::capsule0Primitive)
	{
		//Create attribute.
		renderable = new CCapsuleAttribute();
	}
	else if(type == CPrimitiveAttribute::chamferCylider0Primitive)
	{
		//Create attribute.
		renderable = new CChamferCylinderAttribute();
	}
	else if(type == CPrimitiveAttribute::frustum0Primitive)
	{
		//Create attribute.
		renderable = new CFrustumAttribute();
	}
	else if(type == CPrimitiveAttribute::frustum3Primitive)
	{
		//Create attribute.
		renderable = new CFrustumAttribute(3);
	}
	else if(type == CPrimitiveAttribute::frustum4Primitive)
	{
		//Create attribute.
		renderable = new CFrustumAttribute(4);
	}
	else if(type == CPrimitiveAttribute::frustum6Primitive)
	{
		//Create attribute.
		renderable = new CFrustumAttribute(6);
	}
	else if(type == CPrimitiveAttribute::cylinder0Primitive)
	{
		//Create attribute.
		renderable = new CCylinderAttribute();
	}
	else if(type == CPrimitiveAttribute::cylinder3Primitive)
	{
		//Create attribute.
		renderable = new CCylinderAttribute(3);
	}
	else if(type == CPrimitiveAttribute::cylinder5Primitive)
	{
		//Create attribute.
		renderable = new CCylinderAttribute(5);
	}
	else if(type == CPrimitiveAttribute::cylinder6Primitive)
	{
		//Create attribute.
		renderable = new CCylinderAttribute(6);
	}
	else if(type == CPrimitiveAttribute::sphere0Primitive)
	{
		//Create attribute.
		renderable = new CSphereAttribute();
	}
	else if(type == CPrimitiveAttribute::hemisphere0Primitive)
	{
		//Create attribute.
		renderable = new CHemisphereAttribute();
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
	//Set primitive attribute.
	renderable->setPrimitiveAttribute(attribute);
	//Return result.
	return renderable;
}
