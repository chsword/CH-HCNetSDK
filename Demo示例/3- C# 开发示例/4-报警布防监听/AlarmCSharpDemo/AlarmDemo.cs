using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.IO;

namespace AlarmCSharpDemo
{
    public partial class AlarmDemo : Form
    {
        private Int32 m_lUserID = -1;
        private Int32[] m_lAlarmHandle = new Int32[200];
        private Int32 iListenHandle = -1; 
        private int iDeviceNumber = 0; //添加设备个数
        private uint iLastErr = 0;
        private string strErr;
        private CHCNetSDK.MSGCallBack m_falarmData = null;
        public delegate void UpdateListBoxCallback(string strAlarmTime, string strDevIP, string strAlarmMsg);

        CHCNetSDK.NET_VCA_TRAVERSE_PLANE m_struTraversePlane = new CHCNetSDK.NET_VCA_TRAVERSE_PLANE();
        CHCNetSDK.NET_VCA_AREA m_struVcaArea = new CHCNetSDK.NET_VCA_AREA();
        CHCNetSDK.NET_VCA_INTRUSION m_struIntrusion = new CHCNetSDK.NET_VCA_INTRUSION();
        CHCNetSDK.UNION_STATFRAME m_struStatFrame = new CHCNetSDK.UNION_STATFRAME();
        CHCNetSDK.UNION_STATTIME m_struStatTime = new CHCNetSDK.UNION_STATTIME();
        public AlarmDemo()
        {
            InitializeComponent();
            bool m_bInitSDK = CHCNetSDK.NET_DVR_Init();
            if (m_bInitSDK == false)
            {
                MessageBox.Show("NET_DVR_Init error!");
                return;
            }
            else
            {
                byte[] strIP = new byte[16 * 16];
                uint dwValidNum=0;
                Boolean bEnableBind=false;

                //获取本地PC网卡IP信息
                if (CHCNetSDK.NET_DVR_GetLocalIP(strIP, ref dwValidNum, ref bEnableBind))
                {
                    if (dwValidNum > 0)
                    {
                        //取第一张网卡的IP地址为默认监听端口
                        textBoxListenIP.Text = System.Text.Encoding.UTF8.GetString(strIP, 0, 16);
                    }
                
                }

                //保存SDK日志 To save the SDK log
                CHCNetSDK.NET_DVR_SetLogToFile(3, "C:\\SdkLog\\", true);
                for (int i = 0; i < 200; i++)
                {
                    m_lAlarmHandle[i] = -1;
                }

                //设置报警回调函数
                m_falarmData = new CHCNetSDK.MSGCallBack(MsgCallback);
                CHCNetSDK.NET_DVR_SetDVRMessageCallBack_V30(m_falarmData, IntPtr.Zero);
            }
        }

        public void MsgCallback(int lCommand, ref CHCNetSDK.NET_DVR_ALARMER pAlarmer, IntPtr pAlarmInfo, uint dwBufLen, IntPtr pUser)
        {
            //通过lCommand来判断接收到的报警信息类型，不同的lCommand对应不同的pAlarmInfo内容
            switch (lCommand)
            {
                case CHCNetSDK.COMM_ALARM: //(DS-8000老设备)移动侦测、视频丢失、遮挡、IO信号量等报警信息
                    ProcessCommAlarm(ref pAlarmer, pAlarmInfo, dwBufLen, pUser);
                    break;
                case CHCNetSDK.COMM_ALARM_V30://移动侦测、视频丢失、遮挡、IO信号量等报警信息
                    ProcessCommAlarm_V30(ref pAlarmer, pAlarmInfo, dwBufLen, pUser);
                    break;
                case CHCNetSDK.COMM_ALARM_RULE://进出区域、入侵、徘徊、人员聚集等行为分析报警信息
                    ProcessCommAlarm_RULE(ref pAlarmer, pAlarmInfo, dwBufLen, pUser);
                    break;
                case CHCNetSDK.COMM_UPLOAD_PLATE_RESULT://交通抓拍结果上传(老报警信息类型)
                    ProcessCommAlarm_Plate(ref pAlarmer, pAlarmInfo, dwBufLen, pUser);
                    break;
                case CHCNetSDK.COMM_ITS_PLATE_RESULT://交通抓拍结果上传(新报警信息类型)
                    ProcessCommAlarm_ITSPlate(ref pAlarmer, pAlarmInfo, dwBufLen, pUser);
                    break;
                case CHCNetSDK.COMM_ALARM_PDC://客流量统计报警信息
                    ProcessCommAlarm_PDC(ref pAlarmer, pAlarmInfo, dwBufLen, pUser);
                    break;
                default:
                    break;
            }
        }

