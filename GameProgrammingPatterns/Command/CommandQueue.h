#pragma once

#include <queue>
#include <memory>
#include "Command.h"

class CommandQueue
{
public:
    void AddCommand(std::shared_ptr<Command> Command)
    {
        Commands.push(Command);
    }

    void ProcessCommands()
    {
        while (!Commands.empty())
        {
            std::shared_ptr<Command> Command = Commands.front();
            Commands.pop();
            Command->Execute();
        }
    }

    size_t GetCommandCount() const
    {
        return Commands.size();
    }

private:
    std::queue<std::shared_ptr<Command>> Commands;
};
