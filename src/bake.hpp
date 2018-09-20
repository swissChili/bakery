#include <iostream>
#include <string>
#include <regex>
#include <fstream>

using std::string;

namespace bake
{
  string sourceRecipe ( string recipe )
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
    system("bash ".append(tempDir));
    // attempt to delete the temp file
    if ( remove(tempDir) != 0 )
    {
      perror("Error removing temporary file!");
    }
    else
    {
      return 0;
    }
  }
}
