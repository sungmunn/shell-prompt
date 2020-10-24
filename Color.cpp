#include "Color.hpp"

#include <regex>
#include <iostream>

using namespace std;

const int Color::F_Bold = 0;
const int Color::F_Background = 1;

Color::Color(string hex, int f)
{
    const regex reg{"^#[A-Fa-f0-9]{6}$"};
    if (regex_match(hex, reg))
    {
        m_color = hexTo256(hex);
        m_format = f;
    } else throw invalid_argument("hex is not a valid Hexadecimal color code.");
}

Color::Color(int f) {

    m_color = Color::OFF;
    m_format = f;
}

string Color::hexTo256(string value)
{
    value.replace(0, 1, "0x");
    unsigned int rgb;
    stringstream sstream;
    sstream << hex << value;
    sstream >> rgb;

    unsigned int mask = 0xFF0000;
    unsigned int r = (rgb & mask) >> 16;
    mask >>= 8;
    unsigned int g = (rgb & mask) >> 8;
    mask >>= 8;
    unsigned int b = rgb & mask;

    return to_string(((r < 75 ? 0 : (r - 35) / 40) * 6 * 6 + (g < 75 ? 0 : (g - 35) / 40) * 6 + (b < 75 ? 0 : (b - 35) / 40) + 16));
}

string Color::toString()
{
    if(m_color == Color::OFF)
        return m_color;
    else {
        string prefix = "\033[";

        if (m_format == Color::F_Background)
            prefix += "48;5;";
        else
            prefix += "38;5;";

        return prefix + m_color + "m";
    }
}