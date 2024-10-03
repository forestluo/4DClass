#pragma once
#include "afxwin.h"


// CClassicHingeJointDialog dialog

class CClassicHingeJointDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CClassicHingeJointDialog)

public:
	CClassicHingeJointDialog(bool bChildOnly,CVirtualLabDoc* pDoc,CWnd* pParent = NULL);   // standard constructor
	virtual ~CClassicHingeJointDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_JOINT_HINGE };

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
	//Attributes.
	float m_fStiffness;
	BOOL m_bSelfCollision;
	//Position.
	float m_fXPosition;
	float m_fYPosition;
	float m_fZPosition;
	//Rotation.
	int m_nXRotate;
	int m_nYRotate;
	int m_nZRotate;
};
