// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__4169C38F_FDBE_42D1_A778_A6CF610D68C3__INCLUDED_)
#define AFX_STDAFX_H__4169C38F_FDBE_42D1_A778_A6CF610D68C3__INCLUDED_

/***版权标识**********************************/
#define COPYRIGHT _T("版权声明")
#define ABOUTME   _T("关于我们")
static const char *COMPANY = "elong.tech"; 
static const char *AUTHOR = "denglf";
/*********************************************/

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#if _MSC_VER <= 1400 // 1200=VC++6.0(vs98) - 1400=VC++ 8.0(vs2005)
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif 
#endif
#define _ATL_APARTMENT_THREADED

#define IsNT ((DWORD)(LOBYTE(LOWORD(GetVersion))) >= 4)

//#include <afxwin.h>
//#include <afxdisp.h>

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__4169C38F_FDBE_42D1_A778_A6CF610D68C3__INCLUDED)
