// CodeInjection.cpp : Implementation of CCodeInjection
#include "stdafx.h"
#include "CodeInjection.h"

#include "Method.h"

// CCodeInjection
HRESULT STDMETHODCALLTYPE CCodeInjection::Initialize( 
    /* [in] */ IUnknown *pICorProfilerInfoUnk) 
{
    OLECHAR szGuid[40]={0};
    int nCount = ::StringFromGUID2(CLSID_CodeInjection, szGuid, 40);
    ATLTRACE(_T("::Initialize - %s"), W2CT(szGuid));
    
    m_profilerInfo3 = pICorProfilerInfoUnk;
    if (m_profilerInfo3 == NULL) return E_FAIL;

    DWORD dwMask = 0;
    dwMask |= COR_PRF_MONITOR_MODULE_LOADS;			// Controls the ModuleLoad, ModuleUnload, and ModuleAttachedToAssembly callbacks.
    dwMask |= COR_PRF_MONITOR_JIT_COMPILATION;	    // Controls the JITCompilation, JITFunctionPitched, and JITInlining callbacks.
    dwMask |= COR_PRF_DISABLE_INLINING;				// Disables all inlining.
    dwMask |= COR_PRF_DISABLE_OPTIMIZATIONS;		// Disables all code optimizations.

    m_profilerInfo3->SetEventMask(dwMask);

    return S_OK;
}

HRESULT STDMETHODCALLTYPE CCodeInjection::Shutdown( void) 
{
    ATLTRACE(_T("::Shutdown"));
    return S_OK;
}

/// <summary>Handle <c>ICorProfilerCallback::ModuleAttachedToAssembly</c></summary>
/// <remarks>Inform the host that we have a new module attached and that it may be 
/// of interest</remarks>
HRESULT STDMETHODCALLTYPE CCodeInjection::ModuleAttachedToAssembly( 
    /* [in] */ ModuleID moduleId,
    /* [in] */ AssemblyID assemblyId)
{
    ULONG dwNameSize = 512;
    WCHAR szAssemblyName[512] = {0};
    COM_FAIL_RETURN(m_profilerInfo3->GetAssemblyInfo(assemblyId, 
        dwNameSize, &dwNameSize, szAssemblyName, NULL, NULL), S_OK);
    ATLTRACE(_T("::ModuleAttachedToAssembly(%X => ?, %X => %s)"), 
        moduleId, assemblyId, W2CT(szAssemblyName));   
    return S_OK;
}

std::wstring CCodeInjection::GetMethodName(FunctionID functionId, 
    ModuleID& funcModule, mdToken& funcToken)
{
    ClassID funcClass;
	COM_FAIL_RETURN(m_profilerInfo3->GetFunctionInfo2(functionId, 
        NULL, &funcClass, &funcModule, &funcToken, 0, NULL, 
        NULL), std::wstring());

    CComPtr<IMetaDataImport2> metaDataImport2;
	COM_FAIL_RETURN(m_profilerInfo3->GetModuleMetaData(funcModule, 
        ofRead, IID_IMetaDataImport2, (IUnknown**) &metaDataImport2), std::wstring());

    ULONG dwNameSize = 512;
    WCHAR szMethodName[512] = {};
	COM_FAIL_RETURN(metaDataImport2->GetMethodProps(funcToken, NULL, 
        szMethodName, dwNameSize, &dwNameSize, NULL, 
        NULL, NULL, NULL, NULL), S_OK);

    return std::wstring(szMethodName);
}

/// <summary>Handle <c>ICorProfilerCallback::JITCompilationStarted</c></summary>
/// <remarks>The 'workhorse' </remarks>
HRESULT STDMETHODCALLTYPE CCodeInjection::JITCompilationStarted( 
        /* [in] */ FunctionID functionId, /* [in] */ BOOL fIsSafeToBlock) 
{
    ModuleID moduleId; mdToken funcToken;
    std::wstring methodName = GetMethodName(functionId, 
        moduleId, funcToken);
    ATLTRACE(_T("::JITCompilationStarted(%X -> %s)"), 
        functionId, methodName);

    if (L"TargetMethod" == methodName) {
        // get method body
        LPCBYTE pMethodHeader = NULL;
        ULONG iMethodSize = 0;
        COM_FAIL_RETURN(m_profilerInfo3->GetILFunctionBody(
            moduleId, funcToken, &pMethodHeader, &iMethodSize), 
            S_OK);

        // parse IL
        Method instMethod((IMAGE_COR_ILMETHOD*)pMethodHeader); // <--

        // allocate memory
        CComPtr<IMethodMalloc> methodMalloc;
        m_profilerInfo3->GetILFunctionBodyAllocator(moduleId, 
            &methodMalloc);
        void* pNewMethod = methodMalloc->Alloc(instMethod.GetMethodSize());

        // write new method
        instMethod.WriteMethod((IMAGE_COR_ILMETHOD*)pNewMethod);
        m_profilerInfo3->SetILFunctionBody(moduleId, funcToken, 
            (LPCBYTE) pNewMethod);
    }

    return S_OK;
}