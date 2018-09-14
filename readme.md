# Bake
### Bash-based build tool

## Installation
```sh
g++ -o bake bake.cpp
./bake install
```
This builds bake, then uses it to install itself. Now isn't that neat.

### Why is it useful?
It's really not yet. But its easier than learning `Makefile` so thats something.

### Roadmap
- make it actually useful by adding Bakers, background processes used to run things over SSH or other server things

### Usage
`bake` looks for a `Bakery` in your current directory, here is an example bakery:
```sh
#@bake
echo "This will be called when `bake` is run"
g++ -o coolprogram program.cpp -L./lib/ -l:libdep.a

#@install
echo "this will be called when `bake install` is run"
sudo cp coolprogram /usr/bin/coolprogram

#@test
g++ -o test test.cpp
echo "why are you even testing this way?"
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
#@bake
echo "this also works"
```
One space after the `#@` is allowed, but no more. 

