/////////////////////////////////////////////////////////////////////////////
// Name:        alchemediaSdtafx.h
// Purpose:     
// Author:      Julio Jerez
// Modified by: 
// Created:     22/05/2010 08:02:08
// RCS-ID:      
// Copyright:   Copyright (c) <2010> <Newton Game Dynamics>
// License:     
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely
/////////////////////////////////////////////////////////////////////////////

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#ifndef __ALCHEMEDIA_STDAFX_H__
#define __ALCHEMEDIA_STDAFX_H__



#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions


// for dynamic link library
//#define _AFXDLL 


#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#include <io.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <Newton.h>

#include <tinyxml.h>
#include <dStdAfxMath.h>
#include <dContainersStdAfx.h>


#include <dMathDefines.h>
#include <dVector.h>
#include <dMatrix.h>
#include <dQuaternion.h>

#include <dCRC.h>
#include <dRtti.h>
#include <dHeap.h>
#include <dList.h>
#include <dTree.h>
#include <dClassInfo.h>
#include <dRefCounter.h>
#include <dBaseHierarchy.h>

#include "dPluginStdafx.h"
#include "dScene.h"
#include "dNodeInfo.h"
#include "dDrawUtils.h"
#include "dRootNodeInfo.h"
#include "dMeshNodeInfo.h"
#include "dBoneNodeInfo.h"
#include "dSceneNodeInfo.h"
#include "dCameraNodeInfo.h"
#include "dTextureNodeInfo.h"
#include "dMaterialNodeInfo.h"
#include "dGeometryNodeInfo.h"
#include "dGeometryNodeSkinModifierInfo.h"

#include "dPluginRecord.h"
#include "dImportPlugin.h"
#include "dExportPlugin.h"




#endif