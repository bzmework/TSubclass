/*
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'@Module Name:  Subclass(.h)
'@Main Func:    ���໯����
'@Author:       denglf
'@Last Modify:  2018-08-17
'@Notes:
'@Interface:
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
*/

// Subclass.h : Declaration of the CSubclass

#ifndef __SUBCLASS_H_
#define __SUBCLASS_H_

#include "stdafx.h"
#include "resource.h"       // main symbols
#include "SubclassCP.h"
#include <atlwin.h>

/////////////////////////////////////////////////////////////////////////////
// CSubclass
class ATL_NO_VTABLE CSubclass : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSubclass, &CLSID_Subclass>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CSubclass>,
	public IDispatchImpl<ISubclass, &IID_ISubclass, &LIBID_TSubclass>,
	public CWindowImpl<CSubclass>,
	public CProxy_ISubclassEvents<CSubclass>
{
public:
	CSubclass()
	{
		m_hWnd = NULL;
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_SUBCLASS)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CSubclass)
		COM_INTERFACE_ENTRY(ISubclass)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IConnectionPointContainer)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	END_COM_MAP()
	BEGIN_CONNECTION_POINT_MAP(CSubclass)
		CONNECTION_POINT_ENTRY(DIID__ISubclassEvents)
	END_CONNECTION_POINT_MAP()

	BEGIN_MSG_MAP(CSubClass)
		MESSAGE_RANGE_HANDLER(0x0000, 0xFFFF, OnMessage)
	END_MSG_MAP()

	// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);
	
	//
	// ж���������ര��
	//
	void FinalRelease()
	{
		if (m_hWnd)	
		{
			UnsubclassWindow();
		}
	}

// ISubclass
public:
	
	STDMETHOD(AboutMe)();
	STDMETHOD(get_hWnd)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_hWnd)(/*[in]*/ long newVal);
	STDMETHOD(CallWndProc)(int uMsg, long wParam, long lParam, /*[out, retval]*/ long *pVal);

	//��Ϣ����
	LRESULT OnMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lresult = 0;
		long lrevVal = 0;
		BOOL bhandled = FALSE;

		Fire_OnMessage(uMsg, wParam, lParam, &bhandled, &lrevVal);
		if ((!bhandled) && (uMsg != WM_NCDESTROY)) 
		{
			// ��Ϣδ��������Ĭ�ϴ��ں�������
			lresult = DefWindowProc(uMsg, wParam, lParam);
			bHandled = TRUE; //������ATL����Ϣ���͸�Ĭ�ϴ��ں���
		}
		else
		{
			// ��Ϣ�����������Ҳ�����Ĭ�ϴ��ں�������
			lresult = lrevVal;
			bHandled = bhandled;
		}
		
		// ��Ϣ�Ѿ������ٴ�����Ϣ������¼�
		if(!bHandled)
		{
			Fire_AfterMessage(uMsg, wParam, lParam);
		}
		
		return lresult;
	}

};

#endif //__SUBCLASS_H_
