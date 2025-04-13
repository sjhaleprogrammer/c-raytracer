#include "toolkit.h"

int main() {
    State state = {
            .config = {
                    .applicationName = "Raytracer",
                    .engineName = "minimal raytracer",
                    .windowTitle = "raytracer",
                    .windowWidth = 1280,
                    .windowHeight = 720,
                    .windowFullscreen = false,
                    .apiVersion = VK_API_VERSION_1_4,
                    .swapchainComponentsMapping = (VkComponentMapping) {},
                    .swapchainBuffering = SWAPCHAIN_TRIPLE_BUFFERING,
                    .backgroundColor = {{0.01f, 0.01f, 0.01f, 0.01f}}
            },
    };

    init(&state);
    loop(&state);
    cleanup(&state);

    return EXIT_SUCCESS;
}
