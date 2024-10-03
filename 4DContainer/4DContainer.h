///////////////////////////////////////////////////////////////////////////////
//
// 4DContainer.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _4D_CONTAINER_H_
#define _4D_CONTAINER_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DType.h"

///////////////////////////////////////////////////////////////////////////////
//
// 4DCointainer
//
///////////////////////////////////////////////////////////////////////////////

class C4DContainer
{
public:
	//Without limit.
	static const _INTEGER WITHOUT_LIMIT;

private:
	/**
	 * Count of object in a container.
	 *
	 * <p>�洢�������еĶ�����Ŀ��</p>
	 */
	_INTEGER count;
	/**
	 * Capacity of a container.
	 *
	 * <p>�����������ɵ���������Ŀ��</p>
	 */
	_INTEGER capacity;

	/**
	 * Size of a container.
	 *
	 * <p>�����Ĵ�Сһ���ó��ض�������ռ�õ�Ԫ����Ŀ��������
	 * ����ֵ����������������Ŀһ�¡�����Щ����£�����ڶ�����Ŀ���������ܳ������ڶ�����Ŀ�������</p>
	 */
	_INTEGER size;

public:
	C4DContainer(void);
	C4DContainer(_INTEGER capacity);
	virtual ~C4DContainer(void);
	
protected:
	/**
	 * Set count of container.
	 *
	 * @param count Count of container.
	 * @return
	 *     <p>Count of container.</p>
	 */
	void setCount(_INTEGER count);

	/**
	 * Increase count of container.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void increaseCount();

	/**
	 * Increase count of container.
	 *
	 * @param count Increased count.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void increaseCount(_INTEGER count);

	/**
	 * Decrease count of container.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void decreaseCount();

	/**
	 * Decrease count of container.
	 *
	 * @param count Decreased count.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void decreaseCount(_INTEGER count);

	/**
	 * Set size of container.
	 *
	 * @param size Size of container.
	 * @return
	 *     <p>Size of container.</p>
	 */
	void setSize(_INTEGER size);

	/**
	 * Increase size of container.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void increaseSize();

	/**
	 * Increase size of container.
	 *
	 * @param size Increased size.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void increaseSize(_INTEGER size);

	/**
	 * Decrease size of container.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void decreaseSize();

	/**
	 * Decrease count of container.
	 *
	 * @param size Decreased size.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void decreaseSize(_INTEGER size);

	/**
	 * Increase size and count of container.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void increaseSizeAndCount();

	/**
	 * Decrease size and count of container.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void decreaseSizeAndCount();

public:

	/**
	 * Get size of container.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Size of container.</p>
	 */
	_INTEGER getSize() const;

	/**
	 * Get count of object.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Count of container.</p>
	 */
	_INTEGER getCount() const;

	/**
	 * Get capacity of container.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Capacity of container.</p>
	 */
	_INTEGER getCapacity() const;

	/**
	 * Set capacity of container.
	 *
	 * @param capacity Capacity of container.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setCapacity(_INTEGER capacity);

	/**
	 * Whether container is empty.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if the count is bigger than zero.</p>
	 */
	_BOOL isEmpty() const;

	/**
	 * Whether container is full.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if the count is bigger than capacity.</p>
	 */
	_BOOL isFull() const;

	/**
	 * Remove all objects from this container.
	 *
	 * <p>���������Ҫ�����ء�</p>
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void clearAll();
};

#endif //_4D_CONTAINER_H_