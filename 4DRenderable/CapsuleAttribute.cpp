///////////////////////////////////////////////////////////////////////////////
//
// CapsuleAttribute.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "CapsuleAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include <memory.h>
#include "D3DX10Math.h"

#include "4DVector3.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define DEFAULT_RINGS										16
#define DEFAULT_SEGMENTS									16

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Capsule0.
const CCapsuleAttribute CCapsuleAttribute::capsule0(DEFAULT_RINGS,DEFAULT_SEGMENTS);

///////////////////////////////////////////////////////////////////////////////
//
// CCapsuleAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CCapsuleAttribute::CCapsuleAttribute(void)
{
	//Create capsule0.
	createAttribute(DEFAULT_RINGS,DEFAULT_SEGMENTS);
	//Set type and initialize default.
	type = CPrimitiveAttribute::capsule0Primitive; initializeDefault();
}

///////////////////////////////////////////////////////////////////////////////
//
// CCapsuleAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CCapsuleAttribute::CCapsuleAttribute(_INTEGER rings,_INTEGER segments)
{
#ifdef _DEBUG
	assert(rings == DEFAULT_RINGS && segments == DEFAULT_SEGMENTS);
#endif
	//Create capsule0.
	createAttribute(rings,segments);
	//Set type and initialize default.
	type = CPrimitiveAttribute::capsule0Primitive; initializeDefault();
}

///////////////////////////////////////////////////////////////////////////////
//
// CCapsuleAttribute
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CCapsuleAttribute::~CCapsuleAttribute(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateAttribute
//
/////////////////////////////////////////////////////////////////////////////////

void CCapsuleAttribute::createAttribute(_INTEGER rings,_INTEGER segments)
{
#ifdef _DEBUG
	assert(rings >= 2 && segments >= 3);
#endif
	//Set rings.
	this->rings = rings;
	//Set segments.
	this->segments = segments;

	//Index count.
	_INTEGER indexCount = 2 * rings * (segments + 1);
	//Create index.
	CIndexAttribute::createShort3Index(indexCount);

	//Vertex count.
	_INTEGER vertexCount = (rings + 1) * (segments + 1);
	//Create vertex.
	CVertexAttribute::createFloat3Vertex(vertexCount);

	//Normal count.
	_INTEGER normalCount = vertexCount;
	//Create normal.
	CNormalAttribute::createFloat3Normal(normalCount);

	//Texture count.
	_INTEGER textureCount = vertexCount;
	//Create texture.
	CTextureAttribute::createFloat2Texture(textureCount);

#ifdef _DEBUG
	assert(indexCount >= 16);
	assert(vertexCount >= 12);
	assert(vertexCount == normalCount);
	assert(vertexCount == textureCount);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// GetPrimitiveAttribute
//
/////////////////////////////////////////////////////////////////////////////////

CPrimitiveAttribute CCapsuleAttribute::getPrimitiveAttribute() const
{
	//Attribute.
	CPrimitiveAttribute attribute;
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::capsule0Primitive);
#endif
	//Set type.
	attribute.setType(type);
	//Copy data.
	attribute.rings = rings;
	attribute.segments = segments;
	//Copy data.
	attribute.primitiveData.capsule.radius = radius;
	attribute.primitiveData.capsule.height = height;
	//Return attribute.
	return attribute;
}

/////////////////////////////////////////////////////////////////////////////////
//
// InitializeDefault
//
/////////////////////////////////////////////////////////////////////////////////

void CCapsuleAttribute::initializeDefault()
{
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::capsule0Primitive);
#endif
	//Set value.
	height = 1.0f;
	radius = 1.0f;
	//Setup attribute.
	setupAttribute();
	//Set type.
	this->type = CPrimitiveAttribute::capsule0Primitive;
}

/////////////////////////////////////////////////////////////////////////////////
//
// Initialize
//
/////////////////////////////////////////////////////////////////////////////////

void CCapsuleAttribute::initialize(_FLOAT radius,_FLOAT height)
{
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::capsule0Primitive);
#endif
	//Set radius.
	this->radius = radius;
	//Set height.
	this->height = height;
	//Setup attribute.
	setupAttribute();
	//Set type.
	type = CPrimitiveAttribute::capsule0Primitive;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetBoxAttribute
//
///////////////////////////////////////////////////////////////////////////////

