#ifndef SATURN_COMPONENT_ID_HPP_
#define SATURN_COMPONENT_ID_HPP_

#include <stl/types.hpp>

namespace saturn::ecs {

struct type_id_counter {
    static inline stl::uint64_t cur = 0;

    static stl::uint64_t next() {
        return cur++;
    }
};

template<typename T>
stl::uint64_t get_component_type_id() {
    static stl::uint64_t id = type_id_counter::next();
    return id;
}


} // namespace saturn::ecs

#endif