/**
 * Parser class implementation.
 * @author const39
 */
#include "Parser.hpp"

#include <regex>
#include <sstream>
#include <iostream>

using namespace std;

/**
 * Initialise the text to parse
 * @param text the text to parse
 */
Parser::Parser(string text)
{
    m_text = text;
    m_lines = splitLines(); // Pre-split the text into lines
}

/**
 * Split the text into a vector of lines.
 * @return a vector of strings containing each line
 */
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

/**
 * Search the text for the given key and parse its associated value as an array of string.
 * @param key the key of the line in the text
 * @return a vector of strings with the array values
 */
vector<string> Parser::parseArrayAsStrings(string key)
{
    // * Regex * :
    // Matches all lines which begin with the given key.
    // The associated value must be an array delimited by '[]'.
    // This pattern does not split the array into a chain of values.
    // The array content is a string of alphanumeric characters as well as '_', '#', ',', '"' and several types of spaces.  
    // Note that if the content contain multiple unescaped '"', it will still match the pattern.
    const regex reg{"^(" + key + ")=\\[([a-zA-Z0-9_#,\"\r\n\t\f\v ]*)\\]$"};
    smatch matches;

    string values = "";
    for (size_t i = 0; i < m_lines.size() && values == ""; i++)
    {
        if (regex_search(m_lines.at(i), matches, reg))
            values = matches[2].str();      // Extract the content of the array (second regex group)
    }

    Parser valuesParser(values);
    vector<string> parsedValues = valuesParser.explode(',');    // Split the array content by ',' to obtain a vector of values
    smatch matches2;
    vector<string> res;

    // * Regex * :
    // Matches all lines which begin and end with at least one '"'. Trailing spaces are allowed.
    // Note that a value with multiple unescaped '"' will match the pattern.
    // Each value inside the enclosing '"' can contain whatever character apart from '"'. This is because all '"' will be removed from the string.
    const regex reg2{"^[\r\n\t\f\v ]*\"+(.[^\"]*)\"+[\r\n\t\f\v ]*$"};

    for (size_t i = 0; i < parsedValues.size(); i++)
    {
        if(regex_search(parsedValues.at(i), matches2, reg2)) 
            res.push_back(matches2[1].str());   // Extract each value (removing the enclosing '"')
    }

    return res;
}

/**
 * Search the text for the given key and parse its associated value as a string.
 * @param key the key of the line in the text
 * @return the value
 */
string Parser::parseString(string key)
{
    // * Regex * :
    // Matches all lines which begin with the given key.
    // The associated value can or not be enclosed by '"'.
    // Note that a value with multiple unescaped '"' will match the pattern.
    // This pattern does not split the array into a chain of values.
    // The array content is a string of alphanumeric characters as well as '_', '#', ',', '"' and several types of spaces.
    const regex reg{"^(" + key + ")=\"*([a-zA-Z0-9_]*)\"*$"};
    smatch matches;

    string res = "";
    for (size_t i = 0; i < m_lines.size() && res == ""; i++)
    {
        if (regex_search(m_lines.at(i), matches, reg))
            res = matches[2].str(); // Extract each value (removing the enclosing '"')
    }
    return res;
}