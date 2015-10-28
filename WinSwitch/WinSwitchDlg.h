
// WinSwitchDlg.h : header file
//

#pragma once

#ifndef SORTLISTCTRL_H
#include "SortListCtrl\SortListCtrl.h"
#endif	// SORTLISTCTRL_H
#include "afxwin.h"

// CWinSwitchDlg dialog
class CWinSwitchDlg : public CDialogEx
{
// Construction
public:
	CWinSwitchDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_WINSWITCH_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CSortListCtrl m_ctlList;
private:
	CImageList m_ImageList;
public:
	void RefreshWinList();
protected:
	afx_msg LRESULT OnAddItemToWindowList(WPARAM wParam, LPARAM lParam);
	void GetAppIcon(HWND hwnd);
	BOOL GetProcessNameByWindowHandle(HWND hwnd, LPTSTR ProcName);
	bool UpdateSysTrayIcon(DWORD dwAction);
	int ShowContextMenu(void);
	void HandleContextCommand(int nCmd);
	void ShowAndActivate();
public:
	afx_msg void OnBnClickedShow();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_CheckFullPath;
	afx_msg void OnBnClickedCheck1();
protected:
	afx_msg LRESULT OnSysTrayNotify(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButtonCloseWindow();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
};
