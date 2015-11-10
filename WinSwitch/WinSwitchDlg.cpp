
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

// static
UINT CWinSwitchDlg::s_uTaskbarRestart = ::RegisterWindowMessage(_T("TaskbarCreated"));


CWinSwitchDlg::CWinSwitchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWinSwitchDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinSwitchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctlList);
	DDX_Control(pDX, IDC_CHECK1, m_CheckFullPath);
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	DDX_Control(pDX, IDC_CHECK2_MAX, m_checkMax);
}

BEGIN_MESSAGE_MAP(CWinSwitchDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_MESSAGE(ADD_ITEM_TO_WINDOW_LIST, &CWinSwitchDlg::OnAddItemToWindowList)
	ON_BN_CLICKED(IDSHOW, &CWinSwitchDlg::OnBnClickedShow)
	ON_BN_CLICKED(IDC_BUTTON1, &CWinSwitchDlg::OnBnClickedButton1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CWinSwitchDlg::OnNMDblclkList1)
	ON_BN_CLICKED(IDC_CHECK1, &CWinSwitchDlg::OnBnClickedCheck1)
	ON_MESSAGE(WM_SYSTRAYNOTIFY, &CWinSwitchDlg::OnSysTrayNotify)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDCANCEL, &CWinSwitchDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &CWinSwitchDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_WINDOW, &CWinSwitchDlg::OnBnClickedButtonCloseWindow)
	ON_WM_HOTKEY()
	ON_EN_UPDATE(IDC_EDIT1, &CWinSwitchDlg::OnEnUpdateEdit1)
	ON_BN_CLICKED(IDC_BUTTON3, &CWinSwitchDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4_SORT, &CWinSwitchDlg::OnBnClickedButton4Sort)
	ON_REGISTERED_MESSAGE(s_uTaskbarRestart, &CWinSwitchDlg::OnTaskbarRestart)
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

	// RegisterHotKey to show this dialog
	UINT	uiID = VK_F1;
	UINT	uiMod = MOD_ALT;
	::RegisterHotKey(m_hWnd, CATCH_HOTKEY_ID, uiMod, uiID);

	m_hAccel = ::LoadAccelerators(::AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));

	// Add an icon to taskbar notification area
	UpdateSysTrayIcon(NIM_ADD);

	(void)m_ctlList.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	//m_ctlList.SetHeadings(_T("Window,320;Class,200;Process,200"));
	m_ctlList.SetHeadings(_T("Process (F2 to sort),160;Window,360;Class,180"));
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

	for (int iColumn = 0; iColumn < 3; iColumn++)		// Assume 3 columns in the list
	{
		m_ctlList.ClearSortArrow(iColumn);
	}

	m_ImageList.DeleteImageList();
	m_ImageList.Create(16, 16, ILC_MASK | ILC_COLOR24, 1, 1);
	m_ctlList.SetImageList(&m_ImageList, LVSIL_SMALL);

	::EnumWindows((WNDENUMPROC)EnumWindowsProc, (LPARAM)this->m_hWnd);

}


afx_msg LRESULT CWinSwitchDlg::OnAddItemToWindowList(WPARAM wParam, LPARAM lParam)
{
	TCHAR strWindowText[1024], ClassName[1024];
	HWND hwnd = (HWND)wParam;
	int ItemIndex, IconIndex;

	::GetWindowText(hwnd, strWindowText, sizeof(strWindowText));
	::GetClassName(hwnd, ClassName, sizeof(ClassName));

	// We don't list up my window
	if (_tcscmp(ClassName, MY_WNDCLS_NAME) == 0) return 0;

	TCHAR ProcName[MAX_PATH];
	LPTSTR lpProcName;
	if (GetProcessNameByWindowHandle(hwnd, ProcName)) {
		if (m_CheckFullPath.GetCheck() == BST_CHECKED) {
			lpProcName = ProcName;
		}
		else {
			// To show only exe name
			lpProcName = _tcsrchr(ProcName, _T('\\')) + 1;
		}
	}
	else {
		_stprintf_s(ProcName, _T("unable to get proc name"));
		lpProcName = ProcName;
	}

	ItemIndex = m_ctlList.AddItem(lpProcName, strWindowText, ClassName);
	m_ctlList.SetItemData(ItemIndex, (DWORD)hwnd);

	IconIndex = GetAppIcon(hwnd);
	if (IconIndex != -1) {
		m_ctlList.SetItem(ItemIndex, 0, LVIF_IMAGE, NULL, IconIndex, 0, 0, 0);
	}
	
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

int CWinSwitchDlg::GetAppIcon(HWND hwnd)
{
	HICON hIcon;
	int IconIndex;

	// First method
	SendMessageTimeout(hwnd, WM_GETICON, ICON_SMALL, 0, SMTO_ABORTIFHUNG, 300, (DWORD *)&hIcon);
	//hIcon = (HICON)SendMessage(hWnd, WM_GETICON, wIconType, 0);

	if (hIcon == NULL) {
		// Second method
		hIcon = (HICON)GetClassLong(hwnd, GCL_HICONSM);
	}

	if (hIcon == NULL) {
		// Use default icon
		hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	}

	IconIndex = m_ImageList.Add(hIcon);
	//MyOutputDebugString(_T("IconIndex %d\n"), IconIndex);

	return IconIndex;
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

			if (m_checkMax.GetCheck() == BST_CHECKED)
			{
				::SendMessage(SelectedWin, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
			}
			else
			{
				if (::IsIconic(SelectedWin))
				{
					// Instead of ::ShowWindow(SelectedWin, SW_RESTORE);,
					// This works on Admin process window
					//
					::SendMessage(SelectedWin, WM_SYSCOMMAND, SC_RESTORE, 0);
				}
			}
			//
			// Bring to top
			//
			//if (::SetWindowPos(SelectedWin, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE)) {
			if (::SetForegroundWindow(SelectedWin))
			{
				// If showing up the windows is successful, hide this dialog
				ShowWindow(SW_HIDE);
			}
			else
			{
				CString msg;
				msg.Format(_T("Could not bring item %d to top... hwnd = 0x%X, Error: %0x%X\n"),
					nItem, (int)SelectedWin, GetLastError());
				AfxMessageBox(msg);
			}

		}
	}
}


