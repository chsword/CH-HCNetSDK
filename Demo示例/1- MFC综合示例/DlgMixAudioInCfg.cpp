// DlgMixAudioInCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMixAudioInCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMixAudioInCfg dialog


CDlgMixAudioInCfg::CDlgMixAudioInCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMixAudioInCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMixAudioInCfg)
	m_dwHighPassFilter = 0;
	m_dwNoiseMargin = 0;
	m_bEnableFBC = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgMixAudioInCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMixAudioInCfg)
	DDX_Control(pDX, IDC_CMB_STATIC_FILTER_NUM, m_cmbStaticFilterNum);
	DDX_Control(pDX, IDC_CMB_FILTER_Q_VALUE, m_cmbFilterQValue);
	DDX_Control(pDX, IDC_CMB_MODE, m_cmbMode);
	DDX_Control(pDX, IDC_CMB_AUDIOIN_INDEX, m_cmbAudioInIndex);
	DDX_Text(pDX, IDC_EDIT_HIGH_PASSFILTER, m_dwHighPassFilter);
	DDX_Text(pDX, IDC_EDIT_NOISE_MARGIN, m_dwNoiseMargin);
	DDX_Check(pDX, IDC_CHK_FBC, m_bEnableFBC);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMixAudioInCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgMixAudioInCfg)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_CBN_SELCHANGE(IDC_CMB_AUDIOIN_INDEX, OnSelchangeCmbAudioinIndex)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMixAudioInCfg message handlers

BOOL CDlgMixAudioInCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	char szLan[128] = {0};
	int i = 0;
	m_cmbAudioInIndex.ResetContent();
	for (i = 0; i < 16; i++)
	{
		sprintf(szLan, "MacIn%d", i+1);
		m_cmbAudioInIndex.AddString(szLan);
	}
	for (i = 0; i < 10; i++)
	{
		sprintf(szLan, "LineIn%d", i+1);
		m_cmbAudioInIndex.AddString(szLan);
	}
 
	for (i = g_struDeviceInfo[m_dwDevIndex].iAnalogChanNum; i < g_struDeviceInfo[m_dwDevIndex].iDeviceChanNum; i++)
	{
		//if (g_struDeviceInfo[m_dwDevIndex].pStruChanInfo[i].bEnable)
		{
			m_cmbAudioInIndex.AddString(g_struDeviceInfo[m_dwDevIndex].pStruChanInfo[i].chChanName);
		}
	}

	m_cmbAudioInIndex.SetCurSel(0);
	OnSelchangeCmbAudioinIndex();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMixAudioInCfg::OnBtnGet()
{
	LONG lChannel = m_cmbAudioInIndex.GetCurSel() + 1;

	char szLan[128] = {0};
	NET_DVR_MIX_AUDIOIN_CFG struMixAudioInCfg = {0};
	memset(&struMixAudioInCfg, 0, sizeof(NET_DVR_MIX_AUDIOIN_CFG));
	
	DWORD dwReturnedBytes = 0;
	
	if(NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_MIX_AUDIOIN_CFG, lChannel, &struMixAudioInCfg, sizeof(NET_DVR_MIX_AUDIOIN_CFG), &dwReturnedBytes))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_MIX_AUDIOIN_CFG");
		g_StringLanType(szLan, "ªÒ»°“Ù∆µ ‰»ÎªÏ“Ù≈‰÷√≥…π¶!", "Success to get mix audio parameter config");
		//	AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_MIX_AUDIOIN_CFG");
		g_StringLanType(szLan, "ªÒ»°“Ù∆µ ‰»ÎªÏ“Ù≈‰÷√ ß∞‹!", "Fail to get mix audio parameter config");
		AfxMessageBox(szLan);
		return;
	}

	m_dwHighPassFilter = struMixAudioInCfg.dwHighPassFilter;
	m_dwNoiseMargin = struMixAudioInCfg.dwNoiseMargin;
	m_bEnableFBC = struMixAudioInCfg.struLimitWave.byFBCEnable;
	m_cmbMode.SetCurSel(struMixAudioInCfg.struLimitWave.byMode);
	m_cmbFilterQValue.SetCurSel(struMixAudioInCfg.struLimitWave.byFilterQValue);
	m_cmbStaticFilterNum.SetCurSel(struMixAudioInCfg.struLimitWave.byStaticFilterNum);
	
	UpdateData(FALSE);
}

void CDlgMixAudioInCfg::OnSelchangeCmbAudioinIndex() 
{
	// TODO: Add your control notification handler code here
	LONG lChannel = m_cmbAudioInIndex.GetCurSel() + 1;

	if (lChannel <= 16)//“Ù∆µ ‰»ÎŒ™macIn
	{
		GetDlgItem(IDC_CHK_FBC)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_MODE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CMB_MODE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_FILTER_Q_VALUE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CMB_FILTER_Q_VALUE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_FILTER_NUM)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_OTC)->EnableWindow(TRUE);
		GetDlgItem(IDC_CMB_STATIC_FILTER_NUM)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_LIMIT_WAVE_PARAM)->EnableWindow(TRUE);
	} 
	else
	{
		GetDlgItem(IDC_CHK_FBC)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_MODE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_MODE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_FILTER_Q_VALUE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_FILTER_Q_VALUE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_FILTER_NUM)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_OTC)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMB_STATIC_FILTER_NUM)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_LIMIT_WAVE_PARAM)->EnableWindow(FALSE);
	}

	OnBtnGet();
}


void CDlgMixAudioInCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);

	LONG lChannel = m_cmbAudioInIndex.GetCurSel() + 1;

	char szLan[128] = {0};
	NET_DVR_MIX_AUDIOIN_CFG struMixAudioInCfg = {0};
	memset(&struMixAudioInCfg, 0, sizeof(NET_DVR_MIX_AUDIOIN_CFG));
	
	struMixAudioInCfg.dwSize = sizeof(NET_DVR_MIX_AUDIOIN_CFG);
	struMixAudioInCfg.dwHighPassFilter = m_dwHighPassFilter;
	struMixAudioInCfg.dwNoiseMargin = m_dwNoiseMargin;

	if (lChannel <= 16)//“Ù∆µ ‰»ÎŒ™macIn
	{
		struMixAudioInCfg.struLimitWave.byFBCEnable = m_bEnableFBC;
		struMixAudioInCfg.struLimitWave.byMode = m_cmbMode.GetCurSel();
		struMixAudioInCfg.struLimitWave.byFilterQValue = m_cmbFilterQValue.GetCurSel();
		struMixAudioInCfg.struLimitWave.byStaticFilterNum = m_cmbStaticFilterNum.GetCurSel();
	}
	
	if(NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_MIX_AUDIOIN_CFG, lChannel, &struMixAudioInCfg, sizeof(NET_DVR_MIX_AUDIOIN_CFG)))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_MIX_AUDIOIN_CFG");
		g_StringLanType(szLan, "…Ë÷√“Ù∆µ ‰»ÎªÏ“Ù≈‰÷√≥…π¶!", "Success to set mix audio parameter config");
		//	AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_MIX_AUDIOIN_CFG");
		g_StringLanType(szLan, "…Ë÷√“Ù∆µ ‰»ÎªÏ“Ù≈‰÷√ ß∞‹!", "Fail to set mix audio parameter config");
		AfxMessageBox(szLan);
		return;
	}
}
