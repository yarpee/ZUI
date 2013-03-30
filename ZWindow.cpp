#include "ZWindow.h"
#include "ZGlobal.h"
#include "ZUIMgr.h"
#include "ZControl.h"
#include <tchar.h>
#include <atldef.h>	// for ATLASSERT

#define Z_WINDOW_CLASS_NAME	_T("ZUI Window Class")
#define Z_WINDOW_NAME		_T("ZUI Window")

CZWindow::CZWindow(void)
: m_hWnd(NULL)
, m_pZUIMgr(NULL)
, m_pRootCtrl(NULL)
{
}

CZWindow::~CZWindow(void)
{
	DetachZUIMgr();
}

CZWindow::operator HWND() const
{
	return m_hWnd;
}

VOID CZWindow::AttachZUIMgr(CZUIMgr* pMgr)
{
	ATLASSERT(pMgr != NULL);
	m_pZUIMgr = pMgr;
	ATLASSERT(NULL == m_pRootCtrl);
	m_pRootCtrl = new CZControl();
	if(m_pRootCtrl != NULL)
	{
		m_pRootCtrl->AttachZUIMgr(pMgr);
		RECT rc = {0};
		::GetClientRect(m_hWnd, &rc);
		m_pRootCtrl->SetSize(rc);
	}
}

CZUIMgr* CZWindow::DetachZUIMgr()
{
	if(m_pRootCtrl != NULL)
	{
		m_pRootCtrl->DetachZUIMgr();
		delete m_pRootCtrl;
		m_pRootCtrl = NULL;
	}
	CZUIMgr* pMgr = m_pZUIMgr;
	m_pZUIMgr = NULL;
	return pMgr;
}

CZControl* CZWindow::GetRootControl()
{
	return m_pRootCtrl;
}

BOOL CZWindow::RegisterWindowClass()
{
	WNDCLASSEX wcex;
	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= GetClassStyle();
	wcex.lpfnWndProc	= CZWindow::WindowProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= GetInstance();
	wcex.hIcon			= GetClassIcon(FALSE);
	wcex.hCursor		= GetClassCursor();
	wcex.hbrBackground	= GetClassBackground();
	wcex.lpszMenuName	= GetClassMenuName();
	wcex.lpszClassName	= GetWindowClassName();
	wcex.hIconSm		= GetClassIcon(TRUE);
	ATOM ret = ::RegisterClassEx(&wcex);
	return ret != 0;
}

UINT CZWindow::GetClassStyle()
{
	return CS_HREDRAW | CS_VREDRAW;
}

HICON CZWindow::GetClassIcon(BOOL bSmall)
{
	return NULL;
}

HCURSOR CZWindow::GetClassCursor()
{
	return ::LoadCursor(NULL, IDC_ARROW);
}

HBRUSH CZWindow::GetClassBackground()
{
	return (HBRUSH)(COLOR_WINDOW + 1);
}

LPCTSTR CZWindow::GetClassMenuName()
{
	return NULL;
}

LPCTSTR CZWindow::GetWindowClassName()
{
	return Z_WINDOW_CLASS_NAME;
}

//#ifdef CreateWindow
//#pragma push_macro("CreateWindow")
//#undef CreateWindow
//HWND CZWindow::CreateWindow(DWORD dwStyle, 
HWND CZWindow::CreateZWindow(DWORD dwStyle, 
	DWORD dwExStyle, 
	RECT& rc, 
	LPCTSTR lpWindowName, 
	HWND hWndParent, 
	HMENU hMenu)
//#pragma pop_macro("CreateWindow")
//#endif
{
	if(NULL == lpWindowName)
	{
		lpWindowName = Z_WINDOW_NAME;
	}
	::CreateWindowEx(
		dwExStyle, 
		GetWindowClassName(), 
		lpWindowName, 
		dwStyle, 
		rc.left, 
		rc.top, 
		GetRectWidth(rc), 
		GetRectHeight(rc), 
		hWndParent, 
		hMenu, 
		GetInstance(), 
		this);
	return m_hWnd;	// m_hWnd��WM_NCCREATE������ȷ����
}

VOID CZWindow::ShowWindow(BOOL bShow /* = TRUE */, BOOL bFocus /* = TRUE */)
{
	ATLASSERT(::IsWindow(m_hWnd));
	::ShowWindow(m_hWnd, bShow ? (bFocus ? SW_NORMAL : SW_SHOWNOACTIVATE) : SW_HIDE);
}

#pragma warning(push)
#pragma warning(disable:4244)
#pragma warning(disable:4312)
LRESULT CZWindow::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CZWindow* pThis = NULL;
	LRESULT lRes = -1;
	BOOL bHandled = FALSE;

	switch(uMsg)
	{
	case WM_NCCREATE:
		{
			LPCREATESTRUCT lpCreateStruct = (LPCREATESTRUCT)lParam;
			pThis = (CZWindow*)(lpCreateStruct->lpCreateParams);
			ATLASSERT(pThis != NULL);
			pThis->m_hWnd = hWnd;	// m_hWnd��Ҫ�ڴ�����, ����HandleMessage��ʹ��m_hWnd����ȷ.
			::SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);
		}
		break;
	default:
		{
			// TODO: ����WM_NCDESTROY��Ϣ
			pThis = (CZWindow*)::GetWindowLongPtr(hWnd, GWLP_USERDATA);
		}
		break;
	}

	// �洰���ȴ���, ��DUI����Ϣ�ڴ˴���
	// WM_GETMINMAXINFO��WM_NCCREATE֮ǰ, pThis�п���ΪNULL
	if(pThis != NULL)
	{
		lRes = pThis->HandleMessage(uMsg, wParam, lParam, bHandled);

		// DUI��Ϣ�ڴ˴���
		if(!bHandled && pThis->m_pZUIMgr != NULL)
		{
			lRes = pThis->m_pZUIMgr->HandleMessage(uMsg, wParam, lParam, bHandled);
		}
	}

	// ����Ĭ�ϴ���
	if(!bHandled)
	{
		lRes = ::DefWindowProc(hWnd, uMsg, wParam, lParam);	// ʹ��hWnd����m_hWnd, ��Ϊm_hWnd�����Ѿ��ÿ�.
	}

	return lRes;
}
#pragma warning(pop)

LRESULT CZWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}
