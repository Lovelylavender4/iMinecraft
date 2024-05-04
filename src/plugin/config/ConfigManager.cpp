#include "plugin/config/ConfigManager.h"
#include "plugin/family.h"
#include <fstream>

namespace Minecraft
{
using json = nlohmann::json;

ConfigManager::ConfigManager()
    : mOverallConfigManager(PLUGIN_OVERALL_CONFIG_FILE)
{
}

bool ConfigManager::load() { return overallConfigManagerInstance().load(); }

bool ConfigManager::save() { return overallConfigManagerInstance().save(); }

ConfigManager::~ConfigManager() {}

ConfigManager::OverallConfigManager& ConfigManager::overallConfigManagerInstance()
{
    return instance().mOverallConfigManager;
}

ConfigManager& ConfigManager::instance()
{
    static ConfigManager configManagerInstance;
    return configManagerInstance;
}

ConfigManager::OverallConfigManager::OverallConfigManager(std::string pOverallConfigFilePath)
    : mOverallConfigFilePath(pOverallConfigFilePath)
    , mOverallConfig()
{
}

bool ConfigManager::OverallConfigManager::load()
{
    std::fstream   overallConfigFile(mOverallConfigFilePath);
    nlohmann::json data;
    overallConfigFile >> data;
    mOverallConfig = data.get<OverallConfig>();
    return true;
}

bool ConfigManager::OverallConfigManager::save()
{
    std::fstream   overallConfigFile(mOverallConfigFilePath, std::ios::out | std::ios::trunc);
    nlohmann::json data = mOverallConfig;
    overallConfigFile << data.dump(4);
    return true;
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

static void to_json(json& pJson, const FeaturesConfig& pFeaturesConfig)
{
    pJson["Features"] = pFeaturesConfig.mFeatures;
}
static void from_json(const json& pJson, FeaturesConfig& pFeaturesConfig)
{
    pFeaturesConfig.mFeatures = pJson["Features"].get<FeaturesConfig::Features>();
}

static void to_json(json& pJson, const FeaturesConfig::Features& pFeatures)
{
    pJson["Structures"] = pFeatures.mStructures;
}
static void from_json(const json& pJson, FeaturesConfig::Features& pFeatures)
{
    pFeatures.mStructures = pJson["Structures"].get<FeaturesConfig::Features::Structures>();
}

static void to_json(json& pJson, const FeaturesStructures& pStructures)
{
    pJson["Village"] = pStructures.mVillage;
}
static void from_json(const json& pJson, FeaturesStructures& pStructures)
{
    pStructures.mVillage = pJson["Village"].get<FeaturesStructures::Village>();
}

static void to_json(json& pJson, const FeaturesStructures::Village& pVillage)
{
    pJson["Spawn"]                  = pVillage.mSpawn;
    pJson["Enable"]                 = pVillage.mEnable;
    pJson["TownSpacing"]            = pVillage.mTownSpacing;
    pJson["MinTownSeparation"]      = pVillage.mMinTownSeparation;
    pJson["SpecifiedChunkPosition"] = pVillage.mSpecifiedChunkPosition;
}
static void from_json(const json& pJson, FeaturesStructures::Village& pVillage)
{
    pVillage.mSpawn             = pJson["Spawn"].get<bool>();
    pVillage.mEnable            = pJson["Enable"].get<bool>();
    pVillage.mTownSpacing       = pJson["TownSpacing"].get<uint>();
    pVillage.mMinTownSeparation = pJson["MinTownSeparation"].get<uint>();
    pVillage.mSpecifiedChunkPosition =
        pJson["SpecifiedChunkPosition"].get<std::vector<VillageSpecifiedChunkPosition>>();
}

static void to_json(json& pJson, const VillageSpecifiedChunkPosition& pSpecifiedChunkPosition)
{
    pJson["Enable"]   = pSpecifiedChunkPosition.mEnable;
    pJson["Spawn"]    = pSpecifiedChunkPosition.mSpawn;
    pJson["Position"] = pSpecifiedChunkPosition.mPosition;
}
static void from_json(const json& pJson, VillageSpecifiedChunkPosition& pSpecifiedChunkPosition)
{
    pSpecifiedChunkPosition.mEnable   = pJson["Enable"].get<bool>();
    pSpecifiedChunkPosition.mSpawn    = pJson["Spawn"].get<bool>();
    pSpecifiedChunkPosition.mPosition = pJson["Position"].get<ChunkPos>();
}

static void to_json(json& pJson, const ChunkPos& pChunkPos) { pJson = { pChunkPos.x, pChunkPos.z }; }
static void from_json(const json& pJson, ChunkPos& pChunkPos)
{
    pChunkPos.x = pJson[0].get<int>();
    pChunkPos.z = pJson[1].get<int>();
}

} // namespace nlohmann