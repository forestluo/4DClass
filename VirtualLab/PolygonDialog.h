#pragma once
#include "afxwin.h"


// CPolygonDialog dialog

class CPolygonDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPolygonDialog)

public:
	CPolygonDialog(CVirtualLabDoc* pDoc,CWnd* pParent = NULL);   // standard constructor
	virtual ~CPolygonDialog();

	// Dialog Data
	enum { IDD = IDD_DIALOG_POLYGON };

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
	//Mass
	float m_fMass;
	//Faces
	int m_nFaces;
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
