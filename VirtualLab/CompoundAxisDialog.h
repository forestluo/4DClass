#pragma once


// CCompoundAxisDialog dialog

class CCompoundAxisDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CCompoundAxisDialog)

public:
	CCompoundAxisDialog(CVirtualLabDoc* pDoc,CWnd* pParent = NULL);   // standard constructor
	virtual ~CCompoundAxisDialog();

	// Dialog Data
	enum { IDD = IDD_DIALOG_REALAXIS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()

private:
	//Document.
	CVirtualLabDoc* m_pDoc;

private:
	//Mass
	float m_fMass;
	//Length
	float m_fXLength;
	float m_fYLength;
	float m_fZLength;
	//Rotate.
	int m_nXRotate;
	int m_nYRotate;
	int m_nZRotate;
	//Position.
	float m_fXPosition;
	float m_fYPosition;
	float m_fZPosition;
};
