//////////////////////////////////////////////////////////////////////////
// Creator: Z
// Brief: 内部全局定义
// Version: 1.0
// Change:
// 1.2013/3/16 Z/1.0/创建

#pragma once

// 如果必须将位于下面指定平台之前的平台作为目标，请修改下列定义。
// 有关不同平台对应值的最新信息，请参考 MSDN。
#ifndef WINVER				// 允许使用特定于 Windows XP 或更高版本的功能。
#define WINVER 0x0501		// 将此值更改为相应的值，以适用于 Windows 的其他版本。
#endif

#ifndef _WIN32_WINNT		// 允许使用特定于 Windows XP 或更高版本的功能。
#define _WIN32_WINNT 0x0501	// 将此值更改为相应的值，以适用于 Windows 的其他版本。
#endif						

#ifndef _WIN32_WINDOWS		// 允许使用特定于 Windows 98 或更高版本的功能。
#define _WIN32_WINDOWS 0x0410 // 将此值更改为适当的值，以指定将 Windows Me 或更高版本作为目标。
#endif

#ifndef _WIN32_IE			// 允许使用特定于 IE 6.0 或更高版本的功能。
#define _WIN32_IE 0x0600	// 将此值更改为相应的值，以适用于 IE 的其他版本。
#endif

#define WIN32_LEAN_AND_MEAN		// 从 Windows 头中排除极少使用的资料

#include <Windows.h>
#include <atlbase.h>

#define _Z_VER	0x0100	// ZUI version 1.00

// RECT
inline LONG GetRectWidth(const RECT& rc)
{
	return rc.right - rc.left;
}

inline LONG GetRectHeight(const RECT& rc)
{
	return rc.bottom - rc.top;
}

//////////////////////////////////////////////////////////////////////////
// State
#define ST_NORMAL	0x00000000
#define ST_HOVER	0x00000001
#define ST_PUSH		0x00000002
#define ST_FOCUS	0x00000004
#define ST_DISABLE	0x00000008

//////////////////////////////////////////////////////////////////////////
// Event
typedef struct _EVENT
{
	DWORD	dwEventID;
	WPARAM	wParam;
	LPARAM	lParam;
	DWORD	dwTimestamp;
	POINT	ptMouse;
} EVENT, *PEVENT;

#define E_BASE			0x00000000
#define E_MOUSEMOVE		E_BASE + 1
#define E_MOUSELEAVE	E_MOUSEMOVE + 1
#define E_LBUTTONDOWN	E_MOUSELEAVE + 1
#define E_LBUTTONUP		E_LBUTTONDOWN + 1
#define E_LBUTTONDBCLK	E_LBUTTONUP + 1
#define E_SETFOCUS		E_LBUTTONDBCLK + 1
#define E_KILLFOCUS		E_SETFOCUS + 1

//////////////////////////////////////////////////////////////////////////
// Critical Section
typedef CComAutoCriticalSection CZCritSec;
typedef CComCritSecLock<CComAutoCriticalSection> CZCritSecLock;
