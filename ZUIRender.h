//////////////////////////////////////////////////////////////////////////
// Creator: Z
// Brief: Rendering Engine
// Version: 1.0
// Change:
// 1.2013/3/17 Z/1.0/����

#pragma once

#include <Windows.h>

class CZUIRender
{
public:
	CZUIRender(void);
	~CZUIRender(void);

	// TODO: ����
	static VOID DrawText(HDC hDC, LPCTSTR lpszText, DWORD dwColor, DWORD dwStyle, RECT& rc);
};
