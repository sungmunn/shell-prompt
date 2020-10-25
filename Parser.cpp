/**
 * Parser class implementation.
 * @author const39
 */
#include "Parser.hpp"

#include <regex>
#include <sstream>
#include <iostream>

using namespace std;

Parser::Parser(string text)
{
    m_text = text;
    m_lines = splitLines();
}

vector<string> Parser::splitLines()
{
    return explode('\n');
}

/**
 * Split a string in a vector of substrings delimited by a character.
 * @param delim the delimiter
 * @return a vector containing all substrings
 */
vector<string> Parser::explode(char delim)
{
    vector<string> result;
    stringstream data(m_text);

    while (getline(data, m_text, delim))
        result.push_back(m_text);

    return result;
}

// smatch* Parser::parseLine(const regex &regex)
// {
//     smatch *matches = NULL;

//     // string res = "";
//     // for (size_t i = 0; i < m_lines.size() && !matches; i++)
//     // {
//     //     if (regex_search(m_lines.at(i), *matches, regex))

//     //     // res = matches[0].str();
//     // }
//     return matches;
// }

vector<string> Parser::parseArrayAsStrings(string key)
{
    // const regex reg{"^(" + key + ")=\\[([a-zA-Z0-9_#,]*)\\]$"};
    const regex reg{"^(" + key + ")=\\[([a-zA-Z0-9_#,\"\r\n\t\f\v ]*)\\]$"};
    smatch matches;

    string values = "";
    for (size_t i = 0; i < m_lines.size() && values == ""; i++)
    {
        if (regex_search(m_lines.at(i), matches, reg)) 
            values = matches[2].str();
    }

    Parser valuesParser(values);
    vector<string> parsedValues = valuesParser.explode(',');
    smatch matches2;
    vector<string> res;
    const regex reg2{"^[\r\n\t\f\v ]*\"+(.[^\"]*)\"+[\r\n\t\f\v ]*$"};

    for (size_t i = 0; i < parsedValues.size(); i++)
    {
        if(regex_search(parsedValues.at(i), matches2, reg2)) 
            res.push_back(matches2[1].str());
    }

    return res;
}

string Parser::parseString(string key)
{
    const regex reg{"^(" + key + ")=\"*([a-zA-Z0-9_]*)\"*$"};
    smatch matches;

    string res = "";
    for (size_t i = 0; i < m_lines.size() && res == ""; i++)
    {
        if (regex_search(m_lines.at(i), matches, reg))
            res = matches[2].str();
    }
    return res;
}