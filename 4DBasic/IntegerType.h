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
//ȫ��ͨ�����Ͷ���
//
////////////////////////////////////////////////////////////////////////////////

//�з�������
//8λ����
typedef char                                                _INT8;
//16λ����
typedef short                                               _INT16;
//32λ����
typedef int                                                 _INT32;
//64λ����
typedef __int64                                             _INT64;

//�޷�������
//8λ����
typedef unsigned char                                       _UINT8;
//16λ����
typedef unsigned short                                      _UINT16;
//32λ����
typedef unsigned int                                        _UINT32;
//64λ����
typedef unsigned __int64                                    _UINT64;

////////////////////////////////////////////////////////////////////////////////
//
//ȫ�ֳ������Ͷ���
//
////////////////////////////////////////////////////////////////////////////////

//�ֽ�
typedef _INT8												_BYTE;
//������
typedef _INT16												_SHORT;
//����
typedef _INT32												_INTEGER;
//������
typedef _INT64												_LONG;

//����������
typedef _SHORT												_SHORT2[2];
typedef _SHORT												_SHORT3[3];
typedef _SHORT												_SHORT4[4];

//��������
typedef _INTEGER											_INTEGER2[2];
typedef _INTEGER											_INTEGER3[3];
typedef _INTEGER											_INTEGER4[4];

////////////////////////////////////////////////////////////////////////////////
#endif //_INTEGER_TYPE_H_
