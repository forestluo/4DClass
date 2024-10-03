/////////////////////////////////////////////////////////////////////////////
// Name:        alchemediaDoc.cpp
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

// alchemediaDoc.cpp : implementation of the alchemediaDoc class
//

#include "alchemediaStdafx.h"
#include "alchemedia.h"
#include "alchemediaDoc.h"
#include "alchemediaScene.h"
#include "alchemediaMainFrm.h"
#include "alchemediaExplorerView.h"
#include "AlchemdiaSmoothMeshAngleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif






// alchemediaDoc

IMPLEMENT_DYNCREATE(alchemediaDoc, CDocument)

BEGIN_MESSAGE_MAP(alchemediaDoc, CDocument)
	ON_COMMAND(ID_FILE_NEW, &alchemediaDoc::OnFileNew)
	ON_COMMAND(ID_FILE_SAVE, &alchemediaDoc::OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, &alchemediaDoc::OnFileSaveAs)
	ON_COMMAND(ID_FILE_OPEN, &alchemediaDoc::OnFileOpen)
	ON_COMMAND(ID_FILE_MERGE, &alchemediaDoc::OnFileMerge)
	ON_COMMAND(ID_EDIT_UNDO, &alchemediaDoc::OnEditUndo)
	ON_COMMAND(ID_EDIT_REDO, &alchemediaDoc::OnEditRedo)
	ON_COMMAND(ID_TOOLS_POLYGINIZEDSCENE, &alchemediaDoc::OnToolsPolygonizeScene)
	ON_COMMAND(ID_TOOLS_TRIANGULATESCENE, &alchemediaDoc::OnToolsTriangulatescene)
	ON_COMMAND(ID_TOOLS_SMOOTHSCENENORMAL, &alchemediaDoc::OnToolsSmoothscenenormal)
	ON_COMMAND(ID_TOOLS_WELDTJOINTS, &alchemediaDoc::OnToolsWeldtjoints)
END_MESSAGE_MAP()


int alchemediaDoc::m_physicsMemory = 0;
// alchemediaDoc construction/destruction



