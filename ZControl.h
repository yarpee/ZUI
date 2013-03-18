//////////////////////////////////////////////////////////////////////////
// Creator: Z
// Brief: �ؼ�����
// Version: 1.0
// Change:
// 1.2013/3/16 Z/1.0/����

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

	// �������, һ����CZWindow����
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

	// Size
	VOID SetSize(RECT& rcSize);
	const RECT& GetSize();

	// Visible
	VOID SetVisible(BOOL bVisible);
	BOOL IsVisible();

	// �¼�������
	virtual BOOL HandleEvent(EVENT& e);

	// ����
	VOID Invalidate();
	virtual VOID OnPaint(HDC hDC, RECT& rc);
	virtual VOID OnPaintStateImage(HDC hDC);
	virtual VOID OnPaintText(HDC hDC);

protected:
	CZUIMgr*						m_pZUIMgr;	// ZUI Mgr
	CZControl*						m_pParent;	// ���ؼ�
	ATL::CSimpleArray<CZControl*>	m_aChild;	// �ӿؼ�
	CAtlString						m_strName;	// �ؼ���
	CRect							m_rcSize;	// �ؼ�λ�á���С
	BOOL							m_bVisible;	// �Ƿ�ɼ�
};
