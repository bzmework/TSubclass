#ifndef _SUBCLASSCP_H_
#define _SUBCLASSCP_H_

template <class T>
class CProxy_ISubclassEvents : public IConnectionPointImpl<T, &DIID__ISubclassEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:

	HRESULT Fire_OnMessage(LONG uMsg, LONG wParam, LONG lParam, BOOL * bHandled, LONG * lRetVal)
	{
		CComVariant varResult;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[4];
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
				
				//注意:参数类型必须和IDL中事件的参数类型保持一致,否则事件不会正确触发
				pvars[3] = uMsg;
				pvars[2] = wParam;
				pvars[1] = lParam;
				//pvars[0] = bHandled;
				pvars[0].vt = VT_BOOL | VT_BYREF; //VT_I4 | VT_BYREF;
				pvars[0].byref = bHandled;
				DISPPARAMS disp = { pvars, NULL, 4, 0 };
				pDispatch->Invoke(0x1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
			}
		}
		delete[] pvars;

		*lRetVal = varResult.lVal; //返回值
		return varResult.scode;
		
	}

	HRESULT Fire_AfterMessage(LONG uMsg, LONG wParam, LONG lParam)
	{
		CComVariant varResult;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		CComVariant* pvars = new CComVariant[3];
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
				pvars[2] = uMsg;
				pvars[1] = wParam;
				pvars[0] = lParam;
				DISPPARAMS disp = { pvars, NULL, 3, 0 };
				pDispatch->Invoke(0x2, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);
			}
		}
		delete[] pvars;
		return varResult.scode;
		
	}

};
#endif