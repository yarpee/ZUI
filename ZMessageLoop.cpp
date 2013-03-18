#include "ZMessageLoop.h"
#include "ZUIMgr.h"

CZMessageLoop::CZMessageLoop(void)
: m_pMgr(NULL)
{
}

CZMessageLoop::~CZMessageLoop(void)
{
	DestroyZUIMgr();
}

BOOL CZMessageLoop::AddMessageFilter(CZMessageFilter* pMessageFilter)
{
	return m_aMsgFilter.Add(pMessageFilter);
}

BOOL CZMessageLoop::RemoveMessageFilter(CZMessageFilter* pMessageFilter)
{
	return m_aMsgFilter.Remove(pMessageFilter);
}

BOOL CZMessageLoop::AddIdleHandler(CZIdleHandler* pIdleHandler)
{
	return m_aIdleHandler.Add(pIdleHandler);
}

BOOL CZMessageLoop::RemoveIdleHandler(CZIdleHandler* pIdleHandler)
{
	return m_aIdleHandler.Remove(pIdleHandler);
}

int CZMessageLoop::Run()
{
	MSG msg = {0};
	BOOL bDoIdle = TRUE;
	int nIdleCount = 0;
	do 
	{
		while(bDoIdle && !::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if(!OnIdle(nIdleCount++))
			{
				bDoIdle = FALSE;
			}
		}

		BOOL bRet = ::GetMessage(&msg, NULL, 0, 0);
		if(-1 == bRet)
		{
			// The possibility of a -1 return value means that such code can lead to fatal application errors.
			continue;
		}
		else if(!bRet)
		{
			// WM_QUIT
			break;
		}
		if(!PreTranslateMessage(&msg))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		if(IsIdleMessage(&msg))
		{
			bDoIdle = TRUE;
			nIdleCount = 0;
		}
	} while (1);
	return (int)msg.wParam;
}

CZUIMgr* CZMessageLoop::CreateZUIMgr()
{
	m_pMgr = new CZUIMgr();
	ATLASSERT(m_pMgr != NULL);
	return m_pMgr;
}

VOID CZMessageLoop::DestroyZUIMgr()
{
	if(m_pMgr != NULL)
	{
		m_pMgr->Detach();
		delete m_pMgr;
		m_pMgr = NULL;
	}
}

BOOL CZMessageLoop::PreTranslateMessage(MSG* pMsg)
{
	for(int i = m_aMsgFilter.GetSize() - 1; i >= 0; i--)
	{
		CZMessageFilter* pMessageFilter = m_aMsgFilter[i];
		if(pMessageFilter != NULL && pMessageFilter->PreTranslateMessage(pMsg))
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CZMessageLoop::OnIdle(int /*nIdleCount*/)
{
	for(int i = 0; i < m_aIdleHandler.GetSize(); i++)
	{
		CZIdleHandler* pIdleHandler = m_aIdleHandler[i];
		if(pIdleHandler != NULL)
		{
			pIdleHandler->OnIdle();
		}
	}
	return FALSE;
}

BOOL CZMessageLoop::IsIdleMessage(MSG* pMsg)
{
	// These messages should NOT cause idle processing
	switch(pMsg->message)
	{
	case WM_MOUSEMOVE:
#ifndef _WIN32_WCE
	case WM_NCMOUSEMOVE:
#endif // !_WIN32_WCE
	case WM_PAINT:
	case 0x0118:	// WM_SYSTIMER (caret blink)
		return FALSE;
	}

	return TRUE;
}
