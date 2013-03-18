#include "ZUIRender.h"

CZUIRender::CZUIRender(void)
{
}

CZUIRender::~CZUIRender(void)
{
}

VOID CZUIRender::DrawText(HDC hDC, LPCTSTR lpszText, DWORD dwColor, DWORD dwStyle, RECT& rc)
{
	if(lpszText != NULL)
	{
		// TODO: ×ÖÌå
		::SetBkMode(hDC, TRANSPARENT);
		::SetTextColor(hDC, RGB(GetRValue(dwColor), GetGValue(dwColor), GetBValue(dwColor)));
		::DrawText(hDC, lpszText, -1, &rc, dwStyle);
	}
}
