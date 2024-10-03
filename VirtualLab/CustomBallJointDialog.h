#pragma once
#include "afxwin.h"


// CCustomBallJointDialog dialog

class CCustomBallJointDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CCustomBallJointDialog)

public:
	CCustomBallJointDialog(CVirtualLabDoc* pDoc,CWnd* pParent = NULL);   // standard constructor
	virtual ~CCustomBallJointDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_JOINT_BALL_CUSTOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg void OnBnClickedOk();

	virtual BOOL OnInitDialog();

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
	BOOL m_bSelfCollision;
	//Position
	float m_fXPosition;
	float m_fYPosition;
	float m_fZPosition;
	//Angle.
	int m_nMaxConeAngle;
	int m_nMaxTwistAngle;
	int m_nMinTwistAngle;

private:
	float m_fXMajor;
	float m_fYMajor;
	float m_fZMajor;
	int m_nXRMajor;
	int m_nYRMajor;
	int m_nZRMajor;
};
