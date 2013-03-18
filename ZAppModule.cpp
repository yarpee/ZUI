#include "ZAppModule.h"

CZAppModule::CZAppModule(void)
: m_hInstance(NULL)
{
}

CZAppModule::~CZAppModule(void)
{
}

BOOL CZAppModule::Init(HINSTANCE hInstance)
{
	if(NULL == hInstance)
	{
		return FALSE;
	}
	else
	{
		m_hInstance = hInstance;
		return TRUE;
	}
}

VOID CZAppModule::Term()
{

}

HINSTANCE CZAppModule::GetInstance()
{
	return m_hInstance;
}
