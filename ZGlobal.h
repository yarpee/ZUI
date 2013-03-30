//////////////////////////////////////////////////////////////////////////
// Creator: Z
// Brief: 外部全局定义
// Version: 1.0
// Change:
// 1.2013/3/15 Z/1.0/创建

#pragma once

#include <Windows.h>

//////////////////////////////////////////////////////////////////////////
// Application Module
BOOL InitAppModule(HINSTANCE hInstance);
HINSTANCE GetInstance();

//////////////////////////////////////////////////////////////////////////
// Message Loop
class CZWindow;

int MessageLoop();
BOOL InitZUIMessageLoop(CZWindow* pWindow);

//////////////////////////////////////////////////////////////////////////
// Notify
class CZControl;

typedef struct _NOTIFY
{
	DWORD		dwNotifyID;
	WPARAM		wParam;
	LPARAM		lParam;
	DWORD		dwTimestamp;
	POINT		ptMouse;
	CZControl*	pCtrl;
} NOTIFY, *PNOTIFY;

class INotify
{
public:
	virtual VOID Notify(const NOTIFY& notify) = 0;
};

#define N_BASE	0x00000000
#define N_CLICK	N_BASE + 1
