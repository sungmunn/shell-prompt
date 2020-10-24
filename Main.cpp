#include "Color.hpp"

#include <unistd.h>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

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

vector<string> explode(string str, char delim)
{
    vector<string> result;
    stringstream data(str);

    while (getline(data, str, delim))
        result.push_back(str);

    return result;
}

string buildName(string name, Color &font, Color &back, Color &fontTri, Color &backTri)
{
    Color offBack(Color::F_Background);
    Color offFront(Color::F_Bold);
    string tri = "";
    return back.toString() + font.toString() + " " + name + " " + offBack.toString() + offFront.toString() + backTri.toString() + fontTri.toString() + tri + offBack.toString() + offFront.toString();
}

int main()
{
    string path = get_current_dir_name();
    vector<string> splittedPath = explode(path, '/');
    splittedPath.at(0) = "/";

    Color front("#FFFFFF", Color::F_Bold);

    for (size_t i = 0; i < splittedPath.size(); i++)
    {
        string elem = splittedPath.at(i);

        Color frontTri(gradients[i], Color::F_Bold);
        Color back(gradients[i], Color::F_Background);

        Color *backTri = NULL;
        if (i == splittedPath.size() - 1)
            backTri = new Color(Color::F_Background);
        else
            backTri = new Color(gradients[i + 1], Color::F_Background);
        
        cout << buildName(elem, front, back, frontTri, *backTri);
        delete backTri;
    }
    cout << " ";
}