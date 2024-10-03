///////////////////////////////////////////////////////////////////////////////
//
// GroundMeshObject.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "GroundMeshObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "KinectDevice.h"

#include "D3DXVertex.h"
#include "D3DXApplication.h"

///////////////////////////////////////////////////////////////////////////////
//
// CGroundMeshObject
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CGroundMeshObject::CGroundMeshObject()
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CGroundMeshObject
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CGroundMeshObject::~CGroundMeshObject(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// SelectSource
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CGroundMeshObject::selectSource(CResourceApplication* resourceApplication,const CNormalString& name)
{
#ifdef _DEBUG
	assert(resourceApplication != _NULL);
#endif
	//Get resource manager.
	CResourceManager* resourceManager = resourceApplication->getResourceManager();
#ifdef _DEBUG
	assert(resourceManager != _NULL && name.length() > 0);
#endif
	//Check source.
	if(source != _NULL)
	{
		//Release source.
		source->releaseReference();
		//Clear source.
		source = (CD3DXResource *)_NULL;
	}
	//Get resource.
	CD3DXResource* resource = resourceManager->getResource(name);
#ifdef _DEBUG
	assert(resource != _NULL);
#endif
	//Set name.
	sourceName = name;
	//Add reference.
	resource->addReference();
	//Set source.
	source = (CD3DXDevice *)resource;

	//Get width and height.
	_INTEGER width = 0, height = 0;
	//Check result.
	if(IS_KINECTDEVICE_BASE(resource))
	{
		//Get width.
		width = ((CKinectDevice *)resource)->getWidth();
		//Get height.
		height = ((CKinectDevice *)resource)->getHeight();
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif

	//Attribute.
	CPrimitiveAttribute attribute;
	//Check result.
	if(width == 80 && height == 60)
	{
		//Set type.
		attribute.setType(CPrimitiveAttribute::ground80x60Primitive);
	}
	else if(width == 320 && height == 240)
	{
		//Set type.
		attribute.setType(CPrimitiveAttribute::ground320x240Primitive);
	}
	else if(width == 640 && height == 480)
	{
		//Set type.
		attribute.setType(CPrimitiveAttribute::ground640x480Primitive);
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
	//Set width
	attribute.primitiveData.grid.quadWidth = 0.01f;
	//Set height.
	attribute.primitiveData.grid.quadHeight = 0.0001f;
	//Set type.
	setPrimitiveAttribute(attribute);

	//Get renderable manager.
	CRenderableManager* renderableManager = resourceApplication->getRenderableManager();
#ifdef _DEBUG
	assert(renderableManager != _NULL);
#endif
	//Create renderable.
	CD3DXPrimitive* primitive = renderableManager->createPrimitive(attribute);
#ifdef _DEBUG
	assert(primitive != NULL);
#endif
	//Create renderable.
	setRenderable(primitive);
	//Create texture.
	return _TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CGroundMeshObject::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Result.
	HRESULT hr;

	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	case d3dxOnD3D9CreateDevice:
#ifdef _DEBUG
		assert(d3dxEvent.pUserContext != _NULL);
#endif
		//Check source name.
		if(sourceName.length() > 0)
		{
			//Select source.
			if(!selectSource((CD3DXApplication *)d3dxEvent.pUserContext,sourceName)) return E_FAIL;
		}
		break;
	//On frame move.
	case d3dxOnFrameMove:
#ifdef _DEBUG
		assert(d3dxEvent.pUserContext != _NULL);
#endif
		//Check source.
		if(source != _NULL)
		{
			//Get depth buffer.
			_SHORT* depthBuffer = (_SHORT *)_NULL;
			//Check instance.
			if(IS_KINECTDEVICE_BASE(source))
			{
				//Get depth buffer.
				depthBuffer = ((CKinectDevice *)source)->getDepthBuffer();
			}
#ifdef _DEBUG
			else assert(_FALSE);
#endif
			//Get primitive.
			CD3DXPrimitive* primitive = (CD3DXPrimitive *)CPrimitiveObject::getRenderable();
#ifdef _DEBUG
			assert(primitive != _NULL);
#endif
			//Get width and height.
			_INTEGER width = 0, height = 0;
			//Get primitive type.
			CPrimitiveAttribute primitiveAttribute = primitive->getPrimitiveAttribute();
			//Check type.4
			if(primitiveAttribute.getType() == CPrimitiveAttribute::ground80x60Primitive)
			{
				//Set width and height.
				width = 80; height = 60;
			}
			else if(primitiveAttribute.getType() == CPrimitiveAttribute::ground320x240Primitive)
			{
				//Set width and height.
				width = 320; height = 240;
			}
			else if(primitiveAttribute.getType() == CPrimitiveAttribute::ground640x480Primitive)
			{
				//Set width and height.
				width = 640; height = 480;
			}
#ifdef _DEBUG
			else assert(_FALSE);
#endif

#ifdef _DEBUG
			assert(width * height <= primitive->getVertexCount());
#endif
			//Get vertex buffer.
			LPDIRECT3DVERTEXBUFFER9 pVertexBuffer = primitive->getVertexBuffer();
#ifdef _DEBUG
			assert(pVertexBuffer != NULL);
#endif
			//Vertex
			_4DVERTEX3* pVertexArray;
			//Lock buffer.
			V_RETURN(pVertexBuffer->Lock(0,0,(void **)&pVertexArray,D3DLOCK_DISCARD));
			//Calculate offset.
			_INTEGER offset = 0;
			//Do while.
			for(_INTEGER i = 0;i < height;i ++)
			{
				//Do while.
				for(_INTEGER j = 0;j < width;j ++)
				{
					//Get depth value.
					_INTEGER depthValue = depthBuffer[i * width + j] & 0xFFFF;
					//Check result.
					if(depthValue > 1500) depthValue = 0;
					//Set height.
					pVertexArray[i * (width + 1) + j]._y = depthValue * 0.0001f;
					//Clear normal.
					//pVertexArray[offset]._nx = 0; pVertexArray[offset]._ny = 0; pVertexArray[offset]._nz = 0;
				}
			}
			/*
			//Get index buffer.
			LPDIRECT3DINDEXBUFFER9 pIndexBuffer = primitive->getIndexBuffer();
#ifdef _DEBUG
			assert(pIndexBuffer != NULL);
#endif
			//Index
			DWORD* pIndexArray = NULL;
			//Lock buffer.
			V_RETURN(pIndexBuffer->Lock(0,0,(void **)&pIndexArray,D3DLOCK_DISCARD));

			//Do while.
			for(_INTEGER i = 0;i < primitive->getIndexCount();i ++)
			{
				//Get triangle index.
				int i0 = pIndexArray[3 * i + 0];
				int i1 = pIndexArray[3 * i + 1];
				int i2 = pIndexArray[3 * i + 2];
				//Get vector.
				C4DVector3 v0(pVertexArray[i1]._x - pVertexArray[i0]._x,pVertexArray[i1]._y - pVertexArray[i0]._y,pVertexArray[i1]._z - pVertexArray[i0]._z);
				C4DVector3 v1(pVertexArray[i2]._x - pVertexArray[i0]._x,pVertexArray[i2]._y - pVertexArray[i0]._y,pVertexArray[i2]._z - pVertexArray[i0]._z);
				//Get normal.
				C4DVector3 n = v0.cross(v1).normalize();

				//Add all normal.
				pVertexArray[i0]._nx += n[0]; pVertexArray[i0]._ny += n[1]; pVertexArray[i0]._nz += n[2];
				pVertexArray[i1]._nx += n[0]; pVertexArray[i1]._ny += n[1]; pVertexArray[i1]._nz += n[2];
				pVertexArray[i2]._nx += n[0]; pVertexArray[i2]._ny += n[1]; pVertexArray[i2]._nz += n[2];
			}

			//Offset.
			offset = 0;
			//Do while.
			for(_INTEGER i = 0;i < height;i ++)
			{
				//Do while.
				for(_INTEGER j = 0;j < width;j ++)
				{
					//Normal.
					C4DVector3 n(pVertexArray[offset]._nx,pVertexArray[offset]._ny,pVertexArray[offset]._nz);
					//Normalize.
					n.normalize();
					//Set normal.
					pVertexArray[offset]._nx = n.x();
					pVertexArray[offset]._ny = n.y();
					pVertexArray[offset]._nz = n.z();
					//Add offset.
					offset ++;
				}
			}

			//Unlock buffer.
			V_RETURN(pIndexBuffer->Unlock());
			*/
			//Unlock buffer.
			V_RETURN(pVertexBuffer->Unlock());
		}
		break;
	}
	//Return result.
	return CDynamicPrimitiveObject::handleMessage(d3dxEvent);
}
