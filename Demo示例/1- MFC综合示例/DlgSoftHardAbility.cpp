// DlgSoftHardAbility.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgSoftHardAbility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSoftHardAbility dialog


CDlgSoftHardAbility::CDlgSoftHardAbility(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSoftHardAbility::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSoftHardAbility)
	m_bDDNS = FALSE;
	m_bEptz = FALSE;
	m_bIpv6 = FALSE;
	m_bNas = FALSE;
	m_bNtp = FALSE;
	m_bRtsp = FALSE;
	m_bUpnp = FALSE;
	m_bVca = FALSE;
	m_bSupportIRS = FALSE;
	m_bSupportPOE = FALSE;
	m_bSupportReset = FALSE;
	m_bSuportSD = FALSE;
	m_bSupportVideo = FALSE;
	m_bSupportWifi = FALSE;
	m_iAlarmOutNum = 0;
	m_iAlarmInNum = 0;
	m_iAudioInNum = 0;
	m_iAudioOutNum = 0;
	m_dwFlashSize = 0;
	m_iNetworkPortNum = 0;
	m_dwRamSize = 0;
	m_iRs232Num = 0;
	m_iRs485Num = 0;
	m_iSDNum = 0;
	m_iUsbNum = 0;
	m_csUsbVersion = _T("");
	m_iVideoInNum = 0;
	m_iVideoOutNum = 0;
	m_byNasNum = 0;
	m_byShowStringNum = 0;
	m_bATM = FALSE;
	m_bAudioEncodeTypeReboot = FALSE;
	m_bBackup = FALSE;
	m_bBitrateLimit = FALSE;
	m_bDHCPReboot = FALSE;
	m_bEmailSPT = FALSE;
	m_bFileLockSPT = FALSE;
	m_bHDParamReboot = FALSE;
	m_bHideAlarmSPT = FALSE;
	m_bHttpOverRtspSPT = FALSE;
	m_bHttpPortReboot = FALSE;
	m_bImportCFGFileReboot = FALSE;
	m_bISCSISpt = FALSE;
	m_bMotionDetectAlarmSPT = FALSE;
	m_bMulStreamSPT = FALSE;
	m_bNetPortReboot = FALSE;
	m_bPtzSPT = FALSE;
	m_bRecordTimeReboot = FALSE;
	m_bRS232Reboot = FALSE;
	m_bRtpoverRtsp = FALSE;
	m_bShutDown = FALSE;
	m_bSmartSearch = FALSE;
	m_bSNMP = FALSE;
	m_bStandardTypeReboot = FALSE;
	m_bSubStreamSPT = FALSE;
	m_bVideoEncodeTypeReboot = FALSE;
	m_bVILostAlarmSPT = FALSE;
	m_csDDNSType = _T("");
	m_iMaxChanLinkNum = 0;
	m_iMaxLoginNum = 0;
	m_iMaxPlayBackNum = 0;
	m_iMaxPreviewNum = 0;
	m_csSadpVersion = _T("");
	m_csSNMPVersion = _T("");
	m_byZeroChanNum = 0;
	m_bPPPoeReboot = FALSE;
	m_bMulNetworkCard = FALSE;
	m_bSupportRaid = FALSE;
	m_byAnalogChanNum = 0;
	m_byAudioTalkNum = 0;
	m_byAuxoutNum = 0;
	m_byHardDiskNum = 0;
	m_dwHardwareVersion = 0;
	m_byIPChanNum = 0;
	m_byNetworkCardNum = 0;
	m_byVGANum = 0;
	m_bShelterSPT = FALSE;
	m_iRaidType = 0;
	m_byHDMINum = 0;
	m_byCVBSNum = 0;
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    m_pRecvBuf = NULL;
    m_pSendBuf = NULL;
}



