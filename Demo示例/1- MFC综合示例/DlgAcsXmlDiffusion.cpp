// DlgAcsXmlDiffusion.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgAcsXmlDiffusion.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"


// CDlgAcsXmlDiffusion 对话框

IMPLEMENT_DYNAMIC(CDlgAcsXmlDiffusion, CDialog)

CDlgAcsXmlDiffusion::CDlgAcsXmlDiffusion(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAcsXmlDiffusion::IDD, pParent)
{
    m_csCommandStr = "/ISAPI/AccessControl/AttendanceEffectiveID";
    m_csInputParam = _T("");
    m_csOutputParam = _T("");
}

CDlgAcsXmlDiffusion::~CDlgAcsXmlDiffusion()
{
}

void CDlgAcsXmlDiffusion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_OPERATE_TYPE, m_cmbOperateType);
    DDX_Control(pDX, IDC_COMBO_COMMAND, m_cmbCommand);
    DDX_Text(pDX, IDC_EDIT_COMMAND, m_csCommandStr);
    DDX_Text(pDX, IDC_EDIT_PARAM_INPUT, m_csInputParam);
    DDX_Text(pDX, IDC_EDIT_PARAM_OUTPUT, m_csOutputParam);
}

BOOL CDlgAcsXmlDiffusion::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_cmbOperateType.SetCurSel(0);
    m_cmbCommand.SetCurSel(0);

    return TRUE;
}

BEGIN_MESSAGE_MAP(CDlgAcsXmlDiffusion, CDialog)
    ON_BN_CLICKED(IDC_BTN_GET, &CDlgAcsXmlDiffusion::OnBnClickedBtnGet)
    ON_BN_CLICKED(IDC_BTN_EXIT, &CDlgAcsXmlDiffusion::OnBnClickedBtnExit)
    ON_CBN_SELCHANGE(IDC_COMBO_OPERATE_TYPE, &CDlgAcsXmlDiffusion::OnCbnSelchangeComboOperateType)
    ON_CBN_SELCHANGE(IDC_COMBO_COMMAND, &CDlgAcsXmlDiffusion::OnCbnSelchangeComboCommand)
END_MESSAGE_MAP()


// CDlgAcsXmlDiffusion 消息处理程序


void CDlgAcsXmlDiffusion::OnBnClickedBtnGet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    char szUrl[256] = { 0 };
    CString csCommand = _T("");
    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    DWORD dwBufferLen = 1024 * 1024;
    char *pBuffer = new char[dwBufferLen];
    memset(pBuffer, 0, dwBufferLen);
    CXmlBase xmlOutput;

    if (m_cmbOperateType.GetCurSel() == 0)  //GET
    {
        csCommand = "GET " + m_csCommandStr;
        memcpy(szUrl, csCommand.GetBuffer(), csCommand.GetLength());

        struInput.lpRequestUrl = szUrl;
        struInput.dwRequestUrlLen = strlen(szUrl);
        struOuput.lpOutBuffer = pBuffer;
        struOuput.dwOutBufferSize = dwBufferLen;

        if (!NET_DVR_STDXMLConfig(m_lServerID, &struInput, &struOuput))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, szUrl);
            if (pBuffer != NULL)
            {
                delete[]pBuffer;
                pBuffer = NULL;
            }
            return;
        }
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, szUrl);

        xmlOutput.Parse((char *)struOuput.lpOutBuffer);
    }
    else   //PUT
    {
        csCommand = "PUT " + m_csCommandStr;
        memcpy(szUrl, csCommand.GetBuffer(), csCommand.GetLength());

        struInput.lpRequestUrl = szUrl;
        struInput.dwRequestUrlLen = strlen(szUrl);

        DWORD dwInBufferLen = 1024 * 1024;
        char *pInBuffer = new char[dwInBufferLen];
        memset(pInBuffer, 0, dwInBufferLen);
        memcpy(pInBuffer, m_csInputParam.GetBuffer(), m_csInputParam.GetLength());

        struInput.lpInBuffer = pInBuffer;
        struInput.dwInBufferSize = m_csInputParam.GetLength();
        int iLength = 0;
        for (int i = 0; i < struInput.dwInBufferSize; i++)
        {
            //此处是为了避免传递空格和换行符
            if (*((char*)struInput.lpInBuffer + i) != 10 && *((char*)struInput.lpInBuffer + i) != 32)
            {
                *((char*)struInput.lpInBuffer + iLength) = *((char*)struInput.lpInBuffer + i);
                iLength += 1;
            }
        }
        struInput.dwInBufferSize = iLength;
        struOuput.lpStatusBuffer = pBuffer;
        struOuput.dwStatusSize = dwBufferLen;

        if (!NET_DVR_STDXMLConfig(m_lServerID, &struInput, &struOuput))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, szUrl);
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, szUrl);
        }

        xmlOutput.Parse((char *)struOuput.lpStatusBuffer);

        if (pInBuffer != NULL)
        {
            delete[]pInBuffer;
            pInBuffer = NULL;
        }
    }

    xmlOutput.SetRoot();
    m_csOutputParam = xmlOutput.GetChildren().c_str();
    m_csOutputParam.Replace("\n", "\r\n");

    if (pBuffer != NULL)
    {
        delete[]pBuffer;
        pBuffer = NULL;
    }

    UpdateData(FALSE);
}


