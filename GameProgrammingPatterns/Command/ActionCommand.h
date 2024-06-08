#pragma once

#include <functional>
#include "Command.h"

class ActionCommand : public Command
{
public:
    ActionCommand(std::function<void()> Action, std::function<void()> UndoAction) : Action(Action), UndoAction(UndoAction) {}

    virtual void Execute() override
    {
        if (Action != nullptr)
        {
            Action();
        }
    }

    virtual void Undo() override
    {
        if (UndoAction != nullptr)
        {
            UndoAction();
        }
    }

private:
    std::function<void()> Action;
    std::function<void()> UndoAction;
};
