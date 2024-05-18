#pragma once
#include <aliases.h>
#include <chrono>
#include <fmt/core.h>

namespace iMinecraft::inline Utils::TimeUtils
{
struct time_s
{
    using ushort        = MiracleForest::ushort;
    ushort years        = 0;
    ushort months       = 0;
    ushort days         = 0;
    ushort weeks        = 0;
    ushort hours        = 0;
    ushort minutes      = 0;
    ushort seconds      = 0;
    ushort milliseconds = 0;
    ushort microseconds = 0;
    ushort nanoseconds  = 0;
    ushort yday         = 0;
    int    isdst        = 0;
};
[[nodiscard]] time_s getTimeNowStructure();

[[nodiscard]] std::string getTimeNow();

} // namespace iMinecraft::inline Utils::TimeUtils
