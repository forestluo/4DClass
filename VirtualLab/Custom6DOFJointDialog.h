#pragma once
#include "afxwin.h"


// CCustom6DOFJointDialog dialog

class CCustom6DOFJointDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CCustom6DOFJointDialog)

public:
	CCustom6DOFJointDialog(CVirtualLabDoc* pDoc,CWnd* pParent = NULL);   // standard constructor
	virtual ~CCustom6DOFJointDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_JOINT_6DOF_CUSTOM };

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
	//Attributes.
	float m_fStiffness;
	BOOL m_bSelfCollision;
	//Rotate.
	int m_nXRotate;
	int m_nYRotate;
	int m_nZRotate;
	//Rotation.
	int m_nXRLimitMin;
	int m_nXRLimitMax;
	int m_nYRLimitMin;
	int m_nYRLimitMax;
	int m_nZRLimitMin;
	int m_nZRLimitMax;
	//Limitation.
	float m_fXLimitMin;
	float m_fXLimitMax;
	float m_fYLimitMin;
	float m_fYLimitMax;
	float m_fZLimitMin;
	float m_fZLimitMax;
	//Position.
	float m_fXPosition;
	float m_fYPosition;
	float m_fZPosition;

private:
	float m_fXMajor;
	float m_fYMajor;
	float m_fZMajor;
	int m_nXRMajor;
	int m_nYRMajor;
	int m_nZRMajor;
	float m_fXMinor;
	float m_fYMinor;
	float m_fZMinor;
	int m_nXRMinor;
	int m_nYRMinor;
	int m_nZRMinor;
};
