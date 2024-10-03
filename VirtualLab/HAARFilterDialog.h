#pragma once
#include "afxwin.h"


// CHAARFilterDialog dialog

class CHAARFilterDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CHAARFilterDialog)

public:
	CHAARFilterDialog(CVirtualLabDoc* pDoc,CWnd* pParent = NULL);   // standard constructor
	virtual ~CHAARFilterDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_HAAR_FILTER };

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
