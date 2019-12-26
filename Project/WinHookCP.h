#ifndef _WinHookCP_H_
#define _WinHookCP_H_

template <class T>
class CProxy_IWinHookEvents : public IConnectionPointImpl<T, &DIID__IWinHookEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:

	HRESULT Fire_OnMessage(LONG hWnd, LONG uMsg, LONG wParam, LONG lParam, BOOL* bEatIt)
	{
		CComVariant varResult;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[5];
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IDispatch* pDispatch = reinterpret_cast<IDispatch*>(sp.p);
			if (pDispatch != NULL)
			{
				VariantClear(&varResult);
				pvars[4] = hWnd;
				pvars[3] = uMsg;
				pvars[2] = wParam;
				pvars[1] = lParam;
				//pvars[0] = bEatIt;
				pvars[0].vt = VT_BOOL | VT_BYREF;
				pvars[0].byref = bEatIt;
				DISPPARAMS disp = { pvars, NULL, 5, 0 };
				pDispatch->Invoke(0x1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
			}
		}
		delete[] pvars;
		return varResult.scode;
		
	}

};
#endif