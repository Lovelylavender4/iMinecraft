#include "plugin/config/ConfigManager.h"
#include "plugin/family.h"

namespace Minecraft
{
using json = nlohmann::json;

ConfigManager::ConfigManager(std::string pOverallConfigFilePath) {}

ConfigManager::~ConfigManager() {}

ConfigManager& ConfigManager::instance()
{
    static ConfigManager configManagerInstance(PLUGIN_OVERALL_CONFIG_FILE);
    return configManagerInstance;
}
} // namespace Minecraft

namespace nlohmann
{

static void to_json(json& pJson, const OverallConfig::Path& pOverallConfigPath)
{
    pJson["overall_config"]  = pOverallConfigPath.mOverallConfig;
    pJson["features_config"] = pOverallConfigPath.mFeaturesConfig;
}
static void from_json(const json& pJson, OverallConfig::Path& pOverallConfigPath)
{
    pOverallConfigPath.mOverallConfig  = pJson["overall_config"].get<std::string>();
    pOverallConfigPath.mFeaturesConfig = pJson["features_config"].get<std::string>();
}

static void to_json(json& pJson, const OverallConfig& pOverallConfig)
{
    pJson["format_version"] = pOverallConfig.mFormatVersion;
    pJson["enable"]         = pOverallConfig.mEnable;
    pJson["debug"]          = pOverallConfig.mDebug;
    pJson["enable_log"]     = pOverallConfig.mEnableLog;
    pJson["path"]           = pOverallConfig.mPath;
}
static void from_json(const json& pJson, OverallConfig& pOverallConfig)
{
    pOverallConfig.mFormatVersion = pJson["format_version"].get<Minecraft::uint>();
    pOverallConfig.mEnable        = pJson["enable"].get<bool>();
    pOverallConfig.mDebug         = pJson["debug"].get<bool>();
    pOverallConfig.mEnableLog     = pJson["enable_log"].get<bool>();
    pOverallConfig.mPath          = pJson["path"].get<OverallConfig::Path>();
}
} // namespace nlohmann