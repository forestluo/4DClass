///////////////////////////////////////////////////////////////////////////////
//
// InteractionItem.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _INTERACTION_ITEM_H_
#define _INTERACTION_ITEM_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DVector3.h"

///////////////////////////////////////////////////////////////////////////////
//
// CInteractionItem
//
///////////////////////////////////////////////////////////////////////////////

class CInteractionItem
{
private:
	/**
	 * Pick mode.
	 */
	_INTEGER mode;
	/**
	 * Pick point.
	 */
	C4DVector3 pickPoint;

	/**
	 * Controlled body.
	 */
	_OBJECT controlledBody;
	/**
	 * Body pick controller.
	 */
	_OBJECT bodyPickController;

public:
	CInteractionItem(void);
	virtual ~CInteractionItem(void);

public:

	/**
	* Clear controller.
	*
	* @param None No parameters needed.
	* @return
	*     <p>No results returned.</p>
	*/
	void clearController();

private:

	/** 
	 * Create controller.
	 *
	 * @param body Body.
	 * @param mode Mode of controller.
	 * @param point Point of controller.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void createController(_OBJECT body,_INTEGER mode,const C4DVector3& point);

public:

	/**
	 * Pick object by body pick controller.
	 *
	 * @param body A picked body.
	 * @param point Picked point.
	 * @param
	 *     <p>No results returned.</p>
	 */
	void pickBody(_OBJECT body,const C4DVector3& point);

	/**
	 * Drag object by body pick controller.
	 *
	 * @param body A picked body.
	 * @param direction Direction for moving.
	 * @param
	 *     <p>No results returned.</p>
	 */
	void moveBody(_OBJECT body,const C4DVector3& direction);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_INTERACTION_ITEM_H_
