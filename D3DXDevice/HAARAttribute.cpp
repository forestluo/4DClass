///////////////////////////////////////////////////////////////////////////////
//
// HAARAttribute.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "HAARAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "cv.h"
#include "highgui.h"

#include "SDKmisc.h"
#include "NormalString.h"

///////////////////////////////////////////////////////////////////////////////
//
// CHAARAttribute
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CHAARAttribute::CHAARAttribute()
{
	//Set view matrix.
	viewMatrix.identity();
	//Rotate matrix.
	viewMatrix.xRotate(- D3DX_PI / 2.0f);
	//Set translation radius.
	controlBall.SetTranslationRadius(1.0f);
	//Set default value.
	firstTime = _TRUE;
	detectFace = _FALSE;
	faceCenter[0] = faceCenter[1] = 0;
	workingImage = (IplImage *)_NULL;
	convertedImage = (IplImage *)_NULL;
	memoryStorage = (CvMemStorage *)_NULL;
	haarClassifierCascade = (CvHaarClassifierCascade *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CHAARAttribute
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CHAARAttribute::~CHAARAttribute(void)
{
	//Disable detection.
	disableDetection();
}

///////////////////////////////////////////////////////////////////////////////
//
// IsDetecting
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CHAARAttribute::isDetecting()
{
	//Value.
	_BOOL detectFace;
	//Open lock.
	openLock();
	{
		//Get value.
		detectFace = this->detectFace;
	}
	//Close lock.
	closeLock();
	//Return result.
	return detectFace;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetBallRotation
//
///////////////////////////////////////////////////////////////////////////////

C4DQuaternion CHAARAttribute::getBallRotation()
{
	//Rotation.
	C4DQuaternion rotation;
	//Open lock.
	openLock();
	{
		//Get rotation.
		rotation = C4DQuaternion(*controlBall.GetQuatNow());
	}
	//Close lock.
	closeLock();
	//Rotation.
	return rotation;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetFaceCenter
//
///////////////////////////////////////////////////////////////////////////////

void CHAARAttribute::getFaceCenter(_INTEGER& x,_INTEGER& y)
{
	//Open lock.
	openLock();
	{
		//Set coordination.
		x = faceCenter[0], y = faceCenter[1];
	}
	//Close lock.
	closeLock();
}

///////////////////////////////////////////////////////////////////////////////
//
// DisableDetection
//
///////////////////////////////////////////////////////////////////////////////

void CHAARAttribute::disableDetection()
{
	//Open lock.
	openLock();
	{
		//End.
		controlBall.OnEnd();
		//Set value.
		this->detectFace = _FALSE;
		//Check working image.
		if(workingImage != _NULL)
		{
			//Destroy the allocated OpenCV image.
			cvReleaseImage((IplImage **)&workingImage);
			//Clear working image.
			workingImage = (IplImage *)_NULL;
		}
		//Check converted image.
		if(convertedImage != _NULL)
		{
			//Destroy the allocated OpenCV image.
			cvReleaseImage((IplImage **)&convertedImage);
			//Clear converted image.
			convertedImage = (IplImage *)_NULL;
		}
		//Check memory storage.
		if(memoryStorage != _NULL)
		{
			//Release memory storage.
			cvReleaseMemStorage((CvMemStorage **)&memoryStorage);
			//Clear memory storage.
			memoryStorage = (CvMemStorage *)_NULL;
		}
		//Check cascade.
		if(haarClassifierCascade != _NULL)
		{
			//Release classifier cascade.
			cvReleaseHaarClassifierCascade((CvHaarClassifierCascade **)&haarClassifierCascade);
			//Clear classifier cascade.
			haarClassifierCascade = (CvHaarClassifierCascade *)_NULL;
		}
	}
	//Close lock.
	closeLock();
}

///////////////////////////////////////////////////////////////////////////////
//
// DoDetection
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CHAARAttribute::doDetection(_OBJECT inputImage)
{
#ifdef _DEBUG
	assert(inputImage != _NULL);
#endif
#ifdef _DEBUG
	assert(detectFace != _FALSE);
	assert(workingImage != _NULL);
	assert(memoryStorage != _NULL);
	assert(convertedImage != _NULL);
	assert(haarClassifierCascade != _NULL);
#endif
	//Get the max area.
	_INTEGER x, y, maxArea = 0;
	//Open lock.
	openLock();
	{
		//Convert image.
		cvConvertImage((IplImage *)inputImage,(IplImage *)convertedImage);
		//Smooth down the image.
		cvPyrDown((IplImage *)convertedImage,(IplImage *)workingImage,CV_GAUSSIAN_5x5);
		//Clear memory storage.
		cvClearMemStorage((CvMemStorage *)memoryStorage);
		//Detect objects.
		CvSeq* faces = cvHaarDetectObjects((IplImage *)workingImage,
			(CvHaarClassifierCascade *)haarClassifierCascade,
			(CvMemStorage *)memoryStorage,1.2,2,CV_HAAR_DO_CANNY_PRUNING);
		//Draw faces.
		for(_INTEGER i = 0;i < faces->total;i ++)
		{
			//Point.
			CvPoint pt1, pt2;
			//Rect.
			CvRect* r = (CvRect *)cvGetSeqElem(faces,i);
			//Set rectangle.
			pt1.x = r->x * 2;
			pt2.x = (r->x + r->width) * 2;
			pt1.y = r->y * 2;
			pt2.y = (r->y + r->height) * 2;
			//Check result.
			_INTEGER area = r->width * r->height;
			//Check result.
			if(area > maxArea) {x = r->x; y = r->y; maxArea = area;}
			//Draw rectangle.
			cvRectangle((IplImage *)inputImage,pt1,pt2,CV_RGB(255,0,0),3);
		}
		//Check max area.
		if(maxArea > 0) faceCenter[0] = x, faceCenter[1] = y;
	}
	//Close lock.
	closeLock();
	//Return result.
	return maxArea > 0;
}

///////////////////////////////////////////////////////////////////////////////
//
// RotateViewPort
//
///////////////////////////////////////////////////////////////////////////////

void CHAARAttribute::rotateViewPort(CViewPort* viewPort)
{
#ifdef _DEBUG
	assert(viewPort != _NULL);
#endif
	//Open lock.
	openLock();
	{
		//Matrix.
		D3DXMATRIXA16 inverseMatrix(viewMatrix);
		//Check first time.
		if(firstTime)
		{
			//Clear first time.
			firstTime = _FALSE;
			//Get eye look at.
			eyeLookAt = viewPort->getEyeLookAt();
			//On begin.
			controlBall.OnBegin(faceCenter[0],faceCenter[1],&inverseMatrix);
		}
		//On move.
		controlBall.OnMove(faceCenter[0],faceCenter[1],&inverseMatrix);
		//Get rotation.
		C4DQuaternion rotation(*controlBall.GetQuatNow());
		//Rotate vector.
		C4DVector3 vector = rotation.rotate(eyeLookAt - viewPort->getEyeAt());
		//Set view parameters.
		viewPort->setViewParameters(viewPort->getEyeAt(),viewPort->getEyeAt() + vector);
	}
	//Close lock.
	closeLock();
}

///////////////////////////////////////////////////////////////////////////////
//
// EnableDetection
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CHAARAttribute::enableDetection(_INTEGER width,_INTEGER height)
{
#ifdef _DEBUG
	//Check current status.
	assert(this->detectFace == _FALSE);
#endif

	//Path.
	WCHAR wszPath[MAX_PATH];
	//Find media file.
	if(FAILED(DXUTFindDXSDKMediaFileCch(wszPath,MAX_PATH,L"Misc\\Data\\haarcascades\\haarcascade_frontalface_default.xml"))) return _FALSE;

	//ANSI path.
	CHAR ansiPath[2 * MAX_PATH];
	//Clear path.
	memset(ansiPath,0,2 * MAX_PATH);

	//Normal string.
	CNormalString filePath(wszPath);
	//Get ANSI string.
	_INTEGER size = filePath.getAnsiString(ansiPath,2 * MAX_PATH);
#ifdef _DEBUG
	assert(size > 0 && size <= filePath.length());
#endif

	//Result.
	_BOOL resultFlag = _FALSE;
	//Open lock.
	openLock();
	{
		//Load HAAR classifier cascade.
		haarClassifierCascade = cvLoadHaarClassifierCascade(ansiPath,cvSize(24,24));
		//Check result.
		if(haarClassifierCascade != _NULL)
		{
			//Create memory storage.
			memoryStorage = cvCreateMemStorage(0);
			//Check result.
			if(memoryStorage != _NULL)
			{
				//Create converted image.
				convertedImage = cvCreateImage(cvSize(width,height),IPL_DEPTH_8U,3);
				//Check result.
				if(convertedImage != _NULL)
				{
					//Create working image.
					workingImage = cvCreateImage(cvSize(width >> 1,height >> 1),IPL_DEPTH_8U,3);
					//Check result.
					if(workingImage != _NULL)
					{
						//Set window.
						controlBall.SetWindow(width,height);
						//Reset status.
						this->firstTime = _TRUE; this->detectFace = _TRUE; resultFlag = _TRUE;
					}
					//Release and clear image.
					if(!resultFlag) {cvReleaseImage((IplImage **)&convertedImage); convertedImage = (IplImage *)_NULL;}
				}
				//Release and clear memory storage.
				if(!resultFlag) {cvReleaseMemStorage((CvMemStorage **)&memoryStorage); memoryStorage = (CvMemStorage *)_NULL;}
			}
			//Release and clear classifier cascade.
			if(!resultFlag) {cvReleaseHaarClassifierCascade((CvHaarClassifierCascade **)&haarClassifierCascade); haarClassifierCascade = (CvHaarClassifierCascade *)_NULL;}
		}
	}
	//Close lock.
	closeLock();
	//Return result.
	return resultFlag;
}
