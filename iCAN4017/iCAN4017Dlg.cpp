// iCAN4017Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "iCAN4017.h"
#include "iCAN4017Dlg.h"
#include "icandllheader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CICAN4017Dlg dialog

//�½�һ��CAN����
ROUTECFG cfg;
HANDLE hRoute=0; //�µ�ICAN����
HANDLE hSlave4017=0;//AIģ��4017��MACID=3

//��ʼ������
CICAN4017Dlg::CICAN4017Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CICAN4017Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CICAN4017Dlg)
	m_valuech0 = 0.0;
	m_valuech1 = 0.0;
	m_counter = 0;
	//}}AFX_DATA_INIT
	recbuf[0]=0;
	recbuf[1]=0;
	recbuf[2]=0;
	recbuf[3]=0;
	recbuf[4]=0;
	recbuf[5]=0;
	recbuf[6]=0;
	recbuf[7]=0;
	len=0;
	count=0;

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CICAN4017Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CICAN4017Dlg)
	DDX_Text(pDX, IDC_EDIT1, m_valuech0);
	DDX_Text(pDX, IDC_EDIT2, m_valuech1);
	DDX_Text(pDX, IDC_EDIT5, m_counter);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CICAN4017Dlg, CDialog)
	//{{AFX_MSG_MAP(CICAN4017Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_startCAN, OnstartCAN)
	ON_BN_CLICKED(IDC_linkCAN, OnlinkCAN)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CICAN4017Dlg message handlers

BOOL CICAN4017Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CICAN4017Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CICAN4017Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CICAN4017Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//����CANģ��
void CICAN4017Dlg::OnstartCAN() 
{
	// TODO: Add your control notification handler code here
    cfg.iCardType=4;//ʹ��usbcan2���߿�
	cfg.iCardInd=0;//�����
	cfg.iCANInd=0;//CANͨ��ѡ��0��ʾ0ͨ����1��ʾ1ͨ����
	cfg.wCANBaud=0x001c;//�����ʵ��趨0x001c(500kbps)
	cfg.iMasterCycle=500;//��վѭ������
	cfg.wMasterID=0; //��վID
    
	
    Mgr_AddRoute(cfg,&hRoute);//���iCAN����

	if(Mgr_StartSys()!=ICANOK)//����Mgr_StartSys()������CAN�����Ƿ����������жϣ�����ΪICANOK
	{
		MessageBox("ϵͳ����ʧ��");
	}
	else
	{
		MessageBox("CAN����������");
	}
	
}

//����4017ģ��
void CICAN4017Dlg::OnlinkCAN() 
{
	// TODO: Add your control notification handler code here
	if(Mgr_IsStarted()!=1)
	{
      MessageBox("ϵͳδ����������ʧ�ܣ���������CAN����");
	}
	else
	{
	// TODO: Add your control notification handler code here
	Route_AddSlave(hRoute,3,&hSlave4017);
	if(Slave_Connect(hSlave4017)!=ICANOK)
	{
		MessageBox("4017����ʧ��");
	}
    else
	{
		MessageBox("4017���ӳɹ�");
	}
	
	SetTimer(1,1000,NULL);
	}

}

//��ʱ����ÿ��1���ȡһ��ͨ����״̬
void CICAN4017Dlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==1)
	{    len=16;
         Slave_GetAIData(hSlave4017,recbuf,&len);
         m_valuech0=((double)(recbuf[0]*16*16+recbuf[1])-0x8000)*10/(double)0x8000;
         m_valuech1=((double)(recbuf[2]*16*16+recbuf[3])-0x8000)*10/(double)0x8000;
    //     m_valuech2=((double)(recbuf[4]*16*16+recbuf[5])-0x8000)*10/(double)0x8000;
  //       m_valuech3=((double)(recbuf[6]*16*16+recbuf[7])-0x8000)*10/(double)0x8000;
	     m_counter=count;
         UpdateData(false);
	     count=count+1;
	     CDialog::OnTimer(nIDEvent);
	}

}
