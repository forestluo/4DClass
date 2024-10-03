///////////////////////////////////////////////////////////////////////////////
//
// CylinderAttribute.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "CylinderAttribute.h"

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

#define DEFAULT_RINGS										0
#define DEFAULT_SEGMENTS									16

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Cylinder0.
const CCylinderAttribute CCylinderAttribute::cylinder0(DEFAULT_SEGMENTS);
//Cylinder3.
const CCylinderAttribute CCylinderAttribute::cylinder3(3);
//Cylinder5.
const CCylinderAttribute CCylinderAttribute::cylinder5(5);
//Cylinder6.
const CCylinderAttribute CCylinderAttribute::cylinder6(6);

///////////////////////////////////////////////////////////////////////////////
//
// CCylinderAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CCylinderAttribute::CCylinderAttribute(void)
{
	//Create cylinder0.
	createAttribute(DEFAULT_RINGS,DEFAULT_SEGMENTS);
	//Set type and initialize default.
	type = CPrimitiveAttribute::cylinder0Primitive; initializeDefault();
}

///////////////////////////////////////////////////////////////////////////////
//
// CCylinderAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CCylinderAttribute::CCylinderAttribute(_INTEGER segments)
{
	//Create cylinder0.
	createAttribute(DEFAULT_RINGS,segments);
	//Check segments.
	switch(segments)
	{
	case DEFAULT_SEGMENTS:
		type = CPrimitiveAttribute::cylinder0Primitive;
		break;
	case 3:
		type = CPrimitiveAttribute::cylinder3Primitive;
		break;
	case 5:
		type = CPrimitiveAttribute::cylinder5Primitive;
		break;
	case 6:
		type = CPrimitiveAttribute::cylinder6Primitive;
		break;
	default:
#ifdef _DEBUG
		assert(_FALSE);
#endif
	}
	//Initialize default.
	initializeDefault();
}

///////////////////////////////////////////////////////////////////////////////
//
// CCylinderAttribute
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CCylinderAttribute::~CCylinderAttribute(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateAttribute
//
/////////////////////////////////////////////////////////////////////////////////

void CCylinderAttribute::createAttribute(_INTEGER rings,_INTEGER segments)
{
#ifdef _DEBUG
	assert(segments >= 3);
#endif
	//Set rings.
	this->rings = rings;
	//Set segments.
	this->segments = segments;

	//Index count.
	_INTEGER indexCount = 4 * segments;
	//Create index.
	CIndexAttribute::createShort3Index(indexCount);

	//Vertex count.
	_INTEGER vertexCount = (segments + 1) * 4 + 2;
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
	assert(indexCount >= 12);
	assert(vertexCount >= 18);
	assert(vertexCount == normalCount);
	assert(vertexCount == textureCount);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// GetPrimitiveAttribute
//
/////////////////////////////////////////////////////////////////////////////////

CPrimitiveAttribute CCylinderAttribute::getPrimitiveAttribute() const
{
	//Attribute.
	CPrimitiveAttribute attribute;
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::cylinder0Primitive ||
			type == CPrimitiveAttribute::cylinder3Primitive ||
			type == CPrimitiveAttribute::cylinder5Primitive ||
			type == CPrimitiveAttribute::cylinder6Primitive);
#endif
	//Set type.
	attribute.setType(type);
	//Copy data.
	attribute.rings = rings;
	attribute.segments = segments;
	//Copy data.
	attribute.primitiveData.cylinder.radius = radius;
	attribute.primitiveData.cylinder.height = height;
	//Return attribute.
	return attribute;
}

/////////////////////////////////////////////////////////////////////////////////
//
// InitializeDefault
//
/////////////////////////////////////////////////////////////////////////////////

void CCylinderAttribute::initializeDefault()
{
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::cylinder0Primitive ||
			type == CPrimitiveAttribute::cylinder3Primitive ||
			type == CPrimitiveAttribute::cylinder5Primitive ||
			type == CPrimitiveAttribute::cylinder6Primitive);
#endif
	//Set value.
	height = 1.0f;
	radius = 1.0f;
	//Setup attribute.
	setupAttribute();
}

/////////////////////////////////////////////////////////////////////////////////
//
// Initialize
//
/////////////////////////////////////////////////////////////////////////////////

