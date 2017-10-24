// DlgSuperBrainFunctionTest.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgSuperBrainFunctionTest.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"


// CDlgSuperBrainFunctionTest 对话框

IMPLEMENT_DYNAMIC(CDlgSuperBrainFunctionTest, CDialogEx)

#define WM_MSG_UPDATEDATA_INTERFACE   1003

CDlgSuperBrainFunctionTest::CDlgSuperBrainFunctionTest(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSuperBrainFunctionTest::IDD, pParent)
    , m_strFilePath(_T(""))
    , m_strPicturePath(_T(""))
    , m_strModeData(_T(""))
    , m_lUserID(-1)
    , m_iDeviceIndex(-1)
    , m_ctDateStart(COleDateTime::GetCurrentTime())
    , m_ctTimeStart(COleDateTime::GetCurrentTime())
    , m_ctDateEnd(COleDateTime::GetCurrentTime())
    , m_ctTimeEnd(COleDateTime::GetCurrentTime())
    , m_strSearchID(_T(""))
    , m_iMaxCountRet(0)
    , m_iCountStartRet(0)
    , m_strSearchResult(_T(""))
    , m_strSearchStatus(_T(""))
    , m_iCountResult(0)
    , m_bRegerateID(FALSE)
    , m_iStatusMaxCountRet(0)
    , m_bSearch(FALSE)
    , m_hSearchThread(NULL)
    , m_lChannel(-1)
    , m_strSimilarity(_T(""))
{
    m_iRowCount = 0;
    m_bSelectItem = FALSE;
    m_iSubItem = -1;
    m_iLastItem = -1;
}

CDlgSuperBrainFunctionTest::~CDlgSuperBrainFunctionTest()
{
}

void CDlgSuperBrainFunctionTest::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_PICTURE_PATH, m_strPicturePath);
    DDX_Text(pDX, IDC_EDIT_MODE_DATA, m_strModeData);
    DDX_Control(pDX, IDC_COMBO_IMPORT_TYPE, m_comboImportType);
    DDX_Text(pDX, IDC_EDT_SEARCH_ID, m_strSearchID);
    DDX_Text(pDX, IDC_EDT_MAX_COUNT_RET, m_iMaxCountRet);
    DDX_Text(pDX, IDC_EDT_NUM_BEGIN_RET, m_iCountStartRet);
    DDX_Text(pDX, IDC_EDIT_SEARCH_RET, m_strSearchResult);
    DDX_Text(pDX, IDC_EDIT_SEARCH_STATUS, m_strSearchStatus);
    DDX_Text(pDX, IDC_STA_COUNT_RET, m_iCountResult);
    DDX_Check(pDX, IDC_CHECK_REGERATE_ID, m_bRegerateID);
    DDX_Text(pDX, IDC_STA_MAX_COUNT_RET, m_iStatusMaxCountRet);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DATE_START, m_ctDateStart);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TIME_START, m_ctTimeStart);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DATE_END, m_ctDateEnd);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TIME_END, m_ctTimeEnd);
    DDX_Control(pDX, IDC_COMBO_SEARCH_TYPE, m_comboSearchType);
    DDX_Control(pDX, IDC_LIST_MODE_DATA, m_listModeData);
    DDX_Text(pDX, IDC_EDIT_SIMILARITY, m_strSimilarity);
}


BEGIN_MESSAGE_MAP(CDlgSuperBrainFunctionTest, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_BROWSE, &CDlgSuperBrainFunctionTest::OnBnClickedButtonBrowse)
    ON_BN_CLICKED(IDC_BUTTON_IMPORT, &CDlgSuperBrainFunctionTest::OnBnClickedButtonImport)
    ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CDlgSuperBrainFunctionTest::OnBnClickedButtonSearch)
    ON_BN_CLICKED(IDC_BUTTON_ADD_LIST, &CDlgSuperBrainFunctionTest::OnBnClickedButtonAddList)
    ON_BN_CLICKED(IDC_BUTTON_DELETE_LIST, &CDlgSuperBrainFunctionTest::OnBnClickedButtonDeleteList)
    ON_NOTIFY(NM_CLICK, IDC_LIST_MODE_DATA, &CDlgSuperBrainFunctionTest::OnNMClickListModeData)
    ON_MESSAGE(WM_MSG_UPDATEDATA_INTERFACE, OnMsgUpdateData)
END_MESSAGE_MAP()


// CDlgSuperBrainFunctionTest 消息处理程序

