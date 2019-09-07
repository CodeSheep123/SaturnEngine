#ifndef SATURN_EDITOR_HPP_
#define SATURN_EDITOR_HPP_

#ifdef WITH_EDITOR

#    include <cstddef>
#    include <vector>

#    include "Editor/EditorLog.hpp"
#    include "Editor/EditorPreferencesWidget.hpp"
#    include "Editor/EntityTree.hpp"

namespace Saturn {

enum class SystemUpdateMode;

class Application;
class Scene;
class SceneObject;

namespace Editor {

class Editor {
public:
    Editor(Application& app);

    void setup_viewports();
    SystemUpdateMode get_update_mode();

    // Must be called at the start of the frame
    void render(Scene& scene);
    void frame_end();

private:
    void show_menu_bar(Scene& scene);
    void on_scene_reload(Scene& scene);
    void create_entity(Scene& scene, std::string const& name);
	void create_editor_camera(Scene& scene);
	void on_playmode_enter(Scene& scene);

    Application* app;
    SceneObject* editor_camera;
    std::size_t scene_view_viewport_id = 0;

    struct Widgets {
        EntityTree entity_tree;
        EditorPreferencesWidget preferences;
    } editor_widgets;

	bool playmode_active = false;
};

} // namespace Editor
} // namespace Saturn

#endif
#endif
