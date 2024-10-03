#pragma once


// CArrayDialog dialog

class CArrayDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CArrayDialog)

public:
	CArrayDialog(int nPrimitiveType,int nArrayType,CVirtualLabDoc* pDoc,CWnd* pParent = NULL);   // standard constructor
	virtual ~CArrayDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_ARRAY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()

private:
	//Document.
	CVirtualLabDoc* m_pDoc;

private:
	//Type of array.
	int m_nArrayType;
	//Type of primitive.
	int m_nPrimitiveType;
	//Row.
	int m_nRow;
	//Column.
	int m_nColumn;
	//Position.
	float m_fXPosition;
	float m_fYPosition;
	float m_fZPosition;
};
