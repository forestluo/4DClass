///////////////////////////////////////////////////////////////////////////////
//
// PickIntersection.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "PickIntersection.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include <vector>
using std::vector;

///////////////////////////////////////////////////////////////////////////////
//
// Defination
//
///////////////////////////////////////////////////////////////////////////////

// For simplicity's sake, we limit the number of simultaneously intersected 
// triangles to 16
#define MAX_INTERSECTIONS 16

//Pick Intersection Vector
typedef vector<PickIntersection> PickIntersectionVector;
#define PICK_INSTANCE(p) ((PickIntersectionVector *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// CPickIntersection
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CPickIntersection::CPickIntersection(void)
{
	//Create intersections.
	intersections = new PickIntersectionVector();
#ifdef _DEBUG
	assert(intersections != _NULL);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// CPickIntersection
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CPickIntersection::~CPickIntersection(void)
{
	//Check instance.
	if(intersections != _NULL)
	{
		//Clear all elements.
		PICK_INSTANCE(intersections)->clear();
		//Delete instance.
		delete PICK_INSTANCE(intersections);
	}
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetAlias
//
/////////////////////////////////////////////////////////////////////////////////

const CNormalString& CPickIntersection::getAlias() const
{
	//Return alias.
	return alias;
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetAlias
//
/////////////////////////////////////////////////////////////////////////////////

void CPickIntersection::setAlias(const CNormalString& alias)
{
	//Set alias.
	this->alias = alias;
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetNearestDistance
//
/////////////////////////////////////////////////////////////////////////////////

_FLOAT CPickIntersection::getNearestDistance() const
{
#ifdef _DEBUG
	assert(intersections != _NULL);
#endif
	//No intersection, so return an invalid value.
	if(PICK_INSTANCE(intersections)->size() <= 0) return -1.0f;

	//Distance.
	_FLOAT distance;
	//Index.
	_INTEGER index = 0;
	//Do while.
	do
	{
		//Get distance.
		distance = PICK_INSTANCE(intersections)->at(index).fDist;
		//Check distance.
		if(distance > 0.0f) break;

		//Add index.
		index ++;

	}while(index < (_INTEGER)PICK_INSTANCE(intersections)->size());
	//Check result.
	if(distance < 0.0f || index >= (_INTEGER)PICK_INSTANCE(intersections)->size()) return -1.0f;

	//Do while.
	for(_INTEGER i = index + 1;i < (_INTEGER)PICK_INSTANCE(intersections)->size();i ++)
	{
		//Check distance.
		if(distance > PICK_INSTANCE(intersections)->at(i).fDist)
		{
			//Set distance.
			distance = PICK_INSTANCE(intersections)->at(i).fDist;
		}
	}
	//Return value.
	return distance;
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetCount
//
/////////////////////////////////////////////////////////////////////////////////

_INTEGER CPickIntersection::getCount() const
{
#ifdef _DEBUG
	assert(intersections != _NULL);
#endif
	//Return result.
	return PICK_INSTANCE(intersections)->size();
}

/////////////////////////////////////////////////////////////////////////////////
//
// AddIntersection
//
/////////////////////////////////////////////////////////////////////////////////

void CPickIntersection::addIntersection(const PickIntersection& intersection)
{
#ifdef _DEBUG
	assert(intersections != _NULL);
#endif
	//Check result.
	if(PICK_INSTANCE(intersections)->size() < MAX_INTERSECTIONS)
	{
		//Push back.
		PICK_INSTANCE(intersections)->push_back(intersection);
	}
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetIntersection
//
/////////////////////////////////////////////////////////////////////////////////

const PickIntersection& CPickIntersection::getIntersection(_INTEGER index) const
{
#ifdef _DEBUG
	assert(intersections != _NULL);
	assert(index > 0 && index < getCount());
#endif
	//Return result.
	return PICK_INSTANCE(intersections)->at(index);
}
