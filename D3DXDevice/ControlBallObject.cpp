///////////////////////////////////////////////////////////////////////////////
//
// ControlBallObject.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "ControlBallObject.h"

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
// CControlBallObject
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CControlBallObject::CControlBallObject()
{
	setMass(1000.0f);
}

///////////////////////////////////////////////////////////////////////////////
//
// CControlBallObject
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CControlBallObject::~CControlBallObject(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// SelectSource
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CControlBallObject::selectSource(CResourceApplication* resourceApplication,const CNormalString& name)
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

	//Attribute.
	CPrimitiveAttribute attribute;
	//Set type.
	attribute.setType(CPrimitiveAttribute::sphere0Primitive);
	//Set width
	attribute.primitiveData.sphere.radius = 0.2f;
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

HRESULT CControlBallObject::handleMessage(const D3DXEvent& d3dxEvent)
{
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
			//Width.
			_INTEGER width = 0;
			//Height.
			_INTEGER height = 0;
			//Get depth buffer.
			_SHORT* depthBuffer = (_SHORT *)_NULL;
			//Check instance.
			if(IS_KINECTDEVICE_BASE(source))
			{
				//Get width.
				width = ((CKinectDevice *)source)->getWidth();
				//Get height.
				height = ((CKinectDevice *)source)->getHeight();
				//Get depth buffer.
				depthBuffer = ((CKinectDevice *)source)->getDepthBuffer();
			}
#ifdef _DEBUG
			else assert(_FALSE);
#endif
			//Count.
			_INTEGER count = 0;
			//Position.
			C4DVector3 position;
			//Do while.
			for(_INTEGER i = 0;i < height;i ++)
			{
				for(_INTEGER j = 0;j < width;j ++)
				{
					//Get depth value.
					_INTEGER depthValue = depthBuffer[i * width + j] & 0xFFFF;
					//Check result.
					if(depthValue >= 1000 && depthValue <= 1500)
					{
						//Add count.
						count ++;
						//Add value.
						position.x() += j; position.y() += depthValue; position.z() += i;
					}
				}
			}
			//Calculate average.
			if(count > 0) position /= (_FLOAT)count;
			//Adjust position.
			position.x() -= width / 2;
			position.z() = height / 2 - position.z();
			//Scale the height.
			position.x() *= 0.01f; position.z() *= 0.01f; position.y() *= 0.0002f;

			//Get application.
			CD3DXApplication* application = (CD3DXApplication*)d3dxEvent.pUserContext;
			//Check result.
			if(application->CPhysicsApplication::isRunning())
			{
				//Set position.
				application->CPhysicsApplication::setPosition(this,position);
			}
			//Set transform.
			setPosition(position);
		}
		break;
	}
	//Return result.
	return CDynamicPrimitiveObject::handleMessage(d3dxEvent);
}
