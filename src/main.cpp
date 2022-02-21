#include "App.h"
#include "Environment.h"
#include <iostream>
#include <sstream>

void Run()
{
    Vulkandemo::App::Config config{};
    config.Name = "Vulkan Demo";
    config.Window.Title = config.Name;
    config.Window.Width = 800;
    config.Window.Height = 600;
    config.Vulkan.Name = config.Name;
#ifdef VD_DEBUG
    config.Vulkan.ValidationLayersEnabled = true;
#endif

    auto* app = new Vulkandemo::App(config);
    app->Run();
    delete app;
}

int main(int argc, char* argv[])
{
    if (argc <= 1)
    {
        printf("No arguments");
        return 1;
    }
    for (int i = 0; i < argc; i++)
    {
        printf("argc [%i/%i], argv [%s]\n", (i + 1), argc, argv[i]);
    }

    char* command = argv[1];
    printf("command [%s]\n", command);

    if (strcmp(command, "deps") == 0)
    {
        printf("Installing dependencies (git submodules)...\n");

        const char* also = " && ";
        const char* up = "cd ..";

        std::stringstream ss;
        ss << "git submodule update --init";
        ss << also;
        ss << "cd lib";
        ss << also;
        ss << "cd glfw && git checkout 3.3.4";
        ss << also << up << also;
        ss << "cd glm && git checkout 0.9.9.8";
        ss << also << up << also;
        ss << "cd spdlog && git checkout v1.9.2";

        std::string cmd = ss.str();
        printf("%s\n", cmd.c_str());
        std::system(cmd.c_str());

        return 0;
    }

    if (strcmp(command, "glfw") == 0)
    {
        printf("Building and installing GLFW...");

        const char* also = " && ";
        const char* buildType = "Debug";
        const char* buildDir = "build";

        std::stringstream ss;
        ss << "cd lib/glfw";
        ss << also;
        ss << "cmake -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DCMAKE_BUILD_TYPE=" << buildType << " -S . -B ./" << buildDir;
        ss << also;
        ss << "cmake --build ./" << buildDir << " --config " << buildType;
        ss << also;
        ss << "cmake --install ./" << buildDir << " --config " << buildType;

        std::string cmd = ss.str();
        printf("%s\n", cmd.c_str());
        std::system(cmd.c_str());

        return 0;
    }

    if (strcmp(command, "build") == 0)
    {
        printf("Building application...");

        const char* also = " && ";
        const char* buildType = "Debug";
        const char* buildDir = "cmake-build-debug";

        std::stringstream ss;
        ss << "cmake -DCMAKE_BUILD_TYPE=" << buildType << " -S . -B " << buildDir;
        ss << also;
        ss << "cmake --build " << buildDir << " --config " << buildType;

        std::string cmd = ss.str();
        printf("%s\n", cmd.c_str());
        std::system(cmd.c_str());

        return 0;
    }

    printf("Unknown command\n");
    return 1;
}