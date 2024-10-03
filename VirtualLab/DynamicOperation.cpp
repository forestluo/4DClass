// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// VirtualLabDoc.cpp : implementation of the CVirtualLabDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "VirtualLab.h"
#endif

#include "ResourceName.h"
#include "VirtualLabDoc.h"

#include "KinectDevice.h"

#include "GroundMeshObject.h"
#include "ControlBallObject.h"
#include "ControlItemObject.h"
#include "KinematicItemObject.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CVirtualLabDoc::addControlledBall(const CNormalString& name,const CNormalString& deviceName)
{
#ifdef _DEBUG
	assert(application != NULL);
#endif
	//Open lock.
	application->openLock();
	{
		//Create control ball object.
		CControlBallObject* ballObject = new CControlBallObject();
#ifdef _DEBUG
		assert(ballObject != NULL);
#endif
		//Set name.
		ballObject->setAlias(name);
		//Select source.
		ballObject->selectSource(application,deviceName);

		//Get resource manager.
		CResourceManager* resourceManager = application->getResourceManager();
#ifdef _DEBUG
		assert(resourceManager != _NULL);
#endif
		//Select default effect.
		ballObject->selectEffect(resourceManager,EFFECT_REFLECT);

		//Get foreground.
		CForegroundScene* foreground = application->getForeground();
#ifdef _DEBUG
		assert(foreground != _NULL);
#endif
		//Add it into scene.
		foreground->addObject(ballObject);
	}
	//Close lock.
	application->closeLock();
}

void CVirtualLabDoc::addControlledItemArray(const CNormalString& name,const CNormalString& deviceName)
{
#ifdef _DEBUG
	assert(application != NULL);
#endif
	//Open lock.
	application->openLock();
	{
		//Get resource manager.
		CResourceManager* resourceManager = application->getResourceManager();
#ifdef _DEBUG
		assert(resourceManager != _NULL);
#endif
		//Get device.
		CD3DXResource* resource = resourceManager->getResource(deviceName);
#ifdef _DEBUG
		assert(resource != _NULL);
		assert(IS_KINECTDEVICE_BASE(resource));
#endif
		//Get width.
		_INTEGER width = ((CKinectDevice *)resource)->getWidth();
		//Get height.
		_INTEGER height = ((CKinectDevice *)resource)->getHeight();
		//Do while.
		for(_INTEGER i = 0;i < height;i += 16)
		{
			//Do while.
			for(_INTEGER j = 0;j < width;j += 16)
			{
				//Item name.
				CNormalString itemName;
				//Append.
				itemName.append(L"¿ØÖÆÇò(")->append((i / 16) * width + (j / 16))->append(L")");

				//Create control ball object.
				CControlItemObject* itemObject = new CControlItemObject(j,i);
#ifdef _DEBUG
				assert(itemObject != NULL);
#endif
				//Set name.
				itemObject->setAlias(itemName);
				//Select source.
				itemObject->selectSource(application,deviceName);

				//Select default effect.
				itemObject->selectEffect(resourceManager,EFFECT_REFLECT);

				//Get foreground.
				CForegroundScene* foreground = application->getForeground();
#ifdef _DEBUG
				assert(foreground != _NULL);
#endif
				//Add it into scene.
				foreground->addObject(itemObject);
			}
		}
	}
	//Close lock.
	application->closeLock();
}


void CVirtualLabDoc::addKinematicItemArray(const CNormalString& name,const CNormalString& deviceName)
{
#ifdef _DEBUG
	assert(application != NULL);
#endif
	//Open lock.
	application->openLock();
	{
		//Get resource manager.
		CResourceManager* resourceManager = application->getResourceManager();
#ifdef _DEBUG
		assert(resourceManager != _NULL);
#endif
		//Get device.
		CD3DXResource* resource = resourceManager->getResource(deviceName);
#ifdef _DEBUG
		assert(resource != _NULL);
		assert(IS_KINECTDEVICE_BASE(resource));
#endif
		//Get width.
		_INTEGER width = ((CKinectDevice *)resource)->getWidth();
		//Get height.
		_INTEGER height = ((CKinectDevice *)resource)->getHeight();
		//Do while.
		for(_INTEGER i = 0;i < height;i += 8)
		{
			//Do while.
			for(_INTEGER j = 0;j < width;j += 8)
			{
				//Item name.
				CNormalString itemName;
				//Append.
				itemName.append(L"¿ØÖÆÕó(")->append((i / 8) * width + (j / 8))->append(L")");

				//Create control ball object.
				CKinematicItemObject* itemObject = new CKinematicItemObject(j,i);
#ifdef _DEBUG
				assert(itemObject != NULL);
#endif
				//Set name.
				itemObject->setAlias(itemName);
				//Select source.
				itemObject->selectSource(application,deviceName);

				//Select default effect.
				itemObject->selectEffect(resourceManager,EFFECT_REFLECT);

				//Get foreground.
				CForegroundScene* foreground = application->getForeground();
#ifdef _DEBUG
				assert(foreground != _NULL);
#endif
				//Add it into scene.
				foreground->addObject(itemObject);
			}
		}
	}
	//Close lock.
	application->closeLock();
}

void CVirtualLabDoc::addInputGroundMesh(const CNormalString& name,const CNormalString& deviceName)
{
#ifdef _DEBUG
	assert(application != NULL);
#endif
	//Open lock.
	application->openLock();
	{
		//Create ground mesh object.
		CGroundMeshObject* meshObject = new CGroundMeshObject();
#ifdef _DEBUG
		assert(meshObject != NULL);
#endif
		//Set name.
		meshObject->setAlias(name);
		//Select source.
		meshObject->selectSource(application,deviceName);

		//Get resource manager.
		CResourceManager* resourceManager = application->getResourceManager();
#ifdef _DEBUG
		assert(resourceManager != _NULL);
#endif
		//Select default effect.
		meshObject->selectEffect(resourceManager,EFFECT_REFLECT);

		//Get foreground.
		CForegroundScene* foreground = application->getForeground();
#ifdef _DEBUG
		assert(foreground != _NULL);
#endif
		//Add it into scene.
		foreground->addObject(meshObject);
	}
	//Close lock.
	application->closeLock();
}
