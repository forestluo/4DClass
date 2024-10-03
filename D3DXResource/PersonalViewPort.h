///////////////////////////////////////////////////////////////////////////////
//
// PersonalViewPort.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PERSONAL_VIEW_PORT_H_
#define _PERSONAL_VIEW_PORT_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ViewPort.h"

///////////////////////////////////////////////////////////////////////////////
//
// CPersonalViewPort
//
///////////////////////////////////////////////////////////////////////////////

class CPersonalViewPort : public CViewPort
{
private:
	//Base description.
	static const C4DBase base;

public:

	/**
	 * Get class code.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Hash code of this class.</p>
	 */
	static _LONG getClassCode() {return base.classCode();}

	/**
	 * Get class code.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Hash code of this class.</p>
	 */
	virtual _LONG classCode() const {return base.classCode();}

public:
	CPersonalViewPort(void);
	virtual ~CPersonalViewPort(void);
};

#define IS_PERSONAL_VIEWPORT_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CPersonalViewPort::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_PERSONAL_VIEW_PORT_H_
