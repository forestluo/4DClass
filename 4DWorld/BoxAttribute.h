///////////////////////////////////////////////////////////////////////////////
//
// BoxAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _BOX_ATTRIBUTE_H_
#define _BOX_ATTRIBUTE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "SimpleBox.h"
#include "SimpleSphere.h"

///////////////////////////////////////////////////////////////////////////////
//
// BoxAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CBoxAttribute
{
private:
	/**
	 * Box.
	 */
	CSimpleBox box;
	/**
	 * Sphere.
	 */
	CSimpleSphere sphere;

public:
	CBoxAttribute(void);
	CBoxAttribute(const CBoxAttribute& attribute);
	virtual ~CBoxAttribute(void);

	CBoxAttribute& operator = (const CBoxAttribute& attribute);

public:

	/**
	 * Copy box.
	 *
	 * @param attribute Box attribute.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void copyBox(const CBoxAttribute& attribute);

public:

	/**
	 * Set box.
	 *
	 * @param box Box.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void setBox(const CSimpleBox& box);
	/**
	 * Set sphere.
	 *
	 * @param sphere Sphere.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void setSphere(const CSimpleSphere& sphere);

public:

	/**
	 * Get box.
	 *
	 * @param box Box.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	virtual _BOOL getBox(CSimpleBox& box) const;
	/**
	 * Get sphere.
	 *
	 * @param sphere Sphere.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	virtual _BOOL getSphere(CSimpleSphere& sphere) const;
};

///////////////////////////////////////////////////////////////////////////////
#endif //_BOX_ATTRIBUTE_H_
