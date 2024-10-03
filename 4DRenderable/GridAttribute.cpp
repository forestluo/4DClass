///////////////////////////////////////////////////////////////////////////////
//
// GridAttribute.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "GridAttribute.h"

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

#define DEFAULT_RINGS										3
#define DEFAULT_SEGMENTS									4

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Grid4x3.
const CGridAttribute CGridAttribute::grid4x3(3,4);
//Grid20x15.
const CGridAttribute CGridAttribute::grid20x15(15,20);
//Ground80x60.
const CGridAttribute CGridAttribute::ground80x60(60,80);
//Ground320x240.
const CGridAttribute CGridAttribute::ground320x240(240,320);
//Ground640x480.
const CGridAttribute CGridAttribute::ground640x480(480,640);

///////////////////////////////////////////////////////////////////////////////
//
// CGridAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CGridAttribute::CGridAttribute(void)
{
	//Create.
	createAttribute(DEFAULT_RINGS,DEFAULT_SEGMENTS);
	//Set type and initialize default.
	type = CPrimitiveAttribute::grid4x3Primitive; initializeDefault();
}

///////////////////////////////////////////////////////////////////////////////
//
// CGridAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CGridAttribute::CGridAttribute(_INTEGER rings,_INTEGER segments)
{
	//Create.
	createAttribute(rings,segments);
	//Check rings and segments.
	if(rings == 3 && segments == 4)
	{
		//Set type and initialize default.
		type = CPrimitiveAttribute::grid4x3Primitive;
	}
	else if(rings == 15 && segments == 20)
	{
		//Set type and initialize default.
		type = CPrimitiveAttribute::grid20x15Primitive;
	}
	else if(rings == 60 && segments == 80)
	{
		//Set type and initialize default.
		type = CPrimitiveAttribute::ground80x60Primitive;
	}
	else if(rings == 240 && segments == 320)
	{
		//Set type and initialize default.
		type = CPrimitiveAttribute::ground320x240Primitive;
	}
	else if(rings == 480 && segments == 640)
	{
		//Set type and initialize default.
		type = CPrimitiveAttribute::ground640x480Primitive;
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
	//Initialize default.
	initializeDefault();
}

///////////////////////////////////////////////////////////////////////////////
//
// CGridAttribute
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CGridAttribute::~CGridAttribute(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateAttribute
//
/////////////////////////////////////////////////////////////////////////////////

void CGridAttribute::createAttribute(_INTEGER rings,_INTEGER segments)
{
#ifdef _DEBUG
	assert(rings > 0 && segments > 0);
#endif

	//Set rings.
	this->rings = rings;
	//Set segments.
	this->segments = segments;

	//Index count.
	_INTEGER indexCount = 2 * rings * segments;
	//Create index.
	CIndexAttribute::createInteger3Index(indexCount);

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

CPrimitiveAttribute CGridAttribute::getPrimitiveAttribute() const
{
	//Attribute.
	CPrimitiveAttribute attribute;
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::grid4x3Primitive ||
			type == CPrimitiveAttribute::grid20x15Primitive ||
			type == CPrimitiveAttribute::ground80x60Primitive ||
			type == CPrimitiveAttribute::ground320x240Primitive ||
			type == CPrimitiveAttribute::ground640x480Primitive);
#endif
	//Set type.
	attribute.setType(type);
	//Copy data.
	attribute.rings = rings;
	attribute.segments = segments;
	//Copy data.
	attribute.primitiveData.grid.quadWidth = quadWidth;
	attribute.primitiveData.grid.quadHeight = quadHeight;
	//Return attribute.
	return attribute;
}

/////////////////////////////////////////////////////////////////////////////////
//
// InitializeDefault
//
/////////////////////////////////////////////////////////////////////////////////

void CGridAttribute::initializeDefault()
{
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::grid4x3Primitive ||
		type == CPrimitiveAttribute::grid20x15Primitive ||
		type == CPrimitiveAttribute::ground80x60Primitive ||
		type == CPrimitiveAttribute::ground320x240Primitive ||
		type == CPrimitiveAttribute::ground640x480Primitive);
#endif
	//Set default value.
	quadWidth = 1.0f;
	quadHeight = 0.001f;
	//Setup attribute.
	setupAttribute();
}

/////////////////////////////////////////////////////////////////////////////////
//
// Initialize
//
/////////////////////////////////////////////////////////////////////////////////

void CGridAttribute::initialize(_FLOAT quadWidth,_FLOAT quadHeight)
{
#ifdef _DEBUG
	assert(quadWidth > 0.0f && quadHeight > 0.0f);
#endif

#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::grid4x3Primitive ||
		type == CPrimitiveAttribute::grid20x15Primitive ||
		type == CPrimitiveAttribute::ground80x60Primitive ||
		type == CPrimitiveAttribute::ground320x240Primitive ||
		type == CPrimitiveAttribute::ground640x480Primitive);
#endif
	//Copy data.
	this->quadWidth = quadWidth;
	this->quadHeight = quadHeight;
	//Setup attribute.
	setupAttribute();
}

