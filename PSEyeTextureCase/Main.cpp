///////////////////////////////////////////////////////////////////////////////
//
// Main.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "4DPrint.h"
#include "SimpleExpire.h"

#include "PSEyeDevice.h"

///////////////////////////////////////////////////////////////////////////////
//
// Main
//
///////////////////////////////////////////////////////////////////////////////

void main(int argc,char* argv[])
{
	//Get count of camera.
	_INTEGER count = CPSEyeDevice::getCameraCount();
	//Print guid.
	C4DPrint::printLine(stdout,L"%d camera(s) was detected !",count);
	//Check result.
	for(_INTEGER i = 0;i < count;i ++)
	{
		//Get guid of camera.
		GUID guid = CPSEyeDevice::getCameraGuid(i);
		//Print guid.
		C4DPrint::printLine(stdout,L"\tguid[%d] = [%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x]", 
			i+1, guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
		//Create device.
		CPSEyeDevice device(guid);
		/*
		//Startup dynamic texture.
		if(texture.startup())
		{
			//Print guid.
			C4DPrint::printLine(stdout,L"camera[%d] was startup !",count);

			//Expiration.
			CSimpleExpire expiration(10 * SECOND);
			//Do while.
			while(!expiration.isExpired()) CSimpleThread::sleepMilliseconds(MILLISECOND);
		}
		else
		{
			//Print guid.
			C4DPrint::printLine(stdout,L"fail to startup camera[%d] !",count);
		}
		//Shutdown.
		texture.shutdown();
		*/
	}
}