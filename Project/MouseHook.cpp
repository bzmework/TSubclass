/*
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'@Module Name:  MouseHook(.cpp)
'@Main Func:    鼠标Hook
'@Author:       denglf
'@Last Modify:  2018-08-18
'@Notes:
'@Interface:
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
*/

// MouseHook.cpp : Implementation of CMouseHook
#include "stdafx.h"
#include "TSubclass.h"
#include "MouseHook.h"

MouseHookObject gMouseHook[MaxMouseHooks];
MouseObject gMouseObj[MaxMouseHooks];  

int gMouseHooks = 0;
int gMouseObjs = 0;

/////////////////////////////////////////////////////////////////////////////
// CMouseHook


// 获取当前进程注册的鼠标Hook
HHOOK GetCurrentMouseHook()
{
	DWORD id = GetCurrentThreadId();
	for(int i=0; i<gMouseHooks; i++)
	{
		if(gMouseHook[i].id == id)
		{
			return gMouseHook[i].hHook;
		}
	}
	
	return NULL;
}

// 鼠标Hook处理
LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	HHOOK hHook = GetCurrentMouseHook();
	long bEatIt = 0;
	
	//只把消息分发给当前进程
	if (nCode == HC_ACTION)
	{
		MOUSEHOOKSTRUCT lpMHx;
		long hWnd = 0;
		UINT uMsg = 0;
		long x = 0;
		long y = 0;
		long wMouseData = 0;
		
		//收集消息
		CopyMemory(&lpMHx, (void*)lParam, sizeof(lpMHx));
		hWnd = (long)lpMHx.hwnd;
		uMsg = wParam;
		x = lpMHx.pt.x;
		y = lpMHx.pt.y;
		wMouseData = lpMHx.dwExtraInfo;
		if (_WIN32_WINNT) //NT系统取不到滚轮句柄，因此需要特殊处理
		{
			MSLLHOOKSTRUCT lpMHn;
			CopyMemory(&lpMHn, (void*)lParam, sizeof(lpMHn));
			wMouseData = lpMHn.dwExtraInfo;
		}
	
		//消息分发
		for(int i=0; i<gMouseObjs; i++)
		{
			if(gMouseObj[i].hHook == hHook)
			{	
				gMouseObj[i].pOwner->Fire_OnMessage(hWnd, uMsg, x, y, wMouseData, &bEatIt);
			}
		}
	}
	
	//返回
	if (bEatIt)
	{
		return -1;
	}
	else
	{
		/*
		MSDN: Calling CallNextHookEx is optional, but it is highly recommended; otherwise, 
		other applications that have installed hooks will not receive hook notifications and may behave incorrectly as a result. 
		You should call CallNextHookEx unless you absolutely need to prevent the notification from being seen by other applications. 
		MSDN: 调用CallNextHookEx是可选的，但强烈推荐；否则，
		其他已经安装了钩子的应用程序将不会收到钩子通知，并可能因此行为不正确。
		您应该调用CallNextHookEx，除非您绝对需要防止其他应用程序看到通知。
		*/
		return CallNextHookEx(hHook, nCode, wParam, lParam);
	}
}

// 系统生成，不要修改
STDMETHODIMP CMouseHook::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMouseHook
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

//关于
STDMETHODIMP CMouseHook::AboutMe()
{
	MessageBox(NULL, ABOUTME, COPYRIGHT, MB_ICONWARNING | MB_OK);
	return S_OK;
}

