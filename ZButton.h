//////////////////////////////////////////////////////////////////////////
// Creator: Z
// Brief: Button
// Version: 1.0
// Change:
// 1.2013/3/17 Z/1.0/����

#pragma once

#include "ZStatic.h"

class CZButton : public CZStatic
{
public:
	CZButton(void);
	~CZButton(void);

	// ����CZControl
	virtual LPCTSTR	GetClassName();
	virtual BOOL	HandleEvent(EVENT& e);
	virtual VOID	OnPaintStateImage(HDC hDC);

	VOID SetStateImage(DWORD dwState, LPCTSTR lpszPath);

protected:
	DWORD m_dwState;
	CAtlString m_strNormalImage;
	CAtlString m_strHoverImage;
	CAtlString m_strPushImage;
	CAtlString m_strFocusImage;
	CAtlString m_strDisableImage;
};
