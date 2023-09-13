/**
 * @file main.cpp
 * @author mbk - mt - illegal-instruction-co (machinetherapist@gmail.com)
 * @date 2023-09-13
 *
 * @copyright Copyright (c) 2023
 *
 */

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
        cin >> wifiMac;

        cout << "LAN MAC: ";
        cin >> lanMac;

        ZTEPanel panel(ip, password);
        panel.Login();
        panel.Set(imei, wifiMac, lanMac);
        panel.Reboot();
    });

    for (int i = 1; i < argc; ++i) {
        bool found = false;
        for (const auto& command : g_commands)
            if (command.Match(argv[i])) {
                command.cb();
                found = true;
            }

        if (!found)
            cout << "Unknown command: " << argv[i] << endl;
    }

    return 0;
}
