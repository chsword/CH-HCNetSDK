// DlgVcaBVCalibrate.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaBVCalibrate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaBVCalibrate dialog


CDlgVcaBVCalibrate::CDlgVcaBVCalibrate(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaBVCalibrate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaBVCalibrate)
	m_dwCameraHeight = 0;
	m_fPitchAngle = 0.0f;
	m_fInclineAngle = 0.0f;
	m_bEnable = FALSE;
	m_dwSampleCameraHeight = 0;
	m_dwSampleHumanHeight = 0;
	m_fX = 0.0f;
	m_fY = 0.0f;
	m_dwCameraHeightSample = 0;
	m_fInclineAngleSample = 0.0f;
	m_fPitchAngleSample = 0.0f;
	m_fBvCalibration = 0.0f;
	m_iID = 0;
	//}}AFX_DATA_INIT
	m_lServerID = -1;
    m_iDevIndex = -1;
    m_lChannel = -1;
	m_lPlayHandle = -1;
	m_iCaliType = 0;

	memset(&m_struDirectCaliCfg, 0, sizeof(m_struDirectCaliCfg));
	memset(&m_struSampleCaliCfg, 0, sizeof(m_struSampleCaliCfg));
	memset(&m_struPoint, 0, sizeof(m_struPoint));
	memset(&m_struGetSampleCaliCfg, 0, sizeof(m_struGetSampleCaliCfg));
	memset(&m_struVerifyRect, 0, sizeof(m_struVerifyRect));
}

CDlgVcaBVCalibrate::~CDlgVcaBVCalibrate()
{
	StopPlay();
}