CBoxAttribute CCapsuleAttribute::getBoxAttribute() const
{
	CBoxAttribute attribute;

	//Set box.
	{
		//Box.
		CSimpleBox box;
		//Set value.
		box.x() = 0.0f;
		box.y() = 0.0f;
		box.z() = 0.0f;
		box.dx() = radius;
		box.dy() = height / 2.0f + radius;
		box.dz() = radius;
		//Set box.
		attribute.setBox(box);
	}
	//Set sphere.
	{
		//Sphere.
		CSimpleSphere sphere;
		//Set value.
		sphere.r() = height / 2.0f + radius;
		sphere.x() = 0.0f;
		sphere.y() = 0.0f;
		sphere.z() = 0.0f;
		//Set sphere.
		attribute.setSphere(sphere);
	}
	//Return attribute.
	return attribute;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetPrimitiveAttribute
//
///////////////////////////////////////////////////////////////////////////////

void CCapsuleAttribute::setPrimitiveAttribute(const CPrimitiveAttribute& attribute)
{
#ifdef _DEBUG
	assert(type == attribute.getType());
#endif
	//Initialize it.
	initialize(attribute.primitiveData.capsule.radius,attribute.primitiveData.capsule.height);
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetupAttribute
//
/////////////////////////////////////////////////////////////////////////////////

void CCapsuleAttribute::setupAttribute()
{
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::capsule0Primitive);
#endif

#ifdef _DEBUG
	assert(getIndexType() == CIndexAttribute::short3Index);
	assert(getVertexType() == CVertexAttribute::float3Vertex);
	assert(getNormalType() == CNormalAttribute::float3Normal);
	assert(getTextureType() == CTextureAttribute::float2Texture);
#endif

	//Get index.
	_SHORT3* index = CIndexAttribute::getShort3Index();
#ifdef _DEBUG
	assert(index != _NULL);
	assert(getIndexCount() >= 16);
#endif
	//Index array.
	_SHORT* indexArray = (_SHORT *)index;

	//Vertex index.
	_SHORT vertexIndex = 0;
	//Generate the group of rings for the sphere.
	for(_INTEGER i = 0;i < rings + 1;i ++)
	{
		//Generate the group of segments for the current ring.
		for(_INTEGER j = 0;j < segments + 1;j ++)
		{
			//Add two indices except for the last ring.
			if(i != rings) 
			{
				*indexArray = vertexIndex; indexArray ++;
				*indexArray = vertexIndex + (segments + 1);	indexArray ++;
				*indexArray = vertexIndex + 1; indexArray ++;
				*indexArray = vertexIndex + (segments + 1);	indexArray ++;
				*indexArray = vertexIndex + (segments + 1) + 1;	indexArray ++;
				*indexArray = vertexIndex + 1;	indexArray ++;
				vertexIndex ++;
			}
		}
	}

	//Get vertex.
	_FLOAT3* vertex = CVertexAttribute::getFloat3Vertex();
#ifdef _DEBUG
	assert(vertex != _NULL);
	assert(getVertexCount() >= 12);
#endif

	//Get normal.
	_FLOAT3* normal = CNormalAttribute::getFloat3Normal();
#ifdef _DEBUG
	assert(normal != _NULL);
	assert(getNormalCount() >= 12);
	assert(getNormalCount() == getVertexCount());
#endif

	//Get coordinates.
	_FLOAT2* coordinates = CTextureAttribute::getFloat2Texture();
#ifdef _DEBUG
	assert(coordinates != _NULL);
	assert(getTextureCount() >= 12);
	assert(getTextureCount() == getVertexCount());
#endif

	//Position index.
	_INTEGER positionIndex = 0;
	//Establish constants used in sphere generation
	_FLOAT rDeltaRingAngle = (_FLOAT)D3DX_PI / rings;
	_FLOAT rDeltaSegAngle = 2.0f * (_FLOAT)D3DX_PI / segments;
	//Generate the group of rings for the sphere
	for(_INTEGER i = 0;i < rings + 1;i ++)
	{
		_FLOAT r0 = radius * sinf(i * rDeltaRingAngle);
		_FLOAT y0 = radius * cosf(i * rDeltaRingAngle);

		//Keep original value.
		_FLOAT yy = y0;
		//Check current angle.
		if(i < rings / 2)
		{
			y0 += height / 2.0f;
		}
		else if(i == rings / 2)
		{
			y0 = 0.0f;
		}
		else
		{
			y0 -= height / 2.0f;
		}
		//Generate the group of segments for the current ring
		for(_INTEGER j = 0;j < segments + 1;j ++)
		{
			_FLOAT x0 = r0 * sinf(j * rDeltaSegAngle);
			_FLOAT z0 = r0 * cosf(j * rDeltaSegAngle);
			//Normalize it.
			//The normal is a vector on a sphere.
			C4DVector3 n = C4DVector3(x0,yy,z0).normalize();
			//Add one vertex to the strip which makes up the sphere
			vertex[positionIndex][0] = x0;
			vertex[positionIndex][1] = y0;
			vertex[positionIndex][2] = z0;
			normal[positionIndex][0] = n.x();
			normal[positionIndex][1] = n.y();
			normal[positionIndex][2] = n.z();
			coordinates[positionIndex][0] = 1.0f - (_FLOAT)j / (_FLOAT)segments;
			coordinates[positionIndex][1] = (_FLOAT)i / (_FLOAT)rings;
			//Add index.
			positionIndex ++;
		}
	}
}