alchemediaDoc::alchemediaDoc()
	:m_undoLevels(16)
	,m_newton(NULL)
	,m_textureCache()
	,m_mainFrame(NULL)
	,m_explorer(NULL)
	,m_currentWorld(NULL)
	,m_undoRedoWorlds()
{
	// TODO: add one-time construction code here

	m_currentFileName[0] = 0;
	// Set the memory allocation function before creation the world
	// this is the only function that can be called before the creation of the newton world.
	// it should be called once, and the the call is optional 
	NewtonSetMemorySystem (AllocMemory, FreeMemory);

	m_newton = NewtonCreate();


#if 0
dScene xxxx(m_newton);
xxxx.Deserialize ("C:/Newton200/NewtonSDK/samples/bin/tetra_1.xml");
			   
//xxxx.Deserialize ("C:/Newton_200/NewtonSDK/samples/bin/box_0.xml");
//xxxx.Deserialize ("C:/Newton_200/NewtonSDK/samples/bin/box_1.xml");
//xxxx.Deserialize ("C:/Newton_200/NewtonSDK/samples/bin/box_2.xml");
//xxxx.Deserialize ("C:/Newton_200/NewtonSDK/samples/bin/box_3.xml");
//xxxx.Deserialize ("C:/Newton_200/NewtonSDK/samples/bin/prism_1.xml");
//xxxx.Deserialize ("C:/Newton_200/NewtonSDK/samples/bin/test_2.xml");
//xxxx.Deserialize ("C:/Newton_200/NewtonSDK/samples/bin/hedra_0.xml");
//xxxx.Deserialize ("C:/Newton_200/NewtonSDK/samples/bin/dear_1.xml");
//xxxx.Deserialize ("C:/Newton_200/NewtonSDK/samples/bin/dear_2.xml");
//xxxx.Deserialize ("C:/Newton_200/NewtonSDK/samples/bin/jeep_1.xml");
//xxxx.Deserialize ("C:/Newton_200/NewtonSDK/samples/bin/jeep_2.xml");
//xxxx.Deserialize ("C:/Newton_200/NewtonSDK/samples/bin/ogrehead.xml");
//xxxx.Deserialize ("C:/Newton_200/NewtonSDK/samples/bin/lshape_1.xml");
//xxxx.Deserialize ("C:/Newton_200/NewtonSDK/samples/bin/cshape_1.xml");

//xxxx.Deserialize ("C:/temp/CyrusDebugX86/DebugX86/xxxxx/MTL0001.xml");


dScene::dTreeNode* sceneNode = NULL;
for (void* ptr = xxxx.GetFirstChild (xxxx.GetRootNode()); ptr; ptr = xxxx.GetNextChild(xxxx.GetRootNode(), ptr)){
	dScene::dTreeNode* node = xxxx.GetNodeFromLink(ptr);
	dNodeInfo* const info = xxxx.GetInfoFromNode(node);
	if (info->GetTypeId() == dSceneNodeInfo::GetRttiType()) {
		sceneNode = node;
		break;
	}
}

dScene::dTreeNode* meshNode = NULL;
for (void* ptr = xxxx.GetFirstChild (sceneNode); ptr; ptr = xxxx.GetNextChild(sceneNode, ptr)){
	dScene::dTreeNode* node = xxxx.GetNodeFromLink(ptr);
	dNodeInfo* const info = xxxx.GetInfoFromNode(node);
	if (info->GetTypeId() == dMeshNodeInfo::GetRttiType()) {
		meshNode = node;
		break;
	}
}


/*
NewtonMesh* convexAproximation = NewtonMeshConvexApproximation (meshInfo->GetMesh(), 0.5f);
// create a feature mash
//dScene::dTreeNode* convexNode = xxxx.CreateSceneNode(xxxx.GetRootNode());
//dSceneNodeInfo* const convexInfo = (dSceneNodeInfo*) xxxx.GetInfoFromNode(convexNode);
//dSceneNodeInfo* const sceneInfo = (dSceneNodeInfo*) xxxx.GetInfoFromNode(sceneNode);
//convexInfo->SetTransform(sceneInfo->GetTransform());

//dScene::dTreeNode* convexMeshNode = xxxx.CreateMeshNode(convexNode);
//dMeshNodeInfo* const convexMesh = (dMeshNodeInfo*)xxxx.GetInfoFromNode(convexMeshNode);
//convexMesh->ReplaceMesh(convexAproximation);
//convexMesh->SetPivotMatrix ( meshInfo->GetPivotMatrix());
//xxxx.CreateMaterialNode(convexNode, 0);

// make convex pierces
int count = 0;
NewtonMesh* nextSegment = NULL;
for (NewtonMesh* segment = NewtonMeshCreateFirstSingleSegment (convexAproximation); segment; segment = nextSegment) {
	nextSegment = NewtonMeshCreateNextSingleSegment (convexAproximation, segment);

	NewtonCollision* convexHull = NewtonCreateConvexHullFromMesh (m_newton, segment, 0.01f, 0);
	if (convexHull) {
		NewtonMesh* convexHullMesh = NewtonMeshCreateFromCollision(convexHull);
		NewtonReleaseCollision(m_newton, convexHull);

		dScene::dTreeNode* convexNode = xxxx.CreateSceneNode(xxxx.GetRootNode());
		dSceneNodeInfo* const convexInfo = (dSceneNodeInfo*) xxxx.GetInfoFromNode(convexNode);
		dSceneNodeInfo* const sceneInfo = (dSceneNodeInfo*) xxxx.GetInfoFromNode(sceneNode);
		convexInfo->SetTransform(sceneInfo->GetTransform());

		dScene::dTreeNode* convexMeshNode = xxxx.CreateMeshNode(convexNode);
		dMeshNodeInfo* const convexMesh = (dMeshNodeInfo*)xxxx.GetInfoFromNode(convexMeshNode);
		convexMesh->ReplaceMesh(convexHullMesh);
		convexMesh->SetPivotMatrix ( meshInfo->GetPivotMatrix());
		xxxx.CreateMaterialNode(convexMeshNode, 0);
		count ++;
	}
	NewtonMeshDestroy(segment);
} 
NewtonMeshDestroy(convexAproximation);
*/


dMeshNodeInfo* const meshInfo = (dMeshNodeInfo*) xxxx.GetInfoFromNode(meshNode);
//NewtonMeshFixTJoints (meshInfo->GetMesh());
//NewtonCollision* collision = NewtonCreateCompoundCollisionFromMesh (m_newton, meshInfo->GetMesh(), 30, 0, 0);
NewtonCollision* collision = NewtonCreateConvexHullFromMesh (m_newton, meshInfo->GetMesh(), 0.01f, 0);
NewtonMesh* convexMesh = NewtonMeshCreateFromCollision(collision);
NewtonReleaseCollision(m_newton, collision);
dMeshNodeInfo* const convexMeshInfo = (dMeshNodeInfo*)xxxx.GetInfoFromNode(meshNode);
convexMeshInfo->ReplaceMesh(convexMesh);


xxxx.Serialize("C:/Newton_200/NewtonSDK/samples/bin/test_4.xml");
#endif




}

