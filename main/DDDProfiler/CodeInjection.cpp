// CodeInjection.cpp : Implementation of CCodeInjection
#include "stdafx.h"
#include "CodeInjection.h"

// CCodeInjection
HRESULT STDMETHODCALLTYPE CCodeInjection::Initialize( 
    /* [in] */ IUnknown *pICorProfilerInfoUnk) 
{
    OLECHAR szGuid[40]={0};
    int nCount = ::StringFromGUID2(CLSID_CodeInjection, szGuid, 40);
    ATLTRACE(_T("::Initialize - %s"), W2CT(szGuid));
     
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CCodeInjection::Shutdown( void) 
{
    ATLTRACE(_T("::Shutdown"));
    return S_OK;
}