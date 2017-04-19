#ifndef ICANDLLHEADER_H
#define ICANDLLHEADER_H

//�ӿڿ����Ͷ���
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
#define ICANERR_SRCNOTEXIST		0x02//��Դ������
#define ICANERR_CMDNOTSUPPORT	0x03
#define ICANERR_CMDILLEGAL		0x04
#define ICANERR_CONNECTNOTEXIST	0x05

#define ICANERR					0xf1
#define ICANERR_USING			0xf3//��Դ��ռ��
#define ICANERR_SETCAN			0xf4//���豸ʧ�ܻ��ʼ��CANʧ��
#define ICANERR_SRVSTARTED		0xf5//����������,�޷����д������
#define ICANERR_TIMEOUT			0xf6
#define ICANERR_ITEMEXIST		0xf7//Ŀ���Ѿ�����

#define MASTER_CYCLEUNIT	10

#define IOCTL_ROUTE_SETSRCPORT	1
#define IOCTL_ROUTE_SETDESIP	2
#define IOCTL_ROUTE_SETDESPORT	3
#define IOCTL_ROUTE_START		4

typedef struct _tagRouteCfg
{
	int iCardType;//CAN�ӿڿ�����
	int iCardInd;//CAN�ӿڿ����
	int iCANInd;//CAN·��
	WORD wCANBaud;//0x311c - 10K,0x041c - 100K,0x001c - 500K
	WORD wMasterID;//ICAN������վID
	int iMasterCycle;//ICAN������վ��ʱѭ������
}ROUTECFG;

#ifdef __cplusplus
extern "C"
{
#endif

//���һ��ICAN���磬���趨ICAN�������
DWORD __stdcall Mgr_AddRoute(ROUTECFG &cfg,HANDLE* phRoute);
//ɾ��һ��ICAN����
DWORD __stdcall Mgr_DelRoute(HANDLE hRoute);
//ɾ������ICAN����
DWORD __stdcall Mgr_DelAllRoute();
//����ϵͳ
DWORD __stdcall Mgr_StartSys();
//ֹͣϵͳ
DWORD __stdcall Mgr_StopSys();
//ϵͳ�Ƿ�������
DWORD __stdcall Mgr_IsStarted();

//��ָ��ICAN��������Ӵ�վ
DWORD __stdcall Route_AddSlave(HANDLE hRoute,DWORD SlaveID,HANDLE* phSlave);
//ɾ��ָ��ICAN�����еĴ�վ
DWORD __stdcall Route_DelSlave(HANDLE hRoute,HANDLE hSlave);
//ɾ��ָ��ICAN���������д�վ
DWORD __stdcall Route_DelAllSlave(HANDLE hRoute);
//����ָ��ICAN�������ò���
DWORD __stdcall Route_SetConfig(HANDLE hRoute,ROUTECFG &cfg);
//��ȡָ��ICAN�������ò���
DWORD __stdcall Route_GetConfig(HANDLE hRoute,ROUTECFG* pcfg);
//ͨ����վID��ָ��ICAN�����л�ȡ�ô�վ���
DWORD __stdcall Route_GetSlavebyID(HANDLE hRoute,DWORD SlaveID,HANDLE* phSlave);
DWORD __stdcall Route_ConnectAllSlaveAsync(HANDLE hRoute);

DWORD __stdcall Route_IOCtl(HANDLE hRoute,DWORD code,BYTE* pinbuff=NULL,
							int inlen=0,BYTE* poutbuff=NULL,int outlen=0);

//����ָ����վ
DWORD __stdcall Slave_Connect(HANDLE hSlave);
//�Ͽ�ָ����վ
DWORD __stdcall Slave_Disconnect(HANDLE hSlave);
//��վ�Ƿ�������
DWORD __stdcall Slave_IsConnected(HANDLE hSlave);
//��ȡָ����վID
DWORD __stdcall Slave_GetID(HANDLE hSlave);
//��ȡָ����վIO���ݳ���
DWORD __stdcall Slave_GetIODataLen(HANDLE hSlave,DWORD *pDI,DWORD* pDO,DWORD* pAI,DWORD* pAO);
//��ȡָ����վAI����
DWORD __stdcall Slave_GetAIData(HANDLE hSlave,BYTE* pRecbuf,DWORD* pReclen);
//��ȡָ����վDI����
DWORD __stdcall Slave_GetDIData(HANDLE hSlave,BYTE* pRecbuf,DWORD* pReclen);
//��ָ����վ����AI/DI����
DWORD __stdcall Slave_GetData(HANDLE hSlave,DWORD SourceID,BYTE* pRecbuf,DWORD* pReclen);
//��ָ����վ����AO/DO����
DWORD __stdcall Slave_SendData(HANDLE hSlave,DWORD SourceID,BYTE* pSendbuf,DWORD Sendlen);
//����ָ����վ���ò���
DWORD __stdcall Slave_SetConfig(HANDLE hSlave,DWORD SourceID,DWORD* pSubsourceID,
								BYTE* pSendbuf,DWORD Sendlen);
//��ȡָ����վ���ò���
DWORD __stdcall Slave_GetConfig(HANDLE hSlave,DWORD SourceID,DWORD* pSubsourceID,
								BYTE* pRecbuf,DWORD Reclen);

//���ô�վ������ˢ�����ڣ�Ĭ��ΪROUTECFG.iMasterCycle,��λ10ms
DWORD __stdcall Slave_SetCycle(HANDLE hSlave,DWORD dwCycle);

DWORD __stdcall Slave_GetCycle(HANDLE hSlave);

//��ȡ��������
DWORD __stdcall Slave_GetTriggerData(HANDLE hSlave,DWORD* pSourceIDSt,
									 BYTE* pRecbuf,DWORD* pRecLen);

#ifdef __cplusplus
}
#endif


#endif
