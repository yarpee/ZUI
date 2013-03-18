//////////////////////////////////////////////////////////////////////////
// Creator: Z
// Brief: Sync
// Version: 1.0
// Change:
// 1.2013/3/16 Z/1.0/´´½¨

#pragma once

#include <Windows.h>

class CZCriticalSection
{
public:
	CZCriticalSection(void);
	~CZCriticalSection(void);

	VOID Lock();
	VOID UnLock();

protected:
	BOOL Init();
	VOID Term();

protected:
	CRITICAL_SECTION m_cs;
};

class CZCritSecLock
{
public:
	CZCritSecLock(CZCriticalSection& cs);
	~CZCritSecLock(void);

private:
	CZCriticalSection& m_cs;
};
