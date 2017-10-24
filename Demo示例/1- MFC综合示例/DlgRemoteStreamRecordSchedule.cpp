/**********************************************************
FileName:    DlgRemoteRecordSchedule.cpp
Description: remote record schedule      
Date:        2008/05/17
Note: 		<Global>struct, macro refer to GeneralDef.h, global variants and API refer to ClientDemo.cpp      
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/


#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgRemoteStreamRecordSchedule.h"



// CDlgRemoteStreamRecordSchedule dialog

/*********************************************************
  Function:	CDlgRemoteStreamRecordSchedule
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgRemoteStreamRecordSchedule, CDialog)
CDlgRemoteStreamRecordSchedule::CDlgRemoteStreamRecordSchedule(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteStreamRecordSchedule::IDD, pParent)
	, m_bCheckAllDay(FALSE)
	, m_iHour11(0)
	, m_iMin11(0)
	, m_iHour12(0)
	, m_iMin12(0)
	, m_iHour21(0)
	, m_iMin21(0)
	, m_iHour22(0)
	, m_iMin22(0)
	, m_iHour31(0)
	, m_iMin31(0)
	, m_iHour32(0)
	, m_iMin32(0)
	, m_iHour41(0)
	, m_iMin41(0)
	, m_iHour42(0)
	, m_iMin42(0)
	, m_iHour51(0)
	, m_iMin51(0)
	, m_iHour52(0)
	, m_iMin52(0)
	, m_iHour61(0)
	, m_iMin61(0)
	, m_iHour62(0)
	, m_iMin62(0)
	, m_iHour71(0)
	, m_iMin71(0)
	, m_iHour72(0)
	, m_iMin72(0)
	, m_iHour81(0)
	, m_iMin81(0)
	, m_iHour82(0)
	, m_iMin82(0)
	, m_nDate(0)
	, m_nCopyDate(0)
	, m_pstruStreamRecordInfo(NULL)
{
    m_lServerID = -1;
    m_lChannel = -1; 
    m_iDevIndex = -1;
}

/*********************************************************
  Function:	~CDlgRemoteStreamRecordSchedule
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgRemoteStreamRecordSchedule::~CDlgRemoteStreamRecordSchedule()
{
}

/*********************************************************
Function:	TimeTest
Desc:		check time settings
Input:	
Output:	
Return:	TRUE,correct schedule;FALSE,incorrect schedule;
**********************************************************/
BOOL CDlgRemoteStreamRecordSchedule::TimeTest()
{
	int i = 0;
	int j = 0;
	WORD wStartTime[MAX_TIMESEGMENT_V30], wStopTime[MAX_TIMESEGMENT_V30];
	char szLan[128] = {0};
	UpdateData(TRUE);
	if ((m_iHour11 < 0) || (m_iHour11 > 24) || (m_iHour12 < 0) || (m_iHour12 > 24) ||	\
		(m_iHour21 < 0) || (m_iHour21 > 24) || (m_iHour22 < 0) || (m_iHour22 > 24) ||	\
		(m_iHour31 < 0) || (m_iHour31 > 24) || (m_iHour32 < 0) || (m_iHour32 > 24) ||	\
		(m_iHour41 < 0) || (m_iHour41 > 24) || (m_iHour42 < 0) || (m_iHour42 > 24) ||   \
		(m_iHour51 < 0) || (m_iHour51 > 24) || (m_iHour52 < 0) || (m_iHour52 > 24) ||	\
		(m_iHour61 < 0) || (m_iHour61 > 24) || (m_iHour62 < 0) || (m_iHour62 > 24) ||	\
		(m_iHour71 < 0) || (m_iHour71 > 24) || (m_iHour72 < 0) || (m_iHour72 > 24) ||	\
		(m_iHour81 < 0) || (m_iHour81 > 24) || (m_iHour82 < 0) || (m_iHour82 > 24))
	{
		g_StringLanType(szLan, "小时范围在0 -- 24之间", "Hour between 0 - 24 ");
		AfxMessageBox(szLan);
		return FALSE;
	}
	if ((m_iMin11 < 0) || (m_iMin11 > 60) || (m_iMin12 < 0) || (m_iMin12 > 60) ||	\
		(m_iMin21 < 0) || (m_iMin21 > 60) || (m_iMin22 < 0) || (m_iMin22 > 60) ||	\
		(m_iMin31 < 0) || (m_iMin31 > 60) || (m_iMin32 < 0) || (m_iMin32 > 60) ||	\
		(m_iMin41 < 0) || (m_iMin41 > 60) || (m_iMin42 < 0) || (m_iMin42 > 60) ||   \
		(m_iMin51 < 0) || (m_iMin51 > 60) || (m_iMin52 < 0) || (m_iMin52 > 60) ||	\
		(m_iMin61 < 0) || (m_iMin61 > 60) || (m_iMin62 < 0) || (m_iMin62 > 60) ||	\
		(m_iMin71 < 0) || (m_iMin71 > 60) || (m_iMin72 < 0) || (m_iMin72 > 60) ||	\
		(m_iMin81 < 0) || (m_iMin81 > 60) || (m_iMin82 < 0) || (m_iMin82 > 60))
	{
		g_StringLanType(szLan, "分钟范围在0 -- 60之间", "Minute between 0 - 60 ");
		AfxMessageBox(szLan);
		return FALSE;
	}
	wStartTime[0] = (WORD)(m_iHour11 * 100 + m_iMin11);
	wStartTime[1] = (WORD)(m_iHour21 * 100 + m_iMin21);
	wStartTime[2] = (WORD)(m_iHour31 * 100 + m_iMin31);
	wStartTime[3] = (WORD)(m_iHour41 * 100 + m_iMin41);
	wStopTime[0] = (WORD)(m_iHour12 * 100 + m_iMin12);
	wStopTime[1] = (WORD)(m_iHour22 * 100 + m_iMin22);
	wStopTime[2] = (WORD)(m_iHour32 * 100 + m_iMin32);
	wStopTime[3] = (WORD)(m_iHour42 * 100 + m_iMin42);
	wStartTime[4] = (WORD)(m_iHour51 * 100 + m_iMin51);
	wStartTime[5] = (WORD)(m_iHour61 * 100 + m_iMin61);
	wStartTime[6] = (WORD)(m_iHour71 * 100 + m_iMin71);
	wStartTime[7] = (WORD)(m_iHour81 * 100 + m_iMin81);
	wStopTime[4] = (WORD)(m_iHour52 * 100 + m_iMin52);
	wStopTime[5] = (WORD)(m_iHour62 * 100 + m_iMin62);
	wStopTime[6] = (WORD)(m_iHour72 * 100 + m_iMin72);
	wStopTime[7] = (WORD)(m_iHour82 * 100 + m_iMin82);
	for (i = 0; i < MAX_TIMESEGMENT_V30; i++)
	{
		if ((wStartTime[i] > 2400) || (wStopTime[i] > 2400))
		{
			g_StringLanType(szLan, "布防时间不能超过24:00", "Fortify time can not be more than 24:00");
			AfxMessageBox(szLan);
			return FALSE;
		}
		if (wStartTime[i] > wStopTime[i])
		{
			g_StringLanType(szLan, "布防起始时间不能大于停止时间", "Fortify start time can not be larger than the record to stop time");
			AfxMessageBox(szLan);
			return FALSE;
		}
		for (j = 0; j < MAX_TIMESEGMENT_V30; j++)
		{
			if (i == j)
			{
				continue;
			}
			if ((wStartTime[i] > wStartTime[j]) && (wStartTime[i] < wStopTime[j]) ||	\
				(wStopTime[i] > wStartTime[j]) && (wStopTime[i] < wStopTime[j]))
			{
				g_StringLanType(szLan, "时间段不能重复", "time can not be repeated");
				AfxMessageBox(szLan);
				return FALSE;
			}
		}
	}
	return TRUE;
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteStreamRecordSchedule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRemoteStreamRecordSchedule)
	DDX_Control(pDX, IDC_COMBO_WEEK_DAY, m_comboWeekday);
	DDX_Check(pDX, IDC_CHK_ALL_DAY, m_bCheckAllDay);
	DDX_Control(pDX, IDC_COMBO_ALL_DAY_TYPE, m_comboAllDayType);
	DDX_Text(pDX, IDC_EDIT_HOUR11, m_iHour11);
	DDX_Text(pDX, IDC_EDIT_MIN11, m_iMin11);
	DDX_Text(pDX, IDC_EDIT_HOUR12, m_iHour12);
	DDX_Text(pDX, IDC_EDIT_MIN12, m_iMin12);
	DDX_Text(pDX, IDC_EDIT_HOUR21, m_iHour21);
	DDX_Text(pDX, IDC_EDIT_MIN21, m_iMin21);
	DDX_Text(pDX, IDC_EDIT_HOUR22, m_iHour22);
	DDX_Text(pDX, IDC_EDIT_MIN22, m_iMin22);
	DDX_Text(pDX, IDC_EDIT_HOUR31, m_iHour31);
	DDX_Text(pDX, IDC_EDIT_MIN31, m_iMin31);
	DDX_Text(pDX, IDC_EDIT_HOUR32, m_iHour32);
	DDX_Text(pDX, IDC_EDIT_MIN32, m_iMin32);
	DDX_Text(pDX, IDC_EDIT_HOUR41, m_iHour41);
	DDX_Text(pDX, IDC_EDIT_MIN41, m_iMin41);
	DDX_Text(pDX, IDC_EDIT_HOUR42, m_iHour42);
	DDX_Text(pDX, IDC_EDIT_MIN42, m_iMin42);
	DDX_Text(pDX, IDC_EDIT_HOUR51, m_iHour51);
	DDX_Text(pDX, IDC_EDIT_MIN51, m_iMin51);
	DDX_Text(pDX, IDC_EDIT_HOUR52, m_iHour52);
	DDX_Text(pDX, IDC_EDIT_MIN52, m_iMin52);
	DDX_Text(pDX, IDC_EDIT_HOUR61, m_iHour61);
	DDX_Text(pDX, IDC_EDIT_MIN61, m_iMin61);
	DDX_Text(pDX, IDC_EDIT_HOUR62, m_iHour62);
	DDX_Text(pDX, IDC_EDIT_MIN62, m_iMin62);
	DDX_Text(pDX, IDC_EDIT_HOUR71, m_iHour71);
	DDX_Text(pDX, IDC_EDIT_MIN71, m_iMin71);
	DDX_Text(pDX, IDC_EDIT_HOUR72, m_iHour72);
	DDX_Text(pDX, IDC_EDIT_MIN72, m_iMin72);
	DDX_Text(pDX, IDC_EDIT_HOUR81, m_iHour81);
	DDX_Text(pDX, IDC_EDIT_MIN81, m_iMin81);
	DDX_Text(pDX, IDC_EDIT_HOUR82, m_iHour82);
	DDX_Text(pDX, IDC_EDIT_MIN82, m_iMin82);
	DDX_Control(pDX, IDC_COMBO_TIME_REC_TYPE1, m_comboTimeRecType1);
	DDX_Control(pDX, IDC_COMBO_TIME_REC_TYPE2, m_comboTimeRecType2);
	DDX_Control(pDX, IDC_COMBO_TIME_REC_TYPE3, m_comboTimeRecType3);
	DDX_Control(pDX, IDC_COMBO_TIME_REC_TYPE4, m_comboTimeRecType4);
	DDX_Control(pDX, IDC_COMBO_COPY_WEEKDAY, m_comboCopyWeekday);
	DDX_Control(pDX, IDC_COMBO_TIME_REC_TYPE5, m_comboTimeRecType5);
	DDX_Control(pDX, IDC_COMBO_TIME_REC_TYPE6, m_comboTimeRecType6);
	DDX_Control(pDX, IDC_COMBO_TIME_REC_TYPE7, m_comboTimeRecType7);
	DDX_Control(pDX, IDC_COMBO_TIME_REC_TYPE8, m_comboTimeRecType8);
    //}}AFX_DATA_MAP
}


