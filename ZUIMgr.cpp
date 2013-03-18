#include "ZUIMgr.h"
#include "ZGlobal.h"
#include "ZWindow.h"
#include "ZControl.h"
#include <atldef.h>

CZUIMgr::CZUIMgr(void)
: m_pWindow(NULL)
, m_hPaintDC(NULL)
, m_hOffscreenDC(NULL)
, m_hOffscreenBmp(NULL)
, m_hBackgroundDC(NULL)
, m_hBackgroundBmp(NULL)
{
}

CZUIMgr::~CZUIMgr(void)
{
}

VOID CZUIMgr::Attach(CZWindow* pWindow)
{
	ATLASSERT(pWindow != NULL && ::IsWindow(*pWindow));
	m_pWindow = pWindow;
	m_hPaintDC = ::GetDC(*m_pWindow);
	ATLASSERT(m_hPaintDC != NULL);
	m_pWindow->AttachZUIMgr(this);
}

CZWindow* CZUIMgr::Detach()
{
	if(m_pWindow != NULL)
	{
		m_pWindow->DetachZUIMgr();
	}

	if(m_hPaintDC != NULL)
	{
		::ReleaseDC(*m_pWindow, m_hPaintDC);
		m_hPaintDC = NULL;
	}

	if(m_hOffscreenDC != NULL)
	{
		::DeleteDC(m_hOffscreenDC);
		m_hOffscreenDC = NULL;
	}

	if(m_hOffscreenBmp != NULL)
	{
		::DeleteObject(m_hOffscreenBmp);
		m_hOffscreenBmp = NULL;
	}

	if(m_hBackgroundDC != NULL)
	{
		::DeleteDC(m_hBackgroundDC);
		m_hBackgroundDC = NULL;
	}

	if(m_hBackgroundBmp != NULL)
	{
		::DeleteObject(m_hBackgroundBmp);
		m_hBackgroundBmp = NULL;
	}

	CZWindow* pWindow = m_pWindow;
	m_pWindow = NULL;
	return pWindow;
}

LRESULT CZUIMgr::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATLASSERT(m_pWindow != NULL && ::IsWindow(*m_pWindow));

	bHandled = FALSE;

	switch(uMsg)
	{
	case WM_PAINT:
		{
			bHandled = OnPaint();
		}
		break;
	default:
		{

		}
		break;
	}

	return 0;
}

BOOL CZUIMgr::OnPaint()
{
	BOOL bHandled = FALSE;
	CZControl* pRootCtrl = m_pWindow->GetRootControl();
	if(pRootCtrl != NULL)
	{
		RECT rcUpdate = {0};
		if(::GetUpdateRect(*m_pWindow, &rcUpdate, FALSE))
		{
			PAINTSTRUCT ps = {0};
			::BeginPaint(*m_pWindow, &ps);

			// 创建离屏DC和Bmp
			if(NULL == m_hOffscreenDC)
			{
				RECT rcClient = {0};
				::GetClientRect(*m_pWindow, &rcClient);
				m_hOffscreenDC = ::CreateCompatibleDC(m_hPaintDC);
				m_hOffscreenBmp = ::CreateCompatibleBitmap(m_hPaintDC, 
					GetRectWidth(rcClient), 
					GetRectHeight(rcClient));
				ATLASSERT(m_hOffscreenDC != NULL && m_hOffscreenBmp != NULL);
			}

			// 关联离屏DC和Bmp
			HBITMAP hOldBmp = (HBITMAP)::SelectObject(m_hOffscreenDC, m_hOffscreenBmp);
			int nIndex = ::SaveDC(m_hOffscreenDC);

			// 创建背景DC和Bmp并关联, BitBlt ps.hdc到m_hBackgroundDC
			if(NULL == m_hBackgroundDC)
			{
				RECT rcClient = {0};
				::GetClientRect(*m_pWindow, &rcClient);
				m_hBackgroundDC = ::CreateCompatibleDC(m_hPaintDC);
				m_hBackgroundBmp = ::CreateCompatibleBitmap(m_hPaintDC, 
					GetRectWidth(rcClient), 
					GetRectHeight(rcClient));
				ATLASSERT(m_hBackgroundDC != NULL && m_hBackgroundBmp != NULL);
				::SelectObject(m_hBackgroundDC, m_hBackgroundBmp);
				::BitBlt(m_hBackgroundDC, 
					ps.rcPaint.left, 
					ps.rcPaint.top, 
					GetRectWidth(ps.rcPaint), 
					GetRectHeight(ps.rcPaint), 
					ps.hdc, 
					ps.rcPaint.left, 
					ps.rcPaint.top, 
					SRCCOPY);
			}
			else
			{
				//::SelectObject(m_hBackgroundDC, m_hBackgroundBmp);
			}

			// BitBlt m_hBackgroundDC到m_hOffscreenDC
			::BitBlt(m_hOffscreenDC, 
				ps.rcPaint.left, 
				ps.rcPaint.top, 
				GetRectWidth(ps.rcPaint), 
				GetRectHeight(ps.rcPaint), 
				m_hBackgroundDC, 
				ps.rcPaint.left, 
				ps.rcPaint.top, 
				SRCCOPY);

			// 各控件绘制
			pRootCtrl->OnPaint(m_hOffscreenDC, ps.rcPaint);

			// BitBlt m_hOffscreenDC到ps.hdc
			::RestoreDC(m_hOffscreenDC, nIndex);
			::BitBlt(ps.hdc, 
				ps.rcPaint.left, 
				ps.rcPaint.top, 
				GetRectWidth(ps.rcPaint), 
				GetRectHeight(ps.rcPaint), 
				m_hOffscreenDC, 
				ps.rcPaint.left, 
				ps.rcPaint.top, 
				SRCCOPY);
			::SelectObject(m_hOffscreenDC, hOldBmp);

			::EndPaint(*m_pWindow, &ps);

			bHandled = TRUE;
		}
	}
	return bHandled;
}

VOID CZUIMgr::InvalidateRect(RECT& rc, BOOL bEraseBG /* = FALSE */)
{
	ATLASSERT(m_pWindow != NULL && ::IsWindow(*m_pWindow));
	::InvalidateRect(*m_pWindow, &rc, bEraseBG);
}