alchemediaDoc::~alchemediaDoc()
{
	Cleanup();

	NewtonDestroy(m_newton);
	_ASSERTE (m_physicsMemory == 0);
}

// alchemediaDoc diagnostics

#ifdef _DEBUG
void alchemediaDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void alchemediaDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG




// // memory allocation for the Newton library
void* alchemediaDoc::AllocMemory(int sizeInBytes)
{
	m_physicsMemory += sizeInBytes;
	return new char[sizeInBytes];
}

// free memory use by Newton engine
void alchemediaDoc::FreeMemory(void* const ptr, int sizeInBytes)
{
	m_physicsMemory -= sizeInBytes;
	delete[] (char*)ptr;
}

// Delete all worlds
void alchemediaDoc::Cleanup(void)
{
	// release all texture form all world
	m_undoRedoWorlds.RemoveAll();
}


BOOL alchemediaDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	Cleanup();

	_ASSERTE (m_explorer);
	m_currentFileName[0] = 0;
	m_currentWorld = m_undoRedoWorlds.Append();
	m_currentWorld->GetInfo().SetTextCache(&m_textureCache);
	m_currentWorld->GetInfo().SetNewtonWorld (m_newton);
	m_currentWorld->GetInfo().SetExplorer (m_explorer);

	m_explorer->PopulateScene(&m_currentWorld->GetInfo());
	return TRUE;
}




// alchemediaDoc serialization

void alchemediaDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}




alchemediaScene* alchemediaDoc::GetCurWorld(void) const
{
	return m_currentWorld ? &m_currentWorld->GetInfo() : NULL;
}



alchemediaScene* alchemediaDoc::NewWorldInstance (void)
{
	while (m_currentWorld->GetNext()) {
		m_undoRedoWorlds.Remove (m_currentWorld->GetNext());
	}

	while (m_undoRedoWorlds.GetCount() >= m_undoLevels) {
		m_undoRedoWorlds.Remove (m_undoRedoWorlds.GetFirst());
	}

//	neSceneExplorer* explorer = (neSceneExplorer*) ((neMainFrame*)wxGetApp().GetTopWindow())->GetCommandPanel()->FindWindow(_T("neSceneExplorer"));
//	explorer->SaveState (GetCurWorld());

	m_currentWorld = m_undoRedoWorlds.Append(m_currentWorld->GetInfo());
	return GetCurWorld();
}


void alchemediaDoc::OnFileNew()
{
	// TODO: Add your command handler code here
	OnNewDocument();
	m_mainFrame->Invalidate();
}

