// DlgNetraEventVedio.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgNetraEventVedio.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNetraEventVedio dialog


CDlgNetraEventVedio::CDlgNetraEventVedio(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNetraEventVedio::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNetraEventVedio)
	m_dwCmdType = 0;
	m_strEventID = _T("");
	m_dwRecordTimeLen = 0;
	m_strStreamID = _T("");
	m_uiChannelNo = 0;
	//}}AFX_DATA_INIT
}


void CDlgNetraEventVedio::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNetraEventVedio)
	DDX_Text(pDX, IDC_EDIT_COMMAND_TYPE, m_dwCmdType);
	DDX_Text(pDX, IDC_EDIT_EVENTID, m_strEventID);
	DDX_Text(pDX, IDC_EDIT_RECORD_TIME, m_dwRecordTimeLen);
	DDX_Text(pDX, IDC_EDIT_STREAMID, m_strStreamID);
	DDX_Text(pDX, IDC_EDIT_CHANNELNO, m_uiChannelNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNetraEventVedio, CDialog)
	//{{AFX_MSG_MAP(CDlgNetraEventVedio)
	ON_BN_CLICKED(IDC_BTN_START, OnBtnStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNetraEventVedio message handlers

void CDlgNetraEventVedio::OnBtnStart() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	NET_DVR_CMD_TRIGGER_PERIOD_RECORD_PARA struCmdTriggerRecordPara;
	memset(&struCmdTriggerRecordPara, 0, sizeof(NET_DVR_CMD_TRIGGER_PERIOD_RECORD_PARA));
	struCmdTriggerRecordPara.struStreamInfo.dwSize = sizeof(NET_DVR_STREAM_INFO);
	strncpy((char*)struCmdTriggerRecordPara.struStreamInfo.byID, m_strStreamID, STREAM_ID_LEN-1);
	struCmdTriggerRecordPara.struStreamInfo.dwChannel = m_uiChannelNo;
	strncpy((char*)struCmdTriggerRecordPara.byEventID,m_strEventID,64);
	struCmdTriggerRecordPara.dwCmdType = m_dwCmdType;
	struCmdTriggerRecordPara.dwRecordTimeLen = m_dwRecordTimeLen;
	
	
	if (NET_DVR_RemoteControl(m_lLoginID, NET_DVR_CMD_TRIGGER_PERIOD_RECORD, &struCmdTriggerRecordPara, sizeof(NET_DVR_CMD_TRIGGER_PERIOD_RECORD_PARA)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl");
	}
	
}
