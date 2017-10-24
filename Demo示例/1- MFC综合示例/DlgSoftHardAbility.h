#if !defined(AFX_DLGSOFTHARDABILITY_H__6FB2DEEB_5242_4460_ABCE_1573D2CA04F9__INCLUDED_)
#define AFX_DLGSOFTHARDABILITY_H__6FB2DEEB_5242_4460_ABCE_1573D2CA04F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSoftHardAbility.h : header file
//
#define MAX_VERSION_LENGTH 8
/////////////////////////////////////////////////////////////////////////////
// CDlgSoftHardAbility dialog
#include "Markup.h"

typedef struct tagSOFTWARE_ABILITY_PARAM
{
    BYTE    byNASSupport;				// 是否支持nas存储功能：1-支持，不支持时没有该节点
	BYTE	byNASNum;					// 支持nas个数，8，不支持时没有该节点
	BYTE	byShowStringNum;			// 支持字符串叠加个数,8
	BYTE	byMotionAlarmSpt;			// 是否支持移动侦测报警，1-支持，不支持时没有该节点
    BYTE	byVILostAlarmSpt;			// 是否支持视频丢失报警，1-支持，不支持时没有该节点
	BYTE	byHideAlarmSpt;				// 是否支持遮挡报警，1-支持，不支持时没有该节点
	BYTE	byShelterSpt;				// 是否支持遮盖，1-支持，不支持时没有该节点
	BYTE    byRtspSupport;				// 是否支持rtsp网络传输功能，1-支持，不支持时没有该节点
	BYTE	byRtpOverRtspSpt;			// 是否支持rtp over rtsp网络传输功能，1-支持，不支持时没有该节点
	BYTE	byRtspOverHttpSpt;			// 是否支持http over rtsp网络传输功能，1-支持，不支持时没有该节点
	
    BYTE    byNtpSupport;				// 是否支持NTP校时- 1-支持，不支持时没有该节点
    BYTE    byEptzSupport;				// 是否支持电子云台，1-支持，不支持时没有该节点       
    BYTE	byPtzSpt;					// 是否支持云台控制，1-支持，不支持时没有该节点
	BYTE    byDDNSSupport;				// 是否支持DDNS - 1-支持，不支持时没有该节点
    BYTE	byDDNSHostType[MAX_VERSION_LENGTH];// DDNS服务器类型，0-Hi DDNS，1-Dyndns，2-PeanutHull(花生壳)，3-NO-IP
	BYTE	bySNMPSpt;					// 是否支持SNMP,1-支持，不支持时没有该节点
	BYTE    bySNMPVersion[MAX_VERSION_LENGTH];				// SNMP协议版本，1:v1,2:v2,3:v3
	BYTE    byUPNPSupport;				// 是否支持UPNP- 1-支持，不支持时没有该节点
    BYTE	byiSCSISpt;					// 是否支持iSCSI，1-支持，不支持时没有该节点
	BYTE    byIpv6Support;				// 是否支持ipv6- 1-支持，不支持时没有该节点
    BYTE    byVcaSupport;				// 是否支持智能- 1-支持，不支持时没有该节点
    BYTE	byMulStreamSpt;				// 是否支持复合流，1-支持，不支持时没有该节点
	BYTE	bySubStreamSpt;				// 是否支持字码流，1-支持，不支持时没有该节点
	BYTE	byEmailSpt;					// 是否支持Email，1-支持，不支持时没有该节点
//	BYTE	bySadpSpt;					// 是否支持sadp，0：不支持，1：支持 私有大屏不支持
	BYTE    bySadpVersion[MAX_VERSION_LENGTH];				// sadp版本，0：v1.0，1：v2.0，不支持时没有该节点
//	BYTE	byZeroChanSpt;				// 是否支持零通道，0：不支持，1：支持
	BYTE	byZeroChanNum;				// 零通道编码个数，1，1-支持，不支持时没有该节点
    BYTE	byBackupSpt;				// 是否支持备份，1-支持，不支持时没有该节点
	BYTE	bySmartSearchSpt;			// 是否支持智能搜索录像，1-支持，不支持时没有该节点
	BYTE	byATMSpt;					// 是否支持ATM配置，1-支持，不支持时没有该节点
	BYTE	byFileLockSpt;				// 是否支持文件锁定/解锁，1-支持，不支持时没有该节点
//	BYTE	byVoiceTalkSpt;				// 是否支持语音对讲，1-支持，不支持时没有该节点
	BYTE	byBitrateLimitSpt;			// 是否支持主子码流码率动态限制，1-支持，不支持时没有该节点
//	BYTE	res;
	int		iMaxLoginNum;				// 支持最大注册路数，512，一般产品128,视频综合平台32
	int		iMaxPreviewNum;				// 支持最大预览路数，512，老产品24,新的64
	int		iMaxPlayBackNum;			// 支持最大回放路数，512，前端:回放/预览合计24
	int		iMaxChanLinkNum;			// 通道支持最大连接数，512，新后端产品128,其他为6
	BYTE	byShutDownSpt;				// 是否支持关机，1-支持，不支持时没有该节点
	BYTE	byFrameFreezeSpt;			// 是否支持预置点冻结，1-支持，不支持时没有该节点
	tagSOFTWARE_ABILITY_PARAM()
    {
        byNASSupport = 0;
		byNASNum = 0;
		byShowStringNum = 0;
		byMotionAlarmSpt = 0;
		byVILostAlarmSpt = 0;
		byHideAlarmSpt = 0;
		byShelterSpt = 0;
        byRtspSupport = 0;
		byRtpOverRtspSpt = 0;
		byRtspOverHttpSpt = 0;
        byNtpSupport = 0;
        byEptzSupport = 0;
		byPtzSpt = 0;		
        byDDNSSupport = 0;
		memset(byDDNSHostType,0,sizeof(byDDNSHostType));
	//	byDDNSHostType = 0;
		bySNMPSpt = 0;
		memset(bySNMPVersion,0,sizeof(bySNMPVersion));
	//	bySNMPVersion = 0;
        byUPNPSupport = 0;
		byiSCSISpt = 0;
		byIpv6Support  = 0;
        byVcaSupport = 0;
		byMulStreamSpt = 0;
		bySubStreamSpt = 0;
		byEmailSpt = 0;
	//	bySadpSpt = 0;
		memset(bySadpVersion,0,sizeof(bySadpVersion));
	//	bySadpVersion = 0;
	//	byZeroChanSpt = 0;
		byZeroChanNum = 0;
		byBackupSpt = 0;
		bySmartSearchSpt = 0;
		byATMSpt = 0;
		byFileLockSpt = 0;
	//	byVoiceTalkSpt = 0;
		byBitrateLimitSpt = 0;
		iMaxLoginNum = 0;
		iMaxPreviewNum = 0;
		iMaxPlayBackNum = 0;
		iMaxChanLinkNum = 0;
		byShutDownSpt = 0;
		byFrameFreezeSpt = 0;
    }
}SOFTWARE_ABILITY_PARAM, *LPSOFTWARE_ABILITY_PARAM;


