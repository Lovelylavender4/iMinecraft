#include "plugin/utils/TimeUtils.h"

iMinecraft::TimeUtils::time_s iMinecraft::TimeUtils::getTimeNowStructure()
{
    iMinecraft::TimeUtils::time_s         time;
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm*    now_tm     = new std::tm;
    localtime_s(now_tm, &now_time_t);
    time.years   = now_tm->tm_year + 1900;
    time.months  = now_tm->tm_mon + 1;
    time.days    = now_tm->tm_mday;
    time.weeks   = now_tm->tm_wday + 1;
    time.hours   = now_tm->tm_hour;
    time.minutes = now_tm->tm_min;
    time.seconds = now_tm->tm_sec;

    time.yday  = now_tm->tm_yday;
    time.isdst = now_tm->tm_isdst;

    std::chrono::milliseconds ms;
    std::chrono::microseconds cs;
    std::chrono::nanoseconds  ns;

    ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    cs = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000000;
    ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()) % 1000000000;

    time.milliseconds = ms.count();
    time.microseconds = cs.count() % 1000;
    time.nanoseconds  = ns.count() % 1000;

    delete now_tm;
    return time;
}

std::string iMinecraft::TimeUtils::getTimeNow()
{
    time_s time = iMinecraft::TimeUtils::getTimeNowStructure();

    return fmt::format(
        "{0}.{1}.{2}.{3}:{4}:{5}:{6}",
        time.years,
        time.months,
        time.days,
        time.hours,
        time.minutes,
        time.seconds,
        time.milliseconds
    );
}
