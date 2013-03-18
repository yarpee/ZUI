//////////////////////////////////////////////////////////////////////////
// Creator: Z
// Brief: 对Windows窗口的封装
// Version: 1.0
// Change:
// 1.2013/3/15 Z/1.0/创建

#pragma once

#include <Windows.h>

class CZUIMgr;
class CZControl;

class CZWindow
{
public:
	CZWindow(void);
	~CZWindow(void);

	operator		HWND() const;

	VOID			AttachZUIMgr(CZUIMgr* pMgr);	// 只有AttachZUIMgr后才会成为DUI
	CZUIMgr*		DetachZUIMgr();

	CZControl*		GetRootControl();

protected:
	// 注册窗口类
	BOOL			RegisterWindowClass();
	virtual UINT	GetClassStyle();
	virtual HICON	GetClassIcon(BOOL bSmall = FALSE);
	virtual HCURSOR	GetClassCursor();
	virtual HBRUSH	GetClassBackground();
	virtual LPCTSTR	GetClassMenuName();
	virtual LPCTSTR	GetWindowClassName();

	// 创建窗口
//#ifdef CreateWindow
//#pragma push_macro("CreateWindow")
//#undef CreateWindow
//	HWND CreateWindow(DWORD dwStyle, 
	HWND CreateZWindow(DWORD dwStyle, 
		DWORD dwExStyle, 
		RECT& rc, 
		LPCTSTR lpWindowName = NULL, 
		HWND hWndParent = NULL, 
		HMENU hMenu = NULL);
//#pragma pop_macro("CreateWindow")
//#endif

	// 显示窗口
	VOID ShowWindow(BOOL bShow = TRUE, BOOL bFocus = TRUE);

	// 消息处理函数
	static LRESULT CALLBACK	WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT			HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

protected:
	HWND		m_hWnd;			// 真窗口句柄
	CZUIMgr*	m_pZUIMgr;		// ZUI Mgr
	CZControl*	m_pRootCtrl;	// 控件根结点
};
