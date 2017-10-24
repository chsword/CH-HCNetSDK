/**********************************************************
FileName:    DlgAddDevice.cpp
Description: add device    
Date:        2008/05/17
Note: 		<global>struct, define refer to GeneralDef.h, global variables and functions refer to ClientDemo.cpp   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/


#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgAddDevice.h"
#include ".\dlgadddevice.h"

// CDlgAddDevice dialog
/*********************************************************
  Function:	CDlgAddDevice
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgAddDevice, CDialog)
CDlgAddDevice::CDlgAddDevice(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddDevice::IDD, pParent)
	, m_csNodeName(_T(""))
	, m_nLoginPort(8000)
	, m_csUserName(_T("admin"))
	, m_csPwd(_T("abcd1234"))
	, m_iDeviceIndex(-1)
	, m_bChkGetIPByIPServer(FALSE)
	, m_csDeviceName(_T(""))
	, m_csDevSN(_T("E0120110526CCRR403594603"))
	, m_iIPServerPort(80)	
	, m_csDevAddr(_T("172.9.3.97"))
	, m_csDDNSAddr(_T("www.hiddns.com"))
{

}

/*********************************************************
  Function:	~CDlgAddDevice
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgAddDevice::~CDlgAddDevice()
{
}

/*********************************************************
  Function:	DoDataExchange
  Desc:		the map between control and variable
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgAddDevice::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgAddDevice)
    DDX_Text(pDX, IDC_EDIT_NODE_NAME, m_csNodeName);
    DDX_Text(pDX, IDC_DEVICE_USERNAME, m_csUserName);
    DDX_Text(pDX, IDC_DEVICE_PSW, m_csPwd);
    DDX_Check(pDX, IDC_CHK_GET_IP_BY_IPSERVER, m_bChkGetIPByIPServer);
    DDX_Text(pDX, IDC_EDIT_DEVICE_NAME, m_csDeviceName);
    DDX_Text(pDX, IDC_EDIT_ADD_DEV_SN, m_csDevSN);
    DDX_Text(pDX, IDC_IPSERVER_PORT, m_iIPServerPort);
    DDX_Text(pDX, IDC_DEVICE_PORT, m_nLoginPort);
    DDV_MinMaxInt(pDX, m_nLoginPort, 0, 65535);
    DDX_Text(pDX, IDC_DEVICE_ADDR, m_csDevAddr);
    DDV_MaxChars(pDX, m_csDevAddr, 128);
    DDX_Text(pDX, IDC_EDIT_DDNS_ADDR, m_csDDNSAddr);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COMBO_PROXY, m_cmbProxyType);
}

/*********************************************************
  Function:	BEGIN_MESSAGE_MAP
  Desc:		the map between control and function
  Input:	
  Output:	
  Return:	
**********************************************************/

BEGIN_MESSAGE_MAP(CDlgAddDevice, CDialog)
//{{AFX_MSG_MAP(CDlgAddDevice)
	ON_BN_CLICKED(IDC_ADD_DEVICE_OK, OnBnClickedAddDeviceOk)
	ON_BN_CLICKED(IDC_EXIT, OnBnClickedExit)
	ON_BN_CLICKED(IDC_BTN_GET_DEV_IP, OnBnClickedBtnGetDevIp)
	ON_BN_CLICKED(IDC_CHK_GET_IP_BY_IPSERVER, OnBnClickedChkGetIpByIPServer)
	ON_BN_CLICKED(IDC_ACTIVATE_DEVICE, OnActivateDevice)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*********************************************************
  Function:	OnInitDialog
  Desc:		initialize dialog
  Input:	
  Output:	
  Return:	
**********************************************************/
BOOL CDlgAddDevice::OnInitDialog()
{
	CDialog::OnInitDialog();
	UpdateData(TRUE);
	m_csNodeName.Format("dev%02d", m_iDeviceIndex);	
	GetDlgItem(IDC_EDIT_DDNS_ADDR)->EnableWindow(FALSE);
	OnBnClickedChkGetIpByIPServer();
    m_cmbProxyType.SetCurSel(0);
	UpdateData(FALSE);
	return TRUE;
}

