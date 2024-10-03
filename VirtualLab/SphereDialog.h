#pragma once


// CSphereDialog dialog

class CSphereDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CSphereDialog)

public:
	CSphereDialog(bool bHemisphere,CVirtualLabDoc* pDoc,CWnd* pParent = NULL);   // standard constructor
	virtual ~CSphereDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_SPHERE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()

private:
	//Document.
	CVirtualLabDoc* m_pDoc;

private:
	//Hemisphere.
	bool m_bHemisphere;
	//Mass
	float m_fMass;
	//Radius
	float m_fXRadius;
	float m_fYRadius;
	float m_fZRadius;
	//Rotate.
	int m_nXRotate;
	int m_nYRotate;
	int m_nZRotate;
	//Position.
	float m_fXPosition;
	float m_fYPosition;
	float m_fZPosition;
};
