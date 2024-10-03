#pragma once


// CCubeDialog dialog

class CCubeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CCubeDialog)

public:
	CCubeDialog(CVirtualLabDoc* pDoc,CWnd* pParent = NULL);   // standard constructor
	virtual ~CCubeDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_CUBE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()

private:
	//Document.
	CVirtualLabDoc* m_pDoc;

private:
	//Mass.
	float m_fMass;
	//Length.
	float m_fLength;
	//Rotate.
	int m_nXRotate;
	int m_nYRotate;
	int m_nZRotate;
	//Position.
	float m_fXPosition;
	float m_fYPosition;
	float m_fZPosition;
};
