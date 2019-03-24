#ifndef MVG_APPLICATION_HPP_
#define MVG_APPLICATION_HPP_

#include "Utility.hpp"

#include "glad\glad.h"
#include <GLFW\glfw3.h>
#include <string_view>

namespace Saturn {

class Application {
public:
    friend class Engine;

    struct CreateInfo {
        WindowDim window_size;
        std::string_view window_caption = "";
        bool fullscreen = false;
    };

    Application(CreateInfo create_info);

    // This class is not copyable
    Application(Application const&) = delete;
    Application& operator=(Application const&) = delete;

    Application(Application&&);
    Application& operator=(Application&&);

    ~Application();

    // \brief Runs the application. Blocks the calling thread.
    void run();

    // \brief Call to quit the application.
    void quit();

private:
    GLFWwindow* window_handle;
    WindowDim window_dimensions;
    bool window_is_open;

    // Window callback functions
    static void
        resize_callback([[maybe_unused]] GLFWwindow* window, int w, int h);
   
};

} // namespace Saturn

#endif
