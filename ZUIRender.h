//////////////////////////////////////////////////////////////////////////
// Creator: Z
// Brief: Rendering Engine
// Version: 1.0
// Change:
// 1.2013/3/17 Z/1.0/´´½¨

#pragma once

#include <Windows.h>

class CZUIRender
{
public:
	CZUIRender(void);
	~CZUIRender(void);

	// TODO: Mask
	static HBITMAP LoadImage(LPCTSTR lpszPath);
	static VOID FreeImage(HBITMAP hBmp);

	// TODO: ×ÖÌå
	static VOID DrawText(HDC hDC, LPCTSTR lpszText, DWORD dwColor, DWORD dwStyle, RECT& rc);

	static VOID DrawRect(HDC hDC, RECT& rc, DWORD dwBorderSize, DWORD dwBorderColor, SIZE* pxyBorderRound = NULL);

	// TODO: Too many!
	static VOID DrawImage(HDC hDC, LPCTSTR lpszPath, RECT& rcSize, RECT& rcPaint);
};
