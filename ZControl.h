//////////////////////////////////////////////////////////////////////////
// Creator: Z
// Brief: 控件基类
// Version: 1.0
// Change:
// 1.2013/3/16 Z/1.0/创建

#pragma once

#include <Windows.h>
#include <atlstr.h>		// for CAtlString, #include <atlbase.h>
#include <atltypes.h>	// for CRect
//#include <atlbase.h>	// for ATL::CSimpleArray

typedef struct _EVENT
{
	DWORD	dwEventID;
	WPARAM	wParam;
	LPARAM	lParam;
	DWORD	dwTimestamp;
	POINT	ptMouse;
} EVENT, *PEVENT;

class CZUIMgr;

class CZControl
{
public:
	CZControl(void);
	~CZControl(void);

	// 必须调用, 一般由CZWindow调用
	VOID AttachZUIMgr(CZUIMgr* pMgr);
	CZUIMgr* DetachZUIMgr();

	// 控件类型, 必须重载
	virtual LPCTSTR GetClassName();

	// 控件名, 唯一标识
	VOID SetName(LPCTSTR lpszName);
	LPCTSTR GetName();

	// Parent
	VOID SetParent(CZControl* pParent);
	const CZControl* GetParent();

	// Size
	VOID SetSize(RECT& rcSize);
	const RECT& GetSize();

	// Visible
	VOID SetVisible(BOOL bVisible);
	BOOL IsVisible();

	// 事件处理函数
	virtual BOOL HandleEvent(EVENT& e);

	// 绘制
	VOID Invalidate();
	virtual VOID OnPaint(HDC hDC, RECT& rc);
	virtual VOID OnPaintStateImage(HDC hDC);
	virtual VOID OnPaintText(HDC hDC);

protected:
	CZUIMgr*						m_pZUIMgr;	// ZUI Mgr
	CZControl*						m_pParent;	// 父控件
	ATL::CSimpleArray<CZControl*>	m_aChild;	// 子控件
	CAtlString						m_strName;	// 控件名
	CRect							m_rcSize;	// 控件位置、大小
	BOOL							m_bVisible;	// 是否可见
};
