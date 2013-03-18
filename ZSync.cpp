#include "ZSync.h"

//////////////////////////////////////////////////////////////////////////
// CZCriticalSection
CZCriticalSection::CZCriticalSection(void)
{
	memset(&m_cs, 0, sizeof(m_cs));
	Init();
}

CZCriticalSection::~CZCriticalSection(void)
{
	Term();
}

VOID CZCriticalSection::Lock()
{
	EnterCriticalSection(&m_cs);
}

VOID CZCriticalSection::UnLock()
{
	LeaveCriticalSection(&m_cs);
}

BOOL CZCriticalSection::Init()
{
	BOOL bRet = TRUE;

	// Windows Server 2003 and Windows XP:  In low memory situations, 
	// InitializeCriticalSection can raise a STATUS_NO_MEMORY exception. 
	// This exception was eliminated starting with Windows Vista.
	__try
	{
		InitializeCriticalSection(&m_cs);
	}
	__except(STATUS_NO_MEMORY == GetExceptionCode())
	{
		bRet = FALSE;
	}

	return bRet;
}

VOID CZCriticalSection::Term()
{
	DeleteCriticalSection(&m_cs);
}

//////////////////////////////////////////////////////////////////////////
// CZCritSecLock
CZCritSecLock::CZCritSecLock(CZCriticalSection& cs)
: m_cs(cs)
{
	m_cs.Lock();
}

CZCritSecLock::~CZCritSecLock()
{
	m_cs.UnLock();
}
