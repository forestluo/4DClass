// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

#include "stdafx.h"

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "4DProperties.h"
#include "VirtualLabDoc.h"

#include "ObjectSketcher.h"
#include "JointObjectSketcher.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define MAINFRAME											((CMainFrame *)GetTopLevelFrame())

///////////////////////////////////////////////////////////////////////////////
//
// OnRenderPropertyChanged
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::OnRenderPropertyChanged(CD3DXRenderableObject* pRenderableObject,CMFCPropertyGridProperty *pProp)
{
#ifdef _DEBUG
	assert(pRenderableObject != NULL && pProp != NULL);
#endif
	//Check property.
	if(pProp == HANDLE_RENDER_MODEL_NAME)
	{
		//Check instance and update model.
		if(pRenderableObject->isPrimitiveObject())
		{
			//Set renderable object.
			CD3DXPrimitiveObject* pPrimitiveObject = (CD3DXPrimitiveObject *)pRenderableObject;
#ifdef _DEBUG
			assert(pPrimitiveObject != NULL);
#endif

			//Model name was changed.
			CNormalString modelName(CString(pProp->GetValue()).GetBuffer());
			//Check result.
			if(modelName == pPrimitiveObject->getModelName()) return;

			//Check result.
			if(modelName.length() <= 0)
			{
				//Show message.
				AfxMessageBox(_T("模板名字不允许为空。\n\n系统将恢复原有模板名。"), MB_OK | MB_ICONSTOP);
				//Recover its name.
				pProp->SetValue(pPrimitiveObject->getModelName().getCString());
			}
			else
			{
				//Check main frame.
				if(MAINFRAME != NULL)
				{
					//Get doc.
					CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();
					//Check result.
					if(pDoc != NULL && pDoc->application != NULL)
					{
						//Get resource name.
						CD3DXResource* pResource = pDoc->application->getResource(modelName);
						//Check result.
						if(pResource == NULL)
						{
							//Recover its name.
							pProp->SetValue(pPrimitiveObject->getModelName().getCString());
							//Show message.
							AfxMessageBox(_T("模板已经不存在。\n\n系统将恢复原有模板名。"), MB_OK | MB_ICONSTOP);
						}
						else if(IS_RENDERABLE_BASE(pResource))
						{
							//Open lock.
							pDoc->application->openLock();
							{
								//Set renderable.
								pPrimitiveObject->selectRenderable(pDoc->application->getResourceManager(),modelName);
							}
							//Close lock.
							pDoc->application->closeLock();
						}
						else
						{
							//Recover its name.
							pProp->SetValue(pPrimitiveObject->getModelName().getCString());
							//Show message.
							AfxMessageBox(_T("所选资源不是可绘制模板。\n\n系统将恢复原有模板名。"), MB_OK | MB_ICONSTOP);
						}
					}
				}
			}
		}
	}
	else if(pProp == HANDLE_RENDER_EFFECT_NAME)
	{
		//Check instance and update effect.
		if(pRenderableObject->isPrimitiveObject())
		{
			//Set renderable object.
			CD3DXPrimitiveObject* pPrimitiveObject = (CD3DXPrimitiveObject *)pRenderableObject;
#ifdef _DEBUG
			assert(pPrimitiveObject != NULL);
#endif
			//Effect name was changed.
			CNormalString effectName(CString(pProp->GetValue()).GetBuffer());
			//Check result.
			if(effectName == pPrimitiveObject->getEffectName()) return;

			//Check main frame.
			if(MAINFRAME != NULL)
			{
				//Get doc.
				CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();
				//Check result.
				if(pDoc != NULL && pDoc->application != NULL)
				{
					//Check result.
					if(effectName.length() <= 0)
					{
						//Open lock.
						pDoc->application->openLock();
						{
							//Set default effect.
							pPrimitiveObject->selectEffect(pDoc->application->getResourceManager(),effectName);
						}
						//Close lock.
						pDoc->application->closeLock();
						return;
					}

					//Get resource name.
					CD3DXResource* pResource = pDoc->application->getResource(effectName);
					//Check result.
					if(pResource == NULL)
					{
						//Recover its name.
						pProp->SetValue(pPrimitiveObject->getEffectName().getCString());
						//Show message.
						AfxMessageBox(_T("手法模板已经不存在。\n\n系统将恢复原有手法名称。"), MB_OK | MB_ICONSTOP);
					}
					else if(IS_EFFECT_BASE(pResource))
					{
						//Open lock.
						pDoc->application->openLock();
						{
							//Set effect.
							pPrimitiveObject->selectEffect(pDoc->application->getResourceManager(),effectName);
						}
						//Close lock.
						pDoc->application->closeLock();
					}
					else
					{
						//Recover its name.
						pProp->SetValue(pPrimitiveObject->getEffectName().getCString());
						//Show message.
						AfxMessageBox(_T("所选资源不是手法模板。\n\n系统将恢复原有手法名称。"), MB_OK | MB_ICONSTOP);
					}
				}
			}
		}
	}
	else if(pProp == HANDLE_RENDER_COLOR_GLOBAL)
	{
		//Get color.
		COLORREF dwColor = ((CMFCPropertyGridColorProperty *)pProp)->GetColor();
		//Check object.
		if(pRenderableObject->isPrimitiveObject())
		{
			//Set color.
			((CD3DXPrimitiveObject *)pRenderableObject)->setColor(D3DCOLOR_RGBA(GetRValue(dwColor),GetGValue(dwColor),GetBValue(dwColor),255));
		}
	}
	else if(pProp == HANDLE_RENDER_LIGHT_COLOR)
	{
		//Get color.
		DWORD dwColor = ((CMFCPropertyGridColorProperty *)pProp)->GetColor();
		//Check object.
		if(pRenderableObject->isPrimitiveObject())
		{
			//Light color.
			D3DXVECTOR4 vLightColor;
			//Set value.
			vLightColor.x = GetRValue(dwColor) / 255.0f;
			vLightColor.y = GetGValue(dwColor) / 255.0f;
			vLightColor.z = GetBValue(dwColor) / 255.0f;
			vLightColor.w = 1.0f;
			//Set color.
			((CD3DXPrimitiveObject *)pRenderableObject)->setLightColor(vLightColor);
		}
	}
	//Check property.
	else if(pProp == HANDLE_RENDER_DEBUG_LOCAL_AXIS)
	{
		//Get object sketcher.
		CObjectSketcher* pSketcher = pRenderableObject->getSketcher();
		//Check result.
		if(pSketcher != NULL)
		{
			//Get value.
			pSketcher->drawAxis = pProp->GetValue().boolVal;
		}
	}
	else if(pProp == HANDLE_RENDER_DEBUG_BOX_AABOX)
	{
		//Get object sketcher.
		CObjectSketcher* pSketcher = pRenderableObject->getSketcher();
		//Check result.
		if(pSketcher != NULL)
		{
			//Get value.
			pSketcher->drawBox = pProp->GetValue().boolVal;
		}
	}
	else if(pProp == HANDLE_RENDER_DEBUG_BOX_SPHERE)
	{
		//Get object sketcher.
		CObjectSketcher* pSketcher = pRenderableObject->getSketcher();
		//Check result.
		if(pSketcher != NULL)
		{
			//Get value.
			pSketcher->drawSphere = pProp->GetValue().boolVal;
		}
	}
	else if(pProp == HANDLE_RENDER_DEBUG_JOINT_SPHERE)
	{
		//Get object sketcher.
		CObjectSketcher* pSketcher = pRenderableObject->getSketcher();
		//Check result.
		if(pSketcher != NULL && IS_JOINTOBJECTSKETCHER_BASE(pSketcher))
		{
			//Get value.
			((CJointObjectSketcher *)pSketcher)->drawJointSphere = pProp->GetValue().boolVal;
		}
	}
	else if(pProp == HANDLE_RENDER_DEBUG_JOINT_POSITION)
	{
		//Get object sketcher.
		CObjectSketcher* pSketcher = pRenderableObject->getSketcher();
		//Check result.
		if(pSketcher != NULL && IS_JOINTOBJECTSKETCHER_BASE(pSketcher))
		{
			//Get value.
			((CJointObjectSketcher *)pSketcher)->drawJointPosition = pProp->GetValue().boolVal;
		}
	}
	else if(pProp == HANDLE_RENDER_DEBUG_JOINT_DIRECTION)
	{
		//Get object sketcher.
		CObjectSketcher* pSketcher = pRenderableObject->getSketcher();
		//Check result.
		if(pSketcher != NULL && IS_JOINTOBJECTSKETCHER_BASE(pSketcher))
		{
			//Get value.
			((CJointObjectSketcher *)pSketcher)->drawJointDirection = pProp->GetValue().boolVal;
		}
	}
	else if(pProp == HANDLE_RENDER_TEXTURE_SCENE)
	{
		//Check instance and update effect.
		if(pRenderableObject->isPrimitiveObject())
		{
			//Set renderable object.
			CD3DXPrimitiveObject* pPrimitiveObject = (CD3DXPrimitiveObject *)pRenderableObject;
#ifdef _DEBUG
			assert(pPrimitiveObject != NULL);
#endif
			//Scene map name was changed.
			CNormalString sceneMapName(CString(pProp->GetValue()).GetBuffer());
			//Check result.
			if(sceneMapName == pPrimitiveObject->getSceneMapName()) return;

			//Check main frame.
			if(MAINFRAME != NULL)
			{
				//Get doc.
				CVirtualLabDoc* pDoc = (CVirtualLabDoc *)MAINFRAME->GetActiveDocument();
				//Check result.
				if(pDoc != NULL && pDoc->application != NULL)
				{
					//Check result.
					if(sceneMapName.length() <= 0)
					{
						//Open lock.
						pDoc->application->openLock();
						{
							//Set default scene map.
							pPrimitiveObject->selectSceneMap(pDoc->application->getResourceManager(),sceneMapName);
						}
						//Close lock.
						pDoc->application->closeLock();
						return;
					}

					//Get resource name.
					CD3DXResource* pResource = pDoc->application->getResource(sceneMapName);
					//Check result.
					if(pResource == NULL)
					{
						//Recover its name.
						pProp->SetValue(pPrimitiveObject->getSceneMapName().getCString());
						//Show message.
						AfxMessageBox(_T("场景图已经不存在。\n\n系统将恢复原有场景图名称。"), MB_OK | MB_ICONSTOP);
					}
					else if(IS_TEXTURE_BASE(pResource))
					{
						//Open lock.
						pDoc->application->openLock();
						{
							//Set scene map.
							pPrimitiveObject->selectSceneMap(pDoc->application->getResourceManager(),sceneMapName);
						}
						//Close lock.
						pDoc->application->closeLock();
					}
					else
					{
						//Recover its name.
						pProp->SetValue(pPrimitiveObject->getSceneMapName().getCString());
						//Show message.
						AfxMessageBox(_T("所选资源不是纹理贴图。\n\n系统将恢复原有场景图名称。"), MB_OK | MB_ICONSTOP);
					}
				}
			}
		}
	}
}
