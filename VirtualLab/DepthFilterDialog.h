#pragma once
#include "afxwin.h"


// CDepthFilterDialog dialog

class CDepthFilterDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CDepthFilterDialog)

public:
	CDepthFilterDialog(CVirtualLabDoc* pDoc,CWnd* pParent = NULL);   // standard constructor
	virtual ~CDepthFilterDialog();

	// Dialog Data
	enum { IDD = IDD_DIALOG_DEPTH_FILTER };

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