// 鼠标Hook
STDMETHODIMP CMouseHook::Hook(VARIANT_BOOL* outVal)
{
	*outVal = 0;

	if (!mbHooked)
	{
		int i = 0;

		//超限
		if (gMouseHooks >= MaxMouseHooks)
		{
			return FALSE;
		}
		if (gMouseObjs >= MaxMouseObjs)
		{
			return FALSE;
		}

		//不允许重复注册
		for(i=0; i<gMouseObjs; i++)
		{
			if(gMouseObj[i].pOwner == this)
			{
				return FALSE;
			}
		}
	
		//注册鼠标Hook
		HHOOK hHook = NULL;
		DWORD id = GetCurrentThreadId();
		for(i=0; i<gMouseHooks; i++)
		{
			if(gMouseHook[i].id == id)
			{
				hHook = gMouseHook[i].hHook;
				break;
			}
		}
		if (hHook == NULL)
		{
			/*
			The SetWindowsHookEx function installs an application-defined hook procedure into a hook chain. 
			You would install a hook procedure to monitor the system for certain types of events. 
			These events are associated either with a specific thread or with all threads in the system. 
			SetWindowsHookEx函数将应用程序定义的钩子处理函数安装到钩子链上。
			您将安装一个钩子处理函数来监视系统中特定类型的事件。
			这些事件要么与特定的线程关联，要么与系统中的所有线程关联。
			*/
			hHook = SetWindowsHookEx(WH_MOUSE, (HOOKPROC) MouseHookProc, GetModuleHandle(NULL), id);
			if(hHook == NULL) //Hook失败
			{
				return S_FALSE;
			}
			else
			{
				gMouseHook[gMouseHooks].id = id;
				gMouseHook[gMouseHooks].hHook = hHook;
				gMouseHook[gMouseHooks].lock++; //锁住以保护
				gMouseHooks++;
			}
		}
		
		//注册对象
		gMouseObj[gMouseObjs].hHook = hHook;
		gMouseObj[gMouseObjs].pOwner = this;
		gMouseObjs++;
		
		//返回
		mbHooked = TRUE;
		*outVal = 1;
		return S_OK;
	}
	return S_FALSE;

}

// 卸载鼠标Hook
STDMETHODIMP CMouseHook::UnHook(VARIANT_BOOL* outVal)
{
	*outVal = 0;

	if (mbHooked)
	{
		Destory();
		mbHooked = FALSE;
		*outVal = 1;
		return S_OK;
	}
	return S_FALSE;

}

// 销毁Hook对象
void CMouseHook::Destory()
{	
	int i = 0;
	DWORD id = GetCurrentThreadId();
	HHOOK hHook = GetCurrentMouseHook();
	
	if (hHook != NULL)
	{
		//卸载当前Mouse对象，例如VB中:
		//Set mclsMouseHook1 = New TSubclass.MouseHook
		//Set mclsMouseHook2 = New TSubclass.MouseHook
		//...
		for(i=0; i<gMouseObjs; i++)
		{
			if(gMouseObj[i].pOwner == this) //当前对象
			{
				//注册的窗口数量减1
				gMouseObjs--;
				
				//向前移动窗口
				for(int k = i; k<gMouseObjs; k++)
				{
					gMouseObj[k].hHook = gMouseObj[k+1].hHook;
					gMouseObj[k].pOwner = gMouseObj[k+1].pOwner;
				}
				i--;
			}
		}
		
		//检查是否需要卸载Hook
		bool bUnhook = true;
		for(i=0; i<gMouseObjs; i++)
		{
			if(gMouseObj[i].hHook == hHook) //仍然有注册的对象挂接在Hook链上
			{
				bUnhook = false; 
				break;
			}
		}
		
		//卸载当前进程注册的Hook
		if(bUnhook)
		{
			for(i=0; i<gMouseHooks; i++)
			{
				if(gMouseHook[i].id == id)
				{
					gMouseHook[i].lock--; //解锁
					if(gMouseHook[i].lock == 0)
					{
						//卸载Hook
						UnhookWindowsHookEx(gMouseHook[i].hHook); 
						
						//注册的Hook数量减1
						gMouseHooks--;
						
						//向前移动Hook
						for(int k = i; k<gMouseHooks; k++)
						{
							gMouseHook[k].id = gMouseHook[k+1].id;
							gMouseHook[k].hHook = gMouseHook[k+1].hHook;
							gMouseHook[k].lock = gMouseHook[k+1].lock;
						}
					}
					break;
				}
			}
		}
		
		/*
		if(gMouseHooks<=0)
		{
			MessageBox(0, TEXT("清理干净"), TEXT("MouseHook"), 0);
		}
		*/

	}
}