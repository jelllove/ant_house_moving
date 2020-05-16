// AntMapDrawDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AntMapDraw.h"
#include "AntMapDrawDlg.h"

#include <fstream>

using namespace std;

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
// CAntMapDrawDlg dialog

CAntMapDrawDlg::CAntMapDrawDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAntMapDrawDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAntMapDrawDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAntMapDrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAntMapDrawDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAntMapDrawDlg, CDialog)
	//{{AFX_MSG_MAP(CAntMapDrawDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAntMapDrawDlg message handlers

BOOL CAntMapDrawDlg::OnInitDialog()
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
	

	memset(Map, 0, nMapWidth * nMapHeight * sizeof(int));

	CheckRadioButton(IDC_RADIO_WALL, IDC_RADIO_FOOD, IDC_RADIO_WALL);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAntMapDrawDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAntMapDrawDlg::OnPaint() 
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

	Draw();

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAntMapDrawDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAntMapDrawDlg::OnButton1() 
{
	CFileDialog dlg(false, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "地图文件(*.map)|*.map||", this);

	if (dlg.DoModal() == IDOK)
	{
		fstream file;

		CString str = dlg.GetPathName();

		str += ".map";

		file.open(str.GetBuffer(0), ios::out | ios::binary);

		if (file.bad() || ! file.good())
		{
			file.close();
			AfxMessageBox("文件创建失败");

			return;
		}

		file.write((char *)Map, nMapHeight * nMapWidth * sizeof(int));

		file.close();

		MessageBox("保存成功");

		
	}
	// TODO: Add your control notification handler code here
	
}

void CAntMapDrawDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	if (point.x < (nMapWidth * nPicWidth) && (point.y < (nMapHeight * nPicHeight)))
	{
		int nX = point.x / nPicWidth;
		int nY = point.y / nPicHeight;

		int nIDSelect = GetCheckedRadioButton(IDC_RADIO_WALL, IDC_RADIO_FOOD);

		switch(nIDSelect)
		{
		case IDC_RADIO_WALL:
			{
				if (Map[nY][nX] == NOTHING || Map[nY][nX] == WALL)
				{
					Map[nY][nX] = WALL;
				}
				break;
			}
		case IDC_RADIO_NEST:
			{
				for (int i = 0; i < nMapHeight; i++)
				{
					for (int k = 0; k < nMapWidth; k++)
					{
						if (Map[i][k] == NEST && Map[i][k] != FOOD)
						{
							Map[i][k] = NOTHING;			
						}
					}
				}
				if (Map[nY][nX] != FOOD)
				{
					Map[nY][nX] = NEST;
				}
				
				
				break;
			}
		case IDC_RADIO_FOOD:
			{
				for (int i = 0; i < nMapHeight; i++)
				{
					for (int k = 0; k < nMapWidth; k++)
					{
						if (Map[i][k] == FOOD && Map[i][k] != NEST)
						{
							Map[i][k] = NOTHING;
						}
					}
				}

				if (Map[nY][nX] != NEST)
				{
					Map[nY][nX] = FOOD;
				}


				break;
			}
		}

	}

	Draw();

	CDialog::OnLButtonDown(nFlags, point);
}