BOOL CDlgSuperBrainFunctionTest::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化

    char szLan[128] = { 0 };
    m_listModeData.SetExtendedStyle(m_listModeData.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES);

    g_StringLanType(szLan, "序号", "Index");
    m_listModeData.InsertColumn(0, szLan, LVCFMT_LEFT, 60, -1);

    g_StringLanType(szLan, "建模数据", "Mode data");
    m_listModeData.InsertColumn(1, szLan, LVCFMT_LEFT, 120, -1);

    char szGUID[MAX_XML_ELEM_LEN] = { 0 };
    if (!GenerateGUID(szGUID, MAX_XML_ELEM_LEN))
    {
        MessageBox("生成UUID失败!");
        return TRUE;
    }

    m_strSearchID = szGUID;

    m_comboImportType.SetCurSel(0);
    m_comboSearchType.SetCurSel(0);

    m_ctTimeStart.SetTime(0, 0, 0);
    m_ctTimeEnd.SetTime(23, 59, 59);

    m_iMaxCountRet = 50;
    m_bRegerateID = TRUE;
    m_strSimilarity = "2";

    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}

LRESULT CDlgSuperBrainFunctionTest::OnMsgUpdateData(WPARAM wParam, LPARAM lParam)
{
    DWORD dwTrue = (DWORD)wParam;
    UpdateData(dwTrue);
    return 0;
}

void CDlgSuperBrainFunctionTest::OnBnClickedButtonBrowse()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    char szLan[1024] = { 0 };
    static char szFilter[] = "All File(*.*)|*.*||";
    CFileDialog dlg(TRUE, "*.*", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
    if (dlg.DoModal() == IDOK)
    {
        m_strFilePath = dlg.GetPathName();
        SetDlgItemText(IDC_EDIT_PICTURE_PATH, m_strFilePath);
    }
}


void CDlgSuperBrainFunctionTest::OnBnClickedButtonImport()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    BYTE *pPicInfo = NULL;
    char szLan[128] = { 0 };

    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    char szUrl[256] = { 0 };
    if (m_comboImportType.GetCurSel() == 0)
    {
        sprintf(szUrl, "POST /ISAPI/Intelligent/analysisImage/human\r\n");
    } 
    else if(m_comboImportType.GetCurSel() == 1)
    {
        sprintf(szUrl, "POST /ISAPI/Intelligent/analysisImage/face\r\n");
    }

    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);

    CFile cPicFile;
    if (!cPicFile.Open(m_strFilePath, CFile::modeRead))
    {
        g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
        AfxMessageBox(szLan);
    }
    else
    {
        struInput.dwInBufferSize = (DWORD)cPicFile.GetLength();
        if (struInput.dwInBufferSize == 0)
        {
            g_StringLanType(szLan, "Pic文件为空", "Pic file is empty");
            AfxMessageBox(szLan);
        }

        pPicInfo = new BYTE[struInput.dwInBufferSize];
        cPicFile.Read(pPicInfo, struInput.dwInBufferSize);
        struInput.lpInBuffer = pPicInfo;

        cPicFile.Close();
    }

    DWORD dwOutputLen = 1024 * 1024;
    char *pOutBuf = new char[dwOutputLen];
    memset(pOutBuf, 0, dwOutputLen);
    struOuput.lpOutBuffer = pOutBuf;
    struOuput.dwOutBufferSize = dwOutputLen;

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szUrl);
        delete[]pOutBuf;
        pOutBuf = NULL;
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);
    }

    BOOL bRet = FALSE;
    CXmlBase xmlBase;
    xmlBase.Parse(pOutBuf);
    if (m_comboImportType.GetCurSel() == 0)
    {
        if (xmlBase.FindElem("HumanRecognitionTargetsList") && xmlBase.IntoElem())
        {
            if (xmlBase.FindElem("HumanRecognitionTarget") && xmlBase.IntoElem())
            {
                if (xmlBase.FindElem("modeData"))
                {
                    m_strModeData = xmlBase.GetData().c_str();
                }
                xmlBase.OutOfElem();
            }
            xmlBase.OutOfElem();
        }
    }
    else if (m_comboImportType.GetCurSel() == 1)
    {
        if (xmlBase.FindElem("FaceContrastTargetsList") && xmlBase.IntoElem())
        {
            if (xmlBase.FindElem("FaceContrastTarget") && xmlBase.IntoElem())
            {
                if (xmlBase.FindElem("modeData"))
                {
                    m_strModeData = xmlBase.GetData().c_str();
                }
                xmlBase.OutOfElem();
            }
            xmlBase.OutOfElem();
        }
    }

    if (pOutBuf != NULL)
    {
        delete[]pOutBuf;
        pOutBuf = NULL;
    }

    if (pPicInfo != NULL)
    {
        delete[]pPicInfo;
        pPicInfo = NULL;
    }

    UpdateData(FALSE);
}