        public void ProcessCommAlarm(ref CHCNetSDK.NET_DVR_ALARMER pAlarmer, IntPtr pAlarmInfo, uint dwBufLen, IntPtr pUser)
        {
            CHCNetSDK.NET_DVR_ALARMINFO struAlarmInfo = new CHCNetSDK.NET_DVR_ALARMINFO();

            struAlarmInfo = (CHCNetSDK.NET_DVR_ALARMINFO)Marshal.PtrToStructure(pAlarmInfo, typeof(CHCNetSDK.NET_DVR_ALARMINFO));

            string strIP = pAlarmer.sDeviceIP;
            string stringAlarm = "";
            int i = 0;

            switch (struAlarmInfo.dwAlarmType)
            {
                case 0:
                    stringAlarm = "信号量报警，报警报警输入口：" + struAlarmInfo.dwAlarmInputNumber + "，触发录像通道：";
                    for (i = 0; i < CHCNetSDK.MAX_CHANNUM; i++)
                    {
                        if (struAlarmInfo.dwAlarmRelateChannel[i] == 1)
                        {
                            stringAlarm += (i + 1) + " \\ ";
                        }
                    }
                    break;
                case 1:
                    stringAlarm = "硬盘满，报警硬盘号：";
                    for (i = 0; i < CHCNetSDK.MAX_DISKNUM; i++)
                    {
                        if (struAlarmInfo.dwDiskNumber[i] == 1)
                        {
                            stringAlarm += (i + 1) + " \\ ";
                        }
                    }
                    break;
                case 2:
                    stringAlarm = "信号丢失，报警通道：";
                    for (i = 0; i < CHCNetSDK.MAX_CHANNUM; i++)
                    {
                        if (struAlarmInfo.dwChannel[i] == 1)
                        {
                            stringAlarm += (i + 1) + " \\ ";
                        }
                    }
                    break;
                case 3:
                    stringAlarm = "移动侦测，报警通道：";
                    for (i = 0; i < CHCNetSDK.MAX_CHANNUM; i++)
                    {
                        if (struAlarmInfo.dwChannel[i] == 1)
                        {
                            stringAlarm += (i + 1) + " \\ ";
                        }
                    }
                    break;
                case 4:
                    stringAlarm = "硬盘未格式化，报警硬盘号：";
                    for (i = 0; i < CHCNetSDK.MAX_DISKNUM; i++)
                    {
                        if (struAlarmInfo.dwDiskNumber[i] == 1)
                        {
                            stringAlarm += (i + 1) + " \\ ";
                        }
                    }
                    break;
                case 5:
                    stringAlarm = "读写硬盘出错，报警硬盘号：";
                    for (i = 0; i < CHCNetSDK.MAX_DISKNUM; i++)
                    {
                        if (struAlarmInfo.dwDiskNumber[i] == 1)
                        {
                            stringAlarm += (i + 1) + " \\ ";
                        }
                    }
                    break;
                case 6:
                    stringAlarm = "遮挡报警，报警通道：";
                    for (i = 0; i < CHCNetSDK.MAX_CHANNUM; i++)
                    {
                        if (struAlarmInfo.dwChannel[i] == 1)
                        {
                            stringAlarm += (i + 1) + " \\ ";
                        }
                    }
                    break;
                case 7:
                    stringAlarm = "制式不匹配，报警通道";
                    for (i = 0; i < CHCNetSDK.MAX_CHANNUM; i++)
                    {
                        if (struAlarmInfo.dwChannel[i] == 1)
                        {
                            stringAlarm += (i + 1) + " \\ ";
                        }
                    }
                    break;
                case 8:
                    stringAlarm = "非法访问";
                    break;
                default:
                    stringAlarm = "其他未知报警信息";
                    break;
            }

            if (InvokeRequired)
            {
                object[] paras = new object[3];
                paras[0] = DateTime.Now.ToString();
                paras[1] = strIP;
                paras[2] = stringAlarm;                
                listViewAlarmInfo.BeginInvoke(new UpdateListBoxCallback(UpdateClientList), paras);
            }
            else
            {
                //创建该控件的主线程直接更新信息列表 
                UpdateClientList(DateTime.Now.ToString(),strIP, stringAlarm);
            }
        }

