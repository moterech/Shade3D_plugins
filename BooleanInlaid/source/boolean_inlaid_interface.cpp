#include "boolean_inlaid_interface.h"

bool boolean_inlaid_interface::do_browser(sxsdk::scene_interface* scene, void*) {
    sxsdk::shape_class* source_shapes[MAX_SHAPES];
    const int len = scene->get_active_shapes(source_shapes);
    if (len > MAX_SHAPES)
    {
        scene->message("Aborted. There are too many shapes.");
        return false;
    }
    // =(表面材質を置き換える) が設定された形状を抽出
    sxsdk::shape_class* base_shapes[MAX_SHAPES] = { nullptr };
    sxsdk::shape_class* inlaying_shapes[MAX_SHAPES] = { nullptr };
    for (size_t i = 0; i < len; i++)
    {
        if (source_shapes[i]->has_special_character('='))
        {
            inlaying_shapes[i] = source_shapes[i];
        }
        else
        {
            base_shapes[i] = source_shapes[i];
        }
    }
    // ブーリアン演算による置き換え処理を実行
    for (size_t i = 0; i < len; i++)
    {
        if (base_shapes[i] != nullptr) {
            sxsdk::shape_class* tmp_shapes[MAX_SHAPES] = { nullptr };
            // 置き換える形状との交差部分をくり抜いて穴をあける
            scene->select_shapes(1, &base_shapes[i]);
            scene->begin_boolean_shapes();
            scene->add_boolean_shape(base_shapes[i]);
            for (size_t j = 0; j < len; j++)
            {
                if (inlaying_shapes[j] != nullptr) {
                    scene->add_boolean_shape(inlaying_shapes[j]);
                }
            }
            scene->end_boolean_shapes();
            scene->do_manifold_boolean(sxsdk::smlib::boolean_operation_type::bo_surface_different, -1, -1, sxsdk::enums::surface_replicator_subdivision_level::surface_replicator_subdivision_regular, true, true);
            scene->get_active_shapes(&tmp_shapes[i]);
            // 置き換える形状との交差部分を表面として切り抜き
            for (size_t j = 0; j < len; j++)
            {
                if (inlaying_shapes[j] != nullptr) {
                    scene->select_shapes(1, &base_shapes[i]);
                    scene->begin_boolean_shapes();
                    scene->add_boolean_shape(base_shapes[i]);
                    scene->add_boolean_shape(inlaying_shapes[j]);
                    scene->end_boolean_shapes();
                    scene->do_manifold_boolean(sxsdk::smlib::boolean_operation_type::bo_surface_intersection, -1, -1, sxsdk::enums::surface_replicator_subdivision_level::surface_replicator_subdivision_regular, true, true);
                    scene->get_active_shapes(&tmp_shapes[j]);
                    // 切り抜いた表面の材質を設定
                    sxsdk::shape_class *surface = tmp_shapes[j]->get_son()->get_bro();
                    sxsdk::polygon_mesh_class& mesh = surface->get_polygon_mesh();
                    for (size_t k = 0;  k < mesh.get_number_of_face_groups();  k++)
                    {
                        mesh.set_face_group_surface(k, inlaying_shapes[j]->get_master_surface());
                    }
                }
            }
            // くり抜いた形状と表面を合体
            scene->begin_boolean_shapes();
            for (size_t j = 0; j < len; j++)
            {
                if (tmp_shapes[j] != nullptr) {
                    scene->add_boolean_shape(tmp_shapes[j]);
                }
            }
            scene->end_boolean_shapes();
            scene->do_manifold_boolean(sxsdk::smlib::boolean_operation_type::bo_merge, -1, -1, sxsdk::enums::surface_replicator_subdivision_level::surface_replicator_subdivision_no_subdivision, false, false);
            // 不要な形状を削除
            for (size_t j = 0; j < len; j++)
            {
                if (tmp_shapes[j] != nullptr) {
                    scene->select_shapes(1, &tmp_shapes[j]);
                    scene->clear();
                }
            }
        }
    }
    scene->message("Done.");
    return true;
}