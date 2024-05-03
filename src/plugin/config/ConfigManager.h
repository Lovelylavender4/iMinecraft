#pragma once
#include <aliases.h>
#include <nlohmann/json.hpp>
#include <string>

namespace Minecraft
{
using namespace MiracleForest;

class ConfigManager
{
public:
    struct OverallConfig
    {
        uint mFormatVersion;
        bool mEnable;
        bool mDebug;
        bool mEnableLog;
        struct Path
        {
            std::string mOverallConfig;
            std::string mFeaturesConfig;
        } mPath;
    } mOverallConfig;

public:
    ~ConfigManager();

    static ConfigManager& instance();

private:
    ConfigManager(std::string pOverallConfigFilePath);

    ConfigManager(const ConfigManager&)            = delete;
    ConfigManager(ConfigManager&&)                 = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;

public:
}; // class ConfigManager

} // namespace Minecraft

namespace nlohmann
{
using OverallConfig = Minecraft::ConfigManager::OverallConfig;

static void to_json(json& pJson, const OverallConfig::Path& pOverallConfigPath);
static void from_json(const json& pJson, OverallConfig::Path& pOverallConfigPath);

static void to_json(json& pJson, const OverallConfig& pOverallConfig);
static void from_json(const json& pJson, OverallConfig& pOverallConfig);
} // namespace nlohmann