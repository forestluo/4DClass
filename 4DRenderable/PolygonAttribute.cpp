///////////////////////////////////////////////////////////////////////////////
//
// PolygonAttribute.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "PolygonAttribute.h"

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
#define DEFAULT_SEGMENTS									4

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Polygon4.
const CPolygonAttribute CPolygonAttribute::polygon4(4);
//Polygon6.
const CPolygonAttribute CPolygonAttribute::polygon6(6);
//Polygon8.
const CPolygonAttribute CPolygonAttribute::polygon8(8);
//Polygon12.
const CPolygonAttribute CPolygonAttribute::polygon12(12);
//Polygon20.
const CPolygonAttribute CPolygonAttribute::polygon20(20);

///////////////////////////////////////////////////////////////////////////////
//
// CPolygonAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CPolygonAttribute::CPolygonAttribute(void)
{
	//Create polygon0.
	createAttribute(DEFAULT_RINGS,DEFAULT_SEGMENTS);
	//Set type and initialize default.
	type = CPrimitiveAttribute::polygon4Primitive; initializeDefault();
}

///////////////////////////////////////////////////////////////////////////////
//
// CPolygonAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CPolygonAttribute::CPolygonAttribute(_INTEGER segments)
{
	//Create polygon.
	createAttribute(DEFAULT_RINGS,segments);
	//Check segments.
	switch(segments)
	{
	case DEFAULT_SEGMENTS:
		type = CPrimitiveAttribute::polygon4Primitive;
		break;
	case 6:
		type = CPrimitiveAttribute::polygon6Primitive;
		break;
	case 8:
		type = CPrimitiveAttribute::polygon8Primitive;
		break;
	case 12:
		type = CPrimitiveAttribute::polygon12Primitive;
		break;
	case 20:
		type = CPrimitiveAttribute::polygon20Primitive;
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
// CPolygonAttribute
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CPolygonAttribute::~CPolygonAttribute(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateAttribute
//
/////////////////////////////////////////////////////////////////////////////////

void CPolygonAttribute::createAttribute(_INTEGER rings,_INTEGER segments)
{
#ifdef _DEBUG
	assert(segments >= 3);
#endif
	//Set rings.
	this->rings = rings;
	//Set segments.
	this->segments = segments;

	//Index count.
	_INTEGER indexCount;
	//Vertex count.
	_INTEGER vertexCount;
	//Check segments.
	if(segments == 4)
	{
		//Index count.
		indexCount = 4;
		//Vertex count.
		vertexCount = 4;
	}
	else if(segments == 6)
	{
		//Index count.
		indexCount = 12;
		//Vertex count.
		vertexCount = 8;
	}
	else if(segments == 8)
	{
		//Index count.
		indexCount = 8;
		//Vertex count.
		vertexCount = 6;
	}
	else if(segments == 12)
	{
		//Index count.
		indexCount = 36;
		//Vertex count.
		vertexCount = 20;
	}
	else if(segments == 20)
	{
		//Index count.
		indexCount = 20;
		//Vertex count.
		vertexCount = 12;
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
	//Create index.
	CIndexAttribute::createShort3Index(indexCount);
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
	assert(indexCount >= 4);
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

CPrimitiveAttribute CPolygonAttribute::getPrimitiveAttribute() const
{
	//Attribute.
	CPrimitiveAttribute attribute;
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::polygon4Primitive ||
		type == CPrimitiveAttribute::polygon6Primitive ||
		type == CPrimitiveAttribute::polygon8Primitive ||
		type == CPrimitiveAttribute::polygon12Primitive ||
		type == CPrimitiveAttribute::polygon20Primitive);
#endif
	//Set type.
	attribute.setType(type);
	//Copy data.
	attribute.rings = rings;
	attribute.segments = segments;
	//Copy data.
	attribute.primitiveData.polygon.radius = radius;
	//Return attribute.
	return attribute;
}

/////////////////////////////////////////////////////////////////////////////////
//
// InitializeDefault
//
/////////////////////////////////////////////////////////////////////////////////

void CPolygonAttribute::initializeDefault()
{
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::polygon4Primitive ||
		type == CPrimitiveAttribute::polygon6Primitive ||
		type == CPrimitiveAttribute::polygon8Primitive ||
		type == CPrimitiveAttribute::polygon12Primitive ||
		type == CPrimitiveAttribute::polygon20Primitive);
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

void CPolygonAttribute::initialize(_FLOAT radius)
{
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::polygon4Primitive ||
		type == CPrimitiveAttribute::polygon6Primitive ||
		type == CPrimitiveAttribute::polygon8Primitive ||
		type == CPrimitiveAttribute::polygon12Primitive ||
		type == CPrimitiveAttribute::polygon20Primitive);
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

void CPolygonAttribute::setPrimitiveAttribute(const CPrimitiveAttribute& attribute)
{
#ifdef _DEBUG
	assert(type == attribute.getType());
#endif
	//Initialize it.
	initialize(attribute.primitiveData.polygon.radius);
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetupAttribute
//
/////////////////////////////////////////////////////////////////////////////////

void CPolygonAttribute::setupAttribute()
{
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::polygon4Primitive ||
		type == CPrimitiveAttribute::polygon6Primitive ||
		type == CPrimitiveAttribute::polygon8Primitive ||
		type == CPrimitiveAttribute::polygon12Primitive ||
		type == CPrimitiveAttribute::polygon20Primitive);
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
	assert(getIndexCount() >= 4);
#endif
	//Index array.
	_SHORT* indexArray = (_SHORT *)index;

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

	//Vector.
	C4DVector3 vector;
	//Position index.
	_INTEGER positionIndex = 0;
	//Check segments.
	if(segments == 4)
	{
		//Set index.
		indexArray[0] = 0; indexArray[1] = 1; indexArray[2] = 2;
		indexArray[3] = 0; indexArray[4] = 2; indexArray[5] = 3;
		indexArray[6] = 0; indexArray[7] = 3; indexArray[8] = 1;
		indexArray[9] = 1; indexArray[10] = 3; indexArray[11] = 2;

		_FLOAT sq2 = sqrtf(2.0f), sq3 = sqrtf(3.0f);

		//Set vertex.
		vertex[positionIndex][0] = 0.0f, vertex[positionIndex][1] = radius, vertex[positionIndex][2] = 0.0f;
		vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
		normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
		coordinates[positionIndex][0] = 0.0f, coordinates[positionIndex][1] = 0.0f;
		//Add position index.
		positionIndex ++;

		//Set vertex.
		vertex[positionIndex][0] = 0.0f, vertex[positionIndex][1] = - radius / 3.0f, vertex[positionIndex][2] = radius * 2.0f * sq2 / 3.0f;
		vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
		normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
		coordinates[positionIndex][0] = 0.0f, coordinates[positionIndex][1] = 1.0f;
		//Add position index.
		positionIndex ++;

		//Set vertex.
		vertex[positionIndex][0] = radius * sq2 / sq3, vertex[positionIndex][1] = - radius / 3.0f, vertex[positionIndex][2] = - radius * sq2 / 3.0f;
		vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
		normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
		coordinates[positionIndex][0] = 1.0f, coordinates[positionIndex][1] = 0.0f;
		//Add position index.
		positionIndex ++;

		//Set vertex.
		vertex[positionIndex][0] = - radius * sq2 / sq3, vertex[positionIndex][1] = - radius / 3.0f, vertex[positionIndex][2] = - radius * sq2 / 3.0f;
		vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
		normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
		coordinates[positionIndex][0] = 1.0f, coordinates[positionIndex][1] = 1.0f;
		//Add position index.
		positionIndex ++;
	}
	else if(segments == 6)
	{
		//Set index.
		indexArray[0]  = 7; indexArray[1]  = 2; indexArray[2]  = 0;
		indexArray[3]  = 0; indexArray[4]  = 1; indexArray[5]  = 7;

		indexArray[6]  = 3; indexArray[7]  = 5; indexArray[8]  = 4;
		indexArray[9]  = 4; indexArray[10] = 6; indexArray[11] = 3;

		indexArray[12] = 1; indexArray[13] = 0; indexArray[14] = 3;
		indexArray[15] = 3; indexArray[16] = 6; indexArray[17] = 1;

		indexArray[18] = 5; indexArray[19] = 2; indexArray[20] = 7;
		indexArray[21] = 7; indexArray[22] = 4; indexArray[23] = 5;

		indexArray[24] = 0; indexArray[25] = 2; indexArray[26] = 5;
		indexArray[27] = 5; indexArray[28] = 3; indexArray[29] = 0;

		indexArray[30] = 4; indexArray[31] = 7; indexArray[32] = 1;
		indexArray[33] = 1; indexArray[34] = 6; indexArray[35] = 4;

		_FLOAT sq2 = sqrtf(2.0f), sq3 = sqrtf(3.0f);

		//Set vertex.
		vertex[positionIndex][0] = 0.0f, vertex[positionIndex][1] = radius, vertex[positionIndex][2] = 0.0f;
		vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
		normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
		coordinates[positionIndex][0] = 0.0f, coordinates[positionIndex][1] = 0.0f;
		//Add position index.
		positionIndex ++;

		//Set vertex.
		vertex[positionIndex][0] = 0.0f, vertex[positionIndex][1] = radius / 3.0f, vertex[positionIndex][2] = radius * 2.0f * sq2 / 3.0f;
		vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
		normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
		coordinates[positionIndex][0] = 0.0f, coordinates[positionIndex][1] = 1.0f;
		//Add position index.
		positionIndex ++;

		//Set vertex.
		vertex[positionIndex][0] = radius * sq2 / sq3, vertex[positionIndex][1] = radius / 3.0f, vertex[positionIndex][2] = - radius * sq2 / 3.0f;
		vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
		normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
		coordinates[positionIndex][0] = 1.0f, coordinates[positionIndex][1] = 0.0f;
		//Add position index.
		positionIndex ++;

		//Set vertex.
		vertex[positionIndex][0] = - radius * sq2 / sq3, vertex[positionIndex][1] = radius / 3.0f, vertex[positionIndex][2] = - radius * sq2 / 3.0f;
		vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
		normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
		coordinates[positionIndex][0] = 1.0f, coordinates[positionIndex][1] = 1.0f;
		//Add position index.
		positionIndex ++;

		for(_INTEGER i = 0; i < 4; i ++)
		{
			//Set vertex.
			vertex[positionIndex][0] = -vertex[i][0], vertex[positionIndex][1] = -vertex[i][1], vertex[positionIndex][2] = -vertex[i][2];
			vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
			normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
			coordinates[positionIndex][0] = coordinates[i][0], coordinates[positionIndex][1] = coordinates[i][1];
			//Add position index.
			positionIndex ++;
		}
	}
	else if(segments == 8)
	{
		//Set index.
		indexArray[0]  = 0; indexArray[1]  = 1; indexArray[2]  = 2;
		indexArray[3]  = 0; indexArray[4]  = 2; indexArray[5]  = 4;

		indexArray[6]  = 0; indexArray[7]  = 4; indexArray[8]  = 5;
		indexArray[9]  = 0; indexArray[10] = 5; indexArray[11] = 1;

		indexArray[12] = 3; indexArray[13] = 5; indexArray[14] = 4;
		indexArray[15] = 3; indexArray[16] = 1; indexArray[17] = 5;

		indexArray[18] = 3; indexArray[19] = 2; indexArray[20] = 1;
		indexArray[21] = 3; indexArray[22] = 4; indexArray[23] = 2;

		//Set vertex.
		vertex[positionIndex][0] = 0.0f, vertex[positionIndex][1] = radius, vertex[positionIndex][2] = 0.0f;
		vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
		normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
		coordinates[positionIndex][0] = 0.0f, coordinates[positionIndex][1] = 0.0f;
		//Add position index.
		positionIndex ++;

		//Set vertex.
		vertex[positionIndex][0] = 0.0f, vertex[positionIndex][1] = 0.0f, vertex[positionIndex][2] = radius;
		vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
		normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
		coordinates[positionIndex][0] = 1.0f, coordinates[positionIndex][1] = 0.0f;
		//Add position index.
		positionIndex ++;

		//Set vertex.
		vertex[positionIndex][0] = radius, vertex[positionIndex][1] = 0.0f, vertex[positionIndex][2] = 0.0f;
		vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
		normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
		coordinates[positionIndex][0] = 1.0f, coordinates[positionIndex][1] = 1.0f;
		//Add position index.
		positionIndex ++;

		for(_INTEGER i = 0; i < 3; i ++)
		{
			//Set vertex.
			vertex[positionIndex][0] = -vertex[i][0], vertex[positionIndex][1] = -vertex[i][1], vertex[positionIndex][2] = -vertex[i][2];
			vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
			normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
			coordinates[positionIndex][0] = coordinates[i][0], coordinates[positionIndex][1] = coordinates[i][1];
			//Add position index.
			positionIndex ++;
		}
	}
	else if(segments == 12)
	{
		//Set index.
		indexArray[0]  = 0; indexArray[1]  = 1; indexArray[2]  = 4;
		indexArray[3]  = 0; indexArray[4]  = 4; indexArray[5]  = 5;
		indexArray[6]  = 0; indexArray[7]  = 5; indexArray[8]  = 2;

		indexArray[9]  = 0; indexArray[10] = 2; indexArray[11] = 6;
		indexArray[12] = 0; indexArray[13] = 6; indexArray[14] = 7;
		indexArray[15] = 0; indexArray[16] = 7; indexArray[17] = 3;

		indexArray[18] = 0; indexArray[19] = 3; indexArray[20] = 8;
		indexArray[21] = 0; indexArray[22] = 8; indexArray[23] = 9;
		indexArray[24] = 0; indexArray[25] = 9; indexArray[26] = 1;

		indexArray[27] = 1; indexArray[28] = 9; indexArray[29] = 16;
		indexArray[30] = 1; indexArray[31] = 16; indexArray[32] = 17;
		indexArray[33] = 1; indexArray[34] = 17; indexArray[35] = 4;

		indexArray[36] = 2; indexArray[37] = 5; indexArray[38] = 18;
		indexArray[39] = 2; indexArray[40] = 18; indexArray[41] = 19;
		indexArray[42] = 2; indexArray[43] = 19; indexArray[44] = 6;

		indexArray[45] = 3; indexArray[46] = 7; indexArray[47] = 14;
		indexArray[48] = 3; indexArray[49] = 14; indexArray[50] = 15;
		indexArray[51] = 3; indexArray[52] = 15; indexArray[53] = 8;

		indexArray[54] = 10; indexArray[55] = 12; indexArray[56] = 15;
		indexArray[57] = 10; indexArray[58] = 15; indexArray[59] = 14;
		indexArray[60] = 10; indexArray[61] = 14; indexArray[62] = 11;

		indexArray[63] = 10; indexArray[64] = 13; indexArray[65] = 17;
		indexArray[66] = 10; indexArray[67] = 17; indexArray[68] = 16;
		indexArray[69] = 10; indexArray[70] = 16; indexArray[71] = 12;

		indexArray[72] = 10; indexArray[73] = 11; indexArray[74] = 19;
		indexArray[75] = 10; indexArray[76] = 19; indexArray[77] = 18;
		indexArray[78] = 10; indexArray[79] = 18; indexArray[80] = 13;

		indexArray[81] = 11; indexArray[82] = 14; indexArray[83] = 7;
		indexArray[84] = 11; indexArray[85] = 7; indexArray[86] = 6;
		indexArray[87] = 11; indexArray[88] = 6; indexArray[89] = 19;

		indexArray[90] = 12; indexArray[91] = 16; indexArray[92] = 9;
		indexArray[93] = 12; indexArray[94] = 9; indexArray[95] = 8;
		indexArray[96] = 12; indexArray[97] = 8; indexArray[98] = 15;

		indexArray[99] = 13; indexArray[100] = 18; indexArray[101] = 5;
		indexArray[102] = 13; indexArray[103] = 5; indexArray[104] = 4;
		indexArray[105] = 13; indexArray[106] = 4; indexArray[107] = 17;

		_FLOAT sq3 = sqrtf(3.0f), sq5 = sqrtf(5.0f);
		_FLOAT t1 = (sq5 + 1.0f) / 2.0f, t2 = (sq5 - 1.0f) / 2.0f;

		//Set vertex.
		vertex[positionIndex][0] = 0.0f, vertex[positionIndex][1] = radius, vertex[positionIndex][2] = 0.0f;
		vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
		normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
		coordinates[positionIndex][0] = 0.0f, coordinates[positionIndex][1] = 0.0f;
		//Add position index.
		positionIndex ++;

		//Set vertex.
		vertex[positionIndex][0] = 0.0f, vertex[positionIndex][1] = radius * sq5 / 3.0f, vertex[positionIndex][2] = radius * 2.0f / 3.0f;
		vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
		normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
		coordinates[positionIndex][0] = 0.0f, coordinates[positionIndex][1] = 1.0f;
		//Add position index.
		positionIndex ++;

		//Set vertex.
		vertex[positionIndex][0] = radius * sq3 / 3.0f, vertex[positionIndex][1] = radius * sq5 / 3.0f, vertex[positionIndex][2] = - radius / 3.0f;
		vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
		normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
		coordinates[positionIndex][0] = 1.0f, coordinates[positionIndex][1] = 0.0f;
		//Add position index.
		positionIndex ++;

		//Set vertex.
		vertex[positionIndex][0] = - radius * sq3 / 3.0f, vertex[positionIndex][1] = radius * sq5 / 3.0f, vertex[positionIndex][2] = - radius / 3.0f;
		vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
		normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
		coordinates[positionIndex][0] = 1.0f, coordinates[positionIndex][1] = 1.0f;
		//Add position index.
		positionIndex ++;

		//Set vertex.
		vertex[positionIndex][0] = radius * sq3 / 3.0f, vertex[positionIndex][1] = radius / 3.0f, vertex[positionIndex][2] = radius * sq5 / 3.0f;
		vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
		normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
		coordinates[positionIndex][0] = 0.0f, coordinates[positionIndex][1] = 0.0f;
		//Add position index.
		positionIndex ++;

		//Set vertex.
		vertex[positionIndex][0] = radius * t1 * sq3 / 3.0f, vertex[positionIndex][1] = radius / 3.0f, vertex[positionIndex][2] = radius * t2 * t2 / 3.0f;
		vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
		normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
		coordinates[positionIndex][0] = 0.0f, coordinates[positionIndex][1] = 1.0f;
		//Add position index.
		positionIndex ++;

		//Set vertex.
		vertex[positionIndex][0] = radius * t2 * sq3 / 3.0f, vertex[positionIndex][1] = radius / 3.0f, vertex[positionIndex][2] = - radius * t1 * t1 / 3.0f;
		vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
		normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
		coordinates[positionIndex][0] = 1.0f, coordinates[positionIndex][1] = 0.0f;
		//Add position index.
		positionIndex ++;

		//Set vertex.
		vertex[positionIndex][0] = - radius * t2 * sq3 / 3.0f, vertex[positionIndex][1] = radius / 3.0f, vertex[positionIndex][2] = - radius * t1 * t1 / 3.0f;
		vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
		normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
		coordinates[positionIndex][0] = 1.0f, coordinates[positionIndex][1] = 1.0f;
		//Add position index.
		positionIndex ++;

		//Set vertex.
		vertex[positionIndex][0] = - radius * t1 * sq3 / 3.0f, vertex[positionIndex][1] = radius / 3.0f, vertex[positionIndex][2] = radius * t2 * t2 / 3.0f;
		vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
		normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
		coordinates[positionIndex][0] = 0.0f, coordinates[positionIndex][1] = 0.0f;
		//Add position index.
		positionIndex ++;

		//Set vertex.
		vertex[positionIndex][0] = - radius * sq3 / 3.0f, vertex[positionIndex][1] = radius / 3.0f, vertex[positionIndex][2] = radius * sq5 / 3.0f;
		vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
		normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
		coordinates[positionIndex][0] = 0.0f, coordinates[positionIndex][1] = 1.0f;
		//Add position index.
		positionIndex ++;

		for(_INTEGER i = 0; i < 10; i++)
		{
			//Set vertex.
			vertex[positionIndex][0] = -vertex[i][0], vertex[positionIndex][1] = -vertex[i][1], vertex[positionIndex][2] = -vertex[i][2];
			vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
			normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
			coordinates[positionIndex][0] = coordinates[i][0], coordinates[positionIndex][1] = coordinates[i][1];
			//Add position index.
			positionIndex ++;
		}
	}
	else if(segments == 20)
	{
		//Set index.
		indexArray[0]  = 0; indexArray[1]  = 1; indexArray[2]  = 2;
		indexArray[3]  = 0; indexArray[4]  = 2; indexArray[5]  = 3;

		indexArray[6]  = 0; indexArray[7]  = 3; indexArray[8]  = 4;
		indexArray[9]  = 0; indexArray[10] = 4; indexArray[11] = 5;

		indexArray[12] = 0; indexArray[13] = 5; indexArray[14] = 1;
		indexArray[15] = 1; indexArray[16] = 10; indexArray[17] = 2;

		indexArray[18] = 2; indexArray[19] = 11; indexArray[20] = 3;
		indexArray[21] = 3; indexArray[22] = 7; indexArray[23] = 4;

		indexArray[24] = 4; indexArray[25] = 8; indexArray[26] = 5;
		indexArray[27] = 5; indexArray[28] = 9; indexArray[29] = 1;

		indexArray[30] = 6; indexArray[31] = 8; indexArray[32] = 7;
		indexArray[33] = 6; indexArray[34] = 9; indexArray[35] = 8;

		indexArray[36] = 6; indexArray[37] = 10; indexArray[38] = 9;
		indexArray[39] = 6; indexArray[40] = 11; indexArray[41] = 10;

		indexArray[42] = 6; indexArray[43] = 7; indexArray[44] = 11;
		indexArray[45] = 7; indexArray[46] = 8; indexArray[47] = 4;

		indexArray[48] = 8; indexArray[49] = 9; indexArray[50] = 5;
		indexArray[51] = 9; indexArray[52] = 10; indexArray[53] = 1;

		indexArray[54] = 10; indexArray[55] = 11; indexArray[56] = 2;
		indexArray[57] = 11; indexArray[58] = 7; indexArray[59] = 3;

		_FLOAT sq5 = sqrtf(5.0f);
		_FLOAT t1 = (sq5 + 1.0f) / 2.0f, t2 = (sq5 - 1.0f) / 2.0f; 

		//Set vertex.
		vertex[positionIndex][0] = 0.0f, vertex[positionIndex][1] = radius, vertex[positionIndex][2] = 0.0f;
		vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
		normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
		coordinates[positionIndex][0] = 0.0f, coordinates[positionIndex][1] = 0.0f;
		//Add position index.
		positionIndex ++;

		//Set vertex.
		vertex[positionIndex][0] = 0.0f, vertex[positionIndex][1] = radius / sq5, vertex[positionIndex][2] = radius * 2.0f / sq5;
		vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
		normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
		coordinates[positionIndex][0] = 0.0f, coordinates[positionIndex][1] = 1.0f;
		//Add position index.
		positionIndex ++;

		//Set vertex.
		vertex[positionIndex][0] = radius * sqrt(t1 / sq5), vertex[positionIndex][1] = radius / sq5, vertex[positionIndex][2] = radius * t2 / sq5;
		vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
		normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
		coordinates[positionIndex][0] = 1.0f, coordinates[positionIndex][1] = 0.0f;
		//Add position index.
		positionIndex ++;

		//Set vertex.
		vertex[positionIndex][0] = radius * sqrt(t2 / sq5), vertex[positionIndex][1] = radius / sq5, vertex[positionIndex][2] = - radius * t1 / sq5;
		vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
		normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
		coordinates[positionIndex][0] = 1.0f, coordinates[positionIndex][1] = 1.0f;
		//Add position index.
		positionIndex ++;

		//Set vertex.
		vertex[positionIndex][0] = - radius * sqrt(t2 / sq5), vertex[positionIndex][1] = radius / sq5, vertex[positionIndex][2] = - radius * t1 / sq5;
		vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
		normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
		coordinates[positionIndex][0] = 0.0f, coordinates[positionIndex][1] = 0.0f;
		//Add position index.
		positionIndex ++;

		//Set vertex.
		vertex[positionIndex][0] = - radius * sqrt(t1 / sq5), vertex[positionIndex][1] = radius / sq5, vertex[positionIndex][2] = radius * t2 / sq5;
		vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
		normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
		coordinates[positionIndex][0] = 0.0f, coordinates[positionIndex][1] = 1.0f;
		//Add position index.
		positionIndex ++;

		for(_INTEGER i = 0; i < 6; i++)
		{
			//Set vertex.
			vertex[positionIndex][0] = -vertex[i][0], vertex[positionIndex][1] = -vertex[i][1], vertex[positionIndex][2] = -vertex[i][2];
			vector.x() = vertex[positionIndex][0], vector.y() = vertex[positionIndex][1], vector.z() = vertex[positionIndex][2];vector.normalize();
			normal[positionIndex][0] = vector.x(), normal[positionIndex][1] = vector.y(), normal[positionIndex][2] = vector.z();
			coordinates[positionIndex][0] = coordinates[i][0], coordinates[positionIndex][1] = coordinates[i][1];
			//Add position index.
			positionIndex ++;
		}
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
}
