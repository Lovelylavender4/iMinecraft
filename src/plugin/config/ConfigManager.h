#pragma once
#include <aliases.h>
#include <mc/world/level/ChunkPos.h>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace Minecraft
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
        bool mEnable        = false;
        bool mDebug         = false;
        bool mEnableLog     = false;
        struct Path
        {
            std::string mOverallConfig  = "";
            std::string mFeaturesConfig = "";
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
                    bool mSpawn             = false;
                    bool mEnable            = false;
                    int  mTownSpacing       = -1;
                    int  mMinTownSeparation = -1;
                    struct SpecifiedChunkPosition
                    {
                        bool     mEnable = false;
                        bool     mSpawn  = false;
                        ChunkPos mPosition {};
                    };
                    std::vector<SpecifiedChunkPosition> mSpecifiedChunkPosition {};
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
}; // class ConfigManager

} // namespace Minecraft

namespace nlohmann
{
using OverallConfig                 = Minecraft::ConfigManager::OverallConfig;
using FeaturesConfig                = Minecraft::ConfigManager::FeaturesConfig;
using FeaturesStructures            = FeaturesConfig::Features::Structures;
using VillageSpecifiedChunkPosition = FeaturesConfig::Features::Structures::Village::SpecifiedChunkPosition;

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

static void to_json(json& pJson, const VillageSpecifiedChunkPosition& pSpecifiedChunkPosition);
static void from_json(const json& pJson, VillageSpecifiedChunkPosition& pSpecifiedChunkPosition);

static void to_json(json& pJson, const ChunkPos& pChunkPos);
static void from_json(const json& pJson, ChunkPos& pChunkPos);
} // namespace nlohmann