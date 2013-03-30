#include "ZGlobal.h"
#include "ZAppModule.h"
#include "ZMessageLoop.h"
#include "ZUIMgr.h"
#include "ZWindow.h"

CZAppModule g_theApp;
CZMessageLoop g_theLoop;

//////////////////////////////////////////////////////////////////////////
// Application Module
BOOL InitAppModule(HINSTANCE hInstance)
{
	return g_theApp.Init(hInstance);	// TODO: Call Term()
}

// CZWindow�����ڴ�
HINSTANCE GetInstance()
{
	return g_theApp.GetInstance();
}

//////////////////////////////////////////////////////////////////////////
// Message Loop
int MessageLoop()
{
	int nRet = g_theLoop.Run();
	g_theLoop.DestroyZUIMgr();
	return nRet;
}

BOOL InitZUIMessageLoop(CZWindow* pWindow)
{
	BOOL bRet = FALSE;
	if(pWindow != NULL)
	{
		CZUIMgr* pMgr = g_theLoop.CreateZUIMgr();
		ATLASSERT(pMgr != NULL);
		if(pMgr != NULL)
		{
			pMgr->Attach(pWindow);
			bRet = TRUE;
		}
	}
	return bRet;
}
