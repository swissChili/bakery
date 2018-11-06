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

#ifndef _DAEMON_HPP
#define _DAEMON_HPP
bool exists (string name) {
    struct stat buffer;   
    return (stat (name.c_str(), &buffer) == 0); 
}

void heartbeat() {
    chdir("~");
    std::ofstream heartbeat;
    heartbeat.open(".bake.log");
    heartbeat
        << "Log!"
        << std::endl;
    heartbeat.close();
}
/**
 * Removes the http or https protocol from
 * the beginning of a string passed to this
 * function, used to get the directory to clone
 * repo to from it's remote url.
 */
string removeProtocol(string url)
{
    string http ("http://");
    string https ("https://");

    string cloneUrl = url;

    std::size_t httpFound = url.rfind(http);
    std::size_t httpsFound = url.rfind(https);

    if ( httpFound!=std::string::npos )
        url.replace(httpFound, http.length(), "");
    else if ( httpsFound!=std::string::npos )
        url.replace(httpsFound, https.length(), "");
    else
        return "";

    return url;
}
/**
 * Clones a repo into 
 * ~/.bake/repo/url.git
 */
bool cloneRepo(string repoName)
{
    string cloneUrl = repoName;

    repoName = removeProtocol(repoName);

    // because sprintf is for nerds
    // piping stuff to /dev/null is best error management
    string cloneCommand = string("git clone ")
        .append(cloneUrl).append(" ~/.bake/")
        .append(repoName).append(" &> /dev/null");

    int ret = system(cloneCommand.c_str());

    if ( ret == 0 )
        return true;
    else
        return false;
}
/**
 * the build function takes the repo URL as a 
 * parameter, changes into the directory it is cloned
 * and builds it with bake. If it does not exists it 
 * clones it and then builds
 */
bool build( string repoName )
{
    repoName = removeProtocol(repoName);

    string pullCommand = string("cd ~/.bake/")
        .append(repoName)
        .append(" && git pull &> /dev/null");
    int ret = system(pullCommand.c_str());
    if ( ret )
        return false;
    
    // build the repo
    chdir(string("~/.bake/").append(repoName).c_str());
    ret = system("/usr/bin/bake");
    if ( !ret )
        return true;
    else
        return false;
}

#endif