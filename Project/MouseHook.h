/*
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'@Module Name:  MouseHook(.h)
'@Main Func:    鼠标Hook
'@Author:       denglf
'@Last Modify:  2018-08-18
'@Notes:
'@Interface:
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
*/

// MouseHook.h : Declaration of the CMouseHook

#ifndef __MOUSEHOOK_H_
#define __MOUSEHOOK_H_

#include "resource.h"       // main symbols
#include "MouseHookCP.h"

class CMouseHook;

//Mouse Hook对象
typedef struct{
	DWORD id;				//进程ID
	HHOOK hHook;			//Hook句柄
	int lock;				//保护标志
} MouseHookObject;

//鼠标对象
typedef struct{
	HHOOK hHook;			//所属Hook句柄
	CMouseHook *pOwner;		//鼠标对象
} MouseObject;

const int MaxMouseHooks = 100;	//允许注册的最大Hook对象数量
const int MaxMouseObjs = 1000;	//允许注册的最大鼠标对象数量

extern MouseHookObject gMouseHook[MaxMouseHooks]; //MouseHook对象
extern MouseObject gMouseObj[MaxMouseHooks]; //Mouse对象

extern int gMouseHooks;		//当前注册的Hook对象数量<=MaxMouseHooks
extern int gMouseObjs;		//当前注册的鼠标对象数量<=MaxMouseObjs

/////////////////////////////////////////////////////////////////////////////
// CMouseHook
class ATL_NO_VTABLE CMouseHook : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMouseHook, &CLSID_MouseHook>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CMouseHook>,
	public IDispatchImpl<IMouseHook, &IID_IMouseHook, &LIBID_TSubclass>,
	public CProxy_IMouseHookEvents< CMouseHook >
{
public:
	CMouseHook()
	{
		mbHooked = FALSE;
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_MOUSEHOOK)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CMouseHook)
		COM_INTERFACE_ENTRY(IMouseHook)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IConnectionPointContainer)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	END_COM_MAP()
	BEGIN_CONNECTION_POINT_MAP(CMouseHook)
	CONNECTION_POINT_ENTRY(DIID__IMouseHookEvents)
	END_CONNECTION_POINT_MAP()

	// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	//
	// 卸载Hook对象
	//
	void FinalRelease()
	{	
		Destory();
	}

// IMouseHook
public:
	
	STDMETHOD(AboutMe)();
	STDMETHOD(Hook)(/*[out,retval]*/ VARIANT_BOOL* outVal);
	STDMETHOD(UnHook)(/*[out,retval]*/ VARIANT_BOOL* outVal);
	void Destory();

private:
	
	BOOL mbHooked;

};

#endif //__MOUSEHOOK_H_
