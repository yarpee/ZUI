//////////////////////////////////////////////////////////////////////////
// Creator: Z
// Brief: 全局数据和函数
// Version: 1.0
// Change:
// 1.2013/3/15 Z/1.0/创建

#pragma once

#include <Windows.h>
#include "ZWindow.h"

// Application Module
BOOL InitAppModule(HINSTANCE hInstance);
HINSTANCE GetInstance();

// Message Loop
int MessageLoop();
BOOL InitZUIMessageLoop(CZWindow* pWindow);

// RECT
inline LONG GetRectWidth(const RECT& rc)
{
	return rc.right - rc.left;
}

inline LONG GetRectHeight(const RECT& rc)
{
	return rc.bottom - rc.top;
}
