#include <string>
#include <iostream>
#include "bake.hpp"

using std::string;
using std::cout;
using std::endl;

int main ( int argc, char ** argv )
{
  // attempt to find the Container recipe and parse it
  const string temp = ".bake.sh.temp";

  int ac = 2;
  // c++ is hard
  char deploy[] = "deploy";
  char containerize[] = "container";
  char * av[2] = { deploy, containerize };

  string parsed = bake::parseBakery(ac, av);

  if ( parsed == "" )
    cout << "Failed to parse bakery!";
  else
    bake::sourceRecipe(parsed, temp);
}