void CDlgVcaBVCalibrate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaBVCalibrate)
	DDX_Control(pDX, IDC_COMBO_GET_CALIB_TYPE, m_comGetCalibType);
	DDX_Control(pDX, IDC_COMBO_CALIB_TYPE, m_comCalibType);
	DDX_Control(pDX, IDC_COMBO_VIDEO_TYPE, m_comVideoType);
	DDX_Control(pDX, IDC_COMBO_CAILB_ID_SAMPLE, m_comCailbIDSample);
	DDX_Control(pDX, IDC_COMBO_CAILB_ID, m_comCailbID);
	DDX_Text(pDX, IDC_EDIT_CAMEAR_HEIGHT, m_dwCameraHeight);
	DDX_Text(pDX, IDC_EDIT_PITCH_ANGLE, m_fPitchAngle);
	DDX_Text(pDX, IDC_EDIT_INCLINE_ANGLE, m_fInclineAngle);
	DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
	DDX_Text(pDX, IDC_EDIT_SAMPLE_CAMEAR_HEIGHT, m_dwSampleCameraHeight);
	DDX_Text(pDX, IDC_EDIT_SAMPLE_HUMAN_HEIGHT, m_dwSampleHumanHeight);
	DDX_Text(pDX, IDC_EDIT_POINT_X, m_fX);
	DDX_Text(pDX, IDC_EDIT_POINT_Y, m_fY);
	DDX_Text(pDX, IDC_EDIT_CAMEAR_HEIGHT_SAMPLE, m_dwCameraHeightSample);
	DDX_Text(pDX, IDC_EDIT_INCLINE_ANGLE_SAMPLE, m_fInclineAngleSample);
	DDX_Text(pDX, IDC_EDIT_PITCH_ANGLE_SAMPLE, m_fPitchAngleSample);
	DDX_Text(pDX, IDC_EDIT_BV_CALIBRATION, m_fBvCalibration);
	DDX_Text(pDX, IDC_EDIT_ID, m_iID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaBVCalibrate, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaBVCalibrate)
	ON_BN_CLICKED(IDC_BTN_GET_DIRECT_CALI, OnBtnGetDirectCali)
	ON_BN_CLICKED(IDC_BTN_SET_DIRECT_CALI, OnBtnSetDirectCali)
	ON_BN_CLICKED(IDC_BTN_BEGIN_CALIB, OnBtnBeginCalib)
	ON_BN_CLICKED(IDC_BTN_SET_CALIB, OnBtnSetCalib)
	ON_BN_CLICKED(IDC_BTN_END_CALIB, OnBtnEndCalib)
	ON_BN_CLICKED(IDC_BTN_GET_CALIB, OnBtnGetCalib)
	ON_CBN_SELCHANGE(IDC_COMBO_CAILB_ID_SAMPLE, OnSelchangeComboCailbIdSample)
	ON_BN_CLICKED(IDC_BTN_VERIFY_BV_CALIBRATION, OnBtnVerifyBvCalibration)
	ON_BN_CLICKED(IDC_BTN_GET_OUTPUT_VIDEO_TYPE, OnBtnGetOutputVideoType)
	ON_BN_CLICKED(IDC_BTN_SET_OUTPUT_VIDEO_TYPE, OnBtnSetOutputVideoType)
	ON_BN_CLICKED(IDC_BTN_GET_CALIB_TYPE, OnBtnGetCalibType)
	ON_CBN_SELCHANGE(IDC_COMBO_CALIB_TYPE, OnSelchangeComboCalibType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaBVCalibrate message handlers

BOOL CDlgVcaBVCalibrate::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GetDlgItem(IDC_PLAYWND)->GetClientRect(&m_rcWndRect);
	// TODO: Add extra initialization here
	RealPlay();
	
	m_comCalibType.SetCurSel(0);

	OnSelchangeComboCalibType() ;

	OnBtnGetCalibType();
	
	OnBtnGetOutputVideoType();

// 	GetDlgItem(IDC_STATIC_DIRECT_CALIB)->ShowWindow(SW_SHOW);
// 	GetDlgItem(IDC_STATIC_SAMPLE_CALIB)->ShowWindow(SW_SHOW);


// 
// 	if (ENUM_BV_CALIBRATION_DIRECT == m_iCaliType)
// 	{
// 		GetDlgItem(IDC_STATIC_DIRECT_CALIB)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_SAMPLE_CALIB)->ShowWindow(SW_SHOW);
// 
// 		
// 		GetDlgItem(IDC_STATIC_BEGIN_CALIB)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_SAMPLE_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_SAMPLE_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_SAMPLE_CAMEAR_HEIGHT2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_SAMPLE_HUMAN_HEIGHT)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_SAMPLE_HUMAN_HEIGHT)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_SAMPLE_HUMAN_HEIGHT2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_BTN_BEGIN_CALIB)->ShowWindow(SW_HIDE);
// 
// 		GetDlgItem(IDC_STATIC_SET_CALIB)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_CAILB_ID)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_COMBO_CAILB_ID)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_BTN_SET_CALIB)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_BTN_END_CALIB)->ShowWindow(SW_HIDE);
// 
// 		GetDlgItem(IDC_STATIC_GET_CALIB)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_CAMEAR_HEIGHT_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT_SAMPLE2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_PITCH_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_PITCH_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_PITCH_ANGLE_SAMPLE2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_INCLINE_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_INCLINE_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_INCLINE_ANGLE_SAMPLE2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_CAILB_ID_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_COMBO_CAILB_ID_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_POINT)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_POINT_X)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_POINT_X)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_POINT_Y)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_POINT_Y)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_BTN_GET_CALIB)->ShowWindow(SW_HIDE);
// 	} 
// 	else if(ENUM_BV_CALIBRATION_SAMPLE == m_iCaliType)
// 	{
// 		GetDlgItem(IDC_STATIC_DIRECT_CALIB)->ShowWindow(SW_SHOW);
// 		GetDlgItem(IDC_STATIC_SAMPLE_CALIB)->ShowWindow(SW_HIDE);
// 
// 		GetDlgItem(IDC_CHECK_ENABLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_PITCH_ANGLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_PITCH_ANGLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_PITCH_ANGLE2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_INCLINE_ANGLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_INCLINE_ANGLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_INCLINE_ANGLE2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_BTN_SET_DIRECT_CALI)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_BTN_GET_DIRECT_CALI)->ShowWindow(SW_HIDE);
// 	}
// 	else if (ENUM_BV_CALIBRATION_NONE == m_iCaliType)
// 	{
// 		GetDlgItem(IDC_STATIC_DIRECT_CALIB)->ShowWindow(SW_SHOW);
// 		GetDlgItem(IDC_STATIC_SAMPLE_CALIB)->ShowWindow(SW_SHOW);
// 
// 		GetDlgItem(IDC_STATIC_BEGIN_CALIB)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_SAMPLE_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_SAMPLE_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_SAMPLE_CAMEAR_HEIGHT2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_SAMPLE_HUMAN_HEIGHT)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_SAMPLE_HUMAN_HEIGHT)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_SAMPLE_HUMAN_HEIGHT2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_BTN_BEGIN_CALIB)->ShowWindow(SW_HIDE);
// 		
// 		GetDlgItem(IDC_STATIC_SET_CALIB)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_CAILB_ID)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_COMBO_CAILB_ID)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_BTN_SET_CALIB)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_BTN_END_CALIB)->ShowWindow(SW_HIDE);
// 		
// 		GetDlgItem(IDC_STATIC_GET_CALIB)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_CAMEAR_HEIGHT_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT_SAMPLE2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_PITCH_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_PITCH_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_PITCH_ANGLE_SAMPLE2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_INCLINE_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_INCLINE_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_INCLINE_ANGLE_SAMPLE2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_CAILB_ID_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_COMBO_CAILB_ID_SAMPLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_POINT)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_POINT_X)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_POINT_X)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_POINT_Y)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_POINT_Y)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_BTN_GET_CALIB)->ShowWindow(SW_HIDE);
// 
// 		GetDlgItem(IDC_CHECK_ENABLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_PITCH_ANGLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_PITCH_ANGLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_PITCH_ANGLE2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_EDIT_INCLINE_ANGLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_INCLINE_ANGLE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_INCLINE_ANGLE2)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_BTN_SET_DIRECT_CALI)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_BTN_GET_DIRECT_CALI)->ShowWindow(SW_HIDE);
// 	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LONG CDlgVcaBVCalibrate::RealPlay()
{
    NET_DVR_CLIENTINFO struPlay;
    struPlay.hPlayWnd 	= GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
    struPlay.lChannel 	= m_lChannel; 
    struPlay.lLinkMode 	= 0;
    struPlay.sMultiCastIP = "";	
    m_lPlayHandle = NET_DVR_RealPlay_V30(m_lServerID, &struPlay, NULL, NULL, TRUE); 
    BOOL bRet = FALSE;
    if (m_lPlayHandle < 0)
    {
        g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_RealPlay_V30");
        AfxMessageBox("NET_DVR_RealPlay_V30 FAIL");		
    }

    return m_lPlayHandle;
}

BOOL CDlgVcaBVCalibrate::StopPlay()
{
    BOOL bRet = FALSE;
    if (m_lPlayHandle >= 0)
    {
        bRet = NET_DVR_StopRealPlay(m_lPlayHandle);
        if (!bRet)
        {
            AfxMessageBox("Fail to stop preview");
        }
    }
    return bRet;
}

void CDlgVcaBVCalibrate::DrawVerifyCalibration()
{
    CString str;
    CPen    *green_pen;
    green_pen = new CPen;
    green_pen ->CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
    
    GetDlgItem(IDC_PLAYWND)->Invalidate(FALSE);
    
    CBrush brTmp;
    brTmp.CreateSolidBrush(RGB(0,255,0));
    //Draw the bitmap
    CRect rect;
    GetDlgItem(IDC_PLAYWND)->GetClientRect(&rect);
    CPaintDC dc2(GetDlgItem(IDC_PLAYWND));
    m_pic.DrawPicture(dc2.m_hDC, rect.left, rect.top, rect.Width(), rect.Height());
    
    m_pDCRect = GetDlgItem(IDC_PLAYWND)->GetDC();
    
    m_pDCRect->SetBkMode(TRANSPARENT);
    
    m_pDCRect->SelectObject(green_pen);
    
    CRect rectVerify;
    memset(&rectVerify, 0, sizeof(rectVerify));
    rectVerify.left = (int)(m_struVerifyRect.fX*m_rcWndRect.Width());
    rectVerify.top = (int)(m_struVerifyRect.fY*m_rcWndRect.Height());
    rectVerify.right = (int)((m_struVerifyRect.fX+m_struVerifyRect.fWidth)*m_rcWndRect.Width());
    rectVerify.bottom = (int)((m_struVerifyRect.fY+m_struVerifyRect.fHeight)*m_rcWndRect.Height());
    
    FrameRect(m_pDCRect->GetSafeHdc(), rectVerify,brTmp );
    
    m_pDCRect->SelectObject(green_pen);
    GetDlgItem(IDC_PLAYWND)->ReleaseDC(m_pDCRect);
    delete green_pen;
    
}

BOOL CDlgVcaBVCalibrate::PreTranslateMessage(MSG* pMsg) 
{
	CPoint pt(0,0);
    CRect  rcWnd(0,0,0,0);
    GetDlgItem(IDC_PLAYWND)->GetWindowRect(&rcWnd);
    GetCursorPos(&pt);
    TRACE("pt %d %d \n",pt.x, pt.y);
    switch(pMsg->message) 
    {
    case WM_LBUTTONDOWN:
        if(PtInRect(&rcWnd,pt))
        { 
           m_struPoint.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
           m_struPoint.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
		   OnBtnSetCalib() ;
		   //DrawVerifyCalibration();
        }
        break;
    }
	return CDialog::PreTranslateMessage(pMsg);
}
void CDlgVcaBVCalibrate::OnBtnGetDirectCali() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
// 	if (ENUM_BV_CALIBRATION_DIRECT != m_iCaliType)
// 	{
// 		g_StringLanType(szLan, "错误的标定类型!", "Error Calibration Type");
//         AfxMessageBox(szLan);
// 		return;
// 	}

	DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_CALIBRATION, m_lChannel, &m_struDirectCaliCfg, sizeof(m_struDirectCaliCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_CALIBRATION Chan[%d]", m_lChannel);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_CALIBRATION Chan[%d]", m_lChannel); 
		return ;
    }

	m_bEnable = m_struDirectCaliCfg.byEnable;
	
	if(BV_DIRECT_CALIBRATE == m_struDirectCaliCfg.byCalibrationType)
	{
		m_dwCameraHeight = m_struDirectCaliCfg.uCalibrateParam.struBvDirectCalibration.dwCameraHeight;
		m_fPitchAngle = m_struDirectCaliCfg.uCalibrateParam.struBvDirectCalibration.fPitchAngle;
		m_fInclineAngle = m_struDirectCaliCfg.uCalibrateParam.struBvDirectCalibration.fInclineAngle;
	}
	else
	{
		g_StringLanType(szLan, "错误的直接标定类型!", "Error Direct Calibration Type");
        AfxMessageBox(szLan);
		return;
	}

	UpdateData(FALSE);
}

