#pragma once

#include "Command.h"
#include <map>

namespace VulkandemoCLI
{
    class App
    {
    public:
        App();

        ~App();

        Command* GetCommand(int argc, char* argv[]) const;

    private:
        void PrintHelp() const;

        void PrintInput(int argc, char* argv[]) const;

        static const char* DEFAULT_EXE_NAME;
        std::map<std::string, Command*> commands;
    };
}