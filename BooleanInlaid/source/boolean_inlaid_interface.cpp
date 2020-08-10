#include "boolean_inlaid_interface.h"

bool boolean_inlaid_interface::do_browser(sxsdk::scene_interface* scene, void*) {
    sxsdk::shape_class* shapes[MAX_SHAPES];
    const int len = scene->get_active_shapes(shapes);
    if (len > MAX_SHAPES)
    {
        scene->message("Aborted. There are too many shapes.");
        return false;
    }
    if (len > 1)
    {
        scene->begin_boolean_shapes();
        scene->add_boolean_shape(shapes[0]);
        scene->add_boolean_shape(shapes[1]);
        scene->do_manifold_boolean(sxsdk::smlib::boolean_operation_type::bo_different, -1, -1, sxsdk::enums::surface_replicator_subdivision_level::surface_replicator_subdivision_regular, true, true);
        scene->end_boolean_shapes();
    }
    scene->message("Done.");
    return true;
}