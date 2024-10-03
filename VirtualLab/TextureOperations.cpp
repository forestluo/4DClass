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

#include "D3DXFilter.h"
#include "HAARFilter.h"
#include "DepthFilter.h"

#include "PSEyeDevice.h"
#include "KinectDevice.h"
#include "D3DXInputTexture.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int CVirtualLabDoc::getDeviceCount()
{
	//Count.
	int count = 0;

#ifdef _DEBUG
	assert(application != NULL);
#endif
	//Open lock.
	application->openLock();
	{
		//Get resource manager.
		CResourceManager* resourceManager = application->getResourceManager();
#ifdef _DEBUG
		assert(resourceManager != NULL);
#endif
		//Get count.
		count = resourceManager->getCount(CResourceManager::deviceManager);
	}
	//Close lock.
	application->closeLock();
	//Return result.
	return count;
}

int CVirtualLabDoc::getKinectDeviceCount()
{
	//Count.
	int count = 0;

#ifdef _DEBUG
	assert(application != NULL);
#endif
	//Open lock.
	application->openLock();
	{
		//Get resource manager.
		CResourceManager* resourceManager = application->getResourceManager();
#ifdef _DEBUG
		assert(resourceManager != NULL);
#endif
		//Get count.
		count = resourceManager->getCount(CResourceManager::deviceManager,CKinectDevice::getClassCode());
	}
	//Close lock.
	application->closeLock();
	//Return result.
	return count;
}

void CVirtualLabDoc::openKinectDevices()
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
		assert(resourceManager != NULL);
#endif
		//Check count of kinect.
		_INTEGER count = CKinectDevice::getKinectCount();
		//Check result.
		for(_INTEGER i = 0;i < count;i ++)
		{
			//Name.
			CNormalString deviceName;
			//Append.
			deviceName.append(L"KinectÉãÏñÍ·")->append(i);
#ifdef _DEBUG
			//Get resource.
			assert(resourceManager->getResource(deviceName) == NULL);
#endif
			//Create device.
			CKinectDevice* device = new CKinectDevice();
#ifdef _DEBUG
			assert(device != NULL);
#endif
			//Set name.
			device->CD3DXResource::setName(deviceName);
			//Open device.
			if(!device->openDevice(i))
			{
				//Close device.
				device->closeDevice();
				//Delete device.
				delete (CKinectDevice *)device;
			}
			else
			{
				//Add it into resource manager.
				resourceManager->addResource(device);
			}
		}
	}
	//Close lock.
	application->closeLock();
}

void CVirtualLabDoc::closeKinectDevices()
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
		assert(resourceManager != NULL);
#endif
		//Enumeration.
		CListNodeEnumeration iterator;
		//Get enumeration.
		resourceManager->getEnumeration(CResourceManager::deviceManager,iterator);
		//Check result.
		while(iterator.hasMoreElements())
		{
			//Get next element.
			CD3DXDevice* device = (CD3DXDevice *)iterator.nextElement();
#ifdef _DEBUG
			assert(device != NULL);
#endif
			//The reserved one cannot be removed.
			if(device->isReserved()) continue;
			//Check devices.
			if(!IS_KINECTDEVICE_BASE(device)) continue;
			//Check reference count.
			if(device->countReference() > 0) continue;
#ifndef _DEBUG
			//Remove and delete it.
			resourceManager->removeResource(device->getName());
#else
			//Remove and delete it.
			assert(resourceManager->removeResource(device->getName()) == device);
#endif
			//Delete device.
			delete (CKinectDevice *)device; 
		}
	}
	//Close lock.
	application->closeLock();
}

int CVirtualLabDoc::getPSEyeDeviceCount()
{
	//Count.
	int count = 0;

#ifdef _DEBUG
	assert(application != NULL);
#endif
	//Open lock.
	application->openLock();
	{
		//Get resource manager.
		CResourceManager* resourceManager = application->getResourceManager();
#ifdef _DEBUG
		assert(resourceManager != NULL);
#endif
		//Get count.
		count = resourceManager->getCount(CResourceManager::deviceManager,CPSEyeDevice::getClassCode());
	}
	//Close lock.
	application->closeLock();
	//Return result.
	return count;
}

