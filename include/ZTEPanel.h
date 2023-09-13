#pragma once

#include "HTTPRequest.hpp"
#include "Base64.h"

#include <string>

class ZTEPanel final
{
public:
    explicit ZTEPanel(const std::string &ip, const std::string &password) : m_ip(ip), m_password(password) {}

    std::string Login() const noexcept;

private:
    std::string m_ip;
    std::string m_password;

    inline std::string GetIP() const noexcept
    {
        return m_ip;
    }

    inline std::string GetPassword() const noexcept
    {
        return m_password;
    }

    std::string GetRequest(const std::string &) const noexcept;

    std::string PostRequest(const std::string &, const std::string &) const noexcept;
};
