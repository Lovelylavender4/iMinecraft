#include "plugin/iMinecraft.h"
#include "feature/structure/village/MinecraftVillage.h"
#include "ll/api/plugin/NativePlugin.h"
#include "ll/api/plugin/RegisterHelper.h"
#include "plugin/config/ConfigManager.h"
#include <memory>

namespace iMinecraft
{

static std::unique_ptr<iMinecraftPlugin> instance;

iMinecraftPlugin& iMinecraftPlugin::getInstance() { return *instance; }

iLogger& iMinecraftPlugin::getLogger()
{
    static iMinecraft::iLogger logger("iMinecraft");
    return logger;
}

iMinecraftPlugin::iMinecraftPlugin(ll::plugin::NativePlugin& pSelf)
    : mSelf(pSelf)
{
}

bool iMinecraftPlugin::load()
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

bool iMinecraftPlugin::enable()
{
    getSelf().getLogger().info("Starting...");
    MinecraftVillage::process();
    getSelf().getLogger().info("Done.");
    return true;
}

bool iMinecraftPlugin::disable()
{
    getSelf().getLogger().info("Saving config...");
    ConfigManager::instance().save();
    getSelf().getLogger().info("Done.");
    return true;
}

} // namespace iMinecraft

LL_REGISTER_PLUGIN(iMinecraft::iMinecraftPlugin, iMinecraft::instance);
