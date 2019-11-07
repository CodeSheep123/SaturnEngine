#ifndef SATURN_VERTEX_ARRAY_HPP_
#define SATURN_VERTEX_ARRAY_HPP_

#include <cstddef>
#include <memory>
#include <vector>

#include "OpenGL.hpp"

namespace Saturn {

struct VertexAttribute {
    std::size_t location_in_shader;
    // The amount of components one element has. Must be 1, 2, 3 or 4
    std::size_t num_components;
    std::size_t divisor = 0;
};

enum class BufferMode { Static, Dynamic, DataStream };

class VertexArray {
public:
    struct CreateInfo {
        std::vector<VertexAttribute> attributes;
        std::vector<float> vertices;
        std::vector<GLuint>
            indices;          ///< Index buffer. Leave empty to auto-generate
        bool dynamic = false; ///< Indicates whether the buffer data will change
    };

    struct BufferInfo {
        std::vector<VertexAttribute> attributes;
        std::vector<float> data;
        BufferMode mode = BufferMode::Static;
    };

    VertexArray() = default;
    VertexArray(CreateInfo const& create_info);

    VertexArray(VertexArray const&) = delete;
    VertexArray(VertexArray&& rhs) {
        vao.id = rhs.vao.id;
        rhs.vao.id = 0;
        std::swap(buffers, rhs.buffers);
        ebo.id = rhs.ebo.id;
        rhs.ebo.id = 0;
        vertex_count = rhs.vertex_count;
        rhs.vertex_count = 0;
        indices_size = rhs.indices_size;
        rhs.indices_size = 0;
		std::swap(indices, rhs.indices);
    }

    VertexArray& operator=(VertexArray const&) = delete;
	VertexArray& operator=(VertexArray&& rhs) {
        vao.id = rhs.vao.id;
        rhs.vao.id = 0;
        std::swap(buffers, rhs.buffers);
        ebo.id = rhs.ebo.id;
        rhs.ebo.id = 0;
        vertex_count = rhs.vertex_count;
        rhs.vertex_count = 0;
        indices_size = rhs.indices_size;
        rhs.indices_size = 0;
        std::swap(indices, rhs.indices);
        return *this;
	}

    void assign(CreateInfo const& create_info);

    ~VertexArray();

    static void bind(VertexArray& buf);
    static void unbind();

    // Returns the amount of vertices
    std::size_t size() const;

    // Returns the amount of indices in the index buffer
    std::size_t index_size() const;

    // Returns the index of the added buffer
    std::size_t add_buffer(BufferInfo const& info);

    void update_buffer_data(std::size_t buffer_index,
                            float* data,
                            std::size_t count);

    void swap(VertexArray& other) {
        std::swap(vao.id, other.vao.id);
        std::swap(buffers, other.buffers);
        std::swap(ebo.id, other.ebo.id);
        std::swap(vertex_count, other.vertex_count);
        std::swap(indices_size, other.indices_size);
        std::swap(indices, other.indices);
    }

private:
    friend class Renderer;

    void do_create(CreateInfo const& create_info);

    Vao vao;
    std::vector<std::unique_ptr<Vbo<BufferTarget::ArrayBuffer>>> buffers;
    Vbo<BufferTarget::ElementArrayBuffer> ebo;

    std::size_t vertex_count;
    std::size_t indices_size;

    std::vector<GLuint> indices;
};

} // namespace Saturn

#endif