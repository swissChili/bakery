#include "baketools.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>

using std::string;
using std::cout;
using std::endl;
using std::ostringstream;

int main ( int argc, char ** argv )
{
  // welp nvm now this makes a container
  if ( argc >= 5 && argv[1] == "container" )
  {
    const char * cont_name = argv[2];
    const char * cont_img = argv[3];
    const char * cont_expose = argv[4];

    /*string docker_base = sprintf("FROM %s"
    "WORKDIR ."
    "CMD ['./bake']"
    "CMD ['./bake', 'deploy'"
    "EXPOSE %s", cont_img, cont_expose);
*/
  }
}
