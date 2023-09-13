#include "URL.h"

using namespace std;

string URL::Encode(const std::string &input)
{
    std::ostringstream encoded;
    encoded.fill('0');
    encoded << hex;

    for (char c : input)
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
            encoded << c;
        else if (c == ' ')
            encoded << '+';
        else
            encoded << '%' << setw(2) << int(static_cast<unsigned char>(c));

    return encoded.str();
}
