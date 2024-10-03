///////////////////////////////////////////////////////////////////////////////
//
// HemisphereAttribute.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "HemisphereAttribute.h"

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

//Sphere0.
const CHemisphereAttribute CHemisphereAttribute::hemisphere0(DEFAULT_RINGS,DEFAULT_SEGMENTS);

///////////////////////////////////////////////////////////////////////////////
//
// CHemisphereAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CHemisphereAttribute::CHemisphereAttribute(void)
{
	//Create hemisphere0.
	createAttribute(DEFAULT_RINGS,DEFAULT_SEGMENTS);
	//Set type and initialize default.
	type = CPrimitiveAttribute::hemisphere0Primitive; initializeDefault();
}

///////////////////////////////////////////////////////////////////////////////
//
// CHemisphereAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CHemisphereAttribute::CHemisphereAttribute(_INTEGER rings,_INTEGER segments)
{
#ifdef _DEBUG
	assert(rings == DEFAULT_RINGS && segments == DEFAULT_SEGMENTS);
#endif
	//Create hemisphere0.
	createAttribute(rings,segments);
	//Set type and initialize default.
	type = CPrimitiveAttribute::hemisphere0Primitive; initializeDefault();
}

///////////////////////////////////////////////////////////////////////////////
//
// CHemisphereAttribute
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CHemisphereAttribute::~CHemisphereAttribute(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateAttribute
//
/////////////////////////////////////////////////////////////////////////////////

void CHemisphereAttribute::createAttribute(_INTEGER rings,_INTEGER segments)
{
#ifdef _DEBUG
	assert(rings >= 2 && segments >= 3);
#endif
	//Set rings.
	this->rings = rings;
	//Set segments.
	this->segments = segments;

	//Index count.
	_INTEGER indexCount = 2 * rings * (segments + 1) + segments;
	//Create index.
	CIndexAttribute::createShort3Index(indexCount);

	//Vertex count.
	_INTEGER vertexCount = (rings + 1) * (segments + 1) + ((segments + 1) + 1);
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
	assert(indexCount >= 19);
	assert(vertexCount >= 17);
	assert(vertexCount == normalCount);
	assert(vertexCount == textureCount);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// GetPrimitiveAttribute
//
/////////////////////////////////////////////////////////////////////////////////

CPrimitiveAttribute CHemisphereAttribute::getPrimitiveAttribute() const
{
	//Attribute.
	CPrimitiveAttribute attribute;
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::hemisphere0Primitive);
#endif
	//Set type.
	attribute.setType(type);
	//Copy data.
	attribute.rings = rings;
	attribute.segments = segments;
	//Copy data.
	attribute.primitiveData.hemisphere.radius = radius;
	//Return attribute.
	return attribute;
}

/////////////////////////////////////////////////////////////////////////////////
//
// InitializeDefault
//
/////////////////////////////////////////////////////////////////////////////////

void CHemisphereAttribute::initializeDefault()
{
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::hemisphere0Primitive);
#endif
	//Set value.
	radius = 1.0f;
	//Setup attribute.
	setupAttribute();
}

/////////////////////////////////////////////////////////////////////////////////
//
// Initialize
//
/////////////////////////////////////////////////////////////////////////////////

void CHemisphereAttribute::initialize(_FLOAT radius)
{
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::hemisphere0Primitive);
#endif
	//Set value.
	this->radius = radius;
	//Setup attribute.
	setupAttribute();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetBoxAttribute
//
///////////////////////////////////////////////////////////////////////////////

