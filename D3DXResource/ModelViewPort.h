///////////////////////////////////////////////////////////////////////////////
//
// ModelViewPort.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _MODEL_VIEW_PORT_H_
#define _MODEL_VIEW_PORT_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ViewPort.h"

///////////////////////////////////////////////////////////////////////////////
//
// CModelViewPort
//
///////////////////////////////////////////////////////////////////////////////

class CModelViewPort : public CViewPort
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
	CModelViewPort(void);
	virtual ~CModelViewPort(void);

};

#define IS_MODEL_VIEWPORT_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CModelViewPort::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_MODEL_VIEW_PORT_H_
