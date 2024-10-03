#pragma once
#include "afxwin.h"


// CCircleDialog dialog

class CCircleDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CCircleDialog)

public:
	CCircleDialog(CVirtualLabDoc* pDoc,CWnd* pParent = NULL);   // standard constructor
	virtual ~CCircleDialog();

	// Dialog Data
	enum { IDD = IDD_DIALOG_CIRCLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()

private:
	//Polygon
	CComboBox m_polygon;
	//Document.
	CVirtualLabDoc* m_pDoc;

private:
	//Type
	int m_nType;
	//Radius
	float m_fRadius;
	//Rotate.
	int m_nXRotate;
	int m_nYRotate;
	int m_nZRotate;
	//Position.
	float m_fXPosition;
	float m_fYPosition;
	float m_fZPosition;
};
