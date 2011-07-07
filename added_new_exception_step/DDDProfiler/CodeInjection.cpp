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

HRESULT CCodeInjection::GetMsCorlibRef(ModuleID moduleId, mdModuleRef &mscorlibRef)
{
    // get interfaces
    CComPtr<IMetaDataEmit> metaDataEmit;
    COM_FAIL_RETURN(m_profilerInfo3->GetModuleMetaData(moduleId, 
        ofRead | ofWrite, IID_IMetaDataEmit, (IUnknown**)&metaDataEmit), S_OK);      
    
    CComPtr<IMetaDataAssemblyEmit> metaDataAssemblyEmit;
    COM_FAIL_RETURN(metaDataEmit->QueryInterface(
        IID_IMetaDataAssemblyEmit, (void**)&metaDataAssemblyEmit), S_OK);

    // find mscorlib
    ASSEMBLYMETADATA assembly;
    ZeroMemory(&assembly, sizeof(assembly));
    assembly.usMajorVersion = 4;
    assembly.usMinorVersion = 0;
    assembly.usBuildNumber = 0; 
    assembly.usRevisionNumber = 0;
    BYTE publicKey[] = { 0xB7, 0x7A, 0x5C, 0x56, 0x19, 0x34, 0xE0, 0x89 };
    COM_FAIL_RETURN(metaDataAssemblyEmit->DefineAssemblyRef(publicKey, 
        sizeof(publicKey), L"mscorlib", &assembly, NULL, 0, 0, 
        &mscorlibRef), S_OK);
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

    if (lstrcmp(L"ProfilerTarget", szAssemblyName) == 0) {
        m_magicExceptionCtor = 0;
        // get reference to mscorlib
        mdModuleRef mscorlibRef;
        COM_FAIL_RETURN(GetMsCorlibRef(moduleId, mscorlibRef), S_OK);

        // get interfaces
        CComPtr<IMetaDataEmit> metaDataEmit;
        COM_FAIL_RETURN(m_profilerInfo3->GetModuleMetaData(moduleId, 
            ofRead | ofWrite, IID_IMetaDataEmit, (IUnknown**)&metaDataEmit), S_OK);

        static COR_SIGNATURE ctorCallSignature[] = 
        {
            IMAGE_CEE_CS_CALLCONV_DEFAULT | IMAGE_CEE_CS_CALLCONV_HASTHIS,   
            0x00,                                   
            ELEMENT_TYPE_VOID
        };

        // get base type and constructor
        mdTypeRef exceptionTypeRef;
        COM_FAIL_RETURN(metaDataEmit->DefineTypeRefByName(mscorlibRef, 
             L"System.Exception", &exceptionTypeRef), S_OK);
        mdMemberRef exceptionCtor;
        COM_FAIL_RETURN(metaDataEmit->DefineMemberRef(exceptionTypeRef, 
            L".ctor", ctorCallSignature, sizeof(ctorCallSignature), 
            &exceptionCtor), S_OK);

        // define new type in our module
        mdTypeDef magicExceptionType;
        COM_FAIL_RETURN(metaDataEmit->DefineTypeDef(
            L"DDDMelbourne2011.MagicException", 
            tdPublic | tdSerializable, exceptionTypeRef, NULL,  
            &magicExceptionType), S_OK);

        // define constructor 
        COM_FAIL_RETURN(metaDataEmit->DefineMethod(magicExceptionType, 
            L".ctor", 
            mdPublic | mdHideBySig | mdSpecialName | mdRTSpecialName, 
            ctorCallSignature, sizeof(ctorCallSignature), 0, 
            miIL | miManaged | miPreserveSig, &m_magicExceptionCtor), S_OK);

        // build and allocate constructor body
        BYTE data[] = {(0x01 << 2) | CorILMethod_TinyFormat, CEE_RET};
        Method ctorMethod((IMAGE_COR_ILMETHOD*)data);
        InstructionList instructions;
        instructions.push_back(new Instruction(CEE_LDARG_0));
        instructions.push_back(new Instruction(CEE_CALL, exceptionCtor));
        ctorMethod.InsertSequenceInstructionsAtOffset(0, instructions);
        ctorMethod.DumpIL();

        CComPtr<IMethodMalloc> methodMalloc;
        COM_FAIL_RETURN(m_profilerInfo3->GetILFunctionBodyAllocator(
            moduleId, &methodMalloc), S_OK);

        void* pMethodBody = methodMalloc->Alloc(ctorMethod.GetMethodSize());
        ctorMethod.WriteMethod((IMAGE_COR_ILMETHOD*)pMethodBody);

        COM_FAIL_RETURN(m_profilerInfo3->SetILFunctionBody(moduleId, 
            m_magicExceptionCtor, (LPCBYTE)pMethodBody), S_OK);
    }

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
        functionId, W2CT(methodName.c_str()));

    if (L"TargetMethod" == methodName && m_magicExceptionCtor !=0 ) {
        // get method body
        LPCBYTE pMethodHeader = NULL;
        ULONG iMethodSize = 0;
        COM_FAIL_RETURN(m_profilerInfo3->GetILFunctionBody(
            moduleId, funcToken, &pMethodHeader, &iMethodSize), 
            S_OK);

        // parse IL
        Method instMethod((IMAGE_COR_ILMETHOD*)pMethodHeader); // <--

        // insert new IL block
        InstructionList instructions;
        instructions.push_back(
            new Instruction(CEE_NEWOBJ, m_magicExceptionCtor));
        instructions.push_back(new Instruction(CEE_THROW));
        instMethod.InsertSequenceInstructionsAtOriginalOffset(
            1, instructions);

        instMethod.DumpIL();

        // allocate memory
        CComPtr<IMethodMalloc> methodMalloc;
        COM_FAIL_RETURN(m_profilerInfo3->GetILFunctionBodyAllocator(
            moduleId, &methodMalloc), S_OK);
        void* pNewMethod = methodMalloc->Alloc(instMethod.GetMethodSize());

        // write new method
        instMethod.WriteMethod((IMAGE_COR_ILMETHOD*)pNewMethod);
        COM_FAIL_RETURN(m_profilerInfo3->SetILFunctionBody(moduleId, 
            funcToken, (LPCBYTE) pNewMethod), S_OK);
    }

    return S_OK;
}