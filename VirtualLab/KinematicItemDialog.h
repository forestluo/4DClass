#pragma once
#include "afxwin.h"


// CKinematicItemDialog dialog

class CKinematicItemDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CKinematicItemDialog)

public:
	CKinematicItemDialog(CVirtualLabDoc* pDoc,CWnd* pParent = NULL);   // standard constructor
	virtual ~CKinematicItemDialog();

	// Dialog Data
	enum { IDD = IDD_DIALOG_CONTROLLED_BALL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()

private:
	//Document.
	CVirtualLabDoc* m_pDoc;

private:
	CString m_strName;
	CComboBox m_devices;
	CString m_strDeviceName;
};
