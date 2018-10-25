#include <iostream>
#include <string>
#include <regex>
#include <fstream>

using std::string;
using std::cout;
using std::endl;

namespace bake
{
  int sourceRecipe ( string recipe, string tempDir )
  {
    const string source = "source /usr/bin/baketools.sh";
    string command;
    command.append(source);
    command.append(recipe);
    std::ofstream tempCommand;
    tempCommand.open(tempDir);
    tempCommand << command;
    tempCommand.close();
    system(string("bash ").append(tempDir).c_str());
    // attempt to delete the temp file
    // converting to string back to c_str is a good idea
    system(string("rm ").append(tempDir).c_str());
    return 0;
  }
  string parseBakery ( int argc, char ** argv )
  {
    string line;
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
          if ( argc > 1 ) {
            targetCmd = argv[1];
          } else {
            targetCmd = "bake";
          }

          if ( command == targetCmd ) {
            incommand = true;
          } else {
            incommand = false;
          }

        }  else if ( incommand ) {
          fullCommand.append("\n");
          fullCommand.append(line);
        }
      }
      if ( fullCommand != "" )
      {
        return fullCommand;
      }
    }
    return "";
  }
}
