/*
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'@Module Name:  WinHook(.cpp)
'@Main Func:    窗口Hook
'@Author:       denglf
'@Last Modify:  2018-08-17
'@Notes:
'@Interface:
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
*/

// WinHook.cpp : Implementation of CWinHook
#include "stdafx.h"
#include "TSubclass.h"
#include "WinHook.h"

WinHookObject gWinHook[MaxWinHooks];
WindowObject gWnd[MaxWnds];

int gWinHooks = 0;
int gWnds = 0;

UINT gActMsg = 0;

// 获取当前进程注册的窗口Hook
HHOOK GetCurrentWinHook()
{
	DWORD id = GetCurrentThreadId();
	for(int i=0; i<gWinHooks; i++)
	{
		if(gWinHook[i].id == id)
		{
			return gWinHook[i].hHook;
		}
	}
	
	return NULL;
}

// 消息处理
BOOL ProcessMessage(MSG msg, HHOOK *pHook)
{
	BOOL bEatIt = FALSE;
	
	if(gActMsg != msg.message) //过滤掉相同消息
	{
		for(int i=0; i<gWnds; i++)
		{
			if(msg.hwnd == gWnd[i].hWnd)  
			{
				//派送消息
				gWnd[i].pOwner->Fire_OnMessage((long)msg.hwnd, msg.message, msg.wParam, msg.lParam, &bEatIt);
				
				//返回hHook
				pHook = &(gWnd[i].hHook);

				//缓存消息
				gActMsg = msg.message;
			}
		}
	}
	else
	{
		gActMsg = 0;
	}

	return bEatIt;
}

// 窗口Hook处理
LRESULT CALLBACK WinHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	HHOOK pHook = GetCurrentWinHook();
	MSG *Msg = (MSG *)lParam;

	if (nCode >= 0) 
	{
		if(ProcessMessage(*(MSG *)lParam, &pHook))
		{
			MSG rMsg;
			int i = 0;
			//while(WaitMessage())
			{
				//从队列检索已处理的消息
				while(PeekMessage(&rMsg, Msg->hwnd, Msg->message-1, Msg->message+1, PM_REMOVE))
				{
					i++;
					if(i>10)
						break;
				}
				return -1; //吃掉				
			}
		}
    }
	
	/*
	MSDN: Calling CallNextHookEx is optional, but it is highly recommended; otherwise, 
	other applications that have installed hooks will not receive hook notifications and may behave incorrectly as a result. 
	You should call CallNextHookEx unless you absolutely need to prevent the notification from being seen by other applications. 
	MSDN: 调用CallNextHookEx是可选的，但强烈推荐；否则，
	其他已经安装了钩子的应用程序将不会收到钩子通知，并可能因此行为不正确。
	您应该调用CallNextHookEx，除非您绝对需要防止其他应用程序看到通知。
	*/
	return CallNextHookEx(pHook, nCode, wParam, lParam);
}


/////////////////////////////////////////////////////////////////////////////
// CWinHook

// 系统生成，不要修改
STDMETHODIMP CWinHook::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IWinHook
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// 注册所有子窗口
void CWinHook::RegisterAllChildWindow(HWND hWnd, HHOOK hHook)
{
	HWND hChildWnd = GetWindow((HWND)hWnd, GW_CHILD);

	int start = gWnds;
	while(hChildWnd != NULL)
	{
		//不允许当前对象重复注册同一窗口
		for(int i =0; i<gWnds; i++)	
		{
			if(gWnd[i].hWnd == hChildWnd && gWnd[i].pOwner == this)
			{
				goto Next;
			}
		}

		//注册窗口
		gWnd[gWnds].hWnd = (HWND)hChildWnd;
		gWnd[gWnds].hHook = hHook;
		gWnd[gWnds].pOwner = this;
		gWnds++;
		
		//防止溢出
		if(gWnds >= MaxWnds)
		{
			gWnds--;
		}
Next:
		hChildWnd = GetNextWindow(hChildWnd, GW_HWNDNEXT);
	}

	for(int j = start; j<gWnds; j++)
	{
		RegisterAllChildWindow(gWnd[j].hWnd, hHook);
	}
	
}

//关于
STDMETHODIMP CWinHook::AboutMe()
{
	MessageBox(NULL, ABOUTME, COPYRIGHT, MB_ICONWARNING | MB_OK);
	return S_OK;
}

