#pragma once


// AlchemdiaSmoothMeshAngleDlg dialog

class AlchemdiaSmoothMeshAngleDlg : public CDialog
{
	DECLARE_DYNAMIC(AlchemdiaSmoothMeshAngleDlg)

public:
	AlchemdiaSmoothMeshAngleDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~AlchemdiaSmoothMeshAngleDlg();

// Dialog Data
	enum { IDD = IDD_SMOOTH_MESH_NORMALS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeRichedit21();
};
