#include "ZButton.h"
#include "ZUIRender.h"

#define BUTTON_CLASS_NAME _T("ZUI Button Class")

CZButton::CZButton(void)
: m_dwState(ST_NORMAL)
{
	m_dwTextStyle = DT_SINGLELINE | DT_CENTER | DT_VCENTER;
}

CZButton::~CZButton(void)
{
}

LPCTSTR CZButton::GetClassName()
{
	return BUTTON_CLASS_NAME;
}

BOOL CZButton::HandleEvent(EVENT& e)
{
	BOOL bHandled = TRUE;
	switch(e.dwEventID)
	{
	case E_MOUSEMOVE:
		if(IsEnable())
		{
			m_dwState |= ST_HOVER;
			Invalidate();
		}
		break;
	case E_MOUSELEAVE:
		if(IsEnable())
		{
			m_dwState &= ~ST_HOVER;
			Invalidate();
		}
		break;
	case E_LBUTTONDOWN:
		if(IsEnable())
		{
			m_dwState |= ST_PUSH;
			Invalidate();
		}
		break;
	case E_LBUTTONUP:
		if(IsEnable())
		{
			m_dwState &= ~ST_PUSH;
			Invalidate();
			SendNotify(N_CLICK);	// Í¨Öªµã»÷
		}
		break;
	default:
		bHandled = FALSE;
		break;
	}
	CZStatic::HandleEvent(e);
	return bHandled;
}

VOID CZButton::OnPaintStateImage(HDC hDC)
{
	// ST_DISABLE
	if(!IsEnable())
	{
		m_dwState |= ST_DISABLE;
	}
	else
	{
		m_dwState &= ~ST_DISABLE;
	}

	// ST_FOCUS
	if(IsFocus())
	{
		m_dwState |= ST_FOCUS;
	}
	else
	{
		m_dwState &= ~ST_FOCUS;
	}

	// Ë³Ðò£ºST_DISABLE¡¢ST_PUSH¡¢ST_HOVER¡¢ST_FOCUS¡¢ST_NORMAL
	CAtlString strImage;
	if(m_dwState & ST_DISABLE)
	{
		strImage = m_strDisableImage;
	}
	else if(m_dwState & ST_PUSH)
	{
		strImage = m_strPushImage;
	}
	else if(m_dwState & ST_HOVER)
	{
		strImage = m_strHoverImage;
	}
	else if(m_dwState & ST_FOCUS)
	{
		strImage = m_strFocusImage;
	}
	else
	{
		strImage = m_strNormalImage;
	}
	if(!strImage.IsEmpty())
	{
		CZUIRender::DrawImage(hDC, strImage, m_rcSize, m_rcPaint);
	}
}

VOID CZButton::SetStateImage(DWORD dwState, LPCTSTR lpszPath)
{
	switch(dwState)
	{
	case ST_NORMAL:
		m_strNormalImage = lpszPath;
		break;
	case ST_HOVER:
		m_strHoverImage = lpszPath;
		break;
	case ST_PUSH:
		m_strPushImage = lpszPath;
		break;
	case ST_FOCUS:
		m_strFocusImage = lpszPath;
		break;
	case ST_DISABLE:
		m_strDisableImage = lpszPath;
		break;
	default:
		break;
	}
}