        private void ProcessCommAlarm_V30(ref CHCNetSDK.NET_DVR_ALARMER pAlarmer, IntPtr pAlarmInfo, uint dwBufLen, IntPtr pUser)
        {

            CHCNetSDK.NET_DVR_ALARMINFO_V30 struAlarmInfoV30 = new CHCNetSDK.NET_DVR_ALARMINFO_V30();

            struAlarmInfoV30 = (CHCNetSDK.NET_DVR_ALARMINFO_V30)Marshal.PtrToStructure(pAlarmInfo, typeof(CHCNetSDK.NET_DVR_ALARMINFO_V30));

            string strIP = pAlarmer.sDeviceIP;
            string stringAlarm = "";
            int i;

            switch (struAlarmInfoV30.dwAlarmType)
            {
                case 0:
                    stringAlarm = "信号量报警，报警报警输入口：" + struAlarmInfoV30.dwAlarmInputNumber + "，触发录像通道：";
                    for (i = 0; i < CHCNetSDK.MAX_CHANNUM_V30; i++)
                    {
                        if (struAlarmInfoV30.byAlarmRelateChannel[i] == 1)
                        {
                            stringAlarm += (i + 1) + "\\";
                        }
                    }
                    break;
                case 1:
                    stringAlarm = "硬盘满，报警硬盘号：";
                    for (i = 0; i < CHCNetSDK.MAX_DISKNUM_V30; i++)
                    {
                        if (struAlarmInfoV30.byDiskNumber[i] == 1)
                        {
                            stringAlarm += (i + 1) + " ";
                        }
                    }
                    break;
                case 2:
                    stringAlarm = "信号丢失，报警通道：";
                    for (i = 0; i < CHCNetSDK.MAX_CHANNUM_V30; i++)
                    {
                        if (struAlarmInfoV30.byChannel[i] == 1)
                        {
                            stringAlarm += (i + 1) + " \\ ";
                        }
                    }
                    break;
                case 3:
                    stringAlarm = "移动侦测，报警通道：";
                    for (i = 0; i < CHCNetSDK.MAX_CHANNUM_V30; i++)
                    {
                        if (struAlarmInfoV30.byChannel[i] == 1)
                        {
                            stringAlarm += (i + 1) + " \\ ";
                        }
                    }
                    break;
                case 4:
                    stringAlarm = "硬盘未格式化，报警硬盘号：";
                    for (i = 0; i < CHCNetSDK.MAX_DISKNUM_V30; i++)
                    {
                        if (struAlarmInfoV30.byDiskNumber[i] == 1)
                        {
                            stringAlarm += (i + 1) + " \\ ";
                        }
                    }
                    break;
                case 5:
                    stringAlarm = "读写硬盘出错，报警硬盘号：";
                    for (i = 0; i < CHCNetSDK.MAX_DISKNUM_V30; i++)
                    {
                        if (struAlarmInfoV30.byDiskNumber[i] == 1)
                        {
                            stringAlarm += (i + 1) + " \\ ";
                        }
                    }
                    break;
                case 6:
                    stringAlarm = "遮挡报警，报警通道：";
                    for (i = 0; i < CHCNetSDK.MAX_CHANNUM_V30; i++)
                    {
                        if (struAlarmInfoV30.byChannel[i] == 1)
                        {
                            stringAlarm += (i + 1) + " \\ ";
                        }
                    }
                    break;
                case 7:
                    stringAlarm = "制式不匹配，报警通道";
                    for (i = 0; i < CHCNetSDK.MAX_CHANNUM_V30; i++)
                    {
                        if (struAlarmInfoV30.byChannel[i] == 1)
                        {
                            stringAlarm += (i + 1) + " \\ ";
                        }
                    }
                    break;
                case 8:
                    stringAlarm = "非法访问";
                    break;
                case 9:
                    stringAlarm = "视频信号异常，报警通道";
                    for (i = 0; i < CHCNetSDK.MAX_CHANNUM_V30; i++)
                    {
                        if (struAlarmInfoV30.byChannel[i] == 1)
                        {
                            stringAlarm += (i + 1) + " \\ ";
                        }
                    }
                    break;
                case 10:
                    stringAlarm = "录像/抓图异常，报警通道";
                    for (i = 0; i < CHCNetSDK.MAX_CHANNUM_V30; i++)
                    {
                        if (struAlarmInfoV30.byChannel[i] == 1)
                        {
                            stringAlarm += (i + 1) + " \\ ";
                        }
                    }
                    break;
                case 11:
                    stringAlarm = "智能场景变化，报警通道";
                    for (i = 0; i < CHCNetSDK.MAX_CHANNUM_V30; i++)
                    {
                        if (struAlarmInfoV30.byChannel[i] == 1)
                        {
                            stringAlarm += (i + 1) + " \\ ";
                        }
                    }
                    break;
                case 12:
                    stringAlarm = "阵列异常";
                    break;
                case 13:
                    stringAlarm = "前端/录像分辨率不匹配，报警通道";
                    for (i = 0; i < CHCNetSDK.MAX_CHANNUM_V30; i++)
                    {
                        if (struAlarmInfoV30.byChannel[i] == 1)
                        {
                            stringAlarm += (i + 1) + " \\ ";
                        }
                    }
                    break;
                case 15:
                    stringAlarm = "智能侦测，报警通道";
                    for (i = 0; i < CHCNetSDK.MAX_CHANNUM_V30; i++)
                    {
                        if (struAlarmInfoV30.byChannel[i] == 1)
                        {
                            stringAlarm += (i + 1) + " \\ ";
                        }
                    }
                    break;
                default:
                    stringAlarm = "其他未知报警信息";
                    break;
            }

            if (InvokeRequired)
            {
                object[] paras = new object[3];
                paras[0] = DateTime.Now.ToString();
                paras[1] = strIP;
                paras[2] = stringAlarm;
                listViewAlarmInfo.BeginInvoke(new UpdateListBoxCallback(UpdateClientList), paras);
            }
            else
            {
                //创建该控件的主线程直接更新信息列表 
                UpdateClientList(DateTime.Now.ToString(), strIP, stringAlarm);
            }

        }

