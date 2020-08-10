#include "boolean_inlaid_interface.h"

bool boolean_inlaid_interface::do_browser(sxsdk::scene_interface* scene, void*) {
    scene->message("Done.");
    return true;
}