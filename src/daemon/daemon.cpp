// that's a lotta includes
#include <dirent.h>
#include <iterator>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <syslog.h>
#include <unistd.h>
#include <vector>

#include "daemon.hpp"

using std::string;
using std::vector;

int main ( int argc, char ** argv )
{
    // convert to c++ string to make comparisons not awful
    string args[argc];
    for ( int i = 0; i < argc; ++i )
    {
        args[i] = string(argv[i]);
    }
    if ( argc > 1 )
    {
        string arg = args[1];
        if ( arg == "-q" || arg == "--quit" )
        {
            int ret = system("pkill -INT baked");
            if ( !ret )
            {
                std::cout
                    << "Killed Daemon"
                    << std::endl;
                return 0;
            }
            else
            {
                std::cout
                    << "Failed to kill daemon"
                    << std::endl;
                return 1;
            }
        }
    }
    pid_t pid, sid;

    pid = fork();
    if ( pid > 0 )
    {
        std::cout << "Worked!";
        return 0;
    }
    else if ( pid < 0 )
    {
        return -1;
    }
    // set necessary file permissions
    umask(0);

    sid = setsid();
    if ( sid < 0 )
    {
        syslog(LOG_ERR, "Could not generate SID");
    }

    bool clone = cloneRepo("https://github.com/swissChili/bakery.git");

    if ( clone )
        std::cout << "Cloned Successfully";
    else
        std::cout << "Failed to clone";
    std::cout << std::endl;

}
