/*
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'@Module Name:  WinHook(.cpp)
'@Main Func:    ����Hook
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

// ��ȡ��ǰ����ע��Ĵ���Hook
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

// ��Ϣ����
BOOL ProcessMessage(MSG msg, HHOOK *pHook)
{
	BOOL bEatIt = FALSE;
	
	if(gActMsg != msg.message) //���˵���ͬ��Ϣ
	{
		for(int i=0; i<gWnds; i++)
		{
			if(msg.hwnd == gWnd[i].hWnd)  
			{
				//������Ϣ
				gWnd[i].pOwner->Fire_OnMessage((long)msg.hwnd, msg.message, msg.wParam, msg.lParam, &bEatIt);
				
				//����hHook
				pHook = &(gWnd[i].hHook);

				//������Ϣ
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

// ����Hook����
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
				//�Ӷ��м����Ѵ������Ϣ
				while(PeekMessage(&rMsg, Msg->hwnd, Msg->message-1, Msg->message+1, PM_REMOVE))
				{
					i++;
					if(i>10)
						break;
				}
				return -1; //�Ե�				
			}
		}
    }
	
	/*
	MSDN: Calling CallNextHookEx is optional, but it is highly recommended; otherwise, 
	other applications that have installed hooks will not receive hook notifications and may behave incorrectly as a result. 
	You should call CallNextHookEx unless you absolutely need to prevent the notification from being seen by other applications. 
	MSDN: ����CallNextHookEx�ǿ�ѡ�ģ���ǿ���Ƽ�������
	�����Ѿ���װ�˹��ӵ�Ӧ�ó��򽫲����յ�����֪ͨ�������������Ϊ����ȷ��
	��Ӧ�õ���CallNextHookEx��������������Ҫ��ֹ����Ӧ�ó��򿴵�֪ͨ��
	*/
	return CallNextHookEx(pHook, nCode, wParam, lParam);
}


/////////////////////////////////////////////////////////////////////////////
// CWinHook

// ϵͳ���ɣ���Ҫ�޸�
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

