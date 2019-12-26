

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for TSubclass.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __TSubclass_h__
#define __TSubclass_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISubclass_FWD_DEFINED__
#define __ISubclass_FWD_DEFINED__
typedef interface ISubclass ISubclass;

#endif 	/* __ISubclass_FWD_DEFINED__ */


#ifndef ___ISubclassEvents_FWD_DEFINED__
#define ___ISubclassEvents_FWD_DEFINED__
typedef interface _ISubclassEvents _ISubclassEvents;

#endif 	/* ___ISubclassEvents_FWD_DEFINED__ */


#ifndef __Subclass_FWD_DEFINED__
#define __Subclass_FWD_DEFINED__

#ifdef __cplusplus
typedef class Subclass Subclass;
#else
typedef struct Subclass Subclass;
#endif /* __cplusplus */

#endif 	/* __Subclass_FWD_DEFINED__ */


#ifndef __IWinHook_FWD_DEFINED__
#define __IWinHook_FWD_DEFINED__
typedef interface IWinHook IWinHook;

#endif 	/* __IWinHook_FWD_DEFINED__ */


#ifndef ___IWinHookEvents_FWD_DEFINED__
#define ___IWinHookEvents_FWD_DEFINED__
typedef interface _IWinHookEvents _IWinHookEvents;

#endif 	/* ___IWinHookEvents_FWD_DEFINED__ */


#ifndef __WinHook_FWD_DEFINED__
#define __WinHook_FWD_DEFINED__

#ifdef __cplusplus
typedef class WinHook WinHook;
#else
typedef struct WinHook WinHook;
#endif /* __cplusplus */

#endif 	/* __WinHook_FWD_DEFINED__ */


#ifndef __IMouseHook_FWD_DEFINED__
#define __IMouseHook_FWD_DEFINED__
typedef interface IMouseHook IMouseHook;

#endif 	/* __IMouseHook_FWD_DEFINED__ */


#ifndef ___IMouseHookEvents_FWD_DEFINED__
#define ___IMouseHookEvents_FWD_DEFINED__
typedef interface _IMouseHookEvents _IMouseHookEvents;

#endif 	/* ___IMouseHookEvents_FWD_DEFINED__ */


#ifndef __MouseHook_FWD_DEFINED__
#define __MouseHook_FWD_DEFINED__

#ifdef __cplusplus
typedef class MouseHook MouseHook;
#else
typedef struct MouseHook MouseHook;
#endif /* __cplusplus */

#endif 	/* __MouseHook_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __TSubclass_LIBRARY_DEFINED__
#define __TSubclass_LIBRARY_DEFINED__

/* library TSubclass */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_TSubclass;

#ifndef __ISubclass_INTERFACE_DEFINED__
#define __ISubclass_INTERFACE_DEFINED__

