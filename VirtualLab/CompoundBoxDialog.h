#pragma once


// CCompoundBoxDialog dialog

class CCompoundBoxDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CCompoundBoxDialog)

public:
	CCompoundBoxDialog(CVirtualLabDoc* pDoc,CWnd* pParent = NULL);   // standard constructor
	virtual ~CCompoundBoxDialog();

	// Dialog Data
	enum { IDD = IDD_DIALOG_REALBOX };

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
	//Dimension
	float m_fLength;
	float m_fHeight;
	float m_fDepth;
	//Rotate.
	int m_nXRotate;
	int m_nYRotate;
	int m_nZRotate;
	//Position.
	float m_fXPosition;
	float m_fYPosition;
	float m_fZPosition;
};
