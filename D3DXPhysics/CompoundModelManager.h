///////////////////////////////////////////////////////////////////////////////
//
// CompoundModelManager.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _COMPOUND_MODEL_MANAGER_H_
#define _COMPOUND_MODEL_MANAGER_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "WorldGroup.h"
#include "CompoundObject.h"
#include "ResourceApplication.h"

///////////////////////////////////////////////////////////////////////////////
//
// CompoundModelManager
//
///////////////////////////////////////////////////////////////////////////////

class CCompoundModelManager :
	public virtual CWorldGroup
{
public:
	CCompoundModelManager(void);
	virtual ~CCompoundModelManager(void);

public:

	/**
	 * Add compound.
	 *
	 * @param resourceApplication Resource application.
	 * @param object Compound object.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL addCompound(CResourceApplication* resourceApplication,
						CCompoundObject* object);

	/**
	 * Create compound.
	 *
	 * @param resourceApplication Resource application.
	 * @param classCode Class code of compound object.
	 * @param mass Mass of compound.
	 * @param scaling Scaling of model.
	 * @param rotation Rotation of slice.
	 * @param position Position of model.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	CCompoundObject* createCompound(CResourceApplication* resourceApplication,
									_LONG classCode,_FLOAT mass = 0.0f,
									const C4DVector3& scaling = C4DVector3(1.0f,1.0f,1.0f),
									const C4DVector3& rotation = C4DVector3(0.0f,0.0f,0.0f),
									const C4DVector3& position = C4DVector3(0.0f,0.0f,0.0f));

};

///////////////////////////////////////////////////////////////////////////////
#endif //_COMPOUND_MODEL_MANAGER_H_
