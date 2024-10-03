///////////////////////////////////////////////////////////////////////////////
//
// RandomScene.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "RandomScene.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ResourceName.h"

///////////////////////////////////////////////////////////////////////////////
//
// CRandomScene
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CRandomScene::CRandomScene(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CRandomScene
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CRandomScene::~CRandomScene(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// InitializeObjects
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CRandomScene::initializeObjects(CResourceManager* resourceManager)
{
	//Scaling.
	C4DVector3 scaling;
	//Rotation.
	C4DVector3 rotation;
	//Position.
	C4DVector3 position;
	//Renderable
	CPrimitiveObject* object;

#ifdef _DEBUG
	assert(resourceManager != _NULL);
#endif

	for(_INTEGER i = -1;i <= 1;i ++)
	{
		//Set position.
		position.x() = i * 4.0f;

		//Set rotation.
		rotation.x() = D3DX_PI / 10.0f * i;

		//Set scaling.
		scaling.x() = 1.0f;
		//scaling.z() = 2.0f * sinf(D3DX_PI / 10.0f * i) + 0.1f;

		for(_INTEGER j = -1; j <= 1;j ++)
		{
			//Set position.
			position.y() = j * 4.0f;

			//rotation.y() = 0.0f;
			rotation.y() = D3DX_PI / 10.0f * j;

			//Set scaling.
			scaling.y() = 1.0f;
			//scaling.y() = 2.0f * sinf(D3DX_PI / 10.0f * j) + 0.1f;

			for(_INTEGER k = -1;k <= 1;k ++)
			{
				//Set position.
				position.z() = k * 4.0f;

				//Set rotation.
				//roation.z() = 0.0f;
				rotation.z() = D3DX_PI / 10.0f * k;

				//Set scaling.
				scaling.z() = 1.0f;
				//scaling.z() = 2.0f * sinf(D3DX_PI / 10.0f * k) + 0.1f;

				//Object.
				object = (CPrimitiveObject *)_NULL;
				//Get value.
				_INTEGER index = (rand() + ((i + 10) * 100 + (j + 10) * 10 + (k + 10))) % 19;
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
				assert(object != _NULL);
#endif
				//Set scale.
				object->setScale(scaling.x(),scaling.y(),scaling.z());
				//Set position.
				object->setPosition(position.x(),position.y(),position.z());
				//Set rotation.
				object->setEularRotation(rotation.x(),rotation.y(),rotation.z());
			}
		}
	}
	//Return ok.
	return S_OK;
}