void CWinSwitchDlg::OnBnClickedButton1()
{
	RefreshWinList();
}


void CWinSwitchDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	OnBnClickedShow();

	*pResult = 0;
}


void CWinSwitchDlg::OnBnClickedCheck1()
{
	RefreshWinList();
}

bool CWinSwitchDlg::UpdateSysTrayIcon(DWORD dwAction)
{
	NOTIFYICONDATA nid = { 0 };
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = m_hWnd;

	HICON hIconPrev = NULL;

	switch (dwAction)
	{
	case NIM_MODIFY:
	case NIM_ADD:
	{
		nid.uFlags |= NIF_TIP | NIF_ICON | NIF_MESSAGE;
		nid.uCallbackMessage = WM_SYSTRAYNOTIFY;
		lstrcpyn(nid.szTip, _T("WinSwitch"), ARRAYSIZE(nid.szTip));
		nid.hIcon = m_hIcon;
	}
		break;
	case NIM_DELETE:
		hIconPrev = m_hIcon;
		break;
	}

	BOOL bRes = ::Shell_NotifyIcon(dwAction, &nid);
	ATLASSERT(bRes);

	if (hIconPrev != NULL)
		::DestroyIcon(hIconPrev);

	return (bRes != FALSE);
}


afx_msg LRESULT CWinSwitchDlg::OnSysTrayNotify(WPARAM wParam, LPARAM lParam)
{
	switch (lParam)
	{
	case WM_LBUTTONUP:
		if (IsWindowVisible())
			ShowWindow(SW_HIDE);
		else
			ShowAndActivate();
		break;
	case WM_RBUTTONUP:
		HandleContextCommand(ShowContextMenu());
		break;
	}
	return 0;
}

int CWinSwitchDlg::ShowContextMenu(void)
{
	HMENU hMenu = ::LoadMenu(
		_AtlBaseModule.GetResourceInstance(),
		MAKEINTRESOURCE(IDR_MENU1));
	ATLASSERT(hMenu != NULL);

	HMENU hTrackPopup = ::GetSubMenu(hMenu, 0);
	ATLASSERT(hTrackPopup != NULL);

	const UINT nCheck = MF_BYCOMMAND |
		(IsWindowVisible() ? MF_CHECKED : MF_UNCHECKED);
	::CheckMenuItem(hTrackPopup, IDC_LAUNCH, nCheck);

	POINT pt = { 0 };
	::GetCursorPos(&pt);

	::SetForegroundWindow(m_hWnd);

	int nCmd = ::TrackPopupMenu(hTrackPopup, TPM_RETURNCMD,
		pt.x, pt.y, 0, m_hWnd, NULL);

	PostMessage(WM_NULL);

	return nCmd;
}

void CWinSwitchDlg::HandleContextCommand(int nCmd)
{
	if (nCmd == 0) return;

	switch (nCmd)
	{
	case IDC_LAUNCH:
		if (IsWindowVisible())
			ShowWindow(SW_HIDE);
		else
			ShowAndActivate();
		break;
	case IDC_EXIT:
		DestroyWindow();
		break;
	default:
		ATLASSERT(FALSE);
	}
}

void CWinSwitchDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	if (m_hIcon)	// TODO: Should be m_hSysTrayIcon...
	{
		ATLVERIFY(UpdateSysTrayIcon(NIM_DELETE));
		::DestroyIcon(m_hIcon);
	}

	::UnregisterHotKey(m_hWnd, CATCH_HOTKEY_ID);
}

