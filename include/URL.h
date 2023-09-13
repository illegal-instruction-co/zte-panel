#pragma once

#include <iomanip>
#include <sstream>
#include <string>

struct URL final {
    static std::string Encode(const std::string&);
};
