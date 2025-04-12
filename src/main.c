#include <GLFW/glfw3.h>
#include <stdio.h>

int main() {
    // Uncomment to definitively force X11 if needed
    // glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);

    if (!glfwInit()) {
        fprintf(stderr, "ERROR: Failed to initialize GLFW!\n");
        return -1;
    }

    // We MUST request *some* API, even if we don't use it much here.
    // Try NO_API first, as it's simplest for just window creation.
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Simple Test", NULL, NULL);
    if (!window) {
        const char* description;
        int code = glfwGetError(&description);
        // Capture the specific GLFW error description
        fprintf(stderr, "GLFW Error (%d): %s\n", code, description);
        glfwTerminate();
        fprintf(stderr, "ERROR: Failed to create GLFW window!\n");
        return -1;
    }

    printf("GLFW window created successfully.\n"); // Check if we reach here

    // Keep window open briefly
    double startTime = glfwGetTime();
    while (glfwGetTime() < startTime + 1.0) { // Keep open for 1 second
         glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    printf("GLFW terminated.\n");
    return 0;
}