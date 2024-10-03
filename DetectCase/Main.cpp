///////////////////////////////////////////////////////////////////////////////
//
// Main.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "4DPrint.h"
#include "D3DXCaptureTexture.h"

///////////////////////////////////////////////////////////////////////////////
//
// Main
//
///////////////////////////////////////////////////////////////////////////////

void main(int argc,char* argv[])
{
	//Names.
	CNormalStringList names;

	//Initialize COM.
	CoInitialize(NULL);
	
	//Get capture names.
	CD3DXCaptureTexture::getCaptureNames(names);
	//Check result.
	for(_INTEGER i = 0;i < names.getCount();i ++)
	{
		//Print.
		C4DPrint::printLine(stdout,L"capture[%d] = \"%s\"",i,names.getString(i).getCString());
	}

	//Uninitialize COM.
    CoUninitialize();
}