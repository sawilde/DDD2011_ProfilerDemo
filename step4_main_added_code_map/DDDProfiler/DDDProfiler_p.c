

/* this ALWAYS GENERATED file contains the proxy stub code */


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

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "DDDProfiler_i.h"

#define TYPE_FORMAT_STRING_SIZE   3                                 
#define PROC_FORMAT_STRING_SIZE   1                                 
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _DDDProfiler_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } DDDProfiler_MIDL_TYPE_FORMAT_STRING;

typedef struct _DDDProfiler_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } DDDProfiler_MIDL_PROC_FORMAT_STRING;

typedef struct _DDDProfiler_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } DDDProfiler_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const DDDProfiler_MIDL_TYPE_FORMAT_STRING DDDProfiler__MIDL_TypeFormatString;
extern const DDDProfiler_MIDL_PROC_FORMAT_STRING DDDProfiler__MIDL_ProcFormatString;
extern const DDDProfiler_MIDL_EXPR_FORMAT_STRING DDDProfiler__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ICodeInjection_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ICodeInjection_ProxyInfo;



#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const DDDProfiler_MIDL_PROC_FORMAT_STRING DDDProfiler__MIDL_ProcFormatString =
    {
        0,
        {

			0x0
        }
    };

static const DDDProfiler_MIDL_TYPE_FORMAT_STRING DDDProfiler__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */

			0x0
        }
    };


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: ICodeInjection, ver. 0.0,
   GUID={0xF17D4A2B,0x29ED,0x4E36,{0xBE,0xD3,0xE5,0x04,0x0D,0x01,0x8A,0x4E}} */

#pragma code_seg(".orpc")
static const unsigned short ICodeInjection_FormatStringOffsetTable[] =
    {
    0
    };

static const MIDL_STUBLESS_PROXY_INFO ICodeInjection_ProxyInfo =
    {
    &Object_StubDesc,
    DDDProfiler__MIDL_ProcFormatString.Format,
    &ICodeInjection_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ICodeInjection_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    DDDProfiler__MIDL_ProcFormatString.Format,
    &ICodeInjection_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(3) _ICodeInjectionProxyVtbl = 
{
    0,
    &IID_ICodeInjection,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy
};

const CInterfaceStubVtbl _ICodeInjectionStubVtbl =
{
    &IID_ICodeInjection,
    &ICodeInjection_ServerInfo,
    3,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    DDDProfiler__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x700022b, /* MIDL Version 7.0.555 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _DDDProfiler_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_ICodeInjectionProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _DDDProfiler_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_ICodeInjectionStubVtbl,
    0
};

PCInterfaceName const _DDDProfiler_InterfaceNamesList[] = 
{
    "ICodeInjection",
    0
};


#define _DDDProfiler_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _DDDProfiler, pIID, n)

int __stdcall _DDDProfiler_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_DDDProfiler_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo DDDProfiler_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _DDDProfiler_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _DDDProfiler_StubVtblList,
    (const PCInterfaceName * ) & _DDDProfiler_InterfaceNamesList,
    0, /* no delegation */
    & _DDDProfiler_IID_Lookup, 
    1,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

