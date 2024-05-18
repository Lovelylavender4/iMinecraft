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

static void to_json(json& pJson, const VillageSpecifiedChunk& pSpecifiedChunkPosition);
static void from_json(const json& pJson, VillageSpecifiedChunk& pSpecifiedChunkPosition);

static void to_json(json& pJson, const ChunkPos& pChunkPos);
static void from_json(const json& pJson, ChunkPos& pChunkPos);
} // namespace nlohmann