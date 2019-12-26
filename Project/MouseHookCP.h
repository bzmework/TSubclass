#ifndef _MOUSEHOOKCP_H_
#define _MOUSEHOOKCP_H_


template <class T>
class CProxy_IMouseHookEvents : public IConnectionPointImpl<T, &DIID__IMouseHookEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	HRESULT Fire_OnMessage(LONG hWnd, LONG uMsg, LONG x, LONG y, LONG wMouseData, LONG * bEatIt)
	{
		CComVariant varResult;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[6];
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
				pvars[5] = hWnd;
				pvars[4] = uMsg;
				pvars[3] = x;
				pvars[2] = y;
				pvars[1] = wMouseData;
				//pvars[0] = bEatIt;
				pvars[0].vt = VT_BOOL | VT_BYREF;
				pvars[0].byref = bEatIt;
				DISPPARAMS disp = { pvars, NULL, 6, 0 };
				pDispatch->Invoke(0x1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
			}
		}
		delete[] pvars;
		return varResult.scode;
	
	}
};
#endif