void CCylinderAttribute::initialize(_FLOAT radius,_FLOAT height)
{
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::cylinder0Primitive ||
			type == CPrimitiveAttribute::cylinder3Primitive ||
			type == CPrimitiveAttribute::cylinder5Primitive ||
			type == CPrimitiveAttribute::cylinder6Primitive);
#endif
	//Set radius.
	this->radius = radius;
	//Set height.
	this->height = height;
	//Setup attribute.
	setupAttribute();
}

///////////////////////////////////////////////////////////////////////////////
//
// SetPrimitiveAttribute
//
///////////////////////////////////////////////////////////////////////////////

void CCylinderAttribute::setPrimitiveAttribute(const CPrimitiveAttribute& attribute)
{
#ifdef _DEBUG
	assert(type == attribute.getType());
#endif
	//Initialize it.
	initialize(attribute.primitiveData.cylinder.radius,
				attribute.primitiveData.cylinder.height);
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetupAttribute
//
/////////////////////////////////////////////////////////////////////////////////

void CCylinderAttribute::setupAttribute()
{
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::cylinder0Primitive ||
		type == CPrimitiveAttribute::cylinder3Primitive ||
		type == CPrimitiveAttribute::cylinder5Primitive ||
		type == CPrimitiveAttribute::cylinder6Primitive);
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
	assert(getIndexCount() >= 6);
#endif
	//Index array.
	_SHORT* indexArray = (_SHORT *)index;

	//Index.
	_SHORT startIndex;
	_SHORT centerIndex;
	//Vertex index.
	_SHORT vertexIndex = 0;
	//For each segment, add a triangle to the sides triangle list.
	for(_INTEGER i = segments;i > 0;i --)
	{
		//Set three indices (2 triangle) per segment
		//The first triangle.
		*indexArray = vertexIndex + 0; indexArray ++;
		*indexArray = vertexIndex + 1; indexArray ++;
		*indexArray = vertexIndex + 3; indexArray ++;
		//The second triangle.
		*indexArray = vertexIndex + 0; indexArray ++;
		*indexArray = vertexIndex + 3; indexArray ++;
		*indexArray = vertexIndex + 2; indexArray ++;
		//Add index.
		vertexIndex += 2;
	}
	//Add index.
	vertexIndex += 2;

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
	assert(getNormalCount() >= 18);
	assert(getNormalCount() == getVertexCount());
#endif

	//Get coordinates.
	_FLOAT2* coordinates = CTextureAttribute::getFloat2Texture();
#ifdef _DEBUG
	assert(coordinates != _NULL);
	assert(getTextureCount() >= 18);
	assert(getTextureCount() == getVertexCount());
#endif

	_FLOAT rDeltaSegAngle = 2.0f * (_FLOAT)D3DX_PI / segments;
	_FLOAT rSegmentLength = 1.0f / (_FLOAT)segments;

	//Position index.
	_INTEGER positionIndex = 0;
	//Create the sides triangle strip
	for(_INTEGER i = 0; i <= segments; i ++)
	{
		_FLOAT x0 = radius * sinf(i * rDeltaSegAngle);
		_FLOAT z0 = radius * cosf(i * rDeltaSegAngle);

		vertex[positionIndex][0] = x0;
		vertex[positionIndex][1] = 0.0f + height / 2.0f;
		vertex[positionIndex][2] = z0;
		normal[positionIndex][0] = x0;
		normal[positionIndex][1] = 0.0f;
		normal[positionIndex][2] = z0;
		coordinates[positionIndex][0] = 1.0f - rSegmentLength * (_FLOAT)i;
		coordinates[positionIndex][1] = 0.0f;
		positionIndex ++;

		vertex[positionIndex][0] = x0;
		vertex[positionIndex][1] = 0.0f - height / 2.0f;
		vertex[positionIndex][2] = z0;
		normal[positionIndex][0] = x0;
		normal[positionIndex][1] = 0.0f;
		normal[positionIndex][2] = z0;
		coordinates[positionIndex][0] = 1.0f - rSegmentLength * (_FLOAT)i;
		coordinates[positionIndex][1] = 1.0f;
		positionIndex ++;
	}
	
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
}
