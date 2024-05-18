#pragma once
#include <aliases.h>
#include <mc/world/level/ChunkPos.h>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace iMinecraft
{
using namespace MiracleForest;

class ConfigManager
{
    std::string mOverallConfigFilePath;
    std::string mFeaturesConfigFilePath;

public:
    struct OverallConfig
    {
        uint mFormatVersion = 0;
        bool mEnable        = true;
        bool mDebug         = false;
        bool mEnableLog     = true;
        struct Path
        {
            std::string mOverallConfig  = "config/config.json";
            std::string mFeaturesConfig = "config/features.json";
        } mPath;
    } mOverallConfig;

    struct FeaturesConfig
    {
        struct Features
        {
            struct Structures
            {
                struct Village
                {
                    bool mSpawn             = true;
                    bool mEnable            = true;
                    int  mTownSpacing       = -1;
                    int  mMinTownSeparation = -1;
                    struct SpecifiedChunk
                    {
                        bool     mEnable = true;
                        bool     mSpawn  = true;
                        ChunkPos mPosition { 0, 0 };
                    };
                    std::vector<SpecifiedChunk> mSpecifiedChunk {};
                } mVillage;
            } mStructures;
        } mFeatures;
    } mFeaturesConfig;


private:
public:
    ~ConfigManager();

    static ConfigManager& instance();

private:
    ConfigManager(std::string pOverallConfigFilePath);

    ConfigManager(const ConfigManager&)            = delete;
    ConfigManager(ConfigManager&&)                 = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;

public:
    bool load();
    bool save();

private:
    bool createOverallConfigFile();
    bool createFeaturesConfigFile();
}; // class ConfigManager

} // namespace iMinecraft