///////////////////////////////////////////////////////////////////////////////
//
// SetPrimitiveAttribute
//
///////////////////////////////////////////////////////////////////////////////

void CGridAttribute::setPrimitiveAttribute(const CPrimitiveAttribute& attribute)
{
#ifdef _DEBUG
	assert(type == attribute.getType());
#endif
	//Initialize it.
	initialize(attribute.primitiveData.grid.quadWidth,attribute.primitiveData.grid.quadHeight);
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetupAttribute
//
/////////////////////////////////////////////////////////////////////////////////

void CGridAttribute::setupAttribute()
{
#ifdef _DEBUG
	assert(type == CPrimitiveAttribute::grid4x3Primitive ||
		type == CPrimitiveAttribute::grid20x15Primitive ||
		type == CPrimitiveAttribute::ground80x60Primitive ||
		type == CPrimitiveAttribute::ground320x240Primitive ||
		type == CPrimitiveAttribute::ground640x480Primitive);
#endif

#ifdef _DEBUG
	assert(getIndexType() == CIndexAttribute::integer3Index);
	assert(getVertexType() == CVertexAttribute::float3Vertex);
	assert(getNormalType() == CNormalAttribute::float3Normal);
	assert(getTextureType() == CTextureAttribute::float2Texture);
#endif

	//Get index.
	_INTEGER3* index = CIndexAttribute::getInteger3Index();
#ifdef _DEBUG
	assert(index != _NULL);
	assert(getIndexCount() >= 2);
#endif
	//Offset.
	_INTEGER offset = 0;
	//Check result.
	if(type == CPrimitiveAttribute::grid4x3Primitive ||
		type == CPrimitiveAttribute::grid20x15Primitive)
	{
		//Do while.
		for(_INTEGER i = 0;i < rings;i ++)
		{
			//Do while.
			for(_INTEGER j = 0;j < segments;j ++)
			{
				//Setup triangle.
				index[offset][0] = i * (segments + 1) + j;
				index[offset][1] = (i + 1) * (segments + 1) + j + 1;
				index[offset][2] = (i + 1) * (segments + 1) + j;
				//Add offset.
				offset ++;

				//Setup triangle.
				index[offset][0] = i * (segments + 1) + j;
				index[offset][1] = i * (segments + 1) + j + 1;
				index[offset][2] = (i + 1) * (segments + 1) + j + 1;
				//Add offset.
				offset ++;
			}
		}
	}
	else if(type == CPrimitiveAttribute::ground80x60Primitive ||
		type == CPrimitiveAttribute::ground320x240Primitive ||
		type == CPrimitiveAttribute::ground640x480Primitive)
	{
		//Do while.
		for(_INTEGER i = 0;i < rings;i ++)
		{
			//Do while.
			for(_INTEGER j = 0;j < segments;j ++)
			{
				//Setup triangle.
				index[offset][0] = i * (segments + 1) + j;
				index[offset][1] = (i + 1) * (segments + 1) + j;
				index[offset][2] = (i + 1) * (segments + 1) + j + 1;
				//Add offset.
				offset ++;

				//Setup triangle.
				index[offset][0] = i * (segments + 1) + j;
				index[offset][1] = (i + 1) * (segments + 1) + j + 1;
				index[offset][2] = i * (segments + 1) + j + 1;
				//Add offset.
				offset ++;
			}
		}
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif

#ifdef _DEBUG
	assert(offset == getIndexCount());
#endif

	//Get vertex.
	_FLOAT3* vertex = CVertexAttribute::getFloat3Vertex();
#ifdef _DEBUG
	assert(vertex != _NULL);
	assert(getVertexCount() >= 4);
#endif
	//Set total height.
	_FLOAT totalHeight = quadWidth * 500.0f;
	//Check result.
	if(type == CPrimitiveAttribute::grid4x3Primitive ||
		type == CPrimitiveAttribute::grid20x15Primitive)
	{
		//Start
		_FLOAT zStart = rings * quadWidth / 2.0f;
		_FLOAT xStart = - (segments * quadWidth) / 2.0f;
		//Reset offset.
		offset = 0;
		//Do while.
		for(_INTEGER i = 0;i < rings + 1;i ++)
		{
			//Get z offset.
			_FLOAT zOffset = zStart - i * quadWidth;
			//Do while.
			for(_INTEGER j = 0;j < segments + 1;j ++)
			{
				//Set vertex.
				vertex[offset][0] = xStart + j * quadWidth;
				vertex[offset][1] = (_FLOAT)rand() / (RAND_MAX + 1) * totalHeight * quadHeight;
				vertex[offset][2] = zOffset;
				//Add offset.
				offset ++;
			}
		}
	}
	else if(type == CPrimitiveAttribute::ground80x60Primitive ||
			type == CPrimitiveAttribute::ground320x240Primitive ||
			type == CPrimitiveAttribute::ground640x480Primitive)
	{
		//Reset offset.
		offset = 0;
		//Do while.
		for(_INTEGER i = 0;i < rings + 1;i ++)
		{
			//Get z offset.
			_FLOAT zOffset = i * quadWidth;
			//Do while.
			for(_INTEGER j = 0;j < segments + 1;j ++)
			{
				//Set vertex.
				vertex[offset][0] = j * quadWidth;
				vertex[offset][1] = (_FLOAT)rand() / (RAND_MAX + 1) * totalHeight * quadHeight;
				vertex[offset][2] = zOffset;
				//Add offset.
				offset ++;
			}
		}
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif

#ifdef _DEBUG
	assert(offset == getVertexCount());
#endif

	//Get normal.
	_FLOAT3* normal = CNormalAttribute::getFloat3Normal();
#ifdef _DEBUG
	assert(normal != _NULL);
	assert(getNormalCount() >= 4);
	assert(getNormalCount() == getVertexCount());
#endif
	//Clear all normal.
	memset(normal,0,getNormalCount() * sizeof(_FLOAT3));

	//Do while.
	for(_INTEGER i = 0;i < getIndexCount();i ++)
	{
		//Get triangle index.
		int i0 = index[i][0];
		int i1 = index[i][1];
		int i2 = index[i][2];
		//Get vector.
		C4DVector3 v0(vertex[i1][0] - vertex[i0][0],vertex[i1][1] - vertex[i0][1],vertex[i1][2] - vertex[i0][2]);
		C4DVector3 v1(vertex[i2][0] - vertex[i0][0],vertex[i2][1] - vertex[i0][1],vertex[i2][2] - vertex[i0][2]);
		//Get normal.
		C4DVector3 n = v0.cross(v1).normalize();

		//Add all normal.
		normal[i0][0] += n[0]; normal[i0][1] += n[1]; normal[i0][2] += n[2];
		normal[i1][0] += n[0]; normal[i1][1] += n[1]; normal[i1][2] += n[2];
		normal[i2][0] += n[0]; normal[i2][1] += n[1]; normal[i2][2] += n[2];
	}

	//Offset.
	offset = 0;
	//Do while.
	for(_INTEGER i = 0;i < rings + 1;i ++)
	{
		//Do while.
		for(_INTEGER j = 0;j < segments + 1;j ++)
		{
			//Normal.
			C4DVector3 n(normal[offset][0],normal[offset][1],normal[offset][2]);
			//Normalize.
			n.normalize();
			//Set normal.
			normal[offset][0] = n.x();
			normal[offset][1] = n.y();
			normal[offset][2] = n.z();
			//Add offset.
			offset ++;
		}
	}

	//Get coordinates.
	_FLOAT2* coordinates = CTextureAttribute::getFloat2Texture();
#ifdef _DEBUG
	assert(coordinates != _NULL);
	assert(getTextureCount() >= 4);
	assert(getTextureCount() == getVertexCount());
#endif
	//Get delta v.
	_FLOAT vDelta = 1.0f / rings;
	//Get delta u.
	_FLOAT uDelta = 1.0f / segments;

	//Reset offset.
	offset = 0;
	//Do while.
	for(_INTEGER i = 0;i < rings + 1;i ++)
	{
		//Get v offset.
		_FLOAT vOffset = i * vDelta;
		//Do while.
		for(_INTEGER j = 0;j < segments + 1;j ++)
		{
			//Set coordinates.
			coordinates[offset][0] = j * uDelta;
			coordinates[offset][1] = vOffset;
			//Add offset.
			offset ++;
		}
	}
}
