#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CDlgAddDevice dialog

class CDlgAddDevice : public CDialog
{
	DECLARE_DYNAMIC(CDlgAddDevice)

public:
	CDlgAddDevice(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgAddDevice();


// Dialog Data

public:

// 	BOOL OnInitDialog();
	//{{AFX_DATA(CDlgAddDevice)
	enum { IDD = IDD_DLG_ADD_DEVICE };
	CString m_csNodeName;	
	CString m_csUserName;
	CString m_csPwd;
	int m_iDeviceIndex;
	BOOL m_bChkGetIPByIPServer;
	CString m_csDeviceName;
	CString m_csDevSN;	
	int m_iIPServerPort;
	int		m_nLoginPort;
	CString	m_csDevAddr;
	CString	m_csDDNSAddr;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CDlgAddDevice)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CDlgAddDevice)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedAddDeviceOk();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedBtnGetDevIp();
    afx_msg void OnBnClickedChkGetIpByIPServer();	
	afx_msg void OnActivateDevice();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()


public:
    CComboBox m_cmbProxyType;
};
