///////////////////////////////////////////////////////////////////////////////
//
// HAARAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _HAAR_ATTRIBUTE_H_
#define _HAAR_ATTRIBUTE_H_

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
#include "ControlBall.h"

///////////////////////////////////////////////////////////////////////////////
//
// HAARAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CHAARAttribute :
	protected C4DLock
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
	CHAARAttribute(void);
	virtual ~CHAARAttribute(void);

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
	C4DQuaternion getBallRotation();

	/**
	 * Center position.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Center position of object.</p>
	 */
	void getFaceCenter(_INTEGER& x,_INTEGER& y);

public:

	/** 
	 * Rotate view port.
	 *
	 * @param viewPort View port.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void rotateViewPort(CViewPort* viewPort);

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
	 * @param inputImage Input image.
	 * @return
	 *     <p>Return true, if object was detected.</p>
	 */
	_BOOL doDetection(_OBJECT inputImage);

	/**
	 * Enable detection.
	 *
	 * @param width Width of image.
	 * @param height Height of image.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL enableDetection(_INTEGER width,_INTEGER height);

};

///////////////////////////////////////////////////////////////////////////////
#endif //_HAAR_ATTRIBUTE_H_