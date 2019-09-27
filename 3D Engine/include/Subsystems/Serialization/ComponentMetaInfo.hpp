#ifndef SATURN_COMPONENT_META_INFO_HPP_
#define SATURN_COMPONENT_META_INFO_HPP_

#include <cassert>
#include <glm/glm.hpp>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>

#include "Subsystems/ECS/Components.hpp"
#include "Subsystems/ECS/component_index.hpp"
#include "Utility/Utility.hpp"
#include "Utility/Color.hpp"
#include "Subsystems/Renderer/Shader.hpp"
#include "Subsystems/Renderer/Texture.hpp"
#include "Subsystems/Renderer/Mesh.hpp"

#include <audeo/SoundSource.hpp>

namespace Saturn {

namespace Meta {

struct ComponentInfo {
    // This has a space behind it to avoid problems with UI.
    // #DirtyFixPleaseFixBetter
    std::string name;
	bool hide_in_editor;
	bool editor_only;
	bool default_serialize;
    using type_name_t = std::string;
    std::unordered_map<std::string, type_name_t> fields;
};

class ComponentFieldPtr {
public:
#define SUPPORTED_COMPONENT_FIELD_TYPES                                        \
    std::size_t, float, int, std::string, glm::vec3, glm::vec4, bool, glm::bvec3, color3, color4, unsigned int, \
	Resource<Shader>, Resource<Texture>, Resource<Mesh>, Resource<audeo::SoundSource>
#define SUPPORTED_COMPONENT_FIELD_POINTER_TYPES                                \
    std::size_t*, float*, int*, std::string*, glm::vec3*, glm::vec4*, bool*, glm::bvec3*, color3*, color4*, unsigned int*, \
	Resource<Shader>*, Resource<Texture>*, Resource<Mesh>*, Resource<audeo::SoundSource>*
    using field_variant_t =
        std::variant<SUPPORTED_COMPONENT_FIELD_POINTER_TYPES>;

	
    struct null_state_t {};
    ComponentFieldPtr(null_state_t) { is_null = true; }

    template<typename T>
    ComponentFieldPtr(T* field) {
        static_assert(index_of<T, SUPPORTED_COMPONENT_FIELD_TYPES>::value != -1,
                      "Field type is unsupported");
        variant = field;
    }

    field_variant_t& get() { return variant; }

    static inline null_state_t null_ptr = {};

    bool operator==(null_state_t) const { return is_null; }
    operator bool() const { return !is_null; }
    bool is_valid() const { return !is_null; }

private:
    bool is_null = false;
    field_variant_t variant;
};

namespace detail {
void init_component_meta_data(std::vector<ComponentInfo>& data);
} // namespace detail

template<typename... Cs>
class ComponentsMeta {
public:
    static void init() { detail::init_component_meta_data(data); }

    template<typename C>
    static ComponentInfo const& get_component_meta_info() {
        const std::size_t index = index_table.template get<C>();
        assert(index != index_table.not_found);
        // Return the data
        return data[index];
    }
	
