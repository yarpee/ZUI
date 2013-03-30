//////////////////////////////////////////////////////////////////////////
// Creator: Z
// Brief: �ؼ�����
// Version: 1.0
// Change:
// 1.2013/3/16 Z/1.0/����

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

	// DUI�������, ��CZWindow��AddChild����
	VOID AttachZUIMgr(CZUIMgr* pMgr);
	CZUIMgr* DetachZUIMgr();

	// �ؼ�����, ��������
	virtual LPCTSTR GetClassName();

	// �ؼ���, Ψһ��ʶ
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

	// �¼�������
	virtual BOOL HandleEvent(EVENT& e);
	
	// Notify
	VOID SendNotify(DWORD dwNotifyID);

	// ����
	VOID Invalidate();
	virtual VOID OnPaint(HDC hDC, RECT& rc);
	virtual VOID OnPaintStateImage(HDC hDC);
	virtual VOID OnPaintText(HDC hDC);
	virtual VOID OnPaintBorder(HDC hDC);

	CZControl* FindControl(POINT& pt);

protected:
	CZUIMgr*						m_pZUIMgr;				// ZUI Mgr
	CZControl*						m_pParent;				// ���ؼ�
	ATL::CSimpleArray<CZControl*>	m_aChild;				// �ӿؼ�
	CAtlString						m_strName;				// �ؼ���
	CRect							m_rcSize;				// �ؼ�λ�á���С
	CRect							m_rcPadding;			// Padding
	CRect							m_rcPaint;				// ��ʧЧ���εĽ���
	BOOL							m_bVisible;				// �Ƿ�ɼ�
	BOOL							m_bEnable;				// �Ƿ����
	BOOL							m_bFocus;				// �Ƿ��н���
	CAtlString						m_strTooltip;			// Tooltip

	// Border
	DWORD							m_dwBorderSize;			// ��ϸ
	CSize							m_xyBorderRound;		// Բ��
	DWORD							m_dwBorderColor;		// ��ɫ
	DWORD							m_dwBorderFocusColor;	// �н���ʱ����ɫ
};
