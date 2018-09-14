# Bake
### Bash-based build tool

### Why is it useful?
Bash! its great, we all love it, and now you can more easily use it for building things.

Oh, and you dont need to have a bunch of `build.sh`, `install.sh`, `link.sh` scripts. all in one file!


### Roadmap
- make it actually useful by adding Bakers, background processes used to run things over SSH or other server things

### Usage
`bake` looks for a bakery in your current directory, here is an example bakery:
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
