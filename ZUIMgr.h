//////////////////////////////////////////////////////////////////////////
// Creator: Z
// Brief: DUI处理
// Version: 1.0
// Change:
// 1.2013/3/16 Z/1.0/创建

#pragma once

#include "ZDef.h"
#include "ZGlobal.h"

class CZWindow;
class CZControl;

class CZUIMgr
{
public:
	CZUIMgr(void);
	~CZUIMgr(void);

	VOID Attach(CZWindow* pWindow);
	CZWindow* Detach();

	// Notify
	VOID AddNotifier(INotify* pNotifier);		// why can not use const?
	BOOL RemoveNotifier(INotify* pNotifier);	// why can not use const?
	VOID Notify(const NOTIFY& notify);

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	BOOL OnPaint();
	BOOL OnClose();
	BOOL OnMouseMove(POINT& pt);
	BOOL OnLButtonDown(POINT& pt);
	BOOL OnLButtonUp(POINT& pt);
	BOOL OnLButtonDbClk(POINT& pt);

	// 绘制
	VOID InvalidateRect(RECT& rc, BOOL bEraseBG = FALSE);

private:
	VOID SetFocus(CZControl* pCtrl);

private:
	CZWindow*	m_pWindow;			// Real Window
	CZControl*	m_pHoverCtrl;		// Hover Control
	CZControl*	m_pFocusCtrl;		// Focus Control
	CZControl*	m_pClickCtrl;		// Click Control

	HDC			m_hPaintDC;			// Window DC
	HDC			m_hOffscreenDC;		// Offscreen DC
	HBITMAP		m_hOffscreenBmp;	// Offscreen Bmp
	HDC			m_hBackgroundDC;	// Alpha Background DC
	HBITMAP		m_hBackgroundBmp;	// Alpha Background Bmp

	CZCritSec m_cs;
	ATL::CSimpleArray<INotify*> m_aNotifier;
};
