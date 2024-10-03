///////////////////////////////////////////////////////////////////////////////
//
// CuboidAttribute.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "CuboidAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "DxMath.h"
#include <memory.h>

#include "4DVector3.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define DEFAULT_RINGS										0
#define DEFAULT_SEGMENTS									12

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Cuboid0.
const CCuboidAttribute CCuboidAttribute::cuboid0;

///////////////////////////////////////////////////////////////////////////////
//
// CCuboidAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CCuboidAttribute::CCuboidAttribute(void)
{
	//Create.
	createAttribute(DEFAULT_RINGS,DEFAULT_SEGMENTS);
	//Set type and initialize default.
	type = CPrimitiveAttribute::cuboid0Primitive; initializeDefault();
}

///////////////////////////////////////////////////////////////////////////////
//
// CCuboidAttribute
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CCuboidAttribute::~CCuboidAttribute(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateAttribute
//
/////////////////////////////////////////////////////////////////////////////////

void CCuboidAttribute::createAttribute(_INTEGER rings,_INTEGER segments)
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
	_INTEGER vertexCount = 24;//24 points.
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
	assert(vertexCount >= 24);
	assert(vertexCount == normalCount);
	assert(vertexCount == textureCount);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// GetPrimitiveAttribute
//
/////////////////////////////////////////////////////////////////////////////////

CPrimitiveAttribute CCuboidAttribute::getPrimitiveAttribute() const
{
	//Attribute.
	CPrimitiveAttribute attribute;
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::cuboid0Primitive);
#endif
	//Set type.
	attribute.setType(type);
	//Copy data.
	attribute.rings = rings;
	attribute.segments = segments;
	//Copy data.
	attribute.primitiveData.cuboid.depth = depth;
	attribute.primitiveData.cuboid.width = width;
	attribute.primitiveData.cuboid.height = height;
	//Return attribute.
	return attribute;
}

/////////////////////////////////////////////////////////////////////////////////
//
// InitializeDefault
//
/////////////////////////////////////////////////////////////////////////////////

void CCuboidAttribute::initializeDefault()
{
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::cuboid0Primitive);
#endif
	//Set default value.
	depth = 1.0f;
	width = 1.0f;
	height = 1.0f;
	//Setup attribute.
	setupAttribute();
}

/////////////////////////////////////////////////////////////////////////////////
//
// Initialize
//
/////////////////////////////////////////////////////////////////////////////////

void CCuboidAttribute::initialize(_FLOAT width,_FLOAT height,_FLOAT depth)
{
#ifdef _DEBUG
	assert(width > 0.0f && height > 0.0f && depth > 0.0f);
#endif

#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::cuboid0Primitive);
#endif
	//Copy data.
	this->depth = depth;
	this->width = width;
	this->height = height;
	//Setup attribute.
	setupAttribute();
}

///////////////////////////////////////////////////////////////////////////////
//
// SetPrimitiveAttribute
//
///////////////////////////////////////////////////////////////////////////////

