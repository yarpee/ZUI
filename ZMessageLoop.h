//////////////////////////////////////////////////////////////////////////
// Creator: Z
// Brief: Message Loop���
// Version: 1.0
// Change:
// 1.2013/3/16 Z/1.0/����

#pragma once

#include <Windows.h>
#include <atlbase.h>	// for ATL::CSimpleArray

class CZUIMgr;

// ��Ϣ���˽ӿ�
class CZMessageFilter
{
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg) = 0;
};

// Idle�ӿ�
class CZIdleHandler
{
public:
	virtual BOOL OnIdle() = 0;
};

class CZMessageLoop
{
public:
	CZMessageLoop(void);
	~CZMessageLoop(void);

	// Message filter operations
	BOOL AddMessageFilter(CZMessageFilter* pMessageFilter);
	BOOL RemoveMessageFilter(CZMessageFilter* pMessageFilter);

	// Idle handler operations
	BOOL AddIdleHandler(CZIdleHandler* pIdleHandler);
	BOOL RemoveIdleHandler(CZIdleHandler* pIdleHandler);

	int Run();

	// ZUI Manager
	CZUIMgr* CreateZUIMgr();
	VOID DestroyZUIMgr();

protected:
	BOOL PreTranslateMessage(MSG* pMsg);
	BOOL OnIdle(int nIdleCount);
	static BOOL IsIdleMessage(MSG* pMsg);

private:
	ATL::CSimpleArray<CZMessageFilter*>	m_aMsgFilter;
	ATL::CSimpleArray<CZIdleHandler*>	m_aIdleHandler;
	CZUIMgr*							m_pMgr;
};
