#if !defined(AFX_DLGVCABVCALIBRATE_H__9922B467_43A6_4429_80F6_4F75106C9C43__INCLUDED_)
#define AFX_DLGVCABVCALIBRATE_H__9922B467_43A6_4429_80F6_4F75106C9C43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaBVCalibrate.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaBVCalibrate dialog
#include "Picture.h"
class CDlgVcaBVCalibrate : public CDialog
{
// Construction
public:
	CDlgVcaBVCalibrate(CWnd* pParent = NULL);   // standard constructor
	~CDlgVcaBVCalibrate();
// Dialog Data
	//{{AFX_DATA(CDlgVcaBVCalibrate)
	enum { IDD = IDD_DLG_VCA_BV_CALIBRATE };
	CComboBox	m_comGetCalibType;
	CComboBox	m_comCalibType;
	CComboBox	m_comVideoType;
	CComboBox	m_comCailbIDSample;
	CComboBox	m_comCailbID;
	DWORD	m_dwCameraHeight;
	float	m_fPitchAngle;
	float	m_fInclineAngle;
	BOOL	m_bEnable;
	DWORD	m_dwSampleCameraHeight;
	DWORD	m_dwSampleHumanHeight;
	float	m_fX;
	float	m_fY;
	DWORD	m_dwCameraHeightSample;
	float	m_fInclineAngleSample;
	float	m_fPitchAngleSample;
	float	m_fBvCalibration;
	int		m_iID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaBVCalibrate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaBVCalibrate)
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBtnGetDirectCali();
	afx_msg void OnBtnSetDirectCali();
	afx_msg void OnBtnBeginCalib();
	afx_msg void OnBtnSetCalib();
	afx_msg void OnBtnEndCalib();
	afx_msg void OnBtnGetCalib();
	afx_msg void OnSelchangeComboCailbIdSample();
	afx_msg void OnBtnVerifyBvCalibration();
	afx_msg void OnBtnGetOutputVideoType();
	afx_msg void OnBtnSetOutputVideoType();
	afx_msg void OnBtnGetCalibType();
	afx_msg void OnSelchangeComboCalibType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG    m_lServerID;
    int     m_iDevIndex;
    LONG    m_lChannel;
	LONG    m_lPlayHandle;
	CPicture  m_pic;
    CDC*     m_pDCRect;
	CRect    m_rcWndRect;

	int     m_iCaliType;//标定类型
	NET_DVR_CALIBRATION_CFG m_struDirectCaliCfg;
	NET_DVR_BV_SAMPLE_CALIBRATION m_struSampleCaliCfg;
	NET_VCA_POINT m_struPoint;  //标定点坐标
	NET_VCA_RECT m_struVerifyRect;
	NET_DVR_BV_SAMPLE_CALIB_CFG m_struGetSampleCaliCfg;
	void SetSampleCailbCfg();
	BOOL StopPlay();
    LONG RealPlay();
	void DrawVerifyCalibration();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCABVCALIBRATE_H__9922B467_43A6_4429_80F6_4F75106C9C43__INCLUDED_)
