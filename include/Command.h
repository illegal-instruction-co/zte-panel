#pragma once

#include <string>
#include <functional>

struct Command final
{
    std::string shortCmd;
    std::string longCmd;
    std::function<void()> cb;

    inline bool Match(const std::string &arg) const
    {
        return (arg == shortCmd || arg == longCmd);
    }
};