/* interface ISubclass */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISubclass;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("015EC82A-8F57-4CD9-81EE-8BE15DFD25FA")
    ISubclass : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AboutMe( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hWnd( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_hWnd( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CallWndProc( 
            /* [in] */ int uMsg,
            /* [in] */ long wParam,
            /* [in] */ long lParam,
            /* [retval][out] */ long *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISubclassVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISubclass * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISubclass * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISubclass * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISubclass * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISubclass * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISubclass * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISubclass * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AboutMe )( 
            ISubclass * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_hWnd )( 
            ISubclass * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_hWnd )( 
            ISubclass * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CallWndProc )( 
            ISubclass * This,
            /* [in] */ int uMsg,
            /* [in] */ long wParam,
            /* [in] */ long lParam,
            /* [retval][out] */ long *pVal);
        
        END_INTERFACE
    } ISubclassVtbl;

    interface ISubclass
    {
        CONST_VTBL struct ISubclassVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISubclass_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISubclass_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISubclass_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISubclass_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ISubclass_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ISubclass_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ISubclass_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ISubclass_AboutMe(This)	\
    ( (This)->lpVtbl -> AboutMe(This) ) 

#define ISubclass_get_hWnd(This,pVal)	\
    ( (This)->lpVtbl -> get_hWnd(This,pVal) ) 

#define ISubclass_put_hWnd(This,newVal)	\
    ( (This)->lpVtbl -> put_hWnd(This,newVal) ) 

#define ISubclass_CallWndProc(This,uMsg,wParam,lParam,pVal)	\
    ( (This)->lpVtbl -> CallWndProc(This,uMsg,wParam,lParam,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISubclass_INTERFACE_DEFINED__ */


#ifndef ___ISubclassEvents_DISPINTERFACE_DEFINED__
#define ___ISubclassEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ISubclassEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ISubclassEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("0BA49ED4-EE6E-4128-8F15-27B82A1DC583")
    _ISubclassEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ISubclassEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ISubclassEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ISubclassEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ISubclassEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ISubclassEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ISubclassEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ISubclassEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ISubclassEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _ISubclassEventsVtbl;

    interface _ISubclassEvents
    {
        CONST_VTBL struct _ISubclassEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ISubclassEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _ISubclassEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _ISubclassEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _ISubclassEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _ISubclassEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _ISubclassEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _ISubclassEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ISubclassEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Subclass;

#ifdef __cplusplus

class DECLSPEC_UUID("8494AA18-544F-47FD-A6DA-5EB35762EABF")
Subclass;
#endif

#ifndef __IWinHook_INTERFACE_DEFINED__
#define __IWinHook_INTERFACE_DEFINED__

/* interface IWinHook */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWinHook;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("925F2945-2C28-4210-A51A-62595A6B3DD9")
    IWinHook : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AboutMe( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Hook( 
            /* [in] */ long hWnd,
            /* [retval][out] */ VARIANT_BOOL *outVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HookAll( 
            /* [in] */ long hWnd,
            /* [retval][out] */ VARIANT_BOOL *outVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnHook( 
            /* [retval][out] */ VARIANT_BOOL *outVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IWinHookVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWinHook * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWinHook * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWinHook * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWinHook * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWinHook * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWinHook * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWinHook * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AboutMe )( 
            IWinHook * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IWinHook * This,
            /* [in] */ long hWnd,
            /* [retval][out] */ VARIANT_BOOL *outVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HookAll )( 
            IWinHook * This,
            /* [in] */ long hWnd,
            /* [retval][out] */ VARIANT_BOOL *outVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnHook )( 
            IWinHook * This,
            /* [retval][out] */ VARIANT_BOOL *outVal);
        
        END_INTERFACE
    } IWinHookVtbl;

    interface IWinHook
    {
        CONST_VTBL struct IWinHookVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWinHook_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWinHook_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWinHook_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWinHook_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWinHook_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWinHook_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWinHook_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWinHook_AboutMe(This)	\
    ( (This)->lpVtbl -> AboutMe(This) ) 

#define IWinHook_Hook(This,hWnd,outVal)	\
    ( (This)->lpVtbl -> Hook(This,hWnd,outVal) ) 

#define IWinHook_HookAll(This,hWnd,outVal)	\
    ( (This)->lpVtbl -> HookAll(This,hWnd,outVal) ) 

#define IWinHook_UnHook(This,outVal)	\
    ( (This)->lpVtbl -> UnHook(This,outVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWinHook_INTERFACE_DEFINED__ */


#ifndef ___IWinHookEvents_DISPINTERFACE_DEFINED__
#define ___IWinHookEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IWinHookEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IWinHookEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("4BFAAC50-90E1-4875-A474-1F0F13F3FF5F")
    _IWinHookEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IWinHookEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IWinHookEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IWinHookEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IWinHookEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IWinHookEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IWinHookEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IWinHookEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IWinHookEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _IWinHookEventsVtbl;

    interface _IWinHookEvents
    {
        CONST_VTBL struct _IWinHookEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IWinHookEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IWinHookEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IWinHookEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IWinHookEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IWinHookEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IWinHookEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IWinHookEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IWinHookEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_WinHook;

#ifdef __cplusplus

class DECLSPEC_UUID("BB071AA9-FAEE-4A67-A7E4-207EAC3FAE34")
WinHook;
#endif

#ifndef __IMouseHook_INTERFACE_DEFINED__
#define __IMouseHook_INTERFACE_DEFINED__

/* interface IMouseHook */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMouseHook;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9E6749D6-B954-4A45-82E2-64B8176E2D2B")
    IMouseHook : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AboutMe( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Hook( 
            /* [retval][out] */ VARIANT_BOOL *outVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnHook( 
            /* [retval][out] */ VARIANT_BOOL *outVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMouseHookVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMouseHook * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMouseHook * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMouseHook * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMouseHook * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMouseHook * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMouseHook * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMouseHook * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AboutMe )( 
            IMouseHook * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Hook )( 
            IMouseHook * This,
            /* [retval][out] */ VARIANT_BOOL *outVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnHook )( 
            IMouseHook * This,
            /* [retval][out] */ VARIANT_BOOL *outVal);
        
        END_INTERFACE
    } IMouseHookVtbl;

    interface IMouseHook
    {
        CONST_VTBL struct IMouseHookVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMouseHook_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMouseHook_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMouseHook_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMouseHook_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMouseHook_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMouseHook_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMouseHook_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IMouseHook_AboutMe(This)	\
    ( (This)->lpVtbl -> AboutMe(This) ) 

#define IMouseHook_Hook(This,outVal)	\
    ( (This)->lpVtbl -> Hook(This,outVal) ) 

#define IMouseHook_UnHook(This,outVal)	\
    ( (This)->lpVtbl -> UnHook(This,outVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMouseHook_INTERFACE_DEFINED__ */


#ifndef ___IMouseHookEvents_DISPINTERFACE_DEFINED__
#define ___IMouseHookEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IMouseHookEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IMouseHookEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("F5D8B63F-4E34-415B-A199-AF4F3505879A")
    _IMouseHookEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IMouseHookEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IMouseHookEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IMouseHookEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IMouseHookEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IMouseHookEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IMouseHookEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IMouseHookEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IMouseHookEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _IMouseHookEventsVtbl;

    interface _IMouseHookEvents
    {
        CONST_VTBL struct _IMouseHookEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IMouseHookEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IMouseHookEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IMouseHookEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IMouseHookEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IMouseHookEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IMouseHookEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IMouseHookEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IMouseHookEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MouseHook;

#ifdef __cplusplus

class DECLSPEC_UUID("AB3EF696-ED27-4B99-A335-114D13BB366E")
MouseHook;
#endif
#endif /* __TSubclass_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