void alchemediaDoc::OnFileSave()
{
	// TODO: Add your command handler code here
	if (!m_currentFileName[0]) {
		char fileNamePath[1024];
		fileNamePath[0] = 0;
		OPENFILENAME fileNameInfo;
		memset (&fileNameInfo, 0, sizeof (fileNameInfo));
		fileNameInfo.lStructSize = sizeof (fileNameInfo);
		fileNameInfo.lpstrTitle = "Save alchemedia format";
		fileNameInfo.lpstrFilter = ALCHEMEDIA_FORMAT_DESCRIPTION;
		fileNameInfo.lpstrFile = fileNamePath;
		fileNameInfo.nMaxFile = sizeof (fileNamePath);
		if (GetSaveFileName(&fileNameInfo)) {
			strcpy (m_currentFileName, fileNamePath);
		}
	}

	if (m_currentFileName[0]) {
		const char* ptr = NULL;
		for (ptr = strrchr (m_currentFileName, '.'); ptr && (strchr (ptr, '/') || strchr (ptr, '\\')); ptr = strrchr (ptr, '.')) { 
			ptr ++;
		}
		if (ptr == NULL) {
			ptr = ALCHEMEDIA_FORMAT_ASCII_EXT;
			strcat (m_currentFileName, ALCHEMEDIA_FORMAT_ASCII_EXT);
		}

		if (!stricmp (ptr, ALCHEMEDIA_FORMAT_ASCII_EXT)) {
			GetCurWorld()->Serialize (m_currentFileName);
		} else if (!stricmp (ptr, ALCHEMEDIA_FORMAT_BINAY_EXT)) {
			_ASSERTE (0);
			//world->SerializeBinary (filename);
		}
	}
}

void alchemediaDoc::OnFileSaveAs()
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	char fileNamePath[1024];
	fileNamePath[0] = 0;
	OPENFILENAME fileNameInfo;
	memset (&fileNameInfo, 0, sizeof (fileNameInfo));
	fileNameInfo.lStructSize = sizeof (fileNameInfo);
	fileNameInfo.lpstrTitle = "Save Alchemedia format";
	fileNameInfo.lpstrFilter = ALCHEMEDIA_FORMAT_DESCRIPTION;
	fileNameInfo.lpstrFile = fileNamePath;
	fileNameInfo.nMaxFile = sizeof (fileNamePath);
	if (GetSaveFileName(&fileNameInfo)) {
		strcpy (m_currentFileName, fileNamePath);
		OnFileSave();
	}
}

void alchemediaDoc::OnFileOpen()
{
	// TODO: Add your command handler code here
	char fileNamePath[1024];
	fileNamePath[0] = 0;
	OPENFILENAME fileNameInfo;
	memset (&fileNameInfo, 0, sizeof (fileNameInfo));
	fileNameInfo.lStructSize = sizeof (fileNameInfo);
	fileNameInfo.lpstrTitle = "Load new Alchemedia scene";
	fileNameInfo.lpstrFilter = ALCHEMEDIA_FORMAT_DESCRIPTION;
	fileNameInfo.lpstrFile = fileNamePath;
	fileNameInfo.nMaxFile = sizeof (fileNamePath);
	if (GetOpenFileName(&fileNameInfo)) {
		OnNewDocument();
		strcpy (m_currentFileName, fileNamePath);

		alchemediaScene* const world = GetCurWorld();

		world->Deserialize(fileNamePath);
//		world->MergeDuplicateTextures();
//		world->UpdateAllOOBB ();
		m_explorer->PopulateScene(world);
		m_mainFrame->Invalidate();

//		char texPath[256];
//		dExtractPathFromFullName (fileNamePath, texPath);
//		LoadTextures (world, texPath);

	}
}

