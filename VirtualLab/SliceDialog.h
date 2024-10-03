#pragma once


// CSliceDialog dialog

class CSliceDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CSliceDialog)

public:
	CSliceDialog(CVirtualLabDoc* pDoc,CWnd* pParent = NULL);   // standard constructor
	virtual ~CSliceDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_SLICE };

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
	//Dimension.
	float m_fWidth;
	float m_fLength;
	//Rotation
	int m_nXRotation;
	int m_nYRotation;
	int m_nZRotation;
	//Position.
	float m_fXPosition;
	float m_fYPosition;
	float m_fZPosition;
};
