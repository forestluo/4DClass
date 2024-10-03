///////////////////////////////////////////////////////////////////////////////
//
// PhysicsPrimitiveObject.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PHYSICS_PRIMITIVE_OBJECET_H_
#define _PHYSICS_PRIMITIVE_OBJECET_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsObject.h"
#include "PrimitiveAttribute.h"
#include "RenderableAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// PhysicsPrimitiveObject
//
///////////////////////////////////////////////////////////////////////////////

class CPhysicsPrimitiveObject :
	public CPhysicsObject,
	protected CPrimitiveAttribute
{
public:
	CPhysicsPrimitiveObject(void);
	virtual ~CPhysicsPrimitiveObject(void);

private:

	/**
	 * Copy renderable.
	 *
	 * @param attribute Renderable attribute.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void copyRenderable(const CRenderableAttribute& attribute);

public:

	/**
	 * Get primitive type.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Type of primitive.</p>
	 */
	_INTEGER getPrimitiveType() const;

	/**
	 * Set primitive type.
	 *
	 * @param type Type of primitive.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setPrimitiveType(_INTEGER type);

public:

	/**
	 * Get primitive attribute.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Primitive attribute.</p>
	 */
	const CPrimitiveAttribute& getPrimitiveAttribute() const;

	/**
	 * Set primitive attribute.
	 *
	 * @param attribute Primitive attribute.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setPrimitiveAttribute(const CPrimitiveAttribute& attribute);

public:

	/**
	 * Get index attribute.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Index attribute.</p>
	 */
	void getIndexAttribute(CIndexAttribute& attribute) const;

	/**
	 * Get vertex attribute.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Vertex attribute.</p>
	 */
	void getVertexAttribute(CVertexAttribute& attribute) const;

};

///////////////////////////////////////////////////////////////////////////////
#endif //_PHYSICS_PRIMITIVE_OBJECET_H_
