#pragma once
#include "afxwin.h"


// CClassicUniversalJointDialog dialog

class CClassicUniversalJointDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CClassicUniversalJointDialog)

public:
	CClassicUniversalJointDialog(bool bChildOnly,CVirtualLabDoc* pDoc,CWnd* pParent = NULL);   // standard constructor
	virtual ~CClassicUniversalJointDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_JOINT_UNIVERSAL };

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
	int m_nXRotate2;
	int m_nYRotate2;
	int m_nZRotate2;
};
