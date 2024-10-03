///////////////////////////////////////////////////////////////////////////////
//
// D3DXCaptureTexture.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXCaptureTexture.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include <d3dx9.h>
#include <d3dx9tex.h>
#include <d3d9types.h>
#include <dshow.h>

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CD3DXCaptureTexture::base(L"CD3DXCaptureTexture",L"CD3DXDynamicTexture");

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXCaptureTexture
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXCaptureTexture::CD3DXCaptureTexture(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXCaptureTexture
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXCaptureTexture::~CD3DXCaptureTexture(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// GetCaptureNames
//
/////////////////////////////////////////////////////////////////////////////////

void CD3DXCaptureTexture::getCaptureNames(CNormalStringList& names)
{
	//Result.
	HRESULT hr;

	//Device enumeration.
	ICreateDevEnum* pDevEnum = NULL;
	//Create the system device enumerator.
	hr = CoCreateInstance(CLSID_SystemDeviceEnum,NULL,CLSCTX_INPROC,
							IID_ICreateDevEnum,(void **)&pDevEnum);
	//Check result.
	if(SUCCEEDED(hr))
	{
#ifdef _DEBUG
		assert(pDevEnum != NULL);
#endif
		//Enum moniker.
		IEnumMoniker* pClassEnum = NULL;
		//Create an enumerator for the video capture devices.
		hr = pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,&pClassEnum,0);
		//Check result.
		if(SUCCEEDED(hr) && pClassEnum != NULL)
		{
			//Reset.
			pClassEnum->Reset();

			do 
			{
				//Fetched.
				ULONG cFetched = -1;
				//Moniker.
				IMoniker* pMoniker = NULL;
				//Get next.
				hr = pClassEnum->Next(1,&pMoniker,&cFetched);
				//Check result.
				if(hr != S_OK || pMoniker == NULL || cFetched <= 0) break;
					
				//Property bag.
				IPropertyBag *pBag = NULL;
				//Get moniker.
				hr = pMoniker->BindToStorage(0,0,IID_IPropertyBag,(void **)&pBag);
				//Check result.
				if(SUCCEEDED(hr) && pBag != NULL)
				{
					//Variant.
					VARIANT value;
					//Set type.
					value.vt = VT_BSTR;
					//Read value.
					hr = pBag->Read(L"FriendlyName",&value,NULL);
					//Check result.
					if(hr == NO_ERROR)
					{
						//Copy precisely.
						//Ba care of memory leaking.
						//Friendly name.
						WCHAR friendlyName[256];
						//Clear.
						memset(friendlyName,0,256 * sizeof(WCHAR));
						//Copy string.
						StringCchCopyW(friendlyName,256,value.bstrVal);
						//Free string.
						SysFreeString(value.bstrVal);
						//Get device name.
						CNormalString deviceName((_STRING)friendlyName);
						//Check result.
						if(deviceName.length() > 0) names.addString(deviceName);
					}
					//Release.
					SAFE_RELEASE(pBag);
				}
				//Release.
				SAFE_RELEASE(pMoniker);

			} while(_TRUE);
			//Release.
			SAFE_RELEASE(pClassEnum);
		}
		//Release.
		SAFE_RELEASE(pDevEnum);
	}
}

