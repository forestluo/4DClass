#pragma once
#include "afxwin.h"


// CGridDialog dialog

class CGridDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CGridDialog)

public:
	CGridDialog(CVirtualLabDoc* pDoc,CWnd* pParent = NULL);   // standard constructor
	virtual ~CGridDialog();

	// Dialog Data
	enum { IDD = IDD_DIALOG_GRID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()

private:
	//Resolution.
	CComboBox m_resolution;
	//Document.
	CVirtualLabDoc* m_pDoc;

private:
	//Type
	int m_nType;
	//Dimension.
	float m_fQuadWidth;
	float m_fQuadHeight;
	//Rotate
	int m_nXRotate;
	int m_nYRotate;
	int m_nZRotate;
	//Position.
	float m_fXPosition;
	float m_fYPosition;
	float m_fZPosition;
};