BOOL CDlgSuperBrainFunctionTest::CreateSearchHumanCondition(char* pBuf, DWORD dwBufLen, int &dwRet)
{
    CString strParam = _T("");
    CXmlBase xmlBase;
    xmlBase.CreateRoot("HumanRecognitionSearchDescription");
    xmlBase.SetAttribute("version", "2.0");

    xmlBase.AddNode("searchID", m_strSearchID.GetBuffer(0));
    xmlBase.OutOfElem();

    strParam.Format("%d", m_iCountStartRet);
    xmlBase.AddNode("searchResultPosition", strParam.GetBuffer(0));
    xmlBase.OutOfElem();
    m_iCountStartRet += m_iMaxCountRet;//循环查找

    strParam.Format("%d", m_iMaxCountRet);
    xmlBase.AddNode("maxResults", strParam.GetBuffer(0));
    xmlBase.OutOfElem();

    if (xmlBase.AddNode("timeSpanList"))
    {
        if (xmlBase.AddNode("timeSpan"))
        {
            strParam.Format("%04d-%02d-%02dT%02d:%02d:%02d", m_ctDateStart.GetYear(), m_ctDateStart.GetMonth(),
                m_ctDateStart.GetDay(), m_ctTimeStart.GetHour(), m_ctTimeStart.GetMinute(), m_ctTimeStart.GetSecond());

            xmlBase.AddNode("startTime", strParam.GetBuffer(0));
            xmlBase.OutOfElem();

            strParam.Format("%04d-%02d-%02dT%02d:%02d:%02d", m_ctDateEnd.GetYear(), m_ctDateEnd.GetMonth(),
                m_ctDateEnd.GetDay(), m_ctTimeEnd.GetHour(), m_ctTimeEnd.GetMinute(), m_ctTimeEnd.GetSecond());

            xmlBase.AddNode("endTime", strParam.GetBuffer(0));
            xmlBase.OutOfElem();

            xmlBase.OutOfElem();
        }
        xmlBase.OutOfElem();
    }

    xmlBase.AddNode("positive", "false");
    xmlBase.OutOfElem();

    int iRowCount = m_listModeData.GetItemCount();
    if (iRowCount > 0)
    {
        xmlBase.AddNode("HumanModeList");

        for (int i = 0; i < iRowCount; i++)
        {
            if (xmlBase.AddNode("HumanMode"))
            {
                if (xmlBase.AddNode("ModeInfo"))
                {
                    xmlBase.AddNode("similarity", m_strSimilarity.GetBuffer(0));
                    xmlBase.OutOfElem();

                    xmlBase.AddNode("modeData", m_listModeData.GetItemText(i, 1).GetBuffer(0));
                    xmlBase.OutOfElem();

                    xmlBase.OutOfElem();
                }
            }
        }

        xmlBase.OutOfElem();
    }

    return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}

