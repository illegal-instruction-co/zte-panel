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
    string imei;
    string wifiMac;
    string lanMac;

    static vector<Command> g_commands;

    g_commands.emplace_back("-h", "--help", []() {
        cout << "-----------------------------------------" << endl;
        cout << "Set IP: -i or --ip" << endl;
        cout << "Set Password: -p or --password" << endl;
        cout << "Set IMEI: -im or --imei" << endl;
        cout << "Set WIFI MAC: -wm or --wifimac" << endl;
        cout << "Set LAN MAC: -lm or --lanmac" << endl;
        cout << "Set LAN MAC: -lm or --lanmac" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "Run settings: -s or --set" << endl;
        cout << "Example: ./Panel -i -p -im -s" << endl;
        cout << "-----------------------------------------" << endl;
    });

    g_commands.emplace_back("-i", "--ip", [&ip]() {
        cout << "IP address: ";
        cin >> ip;
    });

    g_commands.emplace_back("-p", "--password", [&password]() {
        cout << "Password: ";
        cin >> password;
    });

    g_commands.emplace_back("-im", "--imei", [&imei]() {
        cout << "IMEI: ";
        cin >> imei;
    });

    g_commands.emplace_back("-wm", "--wifimac", [&wifiMac]() {
        cout << "WIFI MAC: ";
        cin >> wifiMac;
    });

    g_commands.emplace_back("-lm", "--lanmac", [&lanMac]() {
        cout << "LAN MAC: ";
        cin >> lanMac;
    });


    g_commands.emplace_back("-s", "--set", [ip, password, imei, wifiMac, lanMac]() {
        ZTEPanel panel(ip, password);
        panel.Login();
        panel.Set(imei, wifiMac, lanMac);
        panel.Reboot();
    });

    if (!argc)
        g_commands[0].cb();
        
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
