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

void heartbeat() {
    std::ofstream log;
    log.open("/home/cake/bake.log", std::ios_base::app);
    log << "Log!";
    log.close();
}

int main ( int argc, char ** argv )
{
    if ( argc > 1 )
    {
        std::string arg = argv[1];
        if ( arg == "-q" || arg == "--quit" )
        {
            system("pkill -INT baked");
            std::cout
                << "Killed Daemon"
                << std::endl;
            return 0;
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

    while ( 1 )
    {
        heartbeat();
        sleep(1);
    }
}