// ע�������Ӵ���
void CWinHook::RegisterAllChildWindow(HWND hWnd, HHOOK hHook)
{
	HWND hChildWnd = GetWindow((HWND)hWnd, GW_CHILD);

	int start = gWnds;
	while(hChildWnd != NULL)
	{
		//������ǰ�����ظ�ע��ͬһ����
		for(int i =0; i<gWnds; i++)	
		{
			if(gWnd[i].hWnd == hChildWnd && gWnd[i].pOwner == this)
			{
				goto Next;
			}
		}

		//ע�ᴰ��
		gWnd[gWnds].hWnd = (HWND)hChildWnd;
		gWnd[gWnds].hHook = hHook;
		gWnd[gWnds].pOwner = this;
		gWnds++;
		
		//��ֹ���
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

//����
STDMETHODIMP CWinHook::AboutMe()
{
	MessageBox(NULL, ABOUTME, COPYRIGHT, MB_ICONWARNING | MB_OK);
	return S_OK;
}

// Hook����
STDMETHODIMP CWinHook::Hook(long hWnd, VARIANT_BOOL* outVal)
{
	*outVal = 0;

	if (!mbHooked)
	{
		int i = 0;

		//�����Ƿ���Ч
		if (!::IsWindow((HWND)hWnd))
		{
			return S_FALSE;
		}
		
		//����
		if (gWinHooks >= MaxWinHooks)
		{
			return FALSE;
		}
		if(gWnds >= MaxWnds)
		{
			return FALSE;
		}

		//������ǰ�����ظ�ע��ͬһ����
		for(i=0; i<gWnds; i++)	
		{
			if(gWnd[i].hWnd == (HWND)hWnd && gWnd[i].pOwner == this)
			{
				return S_FALSE;
			}
		}

		//ע��Hook
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
			if(hHook == NULL) //Hookʧ��
			{
				return S_FALSE;
			}
			else
			{
				gWinHook[gWinHooks].id = id;
				gWinHook[gWinHooks].hHook = hHook;
				gWinHook[gWinHooks].lock++; //��ס�Ա���
				gWinHooks++;
			}
		}

		//ע�ᴰ��
		hHook = GetCurrentWinHook();
		gWnd[gWnds].hWnd = (HWND)hWnd;
		gWnd[gWnds].hHook = hHook;
		gWnd[gWnds].pOwner = this;
		gWnds++;
		
		//����
		mbHooked = TRUE;
		*outVal = 1;
		return S_OK;
	}
	return S_FALSE;

}

// Hook���ڼ��������Ӵ���
STDMETHODIMP CWinHook::HookAll(long hWnd, VARIANT_BOOL* outVal)
{
	*outVal = 0;

	if(!mbHooked)
	{
		int i = 0;

		//�����Ƿ���Ч
		if (!::IsWindow((HWND)hWnd))
		{
			return S_FALSE;
		}

		//����
		if (gWinHooks >= MaxWinHooks)
		{
			return FALSE;
		}
		if(gWnds >= MaxWnds)
		{
			return FALSE;
		}
		
		//������ǰ�����ظ�ע��ͬһ����
		for(i=0; i<gWnds; i++)	
		{
			if(gWnd[i].hWnd == (HWND)hWnd && gWnd[i].pOwner == this)
			{
				return S_FALSE;
			}
		}

		//ע�ᴰ��Hook
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
			if(hHook == NULL) //Hookʧ��
			{
				return S_FALSE;
			}
			else
			{
				gWinHook[gWinHooks].id = id;
				gWinHook[gWinHooks].hHook = hHook;
				gWinHook[gWinHooks].lock++; //��ס�Ա���
				gWinHooks++;
			}
		}

		//ע�ᴰ�ڼ��������Ӵ���
		hHook = GetCurrentWinHook();
		gWnd[gWnds].hWnd = (HWND)hWnd;
		gWnd[gWnds].hHook = hHook;
		gWnd[gWnds].pOwner = this;
		gWnds++;
		RegisterAllChildWindow((HWND)hWnd, hHook);
		
		//����
		mbHooked = TRUE;
		*outVal = 1;
		return S_OK;
	}
	return S_FALSE;

}

// ж�ش���Hook
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

// ����Hook����
void CWinHook::Destory()
{
	int i = 0;
	DWORD id = GetCurrentThreadId();
	HHOOK hHook = GetCurrentWinHook();
	
	if (hHook != NULL)
	{
		//ж�ص�ǰ����ע��Ĵ��ڣ�����VB��:
		//Set mclsWinHook1 = New TSubclass.WinHook
		//Set mclsWinHook2 = New TSubclass.WinHook
		//...
		for(int i=0; i<gWnds; i++)
		{
			if(gWnd[i].pOwner == this) //��ǰ����
			{
				//ע��Ĵ���������1
				gWnds--;
				
				//��ǰ�ƶ�����
				for(int k = i; k<gWnds; k++)
				{
					gWnd[k].hWnd = gWnd[k+1].hWnd;
					gWnd[k].hHook = gWnd[k+1].hHook;
					gWnd[k].pOwner = gWnd[k+1].pOwner;
				}
				i--;
			}
		}
		
		//����Ƿ���Ҫж��Hook
		bool bUnhook = true;
		for(i=0; i<gWnds; i++)
		{
			if(gWnd[i].hHook == hHook) //��Ȼ��ע��Ĵ��ڹҽ���Hook����
			{
				bUnhook = false; 
				break;
			}
		}

		//ж�ص�ǰ����ע���Hook
		if(bUnhook)
		{
			DWORD id = GetCurrentThreadId();
			for(int i=0; i<gWinHooks; i++)
			{
				if(gWinHook[i].id == id)//��ǰ����
				{
					gWinHook[i].lock--; //����
					if(gWinHook[i].lock == 0)
					{
						//ж��Hook
						UnhookWindowsHookEx(gWinHook[i].hHook); 
						
						//ע���Hook������1
						gWinHooks--;
						
						//��ǰ�ƶ�Hook
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
			MessageBox(0, TEXT("����ɾ�"), TEXT("WinHook"), 0);
		}
		*/

	}

}