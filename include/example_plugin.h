// Copyright (c) 2024, The Endstone Project. (https://endstone.dev) All Rights Reserved.

#pragma once

#include "example_listener.h"
#include "fibonacci_command.h"

#include <endstone/endstone.hpp>
#include <memory>
#include <vector>

class ExamplePlugin : public endstone::Plugin {
public:
    void onLoad() override
    {
        getLogger().info("onLoad is called");
    }

    void onEnable() override
    {
        getLogger().info("onEnable is called");

        if (auto *command = getCommand("fibonacci")) {
            command->setExecutor(std::make_unique<FibonacciCommandExecutor>());
        }

        // You can register an event handler directly in the Plugin class.
        registerEvent(&ExamplePlugin::onServerLoad, *this);

        // You can also create a separate class (e.g. ExampleListener) and register the event handler from that class.
        listener_ = std::make_unique<ExampleListener>(*this);
        registerEvent(&ExampleListener::onServerLoad, *listener_, endstone::EventPriority::High);
    }

    void onDisable() override
    {
        getLogger().info("onDisable is called");
    }

    bool onCommand(endstone::CommandSender &sender, const endstone::Command &command,
                   const std::vector<std::string> &args) override
    {
        // You can also handle commands here instead of setting an executor in onEnable if you prefer
        if (command.getName() == "whoami") {
            if (sender.getPermissionLevel() >= endstone::PermissionLevel::Operator) {
                sender.sendMessage(endstone::ColorFormat::DarkGreen + "You are seeing this because you are the OP!");
            }
            else {
                sender.sendErrorMessage("You should never see this!");
            }
            return true;
        }

        sender.sendErrorMessage("Unknown command: /{}", command.getName());
        return false;
    }

    void onServerLoad(endstone::ServerLoadEvent &event)
    {
        getLogger().info("{} is passed to ExamplePlugin::onServerLoad", event.getEventName());
    }

private:
    std::unique_ptr<ExampleListener> listener_;
};