void CDlgVcaBVCalibrate::OnBtnSetDirectCali() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
// 	if (ENUM_BV_CALIBRATION_DIRECT != m_iCaliType)
// 	{
// 		g_StringLanType(szLan, "错误的标定类型!", "Error Calibration Type");
//         AfxMessageBox(szLan);
// 		return;
// 	}

	memset(&m_struDirectCaliCfg, 0, sizeof(m_struDirectCaliCfg));
	m_struDirectCaliCfg.dwSize = sizeof(m_struDirectCaliCfg);
	m_struDirectCaliCfg.byEnable = m_bEnable;
	m_struDirectCaliCfg.byCalibrationType = BV_DIRECT_CALIBRATE;
	m_struDirectCaliCfg.uCalibrateParam.struBvDirectCalibration.dwCameraHeight = m_dwCameraHeight;
	m_struDirectCaliCfg.uCalibrateParam.struBvDirectCalibration.fPitchAngle = m_fPitchAngle;
	m_struDirectCaliCfg.uCalibrateParam.struBvDirectCalibration.fInclineAngle = m_fInclineAngle;

    if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_CALIBRATION, m_lChannel, &m_struDirectCaliCfg, sizeof(m_struDirectCaliCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_CALIBRATION Chan[%d]", m_lChannel);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_CALIBRATION Chan[%d]", m_lChannel); 
		return ;
    }

}

