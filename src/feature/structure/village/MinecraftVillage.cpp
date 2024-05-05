#include "feature/structure/village/MinecraftVillage.h"
#include "ll/api/memory/Hook.h"
#include "mc/world/level/levelgen/structure/VillageFeature.h"

void Minecraft::MinecraftVillage::process()
{
    townSpacingProcess();
    specifiedPositionProcess();
}
