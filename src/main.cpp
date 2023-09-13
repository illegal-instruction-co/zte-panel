#include "ZTEPanel.h"

#include "Command.h"

#include <iostream>
#include <string_view>
#include <vector>

int main(int argc, char** argv) {
    using namespace std;

    string ip = "192.168.0.1";
    string password = "admin";

    static vector<Command> g_commands;

    g_commands.emplace_back("-i", "--ip", [&ip]() {
        cout << "IP address: ";
        cin >> ip;
    });

    g_commands.emplace_back("-p", "--password", [&password]() {
        cout << "Password: ";
        cin >> password;
    });

    g_commands.emplace_back("-s", "--set", [ip, password]() {
        string imei, wifiMac, lanMac;

        cout << "IMEI: ";
        cin >> imei;

        cout << "WIFI MAC: ";
        cin << wifiMac;

        cout << "LAN MAC: ";
        cin << lanMac;

        ZTEPanel panel(ip, password);
        panel.Login();
        panel.Set(imei, wifiMac, lanMac);
        panel.Reboot();
    });

    for (int i = 1; i < argc; ++i) {
        bool found = true;
        for (const auto& command : g_commands)
            if (command.Match(argv[i]))
                command.cb();
            else
                found = false;

        if (!found)
            cout << "Unknown command: " << argv[i] << endl;
    }

    return 0;
}
