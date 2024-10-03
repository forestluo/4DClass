/////////////////////////////////////////////////////////////////////////////
// Name:        alchemediaDoc.h
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

// alchemediaDoc.h : interface of the alchemediaDoc class
//

#ifndef __ALCHEMEDIA_DOC_H__
#define __ALCHEMEDIA_DOC_H__

#include "alchemediaScene.h"
#include "alchemediaTexCache.h"

//class alchemediaScene;
class alchemediaMainFrame;
class alchemediaExplorerView;

#define	ALCHEMEDIA_FORMAT_ASCII_EXT		".xml" 	
#define	ALCHEMEDIA_FORMAT_BINAY_EXT		".new" 	
#define ALCHEMEDIA_FORMAT_DESCRIPTION	"alchemedia xml\0*.xml\0alchemedia bin\0*.new\0\0"

class alchemediaDoc : public CDocument 
{
	class alchemediaUndoRedoWorlds: public dList<alchemediaScene>
	{

	};


protected: // create from serialization only
	alchemediaDoc();
	DECLARE_DYNCREATE(alchemediaDoc)

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual ~alchemediaDoc();

//	void Cleanup(void);
//	void Init(void);

	// Save the world and make a new world instance as the current world
	alchemediaScene* NewWorldInstance (void);

	// Return the pointer to the current world
	alchemediaScene* GetCurWorld(void) const;

	// Set current Level to the previews level if any
	void Undo(void);
	// Set current Level to the previous level if any
	void Redo(void);


	// unload all texture for the current level
	void UnloadTextures (alchemediaScene* const world);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
	DECLARE_MESSAGE_MAP()

	void Cleanup(void);

	// memory allocation for the Newton library
	static void* AllocMemory(int sizeInBytes);

	// free memory use by Newton engine
	static void FreeMemory(void* const ptr, int sizeInBytes);

	static int m_physicsMemory;

	
	int m_undoLevels;			 // maximum level of Undo to track
	NewtonWorld* m_newton;		 // pointer to the Newton world for all physics and computational geometry actions
	alchemediaUndoRedoWorlds::dListNode* m_currentWorld;  // current active level

	// Texture cache for Opengl 
	alchemediaTextureCache m_textureCache;
	
//	alchemediaScene* m_curScene; // current world state
	alchemediaMainFrame* m_mainFrame;
	alchemediaExplorerView* m_explorer;
	alchemediaUndoRedoWorlds m_undoRedoWorlds;
	char m_currentFileName[1024];
	
	friend class alchemediaMainFrame;
public:
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	
	afx_msg void OnFileMerge();
	afx_msg void OnEditUndo();
	afx_msg void OnEditRedo();
	afx_msg void OnToolsPolygonizeScene();
	afx_msg void OnToolsTriangulatescene();
	afx_msg void OnToolsSmoothscenenormal();
	afx_msg void OnToolsWeldtjoints();
};


#endif