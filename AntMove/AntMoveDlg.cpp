// AntMoveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AntMove.h"
#include "AntMoveDlg.h"

#include "Ant.h"

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
// CAntMoveDlg dialog

CAntMoveDlg::CAntMoveDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAntMoveDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAntMoveDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAntMoveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAntMoveDlg)
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAntMoveDlg, CDialog)
	//{{AFX_MSG_MAP(CAntMoveDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAntMoveDlg message handlers

BOOL CAntMoveDlg::OnInitDialog()
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
	
	m_ntime = 0;

	CClientDC dc(this);

	mdc = CreateCompatibleDC(dc.m_hDC);

	bitmap = CreateCompatibleBitmap(dc.m_hDC, nMapWidth * nPicWidth, nMapHeight * nPicHeight);

	SelectObject(mdc, bitmap);

	InitResource();

	m_slider.SetRange(10, 1000);

	m_slider.SetPos(30);

	SetTimer(1, 30, NULL);

	SetTimer(2, 1000, NULL);

	
	
	for (int i = 0; i < nMapHeight; i++)
	{
		for (int k = 0; k < nMapWidth; k++)
		{
			if (Map[i][k] == NEST)
			{
				nestX = k;
				nestY = i;

				break;
			}
		}
	}
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAntMoveDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAntMoveDlg::OnPaint() 
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

	CClientDC dc(this);

	DrawAll(mdc);

	BitBlt(dc.m_hDC, 0, 0, nMapWidth * nPicWidth, nMapHeight * nPicHeight, mdc, 0, 0, SRCCOPY);

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAntMoveDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



void CAntMoveDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	DeleteDC(mdc);

	DeleteObject(bitmap);

	KillTimer(2);
	KillTimer(1);

	ReleaseResource();
	// TODO: Add your message handler code here
	
}

void CAntMoveDlg::OnTimer(UINT nIDEvent) 
{

	int nFind = 0;

	int nGo = 0;

	int nBack = 0;

	switch(nIDEvent)
	{
	case 1:
		{
			vector<Ant>::iterator it = g_vecAnt.begin();
			
			while (it != g_vecAnt.end())
			{
				(*it).Move();

				switch((*it).m_state) 
				{
				case FINDING:
					{
						nFind++;
						break;
					}
				case GO:
					{
						nGo++;
						break;
					}
				case BACK:
					{
						nBack++;
						break;
					}
				}
				
				it++;
			}
			
			CClientDC dc(this);
			
			DrawAll(mdc);
			
			BitBlt(dc.m_hDC, 0, 0, nMapWidth * nPicWidth, nMapHeight * nPicHeight, mdc, 0, 0, SRCCOPY);
			
			
			CString str;

			str.Format("当前总有:%d只蚂蚁   正在寻找食物的蚂蚁有:%d只   正在往家里搬回食物的蚂蚁有:%d只   正在赶去搬食物的蚂蚁有:%d只    已经用时:%d秒    剩下的食物有:%d", nAntCount, nFind, nBack, nGo, m_ntime, nFoodCount);

			SetWindowText(str);

			if (nFoodCount <= 0)
			{
				KillTimer(1);
				KillTimer(2);
				MessageBox("食物已经搬完");
			}

			break;
		}
	case 2:
		{
			
			if (g_vecAnt.size() < nAntCount)
			{
				Ant ant(nestX, nestY);
				
				g_vecAnt.push_back(ant);
			}
			
			m_ntime++;
		}
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CAntMoveDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	

	SetTimer(1, m_slider.GetPos(), NULL);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
