#include "ZTEPanel.h"

using namespace std;

string ZTEPanel::Login() const noexcept
{
    const auto url = "http://" + GetIP() + "/reqproc/proc_post";
    const auto data = "isTest=false&goformId=LOGIN&password=" + Base64::EncodeString(GetPassword());
    return PostRequest(url, data);
}

string ZTEPanel::GetRequest(const string &url) const noexcept
try
{
    const auto now = chrono::system_clock::now();
    http::Request request(url);

    // send a get request
    const auto response = request.send("GET");
    return string(response.body.begin(), response.body.end());
}
catch (const exception &e)
{
    return e.what();
}

string ZTEPanel::PostRequest(const string &url, const string &data) const noexcept
try
{
    http::Request request(url);

    // send a post request
    const auto response = request.send("POST", data, {{"Content-Type", "application/x-www-form-urlencoded"}});
    return string(response.body.begin(), response.body.end());
}
catch (const exception &e)
{
    return e.what();
}
