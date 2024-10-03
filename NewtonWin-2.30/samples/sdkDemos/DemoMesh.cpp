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


// DemoMesh.cpp: implementation of the DemoMesh class.
//
//////////////////////////////////////////////////////////////////////
#include "toolbox_stdafx.h"
#include "DemoMesh.h"
#include "TargaToOpenGl.h"

dInitRtti(DemoMesh);

//#define EXPORT_ASCI_FILE 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
DemoSubMesh::DemoSubMesh ()
{
	m_indexes = NULL;
	m_indexCount = 0;
	m_textureName[0] = 0;
	m_textureHandle = 0;
	m_shiness = 80.0f;
	m_ambient = dVector (0.2f, 0.2f, 0.2f, 1.0f);
	m_diffuse = dVector (0.7f, 0.7f, 0.7f, 1.0f);
	m_specular = dVector (1.0f, 1.0f, 1.0f, 1.0f);
}

DemoSubMesh::~DemoSubMesh ()
{
	if (m_indexes) {
		free (m_indexes);
	}
}

void DemoSubMesh::AllocIndexData (int indexCount)
{
	m_indexCount = indexCount;
	if (m_indexes) {
		free (m_indexes);
	}
	m_indexes = (unsigned *) malloc (m_indexCount * sizeof (unsigned)); 
}



DemoMesh::DemoMesh(const char* name)
	:dList<DemoSubMesh>(), dClassInfo()
{
	m_vertexCount = 0;
	m_uv = NULL;
	m_vertex = NULL;
	m_normal = NULL;
	strcpy (m_name, name);
}

DemoMesh::DemoMesh(const dScene* scene, dScene::dTreeNode* meshNode)
	:dList<DemoSubMesh>(), dClassInfo(), m_uv(NULL), m_vertex(NULL), m_normal(NULL)
{
	dMeshNodeInfo* info = (dMeshNodeInfo*)scene->GetInfoFromNode(meshNode);
	strcpy (m_name, info->GetName());
	
	NewtonMesh* mesh = info->GetMesh();

	// extract vertex data  from the newton mesh		
	AllocVertexData(NewtonMeshGetPointCount (mesh));
	NewtonMeshGetVertexStreams (mesh, 3 * sizeof (dFloat), (dFloat*) m_vertex,
									  3 * sizeof (dFloat), (dFloat*) m_normal,
									  2 * sizeof (dFloat), (dFloat*) m_uv, 
								      2 * sizeof (dFloat), (dFloat*) m_uv);

	// bake the matrix into the vertex array
	dMatrix matrix (info->GetPivotMatrix());
	matrix.TransformTriplex(m_vertex, 3 * sizeof (dFloat), m_vertex, 3 * sizeof (dFloat), m_vertexCount);
	matrix.m_posit = dVector (0.0f, 0.0f, 0.0f, 1.0f);
	matrix = matrix.Inverse4x4() * matrix.Transpose() * matrix;
	matrix.TransformTriplex(m_normal, 3 * sizeof (dFloat), m_normal, 3 * sizeof (dFloat), m_vertexCount);

	dTree<dScene::dTreeNode*, int> materialMap;
	for (void* ptr = scene->GetFirstChild(meshNode); ptr; ptr = scene->GetNextChild (meshNode, ptr)) {
		dScene::dTreeNode* node = scene->GetNodeFromLink(ptr);
		dNodeInfo* info = scene->GetInfoFromNode(node);
		if (info->GetTypeId() == dMaterialNodeInfo::GetRttiType()) {
			dMaterialNodeInfo* material = (dMaterialNodeInfo*)info;
			materialMap.Insert(node, material->GetId());
		}
	}

	// extract the materials index array for mesh
	void* const meshCookie = NewtonMeshBeginHandle (mesh); 
	for (int handle = NewtonMeshFirstMaterial (mesh, meshCookie); handle != -1; handle = NewtonMeshNextMaterial (mesh, meshCookie, handle)) {
		int materialIndex = NewtonMeshMaterialGetMaterial (mesh, meshCookie, handle); 
		int indexCount = NewtonMeshMaterialGetIndexCount (mesh, meshCookie, handle); 
		DemoSubMesh* segment = AddSubMesh();

		dTree<dScene::dTreeNode*, int>::dTreeNode* matNodeCache = materialMap.Find(materialIndex);
		if (matNodeCache) {
			dScene::dTreeNode* matNode = matNodeCache->GetInfo();
			dMaterialNodeInfo* material = (dMaterialNodeInfo*) scene->GetInfoFromNode(matNode);

			if (material->GetDiffuseTextId() != -1) {
				dScene::dTreeNode* node = scene->FindTextureByTextId(matNode, material->GetDiffuseTextId());
				_ASSERTE (node);
				dTextureNodeInfo* texture = (dTextureNodeInfo*)scene->GetInfoFromNode(node);

				segment->m_textureHandle = LoadTexture(texture->GetPathName());
				strcpy (segment->m_textureName, texture->GetPathName());
			}
			segment->m_shiness = material->GetShininess();
			segment->m_ambient = material->GetAmbientColor();
			segment->m_diffuse = material->GetDiffuseColor();
			segment->m_specular = material->GetSpecularColor();
		}

		segment->AllocIndexData (indexCount);
		// for 16 bit indices meshes
		//NewtonMeshMaterialGetIndexStreamShort (mesh, meshCookie, handle, (short int*)segment->m_indexes); 

		// for 32 bit indices mesh
		NewtonMeshMaterialGetIndexStream (mesh, meshCookie, handle, (int*)segment->m_indexes); 
	}
	NewtonMeshEndHandle (mesh, meshCookie); 
}



