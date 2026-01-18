// Copyright (c) 2024, The Endstone Project. (https://endstone.dev) All Rights Reserved.

#pragma once

#include <endstone/endstone.hpp>
#include <string>

class FibonacciCommandExecutor : public endstone::CommandExecutor {
public:
    bool onCommand(endstone::CommandSender &sender, const endstone::Command &command,
                   const std::vector<std::string> &args) override
    {
        if (!command.testPermission(sender)) {
            return true;
        }

        int n = std::stoi(args[0]);

        if (n <= 0) {
            sender.sendErrorMessage("'n' must be an integer greater than 0.");
            return true;
        }

        if (n >= 1000 && !sender.hasPermission("cpp_example.command.fibonacci.large_n")) {
            sender.sendErrorMessage("Only operator can use this command with n >= 1000.");
            return true;
        }

        int a = 0, b = 1;
        std::string result;
        while (a < n) {
            if (!result.empty()) {
                result += ", ";
            }

            result += std::to_string(a);
            int temp = b;
            b = a + b;
            a = temp;
        }
        sender.sendMessage("Fibonacci series up to {}: {}", n, result);
        return true;
    }
};