        private void ProcessCommAlarm_RULE(ref CHCNetSDK.NET_DVR_ALARMER pAlarmer, IntPtr pAlarmInfo, uint dwBufLen, IntPtr pUser)
        {
            CHCNetSDK.NET_VCA_RULE_ALARM struRuleAlarmInfo = new CHCNetSDK.NET_VCA_RULE_ALARM();
            struRuleAlarmInfo = (CHCNetSDK.NET_VCA_RULE_ALARM)Marshal.PtrToStructure(pAlarmInfo, typeof(CHCNetSDK.NET_VCA_RULE_ALARM));

            //报警信息
            string stringAlarm = "";
            uint dwSize = (uint)Marshal.SizeOf(struRuleAlarmInfo.struRuleInfo.uEventParam);

            switch (struRuleAlarmInfo.struRuleInfo.wEventTypeEx)
            {
                case (ushort)CHCNetSDK.VCA_RULE_EVENT_TYPE_EX.ENUM_VCA_EVENT_TRAVERSE_PLANE:
                    IntPtr ptrTraverseInfo = Marshal.AllocHGlobal((Int32)dwSize);
                    Marshal.StructureToPtr(struRuleAlarmInfo.struRuleInfo.uEventParam, ptrTraverseInfo, false);
                    m_struTraversePlane = (CHCNetSDK.NET_VCA_TRAVERSE_PLANE)Marshal.PtrToStructure(ptrTraverseInfo, typeof(CHCNetSDK.NET_VCA_TRAVERSE_PLANE));
                    stringAlarm = "穿越警戒面，目标ID：" + struRuleAlarmInfo.struTargetInfo.dwID;
                    //警戒面边线起点坐标: (m_struTraversePlane.struPlaneBottom.struStart.fX, m_struTraversePlane.struPlaneBottom.struStart.fY)
                    //警戒面边线终点坐标: (m_struTraversePlane.struPlaneBottom.struEnd.fX, m_struTraversePlane.struPlaneBottom.struEnd.fY)
                    break;
                case (ushort)CHCNetSDK.VCA_RULE_EVENT_TYPE_EX.ENUM_VCA_EVENT_ENTER_AREA:
                    IntPtr ptrEnterInfo = Marshal.AllocHGlobal((Int32)dwSize);
                    Marshal.StructureToPtr(struRuleAlarmInfo.struRuleInfo.uEventParam, ptrEnterInfo, false);
                    m_struVcaArea = (CHCNetSDK.NET_VCA_AREA)Marshal.PtrToStructure(ptrEnterInfo, typeof(CHCNetSDK.NET_VCA_AREA));
                    stringAlarm = "目标进入区域，目标ID：" + struRuleAlarmInfo.struTargetInfo.dwID;
                    //m_struVcaArea.struRegion 多边形区域坐标
                    break;
                case (ushort)CHCNetSDK.VCA_RULE_EVENT_TYPE_EX.ENUM_VCA_EVENT_EXIT_AREA:               
                    IntPtr ptrExitInfo = Marshal.AllocHGlobal((Int32)dwSize);
                    Marshal.StructureToPtr(struRuleAlarmInfo.struRuleInfo.uEventParam, ptrExitInfo, false);
                    m_struVcaArea = (CHCNetSDK.NET_VCA_AREA)Marshal.PtrToStructure(ptrExitInfo, typeof(CHCNetSDK.NET_VCA_AREA));
                    stringAlarm = "目标离开区域，目标ID：" + struRuleAlarmInfo.struTargetInfo.dwID;
                    //m_struVcaArea.struRegion 多边形区域坐标
                    break;
                case (ushort)CHCNetSDK.VCA_RULE_EVENT_TYPE_EX.ENUM_VCA_EVENT_INTRUSION:
                    IntPtr ptrIntrusionInfo = Marshal.AllocHGlobal((Int32)dwSize);
                    Marshal.StructureToPtr(struRuleAlarmInfo.struRuleInfo.uEventParam, ptrIntrusionInfo, false);
                    m_struIntrusion = (CHCNetSDK.NET_VCA_INTRUSION)Marshal.PtrToStructure(ptrIntrusionInfo, typeof(CHCNetSDK.NET_VCA_INTRUSION));
                    stringAlarm = "周界入侵，目标ID：" + struRuleAlarmInfo.struTargetInfo.dwID;
                    //m_struIntrusion.struRegion 多边形区域坐标
                    break;
                default:
                    stringAlarm = "其他行为分析报警，目标ID：" + struRuleAlarmInfo.struTargetInfo.dwID;
                    break;            
            }


            //报警图片保存
            if (struRuleAlarmInfo.dwPicDataLen > 0)
            {
                FileStream fs = new FileStream("行为分析报警抓图.jpg", FileMode.Create);
                int iLen = (int)struRuleAlarmInfo.dwPicDataLen;
                byte[] by = new byte[iLen];
                Marshal.Copy(struRuleAlarmInfo.pImage, by, 0, iLen);
                fs.Write(by, 0, iLen);
                fs.Close();
            }

            //报警时间：年月日时分秒
            string strTimeYear = ((struRuleAlarmInfo.dwAbsTime >> 26) + 2000).ToString();
            string strTimeMonth = ((struRuleAlarmInfo.dwAbsTime >> 22) & 15).ToString("d2");
            string strTimeDay = ((struRuleAlarmInfo.dwAbsTime >> 17) & 31).ToString("d2");
            string strTimeHour = ((struRuleAlarmInfo.dwAbsTime >> 12) & 31).ToString("d2");
            string strTimeMinute = ((struRuleAlarmInfo.dwAbsTime >> 6) & 63).ToString("d2");
            string strTimeSecond = ((struRuleAlarmInfo.dwAbsTime >> 0) & 63).ToString("d2");
            string strTime = strTimeYear + "-" + strTimeMonth + "-" + strTimeDay + " " + strTimeHour + ":" + strTimeMinute + ":" + strTimeSecond;
           
            //报警设备IP地址
            string strIP = struRuleAlarmInfo.struDevInfo.struDevIP.sIpV4;

            //将报警信息添加进列表
            if (InvokeRequired)
            {
                object[] paras = new object[3];
                paras[0] = strTime;
                paras[1] = strIP;
                paras[2] = stringAlarm;
                listViewAlarmInfo.BeginInvoke(new UpdateListBoxCallback(UpdateClientList), paras);
            }
            else
            {
                //创建该控件的主线程直接更新信息列表 
                UpdateClientList(strTime, strIP, stringAlarm);
            }
        }

