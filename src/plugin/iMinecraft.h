#pragma once

#include "ll/api/plugin/NativePlugin.h"
#include "plugin/logger/Logger.h"

namespace iMinecraft
{

class iMinecraftPlugin
{
    using NativePlugin = ll::plugin::NativePlugin;

private:
    NativePlugin& mSelf;

public:
    iMinecraftPlugin(ll::plugin::NativePlugin& pSelf);

public:
    static iMinecraftPlugin& getInstance();

    static iLogger& getLogger();

public:
    [[nodiscard]] ll::plugin::NativePlugin& getSelf() const { return mSelf; }

    bool load();

    bool enable();

    bool disable();
}; // class iMinecraftPlugin

} // namespace iMinecraft
