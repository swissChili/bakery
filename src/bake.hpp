#include <iostream>
#include <string>
#include <regex>
#include <fstream>

using std::string;
using std::cout;
using std::endl;

bool endsWith (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}


namespace bake
{
    int sourceRecipe ( string recipe, string tempDir, bool test )
    {
        const string source = "source /usr/bin/baketools.sh";
        string command;
        command.append(source);
        command.append(recipe);
        std::ofstream tempCommand;
        tempCommand.open(tempDir);
        tempCommand << command;
        tempCommand.close();
        int ret = system(string("bash ").append(tempDir).c_str()) / 256;
        // see how many tests succeeded and failed
        if ( test )
        {
            if ( ret == 0 )
            {
                cout
                    << "All tests passed!"
                    << endl;
            }
            else if ( ret == 1 )
            {
                cout
                    << "One test failed"
                    << endl;
            }
            else
            {
                cout
                    << ret
                    << " tests failed"
                    << endl;
            }
        }
        // attempt to delete the temp file
        // converting to string back to c_str is a good idea
        system(string("rm ").append(tempDir).c_str());
        return 0;
    }
    string parseBakery ( int argc, char ** argv, bool test )
    {
        string line;
        // this hideously verbose line tests for failure
        const string testCommand = " && echo -e \"\033[38;5;43m✓ Done\033[0m\"|| (c=$?; echo \"\033[38;5;203m🗴 Failed\033[0m\"; tests_failed=$((tests_failed+1)))";
        bool incommand = false;
        string fullCommand;
        string targetCmd;
        std::ifstream bakery ("Bakery");
        if ( bakery.is_open() )
        {
            while ( getline(bakery, line) )
            {
                if ( line.rfind("#@", 0) == 0)
                {
                    /**
                     * Parse the syntax for recipes:
                     * #@recipe || #@ recipe
                     */
                    string command(line);
                    command.replace(command.find("#@"), 2, "");
                    if ( command.rfind(" ", 0) == 0 ) {
                        command.replace(command.find(" "), 1, "");
                    }
                    if ( !test )
                    {
                        if ( argc > 1 )
                            targetCmd = argv[1];
                        else
                            targetCmd = "bake";
                    }
                    else
                    {
                        if ( argc > 2 )
                            targetCmd = argv[2];
                        else
                            targetCmd = "bake";
                    }

                    if ( command == targetCmd )
                        incommand = true;
                    else
                        incommand = false;

                }  else if ( incommand ) {
                    fullCommand.append("\n");
                    fullCommand.append(line);
                    // if the line doesn't end with a backslash, 
                    // append the test code to make sure the command
                    // exits with code `0`, only if in test mode
                    if ( !endsWith(line, "\\") && line != "" && test )
                    {
                        fullCommand.append("\ntest_command $?");
                    }
                }
            }
            if ( fullCommand != "" )
            {
                if ( test )
                    fullCommand.append("\ntests_passed");
                return fullCommand;
            }
        }
        return "";
    }

    bool kill ( void )
    {
        std::ifstream namelist (".container.name");
        string name;
        if ( namelist.is_open() )
        {
            while ( getline(namelist, name) )
            {
                system(string("sudo docker kill ").append(name).c_str());
            }
            system("rm .container.name");
            return true;
        }
        return false;
    }
}
