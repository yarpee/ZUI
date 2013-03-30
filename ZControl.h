//////////////////////////////////////////////////////////////////////////
// Creator: Z
// Brief: 控件基类
// Version: 1.0
// Change:
// 1.2013/3/16 Z/1.0/创建

#pragma once

#include "ZDef.h"
#include "ZGlobal.h"
#include <atlstr.h>		// for CAtlString
#include <atltypes.h>	// for CRect

class CZUIMgr;

class CZControl
{
public:
	CZControl(void);
	~CZControl(void);

	// DUI必须调用, 由CZWindow和AddChild调用
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

	// Children
	VOID AddChild(CZControl* pChild);

	// Size
	VOID SetSize(RECT& rcSize);
	const RECT& GetSize();

	// Padding
	VOID SetPadding(RECT& rcPadding);
	const RECT& GetPadding();

	// Visible
	VOID SetVisible(BOOL bVisible = TRUE);
	BOOL IsVisible();

	// Enable
	VOID SetEnable(BOOL bEnable = TRUE);
	BOOL IsEnable();

	// Focus
	VOID SetFocus(BOOL bFocus = TRUE);
	BOOL IsFocus();

	// Tooltip
	VOID SetTooltip(LPCTSTR lpszTooltip);
	LPCTSTR GetTooltip();

	// Border
	VOID SetBorderSize(DWORD dwSize);
	VOID SetBorderRound(SIZE& xyRound);
	VOID SetBorderColor(DWORD dwColor);
	VOID SetBorderFocusColor(DWORD dwColor);

	// 事件处理函数
	virtual BOOL HandleEvent(EVENT& e);
	
	// Notify
	VOID SendNotify(DWORD dwNotifyID);

	// 绘制
	VOID Invalidate();
	virtual VOID OnPaint(HDC hDC, RECT& rc);
	virtual VOID OnPaintStateImage(HDC hDC);
	virtual VOID OnPaintText(HDC hDC);
	virtual VOID OnPaintBorder(HDC hDC);

	CZControl* FindControl(POINT& pt);

protected:
	CZUIMgr*						m_pZUIMgr;				// ZUI Mgr
	CZControl*						m_pParent;				// 父控件
	ATL::CSimpleArray<CZControl*>	m_aChild;				// 子控件
	CAtlString						m_strName;				// 控件名
	CRect							m_rcSize;				// 控件位置、大小
	CRect							m_rcPadding;			// Padding
	CRect							m_rcPaint;				// 与失效矩形的交集
	BOOL							m_bVisible;				// 是否可见
	BOOL							m_bEnable;				// 是否可用
	BOOL							m_bFocus;				// 是否有焦点
	CAtlString						m_strTooltip;			// Tooltip

	// Border
	DWORD							m_dwBorderSize;			// 粗细
	CSize							m_xyBorderRound;		// 圆角
	DWORD							m_dwBorderColor;		// 颜色
	DWORD							m_dwBorderFocusColor;	// 有焦点时的颜色
};
