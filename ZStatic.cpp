#include "ZStatic.h"
#include "ZUIRender.h"

#define STATIC_CLASS_NAME _T("ZUI Static Class")

CZStatic::CZStatic(void)
: m_dwColor(0)
, m_dwTextStyle(DT_CENTER)
{
}

CZStatic::~CZStatic(void)
{
}

LPCTSTR CZStatic::GetClassName()
{
	return STATIC_CLASS_NAME;
}

BOOL CZStatic::HandleEvent(EVENT& e)
{
	return CZControl::HandleEvent(e);
}

VOID CZStatic::OnPaintText(HDC hDC)
{
	CZUIRender::DrawText(hDC, m_strText, m_dwColor, m_dwTextStyle, m_rcSize);
}

VOID CZStatic::SetText(LPCTSTR lpszText)
{
	ATLASSERT(lpszText != NULL);
	m_strText = lpszText;
}

LPCTSTR CZStatic::GetText()
{
	return m_strText;
}

VOID CZStatic::SetTextColor(DWORD dwColor)
{
	m_dwColor = dwColor;
}

DWORD CZStatic::GetTextColor()
{
	return m_dwColor;
}

VOID CZStatic::SetTextStyle(DWORD dwStyle)
{
	m_dwTextStyle = dwStyle;
}

DWORD CZStatic::GetTextStyle()
{
	return m_dwTextStyle;
}