void CDlgVcaBVCalibrate::SetSampleCailbCfg()
{
	if (NET_DVR_RemoteControl(m_lServerID, NET_DVR_CONTROL_BV_SAMPLE_CALIB, &m_struSampleCaliCfg, sizeof(m_struSampleCaliCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_CONTROL_BV_SAMPLE_CALIB Chan[%d]", m_lChannel);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_CONTROL_BV_SAMPLE_CALIB Chan[%d]", m_lChannel); 
		return ;
    }
}

void CDlgVcaBVCalibrate::OnBtnBeginCalib() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
// 	if (ENUM_BV_CALIBRATION_SAMPLE != m_iCaliType)
// 	{
// 		g_StringLanType(szLan, "错误的标定类型!", "Error Calibration Type");
//         AfxMessageBox(szLan);
// 		return;
// 	}

	memset(&m_struSampleCaliCfg, 0, sizeof(m_struSampleCaliCfg));
	m_struSampleCaliCfg.dwSize = sizeof(m_struSampleCaliCfg);
	m_struSampleCaliCfg.dwChannel = m_lChannel;
	m_struSampleCaliCfg.byCommand = ENUM_BV_SAMPLE_CALIB_BEGIN;
	m_struSampleCaliCfg.uCalibParam.struCalibBegin.dwCameraHeight = m_dwSampleCameraHeight;
	m_struSampleCaliCfg.uCalibParam.struCalibBegin.dwHumanHeight = m_dwSampleHumanHeight;
	SetSampleCailbCfg();
}

