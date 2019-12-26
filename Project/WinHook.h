/*
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'@Module Name:  WinHook(.h)
'@Main Func:    窗口Hook
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

//窗口Hook对象
typedef struct{
	DWORD id;				//进程ID
	HHOOK hHook;			//Hook句柄
	int lock;				//保护标志
} WinHookObject;

//窗口对象
typedef struct{
	HWND hWnd;				//窗口句柄
	HHOOK hHook;			//所属Hook句柄
	CWinHook *pOwner;		//拥有者
} WindowObject;

const int MaxWinHooks = 100;	//允许注册的最大Hook数量
const int MaxWnds = 1000;		//允许注册的最大窗口数量

extern WinHookObject gWinHook[MaxWinHooks];	//窗口Hook对象
extern WindowObject gWnd[MaxWnds];			//窗口对象

extern int gWinHooks;		//当前注册的Hook数量<=MaxWinHooks
extern int gWnds;			//当前注册的窗口数量<=MaxWnds

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
	// 卸载所有窗口Hook对象
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
