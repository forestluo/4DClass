#pragma once
#include "afxwin.h"


// CClassicSliderJointDialog dialog

class CClassicSliderJointDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CClassicSliderJointDialog)

public:
	CClassicSliderJointDialog(bool bChildOnly,CVirtualLabDoc* pDoc,CWnd* pParent = NULL);   // standard constructor
	virtual ~CClassicSliderJointDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_JOINT_SLIDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()

private:
	//Child only.
	bool m_bChildOnly;
	//Document.
	CVirtualLabDoc* m_pDoc;

private:
	//Children.
	CComboBox m_children;
	CString m_strChild;
	//Parents.
	CComboBox m_parents;
	CString m_strParent;
	//Rotate
	int m_nXRotate;
	int m_nYRotate;
	int m_nZRotate;
	//Position.
	float m_fXPosition;
	float m_fYPosition;
	float m_fZPosition;
	//Value.
	float m_fStiffness;
	BOOL m_bSelfCollision;
};
