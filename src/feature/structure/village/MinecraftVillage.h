#pragma once

#include "plugin/Family.h"

namespace iMinecraft
{

class MinecraftVillage
{
public:
    static void process();

private:
    static void townSpacingProcess();
    static void specifiedPositionProcess();
}; // class MinecraftVillage

} // namespace iMinecraft