        private void ProcessCommAlarm_Plate(ref CHCNetSDK.NET_DVR_ALARMER pAlarmer, IntPtr pAlarmInfo, uint dwBufLen, IntPtr pUser)
        {
            CHCNetSDK.NET_DVR_PLATE_RESULT struPlateResultInfo = new CHCNetSDK.NET_DVR_PLATE_RESULT();
            uint dwSize = (uint)Marshal.SizeOf(struPlateResultInfo);

            struPlateResultInfo = (CHCNetSDK.NET_DVR_PLATE_RESULT)Marshal.PtrToStructure(pAlarmInfo, typeof(CHCNetSDK.NET_DVR_PLATE_RESULT));

            //保存抓拍图片
            string str = "";
            if (struPlateResultInfo.byResultType == 1 && struPlateResultInfo.dwPicLen != 0)
            {
                str = "D:/UserID_" + pAlarmer.lUserID + "_近景图.jpg";
                FileStream fs = new FileStream(str, FileMode.Create);
                int iLen = (int)struPlateResultInfo.dwPicLen;
                byte[] by = new byte[iLen];
                Marshal.Copy(struPlateResultInfo.pBuffer1, by, 0, iLen);
                fs.Write(by, 0, iLen);
                fs.Close();
            }
            if (struPlateResultInfo.dwPicPlateLen != 0)
            {
                str = "D:/UserID_" + pAlarmer.lUserID + "_车牌图.jpg";
                FileStream fs = new FileStream(str, FileMode.Create);
                int iLen = (int)struPlateResultInfo.dwPicPlateLen;
                byte[] by = new byte[iLen];
                Marshal.Copy(struPlateResultInfo.pBuffer2, by, 0, iLen);
                fs.Write(by, 0, iLen);
                fs.Close();
            }
            if (struPlateResultInfo.dwFarCarPicLen != 0)
            {
                str = "D:/UserID_" + pAlarmer.lUserID + "_远景图.jpg";
                FileStream fs = new FileStream(str, FileMode.Create);
                int iLen = (int)struPlateResultInfo.dwFarCarPicLen;
                byte[] by = new byte[iLen];
                Marshal.Copy(struPlateResultInfo.pBuffer5, by, 0, iLen);
                fs.Write(by, 0, iLen);
                fs.Close();
            }

            //报警设备IP地址
            string strIP = pAlarmer.sDeviceIP;

            //抓拍时间：年月日时分秒
            string strTimeYear = System.Text.Encoding.UTF8.GetString(struPlateResultInfo.byAbsTime);

            //上传结果
            string stringAlarm = "抓拍上传，" + "车牌：" + struPlateResultInfo.struPlateInfo.sLicense + "，车辆序号：" + struPlateResultInfo.struVehicleInfo.dwIndex; 

            if (InvokeRequired)
            {
                object[] paras = new object[3];
                paras[0] = strTimeYear; //当前PC系统时间为DateTime.Now.ToString();
                paras[1] = strIP;
                paras[2] = stringAlarm;
                listViewAlarmInfo.BeginInvoke(new UpdateListBoxCallback(UpdateClientList), paras);
            }
            else
            {
                //创建该控件的主线程直接更新信息列表 
                UpdateClientList(DateTime.Now.ToString(), strIP, stringAlarm);
            }
        }

