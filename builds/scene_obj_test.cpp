// The from_json function in this file was generated code.
// When modifying other code, make sure to edit the template as well.
// At some point, I will move this generated function out of this file
// to avoid this problem. #TODO

#include "Subsystems/Scene/SceneObject.hpp"
#include "Subsystems/Scene/Scene.hpp"

#include "Core/Application.hpp"
#include "Subsystems/AssetManager/AssetManager.hpp"
#include "Subsystems/ECS/ComponentList.hpp"
#include "Subsystems/ECS/Components.hpp"
#include "Subsystems/Math/Math.hpp"
#include "Subsystems/Renderer/Renderer.hpp"
#include "Subsystems/Renderer/Viewport.hpp"
#include "Subsystems/Serialization/ComponentSerializers.hpp"

#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>

namespace Saturn {

SceneObject::SceneObject(Scene* s, SceneObject* parent /*= nullptr*/) :
    scene(s), parent_obj(parent) {}

bool SceneObject::has_parent() const { return parent_obj != nullptr; }

SceneObject* SceneObject::parent() { return parent_obj; }

SceneObject const* SceneObject::parent() const { return parent_obj; }

void SceneObject::serialize_to_file(std::string_view path) {
    nlohmann::json json;
    json = *this;
    std::ofstream file(path.data());
    file << json.dump(4);
}

void to_json(nlohmann::json& j, SceneObject const& obj) {
    obj.serialize_components<COMPONENT_LIST>(j);
}

void from_json(nlohmann::json const& j, SceneObject& obj) {
    using namespace Components;
    auto& ecs = obj.get_scene()->get_ecs();

	// Deserialization for Camera component
	if (auto const& component = j.find("CameraComponent"); component != j.end()) {
		auto& c = obj.get_scene()->get_ecs().get_with_id<Camera>(
			obj.add_component<Camera>());
		j.get_to(c);
		obj.get_scene()->get_app()->get_renderer()->get_viewport(component.viewport_id).set_camera(component.id);
	}
	// Deserialization for CameraZoomController component
	if (auto const& component = j.find("CameraZoomControllerComponent"); component != j.end()) {
		auto& c = obj.get_scene()->get_ecs().get_with_id<CameraZoomController>(
			obj.add_component<CameraZoomController>());
		j.get_to(c);
		
	}
	// Deserialization for DirectionalLight component
	if (auto const& component = j.find("DirectionalLightComponent"); component != j.end()) {
		auto& c = obj.get_scene()->get_ecs().get_with_id<DirectionalLight>(
			obj.add_component<DirectionalLight>());
		j.get_to(c);
		
	}
	// Deserialization for FPSCameraController component
	if (auto const& component = j.find("FPSCameraControllerComponent"); component != j.end()) {
		auto& c = obj.get_scene()->get_ecs().get_with_id<FPSCameraController>(
			obj.add_component<FPSCameraController>());
		j.get_to(c);
		
	}
	// Deserialization for FreeLookController component
	if (auto const& component = j.find("FreeLookControllerComponent"); component != j.end()) {
		auto& c = obj.get_scene()->get_ecs().get_with_id<FreeLookController>(
			obj.add_component<FreeLookController>());
		j.get_to(c);
		
	}
	// Deserialization for Material component
	if (auto const& component = j.find("MaterialComponent"); component != j.end()) {
		auto& c = obj.get_scene()->get_ecs().get_with_id<Material>(
			obj.add_component<Material>());
		j.get_to(c);
		
	}
	// Deserialization for ParticleEmitter component
	if (auto const& component = j.find("ParticleEmitterComponent"); component != j.end()) {
		auto& c = obj.get_scene()->get_ecs().get_with_id<ParticleEmitter>(
			obj.add_component<ParticleEmitter>());
		j.get_to(c);
		
	}
	// Deserialization for PointLight component
	if (auto const& component = j.find("PointLightComponent"); component != j.end()) {
		auto& c = obj.get_scene()->get_ecs().get_with_id<PointLight>(
			obj.add_component<PointLight>());
		j.get_to(c);
		
	}
	// Deserialization for Rotator component
	if (auto const& component = j.find("RotatorComponent"); component != j.end()) {
		auto& c = obj.get_scene()->get_ecs().get_with_id<Rotator>(
			obj.add_component<Rotator>());
		j.get_to(c);
		
	}
	// Deserialization for SpotLight component
	if (auto const& component = j.find("SpotLightComponent"); component != j.end()) {
		auto& c = obj.get_scene()->get_ecs().get_with_id<SpotLight>(
			obj.add_component<SpotLight>());
		j.get_to(c);
		
	}
	// Deserialization for StaticMesh component
	if (auto const& component = j.find("StaticMeshComponent"); component != j.end()) {
		auto& c = obj.get_scene()->get_ecs().get_with_id<StaticMesh>(
			obj.add_component<StaticMesh>());
		j.get_to(c);
		
	}
	// Deserialization for Transform component
	if (auto const& component = j.find("TransformComponent"); component != j.end()) {
		auto& c = obj.get_scene()->get_ecs().get_with_id<Transform>(
			obj.add_component<Transform>());
		j.get_to(c);
		
	}
} 

} // namespace Saturn