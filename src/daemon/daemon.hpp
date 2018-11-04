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

using std::string;
using std::vector;

bool exists (string name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

void heartbeat() {
    vector<string> repos = refreshRepos();
}

vector< string > parseToLines(string path)
{
    vector< string > lines;
    string line;
    std::ifstream file (path);
    while ( file.is_open() )
    {
        while ( getline(file, line) )
        {
            lines.push_back(line);
        }
    }
    return lines;
}

vector< string > refreshRepos()
{
    if ( exists("/bake/repolist") )
    {
        return parseToLines("/bake/repolist");
    }
    else
    {
        return 
    }
}
