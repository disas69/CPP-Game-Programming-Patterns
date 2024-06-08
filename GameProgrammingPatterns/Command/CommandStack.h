#pragma once

#include <queue>
#include <stack>
#include <memory>
#include "Command.h"

class CommandStack
{
public:
    void AddCommand(std::shared_ptr<Command> Command)
    {
        PendingCommands.push(Command);
    }

    void ProcessCommands()
    {
        while (!PendingCommands.empty())
        {
            std::shared_ptr<Command> Command = PendingCommands.front();
            PendingCommands.pop();
            Command->Execute();
            ExecutedCommands.push(Command);
        }
    }

    void UndoLastCommand()
    {
        if (ExecutedCommands.empty())
        {
            return;
        }

        std::shared_ptr<Command> Command = ExecutedCommands.top();
        ExecutedCommands.pop();
        Command->Undo();
    }

    size_t GetPendingCommandCount() const
    {
        return PendingCommands.size();
    }

    size_t GetExecutedCommandCount() const
    {
        return ExecutedCommands.size();
    }

private:
    std::queue<std::shared_ptr<Command>> PendingCommands;
    std::stack<std::shared_ptr<Command>> ExecutedCommands;
};
