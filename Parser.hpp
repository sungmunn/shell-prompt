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
    string m_text;
    vector<string> m_lines;
    vector<string> splitLines();

public:
    Parser(string text);
    vector<string> explode(char delim);
    vector<string> parseArrayAsStrings(string key);
    string parseString(string key);
};