#include "feature/structure/village/MinecraftVillage.h"
#include "ll/api/memory/Hook.h"
#include "mc/util/Random.h"
#include "mc/world/level/dimension/Dimension.h"
#include "mc/world/level/levelgen/structure/VillageFeature.h"
#include "mc/world/level/levelgen/v1/BiomeSource.h"
#include "mc/world/level/levelgen/v1/IPreliminarySurfaceProvider.h"
#include "plugin/config/ConfigManager.h"

using ConfigManager = Minecraft::ConfigManager;
using uint          = MiracleForest::uint;

LL_TYPE_INSTANCE_HOOK(
    MinecraftVillageHook,
    ll::memory::HookPriority::Normal,
    VillageFeature,
    "?isFeatureChunk@VillageFeature@@UEAA_NAEBVBiomeSource@@AEAVRandom@@AEBVChunkPos@@"
    "IAEBVIPreliminarySurfaceProvider@@AEBVDimension@@@Z",
    bool,
    const BiomeSource&                 pBiomeSource,
    Random&                            pRandom,
    const ChunkPos&                    pChunkPos,
    uint                               pLevelSeed,
    const IPreliminarySurfaceProvider& pIPreliminarySurfaceProvider,
    const Dimension&                   pDimension
)
{
    auto& villageConfig = ConfigManager::instance().mFeaturesConfig.mFeatures.mStructures.mVillage;
    bool  r = origin(pBiomeSource, pRandom, pChunkPos, pLevelSeed, pIPreliminarySurfaceProvider, pDimension);
    if (villageConfig.mEnable)
    {
        if (!villageConfig.mSpawn) { return false; }
        if (!villageConfig.mSpecifiedChunk.empty())
        {
            for (auto& specifiedChunk : villageConfig.mSpecifiedChunk)
            {
                if (!specifiedChunk.mEnable) { continue; }
                if (specifiedChunk.mPosition == pChunkPos) { return specifiedChunk.mSpawn; }
            }
        }
    }
    return r;
}

void Minecraft::MinecraftVillage::specifiedPositionProcess() { MinecraftVillageHook::hook(); }
