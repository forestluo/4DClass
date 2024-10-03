///////////////////////////////////////////////////////////////////////////////
//
// ControlItemObject.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _CONTROL_ITEM_OBJECT_H_
#define _CONTROL_ITEM_OBJECT_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ResourceApplication.h"
#include "DynamicPrimitiveObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// ControlItemObject
//
///////////////////////////////////////////////////////////////////////////////

class CControlItemObject : public CDynamicPrimitiveObject
{
private:
	/** 
	 * Position of resolution.
	 */
	_INTEGER x,y;

public:
	CControlItemObject(_INTEGER x,_INTEGER y);
	virtual ~CControlItemObject(void);

public:

	/** 
	 * Select source.
	 *
	 * @param resourceApplication Resource application.
	 * @param name Name of device or filter.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL selectSource(CResourceApplication* resourceApplication,const CNormalString& name);

public:

	/**
	 * Handle message.
	 *
	 * @param d3dxEvent D3DX event.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT handleMessage(const D3DXEvent& d3dxEvent);

};

///////////////////////////////////////////////////////////////////////////////
#endif //_CONTROL_ITEM_OBJECT_H_