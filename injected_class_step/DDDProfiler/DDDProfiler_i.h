

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sat May 21 10:57:42 2011
 */
/* Compiler settings for DDDProfiler.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __DDDProfiler_i_h__
#define __DDDProfiler_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICodeInjection_FWD_DEFINED__
#define __ICodeInjection_FWD_DEFINED__
typedef interface ICodeInjection ICodeInjection;
#endif 	/* __ICodeInjection_FWD_DEFINED__ */


#ifndef __CodeInjection_FWD_DEFINED__
#define __CodeInjection_FWD_DEFINED__

#ifdef __cplusplus
typedef class CodeInjection CodeInjection;
#else
typedef struct CodeInjection CodeInjection;
#endif /* __cplusplus */

#endif 	/* __CodeInjection_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ICodeInjection_INTERFACE_DEFINED__
#define __ICodeInjection_INTERFACE_DEFINED__

/* interface ICodeInjection */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_ICodeInjection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F17D4A2B-29ED-4E36-BED3-E5040D018A4E")
    ICodeInjection : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ICodeInjectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICodeInjection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICodeInjection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICodeInjection * This);
        
        END_INTERFACE
    } ICodeInjectionVtbl;

    interface ICodeInjection
    {
        CONST_VTBL struct ICodeInjectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICodeInjection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICodeInjection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICodeInjection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICodeInjection_INTERFACE_DEFINED__ */



#ifndef __DDDProfilerLib_LIBRARY_DEFINED__
#define __DDDProfilerLib_LIBRARY_DEFINED__

/* library DDDProfilerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_DDDProfilerLib;

EXTERN_C const CLSID CLSID_CodeInjection;

#ifdef __cplusplus

class DECLSPEC_UUID("BDD57A0C-D4F7-486D-A8CA-86070DC12FA0")
CodeInjection;
#endif
#endif /* __DDDProfilerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


