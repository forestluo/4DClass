///////////////////////////////////////////////////////////////////////////////
//
// D3DXApplication.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXApplication.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXEvent.h"
#include "D3DXFilter.h"
#include "D3DXTexture.h"
#include "ResourceName.h"
#include "CompoundObject.h"
#include "CompoundAxisObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXApplication
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CD3DXApplication::CD3DXApplication(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// ~CD3DXApplication
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CD3DXApplication::~CD3DXApplication(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// Startup
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXApplication::startup()
{
	//Add scene.
	CPhysicsApplication::startup(getForeground());
}

///////////////////////////////////////////////////////////////////////////////
//
// ClearForeground
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXApplication::clearForeground()
{
	//Open lock.
	openLock();
	{
		//Get foreground scene.
		CForegroundScene* foreground = getForeground();
#ifdef _DEBUG
		assert(foreground != _NULL);
#endif
		//Release all objects.
		foreground->releaseAll();
	}
	//Close lock.
	closeLock();
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateFloor
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXApplication::createFloor(_INTEGER arrayType,_INTEGER row,_INTEGER column,const C4DVector3& origin)
{
#ifdef _DEBUG
	assert(row > 0 && column > 0);
#endif

	//Open lock.
	openLock();
	{
		//Get foreground scene.
		CForegroundScene* foreground = getForeground();
#ifdef _DEBUG
		assert(foreground != _NULL);
#endif
		//Create floor.
		foreground->createFloor(getResourceManager(),arrayType,row,column,origin);
	}
	//Close lock.
	closeLock();
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateSphereArray
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXApplication::createSphereArray(_INTEGER arrayType,_INTEGER row,_INTEGER column,const C4DVector3& origin)
{
#ifdef _DEBUG
	assert(row > 0 && column > 0);
#endif

	//Open lock.
	openLock();
	{
		//Get foreground scene.
		CForegroundScene* foreground = getForeground();
#ifdef _DEBUG
		assert(foreground != _NULL);
#endif
		//Create sphere array.
		foreground->createSphereArray(getResourceManager(),arrayType,row,column,origin);
	}
	//Close lock.
	closeLock();
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateCuboidArray
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXApplication::createCuboidArray(_INTEGER arrayType,_INTEGER row,_INTEGER column,const C4DVector3& origin)
{
#ifdef _DEBUG
	assert(row > 0 && column > 0);
#endif

	//Open lock.
	openLock();
	{
		//Get foreground scene.
		CForegroundScene* foreground = getForeground();
#ifdef _DEBUG
		assert(foreground != _NULL);
#endif
		//Create cuboid array.
		foreground->createCuboidArray(getResourceManager(),arrayType,row,column,origin);
	}
	//Close lock.
	closeLock();
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateModel
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXApplication::createModel(_INTEGER type,_FLOAT mass,
									const C4DVector3& scaling,
									const C4DVector3& rotation,
									const C4DVector3& position)
{
#ifdef _DEBUG
	assert(mass >= 0.0f);
#endif

	//Open lock.
	openLock();
	{
		//Get foreground scene.
		CForegroundScene* foreground = getForeground();
#ifdef _DEBUG
		assert(foreground != _NULL);
#endif
		//Create model.
		foreground->createModel(getResourceManager(),type,mass,scaling,rotation,position);
	}
	//Close lock.
	closeLock();
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateModel
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXApplication::createModel(const CPrimitiveAttribute& attribute,_FLOAT mass,
									const C4DVector3& scaling,
									const C4DVector3& rotation,
									const C4DVector3& position)
{
#ifdef _DEBUG
	assert(mass >= 0.0f);
#endif

	//Open lock.
	openLock();
	{
		//Get foreground scene.
		CForegroundScene* foreground = getForeground();
#ifdef _DEBUG
		assert(foreground != _NULL);
#endif
		//Create model.
		CPrimitiveObject* object = foreground->createModel(getRenderableManager(),attribute,mass,scaling,rotation,position);
#ifdef _DEBUG
		assert(object != NULL);
#endif
		//Select default effect.
		object->selectEffect(getResourceManager(),EFFECT_REFLECT);
	}
	//Close lock.
	closeLock();
}

///////////////////////////////////////////////////////////////////////////////
//
// AddCompound
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CD3DXApplication::addCompound(CCompoundObject* object)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif

	//Open lock.
	openLock();
	{
		//Get foreground scene.
		CForegroundScene* foreground = getForeground();
#ifdef _DEBUG
		assert(foreground != _NULL);
#endif
		//Add compound.
		foreground->addCompound(this,object);
	}
	//Close lock.
	closeLock();
	//Return true.
	return _TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateCompound
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXApplication::createCompound(_LONG classCode,_FLOAT mass,
										const C4DVector3& scaling,
										const C4DVector3& rotation,
										const C4DVector3& position)
{
	//Open lock.
	openLock();
	{
		//Get foreground scene.
		CForegroundScene* foreground = getForeground();
#ifdef _DEBUG
		assert(foreground != _NULL);
#endif
		//Create compound.
		foreground->createCompound(this,classCode,mass,scaling,rotation,position);
	}
	//Close lock.
	closeLock();
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateJoint
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXApplication::createJoint(_INTEGER jointType,
									const CNormalString& childName,
									const C4DVector3& position,
									const CNormalString& parentName)
{
	//Open lock.
	openLock();
	{
		//Get foreground scene.
		CForegroundScene* foreground = getForeground();
#ifdef _DEBUG
		assert(foreground != _NULL);
#endif
		//Create joint.
		foreground->createJoint(getResourceManager(),jointType,childName,position,parentName);
	}
	//Close lock.
	closeLock();
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateJoint
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXApplication::createJoint(const CJointAttribute& attribute,
									const CNormalString& childName,
									const C4DVector3& position,
									const CNormalString& parentName)
{
	//Open lock.
	openLock();
	{
		//Get foreground scene.
		CForegroundScene* foreground = getForeground();
#ifdef _DEBUG
		assert(foreground != _NULL);
#endif
		//Create joint.
		foreground->createJoint(getResourceManager(),attribute,childName,position,parentName);
	}
	//Close lock.
	closeLock();
}

///////////////////////////////////////////////////////////////////////////////
//
// PickObject
//
///////////////////////////////////////////////////////////////////////////////

CWorldObject* CD3DXApplication::pickObject(const CNormalString& alias,_BOOL clearPicked)
{
	//Picked object.
	CWorldObject* object;

	//Open lock.
	openLock();
	{
		//Get foreground.
		CForegroundScene* foreground = getForeground();
#ifdef _DEBUG
		assert(foreground != _NULL);
#endif
		//Clear picked.
		if(clearPicked) foreground->clearPicked();
		//Get object.
		object = foreground->getObject(alias);
		//Check result.
		if(object != _NULL)
		{
			//Get top parent.
			CWorldObject* parent = (CWorldObject *)CWorldObject::getTopParent(object);
			//Check result.
			if(parent != _NULL && parent->isRenderableObject())
			{
				//Clear picked. 
				((CD3DXRenderableObject *)parent->getRenderable())->setPicked(_FALSE);
			}
			//Check result.
			if(object->isRenderableObject())
			{
				//Set picked.
				((CD3DXRenderableObject *)object->getRenderable())->setPicked(_TRUE);
			}
			//Check result.
			if(parent != _NULL && parent->isRenderableObject())
			{
				//Clear picked and reset picked. 
				((CD3DXRenderableObject *)parent->getRenderable())->setPicked(_TRUE);
			}
		}
	}
	//Close lock.
	closeLock();
	//Return result.
	return object;
}

///////////////////////////////////////////////////////////////////////////////
//
// PickObject
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CD3DXApplication::pickObject(_INTEGER x,_INTEGER y,CPickResult& result,_BOOL allHits)
{
	//Result.
	_BOOL resultFlag;

	//Open lock.
	openLock();
	{
		//Get view port.
		CViewPort* viewPort = getViewPort();
#ifdef _DEBUG
		assert(viewPort != _NULL);
#endif
		//Pick ray.
		CPickRay pickRay;
		//Get view direction.
		C4DVector3 direction = viewPort->getViewDirection(x,y);
		//Set pick parameters.
		pickRay.setPickParameters(viewPort->getViewMatrix(),direction);

		//Get foreground.
		CForegroundScene* foreground = getForeground();
#ifdef _DEBUG
		assert(foreground != _NULL);
#endif
		//Set all hist.
		pickRay.setAllHits(allHits);
		//Get result.
		resultFlag = foreground->pickObject(pickRay,result);
	}
	//Close lock.
	closeLock();
	//Return result.
	return resultFlag;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandlePickEvent
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXApplication::handlePickEvent(const D3DXEvent& d3dxEvent)
{
	//Get x.
	_INTEGER x = (short)LOWORD(d3dxEvent.d3dxMsgProc.lParam);
	//Get y.
	_INTEGER y = (short)HIWORD(d3dxEvent.d3dxMsgProc.lParam);

	//Get foreground.
	CForegroundScene* foreground = getForeground();
#ifdef _DEBUG
	assert(foreground != _NULL);
#endif

	//Pick result.
	CPickResult result;
	//Pick object when button down.
	if(!pickObject(x,y,result))
	{
		//Clear body controller.
		if(CPhysicsApplication::isRunning())
		{
			//Get picked object.
			CWorldObject* worldObject = foreground->getPickedObject();
			//Check result.
			if(worldObject != _NULL && worldObject->isPhysicsObject())
			{
				//Clear controller.
				CPhysicsApplication::clearController((CPhysicsObject *)worldObject->getPhysics());
			}
		}
		//Clear picked.
		foreground->clearPicked();
		//Clear collision.
		foreground->clearCollision();
	}
	else
	{
		//Get nearest intersection.
		CPickIntersection* pickIntersection = result.getNearestIntersection();
		//Check result.
		if(pickIntersection != _NULL)
		{
			//Set picked.
			foreground->setPicked(pickIntersection->getAlias());
			//Get picked object.
			CWorldObject* pickedObject = foreground->getObject(pickIntersection->getAlias());
			//Check result.
			if(pickedObject != _NULL && pickedObject->isRenderableObject())
			{
				//Check object.
				if(CPhysicsApplication::isRunning())
				{
					//Get top parent of a picked object.
					_OBJECT topParent = CWorldObject::getTopParent(pickedObject);
					//Set top parent as a picked object.
					if(topParent != _NULL) pickedObject = (CWorldObject *)topParent;
					//Check result.
					if(pickedObject->isPhysicsObject() &&
						(pickedObject->isPrimitiveObject() || pickedObject->isCompoundObject()))
					{
						//Get physics object.
						CPhysicsObject* physicsObject = (CPhysicsObject *)pickedObject->getPhysics();
#ifdef _DEBUG
						assert(physicsObject != _NULL);
#endif
						//Check result.
						//Get nearest distance.
						_FLOAT distance = pickIntersection->getNearestDistance();
						//Check result.
						//It is valid only when distance is bigger than zero.
						if(distance >= 0.0f && physicsObject->getMass() > 0.0f)
						{
							//Pick body.
							CPhysicsApplication::pickBody(physicsObject,result.getPickOrigin());
						}
					}
				}
				//Update collision.
				foreground->updateCollision((CD3DXRenderableObject *)pickedObject->getRenderable());
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMoveEvent
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXApplication::handleMoveEvent(const D3DXEvent& d3dxEvent)
{
	//Get view port.
	CViewPort* viewPort = getViewPort();
#ifdef _DEBUG
	assert(viewPort != _NULL);
#endif
	//Get foreground.
	CForegroundScene* foreground = getForeground();
#ifdef _DEBUG
	assert(foreground != _NULL);
#endif
	//Get picked object.
	CWorldObject* object = foreground->getPickedObject();
	//Check result.
	if(object == _NULL || !object->isMovable() || !object->isRenderableObject()) return;
	//Get renderable object.
	CD3DXRenderableObject* renderableObject = (CD3DXRenderableObject *)object->getRenderable();
#ifdef _DEBUG
	assert(renderableObject != _NULL);
#endif
	//Get move direction.
	C4DVector3 moveDirection = viewPort->getMoveDirection((short)LOWORD(d3dxEvent.d3dxMsgProc.lParam),
														(short)HIWORD(d3dxEvent.d3dxMsgProc.lParam));
	//Check status.
	if(!CPhysicsApplication::isRunning())
	{
		//Get picked object.
		CWorldObject* pickedObject = renderableObject->getPickedObject();
		//Check result.
		if(pickedObject != _NULL && pickedObject->isMovable()) object = pickedObject;
		//Set new position.
		object->setPosition(object->getPosition() + moveDirection);
	}
	else
	{
		//Get top parent.
		_OBJECT topParent = CWorldObject::getTopParent(object);
		//Set top parent as a picked object.
		if(topParent != _NULL) object = (CWorldObject *)topParent;
		//Check object.
		if(object->isPhysicsObject() && 
			(object->isPrimitiveObject() || object->isCompoundObject()))
		{
			//Get physics object.
			CPhysicsObject* physicsObject = (CPhysicsObject *)object->getPhysics();
#ifdef _DEBUG
			assert(physicsObject != _NULL);
#endif
			//Move body.
			if(physicsObject->getMass() > 0.0f) CPhysicsApplication::moveBody(physicsObject,moveDirection);
		}
	}
	//Update collision.
	foreground->updateCollision(renderableObject);
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXApplication::handleMessage(const D3DXEvent& d3dxEvent)
{
	//New event.
	D3DXEvent newEvent;
	//Copy event.
	memcpy(&newEvent,&d3dxEvent,sizeof(D3DXEvent));
	//Set view port.
	newEvent.pUserContext = (void *)this;

	//Open lock.
	openLock();
	//Check event.
	switch(d3dxEvent.d3dxEventID)
	{
	//Handle key presses.
	case d3dxMsgProc:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxMsgProc.pbNoFurtherProcessing != NULL);
#endif
		//Check message.
		if(d3dxEvent.d3dxMsgProc.IsMousePickEvent()) handlePickEvent(newEvent);
		else if(d3dxEvent.d3dxMsgProc.IsMouseMoveObjectEvent()) handleMoveEvent(newEvent);
		else if(d3dxEvent.d3dxMsgProc.IsMouseReleaseEvent())
		{
			//Clear body controller.
			if(CPhysicsApplication::isRunning())
			{
				//Get foreground.
				CForegroundScene* foreground = getForeground();
#ifdef _DEBUG
				assert(foreground != _NULL);
#endif
				//Get picked object.
				CWorldObject* worldObject = foreground->getPickedObject();
				//Check result.
				if(worldObject != _NULL && worldObject->isPhysicsObject())
				{
					//Clear controller.
					CPhysicsApplication::clearController((CPhysicsObject *)worldObject->getPhysics());
				}
			}
		}

		//Handle message process.
		if(CViewPortApplication::handleMessage(newEvent))
		{
			//Set flag.
			*d3dxEvent.d3dxMsgProc.pbNoFurtherProcessing = true;
		}
		else if(CSceneApplication::handleMessage(newEvent))
		{
			//Set flag.
			*d3dxEvent.d3dxMsgProc.pbNoFurtherProcessing = true;
		}
		break;
	//Message process.
	case d3dxOnKeyboard:
		break;
	//Handle updates to the scene.
	case d3dxOnFrameMove:
		//Do simulation.
		CPhysicsApplication::doSimulation();
		//Handle message.
		CResourceApplication::handleMessage(newEvent);
		//Handle message.
		CViewPortApplication::handleMessage(newEvent);
		//Handle message.
		CSceneApplication::handleMessage(newEvent);
		break;
	//Render the scene using the D3D9 device.
	case d3dxOnD3D9FrameRender:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxFrameRender9.pd3dDevice != NULL);
#endif
		//Handle message.
		CViewPortApplication::handleMessage(newEvent);
		//Call scene function.
		CSceneApplication::handleMessage(newEvent);
		break;
	//Release D3D9 resources created in the OnD3D9CreateDevice callback.
	case d3dxOnD3D9DestroyDevice:
		//Handle message.
		CSceneApplication::handleMessage(newEvent);
		//Handle message.
		CViewPortApplication::handleMessage(newEvent);
		//Handle message.
		CResourceApplication::handleMessage(newEvent);
		break;
	//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	case d3dxOnD3D9CreateDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxCreateDevice9.pd3dDevice != NULL);
#endif
		//Handle message.
		CResourceApplication::handleMessage(newEvent);
		//Handle message.
		CViewPortApplication::handleMessage(newEvent);
		//Handle message.
		CSceneApplication::handleMessage(newEvent);
		break;
	//Release D3D9 resources created in the OnD3D9ResetDevice callback.
	case d3dxOnD3D9LostDevice:
		//Handle message.
		CSceneApplication::handleMessage(newEvent);
		//Handle message.
		CViewPortApplication::handleMessage(newEvent);
		//Handle message.
		CResourceApplication::handleMessage(newEvent);
		break;
	//Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) or that are tied to the back buffer size.
	case d3dxOnD3D9ResetDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxResetDevice9.pd3dDevice != NULL);
#endif
		//Handle message.
		CResourceApplication::handleMessage(newEvent);
		//Handle message.
		CViewPortApplication::handleMessage(newEvent);
		//Handle message.
		CSceneApplication::handleMessage(newEvent);
		break;
	}
	//Close lock.
	closeLock();
	//Return result.
	return CD3DXObject::handleMessage(newEvent);
}
