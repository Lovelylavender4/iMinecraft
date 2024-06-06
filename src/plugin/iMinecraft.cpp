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
#ifdef MINECRAFT_DEBUG
    SelfLogger.warn("Debug mode has been enabled for iMinecraft!");
#endif //^^^^ MINECRAFT_DEBUG ^^^^
    SelfLogger.info("Loading config...");
    if (!ConfigManager::instance().load())
    {
        SelfLogger.error("Failed to load config.");
        return false;
    }
    SelfLogger.info("Done.");
    return true;
}

bool iMinecraftPlugin::enable()
{
    SelfLogger.info("Starting...");
    MinecraftVillage::process();
    SelfLogger.info("Done.");
    return true;
}

bool iMinecraftPlugin::disable()
{
    SelfLogger.info("Saving config...");
    ConfigManager::instance().save();
    SelfLogger.info("Done.");
    return true;
}

} // namespace iMinecraft

LL_REGISTER_PLUGIN(iMinecraft::iMinecraftPlugin, iMinecraft::instance);
