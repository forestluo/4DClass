///////////////////////////////////////////////////////////////////////////////
//
// PrimitiveScene.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "PrimitiveScene.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ResourceName.h"
#include "D3DXApplication.h"

///////////////////////////////////////////////////////////////////////////////
//
// CPrimitiveScene
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CPrimitiveScene::CPrimitiveScene(void)
{
	//Set default value.
	index = 0;
	//Set default value.
	object = (CPrimitiveObject *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CPrimitiveScene
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CPrimitiveScene::~CPrimitiveScene(void)
{
	//Clear value.
	object = (CPrimitiveObject *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// InitializeObjects
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CPrimitiveScene::initializeObjects(CResourceManager* resourceManager)
{
#ifdef _DEBUG
	assert(resourceManager != _NULL);
#endif

	//Add index.
	index ++;

	//Check result.
	object = createModel(resourceManager,PRIMITIVE_TRIANGLE0);
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Return ok.
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CPrimitiveScene::handleMessage(const D3DXEvent& d3dxEvent)
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
					delete (CPrimitiveObject *)object;
					//Clear object.
					object = (CPrimitiveObject *)_NULL;
				}
				//Check result.
				if(index == 0) object = createModel(resourceManager,PRIMITIVE_TRIANGLE0);
				else if(index == 1) object = createModel(resourceManager,PRIMITIVE_QUADRANGLE0);
				else if(index == 2) object = createModel(resourceManager,PRIMITIVE_CONE0);
				else if(index == 3) object = createModel(resourceManager,PRIMITIVE_CONE3);
				else if(index == 4) object = createModel(resourceManager,PRIMITIVE_CONE4);
				else if(index == 5) object = createModel(resourceManager,PRIMITIVE_CONE6);
				else if(index == 6) object = createModel(resourceManager,PRIMITIVE_CYLINDER0);
				else if(index == 7) object = createModel(resourceManager,PRIMITIVE_CYLINDER3);
				else if(index == 8) object = createModel(resourceManager,PRIMITIVE_CYLINDER5);
				else if(index == 9) object = createModel(resourceManager,PRIMITIVE_CYLINDER6);
				else if(index == 10) object = createModel(resourceManager,PRIMITIVE_FRUSTUM0);
				else if(index == 11) object = createModel(resourceManager,PRIMITIVE_FRUSTUM3);
				else if(index == 12) object = createModel(resourceManager,PRIMITIVE_FRUSTUM4);
				else if(index == 13) object = createModel(resourceManager,PRIMITIVE_FRUSTUM6);
				else if(index == 14) object = createModel(resourceManager,PRIMITIVE_CUBOID0);
				else if(index == 15) object = createModel(resourceManager,PRIMITIVE_FLOOR0);
				else if(index == 16) object = createModel(resourceManager,PRIMITIVE_SPHERE0);
				else if(index == 17) object = createModel(resourceManager,PRIMITIVE_HEMISPHERE0);
				else if(index == 18) object = createModel(resourceManager,PRIMITIVE_CAPSULE0);
#ifdef _DEBUG
				else assert(_FALSE);
#endif
#ifdef _DEBUG
				assert(object != _NULL);
#endif
				//Add index.
				index ++; if(index >= 19) index = 0;
			}
		}
		break;
	}
	//Return result.
	return CForegroundScene::handleMessage(d3dxEvent);
}