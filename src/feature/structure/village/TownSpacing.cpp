#include "feature/structure/village/MinecraftVillage.h"
#include "ll/api/memory/Hook.h"
#include "mc/world/level/levelgen/structure/VillageFeature.h"
#include "plugin/config/ConfigManager.h"

using ConfigManager = Minecraft::ConfigManager;

LL_TYPE_INSTANCE_HOOK(
    MinecraftVillageHook,
    ll::memory::HookPriority::Normal,
    VillageFeature,
    "??0VillageFeature@@QEAA@IHH@Z",
    VillageFeature*,
    uint pSeed,
    int  pTownSpacing,
    int  pMinTownSeparation
)
{
    auto& villageConfig = ConfigManager::instance().mFeaturesConfig.mFeatures.mStructures.mVillage;
    if (villageConfig.mEnable)
    {
        return origin(
            pSeed,
            (villageConfig.mTownSpacing == -1) ? pTownSpacing : villageConfig.mTownSpacing,
            (villageConfig.mMinTownSeparation == -1) ? pMinTownSeparation : villageConfig.mMinTownSeparation
        );
    }
    return origin(pSeed, pTownSpacing, pMinTownSeparation);
}

void Minecraft::MinecraftVillage::townSpacingProcess() { MinecraftVillageHook::hook(); }
