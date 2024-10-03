#pragma once


// CConeDialog dialog

class CConeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CConeDialog)

public:
	CConeDialog(int nType,CVirtualLabDoc* pDoc,CWnd* pParent = NULL);   // standard constructor
	virtual ~CConeDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_CONE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()

private:
	//Document.
	CVirtualLabDoc* m_pDoc;

private:
	//Type
	int m_nType;
	//Mass
	float m_fMass;
	//Dimension.
	float m_fRadius;
	float m_fHeight;
	//Rotate
	int m_nXRotate;
	int m_nYRotate;
	int m_nZRotate;
	//Position
	float m_fXPosition;
	float m_fYPosition;
	float m_fZPosition;
};