void CDlgSoftHardAbility::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSoftHardAbility)
	DDX_Control(pDX, IDC_LIST_SNMPVERSION, m_lstSnmpVersion);
	DDX_Control(pDX, IDC_LIST_SADPVERSION, m_lstSadpVersion);
	DDX_Control(pDX, IDC_LIST_DDNSTYPE, m_lstDdnsType);
	DDX_Check(pDX, IDC_CHK_DDNS, m_bDDNS);
	DDX_Check(pDX, IDC_CHK_EPTZ, m_bEptz);
	DDX_Check(pDX, IDC_CHK_IPV6, m_bIpv6);
	DDX_Check(pDX, IDC_CHK_NAS, m_bNas);
	DDX_Check(pDX, IDC_CHK_NTP, m_bNtp);
	DDX_Check(pDX, IDC_CHK_RTSP, m_bRtsp);
	DDX_Check(pDX, IDC_CHK_UPNP, m_bUpnp);
	DDX_Check(pDX, IDC_CHK_VCA, m_bVca);
	DDX_Check(pDX, IDC_CHK_SUPPORT_IRS, m_bSupportIRS);
	DDX_Check(pDX, IDC_CHK_SUPPORT_POE, m_bSupportPOE);
	DDX_Check(pDX, IDC_CHK_SUPPORT_RESET, m_bSupportReset);
	DDX_Check(pDX, IDC_CHK_SUPPORT_SD, m_bSuportSD);
	DDX_Check(pDX, IDC_CHK_SUPPORT_VIDEO, m_bSupportVideo);
	DDX_Check(pDX, IDC_CHK_SUPPORT_WIFI, m_bSupportWifi);
	DDX_Text(pDX, IDC_EDIT_ALARAMOUT_NUM, m_iAlarmOutNum);
	DDX_Text(pDX, IDC_EDIT_ALARMIN_NUM, m_iAlarmInNum);
	DDX_Text(pDX, IDC_EDIT_AUDIOIN_NUM, m_iAudioInNum);
	DDX_Text(pDX, IDC_EDIT_AUDIOOUT_NUM, m_iAudioOutNum);
	DDX_Text(pDX, IDC_EDIT_FLASH_SIZE, m_dwFlashSize);
	DDX_Text(pDX, IDC_EDIT_NETWORK_PORT_NUM, m_iNetworkPortNum);
	DDX_Text(pDX, IDC_EDIT_RAM_SIZE, m_dwRamSize);
	DDX_Text(pDX, IDC_EDIT_RS232_NUM, m_iRs232Num);
	DDX_Text(pDX, IDC_EDIT_RS485_NUM, m_iRs485Num);
	DDX_Text(pDX, IDC_EDIT_SD_NUM, m_iSDNum);
	DDX_Text(pDX, IDC_EDIT_USB_NUM, m_iUsbNum);
	DDX_Text(pDX, IDC_EDIT_USB_VERSION, m_csUsbVersion);
	DDX_Text(pDX, IDC_EDIT_VIDEOIN_NUM, m_iVideoInNum);
	DDX_Text(pDX, IDC_EDIT_VIDEOOUT_NUM, m_iVideoOutNum);
	DDX_Text(pDX, IDC_EDIT_NAS_NUM, m_byNasNum);
	DDX_Text(pDX, IDC_EDIT_SHOWSTRING_NUM, m_byShowStringNum);
	DDX_Check(pDX, IDC_CHK_ATMSPT, m_bATM);
	DDX_Check(pDX, IDC_CHK_AUDIOENCODETYPEREBOOT, m_bAudioEncodeTypeReboot);
	DDX_Check(pDX, IDC_CHK_BACKUPSPT, m_bBackup);
	DDX_Check(pDX, IDC_CHK_BITRATELIMITSPT, m_bBitrateLimit);
	DDX_Check(pDX, IDC_CHK_DHCPENABLEREBOOT, m_bDHCPReboot);
	DDX_Check(pDX, IDC_CHK_EMAILSPT, m_bEmailSPT);
	DDX_Check(pDX, IDC_CHK_FILELOCKSPT, m_bFileLockSPT);
	DDX_Check(pDX, IDC_CHK_HDPARAMREBOOT, m_bHDParamReboot);
	DDX_Check(pDX, IDC_CHK_HIDEALARMSPT, m_bHideAlarmSPT);
	DDX_Check(pDX, IDC_CHK_HTTPOVERRTSP, m_bHttpOverRtspSPT);
	DDX_Check(pDX, IDC_CHK_HTTPPORTREBOOT, m_bHttpPortReboot);
	DDX_Check(pDX, IDC_CHK_IMPORTCFGFILEREBOOT, m_bImportCFGFileReboot);
	DDX_Check(pDX, IDC_CHK_ISCSI, m_bISCSISpt);
	DDX_Check(pDX, IDC_CHK_MOTIONDETECTALARMSPT, m_bMotionDetectAlarmSPT);
	DDX_Check(pDX, IDC_CHK_MULSTREAMSPT, m_bMulStreamSPT);
	DDX_Check(pDX, IDC_CHK_NETPORTREBOOT, m_bNetPortReboot);
	DDX_Check(pDX, IDC_CHK_PTZSPT, m_bPtzSPT);
	DDX_Check(pDX, IDC_CHK_RECORDTIMEREBOOT, m_bRecordTimeReboot);
	DDX_Check(pDX, IDC_CHK_RS232WORKMODEREBOOT, m_bRS232Reboot);
	DDX_Check(pDX, IDC_CHK_RTPOVERRTSP, m_bRtpoverRtsp);
	DDX_Check(pDX, IDC_CHK_SHUTDOWNSPT, m_bShutDown);
	DDX_Check(pDX, IDC_CHK_SMARTSEARCHSPT, m_bSmartSearch);
	DDX_Check(pDX, IDC_CHK_SNMP, m_bSNMP);
	DDX_Check(pDX, IDC_CHK_STANDARDTYPEREBOOT, m_bStandardTypeReboot);
	DDX_Check(pDX, IDC_CHK_SUBSTREAMSPT, m_bSubStreamSPT);
	DDX_Check(pDX, IDC_CHK_VIDEOENCODETYPEREBOOT, m_bVideoEncodeTypeReboot);
	DDX_Check(pDX, IDC_CHK_VILOSTALARMSPT, m_bVILostAlarmSPT);
	DDX_Text(pDX, IDC_EDIT_MAXCHANLINKNUM, m_iMaxChanLinkNum);
	DDX_Text(pDX, IDC_EDIT_MAXLOGINNUM, m_iMaxLoginNum);
	DDX_Text(pDX, IDC_EDIT_MAXPLAYBACKNUM, m_iMaxPlayBackNum);
	DDX_Text(pDX, IDC_EDIT_MAXPREVIEWNUM, m_iMaxPreviewNum);
	DDX_Text(pDX, IDC_EDIT_ZEROCHANNUM, m_byZeroChanNum);
	DDX_Check(pDX, IDC_CHK_PPPOEREBOOT, m_bPPPoeReboot);
	DDX_Check(pDX, IDC_CHK_MULNETWORKCARDSPT, m_bMulNetworkCard);
	DDX_Text(pDX, IDC_EDIT_ANALOGCHAN_NUM, m_byAnalogChanNum);
	DDX_Text(pDX, IDC_EDIT_AUDIOTALK_NUM, m_byAudioTalkNum);
	DDX_Text(pDX, IDC_EDIT_AUXOUT_NUM, m_byAuxoutNum);
	DDX_Text(pDX, IDC_EDIT_HARDDISK_NUM, m_byHardDiskNum);
	DDX_Text(pDX, IDC_EDIT_HARDWAREVERSION, m_dwHardwareVersion);
	DDX_Text(pDX, IDC_EDIT_IPCHAN_NUM, m_byIPChanNum);
	DDX_Text(pDX, IDC_EDIT_NETWORKCARD_NUM, m_byNetworkCardNum);
	DDX_Text(pDX, IDC_EDIT_VGA_NUM, m_byVGANum);
	DDX_Check(pDX, IDC_CHK_SHELTERSPT, m_bShelterSPT);
	DDX_Text(pDX, IDC_EDIT_RAIDTYPE, m_iRaidType);
	DDX_Text(pDX, IDC_EDIT_HDMINUM, m_byHDMINum);
	DDX_Text(pDX, IDC_EDIT_CVBSNUM, m_byCVBSNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSoftHardAbility, CDialog)
	//{{AFX_MSG_MAP(CDlgSoftHardAbility)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSoftHardAbility message handlers

