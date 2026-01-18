#include <endstone/endstone.hpp>
#include <algorithm>
#include <fstream>
#include <random>
#include <string>
#include <vector>

class killfeed : public endstone::Plugin {
public:
    void onLoad() override
    {
        getLogger().info("Killfeed plugin loading...");
        loadConfig();
    }

    void onEnable() override
    {
        getLogger().info("Killfeed plugin enabled!");
        registerEvent(&killfeed::onPlayerDeath, *this);
    }

    void onDisable() override
    {
        getLogger().info("Killfeed plugin disabled!");
    }

    bool onCommand(endstone::CommandSender &sender, const endstone::Command &command,
                   const std::vector<std::string> &args) override
    {
        if (command.getName() == "killfeed") {
            if (args.empty() || args[0] != "reload") {
                sender.sendErrorMessage("Usage: /killfeed reload");
                return true;
            }

            if (!sender.hasPermission("killfeed.reload")) {
                sender.sendErrorMessage("You don't have permission to reload the config!");
                return true;
            }

            deathMessages.clear();
            availableMessages.clear();
            loadConfig();

            sender.sendMessage("§aKillfeed config reloaded! Loaded {} messages.", deathMessages.size());
            getLogger().info("{} reloaded the killfeed config", sender.getName());
            return true;
        }
        return false;
    }

    void onPlayerDeath(endstone::PlayerDeathEvent &event)
    {
        auto &player = event.getPlayer();
        std::string playerName = player.getName();

        std::string message = getRandomMessage(playerName);
        getServer().broadcastMessage(message);

        getLogger().info("Death message broadcasted for player: {}", playerName);
    }

private:
    std::vector<std::string> deathMessages;
    std::vector<std::string> availableMessages;
    std::mt19937 rng;

    void loadConfig()
    {
        std::string configPath = getDataFolder() + "/messages.txt";

        std::ifstream file(configPath);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                if (!line.empty() && line[0] != '#') {
                    deathMessages.push_back(line);
                }
            }
            file.close();
            getLogger().info("Loaded {} death messages from config", deathMessages.size());
        }
        else {
            getLogger().info("Config file not found, creating default messages.txt");
            createDefaultConfig(configPath);
        }

        if (deathMessages.empty()) {
            getLogger().warning("No death messages loaded! Using fallback.");
            deathMessages.push_back("§l§e{user}§r §cdied.");
        }

        availableMessages = deathMessages;
        rng.seed(std::random_device{}());
    }

    void createDefaultConfig(const std::string &path)
    {
        std::filesystem::create_directories(getDataFolder());

        std::ofstream file(path);
        if (file.is_open()) {
            file << "# Killfeed Death Messages Configuration\n";
            file << "# Use {user} as a placeholder for the player's name\n";
            file << "#\n";
            file << "# Example color codes:\n";
            file << "# §l = Bold, §e = Yellow, §c = Red, §r = Reset\n";
            file << "#\n\n";

            file << "§l§e{user}§r §cjust got reality-checked by PvP.\n";
            file << "§l§e{user}§r §cconfused confidence with skill.\n";

            file.close();
            getLogger().info("Created default messages.txt config file");

            deathMessages.push_back("§l§e{user}§r §cjust got reality-checked by PvP.");
            deathMessages.push_back("§l§e{user}§r §cconfused confidence with skill.");
        }
        else {
            getLogger().error("Failed to create config file!");
        }
    }

    std::string getRandomMessage(const std::string &playerName)
    {
        if (availableMessages.empty()) {
            availableMessages = deathMessages;
        }

        std::uniform_int_distribution<size_t> dist(0, availableMessages.size() - 1);
        size_t index = dist(rng);

        std::string message = availableMessages[index];
        availableMessages.erase(availableMessages.begin() + index);

        size_t pos = message.find("{user}");
        if (pos != std::string::npos) {
            message.replace(pos, 6, playerName);
        }

        return message;
    }
};

ENDSTONE_PLUGIN("killfeed", "1.0.0", killfeed)
{
    prefix = "Killfeed";
    description = "Killfeed on chat";
    website = "https://github.com/zcvmix";
    authors = {"hello world"};

    command("killfeed")
        .description("reload the killfeed configuration")
        .usages("/killfeed reload")
        .permissions("killfeed.reload");

    permission("killfeed.reload")
        .description("reload the killfeed config")
        .default_(endstone::PermissionDefault::Operator);
}