typedef struct tagHARDWARE_ABILITY_PARAM
{
    BYTE    byAlarmInPortNum;   // 报警输入个数
    BYTE    byAlarmOutPortNum;  // 报警输出个数
    BYTE    byRs232Num;         // RS232个数
    BYTE    byRs485Num;         // RS485个数    
    BYTE    byNetworkPortNum;   // 网口个数
    BYTE    byUsbNum;           // USB个数
    BYTE    bySDNum;            // SD卡个数
	BYTE	byHardDiskNum;		// 硬盘个数
    BYTE    byVideoInNum;       // VideoInNum    
    BYTE    byVideoOutNum;      // VideoOutNum
    BYTE    byAudioInNum;       // AIN个数
    BYTE    byAudioOutNum;      // AOUT个数
	BYTE	byAudioTalkNum;		// 语音对讲通道个数，2
    BYTE    bySDSupport;        // 是否支持SD卡    
    BYTE    byWifiSupport;      // 是否支持WiFi- 1：支持,不支持时没有该节点
    BYTE    byPOESupport;       // 是否支持POE- 1：支持,不支持时没有该节点
    BYTE    byIRSSupport;       // 是否支持红外 - 1：支持,不支持时没有该节点
    BYTE    byVideoSupport;     // 是否支持本地输出- 1: 支持,不支持时没有该节点
    BYTE	byAnalogChannelNum; // 支持模拟通道个数，255
	BYTE	byIPChannelNum;		// 支持数字通道个数，255
	BYTE	byMulNetworkCardSpt;// 是否支持多网卡，1：支持,不支持时没有该节点
	BYTE	byNetworkCardNum;	// 支持多网卡个数，4
	BYTE	byVGANum;			// 支持VGA个数，255
	BYTE	byHDMINum;			// 支持HDMI个数，255
	BYTE	byCVBSNum;			// 支持CVBS个数，255
	BYTE	byAuxoutNum;		// 支持辅口个数，255
//	BYTE	byRaidSpt;			// 是否支持raid，1：支持,不支持时没有该节点
	int  	iRaidType;			// 0:硬raid,1:软raid,如果不支持raid，解析程序中默认用-1表示,能力集中则没有该节点
    BYTE    byResetSupport;     // 是否支持恢复出厂设置 1：支持,不支持时没有该节点
    BYTE    byRes1[3];          // 保留字节   
	DWORD	dwHardwareVersion;  // 面板版本
    DWORD   dwFlashSize;        // Flash大小
    DWORD   dwRamSize;          // Ram 大小
    char    chUsbVersion[MAX_VERSION_LENGTH];   // USB 版本
// 	DWORD	dwLocal485Num;
// 	DWORD	dwEx485Num;	
// 	DWORD	dwFullDuplex485Num;
// 	DWORD	dwSemiDuplex485Num;
// 	DWORD	dw485SlotNum;
// 	DWORD	dwLocalZoneNum;	
// 	DWORD	dwExZoneNum;
// 	DWORD	dwLocalTriggerNum;
// 	DWORD	dwExTriggerNum;
// 	DWORD	dwTotalSensorNum;
// 	DWORD	dwLocalSensorNum;
// 	DWORD	dwExSensorNum;
// 	BYTE	bySirenNum;

    tagHARDWARE_ABILITY_PARAM()
    {
        byAlarmInPortNum = 0;
        byAlarmOutPortNum = 0;
        byRs232Num = 0;
        byRs485Num = 0;
        
        byNetworkPortNum = 0;
        byUsbNum = 0;
        bySDNum = 0;
		byHardDiskNum = 0;
        byVideoInNum = 0;
        
        byVideoOutNum = 0;
        byAudioInNum = 0;
        byAudioOutNum = 0;
		byAudioTalkNum = 0;
        bySDSupport = 0;
        
        byWifiSupport = 0;
        byPOESupport = 0;
        byIRSSupport = 0;
        byVideoSupport = 0;
		byAnalogChannelNum = 0;
        byIPChannelNum = 0;
		byMulNetworkCardSpt = 0;
		byNetworkCardNum = 0;
		byVGANum = 0;
		byHDMINum = 0;
		byCVBSNum = 0;
		byAuxoutNum = 0;
//	    byRaidSpt = 0;	
		iRaidType = -1;
        byResetSupport = 0;
        memset(byRes1, 0, sizeof(byRes1));
        dwHardwareVersion = 0;
        dwFlashSize = 0;
        dwRamSize = 0;
        memset(chUsbVersion, 0, sizeof(chUsbVersion));
    }
}HARDWARE_ABILITY_PARAM, *LPHARDWARE_ABILITY_PARAM;

