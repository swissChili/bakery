#include <iostream>
#include <string>
#include <regex>

using std::string;

namespace bake
{
  std::regex include("#include.+\"(.+)\"");
  int parseIngredient ( string ingredientPath )
  {
    string line;
    std::ifstream ingredient (ingredientPath);
    if ( ingredient.is_open() )
    {
      int includes = 0;
      while ( getline(ingredient, line) )
      {
        std::smatch m;
        if ( std::regex_match (line, m, include) )
        {
          includes++;
          std::ssub_match smatch = m[1];
          string match = smatch.str();
          std::cout << match << std::endl;
        }
      }
      std::cout << includes << " includes found!" << std::endl;
      return includes;
    }
    else
    {
      std::cout << "Invalid Ingredient path in bakery" << std::endl;
      return 0;
    }
  }
}
