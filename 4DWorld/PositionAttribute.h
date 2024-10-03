///////////////////////////////////////////////////////////////////////////////
//
// PositionAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _POSITION_ATTRIBUTE_H_
#define _POSITION_ATTRIBUTE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DVector3.h"
#include "4DQuaternion.h"

///////////////////////////////////////////////////////////////////////////////
//
// PositionAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CPositionAttribute
{
private:

	/**
	 * Scale.
	 */
	C4DVector3 scale;
	/**
	 * Position
	 */
	C4DVector3	position;
	/**
	 * Rotation
	 */
	C4DQuaternion rotation;

public:
	CPositionAttribute(void);
	CPositionAttribute(const CPositionAttribute& attribute);
	virtual ~CPositionAttribute(void);

	CPositionAttribute& operator = (const CPositionAttribute& attribute);

public:

	/**
	 * Copy position.
	 *
	 * @param attribute Position attribute.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void copyPosition(const CPositionAttribute& attribute);

public:

	/**
	 * Get scale.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Scale of object.</p>
	 */
	const C4DVector3& getScale() const;
	/**
	 * Set scale.
	 *
	 * @param scale Scale of object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setScale(const C4DVector3& scale);
	/**
	 * Set scale.
	 *
	 * @param sx X scale.
	 * @param sy Y scale.
	 * @param sz Z scale.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setScale(_FLOAT sx,_FLOAT sy,_FLOAT sz);

	/**
	 * Get position.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Position of object.</p>
	 */
	const C4DVector3& getPosition() const;
	/**
	 * Set position.
	 *
	 * @param position Vector of position.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setPosition(const C4DVector3& position);
	/**
	 * Set position.
	 *
	 * @param tx X position.
	 * @param ty Y position.
	 * @param tz Z position.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setPosition(_FLOAT tx,_FLOAT ty,_FLOAT tz);

	/**
	 * Get rotation.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Rotation of object.</p>
	 */
	const C4DQuaternion& getRotation() const;
	/**
	 * Set rotation.
	 *
	 * @param rotation Rotation of object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setRotation(const C4DQuaternion& rotation);

public:

	/**
	 * Get eular rotation.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Eular rotation.</p>
	 */
	C4DVector3 getEularRotation() const;
	/**
	 * Set eular rotation.
	 *
	 * @param rx X rotation.
	 * @param ry Y rotation.
	 * @param rz Z rotation.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setEularRotation(_FLOAT rx,_FLOAT ry,_FLOAT rz);
};

////////////////////////////////////////////////////////////////////////////////
#endif //_POSITION_ATTRIBUTE_H_
