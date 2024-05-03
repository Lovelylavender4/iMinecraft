#pragma once

#include "ll/api/plugin/NativePlugin.h"

namespace Minecraft
{

class MinecraftPlugin
{
    using NativePlugin = ll::plugin::NativePlugin;

private:
    NativePlugin& mSelf;

public:
    MinecraftPlugin(ll::plugin::NativePlugin& pSelf);

public:
    static MinecraftPlugin& getInstance();

public:
    [[nodiscard]] ll::plugin::NativePlugin& getSelf() const { return mSelf; }

    bool load();

    bool enable();

    bool disable();
}; // class MinecraftPlugin

} // namespace Minecraft
