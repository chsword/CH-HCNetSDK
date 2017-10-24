// DlgVcaDevAbility.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaDevAbility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaDevAbility dialog

CDlgVcaDevAbility::CDlgVcaDevAbility(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaDevAbility::IDD, pParent)
    , m_iEdcationStudentNum(0)
    , m_iHumanNum(0)
    , m_iRoadDetection(0)
{
	//{{AFX_DATA_INIT(CDlgVcaDevAbility)
	m_iAtmChanNum      = 0;
	m_iVcaChanNum      = 0;
	m_iITSChanNum      = 0;
	m_iBBaseChanNum    = 0;
	m_iBFullChanNum    = 0;
	m_iBAdvanceChanNum = 0;
	m_iPlateChanNum    = 0;
	m_iBPrisonChanNum  = 0;
	m_iTPSChanNum      = 0;
	m_iTFSChanNum      = 0;
	m_bChkSupportChanEx = FALSE;
	m_iPDCChanNum = 0;
	m_iBPPerimeterChanNum = 0;
	m_iFRecogChanNum = 0;
	m_iFRetrievalChanNum = 0;
	m_iFSnapChanNum = 0;
	m_iFSnapBFullChanNum = 0;
	m_iFSnapRecogChanNum = 0;
	m_bChkSupportIntelliTrack = FALSE;
	m_iHeatMapChanNum = 0;
	m_iSmartFaceDetectionChanNum = 0;
	m_iSmartHeatMapChanNum = 0;
	m_iSmartRoadDetectionChanNum = 0;
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    memset(&m_struVcaDevAbility, 0, sizeof(m_struVcaDevAbility));

}


void CDlgVcaDevAbility::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgVcaDevAbility)
    DDX_Text(pDX, IDC_EDIT_ATM_CHAN_NUM, m_iAtmChanNum);
    DDX_Text(pDX, IDC_EDIT_VCA_CHAN_NUM, m_iVcaChanNum);
    DDX_Text(pDX, IDC_EDIT_ITS_CHAN_NUM, m_iITSChanNum);
    DDX_Text(pDX, IDC_EDIT_BBASE_CHAN_NUM, m_iBBaseChanNum);
    DDX_Text(pDX, IDC_EDIT_BFULL_CHAN_NUM, m_iBFullChanNum);
    DDX_Text(pDX, IDC_EDIT_BADVANCE_CHAN_NUM, m_iBAdvanceChanNum);
    DDX_Text(pDX, IDC_EDIT_PLATE_CHAN_NUM, m_iPlateChanNum);
    DDX_Text(pDX, IDC_EDIT_BPRISON_CHAN_NUM, m_iBPrisonChanNum);
    DDX_Text(pDX, IDC_EDIT_TPS_CHAN_NUM, m_iTPSChanNum);
    DDX_Text(pDX, IDC_EDIT_TFS_CHAN_NUM, m_iTFSChanNum);
    DDX_Check(pDX, IDC_CHK_SUPPORT_CHAN_EX, m_bChkSupportChanEx);
    DDX_Text(pDX, IDC_EDIT_PDC_CHAN_NUM, m_iPDCChanNum);
    DDX_Text(pDX, IDC_EDIT_BPPERIMETER_CHAN_NUM, m_iBPPerimeterChanNum);
    DDX_Text(pDX, IDC_EDIT_FRECOG_CHAN_NUM, m_iFRecogChanNum);
    DDX_Text(pDX, IDC_EDIT_FRETRIEVAL_CHAN_NUM, m_iFRetrievalChanNum);
    DDX_Text(pDX, IDC_EDIT_FSNAP_CHAN_NUM, m_iFSnapChanNum);
    DDX_Text(pDX, IDC_EDIT_FSNAPBFULL_CHAN_NUM, m_iFSnapBFullChanNum);
    DDX_Text(pDX, IDC_EDIT_FSNAPRECOG_CHAN_NUM, m_iFSnapRecogChanNum);
    DDX_Check(pDX, IDC_CHK_SUPPORT_INTELLITRACK, m_bChkSupportIntelliTrack);
    DDX_Text(pDX, IDC_EDIT_HEATMAP_CHAN_NUM, m_iHeatMapChanNum);
    DDX_Text(pDX, IDC_EDIT_SMART_FACE_DETECTION_CHAN_NUM, m_iSmartFaceDetectionChanNum);
    DDX_Text(pDX, IDC_EDIT_SMART_HEATMAP_CHAN_NUM, m_iSmartHeatMapChanNum);
    DDX_Text(pDX, IDC_EDIT_SMART_ROAD_DETECTION_CHAN_NUM, m_iSmartRoadDetectionChanNum);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_EDUCATION_STUDENT_NUM, m_iEdcationStudentNum);
    DDX_Text(pDX, IDC_EDIT_HUMAN_NUM, m_iHumanNum);
    DDX_Text(pDX, IDC_EDIT_ROADDETECTION_CHAN_NUM, m_iRoadDetection);
}


