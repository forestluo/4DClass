// AlchemdiaSmoothMeshAngleDlg.cpp : implementation file
//

#include "alchemediaStdafx.h"
#include "alchemedia.h"
#include "AlchemdiaSmoothMeshAngleDlg.h"


// AlchemdiaSmoothMeshAngleDlg dialog

IMPLEMENT_DYNAMIC(AlchemdiaSmoothMeshAngleDlg, CDialog)

AlchemdiaSmoothMeshAngleDlg::AlchemdiaSmoothMeshAngleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(AlchemdiaSmoothMeshAngleDlg::IDD, pParent)
{

}

AlchemdiaSmoothMeshAngleDlg::~AlchemdiaSmoothMeshAngleDlg()
{
}

void AlchemdiaSmoothMeshAngleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AlchemdiaSmoothMeshAngleDlg, CDialog)
	ON_EN_CHANGE(IDC_RICHEDIT21, &AlchemdiaSmoothMeshAngleDlg::OnEnChangeRichedit21)
END_MESSAGE_MAP()


// AlchemdiaSmoothMeshAngleDlg message handlers

void AlchemdiaSmoothMeshAngleDlg::OnEnChangeRichedit21()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
