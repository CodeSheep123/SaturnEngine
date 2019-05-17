#include "Subsystems/Renderer/Renderer.hpp"

#include "Core/Application.hpp"
#include "Subsystems/Logging/LogSystem.hpp"
#include "Subsystems/Math/Math.hpp"
#include "Subsystems/Scene/Scene.hpp"
#include "Utility/Exceptions.hpp"
#include "Utility/bind_guard.hpp"

namespace Saturn {

static std::vector<float> screen_vertices = {
    // Vertices	        Texture coords
    -1.0f, 1.0f,  0.0f, 0.0f, 1.0f, // TL
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // BL
    1.0f,  -1.0f, 0.0f, 1.0f, 0.0f, // BR
    1.0f,  1.0f,  0.0f, 1.0f, 1.0f, // TR
};

Renderer::Renderer(CreateInfo create_info) :
    app(create_info.app), screen_size(create_info.screen_size) {

    // Setup the framebuffer
    Framebuffer::CreateInfo framebuffer_create_info;
    framebuffer_create_info.size = screen_size;
    framebuf.assign(framebuffer_create_info);

    // Create default viewport
    add_viewport(Viewport(0, 0, screen_size.x, screen_size.y));
    // Set it as the active viewport
    Viewport::set_active(get_viewport(0));

    std::vector<VertexAttribute> screen_attributes;
    screen_attributes.push_back({0, 3}); // Position is a vec3
    screen_attributes.push_back({1, 2}); // TexCoords is a vec2

    screen.assign({screen_attributes, screen_vertices, {0, 1, 2, 0, 3, 2}});

    default_shader = AssetManager<Shader>::get_resource(
        "resources/shaders/postprocessing/default.sh");
    if (!default_shader.is_loaded()) {
        LogSystem::write(LogSystem::Severity::Error,
                         "Failed to load default shader");
    }

    LogSystem::write(LogSystem::Severity::Info, "Renderer created.");
    LogSystem::write(LogSystem::Severity::Warning,
                     "No postprocessing shader system in place. Default shader "
                     "will be used");
}

Renderer::~Renderer() {}

void Renderer::clear(
    Color clear_color,
    GLenum flags /*= GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT*/) {

    bind_guard<Framebuffer> framebuf_guard(framebuf);

    glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
    glClear(flags);
}

static Components::Transform
make_absolute_transform(Components::Transform const& old_transform) {
    auto* object = old_transform.entity;
    if (!object->has_parent()) {
        return old_transform;
    } else {
        auto parent = object->parent();
        auto parent_trans = make_absolute_transform(
            parent->get_component<Components::Transform>());

        Components::Transform new_trans = old_transform;
        new_trans.position += parent_trans.position;
        new_trans.rotation += parent_trans.rotation;
        new_trans.scale *= parent_trans.scale;

        return new_trans;
    }
}

void Renderer::render_scene(Scene& scene) {
    // Temporary

    bind_guard<Framebuffer> framebuf_guard(framebuf);
    // All temporary obviously

    // Render every viewport
    for (auto& vp : viewports) {
        if (!vp.has_camera()) continue;
        Viewport::set_active(vp);
        for (auto [relative_transform, mesh, material] :
             scene.ecs.select<Components::Transform, Components::StaticMesh,
                              Components::Material>()) {
            auto& shader = material.shader.get();
            auto& vtx_array = mesh.mesh->get_vertices();

            auto transform = make_absolute_transform(relative_transform);

            auto cam_id = vp.get_camera();
            auto& cam = scene.ecs.get_with_id<Components::Camera>(cam_id);
            auto& cam_trans =
                cam.entity->get_component<Components::Transform>();

            auto projection = glm::perspective(glm::radians(cam.fov),
                                               (float)vp.dimensions().x /
                                                   (float)vp.dimensions().y,
                                               0.1f, 100.0f);

            auto view = glm::lookAt(cam_trans.position,
                                    cam_trans.position + cam.front, cam.up);

            auto model = glm::mat4(1.0f);
            // Apply transformations

            model = glm::translate(model, transform.position);
            model = glm::rotate(model, {glm::radians(transform.rotation.x),
                                        glm::radians(transform.rotation.y),
                                        glm::radians(transform.rotation.z)});

            model = glm::scale(model, transform.scale);

            bind_guard<Shader> shader_guard(shader);
            bind_guard<VertexArray> vao_guard(vtx_array);

            shader.set_mat4("model", model);
            shader.set_mat4("view", view);
            shader.set_mat4("projection", projection);

            if (material.texture.is_loaded()) {
                // If there is a texture
                Texture::bind(material.texture.get());
                shader.set_int("tex", material.texture->unit() - GL_TEXTURE0);
            }

            glDrawElements(GL_TRIANGLES, vtx_array.index_size(),
                           GL_UNSIGNED_INT, nullptr);

            if (material.texture.is_loaded()) {
                Texture::unbind(material.texture.get());
            }
        }
    }
}

void Renderer::update_screen() {
    bind_guard<Framebuffer> framebuf_guard(screen_framebuf);

    Viewport::set_active(get_viewport(0));

    // Bind VAO
    bind_guard<VertexArray> screen_guard(screen);
    bind_guard<Ebo> ebo_guard(screen.ebo);

    // Temporarily disable some GL functionality
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    // Set (postprocessing) shader
    bind_guard<Shader> shader_guard(default_shader.get());

    // Render framebuffer texture to the screen
    glBindTexture(GL_TEXTURE_2D, framebuf.texture);
    glDrawElements(GL_TRIANGLES, screen.index_size(), GL_UNSIGNED_INT, nullptr);

    //	  Re enable functionality
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

Viewport& Renderer::get_viewport(std::size_t index) {
    if (index >= viewports.size()) {
        throw InvalidViewportException("Invalid viewport with index " +
                                       std::to_string(index) + " requested.");
    }
    return viewports[index];
}

std::size_t Renderer::add_viewport(Viewport vp) {
    viewports.push_back(vp);
    return viewports.size() - 1;
}

} // namespace Saturn