typedef struct tagNEEDREBOOT_PARAM
{
	BYTE	byImportCfgFileReboot;		// 导入配置文件是否自动重启，1：需要重启，不需要重启时没有该节点
	BYTE	byRS232workModeReboot;		// 串口232传输模式更改是否需要重启，1：需要重启，不需要重启时没有该节点
	BYTE	byNetPortReboot;			// 网络传输端口更改是否需要重启，1：需要重启，不需要重启时没有该节点
	BYTE	byDhcpEnableReboot;			// DHCP启用状态更改是否需要重启，1：需要重启，不需要重启时没有该节点
	BYTE	byHttpPortReboot;			// http端口更改是否需要重启，1：需要重启，不需要重启时没有该节点
	BYTE	byPPPoEReboot;				// pppoe参数更改是否需要重启，1：需要重启，不需要重启时没有该节点
	BYTE	byHDParamReboot;			// 硬盘参数更改是否需要重启，1：需要重启，不需要重启时没有该节点
	BYTE	byRecordTimeReboot;			// 录像计划的时间更改是否需要重启，1：需要重启，不需要重启时没有该节点
	BYTE	byVideoEncodeTypeReboot;	// 压缩参数的视频编码类型更改是否需要重启，1：需要重启，不需要重启时没有该节点
	BYTE	byAudioEncodeTypeReboot;	// 压缩参数的音频编码类型更改是否需要重启，1：需要重启，不需要重启时没有该节点
	BYTE	byStandardTypeReboot;		// 只是类型更改是否需要重启，1：需要重启，不需要重启时没有该节点
	tagNEEDREBOOT_PARAM()
	{
		byImportCfgFileReboot = 0;		
		byRS232workModeReboot = 0;		
		byNetPortReboot = 0;			
		byDhcpEnableReboot = 0;			
		byHttpPortReboot = 0;			
		byPPPoEReboot = 0;				
		byHDParamReboot = 0;			
		byRecordTimeReboot = 0;			
		byVideoEncodeTypeReboot = 0;	
		byAudioEncodeTypeReboot = 0;	
		byStandardTypeReboot = 0;	
	}
}NEEDREBOOT_PARAM,*LPNEEDREBOOT_PARAM;
typedef struct tagSOFTHARDWARE_ABILITY_PARAM
{
    SOFTWARE_ABILITY_PARAM struSoftAbilityParam;
    HARDWARE_ABILITY_PARAM struHardAbilityParam;
	NEEDREBOOT_PARAM struNeedRebootParam;
}SOFTHARDWARE_ABILITY_PARAM, *LPSOFTHARDWARE_ABILITY_PARAM;

