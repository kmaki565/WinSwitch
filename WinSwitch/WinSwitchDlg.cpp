
// WinSwitchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WinSwitch.h"
#include "WinSwitchDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWinSwitchDlg dialog



CWinSwitchDlg::CWinSwitchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWinSwitchDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinSwitchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctlList);
}

BEGIN_MESSAGE_MAP(CWinSwitchDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(ADD_ITEM_TO_WINDOW_LIST, &CWinSwitchDlg::OnAddItemToWindowList)
	ON_BN_CLICKED(IDSHOW, &CWinSwitchDlg::OnBnClickedShow)
	ON_BN_CLICKED(IDC_BUTTON1, &CWinSwitchDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CWinSwitchDlg message handlers

BOOL CWinSwitchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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
	(void)m_ctlList.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_ctlList.SetHeadings(_T("Window name,320;Class name,200;Proc name,200"));
	m_ctlList.LoadColumnInfo();

	RefreshWinList();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWinSwitchDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWinSwitchDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWinSwitchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lp) {

	TCHAR strWindowText[1024];
	::GetWindowText(hwnd, strWindowText, 1024);
	if (strWindowText[0] == 0) return TRUE;
	if (!::IsWindowVisible(hwnd)) return TRUE;

	SendMessage((HWND)lp, ADD_ITEM_TO_WINDOW_LIST, (WPARAM)hwnd, NULL);

	return TRUE;
}

void CWinSwitchDlg::RefreshWinList()
{
	m_ctlList.DeleteAllItems();
	m_ImageList.DeleteImageList();

	m_ImageList.Create(16, 16, ILC_MASK | ILC_COLOR24, 1, 1);
	::EnumWindows((WNDENUMPROC)EnumWindowsProc, (LPARAM)this->m_hWnd);

	m_ctlList.SetImageList(&m_ImageList, LVSIL_SMALL);
}


afx_msg LRESULT CWinSwitchDlg::OnAddItemToWindowList(WPARAM wParam, LPARAM lParam)
{
	TCHAR strWindowText[1024], ClassName[1024];
	HWND hwnd = (HWND)wParam;
	int ItemIndex;
	//int iImage;

	::GetWindowText(hwnd, strWindowText, sizeof(strWindowText));
	::GetClassName(hwnd, ClassName, sizeof(ClassName));

	TCHAR ProcName[MAX_PATH];
	LPTSTR lpProcName;
	if (GetProcessNameByWindowHandle(hwnd, ProcName)) {
		lpProcName = ProcName;
		// To show only exe name
		//lpProcName = _tcsrchr(ProcName, _T('\\')) + sizeof(TCHAR);
	}
	else {
		_stprintf_s(ProcName, _T("unable to get proc name"));
		lpProcName = ProcName;
	}

	ItemIndex = m_ctlList.AddItem(strWindowText, ClassName, lpProcName);
	m_ctlList.SetItemData(ItemIndex, (DWORD)hwnd);

	GetAppIcon(hwnd);
	LVITEM  listitem;
	listitem.iItem = ItemIndex;
	listitem.mask = LVIF_IMAGE;
	listitem.iImage = ItemIndex;
	m_ctlList.SetItem(&listitem);

	return 0;
}

BOOL CWinSwitchDlg::GetProcessNameByWindowHandle(HWND hwnd, LPTSTR ProcName)
{
	BOOL ret = FALSE;
	DWORD processId;
	GetWindowThreadProcessId(hwnd, &processId);

	HANDLE Handle = OpenProcess(
		PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
		FALSE,
		processId
		);
	if (Handle)
	{
		if (GetModuleFileNameEx(Handle, 0, ProcName, MAX_PATH))
		{
			// At this point, buffer contains the full path to the executable
			ret = TRUE;
		}
		CloseHandle(Handle);
	}
	return ret;
}

void CWinSwitchDlg::GetAppIcon(HWND hwnd)
{
	HICON hIcon;

	SendMessageTimeout(hwnd, WM_GETICON, ICON_SMALL, 0, SMTO_ABORTIFHUNG, 300, (DWORD *)&hIcon);
	//hIcon = (HICON)SendMessage(hWnd, WM_GETICON, wIconType, 0);

	if (hIcon == NULL)
		hIcon = (HICON)GetClassLong(hwnd, GCL_HICONSM);

	if (hIcon != NULL)
	{
		m_ImageList.Add(hIcon);
	}
	else
	{
		// Use default icon
		if ((hIcon = AfxGetApp()->LoadIcon(IDI_ICON1)) != NULL)
			m_ImageList.Add(hIcon);
	}
	return;
}


void CWinSwitchDlg::OnBnClickedShow()
{
	POSITION pos = m_ctlList.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		::MessageBox(this->m_hWnd, _T("No items were selected"), _T("Oops"), MB_OK);
	}
	else
	{
		while (pos)
		{
			int nItem = m_ctlList.GetNextSelectedItem(pos);
			HWND SelectedWin = (HWND)m_ctlList.GetItemData(nItem);
			// Bring to top
			if (::IsIconic(SelectedWin)) {
				::ShowWindow(SelectedWin, SW_RESTORE);
			}
			::SetWindowPos(SelectedWin, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

			TRACE(_T("Item %d was selected!... hwnd = 0x%X\n"), nItem, (int)SelectedWin);

			// you could do your own processing on nItem here
		}
	}
}


void CWinSwitchDlg::OnBnClickedButton1()
{
	RefreshWinList();
}
