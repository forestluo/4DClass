///////////////////////////////////////////////////////////////////////////////
//
// LinestripManager.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _LINESTRIP_MANAGER_H_
#define _LINESTRIP_MANAGER_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXResourceGroup.h"

///////////////////////////////////////////////////////////////////////////////
//
// LinestripManager
//
///////////////////////////////////////////////////////////////////////////////

class CLinestripManager : public CD3DXResourceGroup
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
	CLinestripManager(void);
	virtual ~CLinestripManager(void);

protected:

	/**
	 * Create resources.
	 *
	 * @param resourceManager Resource manager.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT createResources(_OBJECT resourceManager);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_LINESTRIP_MANAGER_H_
