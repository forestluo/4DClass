#pragma once
#include "afxwin.h"


// CCustomHingeJointDialog dialog

class CCustomHingeJointDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CCustomHingeJointDialog)

public:
	CCustomHingeJointDialog(CVirtualLabDoc* pDoc,CWnd* pParent = NULL);   // standard constructor
	virtual ~CCustomHingeJointDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_JOINT_HINGE_CUSTOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()

private:
	//Document.
	CVirtualLabDoc* m_pDoc;

private:
	//Children.
	CComboBox m_children;
	CString m_strChild;
	//Parents.
	CComboBox m_parents;
	CString m_strParent;
	//Attribute.
	BOOL m_bSelfCollision;
	//Position.
	float m_fXPosition;
	float m_fYPosition;
	float m_fZPosition;
	//Rotation.
	int m_nXRotate;
	int m_nYRotate;
	int m_nZRotate;

private:
	float m_fXMajor;
	float m_fYMajor;
	float m_fZMajor;
	int m_nXRMajor;
	int m_nYRMajor;
	int m_nZRMajor;
};
