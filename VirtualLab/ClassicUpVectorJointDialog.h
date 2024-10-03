#pragma once
#include "afxwin.h"


// CClassicUpVectorJointDialog dialog

class CClassicUpVectorJointDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CClassicUpVectorJointDialog)

public:
	CClassicUpVectorJointDialog(CVirtualLabDoc* pDoc,CWnd* pParent = NULL);   // standard constructor
	virtual ~CClassicUpVectorJointDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_JOINT_UPVECTOR };

protected:
	virtual BOOL OnInitDialog();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()

private:
	//Document.
	CVirtualLabDoc* m_pDoc;

private:
	CString m_strChild;
	CComboBox m_children;
	//Position
	float m_fXPosition;
	float m_fYPosition;
	float m_fZPosition;
	//Rotate
	int m_nXRotate;
	int m_nZRotate;
	int m_nYRotate;
};
