///////////////////////////////////////////////////////////////////////////////
//
// D3DXVertexAttribute.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXVertexAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXVertex.h"

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Max Vertex Count
const _INTEGER CD3DXVertexAttribute::maxVertexCount						= 100;

//Defines the vertex data layout.
//Each vertex can contain one or more data types, and each data type is described by a vertex element.
static const D3DVERTEXELEMENT9 d3dxVertexElement9[2] =
{
    {
		//Stream
		//Stream number.
		0,

		//Offset
		//Offset from the beginning of the vertex data to the data associated with the particular data type.
		0,

		//Type
		//The data type, specified as a D3DDECLTYPE
		//One of several predefined types that define the data size. Some methods have an implied type.
		D3DDECLTYPE_FLOAT3,
		//Method
		//The method specifies the tessellator processing,
		//which determines how the tessellator interprets (or operates on) the vertex data.
		//For more information, see D3DDECLMETHOD.

		//Default value.
		//The tessellator copies the vertex data (spline data for patches) as is, with no additional calculations.
		//When the tessellator is used, this element is interpolated.
		//Otherwise vertex data is copied into the input register.
		//The input and output type can be any value, but are always the same type.
		D3DDECLMETHOD_DEFAULT,

		//Usage
		//Defines what the data will be used for;
		//that is, the interoperability between vertex data layouts and vertex shaders.
		//Each usage acts to bind a vertex declaration to a vertex shader.
		//In some cases, they have a special interpretation.
		//For example, an element that specifies D3DDECLUSAGE_NORMAL or
		//D3DDECLUSAGE_POSITION is used by the N-patch tessellator to set up tessellation.
		//See D3DDECLUSAGE for a list of the available semantics.
		//D3DDECLUSAGE_TEXCOORD can be used for user-defined fields (which don't have an existing usage defined).
		D3DDECLUSAGE_POSITION,

		//UsageIndex
		//Modifies the usage data to allow the user to specify multiple usage types.
		0
	},
	//End of delcaration.
    D3DDECL_END()
};

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXVertexAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXVertexAttribute::CD3DXVertexAttribute(void)
{
	//Set default value.
	vertexBuffer = (LPDIRECT3DVERTEXBUFFER9)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXVertexAttribute
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXVertexAttribute::~CD3DXVertexAttribute(void)
{
	//Safe release.
	SAFE_RELEASE(vertexBuffer);
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetVertexBuffer
//
/////////////////////////////////////////////////////////////////////////////////

LPDIRECT3DVERTEXBUFFER9 CD3DXVertexAttribute::getVertexBuffer() const
{
	//Return result.
	return vertexBuffer;
}

/////////////////////////////////////////////////////////////////////////////////
//
// InitializeIndex
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXVertexAttribute::initializeVertex(LPDIRECT3DVERTEXBUFFER9 vertexBuffer)
{
#ifdef _DEBUG
	assert(vertexBuffer != _NULL);
#endif
	//Return.
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateVertexBuffer
//
/////////////////////////////////////////////////////////////////////////////////

LPDIRECT3DVERTEXBUFFER9 CD3DXVertexAttribute::createVertexBuffer(IDirect3DDevice9* pd3dDevice)
{
	//Vertex buffer.
	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;

#ifdef _DEBUG
	assert(pd3dDevice != NULL && maxVertexCount >= 3);
#endif
	//Return result
    return FAILED(pd3dDevice->CreateVertexBuffer(maxVertexCount * sizeof(_4DVERTEX0),
												 //Usage
												 D3DUSAGE_DYNAMIC,
												 //FVF
												 D3DFVF_4DVERTEX3,
												 //Pool
												 D3DPOOL_DEFAULT,
												 //Vertex Buffer
												 &pVertexBuffer,NULL)) ? NULL : pVertexBuffer;
}

/////////////////////////////////////////////////////////////////////////////////
//
// CopyVertex
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXVertexAttribute::copyVertex(const CRenderableAttribute& attribute)
{
	//Result.
	HRESULT hr;

	//Get vertex count.
	_INTEGER vertexCount = attribute.getVertexCount();
#ifdef _DEBUG
	assert(vertexCount >= 3);
	assert(attribute.getVertexType() == CVertexAttribute::float3Vertex);
#endif
	//Get vertex array.
	_FLOAT3* vertexArray = attribute.getFloat3Vertex();
#ifdef _DEBUG
	assert(vertexArray != _NULL);
#endif

	//Get normal count.
	_INTEGER normalCount = attribute.getNormalCount();
#ifdef _DEBUG
	assert(normalCount == vertexCount);
	assert(attribute.getNormalType() == CNormalAttribute::float3Normal);
#endif
	//Get normal array.
	_FLOAT3* normalArray = attribute.getFloat3Normal();
#ifdef _DEBUG
	assert(normalArray != _NULL);
#endif

	//Get texture count.
	_INTEGER textureCount = attribute.getTextureCount();
#ifdef _DEBUG
	assert(textureCount == vertexCount);
	assert(attribute.getTextureType() == CTextureAttribute::float2Texture);
#endif
	//Get texture array.
	_FLOAT2* textureArray = attribute.getFloat2Texture();
#ifdef _DEBUG
	assert(textureArray != _NULL);
#endif

	//Get vertex buffer.
	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer = getVertexBuffer();
#ifdef _DEBUG
	assert(pVertexBuffer != NULL);
#endif

	//Vertex
	_4DVERTEX3* pVertexArray;
	//Lock buffer.
	V_RETURN(pVertexBuffer->Lock(0,0,(void **)&pVertexArray,D3DLOCK_DISCARD));
	//Do while.
	for(_INTEGER i = 0;i < vertexCount;i ++)
	{
		//Set vertex.
		pVertexArray[i]._x = vertexArray[i][0];
		pVertexArray[i]._y = vertexArray[i][1];
		pVertexArray[i]._z = vertexArray[i][2];
		//Set normal.
		pVertexArray[i]._nx = normalArray[i][0];
		pVertexArray[i]._ny = normalArray[i][1];
		pVertexArray[i]._nz = normalArray[i][2];
		//Set texture coordination.
		pVertexArray[i]._u = textureArray[i][0];
		pVertexArray[i]._v = textureArray[i][1];
	}
	//Unlock buffer.
	V_RETURN(pVertexBuffer->Unlock());
	//Return OK.
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXVertexAttribute::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Result.
	HRESULT hr;

	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	//Release D3D9 resources created in the OnD3D9ResetDevice callback.
	case d3dxOnD3D9LostDevice:
		//Release buffer.
		SAFE_RELEASE(vertexBuffer);
		break;
	//Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) or that are tied to the back buffer size.
	case d3dxOnD3D9ResetDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxResetDevice9.pd3dDevice != NULL);
#endif
		//Create vertex buffer.
		vertexBuffer = createVertexBuffer(d3dxEvent.d3dxResetDevice9.pd3dDevice);
		//Check result.
		if(vertexBuffer == _NULL) return E_FAIL;
		//Initialize vertex buffer.
		V_RETURN(initializeVertex(vertexBuffer));
		break;
	}
	//Return result.
	return FALSE;
}
