#include <iostream>
#include <fstream>
#include <string>
#include "bake.hpp"

using std::string;
using std::cout;
using std::endl;

int main (int argc, char **argv)
{
  cout << "Reading Bakery" << endl;
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
      if ( bake::sourceRecipe(fullCommand) )
      {
        cout
          << "error baking recipe, fix your Bakery and try again"
          << endl;
      }
    }
  }
  else
  {
    cout << "unable to find Bakery, did you mean to run this in a different directory?" << endl;
  }
}
