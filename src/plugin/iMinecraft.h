#pragma once

#include "ll/api/mod/NativeMod.h"
#include "plugin/logger/Logger.h"

namespace iMinecraft
{

class iMinecraftPlugin
{
    using NativePlugin = ll::mod::NativeMod;

private:
    NativePlugin& mSelf;

public:
    iMinecraftPlugin(ll::mod::NativeMod& pSelf);

public:
    static iMinecraftPlugin& getInstance();

    static iLogger& getLogger();

public:
    [[nodiscard]] ll::mod::NativeMod& getSelf() const { return mSelf; }

    bool load();

    bool enable();

    bool disable();
}; // class iMinecraftPlugin

} // namespace iMinecraft
