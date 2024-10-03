#pragma once


// CCuboidDialog dialog

class CCuboidDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CCuboidDialog)

public:
	CCuboidDialog(CVirtualLabDoc* pDoc,CWnd* pParent = NULL);   // standard constructor
	virtual ~CCuboidDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_CUBOID };

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
	//Dimension.
	float m_fLength;
	float m_fWidth;
	float m_fHeight;
	//Rotate
	int m_nXRotate;
	int m_nYRotate;
	int m_nZRotate;
	//Position.
	float m_fXPosition;
	float m_fYPosition;
	float m_fZPosition;
};