void CWinSwitchDlg::ShowAndActivate()
{
	RefreshWinList();

	if (!IsWindowVisible() || IsIconic())
		ShowWindow(SW_SHOWNORMAL);

	::SetForegroundWindow(m_hWnd);

	// Set focus to the list
	::SendMessage(m_hWnd, WM_NEXTDLGCTL, (WPARAM)::GetDlgItem(m_hWnd, IDC_LIST1), TRUE);
	//::SetFocus(::GetDlgItem(m_hWnd, IDC_LIST1));

}


void CWinSwitchDlg::OnBnClickedCancel()
{
	// Don't close the app but just put to background.
	ShowWindow(SW_HIDE);
}


void CWinSwitchDlg::OnBnClickedButton2()
{
	// Exit app for debug.
	DestroyWindow();
}


void CWinSwitchDlg::OnBnClickedButtonCloseWindow()
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

			::SendMessage(SelectedWin, WM_SYSCOMMAND, SC_CLOSE, 0);

			DWORD err = GetLastError();
			if (err > 0) {
				CString msg;
				msg.Format(_T("Could not close item %d... hwnd = 0x%X, Error: %0x%X\n"),
					nItem, (int)SelectedWin, err);
				AfxMessageBox(msg);
			}

		}
		RefreshWinList();
	}
}


void CWinSwitchDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	ShowAndActivate();

	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}


void CWinSwitchDlg::OnEnUpdateEdit1()
{
	CString Input1;
	m_Edit1.GetWindowText(Input1);
	// TODO: Real time update
}


//void CWinSwitchDlg::OnEnKillfocusEdit1()
//{
//	CString Input1;
//	m_Edit1.GetWindowText(Input1);
//
//	UpdateLvByInput1(Input1);
//}

//BOOL CWinSwitchDlg::PreTranslateMessage(MSG* pMsg)
//{
//	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_TAB)
//	{
//		CWnd* pFocusWnd = GetFocus();
//
//		if (pFocusWnd != NULL && pFocusWnd->GetDlgCtrlID() == IDC_EDIT1)
//		{
//			CString Input1;
//			m_Edit1.GetWindowText(Input1);
//			UpdateLvByInput1(Input1);
//		}
//	}
//	return CDialog::PreTranslateMessage(pMsg);
//}


void CWinSwitchDlg::FindNextByWindowTitle(CString Input1, int StartItem)
{
	if (Input1.IsEmpty()) return;

	int nItem = StartItem;

	while (nItem < m_ctlList.GetItemCount())
	{
		CString WindowTitle = m_ctlList.GetItemText(nItem, 1);

		WindowTitle.MakeLower();
		Input1.MakeLower();

		if (WindowTitle.Find(Input1) >= 0) {
			// Match
			m_ctlList.SetItemState(nItem, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
			m_ctlList.EnsureVisible(nItem, FALSE);
			break;
		}
		nItem++;
	}

}


//void CWinSwitchDlg::OnEnSetfocusEdit2()
//{
//	CString Input1;
//	m_Edit1.GetWindowText(Input1);
//	UpdateLvByInput1(Input1);
//}


BOOL CWinSwitchDlg::PreTranslateMessage(MSG* pMsg)
{
	::TranslateAccelerator(m_hWnd, m_hAccel, pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

void CWinSwitchDlg::ClearSelections()
{
	int id = m_ctlList.GetNextItem(-1, LVNI_SELECTED);
	if (id != -1)
		m_ctlList.SetItemState(id, 0, LVIS_FOCUSED | LVIS_SELECTED);
}

void CWinSwitchDlg::OnBnClickedButton3()
{
	CString Input1;
	m_Edit1.GetWindowText(Input1);

	int StartItem;
	POSITION p = m_ctlList.GetFirstSelectedItemPosition();
	if (!p) {
		StartItem = 0;
	}
	else {
		StartItem = m_ctlList.GetNextSelectedItem(p) + 1;
	}

	ClearSelections();

	FindNextByWindowTitle(Input1, StartItem);
}


void CWinSwitchDlg::OnBnClickedButton4Sort()
{
	NMLISTVIEW nmlv;
	::memset(&nmlv, 0, sizeof(NMLISTVIEW));

	nmlv.iSubItem = 0;  // Sort first column
	nmlv.hdr.code = LVN_COLUMNCLICK;    // Emulate column click
	nmlv.hdr.idFrom = ::GetDlgCtrlID(m_ctlList.m_hWnd);
	nmlv.hdr.hwndFrom = m_ctlList.m_hWnd;

	::SendMessage(m_hWnd, WM_NOTIFY, nmlv.hdr.idFrom, (LPARAM)&nmlv);
}


afx_msg LRESULT CWinSwitchDlg::OnTaskbarRestart(WPARAM wParam, LPARAM lParam)
{
	return (UpdateSysTrayIcon(NIM_ADD) ? 0L : -1L);
}

