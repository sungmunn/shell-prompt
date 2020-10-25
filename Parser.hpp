/**
 * Parser class header.
 * @author const39
 */
#include <string>
#include <regex>
#include <vector>

using namespace std;

class Parser
{
private:
    string m_text;              // the text to parse
    vector<string> m_lines;     // each text line
    vector<string> splitLines();

public:
    Parser(string text);
    vector<string> explode(char delim);
    vector<string> parseArrayAsStrings(string key);
    string parseString(string key);
};