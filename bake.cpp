#include <iostream>
#include <fstream>
#include <string>
#include "./bake.hpp"

using std::string;
using std::cout;
using std::endl;

int main (int argc, char **argv)
{
  cout << "Reading Bakery" << endl;
  string line;
  bool incommand = false;
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

      } else if ( line.rfind("#&", 0) == 0 ){
        // enters if this is an ingredient
        cout << "Found an ingredient!" << line << endl;
        string command(line);
        command.replace(command.find("#&"), 2, "");
        bake::parseIngredient(command);
      } else if ( incommand == true ) {
        system(line.c_str());
      }
    }
  }
  else
  {
    cout << "unable to find Bakery, did you mean to run this in a differnet directory?" << endl;
  }
}
