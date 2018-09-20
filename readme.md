# Bake
### Bash-based build tool

## Installation
```sh
# change into the source director
cd src
# compile the main bake command
g++ -o bake bake.cpp
# Install using the Bakery
./bake install
```
This builds bake, then uses it to install itself. Now isn't that neat.

### Why is it useful?
Using Bash is nice, and you're probably already familiar with it. This way you don't have to learn anything else.

### Usage
`bake` looks for a `Bakery` in your current directory, here is an example bakery:
```sh
#@bake
echo "This will be called when `bake` is run"
# create a ingredient for the main c++ program
new_ingredient main src/main.cpp
new_ingredient another-thing src/thing.cpp
link_static main lib/libname.a
bake_all # bakes all the ingredients

#@install
echo "this will be called when `bake install` is run"
sudo cp coolprogram /usr/bin/coolprogram

#@test
g++ -o test test.cpp
echo "why are you even testing this way?"
new_recipe test src/test/test.cpp
link_static test src/lib/libthing.a
bake_all
./test
if [ $? -eq 0]
then
    echo "test succeeded"
else
    echo "test failed"
fi
```
Bakeries consist of recipes, and recipes are defined just like bash comments, so they are completely valid bash code.

Recipe definition can look like any of the following:
```sh
#@bake
echo "code here!"
#@ bake
echo "this also works"
```
One space after the `#@` is allowed, but no more. 

#### Bakery Functions
- `new_ingredient ingredient_name ingredient_path`
Creates an ingredient
- `link_static ingredient_name lib_path`
Adds the library to the list of libraries to link to the ingredient. Libraries will not be linked until the ingredient is baked.
- `bake_ingredient ingredient_name`
Bake the ingredient, including linking the specified libraries, using the `compiler` and `c_standard`. These default to `g++` and `c++17` respectively.
Change these simply by setting the variables to something else. These variables are recipe-specific, different compilers and c standards can be defined
for each recipe.
