///////////////////////////////////////////////////////////////////////////////
//
// ControlItemObject1.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _CONTROL_ITEM_OBJECT1_H_
#define _CONTROL_ITEM_OBJECT1_H_

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
// ControlItemObject1
//
///////////////////////////////////////////////////////////////////////////////

class CControlItemObject1 : public CDynamicPrimitiveObject
{
private:
	_BOOL hideFlag;
	_BOOL adjustFlag;
	/** 
	 * Position of resolution.
	 */
	_INTEGER x,y;
	/** 
	 * Height of ball.
	 */
	_FLOAT dHeight;

public:
	CControlItemObject1(_INTEGER x,_INTEGER y);
	virtual ~CControlItemObject1(void);

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
#endif //_CONTROL_ITEM_OBJECT1_H_