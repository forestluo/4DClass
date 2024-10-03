///////////////////////////////////////////////////////////////////////////////
//
// 4DString.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _4D_STRING_H_
#define _4D_STRING_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DType.h"

///////////////////////////////////////////////////////////////////////////////
//
// 4DString
//
///////////////////////////////////////////////////////////////////////////////

class C4DString
{
private:
	//Value.
	_OBJECT value;

public:
	C4DString(void);
	C4DString(const _STRING string);
	C4DString(const C4DString& string);
	virtual ~C4DString(void);

	C4DString& operator = (const C4DString& string);

	_BOOL operator == (const C4DString& string) const;
	_BOOL operator != (const C4DString& string) const;

public:

	/**
	 * Get length of string.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Length of string.</p>
	 */
	_INTEGER length() const;

	/**
	 * Get C-style string.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Pointer of string.</p>
	 */
	const _STRING getCString() const;

	/**
	 * Get ANSI string.
	 *
	 * @param buffer Byte buffer.
	 * @param maxSize Max size.
	 * @return
	 *     <p>Size of converted.</p>
	 */
	_INTEGER getAnsiString(_BYTE* buffer,_INTEGER maxSize) const;

public:

	/**
	 * New tab.
	 *
	 * <p>增加一个换行回车符号。</p>
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>This buffer.</p>
	 */
	C4DString* tab();

	/**
	 * New blank space.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>This buffer.</p>
	 */
	C4DString* skip();

	/**
	 * New line.
	 *
	 * <p>增加一个换行回车符号。</p>
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>This buffer.</p>
	 */
	C4DString* line();

	/**
	 * Append.
	 *
	 * @value byteValue Byte value.
	 * @return
	 *     <p>This object.</p>
	 */
	C4DString* append(_BYTE byteValue);

	/**
	 * Append.
	 *
	 * @value shortValue Short value.
	 * @return
	 *     <p>This object.</p>
	 */
	C4DString* append(_SHORT shortValue);

	/**
	 * Append.
	 *
	 * @value integerValue Integer value.
	 * @return
	 *     <p>This object.</p>
	 */
	C4DString* append(_INTEGER integerValue);

	/**
	 * Append.
	 *
	 * @value booleanValue Boolean value.
	 * @return
	 *     <p>This object.</p>
	 */
	C4DString* append(_BOOL booleanValue);

	/**
	 * Append.
	 *
	 * @value charValue Characater value.
	 * @return
	 *     <p>This object.</p>
	 */
	C4DString* append(_CHAR charValue);

	/**
	 * Append.
	 *
	 * @value longValue Long value.
	 * @return
	 *     <p>This object.</p>
	 */
	C4DString* append(_LONG longValue);

	/**
	 * Append.
	 *
	 * @value floatValue Float value.
	 * @return
	 *     <p>This object.</p>
	 */
	C4DString* append(_FLOAT floatValue);

	/**
	 * Append.
	 *
	 * @value stringValue String value.
	 * @return
	 *     <p>This object.</p>
	 */
	C4DString* append(_STRING stringValue);

	/**
	 * Append.
	 *
	 * @value string String value.
	 * @return
	 *     <p>This object.</p>
	 */
	C4DString* append(C4DString* string);

	/**
	 * Whether equals.
	 *
	 * @param string String value.
	 * @return
	 *     <p>Return true, if they are equal.</p>
	 */
	_BOOL equals(C4DString* string) const;

	/**
	 * Clear all of string.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void clearAll();

	/**
	 * Recycle.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>String value.</p>
	 */
	virtual void recycle() = 0;

public:

	/**
	 * Get hash code.
	 *
	 * @param value String value.
	 * @return
	 *     <p>Hash code of string.</p>
	 */
	static _LONG hashCode(const _STRING string);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_4D_STRING_H_