void CDlgSoftHardAbility::PostNcDestroy() 
{

    if (m_pRecvBuf != NULL)
    {
        delete []m_pRecvBuf;
        m_pRecvBuf = NULL;
    }	

	CDialog::PostNcDestroy();
}

BOOL CDlgSoftHardAbility::OnInitDialog() 
{
	CDialog::OnInitDialog();
	if (m_pRecvBuf == NULL)
	{
        m_pRecvBuf = new char[XML_BUF];
	}

    GetSoftHardAbility();
    ParseSoftHardAbilityXml(m_pRecvBuf, strlen(m_pRecvBuf));
	
    SetSoftHardAbilityToWnd(m_struAbilityParam);
    UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CDlgSoftHardAbility::GetSoftHardAbility()
{
    memset(m_pRecvBuf, 0, XML_BUF);
    if (!NET_DVR_GetDeviceAbility(m_lServerID, DEVICE_SOFTHARDWARE_ABILITY, NULL, 0, m_pRecvBuf, XML_BUF))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "DEVICE_SOFTHARDWARE_ABILITY");
        return FALSE;
    }
    else 
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "DEVICE_SOFTHARDWARE_ABILITY");
        return TRUE;
    }
}


BOOL CDlgSoftHardAbility::ParseSoftHardAbilityXml(char *pBuf, DWORD dwBufSize)
{
    // todo!!!  做个写文件操作
    WirteBufToFile(pBuf, dwBufSize);
    CString strData("");

    CMarkup	XmlMaker;

    if (!XmlMaker.SetDoc(pBuf))
    {
        AfxMessageBox("set doc fail");
    }

    if (XmlMaker.FindElem("BasicCapability"))
    {
        XmlMaker.IntoElem();
        if (XmlMaker.FindElem("HardwareCapability"))
        {
            XmlMaker.IntoElem();

            if (XmlMaker.FindElem("HardwareVersion"))
            {
				m_struAbilityParam.struHardAbilityParam.dwHardwareVersion = (DWORD)atoi(XmlMaker.GetData());
            }

            if (XmlMaker.FindElem("AlarmInPortNum"))
            {
                m_struAbilityParam.struHardAbilityParam.byAlarmInPortNum = (BYTE)atoi(XmlMaker.GetData());
            }

            if (XmlMaker.FindElem("AlarmOutPortNum"))
            {
                m_struAbilityParam.struHardAbilityParam.byAlarmOutPortNum = (BYTE)atoi(XmlMaker.GetData());
            }

            if (XmlMaker.FindElem("RS232Num"))
            {
                m_struAbilityParam.struHardAbilityParam.byRs232Num = (BYTE)atoi(XmlMaker.GetData());
                
            }

            if (XmlMaker.FindElem("RS485Num"))
            {
                m_struAbilityParam.struHardAbilityParam.byRs485Num = (BYTE)atoi(XmlMaker.GetData());
            }

            if (XmlMaker.FindElem("NetworkPortNum"))
            {
                m_struAbilityParam.struHardAbilityParam.byNetworkPortNum = (BYTE)atoi(XmlMaker.GetData());
            }

            if (XmlMaker.FindElem("USBNum"))
            {
                m_struAbilityParam.struHardAbilityParam.byUsbNum = (BYTE)atoi(XmlMaker.GetData());
            }

            if (XmlMaker.FindElem("FlashSize"))
            {
                m_struAbilityParam.struHardAbilityParam.dwFlashSize = atoi(XmlMaker.GetData());
            }

            if (XmlMaker.FindElem("RamSize"))
            {
                m_struAbilityParam.struHardAbilityParam.dwRamSize = atoi(XmlMaker.GetData());
            }

            if (XmlMaker.FindElem("USBVersion"))
            {
                strncpy(m_struAbilityParam.struHardAbilityParam.chUsbVersion, XmlMaker.GetData().GetBuffer(0), \
                    sizeof(m_struAbilityParam.struHardAbilityParam.chUsbVersion));
            }

            if (XmlMaker.FindElem("SDNum"))
            {
                m_struAbilityParam.struHardAbilityParam.bySDNum = (BYTE)atoi(XmlMaker.GetData());
            }            

			if (XmlMaker.FindElem("HardDiskNum"))
			{
				m_struAbilityParam.struHardAbilityParam.byHardDiskNum = (BYTE)atoi(XmlMaker.GetData());
			}
            
            if (XmlMaker.FindElem("VideoInNum"))
            {
                m_struAbilityParam.struHardAbilityParam.byVideoInNum = (BYTE)atoi(XmlMaker.GetData());
            }            
            
            if (XmlMaker.FindElem("VideoOutNum"))
            {
                m_struAbilityParam.struHardAbilityParam.byVideoOutNum = (BYTE)atoi(XmlMaker.GetData());
            }  

            if (XmlMaker.FindElem("AudioInNum"))
            {
                m_struAbilityParam.struHardAbilityParam.byAudioInNum = (BYTE)atoi(XmlMaker.GetData());
            }            
            
            if (XmlMaker.FindElem("AudioOutNum"))
            {
                m_struAbilityParam.struHardAbilityParam.byAudioOutNum = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("AudioTalkNum"))
			{
				m_struAbilityParam.struHardAbilityParam.byAudioTalkNum = (BYTE)atoi(XmlMaker.GetData());
			}

            if (XmlMaker.FindElem("SDSupport"))
            {
                m_struAbilityParam.struHardAbilityParam.bySDSupport = (BYTE)atoi(XmlMaker.GetData());
            }

            if (XmlMaker.FindElem("WiFiSupport"))
            {
                m_struAbilityParam.struHardAbilityParam.byWifiSupport = (BYTE)atoi(XmlMaker.GetData());
            }

            if (XmlMaker.FindElem("POESupport"))
            {
                m_struAbilityParam.struHardAbilityParam.byPOESupport = (BYTE)atoi(XmlMaker.GetData());
            }

            if (XmlMaker.FindElem("IRSupport"))
            {
                m_struAbilityParam.struHardAbilityParam.byIRSSupport = (BYTE)atoi(XmlMaker.GetData());
            }

            if (XmlMaker.FindElem("VideoOutSupport"))
            {
                m_struAbilityParam.struHardAbilityParam.byVideoOutNum = (BYTE)atoi(XmlMaker.GetData());
            }


            if (XmlMaker.FindElem("ResetSupport"))
            {
                m_struAbilityParam.struHardAbilityParam.byResetSupport = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("AnalogChannelNum"))
            {
                m_struAbilityParam.struHardAbilityParam.byAnalogChannelNum = (BYTE)atoi(XmlMaker.GetData());
            }
			
			if (XmlMaker.FindElem("IPChannelNum"))
            {
                m_struAbilityParam.struHardAbilityParam.byIPChannelNum = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("MultiNetworkCard"))
            {
                m_struAbilityParam.struHardAbilityParam.byMulNetworkCardSpt = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("NetworkCardNumber"))
            {
                m_struAbilityParam.struHardAbilityParam.byNetworkCardNum = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("VGANumber"))
            {
                m_struAbilityParam.struHardAbilityParam.byVGANum = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("HDMINumber"))
			{
				m_struAbilityParam.struHardAbilityParam.byHDMINum = (BYTE)atoi(XmlMaker.GetData());
			}

			if (XmlMaker.FindElem("CVBSNumber"))
			{
				m_struAbilityParam.struHardAbilityParam.byCVBSNum = (BYTE)atoi(XmlMaker.GetData());
			}

			if (XmlMaker.FindElem("AuxoutNum"))
            {
                m_struAbilityParam.struHardAbilityParam.byAuxoutNum = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("RAIDType"))
            {
                m_struAbilityParam.struHardAbilityParam.iRaidType = atoi(XmlMaker.GetData());
            }
            XmlMaker.OutOfElem();
        }
        else
        {
            AfxMessageBox("HardwareCapability Fail");
        }    
        
        if (XmlMaker.FindElem("SoftwareCapability"))
        {
            XmlMaker.IntoElem();
            if (XmlMaker.FindElem("NasSupport"))
            {
                m_struAbilityParam.struSoftAbilityParam.byNASSupport = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("NasNumber"))
            {
                m_struAbilityParam.struSoftAbilityParam.byNASNum = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("ShowStringNumber"))
            {
                m_struAbilityParam.struSoftAbilityParam.byShowStringNum = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("MotionDetectAlarmSupport"))
            {
                m_struAbilityParam.struSoftAbilityParam.byMotionAlarmSpt = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("VILostAlarmSupport"))
            {
                m_struAbilityParam.struSoftAbilityParam.byVILostAlarmSpt = (BYTE)atoi(XmlMaker.GetData());
            }
			
			if (XmlMaker.FindElem("HideAlarmSupport"))
            {
                m_struAbilityParam.struSoftAbilityParam.byHideAlarmSpt = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("ShelterSupport"))
            {
                m_struAbilityParam.struSoftAbilityParam.byShelterSpt = (BYTE)atoi(XmlMaker.GetData());
            }

            if (XmlMaker.FindElem("RtspSupport"))
            {
                m_struAbilityParam.struSoftAbilityParam.byRtspSupport = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("RtpoverRtspSupport"))
            {
                m_struAbilityParam.struSoftAbilityParam.byRtpOverRtspSpt = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("RtspoverHttpSupport"))
            {
                m_struAbilityParam.struSoftAbilityParam.byRtspOverHttpSpt = (BYTE)atoi(XmlMaker.GetData());
            }

            if (XmlMaker.FindElem("NtpSupport"))
            {
                m_struAbilityParam.struSoftAbilityParam.byNtpSupport = (BYTE)atoi(XmlMaker.GetData());
            }

            if (XmlMaker.FindElem("EptzSupport"))
            {
                m_struAbilityParam.struSoftAbilityParam.byEptzSupport = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("PtzSupport"))
            {
                m_struAbilityParam.struSoftAbilityParam.byPtzSpt = (BYTE)atoi(XmlMaker.GetData());
            }

            if (XmlMaker.FindElem("DDNSSupport"))
            {
                m_struAbilityParam.struSoftAbilityParam.byDDNSSupport = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("DDNSHostType"))
            {
				CString str;
				str = XmlMaker.GetData();
				ParseStrIndex(str, m_struAbilityParam.struSoftAbilityParam.byDDNSHostType, 
					sizeof(m_struAbilityParam.struSoftAbilityParam.byDDNSHostType));        
		//		strncpy(m_struAbilityParam.struSoftAbilityParam.chDDNSHostType,
		//			XmlMaker.GetData(),sizeof(m_struAbilityParam.struSoftAbilityParam.chDDNSHostType));
               // m_struAbilityParam.struSoftAbilityParam.byVILostAlarmSpt = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("SNMPSupport"))
            {
                m_struAbilityParam.struSoftAbilityParam.bySNMPSpt = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("SNMPVersion"))
            {
				CString str;
				str = XmlMaker.GetData();
				ParseStrIndex(str, m_struAbilityParam.struSoftAbilityParam.bySNMPVersion, 
					sizeof(m_struAbilityParam.struSoftAbilityParam.bySNMPVersion));
			//	strncpy(m_struAbilityParam.struSoftAbilityParam.chSNMPVersion,
			//		XmlMaker.GetData(),sizeof(m_struAbilityParam.struSoftAbilityParam.chSNMPVersion));
				// m_struAbilityParam.struSoftAbilityParam.byVILostAlarmSpt = (BYTE)atoi(XmlMaker.GetData());
            }

            if (XmlMaker.FindElem("UPNPSupport"))
            {
                m_struAbilityParam.struSoftAbilityParam.byUPNPSupport = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("iSCSISupport"))
            {
                m_struAbilityParam.struSoftAbilityParam.byiSCSISpt = (BYTE)atoi(XmlMaker.GetData());
            }

            if (XmlMaker.FindElem("Ipv6Support"))
            {
                m_struAbilityParam.struSoftAbilityParam.byIpv6Support = (BYTE)atoi(XmlMaker.GetData());
            }

            if (XmlMaker.FindElem("VCASupport"))
            {
                m_struAbilityParam.struSoftAbilityParam.byVcaSupport = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("MultipleStreamSupport"))
            {
                m_struAbilityParam.struSoftAbilityParam.byMulStreamSpt = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("SubStreamSupport"))
            {
                m_struAbilityParam.struSoftAbilityParam.bySubStreamSpt = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("EmailSupport"))
            {
                m_struAbilityParam.struSoftAbilityParam.byEmailSpt = (BYTE)atoi(XmlMaker.GetData());
            }

// 			if (XmlMaker.FindElem("SADPSupport"))
//             {
//                 m_struAbilityParam.struSoftAbilityParam.bySadpSpt = (BYTE)atoi(XmlMaker.GetData());
//             }

			if (XmlMaker.FindElem("SADPVersion"))
            {
				CString str;
				str = XmlMaker.GetData();
				ParseStrIndex(str, m_struAbilityParam.struSoftAbilityParam.bySadpVersion, 
					sizeof(m_struAbilityParam.struSoftAbilityParam.bySadpVersion));
//				strncpy(m_struAbilityParam.struSoftAbilityParam.chSadpVersion,XmlMaker.GetData(),
//					sizeof(m_struAbilityParam.struSoftAbilityParam.chSadpVersion));
                //m_struAbilityParam.struSoftAbilityParam.bySNMPSpt = (BYTE)atoi(XmlMaker.GetData());
            }

// 			if (XmlMaker.FindElem("ZeroChanSupport"))
//             {
//                 m_struAbilityParam.struSoftAbilityParam.byZeroChanSpt = (BYTE)atoi(XmlMaker.GetData());
//             }

			if (XmlMaker.FindElem("ZeroChanNumber"))
            {
                m_struAbilityParam.struSoftAbilityParam.byZeroChanNum = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("BackupSupport"))
            {
                m_struAbilityParam.struSoftAbilityParam.byBackupSpt = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("SmartSearchSupport"))
            {
                m_struAbilityParam.struSoftAbilityParam.bySmartSearchSpt = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("ATMSupport"))
            {
                m_struAbilityParam.struSoftAbilityParam.byATMSpt = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("FileLockSupport"))
            {
                m_struAbilityParam.struSoftAbilityParam.byFileLockSpt = (BYTE)atoi(XmlMaker.GetData());
            }

// 			if (XmlMaker.FindElem("VoiceTalkSupport"))
//             {
//                 m_struAbilityParam.struSoftAbilityParam.byVoiceTalkSpt = (BYTE)atoi(XmlMaker.GetData());
//             }

			if (XmlMaker.FindElem("BitrateLimitSupport"))
            {
                m_struAbilityParam.struSoftAbilityParam.byBitrateLimitSpt = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("MaxLoginNum"))
            {
                m_struAbilityParam.struSoftAbilityParam.iMaxLoginNum = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("MaxPreviewNum"))
            {
                m_struAbilityParam.struSoftAbilityParam.iMaxPreviewNum = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("MaxPlayBackNum"))
            {
                m_struAbilityParam.struSoftAbilityParam.iMaxPlayBackNum = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("MaxChanLinkNum"))
            {
                m_struAbilityParam.struSoftAbilityParam.iMaxChanLinkNum = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("ShutDownSupport"))
            {
                m_struAbilityParam.struSoftAbilityParam.byShutDownSpt = (BYTE)atoi(XmlMaker.GetData());
            }

			if (XmlMaker.FindElem("NeedReboot"))
			{
				XmlMaker.IntoElem();
				if (XmlMaker.FindElem("ImportConfigurationFileReboot"))
				{
					m_struAbilityParam.struNeedRebootParam.byImportCfgFileReboot = (BYTE)atoi(XmlMaker.GetData());
				}
				
				if (XmlMaker.FindElem("RS232workModeReboot"))
				{
					m_struAbilityParam.struNeedRebootParam.byRS232workModeReboot = (BYTE)atoi(XmlMaker.GetData());
				}
				
				if (XmlMaker.FindElem("NetPortReboot"))
				{
					m_struAbilityParam.struNeedRebootParam.byNetPortReboot = (BYTE)atoi(XmlMaker.GetData());
				}
				
				if (XmlMaker.FindElem("DhcpEnableReboot"))
				{
					m_struAbilityParam.struNeedRebootParam.byDhcpEnableReboot = (BYTE)atoi(XmlMaker.GetData());
				}
				
				if (XmlMaker.FindElem("HttpPortReboot"))
				{
					m_struAbilityParam.struNeedRebootParam.byHttpPortReboot = (BYTE)atoi(XmlMaker.GetData());
				}
				
				if (XmlMaker.FindElem("PPPoEReboot"))
				{
					m_struAbilityParam.struNeedRebootParam.byPPPoEReboot = (BYTE)atoi(XmlMaker.GetData());
				}
				
				if (XmlMaker.FindElem("HardDiskParamReboot"))
				{
					m_struAbilityParam.struNeedRebootParam.byHDParamReboot = (BYTE)atoi(XmlMaker.GetData());
				}
				
				if (XmlMaker.FindElem("RecordTimeReboot"))
				{
					m_struAbilityParam.struNeedRebootParam.byRecordTimeReboot = (BYTE)atoi(XmlMaker.GetData());
				}
				
				if (XmlMaker.FindElem("VideoEncodeTypeReboot"))
				{
					m_struAbilityParam.struNeedRebootParam.byVideoEncodeTypeReboot = (BYTE)atoi(XmlMaker.GetData());
				}
				
				if (XmlMaker.FindElem("AudioEncodeTypeReboot"))
				{
					m_struAbilityParam.struNeedRebootParam.byAudioEncodeTypeReboot = (BYTE)atoi(XmlMaker.GetData());
				}
				
				if (XmlMaker.FindElem("StandardTypeReboot"))
				{
					m_struAbilityParam.struNeedRebootParam.byStandardTypeReboot = (BYTE)atoi(XmlMaker.GetData());
				}
				XmlMaker.OutOfElem();
			}
			else
			{
				AfxMessageBox("Find NeedReboot fail");
			}
            XmlMaker.OutOfElem();
        }
        else
        {
            AfxMessageBox("SoftwareCapability fail");
        }
        XmlMaker.OutOfElem();
    }
    else
    {
        AfxMessageBox("Find BasicCapability fail");
    }
    
    return TRUE;
}

BOOL CDlgSoftHardAbility::WirteBufToFile(char *pBuf, DWORD dwBufSize)
{
    SYSTEMTIME t;
    GetLocalTime(&t);
    char chTime[128];
    char cFilename[256] = {0};
    sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
    
    sprintf(cFilename, "%s\\SOFT_HARD_%s.xml", g_struLocalParam.chPictureSavePath, chTime);
    
    
    HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        int nError = 0;
        nError = GetLastError();
        return FALSE;
    }
    DWORD dwReturn = 0;
    WriteFile(hFile, pBuf, dwBufSize, &dwReturn, NULL);
    CloseHandle(hFile);
    hFile = NULL;
    
    return TRUE;
}

