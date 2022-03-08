#include "InstallDependenciesCommand.h"
#include "Environment.h"
#include <sstream>

namespace VulkandemoCLI
{
    Command CreateInstallDependenciesCommand(const FileSystem& fileSystem)
    {
        Command command;
        command.Name = "deps";
        command.Usage = "Install dependencies";
        command.Action = [&](const Context& context) -> void
        {
            std::system("git submodule update --init");
            printf("\n");

            std::istringstream iss(fileSystem.ReadFile(".dependencies"));
            for (std::string line; std::getline(iss, line);)
            {
                if (line.empty() || line[0] == '#')
                {
                    continue;
                }
                int equalSignPosition = line.find("=");
                const std::string& name = line.substr(0, equalSignPosition);
                const std::string& version = line.substr(equalSignPosition + 1, line.length());
                printf("%s%s%s%s%s\n", "-- Using [", name.c_str(), "] version [", version.c_str(), "]");
                std::stringstream ss;
                ss << "cd " << "lib" << "/" << name << " && git checkout " << version;
                std::string command = ss.str();
#ifdef VDC_DEBUG
                printf("%s\n", command.c_str());
#endif
                std::system(command.c_str());
                printf("\n");
            }
            printf("\n");

        };
        return command;
    }
}
