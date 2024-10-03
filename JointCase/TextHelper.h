///////////////////////////////////////////////////////////////////////////////
//
// TextHelper.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _TEXT_HELPER_H_
#define _TEXT_HELPER_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXObject.h"
#include "NormalString.h"

///////////////////////////////////////////////////////////////////////////////
//
// SDK
//
///////////////////////////////////////////////////////////////////////////////

#include "SDKmisc.h"
#include "D3DXUtility.h"

///////////////////////////////////////////////////////////////////////////////
//
// TextHelper
//
///////////////////////////////////////////////////////////////////////////////

class CTextHelper : public CD3DXObject
{
private:
	//Base description.
	static const C4DBase base;

public:

	/**
	 * Get class code.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Hash code of this class.</p>
	 */
	static _LONG getClassCode() {return base.classCode();}

	/**
	 * Get class code.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Hash code of this class.</p>
	 */
	virtual _LONG classCode() const {return base.classCode();}

private:
	//Show help.
	bool							g_bShowHelp;

	ID3DXFont*						g_pFont;
	ID3DXSprite*					g_pSprite;
	CDXUTTextHelper*				g_pTxtHelper;

private:
	//Informations.
	CNormalString					g_strHelp;
	CNormalString                   g_strIndication;

protected:
	//Render.
	void Render();

public:
	CTextHelper(void);
	~CTextHelper(void);

	//Show help or not.
	void ToggleShowHelp(void);

	//Set help text.
	void SetHelpText(const CNormalString& strHelp);
	//Set indication text.
	void SetIndicationText(const CNormalString& strIndication);

	///////////////////////////////////////
	//
	// D3DXEvent Function
	//
	///////////////////////////////////////
	virtual HRESULT handleMessage(const D3DXEvent& d3dxEvent);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_TEXT_HELPER_H_
