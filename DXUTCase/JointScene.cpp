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
///////////////////////////////////////////////////////////////////////////////

CJointScene::CJointScene(void)
{
	//Set default value.
	index = 0;
	//Set default value.
	object = (CJointObject *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CJointScene
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CJointScene::~CJointScene(void)
{
	//Clear value.
	object = (CJointObject *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// InitializeObjects
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CJointScene::initializeObjects(CResourceManager* resourceManager)
{
#ifdef _DEBUG
	assert(resourceManager != _NULL);
#endif

	//Add index.
	index ++;

	//Check object.
	object = new CJointObject(CJointAttribute::classicBallJoint);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Add object.
	addObject(object);
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
		//Check keydown.
		if(d3dxEvent.d3dxKeyboard.bKeyDown)
		{
			//Check value.
			if(d3dxEvent.d3dxKeyboard.nChar == VK_SPACE)
			{
#ifdef _DEBUG
				assert(d3dxEvent.pUserContext != _NULL);
#endif
				//Get resource manager.
				CResourceManager* resourceManager = ((CD3DXApplication *)d3dxEvent.pUserContext)->getResourceManager();
#ifdef _DEBUG
				assert(resourceManager != _NULL);
#endif
				//Check object.
				if(object != _NULL)
				{
					//Remove it from scene.
					removeObject(object);
					//Delete object.
					delete (CJointObject *)object;
					//Clear object.
					object = (CJointObject *)_NULL;
				}
				//Check result.
				if(index == 0) object = new CJointObject(CJointAttribute::classicBallJoint);
				else if(index == 1) object = new CJointObject(CJointAttribute::classicCorkscrewJoint);
				else if(index == 2) object = new CJointObject(CJointAttribute::classicHingeJoint);
				else if(index == 3) object = new CJointObject(CJointAttribute::classicSliderJoint);
				else if(index == 4) object = new CJointObject(CJointAttribute::classicUniversalJoint);
				else if(index == 5) object = new CJointObject(CJointAttribute::classicUpVectorJoint);
#ifdef _DEBUG
				else assert(_FALSE);
#endif
#ifdef _DEBUG
				assert(object != _NULL);
#endif
				//Create object.
				object->createObjects(resourceManager);
				//Add object.
				addObject(object);
				//Add index.
				index ++; if(index >= 6) index = 0;
			}
		}
		break;
	}
	//Return result.
	return CForegroundScene::handleMessage(d3dxEvent);
}