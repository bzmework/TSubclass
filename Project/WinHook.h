/*
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'@Module Name:  WinHook(.h)
'@Main Func:    ����Hook
'@Author:       denglf
'@Last Modify:  2018-08-17
'@Notes:
'@Interface:
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
*/

// WinHook.h : Declaration of the CWinHook

#ifndef __WINHOOK_H_
#define __WINHOOK_H_

#include "resource.h"       // main symbols
#include "WinHookCP.h"

class CWinHook;

//����Hook����
typedef struct{
	DWORD id;				//����ID
	HHOOK hHook;			//Hook���
	int lock;				//������־
} WinHookObject;

//���ڶ���
typedef struct{
	HWND hWnd;				//���ھ��
	HHOOK hHook;			//����Hook���
	CWinHook *pOwner;		//ӵ����
} WindowObject;

const int MaxWinHooks = 100;	//����ע������Hook����
const int MaxWnds = 1000;		//����ע�����󴰿�����

extern WinHookObject gWinHook[MaxWinHooks];	//����Hook����
extern WindowObject gWnd[MaxWnds];			//���ڶ���

extern int gWinHooks;		//��ǰע���Hook����<=MaxWinHooks
extern int gWnds;			//��ǰע��Ĵ�������<=MaxWnds

/////////////////////////////////////////////////////////////////////////////
// CWinHook
class ATL_NO_VTABLE CWinHook : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CWinHook, &CLSID_WinHook>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CWinHook>,
	public IDispatchImpl<IWinHook, &IID_IWinHook, &LIBID_TSubclass>,
	public CProxy_IWinHookEvents< CWinHook >
{
public:
	CWinHook()
	{
		mbHooked = FALSE;
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_WINHOOK)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CWinHook)
		COM_INTERFACE_ENTRY(IWinHook)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IConnectionPointContainer)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	END_COM_MAP()
	BEGIN_CONNECTION_POINT_MAP(CWinHook)
	CONNECTION_POINT_ENTRY(DIID__IWinHookEvents)
	END_CONNECTION_POINT_MAP()

	// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	//
	// ж�����д���Hook����
	//
	void FinalRelease()
	{	
		Destory();
	}
	
// IWinHook
public:
	
	STDMETHOD(AboutMe)();
	STDMETHOD(Hook)(long hWnd, /*[out,retval]*/ VARIANT_BOOL* outVal);
	STDMETHOD(HookAll)(long hWnd, /*[out,retval]*/ VARIANT_BOOL* outVal);
	STDMETHOD(UnHook)(/*[out,retval]*/ VARIANT_BOOL* outVal);
	void Destory();

protected:
	BOOL mbHooked;
	
	void RegisterAllChildWindow(HWND hWnd, HHOOK hHook);

};

#endif //__WINHOOK_H_