        private void ProcessCommAlarm_ITSPlate(ref CHCNetSDK.NET_DVR_ALARMER pAlarmer, IntPtr pAlarmInfo, uint dwBufLen, IntPtr pUser)
        {
            CHCNetSDK.NET_ITS_PLATE_RESULT struITSPlateResult = new CHCNetSDK.NET_ITS_PLATE_RESULT();
            uint dwSize = (uint)Marshal.SizeOf(struITSPlateResult);

            struITSPlateResult = (CHCNetSDK.NET_ITS_PLATE_RESULT)Marshal.PtrToStructure(pAlarmInfo, typeof(CHCNetSDK.NET_ITS_PLATE_RESULT));

            //保存抓拍图片
            for (int i = 0; i < struITSPlateResult.dwPicNum; i++)
            {
                if (struITSPlateResult.struPicInfo[i].dwDataLen != 0)
                {
                    string str = "D:/UserID_" + pAlarmer.lUserID + "_Pictype_" + struITSPlateResult.struPicInfo[i].byType + "_Num" + (i + 1) + ".jpg";
                    FileStream fs = new FileStream(str, FileMode.Create);
                    int iLen = (int)struITSPlateResult.struPicInfo[i].dwDataLen;
                    byte[] by = new byte[iLen];
                    Marshal.Copy(struITSPlateResult.struPicInfo[i].pBuffer, by, 0, iLen);
                    fs.Write(by, 0, iLen);
                    fs.Close();
                }
            }
            //报警设备IP地址
            string strIP = pAlarmer.sDeviceIP;

            //抓拍时间：年月日时分秒
            string strTimeYear = string.Format("{0:D4}", struITSPlateResult.struSnapFirstPicTime.wYear) + 
                string.Format("{0:D2}", struITSPlateResult.struSnapFirstPicTime.byMonth) + 
                string.Format("{0:D2}", struITSPlateResult.struSnapFirstPicTime.byDay) + " " 
                + string.Format("{0:D2}", struITSPlateResult.struSnapFirstPicTime.byHour) + ":" 
                + string.Format("{0:D2}", struITSPlateResult.struSnapFirstPicTime.byMinute) + ":" 
                + string.Format("{0:D2}", struITSPlateResult.struSnapFirstPicTime.bySecond) + ":" 
                + string.Format("{0:D3}", struITSPlateResult.struSnapFirstPicTime.wMilliSec);

            //上传结果
            string stringAlarm = "抓拍上传，" + "车牌：" + struITSPlateResult.struPlateInfo.sLicense + "，车辆序号：" + struITSPlateResult.struVehicleInfo.dwIndex;

            if (InvokeRequired)
            {
                object[] paras = new object[3];
                paras[0] = strTimeYear;//当前系统时间为：DateTime.Now.ToString();
                paras[1] = strIP;
                paras[2] = stringAlarm;
                listViewAlarmInfo.BeginInvoke(new UpdateListBoxCallback(UpdateClientList), paras);
            }
            else
            {
                //创建该控件的主线程直接更新信息列表 
                UpdateClientList(DateTime.Now.ToString(), strIP, stringAlarm);
            }
        }

