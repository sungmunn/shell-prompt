/**
 * Color class implementation.
 * @author const39
 */
#include "Color.hpp"

#include <regex>
#include <iostream>

using namespace std;

/**
 * Initialise the color by converting the given hex code to the chosen representation.
 * @param hex the hexadecimal code that will be converted to a 256 bits color code
 * @param useTrueColor indicates if the color coding is Truecolors or not. In the case it is not, a 256-bits color code will be used.
 * Truecolors use 24 bits to describe the colors. Allows to produce much more variety of colors but it more recent and as such not likely to be supported on older terminals.
 * Whereas 256Colors use 8 bits to describe the colors. Colors are not as detailed as with Truecolors but this encoding is older and supported by older terminals.
 * @param isBackground indicates if the color will be used as background or foreground.
 * @throw invalid_argument if the given hex code is not valid.
 * @see For Truecolors: https://tintin.mudhalla.net/info/truecolor/
 * @see For 256Colors: https://tintin.mudhalla.net/info/256color/
 */
Color::Color(string hex, bool useTrueColors, bool isBackground)
{
    const regex reg{"^#[A-Fa-f0-9]{6}$"};
    if (regex_match(hex, reg))
    {
        m_color = useTrueColors ? hexToRGB(hex) : hexTo256(hex);
        m_useTrueColors = useTrueColors;
        m_isBackground = isBackground;
    } else throw invalid_argument("hex is not a valid Hexadecimal color code.");
}

/**
 * Create a transparent color. When used, it will clear any previous color and reset it to the terminal default.
 * @param isBackground indicates if the color will be used as background or foreground.
 */
Color::Color(bool isBackground)
{
    m_color = Color::OFF;
    m_useTrueColors = false;    // Not using Truecolors but the standard ANSI color code to reset previous colors (see Color::OFF)
    m_isBackground = isBackground;
}

/**
 * Convert a hexadecimal code color to a 256-bits representation.
 * @param value the hex color code. No verification is done on the given hex code. The function behavior is not defined if the given string is not a valid 6 digits hex code.
 * @return a string containing a 256-bits color code.
 * @see https://tintin.mudhalla.net/info/256color/
 */
string Color::hexTo256(string value)
{
    /* Replace the '#' by '0x' to allow int conversion */
    value.replace(0, 1, "0x");

    /* Convert the string content to a hex int */
    unsigned int rgb;
    stringstream sstream;
    sstream << hex << value;
    sstream >> rgb;

    /* Extract R, G and B codes */
    unsigned int mask = 0xFF0000;
    unsigned int r = (rgb & mask) >> 16;
    mask >>= 8;
    unsigned int g = (rgb & mask) >> 8;
    mask >>= 8;
    unsigned int b = rgb & mask;

    return "5;" + to_string(((r < 75 ? 0 : (r - 35) / 40) * 6 * 6 + (g < 75 ? 0 : (g - 35) / 40) * 6 + (b < 75 ? 0 : (b - 35) / 40) + 16));
}

/**
 * Convert a hexadecimal code color to the TrueColors representation (on 24 bits).
 * @param value the hex color code. Note that no verification is done on the given hex code. The function behavior is not defined if the given string is not a valid 6 digits hex code.
 * @return a string containing a TrueColors color code.
 * @see https://tintin.mudhalla.net/info/truecolor/
 */
string Color::hexToRGB(string value) {

    /* Replace the '#' by '0x' to allow int conversion */
    value.replace(0, 1, "0x");

    /* Convert the string content to a hex int */ 
    unsigned int rgb;
    stringstream sstream;
    sstream << hex << value;
    sstream >> rgb;

    /* Extract R, G and B codes */
    unsigned int mask = 0xFF0000;
    unsigned int r = (rgb & mask) >> 16;
    mask >>= 8;
    unsigned int g = (rgb & mask) >> 8;
    mask >>= 8;
    unsigned int b = rgb & mask;

    return "2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b);
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
        prefix = prefix + (m_isBackground ? "48;" : "38;");

        return prefix + m_color + "m";
    }
}