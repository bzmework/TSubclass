/*
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'@Module Name:  Subclass(.cpp)
'@Main Func:    ���໯����
'@Author:       denglf
'@Last Modify:  2018-08-17
'@Notes:
'@Interface:
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
*/

// Subclass.cpp : Implementation of CSubclass
#include "stdafx.h"
#include "TSubclass.h"
#include "Subclass.h"

/////////////////////////////////////////////////////////////////////////////
// CSubclass

//ϵͳ���ɣ���Ҫ�޸�
STDMETHODIMP CSubclass::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISubclass
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

//����
STDMETHODIMP CSubclass::AboutMe()
{
	MessageBox(ABOUTME, COPYRIGHT, MB_ICONWARNING | MB_OK);
	return S_OK;
}

//���ش��ھ��
STDMETHODIMP CSubclass::get_hWnd(long *pVal)
{
	*pVal = (long)m_hWnd;
	return S_OK;
}

//���ô��ھ��
STDMETHODIMP CSubclass::put_hWnd(long newVal)
{
	if (m_hWnd)
	{
		UnsubclassWindow();
	}

	if (::IsWindow((HWND)newVal))
	{
		SubclassWindow((HWND)newVal);
	}
	
	return S_OK;
}

//����Ĭ�ϵĴ��ڴ�����
STDMETHODIMP CSubclass::CallWndProc(int uMsg, long wParam, long lParam, long *pVal)
{
	if (m_hWnd)
	{
		*pVal = DefWindowProc(uMsg, wParam, lParam);
	}
	return S_OK;
}
