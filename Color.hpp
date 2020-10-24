#include <string>

using namespace std;

class Color
{
public:
    static const int F_Bold;
    static const int F_Background;

private:
    const string OFF = "\033[0m";
    string m_color;
    int m_format;
    string hexTo256(string value);

public:
    Color(string hex, int f);
    Color(int f);
    string toString();
};
