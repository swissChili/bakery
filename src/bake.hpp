#include <iostream>
#include <string>
#include <regex>
#include <fstream>

using std::string;

namespace bake
{
  int sourceRecipe ( string recipe )
  {
    const string source = "source /usr/bin/baketools.sh";
    const string tempDir = "./~bakecommand_temp.sh";
    string command;
    command.append(source);
    command.append(recipe);
    std::ofstream tempCommand;
    tempCommand.open(tempDir);
    tempCommand << command;
    tempCommand.close();
    system(string("bash ").append(tempDir).c_str());
    // attempt to delete the temp file
    system(string("rm ").append(tempDir).c_str());
    return 0;
  }
}