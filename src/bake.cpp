#include <iostream>
#include <fstream>
#include <string>
#include "bake.hpp"

using std::string;
using std::cout;
using std::endl;

int main (int argc, char **argv)
{
  string version = "0.1.2";
  cout
    << "Reading Bakery    bake v"
    << version
    << endl;

  string parsed = bake::parseBakery(argc, argv);

  if ( parsed == "" )
    cout << "Failed to parse bakery!";
  else
    bake::sourceRecipe(parsed);
}
