/*
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'@Module Name:  MouseHook(.h)
'@Main Func:    ���Hook
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

//Mouse Hook����
typedef struct{
	DWORD id;				//����ID
	HHOOK hHook;			//Hook���
	int lock;				//������־
} MouseHookObject;

//������
typedef struct{
	HHOOK hHook;			//����Hook���
	CMouseHook *pOwner;		//������
} MouseObject;

const int MaxMouseHooks = 100;	//����ע������Hook��������
const int MaxMouseObjs = 1000;	//����ע����������������

extern MouseHookObject gMouseHook[MaxMouseHooks]; //MouseHook����
extern MouseObject gMouseObj[MaxMouseHooks]; //Mouse����

extern int gMouseHooks;		//��ǰע���Hook��������<=MaxMouseHooks
extern int gMouseObjs;		//��ǰע�������������<=MaxMouseObjs

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
	// ж��Hook����
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
