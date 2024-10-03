#pragma once
#include "afxwin.h"


// CInputTextureDialog dialog

class CInputTextureDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CInputTextureDialog)

public:
	CInputTextureDialog(CVirtualLabDoc* pDoc,CWnd* pParent = NULL);   // standard constructor
	virtual ~CInputTextureDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_IMAGE_TEXTURE };

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
