#pragma once

#include "Command.h"

namespace VulkandemoCLI
{
    class BuildProjectCommand : public Command
    {
    public:
        const char* GetName() const override;

        const char* GetDescription() const override;

        void Execute() const override;

        static const char* NAME;
    };
}