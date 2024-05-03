#include "plugin/Minecraft.h"
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
    getSelf().getLogger().info("Loading...");
    // Code for loading the plugin goes here.
    return true;
}

bool MinecraftPlugin::enable()
{
    getSelf().getLogger().info("Enabling...");
    // Code for enabling the plugin goes here.
    return true;
}

bool MinecraftPlugin::disable()
{
    getSelf().getLogger().info("Disabling...");
    // Code for disabling the plugin goes here.
    return true;
}

} // namespace Minecraft

LL_REGISTER_PLUGIN(Minecraft::MinecraftPlugin, Minecraft::instance);
