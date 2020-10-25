/**
 * Color class implementation.
 * @author const39
 */
#include "Color.hpp"

#include <regex>
#include <iostream>

using namespace std;

const int Color::F_Foreground = 0;
const int Color::F_Background = 1;

/**
 * Initialise the color by converting the given hex code (e.g. #AABBCC) to a 256 bits representation.
 * @param hex the hexadecimal code that will be converted to a 256 bits color code
 * @param f the format. Must be one of the class' public static constants available.
 * @throw invalid_argument if the given hex code is not valid.
 */
Color::Color(string hex, int f)
{
    const regex reg{"^#[A-Fa-f0-9]{6}$"};
    if (regex_match(hex, reg))
    {
        m_color = hexTo256(hex);
        m_format = f;
    } else throw invalid_argument("hex is not a valid Hexadecimal color code.");
}

/**
 * Create a transparent color. When used, it will clear any previous color and reset it to the terminal default.
 * @param f the format. Must be one of the class' public static constants available.
 */
Color::Color(int f) {

    m_color = Color::OFF;
    m_format = f;
}

/**
 * Convert a hexadecimal code color to a 256-bits representation.
 * @param value the hex color code. Note that no verification is done on the given hex code. The function behavior is not defined if the given string is not a valid 6 digits hex code.
 * @return a string containing a 256-bits color code.
 */
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

/**
 * Compute the color into a ANSI color code string usable by a terminal.
 * @return a ANSI color code string
 */
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