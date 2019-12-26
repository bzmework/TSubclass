/*
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'@Module Name:  MouseHook(.cpp)
'@Main Func:    ���Hook
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


// ��ȡ��ǰ����ע������Hook
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

// ���Hook����
LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	HHOOK hHook = GetCurrentMouseHook();
	long bEatIt = 0;
	
	//ֻ����Ϣ�ַ�����ǰ����
	if (nCode == HC_ACTION)
	{
		MOUSEHOOKSTRUCT lpMHx;
		long hWnd = 0;
		UINT uMsg = 0;
		long x = 0;
		long y = 0;
		long wMouseData = 0;
		
		//�ռ���Ϣ
		CopyMemory(&lpMHx, (void*)lParam, sizeof(lpMHx));
		hWnd = (long)lpMHx.hwnd;
		uMsg = wParam;
		x = lpMHx.pt.x;
		y = lpMHx.pt.y;
		wMouseData = lpMHx.dwExtraInfo;
		if (_WIN32_WINNT) //NTϵͳȡ�������־���������Ҫ���⴦��
		{
			MSLLHOOKSTRUCT lpMHn;
			CopyMemory(&lpMHn, (void*)lParam, sizeof(lpMHn));
			wMouseData = lpMHn.dwExtraInfo;
		}
	
		//��Ϣ�ַ�
		for(int i=0; i<gMouseObjs; i++)
		{
			if(gMouseObj[i].hHook == hHook)
			{	
				gMouseObj[i].pOwner->Fire_OnMessage(hWnd, uMsg, x, y, wMouseData, &bEatIt);
			}
		}
	}
	
	//����
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
		MSDN: ����CallNextHookEx�ǿ�ѡ�ģ���ǿ���Ƽ�������
		�����Ѿ���װ�˹��ӵ�Ӧ�ó��򽫲����յ�����֪ͨ�������������Ϊ����ȷ��
		��Ӧ�õ���CallNextHookEx��������������Ҫ��ֹ����Ӧ�ó��򿴵�֪ͨ��
		*/
		return CallNextHookEx(hHook, nCode, wParam, lParam);
	}
}

// ϵͳ���ɣ���Ҫ�޸�
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

//����
STDMETHODIMP CMouseHook::AboutMe()
{
	MessageBox(NULL, ABOUTME, COPYRIGHT, MB_ICONWARNING | MB_OK);
	return S_OK;
}

// ���Hook
STDMETHODIMP CMouseHook::Hook(VARIANT_BOOL* outVal)
{
	*outVal = 0;

	if (!mbHooked)
	{
		int i = 0;

		//����
		if (gMouseHooks >= MaxMouseHooks)
		{
			return FALSE;
		}
		if (gMouseObjs >= MaxMouseObjs)
		{
			return FALSE;
		}

		//�������ظ�ע��
		for(i=0; i<gMouseObjs; i++)
		{
			if(gMouseObj[i].pOwner == this)
			{
				return FALSE;
			}
		}
	
		//ע�����Hook
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
			SetWindowsHookEx������Ӧ�ó�����Ĺ��Ӵ�������װ���������ϡ�
			������װһ�����Ӵ�����������ϵͳ���ض����͵��¼���
			��Щ�¼�Ҫô���ض����̹߳�����Ҫô��ϵͳ�е������̹߳�����
			*/
			hHook = SetWindowsHookEx(WH_MOUSE, (HOOKPROC) MouseHookProc, GetModuleHandle(NULL), id);
			if(hHook == NULL) //Hookʧ��
			{
				return S_FALSE;
			}
			else
			{
				gMouseHook[gMouseHooks].id = id;
				gMouseHook[gMouseHooks].hHook = hHook;
				gMouseHook[gMouseHooks].lock++; //��ס�Ա���
				gMouseHooks++;
			}
		}
		
		//ע�����
		gMouseObj[gMouseObjs].hHook = hHook;
		gMouseObj[gMouseObjs].pOwner = this;
		gMouseObjs++;
		
		//����
		mbHooked = TRUE;
		*outVal = 1;
		return S_OK;
	}
	return S_FALSE;

}

// ж�����Hook
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

// ����Hook����
void CMouseHook::Destory()
{	
	int i = 0;
	DWORD id = GetCurrentThreadId();
	HHOOK hHook = GetCurrentMouseHook();
	
	if (hHook != NULL)
	{
		//ж�ص�ǰMouse��������VB��:
		//Set mclsMouseHook1 = New TSubclass.MouseHook
		//Set mclsMouseHook2 = New TSubclass.MouseHook
		//...
		for(i=0; i<gMouseObjs; i++)
		{
			if(gMouseObj[i].pOwner == this) //��ǰ����
			{
				//ע��Ĵ���������1
				gMouseObjs--;
				
				//��ǰ�ƶ�����
				for(int k = i; k<gMouseObjs; k++)
				{
					gMouseObj[k].hHook = gMouseObj[k+1].hHook;
					gMouseObj[k].pOwner = gMouseObj[k+1].pOwner;
				}
				i--;
			}
		}
		
		//����Ƿ���Ҫж��Hook
		bool bUnhook = true;
		for(i=0; i<gMouseObjs; i++)
		{
			if(gMouseObj[i].hHook == hHook) //��Ȼ��ע��Ķ���ҽ���Hook����
			{
				bUnhook = false; 
				break;
			}
		}
		
		//ж�ص�ǰ����ע���Hook
		if(bUnhook)
		{
			for(i=0; i<gMouseHooks; i++)
			{
				if(gMouseHook[i].id == id)
				{
					gMouseHook[i].lock--; //����
					if(gMouseHook[i].lock == 0)
					{
						//ж��Hook
						UnhookWindowsHookEx(gMouseHook[i].hHook); 
						
						//ע���Hook������1
						gMouseHooks--;
						
						//��ǰ�ƶ�Hook
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
			MessageBox(0, TEXT("����ɾ�"), TEXT("MouseHook"), 0);
		}
		*/

	}
}