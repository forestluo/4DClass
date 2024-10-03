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

#include "VirtualLabDoc.h"

#include <propkey.h>

#include "D3DXDevice.h"
#include "D3DXFilter.h"
#include "D3DXEffect.h"
#include "KinectDevice.h"
#include "D3DXFileMesh.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CVirtualLabDoc::addDeviceOptions(CComboBox* pCombo)
{
#ifdef _DEBUG
	assert(application != NULL && pCombo != NULL);
#endif
	//Open lock.
	application->openLock();
	{
		//Get resource manager.
		CResourceManager* resourceManager = application->getResourceManager();
#ifdef _DEBUG
		assert(resourceManager != _NULL);
#endif
		//Enumeration.
		CListNodeEnumeration iterator;
		//Get enumeration.
		resourceManager->getEnumeration(CResourceManager::deviceManager,iterator);
		//Do while.
		while(iterator.hasMoreElements())
		{
			//Get device.
			CD3DXDevice* device = (CD3DXDevice *)iterator.nextElement();
#ifdef _DEBUG
			assert(device != _NULL);
#endif
			//Check result.
			if(device->isReserved()) continue;
			//Add option.
			pCombo->AddString(device->getName().getCString());
		}
	}
	//Close lock.
	application->closeLock();
}


void CVirtualLabDoc::addKinectOptions(CComboBox* pCombo)
{
#ifdef _DEBUG
	assert(application != NULL && pCombo != NULL);
#endif
	//Open lock.
	application->openLock();
	{
		//Get resource manager.
		CResourceManager* resourceManager = application->getResourceManager();
#ifdef _DEBUG
		assert(resourceManager != _NULL);
#endif
		//Enumeration.
		CListNodeEnumeration iterator;
		//Get enumeration.
		resourceManager->getEnumeration(CResourceManager::deviceManager,iterator);
		//Do while.
		while(iterator.hasMoreElements())
		{
			//Get device.
			CD3DXDevice* device = (CD3DXDevice *)iterator.nextElement();
#ifdef _DEBUG
			assert(device != _NULL);
#endif
			//Check result.
			if(device->isReserved()) continue;
			//Check type.
			if(!IS_KINECTDEVICE_BASE(device)) continue;
			//Add option.
			pCombo->AddString(device->getName().getCString());
		}
	}
	//Close lock.
	application->closeLock();
}

void CVirtualLabDoc::addFilterOptions(CComboBox* pCombo)
{
#ifdef _DEBUG
	assert(application != NULL && pCombo != NULL);
#endif
	//Open lock.
	application->openLock();
	{
		//Get resource manager.
		CResourceManager* resourceManager = application->getResourceManager();
#ifdef _DEBUG
		assert(resourceManager != _NULL);
#endif
		//Enumeration.
		CListNodeEnumeration iterator;
		//Get enumeration.
		resourceManager->getEnumeration(CResourceManager::filterManager,iterator);
		//Do while.
		while(iterator.hasMoreElements())
		{
			//Get filter.
			CD3DXFilter* filter = (CD3DXFilter *)iterator.nextElement();
#ifdef _DEBUG
			assert(filter != _NULL);
#endif
			//Check result.
			if(filter->isReserved()) continue;
			//Add option.
			pCombo->AddString(filter->getName().getCString());
		}
	}
	//Close lock.
	application->closeLock();
}

void CVirtualLabDoc::addParentOptions(CComboBox* pCombo)
{
#ifdef _DEBUG
	assert(application != NULL && pCombo != NULL);
#endif

	//Open lock.
	application->openLock();
	{
		//Get foreground.
		CForegroundScene* foreground = application->getForeground();
#ifdef _DEBUG
		assert(foreground != NULL);
#endif
		//Enumeration.
		CListNodeEnumeration iterator;
		//Get enumeration.
		foreground->getEnumeration(iterator);
		//Do while.
		while(iterator.hasMoreElements())
		{
			//Get object.
			CWorldObject* object = (CWorldObject *)iterator.nextElement();
#ifdef _DEBUG
			assert(object != _NULL);
#endif
			//Check instance.
			if(object->isPhysicsObject() && !object->isJointObject())
			{
				//Add parent.
				pCombo->AddString((LPCTSTR)object->getAlias().getCString());
			}
		}
	}
	//Close lock.
	application->closeLock();
}