/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgRemoteStreamRecordSchedule, CDialog)
	//{{AFX_MSG_MAP(CDlgRemoteStreamRecordSchedule)	
	ON_BN_CLICKED(ID_BTN_REMOTE_REC_OK, OnBnClickedBtnRemoteRecOk)
	ON_BN_CLICKED(ID_BTN_REMOTE_REC_EXIT, OnBnClickedBtnRemoteRecExit)
	ON_BN_CLICKED(IDC_BTN_REMOTE_REC_COPY, OnBnClickedBtnRemoteRecCopy)
	ON_CBN_SELCHANGE(IDC_COMBO_WEEK_DAY, OnCbnSelchangeComboWeekDay)
	ON_BN_CLICKED(IDC_CHK_ALL_DAY, OnBnClickedChkAllDay)
	//}}AFX_MSG_MAP	
END_MESSAGE_MAP()


// CDlgRemoteStreamRecordSchedule message handlers
/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgRemoteStreamRecordSchedule::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	m_nDate = 0;
	m_comboWeekday.SetCurSel(m_nDate);
	m_nCopyDate = 0;
	m_comboCopyWeekday.SetCurSel(m_nCopyDate);
	m_bCheckAllDay = m_pstruStreamRecordInfo->struRecordInfo.struRecAllDay[m_nDate].wAllDayRecord;
	m_comboAllDayType.SetCurSel(m_pstruStreamRecordInfo->struRecordInfo.struRecAllDay[m_nDate].byRecordType);		
	m_comboTimeRecType1.SetCurSel(m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][0].byRecordType);
	m_comboTimeRecType2.SetCurSel(m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][1].byRecordType);
	m_comboTimeRecType3.SetCurSel(m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][2].byRecordType);
	m_comboTimeRecType4.SetCurSel(m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][3].byRecordType);
	m_comboTimeRecType5.SetCurSel(m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][4].byRecordType);
	m_comboTimeRecType6.SetCurSel(m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][5].byRecordType);
	m_comboTimeRecType7.SetCurSel(m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][6].byRecordType);
	m_comboTimeRecType8.SetCurSel(m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][7].byRecordType);

	m_iHour11 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][0].struRecordTime.byStartHour;
	m_iHour12 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][0].struRecordTime.byStopHour;
	m_iHour21 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][1].struRecordTime.byStartHour;
	m_iHour22 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][1].struRecordTime.byStopHour;
	m_iHour31 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][2].struRecordTime.byStartHour;
	m_iHour32 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][2].struRecordTime.byStopHour;
	m_iHour41 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][3].struRecordTime.byStartHour;
	m_iHour42 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][3].struRecordTime.byStopHour;
	m_iMin11 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][0].struRecordTime.byStartMin;
	m_iMin12 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][0].struRecordTime.byStopMin;
	m_iMin21 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][1].struRecordTime.byStartMin;
	m_iMin22 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][1].struRecordTime.byStopMin;
	m_iMin31 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][2].struRecordTime.byStartMin;
	m_iMin32 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][2].struRecordTime.byStopMin;
	m_iMin41 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][3].struRecordTime.byStartMin;
	m_iMin42 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][3].struRecordTime.byStopMin;

	m_iHour51 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][4].struRecordTime.byStartHour;
	m_iHour52 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][4].struRecordTime.byStopHour;
	m_iHour61 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][5].struRecordTime.byStartHour;
	m_iHour62 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][5].struRecordTime.byStopHour;
	m_iHour71 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][6].struRecordTime.byStartHour;
	m_iHour72 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][6].struRecordTime.byStopHour;
	m_iHour81 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][7].struRecordTime.byStartHour;
	m_iHour82 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][7].struRecordTime.byStopHour;
	m_iMin51 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][4].struRecordTime.byStartMin;
	m_iMin52 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][4].struRecordTime.byStopMin;
	m_iMin61 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][5].struRecordTime.byStartMin;
	m_iMin62 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][5].struRecordTime.byStopMin;
	m_iMin71 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][6].struRecordTime.byStartMin;
	m_iMin72 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][6].struRecordTime.byStopMin;
	m_iMin81 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][7].struRecordTime.byStartMin;
	m_iMin82 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][7].struRecordTime.byStopMin;
	EnableControl(!m_bCheckAllDay);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/*********************************************************
Function:	EnableControl
Desc:		Dialog control enable
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteStreamRecordSchedule::EnableControl(BOOL bEnable)
{
	GetDlgItem(IDC_EDIT_HOUR11)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR21)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR31)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR41)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR51)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR61)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR71)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR81)->EnableWindow(bEnable);

	GetDlgItem(IDC_EDIT_MIN11)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN21)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN31)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN41)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN51)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN61)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN71)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN81)->EnableWindow(bEnable);

	GetDlgItem(IDC_EDIT_HOUR12)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR22)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR32)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR42)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR52)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR62)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR72)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR82)->EnableWindow(bEnable);

	GetDlgItem(IDC_EDIT_MIN12)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN22)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN32)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN42)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN52)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN62)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN72)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN82)->EnableWindow(bEnable);

	GetDlgItem(IDC_COMBO_TIME_REC_TYPE1)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_TIME_REC_TYPE2)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_TIME_REC_TYPE3)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_TIME_REC_TYPE4)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_TIME_REC_TYPE5)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_TIME_REC_TYPE6)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_TIME_REC_TYPE7)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_TIME_REC_TYPE8)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_ALL_DAY_TYPE)->EnableWindow(!bEnable);
}

/*********************************************************
Function:	OnBnClickedBtnRemoteRecOk
Desc:		check and update schedule settings
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteStreamRecordSchedule::OnBnClickedBtnRemoteRecOk()
{
	UpdateData(TRUE);
	if (!TimeTest())
	{
		return;
	}
    
    m_pstruStreamRecordInfo->struRecordInfo.struRecAllDay[m_nDate].wAllDayRecord = (WORD)m_bCheckAllDay;
    if (m_bCheckAllDay)
    {		
        m_pstruStreamRecordInfo->struRecordInfo.struRecAllDay[m_nDate].byRecordType = (BYTE)m_comboAllDayType.GetCurSel();
    }
    else
    {
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][0].byRecordType = (BYTE)m_comboTimeRecType1.GetCurSel();
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][1].byRecordType = (BYTE)m_comboTimeRecType2.GetCurSel();
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][2].byRecordType = (BYTE)m_comboTimeRecType3.GetCurSel();
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][3].byRecordType = (BYTE)m_comboTimeRecType4.GetCurSel();	
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][4].byRecordType = (BYTE)m_comboTimeRecType5.GetCurSel();
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][5].byRecordType = (BYTE)m_comboTimeRecType6.GetCurSel();
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][6].byRecordType = (BYTE)m_comboTimeRecType7.GetCurSel();
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][7].byRecordType = (BYTE)m_comboTimeRecType8.GetCurSel();
        
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][0].struRecordTime.byStartHour = (BYTE)m_iHour11;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][0].struRecordTime.byStopHour = (BYTE)m_iHour12;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][1].struRecordTime.byStartHour = (BYTE)m_iHour21;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][1].struRecordTime.byStopHour = (BYTE)m_iHour22;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][2].struRecordTime.byStartHour = (BYTE)m_iHour31;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][2].struRecordTime.byStopHour = (BYTE)m_iHour32;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][3].struRecordTime.byStartHour = (BYTE)m_iHour41;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][3].struRecordTime.byStopHour = (BYTE)m_iHour42;
        
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][0].struRecordTime.byStartMin = (BYTE)m_iMin11;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][0].struRecordTime.byStopMin = (BYTE)m_iMin12;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][1].struRecordTime.byStartMin = (BYTE)m_iMin21;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][1].struRecordTime.byStopMin = (BYTE)m_iMin22;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][2].struRecordTime.byStartMin = (BYTE)m_iMin31;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][2].struRecordTime.byStopMin = (BYTE)m_iMin32;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][3].struRecordTime.byStartMin = (BYTE)m_iMin41;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][3].struRecordTime.byStopMin = (BYTE)m_iMin42;
        
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][4].struRecordTime.byStartHour = (BYTE)m_iHour51;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][4].struRecordTime.byStopHour = (BYTE)m_iHour52;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][5].struRecordTime.byStartHour = (BYTE)m_iHour61;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][5].struRecordTime.byStopHour = (BYTE)m_iHour62;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][6].struRecordTime.byStartHour = (BYTE)m_iHour71;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][6].struRecordTime.byStopHour = (BYTE)m_iHour72;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][7].struRecordTime.byStartHour = (BYTE)m_iHour81;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][7].struRecordTime.byStopHour = (BYTE)m_iHour82;
        
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][4].struRecordTime.byStartMin = (BYTE)m_iMin51;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][4].struRecordTime.byStopMin = (BYTE)m_iMin52;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][5].struRecordTime.byStartMin = (BYTE)m_iMin61;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][5].struRecordTime.byStopMin = (BYTE)m_iMin62;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][6].struRecordTime.byStartMin = (BYTE)m_iMin71;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][6].struRecordTime.byStopMin = (BYTE)m_iMin72;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][7].struRecordTime.byStartMin = (BYTE)m_iMin81;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][7].struRecordTime.byStopMin = (BYTE)m_iMin82;
    }
    GetDlgItem(IDC_BTN_REMOTE_REC_COPY)->EnableWindow(TRUE);


}

/*********************************************************
  Function:	OnBnClickedBtnRemoteRecExit
  Desc:		cancle record schedule settings
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteStreamRecordSchedule::OnBnClickedBtnRemoteRecExit()
{
	CDialog::OnOK();
}

/*********************************************************
Function:	OnBnClickedBtnRemoteRecCopy
Desc:		check and update the schedule settings
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteStreamRecordSchedule::OnBnClickedBtnRemoteRecCopy()
{
	UpdateData(TRUE);
	m_nCopyDate = m_comboCopyWeekday.GetCurSel() - 1;
	if (!TimeTest())
	{
		return;
	}

	if (m_nCopyDate != -1)
	{
        m_pstruStreamRecordInfo->struRecordInfo.struRecAllDay[m_nCopyDate].wAllDayRecord = (WORD)m_bCheckAllDay;
        m_pstruStreamRecordInfo->struRecordInfo.struRecAllDay[m_nCopyDate].byRecordType = (BYTE)m_comboAllDayType.GetCurSel();		
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nCopyDate][0].byRecordType = (BYTE)m_comboTimeRecType1.GetCurSel();
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nCopyDate][1].byRecordType = (BYTE)m_comboTimeRecType2.GetCurSel();
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nCopyDate][2].byRecordType = (BYTE)m_comboTimeRecType3.GetCurSel();
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nCopyDate][3].byRecordType = (BYTE)m_comboTimeRecType4.GetCurSel();	
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nCopyDate][0].struRecordTime.byStartHour = (BYTE)m_iHour11;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nCopyDate][0].struRecordTime.byStopHour = (BYTE)m_iHour12;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nCopyDate][1].struRecordTime.byStartHour = (BYTE)m_iHour21;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nCopyDate][1].struRecordTime.byStopHour = (BYTE)m_iHour22;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nCopyDate][2].struRecordTime.byStartHour = (BYTE)m_iHour31;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nCopyDate][2].struRecordTime.byStopHour = (BYTE)m_iHour32;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nCopyDate][3].struRecordTime.byStartHour = (BYTE)m_iHour41;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nCopyDate][3].struRecordTime.byStopHour = (BYTE)m_iHour42;
        
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nCopyDate][0].struRecordTime.byStartMin = (BYTE)m_iMin11;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nCopyDate][0].struRecordTime.byStopMin = (BYTE)m_iMin12;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nCopyDate][1].struRecordTime.byStartMin = (BYTE)m_iMin21;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nCopyDate][1].struRecordTime.byStopMin = (BYTE)m_iMin22;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nCopyDate][2].struRecordTime.byStartMin = (BYTE)m_iMin31;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nCopyDate][2].struRecordTime.byStopMin = (BYTE)m_iMin32;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nCopyDate][3].struRecordTime.byStartMin = (BYTE)m_iMin41;
        m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nCopyDate][3].struRecordTime.byStopMin = (BYTE)m_iMin42;

	}
	else
	{
		for (int i = 0;i < MAX_DAYS;i++)
		{	
			m_pstruStreamRecordInfo->struRecordInfo.struRecAllDay[i].wAllDayRecord = (WORD)m_bCheckAllDay;
			m_pstruStreamRecordInfo->struRecordInfo.struRecAllDay[i].byRecordType = (BYTE)m_comboAllDayType.GetCurSel();	

			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][0].byRecordType = (BYTE)m_comboTimeRecType1.GetCurSel();
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][1].byRecordType = (BYTE)m_comboTimeRecType2.GetCurSel();
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][2].byRecordType = (BYTE)m_comboTimeRecType3.GetCurSel();
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][3].byRecordType = (BYTE)m_comboTimeRecType4.GetCurSel();	
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][4].byRecordType = (BYTE)m_comboTimeRecType5.GetCurSel();
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][5].byRecordType = (BYTE)m_comboTimeRecType6.GetCurSel();
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][6].byRecordType = (BYTE)m_comboTimeRecType7.GetCurSel();
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][7].byRecordType = (BYTE)m_comboTimeRecType8.GetCurSel();	

			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][0].struRecordTime.byStartHour = (BYTE)m_iHour11;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][0].struRecordTime.byStopHour = (BYTE)m_iHour12;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][1].struRecordTime.byStartHour = (BYTE)m_iHour21;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][1].struRecordTime.byStopHour = (BYTE)m_iHour22;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][2].struRecordTime.byStartHour = (BYTE)m_iHour31;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][2].struRecordTime.byStopHour = (BYTE)m_iHour32;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][3].struRecordTime.byStartHour = (BYTE)m_iHour41;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][3].struRecordTime.byStopHour = (BYTE)m_iHour42;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][4].struRecordTime.byStartHour = (BYTE)m_iHour51;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][4].struRecordTime.byStopHour = (BYTE)m_iHour52;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][5].struRecordTime.byStartHour = (BYTE)m_iHour61;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][5].struRecordTime.byStopHour = (BYTE)m_iHour62;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][6].struRecordTime.byStartHour = (BYTE)m_iHour71;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][6].struRecordTime.byStopHour = (BYTE)m_iHour72;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][7].struRecordTime.byStartHour = (BYTE)m_iHour81;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][7].struRecordTime.byStopHour = (BYTE)m_iHour82;

			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][0].struRecordTime.byStartMin = (BYTE)m_iMin11;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][0].struRecordTime.byStopMin = (BYTE)m_iMin12;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][1].struRecordTime.byStartMin = (BYTE)m_iMin21;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][1].struRecordTime.byStopMin = (BYTE)m_iMin22;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][2].struRecordTime.byStartMin = (BYTE)m_iMin31;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][2].struRecordTime.byStopMin = (BYTE)m_iMin32;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][3].struRecordTime.byStartMin = (BYTE)m_iMin41;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][3].struRecordTime.byStopMin = (BYTE)m_iMin42;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][4].struRecordTime.byStartMin = (BYTE)m_iMin51;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][4].struRecordTime.byStopMin = (BYTE)m_iMin52;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][5].struRecordTime.byStartMin = (BYTE)m_iMin61;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][5].struRecordTime.byStopMin = (BYTE)m_iMin62;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][6].struRecordTime.byStartMin = (BYTE)m_iMin71;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][6].struRecordTime.byStopMin = (BYTE)m_iMin72;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][7].struRecordTime.byStartMin = (BYTE)m_iMin81;
			m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[i][7].struRecordTime.byStopMin = (BYTE)m_iMin82;
		}
	}
}

/*********************************************************
  Function:	OnCbnSelchangeComboWeekDay
  Desc:		display schedule for selected date
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteStreamRecordSchedule::OnCbnSelchangeComboWeekDay()
{
	m_nDate = m_comboWeekday.GetCurSel();	

    m_bCheckAllDay = m_pstruStreamRecordInfo->struRecordInfo.struRecAllDay[m_nDate].wAllDayRecord;
    m_comboAllDayType.SetCurSel(m_pstruStreamRecordInfo->struRecordInfo.struRecAllDay[m_nDate].byRecordType);
    m_comboTimeRecType1.SetCurSel(m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][0].byRecordType);
    m_comboTimeRecType2.SetCurSel(m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][1].byRecordType);
    m_comboTimeRecType3.SetCurSel(m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][2].byRecordType);
    m_comboTimeRecType4.SetCurSel(m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][3].byRecordType);
    m_iHour11 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][0].struRecordTime.byStartHour;
    m_iHour12 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][0].struRecordTime.byStopHour;
    m_iHour21 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][1].struRecordTime.byStartHour;
    m_iHour22 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][1].struRecordTime.byStopHour;
    m_iHour31 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][2].struRecordTime.byStartHour;
    m_iHour32 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][2].struRecordTime.byStopHour;
    m_iHour41 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][3].struRecordTime.byStartHour;
    m_iHour42 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][3].struRecordTime.byStopHour;
    m_iMin11 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][0].struRecordTime.byStartMin;
    m_iMin12 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][0].struRecordTime.byStopMin;
    m_iMin21 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][1].struRecordTime.byStartMin;
    m_iMin22 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][1].struRecordTime.byStopMin;
    m_iMin31 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][2].struRecordTime.byStartMin;
    m_iMin32 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][2].struRecordTime.byStopMin;
    m_iMin41 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][3].struRecordTime.byStartMin;
    m_iMin42 = m_pstruStreamRecordInfo->struRecordInfo.struRecordSched[m_nDate][3].struRecordTime.byStopMin;

	EnableControl(!m_bCheckAllDay);
	GetDlgItem(IDC_BTN_REMOTE_REC_COPY)->EnableWindow(FALSE);
	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnBnClickedChkAllDay
  Desc:		all day recording
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteStreamRecordSchedule::OnBnClickedChkAllDay()
{
	UpdateData(TRUE);
	EnableControl(!m_bCheckAllDay);
}
