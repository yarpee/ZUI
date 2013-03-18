//////////////////////////////////////////////////////////////////////////
// Creator: Z
// Brief: Staic
// Version: 1.0
// Change:
// 1.2013/3/17 Z/1.0/����

#pragma once

#include "ZControl.h"
#include <atlstr.h>

class CZStatic : public CZControl
{
public:
	CZStatic(void);
	~CZStatic(void);

	// ����CZControl
	virtual LPCTSTR	GetClassName();
	virtual BOOL	HandleEvent(EVENT& e);
	virtual VOID	OnPaintText(HDC hDC);

	// Attribute
	VOID	SetText(LPCTSTR lpszText);
	LPCTSTR GetText();

	VOID	SetTextColor(DWORD dwColor);
	DWORD	GetTextColor();
	
	VOID	SetTextStyle(DWORD dwStyle);
	DWORD	GetTextStyle();

protected:
	CAtlString	m_strText;	// �ı�
	DWORD		m_dwColor;	// ��ɫ
	DWORD		m_dwStyle;	// ��ʽ
};
