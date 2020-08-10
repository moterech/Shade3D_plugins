#include "sxsdk.cxx"

#define MAX_SHAPES 16

struct boolean_inlaid_interface : public sxsdk::browser_interface
{
    boolean_inlaid_interface(sxsdk::shade_interface& shade) : shade(shade) {};
    static const char* get_name(sxsdk::shade_interface* shade) { return shade->gettext("title"); };
    virtual int get_shade_version() const { return SHADE_BUILD_NUMBER; }
    static const sx::uuid_class uuid() { return sx::uuid_class("9255A624-549E-11D9-8D8E-000A95BACEB2"); }
private:
    sxsdk::shade_interface& shade;
    virtual bool do_browser(sxsdk::scene_interface* scene, void*);
};