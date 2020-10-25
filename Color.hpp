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
private:
    const string OFF = "\033[0m";   // Private preset for no-color
    string m_color;     // Color converted to encoded string
    bool m_useTrueColors; // Indicate which color coding to use 
    bool m_isBackground;  // Indicate if the color is fore or background
    string hexTo256(string value);
    string hexToRGB(string value);

public:
    Color(string hex, bool useTrueColors, bool isBackground);
    Color(bool isBackground);
    string toString();
};
