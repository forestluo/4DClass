///////////////////////////////////////////////////////////////////////////////
//
// BumpScene.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "BumpScene.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ResourceName.h"
#include "D3DXApplication.h"

///////////////////////////////////////////////////////////////////////////////
//
// CBumpScene
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CBumpScene::CBumpScene(void)
{
	//Set default value.
	index = 0;
	//Set default value.
	floor = (CPrimitiveObject *)_NULL;
	object = (CPrimitiveObject *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CBumpScene
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CBumpScene::~CBumpScene(void)
{
	//Clear value.
	floor = (CPrimitiveObject *)_NULL;
	object = (CPrimitiveObject *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// InitializeObjects
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CBumpScene::initializeObjects(CResourceManager* resourceManager)
{
#ifdef _DEBUG
	assert(resourceManager != _NULL);
#endif

	//Add index.
	index ++;

	//Check result.
	object = createModel(resourceManager,PRIMITIVE_SPHERE0);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set mass.
	object->setMass(1.0f);
	//Set scale.
	object->setScale(0.4f,0.4f,0.4f);
	//Set position.
	object->setPosition(0.0f,3.0f,0.0f);
	//Select effect.
	object->selectEffect(resourceManager,EFFECT_TEXTURE);
	//Select scene map.
	object->selectSceneMap(resourceManager,TEXTURE_TULIPS);

	//Check result.
	floor = createModel(resourceManager,PRIMITIVE_FLOOR0);
#ifdef _DEBUG
	assert(floor != _NULL);
#endif
	//Set mass.
	floor->setMass(0.0f);
	//Set scale.
	floor->setScale(6.4f,0.2f,4.8f);
	//Set position.
	floor->setPosition(0.0f,0.0f,0.0f);
	//Set effect.
	floor->selectEffect(resourceManager,EFFECT_TEXTURE);

	//Return ok.
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CBumpScene::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	case d3dxOnD3D9FrameRender:
#ifdef _DEBUG
		assert(d3dxEvent.pUserContext != _NULL);
#endif
		//Check floor.
		if(floor != _NULL && floor->getSceneMap() == _NULL)
		{
			//Get resource manager.
			CResourceManager* resourceManager = ((CD3DXApplication *)d3dxEvent.pUserContext)->getResourceManager();
#ifdef _DEBUG
			assert(resourceManager != _NULL);
#endif
			//Check scene map.
			if(resourceManager->getResource(L"动态纹理0") != _NULL)
			{
				floor->selectSceneMap(resourceManager,L"动态纹理0");
			}
		}
		break;
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
				//Check object.
				if(object != _NULL)
				{
					//Remove it from scene.
					removeObject(object);
					//Delete object.
					delete (CPrimitiveObject *)object;
					//Clear object.
					object = (CPrimitiveObject *)_NULL;
				}
				//Check result.
				if(index == 0) object = createModel(resourceManager,PRIMITIVE_POLYGON4);
				else if(index == 1) object = createModel(resourceManager,PRIMITIVE_POLYGON6);
				else if(index == 2) object = createModel(resourceManager,PRIMITIVE_POLYGON8);
				else if(index == 3) object = createModel(resourceManager,PRIMITIVE_POLYGON12);
				else if(index == 4) object = createModel(resourceManager,PRIMITIVE_POLYGON20);
				else if(index == 5) object = createModel(resourceManager,PRIMITIVE_CONE0);
				else if(index == 6) object = createModel(resourceManager,PRIMITIVE_CONE3);
				else if(index == 7) object = createModel(resourceManager,PRIMITIVE_CONE4);
				else if(index == 8) object = createModel(resourceManager,PRIMITIVE_CONE6);
				else if(index == 9) object = createModel(resourceManager,PRIMITIVE_CYLINDER0);
				else if(index == 10) object = createModel(resourceManager,PRIMITIVE_CYLINDER3);
				else if(index == 11) object = createModel(resourceManager,PRIMITIVE_CYLINDER5);
				else if(index == 12) object = createModel(resourceManager,PRIMITIVE_CYLINDER6);
				else if(index == 13) object = createModel(resourceManager,PRIMITIVE_FRUSTUM0);
				else if(index == 14) object = createModel(resourceManager,PRIMITIVE_FRUSTUM3);
				else if(index == 15) object = createModel(resourceManager,PRIMITIVE_FRUSTUM4);
				else if(index == 16) object = createModel(resourceManager,PRIMITIVE_FRUSTUM6);
				else if(index == 17) object = createModel(resourceManager,PRIMITIVE_CUBOID0);
				else if(index == 18) object = createModel(resourceManager,PRIMITIVE_FLOOR0);
				else if(index == 19) object = createModel(resourceManager,PRIMITIVE_SPHERE0);
				else if(index == 20) object = createModel(resourceManager,PRIMITIVE_HEMISPHERE0);
				else if(index == 21) object = createModel(resourceManager,PRIMITIVE_CAPSULE0);
				else if(index == 22) object = createModel(resourceManager,PRIMITIVE_CHAMFERCYLINDER0);
#ifdef _DEBUG
				else assert(_FALSE);
#endif
#ifdef _DEBUG
				assert(object != _NULL);
#endif
				//Set mass.
				object->setMass(1.0f);
				//Set scale.
				object->setScale(1.0f,1.0f,1.0f);
				//Set position.
				object->setPosition(0.0f,3.0f,0.0f);
				//Add index.
				index ++; if(index >= 22) index = 0;
			}
		}
		break;
	}
	//Return result.
	return CForegroundScene::handleMessage(d3dxEvent);
}