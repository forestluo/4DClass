///////////////////////////////////////////////////////////////////////////////
//
// ChamferCylinderAttribute.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "ChamferCylinderAttribute.h"

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
const CChamferCylinderAttribute CChamferCylinderAttribute::chamferCylinder0(DEFAULT_RINGS,DEFAULT_SEGMENTS);

///////////////////////////////////////////////////////////////////////////////
//
// CChamferCylinderAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CChamferCylinderAttribute::CChamferCylinderAttribute(void)
{
	//Create chamfer cylinder0.
	createAttribute(DEFAULT_RINGS,DEFAULT_SEGMENTS);
	//Set type and initialize default.
	type = CPrimitiveAttribute::chamferCylider0Primitive; initializeDefault();
}

///////////////////////////////////////////////////////////////////////////////
//
// CChamferCylinderAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CChamferCylinderAttribute::CChamferCylinderAttribute(_INTEGER rings,_INTEGER segments)
{
#ifdef _DEBUG
	assert(rings == DEFAULT_RINGS && segments == DEFAULT_SEGMENTS);
#endif
	//Create chamfer cylinder0.
	createAttribute(rings,segments);
	//Set type and initialize default.
	type = CPrimitiveAttribute::chamferCylider0Primitive; initializeDefault();
}

///////////////////////////////////////////////////////////////////////////////
//
// CChamferCylinderAttribute
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CChamferCylinderAttribute::~CChamferCylinderAttribute(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateAttribute
//
/////////////////////////////////////////////////////////////////////////////////

void CChamferCylinderAttribute::createAttribute(_INTEGER rings,_INTEGER segments)
{
#ifdef _DEBUG
	assert(rings >= 2 && segments >= 3);
#endif
	//Set rings.
	this->rings = rings;
	//Set segments.
	this->segments = segments;

	//Index count.
	_INTEGER indexCount = 2 * rings * (segments + 1) + 2 * segments /* The top and bottom fan. */; 
	//_INTEGER indexCount = 2 * segments /* The top and bottom fan. */; 
	//Create index.
	CIndexAttribute::createShort3Index(indexCount);

	//Vertex count.
	_INTEGER vertexCount = (rings + 1) * (segments + 1) + 2 * (1 + (segments + 1)) /* The top and bottom center fan. */;
	//_INTEGER vertexCount = 2 * (1 + (segments + 1)) /* The top and bottom center fan. */;
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
	assert(vertexCount >= 22);
	assert(vertexCount == normalCount);
	assert(vertexCount == textureCount);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// GetPrimitiveAttribute
//
/////////////////////////////////////////////////////////////////////////////////

CPrimitiveAttribute CChamferCylinderAttribute::getPrimitiveAttribute() const
{
	//Attribute.
	CPrimitiveAttribute attribute;
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::chamferCylider0Primitive);
#endif
	//Set type.
	attribute.setType(type);
	//Copy data.
	attribute.rings = rings;
	attribute.segments = segments;
	//Copy data.
	attribute.primitiveData.chamferCylinder.radius = radius;
	attribute.primitiveData.chamferCylinder.height = height;
	//Return attribute.
	return attribute;
}

/////////////////////////////////////////////////////////////////////////////////
//
// InitializeDefault
//
/////////////////////////////////////////////////////////////////////////////////

void CChamferCylinderAttribute::initializeDefault()
{
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::chamferCylider0Primitive);
#endif
	//Set value.
	height = 1.0f;
	radius = 1.0f;
	//Setup attribute.
	setupAttribute();
	//Set type.
	this->type = CPrimitiveAttribute::chamferCylider0Primitive;
}

/////////////////////////////////////////////////////////////////////////////////
//
// Initialize
//
/////////////////////////////////////////////////////////////////////////////////

void CChamferCylinderAttribute::initialize(_FLOAT radius,_FLOAT height)
{
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::chamferCylider0Primitive);
#endif
	//Set radius.
	this->radius = radius;
	//Set height.
	this->height = height;
	//Setup attribute.
	setupAttribute();
	//Set type.
	type = CPrimitiveAttribute::chamferCylider0Primitive;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetBoxAttribute
//
///////////////////////////////////////////////////////////////////////////////

CBoxAttribute CChamferCylinderAttribute::getBoxAttribute() const
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
		box.dx() = height / 2.0f + radius;
		box.dy() = height / 2.0f;
		box.dz() = height / 2.0f + radius;
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

