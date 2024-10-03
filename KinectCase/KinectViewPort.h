///////////////////////////////////////////////////////////////////////////////
//
// KinectViewPort.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _KINECT_VIEW_PORT_H_
#define _KINECT_VIEW_PORT_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ModelViewPort.h"

///////////////////////////////////////////////////////////////////////////////
//
// CKinectViewPort
//
///////////////////////////////////////////////////////////////////////////////

class CKinectViewPort : public CModelViewPort
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
	CKinectViewPort(void);
	virtual ~CKinectViewPort(void);

protected:
	/**
	 * Initialize camera.
	 *
	 * @param camera Camera.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void initializeCamera(_OBJECT pCamera);

};

#define IS_KINECT_VIEWPORT_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CKinectViewPort::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_KINECT_VIEW_PORT_H_
