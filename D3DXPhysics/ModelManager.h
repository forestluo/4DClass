///////////////////////////////////////////////////////////////////////////////
//
// ModelManager.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _MODEL_MANAGER_H_
#define _MODEL_MANAGER_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "WorldGroup.h"
#include "PrimitiveObject.h"
#include "ResourceManager.h"
#include "RenderableManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// ModelManager
//
///////////////////////////////////////////////////////////////////////////////

class CModelManager :
	public virtual CWorldGroup
{
public:
	CModelManager(void);
	virtual ~CModelManager(void);

public:

	/**
	 * Create model.
	 *
	 * @param resourceManager Resource manager.
	 * @param name Name of resource.
	 * @return
	 *     <p>Primitive object.</p>
	 */
	CPrimitiveObject* createModel(CResourceManager* resourceManager,
									const CNormalString& name);

public:

	/**
	 * Create model.
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
	CPrimitiveObject* createModel(CResourceManager* resourceManager,
									_INTEGER type,_FLOAT mass = 0.0f,
									const C4DVector3& scaling = C4DVector3(1.0f,1.0f,1.0f),
									const C4DVector3& rotation = C4DVector3(0.0f,0.0f,0.0f),
									const C4DVector3& position = C4DVector3(0.0f,0.0f,0.0f));

public:

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
#endif //_MODEL_MANAGER_H_