        private void ProcessCommAlarm_PDC(ref CHCNetSDK.NET_DVR_ALARMER pAlarmer, IntPtr pAlarmInfo, uint dwBufLen, IntPtr pUser)
        {
            CHCNetSDK.NET_DVR_PDC_ALRAM_INFO struPDCInfo = new CHCNetSDK.NET_DVR_PDC_ALRAM_INFO();
            uint dwSize = (uint)Marshal.SizeOf(struPDCInfo);
            struPDCInfo = (CHCNetSDK.NET_DVR_PDC_ALRAM_INFO)Marshal.PtrToStructure(pAlarmInfo, typeof(CHCNetSDK.NET_DVR_PDC_ALRAM_INFO));

            string stringAlarm = "客流量统计，进入人数：" + struPDCInfo.dwEnterNum + "，离开人数：" + struPDCInfo.dwLeaveNum;

            uint dwUnionSize = (uint)Marshal.SizeOf(struPDCInfo.uStatModeParam);
            IntPtr ptrPDCUnion = Marshal.AllocHGlobal((Int32)dwUnionSize);
            Marshal.StructureToPtr(struPDCInfo.uStatModeParam, ptrPDCUnion, false);

            if (struPDCInfo.byMode == 0) //单帧统计结果，此处为UTC时间
            {              
                m_struStatFrame = (CHCNetSDK.UNION_STATFRAME)Marshal.PtrToStructure(ptrPDCUnion, typeof(CHCNetSDK.UNION_STATFRAME));       
                stringAlarm = stringAlarm + "，单帧统计，相对时标：" + m_struStatFrame.dwRelativeTime + "，绝对时标：" + m_struStatFrame.dwAbsTime;
            }
            if (struPDCInfo.byMode == 1) //最小时间段统计结果
            {
                m_struStatTime = (CHCNetSDK.UNION_STATTIME)Marshal.PtrToStructure(ptrPDCUnion, typeof(CHCNetSDK.UNION_STATTIME));

                //开始时间
                string strStartTime = string.Format("{0:D4}", m_struStatTime.tmStart.dwYear) +
                string.Format("{0:D2}", m_struStatTime.tmStart.dwMonth) +
                string.Format("{0:D2}", m_struStatTime.tmStart.dwDay) + " "
                + string.Format("{0:D2}", m_struStatTime.tmStart.dwHour) + ":"
                + string.Format("{0:D2}", m_struStatTime.tmStart.dwMinute) + ":"
                + string.Format("{0:D2}", m_struStatTime.tmStart.dwSecond);

                //结束时间
                string strEndTime = string.Format("{0:D4}", m_struStatTime.tmEnd.dwYear) +
                string.Format("{0:D2}", m_struStatTime.tmEnd.dwMonth) +
                string.Format("{0:D2}", m_struStatTime.tmEnd.dwDay) + " "
                + string.Format("{0:D2}", m_struStatTime.tmEnd.dwHour) + ":"
                + string.Format("{0:D2}", m_struStatTime.tmEnd.dwMinute) + ":"
                + string.Format("{0:D2}", m_struStatTime.tmEnd.dwSecond);

                stringAlarm = stringAlarm + "，最小时间段统计，开始时间：" + strStartTime + "，结束时间：" + strEndTime;
            }
            Marshal.FreeHGlobal(ptrPDCUnion);

            //报警设备IP地址
            string strIP = pAlarmer.sDeviceIP;


            if (InvokeRequired)
            {
                object[] paras = new object[3];
                paras[0] = DateTime.Now.ToString(); //当前PC系统时间
                paras[1] = strIP;
                paras[2] = stringAlarm;
                listViewAlarmInfo.BeginInvoke(new UpdateListBoxCallback(UpdateClientList), paras);
            }
            else
            {
                //创建该控件的主线程直接更新信息列表 
                UpdateClientList(DateTime.Now.ToString(), strIP, stringAlarm);
            }
        }

        public void UpdateClientList(string strAlarmTime, string strDevIP, string strAlarmMsg)
        {
            //列表新增报警信息
            listViewAlarmInfo.Items.Add(new ListViewItem(new string[] { strAlarmTime, strDevIP, strAlarmMsg }));
        }

        private void btnLogin_Click(object sender, EventArgs e)
        {
            if (textBoxIP.Text == "" || textBoxPort.Text == "" ||
                textBoxUserName.Text == "" || textBoxPassword.Text == "")
            {
                MessageBox.Show("Please input IP, Port, User name and Password!");
                return;
            }

            if (iDeviceNumber >= 20)
            {
                MessageBox.Show("本程序限制最多添加20台设备！");
                return;
            }

            string DVRIPAddress = textBoxIP.Text; //设备IP地址或者域名 Device IP
            Int16 DVRPortNumber = Int16.Parse(textBoxPort.Text);//设备服务端口号 Device Port
            string DVRUserName = textBoxUserName.Text;//设备登录用户名 User name to login
            string DVRPassword = textBoxPassword.Text;//设备登录密码 Password to login
            CHCNetSDK.NET_DVR_DEVICEINFO_V30 DeviceInfo = new CHCNetSDK.NET_DVR_DEVICEINFO_V30();

            //登录设备 Login the device
            m_lUserID = CHCNetSDK.NET_DVR_Login_V30(DVRIPAddress, DVRPortNumber, DVRUserName, DVRPassword, ref DeviceInfo);
            if (m_lUserID < 0)
            {
                iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                strErr = "NET_DVR_Login_V30 failed, error code= " + iLastErr; //登录失败，输出错误号 Failed to login and output the error code
                MessageBox.Show(strErr);
                return;
            }
            else
            {
                //登录成功
                iDeviceNumber++;
                string str1 = "" + m_lUserID;
                listViewDevice.Items.Add(new ListViewItem(new string[] { str1, DVRIPAddress, "未布防" }));//将已注册设备添加进列表
            }
        }