/*********************************************************
  Function:	OnBnClickedAddDeviceOk
  Desc:		add device ok response function, log in and get device basic info
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgAddDevice::OnBnClickedAddDeviceOk()
{
	char szDeviceIP[128] = {0};
	char cUserName[100] = {0};
	char cPassword[100] = {0};
	NET_DVR_DEVICEINFO_V30 struDeviceInfo;//the info get when login
	LONG lUserID = -1;
	NET_DVR_NETCFG_V30 struNetCfg = {0};
	NET_DVR_DEVICECFG_V40 struDevCfg = {0};
	
	DWORD dwReturned = 0;
	CString csTemp;

	int nErr = 0;
	UpdateData(TRUE);

	if (m_csDevAddr.GetLength() <= 0 || m_csDevAddr.GetLength() > 128)
	{
		char szLan[256] = {0};
		g_StringLanType(szLan, "设备地址长度为1~128!", "please input the device address in 1 and 128 characters!");
		AfxMessageBox(szLan);
		return;
	}
	if (m_nLoginPort <= 0)
	{
		char szLan[256] = {0};
		g_StringLanType(szLan, "非法的端口号!", "illeage port!");
		AfxMessageBox(szLan);
		return;
	}
	if ((strlen(m_csUserName) > 32) || (strlen(m_csPwd) > 16))
	{
		char szLan[256] = {0};
		g_StringLanType(szLan, "用户名不能超过32位和密码不能超过16位!", "user name should be shorter than 32 BYTES and pwd should be shorter than 16 BYTES!");
		AfxMessageBox(szLan);
		return;
	}

	sprintf(szDeviceIP, "%s", m_csDevAddr.GetBuffer(m_csDevAddr.GetLength()));
	strncpy(cUserName, m_csUserName, NAME_LEN);
	strncpy(cPassword, m_csPwd, PASSWD_LEN);
	if (strncmp(m_csNodeName.GetBuffer(0), "All", 3)==0)//Use "All.X" X means the device number，From 192.168.1.Y To 192.168.1.X+Y
	{
		strtok(m_csNodeName.GetBuffer(0), ".");
		
		nErr = atoi(strtok(NULL, "."));
		nErr = min(nErr, MAX_DEVICES-m_iDeviceIndex);
		sprintf(cPassword, "%s", strtok(szDeviceIP, "."));;
		strcat(cPassword, ".");
		strcat(cPassword, strtok(NULL, "."));
		strcat(cPassword, ".");
		strcat(cPassword, strtok(NULL, "."));
		int lastnum = atoi(strtok(NULL, "."));
		int iDeviceIndex = 0;
		for (int i = 0; i<nErr; i++)
		{
			iDeviceIndex = m_iDeviceIndex+i;
			sprintf(g_struDeviceInfo[iDeviceIndex].chLoginUserName, "admin");
			sprintf(g_struDeviceInfo[iDeviceIndex].chLoginPwd, "abcd1234");
			sprintf(g_struDeviceInfo[iDeviceIndex].chDeviceIP, "%s.%d", cPassword, lastnum+i);
			g_struDeviceInfo[iDeviceIndex].iDeviceIndex = m_iDeviceIndex+i;
			g_struDeviceInfo[iDeviceIndex].iDeviceChanNum = 1;
			g_struDeviceInfo[iDeviceIndex].lDevicePort = m_nLoginPort;
			sprintf(g_struDeviceInfo[iDeviceIndex].chLocalNodeName, "%s", g_struDeviceInfo[iDeviceIndex].chDeviceIP);
			g_pMainDlg->RedrawDeviceNode(iDeviceIndex+1000);
		}
		
		g_SaveDeviceConfig();
		CDialog::OnOK();
		return;
	}
	memset(&struDeviceInfo, 0, sizeof(NET_DVR_DEVICEINFO_V30));

	if (m_csNodeName.GetLength() == 0)
	{
		m_csNodeName.Format("%s", szDeviceIP);
	}

	memcpy(szDeviceIP, NULL, 0);

    NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
    NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};
    struLoginInfo.bUseAsynLogin = false;
    memcpy(struLoginInfo.sDeviceAddress, szDeviceIP, NET_DVR_DEV_ADDRESS_MAX_LEN);
    memcpy(struLoginInfo.sUserName, cUserName, NAME_LEN);
    memcpy(struLoginInfo.sPassword, cPassword, PASSWD_LEN);
    struLoginInfo.wPort = m_nLoginPort;
    struLoginInfo.byProxyType = m_cmbProxyType.GetCurSel();
    g_struDeviceInfo[m_iDeviceIndex].byProxyType = struLoginInfo.byProxyType;
    //struLoginInfo.byUseTransport = 1;
    //struLoginInfo.byRes3[119] = 2;
    lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);
	if (lUserID < 0)
	{
        char szLan[128] = {0};
		nErr = NET_DVR_GetLastError();
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_Login_V30[%s]", szDeviceIP);
        if (nErr == NET_DVR_PASSWORD_ERROR)
        {
            g_StringLanType(szLan, "用户名密码错误!", "user name or password error!");
            AfxMessageBox(szLan);
            if(1 == struDeviceInfoV40.bySupportLock)
            {
                sprintf(szLan, "还剩%d尝试机会", struDeviceInfoV40.byRetryLoginTime);
                AfxMessageBox(szLan);
            }
        }
        else if (nErr == NET_DVR_USER_LOCKED)
        {
            if(1 == struDeviceInfoV40.bySupportLock)
            {
                sprintf(szLan, "IP被锁定，剩余锁定时间%dS", struDeviceInfoV40.dwSurplusLockTime);
                AfxMessageBox(szLan);
            }
        }
        else		//TODO: other error value
        {
            char szLan[256] = {0};
            g_StringLanType(szLan, "由于网络原因或DVR忙, 注册失败!", "net error or dvr is busy!");
            AfxMessageBox(szLan);
        }
        return;
    }
    else
    {
        if (1 == struDeviceInfoV40.byPasswordLevel)
        {
            char szLan[128] = {0};
            g_StringLanType(szLan, "默认密码，请修改", "default password, please change the password");
            AfxMessageBox(szLan);
        }
        else if(3 == struDeviceInfoV40.byPasswordLevel)
        {
            char szLan[128] = {0};
            g_StringLanType(szLan, "风险密码，请修改", "risk password, please change the password");
            AfxMessageBox(szLan);
        }
        memcpy(&struDeviceInfo, &struDeviceInfoV40.struDeviceV30, sizeof(struDeviceInfo));
    }

	if(g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo == NULL)
    {
        g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo =  new STRU_CHANNEL_INFO[MAX_CHANNUM_V40];
		
        if(g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo == NULL)
        {
            char szLan[256] = {0};            
            g_StringLanType(szLan, "申请内存失败", "Alloc memory  failed");            
            AfxMessageBox(szLan);
            return;
        }
        for (int i= 0; i < MAX_CHANNUM_V40; i++ )
        {
            memset(&g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i], 0, sizeof(STRU_CHANNEL_INFO));
            g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].lRealHandle = -1;
			g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iChanIndex = -1;
        }
        
    }
	
    if (g_struDeviceInfo[m_iDeviceIndex].pStruIPAlarmInCfgV40 == NULL)
    {
        g_struDeviceInfo[m_iDeviceIndex].pStruIPAlarmInCfgV40 = new NET_DVR_IPALARMINCFG_V40;
		
        if (g_struDeviceInfo[m_iDeviceIndex].pStruIPAlarmInCfgV40 == NULL)
        {
            char szLan[256] = {0};            
            g_StringLanType(szLan, "申请内存失败", "Alloc memory  failed");            
            AfxMessageBox(szLan);
            return;
        }
		
        memset(g_struDeviceInfo[m_iDeviceIndex].pStruIPAlarmInCfgV40, 0, sizeof(NET_DVR_IPALARMINCFG_V40));
    }
	
    if (g_struDeviceInfo[m_iDeviceIndex].pStruIPAlarmOutCfgV40 == NULL)
    {
        g_struDeviceInfo[m_iDeviceIndex].pStruIPAlarmOutCfgV40 =  new NET_DVR_IPALARMOUTCFG_V40;
        if (g_struDeviceInfo[m_iDeviceIndex].pStruIPAlarmOutCfgV40 == NULL)
        {
            char szLan[256] = {0};            
            g_StringLanType(szLan, "申请内存失败", "Alloc memory  failed");            
            AfxMessageBox(szLan);
            return;
        }
		
        memset(g_struDeviceInfo[m_iDeviceIndex].pStruIPAlarmOutCfgV40, 0, sizeof(NET_DVR_IPALARMOUTCFG_V40));
    }
	
    g_struDeviceInfo[m_iDeviceIndex].byCharaterEncodeType = struDeviceInfoV40.byCharEncodeType;
	sprintf(g_struDeviceInfo[m_iDeviceIndex].chLoginUserName, "%s", cUserName);
	sprintf(g_struDeviceInfo[m_iDeviceIndex].chLoginPwd, "%s", cPassword);
	sprintf(g_struDeviceInfo[m_iDeviceIndex].chDeviceIP, "%s", szDeviceIP);

	g_struDeviceInfo[m_iDeviceIndex].lLoginID = lUserID;
	sprintf(g_struDeviceInfo[m_iDeviceIndex].chSerialNumber, "%s", struDeviceInfo.sSerialNumber);
	g_struDeviceInfo[m_iDeviceIndex].iDeviceIndex = m_iDeviceIndex;
	g_struDeviceInfo[m_iDeviceIndex].iDeviceType = struDeviceInfo.wDevType;  //用扩展字段表示设备类型
	g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum = struDeviceInfo.byChanNum + struDeviceInfo.byIPChanNum  + struDeviceInfo.byHighDChanNum*256;
	g_struDeviceInfo[m_iDeviceIndex].iStartChan = struDeviceInfo.byStartChan;
	g_struDeviceInfo[m_iDeviceIndex].iDiskNum = struDeviceInfo.byDiskNum;
	g_struDeviceInfo[m_iDeviceIndex].iAlarmOutNum = struDeviceInfo.byAlarmOutPortNum;
	g_struDeviceInfo[m_iDeviceIndex].iAlarmInNum = struDeviceInfo.byAlarmInPortNum;
	g_struDeviceInfo[m_iDeviceIndex].iAudioNum = struDeviceInfo.byAudioChanNum;
	g_struDeviceInfo[m_iDeviceIndex].iAnalogChanNum = struDeviceInfo.byChanNum;
	g_struDeviceInfo[m_iDeviceIndex].iIPChanNum = struDeviceInfo.byIPChanNum +  struDeviceInfo.byHighDChanNum*256;
    g_struDeviceInfo[m_iDeviceIndex].byZeroChanNum = struDeviceInfo.byZeroChanNum;
	g_struDeviceInfo[m_iDeviceIndex].byStartDTalkChan = struDeviceInfo.byStartDTalkChan;
    g_struDeviceInfo[m_iDeviceIndex].byLanguageType = struDeviceInfo.byLanguageType;
	g_struDeviceInfo[m_iDeviceIndex].byMirrorChanNum = struDeviceInfo.byMirrorChanNum;
	g_struDeviceInfo[m_iDeviceIndex].wStartMirrorChanNo = struDeviceInfo.wStartMirrorChanNo;
	g_struDeviceInfo[m_iDeviceIndex].byAudioInputChanNum = struDeviceInfo.byVoiceInChanNum;
    g_struDeviceInfo[m_iDeviceIndex].byStartAudioInputChanNo = struDeviceInfo.byStartVoiceInChanNo;
	if (struDeviceInfo.bySupport & 0x80)
	{
		g_struDeviceInfo[m_iDeviceIndex].byMainProto = struDeviceInfo.byMainProto + 2;
		g_struDeviceInfo[m_iDeviceIndex].bySubProto = struDeviceInfo.bySubProto + 2;
	}
	else
	{
		g_struDeviceInfo[m_iDeviceIndex].byMainProto = struDeviceInfo.byMainProto;
		g_struDeviceInfo[m_iDeviceIndex].bySubProto = struDeviceInfo.bySubProto;
	}    

	sprintf(g_struDeviceInfo[m_iDeviceIndex].chLocalNodeName, "%s", m_csNodeName.GetBuffer(0));
	g_struDeviceInfo[m_iDeviceIndex].lDevicePort = m_nLoginPort;
	g_struDeviceInfo[m_iDeviceIndex].bySupport1 = struDeviceInfo.bySupport1;
    g_struDeviceInfo[m_iDeviceIndex].bySupport2 = struDeviceInfo.bySupport2;
	g_struDeviceInfo[m_iDeviceIndex].bySupport7 = struDeviceInfo.bySupport7;
    g_struDeviceInfo[m_iDeviceIndex].byLanguageType = struDeviceInfo.byLanguageType;

    char sIPV6Addr[130] = { 0 };
    int i = 0;
    for (; i < sizeof(g_struDeviceInfo[m_iDeviceIndex].chDeviceIP); i++)
    {
        if (g_struDeviceInfo[m_iDeviceIndex].chDeviceIP[i] == '\0')
        {
            break;
        }
        else if (g_struDeviceInfo[m_iDeviceIndex].chDeviceIP[i] == ':')
        {
            sIPV6Addr[i] = '.';
        }
        else
        {
            sIPV6Addr[i] = g_struDeviceInfo[m_iDeviceIndex].chDeviceIP[i];
        }
    }
    strncpy(g_struDeviceInfo[m_iDeviceIndex].chDeviceIPInFileName, sIPV6Addr, sizeof(sIPV6Addr));


	if (!NET_DVR_GetDVRConfig(lUserID, NET_DVR_GET_NETCFG_V30, 0, &struNetCfg, sizeof(NET_DVR_NETCFG_V30), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_NETCFG_V30");	
	}
	else
	{		
					//sprintf(g_struDeviceInfo[m_iDeviceIndex].chDevNetCard1IP, "%s", struNetCfg.struEtherNet[0].struDVRIP.sIpV4);
        if (!g_ValidIPv6((BYTE *)(g_struDeviceInfo[m_iDeviceIndex].chDeviceIP)))
        {
            sprintf(g_struDeviceInfo[m_iDeviceIndex].chDeviceMultiIP, "%s", struNetCfg.struMulticastIpAddr.sIpV4);
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "multi-cast ipv4[%s]", struNetCfg.struMulticastIpAddr.sIpV4);
        }
        else
		{
			sprintf(g_struDeviceInfo[m_iDeviceIndex].chDeviceMultiIP, "%s", struNetCfg.struMulticastIpAddr.byIPv6);
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "multi-cast ipv6[%s]", struNetCfg.struMulticastIpAddr.byIPv6);
		}
        
#if 0
		//IPv6 mcast test	

		memset(g_struDeviceInfo[m_iDeviceIndex].chDeviceMultiIP, 0, sizeof(g_struDeviceInfo[m_iDeviceIndex].chDeviceMultiIP));
		sprintf(g_struDeviceInfo[m_iDeviceIndex].chDeviceMultiIP, "ff02::1234");
#endif		
	}
    //2011-12-29
	if (!NET_DVR_GetDVRConfig(lUserID,NET_DVR_GET_DEVICECFG_V40,0,&struDevCfg,sizeof(NET_DVR_DEVICECFG_V40),&dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_DEVICECFG_V40");
	}
    else
	{
		if (g_struDeviceInfo[m_iDeviceIndex].iDeviceType != (int)struDevCfg.wDevType)
		{
			char szLan[256] = {0};
			char szLanShow[256] = {0};
			g_StringLanType(szLan, "登陆返回设备类型值与获取设备参数返回设备类型值不同", "returned device type is different between login and get device config");
			sprintf(szLanShow,"%s %d,%d",szLan,g_struDeviceInfo[m_iDeviceIndex].iDeviceType,struDevCfg.wDevType);
			AfxMessageBox(szLanShow);
		}
		
		sprintf(g_struDeviceInfo[m_iDeviceIndex].chDeviceName,"%s",struDevCfg.byDevTypeName);
		g_struDeviceInfo[m_iDeviceIndex].dwDevSoftVer = struDevCfg.dwSoftwareVersion;
        ClassifyDevClass(g_struDeviceInfo[m_iDeviceIndex].chDeviceClassName, 100, struDevCfg.wDevClass);
	}


    //Analog Chan Info
    
    if (g_struDeviceInfo[m_iDeviceIndex].iDeviceType == DS_B20_MSU_NP || \
        g_struDeviceInfo[m_iDeviceIndex].iDeviceType == DS_MMC_B20_CLASS || \
        g_struDeviceInfo[m_iDeviceIndex].iDeviceType == DS_B21_MCU_NP_CLASS || \
        g_struDeviceInfo[m_iDeviceIndex].iDeviceType == DS_C20N_VWMS) //B20/B21主控
	{
		int nAllChanNums = 0;
		int nPreChanNums = 0;
		NET_DVR_ALLSUBSYSTEMINFO_V40 struSubSystemInfoV40 = {0};
		if (NET_DVR_MatrixGetSubSystemInfo_V40(lUserID, &struSubSystemInfoV40))
		{
			for (int nSysCnt = 0; nSysCnt < MAX_SUBSYSTEM_NUM_V40; nSysCnt++)
			{
				if (struSubSystemInfoV40.struSubSystemInfo[nSysCnt].bySubSystemType == 2 &&
					struSubSystemInfoV40.struSubSystemInfo[nSysCnt].byBelongBoard != 0xff &&
					struSubSystemInfoV40.struSubSystemInfo[nSysCnt].byInterfaceNums != 0)
				{
					nPreChanNums = nAllChanNums;
					nAllChanNums += struSubSystemInfoV40.struSubSystemInfo[nSysCnt].byInterfaceNums;
					for (int nChanCnt =0 ;nChanCnt < struSubSystemInfoV40.struSubSystemInfo[nSysCnt].byInterfaceNums; nChanCnt++)
					{
						DWORD dwDevNo = 1;
						DWORD dwBelongBoard = struSubSystemInfoV40.struSubSystemInfo[nSysCnt].byBelongBoard;
						DWORD dwChanNo = struSubSystemInfoV40.struSubSystemInfo[nSysCnt].byInterfaceStartNum + nChanCnt;
						g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[nPreChanNums+nChanCnt].iDeviceIndex = m_iDeviceIndex;
						g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[nPreChanNums+nChanCnt].iChanIndex = nPreChanNums+nChanCnt;
						g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[nPreChanNums+nChanCnt].bEnable = TRUE;
						g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[nPreChanNums+nChanCnt].iChanType = DEMO_CHANNEL_TYPE_ANALOG;
						sprintf(g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[nPreChanNums+nChanCnt].chChanName, "Camera_%d_%d_%d", dwDevNo, dwBelongBoard, dwChanNo);
						g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[nPreChanNums+nChanCnt].iChannelNO = dwDevNo<<24|dwBelongBoard<<16|dwChanNo;
					}
				}
			}
			g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum = nAllChanNums;
			g_struDeviceInfo[m_iDeviceIndex].iAnalogChanNum = nAllChanNums;
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_MatrixGetSubSystemInfo_V40");
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_MatrixGetSubSystemInfo_V40");
			char szLan[128] = {0};
			g_StringLanType(szLan, "获取主板子系统信息失败", "failed to get subsystem information");
			AfxMessageBox(szLan);
			return;
		}
	}
	else
	{
		for (int i = 0; i <  g_struDeviceInfo[m_iDeviceIndex].iAnalogChanNum; i++)
		{
			g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iDeviceIndex = m_iDeviceIndex;
			g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iChanIndex = i;
			g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iChannelNO = i + g_struDeviceInfo[m_iDeviceIndex].iStartChan;
			g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].bEnable = TRUE;
			g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iChanType = DEMO_CHANNEL_TYPE_ANALOG;
			sprintf(g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].chChanName, ANALOG_C_FORMAT, i+g_struDeviceInfo[m_iDeviceIndex].iStartChan);
		}
	}

    if (g_struDeviceInfo[m_iDeviceIndex].byZeroChanNum > 0)
    {
        for (int i=0; i<g_struDeviceInfo[m_iDeviceIndex].byZeroChanNum; i++)
        {
                g_struDeviceInfo[m_iDeviceIndex].struZeroChan[i].iDeviceIndex = m_iDeviceIndex;
                g_struDeviceInfo[m_iDeviceIndex].struZeroChan[i].iChanIndex = i+ZERO_CHAN_INDEX;
                sprintf(g_struDeviceInfo[m_iDeviceIndex].struZeroChan[i].chChanName, "ZeroChan%d", i);	
                //analog devices
                if (1)
                {
                    g_struDeviceInfo[m_iDeviceIndex].struZeroChan[i].bEnable = TRUE;
                    g_struDeviceInfo[m_iDeviceIndex].struZeroChan[i].dwImageType = CHAN_ORIGINAL;
                    //				g_struDeviceInfo[iDeviceIndex].iEnableChanNum ++;
                }
                else
                {
                    g_struDeviceInfo[m_iDeviceIndex].struZeroChan[i].dwImageType = CHAN_OFF_LINE;
                    g_struDeviceInfo[m_iDeviceIndex].struZeroChan[i].bEnable = FALSE;		
                }
        }
    }

	if ((g_struDeviceInfo[m_iDeviceIndex].byMirrorChanNum > 0) && (g_struDeviceInfo[m_iDeviceIndex].wStartMirrorChanNo > (g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum -1)))
    {
        for (int i=0; i<g_struDeviceInfo[m_iDeviceIndex].byMirrorChanNum && i < 16; i++)
        {
			g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].iDeviceIndex = m_iDeviceIndex;
			g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].iChanIndex = i + MIRROR_CHAN_INDEX;
			g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].iChannelNO = i + g_struDeviceInfo[m_iDeviceIndex].wStartMirrorChanNo;
			sprintf(g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].chChanName, "MirrorChan%d", i+1);	
			//analog devices
			if (1)
			{
				g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].bEnable = TRUE;
				g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].dwImageType = CHAN_ORIGINAL;
				//				g_struDeviceInfo[iDeviceIndex].iEnableChanNum ++;
			}
			else
			{
				g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].dwImageType = CHAN_OFF_LINE;
				g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[i].bEnable = FALSE;		
			}
        }
    }
    
	//g_pMainDlg->DoGetDeviceResoureCfg(m_iDeviceIndex);
	//new IP channel parameters
    if (g_struDeviceInfo[m_iDeviceIndex].iIPChanNum >=  0)
    {    
        if (g_struDeviceInfo[m_iDeviceIndex].iIPChanNum == 0)
        {
            g_struDeviceInfo[m_iDeviceIndex].pStruIPParaCfgV40 =new NET_DVR_IPPARACFG_V40;
            memset(g_struDeviceInfo[m_iDeviceIndex].pStruIPParaCfgV40, 0, sizeof(NET_DVR_IPPARACFG_V40));
        }
        else
        {
            if (g_struDeviceInfo[m_iDeviceIndex].iIPChanNum % MAX_CHANNUM_V30 == 0)
            {
                g_struDeviceInfo[m_iDeviceIndex].pStruIPParaCfgV40 =new NET_DVR_IPPARACFG_V40[g_struDeviceInfo[m_iDeviceIndex].iIPChanNum/MAX_CHANNUM_V30];
                for (int i = 0; i < g_struDeviceInfo[m_iDeviceIndex].iIPChanNum/MAX_CHANNUM_V30; i++)
                {
                    memset(&g_struDeviceInfo[m_iDeviceIndex].pStruIPParaCfgV40[i], 0, sizeof(NET_DVR_IPPARACFG_V40));
                }
            }
            else
            {
                g_struDeviceInfo[m_iDeviceIndex].pStruIPParaCfgV40 =new NET_DVR_IPPARACFG_V40[g_struDeviceInfo[m_iDeviceIndex].iIPChanNum/MAX_CHANNUM_V30 + 1];
                for (int i = 0; i < g_struDeviceInfo[m_iDeviceIndex].iIPChanNum/MAX_CHANNUM_V30 + 1; i++)
                {
                    memset(&g_struDeviceInfo[m_iDeviceIndex].pStruIPParaCfgV40[i], 0, sizeof(NET_DVR_IPPARACFG_V40));
                }
            }
        }
        if (g_struDeviceInfo[m_iDeviceIndex].pStruIPParaCfgV40 == NULL)
        {
            char szLan[256] = {0};            
            g_StringLanType(szLan, "申请内存失败", "Alloc memory  failed");            
            AfxMessageBox(szLan);
            return;
        }
        g_pMainDlg->DoGetDeviceResoureCfg(m_iDeviceIndex);
    }
     
	g_SaveDeviceConfig();
	CDialog::OnOK();
}

/*********************************************************
  Function:	OnBnClickedExit
  Desc:		exit, no adding
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgAddDevice::OnBnClickedExit()
{
	CDialog::OnCancel();
}

/*********************************************************
Function:	OnBnClickedChkGetIpByIPServer
Desc:		get IP address of the device through IPServer
Input:	
Output:	
Return:	
**********************************************************/
void CDlgAddDevice::OnBnClickedChkGetIpByIPServer()
{
	UpdateData(TRUE);
    if (m_bChkGetIPByIPServer)
    {
		GetDlgItem(IDC_EDIT_DDNS_ADDR)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DEVICE_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_GET_DEV_IP)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_ADD_DEV_SN)->EnableWindow(TRUE);
	 	GetDlgItem(IDC_DEVICE_ADDR)->EnableWindow(FALSE);	
    }
	else
	{
		GetDlgItem(IDC_EDIT_DDNS_ADDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DEVICE_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_ADD_DEV_SN)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_GET_DEV_IP)->EnableWindow(FALSE);
	 	GetDlgItem(IDC_DEVICE_ADDR)->EnableWindow(TRUE);
	}
	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnBnClickedBtnGetDevIp
  Desc:		get IP address
  Input:	
  Output:	
  Return:	
