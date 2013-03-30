#include "ZControl.h"
#include "ZUIMgr.h"
#include "ZUIRender.h"

#define CONTROL_CLASS_NAME _T("ZUI Control Class")

CZControl::CZControl(void)
: m_pZUIMgr(NULL)
, m_pParent(NULL)
, m_bVisible(TRUE)
, m_bEnable(TRUE)
, m_bFocus(FALSE)
, m_dwBorderSize(0)
, m_dwBorderColor(0)
, m_dwBorderFocusColor(0)
{
}

CZControl::~CZControl(void)
{
	DetachZUIMgr();
}

VOID CZControl::AttachZUIMgr(CZUIMgr* pMgr)
{
	ATLASSERT(pMgr != NULL);
	m_pZUIMgr = pMgr;
}

CZUIMgr* CZControl::DetachZUIMgr()
{
	CZUIMgr* pMgr = m_pZUIMgr;
	m_pZUIMgr = NULL;
	return pMgr;
}

LPCTSTR CZControl::GetClassName()
{
	return CONTROL_CLASS_NAME;
}

VOID CZControl::SetName(LPCTSTR lpszName)
{
	m_strName = lpszName;
}

LPCTSTR CZControl::GetName()
{
	return m_strName;
}

VOID CZControl::SetParent(CZControl* pParent)
{
	m_pParent = pParent;
}

const CZControl* CZControl::GetParent()
{
	return m_pParent;
}

VOID CZControl::AddChild(CZControl* pChild)
{
	if(pChild != NULL)
	{
		pChild->AttachZUIMgr(m_pZUIMgr);
		m_aChild.Add(pChild);
	}
}

VOID CZControl::SetSize(RECT& rcSize)
{
	m_rcSize = rcSize;
}

const RECT& CZControl::GetSize()
{
	return m_rcSize;
}

VOID CZControl::SetPadding(RECT& rcPadding)
{
	m_rcPadding = rcPadding;
}

const RECT& CZControl::GetPadding()
{
	return m_rcPadding;
}

VOID CZControl::SetVisible(BOOL bVisible /* = TRUE */)
{
	m_bVisible = bVisible;
}

BOOL CZControl::IsVisible()
{
	return m_bVisible;
}

VOID CZControl::SetEnable(BOOL bEnable /* = TRUE */)
{
	m_bEnable = bEnable;
}

BOOL CZControl::IsEnable()
{
	return m_bEnable;
}

VOID CZControl::SetFocus(BOOL bFocus /* = TRUE */)
{
	m_bFocus = bFocus;
}

BOOL CZControl::IsFocus()
{
	return m_bFocus;
}

VOID CZControl::SetTooltip(LPCTSTR lpszTooltip)
{
	m_strTooltip = lpszTooltip;
}

LPCTSTR CZControl::GetTooltip()
{
	return m_strTooltip;
}

VOID CZControl::SetBorderSize(DWORD dwSize)
{
	m_dwBorderSize = dwSize;
}

VOID CZControl::SetBorderRound(SIZE& xyRound)
{
	m_xyBorderRound = xyRound;
}

VOID CZControl::SetBorderColor(DWORD dwColor)
{
	m_dwBorderColor = dwColor;
}

VOID CZControl::SetBorderFocusColor(DWORD dwColor)
{
	m_dwBorderFocusColor = dwColor;
}

BOOL CZControl::HandleEvent(EVENT& e)
{
	BOOL bHandled = TRUE;
	switch(e.dwEventID)
	{
	case E_SETFOCUS:
		m_bFocus = TRUE;
		break;
	case E_KILLFOCUS:
		m_bFocus = FALSE;
		break;
	default:
		bHandled = FALSE;
		break;
	}
	if(bHandled)
	{
		Invalidate();
	}
	return bHandled;
}

VOID CZControl::SendNotify(DWORD dwNotifyID)
{
	ATLASSERT(m_pZUIMgr != NULL);
	if(m_pZUIMgr != NULL)
	{
		NOTIFY n = {0};
		n.dwNotifyID = dwNotifyID;
		n.dwTimestamp = ::GetTickCount();
		n.pCtrl = this;
		m_pZUIMgr->Notify(n);
	}
}

VOID CZControl::Invalidate()
{
	ATLASSERT(m_pZUIMgr);

	if(IsVisible())
	{
		m_pZUIMgr->InvalidateRect(m_rcSize);
	}
}

VOID CZControl::OnPaint(HDC hDC, RECT& rc)
{
	if(IsVisible() && ::IntersectRect(&m_rcPaint, &rc, &m_rcSize))
	{
		// TODO: ªÊ÷∆À≥–Ú
		OnPaintStateImage(hDC);
		OnPaintText(hDC);
		OnPaintBorder(hDC);
		for(int i = 0; i < m_aChild.GetSize(); ++i)
		{
			if(m_aChild[i] != NULL)
			{
				m_aChild[i]->OnPaint(hDC, rc);
			}
		}
	}
}

VOID CZControl::OnPaintStateImage(HDC hDC)
{
}

VOID CZControl::OnPaintText(HDC hDC)
{
}

VOID CZControl::OnPaintBorder(HDC hDC)
{
	if(m_dwBorderSize > 0)
	{
		if(m_xyBorderRound.cx > 0 || m_xyBorderRound.cy > 0)
		{
			// ‘≤Ω«
			if(IsFocus())
			{
				if(m_dwBorderFocusColor != 0)
				{
					// Draw Focus
					CZUIRender::DrawRect(hDC, m_rcSize, m_dwBorderSize, m_dwBorderFocusColor, &m_xyBorderRound);
				}
			}
			else
			{
				if(m_dwBorderColor != 0)
				{
					// Draw Normal
					CZUIRender::DrawRect(hDC, m_rcSize, m_dwBorderSize, m_dwBorderColor, &m_xyBorderRound);
				}
			}
		}
		else
		{
			if(IsFocus())
			{
				if(m_dwBorderFocusColor != 0)
				{
					// Draw Foucs
					CZUIRender::DrawRect(hDC, m_rcSize, m_dwBorderSize, m_dwBorderFocusColor);
				}
			}
			else
			{
				if(m_dwBorderColor != 0)
				{
					// Draw Normal
					CZUIRender::DrawRect(hDC, m_rcSize, m_dwBorderSize, m_dwBorderColor);
				}
			}
		}
	}
}

CZControl* CZControl::FindControl(POINT& pt)
{
	for(int i = 0; i < m_aChild.GetSize(); ++i)
	{
		if(m_aChild[i] != NULL)
		{
			CZControl* pCtrl = NULL;
			if((pCtrl = m_aChild[i]->FindControl(pt)) != NULL)
			{
				return pCtrl;
			}
		}
	}
	if(IsVisible() && ::PtInRect(&m_rcSize, pt))
	{
		return this;
	}
	return NULL;
}
