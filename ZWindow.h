//////////////////////////////////////////////////////////////////////////
// Creator: Z
// Brief: ��Windows���ڵķ�װ
// Version: 1.0
// Change:
// 1.2013/3/15 Z/1.0/����

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

	VOID			AttachZUIMgr(CZUIMgr* pMgr);	// ֻ��AttachZUIMgr��Ż��ΪDUI
	CZUIMgr*		DetachZUIMgr();

	CZControl*		GetRootControl();

protected:
	// ע�ᴰ����
	BOOL			RegisterWindowClass();
	virtual UINT	GetClassStyle();
	virtual HICON	GetClassIcon(BOOL bSmall = FALSE);
	virtual HCURSOR	GetClassCursor();
	virtual HBRUSH	GetClassBackground();
	virtual LPCTSTR	GetClassMenuName();
	virtual LPCTSTR	GetWindowClassName();

	// ��������
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

	// ��ʾ����
	VOID ShowWindow(BOOL bShow = TRUE, BOOL bFocus = TRUE);

	// ��Ϣ������
	static LRESULT CALLBACK	WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT			HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

protected:
	HWND		m_hWnd;			// �洰�ھ��
	CZUIMgr*	m_pZUIMgr;		// ZUI Mgr
	CZControl*	m_pRootCtrl;	// �ؼ������
};
