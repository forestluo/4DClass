#pragma once
#include "afxwin.h"


// CPSEyeSettingDialog dialog

class CPSEyeSettingDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPSEyeSettingDialog)

public:
	CPSEyeSettingDialog(CVirtualLabDoc* pDoc,CWnd* pParent = NULL);   // standard constructor
	virtual ~CPSEyeSettingDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_PSEYE_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();

	afx_msg void OnCbnSelchangeComboPseyeName();

	DECLARE_MESSAGE_MAP()

private:
	//Document.
	CVirtualLabDoc* m_pDoc;

private:
	CComboBox m_names;
	BOOL m_bDynamicTrack;
	int m_nGain;
	int m_nExposure;
	int m_nRotation;
	int m_nZoom;
};
