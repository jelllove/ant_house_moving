// AntMoveDlg.h : header file
//

#if !defined(AFX_ANTMOVEDLG_H__A68740E2_3E48_4BD0_8497_C2C740771B25__INCLUDED_)
#define AFX_ANTMOVEDLG_H__A68740E2_3E48_4BD0_8497_C2C740771B25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAntMoveDlg dialog

class CAntMoveDlg : public CDialog
{
// Construction
public:
	CAntMoveDlg(CWnd* pParent = NULL);	// standard constructor

	int nestX, nestY;

	int m_ntime;

	HDC mdc;

	HBITMAP bitmap;
// Dialog Data
	//{{AFX_DATA(CAntMoveDlg)
	enum { IDD = IDD_ANTMOVE_DIALOG };
	CSliderCtrl	m_slider;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAntMoveDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAntMoveDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANTMOVEDLG_H__A68740E2_3E48_4BD0_8497_C2C740771B25__INCLUDED_)