void alchemediaDoc::OnFileMerge()
{
	// TODO: Add your command handler code here
	char fileNamePath[1024];
	fileNamePath[0] = 0;
	OPENFILENAME fileNameInfo;
	memset (&fileNameInfo, 0, sizeof (fileNameInfo));
	fileNameInfo.lStructSize = sizeof (fileNameInfo);
	fileNameInfo.lpstrTitle = "Merge Alchemedia scene";
	fileNameInfo.lpstrFilter = ALCHEMEDIA_FORMAT_DESCRIPTION;
	fileNameInfo.lpstrFile = fileNamePath;
	fileNameInfo.nMaxFile = sizeof (fileNamePath);
	if (GetOpenFileName(&fileNameInfo)) {
		//alchemediaScene* world = GetCurWorld();
		alchemediaScene* world = NewWorldInstance();
		alchemediaScene tmpScene (&m_textureCache);
		tmpScene.SetNewtonWorld (world->GetNewtonWorld());
		if (tmpScene.Deserialize(fileNamePath)) {
			world->MergeScene (&tmpScene);
			world->MergeDuplicateTextures();

			m_explorer->PopulateScene(world);
			world->UpdateAllOOBB ();
			m_mainFrame->Invalidate();
		}
	}
}



// Set current Level to the previous level if any
void alchemediaDoc::Undo(void)
{
	if (m_currentWorld->GetPrev()) {
//		neSceneExplorer* explorer = (neSceneExplorer*) ((neMainFrame*)wxGetApp().GetTopWindow())->GetCommandPanel()->FindWindow(_T("neSceneExplorer"));
//		explorer->SaveState (GetCurWorld());
		m_currentWorld = m_currentWorld->GetPrev();
	//	explorer->RestoreState(GetCurWorld());
		m_mainFrame->Invalidate();
		alchemediaScene* world = GetCurWorld();	
		m_explorer->PopulateScene(world);
//		alchemediaScene::Iterator iter (*world);
//		for (alchemediaScene::dTreeNode* )
	}
}

void alchemediaDoc::Redo(void)
{
	if (m_currentWorld->GetNext()) {
//		neSceneExplorer* explorer = (neSceneExplorer*) ((neMainFrame*)wxGetApp().GetTopWindow())->GetCommandPanel()->FindWindow(_T("neSceneExplorer"));
//		explorer->SaveState (GetCurWorld());
		m_currentWorld = m_currentWorld->GetNext();
//		explorer->RestoreState(GetCurWorld());
		m_mainFrame->Invalidate();
		alchemediaScene* world = GetCurWorld();	
		m_explorer->PopulateScene(world);
	}
}


void alchemediaDoc::OnEditRedo()
{
	// TODO: Add your command handler code here
	Redo();
}

void alchemediaDoc::OnEditUndo()
{
	// TODO: Add your command handler code here
	Undo();
}


void alchemediaDoc::OnToolsPolygonizeScene()
{
	// TODO: Add your command handler code here
	alchemediaScene* world = NewWorldInstance();

	dList<alchemediaScene::dTreeNode*> modified; 

	alchemediaScene::Iterator iter (*world);
	for (iter.Begin(); iter; iter ++) {
		alchemediaScene::dTreeNode* node = iter.GetNode();
		dNodeInfo* const info = world->GetInfoFromNode(node);
//		if (info->GetTypeId() == dMeshNodeInfo::GetRttiType()) {
		if (info->IsType (dMeshNodeInfo::GetRttiType())) {
			world->CloneInfoFromNode(node);
			dMeshNodeInfo* const mesh = (dMeshNodeInfo*) world->GetInfoFromNode(node);;
			mesh->ConvertToPolygons();
			modified.Append(node);
		}
	}
	
	for (dList<alchemediaScene::dTreeNode*>::dListNode* modifiedNode = modified.GetFirst(); modifiedNode; modifiedNode = modifiedNode->GetNext()) {
		alchemediaScene::dTreeNode* node = modifiedNode->GetInfo();
		dMeshNodeInfo* const mesh = (dMeshNodeInfo*) world->GetInfoFromNode(node);
		mesh->RemoveUnusedVertices(world, node);
	}

	m_mainFrame->Invalidate();
}