void CVirtualLabDoc::addChildrenOptions(CComboBox* pCombo)
{
#ifdef _DEBUG
	assert(application != NULL && pCombo != NULL);
#endif

	//Open lock.
	application->openLock();
	{
		//Get foreground.
		CForegroundScene* foreground = application->getForeground();
#ifdef _DEBUG
		assert(foreground != NULL);
#endif
		//Enumeration.
		CListNodeEnumeration iterator;
		//Get enumeration.
		foreground->getEnumeration(iterator);
		//Do while.
		while(iterator.hasMoreElements())
		{
			//Get object.
			CWorldObject* object = (CWorldObject *)iterator.nextElement();
#ifdef _DEBUG
			assert(object != _NULL);
#endif
			//Check instance.
			if(object->isPhysicsObject() && !object->isJointObject())
			{
				//Get physics object.
				CPhysicsObject* physicsObject = (CPhysicsObject *)object->getPhysics();
#ifdef _DEBUG
				assert(physicsObject != NULL);
#endif
				//Check mass.
				if(physicsObject->getMass() > 0.0f) pCombo->AddString((LPCTSTR)object->getAlias().getCString());
			}
		}
	}
	//Close lock.
	application->closeLock();
}

void CVirtualLabDoc::addDeviceOptions(CMFCPropertyGridProperty* pProp)
{
#ifdef _DEBUG
	assert(application != NULL && pProp != NULL);
#endif
	//Open lock.
	application->openLock();
	{
		//Get resource manager.
		CResourceManager* resourceManager = application->getResourceManager();
#ifdef _DEBUG
		assert(resourceManager != _NULL);
#endif
		//Enumeration.
		CListNodeEnumeration iterator;
		//Get enumeration.
		resourceManager->getEnumeration(CResourceManager::deviceManager,iterator);
		//Do while.
		while(iterator.hasMoreElements())
		{
			//Get device.
			CD3DXDevice* device = (CD3DXDevice *)iterator.nextElement();
#ifdef _DEBUG
			assert(device != _NULL);
#endif
			//Check result.
			if(device->isReserved()) continue;
			//Add option.
			pProp->AddOption(device->getName().getCString());
		}
	}
	//Close lock.
	application->closeLock();
}

void CVirtualLabDoc::addFilterOptions(CMFCPropertyGridProperty* pProp)
{
#ifdef _DEBUG
	assert(application != NULL && pProp != NULL);
#endif
	//Open lock.
	application->openLock();
	{
		//Get resource manager.
		CResourceManager* resourceManager = application->getResourceManager();
#ifdef _DEBUG
		assert(resourceManager != _NULL);
#endif
		//Enumeration.
		CListNodeEnumeration iterator;
		//Get enumeration.
		resourceManager->getEnumeration(CResourceManager::filterManager,iterator);
		//Do while.
		while(iterator.hasMoreElements())
		{
			//Get filter.
			CD3DXFilter* filter = (CD3DXFilter *)iterator.nextElement();
#ifdef _DEBUG
			assert(filter != _NULL);
#endif
			//Check filter.
			if(filter->isReserved()) continue;
			//Add option.
			pProp->AddOption(filter->getName().getCString());
		}
	}
	//Close lock.
	application->closeLock();
}

