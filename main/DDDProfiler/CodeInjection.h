// CodeInjection.h : Declaration of the CCodeInjection

#pragma once
#include "resource.h"       // main symbols



#include "DDDProfiler_i.h"

#include "ProfileBase.h"

using namespace ATL;


// CCodeInjection

class ATL_NO_VTABLE CCodeInjection :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CCodeInjection, &CLSID_CodeInjection>,
	public ICodeInjection, CProfilerBase
{
public:
	CCodeInjection()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CODEINJECTION)


BEGIN_COM_MAP(CCodeInjection)
	COM_INTERFACE_ENTRY(ICodeInjection)
    COM_INTERFACE_ENTRY(ICorProfilerCallback)
    COM_INTERFACE_ENTRY(ICorProfilerCallback2)
    COM_INTERFACE_ENTRY(ICorProfilerCallback3)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:



};

OBJECT_ENTRY_AUTO(__uuidof(CodeInjection), CCodeInjection)
