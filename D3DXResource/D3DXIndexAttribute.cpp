///////////////////////////////////////////////////////////////////////////////
//
// D3DXIndexAttribute.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXIndexAttribute.h"

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

//Max Index Count
const _INTEGER CD3DXIndexAttribute::maxIndexCount			= 25;

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXIndexAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXIndexAttribute::CD3DXIndexAttribute(void)
{
	//Set default value.
	indexBuffer = (LPDIRECT3DINDEXBUFFER9)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXIndexAttribute
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXIndexAttribute::~CD3DXIndexAttribute(void)
{
	//Safe release.
	SAFE_RELEASE(indexBuffer);
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetIndexBuffer
//
/////////////////////////////////////////////////////////////////////////////////

LPDIRECT3DINDEXBUFFER9 CD3DXIndexAttribute::getIndexBuffer() const
{
	//Return result.
	return indexBuffer;
}

/////////////////////////////////////////////////////////////////////////////////
//
// InitializeIndex
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXIndexAttribute::initializeIndex(LPDIRECT3DINDEXBUFFER9 indexBuffer)
{
#ifdef _DEBUG
	assert(indexBuffer != _NULL);
#endif
	//Return.
	return S_OK;
}
/////////////////////////////////////////////////////////////////////////////////
//
// CreateIndexBuffer
//
/////////////////////////////////////////////////////////////////////////////////

LPDIRECT3DINDEXBUFFER9 CD3DXIndexAttribute::createIndexBuffer(IDirect3DDevice9* pd3dDevice)
{
	//Index buffer.
	LPDIRECT3DINDEXBUFFER9 pIndexBuffer;

#ifdef _DEBUG
	assert(pd3dDevice != NULL && maxIndexCount >= 3);
#endif
	//Return result.
    return FAILED(pd3dDevice->CreateIndexBuffer(maxIndexCount * sizeof(DWORD),
												//Usage
												D3DUSAGE_DYNAMIC,
												//Format
												D3DFMT_INDEX32,
												//Pool
												D3DPOOL_DEFAULT,
												//Index Buffer
												&pIndexBuffer,NULL)) ? NULL : pIndexBuffer;
}

/////////////////////////////////////////////////////////////////////////////////
//
// CopyIndex
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXIndexAttribute::copyIndex(const CRenderableAttribute& attribute)
{
	//Result.
	HRESULT hr;

	//Get index count.
	_INTEGER indexCount = attribute.getIndexCount();
#ifdef _DEBUG
	assert(indexCount >= 1);
#endif

	//Get index buffer.
	LPDIRECT3DINDEXBUFFER9 pIndexBuffer = getIndexBuffer();
#ifdef _DEBUG
	assert(pIndexBuffer != NULL);
#endif
	//Index
	DWORD* pIndexArray = NULL;
	//Lock buffer.
	V_RETURN(pIndexBuffer->Lock(0,0,(void **)&pIndexArray,D3DLOCK_DISCARD));
	//Check type.
	if(attribute.getIndexType() == CIndexAttribute::short3Index)
	{
		//Get index array.
		_SHORT3* indexArray = attribute.getShort3Index();
#ifdef _DEBUG
		assert(indexArray != _NULL);
#endif
		//Copy index array.
		for(_INTEGER i = 0;i < indexCount;i ++)
		{
			//Set index array.
			pIndexArray[3 * i + 0] = indexArray[i][0] & 0xFFFF;
			pIndexArray[3 * i + 1] = indexArray[i][1] & 0xFFFF;
			pIndexArray[3 * i + 2] = indexArray[i][2] & 0xFFFF;
		}
	}
	else if(attribute.getIndexType() == CIndexAttribute::integer3Index)
	{
		//Get index array.
		_INTEGER3* indexArray = attribute.getInteger3Index();
#ifdef _DEBUG
		assert(indexArray != _NULL);
#endif
		//Copy.
		memcpy(pIndexArray,indexArray,indexCount * sizeof(_INTEGER3));
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
	//Unlock buffer.
	V_RETURN(pIndexBuffer->Unlock());
	//Return OK.
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXIndexAttribute::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Result.
	HRESULT hr;

	//Check event id.
	//The event must be dispatched the parent class.
	switch(d3dxEvent.d3dxEventID)
	{
	//Release D3D9 resources created in the OnD3D9ResetDevice callback.
	case d3dxOnD3D9LostDevice:
		//Release buffer.
		SAFE_RELEASE(indexBuffer);
		break;
	//Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) or that are tied to the back buffer size.
	case d3dxOnD3D9ResetDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxResetDevice9.pd3dDevice != NULL);
#endif
		//Create index buffer.
		indexBuffer = createIndexBuffer(d3dxEvent.d3dxResetDevice9.pd3dDevice);
		//Check result.
		if(indexBuffer == NULL) return E_FAIL;
		//Initialize index buffer.
		V_RETURN(initializeIndex(indexBuffer));
		break;
	}
	//Return result.
	return FALSE;
}