BOOL CDlgSuperBrainFunctionTest::CreateSearchFaceCondition(char* pBuf, DWORD dwBufLen, int &dwRet)
{
    CString strParam = _T("");
    CXmlBase xmlBase;
    xmlBase.CreateRoot("FCSearchDescription");
    xmlBase.SetAttribute("version", "2.0");

    xmlBase.AddNode("searchID", m_strSearchID.GetBuffer(0));
    xmlBase.OutOfElem();

    strParam.Format("%d", m_iCountStartRet);
    xmlBase.AddNode("searchResultPosition", strParam.GetBuffer(0));
    xmlBase.OutOfElem();
    m_iCountStartRet += m_iMaxCountRet;//循环查找

    strParam.Format("%d", m_iMaxCountRet);
    xmlBase.AddNode("maxResults", strParam.GetBuffer(0));
    xmlBase.OutOfElem();

    strParam.Format("%04d-%02d-%02dT%02d:%02d:%02d", m_ctDateStart.GetYear(), m_ctDateStart.GetMonth(), 
        m_ctDateStart.GetDay(), m_ctTimeStart.GetHour(), m_ctTimeStart.GetMinute(), m_ctTimeStart.GetSecond());

    xmlBase.AddNode("snapStartTime", strParam.GetBuffer(0));
    xmlBase.OutOfElem();

    strParam.Format("%04d-%02d-%02dT%02d:%02d:%02d", m_ctDateEnd.GetYear(), m_ctDateEnd.GetMonth(),
        m_ctDateEnd.GetDay(), m_ctTimeEnd.GetHour(), m_ctTimeEnd.GetMinute(), m_ctTimeEnd.GetSecond());

    xmlBase.AddNode("snapEndTime", strParam.GetBuffer(0));
    xmlBase.OutOfElem();

    int iRowCount = m_listModeData.GetItemCount();
    if (iRowCount > 0)
    {
        if (xmlBase.AddNode("FaceModeList"))
        {
            for (int i = 0; i < iRowCount; i++)
            {
                if (xmlBase.AddNode("FaceMode"))
                {
                    if (xmlBase.AddNode("ModeInfo"))
                    {
                        xmlBase.AddNode("similarity", m_strSimilarity.GetBuffer(0));
                        xmlBase.OutOfElem();

                        xmlBase.AddNode("modeData", m_listModeData.GetItemText(i, 1).GetBuffer(0));
                        xmlBase.OutOfElem();

                        xmlBase.OutOfElem();
                    }
                    xmlBase.OutOfElem();
                }
            }
            xmlBase.OutOfElem();
        }

    }

    return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}

DWORD  GetSearchDataThread(LPVOID pParam)
{
    CDlgSuperBrainFunctionTest *pThis = (CDlgSuperBrainFunctionTest*)pParam;

    CString strTemp = _T("");
    long t1 = GetTickCount();
    while (pThis->m_bSearch)
    {
        pThis->SearchData();
    }
    long t2 = GetTickCount();
    strTemp.Format("%ld ms", t2 - t1);
    pThis->GetDlgItem(IDC_EDIT_SEARCH_TIME)->SetWindowText(strTemp);
    pThis->GetDlgItem(IDC_EDT_NUM_BEGIN_RET)->SetWindowText("0");
    return FALSE;
}

void CDlgSuperBrainFunctionTest::SearchData()
{
    DWORD dwBufLen = 10 * 1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);
    int dwXmlLen = 0;

    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    char szUrl[256] = { 0 };

    if (m_comboSearchType.GetCurSel() == 0)
    {
        if (!CreateSearchHumanCondition(pBuf, dwBufLen, dwXmlLen))
        {
            delete[]pBuf;
            pBuf = NULL;
            return;
        }
        sprintf(szUrl, "POST /ISAPI/Intelligent/humanRecognition/Search/channels/%d\r\n", m_lChannel);
    }
    else if (m_comboSearchType.GetCurSel() == 1)
    {
        if (!CreateSearchFaceCondition(pBuf, dwBufLen, dwXmlLen))
        {
            delete[]pBuf;
            pBuf = NULL;
            return;
        }
        sprintf(szUrl, "POST /ISAPI/Intelligent/FDLib/FCSearch/channels/%d\r\n", m_lChannel);
    }

    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);
    struInput.lpInBuffer = pBuf;
    struInput.dwInBufferSize = dwXmlLen;
    DWORD dwOutputLen = 1024 * 1024;
    char *pOutBuf = new char[dwOutputLen];
    memset(pOutBuf, 0, dwOutputLen);
    struOuput.lpOutBuffer = pOutBuf;
    struOuput.dwOutBufferSize = dwOutputLen;

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szUrl);
        delete[]pOutBuf;
        pOutBuf = NULL;
        m_strSearchResult = _T("");
        m_strSearchStatus = _T("");
        m_iCountResult = 0;
        m_iStatusMaxCountRet = 50;
        m_bSearch = FALSE;
        GetDlgItem(IDC_BUTTON_SEARCH)->SetWindowText("查找");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);
    }

    BOOL bRet = FALSE;
    CXmlBase xmlBase;
    xmlBase.Parse(pOutBuf);

    if (m_comboSearchType.GetCurSel() == 0)
    {
        if (xmlBase.FindElem("HumanRecognitionSearchResult") && xmlBase.IntoElem())
        {
            if (xmlBase.FindElem("searchID"))
            {
                m_strSearchID = xmlBase.GetData().c_str();
            }
            if (xmlBase.FindElem("responseStatus"))
            {
                m_strSearchResult = xmlBase.GetData().c_str();
            }
            if (xmlBase.FindElem("responseStatusStrg"))
            {
                m_strSearchStatus = xmlBase.GetData().c_str();
            }
            if (xmlBase.FindElem("numOfMatches"))
            {
                m_iCountResult = atoi(xmlBase.GetData().c_str());
            }
            if (xmlBase.FindElem("totalMatches"))
            {
                m_iStatusMaxCountRet = atoi(xmlBase.GetData().c_str());
            }
            xmlBase.OutOfElem();
        }
    }
    else if (m_comboSearchType.GetCurSel() == 1)
    {
        if (xmlBase.FindElem("FCSearchResult") && xmlBase.IntoElem())
        {
            if (xmlBase.FindElem("searchID"))
            {
                m_strSearchID = xmlBase.GetData().c_str();
            }
            if (xmlBase.FindElem("responseStatus"))
            {
                m_strSearchResult = xmlBase.GetData().c_str();
            }
            if (xmlBase.FindElem("responseStatusStrg"))
            {
                m_strSearchStatus = xmlBase.GetData().c_str();
            }
            if (xmlBase.FindElem("numOfMatches"))
            {
                m_iCountResult = atoi(xmlBase.GetData().c_str());
            }
            if (xmlBase.FindElem("totalMatches"))
            {
                m_iStatusMaxCountRet = atoi(xmlBase.GetData().c_str());
            }
            xmlBase.OutOfElem();
        }
    }
    if (m_strSearchResult == "false" || (m_strSearchResult == "true" && m_strSearchStatus != "MORE"))
    {
        m_bSearch = FALSE;
        GetDlgItem(IDC_BUTTON_SEARCH)->SetWindowText("查找");
        PostMessage(WM_MSG_UPDATEDATA_INTERFACE, (WPARAM)FALSE, 0);
    }

    if (pOutBuf != NULL)
    {
        delete[]pOutBuf;
        pOutBuf = NULL;
    }

    if (pBuf != NULL)
    {
        delete[]pBuf;
        pBuf = NULL;
    }
}