void CCuboidAttribute::setPrimitiveAttribute(const CPrimitiveAttribute& attribute)
{
#ifdef _DEBUG
	assert(type == attribute.getType());
#endif
	//Initialize it.
	initialize(attribute.primitiveData.cuboid.width,
				attribute.primitiveData.cuboid.height,attribute.primitiveData.cuboid.depth);
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetupAttribute
//
/////////////////////////////////////////////////////////////////////////////////

void CCuboidAttribute::setupAttribute()
{
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::cuboid0Primitive ||
			type == CPrimitiveAttribute::floor0Primitive);
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
	assert(getIndexCount() >= 12);
#endif
	//Set index.
	index[0][0] = 0, index[0][1] = 1, index[0][2] = 2;//Top
	index[1][0] = 3, index[1][1] = 2, index[1][2] = 1;//Top
	index[2][0] = 4, index[2][1] = 5, index[2][2] = 6;//Face1
	index[3][0] = 7, index[3][1] = 6, index[3][2] = 5;//Face1
	index[4][0] = 8, index[4][1] = 9, index[4][2] = 10;//Face2
	index[5][0] = 11, index[5][1] = 10, index[5][2] = 9;//Face2
	index[6][0] = 12, index[6][1] = 13, index[6][2] = 14;//Face3
	index[7][0] = 15, index[7][1] = 14, index[7][2] = 13;//Face3
	index[8][0] = 16, index[8][1] = 17, index[8][2] = 18;//Face4
	index[9][0] = 19, index[9][1] = 18, index[9][2] = 17;//Face4
	index[10][0] = 20, index[10][1] = 21, index[10][2] = 22;//Bottom
	index[11][0] = 23, index[11][1] = 22, index[11][2] = 21;//Bottom

	//Get vertex.
	_FLOAT3* vertex = CVertexAttribute::getFloat3Vertex();
#ifdef _DEBUG
	assert(vertex != _NULL);
	assert(getVertexCount() >= 24);
#endif
	//Copy.
	memcpy(&vertex[0],(_FLOAT *)C4DVector3(0.0f - (width / 2), 0.0f + (height / 2), 0.0f - (depth / 2)),sizeof(_FLOAT3));
	memcpy(&vertex[1],(_FLOAT *)C4DVector3(0.0f - (width / 2), 0.0f + (height / 2), 0.0f + (depth / 2)),sizeof(_FLOAT3));
	memcpy(&vertex[2],(_FLOAT *)C4DVector3(0.0f + (width / 2), 0.0f + (height / 2), 0.0f - (depth / 2)),sizeof(_FLOAT3));
	memcpy(&vertex[3],(_FLOAT *)C4DVector3(0.0f + (width / 2), 0.0f + (height / 2), 0.0f + (depth / 2)),sizeof(_FLOAT3));
	//Copy.
	memcpy(&vertex[4],(_FLOAT *)C4DVector3(0.0f - (width / 2), 0.0f - (height / 2), 0.0f - (depth / 2)),sizeof(_FLOAT3));
	memcpy(&vertex[5],(_FLOAT *)C4DVector3(0.0f - (width / 2), 0.0f + (height / 2), 0.0f - (depth / 2)),sizeof(_FLOAT3));
	memcpy(&vertex[6],(_FLOAT *)C4DVector3(0.0f + (width / 2), 0.0f - (height / 2), 0.0f - (depth / 2)),sizeof(_FLOAT3));
	memcpy(&vertex[7],(_FLOAT *)C4DVector3(0.0f + (width / 2), 0.0f + (height / 2), 0.0f - (depth / 2)),sizeof(_FLOAT3));
	//Copy.
	memcpy(&vertex[8],(_FLOAT *)C4DVector3(0.0f + (width / 2), 0.0f - (height / 2), 0.0f - (depth / 2)),sizeof(_FLOAT3));
	memcpy(&vertex[9],(_FLOAT *)C4DVector3(0.0f + (width / 2), 0.0f + (height / 2), 0.0f - (depth / 2)),sizeof(_FLOAT3));
	memcpy(&vertex[10],(_FLOAT *)C4DVector3(0.0f + (width / 2), 0.0f - (height / 2), 0.0f + (depth / 2)),sizeof(_FLOAT3));
	memcpy(&vertex[11],(_FLOAT *)C4DVector3(0.0f + (width / 2), 0.0f + (height / 2), 0.0f + (depth / 2)),sizeof(_FLOAT3));
	//Copy.
	memcpy(&vertex[12],(_FLOAT *)C4DVector3(0.0f + (width / 2), 0.0f - (height / 2), 0.0f + (depth / 2)),sizeof(_FLOAT3));
	memcpy(&vertex[13],(_FLOAT *)C4DVector3(0.0f + (width / 2), 0.0f + (height / 2), 0.0f + (depth / 2)),sizeof(_FLOAT3));
	memcpy(&vertex[14],(_FLOAT *)C4DVector3(0.0f - (width / 2), 0.0f - (height / 2), 0.0f + (depth / 2)),sizeof(_FLOAT3));
	memcpy(&vertex[15],(_FLOAT *)C4DVector3(0.0f - (width / 2), 0.0f + (height / 2), 0.0f + (depth / 2)),sizeof(_FLOAT3));
	//Copy.
	memcpy(&vertex[16],(_FLOAT *)C4DVector3(0.0f - (width / 2), 0.0f - (height / 2), 0.0f + (depth / 2)),sizeof(_FLOAT3));
	memcpy(&vertex[17],(_FLOAT *)C4DVector3(0.0f - (width / 2), 0.0f + (height / 2), 0.0f + (depth / 2)),sizeof(_FLOAT3));
	memcpy(&vertex[18],(_FLOAT *)C4DVector3(0.0f - (width / 2), 0.0f - (height / 2), 0.0f - (depth / 2)),sizeof(_FLOAT3));
	memcpy(&vertex[19],(_FLOAT *)C4DVector3(0.0f - (width / 2), 0.0f + (height / 2), 0.0f - (depth / 2)),sizeof(_FLOAT3));
	//Copy.
	memcpy(&vertex[20],(_FLOAT *)C4DVector3(0.0f + (width / 2), 0.0f - (height / 2), 0.0f - (depth / 2)),sizeof(_FLOAT3));
	memcpy(&vertex[21],(_FLOAT *)C4DVector3(0.0f + (width / 2), 0.0f - (height / 2), 0.0f + (depth / 2)),sizeof(_FLOAT3));
	memcpy(&vertex[22],(_FLOAT *)C4DVector3(0.0f - (width / 2), 0.0f - (height / 2), 0.0f - (depth / 2)),sizeof(_FLOAT3));
	memcpy(&vertex[23],(_FLOAT *)C4DVector3(0.0f - (width / 2), 0.0f - (height / 2), 0.0f + (depth / 2)),sizeof(_FLOAT3));

	//Get normal.
	_FLOAT3* normal = CNormalAttribute::getFloat3Normal();
#ifdef _DEBUG
	assert(normal != _NULL);
	assert(getNormalCount() >= 24);
	assert(getNormalCount() == getVertexCount());
#endif
	//Array holds how many times this vertex is shared.
	_INTEGER sharedPolygons[24];
	//Clear memmory.
	memset(sharedPolygons,0,24 * sizeof(_INTEGER));
	//Array holds sum of all face normals for shared vertex.
	C4DVector3 vertexNormals[24];
	//For each triangle, count the number of times each vertex is used and
	//add together the normals of faces that share a vertex
	for(_INTEGER i = 0; i < 12; i ++)
	{
		_SHORT index1 = index[i][0];
		_SHORT index2 = index[i][1];
		_SHORT index3 = index[i][2];

		//Get triangle normal.
		C4DVector3 n(::GetTriangeNormal(&D3DXVECTOR3(vertex[index1][0],vertex[index1][1],vertex[index1][2]), 
								&D3DXVECTOR3(vertex[index2][0],vertex[index2][1],vertex[index2][2]), 
								&D3DXVECTOR3(vertex[index3][0],vertex[index3][1],vertex[index3][2])));

		//Add sharing count.
		sharedPolygons[index1] ++;
		sharedPolygons[index2] ++;
		sharedPolygons[index3] ++;

		//Add normal value.
		vertexNormals[index1] += n;
		vertexNormals[index2] += n;
		vertexNormals[index3] += n;
	}
	//For each vertex, calculate and set the average normal.
	for(_INTEGER i = 0; i < 24; i++)
	{
		//Get average value.
		vertexNormals[i] /= (_FLOAT)sharedPolygons[i];
		//Normalize it and copy.
		memcpy(&normal[i],(_FLOAT *)vertexNormals[i].normalize(),sizeof(_FLOAT3));
	}

	//Get coordinates.
	_FLOAT2* coordinates = CTextureAttribute::getFloat2Texture();
#ifdef _DEBUG
	assert(coordinates != _NULL);
	assert(getTextureCount() >= 24);
	assert(getTextureCount() == getVertexCount());
#endif
	//Set value.
	coordinates[0][0] = 0.0f, coordinates[0][1] = 1.0f;
	coordinates[1][0] = 0.0f, coordinates[1][1] = 0.0f;
	coordinates[2][0] = 1.0f, coordinates[2][1] = 1.0f;
	coordinates[3][0] = 1.0f, coordinates[3][1] = 0.0f;
	//Set value.
	coordinates[4][0] = 0.0f, coordinates[4][1] = 1.0f;
	coordinates[5][0] = 0.0f, coordinates[5][1] = 0.0f;
	coordinates[6][0] = 1.0f, coordinates[6][1] = 1.0f;
	coordinates[7][0] = 1.0f, coordinates[7][1] = 0.0f;
	//Set value.
	coordinates[8][0] = 0.0f, coordinates[8][1] = 1.0f;
	coordinates[9][0] = 0.0f, coordinates[9][1] = 0.0f;
	coordinates[10][0] = 1.0f, coordinates[10][1] = 1.0f;
	coordinates[11][0] = 1.0f, coordinates[11][1] = 0.0f;
	//Set value.
	coordinates[12][0] = 0.0f, coordinates[12][1] = 1.0f;
	coordinates[13][0] = 0.0f, coordinates[13][1] = 0.0f;
	coordinates[14][0] = 1.0f, coordinates[14][1] = 1.0f;
	coordinates[15][0] = 1.0f, coordinates[15][1] = 0.0f;
	//Set value.
	coordinates[16][0] = 0.0f, coordinates[16][1] = 1.0f;
	coordinates[17][0] = 0.0f, coordinates[17][1] = 0.0f;
	coordinates[18][0] = 1.0f, coordinates[18][1] = 1.0f;
	coordinates[19][0] = 1.0f, coordinates[19][1] = 0.0f;
	//Set value.
	coordinates[20][0] = 0.0f, coordinates[20][1] = 1.0f;
	coordinates[21][0] = 0.0f, coordinates[21][1] = 0.0f;
	coordinates[22][0] = 1.0f, coordinates[22][1] = 1.0f;
	coordinates[23][0] = 1.0f, coordinates[23][1] = 0.0f;
}
