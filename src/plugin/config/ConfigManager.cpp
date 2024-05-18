#include "plugin/config/ConfigManager.h"
#include "plugin/Family.h"
#include "plugin/iMinecraft.h"
#include <filesystem>
#include <fstream>

namespace iMinecraft
{
using json = nlohmann::json;

ConfigManager::ConfigManager(std::string pOverallConfigFilePath)
    : mOverallConfigFilePath(pOverallConfigFilePath)
{
}

bool ConfigManager::load()
{
    if (!std::filesystem::exists(PLUGIN_WORK_DIR + mOverallConfigFilePath))
    {
        iMinecraftPlugin::getInstance().getSelf().getLogger().warn(
            "Unable to find configuration file: {}, ready to create this configuration!",
            mOverallConfigFilePath
        );
        if (!createOverallConfigFile())
        {
            iMinecraftPlugin::getInstance().getSelf().getLogger().error(
                "Failed to create configuration file: {}",
                PLUGIN_WORK_DIR + mOverallConfigFilePath
            );
            return false;
        }
        iMinecraftPlugin::getInstance().getSelf().getLogger().info(
            "Successfully created configuration file: {}",
            mOverallConfigFilePath
        );
    }
    else
    {
        std::fstream   overallConfigFile(PLUGIN_WORK_DIR + mOverallConfigFilePath);
        nlohmann::json overallConfigFileData;
        overallConfigFile >> overallConfigFileData;
        mOverallConfig = overallConfigFileData.get<OverallConfig>();
        overallConfigFile.close();
    }
    if (!std::filesystem::exists(PLUGIN_WORK_DIR + mOverallConfig.mPath.mFeaturesConfig))
    {
        iMinecraftPlugin::getInstance().getSelf().getLogger().warn(
            "Unable to find configuration file: {}, ready to create this configuration!",
            mOverallConfig.mPath.mFeaturesConfig
        );
        if (!createFeaturesConfigFile())
        {
            iMinecraftPlugin::getInstance().getSelf().getLogger().error(
                "Failed to create configuration file: {}",
                mOverallConfig.mPath.mFeaturesConfig
            );
            return false;
        }
        iMinecraftPlugin::getInstance().getSelf().getLogger().info(
            "Successfully created configuration file: {}",
            mOverallConfig.mPath.mFeaturesConfig
        );
    }
    else
    {
        std::fstream   featuresConfigFile(PLUGIN_WORK_DIR + mOverallConfig.mPath.mFeaturesConfig);
        nlohmann::json featuresConfigConfigFileData;
        featuresConfigFile >> featuresConfigConfigFileData;
        mFeaturesConfig = featuresConfigConfigFileData.get<FeaturesConfig>();
        featuresConfigFile.close();
    }
    return true;
}

bool ConfigManager::save()
{
    std::fstream overallConfigFile(PLUGIN_WORK_DIR + mOverallConfigFilePath, std::ios::out | std::ios::trunc);
    nlohmann::json overallConfigFileData = mOverallConfig;
    overallConfigFile << overallConfigFileData.dump(4);

    std::fstream featuresConfigFile(
        PLUGIN_WORK_DIR + mOverallConfig.mPath.mFeaturesConfig,
        std::ios::out | std::ios::trunc
    );
    nlohmann::json featuresConfigConfigFileData = mFeaturesConfig;
    featuresConfigFile << featuresConfigConfigFileData.dump(4);
    return true;
}

bool ConfigManager::createOverallConfigFile()
{
    std::filesystem::path currentDir = std::filesystem::current_path();
    std::filesystem::path filePath   = currentDir / (PLUGIN_WORK_DIR + mOverallConfigFilePath);
    std::filesystem::path parentPath = filePath.parent_path();
    std::filesystem::create_directories(parentPath);

    std::ofstream file(filePath);
    if (!file.is_open()) { return false; }
    file << nlohmann::json(mOverallConfig).dump(4);
    file.close();
    return true;
}

bool ConfigManager::createFeaturesConfigFile()
{
    std::filesystem::path currentDir = std::filesystem::current_path();
    std::filesystem::path filePath   = currentDir / (PLUGIN_WORK_DIR + mOverallConfig.mPath.mFeaturesConfig);
    std::filesystem::path parentPath = filePath.parent_path();
    std::filesystem::create_directories(parentPath);

    std::ofstream file(filePath);
    if (!file.is_open()) { return false; }
    file << nlohmann::json(mFeaturesConfig).dump(4);
    file.close();
    return true;
}

ConfigManager::~ConfigManager() {}

ConfigManager& ConfigManager::instance()
{
    static ConfigManager configManagerInstance(PLUGIN_OVERALL_CONFIG_FILE);
    return configManagerInstance;
}

} // namespace iMinecraft

namespace nlohmann
{
} // namespace nlohmann
