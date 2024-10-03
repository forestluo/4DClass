///////////////////////////////////////////////////////////////////////////////
//
// IntegerType.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _INTEGER_TYPE_H_
#define _INTEGER_TYPE_H_

////////////////////////////////////////////////////////////////////////////////
//
//全局通用整型定义
//
////////////////////////////////////////////////////////////////////////////////

//有符号整数
//8位整数
typedef char                                                _INT8;
//16位整数
typedef short                                               _INT16;
//32位整数
typedef int                                                 _INT32;
//64位整数
typedef __int64                                             _INT64;

//无符号整数
//8位整数
typedef unsigned char                                       _UINT8;
//16位整数
typedef unsigned short                                      _UINT16;
//32位整数
typedef unsigned int                                        _UINT32;
//64位整数
typedef unsigned __int64                                    _UINT64;

////////////////////////////////////////////////////////////////////////////////
//
//全局常用整型定义
//
////////////////////////////////////////////////////////////////////////////////

//字节
typedef _INT8												_BYTE;
//短整数
typedef _INT16												_SHORT;
//整数
typedef _INT32												_INTEGER;
//长整数
typedef _INT64												_LONG;

//短整数数组
typedef _SHORT												_SHORT2[2];
typedef _SHORT												_SHORT3[3];
typedef _SHORT												_SHORT4[4];

//整数数组
typedef _INTEGER											_INTEGER2[2];
typedef _INTEGER											_INTEGER3[3];
typedef _INTEGER											_INTEGER4[4];

////////////////////////////////////////////////////////////////////////////////
#endif //_INTEGER_TYPE_H_
