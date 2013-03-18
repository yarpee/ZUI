#include "ZControl.h"
#include "ZUIMgr.h"

#define CONTROL_CLASS_NAME _T("ZUI Control Class")

CZControl::CZControl(void)
: m_pZUIMgr(NULL)
, m_pParent(NULL)
, m_bVisible(TRUE)
{
}

CZControl::~CZControl(void)
{
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

VOID CZControl::SetSize(RECT& rcSize)
{
	m_rcSize = rcSize;
}

const RECT& CZControl::GetSize()
{
	return m_rcSize;
}

VOID CZControl::SetVisible(BOOL bVisible)
{
	m_bVisible = bVisible;
}

BOOL CZControl::IsVisible()
{
	return m_bVisible;
}

BOOL CZControl::HandleEvent(EVENT& e)
{
	return FALSE;
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
	CRect rcPaint;
	if(::IntersectRect(&rcPaint, &rc, &m_rcSize))
	{
		// TODO: ªÊ÷∆À≥–Ú
		OnPaintStateImage(hDC);
		OnPaintText(hDC);
	}
}

VOID CZControl::OnPaintStateImage(HDC hDC)
{
}

VOID CZControl::OnPaintText(HDC hDC)
{
}
