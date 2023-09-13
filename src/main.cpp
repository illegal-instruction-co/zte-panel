#include "ZTEPanel.h"

#include <string>
#include <iostream>

int main()
{
    using namespace std;

    cout << "IP: ";
    string ip;
    cin >> ip;

    cout << "Password: ";
    string password;
    cin >> password;

    ZTEPanel panel(ip, password);
    cout << panel.Login() << endl;

    return 0;
}
