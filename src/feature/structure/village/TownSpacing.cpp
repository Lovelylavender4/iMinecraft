#include "feature/structure/village/MinecraftVillage.h"
#include "ll/api/memory/Hook.h"
#include "mc/world/level/levelgen/structure/VillageFeature.h"
#include "plugin/config/ConfigManager.h"
#include "plugin/iMinecraft.h"

using ConfigManager = iMinecraft::ConfigManager;

LL_TYPE_INSTANCE_HOOK(
    MinecraftVillageCtorHook,
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
#ifdef MINECRAFT_DEBUG
    SelfLogger.info("MinecraftVillageCtorHook called");
#endif //^^^^ MINECRAFT_DEBUG ^^^^

    if (villageConfig.mEnable)
    {
#ifdef MINECRAFT_DEBUG
        SelfLogger.info(
            // o means original value
            "with {{Seed={}, TownSpacing={}(o:{}), "
            "MinTownSeparation={}(o:{})}}",
            pSeed,
            /*TownSpacing*/ (villageConfig.mTownSpacing == -1) ? pTownSpacing : villageConfig.mTownSpacing,
            pTownSpacing,
            /*MinTownSeparation*/
            (villageConfig.mMinTownSeparation == -1) ? pMinTownSeparation : villageConfig.mMinTownSeparation,
            pMinTownSeparation
        );
#endif //^^^^ MINECRAFT_DEBUG ^^^^
        if (villageConfig.mTownSpacing < villageConfig.mMinTownSeparation)
        {
            SelfLogger.error(
                "MinTownSeparation should not be smaller than TownSpacing! Apply original "
                "settings: TownSpacing={}, MinTownSeparation={}",
                pTownSpacing,
                pMinTownSeparation
            );
            return origin(pSeed, pTownSpacing, pMinTownSeparation);
        }
        return origin(
            pSeed,
            (villageConfig.mTownSpacing == -1) ? pTownSpacing : villageConfig.mTownSpacing,
            (villageConfig.mMinTownSeparation == -1) ? pMinTownSeparation : villageConfig.mMinTownSeparation
        );
    }
#ifdef MINECRAFT_DEBUG
    else { SelfLogger.info("VillageConfig disabled."); }
#endif //^^^^ MINECRAFT_DEBUG ^^^^
    return origin(pSeed, pTownSpacing, pMinTownSeparation);
}

void iMinecraft::MinecraftVillage::townSpacingProcess()
{
    MinecraftVillageCtorHook::hook();
#ifdef MINECRAFT_DEBUG
    SelfLogger.info("MinecraftVillageCtorHook hooked.");
#endif //^^^^ MINECRAFT_DEBUG ^^^^
}
