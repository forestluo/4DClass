///////////////////////////////////////////////////////////////////////////////
//
// VertexAttribute.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "VertexAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <memory.h>

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

const _INTEGER CVertexAttribute::nullVertex					= 0;
const _INTEGER CVertexAttribute::float3Vertex				= 1;

///////////////////////////////////////////////////////////////////////////////
//
// CVertexAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CVertexAttribute::CVertexAttribute(void)
{
	//Set default value.
	type = nullVertex;

	//Set count.
	count = 0;
	//Clear data.
	memset(&vertexData,0,sizeof(tagVertexData));
}

///////////////////////////////////////////////////////////////////////////////
//
// CVertexAttribute
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CVertexAttribute::~CVertexAttribute(void)
{
	//Clear all.
	clearAllVertex();
}

///////////////////////////////////////////////////////////////////////////////
//
// CopyVertex
//
/////////////////////////////////////////////////////////////////////////////////

void CVertexAttribute::copyVertex(const CVertexAttribute& attribute)
{
	//Set referenced.
	setReferenced(_TRUE);
	//Set default value.
	type = attribute.type;

	//Set count.
	count = attribute.count;
	//Copy data.
	memcpy(&vertexData,&attribute.vertexData,sizeof(tagVertexData));
}

///////////////////////////////////////////////////////////////////////////////
//
// CloneVertex
//
/////////////////////////////////////////////////////////////////////////////////

void CVertexAttribute::cloneVertex(const CVertexAttribute& attribute)
{
	//Set referenced.
	setReferenced(_FALSE);
	//Set default value.
	type = attribute.type;

	//Set count.
	count = attribute.count;
	//Copy data.
	memcpy(&vertexData,&attribute.vertexData,sizeof(tagVertexData));
	//Check count.
	if(count > 0)
	{
		//Check result.
		if(type == nullVertex)
		{
			//Do nothing.
		}
		else if(type == float3Vertex)
		{
			//Create value.
			vertexData.vertexFloat3.vertices = (_FLOAT3 *)malloc(count * sizeof(_FLOAT3));
#ifdef _DEBUG
			assert(vertexData.vertexFloat3.vertices != _NULL);
#endif
			//Copy value.
			memcpy(vertexData.vertexFloat3.vertices,attribute.vertexData.vertexFloat3.vertices,count * sizeof(_FLOAT3));
		}
#ifdef _DEBUG
		else assert(_FALSE);
#endif
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// GetVertexType
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CVertexAttribute::getVertexType() const
{
	//Return result.
	return type;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetVertexType
//
///////////////////////////////////////////////////////////////////////////////

void CVertexAttribute::setVertexType(_INTEGER type)
{
#ifdef _DEBUG
	assert(type >= 0 && type <= 1);
#endif
	//Set value.
	this->type = type;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetVertexSize
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CVertexAttribute::getVertexSize() const
{
	//Check type.
	switch(type)
	{
	case nullVertex:
		break;
	case float3Vertex:
		return sizeof(_FLOAT3);
	default:
#ifdef _DEBUG
		assert(_FALSE);
#endif
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//
// ClearAllVertex
//
///////////////////////////////////////////////////////////////////////////////

void CVertexAttribute::clearAllVertex()
{
	//Clear count.
	count = 0;
	//Check type.
	switch(type)
	{
	case nullVertex:
		break;
	case float3Vertex:
		//Check result.
		if(vertexData.vertexFloat3.vertices != _NULL)
		{
			//Check result.
			if(!isReferenced())
			{
				//Delete vertices.
				free(vertexData.vertexFloat3.vertices);
			}
			//Clear vertices.
			vertexData.vertexFloat3.vertices = (_FLOAT3 *)_NULL;
		}
		break;
	default:
#ifdef _DEBUG
		assert(_FALSE);
#endif
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// GetVertexCount
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CVertexAttribute::getVertexCount() const
{
	//Return result.
	return count;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetFloat3Vertex
//
///////////////////////////////////////////////////////////////////////////////
	
_FLOAT3* CVertexAttribute::getFloat3Vertex() const
{
	//Return values.
	return vertexData.vertexFloat3.vertices;
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateFloat3Vertex
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT3* CVertexAttribute::createFloat3Vertex(_INTEGER count)
{
	//Vertices.
	_FLOAT3* vertices;

#ifdef _DEBUG
	assert(count > 0);
	assert(this->vertexData.vertexFloat3.vertices == _NULL);
#endif
	//Set count.
	this->count = count;
	//Set type.
	this->type = float3Vertex;

	//Create vertices.
	vertices = (_FLOAT3 *)malloc(count * sizeof(_FLOAT3));
	//Check result.
#ifdef _DEBUG
	assert(vertices != _NULL);
#endif
	//Clear memory.
	memset(vertices,0,count * sizeof(_FLOAT3));

	//Set referenced.
	setReferenced(_FALSE);
	//Set vertices.
	this->vertexData.vertexFloat3.vertices = vertices;
	//Return vertices.
	return vertices;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetFloat3Vertex
//
///////////////////////////////////////////////////////////////////////////////

void CVertexAttribute::setFloat3Vertex(_INTEGER count,_FLOAT3* vertices)
{
#ifdef _DEBUG
	assert(count > 0);
	assert(vertices != _NULL);
	assert(this->vertexData.vertexFloat3.vertices == _NULL);
#endif
	//Set count.
	this->count = count;
	//Set type.
	this->type = float3Vertex;
	//Set referenced.
	setReferenced(_TRUE);
	//Set vertices.
	this->vertexData.vertexFloat3.vertices = vertices;
}