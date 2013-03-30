//////////////////////////////////////////////////////////////////////////
// Creator: Z
// Brief: �ڲ�ȫ�ֶ���
// Version: 1.0
// Change:
// 1.2013/3/16 Z/1.0/����

#pragma once

// ������뽫λ������ָ��ƽ̨֮ǰ��ƽ̨��ΪĿ�꣬���޸����ж��塣
// �йز�ͬƽ̨��Ӧֵ��������Ϣ����ο� MSDN��
#ifndef WINVER				// ����ʹ���ض��� Windows XP ����߰汾�Ĺ��ܡ�
#define WINVER 0x0501		// ����ֵ����Ϊ��Ӧ��ֵ���������� Windows �������汾��
#endif

#ifndef _WIN32_WINNT		// ����ʹ���ض��� Windows XP ����߰汾�Ĺ��ܡ�
#define _WIN32_WINNT 0x0501	// ����ֵ����Ϊ��Ӧ��ֵ���������� Windows �������汾��
#endif						

#ifndef _WIN32_WINDOWS		// ����ʹ���ض��� Windows 98 ����߰汾�Ĺ��ܡ�
#define _WIN32_WINDOWS 0x0410 // ����ֵ����Ϊ�ʵ���ֵ����ָ���� Windows Me ����߰汾��ΪĿ�ꡣ
#endif

#ifndef _WIN32_IE			// ����ʹ���ض��� IE 6.0 ����߰汾�Ĺ��ܡ�
#define _WIN32_IE 0x0600	// ����ֵ����Ϊ��Ӧ��ֵ���������� IE �������汾��
#endif

#define WIN32_LEAN_AND_MEAN		// �� Windows ͷ���ų�����ʹ�õ�����

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
