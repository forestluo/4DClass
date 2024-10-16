///////////////////////////////////////////////////////////////////////////////
//
// BackgroundScene.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "BackgroundScene.h"

///////////////////////////////////////////////////////////////////////////////
//
// Globals
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CBackgroundScene::base(L"CBackgroundScene",L"CD3DXScene");

///////////////////////////////////////////////////////////////////////////////
//
// Definitions.
//
///////////////////////////////////////////////////////////////////////////////

#define _4D_AXIS0_											L"ȫ�������"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXAxisObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// CBackgroundScene
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CBackgroundScene::CBackgroundScene(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CBackgroundScene
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CBackgroundScene::~CBackgroundScene(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// InitializeObjects
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CBackgroundScene::initializeObjects(CResourceManager* resourceManager)
{
	//Check result.
	CD3DXCompoundObject* object = new CD3DXAxisObject();
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set alias.
	object->setAlias(_4D_AXIS0_);
	//Add object.
	addObject(object);
	//Return ok.
	return S_OK;
}
