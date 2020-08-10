#include "sxsdk.cxx"
#include "boolean_inlaid_interface.h"

extern "C" SXSDKEXPORT void STDCALL create_interface(const IID & iid, int i, void** p, sxsdk::shade_interface * shade, void*) {
    sxsdk::browser_interface* u = new boolean_inlaid_interface(*shade);
    u->AddRef();
    *p = (void*)u;
}

extern "C" SXSDKEXPORT int STDCALL has_interface(const IID & iid, sxsdk::shade_interface * shade) {
    if (iid == browser_iid) return 1;
    return 0;
}                                                                                                                                                                                                                                                                                                               

extern "C" SXSDKEXPORT const char* STDCALL get_name(const IID & iid, int i, sxsdk::shade_interface * shade, void*) {
    if (iid == browser_iid) return boolean_inlaid_interface::get_name(shade);
    return 0;
}

extern "C" SXSDKEXPORT sx::uuid_class STDCALL get_uuid(const IID & iid, int i, void*) {
    if (iid == browser_iid) return boolean_inlaid_interface::uuid();
    return sx::uuid_class(0u);
}

extern "C" SXSDKEXPORT bool STDCALL is_resident(const IID & iid, int i, void*) {
    return false;
}       

extern "C" SXSDKEXPORT void STDCALL get_info(sxsdk::shade_plugin_info & info, sxsdk::shade_interface * shade, void*) {
    info.sdk_version = SHADE_BUILD_NUMBER;
    info.recommended_shade_version = 480000;
    info.major_version = 0;
    info.minor_version = 1;
    info.micro_version = 0;
    info.build_number = 0;
}

extern "C" SXSDKEXPORT bool STDCALL has_separate_interfaces(void*) {
    return false;
}