void alchemediaDoc::OnToolsTriangulatescene()
{
	// TODO: Add your command handler code here

	alchemediaScene* world = NewWorldInstance();

	dList<alchemediaScene::dTreeNode*> modified; 

	alchemediaScene::Iterator iter (*world);
	for (iter.Begin(); iter; iter ++) {
		alchemediaScene::dTreeNode* node = iter.GetNode();
		dNodeInfo* const info = world->GetInfoFromNode(node);
//		if (info->GetTypeId() == dMeshNodeInfo::GetRttiType()) {
		if (info->IsType (dMeshNodeInfo::GetRttiType())) {
			world->CloneInfoFromNode(node);
			dMeshNodeInfo* const mesh = (dMeshNodeInfo*) world->GetInfoFromNode(node);;
			mesh->ConvertToTriangles();
			modified.Append(node);
		}
	}

	for (dList<alchemediaScene::dTreeNode*>::dListNode* modifiedNode = modified.GetFirst(); modifiedNode; modifiedNode = modifiedNode->GetNext()) {
		alchemediaScene::dTreeNode* node = modifiedNode->GetInfo();
		dMeshNodeInfo* const mesh = (dMeshNodeInfo*) world->GetInfoFromNode(node);
		mesh->RemoveUnusedVertices(world, node);
	}

	m_mainFrame->Invalidate();
}


void alchemediaDoc::OnToolsSmoothscenenormal()
{
	// TODO: Add your command handler code here

	AlchemdiaSmoothMeshAngleDlg smothAngle;
	smothAngle.DoModal();


	alchemediaScene* world = NewWorldInstance();

	dFloat angleInRadiants = 30.0f * 3.1416f / 180.0f;

	alchemediaScene::Iterator iter (*world);
	for (iter.Begin(); iter; iter ++) {
		alchemediaScene::dTreeNode* node = iter.GetNode();
		dNodeInfo* const info = world->GetInfoFromNode(node);
//		if (info->GetTypeId() == dMeshNodeInfo::GetRttiType()) {
		if (info->IsType (dMeshNodeInfo::GetRttiType())) {
			world->CloneInfoFromNode(node);
			dMeshNodeInfo* const mesh = (dMeshNodeInfo*) world->GetInfoFromNode(node);;
			mesh->SmoothNormals(angleInRadiants);
		}
	}

	m_mainFrame->Invalidate();
}


void alchemediaDoc::OnToolsWeldtjoints()
{
	// TODO: Add your command handler code here

	alchemediaScene* const world = NewWorldInstance();

	dList<alchemediaScene::dTreeNode*> modified; 

	alchemediaScene::Iterator iter (*world);
	for (iter.Begin(); iter; iter ++) {
		alchemediaScene::dTreeNode* node = iter.GetNode();
		dNodeInfo* const info = world->GetInfoFromNode(node);
//		if (info->GetTypeId() == dMeshNodeInfo::GetRttiType()) {
		if (info->IsType (dMeshNodeInfo::GetRttiType())) {
			world->CloneInfoFromNode(node);
			dMeshNodeInfo* const mesh = (dMeshNodeInfo*) world->GetInfoFromNode(node);;
			mesh->WeldTJoints();
			modified.Append(node);
		}
	}

	for (dList<alchemediaScene::dTreeNode*>::dListNode* modifiedNode = modified.GetFirst(); modifiedNode; modifiedNode = modifiedNode->GetNext()) {
		alchemediaScene::dTreeNode* node = modifiedNode->GetInfo();
		dMeshNodeInfo* const mesh = (dMeshNodeInfo*) world->GetInfoFromNode(node);
		mesh->RemoveUnusedVertices(world, node);
	}

	m_mainFrame->Invalidate();

}