class CDlgSoftHardAbility : public CDialog
{
// Construction
public:
	CDlgSoftHardAbility(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSoftHardAbility)
	enum { IDD = IDD_DLG_SOFTHARD_ABILITY };
	CListBox	m_lstSnmpVersion;
	CListBox	m_lstSadpVersion;
	CListBox	m_lstDdnsType;
	BOOL	m_bDDNS;
	BOOL	m_bEptz;
	BOOL	m_bIpv6;
	BOOL	m_bNas;
	BOOL	m_bNtp;
	BOOL	m_bRtsp;
	BOOL	m_bUpnp;
	BOOL	m_bVca;
	BOOL	m_bSupportIRS;
	BOOL	m_bSupportPOE;
	BOOL	m_bSupportReset;
	BOOL	m_bSuportSD;
	BOOL	m_bSupportVideo;
	BOOL	m_bSupportWifi;
	int		m_iAlarmOutNum;
	int		m_iAlarmInNum;
	int		m_iAudioInNum;
	int		m_iAudioOutNum;
	UINT	m_dwFlashSize;
	int		m_iNetworkPortNum;
	UINT	m_dwRamSize;
	int		m_iRs232Num;
	int		m_iRs485Num;
	int		m_iSDNum;
	int		m_iUsbNum;
	CString	m_csUsbVersion;
	int		m_iVideoInNum;
	int		m_iVideoOutNum;
	BYTE	m_byNasNum;
	BYTE	m_byShowStringNum;
	BOOL	m_bATM;
	BOOL	m_bAudioEncodeTypeReboot;
	BOOL	m_bBackup;
	BOOL	m_bBitrateLimit;
	BOOL	m_bDHCPReboot;
	BOOL	m_bEmailSPT;
	BOOL	m_bFileLockSPT;
	BOOL	m_bHDParamReboot;
	BOOL	m_bHideAlarmSPT;
	BOOL	m_bHttpOverRtspSPT;
	BOOL	m_bHttpPortReboot;
	BOOL	m_bImportCFGFileReboot;
	BOOL	m_bISCSISpt;
	BOOL	m_bMotionDetectAlarmSPT;
	BOOL	m_bMulStreamSPT;
	BOOL	m_bNetPortReboot;
	BOOL	m_bPtzSPT;
	BOOL	m_bRecordTimeReboot;
	BOOL	m_bRS232Reboot;
	BOOL	m_bRtpoverRtsp;
	BOOL	m_bShutDown;
	BOOL	m_bSmartSearch;
	BOOL	m_bSNMP;
	BOOL	m_bStandardTypeReboot;
	BOOL	m_bSubStreamSPT;
	BOOL	m_bVideoEncodeTypeReboot;
	BOOL	m_bVILostAlarmSPT;
	CString	m_csDDNSType;
	int		m_iMaxChanLinkNum;
	int		m_iMaxLoginNum;
	int		m_iMaxPlayBackNum;
	int		m_iMaxPreviewNum;
	CString	m_csSadpVersion;
	CString	m_csSNMPVersion;
	BYTE	m_byZeroChanNum;
	BOOL	m_bPPPoeReboot;
	BOOL	m_bMulNetworkCard;
	BOOL	m_bSupportRaid;
	BYTE	m_byAnalogChanNum;
	BYTE	m_byAudioTalkNum;
	BYTE	m_byAuxoutNum;
	BYTE	m_byHardDiskNum;
	DWORD	m_dwHardwareVersion;
	BYTE	m_byIPChanNum;
	BYTE	m_byNetworkCardNum;
	BYTE	m_byVGANum;
	BOOL	m_bShelterSPT;
	int		m_iRaidType;
	BYTE	m_byHDMINum;
	BYTE	m_byCVBSNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSoftHardAbility)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSoftHardAbility)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lServerID;
    int     m_iDevIndex;
    char    *m_pRecvBuf;
    char    *m_pSendBuf;

    SOFTHARDWARE_ABILITY_PARAM m_struAbilityParam;
public:
    BOOL    GetSoftHardAbility();
    BOOL    ParseSoftHardAbilityXml(char *pBuf, DWORD dwBufSize);
    BOOL    WirteBufToFile(char *pBuf, DWORD dwBufSize);
    BOOL    SetSoftHardAbilityToWnd(SOFTHARDWARE_ABILITY_PARAM struSoftHardAbility);
    BOOL    SetSoftAbilityToWnd(SOFTWARE_ABILITY_PARAM struSoftwareAbility);
	BOOL	SetNeedRebootToWnd(NEEDREBOOT_PARAM struNeedReboot);
    BOOL    SetHardAbilityToWnd(HARDWARE_ABILITY_PARAM struHardwareAbility);
	void	ParseStrIndex(CString strIndex, byte* array, int iArrayLength);
	void	SetRangeToWnd(CListBox* pList, BYTE* pArray, int iArrayLength);
//SOFTHARDWARE_ABILITY_PARAM g_struSofgHardAbilityParam;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSOFTHARDABILITY_H__6FB2DEEB_5242_4460_ABCE_1573D2CA04F9__INCLUDED_)
