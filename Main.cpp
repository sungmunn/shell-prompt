/**
 * main
 * @author const39
 */
#include "Color.hpp"
#include "Parser.hpp"

#include <unistd.h>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

/**
 * Compute a string with color formatting using ANSI color codes.
 * @param name the text to color
 * @param text the text color
 * @param back the background color
 * @param textTri the ending triangle color
 * @param backTri the ending triangle background color
 * @return a string with color formatting using ANSI color codes
 */
string buildName(string name, Color &text, Color &back, Color &textTri, Color &backTri)
{
    Color offBack(true);  // Transparent background color
    Color offFront(false); // Transparent text color
    string tri = "";
    return back.toString() + text.toString() + " " + name + " " + offBack.toString() + offFront.toString() + backTri.toString() + textTri.toString() + tri + offBack.toString() + offFront.toString();
}

/**
 * Read the configuration file.
 * @param filename the filename
 * @return the content of the file
 */
string readConfigFile(string filename)
{
    string text;
    fstream file;
    file.open("settings.conf", ios::in);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            text += line + "\n";
        }
        file.close();
    }
    return text;
}

int main()
{
    /* Settings */
    string text = readConfigFile("settings.conf");

    Parser parser(text);
    string useTrueColorStr = parser.parseString("truecolor");
    bool useTrueColor = useTrueColorStr == "true" ? true : false;
    vector<string> textColors = parser.parseArrayAsStrings("foreground");
    vector<string> backColors = parser.parseArrayAsStrings("background");

    /* Retrieve current path */
    string path = get_current_dir_name(); // Get current working dir
    Parser pathParser(path);
    vector<string> splittedPath = pathParser.explode('/'); // Split the string in a vector
    splittedPath.at(0) = "/";                              // Place '/' (root) as the first element

    for (size_t pathIndex = 0, textColorIndex = 0, backColorIndex = 0; pathIndex < splittedPath.size(); pathIndex++, textColorIndex++, backColorIndex++) // Loop on all elements of the path vector
    {
        string elem = splittedPath.at(pathIndex);

        Color text(textColors[textColorIndex], useTrueColor, false);      // Text color
        Color textTri(backColors[backColorIndex], useTrueColor, false);   // Triangle color
        Color back(backColors[backColorIndex], useTrueColor, true); // Text background color

        // Triangle background color : transparent if it's the last or equal to the next element color otherwise
        Color *backTri = NULL;
        if (pathIndex == splittedPath.size() - 1)
            backTri = new Color(true);
        else
            backTri = new Color(backColors[backColorIndex + 1 == backColors.size() ? 0 : backColorIndex + 1], useTrueColor, true);

        cout << buildName(elem, text, back, textTri, *backTri); // Print the formatted text on the standard output

        if (textColorIndex + 1 >= textColors.size())
            textColorIndex = -1;

        if (backColorIndex + 1 >= backColors.size())
            backColorIndex = -1;

        delete backTri;
    }
    cout << " "; // Ending margin
}