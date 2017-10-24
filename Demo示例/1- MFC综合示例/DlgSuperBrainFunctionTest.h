#pragma once
#include "afxwin.h"
#include "ATLComTime.h"
#include "afxcmn.h"
#include "XMLParamsConvert.h"

// CDlgSuperBrainFunctionTest 对话框

class CDlgSuperBrainFunctionTest : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSuperBrainFunctionTest)

public:
	CDlgSuperBrainFunctionTest(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSuperBrainFunctionTest();

// 对话框数据
	enum { IDD = IDD_DLG_SUPER_BRAIN_FUNCTION_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    afx_msg LRESULT OnMsgUpdateData(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonBrowse();

    CString m_strFilePath;
    afx_msg void OnBnClickedButtonImport();
    CString m_strPicturePath;
    CString m_strModeData;
    CComboBox m_comboImportType;
    LONG m_lUserID;
    int m_iDeviceIndex;
    CString m_strSearchID;
    int m_iMaxCountRet;
    int m_iCountStartRet;
    CString m_strSearchResult;
    CString m_strSearchStatus;
    int m_iCountResult;
    BOOL m_bRegerateID;
    int m_iStatusMaxCountRet;
    COleDateTime m_ctDateStart;
    COleDateTime m_ctTimeStart;
    COleDateTime m_ctDateEnd;
    COleDateTime m_ctTimeEnd;
    CComboBox m_comboSearchType;
    CListCtrl m_listModeData;
    BOOL m_bSearch;
    HANDLE	m_hSearchThread;
    int m_iRowCount;
    BOOL m_bSelectItem;
    int m_iSubItem;
    int m_iLastItem;
    LONG  m_lChannel;
    afx_msg void OnBnClickedButtonSearch();
    BOOL CreateSearchHumanCondition(char* pBuf, DWORD dwBufLen, int &dwRet);
    BOOL CreateSearchFaceCondition(char* pBuf, DWORD dwBufLen, int &dwRet);
    void SearchData();
    afx_msg void OnBnClickedButtonAddList();
    afx_msg void OnBnClickedButtonDeleteList();
    virtual BOOL OnInitDialog();
    afx_msg void OnNMClickListModeData(NMHDR *pNMHDR, LRESULT *pResult);
    CString m_strSimilarity;
};
