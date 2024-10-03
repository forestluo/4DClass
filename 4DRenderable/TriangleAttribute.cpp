///////////////////////////////////////////////////////////////////////////////
//
// TriangleAttribute.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "TriangleAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include <memory.h>

#include "4DVector3.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define DEFAULT_RINGS										0
#define DEFAULT_SEGMENTS									1

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Triangle0.
const CTriangleAttribute CTriangleAttribute::triangle0;

///////////////////////////////////////////////////////////////////////////////
//
// CTriangleAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CTriangleAttribute::CTriangleAttribute(void)
{
	//Create.
	createAttribute(DEFAULT_RINGS,DEFAULT_SEGMENTS);
	//Set type and initialize default.
	type = CPrimitiveAttribute::triangle0Primitive; initializeDefault();
}

///////////////////////////////////////////////////////////////////////////////
//
// CTriangleAttribute
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CTriangleAttribute::~CTriangleAttribute(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateAttribute
//
/////////////////////////////////////////////////////////////////////////////////

void CTriangleAttribute::createAttribute(_INTEGER rings,_INTEGER segments)
{
	//Set rings.
	this->rings = rings;
	//Set segments.
	this->segments = segments;

	//Index count.
	_INTEGER indexCount = segments;
	//Create index.
	CIndexAttribute::createShort3Index(indexCount);

	//Vertex count.
	_INTEGER vertexCount = 3;//Three points.
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
	assert(indexCount >= 1);
	assert(vertexCount >= 3);
	assert(vertexCount == normalCount);
	assert(vertexCount == textureCount);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// GetPrimitiveAttribute
//
/////////////////////////////////////////////////////////////////////////////////

CPrimitiveAttribute CTriangleAttribute::getPrimitiveAttribute() const
{
	//Attribute.
	CPrimitiveAttribute attribute;
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::triangle0Primitive);
#endif
	//Set type.
	attribute.setType(type);
	//Copy data.
	attribute.rings = rings;
	attribute.segments = segments;
	//Copy data.
	memcpy(attribute.primitiveData.triangle.a,a,sizeof(_FLOAT3));
	memcpy(attribute.primitiveData.triangle.b,b,sizeof(_FLOAT3));
	memcpy(attribute.primitiveData.triangle.c,c,sizeof(_FLOAT3));
	//Return attribute.
	return attribute;
}

/////////////////////////////////////////////////////////////////////////////////
//
// InitializeDefault
//
/////////////////////////////////////////////////////////////////////////////////

void CTriangleAttribute::initializeDefault()
{
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::triangle0Primitive);
#endif
	//Set default value.
	a[0] = 0.0f;
	a[1] = 1.0f;
	a[2] = 0.0f;
	//Set point.
	b[0] = 1.0f;
	b[1] = 1.0f - sqrt(3.0f);
	b[2] = 0.0f;
	//Set point.
	c[0] = -1.0f;
	c[1] = 1.0f - sqrt(3.0f);
	c[2] = 0.0f;
	//Setup attribute.
	setupAttribute();
}

/////////////////////////////////////////////////////////////////////////////////
//
// Initialize
//
/////////////////////////////////////////////////////////////////////////////////

void CTriangleAttribute::initialize(const _FLOAT3 a,const _FLOAT3 b,const _FLOAT3 c)
{
#ifdef _DEBUG
	assert(a != _NULL && b != _NULL && c != _NULL);
#endif

#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::triangle0Primitive);
#endif
	//Copy data.
	memcpy(this->a,a,sizeof(_FLOAT3));
	memcpy(this->b,b,sizeof(_FLOAT3));
	memcpy(this->c,c,sizeof(_FLOAT3));
	//Setup attribute.
	setupAttribute();
}

///////////////////////////////////////////////////////////////////////////////
//
// SetPrimitiveAttribute
//
///////////////////////////////////////////////////////////////////////////////

void CTriangleAttribute::setPrimitiveAttribute(const CPrimitiveAttribute& attribute)
{
#ifdef _DEBUG
	assert(type == attribute.getType());
#endif
	//Initialize it.
	initialize(attribute.primitiveData.triangle.a,
				attribute.primitiveData.triangle.b,attribute.primitiveData.triangle.c);
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetupAttribute
//
/////////////////////////////////////////////////////////////////////////////////

void CTriangleAttribute::setupAttribute()
{
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::triangle0Primitive);
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
	assert(getIndexCount() >= 1);
#endif
	//Set index.
	index[0][0] = 0, index[0][1] = 1, index[0][2] = 2;

	//Get vertex.
	_FLOAT3* vertex = CVertexAttribute::getFloat3Vertex();
#ifdef _DEBUG
	assert(vertex != _NULL);
	assert(getVertexCount() >= 3);
#endif
	//Copy.
	memcpy(&vertex[0],a,sizeof(_FLOAT3));
	memcpy(&vertex[1],b,sizeof(_FLOAT3));
	memcpy(&vertex[2],c,sizeof(_FLOAT3));

	//Vector.
	C4DVector3 v1(b[0] - a[0],b[1] - a[1],b[2] - a[2]);
	C4DVector3 v2(c[0] - a[0],c[1] - a[1],c[2] - a[2]);
	//Normal.
	C4DVector3 n = C4DVector3::cross(v1,v2).normalize();

	//Get normal.
	_FLOAT3* normal = CNormalAttribute::getFloat3Normal();
#ifdef _DEBUG
	assert(normal != _NULL);
	assert(getNormalCount() >= 3);
	assert(getNormalCount() == getVertexCount());
#endif
	//Copy.
	memcpy(&normal[0],(_FLOAT *)n,sizeof(_FLOAT3));
	memcpy(&normal[1],(_FLOAT *)n,sizeof(_FLOAT3));
	memcpy(&normal[2],(_FLOAT *)n,sizeof(_FLOAT3));

	//Get coordinates.
	_FLOAT2* coordinates = CTextureAttribute::getFloat2Texture();
#ifdef _DEBUG
	assert(coordinates != _NULL);
	assert(getTextureCount() >= 3);
	assert(getTextureCount() == getVertexCount());
#endif
	//Set value.
	coordinates[0][0] = 0.0f, coordinates[0][1] = 0.0f;
	coordinates[1][0] = 1.0f, coordinates[1][1] = 0.0f;
	coordinates[2][0] = 0.0f, coordinates[2][1] = 1.0f;
}