BOOL CDlgSoftHardAbility::SetSoftHardAbilityToWnd(SOFTHARDWARE_ABILITY_PARAM struSoftHardAbility)
{
    SetSoftAbilityToWnd(struSoftHardAbility.struSoftAbilityParam);
    SetHardAbilityToWnd(struSoftHardAbility.struHardAbilityParam);
	SetNeedRebootToWnd(struSoftHardAbility.struNeedRebootParam);
    UpdateData(FALSE);
    return TRUE;
}

BOOL CDlgSoftHardAbility::SetSoftAbilityToWnd(SOFTWARE_ABILITY_PARAM struSoftwareAbility)
{
    m_bNas = struSoftwareAbility.byNASSupport;
	m_byNasNum = struSoftwareAbility.byNASNum;
	m_byShowStringNum = struSoftwareAbility.byShowStringNum;
	m_bMotionDetectAlarmSPT = struSoftwareAbility.byMotionAlarmSpt;
	m_bVILostAlarmSPT = struSoftwareAbility.byVILostAlarmSpt;
	m_bHideAlarmSPT = struSoftwareAbility.byHideAlarmSpt;
	m_bShelterSPT = struSoftwareAbility.byShelterSpt;
    m_bRtsp = struSoftwareAbility.byRtspSupport;
	m_bRtpoverRtsp = struSoftwareAbility.byRtpOverRtspSpt;
	m_bHttpOverRtspSPT = struSoftwareAbility.byRtspOverHttpSpt;
    m_bNtp = struSoftwareAbility.byNtpSupport;
    m_bEptz = struSoftwareAbility.byEptzSupport;
	m_bPtzSPT = struSoftwareAbility.byPtzSpt;
    m_bDDNS = struSoftwareAbility.byDDNSSupport;
	SetRangeToWnd(&m_lstDdnsType,struSoftwareAbility.byDDNSHostType,
		sizeof(struSoftwareAbility.byDDNSHostType));
//	m_csDDNSType.Format("%s",struSoftwareAbility.chDDNSHostType);
	m_bSNMP = struSoftwareAbility.bySNMPSpt;
	SetRangeToWnd(&m_lstSnmpVersion,struSoftwareAbility.bySNMPVersion,
		sizeof(struSoftwareAbility.bySNMPVersion));
//	m_csSNMPVersion.Format("%s",struSoftwareAbility.chSNMPVersion);
    m_bUpnp = struSoftwareAbility.byUPNPSupport;
	m_bISCSISpt = struSoftwareAbility.byiSCSISpt;
    m_bIpv6 = struSoftwareAbility.byIpv6Support;
    m_bVca = struSoftwareAbility.byVcaSupport;
	m_bMulStreamSPT = struSoftwareAbility.byMulStreamSpt;
	m_bSubStreamSPT = struSoftwareAbility.bySubStreamSpt;
	m_bEmailSPT = struSoftwareAbility.byEmailSpt;
//	m_bSadp = struSoftwareAbility.bySadpSpt;
	SetRangeToWnd(&m_lstSadpVersion,struSoftwareAbility.bySadpVersion,
		sizeof(struSoftwareAbility.bySadpVersion));
//	m_csSadpVersion.Format("%s",struSoftwareAbility.chSadpVersion);
//	m_bZeroChanSPT = struSoftwareAbility.byZeroChanSpt;
	m_byZeroChanNum = struSoftwareAbility.byZeroChanNum;
	m_bBackup = struSoftwareAbility.byBackupSpt;
	m_bSmartSearch = struSoftwareAbility.bySmartSearchSpt;
	m_bATM = struSoftwareAbility.byATMSpt;
	m_bFileLockSPT = struSoftwareAbility.byFileLockSpt;
//	m_bVoiceTalkSPT = struSoftwareAbility.byVoiceTalkSpt;
	m_bBitrateLimit = struSoftwareAbility.byBitrateLimitSpt;
	m_iMaxLoginNum = struSoftwareAbility.iMaxLoginNum;
	m_iMaxPreviewNum = struSoftwareAbility.iMaxPreviewNum;
	m_iMaxPlayBackNum = struSoftwareAbility.iMaxPlayBackNum;
	m_iMaxChanLinkNum = struSoftwareAbility.iMaxChanLinkNum;
	m_bShutDown = struSoftwareAbility.byShutDownSpt;	
    return TRUE;
}

