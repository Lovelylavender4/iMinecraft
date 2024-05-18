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
    pOverallConfig.mFormatVersion = pJson["format_version"].get<iMinecraft::uint>();
    pOverallConfig.mEnable        = pJson["enable"].get<bool>();
    pOverallConfig.mDebug         = pJson["debug"].get<bool>();
    pOverallConfig.mEnableLog     = pJson["enable_log"].get<bool>();
    pOverallConfig.mPath          = pJson["path"].get<OverallConfig::Path>();
}

static void to_json(json& pJson, const FeaturesConfig& pFeaturesConfig)
{
    pJson["features"] = pFeaturesConfig.mFeatures;
}
static void from_json(const json& pJson, FeaturesConfig& pFeaturesConfig)
{
    pFeaturesConfig.mFeatures = pJson["features"].get<FeaturesConfig::Features>();
}

static void to_json(json& pJson, const FeaturesConfig::Features& pFeatures)
{
    pJson["structures"] = pFeatures.mStructures;
}
static void from_json(const json& pJson, FeaturesConfig::Features& pFeatures)
{
    pFeatures.mStructures = pJson["structures"].get<FeaturesConfig::Features::Structures>();
}

static void to_json(json& pJson, const FeaturesStructures& pStructures)
{
    pJson["village"] = pStructures.mVillage;
}
static void from_json(const json& pJson, FeaturesStructures& pStructures)
{
    pStructures.mVillage = pJson["village"].get<FeaturesStructures::Village>();
}

static void to_json(json& pJson, const FeaturesStructures::Village& pVillage)
{
    pJson["spawn"]                    = pVillage.mSpawn;
    pJson["enable"]                   = pVillage.mEnable;
    pJson["town_spacing"]             = pVillage.mTownSpacing;
    pJson["min_town_separation"]      = pVillage.mMinTownSeparation;
    pJson["specified_chunk_position"] = pVillage.mSpecifiedChunk;
}
static void from_json(const json& pJson, FeaturesStructures::Village& pVillage)
{
    pVillage.mSpawn             = pJson["spawn"].get<bool>();
    pVillage.mEnable            = pJson["enable"].get<bool>();
    pVillage.mTownSpacing       = pJson["town_spacing"].get<uint>();
    pVillage.mMinTownSeparation = pJson["min_town_separation"].get<uint>();
    pVillage.mSpecifiedChunk    = pJson["specified_chunk_position"].get<std::vector<VillageSpecifiedChunk>>();
}

static void to_json(json& pJson, const VillageSpecifiedChunk& pSpecifiedChunkPosition)
{
    pJson["enable"]   = pSpecifiedChunkPosition.mEnable;
    pJson["spawn"]    = pSpecifiedChunkPosition.mSpawn;
    pJson["position"] = pSpecifiedChunkPosition.mPosition;
}
static void from_json(const json& pJson, VillageSpecifiedChunk& pSpecifiedChunkPosition)
{
    pSpecifiedChunkPosition.mEnable   = pJson["enable"].get<bool>();
    pSpecifiedChunkPosition.mSpawn    = pJson["spawn"].get<bool>();
    pSpecifiedChunkPosition.mPosition = pJson["position"].get<ChunkPos>();
}

static void to_json(json& pJson, const ChunkPos& pChunkPos) { pJson = { pChunkPos.x, pChunkPos.z }; }
static void from_json(const json& pJson, ChunkPos& pChunkPos)
{
    pChunkPos.x = pJson[0].get<int>();
    pChunkPos.z = pJson[1].get<int>();
}

} // namespace nlohmann