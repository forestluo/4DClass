///////////////////////////////////////////////////////////////////////////////
//
// VirtualScene.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _VIRTUAL_SCENE_H_
#define _VIRTUAL_SCENE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ForegroundScene.h"

///////////////////////////////////////////////////////////////////////////////
//
// VirtualScene
//
///////////////////////////////////////////////////////////////////////////////

class CVirtualScene : public CForegroundScene
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
	 * Initialize objects.
	 *
	 * @param resourceManager Resource manager.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT initializeObjects(CResourceManager* resourceManager);

public:
	CVirtualScene(void);
	virtual ~CVirtualScene(void);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_VIRTUAL_SCENE_H_
