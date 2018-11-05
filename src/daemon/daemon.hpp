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
#include <cstddef>

using std::string;
using std::vector;

bool exists (string name) {
    struct stat buffer;   
    return (stat (name.c_str(), &buffer) == 0); 
}

void heartbeat() {
    chdir("/");
    std::ofstream heartbeat;
    heartbeat.open(".bake.log");
    heartbeat
        << "Log!"
        << std::endl;
    heartbeat.close();
}

bool cloneRepo(string repoName)
{
    string http ("http://");
    string https ("https://");

    string cloneUrl = repoName;

    std::size_t httpFound = repoName.rfind(http);
    std::size_t httpsFound = repoName.rfind(https);

    if ( httpFound!=std::string::npos )
        repoName.replace(httpFound, http.length(), "");
    else if ( httpsFound!=std::string::npos )
        repoName.replace(httpsFound, https.length(), "");
    else
        return false;

    // because sprintf is for nerds
    string cloneCommand = string("git clone ")
        .append(cloneUrl).append(" ~/.bake/")
        .append(repoName).append(" &> /dev/null");

    int ret = system(cloneCommand.c_str());

    if ( ret == 0 )
        return true;
    else
        return false;
}