        private void btn_SetAlarm_Click(object sender, EventArgs e)
        {
             CHCNetSDK.NET_DVR_SETUPALARM_PARAM struAlarmParam = new CHCNetSDK.NET_DVR_SETUPALARM_PARAM();
             struAlarmParam.dwSize = (uint)Marshal.SizeOf(struAlarmParam);
             struAlarmParam.byLevel = 1; //0- 一级布防,1- 二级布防
             struAlarmParam.byAlarmInfoType = 1;//智能交通设备有效，新报警信息类型

             for (int i = 0; i < iDeviceNumber; i++)
             {
                 m_lUserID = Int32.Parse(listViewDevice.Items[i].SubItems[0].Text);
                 m_lAlarmHandle[m_lUserID] = CHCNetSDK.NET_DVR_SetupAlarmChan_V41(m_lUserID, ref struAlarmParam);
                 if (m_lAlarmHandle[m_lUserID] < 0)
                 {
                     iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                     strErr = "布防失败，错误号：" + iLastErr; //布防失败，输出错误号
                     listViewDevice.Items[i].SubItems[2].Text = strErr;              
                 }
                 else
                 {
                     listViewDevice.Items[i].SubItems[2].Text = "布防成功";                     
                 }
                 btn_SetAlarm.Enabled = false;
             }
         }

         private void btnCloseAlarm_Click(object sender, EventArgs e)
         {
             for (int i = 0; i < iDeviceNumber; i++)
             {
                 m_lUserID = Int32.Parse(listViewDevice.Items[i].SubItems[0].Text);
                 if (m_lAlarmHandle[m_lUserID] >= 0)
                 {
                     if (!CHCNetSDK.NET_DVR_CloseAlarmChan_V30(m_lAlarmHandle[m_lUserID]))
                     {
                         iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                         strErr = "撤防失败，错误号：" + iLastErr; //撤防失败，输出错误号
                         listViewDevice.Items[i].SubItems[2].Text = strErr;
                     }
                     else
                     {
                         listViewDevice.Items[i].SubItems[2].Text = "未布防";
                         m_lAlarmHandle[i] = -1;
                     }
                 }
                 else 
                 {
                     listViewDevice.Items[i].SubItems[2].Text = "未布防";                 
                 }
             }
             btn_SetAlarm.Enabled = true;
         }

         private void btnExit_Click(object sender, EventArgs e)
         {
             //撤防
             btnCloseAlarm_Click(sender,e);

             //停止监听
             if (iListenHandle >= 0)
             {
                 CHCNetSDK.NET_DVR_StopListen_V30(iListenHandle);
             }

             //注销登录
             for (int i = 0; i < iDeviceNumber; i++)
             {
                 m_lUserID = Int32.Parse(listViewDevice.Items[i].SubItems[0].Text);
                 CHCNetSDK.NET_DVR_Logout(m_lUserID);                 
             }

             //释放SDK资源，在程序结束之前调用
             CHCNetSDK.NET_DVR_Cleanup();

             Application.Exit();
         }

         private void listViewDevice_MouseClick(object sender, MouseEventArgs e)
         {
             if (e.Button == MouseButtons.Right)
             {
                 if (listViewDevice.SelectedItems.Count > 0)
                 {
                     if (DialogResult.OK == MessageBox.Show("请确认是否删除所选择的设备！","删除提示",MessageBoxButtons.OKCancel))
                     {
                         foreach (ListViewItem item in this.listViewDevice.SelectedItems)
                         {
                             if (item.Selected)
                             {
                                 m_lUserID = Int32.Parse(item.SubItems[0].Text);
                                 CHCNetSDK.NET_DVR_CloseAlarmChan_V30(m_lAlarmHandle[m_lUserID]);
                                 CHCNetSDK.NET_DVR_Logout(m_lUserID);
                                 item.Remove();
                                 iDeviceNumber--;
                             }
                         }
                         this.listViewDevice.Refresh();
                     }                      
                 }
                 else
                 {
                     
                 }
             }
         }

         private void btnStartListen_Click(object sender, EventArgs e)
         {
             string sLocalIP = textBoxListenIP.Text;
             ushort wLocalPort = ushort.Parse(textBoxListenPort.Text);

             iListenHandle = CHCNetSDK.NET_DVR_StartListen_V30(sLocalIP, wLocalPort, m_falarmData, IntPtr.Zero);
             if (iListenHandle < 0)
             {
                 iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                 strErr = "启动监听失败，错误号：" + iLastErr; //撤防失败，输出错误号
                 MessageBox.Show(strErr);
             }
             else
             {
                 MessageBox.Show("成功启动监听！");
                 btnStopListen.Enabled = true;
                 btnStartListen.Enabled = false;
             }
         }

         private void btnStopListen_Click(object sender, EventArgs e)
         {
             if (!CHCNetSDK.NET_DVR_StopListen_V30(iListenHandle))
             {
                 iLastErr = CHCNetSDK.NET_DVR_GetLastError();
                 strErr = "停止监听失败，错误号：" + iLastErr; //撤防失败，输出错误号
                 MessageBox.Show(strErr);
             }
             else
             {
                 MessageBox.Show("停止监听！");
                 btnStopListen.Enabled = false;
                 btnStartListen.Enabled = true;
             }
         }
        
    }
}
