#include "Subsystems/Renderer/Modules/MeshRenderModule.hpp"

#include "Subsystems/Renderer/Modules/DepthMapPass.hpp"

#include "Subsystems/AssetManager/AssetManager.hpp"
#include "Subsystems/Renderer/RenderUtils.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Saturn::RenderModules {

using namespace Components;

MeshRenderModule::MeshRenderModule() : RenderModule(10) {}

void MeshRenderModule::init() {

    no_shader_error =
        AssetManager<Shader>::get_resource("resources/shaders/default.sh");
}

void MeshRenderModule::process(Scene& scene,
                               Viewport& viewport,
                               Framebuffer& target) {

    for (auto [relative_transform, mesh, material] :
         scene.get_ecs().select<Transform, StaticMesh, Material>()) {

        if (!mesh.mesh.is_loaded()) { continue; }

        auto& shader = material.shader.is_loaded() ? material.shader.get()
                                                   : no_shader_error.get();

        // Send data to shader
        send_model_matrix(shader, relative_transform);
        send_material_data(shader, material);

        // Set lightspace matrix in shader
        Shader::bind(shader);
        if (material.lit) {
            auto lightspace = get_lightspace_matrix(scene);
            shader.set_mat4(Shader::Uniforms::LightSpaceMatrix, lightspace);
            if (RenderModules::DepthMapPass::last_depthmap) {
                // Set shadow map in shader
                glActiveTexture(GL_TEXTURE2);
                DepthMap::bind_texture(
                    *RenderModules::DepthMapPass::last_depthmap);
                shader.set_int(Shader::Uniforms::DepthMap, 2);
            }
        }

        // Do the actual rendering (maybe put this in another function
        // render_mesh() or something)
        auto& vtx_array = mesh.mesh->get_vertices();

        VertexArray::bind(vtx_array);
        if (!mesh.face_cull) { glDisable(GL_CULL_FACE); }
        glDrawElements(GL_TRIANGLES, vtx_array.index_size(), GL_UNSIGNED_INT,
                       nullptr);
        if (!mesh.face_cull) { glEnable(GL_CULL_FACE); }
        // Cleanup
        unbind_textures(material);
        glActiveTexture(GL_TEXTURE2);
        DepthMap::unbind_texture();
    }
}

void MeshRenderModule::unbind_textures(Material& material) {
    if (material.lit) {
        if (material.diffuse_map.is_loaded()) {
            Texture::unbind(material.diffuse_map.get());
        }
        if (material.specular_map.is_loaded()) {
            Texture::unbind(material.specular_map.get());
        }
    }
}

void MeshRenderModule::send_material_data(Shader& shader, Material& material) {
    Shader::bind(shader);
    if (material.lit) {
        if (material.diffuse_map.is_loaded()) {
            Texture::bind(material.diffuse_map.get());
            shader.set_int(Shader::Uniforms::Material::DiffuseMap,
                           material.diffuse_map->unit() - GL_TEXTURE0);
        }
        if (material.specular_map.is_loaded()) {
            Texture::bind(material.specular_map.get());
            shader.set_int(Shader::Uniforms::Material::SpecularMap,
                           material.specular_map->unit() - GL_TEXTURE0);
        }
        shader.set_float(Shader::Uniforms::Material::Shininess,
                         material.shininess);
    }
    Shader::unbind();
}

} // namespace Saturn::RenderModules