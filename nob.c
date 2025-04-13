// This is your build script. You only need to "bootstrap" it once with `cc -o nob nob.c`
// (you can call the executable whatever actually) or `cl nob.c` on MSVC. After that every
// time you run the `nob` executable if it detects that you modifed nob.c it will rebuild
// itself automatically thanks to NOB_GO_REBUILD_URSELF (see below)
// nob.h is an stb-style library https://github.com/nothings/stb/blob/master/docs/stb_howto.txt
// What that means is that it's a single file that acts both like .c and .h files, but by default
// when you include it, it acts only as .h. To make it include implementations of the functions
// you must define NOB_IMPLEMENTATION macro. This is done to give you full control over where
// the implementations go.
#define NOB_IMPLEMENTATION
#include "nob.h"

// Some folder paths that we use throughout the build process.
#define BUILD_FOLDER "build/"
#define SRC_FOLDER   "src/"

// --- Platform Specific Definitions ---
// We need different libraries/flags depending on the OS
#if defined(_WIN32)
    // Windows platform libraries with volk
    #define PLATFORM_LIBS "-lglfw3", "-lgdi32", "-lopengl32", "-lvulkan-1"
#elif defined(__linux__)
    // Linux platform libraries with volk and libdecor
    #define PLATFORM_LIBS "-lglfw", "-lvulkan", "-ldl", "-lpthread", "-lm"
#elif defined(__APPLE__)
    // macOS platform flags for frameworks
    #define PLATFORM_FLAGS "-framework", "Cocoa", "-framework", "IOKit", "-framework", "CoreVideo"
    // macOS libraries
    #define PLATFORM_LIBS "-lglfw", "-lvulkan"
#else
    #error "Unsupported platform"
#endif

int main(int argc, char **argv)
{
    // This line enables the self-rebuilding. It detects when nob.c is updated and auto rebuilds it then
    // runs it again.
    NOB_GO_REBUILD_URSELF(argc, argv);

    // It's better to keep all the building artifacts in a separate build folder. Let's create it if it
    // does not exist yet.
    if (!nob_mkdir_if_not_exists(BUILD_FOLDER)) return 1;

    // The working horse of nob is the Nob_Cmd structure. It's a Dynamic Array of strings which represent
    // command line that you want to execute.
    Nob_Cmd cmd = {0};

    // Let's append the command line arguments for building the main application
    // Using clang as it often has better diagnostics and Wayland/newer feature support
    // You can change "clang" back to "cc" if you prefer GCC or if clang isn't available
    nob_cmd_append(&cmd, "cc", "-Wall", "-Wextra", "-Wno-unused-result");

    // Add output file
    nob_cmd_append(&cmd, "-o", BUILD_FOLDER"main");

    // Add source files
    nob_cmd_append(&cmd,
        SRC_FOLDER"main.c"
    );

    // Add include paths if necessary (e.g., if headers are not in standard locations)
    // nob_cmd_append(&cmd, "-I/path/to/includes");

    // Add library paths if necessary (e.g., if .so/.a files are not in standard locations)
    // nob_cmd_append(&cmd, "-L/path/to/libs");

    // Add platform specific libraries
    #ifdef PLATFORM_LIBS
        nob_cmd_append(&cmd, PLATFORM_LIBS);
    #endif

    // Add platform specific flags (like frameworks for macOS)
    #ifdef PLATFORM_FLAGS
        nob_cmd_append(&cmd, PLATFORM_FLAGS);
    #endif

    // Let's execute the command synchronously
    nob_log(NOB_INFO, "Building main application...");
    // Optional: Print the command before running it
    // nob_log(NOB_INFO, "CMD: %s", nob_cmd_ss(&cmd));
    if (!nob_cmd_run_sync(cmd)) {
        nob_log(NOB_ERROR, "Build failed");
        nob_cmd_free(cmd);
        return 1;
    }
    nob_log(NOB_INFO, "Successfully built " BUILD_FOLDER"main");

    // --- Optional: Run Command ---
    if (argc > 1 && strcmp(argv[1], "run") == 0) {
        nob_log(NOB_INFO, "Running application...");

        // Reset the cmd array so you can use it again for another command
        cmd.count = 0;

        nob_cmd_append(&cmd, BUILD_FOLDER"main");
        // Append remaining arguments passed to nob after "run" to the executable
        for (int i = 2; i < argc; ++i) {
            nob_cmd_append(&cmd, argv[i]);
        }

        if (!nob_cmd_run_sync(cmd)) {
            nob_log(NOB_ERROR, "Failed to run application");
            nob_cmd_free(cmd);
            return 1;
        }
    }

    // Free command resources
    nob_cmd_free(cmd);

    return 0;
}