void CVirtualLabDoc::addTextureOptions(CMFCPropertyGridProperty* pProp)
{
#ifdef _DEBUG
	assert(application != NULL && pProp != NULL);
#endif
	//Open lock.
	application->openLock();
	{
		//Get resource manager.
		CResourceManager* resourceManager = application->getResourceManager();
#ifdef _DEBUG
		assert(resourceManager != _NULL);
#endif
		//Enumeration.
		CListNodeEnumeration iterator;
		//Get enumeration.
		resourceManager->getEnumeration(CResourceManager::textureManager,iterator);
		//Do while.
		while(iterator.hasMoreElements())
		{
			//Get texture.
			CD3DXTexture* texture = (CD3DXTexture *)iterator.nextElement();
#ifdef _DEBUG
			assert(texture != _NULL);
#endif
			//Check result.
			if(texture->isReserved()) continue;
			//Add option.
			pProp->AddOption(texture->getName().getCString());
		}
	}
	//Close lock.
	application->closeLock();
}

void CVirtualLabDoc::addMeshOptions(CMFCPropertyGridProperty* pProp)
{
#ifdef _DEBUG
	assert(application != NULL && pProp != NULL);
#endif
	//Open lock.
	application->openLock();
	{
		//Get resource manager.
		CResourceManager* resourceManager = application->getResourceManager();
#ifdef _DEBUG
		assert(resourceManager != _NULL);
#endif
		//Enumeration.
		CListNodeEnumeration iterator;
		//Get enumeration.
		resourceManager->getEnumeration(CResourceManager::meshManager,iterator);
		//Do while.
		while(iterator.hasMoreElements())
		{
			//Get mesh.
			CD3DXFileMesh* mesh = (CD3DXFileMesh *)iterator.nextElement();
#ifdef _DEBUG
			assert(mesh != _NULL);
#endif
			//Check result.
			if(mesh->isReserved()) continue;
			//Add option.
			pProp->AddOption(mesh->getName().getCString());
		}
	}
	//Close lock.
	application->closeLock();
}

void CVirtualLabDoc::addPrimitiveOptions(CMFCPropertyGridProperty* pProp)
{
#ifdef _DEBUG
	assert(application != NULL && pProp != NULL);
#endif
	//Open lock.
	application->openLock();
	{
		//Get resource manager.
		CResourceManager* resourceManager = application->getResourceManager();
#ifdef _DEBUG
		assert(resourceManager != _NULL);
#endif
		//Enumeration.
		CListNodeEnumeration iterator;
		//Get enumeration.
		resourceManager->getEnumeration(CResourceManager::primitiveManager,iterator);
		//Do while.
		while(iterator.hasMoreElements())
		{
			//Get primitive.
			CD3DXPrimitive* primitive = (CD3DXPrimitive *)iterator.nextElement();
#ifdef _DEBUG
			assert(primitive != _NULL);
#endif
			//Check primitive.
			if(primitive->isReserved()) continue;
			//Add option.
			pProp->AddOption(primitive->getName().getCString());
		}
	}
	//Close lock.
	application->closeLock();
}

void CVirtualLabDoc::addEffectOptions(CMFCPropertyGridProperty* pProp)
{
#ifdef _DEBUG
	assert(application != NULL && pProp != NULL);
#endif
	//Open lock.
	application->openLock();
	{
		//Get resource manager.
		CResourceManager* resourceManager = application->getResourceManager();
#ifdef _DEBUG
		assert(resourceManager != _NULL);
#endif
		//Enumeration.
		CListNodeEnumeration iterator;
		//Get enumeration.
		resourceManager->getEnumeration(CResourceManager::effectManager,iterator);
		//Do while.
		while(iterator.hasMoreElements())
		{
			//Get effect.
			CD3DXEffect* effect = (CD3DXEffect *)iterator.nextElement();
#ifdef _DEBUG
			assert(effect != _NULL);
#endif
			//Check result.
			if(effect->isReserved()) continue;
			//Add option.
			pProp->AddOption(effect->getName().getCString());
		}
	}
	//Close lock.
	application->closeLock();
}
