// dllmain.h : Declaration of module class.

class CDDDProfilerModule : public ATL::CAtlDllModuleT< CDDDProfilerModule >
{
public :
	DECLARE_LIBID(LIBID_DDDProfilerLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_DDDPROFILER, "{0E77C4B5-2AC2-443A-A58C-3ABE18E2A2D7}")
};

extern class CDDDProfilerModule _AtlModule;
