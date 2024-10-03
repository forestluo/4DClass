///////////////////////////////////////////////////////////////////////////////
//
// IdentityAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _IDENTITY_ATTRIBUTE_H_
#define _IDENTITY_ATTRIBUTE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "NormalString.h"

///////////////////////////////////////////////////////////////////////////////
//
// IdentityAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CIdentityAttribute
{
private:
	/**
	 * Numer of object.
	 */
	static _INTEGER objectNumber;

private:
	/**
	 * ID of object.
	 */
	_INTEGER objectID;
	/**
	 * Alias.
	 */
	CNormalString alias;

public:
	CIdentityAttribute(void);
	virtual ~CIdentityAttribute(void);

public:

	/**
	 * Get id of object.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>ID of object.</p>
	 */
	_INTEGER getID() const;
	
	/**
	 * Get alias.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Alias of object.</p>
	 */
	const CNormalString& getAlias() const;
	/**
	 * Set alias.
	 *
	 * @param wsAlias Alias of object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setAlias(const CNormalString& alias);
	/**
	 * Set alias.
	 *
	 * @param wsPrefix Prefix of alias.
	 * @param wsSuffix Suffix of alias.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setAlias(const CNormalString& prefix,const CNormalString& suffix);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_IDENTITY_ATTRIBUTE_H_