DemoMesh::DemoMesh(const char* name, const NewtonCollision* collision, const char* texture0, const char* texture1, const char* texture2)
	:dList<DemoSubMesh>(), dClassInfo(), m_uv(NULL), m_vertex(NULL), m_normal(NULL)
{
	// create a helper mesh from the collision collision
	NewtonMesh* const mesh = NewtonMeshCreateFromCollision(collision);

	// apply the vertex normals
	NewtonMeshCalculateVertexNormals(mesh, 30.0f * 3.141592f/180.0f);

	// apply uv projections
	NewtonCollisionInfoRecord info;
	NewtonCollisionGetInfo (collision, &info);
	switch (info.m_collisionType) 
	{
		case SERIALIZE_ID_SPHERE:
		{
			NewtonMeshApplySphericalMapping(mesh, LoadTexture (texture0));
			break;
		}

		case SERIALIZE_ID_CONE:
		case SERIALIZE_ID_CYLINDER:
		{
			NewtonMeshApplyCylindricalMapping(mesh, LoadTexture(texture0), LoadTexture(texture1));
			break;
		}

		case SERIALIZE_ID_CAPSULE:
		case SERIALIZE_ID_CHAMFERCYLINDER:
		{
			NewtonMeshApplySphericalMapping(mesh, LoadTexture(texture0));
			break;
		}

		default:
		{
			int tex0;
			int tex1;
			int tex2;

			tex0 = LoadTexture(texture0);
			tex1 = LoadTexture(texture1);
			tex2 = LoadTexture(texture2);
			NewtonMeshApplyBoxMapping(mesh, tex0, tex1, tex2);
			break;
		}
	}


	// extract vertex data  from the newton mesh		
	int vertexCount = NewtonMeshGetPointCount (mesh); 
	AllocVertexData(vertexCount);
	NewtonMeshGetVertexStreams (mesh, 
								3 * sizeof (dFloat), (dFloat*) m_vertex,
								3 * sizeof (dFloat), (dFloat*) m_normal,
								2 * sizeof (dFloat), (dFloat*) m_uv, 
								2 * sizeof (dFloat), (dFloat*) m_uv);

	// extract the materials index array for mesh
	void* const geometryHandle = NewtonMeshBeginHandle (mesh); 
	for (int handle = NewtonMeshFirstMaterial (mesh, geometryHandle); handle != -1; handle = NewtonMeshNextMaterial (mesh, geometryHandle, handle)) {
		int material = NewtonMeshMaterialGetMaterial (mesh, geometryHandle, handle); 
		int indexCount = NewtonMeshMaterialGetIndexCount (mesh, geometryHandle, handle); 

		DemoSubMesh* const segment = AddSubMesh();

		segment->m_textureHandle = (GLuint)material;

		segment->AllocIndexData (indexCount);
		NewtonMeshMaterialGetIndexStream (mesh, geometryHandle, handle, (int*)segment->m_indexes); 
	}
	NewtonMeshEndHandle (mesh, geometryHandle); 

	// destroy helper mesh
	NewtonMeshDestroy(mesh);

	// optimize this mesh for hardware buffers if possible
//	OptimizeForRender ();
}




DemoMesh::~DemoMesh()
{
	if (m_vertex) {
		free (m_vertex);
		free (m_normal);
		free (m_uv);
	}
}

void DemoMesh::GetName (char* nameOut) const
{
	strcpy (nameOut, m_name);
}


void DemoMesh::GetTextureName (const DemoSubMesh* subMesh, char* nameOut) const
{
	strcpy (nameOut, subMesh->m_textureName);
}


void DemoMesh::AllocVertexData (int vertexCount)
{
	m_vertexCount = vertexCount;

	m_vertex = (dFloat*) malloc (3 * m_vertexCount * sizeof (dFloat)); 
	m_normal = (dFloat*) malloc (3 * m_vertexCount * sizeof (dFloat)); 
	m_uv = (dFloat*) malloc (2 * m_vertexCount * sizeof (dFloat)); 
	memset (m_uv, 0, 2 * m_vertexCount * sizeof (dFloat));
}

DemoSubMesh* DemoMesh::AddSubMesh()
{
	return &Append()->GetInfo();
}


void DemoMesh::Render ()
{
	glEnableClientState (GL_VERTEX_ARRAY);
	glEnableClientState (GL_NORMAL_ARRAY);
	glEnableClientState (GL_TEXTURE_COORD_ARRAY);

	glVertexPointer (3, GL_FLOAT, 0, m_vertex);
	glNormalPointer (GL_FLOAT, 0, m_normal);
	glTexCoordPointer (2, GL_FLOAT, 0, m_uv);

	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	for (dListNode* nodes = GetFirst(); nodes; nodes = nodes->GetNext()) {
		DemoSubMesh& segment = nodes->GetInfo();

		glMaterialfv(GL_FRONT, GL_SPECULAR, &segment.m_specular.m_x);
		glMaterialfv(GL_FRONT, GL_AMBIENT, &segment.m_ambient.m_x);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, &segment.m_diffuse.m_x);
		glMaterialf(GL_FRONT, GL_SHININESS, segment.m_shiness);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		if (segment.m_textureHandle) {
			glEnable(GL_TEXTURE_2D);		
			glBindTexture(GL_TEXTURE_2D, GLuint (segment.m_textureHandle));
		} else {
			glDisable(GL_TEXTURE_2D);
		}

		glDrawElements (GL_TRIANGLES, segment.m_indexCount, GL_UNSIGNED_INT, segment.m_indexes);
	}
	glDisableClientState(GL_VERTEX_ARRAY);	// disable vertex arrays
	glDisableClientState(GL_NORMAL_ARRAY);	// disable normal arrays
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);	// disable normal arrays
}
