#pragma once

#include <queue>
#include <stack>
#include <memory>
#include "Command.h"

class CommandStack
{
public:
    void AddCommand(const std::shared_ptr<Command>& Command)
    {
        if (Command != nullptr)
        {
            PendingCommands.push(Command);
        }
    }

    void ProcessCommands()
    {
        while (!PendingCommands.empty())
        {
            std::shared_ptr<Command> Command = PendingCommands.front();
            PendingCommands.pop();

            if (Command != nullptr)
            {
                try
                {
                    Command->Execute();
                    ExecutedCommands.push(Command);
                }
                catch (const std::exception& Exception)
                {
                    std::cerr << "Exception: " << Exception.what() << std::endl;
                }
            }
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
        if (Command != nullptr)
        {
            try
            {
                Command->Undo();
            }
            catch (const std::exception& Exception)
            {
                std::cerr << "Exception: " << Exception.what() << std::endl;
            }
        }
    }

    size_t GetPendingCommandCount() const
    {
        return PendingCommands.size();
    }

    size_t GetExecutedCommandCount() const
    {
        return ExecutedCommands.size();
    }

    void ClearCommands()
    {
        std::queue<std::shared_ptr<Command>> EmptyQueue;
        std::swap(PendingCommands, EmptyQueue);

        std::stack<std::shared_ptr<Command>> EmptyStack;
        std::swap(ExecutedCommands, EmptyStack);
    }

private:
    std::queue<std::shared_ptr<Command>> PendingCommands;
    std::stack<std::shared_ptr<Command>> ExecutedCommands;
};