void CDlgVcaBVCalibrate::OnBtnSetCalib() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
// 	if (ENUM_BV_CALIBRATION_SAMPLE != m_iCaliType)
// 	{
// 		g_StringLanType(szLan, "错误的标定类型!", "Error Calibration Type");
//         AfxMessageBox(szLan);
// 		return;
// 	}
	memset(&m_struSampleCaliCfg, 0, sizeof(m_struSampleCaliCfg));
	m_struSampleCaliCfg.dwSize = sizeof(m_struSampleCaliCfg);
	m_struSampleCaliCfg.dwChannel = m_lChannel;
	m_struSampleCaliCfg.byCommand = ENUM_BV_SAMPLE_CALIB_SETTING;
	m_struSampleCaliCfg.uCalibParam.struCalibSet.struCalibPoint.byCalibPtID = m_comCailbID.GetCurSel()+1;
	memcpy(&m_struSampleCaliCfg.uCalibParam.struCalibSet.struCalibPoint.struPoint, &m_struPoint, sizeof(m_struPoint));
	SetSampleCailbCfg();
}

void CDlgVcaBVCalibrate::OnBtnEndCalib() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
// 	if (ENUM_BV_CALIBRATION_SAMPLE != m_iCaliType)
// 	{
// 		g_StringLanType(szLan, "错误的标定类型!", "Error Calibration Type");
//         AfxMessageBox(szLan);
// 		return;
// 	}

	memset(&m_struSampleCaliCfg, 0, sizeof(m_struSampleCaliCfg));
	m_struSampleCaliCfg.dwSize = sizeof(m_struSampleCaliCfg);
	m_struSampleCaliCfg.dwChannel = m_lChannel;
	m_struSampleCaliCfg.byCommand = ENUM_BV_SAMPLE_CALIB_END;
	SetSampleCailbCfg();
}

void CDlgVcaBVCalibrate::OnBtnGetCalib() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
// 	if (ENUM_BV_CALIBRATION_SAMPLE != m_iCaliType)
// 	{
// 		g_StringLanType(szLan, "错误的标定类型!", "Error Calibration Type");
//         AfxMessageBox(szLan);
// 		return;
// 	}
	
	DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID,  NET_DVR_GET_BV_SAMPLE_CALIB_CFG, m_lChannel, &m_struGetSampleCaliCfg, sizeof(m_struGetSampleCaliCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_BV_SAMPLE_CALIB_CFG Chan[%d]", m_lChannel);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_BV_SAMPLE_CALIB_CFG Chan[%d]", m_lChannel); 
		return ;
    }

	m_dwCameraHeightSample = m_struGetSampleCaliCfg.dwCameraHeight;
	m_fPitchAngleSample = m_struGetSampleCaliCfg.fPitchAngle;
	m_fInclineAngleSample = m_struGetSampleCaliCfg.fInclineAngle;
	m_comCailbIDSample.SetCurSel(0);
	m_iID = m_struGetSampleCaliCfg.struCalibPoint[0].byCalibPtID;
	m_fX = m_struGetSampleCaliCfg.struCalibPoint[0].struPoint.fX;
	m_fY = m_struGetSampleCaliCfg.struCalibPoint[0].struPoint.fY;
	UpdateData(FALSE);
}