	// These functions are generated by SaturnEngine. Do NOT touch!
    static ComponentFieldPtr get_component_field(Components::BoxCollider& comp,
                                                 std::string_view field_name) {
		if (field_name == "center") {
			return ComponentFieldPtr(&comp.center);
		}
		if (field_name == "half_widths") {
			return ComponentFieldPtr(&comp.half_widths);
		}
		
		// return nullptr if the field was not found
		return ComponentFieldPtr(ComponentFieldPtr::null_ptr);
	}
    static ComponentFieldPtr get_component_field(Components::Camera& comp,
                                                 std::string_view field_name) {
		if (field_name == "front") {
			return ComponentFieldPtr(&comp.front);
		}
		if (field_name == "up") {
			return ComponentFieldPtr(&comp.up);
		}
		if (field_name == "fov") {
			return ComponentFieldPtr(&comp.fov);
		}
		if (field_name == "viewport_id") {
			return ComponentFieldPtr(&comp.viewport_id);
		}
		
		// return nullptr if the field was not found
		return ComponentFieldPtr(ComponentFieldPtr::null_ptr);
	}
    static ComponentFieldPtr get_component_field(Components::CameraZoomController& comp,
                                                 std::string_view field_name) {
		if (field_name == "zoom_speed") {
			return ComponentFieldPtr(&comp.zoom_speed);
		}
		if (field_name == "min_zoom") {
			return ComponentFieldPtr(&comp.min_zoom);
		}
		if (field_name == "max_zoom") {
			return ComponentFieldPtr(&comp.max_zoom);
		}
		
		// return nullptr if the field was not found
		return ComponentFieldPtr(ComponentFieldPtr::null_ptr);
	}
    static ComponentFieldPtr get_component_field(Components::ClickEffect& comp,
                                                 std::string_view field_name) {
		if (field_name == "sound_effect") {
			return ComponentFieldPtr(&comp.sound_effect);
		}
		if (field_name == "max_distance") {
			return ComponentFieldPtr(&comp.max_distance);
		}
		
		// return nullptr if the field was not found
		return ComponentFieldPtr(ComponentFieldPtr::null_ptr);
	}
    static ComponentFieldPtr get_component_field(Components::ColliderRenderer& comp,
                                                 std::string_view field_name) {
		
		
		// return nullptr if the field was not found
		return ComponentFieldPtr(ComponentFieldPtr::null_ptr);
	}
    static ComponentFieldPtr get_component_field(Components::DirectionalLight& comp,
                                                 std::string_view field_name) {
		if (field_name == "ambient") {
			return ComponentFieldPtr(&comp.ambient);
		}
		if (field_name == "diffuse") {
			return ComponentFieldPtr(&comp.diffuse);
		}
		if (field_name == "specular") {
			return ComponentFieldPtr(&comp.specular);
		}
		if (field_name == "direction") {
			return ComponentFieldPtr(&comp.direction);
		}
		
		// return nullptr if the field was not found
		return ComponentFieldPtr(ComponentFieldPtr::null_ptr);
	}
    static ComponentFieldPtr get_component_field(Components::DoNotSerialize& comp,
                                                 std::string_view field_name) {
		
		
		// return nullptr if the field was not found
		return ComponentFieldPtr(ComponentFieldPtr::null_ptr);
	}
    static ComponentFieldPtr get_component_field(Components::EditorCameraController& comp,
                                                 std::string_view field_name) {
		if (field_name == "speed") {
			return ComponentFieldPtr(&comp.speed);
		}
		if (field_name == "sensitivity") {
			return ComponentFieldPtr(&comp.sensitivity);
		}
		if (field_name == "zoom_speed") {
			return ComponentFieldPtr(&comp.zoom_speed);
		}
		if (field_name == "invert_x") {
			return ComponentFieldPtr(&comp.invert_x);
		}
		if (field_name == "invert_y") {
			return ComponentFieldPtr(&comp.invert_y);
		}
		
		// return nullptr if the field was not found
		return ComponentFieldPtr(ComponentFieldPtr::null_ptr);
	}
    static ComponentFieldPtr get_component_field(Components::FPSCameraController& comp,
                                                 std::string_view field_name) {
		if (field_name == "speed") {
			return ComponentFieldPtr(&comp.speed);
		}
		
		// return nullptr if the field was not found
		return ComponentFieldPtr(ComponentFieldPtr::null_ptr);
	}
    static ComponentFieldPtr get_component_field(Components::FreeLookController& comp,
                                                 std::string_view field_name) {
		if (field_name == "mouse_sensitivity") {
			return ComponentFieldPtr(&comp.mouse_sensitivity);
		}
		
		// return nullptr if the field was not found
		return ComponentFieldPtr(ComponentFieldPtr::null_ptr);
	}
    static ComponentFieldPtr get_component_field(Components::Material& comp,
                                                 std::string_view field_name) {
		if (field_name == "diffuse_map") {
			return ComponentFieldPtr(&comp.diffuse_map);
		}
		if (field_name == "shader") {
			return ComponentFieldPtr(&comp.shader);
		}
		if (field_name == "lit") {
			return ComponentFieldPtr(&comp.lit);
		}
		if (field_name == "specular_map") {
			return ComponentFieldPtr(&comp.specular_map);
		}
		if (field_name == "shininess") {
			return ComponentFieldPtr(&comp.shininess);
		}
		
		// return nullptr if the field was not found
		return ComponentFieldPtr(ComponentFieldPtr::null_ptr);
	}
    static ComponentFieldPtr get_component_field(Components::MusicController& comp,
                                                 std::string_view field_name) {
		if (field_name == "music") {
			return ComponentFieldPtr(&comp.music);
		}
		if (field_name == "loop") {
			return ComponentFieldPtr(&comp.loop);
		}
		if (field_name == "fade_in_ms") {
			return ComponentFieldPtr(&comp.fade_in_ms);
		}
		
		// return nullptr if the field was not found
		return ComponentFieldPtr(ComponentFieldPtr::null_ptr);
	}
    static ComponentFieldPtr get_component_field(Components::Name& comp,
                                                 std::string_view field_name) {
		if (field_name == "name") {
			return ComponentFieldPtr(&comp.name);
		}
		
		// return nullptr if the field was not found
		return ComponentFieldPtr(ComponentFieldPtr::null_ptr);
	}
    static ComponentFieldPtr get_component_field(Components::OutlineRenderer& comp,
                                                 std::string_view field_name) {
		if (field_name == "color") {
			return ComponentFieldPtr(&comp.color);
		}
		
		// return nullptr if the field was not found
		return ComponentFieldPtr(ComponentFieldPtr::null_ptr);
	}
    static ComponentFieldPtr get_component_field(Components::PointLight& comp,
                                                 std::string_view field_name) {
		if (field_name == "ambient") {
			return ComponentFieldPtr(&comp.ambient);
		}
		if (field_name == "diffuse") {
			return ComponentFieldPtr(&comp.diffuse);
		}
		if (field_name == "specular") {
			return ComponentFieldPtr(&comp.specular);
		}
		if (field_name == "intensity") {
			return ComponentFieldPtr(&comp.intensity);
		}
		
		// return nullptr if the field was not found
		return ComponentFieldPtr(ComponentFieldPtr::null_ptr);
	}
    static ComponentFieldPtr get_component_field(Components::Rigidbody& comp,
                                                 std::string_view field_name) {
		if (field_name == "mass") {
			return ComponentFieldPtr(&comp.mass);
		}
		if (field_name == "locked_axes") {
			return ComponentFieldPtr(&comp.locked_axes);
		}
		
		// return nullptr if the field was not found
		return ComponentFieldPtr(ComponentFieldPtr::null_ptr);
	}
    static ComponentFieldPtr get_component_field(Components::Rotator& comp,
                                                 std::string_view field_name) {
		if (field_name == "speed") {
			return ComponentFieldPtr(&comp.speed);
		}
		if (field_name == "euler_angles") {
			return ComponentFieldPtr(&comp.euler_angles);
		}
		
		// return nullptr if the field was not found
		return ComponentFieldPtr(ComponentFieldPtr::null_ptr);
	}
    static ComponentFieldPtr get_component_field(Components::Sound& comp,
                                                 std::string_view field_name) {
		
		
		// return nullptr if the field was not found
		return ComponentFieldPtr(ComponentFieldPtr::null_ptr);
	}
    static ComponentFieldPtr get_component_field(Components::SoundListener& comp,
                                                 std::string_view field_name) {
		if (field_name == "forward") {
			return ComponentFieldPtr(&comp.forward);
		}
		if (field_name == "position") {
			return ComponentFieldPtr(&comp.position);
		}
		
		// return nullptr if the field was not found
		return ComponentFieldPtr(ComponentFieldPtr::null_ptr);
	}
    static ComponentFieldPtr get_component_field(Components::SpotLight& comp,
                                                 std::string_view field_name) {
		if (field_name == "inner_angle") {
			return ComponentFieldPtr(&comp.inner_angle);
		}
		if (field_name == "ambient") {
			return ComponentFieldPtr(&comp.ambient);
		}
		if (field_name == "diffuse") {
			return ComponentFieldPtr(&comp.diffuse);
		}
		if (field_name == "specular") {
			return ComponentFieldPtr(&comp.specular);
		}
		if (field_name == "intensity") {
			return ComponentFieldPtr(&comp.intensity);
		}
		if (field_name == "direction") {
			return ComponentFieldPtr(&comp.direction);
		}
		if (field_name == "outer_angle") {
			return ComponentFieldPtr(&comp.outer_angle);
		}
		
		// return nullptr if the field was not found
		return ComponentFieldPtr(ComponentFieldPtr::null_ptr);
	}
    static ComponentFieldPtr get_component_field(Components::StaticMesh& comp,
                                                 std::string_view field_name) {
		if (field_name == "mesh") {
			return ComponentFieldPtr(&comp.mesh);
		}
		if (field_name == "face_cull") {
			return ComponentFieldPtr(&comp.face_cull);
		}
		
		// return nullptr if the field was not found
		return ComponentFieldPtr(ComponentFieldPtr::null_ptr);
	}
    static ComponentFieldPtr get_component_field(Components::Transform& comp,
                                                 std::string_view field_name) {
		if (field_name == "position") {
			return ComponentFieldPtr(&comp.position);
		}
		if (field_name == "rotation") {
			return ComponentFieldPtr(&comp.rotation);
		}
		if (field_name == "scale") {
			return ComponentFieldPtr(&comp.scale);
		}
		
		// return nullptr if the field was not found
		return ComponentFieldPtr(ComponentFieldPtr::null_ptr);
	}

private:
    static inline std::vector<ComponentInfo> data = {};
    static inline component_index_table<Cs...> index_table = {};
};

} // namespace Meta

} // namespace Saturn

#endif