BOOL CDlgSoftHardAbility::SetHardAbilityToWnd(HARDWARE_ABILITY_PARAM struHardwareAbility)
{
	m_dwHardwareVersion = struHardwareAbility.dwHardwareVersion;
    m_iAlarmInNum = struHardwareAbility.byAlarmInPortNum;
    m_iAlarmOutNum = struHardwareAbility.byAlarmOutPortNum;
    m_iRs232Num = struHardwareAbility.byRs232Num;
    m_iRs485Num = struHardwareAbility.byRs485Num;

    m_iNetworkPortNum = struHardwareAbility.byNetworkPortNum;
    m_iUsbNum = struHardwareAbility.byUsbNum;
    m_iSDNum = struHardwareAbility.bySDNum;
	m_byHardDiskNum = struHardwareAbility.byHardDiskNum;
    m_iVideoInNum = struHardwareAbility.byVideoInNum;

    m_iVideoOutNum = struHardwareAbility.byVideoOutNum;
    m_iAudioInNum = struHardwareAbility.byAudioInNum;
    m_iAudioOutNum = struHardwareAbility.byAudioOutNum;
	m_byAudioTalkNum = struHardwareAbility.byAudioTalkNum;
    m_bSuportSD = struHardwareAbility.bySDSupport;
   
    m_bSupportWifi = struHardwareAbility.byWifiSupport;
    m_bSupportPOE = struHardwareAbility.byPOESupport;
    m_bSupportIRS = struHardwareAbility.byIRSSupport;
    m_bSupportVideo = struHardwareAbility.byVideoSupport;
    m_bSupportReset = struHardwareAbility.byResetSupport;
	m_byAnalogChanNum = struHardwareAbility.byAnalogChannelNum;
	m_byIPChanNum = struHardwareAbility.byIPChannelNum;
	m_bMulNetworkCard = struHardwareAbility.byMulNetworkCardSpt;
	m_byNetworkCardNum = struHardwareAbility.byNetworkCardNum;
	m_byVGANum = struHardwareAbility.byVGANum;
	m_byHDMINum = struHardwareAbility.byHDMINum;
	m_byCVBSNum = struHardwareAbility.byCVBSNum;
	m_byAuxoutNum = struHardwareAbility.byAuxoutNum;
//	m_bSupportRaid = struHardwareAbility.byRaidSpt;
	m_iRaidType = struHardwareAbility.iRaidType;
	
    m_dwFlashSize = struHardwareAbility.dwFlashSize;
    m_dwRamSize = struHardwareAbility.dwRamSize;
    m_csUsbVersion = struHardwareAbility.chUsbVersion;

    return TRUE;
}

