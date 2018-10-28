#include "bake.hpp"
#include <iostream>

using std::cout;
using std::endl;

int main ( int argc, char ** argv )
{
  if ( bake::kill() )
    cout << "Killed successfully" << endl;
  else
    cout << "Failed to kill, are any containers running?" << endl;
}