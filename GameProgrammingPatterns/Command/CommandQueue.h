#pragma once

#include <queue>
#include <memory>
#include "Command.h"

class CommandQueue
{
public:
    void AddCommand(const std::shared_ptr<Command>& Command)
    {
        if (Command != nullptr)
        {
            Commands.push(Command);
        }
    }

    void ProcessCommands()
    {
        while (!Commands.empty())
        {
            std::shared_ptr<Command> Command = Commands.front();
            Commands.pop();

            if (Command != nullptr)
            {
                try
                {
                    Command->Execute();
                }
                catch (const std::exception& Exception)
                {
                    std::cerr << "Exception: " << Exception.what() << std::endl;
                }
            }
        }
    }

    size_t GetCommandCount() const
    {
        return Commands.size();
    }

    void ClearCommands()
    {
        std::queue<std::shared_ptr<Command>> Empty;
        std::swap(Commands, Empty);
    }

private:
    std::queue<std::shared_ptr<Command>> Commands;
};