CBoxAttribute CHemisphereAttribute::getBoxAttribute() const
{
	CBoxAttribute attribute;

	//Set box.
	{
		//Box.
		CSimpleBox box;
		//Set value.
		box.x() = 0.0f;
		box.y() = radius / 2.0f;
		box.z() = 0.0f;
		box.dx() = radius;
		box.dy() = radius / 2.0f;
		box.dz() = radius;
		//Set box.
		attribute.setBox(box);
	}
	//Set sphere.
	{
		//Sphere.
		CSimpleSphere sphere;
		//Set value.
		sphere.r() = radius;
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

void CHemisphereAttribute::setPrimitiveAttribute(const CPrimitiveAttribute& attribute)
{
#ifdef _DEBUG
	assert(type == attribute.getType());
#endif
	//Initialize it.
	initialize(attribute.primitiveData.hemisphere.radius);
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetupAttribute
//
/////////////////////////////////////////////////////////////////////////////////

void CHemisphereAttribute::setupAttribute()
{
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::hemisphere0Primitive);
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
	assert(getIndexCount() >= 19);
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
			//Add two indices except for the last ring .
			if(i != rings) 
			{
				*indexArray = vertexIndex; indexArray ++;
				*indexArray = vertexIndex + (segments + 1);	indexArray ++;
				*indexArray = vertexIndex + 1; indexArray ++;
				*indexArray = vertexIndex + (segments + 1); indexArray ++;
				*indexArray = vertexIndex + (segments + 1) + 1; indexArray ++;
				*indexArray = vertexIndex + 1; indexArray ++;
				vertexIndex ++;
			}
		}
	}

	//Index.
	_SHORT centerIndex;
	//Center index.
	centerIndex = (rings + 1) * (segments + 1) + 1;
	vertexIndex = centerIndex + 1;

	//For each segment, add a triangle to the sides triangle list
	for(_INTEGER i = segments;i > 0;i --)
	{
		//Set three indices (1 triangle) per segment
		*indexArray = centerIndex; indexArray ++;
		*indexArray = vertexIndex; indexArray ++;
		*indexArray = vertexIndex + 1; indexArray ++;
		vertexIndex ++;
	}

	//Get vertex.
	_FLOAT3* vertex = CVertexAttribute::getFloat3Vertex();
#ifdef _DEBUG
	assert(vertex != _NULL);
	assert(getVertexCount() >= 17);
#endif

	//Get normal.
	_FLOAT3* normal = CNormalAttribute::getFloat3Normal();
#ifdef _DEBUG
	assert(normal != _NULL);
	assert(getNormalCount() >= 17);
	assert(getNormalCount() == getVertexCount());
#endif

	//Get coordinates.
	_FLOAT2* coordinates = CTextureAttribute::getFloat2Texture();
#ifdef _DEBUG
	assert(coordinates != _NULL);
	assert(getTextureCount() >= 17);
	assert(getTextureCount() == getVertexCount());
#endif

	//Position index.
	_INTEGER positionIndex = 0;

	//Establish constants used in sphere generation
	_FLOAT rDeltaRingAngle = (_FLOAT)D3DX_PI / 2.0f / rings;
	_FLOAT rDeltaSegAngle = 2.0f * (_FLOAT)D3DX_PI / segments;

	//Generate the group of rings for the sphere
	for(_INTEGER i = 0;i < rings + 1;i ++)
	{
		_FLOAT r0 = radius * sinf(i * rDeltaRingAngle);
		_FLOAT y0 = radius * cosf(i * rDeltaRingAngle);
		//Generate the group of segments for the current ring
		for(_INTEGER j = 0;j < segments + 1;j ++)
		{
			_FLOAT x0 = r0 * sinf(j * rDeltaSegAngle);
			_FLOAT z0 = r0 * cosf(j * rDeltaSegAngle);
			//Calculate normal.
			C4DVector3 n = C4DVector3(x0,y0,z0).normalize();
			//Add one vertex to the strip which makes up the sphere
			vertex[positionIndex][0] = x0;
			vertex[positionIndex][1] = y0;
			vertex[positionIndex][2] = z0;
			normal[positionIndex][0] = n.x();
			normal[positionIndex][1] = n.y();
			normal[positionIndex][2] = n.z();
			coordinates[positionIndex][0] = 1.0f - (_FLOAT)j / (_FLOAT)segments;
			coordinates[positionIndex][1] = (_FLOAT)i / (_FLOAT)rings;
			//Add position.
			positionIndex ++;
		}
	}

	//Create the bottom triangle fan: Center
	vertex[positionIndex][0] = 0.0f;
	vertex[positionIndex][1] = 0.0f;
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
		vertex[positionIndex][1] = 0.0f;
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