void CDlgAcsXmlDiffusion::OnBnClickedBtnExit()
{
    // TODO:  在此添加控件通知处理程序代码
    CDialog::OnOK();
}


void CDlgAcsXmlDiffusion::OnCbnSelchangeComboOperateType()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    switch (m_cmbOperateType.GetCurSel())
    {
    case 0: //GET
        m_csInputParam = _T("");
        break;
    case 1: //PUT
        GetCommandStrAndInputParam();
        break;
    default:
        break;
    }

    UpdateData(FALSE);
}


void CDlgAcsXmlDiffusion::OnCbnSelchangeComboCommand()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    GetCommandStrAndInputParam();

    UpdateData(FALSE);
}

void CDlgAcsXmlDiffusion::GetCommandStrAndInputParam()
{
    CXmlBase xmlInput;
    switch (m_cmbCommand.GetCurSel())
    {
    case 0: //考勤有效ID获取
        m_csCommandStr = "/ISAPI/AccessControl/AttendanceEffectiveID";
        /*xmlInput.Parse("<DepartmentParam>\
                            <departmentName>department1</departmentName>\
                       </DepartmentParam>");*/
        break;
    case 1: //设备工作模式配置
        m_csCommandStr = "/ISAPI/VideoIntercom/workMode";
        xmlInput.Parse("<WorkMode>\
                          <deviceWorkMode>ipcMode</deviceWorkMode>\
                        </WorkMode>");
        break;
    case 2: //梯控继电器配置
        m_csCommandStr = "/ISAPI/AccessControl/LadderControlRelay/FloorNo/1";
        xmlInput.Parse("<LadderControlRelay>\
                            <CallLadder>\
                                <distractControlNo>3</distractControlNo>\
                                <relayNo>1</relayNo>\
                            </CallLadder>\
                            <KeyControl>\
                                <distractControlNo>3</distractControlNo>\
                                <relayNo>1</relayNo>\
                            </KeyControl>\
                            <AutoKey>\
                                <distractControlNo>3</distractControlNo>\
                                <relayNo>1</relayNo>\
                            </AutoKey>\
                       </LadderControlRelay>");
        break;
    case 3: //智能身份识别终端参数配置
        m_csCommandStr = "/ISAPI/AccessControl/IdentityTerminal";
        xmlInput.Parse("<IdentityTerminal>\
                       <terminalMode>registerMode</terminalMode>\
                       <videoStorageTime>8</videoStorageTime>\
                       <twoDimensionCode>enable</twoDimensionCod>\
                       <blackListCheck>enable</blackListCheck>\
                       <faceAlgorithm>HIK-Z</faceAlgorithm>\
                       </IdentityTerminal>");
        break;
    case 4: //韦根规则配置
        m_csCommandStr = "/ISAPI/AccessControl/WiegandRuleCfg";
        xmlInput.Parse("<WiegandRuleCfg>\
                            <name>name1</name>\
                            <CustomerCardIn>\
                                <totalLength>10</totalLength>\
                                <checkMethod>parityCheck</checkMethod>\
                                <ParityCheck>\
                                    <oddBeginBit>1</oddBeginBit>\
                                    <oddLength>10</oddLength>\
                                    <evenBeginBit>1</evenBeginBit>\
                                    <evenLength>10</evenLength>\
                                </ParityCheck>\
                                <XorCheck>\
                                    <xorBeginBit>1</xorBeginBit>\
                                    <xorPerLength>10</xorPerLength>\
                                    <xorTotalLength>20</xorTotalLength>\
                                </XorCheck>\
                                <cardIdBeginBit>1</cardIdBeginBit>\
                                <cardIdLength>10</cardIdLength>\
                                <siteCodeBeginBit>1</siteCodeBeginBit>\
                                <siteCodeLength>10</siteCodeLength>\
                                <oemBeginBit>2</oemBeginBit>\
                                <oemLength>3</oemLength>\
                                <manufacturerCodeBeginBit>3</manufacturerCodeBeginBit>\
                                <manufacturerCodeLength>4</manufacturerCodeLength>\
                            </CustomerCardIn>\
                            <CustomerCardOut>\
                                <CardContentList>\
                                    <Action><No>1</No><type>cardId</type><length>10</length></Action>\
                                    <Action><No>2</No><type>cardId</type><length>10</length></Action>\
                                    <Action><No>3</No><type>cardId</type><length>10</length></Action>\
                                    <Action><No>4</No><type>cardId</type><length>10</length></Action>\
                                </CardContentList>\
                            </CustomerCardOut>\
                        </WiegandRuleCfg>");
        break;
    case 5: //M1卡加密验证功能配置
        m_csCommandStr = "/ISAPI/AccessControl/M1CardEncryptCfg";
        xmlInput.Parse("<M1CardEncryptCfg>\
                            <enable>true</enable>\
                            <sectionID>1</sectionID>\
                       </M1CardEncryptCfg>");
        break;
    case 6: //布防信息获取
        m_csCommandStr = "/ISAPI/AccessControl/DeployInfo";
        break;
    case 7: //跨主机反潜回服务器配置
        m_csCommandStr = "/ISAPI/AccessControl/SubmarineBack";
        xmlInput.Parse("<SubmarineBack>\
                            <enabled>true</enabled>\
                        </SubmarineBack>");
        break;
    case 8: //加入跨主机反潜回主机配置
        m_csCommandStr = "/ISAPI/AccessControl/SubmarineBackHostInfo/ConfigureNo/1";
        xmlInput.Parse("<SubmarineBackHostInfo>\
                            <HostInfoList>\
                                <Action><deviceNo>1</deviceNo><serial>000000000</serial></Action>\
                                <Action><deviceNo>2</deviceNo><serial>000000000</serial></Action>\
                                <Action><deviceNo>3</deviceNo><serial>000000000</serial></Action>\
                                <Action><deviceNo>4</deviceNo><serial>000000000</serial></Action>\
                                <Action><deviceNo>5</deviceNo><serial>000000000</serial></Action>\
                                <Action><deviceNo>6</deviceNo><serial>000000000</serial></Action>\
                                <Action><deviceNo>7</deviceNo><serial>000000000</serial></Action>\
                                <Action><deviceNo>8</deviceNo><serial>000000000</serial></Action>\
                                <Action><deviceNo>9</deviceNo><serial>000000000</serial></Action>\
                                <Action><deviceNo>10</deviceNo><serial>000000000</serial></Action>\
                                <Action><deviceNo>11</deviceNo><serial>000000000</serial></Action>\
                                <Action><deviceNo>12</deviceNo><serial>000000000</serial></Action>\
                                <Action><deviceNo>13</deviceNo><serial>000000000</serial></Action>\
                                <Action><deviceNo>14</deviceNo><serial>000000000</serial></Action>\
                                <Action><deviceNo>15</deviceNo><serial>000000000</serial></Action>\
                                <Action><deviceNo>16</deviceNo><serial>000000000</serial></Action>\
                            </HostInfoList>\
                       </SubmarineBackHostInfo>");
        break;
    case 9: //起始读卡器配置
        m_csCommandStr = "/ISAPI/AccessControl/StartReaderInfo";
        xmlInput.Parse("<StartReaderInfo>\
                            <hostNo>1</hostNo>\
                            <readerNo>1</readerNo>\
                        </StartReaderInfo>");
        break;
    case 10: //跨主机反潜回读卡器配置
        m_csCommandStr = "/ISAPI/AccessControl/SubmarineBackReader/ConfigureNo/1";
        xmlInput.Parse("<SubmarineBackReader>\
                            <selfHostNo>1</selfHostNo>\
                            <selfReaderNo>1</selfReaderNo>\
                            <FollowReaderList>\
                                <Action><followHostNo>1</followHostNo><followReaderNo>1</followReaderNo></Action>\
                                <Action><followHostNo>2</followHostNo><followReaderNo>2</followReaderNo></Action>\
                                <Action><followHostNo>3</followHostNo><followReaderNo>3</followReaderNo></Action>\
                                <Action><followHostNo>4</followHostNo><followReaderNo>4</followReaderNo></Action>\
                                <Action><followHostNo>5</followHostNo><followReaderNo>5</followReaderNo></Action>\
                                <Action><followHostNo>6</followHostNo><followReaderNo>6</followReaderNo></Action>\
                                <Action><followHostNo>7</followHostNo><followReaderNo>7</followReaderNo></Action>\
                                <Action><followHostNo>8</followHostNo><followReaderNo>8</followReaderNo></Action>\
                                <Action><followHostNo>9</followHostNo><followReaderNo>1</followReaderNo></Action>\
                                <Action><followHostNo>10</followHostNo><followReaderNo>2</followReaderNo></Action>\
                                <Action><followHostNo>11</followHostNo><followReaderNo>3</followReaderNo></Action>\
                                <Action><followHostNo>12</followHostNo><followReaderNo>4</followReaderNo></Action>\
                                <Action><followHostNo>13</followHostNo><followReaderNo>5</followReaderNo></Action>\
                                <Action><followHostNo>14</followHostNo><followReaderNo>6</followReaderNo></Action>\
                                <Action><followHostNo>15</followHostNo><followReaderNo>7</followReaderNo></Action>\
                                <Action><followHostNo>16</followHostNo><followReaderNo>8</followReaderNo></Action>\
                            </FollowReaderList>\
                       </SubmarineBackReader>");
        break;
    case 11: //服务器跨主机反潜回刷卡记录清除
        m_csCommandStr = "/ISAPI/AccessControl/ClearCardRecord";
        xmlInput.Parse("<ClearCardRecord>\
                            <clearAllCard>false</clearAllCard>\
                            <CardList>\
                                <cardNo>1000</cardNo>\
                                <cardNo>1001</cardNo>\
                                <cardNo>1002</cardNo>\
                                <cardNo>1003</cardNo>\
                                <cardNo>1004</cardNo>\
                                <cardNo>1005</cardNo>\
                                <cardNo>1006</cardNo>\
                                <cardNo>1007</cardNo>\
                                <cardNo>1008</cardNo>\
                                <cardNo>1009</cardNo>\
                                <cardNo>1010</cardNo>\
                                <cardNo>1011</cardNo>\
                                <cardNo>1012</cardNo>\
                                <cardNo>1013</cardNo>\
                                <cardNo>1014</cardNo>\
                                <cardNo>1015</cardNo>\
                                <cardNo>1016</cardNo>\
                                <cardNo>1017</cardNo>\
                                <cardNo>1018</cardNo>\
                                <cardNo>1019</cardNo>\
                                <cardNo>1020</cardNo>\
                                <cardNo>1021</cardNo>\
                                <cardNo>1022</cardNo>\
                                <cardNo>1023</cardNo>\
                                <cardNo>1024</cardNo>\
                                <cardNo>1025</cardNo>\
                                <cardNo>1026</cardNo>\
                                <cardNo>1027</cardNo>\
                                <cardNo>1028</cardNo>\
                                <cardNo>1029</cardNo>\
                                <cardNo>1030</cardNo>\
                                <cardNo>1031</cardNo>\
                            </CardList>\
                        </ClearCardRecord>");
        break;
    case 12: //跨主机反潜回模式配置
        m_csCommandStr = "/ISAPI/AccessControl/SubmarineBackMode";
        xmlInput.Parse("<SubmarineBackMode>\
                            <mode>internetCommunicate</mode>\
                            <rule>inOrOut</rule>\
                            <sectionID>1</sectionID>\
                        </SubmarineBackMode>");
        break;
    case 13: //跨主机反潜回信息清除
        m_csCommandStr = "/ISAPI/AccessControl/ClearSubmarineBack";
        xmlInput.Parse("<ClearSubmarineBack>\
                            <clearHostInfo>true</clearHostInfo>\
                            <clearReaderInfo>true</clearReaderInfo>\
                            <clearSubmarineBack>true</clearSubmarineBack>\
                            <clearSubmarineBackHostInfo>true</clearSubmarineBackHostInfo>\
                            <clearStartReaderInfo>true</clearStartReaderInfo>\
                            <clearSubmarineBackReader>true</clearSubmarineBackReader>\
                            <clearSubmarineBackMode>true</clearSubmarineBackMode>\
                            <clearServerDevice>true</clearServerDevice>\
                            <clearReaderAcrossHost>true</clearReaderAcrossHost>\
                        </ClearSubmarineBack>");
        break;
    case 14: //加入跨主机反潜回配置
        m_csCommandStr = "/ISAPI/AccessControl/ServerDevice";
        xmlInput.Parse("<ServerDevice>\
                            <ipAddr>10.17.132.160</ipAddr>\
                            <port>8000</port>\
                        </ServerDevice>");
        break;
    case 15: //读卡器跨主机反潜回配置
        m_csCommandStr = "/ISAPI/AccessControl/ReaderAcrossHost";
        xmlInput.Parse("<ReaderAcrossHost>\
                            <AcrossHostList>\
                                <AcrossHostAction><readerNo>1</readerNo><submarineBackEnabled>true</submarineBackEnabled></AcrossHostAction>\
                                <AcrossHostAction><readerNo>2</readerNo><submarineBackEnabled>false</submarineBackEnabled></AcrossHostAction>\
                                <AcrossHostAction><readerNo>3</readerNo><submarineBackEnabled>true</submarineBackEnabled></AcrossHostAction>\
                                <AcrossHostAction><readerNo>4</readerNo><submarineBackEnabled>false</submarineBackEnabled></AcrossHostAction>\
                                <AcrossHostAction><readerNo>5</readerNo><submarineBackEnabled>true</submarineBackEnabled></AcrossHostAction>\
                                <AcrossHostAction><readerNo>6</readerNo><submarineBackEnabled>false</submarineBackEnabled></AcrossHostAction>\
                                <AcrossHostAction><readerNo>7</readerNo><submarineBackEnabled>true</submarineBackEnabled></AcrossHostAction>\
                                <AcrossHostAction><readerNo>8</readerNo><submarineBackEnabled>false</submarineBackEnabled></AcrossHostAction>\
                            </AcrossHostList>\
                        </ReaderAcrossHost>");
        break;
    case 16: //设备权限密码状态获取
        m_csCommandStr = "/ISAPI/VideoIntercom/PrivilegePasswordStatus";
        break;
    case 17: //可视对讲系统切换配置
        m_csCommandStr = "/ISAPI/VideoIntercom/SystemSwitchCfg";
        xmlInput.Parse("<SystemSwitchCfg>\
                            <systemType>NetworkVideoIntercomSystem</systemType>\
                        </SystemSwitchCfg>");
        break;
    case 18: //蓝牙通讯密钥设置
        m_csCommandStr = "/ISAPI/VideoIntercom/BluetoothCommKey";
        xmlInput.Parse("<BluetoothCommKey>\
                            <encryptionKey>0123456789abcdef</encryptionKey>\
                        </BluetoothCommKey>");
        break;
    case 19: //人脸服务器配置
        m_csCommandStr = "/ISAPI/VideoIntercom/FaceServerCfg";
        xmlInput.Parse("<FaceServerCfg>\
                          <ip>10.17.133.13</ip>\
                          <port>1234</port>\
                        </FaceServerCfg>");
        break;
    default:
        break;
    }
    if (m_cmbOperateType.GetCurSel() == 1)
    {
        xmlInput.SetRoot();
        m_csInputParam = xmlInput.GetChildren().c_str();
        m_csInputParam.Replace("\n", "\r\n");
    }
    else
    {
        m_csInputParam = _T("");
    }
    m_csOutputParam = _T("");
    return;
}
