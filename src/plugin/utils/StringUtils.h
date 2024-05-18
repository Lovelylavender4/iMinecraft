#pragma once
#include <aliases.h>
#include <string>

namespace iMinecraft::inline Utils::StringUtils
{
template<class _Ty>
[[nodiscard]] inline std::string toString(_Ty dat)
{
    return std::to_string(dat);
}

template<>
[[nodiscard]] inline std::string toString<std::string>(std::string dat)
{
    return dat;
}

template<>
[[nodiscard]] inline std::string toString<MiracleForest::CPtr<char>>(MiracleForest::CPtr<char> dat)
{
    return dat;
}

template<class... Args>
[[nodiscard]] inline std::string sumString(MiracleForest::RRef<Args>... args)
{
    return (... + toString(std::forward<Args>(args)));
}
} // namespace iMinecraft::inline Utils::StringUtils
