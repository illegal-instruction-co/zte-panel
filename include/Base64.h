#pragma once

#include <string>
#include <string_view>

struct Base64 final
{
    static inline std::string EncodeString(const std::string_view &str)
    {
        return Encode(str.data(), str.size());
    }

    static inline std::string DecodeString(const std::string_view &str)
    {
        return Decode(str);
    }

    static std::string Encode(const void *, size_t);
    static std::string Decode(const std::string_view &);

    static constexpr char kEncodeTable[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
};
