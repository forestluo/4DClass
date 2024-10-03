///////////////////////////////////////////////////////////////////////////////
//
// CircleAttribute.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "CircleAttribute.h"

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
#define DEFAULT_SEGMENTS									64

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Circle0.
const CCircleAttribute CCircleAttribute::circle0(DEFAULT_SEGMENTS);
//Circle3.
const CCircleAttribute CCircleAttribute::circle3(3);
//Circle4.
const CCircleAttribute CCircleAttribute::circle4(4);
//Circle5.
const CCircleAttribute CCircleAttribute::circle5(5);
//Circle6.
const CCircleAttribute CCircleAttribute::circle6(6);

///////////////////////////////////////////////////////////////////////////////
//
// CCircleAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CCircleAttribute::CCircleAttribute(void)
{
	//Create circle0.
	createAttribute(DEFAULT_RINGS,DEFAULT_SEGMENTS);
	//Set type and initialize default.
	type = CPrimitiveAttribute::circle0Primitive; initializeDefault();
}

///////////////////////////////////////////////////////////////////////////////
//
// CCircleAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CCircleAttribute::CCircleAttribute(_INTEGER segments)
{
	//Create circle0.
	createAttribute(DEFAULT_RINGS,segments);
	//Check segments.
	switch(segments)
	{
	case DEFAULT_SEGMENTS:
		type = CPrimitiveAttribute::circle0Primitive;
		break;
	case 3:
		type = CPrimitiveAttribute::circle3Primitive;
		break;
	case 4:
		type = CPrimitiveAttribute::circle4Primitive;
		break;
	case 5:
		type = CPrimitiveAttribute::circle5Primitive;
		break;
	case 6:
		type = CPrimitiveAttribute::circle6Primitive;
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
// CCircleAttribute
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CCircleAttribute::~CCircleAttribute(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateAttribute
//
/////////////////////////////////////////////////////////////////////////////////

void CCircleAttribute::createAttribute(_INTEGER rings,_INTEGER segments)
{
#ifdef _DEBUG
	assert(segments >= 3);
#endif
	//Set rings.
	this->rings = rings;
	//Set segments.
	this->segments = segments;

	//Index count.
	_INTEGER indexCount = segments;
	//Create index.
	CIndexAttribute::createShort3Index(indexCount);

	//Vertex count.
	_INTEGER vertexCount = 1 + (segments + 1);
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
	assert(indexCount >= 3);
	assert(vertexCount >= 4);
	assert(vertexCount == normalCount);
	assert(vertexCount == textureCount);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// GetPrimitiveAttribute
//
/////////////////////////////////////////////////////////////////////////////////

CPrimitiveAttribute CCircleAttribute::getPrimitiveAttribute() const
{
	//Attribute.
	CPrimitiveAttribute attribute;
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::circle0Primitive ||
		type == CPrimitiveAttribute::circle3Primitive ||
		type == CPrimitiveAttribute::circle4Primitive ||
		type == CPrimitiveAttribute::circle5Primitive ||
		type == CPrimitiveAttribute::circle6Primitive);
#endif
	//Set type.
	attribute.setType(type);
	//Copy data.
	attribute.rings = rings;
	attribute.segments = segments;
	//Copy data.
	attribute.primitiveData.circle.radius = radius;
	//Return attribute.
	return attribute;
}

/////////////////////////////////////////////////////////////////////////////////
//
// InitializeDefault
//
/////////////////////////////////////////////////////////////////////////////////

void CCircleAttribute::initializeDefault()
{
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::circle0Primitive ||
		type == CPrimitiveAttribute::circle3Primitive ||
		type == CPrimitiveAttribute::circle4Primitive ||
		type == CPrimitiveAttribute::circle5Primitive ||
		type == CPrimitiveAttribute::circle6Primitive);
#endif
	//Set value.
	radius = 1.0f;
	//Setup attribute.
	setupAttribute();
	//Set type.
	this->type = type;
}

/////////////////////////////////////////////////////////////////////////////////
//
// Initialize
//
/////////////////////////////////////////////////////////////////////////////////

void CCircleAttribute::initialize(_FLOAT radius)
{
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::circle0Primitive ||
		type == CPrimitiveAttribute::circle3Primitive ||
		type == CPrimitiveAttribute::circle4Primitive ||
		type == CPrimitiveAttribute::circle5Primitive ||
		type == CPrimitiveAttribute::circle6Primitive);
#endif
	//Set radius.
	this->radius = radius;
	//Setup attribute.
	setupAttribute();
}

///////////////////////////////////////////////////////////////////////////////
//
// SetPrimitiveAttribute
//
///////////////////////////////////////////////////////////////////////////////

void CCircleAttribute::setPrimitiveAttribute(const CPrimitiveAttribute& attribute)
{
#ifdef _DEBUG
	assert(type == attribute.getType());
#endif
	//Initialize it.
	initialize(attribute.primitiveData.circle.radius);
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetupAttribute
//
/////////////////////////////////////////////////////////////////////////////////

void CCircleAttribute::setupAttribute()
{
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::circle0Primitive ||
		type == CPrimitiveAttribute::circle3Primitive ||
		type == CPrimitiveAttribute::circle4Primitive ||
		type == CPrimitiveAttribute::circle5Primitive ||
		type == CPrimitiveAttribute::circle6Primitive);
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
	assert(getIndexCount() >= 3);
#endif
	//Index array.
	_SHORT* indexArray = (_SHORT *)index;

	//Vertex index.
	_SHORT vertexIndex = 0;

	//Center index.
	_SHORT centerIndex = vertexIndex; vertexIndex ++;

	//Start index.
	_SHORT startIndex = vertexIndex;
	//For each segment, add a triangle to the sides triangle list.
	for(_INTEGER i = segments;i > 0;i --)
	{
		//Set three indices (1 triangle) per segment.
		*indexArray = centerIndex; indexArray ++;
		*indexArray = vertexIndex; indexArray ++;
		*indexArray = (i > 1) ? (vertexIndex + 1) : startIndex; indexArray ++; vertexIndex ++;
	}

	//Get vertex.
	_FLOAT3* vertex = CVertexAttribute::getFloat3Vertex();
#ifdef _DEBUG
	assert(vertex != _NULL);
	assert(getVertexCount() >= 4);
#endif

	//Get normal.
	_FLOAT3* normal = CNormalAttribute::getFloat3Normal();
#ifdef _DEBUG
	assert(normal != _NULL);
	assert(getNormalCount() >= 4);
	assert(getNormalCount() == getVertexCount());
#endif

	//Get coordinates.
	_FLOAT2* coordinates = CTextureAttribute::getFloat2Texture();
#ifdef _DEBUG
	assert(coordinates != _NULL);
	assert(getTextureCount() >= 4);
	assert(getTextureCount() == getVertexCount());
#endif

	//Position index.
	_INTEGER positionIndex = 0;

	//Create the fan: Center vertex
	vertex[positionIndex][0] = 0.0f;
	vertex[positionIndex][1] = 0.0f;
	vertex[positionIndex][2] = 0.0f;
	normal[positionIndex][0] = 0.0f;
	normal[positionIndex][1] = -1.0f;
	normal[positionIndex][2] = 0.0f;
	coordinates[positionIndex][0] = 0.5f;
	coordinates[positionIndex][1] = 0.5f;
	positionIndex ++;

	//Compute delta.
	_FLOAT rDeltaSegAngle = 2.0f * (_FLOAT)D3DX_PI / (_FLOAT)segments;

	//Create the bottom triangle fan: Edge vertices
	for(_INTEGER i = segments;i >= 0;i --)
	{
		_FLOAT x0 = radius * sinf(i * rDeltaSegAngle);
		_FLOAT z0 = radius * cosf(i * rDeltaSegAngle);

		vertex[positionIndex][0] = x0;
		vertex[positionIndex][1] = 0.0f;
		vertex[positionIndex][2] = z0;
		normal[positionIndex][0] = 0.0f;
		normal[positionIndex][1] = -1.0f;
		normal[positionIndex][2] = 0.0f;

		_FLOAT tu0 = (0.5f * sinf(i * rDeltaSegAngle)) + 0.5f;
		_FLOAT tv0 = (0.5f * cosf(i * rDeltaSegAngle)) + 0.5f;

		coordinates[positionIndex][0] = tu0;
		coordinates[positionIndex][1] = tv0;
		positionIndex ++;
	}
}
