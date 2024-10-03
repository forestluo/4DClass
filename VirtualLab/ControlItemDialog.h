#pragma once
#include "afxwin.h"


// CControlItemDialog dialog

class CControlItemDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CControlItemDialog)

public:
	CControlItemDialog(CVirtualLabDoc* pDoc,CWnd* pParent = NULL);   // standard constructor
	virtual ~CControlItemDialog();

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
