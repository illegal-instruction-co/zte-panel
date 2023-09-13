#include "ZTEPanel.h"

#include "URL.h"

using namespace std;

void ZTEPanel::Set(const std::string& imei, const std::string& wifiMac,
                   const std::string& lanMac) const noexcept {
    string payload = "isTest=false&goformId=set_mac_gmac_imei_val";

    if (!imei.empty())
        payload += "&imei_val=" + imei;

    if (!wifiMac.empty())
        payload += "&mac_val=" + URL::Encode(wifiMac);

    if (!lanMac.empty())
        payload += "&gmac_val=" + URL::Encode(lanMac);

    PostRequest(PrepaireURL("/reqproc/proc_post"), payload);
}

string ZTEPanel::GetRequest(const string& url) const noexcept try {
    http::Request request(url);

    const auto response = request.send("GET");
    return string(response.body.begin(), response.body.end());
} catch (const exception& e) {
    return e.what();
}

string ZTEPanel::PostRequest(const string& url,
                             const string& data) const noexcept try {
    http::Request request(url);

    const auto response = request.send(
        "POST", data, {{"Content-Type", "application/x-www-form-urlencoded"}});
    return string(response.body.begin(), response.body.end());
} catch (const exception& e) {
    return e.what();
}
