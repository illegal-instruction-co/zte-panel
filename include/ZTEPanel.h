#pragma once

#include "Base64.h"
#include "HTTPRequest.hpp"

#include <string>
#include <string_view>

class ZTEPanel final {
  public:
    ZTEPanel(const std::string& ip, const std::string& password)
        : m_ip(ip), m_password(password) {}
    ZTEPanel(const std::string_view& ip, const std::string_view& password)
        : m_ip(ip), m_password(password) {}

    inline void Login() const noexcept {
        PostRequest(PrepaireURL("/reqproc/proc_post"),
                    "isTest=false&goformId=LOGIN&password=" +
                        Base64::EncodeString(GetPassword()));
    }

    inline void Reboot() const noexcept {
        PostRequest(PrepaireURL("/reqproc/proc_post"),
                    "isTest=false&goformId=REBOOT_DEVICE");
    }

    void Set(const std::string&, const std::string&,
             const std::string&) const noexcept;

  private:
    std::string m_ip;
    std::string m_password;

    inline std::string PrepaireURL(const std::string& path) const noexcept {
        return "http://" + GetIP() + path;
    }

    inline std::string GetIP() const noexcept { return m_ip; }

    inline std::string GetPassword() const noexcept { return m_password; }

    std::string GetRequest(const std::string&) const noexcept;

    std::string PostRequest(const std::string&,
                            const std::string&) const noexcept;
};
