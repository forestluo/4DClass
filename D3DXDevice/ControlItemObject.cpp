///////////////////////////////////////////////////////////////////////////////
//
// ControlItemObject.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "ControlItemObject.h"

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
// CControlItemObject
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CControlItemObject::CControlItemObject(_INTEGER x,_INTEGER y)
{
	//Set position.
	this->x = x;
	this->y = y;
	//Set mass.
	setMass(1.0f);
}

///////////////////////////////////////////////////////////////////////////////
//
// CControlItemObject
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CControlItemObject::~CControlItemObject(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// SelectSource
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CControlItemObject::selectSource(CResourceApplication* resourceApplication,const CNormalString& name)
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
	attribute.primitiveData.sphere.radius = 0.079f;
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

HRESULT CControlItemObject::handleMessage(const D3DXEvent& d3dxEvent)
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
			_FLOAT xPos = 0.0f, yPos = 0.0f, zPos = 0.0f;
			//Do while.
			for(_INTEGER i = 0;i < 16;i ++)
			{
				for(_INTEGER j = 0;j < 16;j ++)
				{
					//Calculate offset.
					_INTEGER offset = (y + i) * width + (x + j);
					//Get depth value.
					_INTEGER depthValue = depthBuffer[offset] & 0xFFFF;
					//Check result.
					if(depthValue <= 2000)
					{
						//Add count.
						count ++;
						//Add value.
						/*xPos += x + j;*/ yPos += depthValue; /*zPos += y + i;*/
					}
				}
			}
			//Calculate average.
			if(count > 0)
			{
				//Set pos.
				/*xPos /= (_FLOAT)count;*/ yPos /= (_FLOAT)count; /*zPos /= (_FLOAT)count*/;
			}
			//Adjust position.
			xPos = (x + 8) - width / 2.0f;
			zPos = height / 2.0f - (y + 8);
			//Scale the height.
			xPos *= 0.01f; zPos *= 0.01f;
			//Calculate position.
			if(count > 0) yPos *= 0.001f; else yPos = 0.0f;

			//Get application.
			CD3DXApplication* application = (CD3DXApplication*)d3dxEvent.pUserContext;
			//Check result.
			if(!application->CPhysicsApplication::isRunning())
			{
				//Set transform.
				setPosition(xPos,yPos,zPos);
			}
			else
			{
				//Position.
				C4DVector3 position = C4DVector3(xPos,yPos,zPos);
				//Check count.
				if(count <= 0)
				{
					//Set transform.
					setPosition(position);
					//Set position.
					application->setPosition(this,position);

					//Clear position.
					position.x() = 0.0f;position.y() = 0.0f;position.z() =0.0f;
					//Clear force.
					application->setForce(this,position);
				}
				else
				{
					//Get distance.
					C4DVector3 vector = position - getPosition();
					//Check result.
					if(vector.length() < 0.079f)
					{
						//Clear position.
						position.x() = 0.0f;position.y() = 0.0f;position.z() =0.0f;
						//Clear velocity.
						application->setVelocity(this,position);
					}
					else
					{
						//Set force.
						application->setVelocity(this,9.81f * vector);
					}
				}
			}
		}
		break;
	}
	//Return result.
	return CDynamicPrimitiveObject::handleMessage(d3dxEvent);
}
