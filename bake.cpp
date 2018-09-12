#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::cout;

int main (int argc, char **argv)
{
  string line;
  bool incommand = false;
  string targetCmd;
  std::ifstream bakery ("Bakery");
  if ( bakery.is_open() )
  {
    while ( getline(bakery, line) )
    {
      if ( line.rfind("#", 0) == 0)
      {
        string command(line);
        command.replace(command.find("#"), 1, "");
        if ( argc > 1 ) {
          targetCmd = argv[1];
        } else {
          targetCmd = "bake";
        }

        if ( command == targetCmd )
        {
          incommand = true;
        } else {
          incommand = false;
        }

      } else if ( incommand == true ) {
        system(line.c_str());
      }
    }
  }
  else
  {
    cout << "unable to find Bakery" << std::endl;
  }
}
