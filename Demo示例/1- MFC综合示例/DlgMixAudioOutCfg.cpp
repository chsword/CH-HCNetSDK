// DlgMixAudioOutCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMixAudioOutCfg.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMixAudioOutCfg dialog


CDlgMixAudioOutCfg::CDlgMixAudioOutCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMixAudioOutCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMixAudioOutCfg)
	m_bEnableModulator = FALSE;
	m_bEnablePostFilter = FALSE;
	m_bEnableLimitPressure = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgMixAudioOutCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMixAudioOutCfg)
	DDX_Control(pDX, IDC_CMB_OUTPUT_GAIN, m_cmbOutputGain);
	DDX_Control(pDX, IDC_CMB_TRIGGER_TIME, m_cmbTriggerTime);
	DDX_Control(pDX, IDC_CMB_RECOVERYGAIN, m_cmbRecoveryGain);
	DDX_Control(pDX, IDC_CMB_MODULATOR_VALUE, m_cmbModulatorValue);
	DDX_Control(pDX, IDC_CMB_FREE_TIME, m_cmbFreeTime);
	DDX_Control(pDX, IDC_CMB_COMPRESS_RATE, m_cmbCompressRate);
	DDX_Control(pDX, IDC_CMB_AUDIO_OUT_INDEX, m_cmbAudioOutIndex);
	DDX_Control(pDX, IDC_CMB_COMPRESS_THRESHOLD, m_cmbCompressThreshold);
	DDX_Control(pDX, IDC_CMB_COMPRESS_MODE, m_cmbCompressMode);
	DDX_Check(pDX, IDC_CHK_MODULATOR, m_bEnableModulator);
	DDX_Check(pDX, IDC_CHK_POST_FILTER, m_bEnablePostFilter);
	DDX_Check(pDX, IDC_CHK_LIMIT_PRESSURE, m_bEnableLimitPressure);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMixAudioOutCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgMixAudioOutCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMixAudioOutCfg message handlers

void CDlgMixAudioOutCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	
	LONG lChannel = m_cmbAudioOutIndex.GetCurSel() + 1;
	
	char szLan[128] = {0};
	NET_DVR_MIX_AUDIOOUT_CFG struMixAudioOutCfg = {0};
	memset(&struMixAudioOutCfg, 0, sizeof(NET_DVR_MIX_AUDIOOUT_CFG));
	struMixAudioOutCfg.dwSize = sizeof(struMixAudioOutCfg);
	
	DWORD dwReturnedBytes = 0;
	
	if(NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_MIX_AUDIOOUT_CFG, lChannel, &struMixAudioOutCfg, sizeof(NET_DVR_MIX_AUDIOOUT_CFG), &dwReturnedBytes))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_MIX_AUDIOOUT_CFG");
		g_StringLanType(szLan, "ªÒ»°“Ù∆µ ‰≥ˆªÏ“Ù≈‰÷√≥…π¶!", "Success to get mix audio out parameter config");
		//	AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_MIX_AUDIOOUT_CFG");
		g_StringLanType(szLan, "ªÒ»°“Ù∆µ ‰≥ˆªÏ“Ù≈‰÷√ ß∞‹!", "Fail to get mix audio out parameter config");
		AfxMessageBox(szLan);
		return;
	}
	
	m_bEnableLimitPressure = struMixAudioOutCfg.byLimitPressure;
	m_bEnableModulator = struMixAudioOutCfg.byModulatorEnbale;
	m_bEnablePostFilter = struMixAudioOutCfg.byPostFilter;
	m_cmbFreeTime.SetCurSel(struMixAudioOutCfg.wFreeTime);
	m_cmbModulatorValue.SetCurSel(struMixAudioOutCfg.wModulatorValue);
	m_cmbTriggerTime.SetCurSel(struMixAudioOutCfg.wTriggerTime);
	m_cmbCompressMode.SetCurSel(struMixAudioOutCfg.byCompressMode);
	m_cmbCompressThreshold.SetCurSel(struMixAudioOutCfg.byCompressThreshold);
    m_cmbCompressRate.SetCurSel(struMixAudioOutCfg.byCompressRate);
    m_cmbRecoveryGain.SetCurSel(struMixAudioOutCfg.byRecoveryGain);
    m_cmbOutputGain.SetCurSel(100-struMixAudioOutCfg.byOutputGain);
	
	UpdateData(FALSE);
}

void CDlgMixAudioOutCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	
	LONG lChannel = m_cmbAudioOutIndex.GetCurSel() + 1;
	
	char szLan[128] = {0};
	NET_DVR_MIX_AUDIOOUT_CFG struMixAudioOutCfg = {0};
	memset(&struMixAudioOutCfg, 0, sizeof(NET_DVR_MIX_AUDIOOUT_CFG));
	
	struMixAudioOutCfg.dwSize = sizeof(NET_DVR_MIX_AUDIOOUT_CFG);

	struMixAudioOutCfg.byLimitPressure = m_bEnableLimitPressure;
	struMixAudioOutCfg.byModulatorEnbale = m_bEnableModulator;
	struMixAudioOutCfg.byPostFilter = m_bEnablePostFilter;
	struMixAudioOutCfg.wFreeTime = (WORD)m_cmbFreeTime.GetCurSel();
	struMixAudioOutCfg.wModulatorValue = (WORD)m_cmbModulatorValue.GetCurSel();
	struMixAudioOutCfg.wTriggerTime = (WORD)m_cmbTriggerTime.GetCurSel();
	struMixAudioOutCfg.byCompressMode = m_cmbCompressMode.GetCurSel();
	struMixAudioOutCfg.byCompressThreshold = m_cmbCompressThreshold.GetCurSel();
	struMixAudioOutCfg.byCompressRate = m_cmbCompressRate.GetCurSel();
    struMixAudioOutCfg.byRecoveryGain = m_cmbRecoveryGain.GetCurSel();
    struMixAudioOutCfg.byOutputGain  = 100 - m_cmbOutputGain.GetCurSel();


	if(NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_MIX_AUDIOOUT_CFG, lChannel, &struMixAudioOutCfg, sizeof(NET_DVR_MIX_AUDIOOUT_CFG)))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_MIX_AUDIOOUT_CFG");
		g_StringLanType(szLan, "…Ë÷√“Ù∆µ ‰≥ˆªÏ“Ù≈‰÷√≥…π¶!", "Success to set mix audio out parameter config");
		//	AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_MIX_AUDIOOUT_CFG");
		g_StringLanType(szLan, "…Ë÷√“Ù∆µ ‰≥ˆªÏ“Ù≈‰÷√ ß∞‹!", "Fail to set mix audio out parameter config");
		AfxMessageBox(szLan);
		return;
	}
}

BOOL CDlgMixAudioOutCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

    char szLan[64] = {0};
    int i = 0;
    m_cmbModulatorValue.ResetContent();
    m_cmbTriggerTime.ResetContent();
    m_cmbFreeTime.ResetContent();
    m_cmbCompressRate.ResetContent();
    for ( i = 0; i < 128; i++)
    {
        sprintf(szLan,"%d",i);
        m_cmbModulatorValue.AddString(szLan);
        m_cmbTriggerTime.AddString(szLan);
        m_cmbFreeTime.AddString(szLan);
        m_cmbCompressRate.AddString(szLan);
    }
    
    m_cmbCompressThreshold.ResetContent();
    m_cmbRecoveryGain.ResetContent();
    for (i = 0; i<4;i++)
    {
        DWORD dwTest = (DWORD)pow((double)2,i);
        sprintf(szLan,"%d x",dwTest);
        m_cmbCompressThreshold.AddString(szLan);
        m_cmbRecoveryGain.AddString(szLan);
    }

    
    m_cmbOutputGain.ResetContent();
    for (i = 0; i<= 100;i++)
    {
        sprintf(szLan,"%d",(i-100));
        m_cmbOutputGain.AddString(szLan);
    }

	m_cmbAudioOutIndex.SetCurSel(0);
	
	OnBtnGet();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
