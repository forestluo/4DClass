///////////////////////////////////////////////////////////////////////////////
//
// NoneScene.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _NONE_SCENE_H_
#define _NONE_SCENE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXScene.h"

///////////////////////////////////////////////////////////////////////////////
//
// NoneScene
//
///////////////////////////////////////////////////////////////////////////////

class CNoneScene : public CD3DXScene
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

protected:
	/**
	 * Initialize objects of world.
	 *
	 * @param resourceManager Resource manager.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT initializeObjects(CResourceManager* resourceManager);

public:
	CNoneScene(void);
	virtual ~CNoneScene(void);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_NONE_SCENE_H_
