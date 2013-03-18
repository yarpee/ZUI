//////////////////////////////////////////////////////////////////////////
// Creator: Z
// Brief: Button
// Version: 1.0
// Change:
// 1.2013/3/17 Z/1.0/¥¥Ω®

#pragma once

#include "ZStatic.h"

#define BS_NORMAL	0
#define BS_HOVER	1
#define BS_PUSH		2
#define BS_FOCUS	3
#define BS_DISABLE	4
#define BS_MAX		5

class CZButton : public CZStatic
{
public:
	CZButton(void);
	~CZButton(void);

	// ÷ÿ‘ÿCZControl
	virtual LPCTSTR	GetClassName();
	virtual BOOL	HandleEvent(EVENT& e);
	virtual VOID	OnPaintStateImage(HDC hDC);

protected:
	DWORD m_dwState;
	CAtlString m_aStateImage[BS_MAX];
};
