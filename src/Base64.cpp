#include "Base64.h"

using namespace std;

string Base64::Encode(const void *data, size_t size)
{
    string result;
    result.reserve(((size + 2) / 3) * 4);

    const auto *bytes = static_cast<const uint8_t *>(data);
    size_t i = 0;
    for (; i + 3 <= size; i += 3)
    {
        const uint32_t value = (bytes[i] << 16) | (bytes[i + 1] << 8) | bytes[i + 2];
        result.push_back(kEncodeTable[(value >> 18) & 0x3F]);
        result.push_back(kEncodeTable[(value >> 12) & 0x3F]);
        result.push_back(kEncodeTable[(value >> 6) & 0x3F]);
        result.push_back(kEncodeTable[value & 0x3F]);
    }

    if (i + 1 == size)
    {
        const uint32_t value = bytes[i] << 16;
        result.push_back(kEncodeTable[(value >> 18) & 0x3F]);
        result.push_back(kEncodeTable[(value >> 12) & 0x3F]);
        result.push_back('=');
        result.push_back('=');
    }
    else if (i + 2 == size)
    {
        const uint32_t value = (bytes[i] << 16) | (bytes[i + 1] << 8);
        result.push_back(kEncodeTable[(value >> 18) & 0x3F]);
        result.push_back(kEncodeTable[(value >> 12) & 0x3F]);
        result.push_back(kEncodeTable[(value >> 6) & 0x3F]);
        result.push_back('=');
    }

    return result;
}

string Base64::Decode(const string_view &str)
{
    static constexpr auto decodeChar = [](char c)
    {
        if (c >= 'A' && c <= 'Z')
            return c - 'A';
        if (c >= 'a' && c <= 'z')
            return c - 'a' + 26;
        if (c >= '0' && c <= '9')
            return c - '0' + 52;
        if (c == '+')
            return 62;
        if (c == '/')
            return 63;
        return 0;
    };

    string result;
    result.reserve((str.size() / 4) * 3);

    size_t i = 0;
    for (; i + 4 <= str.size(); i += 4)
    {
        const uint32_t value = (decodeChar(str[i]) << 18) | (decodeChar(str[i + 1]) << 12) | (decodeChar(str[i + 2]) << 6) | decodeChar(str[i + 3]);
        result.push_back((value >> 16) & 0xFF);
        result.push_back((value >> 8) & 0xFF);
        result.push_back(value & 0xFF);
    }

    if (i + 2 == str.size())
    {
        const uint32_t value = (decodeChar(str[i]) << 18) | (decodeChar(str[i + 1]) << 12);
        result.push_back((value >> 16) & 0xFF);
    }
    else if (i + 3 == str.size())
    {
        const uint32_t value = (decodeChar(str[i]) << 18) | (decodeChar(str[i + 1]) << 12) | (decodeChar(str[i + 2]) << 6);
        result.push_back((value >> 16) & 0xFF);
        result.push_back((value >> 8) & 0xFF);
    }

    return result;
}