void CDlgVcaBVCalibrate::OnSelchangeComboCailbIdSample() 
{
	// TODO: Add your control notification handler code here
	int i = m_comCailbIDSample.GetCurSel();
	m_iID = m_struGetSampleCaliCfg.struCalibPoint[i].byCalibPtID;
	m_fX = m_struGetSampleCaliCfg.struCalibPoint[i].struPoint.fX;
	m_fY = m_struGetSampleCaliCfg.struCalibPoint[i].struPoint.fY;

	UpdateData(FALSE);
}

void CDlgVcaBVCalibrate::OnBtnVerifyBvCalibration() 
{
	// TODO: Add your control notification handler code here
	float fHeight = 0;
	if (NET_DVR_VerifyCalibration(m_lServerID, NET_DVR_VERIFY_BV_CALIBRATION, m_lChannel, &m_struPoint, sizeof(m_struPoint), &fHeight, sizeof(fHeight)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_VERIFY_BV_CALIBRATION Chan[%d]", m_lChannel);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_VERIFY_BV_CALIBRATION Chan[%d]", m_lChannel);
	}

	m_fBvCalibration = fHeight;
	UpdateData(FALSE);
	//DrawVerifyCalibration();
}

void CDlgVcaBVCalibrate::OnBtnGetOutputVideoType() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_OUTPUT_VIDEO_TYPE struVideoType = {0};

	DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID,  NET_DVR_GET_OUTPUT_VIDEO_TYPE, m_lChannel, &struVideoType, sizeof(struVideoType), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_OUTPUT_VIDEO_TYPE Chan[%d]", m_lChannel);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_OUTPUT_VIDEO_TYPE Chan[%d]", m_lChannel); 
		return ;
    }

	m_comVideoType.SetCurSel(struVideoType.byType - 1);
}

void CDlgVcaBVCalibrate::OnBtnSetOutputVideoType() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_OUTPUT_VIDEO_TYPE struVideoType = {0};
	struVideoType.dwSize = sizeof(struVideoType);
	struVideoType.byType = m_comVideoType.GetCurSel() + 1;
   if (NET_DVR_SetDVRConfig(m_lServerID,  NET_DVR_SET_OUTPUT_VIDEO_TYPE, m_lChannel, &struVideoType, sizeof(struVideoType)))
   {
	   g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_OUTPUT_VIDEO_TYPE Chan[%d]", m_lChannel);
   }
   else
   {
	   g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_OUTPUT_VIDEO_TYPE Chan[%d]", m_lChannel); 
	   return ;
   }
}

void CDlgVcaBVCalibrate::OnBtnGetCalibType() 
{
	// TODO: Add your control notification handler code here
	
	DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_BV_CALIB_TYPE, m_lChannel, &m_iCaliType, sizeof(m_iCaliType), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_BV_CALIB_TYPE Chan[%d]", m_lChannel);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_BV_CALIB_TYPE Chan[%d]", m_lChannel); 
		return ;
    }

	m_comGetCalibType.SetCurSel(m_iCaliType);
}

