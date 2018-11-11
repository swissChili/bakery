#include <iostream>
#include <fstream>
#include <string>
#include "bake.hpp"

using std::string;
using std::cout;
using std::endl;


int main (int argc, char ** argv)
{
    const string temp = ".bake.sh.temp";

    string sargv[argc];
    bool test = false;

    for ( int i = 0; i < argc; ++i )
    {
        sargv[i] = string(argv[i]);
    }

    if ( sargv[1] == "-k" || sargv[1] == "--kill" )
    {
        if ( bake::kill() )
        {
            cout << "Killed successfully!";
            return 0;
        }
        else
        {
            cout << "Failed to kill! Is there a container running?";
            return 1;
        }
        cout << endl;
    }
    else if ( sargv[1] == "-t" || sargv[1] == "--test" )
    {
        test = true;
        cout
            << "Starting Test"
            << endl;
    }

    const string version = "0.1.3";
    cout
        << "Reading Bakery    bake v"
        << version
        << endl;

    string parsed = bake::parseBakery(argc, argv, test);
    // modern c++ == c# for not windows peasants
    if ( parsed == "" )
        cout << "Failed to parse bakery!";
    else
        bake::sourceRecipe(parsed, temp, test);
}
