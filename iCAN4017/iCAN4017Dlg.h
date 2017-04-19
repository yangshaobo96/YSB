// iCAN4017Dlg.h : header file
//

#if !defined(AFX_ICAN4017DLG_H__9226CBF3_8CCA_4D60_B1FC_4E1B4F06BFDC__INCLUDED_)
#define AFX_ICAN4017DLG_H__9226CBF3_8CCA_4D60_B1FC_4E1B4F06BFDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CICAN4017Dlg dialog

class CICAN4017Dlg : public CDialog
{
// Construction
public:
	CICAN4017Dlg(CWnd* pParent = NULL);	// standard constructor

    unsigned char recbuf[16];
	unsigned long len;
	int count;

// Dialog Data
	//{{AFX_DATA(CICAN4017Dlg)
	enum { IDD = IDD_ICAN4017_DIALOG };
	double	m_valuech0;
	double	m_valuech1;
	int		m_counter;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CICAN4017Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CICAN4017Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnstartCAN();
	afx_msg void OnlinkCAN();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ICAN4017DLG_H__9226CBF3_8CCA_4D60_B1FC_4E1B4F06BFDC__INCLUDED_)
