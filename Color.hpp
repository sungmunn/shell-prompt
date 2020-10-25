/**
 * Color class header.
 * @author const39
 */
#include <string>

using namespace std;

/**
 * Represent a Color. A color is defined by its hex code and a format.
 */
class Color
{
public:
    static const int F_Foreground;  // Preset for foreground color
    static const int F_Background;  // Preset for background color

private:
    const string OFF = "\033[0m";   // Private preset for no-color
    string m_color;     // Color converted to 256 bits
    int m_format;       // Value of the format (will be compared to the presets)
    string hexTo256(string value);

public:
    Color(string hex, int f);   
    Color(int f);
    string toString();
};