**********************************************************/
#define IPSERVER_PORT 7071
void CDlgAddDevice::OnBnClickedBtnGetDevIp()
{
	UpdateData(TRUE);
	char szGetDevIP[128] = {0};		
	sprintf(g_struLocalParam.chIPServerIP, "%s", m_csDDNSAddr.GetBuffer(0));
	DWORD dwPort = 0;
	if (!NET_DVR_GetDVRIPByResolveSvr_EX(m_csDDNSAddr.GetBuffer(0), (WORD)m_iIPServerPort/*IPSERVER_PORT*/, (BYTE *)(m_csDeviceName.GetBuffer(0)), (WORD)m_csDeviceName.GetLength(),\
		(BYTE *)m_csDevSN.GetBuffer(0), (WORD)m_csDevSN.GetLength(), szGetDevIP, &dwPort))
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_GetDVRIPByResolveSvr");
		char szLan[1024] = {0};
		g_StringLanType(szLan, "获取设备地址失败!", "get device address error!");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_GetDVRIPByResolveSvr");
		m_csDevAddr = szGetDevIP;
		m_nLoginPort = dwPort;
	}	
	UpdateData(FALSE);
}


void CDlgAddDevice::OnActivateDevice() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
	char szLan[256] = {0};
    if ((strlen(m_csPwd) > 16))
    {
        g_StringLanType(szLan, "密码不能超过16位！", "pwd should be shorter than 16 BYTES!");
        AfxMessageBox(szLan);
        return;
	}
    NET_DVR_ACTIVATECFG struActivateCfg = {0};
    struActivateCfg.dwSize = sizeof(struActivateCfg);
    memcpy(struActivateCfg.sPassword, m_csPwd.GetBuffer(0), m_csPwd.GetLength());
	if(!NET_DVR_ActivateDevice(m_csDevAddr.GetBuffer(0), m_nLoginPort, &struActivateCfg))
    {
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_ActivateDevice");
        LONG dwErr = NET_DVR_GetLastError();
        AfxMessageBox(NET_DVR_GetErrorMsg(&dwErr));
    }
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_ActivateDevice");
		g_StringLanType(szLan, "设备激活成功！", "The Device is activated successfully!");
        AfxMessageBox(szLan);
	}
}