void CAntMapDrawDlg::Draw()
{

	CClientDC dc(this);

	HDC wallDC = CreateCompatibleDC(dc.m_hDC);
	HBITMAP wallBitmap = (HBITMAP)LoadImage(NULL, "wall.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(wallDC, wallBitmap);


	HDC nestDC = CreateCompatibleDC(dc.m_hDC);
	HBITMAP nestBitmap = (HBITMAP)LoadImage(NULL, "nest.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(nestDC, nestBitmap);

	HDC foodDC = CreateCompatibleDC(dc.m_hDC);
	HBITMAP foodBitmap = (HBITMAP)LoadImage(NULL, "food.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(foodDC, foodBitmap);



	HDC hdc = CreateCompatibleDC(dc.m_hDC);

	HBITMAP bitmap = CreateCompatibleBitmap(dc.m_hDC, nMapWidth * nPicWidth, nMapHeight * nPicHeight);

	SelectObject(hdc, bitmap);

	PatBlt(hdc, 0, 0, nMapWidth * nPicWidth, nMapHeight * nPicHeight, WHITENESS);

	int i,k;
	
	for (i = 0; i < nMapHeight; i++)
	{
		for (k = 0; k < nMapWidth; k++)
		{
			switch(Map[i][k])
			{
			case WALL:
				{
					BitBlt(hdc, k * nPicWidth, i * nPicHeight, nPicWidth, nPicHeight, wallDC, 0, 0, SRCCOPY);
					break;
				}
			case NEST:
				{
					BitBlt(hdc, k * nPicWidth, i * nPicHeight, nPicWidth, nPicHeight, nestDC, 0, 0, SRCCOPY);
					break;
				}
			case FOOD:
				{
					BitBlt(hdc, k * nPicWidth, i * nPicHeight, nPicWidth, nPicHeight, foodDC, 0, 0, SRCCOPY);
					break;
				}
				
			}
		}
	}



	for (i = 0; i < nMapHeight; i++)
	{
	
		MoveToEx(hdc, 0, i * nPicHeight, NULL);

		LineTo(hdc, nMapWidth * nPicWidth, i * nPicHeight);
	}

	for (k = 0; k < nMapWidth; k++)
	{
		MoveToEx(hdc, k * nPicWidth, 0, NULL);

		LineTo(hdc, k * nPicWidth, nMapHeight * nPicHeight);
	}
	
	BitBlt(dc.m_hDC, 0, 0, nMapWidth * nPicWidth, nMapHeight * nPicHeight, hdc, 0, 0, SRCCOPY);

	DeleteDC(hdc);
	DeleteObject(bitmap);

	DeleteDC(nestDC);
	DeleteObject(nestBitmap);

	DeleteDC(wallDC);
	DeleteObject(wallBitmap);

	DeleteDC(foodDC);
	DeleteObject(foodBitmap);
}

void CAntMapDrawDlg::OnMouseMove(UINT nFlags, CPoint point) 
{

	if (nFlags == 1)
	{
		
		if (point.x < (nMapWidth * nPicWidth) && (point.y < (nMapHeight * nPicHeight)))
		{
			int nX = point.x / nPicWidth;
			int nY = point.y / nPicHeight;
			
			int nIDSelect = GetCheckedRadioButton(IDC_RADIO_WALL, IDC_RADIO_FOOD);
			
			switch(nIDSelect)
			{
			case IDC_RADIO_WALL:
				{
					if (Map[nY][nX] == NOTHING || Map[nY][nX] == WALL)
					{
						Map[nY][nX] = WALL;
					}
					break;
				}
			case IDC_RADIO_NEST:
				{
					for (int i = 0; i < nMapHeight; i++)
					{
						for (int k = 0; k < nMapWidth; k++)
						{
							if (Map[i][k] == NEST && Map[i][k] != FOOD)
							{
								Map[i][k] = NOTHING;			
							}
						}
					}
					
					Map[nY][nX] = NEST;
					
					break;
				}
			case IDC_RADIO_FOOD:
				{
					for (int i = 0; i < nMapHeight; i++)
					{
						for (int k = 0; k < nMapWidth; k++)
						{
							if (Map[i][k] == FOOD && Map[i][k] != NEST)
							{
								Map[i][k] = NOTHING;
							}
						}
					}
					
					Map[nY][nX] = FOOD;
					
					break;
				}
			}
			
		}
		
		Draw();
	}
	else
	{
		if (nFlags == 2)
		{
			if (point.x < (nMapWidth * nPicWidth) && (point.y < (nMapHeight * nPicHeight)))
			{
				int nX = point.x / nPicWidth;
				int nY = point.y / nPicHeight;
				
				Map[nY][nX] = NOTHING;

				Draw();
			}
		}
	}
	
	CDialog::OnMouseMove(nFlags, point);
}

void CAntMapDrawDlg::OnButton2() 
{

	memset(Map, 0, nMapWidth * nMapHeight * sizeof(int));
	Draw();
	// TODO: Add your control notification handler code here
	
}

void CAntMapDrawDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	if (point.x < (nMapWidth * nPicWidth) && (point.y < (nMapHeight * nPicHeight)))
	{
			int nX = point.x / nPicWidth;
			int nY = point.y / nPicHeight;

			Map[nY][nX ] = NOTHING;

			Draw();
	}
	CDialog::OnRButtonDown(nFlags, point);
}

void CAntMapDrawDlg::OnButton3() 
{

	CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "地图文件(*.map)|*.map||", this);

	if (dlg.DoModal() == IDOK)
	{
		fstream file;

		CString str = dlg.GetPathName();

		file.open(str.GetBuffer(0), ios::in | ios::binary);

		if (file.bad() || ! file.good())
		{
			file.close();
			AfxMessageBox("文件打开失败");

			return;
		}

		file.read((char *)Map, nMapHeight * nMapWidth * sizeof(int));

		file.close();

		Draw();

	}
	// TODO: Add your control notification handler code here
	
}
