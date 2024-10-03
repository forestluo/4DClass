// PSEyeSettingDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VirtualLab.h"
#include "VirtualLabDoc.h"
#include "PSEyeSettingDialog.h"
#include "afxdialogex.h"

#include "CLEyeMulticam.h"
#include "ResourceManager.h"
#include "D3DXPSEyeTexture.h"

// CPSEyeSettingDialog dialog

IMPLEMENT_DYNAMIC(CPSEyeSettingDialog, CDialogEx)

CPSEyeSettingDialog::CPSEyeSettingDialog(CVirtualLabDoc* pDoc,CWnd* pParent /*=NULL*/)
	: CDialogEx(CPSEyeSettingDialog::IDD, pParent)
	, m_bDynamicTrack(FALSE)
	, m_nGain(50)
	, m_nExposure(511)
	, m_nRotation(0)
	, m_nZoom(0)
{
#ifdef _DEBUG
	assert(pDoc != NULL);
#endif
	//Set document.
	m_pDoc = pDoc;
}

CPSEyeSettingDialog::~CPSEyeSettingDialog()
{
	//Clear value.
	m_pDoc = NULL;
}

void CPSEyeSettingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PSEYE_NAME, m_names);
	DDX_Check(pDX, IDC_CHECK_DYNAMIC_TRACE, m_bDynamicTrack);
	DDX_Text(pDX, IDC_EDIT_GAIN, m_nGain);
	DDV_MinMaxInt(pDX, m_nGain, 0, 79);
	DDX_Text(pDX, IDC_EDIT_EXPOSURE, m_nExposure);
	DDV_MinMaxInt(pDX, m_nExposure, 0, 511);
	DDX_Text(pDX, IDC_EDIT_ROTATION, m_nRotation);
	DDV_MinMaxInt(pDX, m_nRotation, -500, +500);
	DDX_Text(pDX, IDC_EDIT_ZOOM, m_nZoom);
	DDV_MinMaxInt(pDX, m_nZoom, -500, +500);
}


BEGIN_MESSAGE_MAP(CPSEyeSettingDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPSEyeSettingDialog::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_PSEYE_NAME, &CPSEyeSettingDialog::OnCbnSelchangeComboPseyeName)
END_MESSAGE_MAP()


// CPSEyeSettingDialog message handlers

BOOL CPSEyeSettingDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

#ifdef _DEBUG
	assert(m_pDoc != NULL);
	assert(m_pDoc->application != NULL);