void CDlgVcaBVCalibrate::OnSelchangeComboCalibType() 
{
	// TODO: Add your control notification handler code here
	int i = m_comCalibType.GetCurSel();

	if (ENUM_BV_CALIBRATION_DIRECT == i)
	{
// 		GetDlgItem(IDC_STATIC_DIRECT_CALIB)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_STATIC_SAMPLE_CALIB)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_CHECK_ENABLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_CAMEAR_HEIGHT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PITCH_ANGLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PITCH_ANGLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PITCH_ANGLE2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_INCLINE_ANGLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_INCLINE_ANGLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_INCLINE_ANGLE2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_SET_DIRECT_CALI)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_GET_DIRECT_CALI)->ShowWindow(SW_SHOW);

		
		GetDlgItem(IDC_STATIC_BEGIN_CALIB)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SAMPLE_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_SAMPLE_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SAMPLE_CAMEAR_HEIGHT2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SAMPLE_HUMAN_HEIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_SAMPLE_HUMAN_HEIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SAMPLE_HUMAN_HEIGHT2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_BEGIN_CALIB)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_SET_CALIB)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAILB_ID)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_CAILB_ID)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_SET_CALIB)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_END_CALIB)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_GET_CALIB)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_CAMEAR_HEIGHT_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT_SAMPLE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PITCH_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PITCH_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PITCH_ANGLE_SAMPLE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_INCLINE_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_INCLINE_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_INCLINE_ANGLE_SAMPLE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAILB_ID_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_CAILB_ID_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_POINT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_POINT_X)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POINT_X)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_POINT_Y)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POINT_Y)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_GET_CALIB)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_VERIFY_BV_CALIBRATION)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAILB_NOTE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_BV_CALIBRATION)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_BV_CALIBRATION)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_ID)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_ID)->ShowWindow(SW_HIDE);
	} 
	else if(ENUM_BV_CALIBRATION_SAMPLE == i)
	{
// 		GetDlgItem(IDC_STATIC_DIRECT_CALIB)->ShowWindow(SW_SHOW);
// 		GetDlgItem(IDC_STATIC_SAMPLE_CALIB)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CHECK_ENABLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PITCH_ANGLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PITCH_ANGLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PITCH_ANGLE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_INCLINE_ANGLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_INCLINE_ANGLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_INCLINE_ANGLE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_SET_DIRECT_CALI)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_GET_DIRECT_CALI)->ShowWindow(SW_HIDE);


		GetDlgItem(IDC_STATIC_BEGIN_CALIB)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_SAMPLE_CAMEAR_HEIGHT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_SAMPLE_CAMEAR_HEIGHT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_SAMPLE_CAMEAR_HEIGHT2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_SAMPLE_HUMAN_HEIGHT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_SAMPLE_HUMAN_HEIGHT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_SAMPLE_HUMAN_HEIGHT2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_BEGIN_CALIB)->ShowWindow(SW_SHOW);
		
		GetDlgItem(IDC_STATIC_SET_CALIB)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CAILB_ID)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_CAILB_ID)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_SET_CALIB)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_END_CALIB)->ShowWindow(SW_SHOW);
		
		GetDlgItem(IDC_STATIC_GET_CALIB)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT_SAMPLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_CAMEAR_HEIGHT_SAMPLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT_SAMPLE2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PITCH_ANGLE_SAMPLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PITCH_ANGLE_SAMPLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PITCH_ANGLE_SAMPLE2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_INCLINE_ANGLE_SAMPLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_INCLINE_ANGLE_SAMPLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_INCLINE_ANGLE_SAMPLE2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CAILB_ID_SAMPLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_CAILB_ID_SAMPLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_POINT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_POINT_X)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POINT_X)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_POINT_Y)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POINT_Y)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_GET_CALIB)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_VERIFY_BV_CALIBRATION)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CAILB_NOTE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_BV_CALIBRATION)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_BV_CALIBRATION)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_ID)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_ID)->ShowWindow(SW_SHOW);
	}
	else if (ENUM_BV_CALIBRATION_NONE == i)
	{
// 		GetDlgItem(IDC_STATIC_DIRECT_CALIB)->ShowWindow(SW_SHOW);
// 		GetDlgItem(IDC_STATIC_SAMPLE_CALIB)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC_BEGIN_CALIB)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SAMPLE_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_SAMPLE_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SAMPLE_CAMEAR_HEIGHT2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SAMPLE_HUMAN_HEIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_SAMPLE_HUMAN_HEIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SAMPLE_HUMAN_HEIGHT2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_BEGIN_CALIB)->ShowWindow(SW_HIDE);
		
		GetDlgItem(IDC_STATIC_SET_CALIB)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAILB_ID)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_CAILB_ID)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_SET_CALIB)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_END_CALIB)->ShowWindow(SW_HIDE);
		
		GetDlgItem(IDC_STATIC_GET_CALIB)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_CAMEAR_HEIGHT_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT_SAMPLE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PITCH_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PITCH_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PITCH_ANGLE_SAMPLE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_INCLINE_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_INCLINE_ANGLE_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_INCLINE_ANGLE_SAMPLE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAILB_ID_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_CAILB_ID_SAMPLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_POINT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_POINT_X)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POINT_X)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_POINT_Y)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POINT_Y)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_GET_CALIB)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CHECK_ENABLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAMEAR_HEIGHT2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PITCH_ANGLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PITCH_ANGLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PITCH_ANGLE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_INCLINE_ANGLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_INCLINE_ANGLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_INCLINE_ANGLE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_SET_DIRECT_CALI)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_GET_DIRECT_CALI)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_VERIFY_BV_CALIBRATION)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CAILB_NOTE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_BV_CALIBRATION)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_BV_CALIBRATION)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_ID)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_ID)->ShowWindow(SW_HIDE);
	}
}