void CChamferCylinderAttribute::setPrimitiveAttribute(const CPrimitiveAttribute& attribute)
{
#ifdef _DEBUG
	assert(type == attribute.getType());
#endif
	//Initialize it.
	initialize(attribute.primitiveData.chamferCylinder.radius,
				attribute.primitiveData.chamferCylinder.height);
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetupAttribute
//
/////////////////////////////////////////////////////////////////////////////////

void CChamferCylinderAttribute::setupAttribute()
{
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::chamferCylider0Primitive);
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

	//Top and bottom fans.
	{
		//Index.
		_INTEGER centerIndex, startIndex;

		//Center index.
		centerIndex = vertexIndex; vertexIndex ++;

		//Start index.
		startIndex = vertexIndex;
		//For each segment, add a triangle to the sides triangle list.
		for(_INTEGER i = segments;i > 0;i --)
		{
			//Set three indices (1 triangle) per segment.
			*indexArray = centerIndex; indexArray ++;
			*indexArray = vertexIndex; indexArray ++;
			*indexArray = vertexIndex + 1; indexArray ++;
			//Add index.
			vertexIndex ++;
		}
		//Add index.
		vertexIndex ++;

		//Center index.
		centerIndex = vertexIndex; vertexIndex ++;

		//Start index.
		startIndex = vertexIndex;
		//For each segment, add a triangle to the sides triangle list.
		for(_INTEGER i = segments;i > 0;i --)
		{
			//Set three indices (1 triangle) per segment.
			*indexArray = centerIndex; indexArray ++;
			*indexArray = vertexIndex; indexArray ++;
			*indexArray = vertexIndex + 1; indexArray ++;
			vertexIndex ++;
		}
	}

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
	assert(getVertexCount() >= 22);
#endif

	//Get normal.
	_FLOAT3* normal = CNormalAttribute::getFloat3Normal();
#ifdef _DEBUG
	assert(normal != _NULL);
	assert(getNormalCount() >= 22);
	assert(getNormalCount() == getVertexCount());
#endif

	//Get coordinates.
	_FLOAT2* coordinates = CTextureAttribute::getFloat2Texture();
#ifdef _DEBUG
	assert(coordinates != _NULL);
	assert(getTextureCount() >= 22);
	assert(getTextureCount() == getVertexCount());
#endif

	//Position index.
	_INTEGER positionIndex = 0;

	//Establish constants used in sphere generation
	_FLOAT rDeltaRingAngle = (_FLOAT)D3DX_PI / rings;
	_FLOAT rDeltaSegAngle = 2.0f * (_FLOAT)D3DX_PI / segments;

	//Create the top triangle fan: Center
	vertex[positionIndex][0] = 0.0f;
	vertex[positionIndex][1] = 0.0f + height / 2.0f;
	vertex[positionIndex][2] = 0.0f;
	normal[positionIndex][0] = 0.0f;
	normal[positionIndex][1] = 1.0f;
	normal[positionIndex][2] = 0.0f;
	coordinates[positionIndex][0] = 0.5f;
	coordinates[positionIndex][1] = 0.5f;
	positionIndex ++;

	//Create the top triangle fan: Edges
	for(_INTEGER i = 0; i <= segments;i ++)
	{
		_FLOAT x0 = radius * sinf(i * rDeltaSegAngle);
		_FLOAT z0 = radius * cosf(i * rDeltaSegAngle);

		vertex[positionIndex][0] = x0;
		vertex[positionIndex][1] = 0.0f + height / 2.0f;
		vertex[positionIndex][2] = z0;
		normal[positionIndex][0] = 0.0f;
		normal[positionIndex][1] = 1.0f;
		normal[positionIndex][2] = 0.0f;

		_FLOAT tu0 = 0.5f * sinf(i * rDeltaSegAngle) + 0.5f;
		_FLOAT tv0 = 0.5f * cosf(i * rDeltaSegAngle) + 0.5f;

		coordinates[positionIndex][0] = tu0;
		coordinates[positionIndex][1] = tv0;
		positionIndex ++;
	}

	//Create the bottom triangle fan: Center
	vertex[positionIndex][0] = 0.0f;
	vertex[positionIndex][1] = 0.0f - height / 2.0f;
	vertex[positionIndex][2] = 0.0f;
	normal[positionIndex][0] = 0.0f;
	normal[positionIndex][1] = -1.0f;
	normal[positionIndex][2] = 0.0f;
	coordinates[positionIndex][0] = 0.5f;
	coordinates[positionIndex][1] = 0.5f;
	positionIndex ++;

	//Create the bottom triangle fan: Edges
	for(_INTEGER i = segments;i >= 0;i --)
	{
		_FLOAT x0 = radius * sinf(i * rDeltaSegAngle);
		_FLOAT z0 = radius * cosf(i * rDeltaSegAngle);

		vertex[positionIndex][0] = x0;
		vertex[positionIndex][1] = 0.0f - height / 2.0f;
		vertex[positionIndex][2] = z0;
		normal[positionIndex][0] = 0.0f;
		normal[positionIndex][1] = -1.0f;
		normal[positionIndex][2] = 0.0f;

		_FLOAT tu0 = 0.5f * sinf(i * rDeltaSegAngle) + 0.5f;
		_FLOAT tv0 = 0.5f * cosf(i * rDeltaSegAngle) + 0.5f;

		coordinates[positionIndex][0] = tu0;
		coordinates[positionIndex][1] = tv0;
		positionIndex ++;
	}

	//Generate the group of rings for the sphere
	for(_INTEGER i = 0;i < rings + 1;i ++)
	{
		_FLOAT r0 = height / 2.0f * sinf(i * rDeltaRingAngle);
		_FLOAT y0 = height / 2.0f * cosf(i * rDeltaRingAngle);
		//Generate the group of segments for the current ring
		for(_INTEGER j = 0;j < segments + 1;j ++)
		{
			_FLOAT x0 = (r0 + radius) * sinf(j * rDeltaSegAngle);
			_FLOAT z0 = (r0 + radius) * cosf(j * rDeltaSegAngle);
			//Normalize it.
			C4DVector3 n;
			n.x() = height / 2.0f * sinf(j * rDeltaSegAngle);
			n.y() = y0;
			n.z() = height / 2.0f * cosf(j * rDeltaSegAngle);
			n.normalize();
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