void CVirtualLabDoc::openPSEyeDevices()
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
		assert(resourceManager != NULL);
#endif
		//Check count of PSEye camera.
		_INTEGER count = CPSEyeDevice::getCameraCount();
		//Check result.
		for(_INTEGER i = 0;i < count;i ++)
		{
			//Name.
			CNormalString deviceName;
			//Append.
			deviceName.append(L"PSEyeÉãÏñÍ·")->append(i);
#ifdef _DEBUG
			//Get resource.
			assert(resourceManager->getResource(deviceName) == NULL);
#endif
			//Get guid.
			GUID guid = CPSEyeDevice::getCameraGuid(i);
			//Create device.
			CPSEyeDevice* device = new CPSEyeDevice(guid);
#ifdef _DEBUG
			assert(device != NULL);
#endif
			//Set name.
			device->CD3DXResource::setName(deviceName);
			//Open device.
			if(!device->openDevice())
			{
				//Close device.
				device->closeDevice();
				//Delete device.
				delete (CPSEyeDevice *)device;
			}
			else
			{
				//Add it into resource manager.
				resourceManager->addResource(device);
			}
		}
	}
	//Close lock.
	application->closeLock();
}

void CVirtualLabDoc::closePSEyeDevices()
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
		assert(resourceManager != NULL);
#endif
		//Enumeration.
		CListNodeEnumeration iterator;
		//Get enumeration.
		resourceManager->getEnumeration(CResourceManager::deviceManager,iterator);
		//Check result.
		while(iterator.hasMoreElements())
		{
			//Get next element.
			CD3DXDevice* device = (CD3DXDevice *)iterator.nextElement();
#ifdef _DEBUG
			assert(device != NULL);
#endif
			//The reserved one cannot be removed.
			if(device->isReserved()) continue;
			//Check devices.
			if(!IS_PSEYEDEVICE_BASE(device)) continue;
			//Check reference count.
			if(device->countReference() > 0) continue;
#ifndef _DEBUG
			//Remove and delete it.
			resourceManager->removeResource(device->getName());
#else
			//Remove and delete it.
			assert(resourceManager->removeResource(device->getName()) != NULL);
#endif
			//Delete device.
			delete (CPSEyeDevice *)device; 
		}
	}
	//Close lock.
	application->closeLock();
}


void CVirtualLabDoc::closeFilters()
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
		assert(resourceManager != NULL);
#endif
		//Enumeration.
		CListNodeEnumeration iterator;
		//Get enumeration.
		resourceManager->getEnumeration(CResourceManager::filterManager,iterator);
		//Check result.
		while(iterator.hasMoreElements())
		{
			//Get next element.
			CD3DXFilter* filter = (CD3DXFilter *)iterator.nextElement();
#ifdef _DEBUG
			assert(filter != NULL);
#endif
			//The reserved one cannot be removed.
			if(filter->isReserved()) continue;
			//Check reference count.
			if(filter->countReference() > 0) continue;
#ifndef _DEBUG
			//Remove and delete it from resources.
			resourceManager->removeResource(filter->getName());
#else
			//Remove and delete it from resources.
			assert(resourceManager->removeResource(filter->getName()) != NULL);
#endif
			delete (CD3DXFilter *)filter;
		}
	}
	//Close lock.
	application->closeLock();
}


int CVirtualLabDoc::getFilterCount()
{
	//Count.
	int count = 0;

#ifdef _DEBUG
	assert(application != NULL);
#endif
	//Open lock.
	application->openLock();
	{
		//Get resource manager.
		CResourceManager* resourceManager = application->getResourceManager();
#ifdef _DEBUG
		assert(resourceManager != NULL);
#endif
		//Get count.
		count = resourceManager->getCount(CResourceManager::filterManager);
	}
	//Close lock.
	application->closeLock();
	//Return result.
	return count;
}


void CVirtualLabDoc::addHAARFilter(const CNormalString& name,const CNormalString& deviceName)
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
		assert(resourceManager != NULL);
		assert(resourceManager->getResource(name) == NULL);
#endif
		//Create HAAR filter.
		CHAARFilter* filter = new CHAARFilter();
#ifdef _DEBUG
		assert(filter != NULL);
