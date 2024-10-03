///////////////////////////////////////////////////////////////////////////////
//
// PickResult.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "PickResult.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include <vector>
using std::vector;

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

//Pick Intersection Vector
typedef vector<CPickIntersection*> CPickIntersectionVector;
#define PICK_INSTANCE(p) ((CPickIntersectionVector *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// CPickResult
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CPickResult::CPickResult(void)
	: pickOrigin(0.0f,0.0f,0.0f)
	, pickDirection(0.0f,0.0f,1.0f)
{
	//Create picks.
	picks = new CPickIntersectionVector();
#ifdef _DEBUG
	assert(picks != _NULL);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// ~CPickResult
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CPickResult::~CPickResult(void)
{
	//Check picks.
	if(picks != _NULL)
	{
		//Release all.
		releaseAll();
		//Delete instance.
		delete PICK_INSTANCE(picks);
	}
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetPickOrigin
//
/////////////////////////////////////////////////////////////////////////////////

const C4DVector3& CPickResult::getPickOrigin() const
{
	//Return result.
	return pickOrigin;
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetPickOrigin
//
/////////////////////////////////////////////////////////////////////////////////

void CPickResult::setPickOrigin(const C4DVector3& pickOrigin)
{
	//Set value.
	this->pickOrigin = pickOrigin;
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetPickDirection
//
/////////////////////////////////////////////////////////////////////////////////

const C4DVector3& CPickResult::getPickDirection() const
{
	//Return result.
	return pickDirection;
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetPickDirection
//
/////////////////////////////////////////////////////////////////////////////////

void CPickResult::setPickDirection(const C4DVector3& pickDirection)
{
	//Set value.
	this->pickDirection = pickDirection;
}

/////////////////////////////////////////////////////////////////////////////////
//
// ReleaseAll
//
/////////////////////////////////////////////////////////////////////////////////

void CPickResult::releaseAll()
{
#ifdef _DEBUG
	assert(picks != _NULL);
#endif
	//Do while.
	for(_INTEGER i = 0;i < (_INTEGER)PICK_INSTANCE(picks)->size();i ++)
	{
		//Get intersection.
		CPickIntersection* intersection = PICK_INSTANCE(picks)->at(i);
#ifdef _DEBUG
		assert(intersection != _NULL);
#endif
		//Delete intersection.
		delete (CPickIntersection *)intersection;
	}
	//Clear members.
	PICK_INSTANCE(picks)->clear();
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetCount
//
/////////////////////////////////////////////////////////////////////////////////

_INTEGER CPickResult::getCount() const
{
	//Return result.
	return PICK_INSTANCE(picks)->size();
}

/////////////////////////////////////////////////////////////////////////////////
//
// AddIntersection
//
/////////////////////////////////////////////////////////////////////////////////

void CPickResult::addIntersection(CPickIntersection* intersection)
{
#ifdef _DEBUG
	assert(picks != _NULL && intersection != _NULL);
#endif
	//Add it into tail.
	PICK_INSTANCE(picks)->push_back(intersection);
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetIntersection
//
/////////////////////////////////////////////////////////////////////////////////

CPickIntersection* CPickResult::getIntersection(_INTEGER index) const
{
#ifdef _DEBUG
	assert(index >= 0 && index < (_INTEGER)PICK_INSTANCE(picks)->size());
#endif
	//Return result.
	return PICK_INSTANCE(picks)->at(index);
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetNearestIntersection
//
/////////////////////////////////////////////////////////////////////////////////

CPickIntersection* CPickResult::getNearestIntersection() const
{
#ifdef _DEBUG
	assert(picks != _NULL);
#endif
	//Check picks.
	if(PICK_INSTANCE(picks)->size() <= 0) return (CPickIntersection *)_NULL;

	//Distance.
	_FLOAT distance;
	//Index.
	_INTEGER index = 0;
	//Do while.
	do
	{
#ifdef _DEBUG
		assert(PICK_INSTANCE(picks)->at(index) != _NULL);
#endif
		//Get distance.
		distance = PICK_INSTANCE(picks)->at(index)->getNearestDistance();
		//Check distance.
		if(distance > 0.0f) break;

		//Add index.
		index ++;

	}while(index < (_INTEGER)PICK_INSTANCE(picks)->size());
	//Check result.
	if(distance < 0.0f || index >= (_INTEGER)PICK_INSTANCE(picks)->size()) return (CPickIntersection *)_NULL;

	//Do while.
	for(_INTEGER i = index + 1;i < (_INTEGER)PICK_INSTANCE(picks)->size();i ++)
	{
		//Get pick intersection.
		CPickIntersection* intersection = PICK_INSTANCE(picks)->at(i);
#ifdef _DEBUG
		assert(intersection != _NULL);
#endif
		_FLOAT value = intersection->getNearestDistance();
		//Check value.
		if(value > 0.0f && distance > value)
		{
			//Set index.
			index = i;
			//Set value.
			distance = value;
		}
	}
	//Return result.
	return PICK_INSTANCE(picks)->at(index);
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetIntersection
//
/////////////////////////////////////////////////////////////////////////////////

CPickIntersection* CPickResult::getIntersection(const CNormalString& alias) const
{
#ifdef _DEBUG
	assert(alias.length() > 0);
#endif
	//Do while.
	for(_INTEGER i = 0;i < (_INTEGER)PICK_INSTANCE(picks)->size();i ++)
	{
		//Get intersection.
		CPickIntersection* intersection = PICK_INSTANCE(picks)->at(i);
#ifdef _DEBUG
		assert(intersection != _NULL);
#endif
		//Check name.
		if(intersection->getAlias() == alias) return intersection;
	}
	//Return null.
	return (CPickIntersection *)_NULL;
}