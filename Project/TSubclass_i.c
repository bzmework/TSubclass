

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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



#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        EXTERN_C __declspec(selectany) const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif // !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_TSubclass,0xA94EC24D,0xAF4B,0x47FF,0x94,0x49,0x7C,0x18,0xBB,0x0D,0x58,0x5F);


MIDL_DEFINE_GUID(IID, IID_ISubclass,0x015EC82A,0x8F57,0x4CD9,0x81,0xEE,0x8B,0xE1,0x5D,0xFD,0x25,0xFA);


MIDL_DEFINE_GUID(IID, DIID__ISubclassEvents,0x0BA49ED4,0xEE6E,0x4128,0x8F,0x15,0x27,0xB8,0x2A,0x1D,0xC5,0x83);


MIDL_DEFINE_GUID(CLSID, CLSID_Subclass,0x8494AA18,0x544F,0x47FD,0xA6,0xDA,0x5E,0xB3,0x57,0x62,0xEA,0xBF);


MIDL_DEFINE_GUID(IID, IID_IWinHook,0x925F2945,0x2C28,0x4210,0xA5,0x1A,0x62,0x59,0x5A,0x6B,0x3D,0xD9);


MIDL_DEFINE_GUID(IID, DIID__IWinHookEvents,0x4BFAAC50,0x90E1,0x4875,0xA4,0x74,0x1F,0x0F,0x13,0xF3,0xFF,0x5F);


MIDL_DEFINE_GUID(CLSID, CLSID_WinHook,0xBB071AA9,0xFAEE,0x4A67,0xA7,0xE4,0x20,0x7E,0xAC,0x3F,0xAE,0x34);


MIDL_DEFINE_GUID(IID, IID_IMouseHook,0x9E6749D6,0xB954,0x4A45,0x82,0xE2,0x64,0xB8,0x17,0x6E,0x2D,0x2B);


MIDL_DEFINE_GUID(IID, DIID__IMouseHookEvents,0xF5D8B63F,0x4E34,0x415B,0xA1,0x99,0xAF,0x4F,0x35,0x05,0x87,0x9A);


MIDL_DEFINE_GUID(CLSID, CLSID_MouseHook,0xAB3EF696,0xED27,0x4B99,0xA3,0x35,0x11,0x4D,0x13,0xBB,0x36,0x6E);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



