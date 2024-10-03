///////////////////////////////////////////////////////////////////////////////
//
// DetectAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _DETECT_ATTRIBUTE_H_
#define _DETECT_ATTRIBUTE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DLock.h"
#include "4DVector3.h"
#include "4DMatrix4.h"

#include "ViewPort.h"
#include "D3DXObject.h"
#include "ControlBall.h"

///////////////////////////////////////////////////////////////////////////////
//
// DetectAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CDetectAttribute : private C4DLock
{
private:

	/** 
	 * Whether detect face.
	 */
	_BOOL detectFace;

private:

	/** 
	 * First time.
	 */
	_BOOL firstTime;
	/** 
	 * Center of face.
	 */
	_INTEGER faceCenter[2];

	/**
	 * Eye look at.
	 */
	C4DVector3 eyeLookAt;
	/** 
	 * View matrix.
	 */
	C4DMatrix4 viewMatrix;
	/** 
	 * Control ball.
	 */
	CControlBall controlBall;

private:

	/**
	 * Working image.
	 */
	_OBJECT workingImage;
	/** 
	 * Converted image.
	 */
	_OBJECT convertedImage;
	/** 
	 * Memory storage.
	 */
	_OBJECT memoryStorage;
	/** 
	 * HAAR classifier cascade.
	 */
	_OBJECT haarClassifierCascade;

public:
	CDetectAttribute(void);
	virtual ~CDetectAttribute(void);

public:

	/** 
	 * Whether detecting.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if detection is running.</p>
	 */
	_BOOL isDetecting();

	/**
	 * Rotation.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Rotation of control ball.</p>
	 */
	C4DQuaternion getBallRotation() const;

	/**
	 * Center position.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Center position of object.</p>
	 */
	void getFaceCenter(_INTEGER& x,_INTEGER& y) const;

public:

	/** 
	 * Disable detection.
	 *
	 * @param None No parameters needed.</p>
	 * @return
	 *     <p>No results returned.</p>
	 */
	void disableDetection();

	/**
	 * Do detection.
	 *
	 * @param captureImage Capture image.
	 * @return
	 *     <p>No results returned.</p>
	 */
	_BOOL doDetection(_OBJECT captureImage);

	/** 
	 * Rotate view port.
	 *
	 * @param viewPort View port.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void rotateViewPort(CViewPort* viewPort);

protected:

	/**
	 * Enable detection.
	 *
	 * @param None No parameters needed.</p>
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL enableDetection(_INTEGER width,_INTEGER height);

};

///////////////////////////////////////////////////////////////////////////////
#endif //_DETECT_ATTRIBUTE_H_