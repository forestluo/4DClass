#pragma once


// CFrustumDialog dialog

class CFrustumDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CFrustumDialog)

public:
	CFrustumDialog(int nType,CVirtualLabDoc* pDoc,CWnd* pParent = NULL);   // standard constructor
	virtual ~CFrustumDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_FRUSTUM };

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
	//Height
	float m_fHeight;
	//Dimension
	float m_fMajorRadius;
	float m_fMinorRadius;
	//Rotate
	int m_nXRotate;
	int m_nYRotate;
	int m_nZRotate;
	//Position.
	float m_fXPosition;
	float m_fYPosition;
	float m_fZPosition;
};
