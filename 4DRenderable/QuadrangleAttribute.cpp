///////////////////////////////////////////////////////////////////////////////
//
// QuadrangleAttribute.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "QuadrangleAttribute.h"

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
#define DEFAULT_SEGMENTS									2

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Square
const CQuadrangleAttribute CQuadrangleAttribute::quadrangle0;

///////////////////////////////////////////////////////////////////////////////
//
// CQuadrangleAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CQuadrangleAttribute::CQuadrangleAttribute(void)
{
	//Create quadrangle0.
	createAttribute(DEFAULT_RINGS,DEFAULT_SEGMENTS);
	//Set type.
	type = CPrimitiveAttribute::quadrangle0Primitive; initializeDefault();
}

///////////////////////////////////////////////////////////////////////////////
//
// CQuadrangleAttribute
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CQuadrangleAttribute::~CQuadrangleAttribute(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateAttribute
//
/////////////////////////////////////////////////////////////////////////////////

void CQuadrangleAttribute::createAttribute(_INTEGER rings,_INTEGER segments)
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
	_INTEGER vertexCount = 4;//Four points.
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
	assert(indexCount >= 2);
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

CPrimitiveAttribute CQuadrangleAttribute::getPrimitiveAttribute() const
{
	//Attribute.
	CPrimitiveAttribute attribute;
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::quadrangle0Primitive);
#endif
	//Set type.
	attribute.setType(type);
	//Copy data.
	attribute.rings = rings;
	attribute.segments = segments;
	//Copy data.
	memcpy(attribute.primitiveData.quadrangle.a,a,sizeof(_FLOAT2));
	memcpy(attribute.primitiveData.quadrangle.b,b,sizeof(_FLOAT2));
	memcpy(attribute.primitiveData.quadrangle.c,c,sizeof(_FLOAT2));
	memcpy(attribute.primitiveData.quadrangle.d,d,sizeof(_FLOAT2));
	//Return attribute.
	return attribute;
}

/////////////////////////////////////////////////////////////////////////////////
//
// InitializeDefault
//
/////////////////////////////////////////////////////////////////////////////////

void CQuadrangleAttribute::initializeDefault()
{
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::quadrangle0Primitive);
#endif
	//Set points.
	a[0] = -1.0f;
	a[1] = 1.0f;
	//Set points.
	b[0] = 1.0f;
	b[1] = 1.0f;
	//Set points.
	c[0] = 1.0f;
	c[1] = -1.0f;
	//Set points.
	d[0] = -1.0f;
	d[1] = -1.0f;
	//Setup attribute.
	setupAttribute();
}

/////////////////////////////////////////////////////////////////////////////////
//
// Initialize
//
/////////////////////////////////////////////////////////////////////////////////

void CQuadrangleAttribute::initialize(const _FLOAT2 a,const _FLOAT2 b,const _FLOAT2 c,const _FLOAT2 d)
{
#ifdef _DEBUG
	assert(a != _NULL && b != _NULL && c != _NULL && d != _NULL);
#endif

#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::quadrangle0Primitive);
#endif
	//Copy data.
	memcpy(this->a,a,sizeof(_FLOAT2));
	memcpy(this->b,b,sizeof(_FLOAT2));
	memcpy(this->c,c,sizeof(_FLOAT2));
	memcpy(this->d,d,sizeof(_FLOAT2));
	//Setup attribute.
	setupAttribute();
}

///////////////////////////////////////////////////////////////////////////////
//
// SetPrimitiveAttribute
//
///////////////////////////////////////////////////////////////////////////////

void CQuadrangleAttribute::setPrimitiveAttribute(const CPrimitiveAttribute& attribute)
{
#ifdef _DEBUG
	assert(type == attribute.getType());
#endif
	//Initialize it.
	initialize(attribute.primitiveData.quadrangle.a,attribute.primitiveData.quadrangle.b,
				attribute.primitiveData.quadrangle.c,attribute.primitiveData.quadrangle.d);
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetupAttribute
//
/////////////////////////////////////////////////////////////////////////////////

void CQuadrangleAttribute::setupAttribute()
{
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::quadrangle0Primitive);
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
	assert(getIndexCount() >= 2);
#endif
	//Set index.
	index[0][0] = 0, index[0][1] = 1, index[0][2] = 3;
	index[1][0] = 3, index[1][1] = 1, index[1][2] = 2;

	//Get vertex.
	_FLOAT3* vertex = CVertexAttribute::getFloat3Vertex();
#ifdef _DEBUG
	assert(vertex != _NULL);
	assert(getVertexCount() >= 4);
#endif
	//Copy.
	memcpy(&vertex[0],(_FLOAT *)C4DVector3(a[0],a[1],0.0f),sizeof(_FLOAT3));
	memcpy(&vertex[1],(_FLOAT *)C4DVector3(b[0],b[1],0.0f),sizeof(_FLOAT3));
	memcpy(&vertex[2],(_FLOAT *)C4DVector3(c[0],c[1],0.0f),sizeof(_FLOAT3));
	memcpy(&vertex[3],(_FLOAT *)C4DVector3(d[0],d[1],0.0f),sizeof(_FLOAT3));

	//Normal.
	C4DVector3 n(0.0f,0.0f,-1.0f);
	//Get normal.
	_FLOAT3* normal = CNormalAttribute::getFloat3Normal();
#ifdef _DEBUG
	assert(normal != _NULL);
	assert(getNormalCount() >= 4);
	assert(getNormalCount() == getVertexCount());
#endif
	//Copy.
	memcpy(&normal[0],(_FLOAT *)n,sizeof(_FLOAT3));
	memcpy(&normal[1],(_FLOAT *)n,sizeof(_FLOAT3));
	memcpy(&normal[2],(_FLOAT *)n,sizeof(_FLOAT3));
	memcpy(&normal[3],(_FLOAT *)n,sizeof(_FLOAT3));

	//Get coordinates.
	_FLOAT2* coordinates = CTextureAttribute::getFloat2Texture();
#ifdef _DEBUG
	assert(coordinates != _NULL);
	assert(getTextureCount() >= 4);
	assert(getTextureCount() == getVertexCount());
#endif
	//Set value.
	coordinates[0][0] = 0.0f, coordinates[0][1] = 0.0f;
	coordinates[1][0] = 1.0f, coordinates[1][1] = 0.0f;
	coordinates[2][0] = 1.0f, coordinates[2][1] = 1.0f;
	coordinates[3][0] = 0.0f, coordinates[3][1] = 1.0f;
}
