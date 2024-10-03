///////////////////////////////////////////////////////////////////////////////
//
// KinematicItemObject.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "KinematicItemObject.h"

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
// CKinematicItemObject
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CKinematicItemObject::CKinematicItemObject(_INTEGER x,_INTEGER y)
{
	//Set position.
	this->x = x;
	this->y = y;
	//Set mass.
	setMass(1.0f);
}

///////////////////////////////////////////////////////////////////////////////
//
// CKinematicItemObject
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CKinematicItemObject::~CKinematicItemObject(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// SelectSource
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CKinematicItemObject::selectSource(CResourceApplication* resourceApplication,const CNormalString& name)
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
	attribute.primitiveData.sphere.radius = 0.0395f;
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

HRESULT CKinematicItemObject::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	//Release D3D9 resources created in the OnD3D9CreateDevice callback.
	case d3dxOnD3D9DestroyDevice:
#ifdef _DEBUG
		assert(d3dxEvent.pUserContext != _NULL);
#endif
		//Clear controller.
		((CD3DXApplication *)d3dxEvent.pUserContext)->clearController(this);
		break;
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
			for(_INTEGER i = 0;i < 8;i ++)
			{
				for(_INTEGER j = 0;j < 8;j ++)
				{
					//Calculate offset.
					_INTEGER offset = (y + i) * width + (x + j);
					//Get depth value.
					_INTEGER depthValue = depthBuffer[offset] & 0xFFFF;
					//Check result.
					if(depthValue <= 1500)
					{
						//Add count.
						count ++;
						//Add value.
						position.x() += x + j; position.y() += depthValue; position.z() += y + i;
					}
				}
			}
			//Calculate average.
			if(count > 0) position /= (_FLOAT)count;
			//Adjust position.
			position.x() = (x + 4) - width / 2.0f;
			position.z() = height / 2.0f - (y + 4);
			//Scale the horizontal.
			position.x() *= 0.01f; position.z() *= 0.01f;
			//Calculate position.
			if(count <= 0)
			{
				position.y() = 0.0f;
			}
			else
			{
				position.y() *= 0.001f;
			}

			//Get application.
			CD3DXApplication* application = (CD3DXApplication*)d3dxEvent.pUserContext;
			//Check result.
			if(!application->CPhysicsApplication::isRunning())
			{
				//Set transform.
				setPosition(position);
			}
			else
			{
				//Check count.
				if(count <= 0)
				{
					//Set transform.
					setPosition(position);
					//Set position.
					application->setPosition(this,position);

					//Clear force.
					application->setForce(this,C4DVector3());
				}
				else
				{
					//Set force.
					application->setForce(this,9.8f * (position - getPosition()));
				}
			}
		}
		break;
	}
	//Return result.
	return CDynamicPrimitiveObject::handleMessage(d3dxEvent);
}