// Hook窗口
STDMETHODIMP CWinHook::Hook(long hWnd, VARIANT_BOOL* outVal)
{
	*outVal = 0;

	if (!mbHooked)
	{
		int i = 0;

		//窗口是否有效
		if (!::IsWindow((HWND)hWnd))
		{
			return S_FALSE;
		}
		
		//超限
		if (gWinHooks >= MaxWinHooks)
		{
			return FALSE;
		}
		if(gWnds >= MaxWnds)
		{
			return FALSE;
		}

		//不允许当前对象重复注册同一窗口
		for(i=0; i<gWnds; i++)	
		{
			if(gWnd[i].hWnd == (HWND)hWnd && gWnd[i].pOwner == this)
			{
				return S_FALSE;
			}
		}

		//注册Hook
		HHOOK hHook = NULL;
		DWORD id = GetCurrentThreadId();
		for(i=0; i<gWinHooks; i++)
		{
			if(gWinHook[i].id == id)
			{
				hHook = gWinHook[i].hHook;
				break;
			}
		}
		if (hHook == NULL)
		{
			hHook = SetWindowsHookEx(WH_GETMESSAGE, (HOOKPROC) WinHookProc, GetModuleHandle(NULL), id);
			if(hHook == NULL) //Hook失败
			{
				return S_FALSE;
			}
			else
			{
				gWinHook[gWinHooks].id = id;
				gWinHook[gWinHooks].hHook = hHook;
				gWinHook[gWinHooks].lock++; //锁住以保护
				gWinHooks++;
			}
		}

		//注册窗口
		hHook = GetCurrentWinHook();
		gWnd[gWnds].hWnd = (HWND)hWnd;
		gWnd[gWnds].hHook = hHook;
		gWnd[gWnds].pOwner = this;
		gWnds++;
		
		//返回
		mbHooked = TRUE;
		*outVal = 1;
		return S_OK;
	}
	return S_FALSE;

}

// Hook窗口及其所有子窗口
STDMETHODIMP CWinHook::HookAll(long hWnd, VARIANT_BOOL* outVal)
{
	*outVal = 0;

	if(!mbHooked)
	{
		int i = 0;

		//窗口是否有效
		if (!::IsWindow((HWND)hWnd))
		{
			return S_FALSE;
		}

		//超限
		if (gWinHooks >= MaxWinHooks)
		{
			return FALSE;
		}
		if(gWnds >= MaxWnds)
		{
			return FALSE;
		}
		
		//不允许当前对象重复注册同一窗口
		for(i=0; i<gWnds; i++)	
		{
			if(gWnd[i].hWnd == (HWND)hWnd && gWnd[i].pOwner == this)
			{
				return S_FALSE;
			}
		}

		//注册窗口Hook
		HHOOK hHook = NULL;
		DWORD id = GetCurrentThreadId();
		for(i=0; i<gWinHooks; i++)
		{
			if(gWinHook[i].id == id)
			{
				hHook = gWinHook[i].hHook;
				break;
			}
		}
		if (hHook == NULL)
		{
			hHook = SetWindowsHookEx(WH_GETMESSAGE, (HOOKPROC) WinHookProc, GetModuleHandle(NULL), id);
			if(hHook == NULL) //Hook失败
			{
				return S_FALSE;
			}
			else
			{
				gWinHook[gWinHooks].id = id;
				gWinHook[gWinHooks].hHook = hHook;
				gWinHook[gWinHooks].lock++; //锁住以保护
				gWinHooks++;
			}
		}

		//注册窗口及其所有子窗口
		hHook = GetCurrentWinHook();
		gWnd[gWnds].hWnd = (HWND)hWnd;
		gWnd[gWnds].hHook = hHook;
		gWnd[gWnds].pOwner = this;
		gWnds++;
		RegisterAllChildWindow((HWND)hWnd, hHook);
		
		//返回
		mbHooked = TRUE;
		*outVal = 1;
		return S_OK;
	}
	return S_FALSE;

}

// 卸载窗口Hook
STDMETHODIMP CWinHook::UnHook(VARIANT_BOOL* outVal)
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
void CWinHook::Destory()
{
	int i = 0;
	DWORD id = GetCurrentThreadId();
	HHOOK hHook = GetCurrentWinHook();
	
	if (hHook != NULL)
	{
		//卸载当前对象注册的窗口，例如VB中:
		//Set mclsWinHook1 = New TSubclass.WinHook
		//Set mclsWinHook2 = New TSubclass.WinHook
		//...
		for(int i=0; i<gWnds; i++)
		{
			if(gWnd[i].pOwner == this) //当前对象
			{
				//注册的窗口数量减1
				gWnds--;
				
				//向前移动窗口
				for(int k = i; k<gWnds; k++)
				{
					gWnd[k].hWnd = gWnd[k+1].hWnd;
					gWnd[k].hHook = gWnd[k+1].hHook;
					gWnd[k].pOwner = gWnd[k+1].pOwner;
				}
				i--;
			}
		}
		
		//检查是否需要卸载Hook
		bool bUnhook = true;
		for(i=0; i<gWnds; i++)
		{
			if(gWnd[i].hHook == hHook) //仍然有注册的窗口挂接在Hook链上
			{
				bUnhook = false; 
				break;
			}
		}

		//卸载当前进程注册的Hook
		if(bUnhook)
		{
			DWORD id = GetCurrentThreadId();
			for(int i=0; i<gWinHooks; i++)
			{
				if(gWinHook[i].id == id)//当前进程
				{
					gWinHook[i].lock--; //解锁
					if(gWinHook[i].lock == 0)
					{
						//卸载Hook
						UnhookWindowsHookEx(gWinHook[i].hHook); 
						
						//注册的Hook数量减1
						gWinHooks--;
						
						//向前移动Hook
						for(int k = i; k<gWinHooks; k++)
						{
							gWinHook[k].id = gWinHook[k+1].id;
							gWinHook[k].hHook = gWinHook[k+1].hHook;
							gWinHook[k].lock = gWinHook[k+1].lock;
						}
					}
					break;
				}
			}
		}

		/*
		if(gWinHooks<=0)
		{
			MessageBox(0, TEXT("清理干净"), TEXT("WinHook"), 0);
		}
		*/

	}

}