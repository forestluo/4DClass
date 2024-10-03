///////////////////////////////////////////////////////////////////////////////
//
// JointScene.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "JointScene.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ResourceName.h"
#include "D3DXApplication.h"

///////////////////////////////////////////////////////////////////////////////
//
// CJointScene
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CJointScene::CJointScene(void)
{
	//Set default value.
	index = 0;
	//Set default value.
	joint = (CJointObject *)_NULL;
	child = (CPrimitiveObject *)_NULL;
	parent = (CPrimitiveObject *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CJointScene
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CJointScene::~CJointScene(void)
{
	//Clear value.
	joint = (CJointObject *)_NULL;
	child = (CPrimitiveObject *)_NULL;
	parent = (CPrimitiveObject *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// InitializeObjects
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CJointScene::initializeObjects(CResourceManager* resourceManager)
{
#ifdef _DEBUG
	assert(resourceManager != _NULL);
#endif

	//Check result.
	parent = createModel(resourceManager,PRIMITIVE_CUBOID0);
#ifdef _DEBUG
	assert(parent != _NULL);
#endif
	//Set mass.
	parent->setMass(1.0f);
	//Set scale.
	parent->setScale(0.2f,0.2f,0.2f);
	//Set position.
	parent->setPosition(0.0f,2.0f,0.0f);

	//Check result.
	child = createModel(resourceManager,PRIMITIVE_CUBOID0);
#ifdef _DEBUG
	assert(parent != _NULL);
#endif
	//Set mass.
	child->setMass(1.0f);
	//Set scale.
	child->setScale(0.2f,0.2f,0.2f);
	//Set position.
	child->setPosition(0.0f,1.0f,0.0f);

	//Create floor.
	createFloor(resourceManager,CFloorManager::yVerticalFloor);
	//Return ok.
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CJointScene::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	//Message process.
	case d3dxOnKeyboard:
#ifdef _DEBUG
		assert(d3dxEvent.pUserContext != _NULL);
#endif
		//Check keydown.
		if(d3dxEvent.d3dxKeyboard.bKeyDown)
		{
			//Check running.
			if(((CD3DXApplication *)d3dxEvent.pUserContext)->isRunning())
			{
				//Check char.
				if(d3dxEvent.d3dxKeyboard.nChar == VK_SPACE)
				{
					//Shutdown physics.
					((CD3DXApplication *)d3dxEvent.pUserContext)->shutdown();
				}
			}
			else if(d3dxEvent.d3dxKeyboard.nChar == VK_RETURN)
			{
				//Shutdown physics.
				((CD3DXApplication *)d3dxEvent.pUserContext)->startup();
			}
			//Check value.
			else if(d3dxEvent.d3dxKeyboard.nChar == VK_SPACE)
			{
				//Get resource manager.
				CResourceManager* resourceManager = ((CD3DXApplication *)d3dxEvent.pUserContext)->getResourceManager();
#ifdef _DEBUG
				assert(resourceManager != _NULL);
#endif
				//Check joint.
				if(joint != _NULL)
				{
					//Remove it from scene.
					removeObject(joint);
					//Delete object.
					delete (CJointObject *)joint;
					//Clear object.
					joint = (CJointObject *)_NULL;
				}
				//Check result.
				if(index == 0)
				{
					//Create joint.
					joint = createJoint(resourceManager,CJointAttribute::classicBallJoint);
				}
				else if(index == 1)
				{
					//Create joint.
					joint = createJoint(resourceManager,CJointAttribute::classicCorkscrewJoint);
				}
				else if(index == 2)
				{
					//Create joint.
					joint = createJoint(resourceManager,CJointAttribute::classicHingeJoint);
				}
				else if(index == 3)
				{
					//Create joint.
					joint = createJoint(resourceManager,CJointAttribute::classicSliderJoint);
				}
				else if(index == 4)
				{
					//Create joint.
					joint = createJoint(resourceManager,CJointAttribute::classicUniversalJoint);
				}
				else if(index == 5)
				{
					//Create joint.
					joint = createJoint(resourceManager,CJointAttribute::classicUpVectorJoint);
				}
				else if(index == 6)
				{
					//Create joint.
					joint = createJoint(resourceManager,CJointAttribute::customBallJoint);
				}
				else if(index == 7)
				{
					//Create joint.
					joint = createJoint(resourceManager,CJointAttribute::customHingeJoint);
				}
				else if(index == 8)
				{
					//Create joint.
					joint = createJoint(resourceManager,CJointAttribute::customSliderJoint);
				}
				else if(index == 9)
				{
					//Create joint.
					joint = createJoint(resourceManager,CJointAttribute::custom6DOFJoint);
				}
#ifdef _DEBUG
				else assert(_FALSE);
#endif
				//Set child.
				joint->setJointChild(child);
				//Set parent.
				joint->setJointParent(parent);
				//Set position.
				joint->setPosition(0.0f,1.5f,0.0f);
				//Add index.
				index ++; if(index >= 10) index = 0;
			}
		}
		break;
	}
	//Return result.
	return CForegroundScene::handleMessage(d3dxEvent);
}