// AntMapDrawDlg.h : header file
//

#if !defined(AFX_ANTMAPDRAWDLG_H__ABE397FA_2EE1_45CF_A787_B7B5A8987D51__INCLUDED_)
#define AFX_ANTMAPDRAWDLG_H__ABE397FA_2EE1_45CF_A787_B7B5A8987D51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAntMapDrawDlg dialog
enum MAPSTATE//地图上点的状态
{
	NOTHING = 0,
	FOOD = 1,
    NEST = 2,
	WALL = 3
};


const int nMapWidth = 50;//地图宽

const int nMapHeight = 20;//地图高

const int nPicWidth = 16;//每张图片的宽

const int nPicHeight = 16;//每张图片的高

class CAntMapDrawDlg : public CDialog
{
// Construction
public:
	CAntMapDrawDlg(CWnd* pParent = NULL);	// standard constructor

	void Draw();

	int Map[nMapHeight][nMapWidth];//地图数据
	
// Dialog Data
	//{{AFX_DATA(CAntMapDrawDlg)
	enum { IDD = IDD_ANTMAPDRAW_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAntMapDrawDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAntMapDrawDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnButton2();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANTMAPDRAWDLG_H__ABE397FA_2EE1_45CF_A787_B7B5A8987D51__INCLUDED_)
