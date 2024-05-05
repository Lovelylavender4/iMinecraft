#include "plugin/Minecraft.h"
#include "feature/structure/village/MinecraftVillage.h"
#include "ll/api/plugin/NativePlugin.h"
#include "ll/api/plugin/RegisterHelper.h"
#include "plugin/config/ConfigManager.h"
#include <memory>

namespace Minecraft
{

static std::unique_ptr<MinecraftPlugin> instance;

MinecraftPlugin& MinecraftPlugin::getInstance() { return *instance; }

MinecraftPlugin::MinecraftPlugin(ll::plugin::NativePlugin& pSelf)
    : mSelf(pSelf)
{
}

bool MinecraftPlugin::load()
{
    getSelf().getLogger().info("Loading config...");
    if (!ConfigManager::instance().load())
    {
        getSelf().getLogger().error("Failed to load config.");
        return false;
    }
    getSelf().getLogger().info("Done.");
    return true;
}

bool MinecraftPlugin::enable()
{
    getSelf().getLogger().info("Starting...");
    MinecraftVillage::process();
    getSelf().getLogger().info("Done.");
    return true;
}

bool MinecraftPlugin::disable()
{
    getSelf().getLogger().info("Saving config...");
    ConfigManager::instance().save();
    getSelf().getLogger().info("Done.");
    return true;
}

} // namespace Minecraft

LL_REGISTER_PLUGIN(Minecraft::MinecraftPlugin, Minecraft::instance);
