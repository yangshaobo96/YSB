#ifndef ICANDLLHEADER_H
#define ICANDLLHEADER_H

//接口卡类型定义
#define VCI_PCI5121		1
#define VCI_PCI9810		2
#define VCI_USBCAN1		3
#define VCI_USBCAN2		4
#define VCI_PCI9820		5
#define VCI_CAN232		6
#define VCI_PCI5110		7
#define VCI_CANLITE		8
#define VCI_ISA9620		9
#define VCI_ISA5420		10
#define VCI_PC104CAN	11
#define VCI_CANETE		12
#define VCI_DNP9810		13
#define VCI_PCI9840		14
#define VCI_PC104CAN2	15
#define VCI_PCI9820I	16

#define ICANOK					0
#define ICANERR_FUNCNOTEXIST	0x01
#define ICANERR_SRCNOTEXIST		0x02//资源不存在
#define ICANERR_CMDNOTSUPPORT	0x03
#define ICANERR_CMDILLEGAL		0x04
#define ICANERR_CONNECTNOTEXIST	0x05

#define ICANERR					0xf1
#define ICANERR_USING			0xf3//资源被占用
#define ICANERR_SETCAN			0xf4//打开设备失败或初始化CAN失败
#define ICANERR_SRVSTARTED		0xf5//服务已启动,无法进行此项操作
#define ICANERR_TIMEOUT			0xf6
#define ICANERR_ITEMEXIST		0xf7//目标已经存在

#define MASTER_CYCLEUNIT	10

#define IOCTL_ROUTE_SETSRCPORT	1
#define IOCTL_ROUTE_SETDESIP	2
#define IOCTL_ROUTE_SETDESPORT	3
#define IOCTL_ROUTE_START		4

typedef struct _tagRouteCfg
{
	int iCardType;//CAN接口卡类型
	int iCardInd;//CAN接口卡序号
	int iCANInd;//CAN路数
	WORD wCANBaud;//0x311c - 10K,0x041c - 100K,0x001c - 500K
	WORD wMasterID;//ICAN网络主站ID
	int iMasterCycle;//ICAN网络主站定时循环参数
}ROUTECFG;

#ifdef __cplusplus
extern "C"
{
#endif

//添加一个ICAN网络，并设定ICAN网络参数
DWORD __stdcall Mgr_AddRoute(ROUTECFG &cfg,HANDLE* phRoute);
//删除一个ICAN网络
DWORD __stdcall Mgr_DelRoute(HANDLE hRoute);
//删除所有ICAN网络
DWORD __stdcall Mgr_DelAllRoute();
//启动系统
DWORD __stdcall Mgr_StartSys();
//停止系统
DWORD __stdcall Mgr_StopSys();
//系统是否已启动
DWORD __stdcall Mgr_IsStarted();

//往指定ICAN网络中添加从站
DWORD __stdcall Route_AddSlave(HANDLE hRoute,DWORD SlaveID,HANDLE* phSlave);
//删除指定ICAN网络中的从站
DWORD __stdcall Route_DelSlave(HANDLE hRoute,HANDLE hSlave);
//删除指定ICAN网络中所有从站
DWORD __stdcall Route_DelAllSlave(HANDLE hRoute);
//设置指定ICAN网络配置参数
DWORD __stdcall Route_SetConfig(HANDLE hRoute,ROUTECFG &cfg);
//获取指定ICAN网络配置参数
DWORD __stdcall Route_GetConfig(HANDLE hRoute,ROUTECFG* pcfg);
//通过从站ID在指定ICAN网络中获取该从站句柄
DWORD __stdcall Route_GetSlavebyID(HANDLE hRoute,DWORD SlaveID,HANDLE* phSlave);
DWORD __stdcall Route_ConnectAllSlaveAsync(HANDLE hRoute);

DWORD __stdcall Route_IOCtl(HANDLE hRoute,DWORD code,BYTE* pinbuff=NULL,
							int inlen=0,BYTE* poutbuff=NULL,int outlen=0);

//连接指定从站
DWORD __stdcall Slave_Connect(HANDLE hSlave);
//断开指定从站
DWORD __stdcall Slave_Disconnect(HANDLE hSlave);
//从站是否已连接
DWORD __stdcall Slave_IsConnected(HANDLE hSlave);
//获取指定从站ID
DWORD __stdcall Slave_GetID(HANDLE hSlave);
//获取指定从站IO数据长度
DWORD __stdcall Slave_GetIODataLen(HANDLE hSlave,DWORD *pDI,DWORD* pDO,DWORD* pAI,DWORD* pAO);
//获取指定从站AI数据
DWORD __stdcall Slave_GetAIData(HANDLE hSlave,BYTE* pRecbuf,DWORD* pReclen);
//获取指定从站DI数据
DWORD __stdcall Slave_GetDIData(HANDLE hSlave,BYTE* pRecbuf,DWORD* pReclen);
//从指定从站接收AI/DI数据
DWORD __stdcall Slave_GetData(HANDLE hSlave,DWORD SourceID,BYTE* pRecbuf,DWORD* pReclen);
//往指定从站发送AO/DO数据
DWORD __stdcall Slave_SendData(HANDLE hSlave,DWORD SourceID,BYTE* pSendbuf,DWORD Sendlen);
//设置指定从站配置参数
DWORD __stdcall Slave_SetConfig(HANDLE hSlave,DWORD SourceID,DWORD* pSubsourceID,
								BYTE* pSendbuf,DWORD Sendlen);
//获取指定从站配置参数
DWORD __stdcall Slave_GetConfig(HANDLE hSlave,DWORD SourceID,DWORD* pSubsourceID,
								BYTE* pRecbuf,DWORD Reclen);

//设置从站的数据刷新周期，默认为ROUTECFG.iMasterCycle,单位10ms
DWORD __stdcall Slave_SetCycle(HANDLE hSlave,DWORD dwCycle);

DWORD __stdcall Slave_GetCycle(HANDLE hSlave);

//获取触发数据
DWORD __stdcall Slave_GetTriggerData(HANDLE hSlave,DWORD* pSourceIDSt,
									 BYTE* pRecbuf,DWORD* pRecLen);

#ifdef __cplusplus
}
#endif


#endif
