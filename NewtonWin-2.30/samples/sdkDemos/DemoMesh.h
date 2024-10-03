/* Copyright (c) <2009> <Newton Game Dynamics>
* 
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely
*/


#ifndef _D_MESH_H_
#define _D_MESH_H_


#include "glContext.h"

class DemoSubMesh
{
	public:
	DemoSubMesh ();
	~DemoSubMesh ();

	void AllocIndexData (int indexCount);
	int m_indexCount;
	unsigned *m_indexes;
	unsigned m_textureHandle;

	dFloat m_shiness;
	dVector m_ambient;
	dVector m_diffuse;
	dVector m_specular;
	char m_textureName[D_NAME_STRING_LENGTH];
};


class DemoMesh: public dList<DemoSubMesh>, virtual public dClassInfo  
{
	public:
	DemoMesh(const char* name);
	DemoMesh(const dScene* scene, dScene::dTreeNode* meshNode);
	DemoMesh(const char* name, const NewtonCollision* collision, const char* texture0, const char* texture1, const char* texture2);

	DemoSubMesh* AddSubMesh();
	void AllocVertexData (int vertexCount);

	virtual void GetName (char* nameOut) const;
	virtual void GetTextureName (const DemoSubMesh* subMesh, char* nameOut) const;

	virtual void Render ();

	protected:
	virtual ~DemoMesh();

	dAddRtti(dClassInfo);

	public:
	int m_vertexCount;
	dFloat *m_uv;
	dFloat *m_vertex;
	dFloat *m_normal;
	char m_name[D_NAME_STRING_LENGTH];
};






#endif 

