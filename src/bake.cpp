#include <iostream>
#include <fstream>
#include <string>
#include "bake.hpp"

using std::string;
using std::cout;
using std::endl;

int main (int argc, char **argv)
{
  const string temp = ".bake.sh.temp";
  string version = "0.1.2";
  cout
    << "Reading Bakery    bake v"
    << version
    << endl;

  string parsed = bake::parseBakery(argc, argv);

  // modern c++ features are great!
  if ( parsed == "" )
    cout << "Failed to parse bakery!";
  else
    bake::sourceRecipe(parsed, temp);
}
