///////////////////////////////////////////////////////////////////////////////
//
// IndexAttribute.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "IndexAttribute.h"

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

const _INTEGER CIndexAttribute::nullIndex					= 0;
const _INTEGER CIndexAttribute::short3Index					= 1;
const _INTEGER CIndexAttribute::integer3Index				= 2;

///////////////////////////////////////////////////////////////////////////////
//
// CIndexAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CIndexAttribute::CIndexAttribute(void)
{
	//Set default value.
	type = nullIndex;

	//Set count.
	count = 0;
	//Clear data.
	memset(&indexData,0,sizeof(tagIndexData));
}

///////////////////////////////////////////////////////////////////////////////
//
// CIndexAttribute
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CIndexAttribute::~CIndexAttribute(void)
{
	//Clear all.
	clearAllIndex();
}

///////////////////////////////////////////////////////////////////////////////
//
// CopyIndex
//
/////////////////////////////////////////////////////////////////////////////////

void CIndexAttribute::copyIndex(const CIndexAttribute& attribute)
{
	//Set referenced.
	setReferenced(_TRUE);
	//Set default value.
	type = attribute.type;

	//Set count.
	count = attribute.count;
	//Copy data.
	memcpy(&indexData,&attribute.indexData,sizeof(tagIndexData));
}

///////////////////////////////////////////////////////////////////////////////
//
// CloneIndex
//
/////////////////////////////////////////////////////////////////////////////////

void CIndexAttribute::cloneIndex(const CIndexAttribute& attribute)
{
	//Set referenced.
	setReferenced(_FALSE);
	//Set default value.
	type = attribute.type;

	//Set count.
	count = attribute.count;
	//Copy data.
	memcpy(&indexData,&attribute.indexData,sizeof(tagIndexData));
	//Check count.
	if(count > 0)
	{
		//Check result.
		if(type == nullIndex)
		{
			//Do nothing.
		}
		else if(type == short3Index)
		{
			//Create value.
			indexData.indexShort3.indices = (_SHORT3 *)malloc(count * sizeof(_SHORT3));
#ifdef _DEBUG
			assert(indexData.indexShort3.indices != _NULL);
#endif
			//Copy value.
			memcpy(indexData.indexShort3.indices,attribute.indexData.indexShort3.indices,count * sizeof(_SHORT3));
		}
#ifdef _DEBUG
		else assert(_FALSE);
#endif
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// GetIndexType
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CIndexAttribute::getIndexType() const
{
	//Return result.
	return type;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetIndexType
//
///////////////////////////////////////////////////////////////////////////////

void CIndexAttribute::setIndexType(_INTEGER type)
{
#ifdef _DEBUG
	assert(type >= 0 && type <= 2);
#endif
	//Set value.
	this->type = type;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetIndexSize
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CIndexAttribute::getIndexSize() const
{
	//Check type.
	switch(type)
	{
	case nullIndex:
		break;
	case short3Index:
		return sizeof(_SHORT3);
	case integer3Index:
		return sizeof(_INTEGER3);
	default:
#ifdef _DEBUG
		assert(_FALSE);
#endif
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//
// ClearAllIndex
//
///////////////////////////////////////////////////////////////////////////////

void CIndexAttribute::clearAllIndex()
{
	//Clear count.
	count = 0;
	//Check type.
	switch(type)
	{
	case nullIndex:
		break;
	case short3Index:
		//Check result.
		if(indexData.indexShort3.indices != _NULL)
		{
			//Check reference.
			if(!isReferenced())
			{
				//Delete indices.
				free(indexData.indexShort3.indices);
			}
			//Clear indices.
			indexData.indexShort3.indices = (_SHORT3 *)_NULL;
		}
		break;
	case integer3Index:
		//Check result.
		if(indexData.indexInteger3.indices != _NULL)
		{
			//Check reference.
			if(!isReferenced())
			{
				//Delete indices.
				free(indexData.indexInteger3.indices);
			}
			//Clear indices.
			indexData.indexInteger3.indices = (_INTEGER3 *)_NULL;
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
// GetIndexCount
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CIndexAttribute::getIndexCount() const
{
	//Return result.
	return count;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetShort3Index
//
///////////////////////////////////////////////////////////////////////////////
	
_SHORT3* CIndexAttribute::getShort3Index() const
{
	//Return values.
	return indexData.indexShort3.indices;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetInteger3Index
//
///////////////////////////////////////////////////////////////////////////////
	
_INTEGER3* CIndexAttribute::getInteger3Index() const
{
	//Return values.
	return indexData.indexInteger3.indices;
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateShort3Index
//
///////////////////////////////////////////////////////////////////////////////

_SHORT3* CIndexAttribute::createShort3Index(_INTEGER count)
{
	//Indices.
	_SHORT3* indices;

#ifdef _DEBUG
	assert(count > 0);
	assert(this->indexData.indexShort3.indices == _NULL);
#endif
	//Set count.
	this->count = count;
	//Set type.
	this->type = short3Index;

	//Create indices.
	indices = (_SHORT3 *)malloc(count * sizeof(_SHORT3));
#ifdef _DEBUG
	assert(indices != _NULL);
#endif
	//Clear memory.
	memset(indices,0,count * sizeof(_SHORT3));

	//Set referenced.
	setReferenced(_FALSE);
	//Set indices.
	this->indexData.indexShort3.indices = indices;
	//Return indices.
	return indices;
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateInteger3Index
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER3* CIndexAttribute::createInteger3Index(_INTEGER count)
{
	//Indices.
	_INTEGER3* indices;

#ifdef _DEBUG
	assert(count > 0);
	assert(this->indexData.indexInteger3.indices == _NULL);
#endif
	//Set count.
	this->count = count;
	//Set type.
	this->type = integer3Index;
	//Create indices.
	indices = (_INTEGER3 *)malloc(count * sizeof(_INTEGER3));
	//Check result.
#ifdef _DEBUG
	assert(indices != _NULL);
#endif
	//Set referenced.
	setReferenced(_FALSE);
	//Set indices.
	this->indexData.indexInteger3.indices = indices;
	//Return indices.
	return indices;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetShort3Indices
//
///////////////////////////////////////////////////////////////////////////////

void CIndexAttribute::setShort3Index(_INTEGER count,_SHORT3* indices)
{
#ifdef _DEBUG
	assert(count > 0);
	assert(indices != _NULL);
	assert(this->indexData.indexShort3.indices == _NULL);
#endif
	//Set count.
	this->count = count;
	//Set type.
	this->type = short3Index;
	//Set referenced.
	setReferenced(_TRUE);
	//Set indices.
	this->indexData.indexShort3.indices = indices;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetInteger3Index
//
///////////////////////////////////////////////////////////////////////////////

void CIndexAttribute::setInteger3Index(_INTEGER count,_INTEGER3* indices)
{
#ifdef _DEBUG
	assert(count > 0);
	assert(indices != _NULL);
	assert(this->indexData.indexInteger3.indices == _NULL);
#endif
	//Set count.
	this->count = count;
	//Set type.
	this->type = integer3Index;
	//Set referenced.
	setReferenced(_TRUE);
	//Set indices.
	this->indexData.indexInteger3.indices = indices;
}