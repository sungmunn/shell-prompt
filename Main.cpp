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

// Preset gradients
vector<string> gradients = {"#b82929",
                            "#b0004b",
                            "#97086a",
                            "#cf6e00",
                            "#36e25c",
                            "#00b5b8",
                            "#247ba5",
                            "#48437a",
                            "#4c0031",
                            "#860136",
                            "#b82929"};



/**
 * Compute a string with color formatting using ANSI color codes.
 * @param name the text to color
 * @param font the text color
 * @param back the background color
 * @param fontTri the ending triangle color
 * @param backTri the ending triangle background color
 * @return a string with color formatting using ANSI color codes
 */  
string buildName(string name, Color &font, Color &back, Color &fontTri, Color &backTri)
{
    Color offBack(Color::F_Background); // Transparent background color
    Color offFront(Color::F_Bold);      // Transparent text color
    string tri = "";
    return back.toString() + font.toString() + " " + name + " " + offBack.toString() + offFront.toString() + backTri.toString() + fontTri.toString() + tri + offBack.toString() + offFront.toString();
}

int main()
{

    string text;
    fstream file;
    file.open("settings.conf", ios::in);
    if(file.is_open()) {
        string line;
        while (getline(file, line))
        {
            text += line + "\n";
        }
        file.close();
    }

    Parser parser(text);
    string val = parser.parseString("bold");
    cout << "bold=" << val << endl; 
    
    vector<string> vals = parser.parseArrayAsStrings("frontground");
    for (size_t i = 0; i < vals.size(); i++)
    {
        cout << vals[i] << endl; 
    }
    
    cout << endl;
    vals = parser.parseArrayAsStrings("background");
    for (size_t i = 0; i < vals.size(); i++)
    {
        cout << vals[i] << endl; 
    }
    








    // string path = get_current_dir_name();       // Get current working dir
    // vector<string> splittedPath = explode(path, '/');   // Split the string in a vector
    // splittedPath.at(0) = "/";   // Place '/' (root) as the first element

    // Color front("#FFFFFF", Color::F_Bold);  // Text color

    // for (size_t i = 0; i < splittedPath.size(); i++)    // Loop on all elements of the path vector
    // {
    //     string elem = splittedPath.at(i);

    //     Color frontTri(gradients[i], Color::F_Bold);    // Triangle color
    //     Color back(gradients[i], Color::F_Background);  // Text background color

    //     // Triangle background color : transparent if it's the last or equal to the next element color otherwise
    //     Color *backTri = NULL;
    //     if (i == splittedPath.size() - 1)
    //         backTri = new Color(Color::F_Background);
    //     else
    //         backTri = new Color(gradients[i + 1], Color::F_Background);
        
    //     cout << buildName(elem, front, back, frontTri, *backTri);   // Print the formatted text on the standard output
    //     delete backTri;
    // }
    // cout << " ";    // Ending margin
}