void CDlgSuperBrainFunctionTest::OnBnClickedButtonSearch()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    
    char szLan[128] = { 0 };
    CString strTemp = _T("");

    char szGUID[MAX_XML_ELEM_LEN] = { 0 };

    if (m_bRegerateID)
    {
        if (!GenerateGUID(szGUID, MAX_XML_ELEM_LEN))
        {
            MessageBox("生成UUID失败!");
            return;
        }

        m_strSearchID = szGUID;
        UpdateData(FALSE);
    }
    if (!m_bSearch)
    {
        m_bSearch = TRUE;
        GetDlgItem(IDC_BUTTON_SEARCH)->SetWindowText("停止");
    }
    else
    {
        m_bSearch = FALSE;
        GetDlgItem(IDC_BUTTON_SEARCH)->SetWindowText("查找");
        return;
    }


    DWORD dwThreadId = 0;
    m_hSearchThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetSearchDataThread), this, 0, &dwThreadId);
    if (m_hSearchThread == NULL)
    {
        char szLan[256] = { 0 };
        m_bSearch = FALSE;
        GetDlgItem(IDC_BUTTON_SEARCH)->SetWindowText("查找");
        g_StringLanType(szLan, "打开长传文件线程失败!", "open UpLoad thread Fail!");
        AfxMessageBox(szLan);
        return;
    }

    UpdateData(FALSE);
}


void CDlgSuperBrainFunctionTest::OnBnClickedButtonAddList()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    int iRowCount = m_listModeData.GetItemCount();
    CString strTemp = _T("");
    strTemp.Format("%d", iRowCount);
    m_listModeData.InsertItem(iRowCount, strTemp);
    m_listModeData.SetItemText(iRowCount, 1, m_strModeData);
    UpdateData(FALSE);
}


void CDlgSuperBrainFunctionTest::OnBnClickedButtonDeleteList()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    m_iRowCount = m_listModeData.GetItemCount();
    if (m_iLastItem >= 0 && m_iLastItem < m_iRowCount)
    {
        m_listModeData.DeleteItem(m_iLastItem);
    }
    UpdateData(FALSE);
}


void CDlgSuperBrainFunctionTest::OnNMClickListModeData(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    // TODO:  在此添加控件通知处理程序代码
    m_iLastItem = pNMItemActivate->iItem;
    m_iSubItem = pNMItemActivate->iSubItem;
    m_bSelectItem = TRUE;

    *pResult = 0;
}