#endif
		//Set name.
		filter->setName(name);
		//Set device.
		if(!filter->selectDevice(resourceManager,deviceName))
		{
			//Delete filter.
			delete (CHAARFilter *)filter;
		}
		else
		{
			//Add it into resources.
			resourceManager->addResource(filter);
		}
	}
	//Close lock.
	application->closeLock();
}


void CVirtualLabDoc::addDepthFilter(const CNormalString& name,const CNormalString& deviceName)
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
		assert(resourceManager != NULL);
		assert(resourceManager->getResource(name) == NULL);
#endif
		//Create depth filter.
		CDepthFilter* filter = new CDepthFilter();
#ifdef _DEBUG
		assert(filter != NULL);
#endif
		//Set name.
		filter->setName(name);
		//Set device.
		if(!filter->selectDevice(resourceManager,deviceName))
		{
			//Delete filter.
			delete (CDepthFilter *)filter;
		}
		else
		{
			//Add it into resources.
			resourceManager->addResource(filter);
		}
	}
	//Close lock.
	application->closeLock();
}


int CVirtualLabDoc::getHAARFilterCount()
{
	//Count.
	int count = 0;

#ifdef _DEBUG
	assert(application != NULL);
#endif
	//Open lock.
	application->openLock();
	{
		//Get resource manager.
		CResourceManager* resourceManager = application->getResourceManager();
#ifdef _DEBUG
		assert(resourceManager != NULL);
#endif
		//Get count.
		count = resourceManager->getCount(CResourceManager::filterManager,CHAARFilter::getClassCode());
	}
	//Close lock.
	application->closeLock();
	//Return result.
	return count;
}

void CVirtualLabDoc::addInputTexture(const CNormalString& name,const CNormalString& deviceName)
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
		assert(resourceManager != NULL);
		assert(resourceManager->getResource(name) == NULL);
#endif
		//Create input texture.
		CD3DXInputTexture* texture = new CD3DXInputTexture();
#ifdef _DEBUG
		assert(texture != NULL);
#endif
		//Set name.
		texture->setName(name);
		//Select source.
		if(!texture->selectSource(resourceManager,deviceName))
		{
			//Fail to input texture.
			delete (CD3DXInputTexture*)texture;
		}
		else
		{
			//Add it into resources.
			resourceManager->addResource(texture);
		}
	}
	//Close lock.
	application->closeLock();
}

void CVirtualLabDoc::closeInputTextures()
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
		assert(resourceManager != NULL);
#endif
		//Enumeration.
		CListNodeEnumeration iterator;
		//Get enumeration.
		resourceManager->getEnumeration(CResourceManager::textureManager,iterator);
		//Check result.
		while(iterator.hasMoreElements())
		{
			//Get next element.
			CD3DXTexture* texture = (CD3DXTexture *)iterator.nextElement();
#ifdef _DEBUG
			assert(texture != NULL);
#endif
			//The reserved one cannot be removed.
			if(texture->isReserved()) continue;
			//Check textures.
			if(!IS_INPUTTEXTURE_BASE(texture)) continue;

			//Clear reference.
			application->clearTexture(texture->getName());
#ifdef _DEBUG
			//Check reference count.
			assert(texture->countReference() <= 0);
#endif

#ifndef _DEBUG
			//Remove and delete it.
			resourceManager->removeResource(texture->getName());
#else
			//Remove and delete it.
			assert(resourceManager->removeResource(texture->getName()) == texture);
#endif
			//Delete it from memory.
			delete (CD3DXInputTexture *)texture; 
		}
	}
	//Close lock.
	application->closeLock();
}


int CVirtualLabDoc::getInputTextureCount()
{
	//Count.
	int count = 0;

#ifdef _DEBUG
	assert(application != NULL);
#endif
	//Open lock.
	application->openLock();
	{
		//Get resource manager.
		CResourceManager* resourceManager = application->getResourceManager();
#ifdef _DEBUG
		assert(resourceManager != NULL);
#endif
		//Get count.
		count = resourceManager->getCount(CResourceManager::textureManager,CD3DXInputTexture::getClassCode());
	}
	//Close lock.
	application->closeLock();
	//Return result.
	return count;
}