BEGIN_MESSAGE_MAP(CDlgVcaDevAbility, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaDevAbility)
	ON_BN_CLICKED(IDC_BTN_REFRESH, OnBtnRefresh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgVcaDevAbility::GetVcaDevAbility()
{
    BOOL bRet = FALSE;
    if (!NET_DVR_GetDeviceAbility(m_lServerID,  VCA_DEV_ABILITY, NULL, 0, (char*)&m_struVcaDevAbility, sizeof(m_struVcaDevAbility)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "VCA_DEV_ABILITY");
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "VCA_DEV_ABILITY");
        bRet = TRUE;
    }
    return bRet;
}


/////////////////////////////////////////////////////////////////////////////
// CDlgVcaDevAbility message handlers


BOOL CDlgVcaDevAbility::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    GetVcaDevAbility();
	
    ShowAbility();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVcaDevAbility::UpdateWindowParam(LONG lDevIndex)
{   
	if (lDevIndex < 0)
	{
		return;
	}
	m_iDevIndex = lDevIndex;
	m_lServerID = g_struDeviceInfo[m_iDevIndex].lLoginID;

	GetVcaDevAbility();
	ShowAbility();
}

void CDlgVcaDevAbility::ShowAbility()
{
	m_iVcaChanNum         = m_struVcaDevAbility.byVCAChanNum;
    m_iPlateChanNum       = m_struVcaDevAbility.byPlateChanNum;
    m_iAtmChanNum         = m_struVcaDevAbility.byATMChanNum;
    m_iBBaseChanNum       = m_struVcaDevAbility.byBBaseChanNum;
    m_iBAdvanceChanNum    = m_struVcaDevAbility.byBAdvanceChanNum;
    m_iBFullChanNum       = m_struVcaDevAbility.byBFullChanNum;
    m_iITSChanNum         = m_struVcaDevAbility.byITSChanNum;
    m_iBPrisonChanNum     = m_struVcaDevAbility.byBPrisonChanNum;
	m_iTPSChanNum         = m_struVcaDevAbility.byTPSChanNum;
	m_iTFSChanNum         = m_struVcaDevAbility.byTFSChanNum;
	m_iPDCChanNum         = m_struVcaDevAbility.byPDCChanNum;
	m_iBPPerimeterChanNum = m_struVcaDevAbility.byBPPerimeterChanNum;
	m_iFRecogChanNum      = m_struVcaDevAbility.byFRecogChanNum;
	m_iFRetrievalChanNum  = m_struVcaDevAbility.byFRetrievalChanNum;
	m_iFSnapChanNum       = m_struVcaDevAbility.byFSnapChanNum;
	m_iFSnapBFullChanNum  = m_struVcaDevAbility.byFSnapBFullChanNum;
	m_iFSnapRecogChanNum  = m_struVcaDevAbility.byFSnapRecogChanNum;
	m_iHeatMapChanNum     = m_struVcaDevAbility.byHeatMapChanNum;
    m_iSmartRoadDetectionChanNum = m_struVcaDevAbility.bySmartRoadDetectionNum;
    m_iSmartFaceDetectionChanNum = m_struVcaDevAbility.bySmartFaceDetectionNum;
    m_iSmartHeatMapChanNum = m_struVcaDevAbility.bySmartHeatMapNum;
    m_iHumanNum = m_struVcaDevAbility.byHumanRecognitionNum;
    m_iEdcationStudentNum = m_struVcaDevAbility.byEdcationStudentNum;
    m_iRoadDetection = m_struVcaDevAbility.byRoadDetectionNum;
	m_bChkSupportIntelliTrack = (m_struVcaDevAbility.bySupport & 0x01) ? TRUE : FALSE;
	m_bChkSupportChanEx   = (m_struVcaDevAbility.bySupport & 0x02) ? TRUE : FALSE;
	
    UpdateData(FALSE);
}

void CDlgVcaDevAbility::OnBtnRefresh() 
{
	GetVcaDevAbility();
	ShowAbility();
}
