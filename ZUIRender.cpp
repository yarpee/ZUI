#include "ZUIRender.h"
#include "ZDef.h"

extern "C"
{
	extern unsigned char *stbi_load_from_memory(unsigned char const *buffer, int len, int *x, int *y, int *comp, int req_comp);
	extern void stbi_image_free(void *retval_from_stbi_load);
};

CZUIRender::CZUIRender(void)
{
}

CZUIRender::~CZUIRender(void)
{
}

HBITMAP CZUIRender::LoadImage(LPCTSTR lpszPath)
{
	HBITMAP hBmp = NULL;
	do 
	{
		if(NULL == lpszPath)
		{
			break;
		}

		HANDLE hFile = ::CreateFile(lpszPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if(INVALID_HANDLE_VALUE == hFile)
		{
			break;
		}

		DWORD dwSize = ::GetFileSize(hFile, NULL);
		if(0 == dwSize)
		{
			CloseHandle(hFile);
			break;
		}

		BYTE* pData = new BYTE[dwSize];
		if(NULL == pData)
		{
			CloseHandle(hFile);
			break;
		}

		DWORD dwRead = 0;
		::ReadFile(hFile, pData, dwSize, &dwRead, NULL);
		if(dwRead != dwSize)
		{
			delete [] pData;
			CloseHandle(hFile);
			break;
		}
		CloseHandle(hFile);

		int x, y, comp;
		BYTE* pImage = stbi_load_from_memory(pData, dwSize, &x, &y, &comp, 4);
		delete [] pData;
		if(NULL == pImage)
		{
			break;
		}

		BITMAPINFO bmi;
		::ZeroMemory(&bmi, sizeof(BITMAPINFO));
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = x;
		bmi.bmiHeader.biHeight = -y;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32;
		bmi.bmiHeader.biCompression = BI_RGB;
		bmi.bmiHeader.biSizeImage = x * y * 4;
		BYTE* pDest = NULL;
		hBmp = ::CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void**)&pDest, NULL, 0);
		if(NULL == hBmp)
		{
			stbi_image_free(pImage);
			break;
		}
		for(int i = 0; i < x * y; i++) 
		{
			pDest[i * 4 + 3] = pImage[i * 4 + 3];
			if(pDest[i * 4 + 3] < 255)
			{
				pDest[i * 4] = (BYTE)(DWORD(pImage[i * 4 + 2]) * pImage[i * 4 + 3] / 255);
				pDest[i * 4 + 1] = (BYTE)(DWORD(pImage[i * 4 + 1]) * pImage[i * 4 + 3] / 255);
				pDest[i * 4 + 2] = (BYTE)(DWORD(pImage[i * 4]) * pImage[i * 4 + 3] / 255); 
			}
			else
			{
				pDest[i * 4] = pImage[i * 4 + 2];
				pDest[i * 4 + 1] = pImage[i * 4 + 1];
				pDest[i * 4 + 2] = pImage[i * 4]; 
			}
		}
		stbi_image_free(pImage);
	} while (0);
	return hBmp;
}

VOID CZUIRender::FreeImage(HBITMAP hBmp)
{
	if(hBmp != NULL)
	{
		::DeleteObject(hBmp);
	}
}

VOID CZUIRender::DrawText(HDC hDC, LPCTSTR lpszText, DWORD dwColor, DWORD dwStyle, RECT& rc)
{
	if(lpszText != NULL)
	{
		// TODO: 字体
		::SetBkMode(hDC, TRANSPARENT);
		::SetTextColor(hDC, RGB(GetBValue(dwColor), GetGValue(dwColor), GetRValue(dwColor)));
		::DrawText(hDC, lpszText, -1, &rc, dwStyle);
	}
}

VOID CZUIRender::DrawRect(HDC hDC, RECT& rc, DWORD dwBorderSize, DWORD dwBorderColor, SIZE* pxyBorderRound /* = NULL */)
{
	HPEN hPen = ::CreatePen(PS_SOLID | PS_INSIDEFRAME, dwBorderSize, RGB(GetBValue(dwBorderColor), GetGValue(dwBorderColor), GetRValue(dwBorderColor)));
	if(hPen != NULL)
	{
		HPEN hOldPen = (HPEN)::SelectObject(hDC, hPen);
		::SelectObject(hDC, ::GetStockObject(NULL_BRUSH));	// 画刷选用空画刷, 即不实心
		if(pxyBorderRound != NULL)
		{
			// 圆角矩形
			::RoundRect(hDC, rc.left, rc.top, rc.right, rc.bottom, pxyBorderRound->cx, pxyBorderRound->cy);
		}
		else
		{
			::Rectangle(hDC, rc.left, rc.top, rc.right, rc.bottom);
		}
		::SelectObject(hDC, hOldPen);
		::DeleteObject(hPen);
	}
}

VOID CZUIRender::DrawImage(HDC hDC, LPCTSTR lpszPath, RECT& rcSize, RECT& rcPaint)
{
	HBITMAP hBmp = NULL;
	HDC hMemDC = NULL;
	do 
	{
		if(NULL == lpszPath)
		{
			break;
		}

		hBmp = LoadImage(lpszPath);
		if(NULL == hBmp)
		{
			break;
		}

		hMemDC = ::CreateCompatibleDC(hDC);
		if(NULL == hMemDC)
		{
			break;
		}

		HBITMAP hOldBmp = (HBITMAP)::SelectObject(hMemDC, hBmp);

		// 
		RECT rc = {0};
		if((rcSize.left <= rcPaint.left) || (rcSize.top <= rcPaint.top))
		{
			rc.left = rcPaint.left;
			rc.top = rcPaint.top;
		}
		else
		{
			rc.left = rcSize.left;
			rc.top = rcSize.top;
		}
		rc.right = min(rcSize.right, rcPaint.right);
		rc.bottom = min(rcSize.bottom, rcPaint.bottom);

		::BitBlt(hDC, rc.left, rc.top, GetRectWidth(rc), GetRectHeight(rc), hMemDC, 0, 0, SRCCOPY);
		::SelectObject(hMemDC, hOldBmp);
	} while (0);
	if(hMemDC != NULL)
	{
		::DeleteDC(hMemDC);
	}
	if(hBmp != NULL)
	{
		FreeImage(hBmp);
	}
}