#endif
	//Open lock.
	m_pDoc->application->openLock();
	{
		//Enumeration.
		CListNodeEnumeration iterator;
		//Get resource manager.
		CResourceManager* resourceManager = m_pDoc->application->getResourceManager();
#ifdef _DEBUG
		assert(resourceManager != NULL);
#endif
		//Get enumeration.
		resourceManager->CTextureManager::getEnumeration(iterator);

		//First device.
		CD3DXPSEyeTexture* firstDevice = NULL;
		//Do while.
		while(iterator.hasMoreElements())
		{
			//Get texture.
			CD3DXTexture* pTexture = (CD3DXTexture *)iterator.nextElement();
#ifdef _DEBUG
			assert(pTexture != NULL);
#endif
			//Check result.
			if(!IS_PSEYEDYNAMICTEXTURE_BASE(pTexture)) continue;
			//Add name into list.
			m_names.AddString(pTexture->getName().getCString());
			//Check result.
			if(firstDevice == NULL) firstDevice = (CD3DXPSEyeTexture *)pTexture;
		}
		//Check result.
		if(firstDevice != NULL)
		{
			//Set default selection.
			m_names.SetCurSel(0);
			//Get value.
			m_bDynamicTrack = firstDevice->isDetecting();
			m_nZoom = firstDevice->getValue(CLEYE_ZOOM);
			m_nGain = firstDevice->getValue(CLEYE_GAIN);
			m_nExposure = firstDevice->getValue(CLEYE_EXPOSURE);
			m_nRotation = firstDevice->getValue(CLEYE_ROTATION);
		}
	}
	//Close lock.
	m_pDoc->application->closeLock();
	//Update data.
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CPSEyeSettingDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();

	//Update data.
	UpdateData(TRUE);

	//Get current selection.
	int nSelection = m_names.GetCurSel();
	//Open lock.
	m_pDoc->application->openLock();
	{
		//Enumeration.
		CListNodeEnumeration iterator;
		//Get resource manager.
		CResourceManager* resourceManager = m_pDoc->application->getResourceManager();
#ifdef _DEBUG
		assert(resourceManager != NULL);
#endif
		//Get enumeration.
		resourceManager->CTextureManager::getEnumeration(iterator);

		//Selected device.
		CD3DXPSEyeTexture* selectedDevice = NULL;
		//Do while.
		while(iterator.hasMoreElements())
		{
			//Get texture.
			CD3DXTexture* pTexture = (CD3DXTexture *)iterator.nextElement();
#ifdef _DEBUG
			assert(pTexture != NULL);
#endif
			//Check result.
			if(!IS_PSEYEDYNAMICTEXTURE_BASE(pTexture)) continue;
			//Check result.
			if(nSelection > 0)
			{
				//Sub selection.
				nSelection --;
			}
			else
			{
				//Set selected device.
				selectedDevice = (CD3DXPSEyeTexture *)pTexture; break;
			}
		}
		//Check result.
		if(selectedDevice != NULL)
		{
			//Check flag.
			if(m_bDynamicTrack)
			{
				//Enable detecting.
				if(!selectedDevice->isDetecting()) selectedDevice->enableDetection();
			}
			else
			{
				//Disable detecting.
				if(selectedDevice->isDetecting()) selectedDevice->disableDetection();
			}
			//Set value.
			selectedDevice->setValue(CLEYE_ZOOM,m_nZoom);
			selectedDevice->setValue(CLEYE_GAIN,m_nGain);
			selectedDevice->setValue(CLEYE_EXPOSURE,m_nExposure);
			selectedDevice->setValue(CLEYE_ROTATION,m_nRotation);
		}
	}
	//Close lock.
	m_pDoc->application->closeLock();
}

void CPSEyeSettingDialog::OnCbnSelchangeComboPseyeName()
{
#ifdef _DEBUG
	assert(m_pDoc != NULL);
	assert(m_pDoc->application != NULL);
#endif
	//Get current selection.
	int nSelection = m_names.GetCurSel();
	//Open lock.
	m_pDoc->application->openLock();
	{
		//Enumeration.
		CListNodeEnumeration iterator;
		//Get resource manager.
		CResourceManager* resourceManager = m_pDoc->application->getResourceManager();
#ifdef _DEBUG
		assert(resourceManager != NULL);
#endif
		//Get enumeration.
		resourceManager->CTextureManager::getEnumeration(iterator);

		//Selected device.
		CD3DXPSEyeTexture* selectedDevice = NULL;
		//Do while.
		while(iterator.hasMoreElements())
		{
			//Get texture.
			CD3DXTexture* pTexture = (CD3DXTexture *)iterator.nextElement();
#ifdef _DEBUG
			assert(pTexture != NULL);
#endif
			//Check result.
			if(!IS_PSEYEDYNAMICTEXTURE_BASE(pTexture)) continue;
			//Check result.
			if(nSelection > 0)
			{
				//Sub selection.
				nSelection --;
			}
			else
			{
				//Set selected device.
				selectedDevice = (CD3DXPSEyeTexture *)pTexture; break;
			}
		}
		//Check result.
		if(selectedDevice != NULL)
		{
			//Get value.
			m_bDynamicTrack = selectedDevice->isDetecting();
			m_nZoom = selectedDevice->getValue(CLEYE_ZOOM);
			m_nGain = selectedDevice->getValue(CLEYE_GAIN);
			m_nExposure = selectedDevice->getValue(CLEYE_EXPOSURE);
			m_nRotation = selectedDevice->getValue(CLEYE_ROTATION);
		}
	}
	//Close lock.
	m_pDoc->application->closeLock();
	//Update data.
	UpdateData(FALSE);
}
