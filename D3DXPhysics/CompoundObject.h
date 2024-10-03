///////////////////////////////////////////////////////////////////////////////
//
// CompoundObject.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _COMPOUND_OBJECT_H_
#define _COMPOUND_OBJECT_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "PrimitiveObject.h"

#include "D3DXCompoundObject.h"
#include "PhysicsCompoundObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// CompoundObject
//
///////////////////////////////////////////////////////////////////////////////

class CCompoundObject :
	public CD3DXCompoundObject,
	public CPhysicsCompoundObject
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
	CCompoundObject(void);
	virtual ~CCompoundObject(void);

protected:

	/**
	 * Add model.
	 *
	 * @param resourceManager Resource manager.
	 * @param type Type of primitive.
	 * @param mass Mass of model.
	 * @param scaling Scaling of model.
	 * @param rotation Rotation of slice.
	 * @param position Position of model.
	 * @return
	 *     <p>No results returned.</p>
	 */
	CPrimitiveObject* addModel(CResourceManager* resourceManager,
								_INTEGER type,_FLOAT mass = 0.0f,
								const C4DVector3& scaling = C4DVector3(1.0f,1.0f,1.0f),
								const C4DVector3& rotation = C4DVector3(0.0f,0.0f,0.0f),
								const C4DVector3& position = C4DVector3(0.0f,0.0f,0.0f));

	/**
	 * Create model.
	 *
	 * @param renderableManager Renderable manager.
	 * @param attribute Attribute of primitive.
	 * @param mass Mass of model.
	 * @param scaling Scaling of model.
	 * @param rotation Rotation of slice.
	 * @param position Position of model.
	 * @return
	 *     <p>No results returned.</p>
	 */
	CPrimitiveObject* createModel(CRenderableManager* renderableManager,
								const CPrimitiveAttribute& attribute,_FLOAT mass = 0.0f,
								const C4DVector3& scaling = C4DVector3(1.0f,1.0f,1.0f),
								const C4DVector3& rotation = C4DVector3(0.0f,0.0f,0.0f),
								const C4DVector3& position = C4DVector3(0.0f,0.0f,0.0f));
};

///////////////////////////////////////////////////////////////////////////////
#endif //_COMPOUND_OBJECT_H_
