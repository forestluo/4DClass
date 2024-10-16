/////////////////////////////////////////////////////////////////////////////
// Name:        dRootNodeInfo.h
// Purpose:     
// Author:      Julio Jerez
// Modified by: 
// Created:     22/05/2010 08:02:08
// RCS-ID:      
// Copyright:   Copyright (c) <2010> <Newton Game Dynamics>
// License:     
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely
/////////////////////////////////////////////////////////////////////////////

#ifndef _D_ROOT_NODE_H_
#define _D_ROOT_NODE_H_

#include "dNodeInfo.h"


class dRootNodeInfo: public dNodeInfo
{
	public:
	D_DEFINE_CLASS_NODE(dRootNodeInfo,dNodeInfo)

	dRootNodeInfo();
	dRootNodeInfo(dScene* world);
	virtual ~dRootNodeInfo(void);

	virtual void SerializeBinary (FILE* file);
	virtual void Serialize (TiXmlElement* rootNode) const; 
	virtual bool Deserialize (TiXmlElement* rootNode, int revisionNumber);
};

#endif