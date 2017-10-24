#if !defined(AFX_DLGAUDIOOUTVOLUMECFG_H__46DF1BEE_2837_4A64_BA38_7A47E7070DBC__INCLUDED_)
#define AFX_DLGAUDIOOUTVOLUMECFG_H__46DF1BEE_2837_4A64_BA38_7A47E7070DBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAudioOutVolumeCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAudioOutVolumeCfg dialog

class CDlgAudioOutVolumeCfg : public CDialog
{
// Construction
public:
	CDlgAudioOutVolumeCfg(CWnd* pParent = NULL);   // standard constructor

	LONG    m_lUserID;
    LONG    m_lChannel;
	DWORD   m_dwDevIndex;

// Dialog Data
	//{{AFX_DATA(CDlgAudioOutVolumeCfg)
	enum { IDD = IDD_DLG_AUDIOOUT_VOLUME_CFG };
	CSliderCtrl	m_sliderVolume;
	CComboBox	m_cmbAudioOutChan;
	CString	m_csVolume;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAudioOutVolumeCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAudioOutVolumeCfg)
	afx_msg void OnCustomdrawSliderVolume(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAUDIOOUTVOLUMECFG_H__46DF1BEE_2837_4A64_BA38_7A47E7070DBC__INCLUDED_)
