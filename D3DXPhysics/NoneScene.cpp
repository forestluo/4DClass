///////////////////////////////////////////////////////////////////////////////
//
// NoneScene.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "NoneScene.h"

///////////////////////////////////////////////////////////////////////////////
//
// Globals
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CNoneScene::base(L"CNoneScene",L"CD3DXScene");

///////////////////////////////////////////////////////////////////////////////
//
// CNoneScene
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CNoneScene::CNoneScene(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CNoneScene
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CNoneScene::~CNoneScene(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// InitializeObjects
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CNoneScene::initializeObjects(CResourceManager* resourceManager)
{
	//Return OK.
	return S_OK;
}
