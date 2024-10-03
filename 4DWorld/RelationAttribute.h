///////////////////////////////////////////////////////////////////////////////
//
// RelationAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _RELATION_ATTRIBUTE_H
#define _RELATION_ATTRIBUTE_H

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DType.h"

///////////////////////////////////////////////////////////////////////////////
//
// RelationAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CRelationAttribute
{
private:
	/**
	 * This object.
	 */
	_OBJECT thisObject;
	/**
	 * Parent object.
	 */
	_OBJECT parentObject;

private:
	/**
	 * Physics object.
	 */
	_OBJECT physicsObject;
	/**
	 * Renderable object.
	 */
	_OBJECT renderableObject;

public:
	CRelationAttribute(void);
	virtual ~CRelationAttribute(void);

public:

	/**
	 * Whether is a physics object.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if it is a physics object.</p>
	 */
	_BOOL isPhysicsObject() const;
	/**
	 * Whether is a renderable object.
	 *
	 * @param None No parameters needed.
	 * @return
	 *    <p>Return true, if it is a renderable object.</p>
	 */
	_BOOL isRenderableObject() const;
	/**
	 * Whether is a renderable physics object.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if it is a renderable physics object.</p>
	 */
	_BOOL isRenderablePhysicsObject() const;

public:

	/**
	 * Get this.
	 *
	 * <p>It is the top most object pointer.</p>
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>This object.</p>
	 */
	_OBJECT getThis() const;
	/**
	 * Set this.
	 *
	 * <p>It is the top most object pointer.</p>
	 *
	 * @param thisObject This object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setThis(_OBJECT thisObject);

public:

	/**
	 * Get parent.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Parent object.</p>
	 */
	_OBJECT getParent() const;
	/**
	 * Set parent.
	 *
	 * @param parentObject Parent object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setParent(_OBJECT parentObject);

public:

	/**
	 * Get physics.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Physics object.</p>
	 */
	_OBJECT getPhysics() const;

protected:

	/**
	 * Set physics.
	 *
	 * @param physicsObject Physics object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setPhysics(_OBJECT physicsObject);

public:

	/**
	 * Get renderable.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Renderable object.</p>
	 */
	_OBJECT getRenderable() const;

protected:

	/**
	 * Set renderable.
	 *
	 * @param renderableObject Renderable object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setRenderable(_OBJECT renderableObject);

public:

	/**
	 * Get parent.
	 *
	 * @param object Object.
	 * @return
	 *     <p>Top parent.</p>
	 */
	static _OBJECT getTopParent(_OBJECT object);

};

///////////////////////////////////////////////////////////////////////////////
#endif //_RELATION_ATTRIBUTE_H
