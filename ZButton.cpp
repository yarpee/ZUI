#include "ZButton.h"

#define BUTTON_CLASS_NAME _T("ZUI Button Class")

CZButton::CZButton(void)
: m_dwState(BS_NORMAL)
{
	m_dwStyle = DT_SINGLELINE | DT_VCENTER | DT_CENTER;
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
	return FALSE;
}

VOID CZButton::OnPaintStateImage(HDC hDC)
{
	if(!m_aStateImage[m_dwState].IsEmpty())
	{

	}
}
