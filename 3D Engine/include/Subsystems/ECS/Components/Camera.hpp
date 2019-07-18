#ifndef MVG_COMPONENT_CAMERA_HPP_
#define MVG_COMPONENT_CAMERA_HPP_

#include "ComponentBase.hpp"

#include <glm/glm.hpp>

namespace Saturn {

namespace Components {

struct COMPONENT Camera : public ComponentBase {
    glm::vec3 front;
    glm::vec3 up;

	float fov;
	unsigned int viewport_id = 0;
};

} // namespace Components

} // namespace Saturn

#endif
