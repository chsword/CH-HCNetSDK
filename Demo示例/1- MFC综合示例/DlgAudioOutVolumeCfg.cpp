// DlgAudioOutVolumeCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAudioOutVolumeCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAudioOutVolumeCfg dialog


CDlgAudioOutVolumeCfg::CDlgAudioOutVolumeCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAudioOutVolumeCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAudioOutVolumeCfg)
	m_csVolume = _T("");
	//}}AFX_DATA_INIT
}


void CDlgAudioOutVolumeCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAudioOutVolumeCfg)
	DDX_Control(pDX, IDC_SLIDER_VOLUME, m_sliderVolume);
	DDX_Control(pDX, IDC_CMB_AUDIOIN_CHAN_NO, m_cmbAudioOutChan);
	DDX_Text(pDX, IDC_STATIC_VOLUME, m_csVolume);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAudioOutVolumeCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgAudioOutVolumeCfg)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_VOLUME, OnCustomdrawSliderVolume)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAudioOutVolumeCfg message handlers

void CDlgAudioOutVolumeCfg::OnCustomdrawSliderVolume(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE); 
    m_csVolume.Format("%d", m_sliderVolume.GetPos()); 
    UpdateData(FALSE);

	*pResult = 0;
}

void CDlgAudioOutVolumeCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	
	char szLan[128] = {0};
	NET_DVR_VOLUME_CFG struVolumeCfg = {0};
	memset(&struVolumeCfg, 0, sizeof(NET_DVR_VOLUME_CFG));
	
	DWORD dwReturnedBytes = 0;

	LONG lChannel = m_cmbAudioOutChan.GetCurSel() + 1;
	
	if(NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_AUDIOOUT_VOLUME_CFG, lChannel, &struVolumeCfg, sizeof(NET_DVR_VOLUME_CFG), &dwReturnedBytes))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_AUDIOOUT_VOLUME_CFG");
		g_StringLanType(szLan, "获取音频输出口音量调节参数成功!", "Success to get audio out volume parameter config");
		//	AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_AUDIOOUT_VOLUME_CFG");
		g_StringLanType(szLan, "获取音频输出口音量调节参数失败!", "Fail to get audio out volume parameter config");
		AfxMessageBox(szLan);
		return;
	}
	
	m_sliderVolume.SetPos(struVolumeCfg.wVolume[0]);
	
	UpdateData(FALSE);
}

void CDlgAudioOutVolumeCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);
	
	char szLan[128] = {0};
	NET_DVR_VOLUME_CFG struVolumeCfg = {0};
	memset(&struVolumeCfg, 0, sizeof(NET_DVR_VOLUME_CFG));
	
	struVolumeCfg.dwSize = sizeof(NET_DVR_VOLUME_CFG);
	
	struVolumeCfg.wVolume[0] = m_sliderVolume.GetPos();

	LONG lChannel = m_cmbAudioOutChan.GetCurSel() + 1;

	if(NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_AUDIOOUT_VOLUME_CFG, lChannel, &struVolumeCfg, sizeof(NET_DVR_VOLUME_CFG)))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_AUDIOOUT_VOLUME_CFG");
		g_StringLanType(szLan, "设置音频输出口音量调节参数成功!", "Success to set audio out volume parameter config");
		//	AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_AUDIOOUT_VOLUME_CFG");
		g_StringLanType(szLan, "设置音频输出口音量调节参数失败!", "Fail to set audio out volume parameter config");
		AfxMessageBox(szLan);
		return;
	}
}

BOOL CDlgAudioOutVolumeCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	char szLan[128] = {0};
	
	// 	m_cmbAudioInChan.ResetContent();
	// 
	// 	int i = 0;
	// 
	// 	for (i = 0; i < 16; i++)
	// 	{
	// 		sprintf(szLan, "MIC%d", i+1);
	// 		m_cmbAudioInChan.InsertString(0, szLan);
	// 		m_cmbAudioInChan.SetItemData(0, i+1);
	// 	}
	// 
	// 	for (i = 0; i < 4; i++)
	// 	{
	// 	}
	// 	
	// 	m_cmbAudioInChan.InsertString(0, "VGA in4");
	// 	m_cmbAudioInChan.SetItemData(0, 12);
	// 
	// 	m_cmbAudioInChan.InsertString(0, "VGA in4");
	// 	m_cmbAudioInChan.SetItemData(0, 12);
	// 
	// 	m_cmbAudioInChan.InsertString(0, "VGA in4");
	// 	m_cmbAudioInChan.SetItemData(0, 12);
	// 
	// 	m_cmbAudioInChan.InsertString(0, "VGA in4");
	// 	m_cmbAudioInChan.SetItemData(0, 12);
	// 
	// 	m_cmbAudioInChan.InsertString(0, "VGA in4");
	// 	m_cmbAudioInChan.SetItemData(0, 12);
	
	m_cmbAudioOutChan.SetCurSel(0);
	
	m_sliderVolume.SetRange(0, 127);
	m_sliderVolume.SetPos(0);
	
	sprintf(szLan, "%d", 0);
	SetDlgItemText(IDC_STATIC_VOLUME, szLan);
	
	OnBtnGet();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
