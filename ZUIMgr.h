//////////////////////////////////////////////////////////////////////////
// Creator: Z
// Brief: DUI处理
// Version: 1.0
// Change:
// 1.2013/3/16 Z/1.0/创建

#pragma once

#include <Windows.h>

class CZWindow;

class CZUIMgr
{
public:
	CZUIMgr(void);
	~CZUIMgr(void);

	VOID Attach(CZWindow* pWindow);
	CZWindow* Detach();
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	BOOL OnPaint();

	// 绘图
	VOID InvalidateRect(RECT& rc, BOOL bEraseBG = FALSE);

private:
	CZWindow*	m_pWindow;			// Real Window
	HDC			m_hPaintDC;			// Window DC
	HDC			m_hOffscreenDC;		// Offscreen DC
	HBITMAP		m_hOffscreenBmp;	// Offscreen Bmp
	HDC			m_hBackgroundDC;	// Alpha Background DC
	HBITMAP		m_hBackgroundBmp;	// Alpha Background Bmp
};