namespace nlohmann
{
using OverallConfig         = iMinecraft::ConfigManager::OverallConfig;
using FeaturesConfig        = iMinecraft::ConfigManager::FeaturesConfig;
using FeaturesStructures    = FeaturesConfig::Features::Structures;
using VillageSpecifiedChunk = FeaturesConfig::Features::Structures::Village::SpecifiedChunk;

static void to_json(json& pJson, const OverallConfig::Path& pOverallConfigPath);
static void from_json(const json& pJson, OverallConfig::Path& pOverallConfigPath);

static void to_json(json& pJson, const OverallConfig& pOverallConfig);
static void from_json(const json& pJson, OverallConfig& pOverallConfig);

static void to_json(json& pJson, const FeaturesConfig& pFeaturesConfig);
static void from_json(const json& pJson, FeaturesConfig& pFeaturesConfig);

static void to_json(json& pJson, const FeaturesConfig::Features& pFeatures);
static void from_json(const json& pJson, FeaturesConfig::Features& pFeatures);

static void to_json(json& pJson, const FeaturesStructures& pStructures);
static void from_json(const json& pJson, FeaturesStructures& pStructures);

static void to_json(json& pJson, const FeaturesStructures::Village& pVillage);
static void from_json(const json& pJson, FeaturesStructures::Village& pVillage);

static void to_json(json& pJson, const ChunkPos& pChunkPos);
static void from_json(const json& pJson, ChunkPos& pChunkPos);

static void to_json(json& pJson, const VillageSpecifiedChunk& pSpecifiedChunkPosition);
static void from_json(const json& pJson, VillageSpecifiedChunk& pSpecifiedChunkPosition);


void to_json(json& pJson, const OverallConfig::Path& pOverallConfigPath)
{
    pJson["overall_config"]  = pOverallConfigPath.mOverallConfig;
    pJson["features_config"] = pOverallConfigPath.mFeaturesConfig;
}
void from_json(const json& pJson, OverallConfig::Path& pOverallConfigPath)
{
    pOverallConfigPath.mOverallConfig  = pJson["overall_config"].get<std::string>();
    pOverallConfigPath.mFeaturesConfig = pJson["features_config"].get<std::string>();
}

void to_json(json& pJson, const OverallConfig& pOverallConfig)
{
    pJson["format_version"] = pOverallConfig.mFormatVersion;
    pJson["enable"]         = pOverallConfig.mEnable;
    pJson["debug"]          = pOverallConfig.mDebug;
    pJson["enable_log"]     = pOverallConfig.mEnableLog;
    pJson["path"]           = pOverallConfig.mPath;
}
void from_json(const json& pJson, OverallConfig& pOverallConfig)
{
    pOverallConfig.mFormatVersion = pJson["format_version"].get<iMinecraft::uint>();
    pOverallConfig.mEnable        = pJson["enable"].get<bool>();
    pOverallConfig.mDebug         = pJson["debug"].get<bool>();
    pOverallConfig.mEnableLog     = pJson["enable_log"].get<bool>();
    pOverallConfig.mPath          = pJson["path"].get<OverallConfig::Path>();
}

void to_json(json& pJson, const FeaturesConfig& pFeaturesConfig)
{
    pJson["features"] = pFeaturesConfig.mFeatures;
}
void from_json(const json& pJson, FeaturesConfig& pFeaturesConfig)
{
    pFeaturesConfig.mFeatures = pJson["features"].get<FeaturesConfig::Features>();
}

void to_json(json& pJson, const FeaturesConfig::Features& pFeatures)
{
    pJson["structures"] = pFeatures.mStructures;
}
void from_json(const json& pJson, FeaturesConfig::Features& pFeatures)
{
    pFeatures.mStructures = pJson["structures"].get<FeaturesConfig::Features::Structures>();
}

void to_json(json& pJson, const FeaturesStructures& pStructures) { pJson["village"] = pStructures.mVillage; }
void from_json(const json& pJson, FeaturesStructures& pStructures)
{
    pStructures.mVillage = pJson["village"].get<FeaturesStructures::Village>();
}

void to_json(json& pJson, const FeaturesStructures::Village& pVillage)
{
    pJson["spawn"]                    = pVillage.mSpawn;
    pJson["enable"]                   = pVillage.mEnable;
    pJson["town_spacing"]             = pVillage.mTownSpacing;
    pJson["min_town_separation"]      = pVillage.mMinTownSeparation;
    pJson["specified_chunk_position"] = pVillage.mSpecifiedChunk;
}
void from_json(const json& pJson, FeaturesStructures::Village& pVillage)
{
    pVillage.mSpawn             = pJson["spawn"].get<bool>();
    pVillage.mEnable            = pJson["enable"].get<bool>();
    pVillage.mTownSpacing       = pJson["town_spacing"].get<uint>();
    pVillage.mMinTownSeparation = pJson["min_town_separation"].get<uint>();
    pVillage.mSpecifiedChunk    = pJson["specified_chunk_position"].get<std::vector<VillageSpecifiedChunk>>();
}

void to_json(json& pJson, const VillageSpecifiedChunk& pSpecifiedChunkPosition)
{
    pJson["enable"]   = pSpecifiedChunkPosition.mEnable;
    pJson["spawn"]    = pSpecifiedChunkPosition.mSpawn;
    pJson["position"] = pSpecifiedChunkPosition.mPosition;
}
void from_json(const json& pJson, VillageSpecifiedChunk& pSpecifiedChunkPosition)
{
    pSpecifiedChunkPosition.mEnable   = pJson["enable"].get<bool>();
    pSpecifiedChunkPosition.mSpawn    = pJson["spawn"].get<bool>();
    pSpecifiedChunkPosition.mPosition = pJson["position"].get<ChunkPos>();
}

void to_json(json& pJson, const ChunkPos& pChunkPos) { pJson = { pChunkPos.x, pChunkPos.z }; }
void from_json(const json& pJson, ChunkPos& pChunkPos)
{
    pChunkPos.x = pJson[0].get<int>();
    pChunkPos.z = pJson[1].get<int>();
}
} // namespace nlohmann
