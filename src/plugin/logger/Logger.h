#pragma once

#include "ll/api/Logger.h"
#include "plugin/utils/StringUtils.h"
#include "plugin/utils/TimeUtils.h"

namespace iMinecraft
{
#define COLORCAST(r, g, b) "\033[38;2;" #r ";" #g ";" #b "m"

class iLogger : public ll::Logger
{
public:
    using ll::Logger::Logger;

public:
    template<class... Args>
    void note(fmt::format_string<Args...> fmtstr, Args&&... args)
    {
        auto lock = Logger::lock();
        auto time = TimeUtils::getTimeNowStructure();
        fmt::print(
            fmt::runtime(
                StringUtils::sumString(
                    //COLORCAST(255, 170, 255),
                    //time.years,
                    //COLORCAST(240, 24, 28),
                    //".",
                    //COLORCAST(170, 255, 255),
                    //time.months,
                    //COLORCAST(240, 24, 28),
                    //".",
                    //COLORCAST(170, 170, 255),
                    //time.days,
                    //COLORCAST(240, 24, 28),
                    //".",
                    COLORCAST(134, 255, 217),
                    time.hours,
                    COLORCAST(240, 24, 28),
                    ":",
                    COLORCAST(255, 105, 252),
                    time.minutes,
                    COLORCAST(240, 24, 28),
                    ":",
                    COLORCAST(255, 240, 82),
                    time.seconds,
                    COLORCAST(240, 24, 28),
                    ":",
                    COLORCAST(39, 215, 231),
                    time.milliseconds,
                    COLORCAST(255, 170, 255),
                    " N",
                    COLORCAST(69, 255, 240),
                    "o",
                    COLORCAST(255, 255, 0),
                    "t",
                    COLORCAST(67, 236, 62),
                    "e ",
                    COLORCAST(156, 248, 255),
                    "[",
                    COLORCAST(228, 131, 255),
                    Logger::title,
                    COLORCAST(156, 248, 255),
                    "]",
                    //COLORCAST(240, 24, 28),
                    " ",
                    COLORCAST(137, 221, 255),
                    fmtstr.get().data(),
                    COLORCAST(255, 255, 255)
                )
                + "\n"
            ),
            std::forward<Args>(args)...
        );
    }
};

#undef COLORCAST
} // namespace iMinecraft
