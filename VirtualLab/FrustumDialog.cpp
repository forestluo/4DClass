// FrustumDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VirtualLab.h"
#include "VirtualLabDoc.h"
#include "FrustumDialog.h"
#include "afxdialogex.h"


// CFrustumDialog dialog

IMPLEMENT_DYNAMIC(CFrustumDialog, CDialogEx)

CFrustumDialog::CFrustumDialog(int nType,CVirtualLabDoc* pDoc,CWnd* pParent /*=NULL*/)
	: CDialogEx(CFrustumDialog::IDD, pParent)
	, m_nType(nType)
	, m_fMass(1.0f)
	, m_fHeight(0.2f)
	, m_fMinorRadius(0.05f)
	, m_fMajorRadius(0.1f)
	, m_nXRotate(0)
	, m_nYRotate(0)
	, m_nZRotate(0)
	, m_fXPosition(0.0f)
	, m_fYPosition(2.0f)
	, m_fZPosition(0.0f)
{
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Set document.
	m_pDoc = pDoc;
}

CFrustumDialog::~CFrustumDialog()
{
	//Clear value.
	m_pDoc = NULL;
}

void CFrustumDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MASS, m_fMass);
	DDV_MinMaxFloat(pDX, m_fMass, 0.0f, 10000.0f);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_fHeight);
	DDV_MinMaxFloat(pDX, m_fHeight, 0.01f, 10.0f);
	DDX_Text(pDX, IDC_EDIT_RADIUS_MINOR, m_fMinorRadius);
	DDV_MinMaxFloat(pDX, m_fMinorRadius, 0.01f, 10.0f);
	DDX_Text(pDX, IDC_EDIT_RADIUS_MAJOR, m_fMajorRadius);
	DDV_MinMaxFloat(pDX, m_fMajorRadius, 0.01f, 10.0f);

	DDX_Text(pDX, IDC_EDIT_XR, m_nXRotate);
	DDV_MinMaxInt(pDX, m_nXRotate, -360, 360);
	DDX_Text(pDX, IDC_EDIT_YR, m_nYRotate);
	DDV_MinMaxInt(pDX, m_nYRotate, -360, 360);
	DDX_Text(pDX, IDC_EDIT_ZR, m_nZRotate);
	DDV_MinMaxInt(pDX, m_nZRotate, -360, 360);

	DDX_Text(pDX, IDC_EDIT_X, m_fXPosition);
	DDV_MinMaxFloat(pDX, m_fXPosition, -500.0f, 500.0f);
	DDX_Text(pDX, IDC_EDIT_Y, m_fYPosition);
	DDV_MinMaxFloat(pDX, m_fYPosition, -500.0f, 500.0f);
	DDX_Text(pDX, IDC_EDIT_Z, m_fZPosition);
	DDV_MinMaxFloat(pDX, m_fZPosition, -500.0f, 500.0f);

}


BEGIN_MESSAGE_MAP(CFrustumDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFrustumDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CFrustumDialog message handlers


void CFrustumDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();

	//Update data.
	UpdateData(TRUE);

	//Attribute.
	CPrimitiveAttribute attribute;
	//Set type.
	attribute.setType(m_nType);
	//Set height.
	attribute.primitiveData.frustum.height = m_fHeight;
	//Set radius.
	attribute.primitiveData.frustum.topRadius = m_fMinorRadius;
	attribute.primitiveData.frustum.bottomRadius = m_fMajorRadius;

	//Set scale.
	C4DVector3 scale(1.0,1.0,1.0);
	//Set position.
	C4DVector3 position(m_fXPosition,m_fYPosition,m_fZPosition);
	//Set rotation.
	C4DVector3 rotation(m_nXRotate / 180.0f * D3DX_PI,m_nYRotate / 180.0f * D3DX_PI,m_nZRotate / 180.0f * D3DX_PI);
#ifdef _DEBUG
	assert(m_pDoc != NULL);
#endif
	//Check type.
	if(m_nType == CPrimitiveAttribute::frustum0Primitive ||
		m_nType == CPrimitiveAttribute::frustum3Primitive ||
		m_nType == CPrimitiveAttribute::frustum4Primitive ||
		m_nType == CPrimitiveAttribute::frustum6Primitive)
	{
		//Add frustum into scene.
		m_pDoc->application->createModel(attribute,m_fMass,scale,rotation,position);
	}
}