BOOL CDlgSoftHardAbility::SetNeedRebootToWnd(NEEDREBOOT_PARAM struNeedReboot)
{
	m_bImportCFGFileReboot = struNeedReboot.byImportCfgFileReboot;
	m_bRS232Reboot = struNeedReboot.byRS232workModeReboot;
	m_bNetPortReboot = struNeedReboot.byNetPortReboot;
	m_bDHCPReboot = struNeedReboot.byDhcpEnableReboot;
	m_bHttpPortReboot = struNeedReboot.byHttpPortReboot;
	m_bPPPoeReboot = struNeedReboot.byPPPoEReboot;
	m_bHDParamReboot = struNeedReboot.byHDParamReboot;
	m_bRecordTimeReboot = struNeedReboot.byRecordTimeReboot;
	m_bVideoEncodeTypeReboot = struNeedReboot.byVideoEncodeTypeReboot;
	m_bAudioEncodeTypeReboot = struNeedReboot.byAudioEncodeTypeReboot;
	m_bStandardTypeReboot = struNeedReboot.byStandardTypeReboot;
	return TRUE;
}

void CDlgSoftHardAbility::ParseStrIndex(CString strIndex, byte* array, int iArrayLength)
{
    CString strTemp1 = _T("");
    CString strTemp2 = _T("");
    int iIndex = -1;
    
    strTemp1.Format("%s", strIndex);
    
    iIndex = strTemp1.Find(',', 0);
    
    //当没有','时，直接转换为数字
    if (-1 == iIndex)
    {
        //若转换得到的数字大于数组的维数或者小于0，则返回
        if (atoi(strTemp1) >= iArrayLength || atoi(strTemp1) < 0)
        {
            return;
        }
        array[atoi(strTemp1)] = 1;
        return;
    }
    
    //解析strIndex，设置数组的值
    while (iIndex != -1 )
    {
        strTemp2.Format("%s", strTemp1.Left(iIndex));
        //若转换得到的数字大于数组的维数或者小于0，则返回
        if (atoi(strTemp2) >= iArrayLength || atoi(strTemp2) < 0)
        {
            return;
        }
        array[atoi(strTemp2)] = 1;
        strTemp1.Delete(0, iIndex + 1);
        iIndex = strTemp1.Find(',', 0);
    }
    
    //若转换得到的数字大于数组的维数或者小于0，则返回
    if (atoi(strTemp2) >= iArrayLength || atoi(strTemp2) < 0)
    {
        return;
    }
    array[atoi(strTemp1)] = 1;
}

void	CDlgSoftHardAbility::SetRangeToWnd(CListBox* pList, BYTE* pArray, int iArrayLength)
{
	char szLan[128] = {0};
	int i =0;
    for (i =0; i < iArrayLength; i++)
    {
        if (1 == pArray[i])
        {
            sprintf(szLan, "%d", i);
            pList->AddString(szLan);
        }
    }
}
